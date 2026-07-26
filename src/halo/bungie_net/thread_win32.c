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

/* 0x81300 */
void FUN_00081300(void)
{
  int ebx = 0;
  int ecx = 0;

  display_assert((char *)0x00265de0, (char *)0x00265da0, 133, 0);
  system_exit(0);
  /* cmp ebx, ecx -> jb 0x8138a */
  display_assert((char *)0x00265dd8, (char *)0x00265da0, 134, 0);
  system_exit(0);
  FUN_00080fc0();
  error(0, (char *)0x00265e68);

  (void)ebx;
  (void)ecx;
}

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

/* 0x81480 */
void FUN_00081480(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test ebx, ebx -> je 0x8149e */
  /* test edi, edi -> jne 0x814bb */
  display_assert((char *)0x00265ef0, (char *)0x00265f08, 46, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x814db */
  crt_time((void *)0);
  FUN_001d9cf9();
  rand();
  FUN_001d9068();
  FUN_0007ff40();
  /* cmp eax, ecx -> ja 0x8158a */
  /* relift: cmp ecx, dword ptr [esi] -> jae 0x8158a */
  display_assert((char *)0x00265ed4, (char *)0x00265f08, 58, 0);
  system_exit(0);
  /* relift: cmp edx, dword ptr [ebx + 4] -> jb 0x815b7 */
  /* relift: cmp eax, dword ptr [ebx] -> jbe 0x815b7 */
  display_assert((char *)0x00265eb8, (char *)0x00265f08, 59, 0);
  system_exit(0);
  /* test dl, dl -> je 0x815d6 */
  /* cmp ecx, 0x20 -> jl 0x815c4 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x815f0 */
void FUN_000815f0(void)
{
  /* relift: no calls detected — manual review */
}

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
