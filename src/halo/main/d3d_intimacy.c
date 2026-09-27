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

/* FUN_001cf840 (0x1cf840) — readable C lift. */
char FUN_001cf840(int object_handle)
{
  char *obj;

  obj = (char *)object_get_and_verify_type(object_handle, 0x800);
  *(uint32_t *)(obj + 4) |= 0x40000u;
  return 1;
}

/* CloseHandle (0x1cf900) — Capstone tip: NtClose IAT success → 1. */
int __stdcall CloseHandle(int handle)
{
  int status;

  status = (*(int(__stdcall **)(int))0x253090)(handle);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}

/* XapiCallThreadNotifyRoutines (0x1cf944) — Capstone tip: empty notify list. */
void __stdcall XapiCallThreadNotifyRoutines(int create)
{
  void *lock;
  void *node;
  void *head;

  lock = (void *)0x32fd00;
  (*(void(__stdcall **)(void *))0x25309c)(lock);
  node = *(void **)0x32fd1c;
  head = (void *)0x32fd1c;
  while (node != head) {
    void *cur = node;
    node = *(void **)node;
    (*(void(__stdcall **)(int))((char *)cur + 8))(create);
  }
  (*(void(__stdcall **)(void *))0x253098)(lock);
}


/* UnhandledExceptionFilter (0x1cf97c) — readable C lift from XBE leaf. */
int UnhandledExceptionFilter(void *exception_info)
{
  int (*handler)(void *);
  int result;

  handler = *(int (**)(void *))0x632a2c;
  if (!handler) {
    return 0;
  }
  result = handler(exception_info);
  if (result != -1) {
    return 0;
  }
  return result;
}



/* SetThreadPriority (0x1cf999) — Capstone tip: ObReference fail → 0. */
int __stdcall SetThreadPriority(int thread_handle, int priority)
{
  int status;

  (void)priority;
  status = (*(int(__stdcall **)(int, void *, int *))0x2530a8)(
      thread_handle, *(void **)0x2530ac, &thread_handle);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0;
  }
  return 1;
}

/* GetThreadPriority (0x1cf9eb) — Capstone tip: ObReference fail → 0x7fffffff. */
int __stdcall GetThreadPriority(int thread_handle)
{
  int status;

  status = (*(int(__stdcall **)(int, void *, int *))0x2530a8)(
      thread_handle, *(void **)0x2530ac, &thread_handle);
  if (status < 0) {
    XapiSetLastNTError(status);
    return 0x7fffffff;
  }
  return 0;
}


