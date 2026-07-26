/* kb object stubs -> xdk/xapilib/xinput.c */

/* --- XAPILIB:xinput.obj batch drafts (2026-07-26) --- */

/* 0x24c427 */
int XInputSetState(int unused_arg_0, void * unused_arg_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: cmp byte ptr [eax], 1 -> jne 0x24c43b */
  /* relift: FUN_0024d0ae(0, 0); */
  /* cmp ecx, esi -> je 0x24c4a4 */
  /* relift: test byte ptr [ecx + 4], 2 -> jne 0x24c4a4 */
  /* relift: test byte ptr [eax + 0xa2], 8 -> jne 0x24c4a9 */
  /* relift: cmp dword ptr [eax + 4], esi -> jne 0x24c4a9 */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> je 0x24c4d2 */
  /* mem[0x004eb0b8] = ecx */
  /* mem[0x004eb0b8] = edx */
  /* relift: FUN_0024d981(0, 0, 0); */
  /* cmp eax, 0x10 -> jb 0x24c516 */
  /* relift: FUN_0024d90b(0, 0, 0); */
  /* cmp eax, ebx -> je 0x24c57f */
  /* relift: FUN_0024d90b(0, 0, 0); */
  /* cmp eax, ebx -> je 0x24c57f */
  /* relift: FUN_0024d7ec(0); */
  /* relift: FUN_0024d811(0, 0); */
  /* relift: FUN_0024d815(0); */
  /* relift: FUN_0024eff0(0x80000400); */
  /* test eax, 0x20000 -> je 0x24c5e1 */
  /* test eax, 0x10000 -> je 0x24c61a */
  /* relift: FUN_0024dc24(0); */
  /* relift: test byte ptr [esi + 0xc], 2 -> je 0x24c65d */
  /* relift: FUN_0024ec32(0, 0); */
  /* test edx, eax -> jne 0x24c67c */
  /* relift: FUN_0024c591(0); */
  /* relift: FUN_0024d7e8(0); */
  /* test ecx, ecx -> je 0x24c6a4 */
  /* test (char)eax, 4 -> jne 0x24c6a4 */
  /* relift: FUN_0024c663(0, 0); */
  /* relift: FUN_0024ec32(0, 0); */
  /* relift: FUN_0024c663(0, 0); */
  /* relift: FUN_0024c4d3(0); */
  /* relift: FUN_0024c4b8(0, 0); */
  /* cmp esi, ebx -> jne 0x24c75c */
  /* relift: FUN_0024c4d3(0, 0); */
  /* relift: FUN_0024dc24(0); */
  /* test eax, eax -> jl 0x24c881 */
  /* relift: FUN_0024dc24(0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}
