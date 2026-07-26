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

/* 0x1c0ac0 */
void game_state_write_to_persistent_storage(int param_1, void *param_2, int param_3, int param_4)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001c0780(0);
  /* cmp esi, -1 -> je 0x1c0c19 */
  crc_new((void *)(uintptr_t)eax);
  crc_checksum_buffer((void *)(uintptr_t)ecx, (void *)(uintptr_t)edi, 0x00345000);
  /* cmp ebx, 0x800 -> jb 0x1c0b38 */
  display_assert((char *)0x002b9e24, (char *)0x002b9b70, 333, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edi, ebx);
  csmemset((void *)(uintptr_t)edi, 0, ebx);
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c0bae */
  WriteFile(0, (void *)(uintptr_t)edi, edx, (void *)(uintptr_t)ecx, (void *)0);
  /* test eax, eax -> je 0x1c0bae */
  /* relift: cmp dword ptr [ebp - 4], eax -> jne 0x1c0bae */
  SetFilePointer(0, 0, (void *)0, 0);
  /* cmp eax, -1 -> je 0x1c0bae */
  WriteFile(0, (void *)(uintptr_t)edx, ebx, (void *)(uintptr_t)ecx, (void *)0);
  /* test eax, eax -> je 0x1c0bae */
  /* relift: cmp dword ptr [ebp - 4], ebx -> je 0x1c0c00 */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b9df8);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  player_ui_get_path_to_local_player_profile_directory();
  /* test (char)eax, (char)eax -> je 0x1c0c00 */
  DeleteFileA((char *)(uintptr_t)ecx);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)edx, ebx);
  CloseHandle(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1c0d50 */
void FUN_001c0d50(void)
{
  FUN_001c53f0();
}

/* 0x1c0da0 */
void player_profile_delete(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x1c0ddc */
  display_assert((char *)0x002b9f58, (char *)0x002b9f70, 216, 0);
  system_exit(0);
  file_reference_create_from_path((void *)(uintptr_t)eax, (char *)(uintptr_t)esi, 0);
  /* test eax, eax -> je 0x1c0eb3 */
  file_open((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c0eb3 */
  file_read((void *)(uintptr_t)eax, 512, (void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c0e8c */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, 20);
  /* test eax, eax -> jne 0x1c0e85 */
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)edx, 48);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002b9f10);
  file_close((void *)(uintptr_t)eax);
  error(0, (char *)0x002b9eec);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1c0ed0 — campaign level count constant (returns 18). */
unsigned short FUN_001c0ed0(void)
{
  return 0x12;
}

/* 0x1c0ee0 */
void FUN_001c0ee0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1c0f70 — decode last campaign level/difficulty from profile flags. */
void player_profile_save_last_level_played(void *profile, short *out_level,
                                           short *out_difficulty)
{
  int level;
  unsigned char flags;

  if (profile == 0 || out_level == 0 || out_difficulty == 0) {
    display_assert((char *)0x002b9f9c, (char *)0x002b9f70, 0x1b8, 1);
    system_exit(-1);
  }

  *out_level = -1;
  *out_difficulty = 1;
  for (level = 0; level < 10; level++) {
    flags = *((unsigned char *)profile + 0x1c + level);
    if (flags == 0)
      continue;
    *out_level = (short)level;
    if (flags & 8)
      *out_difficulty = 3;
    else if (flags & 4)
      *out_difficulty = 2;
    else if (flags & 2)
      *out_difficulty = 1;
    else if (flags & 1)
      *out_difficulty = 0;
  }
}

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

/* 0x1c1340 */
void player_profile_setup_default_gamespy_settings(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  display_assert((char *)0x002829b0, (char *)0x002b9f70, 609, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x4eaa2c], ebx -> je 0x1c13b7 */
  error(0, (char *)0x002ba0f8);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c1390 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaa2c] = ebx */
  saved_game_files_take_mutex();
  /* test (char)eax, (char)eax -> je 0x1c1535 */
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c1519 */
  file_read((void *)(uintptr_t)ecx, 512, (void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c14ed */
  saved_game_file_generate_checksum();
  csmemcmp((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, 20);
  /* test eax, eax -> jne 0x1c1465 */
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, 48);
  saved_game_file_close();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba0a8);
  csmemset((void *)(uintptr_t)ecx, 0, 48);
  saved_game_file_get_display_name();
  ustrncpy((wchar_t *)(uintptr_t)edx, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, 48);
  saved_game_file_close();
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba080);
  saved_game_file_close();
  saved_game_files_release_mutex();
  error(0, (char *)0x002b9eec);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba030);
  error(0, (char *)0x002ba0a8);
  csmemset((void *)(uintptr_t)edx, 0, 48);
  saved_game_file_get_display_name();
  ustrncpy((wchar_t *)(uintptr_t)eax, (wchar_t *)(uintptr_t)eax, 0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ecx, 48);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1c15c0 */
void FUN_001c15c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1c15f1 */
  display_assert((char *)0x00266c9c, (char *)0x002b9f70, 727, 0);
  system_exit(0);
  error(0, (char *)0x002ba1a4);
  saved_game_files_take_mutex();
  /* test (char)eax, (char)eax -> je 0x1c16f6 */
  FUN_001c4850();
  /* test (char)eax, (char)eax -> je 0x1c16de */
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, 48);
  saved_game_file_generate_checksum();
  file_set_position((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c1686 */
  file_write();
  /* test (char)eax, (char)eax -> jne 0x1c1697 */
  error(0, (char *)0x002ba17c);
  saved_game_file_close();
  /* test (char)eax, (char)eax -> je 0x1c16c8 */
  FUN_001c4990();
  /* test (char)eax, (char)eax -> jne 0x1c16c8 */
  error(0, (char *)0x002ba14c);
  /* test (char)ebx, (char)ebx -> je 0x1c16d5 */
  delete_enumerated_saved_game_file(0);
  saved_game_files_release_mutex();
  error(0, (char *)0x002b9eec);
  saved_game_files_release_mutex();
  error(0, (char *)0x002ba030);
  error(0, (char *)0x002ba130);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

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

/* 0x1c19e0 */
void FUN_001c19e0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  game_state_read_from_persistent_storage();
  snprintf((char *)(uintptr_t)eax, 255, (char *)0x002ba2d8);
  file_reference_create_from_path((void *)(uintptr_t)edx, (char *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x1c1acc */
  saved_game_file_generate_checksum();
  FUN_0019a490((void *)(uintptr_t)edx);
  /* test (char)eax, (char)eax -> je 0x1c1acc */
  file_open((void *)(uintptr_t)eax, 0);
  /* test (char)eax, (char)eax -> je 0x1c1acc */
  file_set_position((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> je 0x1c1acc */
  file_write();
  file_close((void *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x1c1ac8 */
  error(0, (char *)0x002ba2a4);
  /* test (char)ebx, (char)ebx -> jne 0x1c1ae2 */
  error(0, (char *)0x002ba260);
  /* cmp edi, 2 -> jl 0x1c19f0 */
  /* test esi, esi -> jne 0x1c1b27 */
  display_assert((char *)0x002829b0, (char *)0x002b9f70, 704, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1c1b6b */
  error(0, (char *)0x002ba0f8);
  thread_is_done((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x1c1b40 */
  thread_close((void *)(uintptr_t)ecx);
  /* mem[0x004eaa2c] = 0 */
  /* mem[0x004ea9f8] = edx */
  csmemcpy((void *)0x004ea9fc, (void *)(uintptr_t)esi, 48);
  thread_new(0, (void *)0x001c15c0, 0x004ea9f8, (void *)0x004eaa2c);
  csmemset((void *)0x004ea9c8, 0, 108);
  /* test esi, esi -> jne 0x1c1beb */
  display_assert((char *)0x002829b0, (char *)0x002b9f70, 256, 0);
  system_exit(0);
  /* cmp eax, -1 -> je 0x1c1bfc */
  FUN_001c1b00();
  main_get_current_solo_level();
  /* cmp (int16_t)ebx, 4 -> jl 0x1c1c3d */
  display_assert((char *)0x00282750, (char *)0x002b9f70, 378, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> je 0x1c1cb2 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1c1c4e */
  /* cmp (int16_t)esi, 0xa -> jl 0x1c1c6e */
  display_assert((char *)0x002ba30c, (char *)0x002b9f70, 381, 0);
  system_exit(0);
  player_ui_get_active_player_profile_index();
  /* cmp edi, -1 -> je 0x1c1cb1 */
  player_ui_get_active_player_profile();
  /* relift: cmp word ptr [ebp - 0xa], (int16_t)esi -> je 0x1c1ca3 */
  player_profile_get_from_path();
  player_ui_set_active_player_profile();
  /* cmp (int16_t)ebx, 4 -> jl 0x1c1cf7 */
  display_assert((char *)0x00282750, (char *)0x002b9f70, 407, 0);
  system_exit(0);
  main_get_current_solo_level();
  game_difficulty_level_get();
  /* cmp (int16_t)esi, 0xa -> jge 0x1c1d1c */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1c1d1c */
  /* cmp (int16_t)eax, 4 -> jl 0x1c1d3c */
  display_assert((char *)0x002ba3b0, (char *)0x002b9f70, 413, 0);
  system_exit(0);
  player_ui_get_active_player_profile_index();
  /* cmp edi, -1 -> je 0x1c1d8a */
  player_ui_get_active_player_profile();
  FUN_001c1b00();
  player_ui_set_active_player_profile();
  error(0, (char *)0x002ba348);
  csmemset((void *)0x004eaa38, 0, 116);
  /* test eax, eax -> je 0x1c1e0b */
  error(0, (char *)0x002ba430);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
