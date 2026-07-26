/* Cache file precaching system for Xbox. Manages background copying of
 * map files from DVD to the hard drive cache partition. */

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

/* Cache file slot accessor helpers. All take map_file_index in @<si>.
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
 * buffer in @<ecx>, index in @<eax> (caller sign-extends short to int). */
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
bool FUN_001bcb80(const char *map_name /* @<eax> */,
                  void *header_buf /* @<edi> */)
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
 * map_file_index+1 up to but not including 20 (@<ax> = map_file_index).
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

/* FUN_001bcfb0 — open/map the cache file for the given slot (@<ax> =
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

/* Begin precaching a map from DVD to the cache partition. Returns true
 * if the copy was already done or was successfully started. */
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

/* End the current map precache operation. Cleans up resources and
 * resets the precache state. */
void cache_files_precache_map_end(void)
{
  if (!*(uint8_t *)0x4e9220) {
    display_assert("cache_file_globals.copy_in_progress",
                   "c:\\halo\\SOURCE\\cache\\cache_files_windows.c", 0x3d4, 1);
    system_exit(-1);
  }

  ((void (*)(void))0x1baf50)();
  ((void (*)(void))0x1beb10)();
  FUN_001bcfb0(*(int16_t *)0x4e9222);
  ((void (*)(int16_t))0x1bd020)(*(int16_t *)0x4e9222);

  *(uint8_t *)0x4e9220 = 0;
  *(int16_t *)0x4e9222 = -1;
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

/* 0x1bb7d0 */
void cache_copy_initialize_read_data(void)
{
  int ebx = 0;
  int ecx = 0;

  csmemset((void *)(uintptr_t)ebx, 0, 2048);
  FUN_001bb2d0();
  FUN_001ba930();
  /* test ecx, ecx -> je 0x1bb83a */
  display_assert((char *)0x002b89d4, (char *)0x002b839c, 1003, 0);
  system_exit(0);
  FUN_001bb190();
  FUN_001ba8b0();
  cache_file_header_verify((void *)(uintptr_t)ebx, (char *)0x002b89cc, 0);

  (void)ebx;
  (void)ecx;
}

/* 0x1bb8a0 */
void FUN_001bb8a0(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: test dword ptr [esi], ebx -> je 0x1bb8fe */
  display_assert((char *)0x002b8878, (char *)0x002b839c, 1046, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bb909 */
  /* cmp (int16_t)edi, 8 -> jl 0x1bb929 */
  display_assert((char *)0x002b8580, (char *)0x002b839c, 1561, 0);
  system_exit(0);
  FUN_001bb430();

  (void)ebx;
  (void)esi;
  (void)edi;
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

/* 0x1bbb60 */
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
  FUN_001ba9d0();
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
  acquire_read_request();
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

/* 0x1bbea0 */
void simple_cache_copy_thread(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  WaitForSingleObject(0, 0);
  csmemset((void *)0x004e5610, 0, 36);
  QueryPerformanceCounter((void *)0x004e5678);
  FUN_001ba710();
  cache_copy_initialize_and_fill_with_garbage();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bc22b */
  QueryPerformanceCounter((void *)0x004e5638);
  cache_copy_initialize_read_data();
  FUN_001155c0(0, (char *)0x0028ce40, 56);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e5610] = ebx */
  cache_file_header_verify((void *)(uintptr_t)eax, (char *)0x002b8c40, 0);
  /* test (char)eax, (char)eax -> je 0x1bc205 */
  FUN_001bb8a0();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> je 0x1bc1db */
  /* relift: cmp dword ptr [esi + 0xa9c], edi -> jle 0x1bc1e1 */
  /* test (char)ebx, (char)ebx -> je 0x1bc1db */
  /* relift: cmp dword ptr [esi + 0x994], edi -> je 0x1bc03b */
  FUN_001ba9d0();
  /* relift: cmp word ptr [esi + 0xabc], -1 -> jne 0x1bc031 */
  /* test (char)eax, (char)eax -> jne 0x1bc086 */
  /* test (char)ebx, (char)ebx -> jne 0x1bc094 */
  display_assert((char *)0x00255ee8, (char *)0x002b839c, 875, 0);
  system_exit(0);
  QueryPerformanceCounter((void *)0x004e5668);
  /* test (char)ebx, (char)ebx -> je 0x1bc09e */
  QueryPerformanceCounter((void *)0x004e5670);
  QueryPerformanceCounter((void *)0x004e5660);
  SetEvent((void *)(uintptr_t)eax);
  FUN_001d00b9();
  QueryPerformanceCounter((void *)(uintptr_t)edx);
  /* mem[0x004e5624] = ecx */
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e562c] = eax */
  /* test (char)eax, (char)eax -> je 0x1bc040 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* mem[0x004e5628] = eax */
  display_assert((char *)0x002b8c20, (char *)0x002b839c, 866, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1bc19d */
  display_assert((char *)0x002b8ba8, (char *)0x002b839c, 849, 0);
  system_exit(0);
  FUN_001bb970();
  FUN_001bbb60();
  WaitForSingleObject(0, 0);
  /* test eax, eax -> jne 0x1bbfe0 */
  /* relift: cmp dword ptr [esi + 0xa9c], edi -> jne 0x1bc205 */
  FUN_001bab60();
  FUN_001bb2d0();
  FUN_00115430(0);
  FUN_001bab60();
  CloseHandle(0);
  QueryPerformanceCounter((void *)(uintptr_t)ecx);
  /* mem[0x004e5630] = ecx */
  SetEvent((void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1bc360 */
void cache_files_dispose(void)
{
  int eax = 0;

  /* relift: cmp word ptr [0x4e9244], -1 -> je 0x1bc38a */
  display_assert((char *)0x002b8c68, (char *)0x002b8c98, 201, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)eax, (char *)0x002b8c98, 203);

  (void)eax;
}

/* 0x1bc3b0 */
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

/* 0x1bc5c0 */
short FUN_001bc5c0(void)
{
  int ebx = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc5d2 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5f2 */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test dl, dl -> je 0x1bc616 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc5c6 */
  /* test (char)ebx, (char)ebx -> jne 0x1bc5c4 */
  return 0;

  (void)ebx;
  (void)edx;
  (void)esi;
}

/* 0x1bcc10 */
void FUN_001bcc10(void)
{
  FUN_001bc3b0();
}

/* 0x1bcc30 */
void FUN_001bcc30(void)
{
  FUN_001bc3b0();
}

/* 0x1bd1b0 */
void FUN_001bd1b0(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bd1be */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd1de */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  crt_stricmp((char *)(uintptr_t)edi, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bd207 */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd1b3 */

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x1bd210 */
int16_t FUN_001bd210(int16_t map_type, int header_size)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0, (char *)0x002b8c98, 1121, 0);
  system_exit(0);
  /* relift: cmp (int16_t)edi, word ptr [ebp - 8] -> jg 0x1bd367 */
  /* relift: cmp word ptr [0x4e9244], (int16_t)edi -> je 0x1bd355 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd2a8 */
  /* cmp (int16_t)edi, 6 -> jl 0x1bd2c8 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd2d3 */
  /* cmp (int16_t)edi, 6 -> jl 0x1bd2f3 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1181, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 1 -> jg 0x1bd300 */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jle 0x1bd355 */
  /* cmp (int16_t)esi, -1 -> je 0x1bd34c */
  FUN_001bc7e0(0);
  FUN_001bc7e0(0);
  /* cmp ecx, eax -> jl 0x1bd34c */
  FUN_001d0669();
  /* test eax, eax -> jle 0x1bd352 */
  /* relift: cmp (int16_t)edi, word ptr [ebp - 8] -> jle 0x1bd290 */
  /* relift: cmp word ptr [0x4e9244], (int16_t)esi -> jne 0x1bd390 */
  display_assert((char *)0x002b8f78, (char *)0x002b8c98, 1149, 0);
  system_exit(0);
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1bd3a0 */
void FUN_001bd3a0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d00b9();
  /* cmp eax, 0xc0 -> je 0x1bd3a3 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1bd3d2 */
  /* cmp (int16_t)edi, 0x200 -> jl 0x1bd3f2 */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* test (char)ecx, (char)ecx -> je 0x1bd41f */
  /* test (char)ecx, (char)ecx -> jne 0x1bd41f */
  /* test esi, esi -> je 0x1bd41d */
  /* relift: cmp dl, byte ptr [eax + 0x1c] -> jbe 0x1bd41f */
  /* relift: cmp ecx, dword ptr [eax + 8] -> jbe 0x1bd41f */
  /* cmp (int16_t)edi, 0x200 -> jl 0x1bd3c6 */
  /* test esi, esi -> je 0x1bd3a3 */
  /* cmp (int16_t)eax, 6 -> jl 0x1bd464 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  display_assert((char *)0x002b8fb4, (char *)0x002b8c98, 1276, 0);
  system_exit(0);
  FUN_001bc3b0();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1bd4d0 */
void cache_file_open(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001bd1b0();
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

/* 0x1bc280 */
void FUN_001bc280(void)
{
  int eax = 0;
  int ecx = 0;

  QueryPerformanceFrequency((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1bc2b6 */
  display_assert((char *)0x002b8c54, (char *)0x002b839c, 487, 0);
  system_exit(0);
  /* mem[0x0032ea9c] = ecx */
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateEventA((void *)0, 0, 0, (char *)0);
  CreateThread((void *)0, 16384, (void *)0x001bbea0, (void *)0, 0, (void *)0);

  (void)eax;
  (void)ecx;
}

/* 0x1bc620 */
void FUN_001bc620(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: cmp word ptr [0x4e9244], -1 -> jne 0x1bc64a */
  display_assert((char *)0x002b8d90, (char *)0x002b8c98, 645, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bc65c */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc67c */
  display_assert((char *)0x002b8d48, (char *)0x002b8c98, 608, 0);
  system_exit(0);
  /* relift: cmp byte ptr [eax], 0 -> jne 0x1bc685 */
  /* cmp (int16_t)esi, 0x200 -> jl 0x1bc650 */

  (void)eax;
  (void)esi;
}

/* 0x1bd020 */
void cache_file_read_header_into_slot(short map_file_index)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x1bd039 */
  /* cmp (int16_t)esi, 6 -> jl 0x1bd059 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002b8e24);
  FUN_001d18aa();
  FUN_001bc3b0();
  SleepEx(5000, 0);
  /* cmp eax, 0xc0 -> jne 0x1bd0ea */
  /* test (char)eax, (char)eax -> je 0x1bd0d0 */
  /* test (char)eax, (char)eax -> je 0x1bd133 */
  cache_file_header_verify((void *)(uintptr_t)esi, (char *)(uintptr_t)ecx, 0);
  /* test (char)eax, (char)eax -> jne 0x1bd19f */
  csmemset((void *)(uintptr_t)esi, 0, 2048);
  csmemset((void *)(uintptr_t)edx, 0, 0);
  xapi_GetLastError();
  csprintf((char *)0x005ab100, (char *)0x002b8f4c);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1bd176 */
  /* cmp (int16_t)eax, 6 -> jl 0x1bd196 */
  display_assert((char *)0x002b8de4, (char *)0x002b8c98, 1157, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}
