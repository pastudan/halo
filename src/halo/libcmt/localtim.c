/* kb object stubs -> libcmt/localtim.c */

/* --- LIBCMT:localtim.obj batch drafts (2026-07-26) --- */

/* 0x1da92a */
void *crt_localtime(int *timer)
{
  int eax = 0;
  int esi = 0;

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
  FUN_001e153d();
  /* test eax, eax -> jne 0x1dad11 */
  /* relift: cmp dword ptr [esp + 4], 0x5f -> je 0x1dad11 */
  return NULL;

  (void)eax;
  (void)esi;
}
