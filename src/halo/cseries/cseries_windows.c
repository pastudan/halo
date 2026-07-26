char *system_stristr(const char *str, const char *substr)
{
  char c;
  char sc;
  int len;

  c = *substr;
  if (c == '\0')
    return (char *)str;

  len = csstrlen(substr + 1);
  for (;;) {
    do {
      sc = *str++;
      if (sc == '\0')
        return NULL;
    } while (sc != c);
    if (((int(__cdecl *)(const char *, const char *, size_t))0x1e6596)(
          str, substr + 1, len) == 0)
      return (char *)(str - 1);
  }
}

uint32_t system_string_hash(const char *str)
{
  uint32_t crc;

  crc_new(&crc);
  crc_checksum_buffer(&crc, (void *)str, csstrlen(str));
  return crc;
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

int system_unique_identifiers_equal(const void *id1, const void *id2)
{
  uint8_t zeros[16];

  csmemset(zeros, 0, 16);
  if (csmemcmp(id1, zeros, 16) != 0) {
    if (csmemcmp(id1, id2, 16) == 0)
      return 1;
  }
  return 0;
}

uint32_t system_milliseconds(void)
{
  return ((uint32_t(*)(void))0x1d0581)();
}

uint32_t system_seconds(void)
{
  return crt_time(NULL);
}

void system_get_user_name(char *buffer, int16_t max_len)
{
  csstrncpy(buffer, "xbox", max_len);
}

void *system_calloc(int count, int size)
{
  return ((void *(__stdcall *)(uint32_t, uint32_t))0x1d0c48)(0x40,
                                                             count * size);
}

void *system_malloc(int size)
{
  return ((void *(__stdcall *)(uint32_t, uint32_t))0x1d0c48)(0, size);
}

void system_free(void *ptr)
{
  ((void *(__stdcall *)(void *))0x1d0c16)(ptr);
}

void *system_realloc(void *ptr, int size)
{
  if (size < 0) {
    display_assert("size>=0", "c:\\halo\\SOURCE\\cseries\\cseries_windows.c",
                   0x9c, 1);
    halt_and_catch_fire();
  }
  if (ptr == NULL) {
    if (size == 0) {
      display_assert("pointer||size",
                     "c:\\halo\\SOURCE\\cseries\\cseries_windows.c", 0x9d, 1);
      halt_and_catch_fire();
    }
    return ((void *(__stdcall *)(uint32_t, uint32_t))0x1d0c48)(0, size);
  }
  if (size != 0)
    return ((void *(__stdcall *)(void *, uint32_t, uint32_t))0x1d0c65)(ptr,
                                                                       size, 2);

  ((void(__stdcall *)(void *))0x1d0c16)(ptr);
  return NULL;
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

/* system_exception_name (0x8e500) — XBE naked draft (batch 90). */
#if defined(__clang__)


__attribute__((naked, noinline))
const char * system_exception_name(uint32_t code __attribute__((unused)))
{
  __asm__ volatile(
      "xorl %%eax, %%eax\n\t"
      "cmpl $0xc000008f, %%ecx\n\t"
      "ja .Lsystem_exception_name_9\n\t"
      "je .Lsystem_exception_name_8\n\t"
      "cmpl $0xc0000025, %%ecx\n\t"
      "ja .Lsystem_exception_name_5\n\t"
      "je .Lsystem_exception_name_4\n\t"
      "cmpl $0x80000004, %%ecx\n\t"
      "ja .Lsystem_exception_name_3\n\t"
      "je .Lsystem_exception_name_2\n\t"
      "cmpl $0x80000002, %%ecx\n\t"
      "je .Lsystem_exception_name_1\n\t"
      "cmpl $0x80000003, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267c40, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_1:\n\t"
      "movl $0x267c20, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_2:\n\t"
      "movl $0x267c08, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_3:\n\t"
      "cmpl $0xc0000005, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267bec, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_4:\n\t"
      "movl $0x267bc8, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_5:\n\t"
      "cmpl $0xc000008c, %%ecx\n\t"
      "je .Lsystem_exception_name_7\n\t"
      "cmpl $0xc000008d, %%ecx\n\t"
      "je .Lsystem_exception_name_6\n\t"
      "cmpl $0xc000008e, %%ecx\n\t"
      "jne .Lsystem_exception_name_17\n\t"
      "movl $0x267ba8, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_6:\n\t"
      "movl $0x267b88, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_7:\n\t"
      "movl $0x267b68, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_8:\n\t"
      "movl $0x267b48, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_9:\n\t"
      "addl $0x3fffff70, %%ecx\n\t"
      "cmpl $6, %%ecx\n\t"
      "ja .Lsystem_exception_name_17\n\t"
      "jmp *.Lsystem_exception_name_jt(,%%ecx,4)\n\t"
      ".Lsystem_exception_name_10:\n\t"
      "movl $0x267b28, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_11:\n\t"
      "movl $0x267b10, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_12:\n\t"
      "movl $0x267af4, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_13:\n\t"
      "movl $0x267adc, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_14:\n\t"
      "movl $0x267abc, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_15:\n\t"
      "movl $0x267aa4, %%eax\n\t"
      "ret\n\t"
      ".Lsystem_exception_name_16:\n\t"
      "movl $0x267a88, %%eax\n\t"
      ".Lsystem_exception_name_17:\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lsystem_exception_name_jt:\n\t"
      ".long .Lsystem_exception_name_10\n\t"
      ".long .Lsystem_exception_name_11\n\t"
      ".long .Lsystem_exception_name_12\n\t"
      ".long .Lsystem_exception_name_13\n\t"
      ".long .Lsystem_exception_name_14\n\t"
      ".long .Lsystem_exception_name_15\n\t"
      ".long .Lsystem_exception_name_16\n\t"
      ".text\n\t"
      :
      :
      : "memory");
}
#else
#error "system_exception_name: clang naked draft required"
#endif

