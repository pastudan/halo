/* --- network_client_manager.obj batch drafts (2026-07-26) --- */

static char network_client_manager_send_encoded(void *client, void *encoded)
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

/* 0x124730 */
int16_t FUN_00124730(int model_ref, const char *marker_name, char *magic_table,
                     int node_remap, int16_t node_count, void *node_matrices,
                     char mirrored, void *out_markers, int16_t max_markers)
{
  int tag_data;
  int marker_block;
  int marker_count;
  int marker_index;
  int out_count;
  char *marker_elem;
  char *out;
  int16_t node_index;
  int remap_index;

  if (node_matrices == NULL) {
    display_assert("node_matrices",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2f8, 1);
    system_exit(-1);
  }
  if (out_markers == NULL) {
    display_assert("out_markers",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2f9, 1);
    system_exit(-1);
  }

  {
    int16_t (*lookup_marker)(int, const char *) =
      (int16_t (*)(int, const char *))FUN_00123d80;
    marker_index = lookup_marker(model_ref, marker_name);
  }
  if (marker_index == (int16_t)-1)
    return 0;

  tag_data = (int)tag_get(0x6d6f6465, model_ref);
  marker_block = tag_data + 0xac;
  marker_count = *(int *)(marker_block + 0x34);
  out_count = 0;
  marker_index = 0;
  while (marker_index < marker_count) {
    marker_elem = (char *)tag_block_get_element((void *)marker_block, marker_index,
                                                0x20);
    if (magic_table != 0) {
      remap_index = (int)(unsigned char)marker_elem[0];
      if ((char)magic_table[remap_index] != marker_elem[1])
        goto next_marker;
    }
    if (out_count >= max_markers)
      return (int16_t)out_count;
    out_count++;
    out = (char *)out_markers + out_count * 0x6c - 0x6c;
    if (node_remap != 0)
      node_index = *(int16_t *)((char *)node_remap +
                                (int)(unsigned char)marker_elem[2] * 2);
    else
      node_index = *(int16_t *)(tag_data + 0xb8);
    *(int16_t *)out = node_index;
    component_vectors_from_normal3d((float *)(marker_elem + 4),
                                    (float *)(marker_elem + 0x10),
                                    (float *)(out + 4));
    if (node_index < 0 || node_index >= node_count) {
      display_assert("node_index>=0 && node_index<node_count",
                     "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                     0x311, 1);
      system_exit(-1);
    }
    matrix4x3_multiply((float *)((char *)node_matrices + node_index * 0x34),
                       (float *)(out + 4), (float *)(out + 0x38));
    if (mirrored) {
      *(float *)(out + 0x48) = -*(float *)(out + 0x48);
      *(float *)(out + 0x4c) = -*(float *)(out + 0x4c);
      *(float *)(out + 0x50) = -*(float *)(out + 0x50);
    }
  next_marker:
    marker_index++;
  }
  return (int16_t)out_count;
}

/* 0x124900 */
void FUN_00124900(void *model)
{
  char *base;
  int region_index;
  int region_count;
  char *region_block;
  int perm_index;
  int perm_count;

  base = (char *)model + 0xd0;
  region_index = 0;
  region_count = *(int *)base;
  while (region_index < region_count) {
    region_block = (char *)tag_block_get_element((void *)base, region_index, 0x30);
    perm_index = 0;
    perm_count = *(int *)(region_block + 0x24);
    while (perm_index < perm_count) {
      tag_block_get_element((void *)(region_block + 0x24), perm_index, 0x68);
      perm_index++;
    }
    region_index++;
  }
}

/* 0x124a10 */
void network_game_client_keep_alive(void *client)
{
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
}

/* 0x124aa0 */
char network_game_client_initiate_join_game(void *client, void *game,
                                            void *join_token, void *address)
{
  char result;
  unsigned int now;

  if (client == NULL || *(int16_t *)((char *)client + 0xca6) != 0 || game == NULL ||
      join_token == NULL || address == NULL ||
      *(int *)((char *)client + 0x82c) == 0 ||
      network_connection_connected(*(int *)((char *)client + 0x82c)) ||
      *(int16_t *)((char *)game + 0xde) == 0) {
    display_assert("client && (client->state == _network_game_client_state_searching) "
                   "&& game && join_parameters && client->connection && "
                   "!network_connection_connected(client->connection) && "
                   "(game->platform == network_game_get_local_platform())",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x157, 1);
    system_exit(-1);
  }

  *(int *)((char *)client + 0xc90) = 1;
  *(int *)((char *)client + 0x830) = 0;
  now = system_milliseconds();
  *(unsigned int *)((char *)client + 0x834) = now;
  csmemcpy((char *)client + 0x838, join_token, 0x22);
  result = network_connection_connect(*(int *)((char *)client + 0x82c),
                                      (int)address, 0);
  if (result == 1) {
    *(int16_t *)((char *)client + 0xca6) = 1;
    network_game_log("attempting to connect to game @ %s",
                     transport_address_to_string(address));
  } else {
    network_game_log("failed attempt to initiate a connection to game @ %s",
                     transport_address_to_string(address));
  }
  return result;
}

/* 0x124ba0 */
char network_game_client_set_machine(void *client, void *machine)
{
  if (client == NULL || *(uint16_t *)client >= 4 || machine == NULL ||
      *(char *)((char *)machine + 0x40) < 0 || *(char *)((char *)machine + 0x40) >= 4) {
    display_assert("client && (client->machine_index<MAXIMUM_NETWORK_MACHINE_COUNT) "
                   "&& network_machine_is_valid(machine)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x1e1, 1);
    system_exit(-1);
  }
  csmemcpy((char *)client + *(uint16_t *)client * 0x44 + 0x970, machine, 0x44);
  return 1;
}

/* 0x124c10 */
void *network_game_client_get_machine(void *client)
{
  uint16_t index;

  if (client == NULL || (index = *(uint16_t *)client) >= 4)
    return NULL;
  return (void *)((char *)client + index * 0x44 + 0x970);
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

/* 0x124d00 */
int16_t FUN_00124d00(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2bc, 1);
    system_exit(-1);
  }
  return *(int16_t *)((char *)client + 0xca4);
}

/* 0x124d50 */
char network_game_client_address_matches_server(void *client, void *source_address)
{
  int server_addr;

  if (client == NULL) {
    display_assert("client != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2d2, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)client + 0x82c) == 0) {
    display_assert("client->connection",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2d3, 1);
    system_exit(-1);
  }
  if (source_address == NULL) {
    display_assert("source_address",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2d4, 1);
    system_exit(-1);
  }
  if (*(int *)source_address == 0) {
    display_assert("address->address.ipv4_address",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2d5, 1);
    system_exit(-1);
  }
  network_connection_get_address(*(int *)((char *)client + 0x82c), &server_addr, 0);
  return (char)(server_addr == *(int *)source_address);
}

/* 0x124e20 */
void network_game_client_game_out_of_sync(void *client)
{
  int16_t player;

  if (*(char *)0x46e8b8 != 0)
    return;
  network_game_log("local machine is out of sync with the server");
  if (*(char *)((char *)client + 0xcac) == 0) {
    player = local_player_get_next(-1);
    while (player != (int16_t)-1) {
      ui_widget_display_error(8, player, 1, 0);
      player = local_player_get_next(player);
    }
  }
  *(char *)((char *)client + 0xcac) = 1;
}

/* 0x124e90 */
void network_game_client_ponged(void *client, void *source, int timestamp)
{
  unsigned int now;
  unsigned short avg;
  unsigned short count;

  if (client == NULL || source == NULL) {
    display_assert("client && source_address",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x307, 1);
    system_exit(-1);
  }
  if (*(char *)((char *)client + 0x82a) == 0)
    return;
  if (*(int *)((char *)client + 0x808) != *(int *)source)
    return;
  now = system_milliseconds();
  if (timestamp > (int)now)
    return;
  count = *(unsigned short *)((char *)client + 0x826);
  avg = *(unsigned short *)((char *)client + 0x828);
  avg = (unsigned short)((avg * count - timestamp + now) / (count + 1));
  count++;
  *(unsigned short *)((char *)client + 0x826) = count;
  *(unsigned short *)((char *)client + 0x828) = avg;
}

/* 0x124f40 */
void network_game_client_accepted_into_game(void *client, void *source,
                                            void *message)
{
  void *encoded;
  unsigned short size;
  char local_name[0x44];

  if (client == NULL || source == NULL || message == NULL ||
      *(int16_t *)((char *)client + 0xca6) != 1) {
    display_assert("client && source_address && message_packet && "
                   "(client->state == _network_game_client_state_joining)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x327, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)message + 4) < 0 || *(int16_t *)((char *)message + 4) >= 4)
    return;

  *(uint16_t *)client = *(uint16_t *)((char *)message + 4);
  *(char *)((char *)client + *(uint16_t *)client * 0x44 + 0x9b0) =
    *(char *)((char *)message + 4);
  *(int16_t *)((char *)client + 0xca6) = 2;
  network_game_set_random_seed(*(int *)message);
  network_game_log("successfully joined a net game; our machine is #%d",
                   (int)*(int16_t *)((char *)message + 4));
  network_game_generate_local_machine_name(local_name);
  local_name[0x43] = *(char *)((char *)message + 4);
  encoded = encode_network_game_message(0xf, local_name, 0x44);
  if (encoded == NULL) {
    network_game_log("failed to create a message_client_settings_request message");
    return;
  }
  size = (unsigned short)(*(unsigned short *)encoded >> 4);
  if (!network_connection_write((void *)*(int *)((char *)client + 0x82c), encoded,
                                size, 0, 1))
    network_game_log("network_game_client_write() failed while sending a "
                     "message_client_settings_request message");
}

/* 0x125050 */
char network_game_client_game_settings_updated(void *client, void *message)
{
  if (client == NULL || message == NULL) {
    display_assert("client && message_packet",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x375, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)message + 0x112) < 0 ||
      *(int16_t *)((char *)message + 0x112) >= 4 ||
      *(int16_t *)((char *)message + 0x224) < 0 ||
      *(int16_t *)((char *)message + 0x224) >= 0x10)
    return 0;

  if (csstrcmp((char *)client + 0x880, (char *)message + 0x24) != 0) {
    network_game_log("precaching map '%s'...", (char *)message + 0x24);
    main_set_multiplayer_map_name((char *)message + 0x24);
  }
  csmemcpy((char *)client + 0x85c, message, 0x434);
  csmemcpy((char *)client + 0x85c, message, 0x434);
  csmemcpy((char *)client + 0xc8c, (char *)client + 0x85c, 4);
  network_game_log("player count %d machine count %d",
                   (int)*(int16_t *)((char *)message + 0x112),
                   (int)*(int16_t *)((char *)message + 0x224));
  network_game_log("received updated game settings from the server; there are %d "
                   "players on %d machines in the game",
                   (int)*(int16_t *)((char *)message + 0x112),
                   (int)*(int16_t *)((char *)message + 0x224));
  return 1;
}

/* 0x125180 */
int unstrip_player_index(int stripped_index)
{
  data_iter_t iter;
  char *player;

  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  player = (char *)data_iterator_next(&iter);
  while (player != NULL) {
    if ((*(unsigned short *)(player + 8) & 0xffff) ==
        (unsigned short)(stripped_index & 0xffff))
      return *(int *)(player + 4);
    player = (char *)data_iterator_next(&iter);
  }
  return -1;
}

/* 0x1251e0 */
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

/* 0x125380 */
char network_game_client_handle_game_update(void *client, void *message)
{
  int16_t server_tick;
  int16_t msg_tick;
  int clear_count;
  int game_time;

  if (client == NULL || message == NULL) {
    display_assert("client && message_packet",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x40d, 1);
    system_exit(-1);
  }

  msg_tick = *(int16_t *)((char *)message + 0xe);
  server_tick = *(int16_t *)((char *)client + 0xa80);
  if (msg_tick < server_tick) {
    clear_count = (server_tick - msg_tick) << 5;
    csmemset((char *)message + 0x10, 0, clear_count);
    *(int16_t *)((char *)message + 0xe) = server_tick;
  }

  if (*(int *)message != *(int *)((char *)client + 0xc98)) {
    network_game_log("out of sync: client/server random seed mismatch, update= #%ld, "
                     "game time= #%ld (%ld) (#%lx/#%lx)",
                     *(long *)message, *(long *)((char *)message + 8),
                     (long)game_time_get(), *(unsigned long *)message,
                     *(unsigned long *)((char *)client + 0xc98));
    network_game_client_game_out_of_sync(client);
    goto apply;
  }

  if (network_game_server_get() == NULL) {
    game_time = game_time_get();
    if (game_time != *(int *)message ||
        game_time != *(int *)((char *)message + 8)) {
      network_game_log("not a bug, but update %d time %d our time %d",
                       *(int *)message, *(int *)((char *)message + 8), game_time);
    }
    if (game_time != *(int *)((char *)message + 8)) {
      if (*(int *)((char *)message + 4) != (int)get_random_seed()) {
        network_game_log("out of sync: missed a server update (expected #%ld, got #%ld)",
                         (long)*(int *)((char *)message + 8), (long)game_time);
        network_game_client_game_out_of_sync(client);
      }
    }
    if ((*(int *)message % 0x1e) == 0) {
      network_game_log("client is lagging behind the server by #%d game ticks",
                       *(int *)message - game_time_get());
    }
  }

apply:
  {
    char buf[0x200];
    int16_t tick_copy;

    tick_copy = *(int16_t *)((char *)message + 0xe);
    csmemcpy(buf, (char *)message + 0x10, tick_copy << 5);
    FUN_000b97b0(&tick_copy, *(int *)message);
    *(int *)((char *)client + 0xc98) = *(int *)message;
    *(unsigned int *)((char *)client + 0xc9c) = system_milliseconds();
  }
  return 1;
}

/* 0x125510 */
char network_game_client_add_player_to_game(void *client, void *message)
{
  char result;
  int local_index;
  char *spawn_rec;

  result = 0;
  if (client == NULL || message == NULL) {
    display_assert("client && player",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x462, 1);
    system_exit(-1);
  }
  if (!network_player_is_valid(message))
    return 0;
  result = network_game_add_player((char *)client + 0x85c, message);
  if (!result)
    return 0;
  if (*(int16_t *)((char *)client + 0xca6) == 3) {
    spawn_rec = (char *)client + (*(int16_t *)((char *)client + 0xa80) << 5) +
                  0xa62;
    result = network_game_spawn_player(spawn_rec);
    if (!result)
      return 0;
    local_index = unstrip_player_index((int)*(char *)((char *)message + 0x1d));
    if (*(char *)((char *)message + 0x1c) == (char)*(uint16_t *)client) {
      local_player_set_player_index(local_index,
                                    *(int16_t *)((char *)message + 0x1d));
    }
    update_client_add_player(local_index);
    if (network_game_server_get() != NULL)
      FUN_000b8d30(local_index);
  }
  network_game_log("added new player to the game (machine #%d / controller #%d)",
                   (int)*(char *)((char *)message + 0x1c),
                   (int)*(char *)((char *)message + 0x1d));
  return result;
}

/* 0x125660 */
char network_game_client_switch_to_pregame(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x499, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)client + 0xca6) != 2)
    return 1;
  network_game_reset_for_next_round((char *)client + 0x85c, 1);
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
  *(int *)((char *)client + 0xc98) = 0;
  *(int *)((char *)client + 0xc90) = 1;
  *(int *)((char *)client + 0xc9c) = 0;
  *(char *)((char *)client + 0xcad) = 0;
  *(int16_t *)((char *)client + 0xca6) = 2;
  *(char *)((char *)client + 0xcac) = 0;
  network_game_log("switching to pregame");
  network_game_reset_to_pregame_ui();
  network_connection_keep_alive(*(int *)((char *)client + 0x82c));
  return 1;
}

static char network_client_manager_send_player_request(void *client, void *payload,
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

/* 0x1258a0 */
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

/* 0x125a90 */
char network_game_client_update_local_player_data(void *client, void *player)
{
  char payload[0x20];
  void *encoded;
  unsigned short size;

  if (client == NULL || player == NULL) {
    display_assert("client && player",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x587, 1);
    system_exit(-1);
  }
  if ((int)*(char *)((char *)player + 0x1c) != (int)*(uint16_t *)client) {
    display_assert("player->machine_index==client->machine_index",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x588, 1);
    system_exit(-1);
  }
  if (!network_player_is_valid(player)) {
    display_assert("network_player_is_valid(player)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x589, 1);
    system_exit(-1);
  }
  csmemcpy(payload, player, 0x20);
  if ((unsigned char)payload[0x1e] == 0xffu)
    payload[0x1e] = 0;
  encoded = encode_network_game_message(0x10, payload, 0x20);
  if (encoded == NULL)
    return 0;
  size = (unsigned short)(*(unsigned short *)encoded >> 4);
  if (!network_connection_write((void *)*(int *)((char *)client + 0x82c), encoded,
                                size, 0, 1)) {
    network_game_log("network_game_client_update_local_player_data() failed while "
                     "sending a message_client_player_settings_request message");
    return 0;
  }
  return 1;
}

/* 0x125b90 */
char FUN_00125b90(void *client, short request_type)
{
  void *encoded;
  unsigned short size;
  short payload;

  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x5a5, 1);
    system_exit(-1);
  }
  if (request_type < 0 || request_type >= 4) {
    display_assert("(request_type>=0) && (request_type<NUMBER_OF_GAME_START_REQUESTS)",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x5a6, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)client + 0xca6) != 2) {
    network_game_log("failed to send a message_client_game_start_request because we "
                     "are not in the pregame state");
    return 1;
  }
  payload = request_type;
  encoded = encode_network_game_message(0x11, &payload, 2);
  if (encoded == NULL)
    goto fail;
  size = (unsigned short)(*(unsigned short *)encoded >> 4);
  if (!network_connection_write((void *)*(int *)((char *)client + 0x82c), encoded,
                                size, 0, 1))
    goto fail;
  return 1;
fail:
  network_game_log("network_game_client_request_start_time_change() failed to send a "
                   "message_client_game_start_request message");
  return 1;
}

/* 0x125c60 */
void network_game_client_countdown_timer_update(void *client, int16_t timer)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x5c3, 1);
    system_exit(-1);
  }
  *(int16_t *)((char *)client + 0xca4) = timer;
}

/* 0x125cb0 */
char network_game_client_advertised_game_is_valid(void *game)
{
  if (*(char *)((char *)game + 0xe1) == 0)
    return 0;
  if (system_milliseconds() - *(unsigned int *)((char *)game + 0x2c) > 0x1770u)
    return 0;
  return 1;
}

/* 0x125ce0 */
char FUN_00125ce0(void *slot_array /* @<edi> */, void *advertised_game)
{
  char *slots;
  char *slot;
  int i;
  char closed;
  char found;

  closed = 0;
  if ((*(unsigned char *)((char *)advertised_game + 0x102) & 2) != 0 &&
      *(int16_t *)((char *)advertised_game + 0xfa) >= 4)
    closed = 1;

  slots = (char *)slot_array;
  for (i = 0; i < 9; i++) {
    slot = slots + i * 0xe4;
    if (*(char *)(slot + 0xe1) != 0 &&
        system_milliseconds() - *(unsigned int *)(slot + 0x2c) > 0x1770u)
      csmemset(slot, 0, 0xe4);
  }

  slots = (char *)slot_array;
  for (i = 0; i < 9; i++) {
    slot = slots + i * 0xe4;
  {
    char (*nonce_eq)(void *, void *) =
      (char (*)(void *, void *))transport_nonce_is_equal;
    if (nonce_eq((char *)advertised_game + 8, slot + 0x24))
      goto copy_slot;
  }
  }

  slots = (char *)slot_array;
  for (i = 0; i < 9; i++) {
    slot = slots + i * 0xe4;
    if (*(char *)(slot + 0xe1) == 0)
      goto copy_slot;
  }

  if (closed) {
    for (i = 0; i < 9; i++) {
      slot = slots + i * 0xe4 + 0xe0;
      if (slot[1] == 0) {
        display_assert("current->valid",
                       "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                       0x61f, 1);
        system_exit(-1);
      }
      if (*slot == 0) {
        csmemset(slot - 0xe0, 0, 0xe4);
        goto copy_slot;
      }
    }
    error(2, "not fatal, but we have to many active network games cannot add more "
             "to the list");
    return 0;
  }

  slots = (char *)slot_array;
  for (i = 0; i < 9; i++) {
    if (*(char *)(slots + i * 0xe4 + 0xe1) == 0) {
      slot = slots + i * 0xe4;
      goto copy_slot;
    }
  }
  return 0;

copy_slot:
  found = 1;
  *(char *)(slot + 0xe1) = 1;
  csmemcpy(slot + 8, (char *)advertised_game + 0x18, 0x10);
  *(int *)slot = *(int *)((char *)advertised_game + 0x10);
  *(int *)(slot + 4) = *(int *)((char *)advertised_game + 0x14);
  csmemcpy(slot + 0x18, (char *)advertised_game + 0x28, 0xc);
  csmemcpy(slot + 0x24, (char *)advertised_game + 8, 8);
  *(unsigned int *)(slot + 0x2c) = system_milliseconds();
  *(int16_t *)(slot + 0xde) = *(int16_t *)((char *)advertised_game + 0x38);
  if (*(int16_t *)((char *)advertised_game + 0x3a) != 0)
    ustrncpy((wchar_t *)(slot + 0x30), (wchar_t *)((char *)advertised_game + 0x3a),
             0xf);
  else {
    static wchar_t xbox_name[] = { (wchar_t)'X', (wchar_t)'B', (wchar_t)'o',
                                   (wchar_t)'x', 0 };
    ustrncpy((wchar_t *)(slot + 0x30), xbox_name, 0xf);
  }
  csmemcpy(slot + 0x50, (char *)advertised_game + 0x74, 0x84);
  *(int16_t *)(slot + 0x4e) = 0;
  *(int16_t *)(slot + 0xd4) = *(int16_t *)((char *)advertised_game + 0xf8);
  *(int16_t *)(slot + 0xd6) = *(int16_t *)((char *)advertised_game + 0xfa);
  *(int16_t *)(slot + 0xd8) = *(int16_t *)((char *)advertised_game + 0xfc);
  *(int16_t *)(slot + 0xda) = *(int16_t *)((char *)advertised_game + 0xfe);
  return found;
}

/* 0x125fb0 */
void FUN_00125fb0(void *client /* @<esi> */, int16_t reason /* @<ax> */)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x662, 1);
    system_exit(-1);
  }
  if ((unsigned short)reason >= 9u)
    reason = 1;
  if (*(int16_t *)((char *)client + 0xca8) == 0)
    *(int16_t *)((char *)client + 0xca8) = reason;
}

/* 0x126140 */
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

/* 0x1263a0 */
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

/* 0x126590 */
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

/* 0x126700 */
void network_game_client_new_advertised_game(void *client, void *message)
{
  if (client == NULL || message == NULL) {
    display_assert("client && message_packet",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x2fc, 1);
    system_exit(-1);
  }
  FUN_00125ce0((char *)client + 4, message);
}

/* 0x126750 */
void network_game_client_game_shutdown(void *client)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x3fc, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)client + 0xca8) == 0)
    *(int16_t *)((char *)client + 0xca8) = 8;
  network_game_log("the game host is shutting down");
  network_game_client_all_local_players_have_quit();
}

/* 0x1267c0 */
void network_game_client_reset(void *client, char flag)
{
  if (client == NULL) {
    display_assert("client",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x4ee, 1);
    system_exit(-1);
  }
  network_game_invalidate((char *)client + 0x85c);
  *(uint16_t *)client = (uint16_t)-1;
  *(int16_t *)((char *)client + 0xca6) = 0;
  if (flag && *(int *)((char *)client + 0x82c) != 0 &&
      network_connection_connected(*(int *)((char *)client + 0x82c))) {
    *(int *)((char *)client + 0xc90) = 1;
    if (FUN_00129980(*(int *)((char *)client + 0x82c)))
      *(unsigned char *)((char *)client + 0xcaa) &= 0xfeu;
  }
}

/* 0x1268a0 */
bool FUN_001268a0(void *server /* @<eax> */)
{
  bool result;
  unsigned int now;
  char search_buf[0x124];
  char join_params[0x2e];

  result = 1;
  now = system_milliseconds();
  (void)now;
  network_connection_keep_alive(*(int *)((char *)server + 0x82c));

  if (!network_game_is_splitscreen_local()) {
    result = transport_network_available();
    if (!result) {
      error(2, "network connection went down!");
      display_error_when_main_menu_loaded(6);
    }
  }
  if (!result)
    return result;

  if (network_game_server_get() != NULL)
    goto idle;

  csmemset(search_buf, 0, sizeof(search_buf));
  *(int *)(search_buf + 0x108) = 0x7f000001;
  *(int16_t *)(search_buf + 0x116) = 0x141e;
  *(int16_t *)(search_buf + 0x114) = 4;
  transport_get_nonce(search_buf + 0x100, 8);
  network_game_generate_join_game_token(join_params);
  if (!network_game_client_initiate_join_game(server, search_buf + 0xe4,
                                              join_params, search_buf + 0x108)) {
    display_error_when_main_menu_loaded(7);
    network_game_log("network_game_client_initiate_join_game() failed");
    return 0;
  }

idle:
  result = FUN_00129cf0(*(int *)((char *)server + 0x82c), 5000, 0);
  if (!result) {
    network_game_log("network_connection_idle() failed in "
                     "network_game_client_idle_searching()");
    return 0;
  }
  result = FUN_001260c0(server);
  if (!result)
    network_game_log("network_game_client_process_incoming_messages() failed in "
                     "network_game_client_idle_searching()");
  return result;
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
  network_game_client_reset((void *)0x5a95a0, 0);
  return (void *)0x5a95a0;
}

/* 0x1271a0 */
void FUN_001271a0(void *client, void *source, int rejection_code)
{
  const char *reason;

  if (client == NULL || source == NULL) {
    display_assert("client && source_address",
                   "c:\\halo\\SOURCE\\networking\\network_client_manager.c",
                   0x35a, 1);
    system_exit(-1);
  }

  *(int16_t *)((char *)client + 0xca6) = 0;
  switch (rejection_code) {
  case 0: reason = "_rejection_code_blacklisted_machine"; break;
  case 1: reason = "_rejection_code_game_is_closed"; break;
  case 2: reason = "_rejection_code_game_is_full"; break;
  case 3: reason = "_rejection_code_bad_password"; break;
  case 4: reason = "_rejection_code_bad_join_token"; break;
  case 5: reason = "_rejection_code_version_too_new"; break;
  case 6: reason = "_rejection_code_version_too_old"; break;
  default:
    network_game_log("unable to join game: reason= #%d/%s", rejection_code, "unknown");
    network_game_client_reset(client, 1);
    return;
  }
  network_game_log("unable to join game: reason= #%d/%s", rejection_code, reason);
  network_game_client_reset(client, 1);
}

/* 0x127260 */
char FUN_00127260(void *client /* @<esi> */, void *message, int message_size,
                  void *source_address)
{
  char decoded[0x11c];
  int packet_type;
  int packet_version;

  if (network_game_client_get_state(client, NULL) != 0) {
    network_game_log("ignoring an advertised game because we are not looking for new "
                     "games");
    return 1;
  }
  message_size -= 2;
  packet_type = 2;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 1)) {
    network_game_log("failed to decode a message_server_game_advertise packet");
    return 1;
  }
  {
    char (*advertised_valid)(void *, int) = (char (*)(void *, int))FUN_00081fa0;
    if (!advertised_valid(decoded, 8))
      return 1;
  }
  network_game_client_new_advertised_game(client, decoded);
  return 1;
}

/* 0x127310 */
char FUN_00127310(void *client /* @<esi> */, void *message, int message_size,
                  void *source_address)
{
  char decoded[0xc];
  int packet_type;
  int packet_version;
  int timestamp;

  if (network_game_client_get_state(client, NULL) != 0) {
    network_game_log("ignoring a pong message because we are not listening for them");
    return 1;
  }
  message_size -= 2;
  packet_type = 3;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 1)) {
    network_game_log("failed to decode a message_server_pong packet");
    return 1;
  }
  timestamp = *(int *)decoded;
  network_game_client_ponged(client, source_address, timestamp);
  return 1;
}

/* 0x1273a0 */
char FUN_001273a0(void *client /* @<esi> */, void *source_address /* @<edi> */,
                  void *message, int message_size)
{
  char decoded[0x10];
  int packet_type;
  int packet_version;

  if (!network_game_client_address_matches_server(client, source_address))
    return 1;
  if (network_game_client_get_state(client, NULL) != 1)
    return 1;
  message_size -= 2;
  packet_type = 4;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 2)) {
    network_game_log("failed to decode a message_server_machine_accepted packet");
    return 1;
  }
  network_game_client_accepted_into_game(client, source_address, decoded);
  return 1;
}

/* 0x127440 */
char FUN_00127440(void *client /* @<esi> */, void *source_address /* @<edi> */,
                  void *message, int message_size)
{
  char decoded[0xc];
  int packet_type;
  int packet_version;

  if (!network_game_client_address_matches_server(client, source_address))
    return 1;
  if (network_game_client_get_state(client, NULL) != 1)
    return 1;
  message_size -= 2;
  packet_type = 5;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 2)) {
    network_game_log("failed to decode a message_server_machine_rejected packet");
    return 1;
  }
  FUN_001271a0(client, source_address, *(int *)decoded);
  return 1;
}

/* 0x1274e0 */
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

/* 0x127610 */
char FUN_00127610(void *client /* @<esi> */, void *source_address /* @<eax> */,
                    void *message, int message_size)
{
  char decoded[0xc];
  int packet_type;
  int packet_version;

  if (client == NULL) {
    display_assert("client != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x19b, 1);
    system_exit(-1);
  }
  if (source_address == NULL) {
    display_assert("source_address != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x19c, 1);
    system_exit(-1);
  }
  if (!network_game_client_address_matches_server(client, source_address))
    return 1;
  if (network_game_client_get_state(client, NULL) != 2)
    return 1;
  message_size -= 2;
  packet_type = 7;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 2)) {
    network_game_log("failed to decode a message_server_pregame_countdown packet");
    return 1;
  }
  network_game_client_countdown_timer_update(client, *(int16_t *)decoded);
  return 1;
}

/* 0x127710 */
char FUN_00127710(void *client /* @<esi> */, void *source_address /* @<edi> */,
                    void *message, int message_size)
{
  char decoded[4];
  int packet_type;
  int packet_version;

  if (client == NULL) {
    display_assert("client != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x1c4, 1);
    system_exit(-1);
  }
  if (source_address == NULL) {
    display_assert("source_address != NULL",
                   "c:\\halo\\SOURCE\\networking\\network_client_message_handler.c",
                   0x1c5, 1);
    system_exit(-1);
  }
  if (!network_game_client_address_matches_server(client, source_address))
    return 1;
  if (network_game_client_get_state(client, NULL) != 2) {
    network_game_log("failed to handle a message_server_pregame_keep_alive message; we "
                     "are not in pregame");
    return 1;
  }
  message_size -= 2;
  packet_type = 0xa;
  packet_version = 1;
  if (!FUN_0012bce0((int)decoded, (int)message + 2, (short *)&message_size,
                    (short *)&packet_type, (short *)&packet_version, 2)) {
    network_game_log("failed to decode a message_server_pregame_keep_alive packet");
    return 1;
  }
  return 1;
}

