/* Tip-only compile unit for wsock Unicorn proofs. */

/* FUN_00222de0 (0x222de0) — Capstone tip: xnet not inited → WSAENETDOWN 0x276d. */
int __stdcall FUN_00222de0(void *a, void *b)
{
  (void)a; (void)b;
  if (*(void **)0x4ee4b0 == 0)
    return 0x276d;
  *(volatile int *)0 = 0;
  return 0;
}

/* FUN_00222df7 (0x222df7) — Capstone tip: xnet not inited → 0x276d. */
int __stdcall FUN_00222df7(void *key)
{
  (void)key;
  if (*(void **)0x4ee4b0 == 0)
    return 0x276d;
  *(volatile int *)0 = 0;
  return 0;
}

/* xnet_xnaddr_to_inaddr (0x222e31) — Capstone tip: xnet not inited → 0x276d. */
int __stdcall xnet_xnaddr_to_inaddr(void *xnaddr, void *key, unsigned *in_addr)
{
  (void)xnaddr; (void)key; (void)in_addr;
  if (*(void **)0x4ee4b0 == 0)
    return 0x276d;
  *(volatile int *)0 = 0;
  return 0;
}

/* xnet_fd_isset (0x2235f3) — Capstone tip: scan fd_set bits. */
int __stdcall xnet_fd_isset(int fd, void *fds_v)
{
  unsigned *fds = (unsigned *)fds_v;
  unsigned n = fds[0] & 0xffff;
  unsigned *p;
  if (n == 0)
    return 0;
  p = fds + n; /* &fds[n] then -1 in loop start: lea ecx,[ecx+eax*4+4]; sub ecx,4 */
  while (n) {
    if (*p == (unsigned)fd)
      return 1;
    p--;
    n--;
  }
  return 0;
}
