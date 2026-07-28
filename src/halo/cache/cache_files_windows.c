#include <stdint.h>
/* Cache file precaching system for Xbox. Manages background copying of
 * map files from DVD to the hard drive cache partition. */

/* Freestanding TU compile: SleepEx lives in xdk_stubs_rt.c. */
unsigned int __stdcall SleepEx(unsigned int milliseconds, int alertable);

/* Set the precache thread priority — forwards param to thread handler. */
void cache_files_precache_set_priority(bool high)
{
  ((void (*)(bool))0x1ba290)(high);
}

/* Returns true if a map copy operation is currently in progress. */
bool cache_files_precache_in_progress(void)
{
  return *(uint8_t *)0x4e9220;
}

/* Returns true if the named map is currently being copied. */
bool cache_files_precache_is_copying_map(char *map_name)
{
  if (*(int16_t *)0x4e9222 != -1) {
    char *canonical = ((char *(*)(char *))0x19b0d0)(map_name);
    if (((int (*)(void *, char *))0x8dcb0)((void *)0x4e9224, canonical) == 0)
      return 1;
  }
  return 0;
}

/* Signal the end of the map precache queue. Asserts that a copy is
 * currently in progress. */
void cache_files_precache_map_queue_end(void)
{
  if (!*(uint8_t *)0x4e9220) {
    display_assert("cache_file_globals.copy_in_progress",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x3cb, 1);
    system_exit(-1);
  }
  ((void (*)(void))0x1ba5d0)();
}

/* Cache file slot accessor helpers. All take map_file_index in.
 * DAT_004e61d8 is an array of 6 cache file entries, each 0x80c bytes.
 * Source: c:\halo\SOURCE\cache\cache_files_windows.c line 0x485/0x49d. */

void *FUN_001bc720(short map_file_index)
{
  if ((int)map_file_index < 0 || (int)map_file_index >= 6) {
    display_assert(
      "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x485, 1);
    system_exit(-1);
  }
  return (void *)((char *)0x4e61d8 + (int)map_file_index * 0x80c);
}

void FUN_001bc760(short map_file_index)
{
  if ((int)map_file_index < 0 || (int)map_file_index >= 6) {
    display_assert(
      "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x485, 1);
    system_exit(-1);
  }
  *(unsigned int *)((char *)0x4e61d8 + (int)map_file_index * 0x80c) =
    0xffffffff;
}

unsigned int FUN_001bc7a0(short map_file_index)
{
  if ((int)map_file_index < 0 || (int)map_file_index >= 6) {
    display_assert(
      "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x485, 1);
    system_exit(-1);
  }
  return *(unsigned int *)((char *)0x4e61d8 + (int)map_file_index * 0x80c);
}

int FUN_001bc7e0(short map_file_index)
{
  int result;

  if ((int)map_file_index < 0 || (int)map_file_index >= 6) {
    display_assert(
      "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x49d, 1);
    system_exit(-1);
  }
  if (map_file_index <= 1)
    return 0x11600000;
  result = (int)(map_file_index > 2) - 1;
  result &= (int)0xff400000;
  result += 0x2f00000;
  return result;
}

/* Build cache map filename "z:\\cache%03d.map" into buffer.
 * buffer in, index in (caller sign-extends short to int). */
void FUN_001bc830(char *buffer, int index)
{
  crt_sprintf(buffer, "z:\\cache%03d.map", index);
}

/* Signal the cache I/O event at DAT_004e9248. */
void FUN_001bc850(void)
{
  SetEvent(*(void **)0x4e9248);
}

/* FUN_001bc860 — IO completion callback for cache read/write.
 * Called by Windows when an overlapped IO request completes.
 * Validates error_code==ERROR_SUCCESS and bytes_transferred==request->size,
 * then signals the event at request->overlapped.hEvent (offset +0x10)
 * and clears the in-progress flags at +0x1d and +0x1e.
 * __stdcall: callee cleans 3 stack args (RET 0xc).
 */
void __stdcall FUN_001bc860(int error_code, int bytes_transferred,
                            void *finished_request)
{
  char *req = (char *)finished_request;
  char *event_ptr;

  if (error_code != 0) {
    display_assert("error_code==ERROR_SUCCESS",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x538, 1);
    system_exit(-1);
  }
  if (bytes_transferred != *(int *)(req + 0x14)) {
    display_assert("bytes_transferred==finished_request->size",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x539, 1);
    system_exit(-1);
  }
  event_ptr = *(char **)(req + 0x10);
  if (!event_ptr) {
    display_assert("finished_request->overlapped.hEvent",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x53a, 1);
    system_exit(-1);
  }
  *event_ptr = 1;
  *(char *)(req + 0x1d) = 0;
  *(char *)(req + 0x1e) = 0;
}

/* FUN_001bc8f0 — IO completion callback for async operations without
 * size tracking.  Validates error_code==ERROR_SUCCESS and hEvent non-null,
 * then sets *hEvent = 1 to signal the waiter.
 * __stdcall: callee cleans 3 stack args (RET 0xc).
 */
void __stdcall FUN_001bc8f0(int error_code, unsigned int param_2,
                            void *overlapped)
{
  if (error_code != 0) {
    display_assert("error_code==ERROR_SUCCESS",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x54a, 1);
    system_exit(-1);
  }
  if (*(int *)((char *)overlapped + 0x10) == 0) {
    display_assert("overlapped->hEvent",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x54b, 1);
    system_exit(-1);
    **(char **)((char *)overlapped + 0x10) = 1;
    return;
  }
  **(char **)((char *)overlapped + 0x10) = 1;
}

/* cache_file_close — close the currently-open map file if any is open.
 * DAT_004e9244 = cache_file_globals.open_map_file_index (int16_t).
 * If not NONE (-1), calls FUN_001bc620 to close the file, then resets to -1.
 * Frameless in the original (no EBP frame).
 */
void cache_file_close(void)
{
  if (*(int16_t *)0x4e9244 != -1) {
    FUN_001bc620();
    *(int16_t *)0x4e9244 = -1;
  }
}

/* cache_file_read — submit an async IO request to the cache file system.
 * Allocates a free request slot via FUN_001bc5c0, validates inputs, fills the
 * slot (offset +0..+0x1e), clears the completion flag, and fires the IO event.
 * Size is rounded up to the next multiple of 0x200 if not aligned.
 * Returns the request slot index.
 */
short cache_file_read(int param_1, int offset, unsigned int size, int buffer,
                      char *completion_flag, char async_flag)
{
  short request_index;
  char *req;

  request_index = FUN_001bc5c0();
  if (request_index < 0 || request_index > 0x1ff) {
    display_assert(
      "request_index>=0 && request_index<MAXIMUM_SIMULTANEOUS_CACHE_REQUESTS",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x260, 1);
    system_exit(-1);
  }
  req = (char *)(*(int *)0x4e9250 + (int)request_index * 0x20);
  if (*(int16_t *)0x4e9244 == -1) {
    display_assert("cache_file_globals.open_map_file_index!=NONE",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x107, 1);
    system_exit(-1);
  }
  if (!buffer) {
    display_assert("buffer", "c:\\halo\\SOURCE\\cache\\cache_files_windows.c",
                   0x10a, 1);
    system_exit(-1);
  }
  if (!completion_flag) {
    display_assert("completion_flag_reference",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x10b, 1);
    system_exit(-1);
  }
  if (offset < 0) {
    display_assert("offset>=0",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x10e, 1);
    system_exit(-1);
  }
  if (size & 0x1ff)
    size = (size | 0x1ff) + 1;
  *completion_flag = 0;
  csmemset(req, 0, 0x14);
  *(char **)(req + 0x10) = completion_flag;
  *(unsigned int *)(req + 0x14) = size;
  *(int *)(req + 0xc) = 0;
  *(int *)(req + 0x8) = offset;
  *(int *)(req + 0x18) = buffer;
  *(char *)(req + 0x1d) = 1;
  *(char *)(req + 0x1c) = async_flag;
  *(char *)(req + 0x1e) = 0;
  SetEvent(*(void **)0x4e9248);
  return request_index;
}

/* Enable an async cache I/O request. Validates request_index is within
 * [0, 512) and sets the enable byte (offset 0x1c) in the request's
 * 0x20-byte entry in the global cache request array at 0x4e9250. */
void cache_files_io_request_enable(int16_t request_index)
{
  if (request_index < 0 || request_index >= 0x200) {
    display_assert(
      "request_index>=0 && request_index<MAXIMUM_SIMULTANEOUS_CACHE_REQUESTS",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x260, 1);
    system_exit(-1);
  }
  *(uint8_t *)(*(int *)0x4e9250 + (int)request_index * 0x20 + 0x1c) = 1;
}

/* Validate a map file by name (0x1bcb80). Builds the path
 * "d:\\maps\\<map_name>.map" into a 256-byte stack buffer, opens it read-
 * only, reads the first 0x800 bytes into the caller-supplied header buffer
 * (passed in EDI), and asks cache_file_header_verify whether the header is
 * legitimate (signature, version, etc). Returns true only if the file
 * exists, the read returned exactly 0x800 bytes, and the header passes
 * verification. Always closes the handle if it was opened.
 *
 * Register args: EAX = map name (for the printf substitution),
 * EDI = 0x800-byte caller buffer that receives the header.
 */
bool FUN_001bcb80(const char *map_name ,
                  void *header_buf )
{
  char path[256];
  int handle;
  uint32_t bytes_read;
  bool ok;

  ok = false;
  crt_sprintf(path, "d:\\maps\\%s.map", map_name);
  handle = CreateFileA(path, 0x80000000, 0, 0, 3, 0, 0);
  if (handle != -1) {
    if (ReadFile(handle, header_buf, 0x800, &bytes_read, 0) != 0 &&
        bytes_read == 0x800 && cache_file_header_verify(header_buf, path, 1)) {
      ok = true;
    }
    CloseHandle(handle);
  }
  return ok;
}

/* cache_file_block_until_not_busy — spin-wait until all 512 cache IO request
 * slots are idle. Loops: sleeps 1ms (SleepEx(0,1)), then scans all slots
 * checking the active byte at +0x1d. If any slot is still active, repeat.
 * DAT_004e9250 = base of the 512-entry request array (each 0x20 bytes).
 */
void cache_file_block_until_not_busy(void)
{
  int active;
  short i;
  int offset;

  do {
    SleepEx(0, 1);
    active = 0;
    i = 0;
    offset = 0;
    do {
      if (i < 0 || i > 0x1ff) {
        display_assert("request_index>=0 && "
                       "request_index<MAXIMUM_SIMULTANEOUS_CACHE_REQUESTS",
                       "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x260,
                       1);
        system_exit(-1);
      }
      if (*(char *)(*(int *)0x4e9250 + offset + 0x1d) != '\0')
        active = 1;
      i = i + 1;
      offset = offset + 0x20;
    } while (i < 0x200);
  } while (active);
}

/* tags_header_register_vertex_and_index_buffers — register D3D vertex and index
 * buffers from a block. block+0x10: vertex buffer count; block+0x14: vertex
 * buffer array base (stride 0xc). block+0x18: index buffer count; block+0x1c:
 * index buffer array base (stride 0xc). Writes 1 to the first dword of each
 * vertex buffer entry and calls D3DResource_Register; writes 0x10001 to each
 * index buffer entry.
 */
void tags_header_register_vertex_and_index_buffers(void *block)
{
  char *b = (char *)block;
  short s;
  int i;

  s = 0;
  if (*(int *)(b + 0x10) > 0) {
    i = 0;
    do {
      unsigned int *entry = (unsigned int *)(*(int *)(b + 0x14) + i * 0xc);
      *entry = 1;
      D3DResource_Register(entry, 0);
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0x10));
  }
  s = 0;
  if (*(int *)(b + 0x18) > 0) {
    i = 0;
    do {
      *(unsigned int *)(*(int *)(b + 0x1c) + i * 0xc) = 0x10001;
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0x18));
  }
}

/* tags_header_deregister_vertex_and_index_buffers — wait for D3D vertex and
 * index buffers to become idle. Calls D3DResource_BlockUntilNotBusy then
 * asserts !IsBusy for each buffer. Same block layout as
 * tags_header_register_vertex_and_index_buffers.
 */
void tags_header_deregister_vertex_and_index_buffers(void *block)
{
  char *b = (char *)block;
  short s;
  int i;

  s = 0;
  if (*(int *)(b + 0x10) > 0) {
    i = 0;
    do {
      void *entry = (void *)(*(int *)(b + 0x14) + i * 0xc);
      D3DResource_BlockUntilNotBusy(entry);
      if (D3DResource_IsBusy(entry) != 0) {
        display_assert("!IDirect3DVertexBuffer8_IsBusy(vertex_buffer)",
                       "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x205,
                       1);
        system_exit(-1);
      }
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0x10));
  }
  s = 0;
  if (*(int *)(b + 0x18) > 0) {
    i = 0;
    do {
      void *entry = (void *)(*(int *)(b + 0x1c) + i * 0xc);
      D3DResource_BlockUntilNotBusy(entry);
      if (D3DResource_IsBusy(entry) != 0) {
        display_assert("!IDirect3DIndexBuffer8_IsBusy(index_buffer)",
                       "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x212,
                       1);
        system_exit(-1);
      }
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0x18));
  }
}

/* structure_bsp_header_register_vertex_buffers — register D3D vertex and index
 * buffers from a geometry block. block+4/8: vertex count/array; block+0xc/0x10:
 * index count/array (stride 0xc). Writes 1 to first dword of each buffer entry
 * and calls D3DResource_Register. Same as
 * tags_header_register_vertex_and_index_buffers but uses offsets
 * +4/+8/+0xc/+0x10 instead of +0x10/+0x14/+0x18/+0x1c.
 */
void structure_bsp_header_register_vertex_buffers(void *block)
{
  char *b = (char *)block;
  short s;
  int i;

  s = 0;
  if (*(int *)(b + 4) > 0) {
    i = 0;
    do {
      unsigned int *entry = (unsigned int *)(*(int *)(b + 8) + i * 0xc);
      *entry = 1;
      D3DResource_Register(entry, 0);
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 4));
  }
  s = 0;
  if (*(int *)(b + 0xc) > 0) {
    i = 0;
    do {
      unsigned int *entry = (unsigned int *)(*(int *)(b + 0x10) + i * 0xc);
      *entry = 1;
      D3DResource_Register(entry, 0);
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0xc));
  }
}

/* structure_bsp_header_deregister_vertex_buffers — wait for all vertex and
 * index buffers in a geometry block. Sets DAT_00325652=0x11 (render state),
 * blocks until each D3D resource is idle, then clears DAT_00325652=0. Same
 * struct layout as structure_bsp_header_register_vertex_buffers.
 */
void structure_bsp_header_deregister_vertex_buffers(void *block)
{
  char *b = (char *)block;
  short s;
  int i;

  *(char *)0x325652 = 0x11;
  s = 0;
  if (*(int *)(b + 4) > 0) {
    i = 0;
    do {
      D3DResource_BlockUntilNotBusy((void *)(*(int *)(b + 8) + i * 0xc));
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 4));
  }
  s = 0;
  if (*(int *)(b + 0xc) > 0) {
    i = 0;
    do {
      D3DResource_BlockUntilNotBusy((void *)(*(int *)(b + 0x10) + i * 0xc));
      s = s + 1;
      i = (int)s;
    } while (i < *(int *)(b + 0xc));
  }
  *(char *)0x325652 = 0;
}

/* FUN_001bcea0 — delete cache map files z:\cacheNNN.map starting at
 * map_file_index+1 up to but not including 20 ( = map_file_index).
 * Calls SetLastError(0) at the end to clear any DeleteFile error.
 */
void FUN_001bcea0(short map_file_index)
{
  char local_buf[256];
  int i;
  unsigned int count;
  short start;

  start = map_file_index + 1;
  if ((unsigned short)start < 0x14) {
    i = (int)start;
    count = (unsigned int)(unsigned short)(0x14 - start);
    do {
      csprintf(local_buf, "z:\\cache%03d.map", i);
      DeleteFileA(local_buf);
      i = i + 1;
      count = count - 1;
    } while (count != 0);
  }
  SetLastError(0);
}

/* Query the status of the current precache operation. Returns a status
 * code and optionally writes the progress fraction to *progress. */
__int16 cache_files_precache_map_status(float *progress)
{
  int16_t status;

  if (!*(uint8_t *)0x4e9220) {
    display_assert("cache_file_globals.copy_in_progress",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x3a5, 1);
    system_exit(-1);
  }

  status = ((int16_t(*)(float *))0x1badc0)(progress);

  switch ((int)status) {
  case 0:
  case 1:
    return 2;
  case 2:
    FUN_001bc760(*(int16_t *)0x4e9222);
    return 2;
  case 3:
    return 0;
  case 4:
    return 1;
  default:
    display_assert(0, "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x3c2,
                   1);
    system_exit(-1);
    return 0;
  }
}

/* FUN_001bcfb0 — open/map the cache file for the given slot ( =
 * map_file_index). Initializes a local OBJECT_ATTRIBUTES-like struct, fills it
 * with the file path pointer at entry+4, and calls SetFileTime to create a
 * file mapping. Cache file entry at DAT_004e61d8 + index*0x80c; file handle at
 * offset +0.
 */
void FUN_001bcfb0(short map_file_index)
{
  char local_buf[16];
  char *entry;

  if ((int)map_file_index < 0 || (int)map_file_index >= 6) {
    display_assert(
      "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
      "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x485, 1);
    system_exit(-1);
  }
  entry = (char *)0x4e61d8 + (int)map_file_index * 0x80c;
  GetLocalTime(local_buf);
  SystemTimeToFileTime(local_buf, entry + 4);
  SetFileTime(*(int *)entry, entry + 4, 0, 0);
}

/* Returns true if the named map has already been precached.
 * 0x1bd1b0 reads EDI as the canonical map name (set from 0x19b0d0). */
bool cache_files_precache_map_loaded(char *map_name)
{
  int _edi = (int)((char *(*)(char *))0x19b0d0)(map_name);
  int16_t result;
#if defined(_MSC_VER) && !defined(__clang__)
  __asm {
    mov edi, _edi
    mov eax, 0x1bd1b0
    call eax
    mov result, ax
  }
#else
  asm volatile("movl $0x1bd1b0, %%eax\n\t"
               "call *%%eax"
               : "+D"(_edi), "=a"(result)
               :
               : "ecx", "edx", "memory", "cc");
#endif
  return result != -1;
}

/* FUN_001bd5f0 — open or create the 6 cache slot files on Z:.
 * For each slot: opens with OPEN_ALWAYS, checks if existing file has the
 * right size. If the file is new or wrong size, reads the old header (0x800
 * bytes), then resizes via SetFilePointer+SetEndOfFile. After opening,
 * validates the cached header: build string must match "01.10.12.2276" and
 * the CRC must match the DVD source map. Clears slot metadata on mismatch.
 */
void FUN_001bd5f0(void)
{
  char path[256];
  char dvd_header[0x800];
  char read_buf[0x800];
  int expected_size;
  int handle;
  short i;
  bool ok;
  bool nuke_extra;
  char *entry_ptr;
  uint32_t bytes_read;
  uint32_t last_error;

  FUN_001bcea0(6);
  nuke_extra = 0;
  entry_ptr = (char *)0x4e6204;

  for (i = 0; i < 6; i++) {
    ok = 0;

    if (i < 0 || i >= 6) {
      display_assert(
        "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
        "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x485, 1);
      system_exit(-1);
    }

    crt_sprintf(path, "z:\\cache%03d.map", (int)i);

    if (i < 0 || i >= 6) {
      display_assert(
        "map_file_index>=0 && map_file_index<NUMBER_OF_CACHED_MAP_FILES",
        "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x49d, 1);
      system_exit(-1);
    }
    if (i <= 1) {
      expected_size = 0x11600000;
    } else {
      int temp = (int)(i > 2) - 1;
      temp &= (int)0xff400000;
      expected_size = temp + 0x2f00000;
    }

    handle = CreateFileA(path, 0xc0000000, 0, 0, 4, 0x60000000, 0);
    if (handle == -1) {
      {
        char err_buf[256];
        csprintf(err_buf, "couldn't open or create new cache file (#%d)",
                 xapi_GetLastError());
        display_assert(err_buf,
                       "c:\\halo\\SOURCE\\cache\\cache_files_windows.c",
                       0x305, 1);
        system_exit(-1);
      }
      goto post_process;
    }

    last_error = xapi_GetLastError();
    if (last_error == 0xb7 &&
        GetFileSize(handle, 0) == (unsigned int)expected_size) {
      ok = 1;
      goto post_process;
    }

    if (!nuke_extra) {
      FUN_001bcea0(i);
      nuke_extra = 1;
    }

    ReadFile(handle, read_buf, 0x800, &bytes_read, 0);

    if (SetFilePointer(handle, expected_size, 0, 0) != (unsigned int)-1) {
      if (SetEndOfFile(handle)) {
        ok = 1;
      }
    }

    if (!ok) {
      {
        char err_buf[256];
        csprintf(err_buf, "setup for new cache file failed (#%d)",
                 xapi_GetLastError());
        display_assert(err_buf,
                       "c:\\halo\\SOURCE\\cache\\cache_files_windows.c",
                       0x2f9, 1);
        system_exit(-1);
      }
      CloseHandle(handle);
      handle = -1;
    }

  post_process:
    *(int *)(entry_ptr - 0x2c) = handle;

    if (!ok)
      goto clear_entry;

    cache_file_read_header_into_slot(i);

    if (csstrcmp(entry_ptr + 0x20, "01.10.12.2276") != 0) {
      ok = 0;
    }

    if (!FUN_001bcb80(entry_ptr, dvd_header))
      goto clear_entry;

    if (*(int *)(entry_ptr + 0x44) != *(int *)(dvd_header + 0x64))
      goto clear_entry;

    if (ok)
      goto next_slot;

  clear_entry:
    csmemset(entry_ptr - 0x20, 0, 0x800);

  next_slot:
    entry_ptr += 0x80c;
  }
}

/* FUN_001bda90 — initialize the cache IO system: create the sleep event and
 * the IO dispatcher thread (FUN_001bd3a0) with 0x4000 bytes of stack.
 * DAT_004e9248 = sleep_event handle, DAT_004e924c = thread handle.
 */
void FUN_001bda90(void)
{
  *(void **)0x4e9248 = CreateEventA(NULL, 0, 0, NULL);
  if (!*(void **)0x4e9248) {
    display_assert("cache_file_globals.sleep_event",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x4b2, 1);
    system_exit(-1);
  }
  *(void **)0x4e924c = CreateThread(NULL, 0x4000, FUN_001bd3a0, NULL, 0, NULL);
  if (!*(void **)0x4e924c) {
    display_assert("cache_file_globals.thread",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x4b6, 1);
    system_exit(-1);
  }
}

/* FUN_001bdb10 — allocate and initialize cache file globals.
 * Sets open_map_file_index=NONE, allocates request array (0x4000 bytes),
 * creates IO event+thread, and initializes the IO state.
 */
void FUN_001bdb10(void)
{
  *(int16_t *)0x4e9244 = -1;
  *(void **)0x4e9250 = debug_malloc(
    0x4000, 0, "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0xb7);
  if (!*(void **)0x4e9250) {
    display_assert("cache_file_globals.requests",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0xb8, 1);
    system_exit(-1);
  }
  FUN_001bda90();
  FUN_001bd5f0();
  FUN_001bc280();
}

/* cache_files_precache_map_begin (0x1bd910) — readable C lift (restored pre-naked). */

bool cache_files_precache_map_begin(char *map_name, bool show_error)
{
  char path[256];
  char header_buf[0x800];
  char *canonical;
  int16_t cache_idx;

  canonical = ((char *(*)(char *))0x19b0d0)(map_name);
  ((char *(*)(char *))0x19b0d0)(map_name);
  cache_idx = ((int16_t (*)(void))0x1bd1b0)();

  if (cache_idx == -1) {
    if (!FUN_001bcb80(canonical, header_buf)) {
      error(2, "couldn't find map '%s' on the DVD", canonical);
      if (show_error)
        ((void (*)(void))0xe8d20)();
      return 0;
    }

    {
      int copy_handle;
      int buffer;
      int16_t slot;
      int block;
      int file;
      int mapped;

      copy_handle = ((int (*)(bool))0x1ba250)(show_error);
      buffer = (int)xbox_texture_cache_steal_memory(copy_handle);
      slot = FUN_001bd210(
        *(int16_t *)(header_buf + 0x60), *(int *)(header_buf + 8));

      block = (int)FUN_001bc720(slot);
      csmemset((void *)(block + 0xc), 0, 0x800);

      *(uint8_t *)0x4e9220 = 1;
      *(int16_t *)0x4e9222 = slot;
      csstrncpy((char *)0x4e9224, canonical, 0x1f);
      *(uint8_t *)0x4e9243 = 0;

      ((int (*)(char *, const char *, ...))0x1d90f0)(
        path, "d:\\maps\\%s.map", canonical);
      error(2, "starting precaching of map '%s'", canonical);

      file = FUN_001bc7e0(slot);
      mapped = (int)FUN_001bc7a0(slot);
      FUN_001ba2f0(buffer, copy_handle, mapped, file, path);
    }
  }

  return 1;
}


/* cache_files_precache_map_end (0x1bda30) — readable C lift. */
void cache_files_precache_map_end(void)
{
  extern char DAT_002b8c98[];
  extern char DAT_002b8dc0[];
  short map_file_index;
  if (!*(unsigned char *)0x4e9220) {
    display_assert(DAT_002b8dc0, DAT_002b8c98, 0x3d4, 1);
    system_exit(-1);
  }
  FUN_001baf50();
  xbox_texture_cache_return_memory();
  map_file_index = *(short *)0x4e9222;
  FUN_001bcfb0(map_file_index);
  cache_file_read_header_into_slot(map_file_index);
  *(unsigned char *)0x4e9220 = 0;
  *(unsigned short *)0x4e9222 = 0xffff;
}

/* Load cached game state if the cached map metadata matches the currently
 * loaded scenario, map type, checksum, and difficulty. */
void cache_files_precache(void)
{
  char header[0x14c];

  if (!game_state_read_header_from_persistent_storage(
        header, (uint32_t *)(header + 0x148), sizeof(header), 0x345000, NULL)) {
    return;
  }

  if (csstrcmp(header + 0x104, "01.10.12.2276") != 0) {
    return;
  }

  {
    const char *scenario_name = tag_get_name(*(int *)0x326a08);
    if (csstrcmp(header + 0x4, scenario_name) != 0) {
      return;
    }
  }

  if (*(int *)header != *(int *)0x4ea9a0)
    return;
  if (*(int16_t *)(header + 0x124) != *(int16_t *)0x31fa94)
    return;
  if (*(int *)(header + 0x128) != FUN_001b9920())
    return;
  if (*(int16_t *)(header + 0x126) != main_get_difficulty())
    return;

  ((void (*)(void))game_state_callback_32eaa4)();
  FUN_001c0c20(*(void **)0x4ea994, 0x345000);
  game_difficulty_level_set(main_get_difficulty());
  game_state_call_after_load_procs();
  ((void (*)(void))game_state_callback_32eaa0)();
  main_lost_map();
  *(uint8_t *)0x4ea9a5 = game_state_write_to_file() != 0;
  main_start_time();
}
/* --- cache_files_windows.obj batch drafts (2026-07-26) --- */

/* cache_copy_initialize_read_data (0x1bb7d0) — readable C lift (restored pre-naked). */
void cache_copy_initialize_read_data(void)
{
  int ebx = 0;
  int ecx = 0;

  csmemset((void *)(uintptr_t)ebx, 0, 2048);
  FUN_001bb2d0();
  ((void(*)(void))FUN_001ba930)();
  /* test ecx, ecx -> je 0x1bb83a */
  display_assert((char *)0x002b89d4, (char *)0x002b839c, 1003, 0);
  system_exit(0);
  FUN_001bb190();
  ((void(*)(void))FUN_001ba8b0)();
  cache_file_header_verify((void *)(uintptr_t)ebx, (char *)0x002b89cc, 0);

  (void)ebx;
  (void)ecx;
}



/* FUN_001bb8a0 (0x1bb8a0) — readable C lift. */
void FUN_001bb8a0(void *obj)
{
  int idx = 0;
  short slot = 0;
  unsigned int bit;
  unsigned int *word;
  unsigned char *ptr;

  ptr = (unsigned char *)obj + 0xa78;
  while (slot < 8) {
    bit = 1u << (idx & 0x1f);
    word = (unsigned int *)((unsigned char *)obj + 0x994 + ((idx >> 5) * 4));
    if ((*word & bit) != 0) {
      display_assert((const char *)0x2b8878, (const char *)0x2b839c, 0x416, 1);
      system_exit(-1);
    }
    if (slot < 0 || slot >= 8) {
      display_assert((const char *)0x2b8580, (const char *)0x2b839c, 0x619, 1);
      system_exit(-1);
    }
    ((void (*)(void *, unsigned char *, int))FUN_001bb430)(obj, ptr, slot);
    *word |= bit;
    slot++;
    idx++;
    ptr += 2;
  }
}

/* 0x1bb970 */
void FUN_001bb970(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jle 0x1bb9d5 */
  /* test eax, eax -> je 0x1bb9d5 */
  /* test (char)eax, 2 -> je 0x1bb9d5 */
  display_assert((char *)0x002b8ad0, (char *)0x002b839c, 1075, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bba55 */
  /* test eax, eax -> jne 0x1bba55 */
  /* test eax, eax -> jle 0x1bba55 */
  /* cmp (int16_t)ecx, (int16_t)edi -> je 0x1bba13 */
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xabe] -> jle 0x1bba55 */
  /* cmp (int16_t)ecx, (int16_t)eax -> je 0x1bba2e */
  /* relift: cmp (int16_t)edx, word ptr [esi + 0xabe] -> je 0x1bba37 */
  /* cmp (int16_t)eax, 1 -> jl 0x1bba15 */
  FUN_001bb640();
  /* relift: cmp word ptr [esi + 0xabc], (int16_t)edi -> jne 0x1bbb52 */
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jge 0x1bbb52 */
  /* relift: cmp word ptr [esi + ecx*2 + 0xa88], (int16_t)edi -> je 0x1bba87 */
  /* cmp (int16_t)eax, 1 -> jl 0x1bba71 */
  physical_memory_protect((void *)(uintptr_t)eax, 0x00400000, 0);
  /* relift: cmp word ptr [esi + 0xabc], (int16_t)edi -> jne 0x1bbaf0 */
  display_assert((char *)0x002b8aa8, (char *)0x002b839c, 1124, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbb18 */
  display_assert((char *)0x002b8a70, (char *)0x002b839c, 1125, 0);
  system_exit(0);
  /* cmp edx, eax -> je 0x1bbb52 */
  display_assert((char *)0x002b8a00, (char *)0x002b839c, 1126, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
/* FUN_001bbb60 (0x1bbb60) — readable C lift (restored pre-naked). */
void FUN_001bbb60(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  SleepEx(0, 0);
  FUN_001bb970();
  /* test eax, eax -> jne 0x1bbc7f */
  /* test eax, eax -> je 0x1bbbb4 */
  display_assert((char *)0x002b8b8c, (char *)0x002b839c, 1149, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0xac2], 0 -> je 0x1bbbde */
  display_assert((char *)0x002b8b68, (char *)0x002b839c, 1150, 0);
  system_exit(0);
  ((void(*)(void))FUN_001ba9d0)();
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bbc21 */
  /* cmp (int16_t)edi, 8 -> jl 0x1bbc41 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1606, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebx + 4], 0x20000 -> je 0x1bbc7f */
  display_assert((char *)0x002b8b40, (char *)0x002b839c, 1163, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bbca9 */
  display_assert((char *)0x002b8b28, (char *)0x002b839c, 1172, 0);
  system_exit(0);
  /* cmp (int16_t)edi, -1 -> je 0x1bbe91 */
  /* test eax, eax -> jne 0x1bbd32 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bbccc */
  /* cmp (int16_t)edi, 1 -> jl 0x1bbcec */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1633, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bbd0b */
  /* cmp (int16_t)eax, 1 -> jl 0x1bbd2b */
  display_assert((char *)0x002b85c8, (char *)0x002b839c, 1642, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1bbb71 */
  /* test eax, eax -> je 0x1bbb71 */
  /* test (char)eax, (char)eax -> jne 0x1bbd5d */
  SwitchToThread();
  QueryPerformanceCounter((void *)0x004e5650);
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbd7a */
  QueryPerformanceCounter((void *)0x004e5658);
  FUN_001155e0(0, 0);
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* mem[0x004e561c] = edx */
  /* relift: cmp dword ptr [esi + 0xab4], 1 -> jle 0x1bbdd3 */
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5620] = ecx */
  /* test edi, edi -> je 0x1bbddc */
  /* cmp edi, 1 -> jne 0x1bbe29 */
  /* test eax, eax -> jne 0x1bbe0b */
  ((void(*)(void))acquire_read_request)();
  /* test eax, eax -> je 0x1bbe1b */
  /* cmp edi, 1 -> jne 0x1bbb71 */
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bbe91 */
  /* test eax, eax -> jne 0x1bbe4d */
  csprintf((char *)0x004e5510, (char *)0x002b8af0);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* simple_cache_copy_thread (0x1bbea0) — XBE naked draft (batch 248). */
#if defined(__clang__)
static int __stdcall (*const b1bbea0_c1d0336)(int handle, int timeout_ms) = WaitForSingleObject;
static void *(*const b1bbea0_memset)(void *, int, unsigned int) = csmemset;
static bool __stdcall (*const b1bbea0_c1d33e6)(void *counter) = QueryPerformanceCounter;
static void (*const b1bbea0_c1ba710)(void) = FUN_001ba710;
static void (*const b1bbea0_c1ba7c0)(void) = cache_copy_initialize_and_fill_with_garbage;
static void (*const b1bbea0_c1bb7d0)(void) = cache_copy_initialize_read_data;
static int (*const b1bbea0_c1155c0)(int z, char *version, int stream_size) = FUN_001155c0;
static bool (*const b1bbea0_c1b9ce0)(void *header, const char *path, int report_errors) = cache_file_header_verify;
static void (*const b1bbea0_c1bb8a0)(void) = FUN_001bb8a0;
static void *(*const b1bbea0_c1ba9d0)(void *, int16_t) = FUN_001ba9d0;
static void (*const b1bbea0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bbea0_exitfn)(int) = system_exit;
static bool __stdcall (*const b1bbea0_c1cfeaa)(void *handle) = SetEvent;
static void (*const b1bbea0_c1d00b9)(void) = FUN_001d00b9;
static void (*const b1bbea0_c1bb970)(void) = FUN_001bb970;
static void (*const b1bbea0_c1bbb60)(void) = FUN_001bbb60;
static void (*const b1bbea0_c1bab60)(void) = FUN_001bab60;
static void (*const b1bbea0_c1bb2d0)(void) = FUN_001bb2d0;
static int (*const b1bbea0_c115430)(int z) = FUN_00115430;
static int __stdcall (*const b1bbea0_c1cf900)(int handle) = CloseHandle;

__attribute__((naked, noinline))
void simple_cache_copy_thread(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x32ea98, %%esi\n\t"
      "leal 0x94c(%%esi), %%eax\n\t"
      "leal 0x990(%%esi), %%ebx\n\t"
      "leal 0x98c(%%esi), %%ecx\n\t"
      "leal 0x954(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".Lsimple_cache_copy_thread_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "pushl $-1\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0336]\n\t"
      "pushl $0x24\n\t"
      "xorl %%edi, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl $0x4e5610\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0x4e5678\n\t"
      "call *%[c1d33e6]\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1ba710]\n\t"
      "call *%[c1ba7c0]\n\t"
      "movl 0x32ea98, %%edx\n\t"
      "movl 0x950(%%edx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d0336]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsimple_cache_copy_thread_18\n\t"
      "pushl $0x4e5638\n\t"
      "call *%[c1d33e6]\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1bb7d0]\n\t"
      "pushl $0x38\n\t"
      "leal 0x908(%%esi), %%eax\n\t"
      "pushl $0x28ce40\n\t"
      "pushl %%eax\n\t"
      "movl %%edi, (%%eax)\n\t"
      "movl %%edi, 0x90c(%%esi)\n\t"
      "movl %%edi, 0x914(%%esi)\n\t"
      "movl %%edi, 0x918(%%esi)\n\t"
      "call *%[c1155c0]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d33e6]\n\t"
      "movl 0x4e5638, %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "movl 0x4e5610, %%ebx\n\t"
      "subl %%eax, %%edx\n\t"
      "pushl $1\n\t"
      "leal 0x104(%%esi), %%eax\n\t"
      "addl %%edx, %%ebx\n\t"
      "pushl $0x2b8c40\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, 0x4e5610\n\t"
      "call *%[c1b9ce0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsimple_cache_copy_thread_17\n\t"
      "movl 0x10c(%%esi), %%eax\n\t"
      "addl $0xfffff800, %%eax\n\t"
      "pushl %%esi\n\t"
      "movb $1, %%bl\n\t"
      "movl %%eax, 0xa9c(%%esi)\n\t"
      "movl %%eax, 0xa98(%%esi)\n\t"
      "call *%[c1bb8a0]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x950(%%eax), %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0336]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lsimple_cache_copy_thread_15\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lsimple_cache_copy_thread_2:\n\t"
      "cmpl %%edi, 0xa9c(%%esi)\n\t"
      "jle .Lsimple_cache_copy_thread_16\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lsimple_cache_copy_thread_15\n\t"
      "cmpl %%edi, 0x994(%%esi)\n\t"
      "je .Lsimple_cache_copy_thread_5\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0xaba(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1ba9d0]\n\t"
      "movl 0xab4(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "negl %%eax\n\t"
      "sbbb %%al, %%al\n\t"
      "incb %%al\n\t"
      "cmpl $1, %%ecx\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "jne .Lsimple_cache_copy_thread_3\n\t"
      "cmpw $-1, 0xabc(%%esi)\n\t"
      "jne .Lsimple_cache_copy_thread_3\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lsimple_cache_copy_thread_4\n\t"
      ".Lsimple_cache_copy_thread_3:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lsimple_cache_copy_thread_4:\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lsimple_cache_copy_thread_7\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lsimple_cache_copy_thread_8\n\t"
      ".Lsimple_cache_copy_thread_5:\n\t"
      "movl $0xc0, %%edi\n\t"
      ".Lsimple_cache_copy_thread_6:\n\t"
      "movl %%edi, %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "subl $0, %%eax\n\t"
      "je .Lsimple_cache_copy_thread_14\n\t"
      "subl $0xc0, %%eax\n\t"
      "je .Lsimple_cache_copy_thread_12\n\t"
      "subl $0x42, %%eax\n\t"
      "pushl $1\n\t"
      "je .Lsimple_cache_copy_thread_11\n\t"
      "pushl $0x36b\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x255ee8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lsimple_cache_copy_thread_14\n\t"
      ".Lsimple_cache_copy_thread_7:\n\t"
      "pushl $0x4e5668\n\t"
      "call *%[c1d33e6]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lsimple_cache_copy_thread_9\n\t"
      ".Lsimple_cache_copy_thread_8:\n\t"
      "pushl $0x4e5670\n\t"
      "call *%[c1d33e6]\n\t"
      ".Lsimple_cache_copy_thread_9:\n\t"
      "pushl $0x4e5660\n\t"
      "call *%[c1d33e6]\n\t"
      "movl 0x958(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cfeaa]\n\t"
      "movl 0x950(%%esi), %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0x1388\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d00b9]\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c1d33e6]\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl 0x4e5660, %%edx\n\t"
      "movl 0x4e5624, %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%ecx, 0x4e5624\n\t"
      "je .Lsimple_cache_copy_thread_10\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d33e6]\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl 0x4e5670, %%ecx\n\t"
      "movl 0x4e562c, %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, 0x4e562c\n\t"
      ".Lsimple_cache_copy_thread_10:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lsimple_cache_copy_thread_6\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d33e6]\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "movl 0x4e5668, %%edx\n\t"
      "movl 0x4e5628, %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "movl %%eax, 0x4e5628\n\t"
      "jmp .Lsimple_cache_copy_thread_6\n\t"
      ".Lsimple_cache_copy_thread_11:\n\t"
      "pushl $0x362\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8c20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%edx\n\t"
      "addl $0x14, %%esp\n\t"
      "orl $2, %%edx\n\t"
      "movl %%edx, 0x904(%%eax)\n\t"
      "jmp .Lsimple_cache_copy_thread_14\n\t"
      ".Lsimple_cache_copy_thread_12:\n\t"
      "movl 0x998(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsimple_cache_copy_thread_13\n\t"
      "pushl $1\n\t"
      "pushl $0x351\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8ba8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lsimple_cache_copy_thread_13:\n\t"
      "call *%[c1bb970]\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1bbb60]\n\t"
      "movl 0x32ea98, %%eax\n\t"
      "movl 0x904(%%eax), %%ebx\n\t"
      "andb $7, %%bl\n\t"
      "negb %%bl\n\t"
      "sbbb %%bl, %%bl\n\t"
      "incb %%bl\n\t"
      ".Lsimple_cache_copy_thread_14:\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl 0x950(%%ecx), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d0336]\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lsimple_cache_copy_thread_2\n\t"
      ".Lsimple_cache_copy_thread_15:\n\t"
      "cmpl %%edi, 0xa9c(%%esi)\n\t"
      ".Lsimple_cache_copy_thread_16:\n\t"
      "jne .Lsimple_cache_copy_thread_17\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1bab60]\n\t"
      "pushl $1\n\t"
      "pushl %%edi\n\t"
      "leal 0x104(%%esi), %%eax\n\t"
      "pushl $0x800\n\t"
      "pushl %%eax\n\t"
      "movl %%esi, %%edi\n\t"
      "call *%[c1bb2d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      ".Lsimple_cache_copy_thread_17:\n\t"
      "leal 0x908(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c115430]\n\t"
      "movl %%edi, (%%ebx)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "movl %%edi, 0x90c(%%esi)\n\t"
      "movl %%edi, 0x914(%%esi)\n\t"
      "movl %%edi, 0x918(%%esi)\n\t"
      ".Lsimple_cache_copy_thread_18:\n\t"
      "movl %%esi, %%eax\n\t"
      "call *%[c1bab60]\n\t"
      "movl (%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1cf900]\n\t"
      "leal -0x3c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edi, (%%ebx)\n\t"
      "call *%[c1d33e6]\n\t"
      "movl 0x4e5678, %%eax\n\t"
      "movl 0x4e5630, %%ecx\n\t"
      "movl -0x3c(%%ebp), %%edx\n\t"
      "subl %%eax, %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl %%edx, %%ecx\n\t"
      "movl %%ecx, 0x4e5630\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, (%%eax)\n\t"
      "call *%[c1cfeaa]\n\t"
      "jmp .Lsimple_cache_copy_thread_1\n\t"
      :
      : [c1d0336] "m"(b1bbea0_c1d0336), [memset] "m"(b1bbea0_memset), [c1d33e6] "m"(b1bbea0_c1d33e6), [c1ba710] "m"(b1bbea0_c1ba710), [c1ba7c0] "m"(b1bbea0_c1ba7c0), [c1bb7d0] "m"(b1bbea0_c1bb7d0), [c1155c0] "m"(b1bbea0_c1155c0), [c1b9ce0] "m"(b1bbea0_c1b9ce0), [c1bb8a0] "m"(b1bbea0_c1bb8a0), [c1ba9d0] "m"(b1bbea0_c1ba9d0), [assert] "m"(b1bbea0_assert), [exitfn] "m"(b1bbea0_exitfn), [c1cfeaa] "m"(b1bbea0_c1cfeaa), [c1d00b9] "m"(b1bbea0_c1d00b9), [c1bb970] "m"(b1bbea0_c1bb970), [c1bbb60] "m"(b1bbea0_c1bbb60), [c1bab60] "m"(b1bbea0_c1bab60), [c1bb2d0] "m"(b1bbea0_c1bb2d0), [c115430] "m"(b1bbea0_c115430), [c1cf900] "m"(b1bbea0_c1cf900)
      : "memory");
}
#else
#error "simple_cache_copy_thread: clang naked draft required"
#endif


/* cache_files_dispose (0x1bc360) — readable C lift. */
void cache_files_dispose(void)
{
  extern char DAT_002b8c68[];
  extern char DAT_002b8c98[];
  if (*(int16_t *)0x4e9244 != -1) {
    display_assert(DAT_002b8c68, DAT_002b8c98, 0xc9, 1);
    system_exit(-1);
  }
  debug_free(*(void **)0x4e9250, DAT_002b8c98, 0xcb);
}

/* FUN_001bc3b0 (0x1bc3b0) — readable C lift (restored pre-naked). */
void FUN_001bc3b0(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test edi, edi -> jne 0x1bc3d7 */
  display_assert((char *)0x002b8d30, (char *)0x002b8c98, 384, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 8], -1 -> jne 0x1bc3fd */
  display_assert((char *)0x002b8d14, (char *)0x002b8c98, 385, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1bc421 */
  display_assert((char *)0x002b8d08, (char *)0x002b8c98, 386, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc448 */
  display_assert((char *)0x00267900, (char *)0x002b8c98, 387, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc46f */
  display_assert((char *)0x002b8cf8, (char *)0x002b8c98, 388, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1bc493 */
  display_assert((char *)0x002b8ce4, (char *)0x002b8c98, 389, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)esi, 0, 20);
  SleepEx(0, 0);
  SetLastError(0);
  /* test eax, eax -> jne 0x1bc547 */
  xapi_GetLastError();
  /* cmp eax, 8 -> je 0x1bc523 */
  /* cmp eax, 0x5aa -> je 0x1bc523 */
  /* cmp eax, 0x6f8 -> je 0x1bc523 */
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b8cc4);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  SleepEx(0, 0);
  SetLastError(0);
  /* test eax, eax -> je 0x1bc4d7 */
  /* relift: cmp byte ptr [esi], 0 -> jne 0x1bc578 */
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> jne 0x1bc578 */
  /* relift: cmp byte ptr [esi], 0 -> je 0x1bc560 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc58c */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5ac */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* FUN_001bc5c0 (0x1bc5c0) — readable C lift. */
short FUN_001bc5c0(void)
{
  extern char DAT_002b8c98[];
  extern char DAT_002b8d48[];
  char retried = 0;
  for (;;) {
    short i;
    for (i = 0; i < 0x200; i++) {
      unsigned char *base = *(unsigned char **)0x4e9250;
      if ((uint16_t)i >= 0x200u) {
        display_assert(DAT_002b8d48, DAT_002b8c98, 0x260, true);
        system_exit(-1);
      }
      if (!base[(int)i * 0x20 + 0x1d])
        return i;
    }
    if (!retried)
      retried = 1;
  }
}

/* FUN_001bcc10 (0x1bcc10) — readable C lift.
 * Forward to FUN_001bc3b0 with EDI = format string 0x1d19e7. */
void FUN_001bcc10(int a, int b, int edx_arg /*@<edx>*/, int ecx_arg /*@<ecx>*/, int eax_arg /*@<eax>*/)
{
  register int edi asm("edi") = 0x1d19e7;
  (void)edi;
  ((void (*)(int, int, int, int, int))(void *)FUN_001bc3b0)(a, b, edx_arg, ecx_arg, eax_arg);
}

/* FUN_001bcc30 (0x1bcc30) — readable C lift.
 * Forward to FUN_001bc3b0 with EDI = format string 0x1d1a38. */
void FUN_001bcc30(int a, int b, int edx_arg /*@<edx>*/, int ecx_arg /*@<ecx>*/, int eax_arg /*@<eax>*/)
{
  register int edi asm("edi") = 0x1d1a38;
  (void)edi;
  ((void (*)(int, int, int, int, int))(void *)FUN_001bc3b0)(a, b, edx_arg, ecx_arg, eax_arg);
}

/* FUN_001bd1b0 (0x1bd1b0) — readable C lift. */
short FUN_001bd1b0(const char *name)
{
  extern char DAT_002b8c98[];
  extern char DAT_002b8de4[];
  short i;
  for (i = 0; i < 6; i++) {
    if (i < 0 || i >= 6) {
      display_assert(DAT_002b8de4, DAT_002b8c98, 0x485, 1);
      system_exit(-1);
    }
    if (crt_stricmp(name, (const char *)(0x4e6204 + (int)i * 0x80c)) == 0)
      return i;
  }
  return (short)0xffff;
}

/* FUN_001bd210 (0x1bd210) — XBE naked draft (batch 248). */
#if defined(__clang__)
static void (*const b1bd210_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bd210_exitfn)(int) = system_exit;
static int (*const b1bd210_c1bc7e0)(short map_file_index) = FUN_001bc7e0;
static void (*const b1bd210_c1d0669)(void) = FUN_001d0669;

__attribute__((naked, noinline))
int16_t FUN_001bd210(int16_t map_type __attribute__((unused)), int header_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%esi\n\t"
      "orl $0xffffffff, %%esi\n\t"
      "subl $0, %%eax\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "je .LFUN_001bd210_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001bd210_2\n\t"
      "decl %%eax\n\t"
      "je .LFUN_001bd210_1\n\t"
      "pushl $1\n\t"
      "pushl $0x461\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x10(%%ebp), %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001bd210_4\n\t"
      ".LFUN_001bd210_1:\n\t"
      "movl $2, %%edi\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001bd210_4\n\t"
      ".LFUN_001bd210_2:\n\t"
      "movl $3, %%edi\n\t"
      "movl $5, -0x8(%%ebp)\n\t"
      "jmp .LFUN_001bd210_4\n\t"
      ".LFUN_001bd210_3:\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl $1, -0x8(%%ebp)\n\t"
      ".LFUN_001bd210_4:\n\t"
      "cmpw -0x8(%%ebp), %%di\n\t"
      "jg .LFUN_001bd210_15\n\t"
      "pushl %%ebx\n\t"
      "movswl %%di, %%ebx\n\t"
      "imull $0x80c, %%ebx, %%ebx\n\t"
      "addl $0x4e61d8, %%ebx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001bd210_5:\n\t"
      "cmpw %%di, 0x4e9244\n\t"
      "je .LFUN_001bd210_14\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001bd210_6\n\t"
      "cmpw $6, %%di\n\t"
      "jl .LFUN_001bd210_7\n\t"
      ".LFUN_001bd210_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd210_7:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001bd210_8\n\t"
      "cmpw $6, %%di\n\t"
      "jl .LFUN_001bd210_9\n\t"
      ".LFUN_001bd210_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x49d\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd210_9:\n\t"
      "cmpw $1, %%di\n\t"
      "jg .LFUN_001bd210_10\n\t"
      "movl $0x11600000, %%eax\n\t"
      "jmp .LFUN_001bd210_11\n\t"
      ".LFUN_001bd210_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $2, %%di\n\t"
      "setg %%al\n\t"
      "decl %%eax\n\t"
      "andl $0xff400000, %%eax\n\t"
      "addl $0x2f00000, %%eax\n\t"
      ".LFUN_001bd210_11:\n\t"
      "cmpl 0x8(%%ebp), %%eax\n\t"
      "jle .LFUN_001bd210_14\n\t"
      "cmpw $-1, %%si\n\t"
      "je .LFUN_001bd210_12\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c1bc7e0]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c1bc7e0]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jl .LFUN_001bd210_12\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "leal 0x4(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0669]\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_001bd210_13\n\t"
      ".LFUN_001bd210_12:\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      ".LFUN_001bd210_13:\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_001bd210_14:\n\t"
      "incl %%edi\n\t"
      "addl $0x80c, %%ebx\n\t"
      "cmpw -0x8(%%ebp), %%di\n\t"
      "jle .LFUN_001bd210_5\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001bd210_15:\n\t"
      "cmpw %%si, 0x4e9244\n\t"
      "jne .LFUN_001bd210_16\n\t"
      "pushl $1\n\t"
      "pushl $0x47d\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8f78\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd210_16:\n\t"
      "popl %%edi\n\t"
      "movw %%si, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1bd210_assert), [exitfn] "m"(b1bd210_exitfn), [c1bc7e0] "m"(b1bd210_c1bc7e0), [c1d0669] "m"(b1bd210_c1d0669)
      : "memory");
}
#else
#error "FUN_001bd210: clang naked draft required"
#endif


/* FUN_001bd3a0 (0x1bd3a0) — XBE naked draft (batch 253). */
#if defined(__clang__)
static void (*const b1bd3a0_c1d00b9)(void) = FUN_001d00b9;
static void (*const b1bd3a0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bd3a0_exitfn)(int) = system_exit;
static void (*const b1bd3a0_c1bc3b0)(void) = FUN_001bc3b0;

__attribute__((naked, noinline))
void FUN_001bd3a0(void)
{
  __asm__ volatile(
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      ".LFUN_001bd3a0_1:\n\t"
      "movl 0x4e9248, %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d00b9]\n\t"
      "cmpl $0xc0, %%eax\n\t"
      "je .LFUN_001bd3a0_1\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001bd3a0_2:\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_001bd3a0_3:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_001bd3a0_4\n\t"
      "cmpw $0x200, %%di\n\t"
      "jl .LFUN_001bd3a0_5\n\t"
      ".LFUN_001bd3a0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0x260\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8d48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd3a0_5:\n\t"
      "movl 0x4e9250, %%ecx\n\t"
      "leal (%%ebx,%%ecx,1), %%eax\n\t"
      "movb 0x1d(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_001bd3a0_7\n\t"
      "movb 0x1e(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_001bd3a0_7\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001bd3a0_6\n\t"
      "movb 0x1c(%%esi), %%dl\n\t"
      "cmpb 0x1c(%%eax), %%dl\n\t"
      "jbe .LFUN_001bd3a0_7\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "cmpl 0x8(%%eax), %%ecx\n\t"
      "jbe .LFUN_001bd3a0_7\n\t"
      ".LFUN_001bd3a0_6:\n\t"
      "movl %%eax, %%esi\n\t"
      ".LFUN_001bd3a0_7:\n\t"
      "incl %%edi\n\t"
      "addl $0x20, %%ebx\n\t"
      "cmpw $0x200, %%di\n\t"
      "jl .LFUN_001bd3a0_3\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_001bd3a0_1\n\t"
      "movl 0x4e9244, %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%eax, %%edi\n\t"
      "jl .LFUN_001bd3a0_8\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_001bd3a0_9\n\t"
      ".LFUN_001bd3a0_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd3a0_9:\n\t"
      "movb 0x1e(%%esi), %%al\n\t"
      "movswl %%di, %%edx\n\t"
      "imull $0x80c, %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl 0x4e61d8(%%edx), %%edi\n\t"
      "je .LFUN_001bd3a0_10\n\t"
      "pushl $1\n\t"
      "pushl $0x4fc\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8fb4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bd3a0_10:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "movl $0x1bc860, %%ebx\n\t"
      "movl $0x1d19e7, %%edi\n\t"
      "movb $1, 0x1e(%%esi)\n\t"
      "call *%[c1bc3b0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_001bd3a0_2\n\t"
      :
      : [c1d00b9] "m"(b1bd3a0_c1d00b9), [assert] "m"(b1bd3a0_assert), [exitfn] "m"(b1bd3a0_exitfn), [c1bc3b0] "m"(b1bd3a0_c1bc3b0)
      : "memory");
}
#else
#error "FUN_001bd3a0: clang naked draft required"
#endif


/* cache_file_open (0x1bd4d0) — readable C lift (restored pre-naked). */
void cache_file_open(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  ((void(*)(void))FUN_001bd1b0)();
  display_assert((char *)0x002b8fe4, (char *)0x002b8c98, 214, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1bd52a */
  display_assert((char *)0x00265d1c, (char *)0x002b8c98, 215, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x4e9244], -1 -> je 0x1bd554 */
  display_assert((char *)0x002b8c68, (char *)0x002b8c98, 217, 0);
  system_exit(0);
  /* cmp (int16_t)esi, -1 -> jne 0x1bd57a */
  display_assert((char *)0x002b8fcc, (char *)0x002b8c98, 218, 0);
  system_exit(0);
  csmemset((void *)(uintptr_t)eax, 0, 16384);
  /* cmp (int16_t)esi, 6 -> jl 0x1bd5c1 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edi, (void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* --- cache_files_windows.obj orphan shells (2026-07-26) --- */

/* FUN_001bc280 (0x1bc280) — XBE naked draft (batch 263). */
#if defined(__clang__)
static bool __stdcall (*const b1bc280_c1d33fb)(void *freq) = QueryPerformanceFrequency;
static void (*const b1bc280_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bc280_exitfn)(int) = system_exit;
static void * __stdcall (*const b1bc280_c1cfded)(void *security, int manual_reset, int initial_state, const char *name) = CreateEventA;
static void * __stdcall (*const b1bc280_c1cfd8c)(void *security, int stack_size, void *func, void *param, int flags, int *thread_id) = CreateThread;

__attribute__((naked, noinline))
void FUN_001bc280(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d33fb]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_001bc280_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1e7\n\t"
      "pushl $0x2b839c\n\t"
      "pushl $0x2b8c54\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001bc280_1:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "movl %%ecx, 0x32ea9c\n\t"
      "call *%[c1cfded]\n\t"
      "movl 0x32ea98, %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "movl %%eax, 0x954(%%edx)\n\t"
      "call *%[c1cfded]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "movl %%eax, 0x94c(%%ecx)\n\t"
      "call *%[c1cfded]\n\t"
      "movl 0x32ea98, %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "movl %%eax, 0x950(%%edx)\n\t"
      "call *%[c1cfded]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0x1bbea0\n\t"
      "movl %%eax, 0x958(%%ecx)\n\t"
      "pushl $0x4000\n\t"
      "movl $0x1ba660, 0x928(%%ecx)\n\t"
      "pushl $0\n\t"
      "movl $0x1ba6c0, 0x92c(%%ecx)\n\t"
      "call *%[c1cfd8c]\n\t"
      "movl 0x32ea98, %%ecx\n\t"
      "movl %%eax, 0x95c(%%ecx)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1d33fb] "m"(b1bc280_c1d33fb), [assert] "m"(b1bc280_assert), [exitfn] "m"(b1bc280_exitfn), [c1cfded] "m"(b1bc280_c1cfded), [c1cfd8c] "m"(b1bc280_c1cfd8c)
      : "memory");
}
#else
#error "FUN_001bc280: clang naked draft required"
#endif


/* FUN_001bc620 (0x1bc620) — readable C lift. */
void FUN_001bc620(void)
{
  extern char DAT_002b8c98[];
  extern char DAT_002b8d90[];
  extern char DAT_002b8d48[];
  short i;
  int off;
  if (*(int16_t *)0x4e9244 == (int16_t)0xffff) {
    display_assert(DAT_002b8d90, DAT_002b8c98, 0x285, true);
    system_exit(-1);
  }
  off = 0;
  for (i = 0; i < 0x200; i++) {
    unsigned char *p;
    if ((uint16_t)i >= 0x200u) {
      display_assert(DAT_002b8d48, DAT_002b8c98, 0x260, true);
      system_exit(-1);
    }
    p = *(unsigned char **)0x4e9250 + off + 0x1d;
    while (*p)
      ;
    off += 0x20;
  }
}

/* cache_file_read_header_into_slot (0x1bd020) — XBE naked draft (batch 84). */
#if defined(__clang__)
static void (*const b1bd020_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1bd020_exitfn)(int) = system_exit;
static int (*const b1bd020_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b1bd020_c1d18aa)(void) = FUN_001d18aa;
static void (*const b1bd020_c1bc3b0)(void) = FUN_001bc3b0;
static unsigned int __stdcall (*const b1bd020_c1d01c4)(unsigned int milliseconds, int alertable) = SleepEx;
static bool (*const b1bd020_c1b9ce0)(void *header, const char *path, int report_errors) = cache_file_header_verify;
static void *(*const b1bd020_memset)(void *, int, unsigned int) = csmemset;
static int (*const b1bd020_c1d2240)(void) = xapi_GetLastError;
static char * (*const b1bd020_c8d9d0)(char *buffer, const char *format, ...) = csprintf;

__attribute__((naked, noinline))
void cache_file_read_header_into_slot(short map_file_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x124, %%esp\n\t"
      "pushl %%esi\n\t"
      "movw 0x8(%%ebp), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lcache_file_read_header_into_slot_1\n\t"
      "cmpw $6, %%si\n\t"
      "jl .Lcache_file_read_header_into_slot_2\n\t"
      ".Lcache_file_read_header_into_slot_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcache_file_read_header_into_slot_2:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "imull $0x80c, %%ecx, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "leal -0x124(%%ebp), %%edx\n\t"
      "leal 0x4e61d8(%%ecx), %%esi\n\t"
      "pushl $0x2b8e24\n\t"
      "pushl %%edx\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $0\n\t"
      "leal 0x4(%%esi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1d18aa]\n\t"
      "movl (%%esi), %%eax\n\t"
      "leal -0x1(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "pushl $0x800\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "movl $0x1bc8f0, %%ebx\n\t"
      "leal -0x24(%%ebp), %%esi\n\t"
      "movl $0x1d19e7, %%edi\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "call *%[c1bc3b0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "jne .Lcache_file_read_header_into_slot_4\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lcache_file_read_header_into_slot_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x1388\n\t"
      "call *%[c1d01c4]\n\t"
      "cmpl $0xc0, %%eax\n\t"
      "jne .Lcache_file_read_header_into_slot_4\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcache_file_read_header_into_slot_3\n\t"
      ".Lcache_file_read_header_into_slot_4:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcache_file_read_header_into_slot_5\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      "pushl $0\n\t"
      "leal -0x124(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1b9ce0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcache_file_read_header_into_slot_8\n\t"
      "pushl $0x800\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl $8\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcache_file_read_header_into_slot_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x42e\n\t"
      "pushl $0x2b8c98\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b8f4c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lcache_file_read_header_into_slot_6\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .Lcache_file_read_header_into_slot_7\n\t"
      ".Lcache_file_read_header_into_slot_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x485\n\t"
      "pushl $0x2b8c98\n\t"
      "pushl $0x2b8de4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lcache_file_read_header_into_slot_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl $0xffffffff, (%%eax)\n\t"
      ".Lcache_file_read_header_into_slot_8:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1bd020_assert), [exitfn] "m"(b1bd020_exitfn), [c1d90f0] "m"(b1bd020_c1d90f0), [c1d18aa] "m"(b1bd020_c1d18aa), [c1bc3b0] "m"(b1bd020_c1bc3b0), [c1d01c4] "m"(b1bd020_c1d01c4), [c1b9ce0] "m"(b1bd020_c1b9ce0), [memset] "m"(b1bd020_memset), [c1d2240] "m"(b1bd020_c1d2240), [c8d9d0] "m"(b1bd020_c8d9d0)
      : "memory");
}
#else
#error "cache_file_read_header_into_slot: clang naked draft required"
#endif

