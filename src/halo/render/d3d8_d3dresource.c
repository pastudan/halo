/* --- D3D8:d3dresource.obj batch drafts (2026-07-26) --- */

/* 0x1ed7d0 */
void __stdcall D3D_DestroyResource(void *resource)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp esi, 0x50000 -> jne 0x1ed7ec */
  D3D_BlockOnResource();
  /* relift: FUN_001ed4e0(0); */
  /* cmp esi, 0x50000 -> jne 0x1ed81f */
  LocalFree((void *)(uintptr_t)edi);
  /* cmp esi, 0x20000 -> jne 0x1ed841 */
  LocalFree((void *)(uintptr_t)edi);
  /* cmp esi, 0x10000 -> je 0x1ed861 */
  /* cmp esi, 0x60000 -> je 0x1ed861 */
  LocalFree((void *)(uintptr_t)edi);
  /* test eax, 0x780000 -> jne 0x1ed898 */
  /* cmp eax, 0x50000 -> jne 0x1ed8a0 */
  /* test eax, eax -> je 0x1ed8a0 */
  /* relift: test dword ptr [eax], 0x780000 -> je 0x1ed8a0 */
  /* cmp ecx, 0x50000 -> jne 0x1ed8db */
  /* test eax, 0x780000 -> jne 0x1ed8db */
  /* test eax, eax -> je 0x1ed8db */
  /* relift: FUN_001ed8b0(0); */
  /* test eax, 0xffff -> jne 0x1ed917 */
  /* cmp eax, 0x50000 -> jne 0x1ed917 */
  /* test eax, eax -> je 0x1ed917 */
  /* relift: FUN_001ed8f0(0); */
  /* cmp ecx, 1 -> jne 0x1ed972 */
  /* cmp eax, 0x50000 -> jne 0x1ed95d */
  /* test eax, eax -> je 0x1ed95d */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* test eax, 0x780000 -> jne 0x1ed972 */
  /* relift: tail-call D3D_DestroyResource(); */
  /* test edx, edx -> je 0x1ed9b9 */
  /* test eax, 0x780000 -> jne 0x1ed9fb */
  /* test edx, edx -> je 0x1ed9b7 */
  /* relift: test dword ptr [edx], 0x780000 -> jne 0x1ed9fb */
  /* test eax, 0x780000 -> jne 0x1ed9fb */
  /* cmp eax, 0x50000 -> jne 0x1ed9dd */
  /* test eax, eax -> je 0x1ed9dd */
  /* relift: test dword ptr [eax], 0x780000 -> jne 0x1ed9fb */
  /* test edx, edx -> je 0x1eda04 */
  D3DDevice_AddRef();
  /* cmp edx, 0x20000 -> je 0x1eda52 */
  /* relift: FUN_001ed780(0, 0, 0, 0); */
  /* test eax, eax -> je 0x1eda7e */
  /* relift: FUN_001ed630(0, 0); */
  FUN_001d0bb9(64, eax);
  /* test ebx, ebx -> jne 0x1eda9f */
  /* mem[0x001fbb08] = ebx */
  /* relift: FUN_001ed780(0, 0); */
  /* test eax, eax -> jne 0x1edb2b */
  /* test edi, edi -> jne 0x1edb45 */
  /* relift: test byte ptr [eax + 0x1c], 1 -> je 0x1edb77 */
  /* cmp ecx, 0x80000 -> jne 0x1edbf7 */
  /* cmp eax, 0x50000 -> jne 0x1edbe4 */
  /* test eax, eax -> je 0x1edbe4 */
  /* relift: tail-call D3D_DestroyResource(); */
  /* test eax, 0xffff -> jne 0x1edbf7 */
  /* relift: tail-call D3D_DestroyResource(); */
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
  Lock2DSurface((void *)(uintptr_t)ecx, 0, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef2a0(0, 0, 0, 0); */
  /* relift: FUN_001f4270(0, 0, 0, 0); */
  /* relift: FUN_001ef490(0, 0, 0, 0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* relift: test dword ptr [esp + 0x20], 0x10000 -> je 0x1ede24 */
  FUN_001d0bb9(64, 20);
  /* test esi, esi -> je 0x1ede55 */
  /* test eax, eax -> jne 0x1ede60 */
  LocalFree((void *)(uintptr_t)esi);
  /* mem[0x001fe6b0] = eax */
  /* mem[0x001fe6ac] = ecx */
  /* test eax, eax -> jne 0x1eded3 */
  /* mem[0x001fe6b0] = 0x80000 */
  /* test eax, eax -> jne 0x1edee6 */
  /* mem[0x001fe6ac] = 0x8000 */
  /* mem[0x001fe6a0] = 0x1fbb10 */
  /* mem[0x001fe6a4] = 0x1fbb10 */
  /* mem[0x001fbf18] = 1 */
  /* mem[0x001fbb1c] = esi */
  /* relift: FUN_001f3580(0); */
  /* test esi, esi -> jge 0x1edf3f */
  /* relift: FUN_001f3a90(0, 0); */
  /* test eax, eax -> je 0x1edf4d */
  D3DDevice_SetRenderStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetVertexShader(eax);
  D3DDevice_SetPixelShader();
  D3DDevice_SetRenderStateNotInline();
  /* cmp esi, 0x80 -> jb 0x1ee040 */
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp esi, 0x58 -> jb 0x1ee060 */
  D3DDevice_SetPixelShader();
  D3DDevice_SetVertexShader(260);
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)0);
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTextureStageStateNotInline();
  D3DDevice_SetTexture(0, (void *)0);
  /* relift: FUN_001f1b50(0, 0); */
  /* relift: FUN_001ed8f0(0, 0, 0, 0); */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001ed8f0(0); */
  /* cmp eax, 0x80 -> jb 0x1ee180 */
  /* cmp eax, 0x58 -> jb 0x1ee220 */
  /* test eax, eax -> je 0x1ee26d */
  /* cmp eax, 0xe4 -> jb 0x1ee250 */
  D3DDevice_SetRenderTarget((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax);
  D3DResource_Release((void *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1ee2bf */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DDevice_SetTexture(0, (void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1ee2d7 */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DDevice_SetPixelShader();
  D3DDevice_SetVertexShader(edx);
  D3DDevice_SetViewport((void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageStateNotInline();
  /* test ebp, ebp -> jne 0x1ee31d */
  /* relift: cmp dword ptr [edi + 0x1fa270], 0x52 -> jb 0x1ee32c */
  D3DDevice_SetRenderStateNotInline();
  /* cmp edi, 0x80 -> jb 0x1ee310 */
  D3DDevice_SetTextureStageStateNotInline();
  /* cmp edi, 0x58 -> jb 0x1ee340 */
  /* test ebp, ebp -> je 0x1ee39b */
  /* test eax, eax -> je 0x1ee38d */
  D3DDevice_SetRenderStateNotInline();
  /* cmp edi, 0x39 -> jb 0x1ee370 */
  D3DDevice_SetRenderStateNotInline();
  /* relift: FUN_001eb690(0); */
  /* cmp esi, ebp -> jne 0x1ee403 */
  /* cmp eax, ebp -> je 0x1ee43a */
  /* cmp ecx, ebp -> jl 0x1ee41f */
  /* cmp ebx, ecx -> jl 0x1ee428 */
  /* cmp ecx, ebp -> jl 0x1ee431 */
  /* cmp esi, eax -> jl 0x1ee43a */
  /* relift: cmp dword ptr [esp + 0xc], ebx -> jae 0x1ee63e */
  /* cmp ebp, esi -> jae 0x1ee63e */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* cmp eax, 5 -> jne 0x1ee4d7 */
  /* cmp edi, 2 -> jne 0x1ee4ca */
  /* cmp ecx, 2 -> jne 0x1ee4d7 */
  /* relift: relift: fld dword ptr [0x253398] */
  /* test eax, eax -> jge 0x1ee4e9 */
  /* relift: relift: fld dword ptr [0x1fa210] */
  /* relift: relift: fld dword ptr [0x1fa210] */
  /* relift: cmp dword ptr [esi + 0x2b64], 0x80000000 -> je 0x1ee6a5 */
  /* relift: FUN_001ee100(0); */
  /* test (char)eax, 2 -> je 0x1ee6e8 */
  /* mem[0x001fe6a8] = eax */
  /* relift: FUN_001ee030(0, 0, 0, 0); */
  XMETAL_StartPush();
  /* relift: cmp dword ptr [esi + 0x2b64], 0x80000000 -> jne 0x1ee75f */
  /* relift: FUN_001ee3b0(0, 0, 0, 0); */
  /* relift: cmp dword ptr [esi + 0x2b60], 1 -> jne 0x1ee73c */
  /* relift: FUN_001ee3b0(0); */
  /* relift: FUN_001ee3b0(0); */
  /* relift: FUN_001ee290(0); */
  XMETAL_StartPush();
  /* mem[0x001fe6a8] = ecx */
  /* cmp edi, ecx -> jne 0x1ee903 */
  D3D_SetFence();
  /* cmp ecx, 2 -> jb 0x1ee95c */
  /* relift: FUN_001ef520(0, 0); */
  /* cmp eax, 2 -> jae 0x1ee944 */
  /* test (char)eax, 0x30 -> je 0x1ee978 */
  /* relift: FUN_001ee650(0); */
  /* relift: FUN_001ee830(0, 0); */
  CDevice_KickOff();
  /* test eax, eax -> je 0x1eea9a */
  D3D_KickOffAndWaitForIdle();
  /* relift: test dword ptr [esi + 0x2510], 0x1000000 -> je 0x1ee9e0 */
  D3DDevice_BlockUntilVerticalBlank();
  /* test edi, edi -> jne 0x1ee9e2 */
  /* test dl, 1 -> jne 0x1eea54 */
  /* test edi, edi -> je 0x1eea80 */
  /* test eax, eax -> je 0x1eead0 */
  /* relift: FUN_001f489f(0, 0, 0, 0); */
  CMiniport_GetDisplayCapabilities();
  /* cmp edi, 4 -> jne 0x1eeb44 */
  /* test ecx, 0x60000 -> jne 0x1eeb53 */
  /* test ecx, 0x10000 -> je 0x1eeb53 */
  /* test eax, 0x10000 -> je 0x1eeb6c */
  /* test ebx, ecx -> je 0x1eeb6c */
  /* cmp edi, 4 -> jne 0x1eeb68 */
  /* test ebp, ecx -> jne 0x1eeb68 */
  /* test ecx, 0xe0000 -> jne 0x1eeb6c */
  /* cmp ebp, edx -> je 0x1eeb33 */
  /* relift: FUN_001f489f(0); */
  CMiniport_GetDisplayCapabilities();
  /* cmp edi, 4 -> jne 0x1eebf0 */
  /* test ecx, 0x60000 -> jne 0x1eebff */
  /* test ecx, 0x10000 -> je 0x1eebff */
  /* test eax, 0x10000 -> je 0x1eec23 */
  /* test ebx, ecx -> je 0x1eec23 */
  /* cmp edi, 4 -> jne 0x1eec14 */
  /* test ebp, ecx -> jne 0x1eec14 */
  /* test ecx, 0xe0000 -> jne 0x1eec23 */
  /* cmp ebp, edx -> je 0x1eebdf */
  /* relift: FUN_001f4840(0); */
  /* cmp eax, 3 -> ja 0x1eecc5 */
  /* test eax, eax -> je 0x1eed00 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eed0f */
  D3DDevice_GetDeviceCaps((void *)(uintptr_t)eax);
  /* test eax, eax -> je 0x1eed50 */
  /* test ecx, ecx -> jne 0x1eed71 */
  /* relift: FUN_001f4840(0); */
  /* test eax, eax -> je 0x1eedd0 */
  /* cmp ecx, eax -> je 0x1eede5 */
  /* relift: cmp dword ptr [esp + 0x14], eax -> jne 0x1eedf3 */
  /* test eax, eax -> je 0x1eee30 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eee3f */
  /* test (char)ecx, dl -> je 0x1eee91 */
  /* test (char)eax, 2 -> je 0x1eee6c */
  /* relift: test byte ptr [ecx + 0x1f9d58], 0x40 -> jne 0x1eee99 */
  /* test (char)eax, 1 -> je 0x1eee84 */
  /* relift: test byte ptr [edx + 0x1f9d58], (char)ecx -> jne 0x1eee99 */
  /* relift: test byte ptr [eax + 0x1f9d58], 0x3c -> jne 0x1eee99 */
  /* test eax, eax -> jne 0x1eeeec */
  /* cmp eax, edx -> je 0x1eeebd */
  /* relift: cmp dword ptr [esp + 0x10], edx -> je 0x1eef11 */
  /* cmp ecx, 0x11 -> je 0x1eef19 */
  /* test ecx, ecx -> je 0x1eef19 */
  /* cmp eax, 0x40000 -> jbe 0x1eeef4 */
  /* cmp eax, edx -> jb 0x1eef11 */
  /* cmp ecx, edx -> jb 0x1eef11 */
  /* cmp eax, 3 -> ja 0x1eef11 */
  /* cmp ecx, 3 -> jbe 0x1eef19 */
  /* test eax, eax -> je 0x1eef30 */
  /* relift: cmp dword ptr [esp + 8], 1 -> je 0x1eef3f */
  FUN_001d0bb9(0, eax);
  /* test eax, eax -> jne 0x1eef9b */
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
  FUN_001d0bb9(64, 12);
  /* test esi, esi -> je 0x1ef0d3 */
  /* test eax, eax -> jne 0x1ef0dc */
  LocalFree((void *)(uintptr_t)esi);
  XMETAL_StartPush();
  D3D_BlockOnResource();
  /* relift: FUN_001ed7c0(0); */
  D3DResource_GetType();
  FUN_001d0bb9(64, 12);
  /* test edi, edi -> jne 0x1ef189 */
  /* test eax, eax -> jne 0x1ef1be */
  LocalFree((void *)(uintptr_t)edi);
  Get2DSurfaceDesc((void *)(uintptr_t)ecx, 0, (void *)(uintptr_t)eax);
  Lock2DSurface((void *)(uintptr_t)eax, 0, 0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* relift: FUN_001f4200(0, 0, 0); */
  Lock3DSurface();
  FUN_001d0bb9(64, 24);
  /* test esi, esi -> jne 0x1ef2b9 */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  FUN_001d0bb9(64, 24);
  /* test esi, esi -> je 0x1ef38f */
  /* test eax, eax -> jne 0x1ef399 */
  LocalFree((void *)(uintptr_t)esi);
  /* relift: FUN_001f4630(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x1ef41e */
  /* relift: FUN_001ed8f0(0); */
  FUN_001d0bb9(64, 24);
  /* cmp esi, ecx -> jne 0x1ef4ab */
  /* relift: FUN_001ed8f0(0); */
  /* relift: FUN_001ed8f0(0); */
  /* mem[0x001fe6ac] = eax */
  /* cmp eax, edx -> jb 0x1ef75a */
  /* relift: cmp eax, dword ptr [ecx + 0x14] -> jb 0x1ef76e */
  /* cmp eax, esi -> jb 0x1ef78b */
  /* relift: cmp eax, dword ptr [ecx + 0x14] -> jb 0x1ef79f */
  /* cmp esi, 0x80 -> ja 0x1ef80c */
  /* cmp ebx, esi -> jbe 0x1ef836 */
  /* cmp ebx, esi -> ja 0x1ef836 */
  /* relift: test dword ptr [eax + 0x100410], 0x10000 -> jne 0x1ef880 */
  XMETAL_StartPush();
  /* relift: test byte ptr [ecx + 0xc], 4 -> je 0x1ef94c */
  /* relift: test dword ptr [eax + 0x100410], 0x10000 -> jne 0x1ef970 */
  XMETAL_StartPush();
  /* test (char)ebx, 2 -> jne 0x1efa6d */
  CDevice_KickOff();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
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
  D3D_SetFence();
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
  D3D_SetFence();
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
