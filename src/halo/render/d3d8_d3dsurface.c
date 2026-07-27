/* --- D3D8:d3dsurface.obj batch drafts (2026-07-26) --- */

extern int DbgPrint(uintptr_t fmt, ...);

/* 0x1e9190 */
int __stdcall D3DDevice_PersistDisplay(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test eax, eax -> jne 0x1e91c7 */
  CMiniport_IsFlipPending();
  /* test eax, eax -> jne 0x1e91d0 */
  /* test eax, eax -> jne 0x1e9222 */
  /* relift: FUN_001ef3d0(0, 0, 0, 0); */
  /* test eax, eax -> jl 0x1e92ab */
  D3DDevice_CopyRects();
  D3D_KickOffAndWaitForIdle();
  /* relift: FUN_001e77d0(0, 0); */
  /* relift: FUN_001f3cd0(0, 0); */
  /* test esi, esi -> jne 0x1e9260 */
  /* mem[0x0033026c] = eax */
  /* mem[0x00330270] = ecx */
  /* mem[0x00330274] = edx */
  /* mem[0x00330278] = eax */
  /* mem[0x001fb8b0] = ecx */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)eax, (void *)(uintptr_t)edx);
  /* mem[0x001fb868] = ecx */
  /* relift: cmp eax, dword ptr [0x1fbb14] -> jae 0x1e936c */
  /* mem[0x001fbb10] = eax */
  CDevice_MakeSpace();
  /* cmp esi, 0x52 -> jge 0x1e93c9 */
  D3DDevice_SetRenderState_Simple(edi, 0);
  /* cmp esi, 0x74 -> jge 0x1e93ea */
  D3DDevice_SetRenderStateNotInline();
  /* mem[0x001fbb18] = esi */
  /* relift: FUN_001f3c30(0, 0); */
  XMETAL_StartPush();
  /* mem[0x001fb8a4] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb8b4] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb870] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb894] = ecx */
  /* mem[0x001fb894] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb890] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb880] = ecx */
  /* test eax, eax -> jne 0x1e97ef */
  XMETAL_StartPush();
  /* mem[0x001fb898] = eax */
  /* mem[0x001fb898] = eax */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 0x1ff -> jbe 0x1e983f */
  XMETAL_StartPush();
  /* mem[0x001fb8b8] = ebx */
  /* cmp dl, 0x20 -> jne 0x1e9889 */
  /* cmp edi, ecx -> je 0x1e98cb */
  XMETAL_StartPush();
  /* mem[0x001fb8bc] = ebx */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderStateNotInline();
  /* mem[0x001fb89c] = edi */
  XMETAL_StartPush();
  /* test ecx, ecx -> jne 0x1e998d */
  /* mem[0x001fb8a0] = ecx */
  /* mem[0x001fb8a0] = ecx */
  XMETAL_StartPush();
  /* mem[0x001fb874] = ecx */
  /* mem[0x001fb878] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */
  /* mem[0x001fb87c] = eax */
  XMETAL_StartPush();
  /* mem[0x001fb874] = esi */
  XMETAL_StartPush();
  /* mem[0x001fb86c] = ecx */
  /* test ecx, ecx -> je 0x1e9b22 */
  /* cmp ecx, 0x10000 -> jne 0x1e9b44 */
  /* cmp ecx, 0x30000 -> je 0x1e9b52 */
  /* cmp ecx, 0x40000 -> je 0x1e9b4b */
  /* test edx, edx -> jne 0x1e9b6e */
  /* test eax, eax -> je 0x1e9b6e */
  XMETAL_StartPush();
  XMETAL_StartPush();
  XMETAL_StartPush();
  XMETAL_StartPush();
  /* cmp eax, 0x1c -> jne 0x1e9cf9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp eax, 0x1d -> jne 0x1e9d10 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp eax, 0x1e -> jne 0x1e9d27 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp eax, 0x1b -> jg 0x1e9cdf */
  /* relift: cmp dword ptr [0x1fb8a8], edx -> je 0x1e9e3c */
  /* relift: test byte ptr [esi + 4], 6 -> je 0x1e9f34 */
  /* relift: test dword ptr [ecx + 0xc], 0x200 -> jne 0x1e9f18 */
  /* test esi, esi -> jge 0x1e9e6f */
  /* relift: cmp dword ptr [0x1fb884], 2 -> jne 0x1e9fa3 */
  /* test eax, eax -> je 0x1e9fcb */
  /* cmp eax, 0x2d -> je 0x1e9fc5 */
  /* cmp eax, 0x2b -> je 0x1e9fc5 */
  /* cmp eax, 0x31 -> je 0x1e9fc5 */
  /* cmp eax, 0x2f -> jne 0x1e9fcb */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x30 -> je 0x1ea08f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1ea080 */
  /* relift: FUN_001f3c30(0, 0); */
  D3DDevice_SetRenderStateNotInline();
  XMETAL_StartPush();
  /* relift: FUN_001f3e40(0, 0); */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* test ecx, ecx -> je 0x1ea181 */
  /* test ecx, ecx -> je 0x1ea1a4 */
  /* test ecx, ecx -> je 0x1ea1a1 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea1a4 */
  /* test eax, eax -> je 0x1ea227 */
  XMETAL_StartPush();
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1ea2b6 */
  /* test edx, edx -> je 0x1ea2b6 */
  /* mem[0x001fb884] = ecx */
  /* cmp ecx, 2 -> jne 0x1ea2f8 */
  D3D_UpdateProjectionViewportTransform();
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea31e */
  /* test edx, edx -> je 0x1ea341 */
  /* test edx, edx -> je 0x1ea33e */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea341 */
  /* test edx, edx -> je 0x1ea366 */
  /* test ecx, ecx -> je 0x1ea366 */
  /* mem[0x001fb888] = edx */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea39e */
  /* test edx, edx -> je 0x1ea3c1 */
  /* test edx, edx -> je 0x1ea3be */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea3c1 */
  /* mem[0x001fb88c] = ecx */
  /* mem[0x001fb8c0] = eax */
  XMETAL_StartPush();
  /* relift: FUN_001e9f80(0, 0); */
  /* mem[0x001fb8c4] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea447 */
  /* test edx, edx -> je 0x1ea46a */
  /* test edx, edx -> je 0x1ea467 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea46a */
  /* mem[0x001fb8c8] = eax */
  XMETAL_StartPush();
  /* test edx, edx -> je 0x1ea4a7 */
  /* test edx, edx -> je 0x1ea4ca */
  /* test edx, edx -> je 0x1ea4c7 */
  /* relift: cmp dword ptr [0x1fb88c], 0x1e00 -> jne 0x1ea4ca */
  /* mem[0x001fb8cc] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8d0] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8d4] = eax */
  D3D_CommonSetDebugRegisters();
  /* mem[0x001fb8a8] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* mem[0x001fb8ac] = eax */
  /* relift: FUN_001eb6f0(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3e40(0, 0); */
  XMETAL_StartPush();
  /* test dl, 0xf0 -> je 0x1ea71b */
  /* cmp eax, 0x19 -> ja 0x1ea71b */
  /* cmp ebx, ebp -> jne 0x1ea72c */
  /* test dl, 1 -> je 0x1ea820 */
  /* cmp eax, 7 -> ja 0x1ea820 */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp eax, 0xffff -> jle 0x1ea76b */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp eax, 0xffffff -> jle 0x1ea79d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: cmp dword ptr [esp + 0x18], eax -> jge 0x1ea992 */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  XMETAL_StartPush();
  /* test edi, edi -> je 0x1ea9c4 */
  XMETAL_StartPush();
  /* cmp ecx, 4 -> jne 0x1eaa6d */
  /* test ecx, ecx -> je 0x1eaaa0 */
  /* test (char)ebx, 0x10 -> je 0x1eaab2 */
  /* test (char)ecx, (char)ebx -> je 0x1eaad0 */
  /* cmp edx, 1 -> jne 0x1eabb3 */
  /* cmp ecx, ebx -> je 0x1eacc5 */
  /* cmp ecx, 0x20000000 -> je 0x1eadf6 */
  /* cmp ecx, 0x40000000 -> jne 0x1eacc5 */
  /* test eax, 0x10000000 -> je 0x1ead21 */
  /* test eax, 0x8000000 -> jne 0x1ead1d */
  /* cmp eax, 9 -> jb 0x1ead40 */
  /* cmp eax, 0xc -> ja 0x1ead40 */
  /* cmp eax, 9 -> jb 0x1ead96 */
  /* cmp eax, 0xc -> ja 0x1ead96 */
  /* cmp ecx, 7 -> jne 0x1ead85 */
  /* cmp edi, 0x16 -> jne 0x1ead8f */
  /* cmp eax, 3 -> jne 0x1eada5 */
  /* cmp eax, 4 -> jne 0x1eadb4 */
  /* cmp eax, 7 -> jne 0x1eadc3 */
  /* cmp eax, 8 -> jne 0x1eadd3 */
  /* cmp ecx, 0x80000000 -> je 0x1eae5c */
  /* cmp ecx, 0xe0000000 -> jne 0x1eacc5 */
  /* cmp edx, 0x80000000 -> jne 0x1eaf4b */
  /* test ebp, ebp -> je 0x1eaedc */
  /* test ebp, ebp -> je 0x1eaf2c */
  /* test ebp, ebp -> je 0x1eafa2 */
  /* test ecx, ecx -> je 0x1eafb6 */
  /* relift: FUN_001eae70(0, 0); */
  FUN_001d0bb9(0, eax);
  /* test esi, esi -> jne 0x1eafd9 */
  /* test edi, edi -> je 0x1eb023 */
  /* relift: FUN_001eacb0(0, 0, 0); */
  /* test ebp, ebp -> je 0x1eb076 */
  /* cmp ecx, 0x7378 -> jne 0x1eb052 */
  /* relift: FUN_001eac20(0, 0); */
  /* test edi, edi -> je 0x1eb088 */
  /* relift: FUN_001eae70(0, 0); */
  /* test ecx, ecx -> je 0x1eb135 */
  /* test edi, edi -> je 0x1eb160 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  /* relift: FUN_001ef590(0, 0); */
  /* relift: FUN_001ed8b0(0); */
  /* test eax, eax -> je 0x1eb321 */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  /* test edi, edi -> je 0x1eb393 */
  /* relift: FUN_001ed8f0(0); */
  XMETAL_StartPush();
  /* test ecx, ecx -> je 0x1eb3e6 */
  /* test (char)eax, 0x10 -> jne 0x1eb421 */
  /* relift: FUN_001eab60(0, 0); */
  /* relift: FUN_001efe30(0, 0); */
  /* test (char)ecx, 0x10 -> jne 0x1eb495 */
  /* relift: FUN_001efe30(0, 0); */
  /* relift: FUN_001eac20(0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1eb551 */
  /* test (char)eax, 8 -> je 0x1eb572 */
  /* test ecx, ecx -> je 0x1eb587 */
  XMETAL_StartPush();
  /* relift: FUN_001ef590(0, 0); */
  /* relift: FUN_001ef590(0, 0x00400880, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x004008c0, 0x001f9f48); */
  /* relift: FUN_001ef590(0, 0x00400900, 0x001f9f48); */
  XMETAL_StartPush();
  /* relift: FUN_001eac20(0); */
  /* relift: test byte ptr [eax + 4], 2 -> je 0x1eb7ee */
  /* relift: test byte ptr [esi + 0xc], 2 -> je 0x1eb72a */
  /* relift: FUN_001efe30(0, 0); */
  /* relift: cmp dword ptr [0x1fb884], 2 -> jne 0x1eb765 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)ecx, 0x10 -> je 0x1eb7c0 */
  /* relift: cmp dword ptr [0x1fb8a8], ebx -> je 0x1eb7c0 */
  /* cmp edx, ecx -> jne 0x1eb7c0 */
  /* relift: relift: fld dword ptr [0x1f9f98] */
  /* relift: FUN_001eac20(0); */
  /* relift: FUN_001eaa20(0, 0); */
  /* test (char)eax, 4 -> je 0x1eb860 */
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001eb6f0(0, 0); */
  XMETAL_StartPush();
  /* relift: FUN_001e9db0(0, 0); */
  /* relift: FUN_001efe30(0, 0); */
  /* cmp eax, 0x20 -> jle 0x1eb94e */
  /* cmp eax, 0x20 -> jg 0x1eb935 */
  /* test (char)ecx, 8 -> je 0x1eb991 */
  /* relift: cmp dword ptr [ecx - 4], esi -> jne 0x1eb9f7 */
  /* relift: cmp esi, dword ptr [esp + 0x10] -> jae 0x1eb9f7 */
  /* cmp esi, eax -> jb 0x1eb9f7 */
  /* relift: cmp byte ptr [ecx + 8], 0 -> jne 0x1eb9f7 */
  /* relift: cmp dword ptr [ecx + 4], 2 -> je 0x1eb9f7 */
  /* test esi, esi -> jne 0x1eb9d0 */
  /* relift: cmp dword ptr [esp + 0x10], -1 -> je 0x1ebaa4 */
  /* relift: cmp ecx, dword ptr [esp + 0x18] -> je 0x1eba28 */
  /* test edx, edx -> je 0x1eba4f */
  /* cmp (char)eax, 2 -> jne 0x1ebad7 */
  /* test edx, edx -> je 0x1ebaf0 */
  /* cmp (char)eax, 1 -> jne 0x1ebaf1 */
  /* test edx, edx -> je 0x1ebaf0 */
  /* cmp (char)eax, 2 -> jne 0x1ebb06 */
  /* test edx, edx -> je 0x1ebb22 */
  /* cmp (char)eax, 1 -> jne 0x1ebb23 */
  /* test edx, edx -> je 0x1ebb22 */
  /* cmp (char)eax, 2 -> jne 0x1ebb37 */
  /* test edx, edx -> je 0x1ebb50 */
  /* cmp (char)eax, 1 -> jne 0x1ebb51 */
  /* test edx, edx -> je 0x1ebb50 */
  /* cmp (char)eax, 2 -> jne 0x1ebb66 */
  /* test edx, edx -> je 0x1ebb82 */
  /* cmp (char)eax, 1 -> jne 0x1ebb83 */
  /* test edx, edx -> je 0x1ebb82 */
  /* cmp (char)eax, 2 -> jne 0x1ebb98 */
  /* test edx, edx -> je 0x1ebbb4 */
  /* cmp (char)eax, 1 -> jne 0x1ebbb5 */
  /* test edx, edx -> je 0x1ebbb4 */
  /* cmp (char)eax, 2 -> jne 0x1ebbca */
  /* test edx, edx -> je 0x1ebbe6 */
  /* cmp (char)eax, 1 -> jne 0x1ebbe7 */
  /* test edx, edx -> je 0x1ebbe6 */
  /* cmp (char)eax, 2 -> jne 0x1ebbfc */
  /* test edx, edx -> je 0x1ebc18 */
  /* cmp (char)eax, 1 -> jne 0x1ebc19 */
  /* test edx, edx -> je 0x1ebc18 */
  /* cmp (char)eax, 2 -> jne 0x1ebc2e */
  /* test edx, edx -> je 0x1ebc4a */
  /* cmp (char)eax, 1 -> jne 0x1ebc4b */
  /* test edx, edx -> je 0x1ebc4a */
  /* cmp (char)eax, 2 -> jne 0x1ebc63 */
  /* test edx, edx -> je 0x1ebc82 */
  /* cmp (char)eax, 1 -> jne 0x1ebc83 */
  /* test edx, edx -> je 0x1ebc82 */
  /* cmp (char)eax, 2 -> jne 0x1ebc9b */
  /* test edx, edx -> je 0x1ebcba */
  /* cmp (char)eax, 1 -> jne 0x1ebcbb */
  /* test edx, edx -> je 0x1ebcba */
  /* cmp esi, 0x16 -> jb 0x1ebac4 */
  /* test ecx, ecx -> je 0x1ebd39 */
  /* cmp ebp, 1 -> jne 0x1ebcf8 */
  /* cmp ecx, 0xb80 -> jne 0x1ebd2f */
  /* test edx, edx -> je 0x1ebd2b */
  /* test edx, edx -> jne 0x1ebd68 */
  /* test edx, edx -> jne 0x1eb997 */
  /* relift: test byte ptr [esi + 3], 4 -> jne 0x1ebdbb */
  /* test ecx, ecx -> je 0x1ebe55 */
  /* test (char)eax, 1 -> je 0x1ebe0f */
  /* test edi, edi -> jbe 0x1ebeb6 */
  /* relift: FUN_001ed8b0(0); */
  D3D_DestroyResource((void *)(uintptr_t)eax);
  XMETAL_StartPush();
  /* cmp esi, 9 -> jb 0x1ebf8c */
  /* cmp esi, 0xc -> ja 0x1ebf8c */
  /* cmp esi, 9 -> jb 0x1ebfce */
  /* cmp esi, 0xc -> ja 0x1ebfce */
  /* cmp eax, 9 -> jb 0x1ec00e */
  /* cmp eax, 0xc -> ja 0x1ec00e */
  /* cmp esi, 9 -> jb 0x1ec051 */
  /* cmp esi, 0xc -> ja 0x1ec051 */
  /* cmp esi, 0x10 -> jb 0x1ebf70 */
  FUN_001d0bb9(0, 252);
  /* test eax, eax -> jne 0x1ec0c8 */
  /* test ecx, ecx -> je 0x1ec118 */
  /* test (char)eax, 0x41 -> jne 0x1ec19b */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edi, 4 -> jb 0x1ec471 */
  /* cmp ebx, edi -> jae 0x1ec532 */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetRenderState_TextureFactor();
  XMETAL_StartPush();
  /* relift: FUN_001e9d40(0, 0); */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1ec67f */
  /* relift: FUN_001e9d40(0, 0); */
  /* test ecx, ecx -> je 0x1ec749 */
  /* relift: test byte ptr [ebx + 0xc], 0x10 -> jne 0x1ec76f */
  /* mem[0x001fb868] = eax */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x1ec7f2 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1ec825 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* test (char)eax, 0x41 -> jne 0x1ec86c */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* test (char)eax, 0x41 -> jne 0x1ec8b4 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: FUN_001f3c30(0, 0); */
  /* relift: FUN_001f3c30(0, 0); */
  /* cmp edx, ebp -> jne 0x1ec945 */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x20 -> jb 0x1ec922 */
  /* cmp edx, ebp -> jne 0x1ec971 */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x20 -> jb 0x1ec952 */
  /* cmp edx, ebp -> jne 0x1ec99f */
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 8 -> jb 0x1ec980 */
  /* test ebp, ebp -> jne 0x1ec9dc */
  XMETAL_StartPush();
  /* test (char)eax, 0x10 -> je 0x1ecc62 */
  D3D_SetFence();
  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ecd06 */
  /* relift: FUN_001efe30(0, 0); */
  /* test eax, eax -> je 0x1ecd6e */
  /* test (char)eax, 0x10 -> je 0x1ecd95 */
  D3D_SetFence();
  CDevice_SetStateUP();
  XMETAL_StartPush();
  /* cmp eax, ecx -> jb 0x1ece37 */
  /* relift: FUN_001efe30(0); */
  /* test (char)eax, 0x10 -> je 0x1eced1 */
  D3D_SetFence();
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0, 0); */
  CDevice_SetStateVB();
  /* relift: FUN_001efe30(0); */
  /* test eax, eax -> je 0x1ed035 */
  /* cmp edx, 0x3e -> jb 0x1ed062 */
  /* relift: FUN_001efe30(0, 516); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x1f4140 */
void __stdcall Get2DSurfaceDesc(void *texture, unsigned int level, void *desc)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  D3DResource_GetType();
  /* test (char)eax, 0x40 -> je 0x1f418d */
  /* relift: cmp eax, dword ptr [edx + 0x2154] -> jne 0x1f41ad */
  /* test (char)eax, 0x30 -> je 0x1f41ad */
  /* relift: FUN_001f3ff0(0, 0, 0, 0); */
  D3DResource_GetType();
  /* relift: FUN_001f3ff0(0, 0, 0, 0); */
  /* relift: FUN_001ed7c0(0, 0, 0); */
  /* cmp eax, 0xc -> je 0x1f42cc */
  /* cmp eax, 0xd -> jbe 0x1f42ce */
  /* cmp eax, 0xf -> ja 0x1f42ce */
  /* relift: cmp dword ptr [esp + 0x10], ecx -> jbe 0x1f431d */
  /* test eax, eax -> jbe 0x1f434a */
  /* test eax, eax -> jbe 0x1f4357 */
  /* test ecx, ecx -> je 0x1f43d6 */
  /* test edi, edi -> jbe 0x1f43c7 */
  /* test edx, edx -> jbe 0x1f43cc */
  /* cmp edi, eax -> ja 0x1f43f9 */
  /* cmp ecx, 0xc -> je 0x1f442d */
  /* cmp ecx, 0xd -> jle 0x1f441a */
  /* cmp ecx, 0xf -> jg 0x1f441a */
  /* test (char)ebx, 0x20 -> jne 0x1f44b0 */
  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x1f44f0 */
void __stdcall Lock2DSurface(void *texture, unsigned int face, unsigned int level, void *locked_rect, void *rect, unsigned int flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1f4578 */
  D3D_BlockOnResource();
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* cmp edi, 0xc -> je 0x1f46b2 */
  /* cmp edi, 0xd -> jbe 0x1f4667 */
  /* cmp edi, 0xf -> jbe 0x1f46b2 */
  /* relift: FUN_001f3cc0(0, 0); */
  /* relift: FUN_001f3cc0(0, 0); */
  /* relift: FUN_001f3cc0(0, 0); */
  /* cmp edi, 0xd -> jbe 0x1f46f4 */
  /* cmp edi, 0xf -> ja 0x1f46f4 */
  /* cmp esi, ecx -> jbe 0x1f4717 */
  /* cmp edx, ecx -> jbe 0x1f4748 */
  /* test edx, edx -> jbe 0x1f476f */
  /* test ebp, ebp -> jbe 0x1f4774 */
  /* test ecx, 0x10000 -> je 0x1f4851 */
  /* test ecx, 0x200000 -> je 0x1f485e */
  /* test ecx, 0x1000000 -> je 0x1f486d */
  /* test ecx, 0x2000000 -> je 0x1f487d */
  /* relift: cmp dword ptr [0x1fb468], eax -> jne 0x1f4899 */
  CMiniport_GetDisplayCapabilities();
  /* cmp ebp, 0x8f4 -> jb 0x1f48c7 */
  /* cmp edx, eax -> jae 0x1f490d */
  /* relift: cmp ecx, dword ptr [esp + 0x14] -> je 0x1f490d */
  /* cmp edx, eax -> jb 0x1f48f5 */
  /* relift: FUN_001f3cd0(rect, 0, 0, 0); */
  /* relift: FUN_001f3dd0(0); */
  /* relift: FUN_001f489f(0, 0); */
  CMiniport_GetDisplayCapabilities();
  /* relift: cmp dword ptr [ebp - 0xc], 4 -> jne 0x1f498e */
  /* relift: cmp dword ptr [ebp + 0x10], eax -> je 0x1f49b1 */
  /* relift: cmp dword ptr [ebp + 0x10], 0x32 -> je 0x1f49aa */
  /* relift: cmp dword ptr [ebp + 0x10], 0x3c -> jne 0x1f49b1 */
  /* relift: cmp dword ptr [ebp - 0xc], 4 -> jne 0x1f49d1 */
  /* relift: test dword ptr [ebp - 0x14], edi -> jne 0x1f49d1 */
  /* test edi, 0xe0000 -> jne 0x1f4a4b */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jne 0x1f4a4b */
  /* relift: cmp eax, dword ptr [ebp + 0xc] -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test (char)eax, 1 -> jne 0x1f4a4b */
  /* test eax, edi -> je 0x1f4a4b */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x1f4a62 */
  /* relift: test byte ptr [ebp - 4], 0x20 -> je 0x1f4a3d */
  /* test edi, 0x200000 -> jne 0x1f4a62 */
  /* relift: test byte ptr [ebp - 4], 0x40 -> je 0x1f4a4b */
  /* test edi, 0x200000 -> je 0x1f4a62 */
  /* relift: cmp eax, dword ptr [ebp - 0x18] -> je 0x1f49be */
  /* test ecx, ecx -> jne 0x1f4b12 */
  /* test ecx, ecx -> je 0x1f4bd7 */
  /* test eax, eax -> je 0x1f4bd7 */
  /* test eax, 0x1000000 -> je 0x1f4bb4 */
  /* relift: cmp dword ptr [esi + ecx*8 + 0x1b4], 1 -> jne 0x1f4b8b */
  /* relift: cmp dword ptr [esi + 4], 2 -> jne 0x1f4b7c */
  /* test (char)eax, 1 -> je 0x1f4b8b */
  /* mem[0x001fe6b4] = ecx */
  /* cmp eax, 0x80000000 -> jne 0x1f4bb4 */
  /* relift: test dword ptr [esi + 0x208], 0x200000 -> je 0x1f4bb4 */
  /* relift: FUN_001efe80(0); */
  /* cmp eax, ebx -> jne 0x1f4cc0 */
  /* relift: cmp dword ptr [esi + 4], 2 -> jne 0x1f4c31 */
  /* test (char)ebx, (char)eax -> je 0x1f4cc0 */
  /* relift: FUN_001efe80(0, 0); */
  /* relift: cmp dword ptr [esi + ebp*4 + 0x814], ebx -> jne 0x1f4c84 */
  /* relift: FUN_001eff04(0); */
  /* relift: test dword ptr [edi + 0x100], 0x1000000 -> jne 0x1f4cc0 */
  /* test eax, eax -> je 0x1f4d09 */
  /* test (char)ecx, 1 -> je 0x1f4d37 */
  /* cmp edx, -1 -> je 0x1f4d8d */
  /* cmp edx, -1 -> jne 0x1f4d60 */
  /* relift: cmp dword ptr [esp + 0x14], 0x308 -> jne 0x1f4db6 */
  /* relift: FUN_001efe80(0); */
  /* relift: cmp dword ptr [esi + edi*4 + 0x814], 1 -> jne 0x1f4e38 */
  /* relift: FUN_001eff04(0); */
  /* relift: FUN_001f4d40(0, 0); */
  /* relift: FUN_001ef860(0, 0); */
  /* relift: FUN_001f6135(0, 0); */
  /* test edx, edx -> jne 0x1f5010 */
  /* relift: FUN_001f8d2e(0); */
  /* test (char)ebx, 0x10 -> je 0x1f5033 */
  /* test ebx, 0x100000 -> je 0x1f505b */
  /* test dl, 0x40 -> je 0x1f505b */
  /* test ebx, ebx -> je 0x1f510a */
  /* cmp ebx, 0x1000000 -> je 0x1f510a */
  /* test (char)ebx, 0x10 -> je 0x1f509c */
  /* test ecx, ecx -> jne 0x1f5092 */
  /* test edx, edx -> je 0x1f50f1 */
  /* test (char)ebx, 1 -> jne 0x1f50ad */
  /* test ebx, 0x100000 -> je 0x1f50f1 */
  /* cmp ebp, 0x100 -> jne 0x1f50d9 */
  /* relift: FUN_001f4dc0(0, 0); */
  DbgPrint(0x001fb2d8, 0, 0, 0);
  /* test ebx, 0x10000 -> je 0x1f510a */
  /* test ecx, ecx -> jne 0x1f5100 */
  /* test eax, 0x1000000 -> je 0x1f5161 */
  /* test (char)ebx, dl -> je 0x1f51b0 */
  /* test (char)eax, 0x10 -> je 0x1f519e */
  /* test (char)edx, 0x10 -> je 0x1f521a */
  DbgPrint(0x001fb360, 0);
  DbgPrint(0x001fb354, 0);
  DbgPrint(0x001fb348, 0);
  /* cmp eax, ecx -> je 0x1f521a */
  /* test (char)eax, 0x10 -> je 0x1f528a */
  /* test (char)eax, 0x10 -> jne 0x1f5263 */
  /* relift: cmp dword ptr [esi + 0x2100], edi -> jne 0x1f5263 */
  /* relift: cmp dword ptr [esi + 0x400100], edi -> je 0x1f5247 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f525a */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f5230 */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f528a */
  /* relift: test byte ptr [esi + 0x2500], 0x10 -> jne 0x1f5270 */
  /* relift: cmp dword ptr [esi + 0x2100], edi -> jne 0x1f529e */
  /* test esi, 0x100000 -> je 0x1f52f0 */
  /* test esi, 0x1000000 -> je 0x1f5301 */
  /* relift: FUN_001f4be0(0, 0); */
  /* test esi, 0x1000 -> je 0x1f5312 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* test esi, 0x100 -> jne 0x1f5323 */
  /* relift: test byte ptr [ebp + 0x2080], 1 -> je 0x1f532c */
  /* relift: FUN_001f5130(0, 0); */
  /* test esi, 0x10000 -> je 0x1f5349 */
  /* relift: test byte ptr [eax + 0x8100], 1 -> je 0x1f5349 */
  /* test edi, edi -> jne 0x1f52d0 */
  FUN_001d0bb9(64, eax);
  XPhysicalAlloc(ecx, 0, eax, 1028);
  /* test eax, eax -> je 0x1f53c1 */
  /* cmp edi, 0x2000 -> ja 0x1f54c7 */
  XMETAL_StartPush();
  /* test esi, esi -> jne 0x1f5504 */
  CDevice_KickOff();
  /* relift: cmp ebx, dword ptr [esi] -> jne 0x1f5596 */
  /* relift: cmp edi, dword ptr [esi + 4] -> jne 0x1f5596 */
  /* relift: FUN_001ef520(0, 0); */
  /* relift: cmp ebx, dword ptr [esi] -> jne 0x1f5596 */
  /* relift: cmp edi, dword ptr [esi + 4] -> je 0x1f5588 */
  /* cmp edx, edi -> jae 0x1f55c5 */
  /* relift: FUN_001ef520(0, 0); */
  /* cmp eax, ebx -> jb 0x1f55b0 */
  /* cmp ecx, edi -> jb 0x1f55b0 */
  XMETAL_StartPush();
  /* test eax, eax -> je 0x1f56c7 */
  XMETAL_StartPush();
  /* cmp ecx, 0x100 -> jb 0x1f570a */
  /* relift: FUN_001f8127(0, 0, 0, 0); */
  /* relift: FUN_001f82b4(0); */
  /* mem[0xfd001804] = eax */
  /* mem[0xfd600140] = 0 */
  /* mem[0xfd009140] = 0 */
  /* relift: FUN_001f7660(0, 0, 0, 0); */
  /* test edx, edx -> je 0x1f58f4 */
  /* test edx, edx -> je 0x1f591b */
  /* cmp ecx, ebp -> ja 0x1f594e */
  /* cmp ebx, ebp -> jbe 0x1f5962 */
  /* relift: FUN_001f77c7(0, 0); */
  /* relift: FUN_001f78c5(0, 0); */
  /* relift: FUN_001f56e3(0); */
  /* relift: FUN_001f7994(0, 0); */
  /* relift: FUN_001f79ca(0, 0); */
  /* relift: FUN_001f79fa(0, 0); */
  /* relift: FUN_001f7ddc(0, 0); */
  /* relift: cmp word ptr [ebp - 0x18], 0x7c6 -> jle 0x1f5a2c */
  /* test (char)ecx, 3 -> jne 0x1f5a64 */
  /* relift: cmp word ptr [ebp - 0x16], 2 -> jle 0x1f5a64 */
  /* relift: FUN_001f8ed2(0, 0); */
  /* relift: FUN_001f8e51(0, 0); */
  /* relift: FUN_001f5b01(level, 0, 0, 0); */
  /* relift: cmp dword ptr [ebp - 4], 2 -> je 0x1f5bdd */
  /* relift: cmp dword ptr [ebp - 4], 3 -> jne 0x1f5bd1 */
  /* relift: cmp dword ptr [ebp - 4], 1 -> jne 0x1f5bdd */
  /* relift: FUN_001f834f(0, 0); */
  /* relift: FUN_001f82ed(0, face); */
  /* relift: FUN_001f5786(0); */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f5cec */
  /* relift: test byte ptr [esi + 0x2400], 0x10 -> je 0x1f5cec */
  /* relift: test byte ptr [esi + 0x3220], 0x10 -> je 0x1f5d18 */
  /* relift: FUN_001f5130(0, 0); */
  /* relift: cmp dword ptr [esi + 0x400100], 0 -> je 0x1f5d03 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f5cd1 */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [eax], 0x10 -> jne 0x1f5d2e */
  /* relift: cmp eax, dword ptr [esp + 4] -> jb 0x1f5d40 */
  /* relift: FUN_001f5850(0, 0); */
  /* test eax, eax -> jne 0x1f5dc3 */
  /* relift: FUN_001f587b(0, 0); */
  /* test eax, eax -> je 0x1f5dbc */
  /* test (char)eax, (char)eax -> jne 0x1f5e01 */
  /* relift: FUN_001f58bc(0, 0); */
  /* test eax, eax -> je 0x1f5dfd */
  /* cmp eax, edx -> jb 0x1f5e3e */
  /* relift: FUN_001f59c6(0, 0); */
  /* relift: FUN_001f5ccb(0, 0, 0, 0); */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [ecx] -> jne 0x1f5f0f */
  /* relift: cmp eax, dword ptr [ecx + 0x400908] -> jne 0x1f5f0f */
  /* test eax, 0xffffc000 -> jne 0x1f5f0f */
  /* relift: test dword ptr [ebp + 0x18], ecx -> je 0x1f6060 */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [esi + edi*4 + 0x400980] -> jne 0x1f5fff */
  /* relift: cmp dword ptr [ebp + 0x20], 0 -> je 0x1f6060 */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [edi] -> jne 0x1f604b */
  /* relift: FUN_001f5ccb(0, 0, 0, 0); */
  /* relift: FUN_001f7a6b(0, 0); */
  /* relift: cmp eax, dword ptr [ecx] -> jne 0x1f60bc */
  /* test eax, eax -> jne 0x1f615a */
  /* relift: FUN_001f6073(0, 0); */
  /* relift: cmp dword ptr [ebp - 4], 8 -> jl 0x1f615d */
  /* relift: test byte ptr [esi + 0x3214], 0x10 -> je 0x1f6193 */
  /* relift: test byte ptr [esi + 0x2400], 0x10 -> je 0x1f6193 */
  /* relift: test byte ptr [esi + 0x3220], 0x10 -> je 0x1f61be */
  /* relift: FUN_001f5130(0, 0); */
  /* relift: cmp dword ptr [esi + 0x400100], ebx -> je 0x1f61a9 */
  /* relift: FUN_001f4fc0(0, 0); */
  /* relift: test dword ptr [esi + 0x100], 0x1000000 -> je 0x1f6178 */
  /* relift: FUN_001f4be0(0, 0); */
  /* relift: test byte ptr [eax], 0x10 -> jne 0x1f61c6 */
  /* relift: FUN_001f7ae3(0); */
  /* relift: cmp dword ptr [edi + 0x108], ebx -> je 0x1f6251 */
  /* relift: cmp dword ptr [ebp - 4], 0x80 -> jb 0x1f622e */
  /* relift: FUN_001f8d2e(0); */
  /* test ebx, ebx -> je 0x1f634f */
  /* test eax, eax -> jne 0x1f636c */
  /* test ecx, ecx -> je 0x1f63bf */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* cmp eax, 0xcafebeef -> jne 0x1f661a */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0); */
  /* test edi, edi -> jne 0x1f6744 */
  /* relift: cmp dword ptr [edi + 0x1fb528], 1 -> je 0x1f6715 */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* relift: FUN_001f6310(0, 0); */
  /* test eax, eax -> je 0x1f68c4 */
  /* relift: cmp dword ptr [eax + 0x1fb498], 0x16 -> je 0x1f68c4 */
  /* cmp edi, ecx -> jne 0x1f6936 */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6440(0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f6310(0, 0, 0, 0); */
  /* relift: FUN_001f64b0(0, 0); */
  /* cmp eax, 1 -> jne 0x1f6ac9 */
  /* test edi, edi -> jne 0x1f6aa1 */
  /* relift: FUN_001f6510(0, 0); */
  /* relift: FUN_001f6570(0, 0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f65d0(0xcafebeef); */
  /* relift: FUN_001f65d0(0); */
  /* relift: FUN_001f66b0(0, 0); */
  /* relift: FUN_001f6770(0, 0); */
  /* relift: FUN_001f67d0(0, 0); */
  /* cmp edi, ecx -> jne 0x1f6a9b */
  /* relift: FUN_001f6820(0, 0, 0, 0); */
  /* test ebx, ebx -> je 0x1f6bcf */
  /* test eax, eax -> jne 0x1f6bec */
  /* test ecx, ecx -> je 0x1f6c50 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* cmp eax, 0xcafebeef -> jne 0x1f6eac */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* test ebx, ebx -> jne 0x1f6fe3 */
  /* relift: cmp dword ptr [0x1fb518], 1 -> je 0x1f6fb2 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* test ecx, ecx -> jne 0x1f7101 */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* relift: FUN_001f6b90(0, 0); */
  /* test eax, eax -> je 0x1f7321 */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6cd0(0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6d40(0, 0); */
  /* relift: FUN_001f6da0(0, 0); */
  /* relift: FUN_001f6e00(0, 0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6e60(0xcafebeef); */
  /* relift: FUN_001f6e60(0); */
  /* relift: FUN_001f6f50(0, 0); */
  /* relift: FUN_001f7010(0); */
  /* relift: FUN_001f7080(0); */
  /* cmp eax, 1 -> jne 0x1f7573 */
  /* cmp edi, ebx -> jne 0x1f754b */
  /* relift: FUN_001f7010(0); */
  /* relift: FUN_001f70f0(0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f6b90(0, 0, 0, 0); */
  /* relift: FUN_001f7180(0, 0); */
  /* relift: FUN_001f71e0(0, 0); */
  /* cmp edi, ebx -> jne 0x1f7541 */
  /* relift: FUN_001f7240(0, 0, 0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* mat4x4_transform_vec4 (0x1ff03f) — readable C lift: D3D row-major vec4*xform. */
float *__stdcall mat4x4_transform_vec4(float *out, float *in, float *matrix)
{
  float x;
  float y;
  float z;
  float w;

  x = in[0];
  y = in[1];
  z = in[2];
  w = in[3];
  out[0] = x * matrix[0] + y * matrix[4] + z * matrix[8] + w * matrix[12];
  out[1] = x * matrix[1] + y * matrix[5] + z * matrix[9] + w * matrix[13];
  out[2] = x * matrix[2] + y * matrix[6] + z * matrix[10] + w * matrix[14];
  out[3] = x * matrix[3] + y * matrix[7] + z * matrix[11] + w * matrix[15];
  return out;
}

/* matrix_build_perspective_projection (0x1ff913) — readable C lift.
 * kb names fov/aspect; XBE treats them as frustum width/height at near plane. */
void __stdcall matrix_build_perspective_projection(void *matrix_out, float fov, float aspect, float z_near, float z_far)
{
  float *m;
  float two_n;
  float q;

  m = (float *)matrix_out;
  two_n = z_near + z_near;
  m[0] = two_n / fov;
  m[1] = 0.0f;
  m[2] = 0.0f;
  m[3] = 0.0f;
  m[4] = 0.0f;
  m[5] = two_n / aspect;
  m[6] = 0.0f;
  m[7] = 0.0f;
  m[8] = 0.0f;
  m[9] = 0.0f;
  q = z_far / (z_far - z_near);
  m[10] = q;
  m[11] = 1.0f;
  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = -(z_near * q);
  m[15] = 0.0f;
}

/* 0x1ffc57 */
void __stdcall matrix_build_ortho_projection(void *matrix_out, float scale_x, float scale_y, float z_near, float z_far)
{
  /* relift: relift: fld dword ptr [0x253f40] */
  /* relift: relift: fld dword ptr [0x253f40] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x253f40] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x253f40] */
  /* relift: relift: fld dword ptr [0x253398] */
  FUN_001d94f0();
}
