/* kb object stubs -> xdk/xnet/wsock.c */

/* --- XNET:wsock.obj batch drafts (2026-07-26) --- */

/* 0x222df7 */
int FUN_00222df7(void *key)
{
  (void)key;
  return 0;
}

/* 0x22486b */
int xnet_getpeername(int socket, void *name, int *namelen)
{
  (void)socket;
  (void)name;
  (void)namelen;
  return 0;
}

/* 0x224876 */
int xnet_getsockname(int socket, void *name, int *namelen)
{
  (void)socket;
  (void)name;
  (void)namelen;
  return 0;
}

/* 0x225197 */
int xnet_bind(int socket, void *name, int namelen)
{
  (void)socket;
  (void)name;
  (void)namelen;
  return 0;
}

/* 0x225bb6 */
int xnet_recv(int socket, void *buf, int len, int flags)
{
  (void)socket;
  (void)buf;
  (void)len;
  (void)flags;
  return 0;
}

/* 0x225c20 */
int xnet_send(int socket, const char *buf, int len, int flags)
{
  (void)socket;
  (void)buf;
  (void)len;
  (void)flags;
  return 0;
}

/* 0x225cc6 */
int xnet_closesocket(int socket)
{
  (void)socket;
  return 0;
}

/* 0x225cd1 */
int xnet_recvfrom(int socket, void *buf, int len, int flags, void *from, int *fromlen)
{
  (void)socket;
  (void)buf;
  (void)len;
  (void)flags;
  (void)from;
  (void)fromlen;
  return 0;
}
