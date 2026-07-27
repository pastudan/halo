#include <stdint.h>

/* system_stristr (0x8e250) — readable C lift. */
char *system_stristr(const char *str, const char *substr)
{
  const char *p;
  char first;
  int rest_len;

  first = *substr;
  substr++;
  if (!first)
    return (char *)str;
  rest_len = csstrlen(substr);
  p = str;
  for (;;) {
    char c = *p++;
    if (!c)
      return (char *)0;
    if (c != first)
      continue;
    if (__strnicmp(p, substr, (size_t)rest_len) == 0)
      return (char *)(p - 1);
  }
}


/* system_string_hash (0x8e2b0) — readable C lift. */
uint32_t system_string_hash(const char *str)
{
  uint32_t checksum;
  crc_new(&checksum);
  crc_checksum_buffer(&checksum, (void *)str, csstrlen(str));
  return checksum;
}

void display_debug_string(const char *str)
{
  ((void(__stdcall *)(const char *))0x1d0370)(str);
}

void system_exit(int code)
{
  (void)code;
  halt_and_catch_fire();
  __builtin_unreachable();
}

/* system_unique_identifiers_equal (0x8e320) — readable C lift. */
int system_unique_identifiers_equal(const void *id1, const void *id2)
{
  char zero[16];
  csmemset(zero, 0, 0x10);
  if (csmemcmp(id1, zero, 0x10) == 0)
    return 0;
  if (csmemcmp(id1, id2, 0x10) != 0)
    return 0;
  return 1;
}

uint32_t system_milliseconds(void)
{
  return ((uint32_t(*)(void))0x1d0581)();
}

uint32_t system_seconds(void)
{
  return crt_time(NULL);
}

/* system_get_user_name (0x8e390) — readable C lift. */
void system_get_user_name(char *buffer, int16_t max_len)
{
  csstrncpy(buffer, (const char *)0x267a68, (size_t)(int32_t)max_len);
}

/* system_calloc (0x8e3b0) — readable C lift from XBE leaf. */
void *system_calloc(int count, int size)
{
  return FUN_001d0c48(0x40, count * size);
}




void *system_malloc(int size)
{
  return FUN_001d0c48(0, (uint32_t)size);
}

void system_free(void *ptr)
{
  ((void *(__stdcall *)(void *))0x1d0c16)(ptr);
}

/* system_realloc (0x8e3f0) — readable C lift. */
void *system_realloc(void *ptr, int size)
{
  if (size < 0) {
    display_assert((const char *)0x267a80, (const char *)0x267a3c, 0x9c, 1);
    halt_and_catch_fire();
  }
  if (ptr == NULL) {
    if (size == 0) {
      display_assert((const char *)0x267a70, (const char *)0x267a3c, 0x9d, 1);
      halt_and_catch_fire();
    }
    return FUN_001d0c48(0, (uint32_t)size);
  }
  if (size == 0) {
    LocalFree(ptr);
    return NULL;
  }
  return FUN_001d0c65(ptr, (uint32_t)size, 2);
}


uint32_t system_get_used_memory_size(uint32_t *output)
{
  return ((uint32_t(__stdcall *)(void *))0x1d0c02)(output);
}

void FUN_0008e480(uint32_t *output)
{
  uint32_t status[8];

  csmemset(status, 0, 0x20);
  status[0] = 0x20;
  xbox_query_global_memory_status(status);
  csmemset(output, 0, 8);
  output[0] = status[3];
  output[1] = status[2];
}

/* system_exception_name (0x8e500) — readable C lift. */
const char *system_exception_name(unsigned int code /* @<ecx> */)
{
  unsigned int idx;

  if (code == 0x80000003u)
    return (const char *)0x267c40;
  if (code == 0x80000002u)
    return (const char *)0x267c20;
  if (code == 0x80000004u)
    return (const char *)0x267c08;
  if (code == 0xc0000005u)
    return (const char *)0x267bec;
  if (code == 0xc0000025u)
    return (const char *)0x267bc8;
  if (code == 0xc000008eu)
    return (const char *)0x267ba8;
  if (code == 0xc000008du)
    return (const char *)0x267b88;
  if (code == 0xc000008cu)
    return (const char *)0x267b68;
  if (code == 0xc000008fu)
    return (const char *)0x267b48;
  /* codes 0xc0000090 .. 0xc0000096 */
  idx = code + 0x3fffff70u;
  if (idx > 6u)
    return 0;
  switch (idx) {
  case 0: return (const char *)0x267b28;
  case 1: return (const char *)0x267b10;
  case 2: return (const char *)0x267af4;
  case 3: return (const char *)0x267adc;
  case 4: return (const char *)0x267abc;
  case 5: return (const char *)0x267aa4;
  case 6: return (const char *)0x267a88;
  default: return 0;
  }
}

