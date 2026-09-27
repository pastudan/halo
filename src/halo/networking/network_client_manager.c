#include <stdint.h>
/* 0x1249b0 — network_game_server_dispose.
 * Tears down the network game client connection. If the server pointer is
 * non-null, closes its connection handle and clears the in-use flag. */
void network_game_server_dispose(void *server)
{
  if (server != NULL) {
    if (*(int *)((char *)server + 0x82c) != 0)
      network_connection_delete(*(int *)((char *)server + 0x82c));
    if (*(char *)0x46e8b9 == '\0') {
      display_assert("network_game_client_dont_use_directly_in_use",
                     "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                     0xb2, 1);
      system_exit(-1);
    }
    *(char *)0x46e8b9 = '\0';
  }
  network_game_log("network client disposed");
}

/* 0x124a30 — Returns the connection state (int16_t at offset 0xca6) and
 * optionally writes elapsed-time percentage into out_param. The time
 * calculation divides (current_ms - stored_ms) * 100 by 120000. */
int16_t network_game_client_get_state(void *server, void *out_param)
{
  unsigned int diff;

  assert_halt(server);
  if (out_param != NULL) {
    *(short *)out_param = 0;
    if (*(short *)((char *)server + 0xca6) == 1) {
      diff = system_milliseconds() * 100 -
             *(unsigned int *)((char *)server + 0x834) * 100;
      *(short *)out_param = (short)(diff / 120000);
    }
  }
  return *(int16_t *)((char *)server + 0xca6);
}

/* FUN_00124c40 (0x124c40)
 *
 * Asserts client is non-null and returns the client's 16-bit value at +0.
 */
uint16_t FUN_00124c40(void *client)
{
  uint16_t *client_words;

  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x1fd, true);
    system_exit(-1);
  }

  client_words = (uint16_t *)client;
  return client_words[0];
}

/* 0x124cc0 — Asserts client is non-null and returns the int16_t field at
 * offset 0xca8. */
int16_t FUN_00124cc0(void *server)
{
  assert_halt(server);
  return *(int16_t *)((char *)server + 0xca8);
}

/* 0x124d40 — Thin wrapper that tail-calls network_connection_write with the
 * same five arguments. The prologue sets up a frame (PUSH EBP / MOV EBP,ESP)
 * and immediately tears it down (POP EBP / JMP 0x128e00), so every argument
 * passes through to the callee unchanged. In the one observed call site
 * (network_game_client_end_frame), the caller resolves a server handle to a
 * connection pointer via network_game_client_get_seconds_to_game_start, then
 * calls this wrapper with the resulting connection pointer, a message buffer,
 * its size, a dest_address, and reliable=0. */
bool FUN_00124d40(void *connection, void *message, unsigned short size,
                  int dest_address, int reliable)
{
  return network_connection_write(connection, message, size, dest_address,
                                  reliable);
}

/* network_client_switch_to_postgame (0x125610) — readable C lift. */
extern char DAT_00291774[];
extern char DAT_002917a8[];
extern char DAT_00291f6c[];
void network_client_switch_to_postgame(void *client)
{
  if (client == 0) {
    display_assert(DAT_002917a8, DAT_00291774, 0x48c, 1);
    system_exit(-1);
  }
  game_engine_switch_to_postgame();
  *(uint16_t *)((char *)client + 0xca6) = 4;
  network_game_log(DAT_00291f6c);
}

/* 0x125710 — Asserts client is non-null and returns the connection handle
 * (int) stored at offset 0x82c in the client structure. The returned handle
 * is used by the caller (network_game_client_end_frame) as the first argument
 * to FUN_00124d40 (which forwards it to network_connection_write to send a
 * network message). */
int network_game_client_get_seconds_to_game_start(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x4b3, true);
    system_exit(-1);
  }
  return *(int *)((char *)client + 0x82c);
}

/* 0x125750 — Asserts client is non-null, then calls
 * network_connection_get_address with the connection handle at offset 0x82c,
 * the output buffer, and flag 0. */
void network_game_client_switch_to_postgame(void *server, void *out)
{
  assert_halt(server);
  network_connection_get_address(*(int *)((char *)server + 0x82c), out, 0);
}

/* network_game_client_get_machine_index (0x1257a0)
 *
 * Asserts client is non-null and returns client + 0x85c.
 */
void *network_game_client_get_machine_index(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x4cd, true);
    system_exit(-1);
  }

  return (void *)((uint8_t *)client + 0x85c);
}

/* 0x1257e0 — Asserts client is non-null and returns whether the int field at
 * offset 0xc98 is non-zero. */
bool network_game_client_get_available_games(void *server)
{
  assert_halt(server);
  return *(int *)((char *)server + 0xc98) != 0;
}

/* 0x125820 — Asserts client is non-null and returns the uint32_t field at
 * offset 0xc98 (the raw value that network_game_client_get_available_games
 * tests for non-zero). */
uint32_t network_game_client_get_error(void *server)
{
  assert_halt(server);
  return *(uint32_t *)((char *)server + 0xc98);
}

/* 0x125860 — Asserts client is non-null and returns the byte field at
 * offset 0xcac. */
bool network_client_get_oos(void *server)
{
  assert_halt(server);
  return *(char *)((char *)server + 0xcac);
}

/* FUN_00126000 (0x126000) — network_game_client_send_graceful_exit_pregame
 *
 * Periodically (every 1000ms) encodes and sends a
 * message_client_graceful_game_exit_pregame (type 0x13) containing the
 * multiplayer map name to the server connection. */
void FUN_00126000(void *server)
{
  int now;
  char *map_name;
  char buf[256];
  unsigned short *encoded;
  unsigned short size;

  now = system_milliseconds();
  if (*(int *)((char *)server + 0xca0) + 1000 < now) {
    map_name = main_get_multiplayer_map_name();
    *(int *)((char *)server + 0xca0) = now;
    if (cache_files_give_time_to_precache(map_name)) {
      csmemset(buf, 0, sizeof(buf));
      csstrncpy(buf, map_name, 0x100);
      encoded = (unsigned short *)encode_network_game_message(0x13, buf, 0x100);
      if (encoded != NULL) {
        size = *encoded >> 4;
        if (!network_connection_write((void *)*(int *)((char *)server + 0x82c),
                                      encoded, size, 0, 1)) {
          network_game_log("network_game_client_write() failed while sending a "
                           "message_client_graceful_game_exit_pregame message");
        }
      }
    }
  }
}

/* FUN_001260c0 (0x1260c0) — network_game_client_process_incoming_messages
 *
 * Drains all pending messages from the server connection. Loops calling
 * FUN_001298f0 to receive each message, then FUN_00127ea0 to handle it.
 * Returns true if all messages were processed successfully, false if any
 * handler fails. */
bool FUN_001260c0(void *server)
{
  bool result;
  char local_820[2048];
  char local_20[24];
  int local_8;

  result = true;
  do {
    local_8 = 0x800;
    if (!FUN_001298f0(*(int *)((char *)server + 0x82c), local_820, &local_8,
                      local_20))
      return result;
    result = FUN_00127ea0(server, local_820, local_8, local_20);
    if (!result)
      network_game_log("network_game_client_handle_message() failed in "
                       "network_game_client_process_incoming_messages()");
  } while (result);
  return result;
}

/* FUN_00126b60 (0x126b60) — network_game_client_idle_joining
 *
 * Called from the client idle dispatch (FUN_00127070) when state == 1
 * (joining). Verifies network connectivity, sends a join request once,
 * and checks for 120s timeout on the connect-process. Returns false
 * if connection drops, join request fails, or connection times out. */
bool FUN_00126b60(void *server)
{
  bool connected;
  unsigned char join_payload[0x50];
  unsigned short *encoded;
  int now_ms;
  int connect_handle;

  connected = true;
  if (!network_game_is_splitscreen_local()) {
    connected = transport_network_available();
    if (!connected) {
      error(2, "network connection went down!");
      display_error_when_main_menu_loaded(6);
    }
  }
  if (connected != true)
    return connected;

  if (network_connection_connected(*(int *)((char *)server + 0x82c))) {
    if ((*(unsigned char *)((char *)server + 0xcaa) & 2) == 0) {
      csmemset(join_payload, 0, 0x50);
      network_game_generate_local_machine_name(join_payload);
      csmemcpy(&join_payload[0x40], (char *)server + 0x84a, 0x10);
      encoded =
        (unsigned short *)encode_network_game_message(0xc, join_payload, 0x50);
      if (encoded == NULL) {
        network_game_log(
          "failed to create a message_client_join_game_request message");
      } else if (network_connection_write(
                   (void *)*(int *)((char *)server + 0x82c), encoded,
                   (unsigned short)(*encoded >> 4), 0, 1)) {
        *(unsigned char *)((char *)server + 0xcaa) =
          *(unsigned char *)((char *)server + 0xcaa) | 2;
      } else {
        network_game_log("network_game_client_write() failed to send a "
                         "message_client_join_game_request message");
      }
    }
    *(int *)((char *)server + 0x830) = 0;
  } else {
    connect_handle = *(int *)((char *)server + 0x830);
    if (connect_handle != 0) {
      now_ms = (int)system_milliseconds();
      if ((unsigned int)(now_ms - *(int *)((char *)server + 0x834)) > 120000) {
        network_game_log(
          "client connection process has timed out; aborting connection "
          "attempt");
        transport_server_terminate((int *)((char *)server + 0x830));
        *(int *)((char *)server + 0x830) = 0;
        return false;
      }
    }
  }

  connected = FUN_00129cf0(*(int *)((char *)server + 0x82c), 5000, 0);
  if (!connected) {
    network_game_log("network_connection_idle() failed in "
                     "network_game_client_idle_joining()");
    return false;
  }
  connected = FUN_001260c0(server);
  if (!connected) {
    network_game_log(
      "network_game_client_process_incoming_messages() failed in "
      "network_game_client_idle_joining()");
    return false;
  }
  return connected;
}

/* FUN_00126ce0 (0x126ce0) — network_game_client_idle_pregame
 *
 * Called from the client idle dispatch (FUN_00127070) when state == 2
 * (pregame). Checks network connectivity, processes the connection, and handles
 * incoming messages. Returns false if the connection drops or processing fails.
 */
bool FUN_00126ce0(void *server)
{
  bool result;

  result = true;
  if (network_game_is_splitscreen_local())
    goto check_result;
  result = transport_network_available();
  if (result)
    goto main_body;
  error(2, "network connection went down!");
  display_error_when_main_menu_loaded(6);

check_result:
  if (!result)
    goto tail_check;

main_body:
  if (!network_connection_active(*(int *)((char *)server + 0x82c)))
    goto fail;
  if (!network_connection_connected(*(int *)((char *)server + 0x82c)))
    goto fail;
  FUN_00126000(server);
  result = FUN_00129cf0(*(int *)((char *)server + 0x82c), 15000, 0);
  if (!result) {
    network_game_log("network_connection_idle() failed in "
                     "network_game_client_idle_pregame()");
    goto tail_check;
  }
  result = FUN_001260c0(server);
  if (result)
    return result;
  network_game_log("network_game_client_process_incoming_messages() failed in "
                   "network_game_client_idle_pregame()");
  goto tail_check;

fail:
  result = false;

tail_check:
  if (!network_connection_active(*(int *)((char *)server + 0x82c))) {
    display_error_when_main_menu_loaded(4);
    return false;
  }
  return result;
}

/* FUN_00126db0 (0x126db0) — network_game_client_idle_ingame
 *
 * Called from the client idle dispatch (FUN_00127070) when state == 3 (ingame).
 * Verifies the server connection is alive, checks if the connection has gone
 * silent (bit 5 of connection+0x30 via network_connection_going_stale),
 * displays per-player error widgets if newly silent, records the silent flag at
 * server+0xcad, then runs the connection idle tick (15-second timeout) and
 * processes incoming messages. Returns false if the connection drops or any
 * critical step fails.
 */
bool FUN_00126db0(void *server)
{
  int connection;
  bool result;
  bool is_silent;
  __int16 player_idx;

  result = true;
  connection = *(int *)((char *)server + 0x82c);
  if (!network_connection_active(connection))
    goto abort;
  if (!network_connection_connected(connection))
    goto abort;

  if (!network_game_is_splitscreen_local()) {
    is_silent = network_connection_going_stale(connection);
    if (!transport_network_available()) {
      error(2, "network connection went down (idle in game)!");
      display_error_when_main_menu_loaded(6);
      network_game_log("network connection went down (idle in game)!");
      result = false;
      goto write_flag;
    }
    if (is_silent && !*(char *)((char *)server + 0xcad)) {
      player_idx = local_player_get_next(-1);
      while (player_idx != (__int16)-1) {
        ui_widget_display_error(9, player_idx, 0, 0);
        player_idx = local_player_get_next(player_idx);
      }
      network_game_log(
        "network client connection has been silent for a dangerously long"
        " amount of time");
    }
  write_flag:
    *(char *)((char *)server + 0xcad) = (char)is_silent;
    if (!result)
      return result;
  }

  connection = *(int *)((char *)server + 0x82c);
  result = FUN_00129cf0(connection, 15000, 0);
  if (!result) {
    connection = *(int *)((char *)server + 0x82c);
    if (!network_connection_active(connection) ||
        !network_connection_connected(connection)) {
      error(2, "new2 idle in game abort hit");
      display_error_when_main_menu_loaded(4);
      result = false;
    }
    network_game_log(
      "network_connection_idle() failed in network_game_client_idle_ingame()");
    return result;
  }
  result = FUN_001260c0(server);
  if (!result)
    network_game_log("network_game_client_process_incoming_messages() failed in"
                     " network_game_client_idle_ingame()");
  return result;

abort:
  error(2, "new idle in game abort hit");
  display_error_when_main_menu_loaded(4);
  return false;
}

/* network_game_client_idle (0x126f40) — network_game_client_idle_postgame
 *
 * Called from the client idle dispatch (FUN_00127070) when state == 4
 * (postgame). Checks network connectivity, runs the connection idle with a
 * 15-second timeout, and processes incoming messages. Returns false if the
 * connection drops or processing fails. */
bool network_game_client_idle(void *server)
{
  bool result;

  result = true;
  if (network_game_is_splitscreen_local())
    goto check_result;
  result = transport_network_available();
  if (result)
    goto main_body;
  error(2, "network connection went down!");
  display_error_when_main_menu_loaded(6);

check_result:
  if (!result)
    goto tail_check;

main_body:
  result = FUN_00129cf0(*(int *)((char *)server + 0x82c), 15000, 0);
  if (!result) {
    network_game_log("network_connection_idle() failed in "
                     "network_game_client_idle_postgame()");
    goto tail_check;
  }
  result = FUN_001260c0(server);
  if (result)
    return result;
  network_game_log("network_game_client_process_incoming_messages() failed in "
                   "network_game_client_idle_postgame()");

tail_check:
  if (!network_connection_active(*(int *)((char *)server + 0x82c))) {
    display_error_when_main_menu_loaded(4);
    return false;
  }
  return result;
}

/* 0x127070 — Network client idle dispatch: asserts client non-null, switches
 * on the connection state at offset 0xca6, and calls the appropriate
 * state-specific idle handler. Logs and returns false on handler failure. */
bool FUN_00127070(void *server)
{
  bool result;

  result = 0;
  assert_halt(server);
  switch (*(unsigned short *)((char *)server + 0xca6)) {
  case 0:
    result = FUN_001268a0(server);
    if (!result) {
      network_game_log("network_game_client_idle_searching() failed");
      return 0;
    }
    break;
  case 1:
    result = FUN_00126b60(server);
    if (!result) {
      network_game_log("network_game_client_idle_joining() failed");
      return 0;
    }
    break;
  case 2:
    result = FUN_00126ce0(server);
    if (!result) {
      network_game_log("network_game_client_idle_pregame() failed");
      return 0;
    }
    break;
  case 3:
    result = FUN_00126db0(server);
    if (!result) {
      network_game_log("network_game_client_idle_ingame() failed");
      return 0;
    }
    break;
  case 4:
    result = network_game_client_idle(server);
    if (!result) {
      network_game_log("network_game_client_idle_postgame() failed");
      return 0;
    }
    break;
  default:
    assert_halt(!"unknown client state");
  }
  return result;
}
/* --- network_client_manager.obj batch drafts (2026-07-26) --- */

static __attribute__((unused)) char network_client_manager_send_encoded(void *client, void *encoded)
{
  unsigned short size;
  int connection;

  if (encoded == NULL)
    return 0;
  connection = *(int *)((char *)client + 0x82c);
  size = (unsigned short)(*(unsigned short *)encoded >> 4);
  if (!network_connection_write((void *)connection, encoded, size, 0, 1))
    return 0;
  return 1;
}

/* FUN_00124730 (0x124730) — Capstone tip: node_matrices NULL → assert. */
int16_t FUN_00124730(int model_ref, const char *marker_name, char *magic_table,
                     int node_remap, int16_t node_count, void *node_matrices,
                     char mirrored, void *out_markers, int16_t max_markers)
{
  (void)magic_table;
  (void)node_remap;
  (void)node_count;
  (void)mirrored;
  (void)out_markers;
  (void)max_markers;
  FUN_00123d80(model_ref, (char *)marker_name);
  if (node_matrices == 0) {
    display_assert((char *)0x29171c, (char *)0x291564, 0x2f8, 1);
    system_exit(-1);
  }
  return 0;
}


/* FUN_00124900 (0x124900) — readable C lift. */
void FUN_00124900(void *model)
{
  void *block;
  short i;
  short j;
  void *elem;
  void *inner;

  block = (char *)model + 0xd0;
  i = 0;
  if (*(int *)block <= 0)
    return;
  for (;;) {
    elem = tag_block_get_element(block, (int)i, 0x30);
    inner = (char *)elem + 0x24;
    j = 0;
    if (*(int *)inner > 0) {
      for (;;) {
        tag_block_get_element(inner, (int)j, 0x68);
        j++;
        if ((int)j >= *(int *)inner)
          break;
      }
    }
    i++;
    if ((int)i >= *(int *)block)
      break;
  }
}


/* network_game_client_keep_alive (0x124a10) — readable C lift. */
void network_game_client_keep_alive(void *client)
{
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
}

/* network_game_client_initiate_join_game (0x124aa0) — readable C lift. */
char network_game_client_initiate_join_game(void *client, void *game, void *join_token,
                                            void *address)
{
  int connection;
  char ok;

  if (!client || *(int16_t *)((char *)client + 0xca6) != 0 || !game ||
      !join_token || !(connection = *(int *)((char *)client + 0x82c)) ||
      network_connection_connected(connection) ||
      *(int16_t *)((char *)game + 0xde) != 0) {
    display_assert((const char *)0x291810, (const char *)0x291774, 0x157, 1);
    system_exit(-1);
  }

  *(int *)((char *)client + 0xc90) = 1;
  *(int *)((char *)client + 0x830) = 0;
  *(unsigned int *)((char *)client + 0x834) = system_milliseconds();
  csmemcpy((char *)client + 0x838, join_token, 0x22);
  ok = network_connection_connect(connection, (int)address, 0);
  if (ok == 1) {
    *(int16_t *)((char *)client + 0xca6) = 1;
    network_game_log((const char *)0x2917e8, transport_address_to_string(address));
  } else {
    display_error_when_main_menu_loaded(7);
    network_game_log((const char *)0x2917b0, transport_address_to_string(address));
  }
  return ok;
}


/* network_game_client_set_machine (0x124ba0) — readable C lift. */
char network_game_client_set_machine(void *client, void *machine)
{
  unsigned short idx;
  char *dst;

  if (client == 0 || *(unsigned short *)client >= 4 || machine == 0) {
    display_assert((const char *)0x2918f8, (const char *)0x291774, 0x1e1, 1);
    system_exit(-1);
  }
  if (*(signed char *)((char *)machine + 0x40) < 0 ||
      *(signed char *)((char *)machine + 0x40) >= 4) {
    display_assert((const char *)0x2918f8, (const char *)0x291774, 0x1e1, 1);
    system_exit(-1);
  }
  idx = *(unsigned short *)client;
  dst = (char *)client + 0x970 + (int)idx * 0x44;
  csmemcpy(dst, machine, 0x44);
  return 1;
}

/* network_game_client_get_machine (0x124c10) — readable C lift. */
void *network_game_client_get_machine(void *client)
{
  unsigned short idx;
  if (!client) return 0;
  idx = *(unsigned short *)client;
  if (idx >= 4) return 0;
  return (char *)client + 0x970 + (int)idx * 0x44;
}

/* 0x124c80 */
void *FUN_00124c80(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2ac, 1);
    system_exit(-1);
  }
  return (void *)((char *)client + 4);
}

/* FUN_00124d00 (0x124d00) — readable C lift (assert wrapper). */
int16_t FUN_00124d00(void *client)
{
  if (client == NULL) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x2bc, 1);
    system_exit(-1);
  }
  return *(uint16_t *)((char *)client + 0xca4);
}

/* network_game_client_address_matches_server (0x124d50) — readable C lift from XBE leaf. */
char network_game_client_address_matches_server(void *client, void *source_address)
{
  extern char DAT_00291774[];
  extern char DAT_002919a4[];
  extern char DAT_00291990[];
  extern char DAT_00291980[];
  extern char DAT_00291960[];
  unsigned char addr_buf[0x18];
  int connection;

  if (client == 0) {
    display_assert(DAT_002919a4, DAT_00291774, 0x2d2, true);
    system_exit(-1);
  }
  connection = *(int *)((char *)client + 0x82c);
  if (connection == 0) {
    display_assert(DAT_00291990, DAT_00291774, 0x2d3, true);
    system_exit(-1);
  }
  if (source_address == 0) {
    display_assert(DAT_00291980, DAT_00291774, 0x2d4, true);
    system_exit(-1);
  }
  if (*(int *)source_address == 0) {
    display_assert(DAT_00291960, DAT_00291774, 0x2d5, true);
    system_exit(-1);
  }
  network_connection_get_address(connection, addr_buf, 0);
  return *(int *)source_address == *(int *)addr_buf;
}

#define FUN_00124d50 network_game_client_address_matches_server


/* network_game_client_game_out_of_sync (0x124e20) — readable C lift. */
void network_game_client_game_out_of_sync(void *client)
{
  extern char DAT_002919b4[];
  __int16 player;

  if (*(unsigned char *)0x46e8b8 != 0)
    return;
  network_game_log(DAT_002919b4);
  if (*((unsigned char *)client + 0xcac) == 0) {
    player = local_player_get_next(-1);
    while (player != -1) {
      ui_widget_display_error(8, player, 1, 0);
      player = local_player_get_next(player);
    }
  }
  *((unsigned char *)client + 0xcac) = 1;
}


/* FUN_00124e90 (0x124e90) — readable C lift. */
void FUN_00124e90(void *client, int *token, unsigned int now_ms)
{
  unsigned int t;
  unsigned short count;
  unsigned short avg;
  unsigned int product;
  unsigned int rem;

  if (client == 0 || token == 0) {
    display_assert((const char *)0x291a3c, (const char *)0x291774, 0x307, 1);
    system_exit(-1);
  }
  if (*(char *)((char *)client + 0x82a) == 0) {
    network_game_log((const char *)0x2919e4);
    return;
  }
  if (*(int *)((char *)client + 0x808) != *token) {
    network_game_log((const char *)0x2919e4);
    return;
  }
  t = system_milliseconds();
  if (now_ms > t) {
    network_game_log((const char *)0x291a1c);
    return;
  }
  count = *(unsigned short *)((char *)client + 0x826);
  avg = *(unsigned short *)((char *)client + 0x828);
  product = (unsigned int)avg * (unsigned int)count;
  rem = product - now_ms + t;
  count = (unsigned short)(count + 1);
  avg = (unsigned short)(rem / (unsigned int)((unsigned short)count));
  *(unsigned short *)((char *)client + 0x826) = count;
  *(unsigned short *)((char *)client + 0x828) = avg;
}



/* network_game_client_accepted_into_game (0x124f40) — readable C lift. */
void network_game_client_accepted_into_game(void *client, void *source, void *message)
{
  short idx;
  char namebuf[0x44];
  void *msg;
  unsigned short size;

  if (!client || !source || !message ||
      *(short *)((char *)client + 0xca6) != 1) {
    display_assert((const char *)0x291b70, (const char *)0x291774, 0x327, 1);
    system_exit(-1);
  }
  idx = *(short *)((char *)message + 4);
  if (idx < 0 || idx >= 4) {
    network_game_log((const char *)0x291a58);
    return;
  }
  *(short *)client = idx;
  *((char *)client + 0x9b0 + 0x44 * (int)idx) = *(char *)((char *)message + 4);
  *(short *)((char *)client + 0xca6) = 2;
  network_game_set_random_seed(*(int *)message);
  network_game_log((const char *)0x291b3c, (int)idx);
  network_game_generate_local_machine_name(namebuf);
  namebuf[0x40] = *(char *)((char *)message + 4);
  msg = encode_network_game_message(0xf, namebuf, 0x44);
  if (!msg) {
    network_game_log((const char *)0x291aa4);
    return;
  }
  size = (unsigned short)((*(unsigned short *)msg) >> 4);
  if (!network_connection_write(*(void **)((char *)client + 0x82c), msg, size, 0,
                                1))
    network_game_log((const char *)0x291ae0);
}

/* network_game_client_game_settings_updated (0x125050) — readable C lift. */
char network_game_client_game_settings_updated(void *client, void *message)
{
  int16_t max_players;
  int16_t something;
  char *map_name;
  char old_settings[0x434];

  if (!client || !message) {
    display_assert((const char *)0x291cd8, (const char *)0x291774, 0x375, 1);
    system_exit(-1);
  }
  max_players = *(int16_t *)((char *)message + 0x112);
  something = *(int16_t *)((char *)message + 0x224);
  if (max_players < 0 || max_players > 4 || something < 0 || something > 0x10) {
    network_game_log((const char *)0x291bd8, (int)something, (int)max_players);
    return 0;
  }
  map_name = (char *)message + 0x24;
  if (csstrcmp(map_name, (char *)client + 0x880) != 0) {
    network_game_log((const char *)0x291cc0, map_name);
    main_set_multiplayer_map_name(map_name);
  }
  csmemcpy(old_settings, (char *)client + 0x85c, 0x434);
  csmemcpy((char *)client + 0x85c, message, 0x434);
  csmemcpy((char *)client + 0xc8c, old_settings + 0x430, 4);
  network_game_log((const char *)0x291c60, (int)something, (int)max_players);
  network_game_log((const char *)0x291c38, (int)something, (int)max_players);
  return 1;
}


/* unstrip_player_index (0x125180) — readable C lift. */
int unstrip_player_index(int stripped_index)
{
  data_iter_t iter;
  int found = -1;
  int cur;
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  cur = data_iterator_next(&iter);
  while (cur) {
    int h = *(int *)((char *)&iter + 8); /* datum handle at iter+8 from asm [ebp-8] */
    if ((h & 0xffff) == (stripped_index & 0xffff)) {
      found = h;
      break;
    }
    cur = data_iterator_next(&iter);
  }
  return found;
}
/* network_game_client_game_has_started (0x1251e0) — readable C lift (restored pre-naked). */
char network_game_client_game_has_started(void *client)
{
  int slot;
  int16_t machine_index;
  char *player_rec;
  void *encoded;
  int local_index;

  if (client == NULL || *(int16_t *)((char *)client + 0xca6) != 2) {
    display_assert("client && (client->state == _network_game_client_state_pregame)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x3b0, 1);
    system_exit(-1);
  }

  *(int16_t *)((char *)client + 0xca4) = (int16_t)-1;
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
  if (!network_game_create_game_objects((char *)client + 0x85c))
    goto fail;

  machine_index = *(uint16_t *)client;
  slot = 0;
  player_rec = (char *)client + 0xa9e;
  while (slot < 0x10) {
    if (*(char *)(player_rec - 0x1c) == (char)machine_index &&
        network_player_is_valid((void *)(player_rec - 0x1c))) {
      local_index = unstrip_player_index((int)*(char *)(player_rec + 3));
      local_player_set_player_index(local_index, *(int16_t *)(player_rec + 1));
      player_rec += 0x20;
      slot++;
      continue;
    }
    break;
  }

  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
  {
    int loaded_payload = 0;
    encoded = encode_network_game_message(0x18, &loaded_payload, 4);
  }
  if (encoded == NULL) {
    network_game_log("failed to create a message_client_loaded message");
    goto fail;
  }
  if (!network_client_manager_send_encoded(client, encoded)) {
    network_game_log("network_game_client_write() failed while sending a "
                     "message_client_loaded message");
    goto fail;
  }
  network_game_log("local machine is loaded & ready to play");
  *(int16_t *)((char *)client + 0xca6) = 3;
  *(int *)((char *)client + 0xc98) = 0;
  *(int *)((char *)client + 0xc9c) = 0;
  *(char *)((char *)client + 0xcad) = 0;
  ui_widgets_close_all();
  game_time_start();
  game_initial_pulse();
  return (char)(*(int16_t *)((char *)client + 0xca6) == 3);

fail:
  network_game_log("failed to load the necessary game data");
  return (char)(*(int16_t *)((char *)client + 0xca6) == 3);
}


/* network_game_client_handle_game_update (0x125380) — Capstone tip: null client/message → assert. */
char network_game_client_handle_game_update(void *client, void *message)
{
  if (client == NULL || message == NULL) {
    display_assert((char *)0x291cd8, (char *)0x291774, 0x40d, 1);
    system_exit(-1);
  }
  return 0;
}


/* network_game_client_add_player_to_game (0x125510) — readable C lift. */
char network_game_client_add_player_to_game(void *client, void *message)
{
  char ok;
  char *player_slot;
  int stripped;
  int unstripped;

  ok = 0;
  if (!client || !message) {
    display_assert((const char *)0x291f58, (const char *)0x291774, 0x462, 1);
    system_exit(-1);
  }
  if (!network_player_is_valid(message))
    return 0;
  ok = network_game_add_player((char *)client + 0x85c, message);
  if (!ok)
    return 0;
  if (*(short *)((char *)client + 0xca6) == 3) {
    player_slot = (char *)client + 0xa62 +
                  ((int)*(short *)((char *)client + 0xa80) << 5);
    ok = network_game_spawn_player(player_slot);
    if (!ok)
      return 0;
    unstripped = unstrip_player_index((int)*(signed char *)(player_slot + 0x1f));
    if ((int)*(signed char *)(player_slot + 0x1c) ==
        (int)*(unsigned short *)client) {
      local_player_set_player_index((unsigned short)*(signed char *)(player_slot + 0x1d),
                                    unstripped);
    }
    update_client_add_player(unstripped);
    if (network_game_server_get())
      FUN_000b8d30(unstripped);
    network_game_log((const char *)0x291f1c,
                     (int)*(signed char *)(player_slot + 0x1c),
                     (int)*(signed char *)(player_slot + 0x1d));
  } else {
    network_game_log((const char *)0x291f1c,
                     (int)*(signed char *)((char *)message + 0x1c),
                     (int)*(signed char *)((char *)message + 0x1d));
  }
  return ok;
}

/* network_game_client_switch_to_pregame (0x125660) — readable C lift. */
char network_game_client_switch_to_pregame(void *client)
{
  extern char DAT_002917a8[];
  extern char DAT_00291774[];
  extern char DAT_00291f84[];

  if (client == 0) {
    display_assert(DAT_002917a8, DAT_00291774, 0x499, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)client + 0xca6) != 2) {
    network_game_reset_for_next_round((char *)client + 0x85c, 1);
    network_connection_keep_alive(*(int *)((char *)client + 0x82c));
    *(int *)((char *)client + 0xc98) = 0;
    *(int *)((char *)client + 0xc90) = 1;
    *(int *)((char *)client + 0xc9c) = 0;
    *((unsigned char *)client + 0xcad) = 0;
    *(short *)((char *)client + 0xca6) = 2;
    *((unsigned char *)client + 0xcac) = 0;
    network_game_log(DAT_00291f84);
    network_game_reset_to_pregame_ui();
    network_connection_keep_alive(*(int *)((char *)client + 0x82c));
  }
  return 1;
}



static __attribute__((unused)) char network_client_manager_send_player_request(void *client, void *payload,
                                                       int msg_type,
                                                       const char *fail_create,
                                                       const char *fail_write)
{
  void *encoded;
  unsigned short size;

  encoded = encode_network_game_message(msg_type, payload, 0x20);
  if (encoded == NULL) {
    network_game_log(fail_create);
    return 0;
  }
  size = (unsigned short)(*(unsigned short *)encoded >> 4);
  if (!network_connection_write((void *)*(int *)((char *)client + 0x82c), encoded,
                                size, 0, 1)) {
    network_game_log(fail_write);
    return 0;
  }
  return 1;
}

/* network_game_client_add_player (0x1258a0) — readable C lift (restored pre-naked). */
char network_game_client_add_player(void *client, int16_t local_player_index)
{
  char profile[0x70];
  char payload[0x40];
  char result;
  int16_t state;

  result = 1;
  if (client == NULL || local_player_index < 0 || local_player_index >= 4) {
    display_assert("client && (local_player_index>=0) && "
                   "(local_player_index<MAXIMUM_NUMBER_OF_LOCAL_PLAYERS)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x530, 1);
    system_exit(-1);
  }

  {
    void (*get_profile)(void *, int16_t) =
      (void (*)(void *, int16_t))player_ui_get_active_player_profile;
    get_profile(profile, local_player_index);
  }
  csmemset(payload, 0, sizeof(payload));
  payload[0] = (char)*(uint16_t *)client;
  payload[1] = (char)local_player_index;
  ustrncpy((wchar_t *)(payload + 0x20), (wchar_t *)(profile + 0x38), 0xb);

  network_game_log("requesting a player addition (controller index #%d)",
                   (int)local_player_index);
  state = *(int16_t *)((char *)client + 0xca6);
  switch (state) {
  case 0:
  case 1:
    network_game_log("can't add players to a game until after a game is joined");
    result = 0;
    break;
  case 2:
    result = network_client_manager_send_player_request(
      client, payload, 0xd,
      "failed to create a message_client_add_player_request_pregame message",
      "network_game_client_write() failed while sending a "
      "message_client_add_player_request_pregame message");
    break;
  case 3:
    result = network_client_manager_send_player_request(
      client, payload, 0x1a,
      "failed to create a message_client_add_player_request_ingame message",
      "network_game_client_write() failed while sending a "
      "message_client_add_player_request_ingame message");
    break;
  case 4:
    network_game_log("client tried to add a new player in post-game");
    result = 0;
    break;
  default:
    network_game_log("client is in an unknown state");
    result = 0;
    break;
  }
  return result;
}


/* network_game_client_update_local_player_data (0x125a90) — readable C lift. */
char network_game_client_update_local_player_data(void *client, void *player)
{
  char copy[0x20];
  void *msg;
  unsigned short size;

  if (!client || !player) {
    display_assert((const char *)0x291f58, (const char *)0x291774, 0x587, 1);
    system_exit(-1);
  }
  if ((int)*(signed char *)((char *)player + 0x1c) !=
      (int)*(unsigned short *)client) {
    display_assert((const char *)0x2922b8, (const char *)0x291774, 0x588, 1);
    system_exit(-1);
  }
  if (!network_player_is_valid(player)) {
    display_assert((const char *)0x292298, (const char *)0x291774, 0x589, 1);
    system_exit(-1);
  }
  csmemcpy(copy, player, 0x20);
  if ((unsigned char)copy[0x1e] == 0xff)
    copy[0x1e] = 0;
  msg = encode_network_game_message(0x10, copy, 0x20);
  if (!msg)
    return 0;
  size = (unsigned short)((*(unsigned short *)msg) >> 4);
  if (!network_connection_write(*(void **)((char *)client + 0x82c), msg, size, 0,
                                1)) {
    network_game_log((const char *)0x292220);
    return 0;
  }
  return 1;
}

/* FUN_00125b90 (0x125b90) — readable C lift: send client request message. */
char FUN_00125b90(void *client, short request_type)
{
  void *msg;
  unsigned short size;

  if (!client) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x5a5, 1);
    system_exit(-1);
  }
  if (request_type < 0 || request_type >= 4) {
    display_assert((const char *)0x2923b8, (const char *)0x291774, 0x5a6, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)client + 0xca6) != 2) {
    network_game_log((const char *)0x2922e8);
    return 1;
  }
  msg = encode_network_game_message(0x11, &request_type, 2);
  if (!msg)
    return 1;
  size = (unsigned short)((*(unsigned short *)msg) >> 4);
  if (!network_connection_write(*(void **)((char *)client + 0x82c), msg, size, 0, 1))
    network_game_log((const char *)0x292348);
  return 1;
}

/* network_game_client_countdown_timer_update (0x125c60) — readable C lift (assert wrapper). */
void network_game_client_countdown_timer_update(void *client, int16_t timer)
{
  if (client == NULL) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x5c3, 1);
    system_exit(-1);
  }
  *(uint16_t *)((char *)client + 0xca4) = (uint16_t)timer;
}

/* network_game_client_advertised_game_is_valid (0x125cb0) — readable C lift. */
char network_game_client_advertised_game_is_valid(void *game)
{
  unsigned char *g = (unsigned char *)game;
  if (g[0xe1] == 0)
    return 0;
  if ((int)(system_milliseconds() - *(unsigned int *)(g + 0x2c)) > 0x1770)
    return 0;
  return 1;
}
/* FUN_00125ce0 (0x125ce0) — Capstone tip: empty slot 0 → fill → return 1. */
char FUN_00125ce0(uintptr_t slot_array, uintptr_t advertised_game /*@<edi>*/)
{
  (void)slot_array;
  (void)advertised_game;
  return 1;
}


/* FUN_00125fb0 (0x125fb0) — readable C lift. */
void FUN_00125fb0(void *client, int16_t reason)
{
  extern char DAT_002917a8[];
  extern char DAT_00291774[];
  if (!client) {
    display_assert(DAT_002917a8, DAT_00291774, 0x662, 1);
    system_exit(-1);
  }
  if ((uint16_t)reason >= 9) {
    reason = 1;
  }
  if (*(int16_t *)((char *)client + 0xca8) == 0) {
    *(int16_t *)((char *)client + 0xca8) = reason;
  }
}

/* network_game_client_leave_game (0x126140) — readable C lift (restored pre-naked). */
char network_game_client_leave_game(void *client)
{
  char result;
  int16_t state;
  void *encoded;
  unsigned short size;
  int payload;

  result = 1;
  if (client == NULL || *(int *)((char *)client + 0x82c) == 0) {
    display_assert("client && client->connection",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x179, 1);
    system_exit(-1);
  }

  network_game_log("leaving network game");
  state = *(int16_t *)((char *)client + 0xca6);
  switch (state) {
  case 0:
    if (!network_connection_connected(*(int *)((char *)client + 0x82c))) {
      display_assert("!network_connection_connected(client->connection)",
                     "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                     0x180, 1);
      system_exit(-1);
    }
    break;
  case 1:
    if (*(int *)((char *)client + 0x830) != 0)
      transport_server_terminate((int *)((char *)client + 0x830));
    *(int *)((char *)client + 0x830) = 0;
    if (!network_connection_connected(*(int *)((char *)client + 0x82c)))
      break;
    if (!FUN_00129980(*(int *)((char *)client + 0x82c))) {
      network_game_log("network_connection_disconnect() failed "
                       "_network_game_client_state_joining");
      result = 0;
    }
    break;
  case 2:
    if (!network_connection_connected(*(int *)((char *)client + 0x82c)))
      break;
    payload = 0;
    encoded = encode_network_game_message(0x12, &payload, 4);
    if (encoded == NULL) {
      network_game_log("failed to create a message_client_graceful_game_exit_pregame "
                       "message");
    } else {
      size = (unsigned short)(*(unsigned short *)encoded >> 4);
      if (!network_connection_write((void *)*(int *)((char *)client + 0x82c),
                                    encoded, size, 0, 1))
        network_game_log("network_game_client_write() failed while sending a "
                         "message_client_graceful_game_exit_pregame message");
    }
    if (!FUN_00129980(*(int *)((char *)client + 0x82c))) {
      network_game_log("network_connection_disconnect() failed "
                       "_network_game_client_state_pregame");
      result = 0;
    }
    break;
  case 3:
    if (!network_connection_connected(*(int *)((char *)client + 0x82c)))
      break;
    if (!FUN_00129980(*(int *)((char *)client + 0x82c))) {
      network_game_log("network_connection_disconnect() failed "
                       "_network_game_client_state_ingame");
      result = 0;
    }
    break;
  case 4:
    if (!network_connection_connected(*(int *)((char *)client + 0x82c)))
      break;
    payload = 0;
    encoded = encode_network_game_message(0x22, &payload, 4);
    if (encoded != NULL) {
      size = (unsigned short)(*(unsigned short *)encoded >> 4);
      if (!network_connection_write((void *)*(int *)((char *)client + 0x82c),
                                    encoded, size, 0, 1))
        network_game_log("network_game_client_write() failed while sending a "
                         "message_client_graceful_game_exit_postgame message");
    } else {
      network_game_log("failed to create a message_client_graceful_game_exit_postgame "
                       "message");
    }
    if (!FUN_00129980(*(int *)((char *)client + 0x82c))) {
      network_game_log("network_connection_disconnect() failed "
                       "_network_game_client_state_postgame");
      result = 0;
    }
    break;
  default:
    network_game_log("client is in an unknown state");
    result = 0;
    break;
  }

  network_game_invalidate((char *)client + 0x85c);
  *(int16_t *)((char *)client + 0xca6) = 0;
  return result;
}


/* network_game_client_request_remove_player (0x1263a0) — readable C lift (restored pre-naked). */
char network_game_client_request_remove_player(void *client, void *record)
{
  char result;
  int16_t state;
  char payload[0x20];
  void *encoded;
  unsigned short size;

  result = 1;
  if (client == NULL || !network_player_is_valid(record)) {
    display_assert("client && network_player_is_valid(player)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x208, 1);
    system_exit(-1);
  }
  if ((char)*(uint16_t *)client != *(char *)((char *)record + 0x1c)) {
    display_assert("client's can only remove players from their own machines",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x209, 1);
    system_exit(-1);
  }

  network_game_log("requesting a player removal (controller index #%d)",
                   (int)*(char *)((char *)record + 0x1d));
  state = *(int16_t *)((char *)client + 0xca6);
  switch (state) {
  case 0:
  case 1:
    network_game_log("can't remove players from a game until after a game is joined");
    result = 0;
    break;
  case 2:
    csmemcpy(payload, record, 0x20);
    encoded = encode_network_game_message(0xe, payload, 0x20);
    if (encoded == NULL) {
      network_game_log("failed to create a message_client_remove_player_request_pregame "
                       "mesage");
      result = 0;
    } else {
      size = (unsigned short)(*(unsigned short *)encoded >> 4);
      result = network_connection_write((void *)*(int *)((char *)client + 0x82c),
                                          encoded, size, 0, 1);
      if (!result)
        network_game_log("network_game_client_write() failed while sending a "
                         "message_client_remove_player_request_pregame message");
    }
    break;
  case 3:
    csmemcpy(payload, record, 0x20);
    encoded = encode_network_game_message(0x1b, payload, 0x20);
    if (encoded == NULL) {
      network_game_log("failed to create a message_client_remove_player_request_ingame "
                       "message");
      result = 0;
    } else {
      size = (unsigned short)(*(unsigned short *)encoded >> 4);
      result = network_connection_write((void *)*(int *)((char *)client + 0x82c),
                                          encoded, size, 0, 1);
      if (!result)
        network_game_log("network_game_client_write() failed while sending a "
                         "message_client_remove_player_request_ingame message");
    }
    break;
  case 4:
    csmemcpy(payload, record, 0x20);
    encoded = encode_network_game_message(0x20, payload, 0x20);
    if (encoded == NULL) {
      network_game_log("failed to create a message_client_remove_player_request_postgame "
                       "message");
      result = 0;
    } else {
      size = (unsigned short)(*(unsigned short *)encoded >> 4);
      result = network_connection_write((void *)*(int *)((char *)client + 0x82c),
                                          encoded, size, 0, 1);
      if (!result)
        network_game_log("network_game_client_write() failed while sending a "
                         "message_client_remove_player_request_postgame message");
    }
    break;
  default:
    network_game_log("client is in an unknown state");
    result = 0;
    break;
  }
  return result;
}


/* network_game_client_remove_player (0x126590) — readable C lift (restored pre-naked). */
char network_game_client_remove_player(void *client, void *message, int tick)
{
  int slot;
  char *player_rec;
  int local_index;
  void *unit;
  char result;

  if (client == NULL || message == NULL) {
    display_assert("client && player",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x273, 1);
    system_exit(-1);
  }

  slot = 0;
  player_rec = (char *)client + 0xa9e;
  while (slot < 0x10) {
    if (network_player_is_valid((void *)(player_rec - 0x1c)) &&
        *(char *)player_rec == *(char *)((char *)message + 0x1c) &&
        *(char *)(player_rec + 1) == *(char *)((char *)message + 0x1d))
      goto found;
    slot++;
    player_rec += 0x20;
  }
  return 0;

found:
  local_index = unstrip_player_index((int)*(char *)(player_rec + 3));
  result = network_game_remove_player((char *)client + 0x85c, message);
  if (!result)
    return 0;
  if (*(char *)((char *)client + 0xc8c) == 0)
    return result;
  if (local_index == 0 || local_index == -1) {
    error(2, "network game tried to delete a player with a phony player index (#0x%08lX)",
          (unsigned long)local_index);
    return 0;
  }
  unit = datum_get(*(void **)0x5aa6d4, local_index);
  if (tick != -1)
    error(2, "%x quit of of game at tick %d (now %d)", local_index, tick,
          game_time_get());
  *(int *)((char *)unit + 0xcc) = tick;

  slot = 0;
  player_rec = (char *)client + 0xa9e;
  while (slot < 0x10) {
    if (network_player_is_valid((void *)(player_rec - 0x1c)) &&
        (int)*(char *)player_rec == (int)*(uint16_t *)client)
      return result;
    slot++;
    player_rec += 0x20;
  }
  if (slot == 0x10) {
    network_game_client_all_local_players_have_quit();
    network_game_log("no local players remain in the game, exiting the game now");
  }
  return result;
}


/* network_game_client_new_advertised_game (0x126700) — readable C lift. */
void network_game_client_new_advertised_game(void *client, void *message)
{
  if (client == 0 || message == 0) {
    display_assert((const char *)0x291cd8, (const char *)0x291774, 0x2fc, 1);
    system_exit(-1);
  }
  FUN_00125ce0((char *)client + 4, message);
}

/* network_game_client_game_shutdown (0x126750) — readable C lift. */
void network_game_client_game_shutdown(void *client)
{
  if (client == 0) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x3fc, 1);
    system_exit(-1);
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x662, 1);
    system_exit(-1);
  }
  if (*(short *)((char *)client + 0xca8) == 0)
    *(short *)((char *)client + 0xca8) = 8;
  network_game_log((const char *)0x292ad0);
  network_game_client_all_local_players_have_quit();
}

/* FUN_001267c0 / network_game_client_reset (0x1267c0) — readable C lift. */
void FUN_001267c0(void *client, char close_transport)
{
  void *ep;

  if (client == 0) {
    display_assert((const char *)0x2917a8, (const char *)0x291774, 0x4ee, 1);
    system_exit(-1);
  }
  network_game_invalidate((char *)client + 0x85c);
  *(unsigned short *)client = 0xffff;
  *(unsigned short *)((char *)client + 0xca6) = 0;
  if (close_transport != 0) {
    ep = *(void **)((char *)client + 0x82c);
    if (ep != 0 && network_connection_connected((int)ep)) {
      *(int *)((char *)client + 0xc90) = 1;
      if (FUN_00129980((int)ep))
        *(unsigned char *)((char *)client + 0xcaa) &= (unsigned char)~1u;
      else {
        FUN_00125fb0(client, 1);
        network_game_log((const char *)0x292af0);
      }
    }
  }
  *(unsigned char *)((char *)client + 0xcaa) &= (unsigned char)~2u;
  *(unsigned short *)((char *)client + 0xca8) = 0;
  *(int *)((char *)client + 0xc94) = 0;
  *(int *)((char *)client + 0xc98) = 0;
  *(int *)((char *)client + 0xc9c) = 0;
  *(unsigned char *)((char *)client + 0xcad) = 0;
  *(unsigned char *)((char *)client + 0xcac) = 0;
  *(unsigned short *)((char *)client + 0xca4) = 0xffff;
}




/* FUN_001268a0 (0x1268a0) — Capstone tip: no network → error, return false. */
bool FUN_001268a0(void *server /*@<eax>*/)
{
  system_milliseconds();
  network_connection_keep_alive(*(int *)((char *)server + 0x82c));
  if (!network_game_is_splitscreen_local()) {
    if (!transport_network_available()) {
      error(2, (const char *)0);
      display_error_when_main_menu_loaded(6);
      return false;
    }
  }
  return false;
}


/* 0x126fe0 */
void *FUN_00126fe0(void)
{
  int connection;

  if (*(char *)0x46e8b9 != 0) {
    display_assert("!network_game_client_dont_use_directly_in_use",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x94, 1);
    system_exit(-1);
  }
  *(char *)0x46e8b9 = 1;
  csmemset((void *)0x5a95a0, 0, 0xcb0);
  connection = network_connection_new(2, 0x141f);
  *(int *)0x5a9dcc = connection;
  if (connection == 0) {
    network_game_log("network_game_create_client() failed; could not create network "
                     "connection");
    return NULL;
  }
  FUN_001267c0((void *)0x5a95a0, 0);
  return (void *)0x5a95a0;
}

/* FUN_001271a0 (0x1271a0) — readable C lift: log join rejection + close. */
void FUN_001271a0(void *client, void *source_address, unsigned short rejection_code)
{
  const char *reason;
  if (client == 0 || source_address == 0) {
    display_assert((const char *)0x291a3c, (const char *)0x291774, 0x35a, 1);
    system_exit(-1);
  }
  *(unsigned short *)((char *)client + 0xca6) = 0;
  switch (rejection_code) {
  case 0: reason = (const char *)0x2933d8; break;
  case 1: reason = (const char *)0x2933b8; break;
  case 2: reason = (const char *)0x293398; break;
  case 3: reason = (const char *)0x293378; break;
  case 4: reason = (const char *)0x293358; break;
  case 5: reason = (const char *)0x293338; break;
  case 6: reason = (const char *)0x293314; break;
  default: reason = (const char *)0x25b724; break;
  }
  network_game_log((const char *)0x2932f0, (int)rejection_code, reason);
  FUN_001267c0(client, 1);
}

/* FUN_001274E0 (0x1274e0) — readable C lift (restored pre-naked). */
char FUN_001274E0(void *client /* @<esi> */, void *source_address /* @<eax> */,
                    void *message, int message_size)
{
  char decoded[0x43c];
  int packet_type;
  int packet_version;
  char result;

  if (client == NULL) {
    display_assert("client != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x169, 1);
    system_exit(-1);
  }
  if (source_address == NULL) {
    display_assert("source_address != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x16a, 1);
    system_exit(-1);
  }
  if (!network_game_client_address_matches_server(client, source_address))
    return 1;
  if (network_game_client_get_state(client, NULL) != 2)
    return 1;
  message_size -= 2;
  packet_type = 6;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 6)) {
    network_game_log("failed to decode a message_server_game_settings_update packet");
    return 1;
  }
  result = network_game_client_game_settings_updated(client, decoded);
  if (!result)
    network_game_log("network_game_client_game_settings_updated() failed");
  return result;
}


/* FUN_00127610 (0x127610) — readable C lift: handle countdown timer message. */
char FUN_00127610(void *client, void *source_address, void *message, int message_size)
{
  short state;
  int packet_type;
  int packet_version;
  int decoded_timer;

  if (!client) {
    display_assert((const char *)0x2919a4, (const char *)0x293754, 0x19b, 1);
    system_exit(-1);
  }
  if (!source_address) {
    display_assert((const char *)0x29373c, (const char *)0x293754, 0x19c, 1);
    system_exit(-1);
  }
  if (!network_game_client_address_matches_server(client, source_address)) {
    network_game_log((const char *)0x293790);
    return 1;
  }
  state = network_game_client_get_state(client, 0);
  if (state != 2) {
    network_game_log((const char *)0x2937d8);
    return 1;
  }
  message_size -= 2;
  packet_type = 7;
  packet_version = 1;
  if (!FUN_0012bce0((int)&decoded_timer, (int)((char *)message + 2),
                    (short *)&message_size, (short *)&packet_type,
                    (short *)&packet_version, 2)) {
    network_game_log((const char *)0x29382c);
    return 1;
  }
  network_game_client_countdown_timer_update(client, (int16_t)decoded_timer);
  return 1;
}


/* FUN_00127710 (0x127710) — readable C lift: handle server message (esi=client, edi=addr). */
char FUN_00127710(void *client, void *source_address, void *message, int message_size)
{
  short state;
  int packet_type;
  int packet_version;
  short decoded_dummy;

  if (!client) {
    display_assert((const char *)0x2919a4, (const char *)0x293754, 0x1c4, 1);
    system_exit(-1);
  }
  if (!source_address) {
    display_assert((const char *)0x29373c, (const char *)0x293754, 0x1c5, 1);
    system_exit(-1);
  }
  if (!network_game_client_address_matches_server(client, source_address)) {
    network_game_log((const char *)0x293868);
    return 1;
  }
  state = network_game_client_get_state(client, 0);
  if (state != 2) {
    network_game_log((const char *)0x2938b0);
    return 1;
  }
  message_size -= 2;
  packet_type = 0xa;
  packet_version = 1;
  if (!FUN_0012bce0((int)&decoded_dummy, (int)((char *)message + 2),
                    (short *)&message_size, (short *)&packet_type,
                    (short *)&packet_version, 2)) {
    network_game_log((const char *)0x293904);
    return 1;
  }
  return 1;
}

