/* kb object stubs -> libcmt/strncat.c */

/* --- LIBCMT:strncat.obj batch drafts (2026-07-26) --- */

/* 0x1da5d0 */
char *crt_strncat(char *dest, const char *src, size_t count)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test ecx, ecx -> je 0x1da684 */
  /* test (char)eax, (char)eax -> je 0x1da62b */
  /* test edi, 3 -> jne 0x1da5eb */
  /* test eax, 0x81010100 -> je 0x1da5fa */
  /* test (char)eax, (char)eax -> je 0x1da638 */
  /* test (char)eax, (char)eax -> je 0x1da633 */
  /* test eax, 0xff0000 -> je 0x1da62e */
  /* test eax, 0xff000000 -> jne 0x1da5fa */
  /* test esi, 3 -> jne 0x1da650 */
  /* test dl, dl -> je 0x1da68a */
  /* test esi, 3 -> jne 0x1da650 */
  /* test dl, dl -> je 0x1da682 */
  /* test eax, 0x81010100 -> je 0x1da694 */
  /* test dl, dl -> je 0x1da68a */
  /* test (char)edx, (char)edx -> je 0x1da6e8 */
  /* test edx, 0xff0000 -> je 0x1da6d8 */
  /* test edx, 0xff000000 -> jne 0x1da694 */
  /* relift: cmp (char)eax, byte ptr [edi - 1] -> ja 0x1da72f */
  /* test ecx, ecx -> je 0x1da7c3 */
  /* test (char)eax, (char)eax -> je 0x1da79a */
  /* test esi, 3 -> jne 0x1da764 */
  /* test (char)eax, (char)eax -> je 0x1da7be */
  /* test edi, 3 -> je 0x1da7b4 */
  /* test edi, 3 -> jne 0x1da7a2 */
  /* test eax, 0x81010100 -> je 0x1da7c9 */
  /* test dl, dl -> je 0x1da81b */
  /* test (char)edx, (char)edx -> je 0x1da811 */
  /* test edx, 0xff0000 -> je 0x1da807 */
  /* test edx, 0xff000000 -> jne 0x1da7c9 */
  FUN_001dff91();
  /* test dl, dl -> jne 0x1da85f */
  /* test edx, edx -> jne 0x1da88e */
  /* test (char)eax, (char)eax -> je 0x1da8a7 */
  /* test (char)ecx, (char)ebx -> jne 0x1da889 */
  /* test (char)ecx, (char)eax -> jne 0x1da8ca */
  /* relift: cmp byte ptr [edx], 0 -> jne 0x1da8ab */
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
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
