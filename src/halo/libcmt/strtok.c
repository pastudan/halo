/* kb object stubs -> libcmt/strtok.c */

/* --- LIBCMT:strtok.obj batch drafts (2026-07-26) --- */

/* 0x1da83e */
char *crt_strtok(char *string, const char *delimiters)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  FUN_001dff91();
  /* test dl, dl -> jne 0x1da85f */
  /* test edx, edx -> jne 0x1da88e */
  /* test (char)eax, (char)eax -> je 0x1da8a7 */
  /* test (char)ecx, (char)ebx -> jne 0x1da889 */
  /* test (char)ecx, (char)eax -> jne 0x1da8ca */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x1da8ab */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x1da8e3 */
wchar_t *FUN_001da8e3(wchar_t *s, size_t count)
{
  int eax = 0;
  int esi = 0;

  /* cmp (int16_t)esi, (int16_t)eax -> je 0x1da928 */
  /* relift: cmp dword ptr [0x4fc25c], 0 -> jne 0x1da914 */
  /* cmp (int16_t)esi, 0x41 -> jb 0x1da90f */
  /* cmp (int16_t)esi, 0x5a -> ja 0x1da90f */
  /* cmp (int16_t)esi, 0x100 -> jae 0x1da925 */
  FUN_001dc3e9(0, 0);
  /* relift: cmp dword ptr [esi], 0 -> jge 0x1da93d */
  FUN_001e1953();
  /* cmp eax, 0x3f480 -> jle 0x1da9a3 */
  /* cmp eax, 0x7ffc0b7f -> jge 0x1da9a3 */
  _gmtime();
  FUN_001e1997();
  _gmtime();
  _gmtime();
  FUN_001e1997();
  /* test eax, eax -> jg 0x1daa67 */
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1daac4 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1daaef */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab18 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab41 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab6d */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dab98 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dabc1 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dabed */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac1b */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac49 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dac74 */
  FUN_001e153d();
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dacb6 */
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dacd4 */
  /* relift: cmp dword ptr [esp + 4], 0x5f -> je 0x1dacd4 */
  /* relift: cmp dword ptr [0x3317bc], 1 -> jle 0x1dacf3 */
  return NULL;

  (void)eax;
  (void)esi;
}
