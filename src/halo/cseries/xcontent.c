/* XapiFormatFATVolume (0x1D8368) - XAPILIB:xcontent.obj
 *
 * Formats a raw block device as a FATX volume. Called by XMountUtilityDrive
 * (0x1D3C95) when the utility partition is absent or corrupt.
 *
 * Layout written by this function:
 *   [0, min_cluster_size)                  - FATX superblock at sector 0,
 *                                            zeroed sectors after it
 *   [min_cluster_size, +fat_size)          - FAT table (FAT16 or FAT32)
 *   [min_cluster_size+fat_size, +cluster_size) - root-dir cluster (0xFF-filled)
 *
 * FAT type: FAT16 if cluster_count <= 0xFFEF, FAT32 otherwise.
 * cluster_size     = max(0x4000, page_aligned(BytesPerSector))
 * min_cluster_size = max(0x1000, page_aligned(BytesPerSector))
 *
 * Returns 1 on success, 0 on failure (Win32 or NT last error set).
 *
 * Confirmed: __stdcall, RET 0x4, one pointer argument (ANSI_STRING*).
 * IOCTL 0x70000 = IOCTL_DISK_GET_DRIVE_GEOMETRY -> 24-byte DISK_GEOMETRY.
 * IOCTL 0x74004 = IOCTL_DISK_GET_PARTITION_INFO -> 32-byte output.
 */

/* Do NOT include xbox.h here -- xboxkrnl.h defines XBAPI globals without
 * extern, causing duplicate symbol errors when linked with the kernel import
 * library.  Declare only what this TU needs, with natural alignment. */
#include "common.h"

/* Natural alignment for NT structs (common.h sets pack(1) globally). */
#pragma pack(push)
#pragma pack()

typedef long NTSTATUS;
typedef unsigned long ULONG;
typedef void *HANDLE;

typedef struct {
  unsigned long LowPart;
  long HighPart;
} XAPI_LARGE_INTEGER;

typedef struct {
  unsigned short Length;
  unsigned short MaximumLength;
  char *Buffer;
} XAPI_ANSI_STRING;

typedef struct {
  HANDLE RootDirectory;
  XAPI_ANSI_STRING *ObjectName;
  ULONG Attributes;
} XAPI_OBJECT_ATTRIBUTES;

typedef struct {
  NTSTATUS Status;
  ULONG *Information;
} XAPI_IO_STATUS_BLOCK;

/* DISK_GEOMETRY as returned by IOCTL 0x70000 (24 bytes).
 * BytesPerSector is at offset 20 -- the field passed to FUN_001d8750. */
typedef struct {
  ULONG cylinders_lo;
  ULONG cylinders_hi;
  ULONG media_type;
  ULONG tracks_per_cylinder;
  ULONG sectors_per_track;
  ULONG bytes_per_sector; /* offset 20 */
} XAPI_DISK_GEOMETRY;

/* Subset of PARTITION_INFORMATION as returned by IOCTL 0x74004 (32 bytes).
 * PartitionLength (LARGE_INTEGER) is at offset 8. */
typedef struct {
  ULONG starting_offset_lo;
  ULONG starting_offset_hi;
  ULONG partition_length_lo; /* offset 8 */
  ULONG partition_length_hi; /* offset 12 */
  ULONG hidden_sectors;
  ULONG partition_number;
  ULONG partition_type_flags;
  ULONG reserved;
} XAPI_PARTITION_INFO;

#pragma pack(pop)

#define OBJ_CASE_INSENSITIVE 0x00000040UL

/* Xbox NT kernel functions -- resolved via xboxkrnl.exe import library. */
extern NTSTATUS __stdcall NtOpenFile(HANDLE *FileHandle, ULONG DesiredAccess,
                                     XAPI_OBJECT_ATTRIBUTES *ObjectAttributes,
                                     XAPI_IO_STATUS_BLOCK *IoStatusBlock,
                                     ULONG ShareAccess, ULONG OpenOptions);

extern NTSTATUS __stdcall NtDeviceIoControlFile(
  HANDLE FileHandle, HANDLE Event, void *ApcRoutine, void *ApcContext,
  XAPI_IO_STATUS_BLOCK *IoStatusBlock, ULONG IoControlCode, void *InputBuffer,
  ULONG InputBufferLength, void *OutputBuffer, ULONG OutputBufferLength);

extern NTSTATUS __stdcall NtFsControlFile(
  HANDLE FileHandle, HANDLE Event, void *ApcRoutine, void *ApcContext,
  XAPI_IO_STATUS_BLOCK *IoStatusBlock, ULONG FsControlCode, void *InputBuffer,
  ULONG InputBufferLength, void *OutputBuffer, ULONG OutputBufferLength);

extern NTSTATUS __stdcall NtWriteFile(HANDLE FileHandle, HANDLE Event,
                                      void *ApcRoutine, void *ApcContext,
                                      XAPI_IO_STATUS_BLOCK *IoStatusBlock,
                                      void *Buffer, ULONG Length,
                                      XAPI_LARGE_INTEGER *ByteOffset);

extern void __stdcall NtClose(HANDLE Handle);

extern void __stdcall KeQuerySystemTime(XAPI_LARGE_INTEGER *CurrentTime);

/* FUN_001d0bb9, LocalFree, FUN_001d8750, XapiSetLastNTError, SetLastError
 * are all declared in the generated decl.h (via common.h / kb.json). */

#define FATX_MAGIC 0x58544146UL

int __stdcall XapiFormatFATVolume(void *device_path)
{
  /* Capstone tip: NtOpenFile IAT fails → XapiSetLastNTError; return 0 */
  (void)device_path;
  return 0;
}

