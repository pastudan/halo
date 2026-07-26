/*
 * game_state_xbox.c — Xbox-specific game state buffer and file management.
 *
 * Corresponds to game_state_xbox.obj (game_state_xbox.c in the original
 * source tree at c:\halo\SOURCE\saved games\game_state_xbox.c).
 */

#ifdef XDK_BUILD
void __stdcall MmFreeContiguousMemory(void *BaseAddress);
#else
#include "xbox.h"
#endif

/* Xbox kernel file I/O wrappers (stdcall) */
typedef bool(__stdcall *close_handle_fn)(int handle);
typedef int(__stdcall *set_file_pointer_fn)(int handle, int distance_to_move,
                                            int *distance_high,
                                            uint32_t move_method);
typedef bool(__stdcall *read_file_fn)(int handle, void *buffer,
                                      uint32_t number_of_bytes_to_read,
                                      int *number_of_bytes_read,
                                      void *overlapped);
typedef bool(__stdcall *write_file_fn)(int handle, void *buffer,
                                       uint32_t number_of_bytes_to_write,
                                       int *number_of_bytes_written,
                                       void *overlapped);
typedef bool(__stdcall *delete_file_fn)(const char *path);
typedef int (*open_save_file_fn)(int param_1);
typedef char (*get_save_path_fn)(short index, void *out_path);
typedef int (*get_last_error_fn)(void);
typedef void (*crc_begin_fn)(uint32_t *checksum);

#define XCloseHandle ((close_handle_fn)0x1cf900)
#define XSetFilePointer ((set_file_pointer_fn)0x1d1610)
#define XReadFile ((read_file_fn)0x1d13c9)
#define XWriteFile ((write_file_fn)0x1d14b6)
#define XDeleteFile ((delete_file_fn)0x1d0ff9)
#define xapi_GetLastError ((get_last_error_fn)0x1d2240)
#define xbox_game_state_open_file ((open_save_file_fn)0x1c0780)
#define xbox_saved_game_get_path ((get_save_path_fn)0xe0bf0)
#define crc_checksum_begin ((crc_begin_fn)0x1190b0)

/* xbox_game_state_globals layout (at 0x4ea9b0):
 *   +0x00 (0x4ea9b0): char  buffer_allocated
 *   +0x04 (0x4ea9b4): void* buffer
 *   +0x08 (0x4ea9b8): int   buffer_size
 *   +0x0C (0x4ea9bc): char  file_open
 *   +0x0D (0x4ea9bd): char  file_written
 *   +0x10 (0x4ea9c0): int   file_handle
 */

/* 0x1c0220
 * Release the contiguous physical memory buffer allocated for Xbox game-state
 * saves. Asserts that the buffer is marked allocated before freeing, then
 * clears the flag. The globals at 0x4ea9b0 (buffer_allocated flag) and
 * 0x4ea9b4 (buffer pointer) belong to xbox_game_state_globals.
 */
void xbox_game_state_dispose_buffer(void)
{
  assert_halt(*(char *)0x4ea9b0);
  MmFreeContiguousMemory(*(void **)0x4ea9b4);
  *(char *)0x4ea9b0 = 0;
}

/* 0x1c0330
 * Close the Xbox game-state file handle. Asserts that the file is marked open,
 * then calls the close-file routine and clears the open flag.
 */
void xbox_game_state_close_file(void)
{
  assert_halt(*(char *)0x4ea9bc);
  XCloseHandle(*(int *)0x4ea9c0);
  *(char *)0x4ea9bc = 0;
}

/* 0x1c0370
 * Write the game-state buffer to the save file. Asserts that both the buffer
 * is allocated and the file is open, seeks to the beginning, then writes the
 * entire buffer. Sets the file_written flag on success.
 */
char game_state_write_to_file(void)
{
  int bytes_written;

  assert_halt(*(char *)0x4ea9b0); /* buffer_allocated */
  assert_halt(*(char *)0x4ea9bc); /* file_open */

  if (XSetFilePointer(*(int *)0x4ea9c0, 0, NULL, 0) != -1) {
    if (XWriteFile(*(int *)0x4ea9c0, *(void **)0x4ea9b4, *(uint32_t *)0x4ea9b8,
                   &bytes_written, NULL) &&
        bytes_written == *(int *)0x4ea9b8) {
      *(char *)0x4ea9bd = 1; /* file_written */
      return 1;
    }
  }

  display_assert(csprintf((char *)0x5ab100,
                          "couldn't write saved game file (#%d)",
                          xapi_GetLastError()),
                 "c:\\halo\\SOURCE\\saved games\\game_state_xbox.c", 0x84, 1);
  system_exit(-1);
  return 0;
}

/* 0x1c0720 — return the Xbox save-game filename.
 * Used as the leaf file name when constructing the save path. */
const char *FUN_001c0720(void)
{
  return "savegame.bin";
}

/* 0x1c0750
 * Delete the local player's save game file. Gets the profile directory
 * path and, if valid, deletes the file at that path. */
void FUN_001c0750(void)
{
  char path_buffer[256];

  if (xbox_saved_game_get_path(0, path_buffer)) {
    XDeleteFile(path_buffer);
  }
}

/* 0x1c0910
 * Read and verify a saved game from persistent storage. Reads header first,
 * then checksums the remaining data in 128KB chunks. Returns 1 on success.
 *
 * param_1 (header):      destination buffer for the header portion
 * param_2 (scratch):     pointer to a uint32_t holding the expected checksum;
 *                         zeroed before CRC computation and restored on
 * mismatch param_3 (header_size): byte count for the header read param_4
 * (buffer_size): total byte count (header + body) to checksum param_5 (flags):
 * optional output byte; set to 1 if checksum mismatch with a non-zero expected
 * checksum
 */
char game_state_read_header_from_persistent_storage(void *header,
                                                    uint32_t *scratch,
                                                    int header_size,
                                                    int buffer_size,
                                                    char *flags)
{
  static char scratch_buffer[0x20000]; /* 128KB — avoids _chkstk */
  char path_buffer[0x100];

  int file_handle;
  char result;
  int bytes_transferred;
  uint32_t checksum;
  uint32_t saved_checksum;
  int remaining;
  int chunk;

  file_handle = xbox_game_state_open_file(0);
  result = 0;

  if (flags != NULL) {
    *flags = 0;
  }

  if (file_handle == -1) {
    return result;
  }

  /* Seek to beginning */
  if (XSetFilePointer(file_handle, 0, NULL, 0) == -1) {
    goto read_error;
  }

  /* Read the header */
  if (!XReadFile(file_handle, header, (uint32_t)header_size, &bytes_transferred,
                 NULL) ||
      bytes_transferred != header_size) {
    goto read_error;
  }

  /* Save the expected checksum and prepare for computation */
  saved_checksum = *scratch;
  crc_checksum_begin(&checksum);
  *scratch = 0;
  crc_checksum_buffer(&checksum, header, header_size);

  /* Read and checksum remaining data in 128KB chunks */
  remaining = buffer_size - header_size;
  while (remaining > 0) {
    chunk = remaining;
    if ((unsigned int)remaining > 0x20000) {
      chunk = 0x20000;
    }

    if (XReadFile(file_handle, scratch_buffer, (uint32_t)chunk,
                  &bytes_transferred, NULL) &&
        bytes_transferred == chunk) {
      crc_checksum_buffer(&checksum, scratch_buffer, chunk);
    }

    sound_idle(); /* sound_pump / idle tick */
    remaining -= chunk;
  }

  /* Verify checksum */
  if (checksum == saved_checksum) {
    result = 1;
    XCloseHandle(file_handle);
    return result;
  }

  /* Checksum mismatch */
  if (flags != NULL && saved_checksum != 0) {
    *flags = 1;
  }
  error(2, "checksum failed on persistent storage");
  XCloseHandle(file_handle);
  return result;

read_error:
  display_assert(csprintf((char *)0x5ab100,
                          "couldn't read header from persistent storage (#%d)",
                          xapi_GetLastError()),
                 "c:\\halo\\SOURCE\\saved games\\game_state_xbox.c", 0x12a, 1);
  system_exit(-1);

  /* After the fatal assert, attempt to delete the corrupt save file */
  if (xbox_saved_game_get_path(0, path_buffer)) {
    XDeleteFile(path_buffer);
  }
  XCloseHandle(file_handle);
  return result;
}

/* 0x1c0c20
 * Read game-state data from persistent storage into a caller-supplied buffer.
 * Opens the save file, seeks to the beginning, reads `size` bytes into `dst`,
 * and verifies the byte count. On failure, asserts with the last error code,
 * exits, and attempts to delete the corrupt save file.
 */
void FUN_001c0c20(void *dst, int size)
{
  char path_buffer[0x100];
  int bytes_read;

  int file_handle = xbox_game_state_open_file(0);
  if (file_handle == -1) {
    return;
  }

  if (XSetFilePointer(file_handle, 0, NULL, 0) == -1 ||
      !XReadFile(file_handle, dst, size, &bytes_read, NULL) ||
      bytes_read != size) {
    display_assert(
      csprintf((char *)0x5ab100, "failed to read from persistent storage (#%d)",
               xapi_GetLastError()),
      "c:\\halo\\SOURCE\\saved games\\game_state_xbox.c", 0x17f, 1);
    system_exit(-1);

    if (xbox_saved_game_get_path(0, path_buffer)) {
      XDeleteFile(path_buffer);
    }
  }

  XCloseHandle(file_handle);
}

/* 0x1c0cd0
 * Close the file handle obtained from xbox_game_state_open_file for a given
 * parameter. Opens the file, and if valid, closes the resulting handle.
 */
void FUN_001c0cd0(int param_1)
{
  int handle;

  handle = xbox_game_state_open_file(param_1);
  if (handle != -1) {
    XCloseHandle(handle);
  }
}

/* 0x1c0cf0
 * Wait for any in-flight asynchronous player profile writes to complete, then
 * clear the profile write state buffer at 0x4ea9c8 (0x6c bytes).
 */
void FUN_001c0cf0(void)
{
  if (*(int *)0x4eaa2c != 0) {
    error(2, "waiting for asynchronous player profile writes to finish...");
    do {
      /* spin until the async write thread signals completion */
    } while (!thread_is_done(*(void **)0x4eaa2c));
    thread_close(*(void **)0x4eaa2c);
    *(int *)0x4eaa2c = 0;
  }
  csmemset((void *)0x4ea9c8, 0, 0x6c);
}

/* 0x1c0d70
 * Delete a player profile by index. Calls the saved-game file deletion
 * routine and logs an error if it fails.
 */
void FUN_001c0d70(int param_1)
{
  if (param_1 != -1) {
    if (!delete_enumerated_saved_game_file(param_1)) {
      error(2, "player_profile_delete() failed (profile index= #0x%lX)",
            param_1);
    }
  }
}
/* --- game_state_xbox.obj batch drafts (2026-07-26) --- */

/* 0x1c0260 */
void game_state_create_or_open_file(void)
{
  int eax = 0;

  /* test (char)eax, (char)eax -> jne 0x1c0286 */
  display_assert((char *)0x002b9ba0, (char *)0x002b9b70, 86, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x1c02ac */
  display_assert((char *)0x002b9c0c, (char *)0x002b9b70, 87, 0);
  system_exit(0);
  CreateFileA((char *)0x002b9bfc, 0xc0000000, 0, 0, 0, 0x28000000, 0);
  /* mem[0x004ea9c0] = eax */
  SetFilePointer(0, 0x00380000, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c02fd */
  SetEndOfFile(0);
  /* test eax, eax -> je 0x1c02fd */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b9bcc);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
}

/* 0x1c0450 */
void game_state_read_from_file(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test (char)eax, (char)eax -> jne 0x1c0480 */
  display_assert((char *)0x002b9ba0, (char *)0x002b9b70, 144, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1c04a9 */
  display_assert((char *)0x002b9c30, (char *)0x002b9b70, 145, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1c04db */
  /* test (char)eax, (char)eax -> jne 0x1c04db */
  display_assert((char *)0x002b9ca0, (char *)0x002b9b70, 146, 0);
  system_exit(0);
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c0526 */
  ReadFile(0, (void *)(uintptr_t)eax, edx, (void *)(uintptr_t)ecx, (void *)0);
  /* test eax, eax -> je 0x1c0526 */
  /* relift: cmp edx, dword ptr [0x4ea9b8] -> jne 0x1c0526 */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b9c7c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1c0570 */
void game_state_write_core(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  CreateDirectoryA((char *)0x002b9cf4, 0);
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b9ce8);
  CreateFileA((char *)(uintptr_t)edx, 0x40000000, 0, 0, 0, 128, 0);
  /* cmp esi, -1 -> je 0x1c05e7 */
  WriteFile(0, (void *)(uintptr_t)ecx, edi, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1c05e6 */
  /* relift: cmp dword ptr [ebp - 4], edi -> jne 0x1c05e6 */
  CloseHandle(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c0600 */
void game_state_read_core_header(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b9ce8);
  CreateFileA((char *)(uintptr_t)edx, 0x80000000, 0, 0, 0, 128, 0);
  /* cmp esi, -1 -> je 0x1c066b */
  ReadFile(0, (void *)(uintptr_t)ecx, edi, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1c066a */
  /* relift: cmp dword ptr [ebp - 4], edi -> jne 0x1c066a */
  CloseHandle(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c0680 */
void game_state_read_core(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002b9ce8);
  CreateFileA((char *)(uintptr_t)edx, 0x80000000, 0, 0, 0, 128, 0);
  /* cmp esi, -1 -> je 0x1c06e5 */
  ReadFile(0, (void *)(uintptr_t)ecx, edi, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1c06e5 */
  /* relift: cmp dword ptr [ebp - 4], edi -> je 0x1c0705 */
  display_assert((char *)0x002b9cfc, (char *)0x002b9b70, 226, 0);
  system_exit(0);
  CloseHandle(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c0780 */
int FUN_001c0780(int param_1)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_001d90e0();
  player_ui_get_path_to_local_player_profile_directory();
  /* test (char)eax, (char)eax -> je 0x1c08ad */
  player_ui_get_path_to_local_player_profile_directory();
  FUN_0008dc30((char *)(uintptr_t)eax, (char *)0x002b9d34);
  CreateFileA((char *)(uintptr_t)ecx, 0xc0000000, 0, 0, 0, 0, 0);
  /* cmp esi, -1 -> je 0x1c08c7 */
  GetFileSize(0, (void *)0);
  /* cmp eax, 0x380000 -> je 0x1c0904 */
  csmemset((void *)(uintptr_t)edx, 0, 16384);
  WriteFile(0, (void *)(uintptr_t)ecx, 16384, (void *)(uintptr_t)eax, (void *)0);
  /* test eax, eax -> je 0x1c086d */
  /* relift: cmp dword ptr [ebp + 8], 0x4000 -> jne 0x1c086d */
  SetFilePointer(0, 0x00380000, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c086d */
  SetEndOfFile(0);
  /* test eax, eax -> jne 0x1c0904 */
  csprintf((char *)0x005ab100, (char *)0x002b9d74);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_001c0750();
  CloseHandle(0);
  csstrcpy((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  csprintf((char *)0x005ab100, (char *)0x002b9d44);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* game_state_write_to_persistent_storage (0x1c0ac0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static int (*const b1c0ac0_c1c0780)(int param_1) = FUN_001c0780;
static void (*const b1c0ac0_c1190b0)(uint32_t *checksum) = crc_new;
static void (*const b1c0ac0_c119100)(uint32_t *checksum, void *data, int size) = crc_checksum_buffer;
static void (*const b1c0ac0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c0ac0_exitfn)(int) = system_exit;
static void * (*const b1c0ac0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void *(*const b1c0ac0_memset)(void *, int, unsigned int) = csmemset;
static unsigned int __stdcall (*const b1c0ac0_c1d1610)(int handle, int distance, int *distance_high, unsigned int method) = SetFilePointer;
static int __stdcall (*const b1c0ac0_c1d14b6)(int handle, void *buffer, uint32_t size, uint32_t *bytes_written, void *overlapped) = WriteFile;
static int (*const b1c0ac0_c1d2240)(void) = xapi_GetLastError;
static char * (*const b1c0ac0_c8d9d0)(char *buffer, const char *format, ...) = csprintf;
static void (*const b1c0ac0_ce0bf0)(void) = player_ui_get_path_to_local_player_profile_directory;
static bool __stdcall (*const b1c0ac0_c1d0ff9)(const char *path) = DeleteFileA;
static int __stdcall (*const b1c0ac0_c1cf900)(int handle) = CloseHandle;

__attribute__((naked, noinline))
void game_state_write_to_persistent_storage(int param_1 __attribute__((unused)), void *param_2 __attribute__((unused)), int param_3 __attribute__((unused)), int param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x908, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c1c0780]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lgame_state_write_to_persistent_storage_4\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl $0, (%%ebx)\n\t"
      "call *%[c1190b0]\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0x345000\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c119100]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edx, (%%ebx)\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $0x800, %%ebx\n\t"
      "jb .Lgame_state_write_to_persistent_storage_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14d\n\t"
      "pushl $0x2b9b70\n\t"
      "pushl $0x2b9e24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lgame_state_write_to_persistent_storage_1:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x908(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[memset]\n\t"
      "addl $0x18, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d1610]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lgame_state_write_to_persistent_storage_2\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d14b6]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lgame_state_write_to_persistent_storage_2\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "cmpl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lgame_state_write_to_persistent_storage_2\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d1610]\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lgame_state_write_to_persistent_storage_2\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x908(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1d14b6]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lgame_state_write_to_persistent_storage_2\n\t"
      "cmpl %%ebx, -0x4(%%ebp)\n\t"
      "je .Lgame_state_write_to_persistent_storage_3\n\t"
      ".Lgame_state_write_to_persistent_storage_2:\n\t"
      "pushl $1\n\t"
      "pushl $0x15f\n\t"
      "pushl $0x2b9b70\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b9df8\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "leal -0x108(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[ce0bf0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lgame_state_write_to_persistent_storage_3\n\t"
      "leal -0x108(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0ff9]\n\t"
      ".Lgame_state_write_to_persistent_storage_3:\n\t"
      "pushl %%ebx\n\t"
      "leal -0x908(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "call *%[c1cf900]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lgame_state_write_to_persistent_storage_4:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c0780] "m"(b1c0ac0_c1c0780), [c1190b0] "m"(b1c0ac0_c1190b0), [c119100] "m"(b1c0ac0_c119100), [assert] "m"(b1c0ac0_assert), [exitfn] "m"(b1c0ac0_exitfn), [c8e0b0] "m"(b1c0ac0_c8e0b0), [memset] "m"(b1c0ac0_memset), [c1d1610] "m"(b1c0ac0_c1d1610), [c1d14b6] "m"(b1c0ac0_c1d14b6), [c1d2240] "m"(b1c0ac0_c1d2240), [c8d9d0] "m"(b1c0ac0_c8d9d0), [ce0bf0] "m"(b1c0ac0_ce0bf0), [c1d0ff9] "m"(b1c0ac0_c1d0ff9), [c1cf900] "m"(b1c0ac0_c1cf900)
      : "memory");
}
#else
#error "game_state_write_to_persistent_storage: clang naked draft required"
#endif


/* 0x1c0d50 */
void FUN_001c0d50(void)
{
  FUN_001c53f0();
}

/* player_profile_delete (0x1c0da0) — XBE naked draft (batch 251). */
#if defined(__clang__)
static void (*const b1c0da0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c0da0_exitfn)(int) = system_exit;
static file_ref_t * (*const b1c0da0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static bool (*const b1c0da0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c0da0_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c0da0_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c0da0_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void * (*const b1c0da0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b1c0da0_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c0da0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void player_profile_delete(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x320, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lplayer_profile_delete_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lplayer_profile_delete_2\n\t"
      ".Lplayer_profile_delete_1:\n\t"
      "pushl $1\n\t"
      "pushl $0xd8\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2b9f58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_profile_delete_2:\n\t"
      "pushl $0\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lplayer_profile_delete_6\n\t"
      "leal -0x120(%%ebp), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_delete_6\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_delete_4\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl $0x30\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x2f0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplayer_profile_delete_3\n\t"
      "pushl $0x30\n\t"
      "leal -0x320(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_delete_3:\n\t"
      "pushl $0x2b9f30\n\t"
      "jmp .Lplayer_profile_delete_5\n\t"
      ".Lplayer_profile_delete_4:\n\t"
      "pushl $0x2b9f10\n\t"
      ".Lplayer_profile_delete_5:\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "leal -0x120(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_delete_6:\n\t"
      "pushl $0x2b9eec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c0da0_assert), [exitfn] "m"(b1c0da0_exitfn), [c1999f0] "m"(b1c0da0_c1999f0), [c19a7a0] "m"(b1c0da0_c19a7a0), [c19ab50] "m"(b1c0da0_c19ab50), [c1c3160] "m"(b1c0da0_c1c3160), [c8da40] "m"(b1c0da0_c8da40), [c8e0b0] "m"(b1c0da0_c8e0b0), [c19a930] "m"(b1c0da0_c19a930), [c8f390] "m"(b1c0da0_c8f390)
      : "memory");
}
#else
#error "player_profile_delete: clang naked draft required"
#endif


/* 0x1c0ed0 — campaign level count constant (returns 18). */
unsigned short FUN_001c0ed0(void)
{
  return 0x12;
}

/* FUN_001c0ee0 (0x1c0ee0) — XBE naked draft (batch 251). */
#if defined(__clang__)


__attribute__((naked, noinline))
void FUN_001c0ee0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl $0x11, %%eax\n\t"
      "jl .LFUN_001c0ee0_1\n\t"
      "movl $0x11, %%eax\n\t"
      ".LFUN_001c0ee0_1:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%eax, %%eax\n\t"
      "setl %%cl\n\t"
      "decl %%ecx\n\t"
      "andl %%eax, %%ecx\n\t"
      "movl 0x32eae0(,%%ecx,4), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "sarl $0x10, %%edx\n\t"
      "andl $0xff, %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%eax, %%ecx\n\t"
      "sarl $8, %%ecx\n\t"
      "andl $0xff, %%ecx\n\t"
      "fmuls 0x261518\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "andl $0xff, %%eax\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "fmuls 0x261518\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "fmuls 0x261518\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "FUN_001c0ee0: clang naked draft required"
#endif


/* player_profile_save_last_level_played (0x1c0f70) — XBE naked draft (batch 243). */
#if defined(__clang__)
static void (*const b1c0f70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c0f70_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void player_profile_save_last_level_played(void *profile __attribute__((unused)), short *out_level __attribute__((unused)), short *out_difficulty __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "je .Lplayer_profile_save_last_level_played_1\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lplayer_profile_save_last_level_played_1\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lplayer_profile_save_last_level_played_2\n\t"
      ".Lplayer_profile_save_last_level_played_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x1b8\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2b9f9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_profile_save_last_level_played_2:\n\t"
      "movw $0xffff, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "movb 0x1c(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_6\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_3\n\t"
      "movw $0, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_6\n\t"
      ".Lplayer_profile_save_last_level_played_3:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_4\n\t"
      "movw $0, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_6\n\t"
      ".Lplayer_profile_save_last_level_played_4:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_5\n\t"
      "movw $0, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_6\n\t"
      ".Lplayer_profile_save_last_level_played_5:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_6\n\t"
      "movw $0, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_6:\n\t"
      "movb 0x1d(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_10\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_7\n\t"
      "movw $1, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_10\n\t"
      ".Lplayer_profile_save_last_level_played_7:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_8\n\t"
      "movw $1, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_10\n\t"
      ".Lplayer_profile_save_last_level_played_8:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_9\n\t"
      "movw $1, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_10\n\t"
      ".Lplayer_profile_save_last_level_played_9:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_10\n\t"
      "movw $1, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_10:\n\t"
      "movb 0x1e(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_14\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_11\n\t"
      "movw $2, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_14\n\t"
      ".Lplayer_profile_save_last_level_played_11:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_12\n\t"
      "movw $2, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_14\n\t"
      ".Lplayer_profile_save_last_level_played_12:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_13\n\t"
      "movw $2, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_14\n\t"
      ".Lplayer_profile_save_last_level_played_13:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_14\n\t"
      "movw $2, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_14:\n\t"
      "movb 0x1f(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_18\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_15\n\t"
      "movw $3, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_18\n\t"
      ".Lplayer_profile_save_last_level_played_15:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_16\n\t"
      "movw $3, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_18\n\t"
      ".Lplayer_profile_save_last_level_played_16:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_17\n\t"
      "movw $3, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_18\n\t"
      ".Lplayer_profile_save_last_level_played_17:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_18\n\t"
      "movw $3, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_18:\n\t"
      "movb 0x20(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_22\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_19\n\t"
      "movw $4, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_22\n\t"
      ".Lplayer_profile_save_last_level_played_19:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_20\n\t"
      "movw $4, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_22\n\t"
      ".Lplayer_profile_save_last_level_played_20:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_21\n\t"
      "movw $4, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_22\n\t"
      ".Lplayer_profile_save_last_level_played_21:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_22\n\t"
      "movw $4, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_22:\n\t"
      "movb 0x21(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_26\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_23\n\t"
      "movw $5, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_26\n\t"
      ".Lplayer_profile_save_last_level_played_23:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_24\n\t"
      "movw $5, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_26\n\t"
      ".Lplayer_profile_save_last_level_played_24:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_25\n\t"
      "movw $5, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_26\n\t"
      ".Lplayer_profile_save_last_level_played_25:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_26\n\t"
      "movw $5, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_26:\n\t"
      "movb 0x22(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_30\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_27\n\t"
      "movw $6, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_30\n\t"
      ".Lplayer_profile_save_last_level_played_27:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_28\n\t"
      "movw $6, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_30\n\t"
      ".Lplayer_profile_save_last_level_played_28:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_29\n\t"
      "movw $6, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_30\n\t"
      ".Lplayer_profile_save_last_level_played_29:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_30\n\t"
      "movw $6, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_30:\n\t"
      "movb 0x23(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_34\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_31\n\t"
      "movw $7, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_34\n\t"
      ".Lplayer_profile_save_last_level_played_31:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_32\n\t"
      "movw $7, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_34\n\t"
      ".Lplayer_profile_save_last_level_played_32:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_33\n\t"
      "movw $7, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_34\n\t"
      ".Lplayer_profile_save_last_level_played_33:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_34\n\t"
      "movw $7, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_34:\n\t"
      "movb 0x24(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_38\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_35\n\t"
      "movw $8, (%%edi)\n\t"
      "movw $3, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_38\n\t"
      ".Lplayer_profile_save_last_level_played_35:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_36\n\t"
      "movw $8, (%%edi)\n\t"
      "movw $2, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_38\n\t"
      ".Lplayer_profile_save_last_level_played_36:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_37\n\t"
      "movw $8, (%%edi)\n\t"
      "movw $1, (%%esi)\n\t"
      "jmp .Lplayer_profile_save_last_level_played_38\n\t"
      ".Lplayer_profile_save_last_level_played_37:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_38\n\t"
      "movw $8, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_38:\n\t"
      "movb 0x25(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_42\n\t"
      "testb $8, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_39\n\t"
      "movw $9, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw $3, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_last_level_played_39:\n\t"
      "testb $4, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_40\n\t"
      "movw $9, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw $2, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_last_level_played_40:\n\t"
      "testb $2, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_41\n\t"
      "movw $9, (%%edi)\n\t"
      "popl %%edi\n\t"
      "movw $1, (%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_save_last_level_played_41:\n\t"
      "testb $1, %%al\n\t"
      "je .Lplayer_profile_save_last_level_played_42\n\t"
      "movw $9, (%%edi)\n\t"
      "movw $0, (%%esi)\n\t"
      ".Lplayer_profile_save_last_level_played_42:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c0f70_assert), [exitfn] "m"(b1c0f70_exitfn)
      : "memory");
}
#else
#error "player_profile_save_last_level_played: clang naked draft required"
#endif


/* 0x1c1280 */
void FUN_001c1280(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c1290 */
void game_state_read_from_persistent_storage(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* cmp esi, ebx -> je 0x1c12a6 */
  /* cmp eax, ebx -> jl 0x1c12a6 */
  /* cmp eax, 2 -> jl 0x1c12c6 */
  display_assert((char *)0x002b9fec, (char *)0x002b9f70, 567, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 48);
  display_assert((char *)0x002b9fbc, (char *)0x002b9f70, 594, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* player_profile_setup_default_gamespy_settings (0x1c1340) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b1c1340_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c1340_exitfn)(int) = system_exit;
static void (*const b1c1340_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static bool (*const b1c1340_c81720)(void *thread_reference) = thread_is_done;
static void (*const b1c1340_c81770)(void *thread_reference) = thread_close;
static void (*const b1c1340_c1c2af0)(void) = saved_game_files_take_mutex;
static void (*const b1c1340_c1c4850)(void) = FUN_001c4850;
static bool (*const b1c1340_c19ab50)(file_ref_t *info, int size, void *buffer) = file_read;
static void (*const b1c1340_c1c3160)(void) = saved_game_file_generate_checksum;
static int (*const b1c1340_c8da40)(const void *a, const void *b, int size) = csmemcmp;
static void * (*const b1c1340_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c1340_c1c2890)(void) = saved_game_file_close;
static void (*const b1c1340_c1c2b10)(void) = saved_game_files_release_mutex;
static void *(*const b1c1340_memset)(void *, int, unsigned int) = csmemset;
static void (*const b1c1340_c1c4600)(void) = saved_game_file_get_display_name;
static wchar_t * (*const b1c1340_c19dc90)(wchar_t *dest, wchar_t *src, size_t count) = ustrncpy;

__attribute__((naked, noinline))
void player_profile_setup_default_gamespy_settings(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x354, %%esp\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "jne .Lplayer_profile_setup_default_gamespy_settings_1\n\t"
      "pushl $1\n\t"
      "pushl $0x261\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x2829b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_1:\n\t"
      "cmpl %%ebx, 0x4eaa2c\n\t"
      "je .Lplayer_profile_setup_default_gamespy_settings_3\n\t"
      "pushl $0x2ba0f8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_2:\n\t"
      "movl 0x4eaa2c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c81720]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_setup_default_gamespy_settings_2\n\t"
      "movl 0x4eaa2c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c81770]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebx, 0x4eaa2c\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_3:\n\t"
      "testl %%edi, %%edi\n\t"
      "jns .Lplayer_profile_setup_default_gamespy_settings_8\n\t"
      "call *%[c1c2af0]\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_setup_default_gamespy_settings_7\n\t"
      "leal -0x154(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1c4850]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_setup_default_gamespy_settings_6\n\t"
      "leal -0x354(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x154(%%ebp), %%ecx\n\t"
      "pushl $0x200\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19ab50]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lplayer_profile_setup_default_gamespy_settings_5\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x354(%%ebp), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "pushl $0x14\n\t"
      "leal -0x324(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x48(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c8da40]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lplayer_profile_setup_default_gamespy_settings_4\n\t"
      "pushl $0x30\n\t"
      "leal -0x354(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x154(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_4:\n\t"
      "pushl $0x2ba0a8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0xb\n\t"
      "pushl %%edi\n\t"
      "movw $0xffff, -0x1c(%%ebp)\n\t"
      "movb $3, -0xa(%%ebp)\n\t"
      "movb %%bl, -0x9(%%ebp)\n\t"
      "movb %%bl, -0x7(%%ebp)\n\t"
      "movb %%bl, -0x5(%%ebp)\n\t"
      "movb %%bl, -0x8(%%ebp)\n\t"
      "movw %%bx, -0xe(%%ebp)\n\t"
      "movb %%bl, -0xc(%%ebp)\n\t"
      "movb %%bl, -0xb(%%ebp)\n\t"
      "movw %%bx, -0x1a(%%ebp)\n\t"
      "call *%[c1c4600]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19dc90]\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "movw %%bx, -0x1e(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x18, %%esp\n\t"
      "leal -0x154(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_5:\n\t"
      "pushl $0x2ba080\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x154(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_6:\n\t"
      "pushl $0x2b9eec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_7:\n\t"
      "pushl $0x2ba030\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lplayer_profile_setup_default_gamespy_settings_8:\n\t"
      "pushl $0x2ba0a8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0xb\n\t"
      "pushl %%edi\n\t"
      "movw $0xffff, -0x1c(%%ebp)\n\t"
      "movb $3, -0xa(%%ebp)\n\t"
      "movb %%bl, -0x9(%%ebp)\n\t"
      "movb %%bl, -0x7(%%ebp)\n\t"
      "movb %%bl, -0x5(%%ebp)\n\t"
      "movb %%bl, -0x8(%%ebp)\n\t"
      "movw %%bx, -0xe(%%ebp)\n\t"
      "movb %%bl, -0xc(%%ebp)\n\t"
      "movb %%bl, -0xb(%%ebp)\n\t"
      "movw %%bx, -0x1a(%%ebp)\n\t"
      "call *%[c1c4600]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19dc90]\n\t"
      "pushl $0x30\n\t"
      "leal -0x34(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movw %%bx, -0x1e(%%ebp)\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x18, %%esp\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c1340_assert), [exitfn] "m"(b1c1340_exitfn), [c8f390] "m"(b1c1340_c8f390), [c81720] "m"(b1c1340_c81720), [c81770] "m"(b1c1340_c81770), [c1c2af0] "m"(b1c1340_c1c2af0), [c1c4850] "m"(b1c1340_c1c4850), [c19ab50] "m"(b1c1340_c19ab50), [c1c3160] "m"(b1c1340_c1c3160), [c8da40] "m"(b1c1340_c8da40), [c8e0b0] "m"(b1c1340_c8e0b0), [c1c2890] "m"(b1c1340_c1c2890), [c1c2b10] "m"(b1c1340_c1c2b10), [memset] "m"(b1c1340_memset), [c1c4600] "m"(b1c1340_c1c4600), [c19dc90] "m"(b1c1340_c19dc90)
      : "memory");
}
#else
#error "player_profile_setup_default_gamespy_settings: clang naked draft required"
#endif


/* FUN_001c15c0 (0x1c15c0) — XBE naked draft (batch 249). */
#if defined(__clang__)
static void (*const b1c15c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1c15c0_exitfn)(int) = system_exit;
static void (*const b1c15c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b1c15c0_c1c2af0)(void) = saved_game_files_take_mutex;
static void (*const b1c15c0_c1c4850)(void) = FUN_001c4850;
static void * (*const b1c15c0_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b1c15c0_c1c3160)(void) = saved_game_file_generate_checksum;
static bool (*const b1c15c0_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c15c0_c19ac00)(void) = file_write;
static void (*const b1c15c0_c1c2890)(void) = saved_game_file_close;
static void (*const b1c15c0_c1c4990)(void) = FUN_001c4990;
static char (*const b1c15c0_c1c46c0)(int param_1) = delete_enumerated_saved_game_file;
static void (*const b1c15c0_c1c2b10)(void) = saved_game_files_release_mutex;

__attribute__((naked, noinline))
void FUN_001c15c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001c15c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x2d7\n\t"
      "pushl $0x2b9f70\n\t"
      "pushl $0x266c9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001c15c0_1:\n\t"
      "pushl $0x2ba1a4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2af0]\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c15c0_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl (%%esi), %%edi\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "addl $4, %%esi\n\t"
      "call *%[c1c4850]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c15c0_6\n\t"
      "pushl $0x30\n\t"
      "leal -0x30c(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "leal -0x2dc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30c(%%ebp), %%eax\n\t"
      "pushl $0x30\n\t"
      "pushl %%eax\n\t"
      "call *%[c1c3160]\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19aa00]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c15c0_2\n\t"
      "leal -0x30c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c15c0_3\n\t"
      ".LFUN_001c15c0_2:\n\t"
      "pushl $0x2ba17c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_001c15c0_3:\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c2890]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c15c0_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c4990]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c15c0_4\n\t"
      "pushl $0x2ba14c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c15c0_4:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001c15c0_5\n\t"
      "pushl %%edi\n\t"
      "call *%[c1c46c0]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_001c15c0_5:\n\t"
      "call *%[c1c2b10]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jmp .LFUN_001c15c0_8\n\t"
      ".LFUN_001c15c0_6:\n\t"
      "pushl $0x2b9eec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "call *%[c1c2b10]\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jmp .LFUN_001c15c0_8\n\t"
      ".LFUN_001c15c0_7:\n\t"
      "pushl $0x2ba030\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001c15c0_8:\n\t"
      "pushl $0x2ba130\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1c15c0_assert), [exitfn] "m"(b1c15c0_exitfn), [c8f390] "m"(b1c15c0_c8f390), [c1c2af0] "m"(b1c15c0_c1c2af0), [c1c4850] "m"(b1c15c0_c1c4850), [c8e0b0] "m"(b1c15c0_c8e0b0), [c1c3160] "m"(b1c15c0_c1c3160), [c19aa00] "m"(b1c15c0_c19aa00), [c19ac00] "m"(b1c15c0_c19ac00), [c1c2890] "m"(b1c15c0_c1c2890), [c1c4990] "m"(b1c15c0_c1c4990), [c1c46c0] "m"(b1c15c0_c1c46c0), [c1c2b10] "m"(b1c15c0_c1c2b10)
      : "memory");
}
#else
#error "FUN_001c15c0: clang naked draft required"
#endif


/* 0x1c1720 */
void FUN_001c1720(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_001c5560();
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c18b1 */
  csmemset((void *)0, 0, 0);
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)esi, 11);
  error(0, (char *)0x002ba220);
  /* cmp ecx, 4 -> jl 0x1c1800 */
  /* cmp esi, 0xa -> jl 0x1c17f5 */
  saved_game_file_generate_checksum();
  file_set_position((void *)(uintptr_t)edx, 0);
  /* test (char)eax, (char)eax -> je 0x1c1861 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c1895 */
  error(0, (char *)0x002ba1ec);
  delete_enumerated_saved_game_file(0);
  saved_game_file_close();
  saved_game_file_close();
  error(0, (char *)0x002ba1c0);
  delete_enumerated_saved_game_file(0);
  error(0, (char *)0x00288848);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c18f0 */
void player_profile_new(void)
{
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002829b0, (char *)0x002b9f70, 194, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x1c193e */
  csmemcpy((void *)(uintptr_t)esi, (void *)0x004ea9c8, 48);
  player_profile_setup_default_gamespy_settings();

  (void)esi;
  (void)edi;
}

/* 0x1c1950 */
void FUN_001c1950(void)
{
  FUN_001c0ee0();
}

/* 0x1c19a0 */
int FUN_001c19a0(void)
{
  int eax = 0;

  random_math_get_local_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  return 0;

  (void)eax;
}

/* 0x1c19c0 */
int FUN_001c19c0(void)
{
  int eax = 0;

  random_math_get_local_seed_address();
  random_range((void *)(uintptr_t)eax, 0, 0);
  return 0;

  (void)eax;
}

/* FUN_001c19e0 (0x1c19e0) — XBE naked draft (batch 242). */
#if defined(__clang__)
static void (*const b1c19e0_c1c1290)(void) = game_state_read_from_persistent_storage;
static int (*const b1c19e0_c1d9179)(char *str, size_t size, const char *format, ...) = snprintf;
static file_ref_t * (*const b1c19e0_c1999f0)(file_ref_t *info, const char *directory, bool a4) = file_reference_create_from_path;
static void (*const b1c19e0_c1c3160)(void) = saved_game_file_generate_checksum;
static bool (*const b1c19e0_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b1c19e0_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b1c19e0_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static void (*const b1c19e0_c19ac00)(void) = file_write;
static bool (*const b1c19e0_c19a930)(file_ref_t *info) = file_close;
static void (*const b1c19e0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_001c19e0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x40c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_001c19e0_1:\n\t"
      "pushl %%edi\n\t"
      "leal -0x40c(%%ebp), %%esi\n\t"
      "call *%[c1c1290]\n\t"
      "pushl %%edi\n\t"
      "pushl $0x2ba2d8\n\t"
      "leal -0x20c(%%ebp), %%eax\n\t"
      "pushl $0xff\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d9179]\n\t"
      "pushl $0\n\t"
      "leal -0x20c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1999f0]\n\t"
      "addl $0x20, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001c19e0_3\n\t"
      "leal -0x3dc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x40c(%%ebp), %%ecx\n\t"
      "pushl $0x30\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1c3160]\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a490]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c19e0_3\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $2\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c19e0_3\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19aa00]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001c19e0_3\n\t"
      "leal -0x40c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0x200\n\t"
      "pushl %%eax\n\t"
      "call *%[c19ac00]\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, %%bl\n\t"
      "call *%[c19a930]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_001c19e0_2\n\t"
      "leal -0x20c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x2ba2a4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c19e0_2:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_001c19e0_4\n\t"
      ".LFUN_001c19e0_3:\n\t"
      "leal -0x20c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2ba260\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001c19e0_4:\n\t"
      "incl %%edi\n\t"
      "cmpl $2, %%edi\n\t"
      "jl .LFUN_001c19e0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1c1290] "m"(b1c19e0_c1c1290), [c1d9179] "m"(b1c19e0_c1d9179), [c1999f0] "m"(b1c19e0_c1999f0), [c1c3160] "m"(b1c19e0_c1c3160), [c19a490] "m"(b1c19e0_c19a490), [c19a7a0] "m"(b1c19e0_c19a7a0), [c19aa00] "m"(b1c19e0_c19aa00), [c19ac00] "m"(b1c19e0_c19ac00), [c19a930] "m"(b1c19e0_c19a930), [c8f390] "m"(b1c19e0_c8f390)
      : "memory");
}
#else
#error "FUN_001c19e0: clang naked draft required"
#endif

