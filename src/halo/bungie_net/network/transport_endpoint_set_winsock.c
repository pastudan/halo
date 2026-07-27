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

/* create_endpoint_set (0x82310) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b82310_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b82310_exitfn)(int) = system_exit;
static void * (*const b82310_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b82310_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
int create_endpoint_set(int count __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcreate_endpoint_set_1\n\t"
      "pushl $1\n\t"
      "pushl $0x196\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcreate_endpoint_set_1:\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movw 0x8(%%ebp), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jg .Lcreate_endpoint_set_2\n\t"
      "pushl $1\n\t"
      "pushl $0x197\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x2665c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcreate_endpoint_set_2:\n\t"
      "pushl $0x199\n\t"
      "pushl $0x266458\n\t"
      "pushl $0\n\t"
      "pushl $0x118\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lcreate_endpoint_set_3\n\t"
      "cmpw $0x40, %%di\n\t"
      "jg .Lcreate_endpoint_set_5\n\t"
      "pushl $0x1a2\n\t"
      "movswl %%di, %%edi\n\t"
      "pushl $0x266458\n\t"
      "leal (,%%edi,4), %%eax\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "movl $0, 0x114(%%esi)\n\t"
      "movl $0, (%%esi)\n\t"
      "call *%[c8ee60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, 0x104(%%esi)\n\t"
      "je .Lcreate_endpoint_set_4\n\t"
      "movl %%edi, 0x108(%%esi)\n\t"
      "movl $0xffffffff, 0x10c(%%esi)\n\t"
      "movl $0, 0x110(%%esi)\n\t"
      ".Lcreate_endpoint_set_3:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcreate_endpoint_set_4:\n\t"
      "pushl $0x1aa\n\t"
      "jmp .Lcreate_endpoint_set_6\n\t"
      ".Lcreate_endpoint_set_5:\n\t"
      "pushl $0x1b0\n\t"
      ".Lcreate_endpoint_set_6:\n\t"
      "pushl $0x266458\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b82310_assert), [exitfn] "m"(b82310_exitfn), [c8ee60] "m"(b82310_c8ee60), [c8ef70] "m"(b82310_c8ef70)
      : "memory");
}
#else
#error "create_endpoint_set: clang naked draft required"
#endif


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

/* poll_endpoint_set (0x824d0) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b824d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b824d0_exitfn)(int) = system_exit;
static void __cdecl (*const b824d0_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = (void *)qsort;
static void * (*const b824d0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void b824d0_c2251b8_tgt(void) { return; }
static void (*const b824d0_c2251b8)(void) = b824d0_c2251b8_tgt;
static void b824d0_c2235f3_tgt(void) { return; }
static void (*const b824d0_c2235f3)(void) = b824d0_c2235f3_tgt;
static void (*const b824d0_c2235c4)(void) = GetLastError;
static const char * (*const b824d0_c83310)(int error_code) = winsock_error_report;

__attribute__((naked, noinline))
int poll_endpoint_set(int endpoint_set __attribute__((unused)), unsigned short timeout __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lpoll_endpoint_set_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1dd\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x266450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpoll_endpoint_set_1:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lpoll_endpoint_set_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1de\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lpoll_endpoint_set_2:\n\t"
      "movzwl 0xc(%%ebp), %%eax\n\t"
      "imull $0x3e8, %%eax, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x114(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "je .Lpoll_endpoint_set_10\n\t"
      "movl 0x10c(%%esi), %%ecx\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "pushl $0x824a0\n\t"
      "pushl $4\n\t"
      "incl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d9260]\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "movl 0x104(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%eax,4), %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edx, %%edx\n\t"
      "jne .Lpoll_endpoint_set_4\n\t"
      ".Lpoll_endpoint_set_3:\n\t"
      "movl 0x10c(%%esi), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0x10c(%%esi)\n\t"
      "movl 0x104(%%esi), %%eax\n\t"
      "cmpl $0, (%%eax,%%edx,4)\n\t"
      "je .Lpoll_endpoint_set_3\n\t"
      ".Lpoll_endpoint_set_4:\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0, (%%esi)\n\t"
      "jl .Lpoll_endpoint_set_9\n\t"
      "pushl %%ebx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lpoll_endpoint_set_5:\n\t"
      "movl (%%esi), %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .Lpoll_endpoint_set_7\n\t"
      "movl 0x104(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%edi,4), %%edx\n\t"
      "movl (%%edx), %%edx\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      ".Lpoll_endpoint_set_6:\n\t"
      "cmpl %%edx, (%%ecx)\n\t"
      "je .Lpoll_endpoint_set_7\n\t"
      "incl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "jb .Lpoll_endpoint_set_6\n\t"
      ".Lpoll_endpoint_set_7:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Lpoll_endpoint_set_8\n\t"
      "cmpl $0x40, %%ebx\n\t"
      "jae .Lpoll_endpoint_set_8\n\t"
      "movl 0x104(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%edi,4), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi,%%eax,4)\n\t"
      "incl (%%esi)\n\t"
      ".Lpoll_endpoint_set_8:\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl (%%edx,%%edi,4), %%eax\n\t"
      "andb $0xfb, 0x4(%%eax)\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jle .Lpoll_endpoint_set_5\n\t"
      "popl %%ebx\n\t"
      ".Lpoll_endpoint_set_9:\n\t"
      "movl $0, 0x114(%%esi)\n\t"
      "jmp .Lpoll_endpoint_set_12\n\t"
      ".Lpoll_endpoint_set_10:\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lpoll_endpoint_set_12\n\t"
      "jmp .Lpoll_endpoint_set_11\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lpoll_endpoint_set_11:\n\t"
      "movl 0x104(%%esi), %%eax\n\t"
      "movl (%%eax,%%edi,4), %%eax\n\t"
      "andb $0xfb, 0x4(%%eax)\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jle .Lpoll_endpoint_set_11\n\t"
      ".Lpoll_endpoint_set_12:\n\t"
      "pushl $0x104\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movl 0x10c(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "incl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2251b8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lpoll_endpoint_set_17\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lpoll_endpoint_set_15\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lpoll_endpoint_set_13:\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl (%%edx,%%edi,4), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lpoll_endpoint_set_16\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2235f3]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lpoll_endpoint_set_14\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl (%%edx,%%edi,4), %%eax\n\t"
      "orb $4, 0x4(%%eax)\n\t"
      ".Lpoll_endpoint_set_14:\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "cmpl %%eax, %%edi\n\t"
      "jle .Lpoll_endpoint_set_13\n\t"
      ".Lpoll_endpoint_set_15:\n\t"
      "popl %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpoll_endpoint_set_16:\n\t"
      "popl %%edi\n\t"
      "movl $0xfffffff4, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpoll_endpoint_set_17:\n\t"
      "jl .Lpoll_endpoint_set_18\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lpoll_endpoint_set_19\n\t"
      ".Lpoll_endpoint_set_18:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffeb, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lpoll_endpoint_set_19:\n\t"
      "popl %%edi\n\t"
      "movl $0xfffffff3, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b824d0_assert), [exitfn] "m"(b824d0_exitfn), [c1d9260] "m"(b824d0_c1d9260), [c8e0b0] "m"(b824d0_c8e0b0), [c2251b8] "m"(b824d0_c2251b8), [c2235f3] "m"(b824d0_c2235f3), [c2235c4] "m"(b824d0_c2235c4), [c83310] "m"(b824d0_c83310)
      : "memory");
}
#else
#error "poll_endpoint_set: clang naked draft required"
#endif


/* add_endpoint_to_set (0x82700) — XBE naked draft (batch 248). */
#if defined(__clang__)
static void (*const b82700_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b82700_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
int add_endpoint_to_set(int endpoint __attribute__((unused)), void *set __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "je .Ladd_endpoint_to_set_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Ladd_endpoint_to_set_2\n\t"
      ".Ladd_endpoint_to_set_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x22f\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x2665ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ladd_endpoint_to_set_2:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Ladd_endpoint_to_set_3\n\t"
      "pushl $1\n\t"
      "pushl $0x230\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ladd_endpoint_to_set_3:\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Ladd_endpoint_to_set_4\n\t"
      "pushl $1\n\t"
      "pushl $0x39\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x266450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ladd_endpoint_to_set_4:\n\t"
      "movl 0x108(%%esi), %%ecx\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jg .Ladd_endpoint_to_set_12\n\t"
      "leal 0x1(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jl .Ladd_endpoint_to_set_12\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl %%ebx, (%%edx,%%edi,4)\n\t"
      "testb $2, 0x4(%%ebx)\n\t"
      "movl (%%esi), %%ebx\n\t"
      "je .Ladd_endpoint_to_set_7\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .Ladd_endpoint_to_set_6\n\t"
      "movl 0x104(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%edi,4), %%edx\n\t"
      "movl (%%edx), %%edx\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      ".Ladd_endpoint_to_set_5:\n\t"
      "cmpl %%edx, (%%ecx)\n\t"
      "je .Ladd_endpoint_to_set_6\n\t"
      "incl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "jb .Ladd_endpoint_to_set_5\n\t"
      ".Ladd_endpoint_to_set_6:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Ladd_endpoint_to_set_11\n\t"
      "cmpl $0x40, %%ebx\n\t"
      "jae .Ladd_endpoint_to_set_11\n\t"
      "movl 0x104(%%esi), %%ecx\n\t"
      "movl (%%ecx,%%edi,4), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi,%%eax,4)\n\t"
      "jmp .Ladd_endpoint_to_set_10\n\t"
      ".Ladd_endpoint_to_set_7:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jbe .Ladd_endpoint_to_set_9\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl (%%edx,%%edi,4), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "leal 0x4(%%esi), %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Ladd_endpoint_to_set_8:\n\t"
      "cmpl %%edx, (%%ecx)\n\t"
      "je .Ladd_endpoint_to_set_9\n\t"
      "incl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "cmpl (%%esi), %%eax\n\t"
      "jb .Ladd_endpoint_to_set_8\n\t"
      ".Ladd_endpoint_to_set_9:\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jne .Ladd_endpoint_to_set_11\n\t"
      "cmpl $0x40, %%ebx\n\t"
      "jae .Ladd_endpoint_to_set_11\n\t"
      "movl 0x104(%%esi), %%edx\n\t"
      "movl (%%edx,%%edi,4), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, 0x4(%%esi,%%eax,4)\n\t"
      ".Ladd_endpoint_to_set_10:\n\t"
      "incl (%%esi)\n\t"
      ".Ladd_endpoint_to_set_11:\n\t"
      "movl 0x10c(%%esi), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "movl %%edx, 0x10c(%%esi)\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "popl %%edi\n\t"
      "orb $8, %%cl\n\t"
      "popl %%esi\n\t"
      "movb %%cl, 0x4(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ladd_endpoint_to_set_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xffffffec, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b82700_assert), [exitfn] "m"(b82700_exitfn)
      : "memory");
}
#else
#error "add_endpoint_to_set: clang naked draft required"
#endif


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

/* FUN_00082a90 (0x82a90) — XBE naked draft (batch 260). */
#if defined(__clang__)
static void (*const b82a90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b82a90_exitfn)(int) = system_exit;
static int __stdcall (*const b82a90_c222df7)(void *key) = FUN_00222df7;
static void b82a90_c222da0_tgt(void) { return; }
static void (*const b82a90_c222da0)(void) = b82a90_c222da0_tgt;
static void (*const b82a90_c81e00)(uint32_t *, uint32_t *) = FUN_00081e00;

__attribute__((naked, noinline))
void FUN_00082a90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x18, %%esp\n\t"
      "movb 0x335091, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00082a90_3\n\t"
      "movl 0x335094, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00082a90_1\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x2664a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00082a90_1:\n\t"
      "decl 0x335094\n\t"
      "jne .LFUN_00082a90_2\n\t"
      "pushl $0x5ab220\n\t"
      "call *%[c222df7]\n\t"
      ".LFUN_00082a90_2:\n\t"
      "movb $0, 0x335091\n\t"
      ".LFUN_00082a90_3:\n\t"
      "movl 0x335094, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00082a90_4\n\t"
      "pushl $1\n\t"
      "pushl $0x79\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x2665f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00082a90_4:\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb $1, 0x5ab204\n\t"
      "call *%[c222da0]\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81e00]\n\t"
      "addl $8, %%esp\n\t"
      "xorw %%ax, %%ax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b82a90_assert), [exitfn] "m"(b82a90_exitfn), [c222df7] "m"(b82a90_c222df7), [c222da0] "m"(b82a90_c222da0), [c81e00] "m"(b82a90_c81e00)
      : "memory");
}
#else
#error "FUN_00082a90: clang naked draft required"
#endif


/* FUN_00082bd0 (0x82bd0) — XBE naked draft (batch 257). */
#if defined(__clang__)
static void (*const b82bd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b82bd0_exitfn)(int) = system_exit;
static int __stdcall (*const b82bd0_c222df7)(void *key) = FUN_00222df7;
static void (*const b82bd0_c81e00)(uint32_t *, uint32_t *) = FUN_00081e00;
static void b82bd0_c222e31_tgt(void) { return; }
static void (*const b82bd0_c222e31)(void) = b82bd0_c222e31_tgt;

__attribute__((naked, noinline))
void FUN_00082bd0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movb 0x335091, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00082bd0_3\n\t"
      "movl 0x335094, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_00082bd0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x66\n\t"
      "pushl $0x266458\n\t"
      "pushl $0x2664a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00082bd0_1:\n\t"
      "decl 0x335094\n\t"
      "jne .LFUN_00082bd0_2\n\t"
      "pushl $0x5ab220\n\t"
      "call *%[c222df7]\n\t"
      ".LFUN_00082bd0_2:\n\t"
      "movb $0, 0x335091\n\t"
      ".LFUN_00082bd0_3:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c81e00]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c222e31]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x10, %%edx\n\t"
      "andl $0xff0000, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $0xff00, %%edx\n\t"
      "shll $0x10, %%eax\n\t"
      "orl %%eax, %%edx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "shrl $8, %%ecx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movw 0x14(%%ebp), %%cx\n\t"
      "movw $4, 0x10(%%eax)\n\t"
      "movw %%cx, 0x12(%%eax)\n\t"
      "movl $0, 0x14(%%eax)\n\t"
      "movb $1, 0x335091\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b82bd0_assert), [exitfn] "m"(b82bd0_exitfn), [c222df7] "m"(b82bd0_c222df7), [c81e00] "m"(b82bd0_c81e00), [c222e31] "m"(b82bd0_c222e31)
      : "memory");
}
#else
#error "FUN_00082bd0: clang naked draft required"
#endif


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

/* FUN_00083040 (0x83040) — XBE naked draft (batch 256). */
#if defined(__clang__)
static void (*const b83040_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b83040_exitfn)(int) = system_exit;
static void b83040_c2251b8_tgt(void) { return; }
static void (*const b83040_c2251b8)(void) = b83040_c2251b8_tgt;
static void b83040_c2235f3_tgt(void) { return; }
static void (*const b83040_c2235f3)(void) = b83040_c2235f3_tgt;

__attribute__((naked, noinline))
char FUN_00083040(int endpoint __attribute__((unused)), unsigned short timeout __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "jne .LFUN_00083040_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3f3\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266658\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083040_1:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "je .LFUN_00083040_4\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00083040_2\n\t"
      "shrl $2, %%eax\n\t"
      "popl %%esi\n\t"
      "andb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083040_2:\n\t"
      "movzwl 0xc(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x108(%%ebp)\n\t"
      "imull $0x3e8, %%eax, %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $1, -0x10c(%%ebp)\n\t"
      "call *%[c2251b8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00083040_3\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2235f3]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083040_3\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083040_3:\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083040_4:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b83040_assert), [exitfn] "m"(b83040_exitfn), [c2251b8] "m"(b83040_c2251b8), [c2235f3] "m"(b83040_c2235f3)
      : "memory");
}
#else
#error "FUN_00083040: clang naked draft required"
#endif


/* transport_server_initialize (0x83100) — XBE naked draft (batch 262). */
#if defined(__clang__)
static void (*const b83100_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b83100_exitfn)(int) = system_exit;
static void b83100_c2251b8_tgt(void) { return; }
static void (*const b83100_c2251b8)(void) = b83100_c2251b8_tgt;
static void b83100_c2235f3_tgt(void) { return; }
static void (*const b83100_c2235f3)(void) = b83100_c2235f3_tgt;

__attribute__((naked, noinline))
void transport_server_initialize(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Ltransport_server_initialize_1\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "jne .Ltransport_server_initialize_2\n\t"
      ".Ltransport_server_initialize_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x417\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x26667c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Ltransport_server_initialize_2:\n\t"
      "movzwl 0xc(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "imull $0x3e8, %%eax, %%eax\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x108(%%ebp)\n\t"
      "movl $1, -0x10c(%%ebp)\n\t"
      "call *%[c2251b8]\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Ltransport_server_initialize_3\n\t"
      "movl (%%esi), %%edx\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2235f3]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Ltransport_server_initialize_3\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ltransport_server_initialize_3:\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b83100_assert), [exitfn] "m"(b83100_exitfn), [c2251b8] "m"(b83100_c2251b8), [c2235f3] "m"(b83100_c2235f3)
      : "memory");
}
#else
#error "transport_server_initialize: clang naked draft required"
#endif


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


/* FUN_00083bd0 (0x83bd0) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b83bd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b83bd0_exitfn)(int) = system_exit;
static void b83bd0_c224633_tgt(void) { return; }
static void (*const b83bd0_c224633)(void) = b83bd0_c224633_tgt;
static void (*const b83bd0_c2235c4)(void) = GetLastError;
static const char * (*const b83bd0_c83310)(int error_code) = winsock_error_report;

__attribute__((naked, noinline))
short FUN_00083bd0(int endpoint __attribute__((unused)), int flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00083bd0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x139\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266658\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083bd0_1:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00083bd0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x13a\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083bd0_2:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00083bd0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x436\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266658\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083bd0_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x4(%%edi), %%al\n\t"
      "shrl $4, %%eax\n\t"
      "notb %%al\n\t"
      "testb $1, %%al\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "jne .LFUN_00083bd0_4\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083bd0_6\n\t"
      "movl (%%edi), %%edx\n\t"
      "leal 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x8004667e\n\t"
      "pushl %%edx\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "call *%[c224633]\n\t"
      "movl %%eax, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00083bd0_5\n\t"
      "andb $0xef, 0x4(%%edi)\n\t"
      "movw %%si, 0x6(%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083bd0_4:\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00083bd0_6\n\t"
      "movl (%%edi), %%ecx\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x8004667e\n\t"
      "pushl %%ecx\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      "call *%[c224633]\n\t"
      "movl %%eax, %%esi\n\t"
      "testw %%si, %%si\n\t"
      "jne .LFUN_00083bd0_5\n\t"
      "orb $0x10, 0x4(%%edi)\n\t"
      "movw %%si, 0x6(%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083bd0_5:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0xffffffee, %%esi\n\t"
      ".LFUN_00083bd0_6:\n\t"
      "movw %%si, 0x6(%%edi)\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b83bd0_assert), [exitfn] "m"(b83bd0_exitfn), [c224633] "m"(b83bd0_c224633), [c2235c4] "m"(b83bd0_c2235c4), [c83310] "m"(b83bd0_c83310)
      : "memory");
}
#else
#error "FUN_00083bd0: clang naked draft required"
#endif


/* FUN_00083e20 (0x83e20) — XBE naked draft (batch 246). */
#if defined(__clang__)
static void (*const b83e20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b83e20_exitfn)(int) = system_exit;
static int (*const b83e20_c83930)(int af, int type, int protocol) = FUN_00083930;
static short (*const b83e20_c83bd0)(int endpoint, int flag) = FUN_00083bd0;
static void b83e20_c2251a2_tgt(void) { return; }
static void (*const b83e20_c2251a2)(void) = b83e20_c2251a2_tgt;
static void (*const b83e20_c2235c4)(void) = GetLastError;
static unsigned int (*const b83e20_c8e370)(void) = system_milliseconds;
static void b83e20_c2251b8_tgt(void) { return; }
static void (*const b83e20_c2251b8)(void) = b83e20_c2251b8_tgt;
static const char * (*const b83e20_c83310)(int error_code) = winsock_error_report;
static int __stdcall (*const b83e20_c225cc6)(int socket) = xnet_closesocket;

__attribute__((naked, noinline))
short FUN_00083e20(int endpoint __attribute__((unused)), int address __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x11c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .LFUN_00083e20_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00083e20_2\n\t"
      ".LFUN_00083e20_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1b5\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266c70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083e20_2:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00083e20_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1b6\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00083e20_3:\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "cmpb $0x11, %%al\n\t"
      "jne .LFUN_00083e20_7\n\t"
      "movl $2, %%edx\n\t"
      ".LFUN_00083e20_4:\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "jne .LFUN_00083e20_5\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $2, %%ecx\n\t"
      "call *%[c83930]\n\t"
      "movl %%eax, (%%esi)\n\t"
      ".LFUN_00083e20_5:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xff0000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x10, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "shll $0x10, %%edx\n\t"
      "andl $0xff00, %%eax\n\t"
      "orl %%eax, %%edx\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "pushl %%ebx\n\t"
      "shrl $8, %%ecx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movb 0x4(%%esi), %%bl\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movzbw %%ah, %%cx\n\t"
      "movb %%al, %%ch\n\t"
      "pushl $0\n\t"
      "shrl $4, %%ebx\n\t"
      "notb %%bl\n\t"
      "pushl %%esi\n\t"
      "movw $2, -0x18(%%ebp)\n\t"
      "andb $1, %%bl\n\t"
      "movw %%cx, -0x16(%%ebp)\n\t"
      "call *%[c83bd0]\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0x10\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c2251a2]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083e20_14\n\t"
      "call *%[c2235c4]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $0x2733, %%edi\n\t"
      "jne .LFUN_00083e20_11\n\t"
      "call *%[c8e370]\n\t"
      "addl $0x2710, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00083e20_6:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x11c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "movl %%ecx, -0x118(%%ebp)\n\t"
      "movl $1, -0x11c(%%ebp)\n\t"
      "call *%[c2251b8]\n\t"
      "cmpl $1, %%eax\n\t"
      "jne .LFUN_00083e20_9\n\t"
      "xorl %%edi, %%edi\n\t"
      "jmp .LFUN_00083e20_10\n\t"
      ".LFUN_00083e20_7:\n\t"
      "cmpb $0x12, %%al\n\t"
      "jne .LFUN_00083e20_8\n\t"
      "movl $1, %%edx\n\t"
      "jmp .LFUN_00083e20_4\n\t"
      ".LFUN_00083e20_8:\n\t"
      "movl $0xfffffff4, %%eax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083e20_9:\n\t"
      "call *%[c2235c4]\n\t"
      "movl %%eax, %%edi\n\t"
      ".LFUN_00083e20_10:\n\t"
      "call *%[c8e370]\n\t"
      "cmpl 0x8(%%ebp), %%eax\n\t"
      "ja .LFUN_00083e20_13\n\t"
      "cmpl $0x2734, %%edi\n\t"
      "je .LFUN_00083e20_6\n\t"
      ".LFUN_00083e20_11:\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00083e20_14\n\t"
      ".LFUN_00083e20_12:\n\t"
      "pushl %%edi\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl $0xfffffff0, %%eax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00083e20_13:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x2734, %%edi\n\t"
      "call *%[c225cc6]\n\t"
      "jmp .LFUN_00083e20_12\n\t"
      ".LFUN_00083e20_14:\n\t"
      "movzbl %%bl, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c83bd0]\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "addl $8, %%esp\n\t"
      "andb $0xef, %%al\n\t"
      "orb $0x21, %%al\n\t"
      "movb %%al, 0x4(%%esi)\n\t"
      "popl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b83e20_assert), [exitfn] "m"(b83e20_exitfn), [c83930] "m"(b83e20_c83930), [c83bd0] "m"(b83e20_c83bd0), [c2251a2] "m"(b83e20_c2251a2), [c2235c4] "m"(b83e20_c2235c4), [c8e370] "m"(b83e20_c8e370), [c2251b8] "m"(b83e20_c2251b8), [c83310] "m"(b83e20_c83310), [c225cc6] "m"(b83e20_c225cc6)
      : "memory");
}
#else
#error "FUN_00083e20: clang naked draft required"
#endif


/* FUN_00084080 (0x84080) — XBE naked draft (batch 253). */
#if defined(__clang__)
static void (*const b84080_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b84080_exitfn)(int) = system_exit;
static short (*const b84080_c83e20)(int endpoint, int address) = FUN_00083e20;
static bool (*const b84080_c81870)(int *mutex_reference, int timeout_ms) = take_mutex;
static void (*const b84080_c84000)(int *ep) = close_endpoint;
static void (*const b84080_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void (*const b84080_c818d0)(int *mutex_reference) = release_mutex;
static void (*const b84080_c81910)(void *a0) = FUN_00081910;
static void (*const b84080_c82cf0)(void *endpoint) = FUN_00082cf0;

__attribute__((naked, noinline))
void FUN_00084080(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00084080_1\n\t"
      "pushl $1\n\t"
      "pushl $0x239\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084080_1:\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jne .LFUN_00084080_2\n\t"
      "pushl $1\n\t"
      "pushl $0x23a\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266c90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084080_2:\n\t"
      "movl 0x1c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00084080_3\n\t"
      "pushl $1\n\t"
      "pushl $0x23b\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266c80\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084080_3:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00084080_4\n\t"
      "pushl $1\n\t"
      "pushl $0x23c\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084080_4:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "leal 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c83e20]\n\t"
      "movl 0x20(%%edi), %%edx\n\t"
      "pushl $0x3e8\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c81870]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00084080_6\n\t"
      "movb 0x24(%%edi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00084080_5\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c84000]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00084080_5:\n\t"
      "movl 0x1c(%%edi), %%ecx\n\t"
      "movl 0x20(%%edi), %%esi\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .LFUN_00084080_7\n\t"
      ".LFUN_00084080_6:\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      ".LFUN_00084080_7:\n\t"
      "testl %%esi, %%esi\n\t"
      "movl (%%edi), %%edx\n\t"
      "movw %%bx, 0x6(%%edx)\n\t"
      "je .LFUN_00084080_8\n\t"
      "pushl $0x252\n\t"
      "pushl $0x266618\n\t"
      "pushl %%edi\n\t"
      "call *%[c8ef70]\n\t"
      "pushl %%esi\n\t"
      "call *%[c818d0]\n\t"
      "pushl %%esi\n\t"
      "call *%[c81910]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084080_8:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_00084080_9\n\t"
      "call *%[c82cf0]\n\t"
      ".LFUN_00084080_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movswl %%bx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b84080_assert), [exitfn] "m"(b84080_exitfn), [c83e20] "m"(b84080_c83e20), [c81870] "m"(b84080_c81870), [c84000] "m"(b84080_c84000), [c8ef70] "m"(b84080_c8ef70), [c818d0] "m"(b84080_c818d0), [c81910] "m"(b84080_c81910), [c82cf0] "m"(b84080_c82cf0)
      : "memory");
}
#else
#error "FUN_00084080: clang naked draft required"
#endif


/* FUN_000841b0 (0x841b0) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b841b0_c82d30)(void) = endpoint_pool_cleanup;
static void (*const b841b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b841b0_exitfn)(int) = system_exit;
static void * (*const b841b0_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static void (*const b841b0_c817e0)(void) = create_mutex;
static bool (*const b841b0_c81630)(int priority_flags, void *function, int param, void **thread_reference) = thread_new;
static char (*const b841b0_c82c90)(void *endpoint) = FUN_00082c90;
static void (*const b841b0_c81770)(void *thread_reference) = thread_close;
static void (*const b841b0_c81910)(void *a0) = FUN_00081910;
static void (*const b841b0_c8ef70)(void *ptr, const char *file, int line) = debug_free;

__attribute__((naked, noinline))
short FUN_000841b0(int endpoint __attribute__((unused)), int address __attribute__((unused)), int process_ref __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c82d30]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "je .LFUN_000841b0_1\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_000841b0_1\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000841b0_2\n\t"
      ".LFUN_000841b0_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x268\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266ca4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000841b0_2:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000841b0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x269\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000841b0_3:\n\t"
      "pushl $0x26b\n\t"
      "pushl $0x266618\n\t"
      "pushl $1\n\t"
      "pushl $0x28\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_000841b0_6\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "leal 0x4(%%ebx), %%edi\n\t"
      "movl $6, %%ecx\n\t"
      "rep movsl\n\t"
      "leal 0x20(%%ebx), %%edi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, (%%ebx)\n\t"
      "movb $0, 0x24(%%ebx)\n\t"
      "call *%[c817e0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000841b0_5\n\t"
      "leal 0x1c(%%ebx), %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x84080\n\t"
      "pushl $2\n\t"
      "call *%[c81630]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000841b0_5\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c82c90]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000841b0_4\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl $0xffffffe9, %%eax\n\t"
      "movl %%ebx, (%%edx)\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x6(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000841b0_4:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c81770]\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81910]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0, (%%esi)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x6(%%ecx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000841b0_5:\n\t"
      "pushl $0x282\n\t"
      "pushl $0x266618\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movl $0xfffffff0, %%eax\n\t"
      "popl %%esi\n\t"
      "movw %%ax, 0x6(%%edx)\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000841b0_6:\n\t"
      "movl $0xfffffff7, %%eax\n\t"
      "movw %%ax, 0x6(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c82d30] "m"(b841b0_c82d30), [assert] "m"(b841b0_assert), [exitfn] "m"(b841b0_exitfn), [c8ee60] "m"(b841b0_c8ee60), [c817e0] "m"(b841b0_c817e0), [c81630] "m"(b841b0_c81630), [c82c90] "m"(b841b0_c82c90), [c81770] "m"(b841b0_c81770), [c81910] "m"(b841b0_c81910), [c8ef70] "m"(b841b0_c8ef70)
      : "memory");
}
#else
#error "FUN_000841b0: clang naked draft required"
#endif


/* FUN_000843a0 (0x843a0) — XBE naked draft (batch 259). */
#if defined(__clang__)
static void (*const b843a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b843a0_exitfn)(int) = system_exit;
static void b843a0_c2249ec_tgt(void) { return; }
static void (*const b843a0_c2249ec)(void) = b843a0_c2249ec_tgt;
static void (*const b843a0_c2235c4)(void) = GetLastError;
static const char * (*const b843a0_c83310)(int error_code) = winsock_error_report;

__attribute__((naked, noinline))
short FUN_000843a0(int endpoint __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_000843a0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2b0\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266658\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000843a0_1:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000843a0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2b1\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000843a0_2:\n\t"
      "movl (%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_000843a0_4\n\t"
      "pushl $0x20\n\t"
      "pushl %%eax\n\t"
      "call *%[c2249ec]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000843a0_3\n\t"
      "orb $2, 0x4(%%esi)\n\t"
      "movw %%di, 0x6(%%esi)\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000843a0_3:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      "movl $0xffffffef, %%eax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000843a0_4:\n\t"
      "movl $0xfffffff4, %%eax\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b843a0_assert), [exitfn] "m"(b843a0_exitfn), [c2249ec] "m"(b843a0_c2249ec), [c2235c4] "m"(b843a0_c2235c4), [c83310] "m"(b843a0_c83310)
      : "memory");
}
#else
#error "FUN_000843a0: clang naked draft required"
#endif


/* FUN_00084450 (0x84450) — XBE naked draft (batch 255). */
#if defined(__clang__)
static void (*const b84450_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b84450_exitfn)(int) = system_exit;
static void b84450_c2251ad_tgt(void) { return; }
static void (*const b84450_c2251ad)(void) = b84450_c2251ad_tgt;
static void *(*const b84450_c82d70)(int type) = get_next_endpoint_from_set;
static void (*const b84450_c2235c4)(void) = GetLastError;
static const char * (*const b84450_c83310)(int error_code) = winsock_error_report;

__attribute__((naked, noinline))
int FUN_00084450(int listening_endpoint __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x10, -0x4(%%ebp)\n\t"
      "jne .LFUN_00084450_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d1\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266d20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084450_1:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00084450_2\n\t"
      "pushl $1\n\t"
      "pushl $0x2d2\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084450_2:\n\t"
      "movl (%%esi), %%edx\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c2251ad]\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00084450_4\n\t"
      "movsbl 0x5(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c82d70]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00084450_3\n\t"
      "movb 0x4(%%eax), %%cl\n\t"
      "movl %%edi, (%%eax)\n\t"
      "popl %%edi\n\t"
      "orb $1, %%cl\n\t"
      "popl %%esi\n\t"
      "movb %%cl, 0x4(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00084450_3:\n\t"
      "popl %%edi\n\t"
      "movw $0xfff7, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00084450_4:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movw $0xffff, 0x6(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b84450_assert), [exitfn] "m"(b84450_exitfn), [c2251ad] "m"(b84450_c2251ad), [c82d70] "m"(b84450_c82d70), [c2235c4] "m"(b84450_c2235c4), [c83310] "m"(b84450_c83310)
      : "memory");
}
#else
#error "FUN_00084450: clang naked draft required"
#endif


/* FUN_00084740 (0x84740) — XBE naked draft (batch 248). */
#if defined(__clang__)
static void (*const b84740_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b84740_exitfn)(int) = system_exit;
static int (*const b84740_c83930)(int af, int type, int protocol) = FUN_00083930;
static void b84740_c225ce0_tgt(void) { return; }
static void (*const b84740_c225ce0)(void) = b84740_c225ce0_tgt;
static void (*const b84740_c2235c4)(void) = GetLastError;

__attribute__((naked, noinline))
int FUN_00084740(int endpoint __attribute__((unused)), void *message __attribute__((unused)), int size __attribute__((unused)), int dest_address __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "je .LFUN_00084740_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00084740_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00084740_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00084740_2\n\t"
      ".LFUN_00084740_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x3bd\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266ddc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084740_2:\n\t"
      "movb 0x335090, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00084740_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3be\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x265fe4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084740_3:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xff0000, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "shrl $0x10, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%eax, %%edx\n\t"
      "andl $0xff00, %%eax\n\t"
      "shll $0x10, %%edx\n\t"
      "orl %%eax, %%edx\n\t"
      "movw 0x12(%%edi), %%ax\n\t"
      "shrl $8, %%ecx\n\t"
      "shll $8, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movzbw %%ah, %%cx\n\t"
      "movb %%al, %%ch\n\t"
      "cmpl $-1, (%%esi)\n\t"
      "movw $2, -0x10(%%ebp)\n\t"
      "movw %%cx, -0xe(%%ebp)\n\t"
      "jne .LFUN_00084740_5\n\t"
      "cmpb $0x11, 0x5(%%esi)\n\t"
      "je .LFUN_00084740_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3c6\n\t"
      "pushl $0x266618\n\t"
      "pushl $0x266d90\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00084740_4:\n\t"
      "movl $2, %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "call *%[c83930]\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "je .LFUN_00084740_7\n\t"
      ".LFUN_00084740_5:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c225ce0]\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00084740_11\n\t"
      ".LFUN_00084740_6:\n\t"
      "call *%[c2235c4]\n\t"
      "addl $0xffffd8cd, %%eax\n\t"
      "cmpl $0x19, %%eax\n\t"
      "ja .LFUN_00084740_10\n\t"
      "movzbl 0x848a4(%%eax), %%edx\n\t"
      "jmp *.LFUN_00084740_jt(,%%edx,4)\n\t"
      ".LFUN_00084740_7:\n\t"
      "movw $0xffff, 0x6(%%esi)\n\t"
      "jmp .LFUN_00084740_6\n\t"
      ".LFUN_00084740_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0xfffffffc, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00084740_9:\n\t"
      "movb 0x4(%%esi), %%al\n\t"
      "andb $0xfe, %%al\n\t"
      "popl %%edi\n\t"
      "movb %%al, 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl $0xfffffffd, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00084740_10:\n\t"
      "movl $0xfffffffe, %%eax\n\t"
      ".LFUN_00084740_11:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00084740_jt:\n\t"
      ".long .LFUN_00084740_8\n\t"
      ".long .LFUN_00084740_9\n\t"
      ".long .LFUN_00084740_10\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b84740_assert), [exitfn] "m"(b84740_exitfn), [c83930] "m"(b84740_c83930), [c225ce0] "m"(b84740_c225ce0), [c2235c4] "m"(b84740_c2235c4)
      : "memory");
}
#else
#error "FUN_00084740: clang naked draft required"
#endif


/* FUN_00084940 (0x84940) — readable C lift. */
int FUN_00084940(int listening_endpoint)
{
  void *p = (void *)FUN_00084450(listening_endpoint);
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

/* FUN_00083930 (0x83930) — XBE naked draft (batch 277). */
#if defined(__clang__)
static void b83930_c2255f6_tgt(void) { return; }
static void (*const b83930_c2255f6)(void) = b83930_c2255f6_tgt;
static void b83930_c225188_tgt(void) { return; }
static void (*const b83930_c225188)(void) = b83930_c225188_tgt;
static void (*const b83930_c2235c4)(void) = GetLastError;
static const char * (*const b83930_c83310)(int error_code) = winsock_error_report;
static void b83930_c22485c_tgt(void) { return; }
static void (*const b83930_c22485c)(void) = b83930_c22485c_tgt;

__attribute__((naked, noinline))
int FUN_00083930(int af __attribute__((unused)), int type __attribute__((unused)), int protocol __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c2255f6]\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_00083930_5\n\t"
      "cmpl $2, %%edi\n\t"
      "jne .LFUN_00083930_1\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x20\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl $0xffffffff, -0x4(%%ebp)\n\t"
      "call *%[c225188]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083930_1\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00083930_1:\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $4\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "call *%[c225188]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083930_2\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00083930_2:\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x1001\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "call *%[c22485c]\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x4000, %%edi\n\t"
      "jne .LFUN_00083930_3\n\t"
      "cmpl %%edi, -0x4(%%ebp)\n\t"
      "jge .LFUN_00083930_4\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1001\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c225188]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083930_4\n\t"
      ".LFUN_00083930_3:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00083930_4:\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x1002\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "call *%[c22485c]\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00083930_5\n\t"
      "cmpl %%edi, -0x4(%%ebp)\n\t"
      "jge .LFUN_00083930_6\n\t"
      "pushl $4\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x1002\n\t"
      "pushl $0xffff\n\t"
      "pushl %%esi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "call *%[c225188]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00083930_6\n\t"
      ".LFUN_00083930_5:\n\t"
      "call *%[c2235c4]\n\t"
      "pushl %%eax\n\t"
      "call *%[c83310]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00083930_6:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c2255f6] "m"(b83930_c2255f6), [c225188] "m"(b83930_c225188), [c2235c4] "m"(b83930_c2235c4), [c83310] "m"(b83930_c83310), [c22485c] "m"(b83930_c22485c)
      : "memory");
}
#else
#error "FUN_00083930: clang naked draft required"
#endif

