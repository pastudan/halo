#include <stdint.h>
#define FILE_REF_MAGIC 0x66696C6F

#define FIND_FILES_RECURSIVE_BIT 1
#define FIND_FILES_DIRECTORIES_BIT 2

typedef int(__stdcall *find_first_file_fn)(const char *path, void *find_data);
typedef bool(__stdcall *find_next_file_fn)(int handle, void *find_data);
typedef bool(__stdcall *close_handle_fn)(int handle);
typedef int(__stdcall *create_file_fn)(
  const char *path, uint32_t desired_access, uint32_t share_mode,
  void *security_attributes, uint32_t creation_disposition,
  uint32_t flags_and_attributes, int template_file);
typedef int(__stdcall *set_file_pointer_fn)(int handle, int distance_to_move,
                                            int *distance_high,
                                            uint32_t move_method);
typedef int(__stdcall *get_file_size_fn)(int handle, int *size_high);
typedef bool(__stdcall *read_file_fn)(int handle, void *buffer,
                                      uint32_t number_of_bytes_to_read,
                                      int *number_of_bytes_read,
                                      void *overlapped);
typedef uint16_t (*intl_string_prev_char_fn)(const char *str, int16_t *index);
typedef int (*is_alpha_fn)(int c);
typedef void (*debug_log_fn)(int level, const char *format, ...);
typedef uint32_t(__stdcall *xget_last_error_fn)(void);
typedef void(__stdcall *xset_last_error_fn)(uint32_t error);
typedef int(__stdcall *nt_create_file_fn)(const char *path, int access);
typedef bool(__stdcall *remove_directory_fn)(const char *path);
typedef bool(__stdcall *set_file_attributes_fn)(const char *path,
                                                uint32_t attributes);
typedef bool(__stdcall *delete_file_fn)(const char *path);
typedef bool(__stdcall *move_file_fn)(const char *existing_path,
                                      const char *new_path);

#define XFindFirstFile ((find_first_file_fn)0x1d3576)
#define XFindNextFile ((find_next_file_fn)0x1d3683)
#define XCloseHandle ((close_handle_fn)0x1cf900)
#define XCreateFile ((create_file_fn)0x1d1d85)
#define XSetFilePointer ((set_file_pointer_fn)0x1d1610)
#define XGetFileSize ((get_file_size_fn)0x1d1d4a)
#define XReadFile ((read_file_fn)0x1d13c9)
#define IntlStringPrevChar ((intl_string_prev_char_fn)0x19d240)
#define XIsAlpha ((is_alpha_fn)0x1daaaa)
#define DEBUG_LOG ((debug_log_fn)0x8f390)
#define XGetLastError ((xget_last_error_fn)0x1d2240)
#define XSetLastError ((xset_last_error_fn)0x1d2268)
#define XNtCreateFile ((nt_create_file_fn)0x1d3410)
#define XRemoveDirectory ((remove_directory_fn)0x1d347c)
#define XSetFileAttributes ((set_file_attributes_fn)0x1d0df0)
#define XDeleteFile ((delete_file_fn)0x1d0ff9)
#define XMoveFile ((move_file_fn)0x1d0f63)

static uint32_t g_find_files_flags;
static int16_t g_find_files_index = -1;
static int16_t g_find_files_location;
static char g_find_files_path[260];
static int g_find_file_handles[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
static unsigned char g_find_file_data[0x148];

/**
 * find_files - enumerate files matching a directory reference.
 *
 * Begins a file search using the given flags and directory reference,
 * then iterates up to max_count entries, storing each result in the
 * results array (stride = sizeof(file_ref_t) = 0x10C).
 * Returns the number of files found.
 */
int16_t find_files(int flags, file_ref_t *dir, int16_t max_count,
                   file_ref_t *results)
{
  int16_t count = 0;

  if (max_count < 1) {
    display_assert("maximum_count>0", "c:\\halo\\SOURCE\\tag_files\\files.c",
                   0x101, true);
    system_exit(-1);
  }
  if (results == NULL) {
    display_assert("references", "c:\\halo\\SOURCE\\tag_files\\files.c", 0x102,
                   true);
    system_exit(-1);
  }

  find_files_begin(flags, dir);

  if (max_count > 0) {
    do {
      if (!find_files_next(&results[count], 0))
        return count;
      count++;
    } while (count < max_count);
  }

  return count;
}

/**
 * file_read_into_buffer - read an entire file into a newly allocated buffer.
 *
 * Opens the file for reading, queries its size via file_get_eof, allocates
 * a buffer with debug_malloc, reads the full contents into it, then closes
 * the file. On success, writes the file size to *size_out and returns
 * the allocated buffer. On any failure (open, alloc, or read), returns NULL.
 * If the read fails after allocation, the buffer is freed before returning.
 */
void *file_read_into_buffer(file_ref_t *file_ref, int *size_out)
{
  void *buffer;

  buffer = NULL;
  if (file_open(file_ref, 1)) {
    *size_out = file_get_eof(file_ref);
    buffer =
      debug_malloc(*size_out, 0, "c:\\halo\\SOURCE\\tag_files\\files.c", 0x118);
    if (buffer != NULL) {
      if (!file_read(file_ref, *size_out, buffer)) {
        debug_free(buffer, "c:\\halo\\SOURCE\\tag_files\\files.c", 0x11e);
        buffer = NULL;
      }
    }
    file_close(file_ref);
  }
  return buffer;
}

/**
 * file_reference_verify - validate a file_ref_t pointer.
 *
 * Checks that the pointer is non-NULL, the magic signature matches
 * FILE_REFERENCE_SIGNATURE (0x66696C6F), flags are valid (only bit 0
 * allowed in the reference info flags), and the location field is in
 * the range [-1, 1] (NONE through NUMBER_OF_FILE_REFERENCE_LOCATIONS).
 *
 * Returns the validated pointer.
 */
file_ref_t *file_reference_verify(file_ref_t *info)
{
  if (info == NULL) {
    display_assert("info", "c:\\halo\\SOURCE\\tag_files\\files.c", 0x1fc, true);
    system_exit(-1);
  }
  if (info->magic != FILE_REF_MAGIC) {
    display_assert("info->signature==FILE_REFERENCE_SIGNATURE",
                   "c:\\halo\\SOURCE\\tag_files\\files.c", 0x1fd, true);
    system_exit(-1);
  }
  if ((*(uint16_t *)&info->unk_4[0] & 0xfffe) != 0) {
    display_assert("VALID_FLAGS(info->flags, NUMBER_OF_REFERENCE_INFO_FLAGS)",
                   "c:\\halo\\SOURCE\\tag_files\\files.c", 0x1fe, true);
    system_exit(-1);
  }
  if (info->unk_6 < -1 || info->unk_6 > 1) {
    display_assert("info->location>=NONE && "
                   "info->location<NUMBER_OF_FILE_REFERENCE_LOCATIONS",
                   "c:\\halo\\SOURCE\\tag_files\\files.c", 0x1ff, true);
    system_exit(-1);
  }
  return info;
}

/**
 * file_reference_add_directory - append a directory component to a file
 * reference's path.
 *
 * Verifies the file reference, asserts that the directory string is
 * non-NULL and that the _has_filename_bit flag is not set (cannot add a
 * directory component after a filename has been set), then appends the
 * directory to the internal path buffer using path_add_directory.
 *
 * Returns the file reference pointer.
 */
file_ref_t *file_reference_add_directory(file_ref_t *info,
                                         const char *directory)
{
  file_ref_t *ref;

  ref = file_reference_verify(info);
  if (directory == NULL) {
    display_assert("directory", "c:\\halo\\SOURCE\\tag_files\\files.c", 0x89,
                   true);
    system_exit(-1);
  }
  if (ref->unk_4[0] & 1) {
    display_assert("!TEST_FLAG(info->flags, _has_filename_bit)",
                   "c:\\halo\\SOURCE\\tag_files\\files.c", 0x8a, true);
    system_exit(-1);
  }
  path_add_directory(ref->unk_8, directory);
  return info;
}

/**
 * file_reference_set_name - set the filename component of a file reference.
 *
 * Verifies the file reference and asserts that the name string is
 * non-NULL. If the _has_filename_bit flag is already set, strips the
 * existing filename from the path (via path_remove_filename) before
 * appending the new name with path_add_directory. Sets the
 * _has_filename_bit flag afterward.
 *
 * Returns the file reference pointer.
 */
file_ref_t *file_reference_set_name(file_ref_t *info, const char *name)
{
  file_ref_t *ref;

  ref = file_reference_verify(info);
  if (name == NULL) {
    display_assert("name", "c:\\halo\\SOURCE\\tag_files\\files.c", 0x97, true);
    system_exit(-1);
  }
  if (ref->unk_4[0] & 1) {
    path_remove_filename(ref->unk_8);
  }
  path_add_directory(ref->unk_8, name);
  ref->unk_4[0] |= 1;
  return info;
}

/* file_reference_get_location (0x1997f0) — readable C lift. */
uint16_t file_reference_get_location(void *info)
{
  char *ref;

  ref = (char *)file_reference_verify(info);
  return *(uint16_t *)(ref + 6);
}

/**
 * file_reference_get_name - extract a formatted name string from a file
 * reference.
 *
 * Validates the file reference, builds the full path, splits it into
 * components (directory, parent directory, filename, extension), and
 * reassembles the requested parts based on the flags bitmask:
 *   bit 0: directory
 *   bit 1: parent directory
 *   bit 2: filename (stem)
 *   bit 3: extension
 *
 * Returns name_out.
 */
char *file_reference_get_name(file_ref_t *info, int flags, char *name_out)
{
  file_ref_t *ref;
  char path[256];
  char *dir_part;
  char *parent_part;
  char *file_part;
  char *ext_part;
  int has_dir_flag;

  ref = file_reference_verify(info);

  csmemset(path, 0, sizeof(path));

  if (name_out == NULL) {
    display_assert("name", "c:\\halo\\SOURCE\\tag_files\\files.c", 0xb9, true);
    system_exit(-1);
  }
  if ((*(uint16_t *)&ref->unk_4[0] & 0xfff0) != 0) {
    display_assert("VALID_FLAGS(info->flags, NUMBER_OF_NAME_FLAGS)",
                   "c:\\halo\\SOURCE\\tag_files\\files.c", 0xba, true);
    system_exit(-1);
  }
  if (flags == 0) {
    display_assert("flags", "c:\\halo\\SOURCE\\tag_files\\files.c", 0xbb, true);
    system_exit(-1);
  } else if (flags == 9) {
    display_assert(
      "flags!=(FLAG(_name_directory_bit)|FLAG(_name_extension_bit))",
      "c:\\halo\\SOURCE\\tag_files\\files.c", 0xbc, true);
    system_exit(-1);
  }
  if ((flags & 1) && (flags & 2)) {
    display_assert(
      "!TEST_FLAG(flags, _name_directory_bit) || !TEST_FLAG(flags, "
      "_name_parent_directory_bit)",
      "c:\\halo\\SOURCE\\tag_files\\files.c", 0xbd, true);
    system_exit(-1);
  }

  has_dir_flag = flags & 1;

  path_from_file_reference(ref->unk_6, ref->unk_8, path);
  path_split(path, &dir_part, &parent_part, &file_part, &ext_part,
             (uint8_t)ref->unk_4[0] & 1);

  *name_out = '\0';

  if (has_dir_flag) {
    path_add_directory(name_out, dir_part);
  }
  if (flags & 2) {
    path_add_directory(name_out, parent_part);
  }
  if (flags & 4) {
    path_add_directory(name_out, file_part);
  }
  if (flags & 8) {
    path_add_extension(name_out, ext_part);
  }

  return name_out;
}

/* file_references_equal (0x1999a0) — readable C lift. */
bool file_references_equal(file_ref_t *info1, file_ref_t *info2)
{
  file_ref_t *a = file_reference_verify(info1);
  file_ref_t *b = file_reference_verify(info2);
  if (*(int16_t *)((char *)a + 6) != *(int16_t *)((char *)b + 6))
    return false;
  return csstrcmp((const char *)a + 8, (const char *)b + 8) == 0;
}

/**
 * file_reference_create_from_path - initialize a file reference from a path.
 *
 * Zeroes the file_ref_t, sets the magic and location fields, then either
 * adds the directory as a path component (a3=true) or sets it as the
 * base name (a3=false).
 */
file_ref_t *file_reference_create_from_path(file_ref_t *info,
                                            const char *directory, bool a3)
{
  if (info == NULL) {
    display_assert("info", "c:\\halo\\SOURCE\\tag_files\\files.c", 0x5B, true);
    system_exit(-1);
  }

  csmemset(info, 0, sizeof(*info));
  info->magic = FILE_REF_MAGIC;
  info->unk_6 = -1;

  if (a3) {
    file_reference_add_directory(info, directory);
  } else {
    file_reference_set_name(info, directory);
  }

  return info;
}

void find_files_begin(int flags, file_ref_t *dir)
{
  file_ref_t *ref;

  ref = file_reference_verify(dir);

  if ((flags & ~3) != 0) {
    display_assert("VALID_FLAGS(flags, NUMBER_OF_FIND_FILES_FLAGS)",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x224, true);
    system_exit(-1);
  }
  if ((ref->unk_4[0] & 1) != 0) {
    display_assert("!TEST_FLAG(info->flags, has_filename_bit)",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x225, true);
    system_exit(-1);
  }

  while (g_find_files_index >= 0) {
    int handle = g_find_file_handles[(uint16_t)g_find_files_index];
    if (handle != -1) {
      XCloseHandle(handle);
      g_find_file_handles[(uint16_t)g_find_files_index] = -1;
    }
    g_find_files_index--;
  }

  g_find_files_flags = (uint32_t)flags;
  g_find_files_index = 0;
  g_find_files_location = ref->unk_6;
  csstrcpy(g_find_files_path, ref->unk_8);
}

void path_add_directory(char *path, const char *directory)
{
  int path_length;
  char *tail;

  if (*directory == '\0') {
    return;
  }

  if (csstrlen(path) + 1 + csstrlen(directory) > 0xFF) {
    display_assert("strlen(path)+1+strlen(name)<=MAXIMUM_FILENAME_LENGTH",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x2A0, true);
    system_exit(-1);
  }

  path_length = csstrlen(path);
  tail = path + path_length;
  if (tail != path) {
    *tail = '\\';
    tail++;
    *tail = '\0';
  }

  path_length = csstrlen(path);
  csstrncpy(tail, directory, 0xFF - path_length);
  path[0xFF] = '\0';
}

void path_add_extension(char *path, const char *extension)
{
  int path_length;
  char *tail;

  if (*extension == '\0') {
    return;
  }

  if (csstrlen(path) + 1 + csstrlen(extension) > 0xFF) {
    display_assert("strlen(path)+1+strlen(extension)<=MAXIMUM_FILENAME_LENGTH",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x2b8, true);
    system_exit(-1);
  }

  path_length = csstrlen(path);
  tail = path + path_length;
  if (tail != path) {
    *tail = '.';
    tail++;
    *tail = '\0';
  }

  path_length = csstrlen(path);
  csstrncpy(tail, extension, 0xFF - path_length);
  path[0xFF] = '\0';
}

void path_remove_filename(char *path)
{
  int i;
  int length;

  length = csstrlen(path);
  for (i = length - 1; i >= 0; i--) {
    if (path[i] == '\\') {
      path[i] = '\0';
      return;
    }
  }

  *path = '\0';
}

void path_split(const char *path, char **directory, char **parent_directory,
                char **filename, char **extension, int flags)
{
  char *mutable_path = (char *)path;
  int16_t path_length = (int16_t)csstrlen(path);
  char *end = mutable_path + path_length;
  uint16_t ch;

  *directory = end;
  *parent_directory = end;
  *filename = end;
  *extension = end;

  while (path_length != 0) {
    ch = IntlStringPrevChar(mutable_path, &path_length);

    if (ch == '.') {
      if (flags != 0 && **filename == '\0' && **extension == '\0') {
        mutable_path[path_length] = '\0';
        *extension = mutable_path + path_length + 1;
      }
    } else if (ch == '\\') {
      if (flags == 0 || **filename != '\0') {
        if (**parent_directory == '\0') {
          *parent_directory = mutable_path + path_length + 1;
        }
      } else {
        mutable_path[path_length] = '\0';
        *filename = mutable_path + path_length + 1;
      }
    }
  }

  if (flags != 0 && **filename == '\0') {
    *filename = mutable_path;
    return;
  }

  if (*filename != mutable_path) {
    *directory = mutable_path;
  }
}

void path_from_file_reference(int16_t location, const char *path, char *out)
{
  (void)location;

  if (path == NULL || out == NULL) {
    display_assert("path && full_path",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x314, true);
    system_exit(-1);
  }

  *out = '\0';

  if (!(path[0] != '\0' && path[1] != '\0' && path[2] != '\0' &&
        XIsAlpha((unsigned char)path[0]) != 0 && path[1] == ':' &&
        path[2] == '\\')) {
    csstrcpy(out, "d:\\");
  }

  csstrcpy(out + csstrlen(out), path);
}

/* 0x19a450: PUSH EAX (info) at entry — EAX is passed directly to
 * file_reference_verify (0x199620); [EBP+8] = function_name (only stack arg).
 * info is a register arg @<eax>; kb.json decl updated accordingly. */
void file_error(file_ref_t *info, const char *function_name)
{
  file_ref_t *ref;
  uint32_t error;

  ref = file_reference_verify(info);
  error = XGetLastError();
  DEBUG_LOG(2, "%s('%s') error 0x%08x", function_name, ref->unk_8, error);
  XSetLastError(0);
}

/**
 * file_create - create a file referenced by info.
 *
 * Builds the full path from the file reference.
 * If the write-mode bit (bit 0 of unk_4[0]) is clear, uses the NT
 * NtCreateFile wrapper (CreateDirectoryA) with default access flags.
 * If the write-mode bit is set, uses CreateFileA (XCreateFile) with
 * GENERIC_WRITE | FILE_ATTRIBUTE_HIDDEN | FILE_FLAG_SEQUENTIAL_SCAN.
 * On success, closes the returned handle. On failure, logs the error and
 * clears it. Returns true on success, false on failure.
 */
bool FUN_0019a490(file_ref_t *info)
{
  file_ref_t *ref;
  char path[256];
  int handle;

  ref = file_reference_verify(info);

  csmemset(path, 0, sizeof(path));

  path_from_file_reference(ref->unk_6, ref->unk_8, path);

  if ((ref->unk_4[0] & 1) == 0) {
    handle = XNtCreateFile(ref->unk_8, 0);
    if (handle == 0) {
      goto error;
    }
  } else {
    handle = XCreateFile(path, 0x40000000, 0, 0, 2, 0x80, 0);
    if (handle == -1) {
      goto error;
    }
    XCloseHandle(handle);
  }
  return true;

error:
  ref = file_reference_verify(info);
  DEBUG_LOG(2, "%s('%s') error 0x%08x", "file_create", ref->unk_8,
            XGetLastError());
  XSetLastError(0);
  return false;
}

/* 0x19a560 — delete the file (or directory) referenced by info.
 * For directories (unk_4[0] bit 0 clear), uses XRemoveDirectory.
 * For regular files (unk_4[0] bit 0 set), clears FILE_ATTRIBUTE_NORMAL
 * then calls XDeleteFile. Returns true on success, logs error and
 * returns false on failure. */
bool file_delete(file_ref_t *info)
{
  file_ref_t *ref;
  char path[256];

  ref = file_reference_verify(info);
  csmemset(path, 0, sizeof(path));
  path_from_file_reference(ref->unk_6, ref->unk_8, path);

  if ((ref->unk_4[0] & 1) == 0) {
    if (XRemoveDirectory(path)) {
      return true;
    }
  } else {
    if (XSetFileAttributes(path, 0x80)) {
      if (XDeleteFile(path)) {
        return true;
      }
    }
  }

  ref = file_reference_verify(info);
  DEBUG_LOG(2, "%s('%s') error 0x%08x", "file_delete", ref->unk_8,
            XGetLastError());
  XSetLastError(0);
  return false;
}

/**
 * file_exists - check whether a file referenced by info exists on disk.
 *
 * Builds the full path from the file reference, then calls
 * file_get_full_attributes (NtQueryFullAttributesFile wrapper).
 * Returns true if the file was found, false otherwise. Logs an error
 * via file_error if the failure was not ERROR_FILE_NOT_FOUND (2) or
 * ERROR_PATH_NOT_FOUND (3).
 */
bool file_exists(file_ref_t *info)
{
  file_ref_t *ref;
  char path[256];
  int result;

  ref = file_reference_verify(info);

  csmemset(path, 0, sizeof(path));

  path_from_file_reference(ref->unk_6, ref->unk_8, path);

  result = file_get_full_attributes(path);
  if (result != -1) {
    return true;
  }

  if (xapi_GetLastError() != 2) {
    if (xapi_GetLastError() != 3) {
      file_error(info, "file_exists");
    }
  }

  return false;
}

/* 0x19a6d0 — rename (or move) the file referenced by info to new_name.
 * Builds the full source path from info; builds the destination path by
 * copying the source path, stripping the filename, and appending new_name.
 * Calls XMoveFile to perform the rename. On success also updates the
 * file_ref's internal path. Returns true on success, false on failure. */
bool file_rename(file_ref_t *info, const char *new_name)
{
  file_ref_t *ref;
  char src_path[256];
  char dst_path[256];

  ref = file_reference_verify(info);
  csmemset(src_path, 0, sizeof(src_path));
  csmemset(dst_path, 0, sizeof(dst_path));
  path_from_file_reference(ref->unk_6, ref->unk_8, src_path);
  csstrcpy(dst_path, src_path);
  path_remove_filename(dst_path);
  path_add_directory(dst_path, new_name);

  if (XMoveFile(src_path, dst_path)) {
    path_remove_filename(ref->unk_8);
    path_add_directory(ref->unk_8, new_name);
    return true;
  }
  return false;
}

bool file_open(file_ref_t *info, int flags)
{
  file_ref_t *ref;
  char path[256];
  uint32_t access;
  int handle;

  ref = file_reference_verify(info);

  csmemset(path, 0, sizeof(path));

  if ((flags & ~7) != 0) {
    display_assert("VALID_FLAGS(flags, NUMBER_OF_PERMISSION_FLAGS)",
                   "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x134, true);
    system_exit(-1);
  }
  if ((flags & 3) == 0) {
    display_assert(
      "flags & (FLAG(_permission_read_bit)|FLAG(_permission_write_bit))",
      "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x135, true);
    system_exit(-1);
  }
  if (((flags & 2) == 0) && ((flags & 4) != 0)) {
    display_assert(
      "TEST_FLAG(flags, _permission_write_bit) || !TEST_FLAG(flags, "
      "_permission_append_bit)",
      "c:\\halo\\SOURCE\\tag_files\\files_windows.c", 0x136, true);
    system_exit(-1);
  }

  path_from_file_reference(ref->unk_6, ref->unk_8, path);

  access = 0;
  if ((flags & 1) != 0) {
    access = 0x80000000;
  }
  if ((flags & 2) != 0) {
    access |= 0x40000000;
  }

  handle = XCreateFile(path, access, 0, NULL, 3, 0x80, 0);
  if (handle != -1) {
    *(int *)&ref->unk_8[256] = handle;
    if ((flags & 4) == 0) {
      return true;
    }

    if (XSetFilePointer(handle, 0, NULL, 2) != -1) {
      return true;
    }

    XCloseHandle(*(int *)&ref->unk_8[256]);
    *(int *)&ref->unk_8[256] = 0;
  }

  file_error(info, "file_open");
  return false;
}

bool file_close(file_ref_t *info)
{
  file_ref_t *ref;

  ref = file_reference_verify(info);
  if (XCloseHandle(*(int *)&ref->unk_8[256])) {
    *(int *)&ref->unk_8[256] = 0;
    return true;
  }

  file_error(info, "file_close");
  return false;
}

/* 0x19a9a0 — return the current byte offset within the open file.
 * Calls SetFilePointer with move=0 from FILE_CURRENT (1) to query the
 * position without moving. On failure, logs an error and returns -1. */
int file_get_position(file_ref_t *info)
{
  file_ref_t *ref;
  int pos;
  unsigned int err;

  ref = file_reference_verify(info);
  pos = XSetFilePointer(*(int *)&ref->unk_8[256], 0, NULL, 1);
  if (pos == -1) {
    ref = file_reference_verify(info);
    err = XGetLastError();
    error(2, "%s('%s') error 0x%08x", "file_get_position", ref->unk_8, err);
    XSetLastError(0);
  }
  return pos;
}

/* 0x19aa00 — seek to an absolute byte offset within the open file.
 * Calls SetFilePointer with method=FILE_BEGIN (0). Returns true on
 * success, false on failure; logs an error on failure. */
bool file_set_position(file_ref_t *info, int offset)
{
  file_ref_t *ref;
  int result;
  unsigned int err;

  ref = file_reference_verify(info);
  result = XSetFilePointer(*(int *)&ref->unk_8[256], offset, NULL, 0);
  if (result == -1) {
    ref = file_reference_verify(info);
    err = XGetLastError();
    error(2, "%s('%s') error 0x%08x", "file_set_position", ref->unk_8, err);
    XSetLastError(0);
  }
  return result != -1;
}

int file_get_eof(file_ref_t *info)
{
  file_ref_t *ref;
  int eof;

  ref = file_reference_verify(info);
  eof = XGetFileSize(*(int *)&ref->unk_8[256], NULL);
  if (eof == -1) {
    file_error(info, "file_get_eof");
  }

  return eof;
}

bool file_read(file_ref_t *info, int size, void *buffer)
{
  file_ref_t *ref;
  int bytes_read;

  ref = file_reference_verify(info);
  if (buffer == NULL) {
    display_assert("buffer", "c:\\halo\\SOURCE\\tag_files\\files_windows.c",
                   0x1a7, true);
    system_exit(-1);
  }

  if (XReadFile(*(int *)&ref->unk_8[256], buffer, (uint32_t)size, &bytes_read,
                NULL)) {
    if (bytes_read == size) {
      return true;
    }
    XSetLastError(0x26);
  }

  file_error(info, "file_read");
  return false;
}

/* 0x19acb0 — seek to 'offset' then read 'size' bytes into 'buffer'.
 * Combines file_set_position and file_read; returns true only if both
 * succeed, false otherwise. */
bool file_read_from_position(file_ref_t *info, int offset, int size,
                             void *buffer)
{
  char ok_pos;
  char ok_read;

  ok_pos = file_set_position(info, offset);
  if (ok_pos != '\0') {
    ok_read = file_read(info, size, buffer);
    if (ok_read != '\0') {
      return 1;
    }
  }
  return 0;
}

bool find_files_next(file_ref_t *result, int param2)
{
  char full_path[256];

  csmemset(full_path, 0, sizeof(full_path));

  while (g_find_files_index >= 0) {
    int level = (uint16_t)g_find_files_index;
    int handle = g_find_file_handles[level];

    if (handle == -1) {
      path_from_file_reference(g_find_files_location, g_find_files_path,
                               full_path);
      path_add_directory(full_path, "*.*");

      handle = XFindFirstFile(full_path, g_find_file_data);
      g_find_file_handles[level] = handle;
      if (handle == -1) {
        path_remove_filename(g_find_files_path);
        g_find_files_index--;
        continue;
      }
    } else {
      if (!XFindNextFile(handle, g_find_file_data)) {
        XCloseHandle(g_find_file_handles[level]);
        g_find_file_handles[level] = -1;
        path_remove_filename(g_find_files_path);
        g_find_files_index--;
        continue;
      }
    }

    if ((*(uint32_t *)&g_find_file_data[0] & 0x10) != 0) {
      char *entry_name = (char *)&g_find_file_data[0x2C];

      if (csstrcmp(entry_name, ".") != 0 && csstrcmp(entry_name, "..") != 0) {
        if ((g_find_files_flags & FIND_FILES_DIRECTORIES_BIT) != 0) {
          csmemset(result, 0, sizeof(*result));
          result->unk_6 = g_find_files_location;
          result->magic = FILE_REF_MAGIC;
          file_reference_add_directory(result, g_find_files_path);
          file_reference_add_directory(result, entry_name);
        }

        if ((g_find_files_flags & FIND_FILES_RECURSIVE_BIT) != 0) {
          if ((g_find_files_flags & FIND_FILES_DIRECTORIES_BIT) == 0) {
            path_add_directory(g_find_files_path, entry_name);
          }
          g_find_files_index++;
        }

        if ((g_find_files_flags & FIND_FILES_DIRECTORIES_BIT) != 0) {
          if (param2 != 0) {
            csmemcpy((void *)param2, &g_find_file_data[0x14], 8);
          }
          return true;
        }
      }
    } else if ((g_find_files_flags & FIND_FILES_DIRECTORIES_BIT) == 0) {
      csmemset(result, 0, sizeof(*result));
      result->unk_6 = g_find_files_location;
      result->magic = FILE_REF_MAGIC;
      file_reference_add_directory(result, g_find_files_path);
      file_reference_set_name(result, (char *)&g_find_file_data[0x2C]);

      if (param2 != 0) {
        csmemcpy((void *)param2, &g_find_file_data[0x14], 8);
      }
      return true;
    }
  }

  return false;
}
/* --- files_windows.obj batch drafts (2026-07-26) --- */

/* FUN_00199d40 (0x199d40) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void (*const b199d40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b199d40_exitfn)(int) = system_exit;
static int (*const b199d40_c8df60)(const char *s1) = csstrlen;
static void *(*const b199d40_memset)(void *, int, unsigned int) = csmemset;
static file_ref_t * (*const b199d40_c199780)(file_ref_t *info, const char *name) = file_reference_set_name;
static bool (*const b199d40_c19a640)(file_ref_t *info) = file_exists;
static void * (*const b199d40_c199540)(file_ref_t *file_ref, int *size_out) = file_read_into_buffer;
static bool (*const b199d40_c19a560)(file_ref_t *info) = file_delete;
static void (*const b199d40_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static void * (*const b199d40_c8ee60)(uint32_t size, bool zero, const char *file, int line) = debug_malloc;
static int (*const b199d40_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static char * (*const b199d40_c8dff0)(char *destination, const char *source) = csstrcpy;
static void * (*const b199d40_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static bool (*const b199d40_c19a490)(file_ref_t *info) = FUN_0019a490;
static bool (*const b199d40_c19a7a0)(file_ref_t *info, int flags) = file_open;
static bool (*const b199d40_c19ac00)(file_ref_t *info, void *buffer, int size) = file_write;
static bool (*const b199d40_c19a930)(file_ref_t *info) = file_close;

__attribute__((naked, noinline))
void FUN_00199d40(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x114, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jne .LFUN_00199d40_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1ae\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00199d40_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1af\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_2:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .LFUN_00199d40_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1b0\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_3:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "jne .LFUN_00199d40_4\n\t"
      "pushl $1\n\t"
      "pushl $0x1b1\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_4:\n\t"
      "cmpl $0xff, 0x10(%%ebp)\n\t"
      "jl .LFUN_00199d40_5\n\t"
      "pushl $1\n\t"
      "pushl $0x1b2\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_5:\n\t"
      "pushl %%edi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xff, %%eax\n\t"
      "jb .LFUN_00199d40_6\n\t"
      "pushl $1\n\t"
      "pushl $0x1b3\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3ce0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_6:\n\t"
      "pushl $0x10c\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x66696c6f, -0x114(%%ebp)\n\t"
      "movw $0xffff, -0x10e(%%ebp)\n\t"
      "call *%[c199780]\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a640]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00199d40_9\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c199540]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00199d40_7\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a560]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00199d40_7:\n\t"
      "cmpl $0x18e70, -0x8(%%ebp)\n\t"
      "je .LFUN_00199d40_8\n\t"
      "pushl $0x1c2\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl %%edi\n\t"
      "call *%[c8ef70]\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a560]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .LFUN_00199d40_9\n\t"
      ".LFUN_00199d40_8:\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00199d40_10\n\t"
      ".LFUN_00199d40_9:\n\t"
      "pushl $0x1cd\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0\n\t"
      "pushl $0x18e70\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_00199d40_16\n\t"
      "pushl $0x18e70\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00199d40_10:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%edi, %%ebx\n\t"
      "jmp .LFUN_00199d40_11\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00199d40_11:\n\t"
      "cmpb $0, (%%ebx)\n\t"
      "je .LFUN_00199d40_12\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00199d40_12\n\t"
      "incl %%esi\n\t"
      "addl $0x1fe, %%ebx\n\t"
      "cmpl $0xc8, %%esi\n\t"
      "jl .LFUN_00199d40_11\n\t"
      "jmp .LFUN_00199d40_13\n\t"
      ".LFUN_00199d40_12:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "imull $0x1fe, %%esi, %%esi\n\t"
      "pushl %%edx\n\t"
      "addl %%edi, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c8dff0]\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "addl $0xff, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0x14, %%esp\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00199d40_13:\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a640]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_00199d40_14\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00199d40_14:\n\t"
      "leal -0x114(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19a7a0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00199d40_15\n\t"
      "pushl %%edi\n\t"
      "leal -0x114(%%ebp), %%edx\n\t"
      "pushl $0x18e70\n\t"
      "pushl %%edx\n\t"
      "call *%[c19ac00]\n\t"
      "leal -0x114(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a930]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00199d40_15:\n\t"
      "pushl $0x1ec\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl %%edi\n\t"
      "call *%[c8ef70]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00199d40_17\n\t"
      ".LFUN_00199d40_16:\n\t"
      "pushl $1\n\t"
      "pushl $0x1ef\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x254818\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199d40_17:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b199d40_assert), [exitfn] "m"(b199d40_exitfn), [c8df60] "m"(b199d40_c8df60), [memset] "m"(b199d40_memset), [c199780] "m"(b199d40_c199780), [c19a640] "m"(b199d40_c19a640), [c199540] "m"(b199d40_c199540), [c19a560] "m"(b199d40_c19a560), [c8ef70] "m"(b199d40_c8ef70), [c8ee60] "m"(b199d40_c8ee60), [c8dcb0] "m"(b199d40_c8dcb0), [c8dff0] "m"(b199d40_c8dff0), [c8e0b0] "m"(b199d40_c8e0b0), [c19a490] "m"(b199d40_c19a490), [c19a7a0] "m"(b199d40_c19a7a0), [c19ac00] "m"(b199d40_c19ac00), [c19a930] "m"(b199d40_c19a930)
      : "memory");
}
#else
#error "FUN_00199d40: clang naked draft required"
#endif


/* file_compare_last_modification_dates (0x19a020) — readable C lift. */
int file_compare_last_modification_dates(const void *a, const void *b)
{
  return csmemcmp(a, b, 8);
}

/* file_read_only (0x19a400) — readable C lift. */
bool file_read_only(file_ref_t *info)
{
  char path[0x100];
  file_ref_t *ref;
  int attrs;

  ref = file_reference_verify(info);
  path_from_file_reference(*(int16_t *)((char *)ref + 6), (const char *)((char *)ref + 8), path);
  attrs = file_get_full_attributes(path);
  if (attrs == -1)
    return 0;
  return (attrs & 1) != 0;
}


/* file_set_eof (0x19aad0) — XBE naked draft (batch 266). */
#if defined(__clang__)
static file_ref_t * (*const b19aad0_c199620)(file_ref_t *info) = file_reference_verify;
static bool (*const b19aad0_c19aa00)(file_ref_t *info, int offset) = file_set_position;
static bool __stdcall (*const b19aad0_c1d158c)(int handle) = SetEndOfFile;
static int (*const b19aad0_c1d2240)(void) = xapi_GetLastError;
static void (*const b19aad0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void __stdcall (*const b19aad0_c1d2268)(unsigned int error) = SetLastError;

__attribute__((naked, noinline))
void file_set_eof(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c199620]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c19aa00]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lfile_set_eof_1\n\t"
      "movl 0x108(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d158c]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfile_set_eof_1\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfile_set_eof_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c199620]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2b4000\n\t"
      "pushl $0x2b3ea4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c199620] "m"(b19aad0_c199620), [c19aa00] "m"(b19aad0_c19aa00), [c1d158c] "m"(b19aad0_c1d158c), [c1d2240] "m"(b19aad0_c1d2240), [c8f390] "m"(b19aad0_c8f390), [c1d2268] "m"(b19aad0_c1d2268)
      : "memory");
}
#else
#error "file_set_eof: clang naked draft required"
#endif


/* file_write (0x19ac00) — XBE naked draft (batch 265). */
#if defined(__clang__)
static file_ref_t * (*const b19ac00_c199620)(file_ref_t *info) = file_reference_verify;
static void (*const b19ac00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19ac00_exitfn)(int) = system_exit;
static int __stdcall (*const b19ac00_c1d14b6)(int handle, void *buffer, uint32_t size, uint32_t *bytes_written, void *overlapped) = WriteFile;
static int (*const b19ac00_c1d2240)(void) = xapi_GetLastError;
static void (*const b19ac00_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void __stdcall (*const b19ac00_c1d2268)(unsigned int error) = SetLastError;

__attribute__((naked, noinline))
bool file_write(file_ref_t *info __attribute__((unused)),
                void *buffer __attribute__((unused)),
                int size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c199620]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "jne .Lfile_write_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1c3\n\t"
      "pushl $0x2b3dec\n\t"
      "pushl $0x267900\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfile_write_1:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x108(%%esi), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d14b6]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfile_write_2\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "cmpl %%eax, -0x4(%%ebp)\n\t"
      "jne .Lfile_write_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfile_write_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c199620]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2b401c\n\t"
      "pushl $0x2b3ea4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c199620] "m"(b19ac00_c199620), [assert] "m"(b19ac00_assert), [exitfn] "m"(b19ac00_exitfn), [c1d14b6] "m"(b19ac00_c1d14b6), [c1d2240] "m"(b19ac00_c1d2240), [c8f390] "m"(b19ac00_c8f390), [c1d2268] "m"(b19ac00_c1d2268)
      : "memory");
}
#else
#error "file_write: clang naked draft required"
#endif


/* file_write_to_position (0x19acf0) — readable C lift. */
bool file_write_to_position(file_ref_t *info, int offset, void *buffer, int size)
{
  if (!file_set_position(info, offset))
    return 0;
  if (!file_write(info, buffer, size))
    return 0;
  return 1;
}


/* file_get_last_modification_date (0x19ad30) — XBE naked draft (batch 257). */
#if defined(__clang__)
static file_ref_t * (*const b19ad30_c199620)(file_ref_t *info) = file_reference_verify;
static void *(*const b19ad30_memset)(void *, int, unsigned int) = csmemset;
static void (*const b19ad30_c19a370)(int16_t location, const char *path, char *out) = path_from_file_reference;
static void (*const b19ad30_c1d0ee1)(void) = FUN_001d0ee1;
static void * (*const b19ad30_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static int (*const b19ad30_c1d2240)(void) = xapi_GetLastError;
static void (*const b19ad30_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void __stdcall (*const b19ad30_c1d2268)(unsigned int error) = SetLastError;

__attribute__((naked, noinline))
void file_get_last_modification_date(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x124, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c199620]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb $0, -0x124(%%ebp)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl $0x3f, %%ecx\n\t"
      "leal -0x123(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      "pushl $8\n\t"
      ".byte 0xaa\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[memset]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "leal -0x124(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a370]\n\t"
      "addl $0x1c, %%esp\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x124(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0ee1]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfile_get_last_modification_date_1\n\t"
      "pushl $8\n\t"
      "leal -0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfile_get_last_modification_date_1:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c199620]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2b4028\n\t"
      "pushl $0x2b3ea4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c199620] "m"(b19ad30_c199620), [memset] "m"(b19ad30_memset), [c19a370] "m"(b19ad30_c19a370), [c1d0ee1] "m"(b19ad30_c1d0ee1), [c8e0b0] "m"(b19ad30_c8e0b0), [c1d2240] "m"(b19ad30_c1d2240), [c8f390] "m"(b19ad30_c8f390), [c1d2268] "m"(b19ad30_c1d2268)
      : "memory");
}
#else
#error "file_get_last_modification_date: clang naked draft required"
#endif


/* file_get_size (0x19adf0) — XBE naked draft (batch 261). */
#if defined(__clang__)
static file_ref_t * (*const b19adf0_c199620)(file_ref_t *info) = file_reference_verify;
static void (*const b19adf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b19adf0_exitfn)(int) = system_exit;
static void (*const b19adf0_c19a370)(int16_t location, const char *path, char *out) = path_from_file_reference;
static void (*const b19adf0_c1d0ee1)(void) = FUN_001d0ee1;
static int (*const b19adf0_c1d2240)(void) = xapi_GetLastError;
static void (*const b19adf0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void __stdcall (*const b19adf0_c1d2268)(unsigned int error) = SetLastError;

__attribute__((naked, noinline))
void file_get_size(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x124, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c199620]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb $0, -0x124(%%ebp)\n\t"
      "movl $0x3f, %%ecx\n\t"
      "leal -0x123(%%ebp), %%edi\n\t"
      "rep stosl\n\t"
      "stosw\n\t"
      ".byte 0xaa\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lfile_get_size_1\n\t"
      "pushl $1\n\t"
      "pushl $0x20c\n\t"
      "pushl $0x2b3dec\n\t"
      "pushl $0x267f68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lfile_get_size_1:\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x6(%%ebx), %%dx\n\t"
      "leal -0x124(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal 0x8(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a370]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "leal -0x124(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d0ee1]\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfile_get_size_2\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lfile_get_size_2:\n\t"
      "pushl %%esi\n\t"
      "call *%[c199620]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c1d2240]\n\t"
      "pushl %%eax\n\t"
      "addl $8, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x2b4048\n\t"
      "pushl $0x2b3ea4\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c1d2268]\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c199620] "m"(b19adf0_c199620), [assert] "m"(b19adf0_assert), [exitfn] "m"(b19adf0_exitfn), [c19a370] "m"(b19adf0_c19a370), [c1d0ee1] "m"(b19adf0_c1d0ee1), [c1d2240] "m"(b19adf0_c1d2240), [c8f390] "m"(b19adf0_c8f390), [c1d2268] "m"(b19adf0_c1d2268)
      : "memory");
}
#else
#error "file_get_size: clang naked draft required"
#endif

/* --- files.obj batch drafts (2026-07-26) --- */

/* file_reference_create (0x199420) — readable C lift. */
void *file_reference_create(void *ref, int16_t location)
{
  extern char DAT_002b3b10[];
  extern char DAT_002b3aac[];
  extern char DAT_002b3ad0[];
  if (!ref) {
    display_assert(DAT_002b3b10, DAT_002b3aac, 0x5b, 1);
    system_exit(-1);
  }
  if (location < -1 || location >= 2) {
    display_assert(DAT_002b3ad0, DAT_002b3aac, 0x5c, 1);
    system_exit(-1);
  }
  csmemset(ref, 0, 0x10c);
  *(int16_t *)((char *)ref + 6) = location;
  *(uint32_t *)ref = 0x66696c6f;
  return ref;
}
/* file_printf (0x1995c0) — XBE naked draft (batch 258). */
#if defined(__clang__)
static int (*const b1995c0_c1da209)(char *buffer, const char *format, char *arglist) = vsprintf;
static int (*const b1995c0_c8df60)(const char *s1) = csstrlen;
static bool (*const b1995c0_c19ac00)(file_ref_t *info, void *buffer, int size) = file_write;
static int (*const b1995c0_c19a9a0)(file_ref_t *info) = file_get_position;
static void (*const b1995c0_c19aad0)(void) = file_set_eof;

__attribute__((naked, noinline))
void file_printf(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x400, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lfile_printf_1\n\t"
      "pushl %%esi\n\t"
      "leal 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "leal -0x400(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1da209]\n\t"
      "addl $0xc, %%esp\n\t"
      "leal -0x400(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x400(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8df60]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c19ac00]\n\t"
      "pushl %%esi\n\t"
      "call *%[c19a9a0]\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c19aad0]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%esi\n\t"
      ".Lfile_printf_1:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1da209] "m"(b1995c0_c1da209), [c8df60] "m"(b1995c0_c8df60), [c19ac00] "m"(b1995c0_c19ac00), [c19a9a0] "m"(b1995c0_c19a9a0), [c19aad0] "m"(b1995c0_c19aad0)
      : "memory");
}
#else
#error "file_printf: clang naked draft required"
#endif


/* file_reference_copy (0x1996d0) — readable C lift. */
void *file_reference_copy(void *dst, void *src)
{
  file_reference_verify((file_ref_t *)src);
  csmemcpy(dst, src, 0x108);
  return dst;
}

/* directory_create_or_delete_contents (0x199a60) — XBE naked draft (batch 272). */
#if defined(__clang__)
static void *(*const b199a60_memset)(void *, int, unsigned int) = csmemset;
static file_ref_t * (*const b199a60_c199700)(file_ref_t *info, const char *directory) = file_reference_add_directory;
static bool (*const b199a60_c19a640)(file_ref_t *info) = file_exists;
static void (*const b199a60_c19a040)(int flags, file_ref_t *dir) = find_files_begin;
static bool (*const b199a60_c19aed0)(file_ref_t *result, int param2) = find_files_next;
static bool (*const b199a60_c19a560)(file_ref_t *info) = file_delete;
static bool (*const b199a60_c19a490)(file_ref_t *info) = FUN_0019a490;

__attribute__((naked, noinline))
void directory_create_or_delete_contents(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x218, %%esp\n\t"
      "pushl $0x10c\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0x66696c6f, -0x10c(%%ebp)\n\t"
      "movw $0xffff, -0x106(%%ebp)\n\t"
      "call *%[c199700]\n\t"
      "leal -0x10c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a640]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldirectory_create_or_delete_contents_2\n\t"
      "leal -0x10c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c19a040]\n\t"
      "leal -0x218(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[c19aed0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Ldirectory_create_or_delete_contents_3\n\t"
      "jmp .Ldirectory_create_or_delete_contents_1\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Ldirectory_create_or_delete_contents_1:\n\t"
      "leal -0x218(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a560]\n\t"
      "leal -0x218(%%ebp), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19aed0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Ldirectory_create_or_delete_contents_1\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Ldirectory_create_or_delete_contents_2:\n\t"
      "leal -0x10c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a490]\n\t"
      "addl $4, %%esp\n\t"
      ".Ldirectory_create_or_delete_contents_3:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [memset] "m"(b199a60_memset), [c199700] "m"(b199a60_c199700), [c19a640] "m"(b199a60_c19a640), [c19a040] "m"(b199a60_c19a040), [c19aed0] "m"(b199a60_c19aed0), [c19a560] "m"(b199a60_c19a560), [c19a490] "m"(b199a60_c19a490)
      : "memory");
}
#else
#error "directory_create_or_delete_contents: clang naked draft required"
#endif


/* FUN_00199b20 (0x199b20) — XBE naked draft (batch 246). */
#if defined(__clang__)
static void (*const b199b20_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b199b20_exitfn)(int) = system_exit;
static int (*const b199b20_c8df60)(const char *s1) = csstrlen;
static void *(*const b199b20_memset)(void *, int, unsigned int) = csmemset;
static file_ref_t * (*const b199b20_c199780)(file_ref_t *info, const char *name) = file_reference_set_name;
static bool (*const b199b20_c19a640)(file_ref_t *info) = file_exists;
static void * (*const b199b20_c199540)(file_ref_t *file_ref, int *size_out) = file_read_into_buffer;
static bool (*const b199b20_c19a560)(file_ref_t *info) = file_delete;
static void (*const b199b20_c8ef70)(void *ptr, const char *file, int line) = debug_free;
static int (*const b199b20_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static void * (*const b199b20_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;

__attribute__((naked, noinline))
void FUN_00199b20(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x110, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "jne .LFUN_00199b20_1\n\t"
      "pushl $1\n\t"
      "pushl $0x171\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00199b20_2\n\t"
      "pushl $1\n\t"
      "pushl $0x172\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_2:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "jne .LFUN_00199b20_3\n\t"
      "pushl $1\n\t"
      "pushl $0x173\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_3:\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .LFUN_00199b20_4\n\t"
      "pushl $1\n\t"
      "pushl $0x174\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_4:\n\t"
      "cmpl $0xff, 0x10(%%ebp)\n\t"
      "jl .LFUN_00199b20_5\n\t"
      "pushl $1\n\t"
      "pushl $0x175\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3d14\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_5:\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xff, %%eax\n\t"
      "jb .LFUN_00199b20_6\n\t"
      "pushl $1\n\t"
      "pushl $0x176\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl $0x2b3ce0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00199b20_6:\n\t"
      "pushl $0x10c\n\t"
      "leal -0x110(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[memset]\n\t"
      "leal -0x110(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x66696c6f, -0x110(%%ebp)\n\t"
      "movw $0xffff, -0x10a(%%ebp)\n\t"
      "call *%[c199780]\n\t"
      "leal -0x110(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a640]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00199b20_12\n\t"
      "leal -0x4(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x110(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c199540]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .LFUN_00199b20_7\n\t"
      "leal -0x110(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c19a560]\n\t"
      "addl $4, %%esp\n\t"
      ".LFUN_00199b20_7:\n\t"
      "cmpl $0x18e70, -0x4(%%ebp)\n\t"
      "je .LFUN_00199b20_8\n\t"
      "pushl $0x185\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "leal -0x110(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19a560]\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00199b20_8:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_00199b20_12\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl %%ebx, %%edi\n\t"
      ".LFUN_00199b20_9:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00199b20_10\n\t"
      "cmpb $0, (%%edi)\n\t"
      "je .LFUN_00199b20_11\n\t"
      "incl %%esi\n\t"
      "addl $0x1fe, %%edi\n\t"
      "cmpl $0xc8, %%esi\n\t"
      "jl .LFUN_00199b20_9\n\t"
      "jmp .LFUN_00199b20_11\n\t"
      ".LFUN_00199b20_10:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "imull $0x1fe, %%esi, %%esi\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal 0xff(%%esi,%%ebx,1), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      ".LFUN_00199b20_11:\n\t"
      "pushl $0x1a0\n\t"
      "pushl $0x2b3aac\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00199b20_12:\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b199b20_assert), [exitfn] "m"(b199b20_exitfn), [c8df60] "m"(b199b20_c8df60), [memset] "m"(b199b20_memset), [c199780] "m"(b199b20_c199780), [c19a640] "m"(b199b20_c19a640), [c199540] "m"(b199b20_c199540), [c19a560] "m"(b199b20_c19a560), [c8ef70] "m"(b199b20_c8ef70), [c8dcb0] "m"(b199b20_c8dcb0), [c8e0b0] "m"(b199b20_c8e0b0)
      : "memory");
}
#else
#error "FUN_00199b20: clang naked draft required"
#endif

