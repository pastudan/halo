/*
 * bungie_net/thread_win32.c — lightweight thread pool for Xbox
 * XBE source: c:\halo\SOURCE\bungie_net\common\thread_win32.c
 *
 * Re-implemented functions (by XBE address, ascending):
 *   0x81630  thread_new
 *   0x81720  thread_is_done
 *   0x81770  thread_close
 *   0x81870  mutex_acquire (take_mutex)
 *   0x818d0  mutex_release (release_mutex)
 */

#include "common.h"

#define MAXIMUM_THREADS 32

/* XDK XAPI imports — called by name through kb.json __stdcall decls
 * (CreateThread 0x1cfd8c, SetThreadPriority 0x1cf999, ResumeThread 0x1cfaec,
 * CloseHandle 0x1cf900, GetExitCodeThread 0x1cfbbd, WaitForSingleObject
 * 0x1d0336, ReleaseMutex 0x1d0099). The former raw fn-pointer casts hid the
 * calling convention from kb.json audits (lift-learnings §30). */

/* WaitForSingleObject return codes */
#define WAIT_OBJECT_0 0x00
#define WAIT_ABANDONED 0x80

#define STILL_ACTIVE 0x103

typedef struct {
  int handle;
  char in_use;
  char pad[3];
} thread_slot_t;

/* 32-entry thread slot array at 0x334990 */
static thread_slot_t *thread_slots(void)
{
  return (thread_slot_t *)0x334990;
}

/*
 * thread_new — allocate a thread slot and create an Xbox thread.
 *
 * Searches the 32-slot pool for an unused entry, creates a suspended thread
 * via CreateThread, sets its priority based on priority_flags bits, then
 * resumes it. Returns true on success.
 *
 * Confirmed: assert "function" at line 0x6b, "thread_reference" at line 0x6c.
 * Confirmed: CREATE_SUSPENDED (0x4) flag, stack size 0x4000.
 * Confirmed: priority_flags bit 0x2 = below-normal (-1), bit 0x4 = above-normal
 * (+1).
 */
bool thread_new(int priority_flags, void *function, int param,
                void **thread_reference)
{
  thread_slot_t *slots = thread_slots();
  thread_slot_t *slot = NULL;
  int i;
  int thread_id;
  int handle;
  int priority;

  if (function == NULL) {
    display_assert("function",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0x6b,
                   1);
    system_exit(-1);
  }
  if (thread_reference == NULL) {
    display_assert("thread_reference",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0x6c,
                   1);
    system_exit(-1);
  }

  for (i = 0; i < MAXIMUM_THREADS; i++) {
    if (slots[i].in_use == 0) {
      slot = &slots[i];
      slot->handle = 0;
      slot->in_use = 1;
      break;
    }
  }

  if (slot != NULL) {
    handle = (int)CreateThread(NULL, 0x4000, function, (void *)param, 4, &thread_id);
    slot->handle = handle;
    if (handle != 0) {
      priority = 0;
      if ((priority_flags & 2) != 0) {
        priority = -1;
      } else if ((priority_flags & 4) != 0) {
        priority = 1;
      }
      if (SetThreadPriority(handle, priority) != 0) {
        if (ResumeThread(slot->handle) != -1) {
          *thread_reference = slot;
          return true;
        }
      }
      CloseHandle(slot->handle);
      *thread_reference = NULL;
      return false;
    }
  }

  *thread_reference = slot;
  return false;
}

/*
 * thread_is_done — check whether a thread has finished executing.
 *
 * Calls GetExitCodeThread and returns true if the thread exited (i.e. the
 * exit code is not STILL_ACTIVE).
 *
 * Confirmed: assert "thread_reference" at line 0x98.
 * Confirmed: compares exit code against 0x103 (STILL_ACTIVE).
 */
bool thread_is_done(void *thread_reference)
{
  thread_slot_t *slot = (thread_slot_t *)thread_reference;
  int exit_code;

  if (slot == NULL) {
    display_assert("thread_reference",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0x98,
                   1);
    system_exit(-1);
  }

  if (GetExitCodeThread(slot->handle, &exit_code) == 0) {
    return false;
  }
  if (exit_code == STILL_ACTIVE) {
    return false;
  }
  return true;
}

/*
 * thread_close — close a thread handle and release its slot.
 *
 * Confirmed: assert "thread_reference" at line 0xa8.
 * Confirmed: assert "thread_reference->in_use" at line 0xa9.
 * Confirmed: calls CloseHandle, then zeroes handle and in_use.
 */
void thread_close(void *thread_reference)
{
  thread_slot_t *slot = (thread_slot_t *)thread_reference;

  if (slot == NULL) {
    display_assert("thread_reference",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0xa8,
                   1);
    system_exit(-1);
  }
  if (slot->in_use == 0) {
    display_assert("thread_reference->in_use",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0xa9,
                   1);
    system_exit(-1);
  }

  CloseHandle(slot->handle);
  slot->handle = 0;
  slot->in_use = 0;
}

/*
 * take_mutex — acquire a mutex with a timeout.
 *
 * Calls WaitForSingleObject(*mutex_reference, timeout_ms). Returns true if the
 * wait succeeded (WAIT_OBJECT_0 = 0) or the mutex was abandoned (WAIT_ABANDONED
 * = 0x80). Returns false on timeout or any other error.
 *
 * Confirmed: assert "mutex_reference" at line 0xd3.
 * Confirmed: WaitForSingleObject at 0x1d0336; success codes 0x00 and 0x80.
 */
bool take_mutex(int *mutex_reference, int timeout_ms)
{
  int result;

  if (mutex_reference == NULL) {
    display_assert("mutex_reference",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0xd3,
                   1);
    system_exit(-1);
  }
  result = WaitForSingleObject(*mutex_reference, timeout_ms);
  if (result != WAIT_OBJECT_0 && result != WAIT_ABANDONED) {
    return false;
  }
  return true;
}

/*
 * release_mutex — release a mutex.
 *
 * Calls ReleaseMutex(*mutex_reference) via the XDK thunk at 0x1d0099
 * (NtReleaseMutant wrapper). Returns void.
 *
 * Confirmed: assert "mutex_reference" at line 0xe6.
 * Confirmed: ReleaseMutex at 0x1d0099.
 */
void release_mutex(int *mutex_reference)
{
  if (mutex_reference == NULL) {
    display_assert("mutex_reference",
                   "c:\\halo\\SOURCE\\bungie_net\\common\\thread_win32.c", 0xe6,
                   1);
    system_exit(-1);
  }
  ReleaseMutex(*mutex_reference);
}
/* --- thread_win32.obj batch drafts (2026-07-26) --- */

/* 0x81170 */
void FUN_00081170(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_00080eb0();
  FUN_00080eb0();
  FUN_00081410();
  FUN_00081410();
  /* cmp eax, ecx -> jb 0x8120c */
  display_assert((char *)0x00265e08, (char *)0x00265da0, 162, 0);
  system_exit(0);
  /* cmp eax, edx -> jb 0x81236 */
  display_assert((char *)0x00265de4, (char *)0x00265da0, 163, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x81250 */
void FUN_00081250(void)
{
  FUN_00081090();
  error(0, (char *)0x00265e2c);
}

/* FUN_00081300 (0x81300) — XBE naked draft (batch 320). */
#if defined(__clang__)
static void (*const b81300_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81300_exitfn)(int) = system_exit;
static void (*const b81300_c80fc0)(void) = FUN_00080fc0;
static void (*const b81300_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_00081300(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "subl %%esi, %%eax\n\t"
      "subl %%esi, %%ecx\n\t"
      "subl %%esi, %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00081300_2\n\t"
      ".LFUN_00081300_1:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_00081300_2:\n\t"
      "movl (%%eax,%%esi,1), %%ebx\n\t"
      "movl (%%esi), %%edi\n\t"
      "cmpl $2, %%edi\n\t"
      "movl (%%ecx,%%esi,1), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "ja .LFUN_00081300_3\n\t"
      "pushl $1\n\t"
      "pushl $0x85\n\t"
      "pushl $0x265da0\n\t"
      "pushl $0x265de0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081300_3:\n\t"
      "leal -0x1(%%edi), %%ecx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "jb .LFUN_00081300_4\n\t"
      "pushl $1\n\t"
      "pushl $0x86\n\t"
      "pushl $0x265da0\n\t"
      "pushl $0x265dd8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081300_4:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%edi, %%edx\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[c80fc0]\n\t"
      "movl %%eax, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "shrl $0x10, %%ecx\n\t"
      "andl $0xff0000, %%edx\n\t"
      "orl %%ecx, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0xff00, %%eax\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "shrl $8, %%edx\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "movl %%edx, (%%eax,%%esi,1)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00081300_1\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl (%%eax), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x265e68\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b81300_assert), [exitfn] "m"(b81300_exitfn), [c80fc0] "m"(b81300_c80fc0), [c8f390] "m"(b81300_c8f390)
      : "memory");
}
#else
#error "FUN_00081300: clang naked draft required"
#endif


/* 0x81410 */
void FUN_00081410(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x81434 */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();
  FUN_001d9068();

  (void)eax;
}

/* FUN_00081480 (0x81480) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void (*const b81480_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81480_exitfn)(int) = system_exit;
static unsigned int (*const b81480_c1d9d28)(int *timer) = crt_time;
static void (*const b81480_c1d9cf9)(void) = FUN_001d9cf9;
static int (*const b81480_c1d9d06)(void) = rand;
static void (*const b81480_ftol)(void) = FUN_001d9068;
static void (*const b81480_c7ff40)(void) = FUN_0007ff40;

__attribute__((naked, noinline))
void FUN_00081480(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "je .LFUN_00081480_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00081480_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00081480_2\n\t"
      ".LFUN_00081480_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x2e\n\t"
      "pushl $0x265f08\n\t"
      "pushl $0x265ef0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081480_2:\n\t"
      "movb 0x334980, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00081480_3\n\t"
      "pushl $0\n\t"
      "call *%[c1d9d28]\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9cf9]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x334980\n\t"
      ".LFUN_00081480_3:\n\t"
      "call *%[c1d9d06]\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "andl $0x80000000, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "fchs\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "andl $0x80000000, %%ecx\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "fchs\n\t"
      ".byte 0xde, 0xc1\n\t"
      "faddl 0x265eb0\n\t"
      ".byte 0xde, 0xf9\n\t"
      "call *%[ftol]\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "pushl %%edi\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c7ff40]\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "ja .LFUN_00081480_5\n\t"
      "jb .LFUN_00081480_4\n\t"
      "movl (%%edi), %%ecx\n\t"
      "cmpl (%%esi), %%ecx\n\t"
      "jae .LFUN_00081480_5\n\t"
      ".LFUN_00081480_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x3a\n\t"
      "pushl $0x265f08\n\t"
      "pushl $0x265ed4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081480_5:\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "cmpl 0x4(%%ebx), %%edx\n\t"
      "jb .LFUN_00081480_7\n\t"
      "ja .LFUN_00081480_6\n\t"
      "movl (%%edi), %%eax\n\t"
      "cmpl (%%ebx), %%eax\n\t"
      "jbe .LFUN_00081480_7\n\t"
      ".LFUN_00081480_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "pushl $0x265f08\n\t"
      "pushl $0x265eb8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081480_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b81480_assert), [exitfn] "m"(b81480_exitfn), [c1d9d28] "m"(b81480_c1d9d28), [c1d9cf9] "m"(b81480_c1d9cf9), [c1d9d06] "m"(b81480_c1d9d06), [ftol] "m"(b81480_ftol), [c7ff40] "m"(b81480_c7ff40)
      : "memory");
}
#else
#error "FUN_00081480: clang naked draft required"
#endif


/* FUN_000815f0 (0x815f0) — XBE naked draft (batch 328). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_000815f0(void)
{
  __asm__ volatile(
      "xorl %%eax, %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x334ab4, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000815f0_1:\n\t"
      "cmpb $0, (%%ecx)\n\t"
      "je .LFUN_000815f0_2\n\t"
      "addl $0x28, %%ecx\n\t"
      "incl %%edx\n\t"
      "cmpl $0x334fb4, %%ecx\n\t"
      "jl .LFUN_000815f0_1\n\t"
      "ret\n\t"
      ".LFUN_000815f0_2:\n\t"
      "leal (%%edx,%%edx,4), %%eax\n\t"
      "leal 0x334a90(,%%eax,8), %%eax\n\t"
      "movb $0, 0x4(%%eax)\n\t"
      "movl $0, (%%eax)\n\t"
      "movb $1, 0x24(%%eax)\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_000815f0: clang naked draft required"
#endif


/* 0x817e0 */
void create_mutex(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 184, 0);
  system_exit(0);
  FUN_000815f0();
  /* test esi, esi -> je 0x8185c */
  /* mem[0x00334988] = eax */
  snprintf((char *)(uintptr_t)edi, 32, (char *)0);
  CreateMutexA();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x81910 */
void FUN_00081910(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x8193b */
  display_assert((char *)0x00265fb4, (char *)0x00265f5c, 240, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x81962 */
  display_assert((char *)0x00265fc4, (char *)0x00265f5c, 241, 0);
  system_exit(0);
  CloseHandle(0);

  (void)eax;
  (void)esi;
}

/* 0x81980 */
void FUN_00081980(void)
{
  int eax = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> jne 0x819a9 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 30, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x819ce */
  display_assert((char *)0x00265fdc, (char *)0x00265ffc, 31, 0);
  system_exit(0);
  debug_malloc(24, 0, (char *)0x00265ffc, 33);
  /* test eax, eax -> je 0x81a14 */

  (void)eax;
  (void)esi;
}

/* 0x81a20 */
void FUN_00081a20(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> jne 0x81a49 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 47, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x81a6e */
  display_assert((char *)0x00265fdc, (char *)0x00265ffc, 48, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)esi, (char *)0x00265ffc, 50);
  display_assert((char *)0x00266090, (char *)0x00265ffc, 59, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x81add */
  display_assert((char *)0x0026608c, (char *)0x00265ffc, 60, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x81b03 */
  display_assert((char *)0x00265fe4, (char *)0x00265ffc, 61, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81b27 */
  display_assert((char *)0x00266060, (char *)0x00265ffc, 63, 0);
  system_exit(0);
  /* relift: cmp word ptr [edi + 0x10], 4 -> je 0x81b4b */
  display_assert((char *)0x00266034, (char *)0x00265ffc, 64, 0);
  system_exit(0);
  csmemcmp((void *)(uintptr_t)esi, (void *)(uintptr_t)edi, 0);
  /* test eax, eax -> jne 0x81b80 */
  /* relift: cmp (int16_t)eax, word ptr [edi + 0x12] -> jne 0x81b80 */
  /* test esi, esi -> jne 0x81bb8 */
  display_assert((char *)0x002660f8, (char *)0x00265ffc, 74, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x10], 4 -> je 0x81bdc */
  display_assert((char *)0x002660cc, (char *)0x00265ffc, 75, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 4 -> jne 0x81c24 */
  snprintf((char *)0x00334f90, 256, (char *)0x002660b8);
  /* cmp (int16_t)eax, 0x10 -> jne 0x81c6d */
  snprintf((char *)0x00334f90, 256, (char *)0x00266094);
  /* cmp eax, 0x17 -> ja 0x81d42 */
  /* test esi, esi -> jne 0x81de1 */
  display_assert((char *)0x00266450, (char *)0x00266458, 57, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x81df6 */
  /* mem[0x005ab210] = ecx */
  /* mem[0x005ab214] = edx */
  /* mem[0x005ab218] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
