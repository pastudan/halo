/*
 * telnet_console.c — Debug telnet server for runtime console access.
 *
 * Listens on TCP port 23 (telnet). Accepts exactly one client connection at a
 * time. Each process tick checks for new connections and forwards received data
 * to the HS (HaloScript) command processor via FUN_00130b70.
 *
 * Globals layout at 0x46eee0 (0x8c bytes, zeroed by initialize/dispose):
 *   [+0x00] int*  listening_endpoint  — TCP listening socket wrapper
 *   [+0x04] int*  clients[0].ep       — accepted client endpoint (one slot)
 *   [+0x08] char  clients[0].buf[128] — telnet line input buffer
 *   [+0x88] char  initialized         — non-zero when subsystem is live
 */

/*
 * Transport endpoint helpers — not in kb.json (only used here).
 * All calls go through hardcoded function-pointer casts.
 *
 *   0x82d70  create_transport_endpoint(int type) -> int* (NULL on failure)
 *   0x83ce0  bind_endpoint(int *ep, void *addr)  -> int16_t (0=ok)
 *   0x843a0  listen_endpoint(int *ep)             -> int16_t (0=ok)
 *   0x848c0  destroy_endpoint(int *ep)            -> void
 *   0x83040  endpoint_readable(int *ep, uint16_t timeout_ms) -> char (bool)
 *   0x84450  accept_endpoint(int *ep)             -> int* (NULL if none)
 *   0x82f50  send_endpoint(int *ep, char *buf, int len) -> int (<=0 = error)
 *   0x82e50  recv_endpoint(int *ep, char *buf, int maxlen) -> int (<=0 = error)
 *   0x81c80  transport_error_string(int16_t code) -> char* (description)
 *   0x130b70 process_telnet_client_input(char *buf, int len)
 *            -> char (bool: 1=ok, 0=close client); ESI = &clients[0] (implicit)
 */

/* telnet_console_globals layout (as addressed from 0x46eee0): */
#define tc_listening_ep (*(int **)0x46eee0)
#define tc_client0_ep (*(int **)0x46eee4)
#define tc_initialized (*(char *)0x46ef68)

/* Maximum number of simultaneous telnet clients. */
#define TELNET_CONSOLE_MAX_CLIENTS 1

/* TCP transport type code. */
#define TRANSPORT_TYPE_TCP 0x12

/*
 * telnet_console_initialize — create listening TCP socket on port 23.
 *
 * Allocates a TCP transport endpoint, binds it to INADDR_ANY:23, and sets
 * the socket to listen.  Sets the initialized flag on success; logs and
 * tears down on any failure.
 */
void telnet_console_initialize(void)
{
  int16_t result;
  int *ep;

  /* Transport address struct (0x18 bytes).  Layout inferred from bind_endpoint
   * internals: ip at [+0], unknown word at [+0x10], port (host order) at
   * [+0x12].  All other bytes are zero (INADDR_ANY, no options). */
  struct {
    uint32_t ip; /* [+0x00] INADDR_ANY = 0 */
    uint8_t pad[0x10]; /* [+0x04..+0x0f] zeroed */
    uint16_t unk_10; /* [+0x10] = 0x0004 (observed, unknown field) */
    uint16_t port; /* [+0x12] = 23 (telnet), host byte order */
    uint32_t pad2; /* [+0x14] = 0 */
  } addr;

  /* Zero the globals block before populating it. */
  csmemset((void *)0x46eee0, 0, 0x8c);

  /* Allocate a TCP endpoint. */
  ep = ((int *(*)(int))0x82d70)(TRANSPORT_TYPE_TCP);
  if (ep == 0) {
    error(2, "create_transport_endpoint() failed on telnet console endpoint");
    return;
  }
  tc_listening_ep = ep;

  /* Build the bind address: INADDR_ANY on port 23. */
  csmemset(&addr, 0, sizeof(addr));
  addr.unk_10 = 0x0004;
  addr.port = 0x0017; /* 23 decimal = telnet */

  result = ((int16_t(*)(int *, void *))0x83ce0)(ep, &addr);
  if (result != 0) {
    error(2, "bind_endpoint() failed on telnet console endpoint");
    goto fail;
  }

  result = ((int16_t(*)(int *))0x843a0)(ep);
  if (result != 0) {
    error(2, "listen_endpoint() failed on telnet console endpoint");
    goto fail;
  }

  /* Mark subsystem active. */
  tc_initialized = 1;
  return;

fail:
  ((void (*)(int *))0x848c0)(ep);
  tc_listening_ep = 0;
}

/*
 * telnet_console_dispose — shut down the telnet server.
 *
 * Closes the listening endpoint and any connected client, then zeros the
 * entire globals block so the subsystem is in a clean uninitialized state.
 */
void telnet_console_dispose(void)
{
  if (tc_initialized) {
    if (tc_listening_ep != 0) {
      ((void (*)(int *))0x848c0)(tc_listening_ep);
    }
    if (tc_client0_ep != 0) {
      ((void (*)(int *))0x848c0)(tc_client0_ep);
    }
  }
  csmemset((void *)0x46eee0, 0, 0x8c);
}

/*
 * telnet_console_process — per-tick I/O pump for the telnet console.
 *
 * Called once per game tick.  Two independent sections:
 *
 * 1. Accept section: if the listening endpoint is readable, attempt to
 *    accept a new connection.  If accepted and a free client slot exists,
 *    send a greeting and record the endpoint.  If all slots are occupied,
 *    send a rejection message and close the new connection.
 *
 * 2. Receive section: if the connected client's endpoint is readable,
 *    recv up to 0x20 bytes and dispatch to FUN_00130b70 (the per-character
 *    input handler, which echoes chars and processes CR/LF as commands).
 *    On recv error or handler failure, log and close the client.
 *
 * Note: FUN_00130b70 (0x130b70) reads ESI as an implicit register argument
 * pointing to the client slot struct at 0x46eee4.  It cannot be expressed
 * as a plain C function pointer.  The call uses inline asm to load ESI
 * before the call and pass the two stack arguments via "r" constraints
 * (safe — no "m" constraints with pushl, per project convention).
 */
void telnet_console_process(void)
{
  int slot;
  int *new_ep;
  int *slot_ep;
  char readable;
  int recv_result;
  char recv_buf[0x20];
  char input_ok;
  char *error_str;

  if (!tc_initialized) {
    return;
  }

  /* --- Accept section --- */
  readable = ((char (*)(int *, uint16_t))0x83040)(tc_listening_ep, 0);
  if (readable) {
    new_ep = ((int *(*)(int *))0x84450)(tc_listening_ep);
    if (new_ep != 0) {
      /* Search for a free client slot (max 1). */
      for (slot = 0; slot < TELNET_CONSOLE_MAX_CLIENTS; slot++) {
        if (*(int *)(0x46eee4 + slot * 0x84) == 0) {
          /* Found a free slot — send greeting. */
          const char *greeting = "Would you like to play a game?\r\n";
          int greet_len = csstrlen(greeting);
          int sent = ((int (*)(int *, const char *, int))0x82f50)(
            new_ep, greeting, greet_len);
          if (sent < 1) {
            /* Send failed; reject the connection. */
            ((void (*)(int *))0x848c0)(new_ep);
          } else {
            /* Store the accepted endpoint and clear the input buffer. */
            *(int *)(0x46eee4 + slot * 0x84) = (int)new_ep;
            *(char *)(0x46eee8 + slot * 0x84) = 0;
          }
          goto accept_done;
        }
      }
      /* No free slot — send rejection and close. */
      {
        const char *full_msg =
          "sorry - the maximum number of clients are already connected."
          " goodbye!\r\n";
        int full_len = csstrlen(full_msg);
        ((int (*)(int *, const char *, int))0x82f50)(new_ep, full_msg,
                                                     full_len);
        ((void (*)(int *))0x848c0)(new_ep);
      }
    accept_done:;
    }
  }

  /* --- Receive section (client slot 0 only) --- */
  slot_ep = tc_client0_ep;
  if (slot_ep == 0) {
    return;
  }
  readable = ((char (*)(int *, uint16_t))0x83040)(slot_ep, 0);
  if (!readable) {
    return;
  }

  recv_result = ((int (*)(int *, char *, int))0x82e50)(slot_ep, recv_buf, 0x20);
  if (recv_result > 0) {
    /* Dispatch received bytes to the telnet input handler.
     * FUN_00130b70 reads ESI as a pointer to the client slot struct
     * (0x46eee4).  Use inline asm to set ESI before the call. */
    int _buf = (int)recv_buf;
    int _len = recv_result;
    int _esi = 0x46eee4;
    asm volatile("pushl %[len]\n\t"
                 "pushl %[buf]\n\t"
                 "call *%[fn]\n\t"
                 "addl $8, %%esp"
                 : "=a"(input_ok)
                 : [fn] "r"((void *)0x130b70), [buf] "r"(_buf), [len] "r"(_len),
                   [esi] "S"(_esi)
                 : "ecx", "edx", "memory", "cc");
    if (input_ok) {
      return;
    }
    error(2, "error processing telnet client");
  } else {
    /* recv returned <= 0 — connection lost or error. */
    error_str = ((char *(*)(int16_t))0x81c80)((int16_t)recv_result);
    error(2, "connection lost to telnet client ('%s')", error_str);
  }

  /* Close and nullify the client on any error or graceful disconnect. */
  if (tc_client0_ep != 0) {
    ((void (*)(int *))0x848c0)(tc_client0_ep);
    tc_client0_ep = 0;
  }
}
/* --- telnet_console.obj batch drafts (2026-07-26) --- */

/* 0x130ec0 */
void FUN_00130ec0(void)
{
  int eax = 0;

  game_state_data_new((char *)0x0029a9e0, 12, 700);
  /* mem[0x005a90d4] = eax */
  error(eax, (char *)0x0029a9bc);

  (void)eax;
}

/* 0x130ef0 */
void FUN_00130ef0(void)
{
  int eax = 0;

  data_delete_all((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x130f00 */
void FUN_00130f00(void)
{
  int eax = 0;

  data_make_invalid((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x130f10 */
void FUN_00130f10(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x130f30 */
void FUN_00130f30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  tag_get('!tna', 0);
  data_new_at_index((void *)(uintptr_t)eax);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('mtib', 0);
  /* cmp ecx, edx -> jge 0x1310bd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 64);
  /* cmp ecx, ebx -> je 0x1310bd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 32);
  FUN_00076ff0(0, 0);
  /* cmp eax, ebx -> je 0x1310bd */
  /* cmp eax, edx -> jl 0x130fd0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x131130 */
void FUN_00131130(void)
{
  int ecx = 0;

  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)ecx;
}

/* 0x131150 */
void FUN_00131150(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  object_get_markers_by_string_id(0, (void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 0);
  scenario_location_from_point((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131223 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131223 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> jne 0x131269 */
  /* test eax, eax -> jle 0x131269 */
  /* cmp eax, ebx -> jl 0x131235 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x131280 */
void FUN_00131280(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)eax, 0x41 -> jne 0x1312e8 */
  FUN_0018d2c0((void *)(uintptr_t)edx, ecx, eax, 0x00326b30, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)eax, 0x41 -> jne 0x1313c0 */
  FUN_0018d6e0((void *)(uintptr_t)edx, 0, ecx, 0, (float *)(uintptr_t)esi, (float *)(uintptr_t)eax, 0.0f, 0.0f, (float *)0, 0.0f, 0);
  /* cmp eax, ecx -> jl 0x131320 */
  FUN_0018d360((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1313f0 */
void FUN_001313f0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_00131150();
  /* test (char)eax, (char)eax -> jne 0x1316eb */
  /* test (char)eax, 0x41 -> jne 0x1316eb */
  /* test edx, edx -> jle 0x1316ea */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get(0x70706879, 0);
  FUN_00154a50(0, 0, (void *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (void *)0, 0.0f, 0.0f);
  normalize3d((float *)0);
  FUN_0010c510((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  rotate_vector3d_by_sincos((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, 0.0f);
  /* cmp eax, edx -> jl 0x131463 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x131700 */
void FUN_00131700(void)
{
  int eax = 0;
  int ecx = 0;

  object_get_and_verify_type(0, 0);
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!tna', 0);
  /* test (char)eax, (char)eax -> jne 0x13177f */
  FUN_001313f0();
  FUN_001313f0();
  FUN_001313f0();
  FUN_00131280();

  (void)eax;
  (void)ecx;
}

/* 0x131790 */
void FUN_00131790(void)
{
  int eax = 0;
  int ecx = 0;
  int edi = 0;

  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> je 0x131832 */
  datum_get((void *)(uintptr_t)ecx, 0);
  tag_get('!tna', 0);
  /* test (char)eax, (char)eax -> jne 0x13181b */
  /* cmp (int16_t)eax, 5 -> jge 0x13181b */
  /* test (char)eax, 0x41 -> jne 0x131807 */
  FUN_001313f0();
  data_next_index((void *)(uintptr_t)eax, 0);
  /* cmp edi, -1 -> jne 0x1317b1 */

  (void)eax;
  (void)ecx;
  (void)edi;
}

/* 0x131840 */
void FUN_00131840(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x131871 */
  display_assert((char *)0x0029aa24, (char *)0x0029aa38, 96, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131880 */
  /* relift: cmp (int16_t)ebx, word ptr [edi + 0xc] -> jl 0x13189d */
  display_assert((char *)0x0029aa08, (char *)0x0029aa38, 97, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1318ac */
  /* relift: cmp (int16_t)esi, word ptr [edi + 0xe] -> jl 0x1318c9 */
  display_assert((char *)0x0029a9e8, (char *)0x0029aa38, 98, 0);
  system_exit(0);

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1318f0 */
void telnet_console_print(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x131921 */
  display_assert((char *)0x0029aa24, (char *)0x0029aa38, 109, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131936 */
  /* cmp ecx, eax -> jl 0x131953 */
  display_assert((char *)0x0029aa80, (char *)0x0029aa38, 110, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x131968 */
  /* cmp eax, edx -> jl 0x131985 */
  display_assert((char *)0x0029aa60, (char *)0x0029aa38, 111, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1319b0 */
void FUN_001319b0(void)
{
  int eax = 0;

  game_state_data_new((char *)0x0029aac0, 0, 5820);
  /* mem[0x005a90d0] = eax */
  error(eax, (char *)0x0029aaa0);

  (void)eax;
}

/* 0x1319e0 */
void FUN_001319e0(void)
{
  int eax = 0;

  data_delete_all((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1319f0 */
void FUN_001319f0(void)
{
  int eax = 0;

  data_make_invalid((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x131a00 */
void FUN_00131a00(void)
{
  /* relift: no calls detected — manual review */
}

/* 0x131a20 */
void FUN_00131a20(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp edi, ecx -> jge 0x131b1e */
  /* relift: cmp word ptr [ebp + 0x10], 0 -> jl 0x131b0f */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x131b0f */
  /* cmp esi, ecx -> jge 0x131b0f */
  /* cmp edi, eax -> jge 0x131b0f */
  /* cmp (int16_t)ecx, 4 -> je 0x131ab5 */
  /* cmp (int16_t)ecx, 5 -> je 0x131ab5 */
  /* cmp (int16_t)ecx, 4 -> je 0x131ad5 */
  /* cmp (int16_t)ecx, 2 -> je 0x131ad5 */
  telnet_console_print();
  /* cmp (int16_t)esi, (int16_t)edi -> jne 0x131afe */
  /* cmp edi, ecx -> jl 0x131a70 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x131b40 */
void FUN_00131b40(void)
{
  int ecx = 0;

  datum_delete((void *)(uintptr_t)ecx, 0);

  (void)ecx;
}

/* 0x131b60 */
void FUN_00131b60(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_block_get_element((void *)(uintptr_t)edi, 0, 52);
  object_get_markers_by_string_id(0, (void *)(uintptr_t)eax, (void *)0, 0);
  /* relift: cmp esi, dword ptr [edi] -> jl 0x131b80 */
  scenario_location_from_point((void *)(uintptr_t)edx, (void *)(uintptr_t)edi);
  /* test (char)ecx, (char)ecx -> jne 0x131df6 */
  /* relift: cmp word ptr [ebx + 0xe], (int16_t)esi -> jle 0x131c08 */
  /* relift: cmp (int16_t)eax, word ptr [ebx + 0xe] -> jl 0x131bf5 */
  /* relift: cmp (int16_t)esi, word ptr [ebx + 0xe] -> jge 0x131d0b */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 52);
  /* test (int16_t)eax, (int16_t)eax -> jge 0x131c46 */
  /* cmp eax, ecx -> jg 0x131c58 */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131d8e */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> je 0x131d8e */
  FUN_001d9068();
  /* test (char)eax, 0x41 -> jne 0x131de6 */
  /* relift: cmp word ptr [ebx + 0xc], (int16_t)edi -> jle 0x131de3 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x131dd9 */
  FUN_00131840();
  /* cmp (int16_t)esi, (int16_t)eax -> jl 0x131da7 */
  /* relift: cmp (int16_t)edi, word ptr [ebx + 0xc] -> jl 0x131da0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x131e00 */
void FUN_00131e00(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp word ptr [esi + 8], (int16_t)edi -> je 0x131ebe */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0xe] -> jge 0x131ebd */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 52);
  /* test (int16_t)ecx, (int16_t)ecx -> jge 0x131e59 */
  /* cmp ecx, eax -> jg 0x131e6b */
  FUN_00131a20();
  FUN_00131a20();

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x131ed0 */
void FUN_00131ed0(void)
{
  int ecx = 0;

  /* test (int16_t)ecx, (int16_t)ecx -> je 0x131fae */
  /* cmp (int16_t)ecx, 4 -> je 0x131efb */
  /* cmp (int16_t)ecx, 3 -> jne 0x131f39 */
  FUN_00131a20();
  /* cmp (int16_t)ecx, 4 -> jne 0x131f57 */
  FUN_00131a20();
  /* cmp (int16_t)ecx, 1 -> jne 0x131f84 */
  FUN_00131a20();
  FUN_00131a20();
  /* cmp (int16_t)ecx, 2 -> jne 0x131fac */
  FUN_00131a20();
  FUN_00131a20();

  (void)ecx;
}

/* 0x131fc0 */
void FUN_00131fc0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  FUN_00131b60();
  FUN_0018f3e0((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, (void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x13244b */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1320c3 */
  /* test (int16_t)ebx, (int16_t)ebx -> je 0x1320e0 */
  /* test ecx, ecx -> je 0x13243d */
  FUN_00131840();
  tag_get('yhpp', 0);
  tag_get('yhpp', 0);
  random_math_get_local_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  tag_get(0x70706879, 0);
  FUN_00154a50(0, 0, (void *)0, 0, (float *)0, (float *)0, (float *)0, (float *)0, (void *)0, 0.0f, 0.0f);
  /* relift: cmp word ptr [ebp - 0x10], 0 -> jne 0x132214 */
  /* cmp (int16_t)eax, 0xffff -> je 0x132214 */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1322f5 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0xc] -> jge 0x1322f5 */
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x1322f5 */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0xe] -> jge 0x1322f5 */
  FUN_00131840();
  /* relift: cmp word ptr [ebp - 0x10], 0 -> je 0x132344 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x132344 */
  /* relift: cmp word ptr [ebp - 0x10], 0 -> jne 0x1323c0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
  (void)ebp;
}

/* flag_render_proper (0x132460) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void *(*const b132460_get)(int, int) = object_get_and_verify_type;
static int (*const b132460_c17c970)(int mode) = rasterizer_widget_submit;
static int (*const b132460_rzbuf)(int, int) = rasterizer_widget_set_zbuffer_enable;
static void *(*const b132460_tag)(int, int) = tag_get;
static int (*const b132460_rspr)(int) = rasterizer_widget_draw_sprite3d;
static void * (*const b132460_c17c980)(int handle) = rasterizer_widget_begin;
static void *(*const b132460_memset)(void *, int, unsigned int) = csmemset;
static void (*const b132460_c131840)(void) = FUN_00131840;
static void (*const b132460_c180d10)(short type, int count, int compressed_out, int compressed_size, void *uncompressed, int uncompressed_size) = FUN_00180d10;
static void (*const b132460_c1318f0)(void) = telnet_console_print;
static void (*const b132460_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b132460_exitfn)(int) = system_exit;
static void (*const b132460_c17c990)(int handle) = rasterizer_widget_set_texture;
static void (*const b132460_rend)(int) = rasterizer_widget_end;
static void (*const b132460_c17c960)(int param_1) = rasterizer_psuedo_dynamic_screen_quad_draw;
static void (*const b132460_c17d1a0)(int param_1) = FUN_0017d1a0;
static void (*const b132460_c17cbb0)(void *param_1, int param_2) = FUN_0017cbb0;
static char (*const b132460_c1909d0)(int16_t shader_type) = shader_type_is_transparent;
static void (*const b132460_c17cbd0)(int shader, int p2, int p3, int widget_handle, int p5, int p6, int zbuf_handle, float *position, int p9) = FUN_0017cbd0;
static void (*const b132460_c17cbc0)(int shader, int p2, int p3, int widget_handle, int p5, int p6, int zbuf_handle) = FUN_0017cbc0;
static void (*const b132460_c17cbe0)(void) = FUN_0017cbe0;
static void (*const b132460_c17cbf0)(void) = FUN_0017cbf0;
static void (*const b132460_c17c9a0)(int handle) = rasterizer_widget_set_tint_factor;
static void (*const b132460_rocc)(int) = rasterizer_widget_submit_occlusion_test;

__attribute__((naked, noinline))
void flag_render_proper(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x160, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x68(%%eax)\n\t"
      "je .Lflag_render_proper_1\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jmp .Lflag_render_proper_2\n\t"
      ".Lflag_render_proper_1:\n\t"
      "movl 0x24(%%esi), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      ".Lflag_render_proper_2:\n\t"
      "cmpl $-1, -0x18(%%ebp)\n\t"
      "jne .Lflag_render_proper_3\n\t"
      "movl 0x50(%%esi), %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      ".Lflag_render_proper_3:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw $0xb, 0x325652\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "shlw $1, %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "subl $2, %%eax\n\t"
      "decw %%cx\n\t"
      "imull %%ecx, %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c17c970]\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "imull %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $5\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "call *%[rzbuf]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .Lflag_render_proper_34\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lflag_render_proper_34\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "pushl $-1\n\t"
      "pushl %%edx\n\t"
      "call *%[get]\n\t"
      "movl (%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[rspr]\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "call *%[c17c980]\n\t"
      "movswl 0xc(%%esi), %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movswl 0xe(%%esi), %%eax\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "decl %%eax\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "pushl $0x44\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw %%ax, 0xc(%%esi)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "jle .Lflag_render_proper_11\n\t"
      "jmp .Lflag_render_proper_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lflag_render_proper_4:\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .Lflag_render_proper_10\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%ebx, -0x38(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "fmuls -0x48(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "jmp .Lflag_render_proper_6\n\t"
      ".Lflag_render_proper_5:\n\t"
      "movl -0x38(%%ebp), %%ebx\n\t"
      ".Lflag_render_proper_6:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .Lflag_render_proper_7\n\t"
      "decl %%ebx\n\t"
      ".Lflag_render_proper_7:\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%ebx, -0x1c(%%ebp)\n\t"
      "movl %%eax, -0x50(%%ebp)\n\t"
      "jl .Lflag_render_proper_8\n\t"
      "decl %%eax\n\t"
      ".Lflag_render_proper_8:\n\t"
      "movl %%eax, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "incl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c131840]\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "addl $0x30, %%esp\n\t"
      "fsubs (%%ebx)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x80(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x80(%%ebp)\n\t"
      "fmuls -0x80(%%ebp)\n\t"
      "flds -0x84(%%ebp)\n\t"
      "fmuls -0x84(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x88(%%ebp)\n\t"
      "fmuls -0x88(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lflag_render_proper_9\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x88(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x88(%%ebp)\n\t"
      "flds -0x84(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "flds -0x80(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x80(%%ebp)\n\t"
      ".Lflag_render_proper_9:\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl (%%eax), %%edx\n\t"
      "fildl -0x50(%%ebp)\n\t"
      "movl -0x34(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      "movl %%ecx, -0x90(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movl -0x44(%%ebp), %%eax\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "movl %%edx, -0x8c(%%ebp)\n\t"
      "pushl $0x44\n\t"
      "leal -0x94(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x30(%%ebp), %%ecx\n\t"
      "movswl %%bx, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "pushl $0x20\n\t"
      "addl %%ecx, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "movl %%eax, -0x64(%%ebp)\n\t"
      "call *%[c180d10]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%eax\n\t"
      "incl %%ebx\n\t"
      "cmpw 0xe(%%esi), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl -0x2c(%%ebp), %%eax\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "jl .Lflag_render_proper_5\n\t"
      ".Lflag_render_proper_10:\n\t"
      "incl %%eax\n\t"
      "cmpw 0xc(%%esi), %%ax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jl .Lflag_render_proper_4\n\t"
      ".Lflag_render_proper_11:\n\t"
      "movswl 0xc(%%esi), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "decl %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ebx, 0xc(%%ebp)\n\t"
      "jle .Lflag_render_proper_29\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lflag_render_proper_12:\n\t"
      "movswl 0xe(%%esi), %%ecx\n\t"
      "xorl %%edi, %%edi\n\t"
      "decl %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .Lflag_render_proper_28\n\t"
      "nop\n\t"
      ".Lflag_render_proper_13:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1318f0]\n\t"
      "movswl (%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $5, %%eax\n\t"
      "ja .Lflag_render_proper_26\n\t"
      "jmp *.Lflag_render_proper_jt(,%%eax,4)\n\t"
      ".Lflag_render_proper_14:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lflag_render_proper_15\n\t"
      "pushl $1\n\t"
      "pushl $0x2e6\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_15:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "leal 0x1(%%ebx), %%ecx\n\t"
      "imulw %%cx, %%dx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, 0x2(%%ecx)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "incl %%eax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, 0x4(%%ecx)\n\t"
      "jl .Lflag_render_proper_16\n\t"
      "pushl $1\n\t"
      "pushl $0x2eb\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_16:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movswl %%ax, %%ecx\n\t"
      "leal (%%ecx,%%ecx,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "leal 0x1(%%ebx), %%ecx\n\t"
      "imulw %%cx, %%dx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, 0x2(%%ecx)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "leal 0x1(%%ebx), %%ecx\n\t"
      "imulw %%cx, %%dx\n\t"
      "incl %%eax\n\t"
      "leal 0x1(%%edx,%%edi,1), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw %%cx, 0x4(%%edx)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jmp .Lflag_render_proper_27\n\t"
      ".Lflag_render_proper_17:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lflag_render_proper_18\n\t"
      "pushl $1\n\t"
      "pushl $0x2f2\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_18:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, (%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "leal 0x1(%%ebx), %%edx\n\t"
      "imulw 0xe(%%esi), %%dx\n\t"
      "addl %%edi, %%edx\n\t"
      "incl %%ecx\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jmp .Lflag_render_proper_27\n\t"
      ".Lflag_render_proper_19:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lflag_render_proper_20\n\t"
      "pushl $1\n\t"
      "pushl $0x2f9\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_20:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal (%%eax,%%edx,2), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, (%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%bx, %%dx\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "leal 0x1(%%ebx), %%edx\n\t"
      "imulw 0xe(%%esi), %%dx\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "jmp .Lflag_render_proper_27\n\t"
      ".Lflag_render_proper_21:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lflag_render_proper_22\n\t"
      "pushl $1\n\t"
      "pushl $0x300\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_22:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xe(%%esi), %%cx\n\t"
      "imulw %%bx, %%cx\n\t"
      "addl %%edi, %%ecx\n\t"
      "movw %%cx, (%%eax)\n\t"
      "jmp .Lflag_render_proper_25\n\t"
      ".Lflag_render_proper_23:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "cmpw -0x8(%%ebp), %%ax\n\t"
      "jl .Lflag_render_proper_24\n\t"
      "pushl $1\n\t"
      "pushl $0x307\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aad0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_24:\n\t"
      "movswl 0xc(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xe(%%esi), %%cx\n\t"
      "imulw %%bx, %%cx\n\t"
      "leal 0x1(%%ecx,%%edi,1), %%edx\n\t"
      "movw %%dx, (%%eax)\n\t"
      ".Lflag_render_proper_25:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "leal 0x1(%%ebx), %%ecx\n\t"
      "imulw %%cx, %%dx\n\t"
      "leal 0x1(%%edx,%%edi,1), %%edx\n\t"
      "movw %%dx, 0x2(%%eax)\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "imulw %%cx, %%dx\n\t"
      "addl %%edi, %%edx\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      "incl 0xc(%%ebp)\n\t"
      "jmp .Lflag_render_proper_27\n\t"
      ".Lflag_render_proper_26:\n\t"
      "pushl $1\n\t"
      "pushl $0x310\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_27:\n\t"
      "movswl 0xe(%%esi), %%eax\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%ecx\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .Lflag_render_proper_13\n\t"
      ".Lflag_render_proper_28:\n\t"
      "movswl 0xc(%%esi), %%edx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .Lflag_render_proper_12\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      ".Lflag_render_proper_29:\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17c990]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[rend]\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $0, 0xc(%%esi)\n\t"
      "movl %%eax, -0x30(%%ebp)\n\t"
      "jg .Lflag_render_proper_30\n\t"
      "pushl $1\n\t"
      "pushl $0x61\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29aa08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_30:\n\t"
      "cmpw $0, 0xe(%%esi)\n\t"
      "jg .Lflag_render_proper_31\n\t"
      "pushl $1\n\t"
      "pushl $0x62\n\t"
      "pushl $0x29aa38\n\t"
      "pushl $0x29a9e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lflag_render_proper_31:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "decw %%cx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xe(%%esi), %%dx\n\t"
      "decw %%dx\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0xe(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%esi), %%cx\n\t"
      "decw %%ax\n\t"
      "decw %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c131840]\n\t"
      "flds (%%eax)\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "fadds (%%ecx)\n\t"
      "pushl $0xcc\n\t"
      "leal -0x160(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "fadds (%%ebx)\n\t"
      "pushl %%edx\n\t"
      "fadds 0x1c(%%edi)\n\t"
      "fmuls 0x25337c\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fadds 0x20(%%edi)\n\t"
      "fmuls 0x25337c\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fadds 0x24(%%edi)\n\t"
      "fmuls 0x25337c\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x31fc60, %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl %%eax, -0x158(%%ebp)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl $1, %%ebx\n\t"
      "movl %%ebx, -0x15c(%%ebp)\n\t"
      "movw %%bx, -0x154(%%ebp)\n\t"
      "movl $0x1d, %%ecx\n\t"
      "leal -0x150(%%ebp), %%edi\n\t"
      "rep movsl\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl %%ecx, -0xdc(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl %%edx, -0xd8(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0xac(%%ebp)\n\t"
      "movl %%ecx, -0xa8(%%ebp)\n\t"
      "movl %%edx, -0xa4(%%ebp)\n\t"
      "movl $0x3f800000, -0x98(%%ebp)\n\t"
      "movl $0x3f800000, -0x9c(%%ebp)\n\t"
      "call *%[c17c960]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c17d1a0]\n\t"
      "leal -0x160(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c17cbb0]\n\t"
      "movl -0x30(%%ebp), %%esi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x24(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1909d0]\n\t"
      "movswl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "je .Lflag_render_proper_32\n\t"
      "pushl $0\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c17cbd0]\n\t"
      "addl $0x24, %%esp\n\t"
      "jmp .Lflag_render_proper_33\n\t"
      ".Lflag_render_proper_32:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c17cbc0]\n\t"
      "addl $0x1c, %%esp\n\t"
      ".Lflag_render_proper_33:\n\t"
      "call *%[c17cbe0]\n\t"
      "call *%[c17cbf0]\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17c960]\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      ".Lflag_render_proper_34:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c17c9a0]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[rocc]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x325652\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lflag_render_proper_jt:\n\t"
      ".long .Lflag_render_proper_14\n\t"
      ".long .Lflag_render_proper_27\n\t"
      ".long .Lflag_render_proper_17\n\t"
      ".long .Lflag_render_proper_19\n\t"
      ".long .Lflag_render_proper_21\n\t"
      ".long .Lflag_render_proper_23\n\t"
      ".text\n\t"
      :
      : [get] "m"(b132460_get), [c17c970] "m"(b132460_c17c970), [rzbuf] "m"(b132460_rzbuf), [tag] "m"(b132460_tag), [rspr] "m"(b132460_rspr), [c17c980] "m"(b132460_c17c980), [memset] "m"(b132460_memset), [c131840] "m"(b132460_c131840), [c180d10] "m"(b132460_c180d10), [c1318f0] "m"(b132460_c1318f0), [assert] "m"(b132460_assert), [exitfn] "m"(b132460_exitfn), [c17c990] "m"(b132460_c17c990), [rend] "m"(b132460_rend), [c17c960] "m"(b132460_c17c960), [c17d1a0] "m"(b132460_c17d1a0), [c17cbb0] "m"(b132460_c17cbb0), [c1909d0] "m"(b132460_c1909d0), [c17cbd0] "m"(b132460_c17cbd0), [c17cbc0] "m"(b132460_c17cbc0), [c17cbe0] "m"(b132460_c17cbe0), [c17cbf0] "m"(b132460_c17cbf0), [c17c9a0] "m"(b132460_c17c9a0), [rocc] "m"(b132460_rocc)
      : "memory");
}
#else
#error "flag_render_proper: clang naked draft required"
#endif

