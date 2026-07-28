#include <stdint.h>
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

/* FUN_00130ec0 (0x130ec0) — readable C lift. */
void FUN_00130ec0(void)
{
  void *p = game_state_data_new(0x29a9e0, 0xc, 0x2bc);
  *(void **)0x5a90d4 = p;
  if (p == NULL)
    error(p, 0x29a9bc);
}

/* FUN_00130ef0 (0x130ef0) — readable C lift. */
void FUN_00130ef0(void)
{
  data_delete_all(*(data_t **)0x5a90d4);
}

/* FUN_00130f00 (0x130f00) — readable C lift. */
void FUN_00130f00(void)
{
  data_make_invalid(*(data_t **)0x5a90d4);
}

/* FUN_00130f10 (0x130f10) — readable C lift. */
void FUN_00130f10(void)
{
  if (*(int *)0x5a90d4 != 0) {
    *(int *)0x5a90d4 = 0;
  }
}

/* FUN_00130f30 (0x130f30) — readable C lift (restored pre-naked). */
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


/* FUN_00131130 (0x131130) — readable C lift. */
void FUN_00131130(int handle)
{
  datum_delete(*(data_t **)0x5a90d4, handle);
}

/* FUN_00131150 (0x131150) — readable C lift (restored pre-naked). */
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


/* FUN_001313f0 (0x1313f0) — readable C lift (restored pre-naked). */
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


/* FUN_00131700 (0x131700) — readable C lift: bind antenna to object. */
void FUN_00131700(int object_handle, int antenna_handle)
{
  char *ant;
  void *tag;
  void (*fn_1313f0)(void *, void *, unsigned int);
  void (*fn_131280)(void *, void *);

  object_get_and_verify_type(object_handle, -1);
  ant = (char *)datum_get(*(data_t **)0x5a90d4, antenna_handle);
  tag = tag_get(*(int *)(ant + 8), 0x616e7421);
  if (*(unsigned char *)(ant + 5) != 0)
    return;
  *(int *)(ant + 0xc) = object_handle;
  fn_1313f0 = (void (*)(void *, void *, unsigned int))FUN_001313f0;
  fn_131280 = (void (*)(void *, void *))FUN_00131280;
  if (*(short *)(ant + 6) > 5) {
    fn_1313f0(ant, tag, 0x3d4ccccd);
    fn_1313f0(ant, tag, 0x3d4ccccd);
    fn_1313f0(ant, tag, 0x3d4ccccd);
  }
  *(short *)(ant + 6) = 0;
  __asm__ volatile("movl %0, %%ecx" : : "r"(tag) : "ecx");
  ((void (*)(void *))FUN_00131280)(ant);
}

/* FUN_00131790 (0x131790) — XBE naked draft (batch 142). */
#if defined(__clang__)
static int (*const b131790_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b131790_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b131790_tag)(int, int) = tag_get;
static void (*const b131790_c1313f0)(void) = FUN_001313f0;

__attribute__((naked, noinline))
void FUN_00131790(float dt __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a90d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00131790_5\n\t"
      "pushl %%esi\n\t"
      ".LFUN_00131790_1:\n\t"
      "movl 0x5a90d4, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x616e7421\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movb 0x5(%%esi), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00131790_4\n\t"
      "incw 0x6(%%esi)\n\t"
      "cmpl $-1, 0xc(%%esi)\n\t"
      "movw 0x6(%%esi), %%ax\n\t"
      "je .LFUN_00131790_4\n\t"
      "cmpw $5, %%ax\n\t"
      "jge .LFUN_00131790_4\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x253d48\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00131790_2\n\t"
      "movl $0x3d888889, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00131790_3\n\t"
      ".LFUN_00131790_2:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".LFUN_00131790_3:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1313f0]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00131790_4:\n\t"
      "movl 0x5a90d4, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .LFUN_00131790_1\n\t"
      "popl %%esi\n\t"
      ".LFUN_00131790_5:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b131790_c1198f0), [dget] "m"(b131790_dget), [tag] "m"(b131790_tag), [c1313f0] "m"(b131790_c1313f0)
      : "memory");
}
#else
#error "FUN_00131790: clang naked draft required"
#endif


/* FUN_00131840 (0x131840) — readable C lift. */
void *FUN_00131840(void *base, short *dims, short x, short y)
{
  extern char DAT_0029aa08[];
  extern char DAT_0029aa24[];
  extern char DAT_0029aa38[];
  extern char DAT_0029a9e8[];
  int idx;

  if (base == 0 || dims == 0) {
    display_assert(DAT_0029aa24, DAT_0029aa38, 0x60, 1);
    system_exit(-1);
  }
  if (x < 0 || x >= dims[6]) {
    display_assert(DAT_0029aa08, DAT_0029aa38, 0x61, 1);
    system_exit(-1);
  }
  if (y < 0 || y >= dims[7]) {
    display_assert(DAT_0029a9e8, DAT_0029aa38, 0x62, 1);
    system_exit(-1);
  }
  idx = (int)dims[7] * (int)x + (int)y;
  return (char *)base + idx * 24 + 0x1c;
}
/* telnet_console_print (0x1318f0) — readable C lift (grid cell ptr). */
void *telnet_console_print(void *base, short *dims, short x, short y)
{
  extern char DAT_0029aa24[];
  extern char DAT_0029aa38[];
  extern char DAT_0029aa60[];
  extern char DAT_0029aa80[];
  int idx;

  if (base == 0 || dims == 0) {
    display_assert(DAT_0029aa24, DAT_0029aa38, 0x6d, 1);
    system_exit(-1);
  }
  if (x < 0 || (int)x >= (int)dims[6] - 1) {
    display_assert(DAT_0029aa80, DAT_0029aa38, 0x6e, 1);
    system_exit(-1);
  }
  if (y < 0 || (int)y >= (int)dims[7] - 1) {
    display_assert(DAT_0029aa60, DAT_0029aa38, 0x6f, 1);
    system_exit(-1);
  }
  idx = ((int)dims[7] - 1) * (int)x + (int)y;
  return (char *)base + idx * 2 + 0x1534;
}
/* FUN_001319b0 (0x1319b0) — readable C lift. */
void FUN_001319b0(void)
{
  void *p = game_state_data_new(0x29aac0, 2, 0x16bc);
  *(void **)0x5a90d0 = p;
  if (p == NULL)
    error(p, 0x29aaa0);
}

/* FUN_001319e0 (0x1319e0) — readable C lift. */
void FUN_001319e0(void)
{
  data_delete_all(*(data_t **)0x5a90d0);
}

/* FUN_001319f0 (0x1319f0) — readable C lift. */
void FUN_001319f0(void)
{
  data_make_invalid(*(data_t **)0x5a90d0);
}

/* FUN_00131a00 (0x131a00) — readable C lift. */
void FUN_00131a00(void)
{
  if (*(int *)0x5a90d0 != 0) {
    *(int *)0x5a90d0 = 0;
  }
}

/* FUN_00131a20 (0x131a20) — readable C lift (restored pre-naked). */
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
  ((void *(*)(void))telnet_console_print)();
  /* cmp (int16_t)esi, (int16_t)edi -> jne 0x131afe */
  /* cmp edi, ecx -> jl 0x131a70 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* FUN_00131b40 (0x131b40) — readable C lift. */
void FUN_00131b40(int handle)
{
  datum_delete(*(data_t **)0x5a90d0, handle);
}

/* FUN_00131b60 (0x131b60) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00131840)();
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


/* FUN_00131fc0 (0x131fc0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_00131840)();
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
  ((void(*)(void))FUN_00131840)();
  /* relift: cmp word ptr [ebp - 0x10], 0 -> je 0x132344 */
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x132344 */
  /* relift: cmp word ptr [ebp - 0x10], 0 -> jne 0x1323c0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
  (void)ebp;
}



/* flag_render_proper (0x132460) — readable C lift (restored pre-naked). */
void flag_render_proper(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int ebp = 0;

  object_get_and_verify_type(0, 0);
  /* relift: cmp word ptr [eax + 0x68], 0 -> je 0x13248f */
  /* relift: cmp dword ptr [ebp - 0x18], -1 -> jne 0x1324a1 */
  rasterizer_widget_submit(0);
  rasterizer_widget_set_zbuffer_enable(0, 0);
  /* cmp eax, -1 -> je 0x132c5e */
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  rasterizer_widget_draw_sprite3d(0);
  rasterizer_widget_begin(0);
  csmemset((void *)0, 0, 0);
  ((void(*)(void))FUN_00131840)();
  /* cmp ebx, eax -> jl 0x1325c2 */
  ((void(*)(void))FUN_00131840)();
  ((void(*)(void))FUN_00131840)();
  ((void(*)(void))FUN_00131840)();
  FUN_00180d10(0, 0, 0, 0, (void *)0, 0);
  /* test ecx, ecx -> jle 0x132a54 */
  ((void(*)(void))telnet_console_print)();
  /* cmp eax, 5 -> ja 0x132a26 */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 8] -> jl 0x1327be */
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 742, 0);
  system_exit(0);
  display_assert((char *)0x0029aad0, (char *)0x0029aa38, 747, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)ebp;
}


