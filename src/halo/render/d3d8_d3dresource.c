/* --- D3D8:d3dresource.obj batch drafts (2026-07-26) --- */

/* D3D_DestroyResource (0x1ed7d0) — Capstone tip: type 0x10000/0x60000 → LocalFree path. */
void __stdcall D3D_DestroyResource(void *resource)
{
  unsigned int *r;
  unsigned int common;
  unsigned int kind;

  r = (unsigned int *)resource;
  common = r[0];
  kind = common & 0x70000u;
  if (kind != 0x50000u || (int)common >= 0)
    D3D_BlockOnResource(resource);

  FUN_001ed4e0(resource);

  if (kind == 0x10000u || kind == 0x60000u) {
    FUN_001d0c16(resource);
    return;
  }
}


/* 0x1efa80 */
void __stdcall D3D_BlockOnTime(uint32_t time, int param2)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp ecx, edx -> jae 0x1efb3f */
  /* cmp esi, eax -> jne 0x1efabc */
  D3D_SetFence(0);
  /* relift: FUN_001ef7e0(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jb 0x1efb27 */
  /* relift: FUN_001ef860(0, 0); */
  /* relift: FUN_001ef770(0, 0); */
  /* cmp eax, 0x8000 -> jae 0x1efb45 */
  /* relift: FUN_001ef860(0, 0); */
  /* cmp eax, esi -> jb 0x1efb34 */
  /* test eax, eax -> jne 0x1efb51 */
  /* cmp eax, edx -> ja 0x1efbca */
  /* cmp eax, ecx -> je 0x1efbf0 */
  /* cmp eax, edx -> jb 0x1efc2f */
  /* relift: cmp eax, dword ptr [esi + 0x14] -> jb 0x1efc43 */
  /* cmp ecx, eax -> jae 0x1efd12 */
  /* relift: cmp eax, dword ptr [esp + 8] -> ja 0x1efd12 */
  /* relift: cmp edi, dword ptr [esp + 0x14] -> jae 0x1efc8c */
  /* cmp edi, ebp -> jb 0x1efd3e */
  /* cmp eax, ecx -> je 0x1efcb6 */
  /* cmp ecx, edx -> jb 0x1efc80 */
  /* cmp eax, edx -> jb 0x1efce9 */
  /* relift: cmp eax, dword ptr [esi + 0x14] -> jb 0x1efcfd */
  /* relift: cmp dword ptr [esp + 0x14], eax -> jae 0x1efd09 */
  /* relift: cmp eax, dword ptr [esp + 0x10] -> jbe 0x1efcc0 */
  /* relift: FUN_001ef740(0, 0); */
  CDevice_KickOff();
  /* relift: tail-call D3D_BlockOnTime(); */
  D3D_SetFence(0);
  CDevice_KickOff();
  /* relift: tail-call D3D_BlockOnTime(); */
  /* test eax, eax -> je 0x1efdfe */
  /* test edi, edi -> je 0x1efdc6 */
  /* relift: FUN_001ed870(0); */
  /* test eax, eax -> je 0x1efdc4 */
  /* relift: tail-call D3D_BlockOnTime(); */
  /* relift: FUN_001ed870(0); */
  /* relift: tail-call D3D_BlockOnTime(); */
  /* relift: tail-call D3D_BlockOnTime(); */
  /* relift: cmp eax, dword ptr [ecx + 4] -> jb 0x1efe20 */
  CDevice_MakeSpace();
  CDevice_MakeSpace();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
