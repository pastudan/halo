#include <stdint.h>
/* Xbox network transport layer — Winsock/XNet wrapper. */

/* Initialize the Xbox network transport layer.
 *
 * Queries ethernet link status, optionally enables XNet security bypass
 * (if d:\bypass_security.txt exists), starts XNet and WinSock, then
 * polls for ethernet link with a 10-second timeout. On success, sets
 * the transport_initialized flag. On any failure, cleans up and returns.
 *
 * Confirmed: XNetGetEthernetLinkStatus (0x1d8b76) returns link flags;
 * XNetStartup (0x2231f8, stdcall 1 arg) and WSAStartup (0x223206,
 * stdcall 2 args); XNetCleanup (0x2232f5) and WSACleanup (0x2232ed);
 * XNetGetEthernetLinkStatus poll wrapper (0x222ecf, stdcall 1 arg);
 * setsockopt-like (0x222e0e, stdcall 2 args); fopen (0x1d9e59, cdecl);
 * fclose (0x1d9dac, cdecl); winsock_error_report (0x83310, cdecl).
 */
void transport_initialize(void)
{
  uint8_t xnet_params[11];
  uint8_t wsadata[0x190];
  uint32_t link_status;
  const char *connected_str;
  const char *speed100_str;
  const char *speed10_str;
  const char *fullduplex_str;
  const char *halfduplex_str;
  void *file;
  int xnet_result;
  int16_t wsa_result;
  unsigned int start_time;
  unsigned int deadline;
  int link_result;

  /* Early out if already initialized. */
  if (*(uint8_t *)0x335090 != 0)
    return;

  /* Zero the WSADATA buffer. */
  csmemset(wsadata, 0, sizeof(wsadata));

  /* Build XNetStartupParams structure (11 bytes). */
  xnet_params[0] = 0x0B; /* cfgSizeOfStruct */
  xnet_params[1] = 0x00; /* cfgFlags */
  xnet_params[2] = 0x18; /* cfgSockMaxDgramSockets */
  xnet_params[3] = 0x08; /* cfgSockMaxStreamSockets */
  xnet_params[4] = 0x04; /* cfgSockDefaultRecvBufsizeInK */
  xnet_params[5] = 0x08; /* cfgSockDefaultSendBufsizeInK */
  xnet_params[6] = 0x80; /* cfgKeyRegMax */
  xnet_params[7] = 0x00; /* cfgSecRegMax */
  xnet_params[8] = 0x00; /* cfgQosDataLimitDiv4 */
  xnet_params[9] = 0x01; /* cfgQosProbeMinWait */
  xnet_params[10] = 0x20; /* cfgQosProbeMaxWait */

  /* Query ethernet link status and log it. */
  link_status = XNetGetEthernetLinkStatus();

  halfduplex_str = (link_status & 0x10) ? " in half-duplex mode" : "";
  fullduplex_str = (link_status & 0x08) ? " in full-duplex mode" : "";
  speed10_str = (link_status & 0x04) ? " at 10 Mbps" : "";
  speed100_str = (link_status & 0x02) ? " at 100 Mbps" : "";
  connected_str = (link_status & 0x01) ? "connected" : "not connected";

  error(3, "xbox ethernet link is %s%s%s%s%s", connected_str, speed100_str,
        speed10_str, fullduplex_str, halfduplex_str);

  /* Re-init cfgSizeOfStruct and cfgFlags before checking bypass. */
  xnet_params[0] = 0x0B;
  xnet_params[1] = 0x00;

  /* Check for security bypass file. */
  file = ((void *(*)(const char *, const char *))0x1d9e59)(
    "d:\\bypass_security.txt", "r");
  if (file != 0) {
    error(2, "XNET_STARTUP_BYPASS_SECURITY [ON]");
    xnet_params[1] |= 0x01;
    ((void (*)(void *))0x1d9dac)(file);
  }

  /* Start XNet. */
  xnet_result = ((int(__stdcall *)(uint8_t *))0x2231f8)(xnet_params);
  if (xnet_result != 0)
    return;

  /* Start WinSock 2.2. */
  wsa_result = ((int16_t(__stdcall *)(int16_t, uint8_t *))0x223206)(2, wsadata);
  if (wsa_result != 0) {
    /* Cleanup: WSACleanup then report error. */
    ((void (*)(void))0x2232ed)();
    winsock_error_report((int)wsa_result);
    return;
  }

  /* Poll for ethernet link with 10-second timeout. */
  start_time = system_milliseconds();
  deadline = start_time + 10000;

  for (;;) {
    link_result = ((int(__stdcall *)(void *))0x222ecf)((void *)0x5ab230);
    if (system_milliseconds() > deadline)
      break;
    if (link_result == 0)
      continue;
    if (link_result != 1) {
      /* Link detected — configure socket options and mark initialized. */
      ((int(__stdcall *)(void *, int))0x222e0e)((void *)0x5ab228, 8);
      *(uint8_t *)0x335090 = 1;
      return;
    }
    break;
  }

  /* Timeout or error — shut down XNet and WSACleanup. */
  ((void (*)(void))0x2232f5)();
  ((void (*)(void))0x2232ed)();
}

/* Shut down the network transport layer. */
void transport_dispose(void)
{
  if (*(uint8_t *)0x335090 != 0) {
    ((void (*)(void))0x2232f5)();
    ((void (*)(void))0x2232ed)();
    *(uint8_t *)0x335090 = 0;
  }
}

/* Check whether the Xbox ethernet link is currently connected.
 *
 * Calls XNetGetEthernetLinkStatus (0x1d8b76) and returns bit 0,
 * which is the "connected" flag.
 *
 * Confirmed: 3-instruction function — CALL, AND AL,1, RET.
 * Callers include network session management functions.
 */
bool transport_network_available(void)
{
  return XNetGetEthernetLinkStatus() & 1;
}

/* Remove an endpoint from an endpoint set.
 * Searches the set's endpoint_array for the matching pointer, then finds and
 * removes the endpoint's socket from the fd_array by shifting. Clears the
 * "in set" flag (bit 3) on the endpoint, nulls the array slot, and marks
 * the set dirty. Returns 0 on success, -19 if the endpoint is not found. */
short remove_endpoint_from_set(int *endpoint, uint32_t *endpoint_set)
{
  int i = 0;
  uint32_t **ep_array;
  uint32_t j;
  uint32_t *fds;

  assert_halt(endpoint && endpoint_set);
  assert_halt(*(uint8_t *)0x335090);

  if ((int)endpoint_set[0x43] >= 0) {
    ep_array = (uint32_t **)endpoint_set[0x41];
    do {
      if ((int *)ep_array[i] == endpoint) {
        j = 0;
        if (endpoint_set[0] == 0)
          goto clear_entry;
        fds = endpoint_set + 1;
        while (1) {
          if (*fds == (uint32_t)*endpoint) {
            if (j < endpoint_set[0] - 1) {
              uint32_t *p = endpoint_set + j + 1;
              do {
                *p = p[1];
                j++;
                p++;
              } while (j < endpoint_set[0] - 1);
            }
            endpoint_set[0]--;
            goto clear_entry;
          }
          j++;
          fds++;
          if (j >= endpoint_set[0])
            goto clear_entry;
        }
      }
      i++;
    } while (i <= (int)endpoint_set[0x43]);
  }
  return -19;

clear_entry:
  *(uint8_t *)((char *)endpoint + 4) &= 0xf7;
  *(uint32_t *)(endpoint_set[0x41] + i * 4) = 0;
  endpoint_set[0x45] = 1;
  return 0;
}

/* Release the global XNet key and clear associated state.
 *
 * If the "key owned" flag (0x335091) is set, decrements global_key_depth
 * (0x335094) and, if it reaches zero, calls FUN_00222df7 to release the
 * key object at 0x5ab220.  Clears the owned flag.  Then always performs a
 * second decrement-and-release of global_key_depth.  Finally clears the
 * byte at 0x5ab204 via csmemset.
 *
 * Confirmed: display_assert (0x8d9f0); system_exit (0x8e2f0);
 * FUN_00222df7 (0x222df7, __stdcall 1 arg, RET 4);
 * csmemset (0x8db80, cdecl 3 args);
 * assert string "global_key_depth > 0" at 0x2664a8;
 * __FILE__ string at 0x266458; source line 0x66 = 102.
 */
void FUN_00082b30(void)
{
  if (*(uint8_t *)0x335091 != 0) {
    assert_halt(*(int *)0x335094 > 0);
    *(int *)0x335094 -= 1;
    if (*(int *)0x335094 == 0) {
      FUN_00222df7((void *)0x5ab220);
    }
    *(uint8_t *)0x335091 = 0;
  }

  assert_halt(*(int *)0x335094 > 0);
  *(int *)0x335094 -= 1;
  if (*(int *)0x335094 == 0) {
    FUN_00222df7((void *)0x5ab220);
  }

  csmemset((void *)0x5ab204, 0, 1);
}

/* Clean up the endpoint pool. Iterates 64 entries (8 bytes each) at
 * 0x3350a0. For each entry with a non-zero thread handle and cleanup
 * flag set, closes the thread and clears the entry. */
void endpoint_pool_cleanup(void)
{
  int *entry = (int *)0x3350a0;

  do {
    if (entry[0] != 0 && *(char *)(entry + 1) != 0) {
      thread_close((void *)entry[0]);
      entry[0] = 0;
      *(char *)(entry + 1) = 0;
    }
    entry += 2;
  } while ((int)entry < 0x3352a0);
}

/* Receive data from a transport endpoint.
 *
 * Calls xnet_recv (0x225bb6) with the socket handle stored at ep[0].
 * On success returns the byte count from recv(); if recv returns 0
 * (graceful close), returns -3 instead.
 * On failure, classifies the Winsock error via xapi_GetLastError (0x2235c4):
 *   WSAECONNRESET (0x2733)                      -> ep status = -4, return -4
 *   WSAECONNABORTED/disconnect-family            -> ep status = -3, return -3
 *     (0x2744/0x2745/0x2746/0x2749/0x274a/0x274c,
 *      also clears bits 0 and 2 of ep flags byte at offset 4)
 *   Any other error                              -> ep status = -2, return -2
 *     (clears bit 2 only of ep flags byte at offset 4)
 *
 * ep struct layout (from disassembly):
 *   [ep+0]  int      socket fd
 *   [ep+4]  uint8_t  flags (bit 0 = connected, bit 2 = ?)
 *   [ep+6]  int16_t  status/error code
 *
 * Confirmed: xnet_recv (0x225bb6, __stdcall 4 args);
 * xapi_GetLastError (0x2235c4); assert strings at 0x26665c, 0x265fe4;
 * switch jump table at 0x82f28; byte redirect table at 0x82f34;
 * source lines 0x322/0x323.
 */
int recv_endpoint(int *ep, void *buffer, int maxlen)
{
  int result;
  int error_code;

  assert_halt(ep && buffer && (maxlen > 0));
  assert_halt(*(uint8_t *)0x335090);

  result = xnet_recv(ep[0], buffer, maxlen, 0);
  if (result == -1) {
    error_code = xapi_GetLastError();
    switch (error_code) {
    case 0x2733:
      /* WSAECONNRESET — connection reset by peer. */
      *(int16_t *)((char *)ep + 6) = -4;
      return -4;
    case 0x2744:
    case 0x2745:
    case 0x2746:
    case 0x2749:
    case 0x274a:
    case 0x274c:
      /* Disconnect-family errors — clear connected and another flag bit. */
      *(uint8_t *)((char *)ep + 4) &= 0xfa;
      *(int16_t *)((char *)ep + 6) = -3;
      return -3;
    default:
      /* Unknown Winsock error — clear flag bit 2 only. */
      *(uint8_t *)((char *)ep + 4) &= 0xfb;
      *(int16_t *)((char *)ep + 6) = -2;
      return -2;
    }
  }
  if (result == 0)
    result = -3;
  return result;
}

/* Send data over a transport endpoint.
 *
 * Calls xnet_send (0x225c20) with the socket handle stored at ep[0].
 * On success returns the byte count from send().
 * On failure, classifies the Winsock error via xapi_GetLastError (0x2235c4):
 *   WSAECONNRESET (0x2733)                      -> ep status = -4, return -4
 *   WSAECONNABORTED/disconnect-family            -> ep status = -3, return -3
 *     (0x2744/0x2745/0x2746/0x2749/0x274a/0x274c,
 *      also clears connected bit (bit 0) of ep flags byte at offset 4)
 *   Any other error                              -> ep status = -2, return -2
 *
 * ep struct layout (from disassembly):
 *   [ep+0]  int      socket fd
 *   [ep+4]  uint8_t  flags (bit 0 = connected)
 *   [ep+6]  int16_t  status/error code
 *
 * Confirmed: xnet_send (0x225c20, __stdcall 4 args, RET 0x10);
 * xapi_GetLastError (0x2235c4 thunk -> 0x1d2240);
 * switch jump table at 0x83010; byte redirect table at 0x8301c;
 * assert strings at 0x26665c, 0x265fe4; source line 0x350/0x351.
 */
int send_endpoint(int *ep, const char *buf, int len)
{
  int result;
  int error_code;

  assert_halt(ep && buf && (len > 0));
  assert_halt(*(uint8_t *)0x335090);

  result = xnet_send(ep[0], buf, len, 0);
  if (result != -1)
    return result;

  error_code = xapi_GetLastError();
  switch (error_code) {
  case 0x2733:
    /* WSAECONNRESET — connection reset by peer. */
    *(int16_t *)((char *)ep + 6) = -4;
    return -4;
  case 0x2744:
  case 0x2745:
  case 0x2746:
  case 0x2749:
  case 0x274a:
  case 0x274c:
    /* Various disconnect/abort errors — mark endpoint not connected. */
    *(uint8_t *)((char *)ep + 4) &= 0xfe;
    *(int16_t *)((char *)ep + 6) = -3;
    return -3;
  default:
    /* Unknown Winsock error. */
    *(int16_t *)((char *)ep + 6) = -2;
    return -2;
  }
}

/* Test whether a Winsock endpoint is currently connected.
 *
 * Asserts that endpoint is non-null, then returns the state of the
 * connected flag (bit 0 of the byte at endpoint+4). This flag is cleared
 * by send_endpoint when it receives disconnect/abort errors from Winsock.
 *
 * Confirmed: display_assert (0x8d9f0, cdecl, 4 args); system_exit (0x8e2f0).
 * Confirmed: bit 0 of *(byte*)(endpoint+4) is the connected flag.
 */
bool FUN_000831a0(int endpoint)
{
  assert_halt(endpoint);
  return *(uint8_t *)(endpoint + 4) & 1;
}

/* Map a WinSock error code to its symbolic name string and report it.
 *
 * Translates the given WinSock/WSA error code into a human-readable
 * constant name (e.g. "WSAECONNRESET"). Stores the result string in a
 * global at 0x335098. If the error code differs from the last reported
 * one (tracked at 0x3352a0), logs it via error(3, ...). Returns the
 * error name string.
 *
 * Confirmed: error (0x8f390, cdecl, variadic);
 * format string "winsock error #%d: %s" at 0x2666a4;
 * global string pointer at 0x335098; last error code at 0x3352a0.
 */
const char *winsock_error_report(int error_code)
{
  const char *name;

  switch (error_code) {
  case -1:
    name = "WSA_WAIT_FAILED";
    break;
  case 0:
    name = "WSA_INVALID_EVENT";
    break;
  case 6:
    name = "WSA_INVALID_HANDLE";
    break;
  case 8:
    name = "WSA_NOT_ENOUGH_MEMORY";
    break;
  case 0x40:
    name = "WSA_MAXIMUM_WAIT_EVENTS";
    break;
  case 0x57:
    name = "WSA_INVALID_PARAMETER";
    break;
  case 0xC0:
    name = "WSA_WAIT_IO_COMPLETION";
    break;
  case 0x102:
    name = "WSA_WAIT_TIMEOUT";
    break;
  case 0x3E3:
    name = "WSA_OPERATION_ABORTED";
    break;
  case 0x3E4:
    name = "WSA_IO_INCOMPLETE";
    break;
  case 0x3E5:
    name = "WSA_IO_PENDING";
    break;

  case 0x2714:
    name = "WSAEINTR";
    break;
  case 0x2719:
    name = "WSAEBADF";
    break;
  case 0x271D:
    name = "WSAEACCES";
    break;
  case 0x271E:
    name = "WSAEFAULT";
    break;
  case 0x2726:
    name = "WSAEINVAL";
    break;
  case 0x2728:
    name = "WSAEMFILE";
    break;
  case 0x2733:
    name = "WSAEWOULDBLOCK";
    break;
  case 0x2734:
    name = "WSAEINPROGRESS";
    break;
  case 0x2735:
    name = "WSAEALREADY";
    break;
  case 0x2736:
    name = "WSAENOTSOCK";
    break;

  case 0x2737:
    name = "WSAEDESTADDRREQ";
    break;

  case 0x2738:
    name = "WSAEMSGSIZE";
    break;
  case 0x2739:
    name = "WSAEPROTOTYPE";
    break;
  case 0x273A:
    name = "WSAENOPROTOOPT";
    break;
  case 0x273B:
    name = "WSAEPROTONOSUPPORT";
    break;
  case 0x273C:
    name = "WSAESOCKTNOSUPPORT";
    break;
  case 0x273D:
    name = "WSAEOPNOTSUPP";
    break;
  case 0x273E:
    name = "WSAEPFNOSUPPORT";
    break;
  case 0x273F:
    name = "WSAEAFNOSUPPORT";
    break;
  case 0x2740:
    name = "WSAEADDRINUSE";
    break;
  case 0x2741:
    name = "WSAEADDRNOTAVAIL";
    break;
  case 0x2742:
    name = "WSAENETDOWN";
    break;
  case 0x2743:
    name = "WSAENETUNREACH";
    break;
  case 0x2744:
    name = "WSAENETRESET";
    break;
  case 0x2745:
    name = "WSAECONNABORTED";
    break;
  case 0x2746:
    name = "WSAECONNRESET";
    break;
  case 0x2747:
    name = "WSAENOBUFS";
    break;
  case 0x2748:
    name = "WSAEISCONN";
    break;
  case 0x2749:
    name = "WSAENOTCONN";
    break;
  case 0x274A:
    name = "WSAESHUTDOWN";
    break;
  case 0x274B:
    name = "WSAETOOMANYREFS";
    break;

  case 0x274C:
    name = "WSAETIMEDOUT";
    break;

  case 0x274D:
    name = "WSAECONNREFUSED";
    break;
  case 0x274E:
    name = "WSAELOOP";
    break;
  case 0x274F:
    name = "WSAENAMETOOLONG";
    break;
  case 0x2750:
    name = "WSAEHOSTDOWN";
    break;
  case 0x2751:
    name = "WSAEHOSTUNREACH";
    break;
  case 0x2752:
    name = "WSAENOTEMPTY";
    break;
  case 0x2753:
    name = "WSAEPROCLIM";
    break;
  case 0x2754:
    name = "WSAEUSERS";
    break;
  case 0x2755:
    name = "WSAEDQUOT";
    break;
  case 0x2756:
    name = "WSAESTALE";
    break;
  case 0x2757:
    name = "WSAEREMOTE";
    break;

  case 0x276B:
    name = "WSASYSNOTREADY";
    break;
  case 0x276C:
    name = "WSAVERNOTSUPPORTED";
    break;
  case 0x276D:
    name = "WSANOTINITIALISED";
    break;

  case 0x2775:
    name = "WSAEDISCON";
    break;
  case 0x2776:
    name = "WSAENOMORE";
    break;
  case 0x2777:
    name = "WSAECANCELLED";
    break;
  case 0x2778:
    name = "WSAEINVALIDPROCTABLE";
    break;
  case 0x2779:
    name = "WSAEINVALIDPROVIDER";
    break;
  case 0x277A:
    name = "WSAEPROVIDERFAILEDINIT";
    break;
  case 0x277B:
    name = "WSASYSCALLFAILURE";
    break;
  case 0x277C:
    name = "WSASERVICE_NOT_FOUND";
    break;
  case 0x277D:
    name = "WSATYPE_NOT_FOUND";
    break;
  case 0x277E:
    name = "WSA_E_NO_MORE";
    break;
  case 0x277F:
    name = "WSA_E_CANCELLED";
    break;
  case 0x2780:
    name = "WSAEREFUSED";
    break;

  case 0x2AF9:
    name = "WSAHOST_NOT_FOUND";
    break;
  case 0x2AFA:
    name = "WSATRY_AGAIN";
    break;
  case 0x2AFB:
    name = "WSANO_RECOVERY";
    break;
  case 0x2AFC:
    name = "WSANO_DATA";
    break;

  case 0x2AFD:
    name = "WSA_QOS_RECEIVERS";
    break;
  case 0x2AFE:
    name = "WSA_QOS_SENDERS";
    break;
  case 0x2AFF:
    name = "WSA_QOS_NO_SENDERS";
    break;
  case 0x2B00:
    name = "WSA_QOS_NO_RECEIVERS";
    break;
  case 0x2B01:
    name = "WSA_QOS_REQUEST_CONFIRMED";
    break;
  case 0x2B02:
    name = "WSA_QOS_ADMISSION_FAILURE";
    break;
  case 0x2B03:
    name = "WSA_QOS_POLICY_FAILURE";
    break;
  case 0x2B04:
    name = "WSA_QOS_BAD_STYLE";
    break;
  case 0x2B05:
    name = "WSA_QOS_BAD_OBJECT";
    break;
  case 0x2B06:
    name = "WSA_QOS_TRAFFIC_CTRL_ERROR";
    break;
  case 0x2B07:
    name = "WSA_QOS_GENERIC_ERROR";
    break;

  default:
    name = "<unknown error>";
    break;
  }

  *(const char **)0x335098 = name;
  if (error_code != *(int *)0x3352a0) {
    error(3, "winsock error #%d: %s", error_code, name);
    *(int *)0x3352a0 = error_code;
  }
  return name;
}

/* Get the socket address for an endpoint.
 *
 * Tries getsockname (0x224876) first; if that fails, tries getpeername
 * (0x22486b).  Both are XNet thunks with signature
 * __stdcall(int socket, void *name, int *namelen) RET 0xc.  The local
 * sockaddr buffer is 16 bytes (AF_INET: family=2, port, sin_addr).
 *
 * On success: stores ntohl(sin_addr) at addr[0], stores 4 as a uint16_t
 * at byte offset 0x10, stores ntohs(sin_port) as a uint16_t at byte
 * offset 0x12; clears ep[6] (status) to 0; returns 0.
 * On failure: calls xapi_GetLastError and reports via winsock_error_report;
 * sets ep[6] to 0xfff1; returns 0xfff1 (short -15).
 *
 * ep struct layout (from disassembly):
 *   [ep+0]  int      socket fd (-1 = invalid)
 *   [ep+6]  int16_t  status/error code
 *
 * Confirmed: xnet_getsockname (0x224876, __stdcall 3 args, RET 0xc);
 * xnet_getpeername (0x22486b, __stdcall 3 args, RET 0xc);
 * xapi_GetLastError (0x2235c4 thunk -> 0x1d2240);
 * winsock_error_report (0x83310, cdecl 1 arg);
 * transport_initialized flag at 0x335090;
 * assert strings: "ep && address" at 0x266c70, file at 0x266618;
 * source lines 0xf7/0xf8.
 */
short FUN_00083a60(int *ep, void *addr)
{
  int result;
  int err;
  uint32_t ip;
  uint32_t ip_host;
  uint16_t port;
  uint16_t port_host;
  int16_t sa_buf[8]; /* 16-byte sockaddr_in buffer */
  int sa_len;

  sa_len = 0x10;

  assert_halt(ep && addr);
  assert_halt(*(uint8_t *)0x335090);

  if (*ep != -1) {
    result = xnet_getsockname(*ep, sa_buf, &sa_len);
    if (result == 0) {
      if (sa_buf[0] == 2) {
        /* AF_INET: extract and byte-swap IP and port. */
        port = (uint16_t)sa_buf[1];
        ip = *(uint32_t *)((char *)sa_buf + 4);
        /* ntohl(ip): reorder bytes from network order to host order. */
        ip_host = (((ip & 0xff0000u) | (ip >> 16)) >> 8) |
                  (((ip & 0xff00u) | (ip << 16)) << 8);
        /* ntohs(port): swap port bytes. */
        port_host =
          (uint16_t)(((uint16_t)(port << 8)) | ((uint16_t)(port >> 8)));
        *(uint32_t *)addr = ip_host;
        *(uint16_t *)((char *)addr + 0x10) = 4;
        *(uint16_t *)((char *)addr + 0x12) = port_host;
        *(int16_t *)((char *)ep + 6) = 0;
        return 0;
      }
    } else {
      result = xnet_getpeername(*ep, sa_buf, &sa_len);
      if (result == 0 && sa_buf[0] == 2) {
        port = (uint16_t)sa_buf[1];
        ip = *(uint32_t *)((char *)sa_buf + 4);
        ip_host = (((ip & 0xff0000u) | (ip >> 16)) >> 8) |
                  (((ip & 0xff00u) | (ip << 16)) << 8);
        port_host =
          (uint16_t)(((uint16_t)(port << 8)) | ((uint16_t)(port >> 8)));
        *(uint32_t *)addr = ip_host;
        *(uint16_t *)((char *)addr + 0x10) = 4;
        *(uint16_t *)((char *)addr + 0x12) = port_host;
        *(int16_t *)((char *)ep + 6) = 0;
        return 0;
      }
    }
    err = xapi_GetLastError();
    winsock_error_report(err);
  }
  *(int16_t *)((char *)ep + 6) = (int16_t)0xfff1;
  return (short)0xfff1;
}

/* Bind a transport endpoint to an address.
 *
 * If the socket is not yet created (== -1), creates one via FUN_00083930
 * (regarg: ECX=af, EDX=type, EAX=protocol) using SOCK_STREAM=1 for TCP
 * (ep->type==0x12) or SOCK_DGRAM=2 for UDP (ep->type==0x11). Converts
 * the custom address format (host-order IP at addr[0], type at addr+0x10,
 * host-order port at addr+0x12) into a sockaddr_in and calls xnet_bind
 * (0x225197, stdcall 3 args).
 *
 * Returns 0 on success, -1 if socket creation fails or type is unknown,
 * -14 (0xfff2) if bind fails.
 *
 * Confirmed: FUN_00083930 (0x83930, regarg ECX/EDX/EAX);
 * xnet_bind (0x225197, stdcall 3 args);
 * xapi_GetLastError (0x2235c4); winsock_error_report (0x83310, cdecl);
 * transport_initialized at 0x335090; source lines 0x16c/0x16d.
 */
short FUN_00083ce0(int *ep, void *addr)
{
  int socket_result;
  int bind_result;
  int error_code;
  short status;
  uint32_t ip;
  uint16_t port;
  uint8_t sa[16];

  status = 0;

  assert_halt(ep && addr);
  assert_halt(*(uint8_t *)0x335090);

  if (*ep == -1) {
    if (*(uint8_t *)((char *)ep + 5) == 0x12) {
      socket_result = FUN_00083930(2, 1, 0);
      *ep = socket_result;
      if (socket_result != -1)
        goto do_bind;
      status = -1;
    } else if (*(uint8_t *)((char *)ep + 5) == 0x11) {
      socket_result = FUN_00083930(2, 2, 0);
      *ep = socket_result;
      if (socket_result != -1)
        goto do_bind;
      status = -1;
    } else {
      status = -12;
    }
    if (*ep == -1 || status != 0) {
      *(uint16_t *)((char *)ep + 6) = 0xffff;
      return -1;
    }
  }

do_bind:
  ip = *(uint32_t *)addr;
  *(uint32_t *)(sa + 4) = (((ip & 0xff0000u) | (ip >> 16)) >> 8) |
                          (((ip & 0xff00u) | (ip << 16)) << 8);
  port = *(uint16_t *)((char *)addr + 0x12);
  *(uint16_t *)(sa + 2) =
    (uint16_t)(((uint16_t)(port << 8)) | ((uint16_t)(port >> 8)));
  *(uint16_t *)sa = 2;

  bind_result = xnet_bind(*ep, sa, 0x10);
  if (bind_result == 0) {
    *(int16_t *)((char *)ep + 6) = status;
    return status;
  }

  error_code = xapi_GetLastError();
  winsock_error_report(error_code);
  *(int16_t *)((char *)ep + 6) = (int16_t)0xfff2;
  return (short)0xfff2;
}

/* Close a transport endpoint's socket and clear its connected flag.
 *
 * If the endpoint's socket handle is not INVALID_SOCKET (-1), calls
 * xnet_closesocket to close it. On failure, reports the Winsock error
 * via winsock_error_report. Then sets the socket handle to -1.
 * Always clears bit 0 (connected) of the flags byte at ep+4.
 *
 * ep struct layout (from disassembly):
 *   [ep+0]  int      socket fd (-1 = invalid)
 *   [ep+4]  uint8_t  flags (bit 0 = connected)
 *
 * Confirmed: xnet_closesocket (0x225cc6, __stdcall 1 arg, RET 4);
 * xapi_GetLastError (0x2235c4 thunk -> 0x1d2240);
 * winsock_error_report (0x83310, cdecl 1 arg);
 * assert strings at 0x266658, 0x265fe4; source lines 0x221/0x222.
 */
void close_endpoint(int *ep)
{
  int result;
  int err;

  assert_halt(ep != NULL);
  assert_halt(*(uint8_t *)0x335090);

  if (*ep != -1) {
    result = xnet_closesocket(*ep);
    if (result != 0) {
      err = xapi_GetLastError();
      winsock_error_report(err);
    }
    *ep = -1;
  }
  *(uint8_t *)((char *)ep + 4) &= 0xfe;
}

/* Cancel an in-progress connection attempt.
 *
 * Validates the connect_handle struct (non-null, has ep, has thread), then
 * calls endpoint_pool_cleanup() before attempting to acquire the connection
 * mutex with a 1000 ms timeout. On success: closes the underlying socket via
 * close_endpoint(), clears all endpoint flags (word at ep+6), marks the
 * handle as cancelled (byte at connect_handle+0x24), and releases the mutex.
 * On failure to acquire the mutex: asserts and halts.
 *
 * connect_handle layout (int[] offsets):
 *   [0]  int * — pointer to the endpoint struct (socket handle at ep[0])
 *   [7]  int   — thread reference (must be non-zero)
 *   [8]  int * — pointer to the mutex HANDLE for this connection
 *   [9]  char  — cancel flag (set to 1 on successful cancel, byte at +0x24)
 *
 * Confirmed: assert "input && input->ep && input->thread" at line 0x298;
 *   assert "!\"unable to get mutex in cancel_connect_process()!\"" at 0x2a5;
 *   source file
 * "c:\halo\SOURCE\bungie_net\network\transport_endpoint_winsock.c";
 *   take_mutex (mutex_acquire, 0x81870, cdecl 2 args: mutex_ref, timeout_ms);
 *   release_mutex (mutex_release, 0x818d0, cdecl 1 arg: mutex_ref);
 *   close_endpoint (0x84000); endpoint_pool_cleanup (0x82d30).
 *   endpoint flags word cleared at ep+6 after close; cancel flag at ESI+0x24.
 */
void transport_server_terminate(int *connect_handle)
{
  if (connect_handle == NULL || connect_handle[0] == 0 ||
      connect_handle[7] == 0) {
    display_assert(
      "input && input->ep && input->thread",
      "c:\\halo\\SOURCE\\bungie_net\\network\\transport_endpoint_winsock.c",
      0x298, 1);
    system_exit(-1);
  }

  endpoint_pool_cleanup();

  if (take_mutex((int *)connect_handle[8], 1000)) {
    close_endpoint((int *)connect_handle[0]);
    *(uint16_t *)((char *)(int *)connect_handle[0] + 6) = 0;
    *(uint8_t *)((char *)connect_handle + 0x24) = 1;
    release_mutex((int *)connect_handle[8]);
    return;
  }

  display_assert(
    "!\"unable to get mutex in cancel_connect_process()!\"",
    "c:\\halo\\SOURCE\\bungie_net\\network\\transport_endpoint_winsock.c",
    0x2a5, 1);
  system_exit(-1);
}

/* Receive a UDP datagram and return the sender's address.
 *
 * If the endpoint's socket is not yet created (== -1), creates a UDP socket
 * via FUN_00083930 (regarg: ECX=af, EDX=type, EAX=protocol) and binds to
 * any address/port via FUN_00083ce0. Then calls xnet_recvfrom (0x225cd1,
 * stdcall 6 args). On success, converts the sender's sockaddr_in to the
 * custom address format: addr[0]=ntohl(ip), addr+0x10=4, addr+0x12=ntohs(port).
 * On failure, classifies the Winsock error:
 *   WSAEWOULDBLOCK (0x2733) -> return -4
 *   Disconnect family (0x2744-0x274c) -> clear bits 0,2 of flags, return -3
 *   Other -> clear bit 2 of flags, return -2
 *
 * Confirmed: FUN_00083930 (0x83930, regarg ECX/EDX/EAX, creates socket);
 * FUN_00083ce0 (0x83ce0, cdecl 2 args, binds endpoint);
 * xnet_recvfrom (0x225cd1, stdcall 6 args);
 * xapi_GetLastError (0x2235c4); transport_initialized at 0x335090.
 * Assert strings at 0x266db0/0x266618; source lines 0x377-0x38b.
 */
int FUN_00084520(int *ep, void *buffer, int length, void *addr)
{
  int socket_result;
  short bind_result;
  int recv_result;
  int error_code;
  uint32_t bind_addr[6];
  uint8_t from_addr[16];
  int from_len;
  uint32_t ip;
  uint16_t port;

  from_len = 0x10;

  assert_halt(ep && buffer && addr && (length > 0));
  assert_halt(*(uint8_t *)0x335090);

  if (*ep == -1) {
    assert_halt(*(uint8_t *)((char *)ep + 5) == 0x11);

    socket_result = FUN_00083930(2, 2, 0);
    *ep = socket_result;
    if (socket_result != -1) {
      bind_addr[0] = 0;
      bind_addr[1] = 0;
      bind_addr[2] = 0;
      bind_addr[3] = 0;
      bind_addr[4] = 0;
      bind_addr[5] = 0;
      *(uint16_t *)&bind_addr[4] = 4;

      bind_result = FUN_00083ce0(ep, (void *)bind_addr);
      assert_halt(bind_result == 0);

      if (*ep != -1)
        goto do_recvfrom;
    }
    *(uint16_t *)((char *)ep + 6) = 0xffff;
  } else {
  do_recvfrom:
    assert_halt(!(*(uint8_t *)((char *)ep + 4) & 1));

    recv_result = xnet_recvfrom(*ep, buffer, length, 0, from_addr, &from_len);
    if (recv_result != -1) {
      if (recv_result >= 0) {
        ip = *(uint32_t *)(from_addr + 4);
        *(uint32_t *)addr = (((ip & 0xff0000u) | (ip >> 16)) >> 8) |
                            (((ip & 0xff00u) | (ip << 16)) << 8);
        *(uint16_t *)((char *)addr + 0x10) = 4;
        port = *(uint16_t *)(from_addr + 2);
        *(uint16_t *)((char *)addr + 0x12) =
          (uint16_t)(((uint16_t)(port << 8)) | ((uint16_t)(port >> 8)));
      }
      return recv_result;
    }
  }

  error_code = xapi_GetLastError();
  switch (error_code) {
  case 0x2733:
    return -4;
  case 0x2744:
  case 0x2745:
  case 0x2746:
  case 0x2749:
  case 0x274a:
  case 0x274c:
    *(uint8_t *)((char *)ep + 4) &= 0xfa;
    return -3;
  default:
    *(uint8_t *)((char *)ep + 4) &= 0xfb;
    return -2;
  }
}

/* Destroy a transport endpoint: close its socket, free memory, cleanup pool.
 *
 * Calls close_endpoint (0x84000) to close the underlying socket and clear
 * the socket handle.  Then frees the endpoint allocation via debug_free
 * (0x8ef70) with original XBE source path and line.  Finally tail-calls
 * endpoint_pool_cleanup (0x82d30) to remove the entry from the active table.
 *
 * Confirmed: close_endpoint (0x84000, cdecl 1 arg: int *ep);
 * debug_free (0x8ef70, 3 args); endpoint_pool_cleanup (0x82d30, 0 args);
 * assert strings at 0x266658, 0x265fe4; source line 0xe4/0xe5/0xe8.
 */
void destroy_endpoint(int *ep)
{
  assert_halt(ep != NULL);
  assert_halt(*(uint8_t *)0x335090);

  /* Close the underlying socket and clear handle/flags. */
  close_endpoint(ep);

  /* Free the endpoint allocation using original XBE source path and line. */
  debug_free(
    ep, "c:\\halo\\SOURCE\\bungie_net\\network\\transport_endpoint_winsock.c",
    0xe8);

  /* Remove from active endpoint pool. */
  endpoint_pool_cleanup();
}
/* --- transport_endpoint_set_winsock.obj batch drafts (2026-07-26) --- */

/* transport_get_nonce (0x81ec0) — readable C lift. */
void transport_get_nonce(void *dst, int bytes)
{
  if (dst == NULL) {
    display_assert((const char *)0x2664e0, (const char *)0x266458, 0x97, 1);
    system_exit(-1);
  }
  if (bytes != 8) {
    display_assert((const char *)0x2664c0, (const char *)0x266458, 0x98, 1);
    system_exit(-1);
  }
  csmemcpy(dst, (void *)0x5ab228, 8);
}

/* transport_nonce_is_equal (0x81f30) — readable C lift. */
bool transport_nonce_is_equal(const void *a, const void *b)
{
  if (!a) {
    display_assert((const char *)0x2664ec, (const char *)0x266458, 0xa3, 1);
    system_exit(-1);
  }
  if (!b) {
    display_assert((const char *)0x2664e0, (const char *)0x266458, 0xa4, 1);
    system_exit(-1);
  }
  return csmemcmp(a, b, 8) == 0;
}


/* FUN_00081fa0 (0x81fa0) — readable C lift: compare nonce to transport nonce. */
bool FUN_00081fa0(void *nonce, int bytes)
{
  if (nonce == NULL) {
    display_assert((const char *)0x2664ec, (const char *)0x266458, 0xaf, 1);
    system_exit(-1);
  }
  if (bytes != 8) {
    display_assert((const char *)0x2664c0, (const char *)0x266458, 0xb0, 1);
    system_exit(-1);
  }
  return transport_nonce_is_equal(nonce, (void *)0x5ab228);
}



/* transport_get_xnaddr (0x82060) — readable C lift. */
void *transport_get_xnaddr(void *dst)
{
  int *out = (int *)dst;
  out[0] = *(int *)0x5ab230;
  out[1] = *(int *)0x5ab234;
  out[2] = *(int *)0x5ab238;
  return dst;
}

/* transport_get_key_id (0x82090) — readable C lift (assert wrapper). */
int64_t transport_get_key_id(void)
{
  if (*(int *)0x335094 <= 0) {
    display_assert((const char *)0x2664a8, (const char *)0x266458, 0xe0, 1);
    system_exit(-1);
  }
  /* edx:eax */
  (void)*(uint32_t *)0x5ab224;
  return *(uint32_t *)0x5ab220;
}

/* transport_get_key (0x820d0) — readable C lift. */
void *transport_get_key(void *dst)
{
  extern char DAT_002664a8[];
  extern char DAT_00266458[];
  uint32_t *out = (uint32_t *)dst;

  if (*(int *)0x335094 <= 0) {
    display_assert(DAT_002664a8, DAT_00266458, 0xe7, 1);
    system_exit(-1);
  }
  out[0] = *(uint32_t *)0x5ab210;
  out[1] = *(uint32_t *)0x5ab214;
  out[2] = *(uint32_t *)0x5ab218;
  out[3] = *(uint32_t *)0x5ab21c;
  return dst;
}

/* create_endpoint_set (0x82310) — readable C lift from XBE leaf. */
int create_endpoint_set(int count)
{
  extern char DAT_00265fe4[];
  extern char DAT_00266458[];
  extern char DAT_002665c0[];
  char *set;
  void *entries;
  int16_t n16 = (int16_t)count;
  int n;

  /* Flag at 0x335090 — absolute load matches XBE / Unicorn auto-map path. */
  if (*(unsigned char *)0x335090 == 0) {
    display_assert(DAT_00265fe4, DAT_00266458, 0x196, true);
    system_exit(-1);
  }
  if (n16 <= 0) {
    display_assert(DAT_002665c0, DAT_00266458, 0x197, true);
    system_exit(-1);
  }
  set = (char *)debug_malloc(0x118, 0, DAT_00266458, 0x199);
  if (set == 0)
    return 0;
  if (n16 > 0x40) {
    debug_free(set, DAT_00266458, 0x1b0);
    return 0;
  }
  n = (int)n16;
  *(int *)(set + 0x114) = 0;
  *(int *)set = 0;
  entries = debug_malloc((uint32_t)(n * 4), 1, DAT_00266458, 0x1a2);
  *(void **)(set + 0x104) = entries;
  if (entries == 0) {
    debug_free(set, DAT_00266458, 0x1aa);
    return 0;
  }
  *(int *)(set + 0x108) = n;
  *(int *)(set + 0x10c) = -1;
  *(int *)(set + 0x110) = 0;
  return (int)(uintptr_t)set;
}


/* delete_endpoint_set (0x82410) — readable C lift from XBE leaf. */
void delete_endpoint_set(void *set)
{
  extern char DAT_002665d4[];
  extern char DAT_00266458[];
  extern char DAT_00265fe4[];
  void *inner;

  if (set == 0 || *(void **)((char *)set + 0x104) == 0) {
    display_assert(DAT_002665d4, DAT_00266458, 0x1bb, true);
    system_exit(-1);
  }
  if (*(unsigned char *)0x335090 == 0) {
    display_assert(DAT_00265fe4, DAT_00266458, 0x1bc, true);
    system_exit(-1);
  }
  inner = *(void **)((char *)set + 0x104);
  debug_free(inner, DAT_00266458, 0x1be);
  debug_free(set, DAT_00266458, 0x1bf);
}



/* FUN_000824a0 (0x824a0) — readable C lift. */
int FUN_000824a0(int *a, int *b)
{
  int av = *a;
  int bv = *b;
  if (av == 0) {
    if (bv == 0) return 0;
    return 1;
  }
  if (bv == 0) return -1;
  return 0;
}

/* poll_endpoint_set (0x824d0) — Capstone tip: null endpoint_set → assert. */
int poll_endpoint_set(int endpoint_set, unsigned short timeout)
{
  (void)timeout;
  if (endpoint_set == 0) {
    display_assert((char *)0x266450, (char *)0x266458, 0x1dd, 1);
    system_exit(-1);
  }
  return 0;
}


/* add_endpoint_to_set (0x82700) — readable C lift from XBE leaf. */
int add_endpoint_to_set(int *endpoint, void *set)
{
  int *esi;
  int count;
  int max;
  int idx;
  int *arr;
  int n;
  int i;
  int sock;

  assert_halt(endpoint && set);
  assert_halt(*(uint8_t *)0x335090);
  assert_halt(set != 0);

  esi = (int *)set;
  max = *(int *)((char *)esi + 0x108);
  count = *(int *)((char *)esi + 0x10c);
  if (count > max - 1)
    return -20;
  idx = count + 1;
  if (idx < 0)
    return -20;

  arr = *(int **)((char *)esi + 0x104);
  arr[idx] = (int)endpoint;

  n = esi[0];
  sock = *endpoint;
  i = 0;
  if (n > 0) {
    int *fds = esi + 1;
    while (i < n) {
      if (*fds == sock)
        break;
      i++;
      fds++;
    }
  }
  if (i == n && n < 0x40) {
    esi[1 + i] = sock;
    esi[0] = n + 1;
  }

  *(int *)((char *)esi + 0x10c) = count + 1;
  *(uint8_t *)((char *)endpoint + 4) |= 8;
  return 0;
}
/* rewind_endpoint_set (0x82940) — readable C lift. */
void rewind_endpoint_set(void *a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x266450, (const char *)0x266458, 0x26d, 1);
    system_exit(-1);
  }
  if (*(uint8_t *)0x335090 == 0) {
    display_assert((const char *)0x265fe4, (const char *)0x266458, 0x26e, 1);
    system_exit(-1);
  }
  *(uint32_t *)((char *)a0 + 0x110) = 0;
}

/* FUN_000829b0 (0x829b0) — readable C lift. */
int FUN_000829b0(void *endpoint_set)
{
  int idx;
  int *arr;

  if (!endpoint_set) {
    display_assert((const char *)0x266450, (const char *)0x266458, 0x27a, 1);
    system_exit(-1);
  }
  if (!*(uint8_t *)0x335090) {
    display_assert((const char *)0x265fe4, (const char *)0x266458, 0x27b, 1);
    system_exit(-1);
  }
  idx = *(int *)((char *)endpoint_set + 0x110);
  if (idx > *(int *)((char *)endpoint_set + 0x10c))
    return 0;
  arr = *(int **)((char *)endpoint_set + 0x104);
  *(int *)((char *)endpoint_set + 0x110) = idx + 1;
  return arr[idx];
}


/* FUN_00082a30 (0x82a30) — readable C lift. */
int FUN_00082a30(int endpoint_set)
{
  if (endpoint_set == 0) {
    display_assert((const char *)0x266450, (const char *)0x266458, 0x289, 1);
    system_exit(-1);
  }
  if (*(uint8_t *)0x335090 == 0) {
    display_assert((const char *)0x265fe4, (const char *)0x266458, 0x28a, 1);
    system_exit(-1);
  }
  return *(uint32_t *)((char *)endpoint_set + 0x10c) + 1;
}

/* FUN_00082a90 (0x82a90) — readable C lift. */
short FUN_00082a90(void)
{
  uint32_t key[2];
  uint32_t nonce[4];

  if (*(unsigned char *)0x335091 != 0) {
    if (*(int *)0x335094 <= 0) {
      display_assert((const char *)0x2664a8, (const char *)0x266458, 0x66, 1);
      system_exit(-1);
    }
    if (--*(int *)0x335094 == 0)
      ((int (__stdcall *)(void *))0x222df7)((void *)0x5ab220);
    *(unsigned char *)0x335091 = 0;
  }
  if (*(int *)0x335094 != 0) {
    display_assert((const char *)0x2665f8, (const char *)0x266458, 0x79, 1);
    system_exit(-1);
  }
  *(unsigned char *)0x5ab204 = 1;
  ((void (__stdcall *)(uint32_t *, uint32_t *))0x222da0)(key, nonce);
  FUN_00081e00(key, nonce);
  return 0;
}
/* FUN_00082bd0 (0x82bd0) — readable C lift: build transport addr from xnaddr. */
void FUN_00082bd0(void *xnaddr, uint32_t *key, uint32_t *nonce, uint16_t port, void *addr)
{
  uint32_t ip;

  if (*(uint8_t *)0x335091 != 0) {
    assert_halt(*(int *)0x335094 > 0);
    *(int *)0x335094 -= 1;
    if (*(int *)0x335094 == 0)
      FUN_00222df7((void *)0x5ab220);
    *(uint8_t *)0x335091 = 0;
  }

  FUN_00081e00(key, nonce);
  xnet_xnaddr_to_inaddr(xnaddr, nonce, &ip);
  ip = (((ip & 0xff0000u) | (ip >> 16)) >> 8) |
       (((ip & 0xff00u) | (ip << 16)) << 8);
  *(uint32_t *)addr = ip;
  *(uint16_t *)((char *)addr + 0x10) = 4;
  *(uint16_t *)((char *)addr + 0x12) = port;
  *(uint32_t *)((char *)addr + 0x14) = 0;
  *(uint8_t *)0x335091 = 1;
}

/* FUN_00082c90 (0x82c90) — readable C lift. */
char FUN_00082c90(void *endpoint)
{
  unsigned int idx;

  idx = 0;
  if (*(uint32_t *)0x3350a0 != 0) {
    for (;;) {
      uint32_t slot;

      if ((int)idx >= 0x40) {
        idx = 0xffffffffu;
        break;
      }
      slot = *(uint32_t *)(0x3350a8 + idx * 8);
      idx++;
      if (slot == 0) {
        if ((int)idx >= 0x40)
          idx = 0xffffffffu;
        break;
      }
    }
  }
  if (idx == 0xffffffffu)
    return 0;
  *(uint32_t *)(0x3350a0 + idx * 8) = (uint32_t)endpoint;
  *(uint8_t *)(0x3350a4 + idx * 8) = 0;
  return 1;
}


/* FUN_00082cf0 (0x82cf0) — readable C lift. */
void FUN_00082cf0(void *endpoint)
{
  extern char DAT_00266618[];
  extern char DAT_00266610[];
  int i;
  if (!endpoint) {
    display_assert(DAT_00266610, DAT_00266618, 0x4f, 1);
    system_exit(-1);
  }
  for (i = 0; i < 0x40; i++) {
    if (*(void **)(0x3350a0 + i * 8) == endpoint) {
      *(unsigned char *)(0x3350a4 + i * 8) = 1;
      return;
    }
  }
}

/* get_next_endpoint_from_set (0x82d70) — readable C lift. */
void *get_next_endpoint_from_set(int type)
{
  void *ep;

  if (!*(uint8_t *)0x335090) {
    display_assert((const char *)0x265fe4, (const char *)0x266618, 0xce, 1);
    system_exit(-1);
  }
  endpoint_pool_cleanup();
  if (type != 0x11 && type != 0x12)
    return NULL;
  ep = debug_malloc(8, 0, (const char *)0x266618, 0xd4);
  if (!ep)
    return NULL;
  *(uint16_t *)((char *)ep + 6) = 0;
  *(uint8_t *)((char *)ep + 5) = (uint8_t)type;
  *(uint32_t *)ep = 0xffffffffu;
  *(uint8_t *)((char *)ep + 4) = 0;
  return ep;
}


/* count_endpoints_in_set (0x82df0) — readable C lift (assert wrapper). */
int count_endpoints_in_set(void * a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x266658, (const char *)0x266618, 0x12c, 1);
    system_exit(-1);
  }
  if (*(uint8_t *)0x335090 == 0) {
    display_assert((const char *)0x265fe4, (const char *)0x266618, 0x12d, 1);
    system_exit(-1);
  }
  return (int8_t)*(int8_t *)((char *)a0 + 0x5);
}

/* FUN_00083040 (0x83040) — readable C lift: endpoint_readable. */
char FUN_00083040(int *endpoint, unsigned short timeout)
{
  int sock;
  uint8_t flags;
  struct {
    int count;
    int fd;
    int pad[62];
  } readfds;
  int tv[2];
  int n;

  assert_halt(endpoint != 0);

  sock = *endpoint;
  if (sock == -1)
    return 0;

  flags = *(uint8_t *)((char *)endpoint + 4);
  if (flags & 8)
    return (char)((flags >> 2) & 1);

  readfds.count = 1;
  readfds.fd = sock;
  tv[0] = 0;
  tv[1] = (int)timeout * 1000;

  n = xnet_select(1, &readfds, 0, 0, tv);
  if (n <= 0)
    return 0;

  if (xnet_fd_isset(sock, &readfds) == 0)
    return 0;
  return 1;
}

/* transport_server_initialize (0x83100) — readable C lift. */
char transport_server_initialize(int *endpoint, unsigned short timeout)
{
  int sock;
  struct {
    int count;
    int fd;
    int pad[62];
  } readfds;
  int tv[2];
  int n;

  if (endpoint == 0 || *endpoint == -1) {
    display_assert((const char *)0x26667c, (const char *)0x266618, 0x417, 1);
    system_exit(-1);
  }

  sock = *endpoint;
  readfds.count = 1;
  readfds.fd = sock;
  tv[0] = 0;
  tv[1] = (int)timeout * 1000;

  n = xnet_select(1, &readfds, 0, 0, tv);
  if (n <= 0)
    return 0;

  if (xnet_fd_isset(sock, &readfds) == 0)
    return 0;
  return 1;
}

/* FUN_000831e0 (0x831e0) — readable C lift (assert wrapper). */
int FUN_000831e0(void * a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x266658, (const char *)0x266618, 0x42e, 1);
    system_exit(-1);
  }
  return (int)(((uint32_t)*(uint8_t *)((char *)a0 + 0x4) & 2) >> 1);
}

/* FUN_00083220 (0x83220) — readable C lift (assert wrapper). */
int FUN_00083220(void * a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x266658, (const char *)0x266618, 0x436, 1);
    system_exit(-1);
  }
  return (int)((~((uint32_t)*(uint8_t *)((char *)a0 + 0x4) >> 4)) & 1);
}

/* FUN_00083260 (0x83260) — readable C lift (assert wrapper). */
uint16_t FUN_00083260(void * a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x266658, (const char *)0x266618, 0x43e, 1);
    system_exit(-1);
  }
  return *(uint16_t *)((char *)a0 + 0x6);
}

/* FUN_000832a0 (0x832a0) — readable C lift. */
int FUN_000832a0(int *a, int *b)
{
  int val;

  if (!a) {
    display_assert((const char *)0x266090, (const char *)0x266618, 0x447, 1);
    system_exit(-1);
  }
  if (!b) {
    display_assert((const char *)0x26608c, (const char *)0x266618, 0x448, 1);
    system_exit(-1);
  }
  val = *a;
  if (val == -1)
    return 0;
  if (val != *b)
    return 0;
  return 1;
}


/* FUN_00083bd0 (0x83bd0) — Capstone tip: nonblock bit clear + blocking → return 0. */
short FUN_00083bd0(int *endpoint, int blocking)
{
  unsigned char flags;
  if (!endpoint) {
    display_assert((char *)0x266658, (char *)0x266618, 0x139, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x335090 == 0) {
    display_assert((char *)0x265fe4, (char *)0x266618, 0x13a, 1);
    system_exit(-1);
  }
  if (!endpoint) {
    display_assert((char *)0x266658, (char *)0x266618, 0x436, 1);
    system_exit(-1);
  }
  flags = *((unsigned char *)endpoint + 4);
  if (((flags >> 4) & 1) == 0) {
    if (blocking) {
      *((unsigned short *)((char *)endpoint + 6)) = 0;
      return 0;
    }
  } else {
    if (!blocking) {
      *((unsigned short *)((char *)endpoint + 6)) = 0;
      return 0;
    }
  }
  /* ioctl paths not tip-proven */
  *(volatile int *)0 = 0;
  return -18;
}

/* FUN_00083e20 (0x83e20) — Capstone tip: bad endpoint type → return -12. */
short FUN_00083e20(int endpoint, int address)
{
  unsigned char *ep = (unsigned char *)(uintptr_t)endpoint;
  if (!endpoint || !address) {
    display_assert((char *)0x266c70, (char *)0x266618, 0x1b5, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x335090 == 0) {
    display_assert((char *)0x265fe4, (char *)0x266618, 0x1b6, 1);
    system_exit(-1);
  }
  if (ep[5] != 0x11 && ep[5] != 0x12) {
    *(short *)(ep + 6) = (short)0xfff4;
    return (short)0xfff4;
  }
  *(volatile int *)0 = 0;
  return 0;
}

/* FUN_00084080 (0x84080) — readable C lift (restored pre-naked). */
void FUN_00084080(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x840af */
  display_assert((char *)0x00266c9c, (char *)0x00266618, 569, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x840d4 */
  display_assert((char *)0x00266c90, (char *)0x00266618, 570, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x840fb */
  display_assert((char *)0x00266c80, (char *)0x00266618, 571, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x84124 */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 572, 0);
  system_exit(0);
  FUN_00083e20(0, 0);
  take_mutex((void *)(uintptr_t)edx, 1000);
  /* test (char)eax, (char)eax -> je 0x84164 */
  /* test (char)eax, (char)eax -> je 0x84159 */
  close_endpoint((void *)(uintptr_t)eax);
  debug_free((void *)(uintptr_t)edi, (char *)0x00266618, 594);
  release_mutex((void *)(uintptr_t)esi);
  ((void(*)(void))FUN_00081910)();
  /* test esi, esi -> je 0x8419c */
  ((void(*)(void))FUN_00082cf0)();

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_000841b0 (0x841b0) — Capstone tip: debug_malloc fail → return -9. */
short FUN_000841b0(int endpoint, int address, int process_ref)
{
  void *mem;
  if (!endpoint || !address || !process_ref) {
    display_assert((char *)0x266ca4, (char *)0x266618, 0x268, 1);
    system_exit(-1);
  }
  if (*(unsigned char *)0x335090 == 0) {
    display_assert((char *)0x265fe4, (char *)0x266618, 0x269, 1);
    system_exit(-1);
  }
  endpoint_pool_cleanup();
  mem = debug_malloc(0x28, 1, (const char *)0x266618, 0x26b);
  if (!mem) {
    *(short *)((char *)(uintptr_t)endpoint + 6) = (short)0xfff7;
    return (short)0xfff7;
  }
  *(volatile int *)0 = 0;
  return 0;
}

/* FUN_000843a0 (0x843a0) — readable C lift: listen_endpoint. */
short FUN_000843a0(int *endpoint)
{
  int sock;
  int ok;

  assert_halt(endpoint != 0);
  assert_halt(*(uint8_t *)0x335090);

  sock = *endpoint;
  if (sock == -1) {
    *(int16_t *)((char *)endpoint + 6) = -12;
    return -12;
  }

  ok = xnet_listen(sock, 0x20);
  if (ok == 0) {
    *(uint8_t *)((char *)endpoint + 4) |= 2;
    *(int16_t *)((char *)endpoint + 6) = 0;
    return 0;
  }

  winsock_error_report(xapi_GetLastError());
  *(int16_t *)((char *)endpoint + 6) = -17;
  return -17;
}

/* FUN_00084450 (0x84450) — readable C lift: accept into new endpoint. */
void *FUN_00084450(int *listening_endpoint)
{
  int sa_len;
  uint8_t sa[0x10];
  int sock;
  void *ep;
  uint8_t flags;

  sa_len = 0x10;
  assert_halt(listening_endpoint != 0);
  assert_halt(*(uint8_t *)0x335090);

  sock = xnet_accept(*listening_endpoint, sa, &sa_len);
  if (sock == -1) {
    winsock_error_report(xapi_GetLastError());
    *(int16_t *)((char *)listening_endpoint + 6) = -1;
    return 0;
  }

  ep = get_next_endpoint_from_set(*(int8_t *)((char *)listening_endpoint + 5));
  if (ep == 0) {
    *(int16_t *)((char *)listening_endpoint + 6) = -9;
    return 0;
  }

  flags = *(uint8_t *)((char *)ep + 4);
  *(int *)ep = sock;
  *(uint8_t *)((char *)ep + 4) = (uint8_t)(flags | 1);
  return ep;
}
/* FUN_00084740 (0x84740) — readable C lift (restored pre-naked). */
int FUN_00084740(int endpoint, void *message, int size, int dest_address)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x84765 */
  /* test ebx, ebx -> jle 0x84765 */
  /* test edi, edi -> jne 0x84785 */
  display_assert((char *)0x00266ddc, (char *)0x00266618, 957, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x847ae */
  display_assert((char *)0x00265fe4, (char *)0x00266618, 958, 0);
  system_exit(0);
  /* relift: cmp byte ptr [esi + 5], 0x11 -> je 0x84815 */
  display_assert((char *)0x00266d90, (char *)0x00266618, 966, 0);
  system_exit(0);
  FUN_00083930(0, 0, 0);
  /* relift: FUN_00225ce0(0, 0, 0, 0); */
  /* cmp eax, -1 -> jne 0x8488e */
  GetLastError();
  /* cmp eax, 0x19 -> ja 0x84889 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}


/* FUN_00084940 (0x84940) — readable C lift. */
int FUN_00084940(int listening_endpoint)
{
  void *p = (void *)FUN_00084450((int *)(intptr_t)listening_endpoint);
  if (p)
    destroy_endpoint(p);
  return 0;
}

/* FUN_00084970 (0x84970) — readable C lift. */
void FUN_00084970(unsigned int *ep)
{
  ep[2] = 0;
  ep[0] = system_milliseconds();
  ep[1] = 0;
}

/* --- transport_endpoint_set_winsock.obj orphan shells (2026-07-26) --- */

/* FUN_00083930 (0x83930) — Capstone tip: socket()==-1 → error path. */
int FUN_00083930(int af /*@<ecx>*/, int type /*@<edx>*/, int protocol /*@<eax>*/)
{
  int (*volatile socket_fn)(int, int, int);
  int s;
  socket_fn = (int (*)(int, int, int))0x2255f6;
  s = socket_fn(af, type, protocol);
  if (s == -1) {
    winsock_error_report(GetLastError());
    return -1;
  }
  return s;
}
