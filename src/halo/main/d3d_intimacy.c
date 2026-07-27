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

/* XapiCallThreadNotifyRoutines (0x1cf944) — XBE naked draft (batch 165). */
#if defined(__clang__)


__attribute__((naked, noinline))
void XapiCallThreadNotifyRoutines(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0x32fd00, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *0x25309c\n\t"
      "movl 0x32fd1c, %%esi\n\t"
      "movl $0x32fd1c, %%edi\n\t"
      "jmp .LXapiCallThreadNotifyRoutines_2\n\t"
      ".LXapiCallThreadNotifyRoutines_1:\n\t"
      "pushl 0x10(%%esp)\n\t"
      "movl %%esi, %%eax\n\t"
      "movl (%%esi), %%esi\n\t"
      "call *0x8(%%eax)\n\t"
      ".LXapiCallThreadNotifyRoutines_2:\n\t"
      "cmpl %%edi, %%esi\n\t"
      "jne .LXapiCallThreadNotifyRoutines_1\n\t"
      "pushl %%ebx\n\t"
      "call *0x253098\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "XapiCallThreadNotifyRoutines: clang naked draft required"
#endif


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

/* GetThreadPriority (0x1cf9eb) — XBE naked draft (batch 166). */
#if defined(__clang__)
static void __stdcall (*const b1cf9eb_c1d2296)(int status) = XapiSetLastNTError;

__attribute__((naked, noinline))
void GetThreadPriority(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "leal 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl 0x2530ac\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530a8\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LGetThreadPriority_4\n\t"
      "pushl %%esi\n\t"
      "pushl 0x8(%%ebp)\n\t"
      "call *0x2530b0\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl $0x10, %%esi\n\t"
      "jne .LGetThreadPriority_1\n\t"
      "pushl $0xf\n\t"
      "jmp .LGetThreadPriority_2\n\t"
      ".LGetThreadPriority_1:\n\t"
      "cmpl $-0x10, %%esi\n\t"
      "jne .LGetThreadPriority_3\n\t"
      "pushl $-0xf\n\t"
      ".LGetThreadPriority_2:\n\t"
      "popl %%esi\n\t"
      ".LGetThreadPriority_3:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "call *0x2530a0\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "jmp .LGetThreadPriority_5\n\t"
      ".LGetThreadPriority_4:\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d2296]\n\t"
      "movl $0x7fffffff, %%eax\n\t"
      ".LGetThreadPriority_5:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d2296] "m"(b1cf9eb_c1d2296)
      : "memory");
}
#else
#error "GetThreadPriority: clang naked draft required"
#endif

