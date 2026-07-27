#include <stdint.h>
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
    handle =
      (int)CreateThread(NULL, 0x4000, function, (void *)param, 4, &thread_id);
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

/* FUN_00081170 (0x81170) — XBE naked draft (batch 343). */
#if defined(__clang__)
static void (*const b81170_c80eb0)(void) = FUN_00080eb0;
static void (*const b81170_c81410)(void) = FUN_00081410;
static void (*const b81170_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81170_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00081170(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "subl %%esi, %%ebx\n\t"
      "subl %%esi, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $2, -0x4(%%ebp)\n\t"
      ".LFUN_00081170_1:\n\t"
      "pushl $0xffff\n\t"
      "call *%[c80eb0]\n\t"
      "pushl $0xffff\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c80eb0]\n\t"
      "imull %%edi, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $0xffffff, %%eax\n\t"
      "movl %%eax, (%%esi)\n\t"
      "jb .LFUN_00081170_1\n\t"
      "addl $-2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xff\n\t"
      "call *%[c81410]\n\t"
      "movl %%eax, (%%ebx,%%esi,1)\n\t"
      "movl (%%esi), %%eax\n\t"
      "decl %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xff\n\t"
      "call *%[c81410]\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, (%%edi,%%esi,1)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl (%%ebx,%%esi,1), %%eax\n\t"
      "subl $2, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jb .LFUN_00081170_2\n\t"
      "pushl $1\n\t"
      "pushl $0xa2\n\t"
      "pushl $0x265da0\n\t"
      "pushl $0x265e08\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081170_2:\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl (%%edi,%%esi,1), %%eax\n\t"
      "decl %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jb .LFUN_00081170_3\n\t"
      "pushl $1\n\t"
      "pushl $0xa3\n\t"
      "pushl $0x265da0\n\t"
      "pushl $0x265de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00081170_3:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $4, %%esi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_00081170_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c80eb0] "m"(b81170_c80eb0), [c81410] "m"(b81170_c81410), [assert] "m"(b81170_assert), [exitfn] "m"(b81170_exitfn)
      : "memory");
}
#else
#error "FUN_00081170: clang naked draft required"
#endif


/* FUN_00081250 (0x81250) — XBE naked draft (batch 336). */
#if defined(__clang__)
static void (*const b81250_c81090)(void) = FUN_00081090;
static void (*const b81250_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_00081250(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "subl %%eax, %%ecx\n\t"
      "subl %%eax, %%edx\n\t"
      "subl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "movl $2, -0x8(%%ebp)\n\t"
      "jmp .LFUN_00081250_2\n\t"
      ".LFUN_00081250_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00081250_2:\n\t"
      "movl (%%ecx,%%eax,1), %%edi\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl (%%edx,%%eax,1), %%esi\n\t"
      "call *%[c81090]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl %%eax, (%%edx,%%ecx,1)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_00081250_1\n\t"
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
      "pushl $0x265e2c\n\t"
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
      : [c81090] "m"(b81250_c81090), [c8f390] "m"(b81250_c8f390)
      : "memory");
}
#else
#error "FUN_00081250: clang naked draft required"
#endif


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


/* FUN_00081410 (0x81410) — readable C lift: seeded rand in [lo, lo+hi*r/32767]. */
unsigned int FUN_00081410(unsigned int lo, unsigned int hi)
{
  unsigned int r;
  double num;
  double den;

  if (*(unsigned char *)0x334980 == 0) {
    r = crt_time(0);
    ((void (*)(unsigned int))FUN_001d9cf9)(r);
    *(unsigned char *)0x334980 = 1;
  }
  r = (unsigned int)rand();
  num = (double)r * (double)hi;
  den = (double)lo + *(double *)0x265eb0;
  return lo + (unsigned int)(int)(num / den);
}
/* FUN_00081480 (0x81480) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void (*const b81480_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b81480_exitfn)(int) = system_exit;
static unsigned int (*const b81480_c1d9d28)(int *timer) = crt_time;
static void (*const b81480_c1d9cf9)(void) = FUN_001d9cf9;
static int (*const b81480_c1d9d06)(void) = rand;
static void (*const b81480_ftol)(void) = FUN_001d9068;
static void (*const b81480_c7ff40)(void) = (void (*)(void))(void *)FUN_0007ff40;

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


/* FUN_000815f0 (0x815f0) — readable C lift. */
void *FUN_000815f0(void)
{
  unsigned char *slot = (unsigned char *)0x334ab4;
  int index = 0;
  while (slot < (unsigned char *)0x334fb4) {
    if (*slot == 0) {
      void *entry = (void *)(0x334a90 + index * 40);
      *((unsigned char *)entry + 4) = 0;
      *(unsigned int *)entry = 0;
      *((unsigned char *)entry + 0x24) = 1;
      return entry;
    }
    slot += 0x28;
    index += 1;
  }
  return 0;
}

/* create_mutex (0x817e0) — readable C lift. */
char create_mutex(void **out)
{
  void *obj;
  char name[0x20];
  void *handle;
  unsigned int seq;

  if (out == NULL) {
    display_assert((const char *)0x265fb4, (const char *)0x265f5c, 0xb8, 1);
    system_exit(-1);
  }
  obj = FUN_000815f0();
  if (obj == NULL) {
    *out = NULL;
    return 0;
  }
  seq = *(unsigned int *)0x334988;
  *(unsigned int *)0x334988 = seq + 1;
  snprintf((char *)obj + 4, 0x20, (const char *)0x265fa8, seq);
  handle = CreateMutexA(NULL, 0, (const char *)obj + 4);
  *(void **)obj = handle;
  if (handle == NULL) {
    *out = NULL;
    return 0;
  }
  *out = obj;
  return 1;
}

/* FUN_00081910 (0x81910) — readable C lift. */
void FUN_00081910(void * a0)
{
  if (a0 == NULL) {
    display_assert((const char *)0x265fb4, (const char *)0x265f5c, 0xf0, 1);
    system_exit(-1);
  }
  if (*(uint8_t *)((char *)a0 + 0x24) == 0) {
    display_assert((const char *)0x265fc4, (const char *)0x265f5c, 0xf1, 1);
    system_exit(-1);
  }
  CloseHandle(*(void **)a0);
  *(uint8_t *)((char *)a0 + 0x4) = (uint8_t)0;
  *(uint32_t *)((char *)a0 + 0x0) = (uint32_t)0;
  *(uint8_t *)((char *)a0 + 0x24) = (uint8_t)0;
}

/* FUN_00081980 (0x81980) — readable C lift. */
void *FUN_00081980(void *src, unsigned short a, unsigned short b)
{
  void *dst;
  if (*(unsigned char *)0x335090 == 0) {
    display_assert((const char *)0x265fe4, (const char *)0x265ffc, 0x1e, 1);
    system_exit(-1);
  }
  if (src == NULL) {
    display_assert((const char *)0x265fdc, (const char *)0x265ffc, 0x1f, 1);
    system_exit(-1);
  }
  dst = debug_malloc(0x18, 0, (const char *)0x265ffc, 0x21);
  if (dst != NULL) {
    *(uint32_t *)((char *)dst + 0x0) = *(uint32_t *)((char *)src + 0x0);
    *(uint32_t *)((char *)dst + 0x4) = *(uint32_t *)((char *)src + 0x4);
    *(uint32_t *)((char *)dst + 0x8) = *(uint32_t *)((char *)src + 0x8);
    *(uint32_t *)((char *)dst + 0xc) = *(uint32_t *)((char *)src + 0xc);
    *(uint16_t *)((char *)dst + 0x10) = a;
    *(uint16_t *)((char *)dst + 0x12) = b;
    *(uint32_t *)((char *)dst + 0x14) = 0;
  }
  return dst;
}

/* FUN_00081a20 (0x81a20) — readable C lift from XBE leaf. */
void FUN_00081a20(void *ptr)
{
  extern char DAT_00265fe4[];
  extern char DAT_00265ffc[];
  extern char DAT_00265fdc[];

  if (*(unsigned char *)0x335090 == 0) {
    display_assert(DAT_00265fe4, DAT_00265ffc, 0x2f, true);
    system_exit(-1);
  }
  if (ptr == 0) {
    display_assert(DAT_00265fdc, DAT_00265ffc, 0x30, true);
    system_exit(-1);
  }
  debug_free(ptr, DAT_00265ffc, 0x32);
}



