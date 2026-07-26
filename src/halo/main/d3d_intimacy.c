/* Find the D3D flipcount by probing internal D3D state (0x1cf880).
 * Validates the D3D context: interrupts enabled, vblank callback matches,
 * and vblank count is sane. Returns pointer to the flipcount variable. */
int *d3d_find_flipcount(void)
{
  if (*(int *)0x1fdebc != 1) {
    error(2,
          "### WARNING: direct3d context unreadable "
          "(interrupts 0x%08X != 0x00000001)...",
          *(unsigned int *)0x1fdebc);
  } else {
    if (*(int *)0x1fdffc != (int)0x101cd0) {
      error(2,
            "### WARNING: direct3d context unreadable "
            "(callback 0x%08X != 0x%08X)...",
            *(int *)0x1fdffc, 0x101cd0);
    } else {
      if (*(unsigned int *)0x1fe634 <= 0x10000)
        return (int *)0x1fe028;
      error(2,
            "### WARNING: direct3d context unreadable "
            "(vblank 0x%08X greater than 0x00010000)...",
            *(unsigned int *)0x1fe634);
    }
  }
  display_assert(
    "### FATAL ERROR LOCATING DIRECT3D FLIPCOUNT, THIS IS HORRIBLY BAD",
    "c:\\halo\\SOURCE\\main\\d3d_intimacy.cpp", 0x35, 1);
  system_exit(-1);
  return NULL;
}
/* --- d3d_intimacy.obj batch drafts (2026-07-26) --- */

/* 0x1cf840 */
void FUN_001cf840(void)
{
  object_get_and_verify_type(0, 2048);
}

/* 0x1cf900 */
int __stdcall CloseHandle(int handle)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cf913 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cf939 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1cf944 */
void XapiCallThreadNotifyRoutines(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1cf97c */
void UnhandledExceptionFilter(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1cf999 */
int __stdcall SetThreadPriority(int thread_handle, int priority)
{
  int eax = 0;

  /* test eax, eax -> jl 0x1cf9df */
  /* cmp eax, 0xf -> jne 0x1cf9bf */
  /* cmp eax, -0xf -> jne 0x1cf9c7 */
  XapiSetLastNTError(0);
  return 0;

  (void)eax;
}

/* 0x1cf9eb */
void GetThreadPriority(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test eax, eax -> jl 0x1cfa30 */
  /* cmp esi, 0x10 -> jne 0x1cfa1a */
  /* cmp esi, -0x10 -> jne 0x1cfa22 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cfa79 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jl 0x1cfaba */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1cfae5 */
  XapiSetLastNTError(0);
  /* test eax, eax -> jge 0x1cfb0b */
  XapiSetLastNTError(0);
  /* cmp ecx, 0xf -> jbe 0x1cfb45 */
  XapiCallThreadNotifyRoutines();
  /* test eax, eax -> jl 0x1cfbfd */
  /* relift: cmp byte ptr [ecx + 4], 0 -> je 0x1cfbe8 */
  XapiSetLastNTError(0);
  /* mem[0x00632a2c] = ecx */
  /* cmp eax, ebx -> jl 0x1cfc97 */
  XapiSetLastNTError(0);
  /* relift: cmp dword ptr [esp + 0xc], 0 -> je 0x1cfcd4 */
  /* mem[0x0032fd20] = eax */
  FUN_001dd5c8();
  /* test ecx, ecx -> je 0x1cfd59 */
  XapiCallThreadNotifyRoutines();
  XapiCallThreadNotifyRoutines();
  UnhandledExceptionFilter();
  /* test eax, eax -> jne 0x1cfd9b */
  /* test eax, eax -> jge 0x1cfdd9 */
  XapiSetLastNTError(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}
