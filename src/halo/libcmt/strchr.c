/* kb object stubs -> libcmt/strchr.c */

/* --- LIBCMT:strchr.obj batch drafts (2026-07-26) --- */

/* 0x1d94f0 */
void FUN_001d94f0(void)
{
  FUN_001dee48();
  FUN_001d950d();
  __fload_withFB();
}

/* 0x1d950d */
void FUN_001d950d(void)
{
  int eax = 0;

  /* relift: cmp word ptr [esp], 0x27f -> je 0x1d9521 */
  FUN_001dedd5();
  /* cmp eax, 0x3ff00000 -> jae 0x1d9555 */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  FUN_001dedec();
  /* test eax, 0xfffff -> jne 0x1d957a */
  /* relift: cmp dword ptr [esp + 8], 0 -> jne 0x1d957a */
  /* relift: relift: fld xword ptr [0x3314b8] */
  /* relift: cmp dword ptr [0x4fc000], 0 -> jne 0x1dee5e */
  __startOneArgErrorHandling();

  (void)eax;
}

/* 0x1d95d0 */
char *crt_strchr(const char *str, int c)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edx, 3 -> je 0x1d95fb */
  /* cmp (char)ecx, (char)ebx -> je 0x1d95c0 */
  /* test (char)ecx, (char)ecx -> je 0x1d9644 */
  /* test edx, 3 -> jne 0x1d95e8 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9685 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d967e */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9677 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* cmp (char)eax, (char)ebx -> je 0x1d9670 */
  /* test (char)eax, (char)eax -> je 0x1d9642 */
  /* test dl, dl -> je 0x1d970a */
  /* test (char)edx, (char)edx -> je 0x1d96f7 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> je 0x1d96c4 */
  /* cmp (char)eax, dl -> je 0x1d96ca */
  /* test (char)eax, (char)eax -> jne 0x1d96b9 */
  /* cmp (char)eax, (char)edx -> jne 0x1d96bc */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> jne 0x1d96a8 */
  /* test (char)eax, (char)eax -> je 0x1d9703 */
  /* cmp (char)eax, (char)eax -> je 0x1d96d4 */
  /* relift: cmp byte ptr [edi], (char)eax -> je 0x1d9731 */
  FUN_001df055();
  FUN_001defb3();
  /* test eax, eax -> je 0x1d9756 */
  /* relift: cmp esi, dword ptr [esp + 8] -> jb 0x1d974e */
  FUN_001df055();
  /* mem[0x004fc010] = 1 */
  /* relift: relift: mov byte ptr [0x4fc00c], (char)ebx */
  /* test ecx, ecx -> je 0x1d97b5 */
  /* test eax, eax -> je 0x1d97a0 */
  /* mem[0x00632dcc] = eax */
  /* cmp eax, edi -> jae 0x1d97d4 */
  /* test eax, eax -> je 0x1d97cd */
  /* cmp esi, edi -> jb 0x1d97c5 */
  /* cmp eax, edi -> jae 0x1d97f3 */
  /* test eax, eax -> je 0x1d97ec */
  /* cmp esi, edi -> jb 0x1d97e4 */
  FUN_001defb3();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001d9761();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d98a3();
  __SEH_epilog();
  __unlock_file();
  FUN_001dd5c8();
  __lock_file();
  __stbuf();
  FUN_001de452();
  __ftbuf();
  FUN_001d9901();
  __SEH_epilog();
  __unlock_file();
  /* cmp eax, esi -> jge 0x1d9930 */
  /* mem[0x00632dc4] = eax */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* mem[0x00632dc4] = esi */
  FUN_001df1bd();
  /* mem[0x00632dc0] = eax */
  /* cmp ecx, 0x3312b0 -> jl 0x1d996a */
  /* cmp eax, -1 -> je 0x1d99a7 */
  /* test eax, eax -> jne 0x1d99aa */
  /* cmp edx, 0x3310a0 -> jl 0x1d9987 */
  __flushall();
  /* relift: cmp byte ptr [0x4fc00c], 0 -> je 0x1d99cd */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
