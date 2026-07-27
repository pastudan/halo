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

/* FUN_00124730 (0x124730) — XBE naked draft (batch 116). */
#if defined(__clang__)
static void (*const b124730_c123d80)(void) = (void (*)(void))FUN_00123d80;
static void (*const b124730_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b124730_exitfn)(int) = system_exit;
static void *(*const b124730_tag)(int, int) = tag_get;
static void *(*const b124730_elem)(void *, int, int) = tag_block_get_element;
static void (*const b124730_c1094d0)(float *out_matrix, float *position, float *basis_data) = component_vectors_from_normal3d;
static void (*const b124730_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;

__attribute__((naked, noinline))
int16_t FUN_00124730(int model_ref __attribute__((unused)), const char *marker_name __attribute__((unused)), char *magic_table __attribute__((unused)), int node_remap __attribute__((unused)), int16_t node_count __attribute__((unused)), void *node_matrices __attribute__((unused)), char mirrored __attribute__((unused)), void *out_markers __attribute__((unused)), int16_t max_markers __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "call *%[c123d80]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00124730_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2f8\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x29171c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00124730_1:\n\t"
      "movl 0x24(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00124730_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2f9\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x291714\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00124730_2:\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_00124730_14\n\t"
      "pushl %%edi\n\t"
      "pushl $0x6d6f6465\n\t"
      "call *%[tag]\n\t"
      "movswl %%si, %%ecx\n\t"
      "pushl $0x40\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "addl $0xac, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "leal 0x34(%%eax), %%ebx\n\t"
      "movl (%%ebx), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .LFUN_00124730_12\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00124730_3:\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00124730_4\n\t"
      "movzbl (%%eax), %%edx\n\t"
      "movb (%%edx,%%esi,1), %%cl\n\t"
      "cmpb 0x1(%%eax), %%cl\n\t"
      "jne .LFUN_00124730_11\n\t"
      ".LFUN_00124730_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpw 0x28(%%ebp), %%cx\n\t"
      "jge .LFUN_00124730_13\n\t"
      "movl 0x24(%%ebp), %%edx\n\t"
      "movswl %%cx, %%esi\n\t"
      "imull $0x6c, %%esi, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00124730_5\n\t"
      "movzbl 0x2(%%eax), %%edx\n\t"
      "movswl (%%ecx,%%edx,2), %%ecx\n\t"
      "jmp .LFUN_00124730_6\n\t"
      ".LFUN_00124730_5:\n\t"
      "movzbl 0x2(%%eax), %%ecx\n\t"
      ".LFUN_00124730_6:\n\t"
      "movw %%cx, (%%esi)\n\t"
      "leal 0x10(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x4(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1094d0]\n\t"
      "movw (%%esi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00124730_9\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .LFUN_00124730_7\n\t"
      "movswl 0x18(%%ebp), %%ecx\n\t"
      "jmp .LFUN_00124730_8\n\t"
      ".LFUN_00124730_7:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl 0xb8(%%edx), %%ecx\n\t"
      ".LFUN_00124730_8:\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00124730_10\n\t"
      ".LFUN_00124730_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x311\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x2916a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00124730_10:\n\t"
      "movswl (%%esi), %%edx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "leal 0x38(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c109850]\n\t"
      "movb 0x20(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00124730_11\n\t"
      "flds 0x48(%%esi)\n\t"
      "fchs\n\t"
      "fstps 0x48(%%esi)\n\t"
      "flds 0x4c(%%esi)\n\t"
      "fchs\n\t"
      "fstps 0x4c(%%esi)\n\t"
      "flds 0x50(%%esi)\n\t"
      "fchs\n\t"
      "fstps 0x50(%%esi)\n\t"
      ".LFUN_00124730_11:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_00124730_3\n\t"
      ".LFUN_00124730_12:\n\t"
      "movw -0x4(%%ebp), %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00124730_13:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%cx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00124730_14:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw %%bx, %%ax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c123d80] "m"(b124730_c123d80), [assert] "m"(b124730_assert), [exitfn] "m"(b124730_exitfn), [tag] "m"(b124730_tag), [elem] "m"(b124730_elem), [c1094d0] "m"(b124730_c1094d0), [c109850] "m"(b124730_c109850)
      : "memory");
}
#else
#error "FUN_00124730: clang naked draft required"
#endif


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

/* network_game_client_initiate_join_game (0x124aa0) — XBE naked draft (batch 134). */
#if defined(__clang__)
static bool (*const b124aa0_c128360)(int connection) = network_connection_connected;
static void (*const b124aa0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b124aa0_exitfn)(int) = system_exit;
static unsigned int (*const b124aa0_c8e370)(void) = system_milliseconds;
static void * (*const b124aa0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b124aa0_c128460)(int connection, int remote_address, int async_process_ref) = network_connection_connect;
static const char * (*const b124aa0_c81b90)(void *addr) = transport_address_to_string;
static void (*const b124aa0_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b124aa0_ce44d0)(int16_t) = display_error_when_main_menu_loaded;

__attribute__((naked, noinline))
char network_game_client_initiate_join_game(void *client __attribute__((unused)), void *game __attribute__((unused)), void *join_token __attribute__((unused)), void *address __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "je .Lnetwork_game_client_initiate_join_game_1\n\t"
      "cmpw $0, 0xca6(%%esi)\n\t"
      "jne .Lnetwork_game_client_initiate_join_game_1\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .Lnetwork_game_client_initiate_join_game_1\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_game_client_initiate_join_game_1\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_initiate_join_game_1\n\t"
      "pushl %%eax\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_client_initiate_join_game_1\n\t"
      "cmpw $0, 0xde(%%ebx)\n\t"
      "je .Lnetwork_game_client_initiate_join_game_2\n\t"
      ".Lnetwork_game_client_initiate_join_game_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x157\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x291810\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_initiate_join_game_2:\n\t"
      "movl $1, 0xc90(%%esi)\n\t"
      "movl $0, 0x830(%%esi)\n\t"
      "call *%[c8e370]\n\t"
      "pushl $0x22\n\t"
      "movl %%eax, 0x834(%%esi)\n\t"
      "leal 0x838(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl 0x82c(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c128460]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .Lnetwork_game_client_initiate_join_game_3\n\t"
      "pushl %%edi\n\t"
      "movw $1, 0xca6(%%esi)\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2917e8\n\t"
      "call *%[c12b650]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_initiate_join_game_3:\n\t"
      "pushl $7\n\t"
      "call *%[ce44d0]\n\t"
      "pushl %%edi\n\t"
      "call *%[c81b90]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2917b0\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c128360] "m"(b124aa0_c128360), [assert] "m"(b124aa0_assert), [exitfn] "m"(b124aa0_exitfn), [c8e370] "m"(b124aa0_c8e370), [c8e0b0] "m"(b124aa0_c8e0b0), [c128460] "m"(b124aa0_c128460), [c81b90] "m"(b124aa0_c81b90), [c12b650] "m"(b124aa0_c12b650), [ce44d0] "m"(b124aa0_ce44d0)
      : "memory");
}
#else
#error "network_game_client_initiate_join_game: clang naked draft required"
#endif


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

/* network_game_client_game_settings_updated (0x125050) — XBE naked draft (batch 129). */
#if defined(__clang__)
static void (*const b125050_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b125050_exitfn)(int) = system_exit;
static int (*const b125050_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static void (*const b125050_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b125050_c100010)(const char *name) = main_set_multiplayer_map_name;
static void * (*const b125050_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
char network_game_client_game_settings_updated(void *client __attribute__((unused)), void *message __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x434, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "je .Lnetwork_game_client_game_settings_updated_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lnetwork_game_client_game_settings_updated_2\n\t"
      ".Lnetwork_game_client_game_settings_updated_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x375\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x291cd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_game_settings_updated_2:\n\t"
      "movw 0x112(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lnetwork_game_client_game_settings_updated_4\n\t"
      "cmpw $4, %%ax\n\t"
      "jg .Lnetwork_game_client_game_settings_updated_4\n\t"
      "movw 0x224(%%esi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jl .Lnetwork_game_client_game_settings_updated_4\n\t"
      "cmpw $0x10, %%cx\n\t"
      "jg .Lnetwork_game_client_game_settings_updated_4\n\t"
      "pushl %%edi\n\t"
      "leal 0x880(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_game_settings_updated_3\n\t"
      "pushl %%edi\n\t"
      "pushl $0x291cc0\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%edi\n\t"
      "call *%[c100010]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lnetwork_game_client_game_settings_updated_3:\n\t"
      "pushl $0x434\n\t"
      "leal 0x85c(%%ebx), %%edi\n\t"
      "leal -0x434(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x434\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0xc8c, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x112(%%esi), %%eax\n\t"
      "movswl 0x224(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x291c60\n\t"
      "call *%[c12b650]\n\t"
      "movswl 0x112(%%esi), %%edx\n\t"
      "movswl 0x224(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x291c38\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x3c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_game_settings_updated_4:\n\t"
      "movswl 0x224(%%esi), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x291bd8\n\t"
      "call *%[c12b650]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b125050_assert), [exitfn] "m"(b125050_exitfn), [c8dcb0] "m"(b125050_c8dcb0), [c12b650] "m"(b125050_c12b650), [c100010] "m"(b125050_c100010), [c8e0b0] "m"(b125050_c8e0b0)
      : "memory");
}
#else
#error "network_game_client_game_settings_updated: clang naked draft required"
#endif


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
/* network_game_client_game_has_started (0x1251e0) — XBE naked draft (batch 124). */
#if defined(__clang__)
static void (*const b1251e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1251e0_exitfn)(int) = system_exit;
static void (*const b1251e0_c128d20)(int connection) = network_connection_keep_alive;
static bool (*const b1251e0_c12b350)(void *game) = network_game_create_game_objects;
static bool (*const b1251e0_c12ac80)(void *client) = network_player_is_valid;
static int (*const b1251e0_c125180)(int stripped_index) = unstrip_player_index;
static int (*const b1251e0_cba410)(unsigned __int16 a1, int a2) = local_player_set_player_index;
static void * (*const b1251e0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b1251e0_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static void (*const b1251e0_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b1251e0_ce58c0)(void) = (void (*)(void))ui_widgets_close_all;
static void (*const b1251e0_cb5f40)(void) = (void (*)(void))game_time_start;
static void (*const b1251e0_ca73c0)(void) = (void (*)(void))game_initial_pulse;

__attribute__((naked, noinline))
char network_game_client_game_has_started(void *client __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lnetwork_game_client_game_has_started_1\n\t"
      "cmpw $2, 0xca6(%%esi)\n\t"
      "je .Lnetwork_game_client_game_has_started_2\n\t"
      ".Lnetwork_game_client_game_has_started_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x3b0\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x291dd0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_game_has_started_2:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movw $0xffff, 0xca4(%%esi)\n\t"
      "call *%[c128d20]\n\t"
      "leal 0x85c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12b350]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_game_has_started_9\n\t"
      "movzwl (%%esi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal 0xa9e(%%esi), %%ecx\n\t"
      "pushl %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lnetwork_game_client_game_has_started_3:\n\t"
      "movsbl (%%ecx), %%edi\n\t"
      "cmpl %%edx, %%edi\n\t"
      "je .Lnetwork_game_client_game_has_started_4\n\t"
      "incl %%eax\n\t"
      "addl $0x20, %%ecx\n\t"
      "cmpl $0x10, %%eax\n\t"
      "jl .Lnetwork_game_client_game_has_started_3\n\t"
      "jmp .Lnetwork_game_client_game_has_started_6\n\t"
      ".Lnetwork_game_client_game_has_started_4:\n\t"
      "shll $5, %%eax\n\t"
      "leal (%%eax,%%esi,1), %%edi\n\t"
      "movsbl 0xa9e(%%edi), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .Lnetwork_game_client_game_has_started_6\n\t"
      ".Lnetwork_game_client_game_has_started_5:\n\t"
      "leal 0xa82(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_game_has_started_6\n\t"
      "movsbl 0xaa1(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c125180]\n\t"
      "pushl %%eax\n\t"
      "movsbw 0xa9f(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[cba410]\n\t"
      "movsbl 0xabe(%%edi), %%ecx\n\t"
      "movzwl (%%esi), %%edx\n\t"
      "addl $0x20, %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .Lnetwork_game_client_game_has_started_5\n\t"
      ".Lnetwork_game_client_game_has_started_6:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c128d20]\n\t"
      "pushl $4\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x18\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "je .Lnetwork_game_client_game_has_started_8\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_game_has_started_7\n\t"
      "pushl $0x291da4\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movw $3, 0xca6(%%esi)\n\t"
      "movl $0, 0xc98(%%esi)\n\t"
      "movl $0, 0xc9c(%%esi)\n\t"
      "movb $0, 0xcad(%%esi)\n\t"
      "call *%[ce58c0]\n\t"
      "call *%[cb5f40]\n\t"
      "call *%[ca73c0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $3, 0xca6(%%esi)\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_game_has_started_7:\n\t"
      "pushl $0x291d50\n\t"
      "jmp .Lnetwork_game_client_game_has_started_10\n\t"
      ".Lnetwork_game_client_game_has_started_8:\n\t"
      "pushl $0x291d1c\n\t"
      "jmp .Lnetwork_game_client_game_has_started_10\n\t"
      ".Lnetwork_game_client_game_has_started_9:\n\t"
      "pushl $0x291cf4\n\t"
      ".Lnetwork_game_client_game_has_started_10:\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $3, 0xca6(%%esi)\n\t"
      "popl %%esi\n\t"
      "sete %%al\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1251e0_assert), [exitfn] "m"(b1251e0_exitfn), [c128d20] "m"(b1251e0_c128d20), [c12b350] "m"(b1251e0_c12b350), [c12ac80] "m"(b1251e0_c12ac80), [c125180] "m"(b1251e0_c125180), [cba410] "m"(b1251e0_cba410), [c12b700] "m"(b1251e0_c12b700), [c128e00] "m"(b1251e0_c128e00), [c12b650] "m"(b1251e0_c12b650), [ce58c0] "m"(b1251e0_ce58c0), [cb5f40] "m"(b1251e0_cb5f40), [ca73c0] "m"(b1251e0_ca73c0)
      : "memory");
}
#else
#error "network_game_client_game_has_started: clang naked draft required"
#endif


/* network_game_client_handle_game_update (0x125380) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void (*const b125380_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b125380_exitfn)(int) = system_exit;
static void *(*const b125380_memset)(void *, int, unsigned int) = csmemset;
static void (*const b125380_c12b650)(const char *fmt, ...) = network_game_log;
static void (*const b125380_c124e20)(void *client) = network_game_client_game_out_of_sync;
static void * (*const b125380_c12a1d0)(void) = network_game_server_get;
static int (*const b125380_gtime)(void) = game_time_get;
static unsigned int (*const b125380_c10b110)(void) = get_random_seed;
static void * (*const b125380_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b125380_cb97b0)(void *data, int sequence_index) = FUN_000b97b0;
static unsigned int (*const b125380_c8e370)(void) = system_milliseconds;

__attribute__((naked, noinline))
char network_game_client_handle_game_update(void *client __attribute__((unused)), void *message __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x204, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lnetwork_game_client_handle_game_update_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lnetwork_game_client_handle_game_update_2\n\t"
      ".Lnetwork_game_client_handle_game_update_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x40d\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x291cd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_handle_game_update_2:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movw 0xa80(%%edi), %%cx\n\t"
      "cmpw %%cx, %%ax\n\t"
      "jge .Lnetwork_game_client_handle_game_update_3\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "shll $5, %%eax\n\t"
      "leal 0x10(%%eax,%%esi,1), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movw 0xa80(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%ax, 0xe(%%esi)\n\t"
      ".Lnetwork_game_client_handle_game_update_3:\n\t"
      "movl (%%esi), %%eax\n\t"
      "movl 0xc98(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .Lnetwork_game_client_handle_game_update_4\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x291edc\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%edi\n\t"
      "call *%[c124e20]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lnetwork_game_client_handle_game_update_8\n\t"
      ".Lnetwork_game_client_handle_game_update_4:\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_client_handle_game_update_8\n\t"
      "call *%[gtime]\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "jne .Lnetwork_game_client_handle_game_update_5\n\t"
      "call *%[gtime]\n\t"
      "cmpl %%eax, 0x8(%%esi)\n\t"
      "je .Lnetwork_game_client_handle_game_update_5\n\t"
      "call *%[gtime]\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x291eac\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lnetwork_game_client_handle_game_update_5:\n\t"
      "call *%[gtime]\n\t"
      "cmpl 0x8(%%esi), %%eax\n\t"
      "jne .Lnetwork_game_client_handle_game_update_7\n\t"
      "pushl %%ebx\n\t"
      "movl 0x4(%%esi), %%ebx\n\t"
      "call *%[c10b110]\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "je .Lnetwork_game_client_handle_game_update_6\n\t"
      "pushl %%ebx\n\t"
      "call *%[c10b110]\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[gtime]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x291e48\n\t"
      "call *%[c12b650]\n\t"
      "pushl %%edi\n\t"
      "call *%[c124e20]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lnetwork_game_client_handle_game_update_6:\n\t"
      "popl %%ebx\n\t"
      ".Lnetwork_game_client_handle_game_update_7:\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x1e, %%ecx\n\t"
      "divl %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lnetwork_game_client_handle_game_update_8\n\t"
      "call *%[gtime]\n\t"
      "movl (%%esi), %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x291e10\n\t"
      "call *%[c12b650]\n\t"
      "addl $8, %%esp\n\t"
      ".Lnetwork_game_client_handle_game_update_8:\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "movw %%ax, -0x204(%%ebp)\n\t"
      "movzwl %%ax, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x200(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x204(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cb97b0]\n\t"
      "movl 0xc98(%%edi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0xc98(%%edi)\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, 0xc9c(%%edi)\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b125380_assert), [exitfn] "m"(b125380_exitfn), [memset] "m"(b125380_memset), [c12b650] "m"(b125380_c12b650), [c124e20] "m"(b125380_c124e20), [c12a1d0] "m"(b125380_c12a1d0), [gtime] "m"(b125380_gtime), [c10b110] "m"(b125380_c10b110), [c8e0b0] "m"(b125380_c8e0b0), [cb97b0] "m"(b125380_cb97b0), [c8e370] "m"(b125380_c8e370)
      : "memory");
}
#else
#error "network_game_client_handle_game_update: clang naked draft required"
#endif


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

/* network_game_client_add_player (0x1258a0) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void (*const b1258a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1258a0_exitfn)(int) = system_exit;
static void (*const b1258a0_ce0980)(void) = (void (*)(void))player_ui_get_active_player_profile;
static wchar_t * (*const b1258a0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b1258a0_c12b650)(const char *fmt, ...) = network_game_log;
static void * (*const b1258a0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void * (*const b1258a0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b1258a0_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;

__attribute__((naked, noinline))
char network_game_client_add_player(void *client __attribute__((unused)), int16_t local_player_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x70, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "movb $1, %%bl\n\t"
      "je .Lnetwork_game_client_add_player_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lnetwork_game_client_add_player_1\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lnetwork_game_client_add_player_2\n\t"
      ".Lnetwork_game_client_add_player_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x530\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x2921c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_add_player_2:\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[ce0980]\n\t"
      "movb 0xc(%%ebp), %%dl\n\t"
      "movb (%%esi), %%al\n\t"
      "pushl $0xb\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "movb %%dl, -0x3(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movb %%al, -0x4(%%ebp)\n\t"
      "call *%[c19dc90]\n\t"
      "movsbl -0x3(%%ebp), %%ecx\n\t"
      "movw -0x58(%%ebp), %%ax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x29218c\n\t"
      "movw $0, -0xa(%%ebp)\n\t"
      "movw %%ax, -0x8(%%ebp)\n\t"
      "movw $0xffff, -0x6(%%ebp)\n\t"
      "movb $0xff, -0x2(%%ebp)\n\t"
      "movb $0xff, -0x1(%%ebp)\n\t"
      "call *%[c12b650]\n\t"
      "movzwl 0xca6(%%esi), %%eax\n\t"
      "addl $0x1c, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .Lnetwork_game_client_add_player_9\n\t"
      "jmp *.Lnetwork_game_client_add_player_jt(,%%eax,4)\n\t"
      ".Lnetwork_game_client_add_player_3:\n\t"
      "pushl $0x292150\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_4:\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_add_player_5\n\t"
      "movl 0x82c(%%esi), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_add_player_10\n\t"
      "pushl $0x2920e8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_5:\n\t"
      "pushl $0x2920a0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_6:\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x1a\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_add_player_7\n\t"
      "movl 0x82c(%%esi), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_add_player_10\n\t"
      "pushl $0x292038\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_7:\n\t"
      "pushl $0x291ff0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_8:\n\t"
      "pushl $0x291fbc\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_add_player_9:\n\t"
      "pushl $0x291f9c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_add_player_10:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lnetwork_game_client_add_player_jt:\n\t"
      ".long .Lnetwork_game_client_add_player_3\n\t"
      ".long .Lnetwork_game_client_add_player_3\n\t"
      ".long .Lnetwork_game_client_add_player_4\n\t"
      ".long .Lnetwork_game_client_add_player_6\n\t"
      ".long .Lnetwork_game_client_add_player_8\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b1258a0_assert), [exitfn] "m"(b1258a0_exitfn), [ce0980] "m"(b1258a0_ce0980), [c19dc90] "m"(b1258a0_c19dc90), [c12b650] "m"(b1258a0_c12b650), [c8e0b0] "m"(b1258a0_c8e0b0), [c12b700] "m"(b1258a0_c12b700), [c128e00] "m"(b1258a0_c128e00)
      : "memory");
}
#else
#error "network_game_client_add_player: clang naked draft required"
#endif


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
/* FUN_00125ce0 (0x125ce0) — XBE naked draft (batch 113). */
#if defined(__clang__)
static unsigned int (*const b125ce0_c8e370)(void) = system_milliseconds;
static void *(*const b125ce0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b125ce0_c81f30)(void) = (void (*)(void))transport_nonce_is_equal;
static void (*const b125ce0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b125ce0_exitfn)(int) = system_exit;
static void (*const b125ce0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b125ce0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static wchar_t * (*const b125ce0_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;
static void (*const b125ce0_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char FUN_00125ce0(void *slot_array /* */ __attribute__((unused)), void *advertised_game __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "testb $2, 0x102(%%edi)\n\t"
      "je .LFUN_00125ce0_1\n\t"
      "cmpw $4, 0xfa(%%edi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jl .LFUN_00125ce0_2\n\t"
      ".LFUN_00125ce0_1:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_00125ce0_2:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $0x2c, %%esi\n\t"
      "movl $9, %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00125ce0_3:\n\t"
      "movb 0xb5(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00125ce0_4\n\t"
      "call *%[c8e370]\n\t"
      "subl (%%esi), %%eax\n\t"
      "cmpl $0x1770, %%eax\n\t"
      "jle .LFUN_00125ce0_5\n\t"
      ".LFUN_00125ce0_4:\n\t"
      "pushl $0xe4\n\t"
      "leal -0x2c(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00125ce0_5:\n\t"
      "addl $0xe4, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00125ce0_3\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00125ce0_6:\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81f30]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00125ce0_7\n\t"
      "incl %%ebx\n\t"
      "addl $0xe4, %%esi\n\t"
      "cmpl $9, %%ebx\n\t"
      "jl .LFUN_00125ce0_6\n\t"
      "jmp .LFUN_00125ce0_8\n\t"
      ".LFUN_00125ce0_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00125ce0_15\n\t"
      ".LFUN_00125ce0_8:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      ".LFUN_00125ce0_9:\n\t"
      "movb 0xe1(%%ecx), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .LFUN_00125ce0_13\n\t"
      "incl %%eax\n\t"
      "addl $0xe4, %%ecx\n\t"
      "cmpl $9, %%eax\n\t"
      "jl .LFUN_00125ce0_9\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00125ce0_12\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0xe0, %%esi\n\t"
      "jmp .LFUN_00125ce0_10\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00125ce0_10:\n\t"
      "movb 0x1(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0xe0(%%esi), %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00125ce0_11\n\t"
      "pushl $1\n\t"
      "pushl $0x61f\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x2924c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00125ce0_11:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "je .LFUN_00125ce0_14\n\t"
      "incl %%ebx\n\t"
      "addl $0xe4, %%esi\n\t"
      "cmpl $9, %%ebx\n\t"
      "jl .LFUN_00125ce0_10\n\t"
      ".LFUN_00125ce0_12:\n\t"
      "pushl $0x292470\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00125ce0_13:\n\t"
      "movl %%ecx, %%esi\n\t"
      "jmp .LFUN_00125ce0_15\n\t"
      ".LFUN_00125ce0_14:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "pushl $0xe4\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00125ce0_15:\n\t"
      "movb $1, 0xe1(%%esi)\n\t"
      "leal 0x18(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "movl 0x10(%%edi), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "movl 0x14(%%edi), %%edx\n\t"
      "movl %%edx, 0x4(%%esi)\n\t"
      "leal 0x28(%%edi), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x18(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "pushl $8\n\t"
      "leal 0x8(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "movw 0x38(%%edi), %%dx\n\t"
      "leal 0x3a(%%edi), %%eax\n\t"
      "movw %%dx, 0xde(%%esi)\n\t"
      "cmpw $0, (%%eax)\n\t"
      "pushl $0xf\n\t"
      "je .LFUN_00125ce0_16\n\t"
      "pushl %%eax\n\t"
      "leal 0x30(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_00125ce0_17\n\t"
      ".LFUN_00125ce0_16:\n\t"
      "pushl $0x292468\n\t"
      "leal 0x30(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00125ce0_17:\n\t"
      "call *%[c19dc90]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x84\n\t"
      "leal 0x74(%%edi), %%eax\n\t"
      "movw $0, 0x4e(%%esi)\n\t"
      "movw 0xf8(%%edi), %%dx\n\t"
      "pushl %%eax\n\t"
      "leal 0x50(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movw %%dx, 0xd4(%%esi)\n\t"
      "call *%[c8e0b0]\n\t"
      "movw 0xfa(%%edi), %%dx\n\t"
      "movw %%dx, 0xd6(%%esi)\n\t"
      "movw 0xfc(%%edi), %%ax\n\t"
      "movw %%ax, 0xd8(%%esi)\n\t"
      "movw 0xfe(%%edi), %%cx\n\t"
      "movw %%cx, 0xda(%%esi)\n\t"
      "movw 0x100(%%edi), %%dx\n\t"
      "movw %%dx, 0xdc(%%esi)\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "movb %%dl, 0xe0(%%esi)\n\t"
      "movb 0x102(%%edi), %%al\n\t"
      "shrb $2, %%al\n\t"
      "andb $1, %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, 0xd4(%%esi)\n\t"
      "movb %%al, 0xe2(%%esi)\n\t"
      "jne .LFUN_00125ce0_18\n\t"
      "testb $8, 0x102(%%edi)\n\t"
      "je .LFUN_00125ce0_18\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00125ce0_19\n\t"
      ".LFUN_00125ce0_18:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00125ce0_19:\n\t"
      "movb %%al, 0xe3(%%esi)\n\t"
      "movw 0xde(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $1, %%bl\n\t"
      "jne .LFUN_00125ce0_20\n\t"
      "movl $0x292460, %%ecx\n\t"
      "jmp .LFUN_00125ce0_21\n\t"
      ".LFUN_00125ce0_20:\n\t"
      "cmpw $1, %%ax\n\t"
      "movl $0x29245c, %%ecx\n\t"
      "je .LFUN_00125ce0_21\n\t"
      "movl $0x292448, %%ecx\n\t"
      ".LFUN_00125ce0_21:\n\t"
      "testb %%dl, %%dl\n\t"
      "movl $0x292440, %%eax\n\t"
      "jne .LFUN_00125ce0_22\n\t"
      "movl $0x292434, %%eax\n\t"
      ".LFUN_00125ce0_22:\n\t"
      "movzwl 0xd6(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movzwl 0xd8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2923fc\n\t"
      "call *%[c12b650]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b125ce0_c8e370), [memset] "m"(b125ce0_memset), [c81f30] "m"(b125ce0_c81f30), [assert] "m"(b125ce0_assert), [exitfn] "m"(b125ce0_exitfn), [c8f390] "m"(b125ce0_c8f390), [c8e0b0] "m"(b125ce0_c8e0b0), [c19dc90] "m"(b125ce0_c19dc90), [c12b650] "m"(b125ce0_c12b650)
      : "memory");
}
#else
#error "FUN_00125ce0: clang naked draft required"
#endif


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

/* network_game_client_leave_game (0x126140) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void (*const b126140_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b126140_exitfn)(int) = system_exit;
static void (*const b126140_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b126140_c128360)(int connection) = network_connection_connected;
static void (*const b126140_c84300)(int *connect_handle) = transport_server_terminate;
static bool (*const b126140_c129980)(int connection) = FUN_00129980;
static void * (*const b126140_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b126140_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;
static void (*const b126140_c12b150)(void *game) = network_game_invalidate;

__attribute__((naked, noinline))
char network_game_client_leave_game(void *client __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpl %%edi, %%esi\n\t"
      "movb $1, %%bl\n\t"
      "je .Lnetwork_game_client_leave_game_1\n\t"
      "cmpl %%edi, 0x82c(%%esi)\n\t"
      "jne .Lnetwork_game_client_leave_game_2\n\t"
      ".Lnetwork_game_client_leave_game_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x179\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x2927d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_leave_game_2:\n\t"
      "pushl $0x2927b8\n\t"
      "call *%[c12b650]\n\t"
      "movzwl 0xca6(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .Lnetwork_game_client_leave_game_13\n\t"
      "jmp *.Lnetwork_game_client_leave_game_jt(,%%eax,4)\n\t"
      ".Lnetwork_game_client_leave_game_3:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $1\n\t"
      "pushl $0x180\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x292784\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lnetwork_game_client_leave_game_15\n\t"
      ".Lnetwork_game_client_leave_game_4:\n\t"
      "movl 0x830(%%esi), %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lnetwork_game_client_leave_game_5\n\t"
      "pushl %%eax\n\t"
      "call *%[c84300]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, 0x830(%%esi)\n\t"
      ".Lnetwork_game_client_leave_game_5:\n\t"
      "movl 0x82c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_leave_game_15\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c129980]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $0x292738\n\t"
      "jmp .Lnetwork_game_client_leave_game_14\n\t"
      ".Lnetwork_game_client_leave_game_6:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $4\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x12\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lnetwork_game_client_leave_game_7\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_client_leave_game_9\n\t"
      "pushl $0x2924d0\n\t"
      "jmp .Lnetwork_game_client_leave_game_8\n\t"
      ".Lnetwork_game_client_leave_game_7:\n\t"
      "pushl $0x2926f0\n\t"
      ".Lnetwork_game_client_leave_game_8:\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_leave_game_9:\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c129980]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $0x2926a0\n\t"
      "jmp .Lnetwork_game_client_leave_game_14\n\t"
      ".Lnetwork_game_client_leave_game_10:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_leave_game_15\n\t"
      "movl 0x82c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c129980]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $0x292650\n\t"
      "jmp .Lnetwork_game_client_leave_game_14\n\t"
      ".Lnetwork_game_client_leave_game_11:\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "call *%[c128360]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $4\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x22\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edi, %%eax\n\t"
      "je .Lnetwork_game_client_leave_game_12\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_client_leave_game_12\n\t"
      "pushl $0x2925e8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_leave_game_12:\n\t"
      "movl 0x82c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c129980]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_leave_game_15\n\t"
      "pushl $0x292598\n\t"
      "jmp .Lnetwork_game_client_leave_game_14\n\t"
      ".Lnetwork_game_client_leave_game_13:\n\t"
      "pushl $0x291f9c\n\t"
      ".Lnetwork_game_client_leave_game_14:\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_leave_game_15:\n\t"
      "leal 0x85c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c12b150]\n\t"
      "addl $4, %%esp\n\t"
      "movw %%di, 0xca6(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lnetwork_game_client_leave_game_jt:\n\t"
      ".long .Lnetwork_game_client_leave_game_3\n\t"
      ".long .Lnetwork_game_client_leave_game_4\n\t"
      ".long .Lnetwork_game_client_leave_game_6\n\t"
      ".long .Lnetwork_game_client_leave_game_10\n\t"
      ".long .Lnetwork_game_client_leave_game_11\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b126140_assert), [exitfn] "m"(b126140_exitfn), [c12b650] "m"(b126140_c12b650), [c128360] "m"(b126140_c128360), [c84300] "m"(b126140_c84300), [c129980] "m"(b126140_c129980), [c12b700] "m"(b126140_c12b700), [c128e00] "m"(b126140_c128e00), [c12b150] "m"(b126140_c12b150)
      : "memory");
}
#else
#error "network_game_client_leave_game: clang naked draft required"
#endif


/* network_game_client_request_remove_player (0x1263a0) — XBE naked draft (batch 114). */
#if defined(__clang__)
static bool (*const b1263a0_c12ac80)(void *client) = network_player_is_valid;
static void (*const b1263a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1263a0_exitfn)(int) = system_exit;
static void (*const b1263a0_c12b650)(const char *fmt, ...) = network_game_log;
static void * (*const b1263a0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void * (*const b1263a0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b1263a0_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;

__attribute__((naked, noinline))
char network_game_client_request_remove_player(void *client __attribute__((unused)), void *record __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movb $1, %%bl\n\t"
      "je .Lnetwork_game_client_request_remove_player_1\n\t"
      "pushl %%edi\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lnetwork_game_client_request_remove_player_2\n\t"
      ".Lnetwork_game_client_request_remove_player_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x208\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x2929f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_request_remove_player_2:\n\t"
      "movzwl (%%esi), %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "movb 0x9b0(%%eax,%%esi,1), %%cl\n\t"
      "cmpb 0x1c(%%edi), %%cl\n\t"
      "je .Lnetwork_game_client_request_remove_player_3\n\t"
      "pushl $1\n\t"
      "pushl $0x209\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x2929b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_request_remove_player_3:\n\t"
      "movsbl 0x1d(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x292980\n\t"
      "call *%[c12b650]\n\t"
      "movzwl 0xca6(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "ja .Lnetwork_game_client_request_remove_player_11\n\t"
      "jmp *.Lnetwork_game_client_request_remove_player_jt(,%%eax,4)\n\t"
      ".Lnetwork_game_client_request_remove_player_4:\n\t"
      "pushl $0x292940\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_5:\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xe\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_client_request_remove_player_7\n\t"
      "pushl $0x2928f8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_6:\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1b\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_request_remove_player_8\n\t"
      ".Lnetwork_game_client_request_remove_player_7:\n\t"
      "movl 0x82c(%%esi), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%al, %%bl\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_8:\n\t"
      "pushl $0x2928b0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_9:\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x20\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x20\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lnetwork_game_client_request_remove_player_10\n\t"
      "movl 0x82c(%%esi), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lnetwork_game_client_request_remove_player_12\n\t"
      "pushl $0x292840\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_10:\n\t"
      "pushl $0x2927f0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_request_remove_player_11:\n\t"
      "pushl $0x291f9c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_request_remove_player_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lnetwork_game_client_request_remove_player_jt:\n\t"
      ".long .Lnetwork_game_client_request_remove_player_4\n\t"
      ".long .Lnetwork_game_client_request_remove_player_4\n\t"
      ".long .Lnetwork_game_client_request_remove_player_5\n\t"
      ".long .Lnetwork_game_client_request_remove_player_6\n\t"
      ".long .Lnetwork_game_client_request_remove_player_9\n\t"
      ".text\n\t"
      :
      : [c12ac80] "m"(b1263a0_c12ac80), [assert] "m"(b1263a0_assert), [exitfn] "m"(b1263a0_exitfn), [c12b650] "m"(b1263a0_c12b650), [c8e0b0] "m"(b1263a0_c8e0b0), [c12b700] "m"(b1263a0_c12b700), [c128e00] "m"(b1263a0_c128e00)
      : "memory");
}
#else
#error "network_game_client_request_remove_player: clang naked draft required"
#endif


/* network_game_client_remove_player (0x126590) — XBE naked draft (batch 122). */
#if defined(__clang__)
static void (*const b126590_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b126590_exitfn)(int) = system_exit;
static bool (*const b126590_c12ac80)(void *client) = network_player_is_valid;
static int (*const b126590_c125180)(int stripped_index) = unstrip_player_index;
static bool (*const b126590_c12b290)(void *game, void *player) = network_game_remove_player;
static void *(*const b126590_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const b126590_gtime)(void) = game_time_get;
static void (*const b126590_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b126590_c12a790)(void) = (void (*)(void))network_game_client_all_local_players_have_quit;
static void (*const b126590_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char network_game_client_remove_player(void *client __attribute__((unused)), void *message __attribute__((unused)), int tick __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Lnetwork_game_client_remove_player_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lnetwork_game_client_remove_player_2\n\t"
      ".Lnetwork_game_client_remove_player_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x273\n\t"
      "pushl $0x291774\n\t"
      "pushl $0x291f58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lnetwork_game_client_remove_player_2:\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0xa9e(%%ebx), %%edi\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lnetwork_game_client_remove_player_3:\n\t"
      "leal -0x1c(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_remove_player_4\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movb (%%edi), %%cl\n\t"
      "cmpb 0x1c(%%eax), %%cl\n\t"
      "jne .Lnetwork_game_client_remove_player_4\n\t"
      "movb 0x1(%%edi), %%dl\n\t"
      "cmpb 0x1d(%%eax), %%dl\n\t"
      "je .Lnetwork_game_client_remove_player_5\n\t"
      ".Lnetwork_game_client_remove_player_4:\n\t"
      "incl %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jl .Lnetwork_game_client_remove_player_3\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_remove_player_5:\n\t"
      "shll $5, %%esi\n\t"
      "movsbl 0xaa1(%%esi,%%ebx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c125180]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x85c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c12b290]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "je .Lnetwork_game_client_remove_player_11\n\t"
      "movb 0xc8c(%%ebx), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .Lnetwork_game_client_remove_player_11\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lnetwork_game_client_remove_player_12\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lnetwork_game_client_remove_player_12\n\t"
      "movl 0x5aa6d4, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "je .Lnetwork_game_client_remove_player_6\n\t"
      "call *%[gtime]\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x292aa8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl %%edi, 0xcc(%%ebx)\n\t"
      ".Lnetwork_game_client_remove_player_6:\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $0xa9e, %%edi\n\t"
      ".Lnetwork_game_client_remove_player_7:\n\t"
      "leal -0x1c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c12ac80]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lnetwork_game_client_remove_player_8\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movsbl (%%edi), %%edx\n\t"
      "movzwl (%%eax), %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .Lnetwork_game_client_remove_player_9\n\t"
      ".Lnetwork_game_client_remove_player_8:\n\t"
      "incl %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jl .Lnetwork_game_client_remove_player_7\n\t"
      ".Lnetwork_game_client_remove_player_9:\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jne .Lnetwork_game_client_remove_player_10\n\t"
      "call *%[c12a790]\n\t"
      "pushl $0x292a6c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".Lnetwork_game_client_remove_player_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      ".Lnetwork_game_client_remove_player_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lnetwork_game_client_remove_player_12:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x292a20\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b126590_assert), [exitfn] "m"(b126590_exitfn), [c12ac80] "m"(b126590_c12ac80), [c125180] "m"(b126590_c125180), [c12b290] "m"(b126590_c12b290), [dget] "m"(b126590_dget), [gtime] "m"(b126590_gtime), [c8f390] "m"(b126590_c8f390), [c12a790] "m"(b126590_c12a790), [c12b650] "m"(b126590_c12b650)
      : "memory");
}
#else
#error "network_game_client_remove_player: clang naked draft required"
#endif


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




/* FUN_001268a0 (0x1268a0) — XBE naked draft (batch 111). */
#if defined(__clang__)
static unsigned int (*const b1268a0_c8e370)(void) = system_milliseconds;
static void (*const b1268a0_c128d20)(int connection) = network_connection_keep_alive;
static bool (*const b1268a0_c12a170)(void) = network_game_is_splitscreen_local;
static bool (*const b1268a0_c82300)(void) = transport_network_available;
static void (*const b1268a0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1268a0_ce44d0)(int16_t) = display_error_when_main_menu_loaded;
static void * (*const b1268a0_c12a1d0)(void) = network_game_server_get;
static void (*const b1268a0_c81ec0)(void *dst, int bytes) = transport_get_nonce;
static void (*const b1268a0_c12d250)(void *join_token) = network_game_generate_join_game_token;
static char (*const b1268a0_c124aa0)(void *client, void *game, void *join_token, void *address) = network_game_client_initiate_join_game;
static void (*const b1268a0_c12b650)(const char *fmt, ...) = network_game_log;
static bool (*const b1268a0_c129cf0)(int connection, int flag, int *output) = FUN_00129cf0;
static bool (*const b1268a0_c1260c0)(void *server /* */) = FUN_001260c0;
static void * (*const b1268a0_c12b700)(int type, void *data, int16_t message_struct_size) = encode_network_game_message;
static bool (*const b1268a0_c128e00)(void *connection, void *message, unsigned short size, int dest_address, bool reliable) = network_connection_write;

__attribute__((naked, noinline))
bool FUN_001268a0(void *server /* */ __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x124, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c8e370]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c128d20]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c12a170]\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001268a0_1\n\t"
      "call *%[c82300]\n\t"
      "movb %%al, %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001268a0_1\n\t"
      "pushl $0x2893dc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $6\n\t"
      "call *%[ce44d0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001268a0_1:\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_001268a0_10\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001268a0_2\n\t"
      "movb $0, -0x124(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x38, %%ecx\n\t"
      "leal -0x123(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "stosb\n\t"
      "leal -0x100(%%ebp), %%ecx\n\t"
      "pushl $8\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x7f000001, -0x1c(%%ebp)\n\t"
      "movw $0x141e, -0xa(%%ebp)\n\t"
      "movw $4, -0xc(%%ebp)\n\t"
      "movw %%di, -0x46(%%ebp)\n\t"
      "call *%[c81ec0]\n\t"
      "leal -0x2e(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw %%di, -0x3e(%%ebp)\n\t"
      "call *%[c12d250]\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x124(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c124aa0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001268a0_10\n\t"
      "pushl $7\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[ce44d0]\n\t"
      "pushl $0x292d14\n\t"
      "call *%[c12b650]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_2:\n\t"
      "movl 0x82c(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0x1388\n\t"
      "pushl %%eax\n\t"
      "call *%[c129cf0]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001268a0_3\n\t"
      "pushl $7\n\t"
      "call *%[ce44d0]\n\t"
      "pushl $0x292cc8\n\t"
      "call *%[c12b650]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_3:\n\t"
      "call *%[c1260c0]\n\t"
      "movb %%al, %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001268a0_4\n\t"
      "pushl $0x292c68\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_4:\n\t"
      "movl 0xc94(%%esi), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $0x7d0, %%ecx\n\t"
      "jbe .LFUN_001268a0_7\n\t"
      "call *%[c12a1d0]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_001268a0_10\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl $8\n\t"
      "pushl %%edx\n\t"
      "movw $0x141f, -0x10(%%ebp)\n\t"
      "movw $1, -0xe(%%ebp)\n\t"
      "call *%[c81ec0]\n\t"
      "pushl $0xc\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "movw $4, -0x28(%%ebp)\n\t"
      "movl $0xffffffff, -0x38(%%ebp)\n\t"
      "movw $0x141e, -0x26(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001268a0_6\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $0\n\t"
      "leal -0x38(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c128e00]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpb $1, %%bl\n\t"
      "jne .LFUN_001268a0_5\n\t"
      "pushl $0x292c40\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, 0xc94(%%esi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_5:\n\t"
      "pushl $0x292be0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_6:\n\t"
      "pushl $0x292ba0\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_7:\n\t"
      "cmpb $1, 0x82a(%%esi)\n\t"
      "jne .LFUN_001268a0_10\n\t"
      "movl 0x820(%%esi), %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $0x3e8, %%ecx\n\t"
      "jbe .LFUN_001268a0_10\n\t"
      "pushl $8\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "movl %%edi, -0xc(%%ebp)\n\t"
      "movw $0x141f, -0x8(%%ebp)\n\t"
      "call *%[c12b700]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001268a0_9\n\t"
      "movl 0x82c(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%eax), %%cx\n\t"
      "shrw $4, %%cx\n\t"
      "pushl $0\n\t"
      "leal 0x808(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[c128e00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001268a0_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x820(%%esi)\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_8:\n\t"
      "pushl $0x292b50\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001268a0_9:\n\t"
      "pushl $0x292b1c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001268a0_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b1268a0_c8e370), [c128d20] "m"(b1268a0_c128d20), [c12a170] "m"(b1268a0_c12a170), [c82300] "m"(b1268a0_c82300), [c8f390] "m"(b1268a0_c8f390), [ce44d0] "m"(b1268a0_ce44d0), [c12a1d0] "m"(b1268a0_c12a1d0), [c81ec0] "m"(b1268a0_c81ec0), [c12d250] "m"(b1268a0_c12d250), [c124aa0] "m"(b1268a0_c124aa0), [c12b650] "m"(b1268a0_c12b650), [c129cf0] "m"(b1268a0_c129cf0), [c1260c0] "m"(b1268a0_c1260c0), [c12b700] "m"(b1268a0_c12b700), [c128e00] "m"(b1268a0_c128e00)
      : "memory");
}
#else
#error "FUN_001268a0: clang naked draft required"
#endif


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

/* FUN_001274E0 (0x1274e0) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const b1274e0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1274e0_exitfn)(int) = system_exit;
static char (*const b1274e0_c124d50)(void *client, void *source_address) = network_game_client_address_matches_server;
static int16_t (*const b1274e0_c124a30)(void *server, void *out_param) = network_game_client_get_state;
static bool (*const b1274e0_c12bce0)(int param_1, int param_2, short *param_3, short *param_4, short *param_5, int param_6) = FUN_0012bce0;
static char (*const b1274e0_c125050)(void *client, void *message) = network_game_client_game_settings_updated;
static void (*const b1274e0_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char FUN_001274E0(void *client /* */ __attribute__((unused)), void *source_address /* */ __attribute__((unused)), void *message __attribute__((unused)), int message_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x43c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_001274E0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x169\n\t"
      "pushl $0x293754\n\t"
      "pushl $0x2919a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001274E0_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_001274E0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x16a\n\t"
      "pushl $0x293754\n\t"
      "pushl $0x29373c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001274E0_2:\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c124d50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001274E0_6\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c124a30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_001274E0_5\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $2\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x43c(%%ebp), %%ecx\n\t"
      "subl $2, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $6, -0x4(%%ebp)\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "call *%[c12bce0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001274E0_4\n\t"
      "leal -0x43c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c125050]\n\t"
      "movb %%al, %%bl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001274E0_3\n\t"
      "pushl $0x293708\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001274E0_3:\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001274E0_4:\n\t"
      "pushl $0x2936c8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001274E0_5:\n\t"
      "pushl $0x293670\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001274E0_6:\n\t"
      "pushl $0x293628\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1274e0_assert), [exitfn] "m"(b1274e0_exitfn), [c124d50] "m"(b1274e0_c124d50), [c124a30] "m"(b1274e0_c124a30), [c12bce0] "m"(b1274e0_c12bce0), [c125050] "m"(b1274e0_c125050), [c12b650] "m"(b1274e0_c12b650)
      : "memory");
}
#else
#error "FUN_001274E0: clang naked draft required"
#endif


/* FUN_00127610 (0x127610) — XBE naked draft (batch 130). */
#if defined(__clang__)
static void (*const b127610_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b127610_exitfn)(int) = system_exit;
static char (*const b127610_c124d50)(void *client, void *source_address) = network_game_client_address_matches_server;
static int16_t (*const b127610_c124a30)(void *server, void *out_param) = network_game_client_get_state;
static bool (*const b127610_c12bce0)(int param_1, int param_2, short *param_3, short *param_4, short *param_5, int param_6) = FUN_0012bce0;
static void (*const b127610_c125c60)(void *client, int16_t timer) = network_game_client_countdown_timer_update;
static void (*const b127610_c12b650)(const char *fmt, ...) = network_game_log;

__attribute__((naked, noinline))
char FUN_00127610(void *client /* */ __attribute__((unused)), void *source_address /* */ __attribute__((unused)), void *message __attribute__((unused)), int message_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%edi\n\t"
      "jne .LFUN_00127610_1\n\t"
      "pushl $1\n\t"
      "pushl $0x19b\n\t"
      "pushl $0x293754\n\t"
      "pushl $0x2919a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00127610_1:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00127610_2\n\t"
      "pushl $1\n\t"
      "pushl $0x19c\n\t"
      "pushl $0x293754\n\t"
      "pushl $0x29373c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00127610_2:\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c124d50]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00127610_5\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c124a30]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%ax\n\t"
      "jne .LFUN_00127610_4\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $2\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0xc(%%ebp), %%ecx\n\t"
      "subl $2, %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $7, -0x8(%%ebp)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "call *%[c12bce0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00127610_3\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c125c60]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00127610_3:\n\t"
      "pushl $0x29382c\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00127610_4:\n\t"
      "pushl $0x2937d8\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00127610_5:\n\t"
      "pushl $0x293790\n\t"
      "call *%[c12b650]\n\t"
      "addl $4, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b127610_assert), [exitfn] "m"(b127610_exitfn), [c124d50] "m"(b127610_c124d50), [c124a30] "m"(b127610_c124a30), [c12bce0] "m"(b127610_c12bce0), [c125c60] "m"(b127610_c125c60), [c12b650] "m"(b127610_c12b650)
      : "memory");
}
#else
#error "FUN_00127610: clang naked draft required"
#endif


/* FUN_00127710 (0x127710) — readable C lift: handle server message (esi=client, edi=addr). */
char FUN_00127710(void *client, void *source_address, void *message, int message_size)
{
  short state;
  int decoded_type;
  short a, b;

  __asm__ volatile("movl %%esi, %0" : "=r"(client));
  __asm__ volatile("movl %%edi, %0" : "=r"(source_address));
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
  decoded_type = 0xa;
  a = 1;
  b = 0;
  if (!FUN_0012bce0((int)((char *)message + 2), message_size, &b, &decoded_type, &a, 2)) {
    network_game_log((const char *)0x293904);
    return 1;
  }
  return 1;
}

