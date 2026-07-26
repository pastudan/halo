/*
 * rasterizer_xbox_dynavobgeom.c
 *
 * Dynamic visible-object geometry rasterizer (Xbox D3D8 path).
 * Source path (from binary):
 * c:\halo\SOURCE\rasterizer\xbox\rasterizer_xbox_dynavobgeom.c
 */

/* --- rasterizer_xbox_dynavobgeom.obj batch drafts (2026-07-26) --- */

/* 0x15dc10 */
void FUN_0015dc10(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a0110, 823, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x15de4e */
  /* cmp edi, -1 -> je 0x15de36 */
  /* test ebx, ebx -> je 0x15de36 */
  /* test eax, eax -> je 0x15de36 */
  /* test eax, eax -> jne 0x15dcab */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 834, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15dccf */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 837, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [0x47dbe0] -> jl 0x15dcf7 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 838, 0);
  system_exit(0);
  FUN_00180050(0);
  /* test eax, eax -> jge 0x15dd38 */
  display_assert((char *)0x002a0784, (char *)0x002a0110, 845, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15dd5c */
  display_assert((char *)0x002a0770, (char *)0x002a0110, 846, 0);
  system_exit(0);
  /* cmp esi, ecx -> jle 0x15dd86 */
  display_assert((char *)0x002a0720, (char *)0x002a0110, 847, 0);
  system_exit(0);
  /* cmp esi, 0x2710 -> jle 0x15dd93 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)eax, edx);
  /* test (char)eax, (char)eax -> je 0x15ddad */
  FUN_00167ff0(0, (char *)0x002a09a8);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15ddd4 */
  FUN_00167ff0(0, (char *)0x002a0950);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15de0b */
  FUN_00167ff0(0, (char *)0x002a0868);
  error(0, (char *)0x002a0820);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x15de60 */
void FUN_0015de60(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a0110, 890, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x15e0e2 */
  /* cmp edi, -1 -> je 0x15e0c9 */
  /* test ebx, ebx -> je 0x15e0c9 */
  /* test eax, eax -> je 0x15e0c9 */
  /* test esi, esi -> je 0x15e0c9 */
  /* test eax, eax -> je 0x15e0c9 */
  /* test eax, eax -> jne 0x15df02 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 903, 0);
  system_exit(0);
  /* test edi, edi -> jge 0x15df26 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 906, 0);
  system_exit(0);
  /* relift: cmp edi, dword ptr [0x47dbe0] -> jl 0x15df4e */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 907, 0);
  system_exit(0);
  FUN_00180050(0);
  FUN_00180050(0);
  /* test eax, eax -> jge 0x15df9c */
  display_assert((char *)0x002a0784, (char *)0x002a0110, 915, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15dfc3 */
  display_assert((char *)0x002a0770, (char *)0x002a0110, 916, 0);
  system_exit(0);
  /* cmp esi, edx -> jle 0x15dfed */
  display_assert((char *)0x002a0720, (char *)0x002a0110, 917, 0);
  system_exit(0);
  /* cmp esi, 0x2710 -> jle 0x15dffa */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, ebx);
  /* test (char)eax, (char)eax -> je 0x15e014 */
  FUN_00167ff0(0, (char *)0x002a0bd8);
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, edx);
  /* test (char)ebx, (char)ebx -> je 0x15e03f */
  FUN_00167ff0(0, (char *)0x002a0b58);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e066 */
  FUN_00167ff0(0, (char *)0x002a0950);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e09e */
  FUN_00167ff0(0, (char *)0x002a0a70);
  error(0, (char *)0x002a0a28);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x15e0f0 */
void FUN_0015e0f0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a0110, 963, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x15e42c */
  /* test eax, eax -> je 0x15e413 */
  /* test ecx, ecx -> je 0x15e413 */
  /* cmp esi, -1 -> je 0x15e413 */
  /* test eax, eax -> jne 0x15e18b */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 977, 0);
  system_exit(0);
  /* test esi, esi -> jge 0x15e1af */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 980, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15e1d7 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 981, 0);
  system_exit(0);
  FUN_00180050(0);
  /* test edi, edi -> jne 0x15e222 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp edi, 0x476b60 -> jne 0x15e23e */
  /* test ebx, ebx -> jne 0x15e265 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 991, 0);
  system_exit(0);
  /* test eax, eax -> jge 0x15e28c */
  display_assert((char *)0x002a04a0, (char *)0x002a0110, 994, 0);
  system_exit(0);
  /* cmp eax, ecx -> jle 0x15e2ba */
  display_assert((char *)0x002a0438, (char *)0x002a0110, 995, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15e2e1 */
  display_assert((char *)0x002a0e84, (char *)0x002a0110, 998, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15e2f2 */
  /* cmp (int16_t)eax, 2 -> jl 0x15e312 */
  display_assert((char *)0x002a0e30, (char *)0x002a0110, 999, 0);
  system_exit(0);
  /* cmp edi, 0x2710 -> jle 0x15e322 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ebx, eax);
  /* test (char)eax, (char)eax -> je 0x15e339 */
  FUN_00167ff0(0, (char *)0x002a03e0);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e362 */
  FUN_00167ff0(0, (char *)0x002a0d98);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e3af */
  FUN_00167ff0(0, (char *)0x002a0cc8);
  display_assert((char *)0x002a0c9c, (char *)0x002a0110, 1030, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15e140 */
  error(0, (char *)0x002a0c58);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x15e430 */
void FUN_0015e430(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a0110, 1063, 0);
  system_exit(0);
  /* test esi, esi -> jle 0x15e643 */
  /* test edi, edi -> je 0x15e62b */
  /* test eax, eax -> je 0x15e62b */
  /* test ebx, ebx -> je 0x15e62b */
  /* test eax, eax -> je 0x15e62b */
  /* test eax, eax -> jne 0x15e4d2 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 1073, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15e4f9 */
  display_assert((char *)0x002a0e84, (char *)0x002a0110, 1078, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15e507 */
  /* cmp (int16_t)eax, 2 -> jl 0x15e527 */
  display_assert((char *)0x002a0e30, (char *)0x002a0110, 1079, 0);
  system_exit(0);
  FUN_00180050(0);
  /* cmp esi, 0x2710 -> jle 0x15e542 */
  D3DDevice_SetStreamSource(0, (void *)(uintptr_t)ecx, eax);
  /* test (char)eax, (char)eax -> je 0x15e559 */
  FUN_00167ff0(0, (char *)0x002a09a8);
  D3DDevice_SetIndices();
  /* test (char)ebx, (char)ebx -> je 0x15e57d */
  FUN_00167ff0(0, (char *)0x002a0fa8);
  D3DDevice_DrawIndexedVertices();
  /* test (char)ebx, (char)ebx -> je 0x15e5c7 */
  FUN_00167ff0(0, (char *)0x002a0ee8);
  display_assert((char *)0x002a0c9c, (char *)0x002a0110, 1113, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15e47d */
  error(0, (char *)0x002a0ea0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x15e650 */
void FUN_0015e650(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, -1 -> jne 0x15e69d */
  /* cmp eax, -1 -> je 0x15e69d */
  display_assert((char *)0x002a107c, (char *)0x002a0110, 1146, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x15e6e4 */
  /* cmp edi, -1 -> je 0x15e6e4 */
  display_assert((char *)0x002a1014, (char *)0x002a0110, 1150, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x15e71a */
  /* test esi, esi -> je 0x15e703 */
  FUN_0015e430();
  FUN_0015e0f0();
  FUN_0015dc10();
  FUN_0015d8b0();
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x15e770 */
void FUN_0015e770(void)
{
  D3DVertexBuffer_Lock();
}

/* 0x15e7a0 */
void FUN_0015e7a0(void)
{
  int eax = 0;

  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x15e7d0 */
void FUN_0015e7d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x15e800 */
void FUN_0015e800(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x15e82c */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 93, 0);
  system_exit(0);
  D3DDevice_CreateIndexBuffer();
  /* test eax, eax -> jl 0x15e84f */
  FUN_00167ff0(0, (char *)0x002a1370);
  /* test eax, eax -> jne 0x15e86c */
  /* test (char)ebx, (char)ebx -> jne 0x15e889 */
  /* mem[0x0047dbe8] = 0 */
  error(0, (char *)0x002a1338);
  /* cmp (int16_t)ecx, 0xc -> jge 0x15e950 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)(uintptr_t)edi);
  /* test (char)ebx, (char)ebx -> je 0x15e904 */
  /* test eax, eax -> jl 0x15e904 */
  FUN_00167ff0(0, (char *)0x002a1268);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x15e91d */
  /* test (char)ebx, (char)ebx -> jne 0x15e936 */
  error(0, (char *)0x002a1230);
  /* test (char)ebx, (char)ebx -> je 0x15e9a8 */
  FUN_00180050(0);
  D3DDevice_CreateVertexBuffer(eax, 520, 0, 0, (void *)0);
  /* test eax, eax -> jl 0x15e97d */
  FUN_00167ff0(0, (char *)0x002a1128);
  /* test eax, eax -> jne 0x15e99a */
  /* test (char)ebx, (char)ebx -> jne 0x15e9b7 */
  /* mem[0x0047dbf0] = 0 */
  error(0, (char *)0x002a10ec);
  /* relift: FUN_e912e9e3(0, 0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x15e9e0 */
void FUN_0015e9e0(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x15ea09 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 263, 0);
  system_exit(0);
  /* test eax, eax -> je 0x15ea27 */
  D3DResource_Release((void *)(uintptr_t)eax);
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x0047dbf0] = 0 */
  /* test eax, eax -> je 0x15ea61 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x0047dbe8] = 0 */

  (void)eax;
}

/* 0x15ea70 */
void *FUN_0015ea70(int dynamic_triangle_buffer_index)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x15eaa0 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 331, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15eb78 */
  /* test esi, esi -> jge 0x15ead0 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 337, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47dbe0] -> jl 0x15eaf8 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 338, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15eb21 */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 340, 0);
  system_exit(0);
  display_assert((char *)0x002a14a4, (char *)0x002a0110, 344, 0);
  system_exit(0);
  /* relift: relift: mov byte ptr [0x47dbec], 0 */
  error(0, (char *)0x002a1468);
  return NULL;

  (void)eax;
  (void)esi;
}

/* 0x15eb90 */
void FUN_0015eb90(void)
{
  int eax = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x15ebbc */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 373, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15ec3d */
  /* test esi, esi -> jge 0x15ebe9 */
  display_assert((char *)0x002a07f8, (char *)0x002a0110, 377, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47dbe0] -> jl 0x15ec11 */
  display_assert((char *)0x002a07b8, (char *)0x002a0110, 378, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ec4c */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 380, 0);
  system_exit(0);
  error(0, (char *)0x002a14d0);

  (void)eax;
  (void)esi;
}

/* 0x15ec50 */
int FUN_0015ec50(int dynamic_vertex_buffer_index)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x15ec81 */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 519, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x325652], 0 -> jne 0x15ec9a */
  error(0, (char *)0x002a15d8);
  /* cmp esi, -1 -> je 0x15ee64 */
  /* test esi, esi -> jge 0x15ecca */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 535, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ecf2 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 536, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ed1b */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 539, 0);
  system_exit(0);
  FUN_00180050(0);
  display_assert((char *)0x002a15b4, (char *)0x002a0110, 544, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0xc -> jl 0x15ed81 */
  display_assert((char *)0x002a1574, (char *)0x002a0110, 545, 0);
  system_exit(0);
  /* test eax, eax -> jg 0x15eda8 */
  display_assert((char *)0x002a154c, (char *)0x002a0110, 546, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x15edda */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp ebx, 0x476b60 -> jne 0x15edfb */
  /* test eax, eax -> jne 0x15ee28 */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 551, 0);
  system_exit(0);
  D3DVertexBuffer_Lock();
  error(0, (char *)0x002a1510);
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x15ee80 */
void FUN_0015ee80(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x15eeac */
  display_assert((char *)0x0029dc40, (char *)0x002a0110, 582, 0);
  system_exit(0);
  /* cmp esi, -1 -> je 0x15efde */
  /* test esi, esi -> jge 0x15eedd */
  display_assert((char *)0x002a02d4, (char *)0x002a0110, 588, 0);
  system_exit(0);
  /* relift: cmp esi, dword ptr [0x47abd8] -> jl 0x15ef05 */
  display_assert((char *)0x002a0298, (char *)0x002a0110, 589, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ef2e */
  display_assert((char *)0x002a0194, (char *)0x002a0110, 591, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x15ef45 */
  /* cmp (int16_t)eax, 0xc -> jl 0x15ef65 */
  display_assert((char *)0x002a1668, (char *)0x002a0110, 595, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x15ef96 */
  display_assert((char *)0x0026276c, (char *)0x002a0110, 504, 0);
  system_exit(0);
  /* cmp esi, 0x476b60 -> jne 0x15efb4 */
  /* test esi, esi -> jne 0x15efed */
  display_assert((char *)0x002a04d0, (char *)0x002a0110, 600, 0);
  system_exit(0);
  error(0, (char *)0x002a1628);
  /* cmp esi, 0x52 -> jge 0x15f00b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15f019 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15f02e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15f03a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15f046 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15f052 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15f05e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15f06a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15f076 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15f082 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15f08e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15f09a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15f0a6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15f0b5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15f0c4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15f0d3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15f0e2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15f0f1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15f100 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15f10f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15f11e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15f12d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15f13c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15f14b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15f15a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15f169 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15f178 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15f187 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15f195 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x15f1ac */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15f1b9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15f1c6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15f1d3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15f1e0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x15f1f0 */
void FUN_0015f1f0(void)
{
  FUN_0016f910(27);
}

/* 0x15f200 */
void FUN_0015f200(void)
{
  FUN_0016fa40(27);
}

/* 0x15f220 */
void FUN_0015f220(void)
{
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a16bc, (char *)0x002a16c4, 220, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x15f273 */
  display_assert((char *)0x002a16ac, (char *)0x002a16c4, 221, 0);
  system_exit(0);
  /* cmp esi, 0x52 -> jge 0x15f33f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x15f352 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x15f36f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x15f37f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x15f38f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x15f39f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x15f3af */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x15f3bf */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x15f3cf */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x15f3df */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x15f3ef */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x15f3ff */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x15f40f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x15f422 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x15f435 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x15f448 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x15f45b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x15f46e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x15f481 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x15f494 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x15f4a7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x15f4ba */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x15f4cd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x15f4e0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x15f4f3 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x15f506 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x15f519 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x15f52c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x15f53a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();

  (void)esi;
  (void)edi;
}

/* 0x15f540 */
void FUN_0015f540(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  display_assert((char *)0x002a1704, (char *)0x002a16c4, 255, 0);
  system_exit(0);
  /* cmp edx, 0x16 -> jge 0x15f580 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x15f591 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x15f5a2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x15f5b3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x15f5c0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x15f5e0 */
void FUN_0015f5e0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexDataColor(ecx, eax);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x15f630 */
void FUN_0015f630(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ebx -> jne 0x15f65f */
  display_assert((char *)0x0029dc40, (char *)0x002a16c4, 38, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x3256d8], (char)ebx -> je 0x15f89b */
  /* relift: test byte ptr [ebp + 0x24], 0x20 -> je 0x15f698 */
  /* relift: cmp word ptr [eax + 0x24], 1 -> je 0x15f698 */
  display_assert((char *)0x002a17a8, (char *)0x002a16c4, 42, 0);
  system_exit(0);
  /* relift: cmp word ptr [ecx + 0x24], 1 -> je 0x15f6bf */
  display_assert((char *)0x002a1780, (char *)0x002a16c4, 44, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x15f6e5 */
  display_assert((char *)0x002a1774, (char *)0x002a16c4, 52, 0);
  system_exit(0);
  rasterizer_transparent_geometry_group_new();
  /* cmp esi, ebx -> je 0x15f87b */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: cmp word ptr [eax + 0x24], 1 -> jne 0x15f814 */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* test (char)ecx, 1 -> je 0x15f817 */
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x15f899 */
  /* mem[0x005a5504] = esi */
  /* mem[0x005a5508] = edx */
  /* mem[0x005a550c] = eax */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5510] = ecx */
  /* relift: cmp byte ptr [0x47dbf6], (char)ebx -> jne 0x15f899 */
  error(0, (char *)0x002a1744);
  /* relift: relift: mov byte ptr [0x47dbf6], 1 */
  D3DDevice_SetVertexDataColor(0, eax);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x15f8e0 */
void FUN_0015f8e0(void *parameters, void *vertices)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ebx -> jne 0x15f915 */
  display_assert((char *)0x0029dc40, (char *)0x002a16c4, 756, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256da] */
  /* test (char)eax, (char)eax -> je 0x160433 */
  /* relift: cmp word ptr [0x5a5bc0], (int16_t)ebx -> jne 0x160433 */
  display_assert((char *)0x0029f510, (char *)0x002a16c4, 761, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0xc], ebx -> jne 0x15f97d */
  display_assert((char *)0x002a18a4, (char *)0x002a16c4, 763, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x14], ebx -> je 0x15f9a7 */
  /* relift: cmp dword ptr [esi + 0x10], ebx -> jne 0x15f9ac */
  display_assert((char *)0x002a1878, (char *)0x002a16c4, 765, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x10], ebx -> je 0x15f9d0 */
  /* relift: cmp dword ptr [esi], ebx -> je 0x15f9d0 */
  display_assert((char *)0x002a1840, (char *)0x002a16c4, 767, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_001580b0(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* cmp edx, ebx -> je 0x15fa6f */
  /* cmp edx, ebx -> je 0x15fa91 */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  /* cmp eax, ebx -> je 0x15fc19 */
  /* cmp eax, ebx -> je 0x15fc32 */
  /* cmp eax, ebx -> je 0x15fc4d */
  /* cmp eax, ebx -> je 0x15fc63 */
  /* cmp eax, ebx -> je 0x15fc78 */
  /* cmp eax, ebx -> je 0x15fc8b */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x15fd8e */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jl 0x15fce1 */
  FUN_00178b40(0, 0, 0);
  /* test edi, edi -> je 0x15ffc7 */
  /* test (char)eax, (char)eax -> jne 0x15fdd0 */
  display_assert((char *)0x002a182c, (char *)0x002a16c4, 886, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [edi + 0x18], 0x3f800000 -> je 0x15fdf8 */
  display_assert((char *)0x002a1814, (char *)0x002a16c4, 887, ebx);
  system_exit(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x8001 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ebx */
  /* mem[0x005a5b94] = 0x11104 */
  /* mem[0x005a5ae8] = ecx */
  /* test (char)eax, 0x41 -> je 0x15fec2 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00159070(0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x12081208 */
  /* mem[0x005a5b48] = 0x1120e820 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b0c] = ecx */
  /* mem[0x005a5ac4] = 0x6c200000 */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5b4c] = 0x3c011c02 */
  /* mem[0x005a5b78] = edx */
  /* mem[0x005a5af0] = eax */
  /* mem[0x005a5b10] = ecx */
  /* mem[0x005a5ac8] = 0x820b220 */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5af4] = ecx */
  /* mem[0x005a5b14] = edx */
  /* mem[0x005a5acc] = 0x12201120 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0xc200120 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ae0] = 0xc180000 */
  /* test eax, eax -> je 0x1603ae */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* test ecx, ecx -> jne 0x160022 */
  /* test ecx, ecx -> jne 0x16003c */
  /* test eax, eax -> je 0x16008a */
  /* test eax, eax -> je 0x1600a2 */
  FUN_000d1c90((float *)(uintptr_t)eax);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1c90((float *)(uintptr_t)ecx);
  /* mem[0x005a5b08] = eax */
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* mem[0x005a5aec] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5af8] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5afc] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b00] = eax */
  FUN_000d1c90((float *)(uintptr_t)edi);
  /* mem[0x005a5b04] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x8010902 */
  /* mem[0x005a5ac0] = 0x18111912 */
  /* mem[0x005a5b4c] = 0xa010804 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ac4] = 0x1a111814 */
  /* mem[0x005a5b2c] = eax */
  /* cmp eax, 5 -> ja 0x160287 */
  /* mem[0x005a5b50] = 0xc200920 */
  /* mem[0x005a5ac8] = 0x1c201920 */
  /* mem[0x005a5b7c] = edi */
  /* mem[0x005a5b50] = 0xc20e920 */
  /* mem[0x005a5ac8] = 0x1c20f920 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5b7c] = ebx */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = ebx */
  /* mem[0x005a5b7c] = 0x20c0 */
  /* mem[0x005a5b50] = 0xc090000 */
  /* mem[0x005a5ac8] = 0x1c190000 */
  /* mem[0x005a5b30] = edi */
  /* mem[0x005a5ac8] = 0x820a920 */
  /* mem[0x005a5b50] = 0x1920b820 */
  /* mem[0x005a5acc] = 0x1c1c0c0c */
  /* mem[0x005a5b34] = 0x24c00 */
  /* mem[0x005a5b54] = eax */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5ad0] = 0x5c5c */
  /* mem[0x005a5b38] = 0x4d00 */
  /* mem[0x005a5b58] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5ad4] = eax */
  /* mem[0x005a5b3c] = edx */
  /* mem[0x005a5b5c] = 0x1ca01da0 */
  /* mem[0x005a5b88] = edx */
  /* mem[0x005a5b30] = edx */
  /* mem[0x005a5b7c] = edx */
  /* test eax, eax -> je 0x16038d */
  /* cmp eax, 4 -> ja 0x16038c */
  /* relift: cmp word ptr [esi + 0x84], 5 -> jne 0x1602d5 */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_CullMode(2305);
  FUN_00178b40(0, 0, 0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, ecx);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x16048b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x160499 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1604ae */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1604ba */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1604c6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1604d2 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1604de */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1604ea */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1604f6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x160502 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16050e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16051a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x160526 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x160535 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x160544 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160553 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x160562 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x160571 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x160580 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16058f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16059e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1605ad */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1605bc */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1605cb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1605da */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1605e9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1605f8 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x160607 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x160615 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16062c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x160639 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x160646 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x160653 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x160660 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, 0x52 -> jge 0x16068f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1606a2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1606bf */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1606cf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1606df */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1606ef */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1606ff */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16070f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16071f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16072f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16073f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16074f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16075f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x160772 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x160785 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x160798 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1607ab */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1607be */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1607d1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1607e4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1607f7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16080a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16081d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x160830 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x160843 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x160856 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x160869 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16087c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16088a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  D3DDevice_SetTexture(ecx, (void *)(uintptr_t)eax);
  /* cmp edx, 0x16 -> jge 0x1608b0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1608c1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1608d2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1608e3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1608f0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x160920 */
void FUN_00160920(void)
{
  FUN_0016fa40(0);
}

/* 0x160930 */
void FUN_00160930(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x160940 */
void _rasterizer_hud_begin(void)
{
  FUN_0016fa40(0);
}

/* 0x160950 */
void FUN_00160950(void)
{
  FUN_00158ae0(0);
  FUN_0016fa40(0);
}

/* 0x160970 */
void _rasterizer_hud_end(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x160980 */
void FUN_00160980(void)
{
  FUN_0016fa40(11);
}

/* 0x1609a0 */
void _rasterizer_dynamic_lit_geometry_draw(void)
{
  FUN_0016fa40(12);
}

/* 0x1609b0 */
void FUN_001609b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d0] */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dca4] */
  /* test (char)eax, (char)eax -> jne 0x160ba4 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2173, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x160a83 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x160ba1 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  FUN_00178b40(58, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  FUN_00159070(0.0f);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6e0] = esi */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x160ba1 */
  /* mem[0x005a548c] = eax */
  /* mem[0x005a5488] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5484] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x160bc0 */
void FUN_00160bc0(void)
{
  FUN_0016fa40(13);
}

/* 0x160bd0 */
void FUN_00160bd0(void)
{
  FUN_0016f910(14);
}

/* 0x160be0 */
void FUN_00160be0(void)
{
  FUN_0016fa40(14);
}

/* 0x160bf0 */
void FUN_00160bf0(void)
{
  FUN_0016f910(15);
}

/* 0x160c00 */
void FUN_00160c00(void)
{
  FUN_0016fa40(15);
}

/* 0x160c10 */
void FUN_00160c10(void)
{
  FUN_0016f910(16);
}

/* 0x160c20 */
void FUN_00160c20(void)
{
  FUN_001749b0();
  FUN_0016fa40(16);
}

/* 0x160c30 */
void FUN_00160c30(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */
  /* cmp (int16_t)eax, 2 -> je 0x160c99 */
  /* cmp (int16_t)eax, 6 -> je 0x160c99 */
  /* cmp (int16_t)eax, 3 -> je 0x160c99 */
  /* cmp (int16_t)eax, 4 -> je 0x160c99 */
  /* cmp (int16_t)eax, 7 -> je 0x160c99 */
  /* cmp (int16_t)eax, 5 -> je 0x160c99 */
  /* cmp (int16_t)eax, 8 -> jne 0x160db3 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256c9] */
  /* test (char)eax, (char)eax -> je 0x160db3 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1010101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 1 */
  D3DDevice_SetRenderState_ZBias(0);

  (void)eax;
}

/* 0x160dc0 */
void FUN_00160dc0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x160dea */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 68, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160e23 */
  /* cmp (int16_t)eax, 2 -> je 0x160e23 */
  /* cmp (int16_t)eax, 6 -> je 0x160e23 */
  /* cmp (int16_t)eax, 3 -> je 0x160e23 */
  /* cmp (int16_t)eax, 4 -> je 0x160e23 */
  /* cmp (int16_t)eax, 7 -> je 0x160e23 */
  /* cmp (int16_t)eax, 5 -> je 0x160e23 */
  /* cmp (int16_t)eax, 8 -> jne 0x160f3d */
  /* relift: relift: mov (char)eax, byte ptr [0x3256c9] */
  /* test (char)eax, (char)eax -> je 0x160f3d */
  /* test esi, esi -> je 0x160ecb */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)esi);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: relift: mov (char)ecx, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* relift: relift: mov dl, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(edx, 0, 0);
  /* relift: relift: mov byte ptr [0x47dca4], 0 */
  D3DDevice_SetTexture(0, (void *)0);
  /* relift: relift: mov byte ptr [0x47dca4], 1 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256b0] */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x160f3c */
  /* cmp (int16_t)eax, 2 -> jne 0x160f09 */
  /* relift: relift: fld dword ptr [0x3256e4] */
  /* relift: relift: fstp dword ptr [0x47dc98] */
  random_math_real((void *)(uintptr_t)eax);
  /* relift: relift: fstp dword ptr [0x47dc98] */
  random_math_real((void *)(uintptr_t)ecx);
  /* relift: relift: fstp dword ptr [0x47dc9c] */
  random_math_real((void *)(uintptr_t)edx);
  /* relift: relift: fstp dword ptr [0x47dca0] */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x160f50 */
void FUN_00160f50(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 135, ebx);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* cmp (int16_t)eax, 9 -> jne 0x161693 */
  /* relift: cmp word ptr [eax], (int16_t)ebx -> jne 0x161ecc */
  /* cmp (int16_t)edx, 0x33 -> jge 0x161ecc */
  /* cmp eax, esi -> je 0x1612f8 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(edi);
  FUN_00178b40(37, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = edx */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* mem[0x005a5b94] = 3 */
  /* mem[0x005a5ae8] = 0xff0000 */
  /* mem[0x005a5b08] = 0xff */
  /* mem[0x005a5b48] = 0x4849484a */
  /* mem[0x005a5b74] = 0x30cd */
  /* mem[0x005a5b4c] = 0xc0c0d0d */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b50] = 0xc010d02 */
  /* mem[0x005a5b7c] = 0xc00 */
  /* mem[0x005a5ae0] = eax */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ae0] = edx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (char)ecx, byte ptr [0x47dca4] */
  FUN_0015de60();
  /* cmp (int16_t)eax, (int16_t)edi -> je 0x1616c6 */
  /* cmp (int16_t)eax, 2 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 6 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 3 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 4 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 7 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 5 -> je 0x1616c6 */
  /* cmp (int16_t)eax, 8 -> jne 0x161ecc */
  /* relift: relift: mov (char)eax, byte ptr [0x3256c9] */
  /* test (char)eax, (char)eax -> je 0x161ecc */
  /* relift: cmp dword ptr [ebp + 8], edi -> jne 0x1616f6 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 347, ebx);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0x1c], edi -> jne 0x161719 */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 348, ebx);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edx, 0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)eax);
  FUN_00178b40(16, 0, 0);
  /* test (char)ebx, (char)eax -> je 0x161756 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256f4] */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = eax */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [edi + 0x180], (char)ebx -> je 0x161850 */
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 13, 0);
  SetTextureStageStateSmart(0, 14, 0);
  SetTextureStageStateSmart(0, 15, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* relift: cmp dword ptr [edi + 0x260], esi -> jne 0x161989 */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: mov (char)ecx, byte ptr [0x47dca4] */
  /* relift: relift: mov (char)ecx, byte ptr [0x3256ec] */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5b74] = 0x208c */
  /* mem[0x005a5ac4] = 0x34201408 */
  /* mem[0x005a5b2c] = 0xc00 */
  /* mem[0x005a5ae0] = 0xa0f000c */
  /* mem[0x005a5ae4] = 0x1c011800 */
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b48] = ecx */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a199c, (char *)0x002a18c0, 448, ebx);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a196c, (char *)0x002a18c0, 449, ebx);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a1940, (char *)0x002a18c0, 450, ebx);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(edx, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(eax, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(ecx, 0.0f);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00012fb0((float *)(uintptr_t)eax, 0.0f, (float *)0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00012fb0((float *)(uintptr_t)edx, 0.0f, (float *)0);
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)0);
  vector3d_scale_add((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)0);
  FUN_00012fb0((float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)eax);
  FUN_00012fb0((float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)edx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: mov dl, byte ptr [0x47dca4] */
  /* relift: relift: mov dl, byte ptr [0x3256ec] */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5b88] = eax */
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b94] = 0x11106 */
  /* mem[0x005a5ac0] = 0x1120b920 */
  /* mem[0x005a5b48] = 0x1920b120 */
  /* mem[0x005a5ac4] = 0xdcdccccc */
  /* mem[0x005a5b2c] = 0x24c00 */
  /* mem[0x005a5b4c] = edx */
  /* mem[0x005a5b78] = 0x2080 */
  /* mem[0x005a5af0] = 0xff0000 */
  /* mem[0x005a5b10] = 0xff00 */
  /* mem[0x005a5ac8] = 0x1c1c0920 */
  /* mem[0x005a5b30] = 0xc9 */
  /* mem[0x005a5b50] = 0x9010902 */
  /* mem[0x005a5b7c] = 0x30cd */
  /* mem[0x005a5acc] = 0x5c5c */
  /* mem[0x005a5b34] = 0x4c00 */
  /* mem[0x005a5b54] = 0xc010d02 */
  /* mem[0x005a5b80] = 0xd00 */
  /* mem[0x005a5ad0] = 0x34201408 */
  /* mem[0x005a5b58] = 0x11c0220 */
  /* mem[0x005a5b5c] = 0xc190d20 */
  /* mem[0x005a5ae0] = 0xa0f000c */
  /* mem[0x005a5ae4] = 0x1c011800 */
  FUN_00159070(0.0f);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5af4] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5b14] = eax */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5af8] = eax */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5b18] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edi);
  /* mem[0x005a5b6c] = eax */
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256b0] */
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x161d7b */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  /* mem[0x005a5ae0] = 0x2004000c */
  /* cmp (int16_t)eax, 2 -> je 0x161d87 */
  /* cmp (int16_t)eax, 3 -> jne 0x161da3 */
  FUN_000d1dd0((void *)0x0047dc98);
  /* mem[0x005a5b70] = eax */
  /* mem[0x005a5ae0] = 0x2002000c */
  /* cmp eax, 8 -> ja 0x161e3c */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 8 */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = 0x48402020 */
  /* mem[0x005a5b28] = 0x20d00 */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0x1d */
  /* mem[0x005a5b94] = ebx */
  /* mem[0x005a5ac0] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0x20 */
  display_assert((char *)0x002a1900, (char *)0x002a18c0, 575, ebx);
  system_exit(0);
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (char)ebx, byte ptr [0x47dca4] */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x161ecc */
  /* mem[0x005a542c] = eax */
  /* mem[0x005a5428] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5424] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x161f00 */
void FUN_00161f00(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 627, esi);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1621be */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cb] */
  /* test (char)eax, (char)eax -> je 0x1621be */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetTextureStageState(esi, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18861 */
  /* mem[0x005a5b94] = 4 */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20c00 */
  /* mem[0x005a5b48] = 0x90a484b */
  /* mem[0x005a5b74] = ecx */
  /* mem[0x005a5b4c] = 0xc0d0000 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5b50] = 0xc1c0000 */
  /* mem[0x005a5b7c] = eax */
  /* mem[0x005a5b54] = 0xc010c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ae0] = 0xc010000 */
  /* mem[0x005a5ae4] = 0xd00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x1621c0 */
void FUN_001621c0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x1621f2 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 723, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16254e */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cb] */
  /* test (char)eax, (char)eax -> je 0x16254e */
  /* test esi, esi -> jl 0x16221d */
  /* relift: cmp esi, dword ptr [0x5a37e0] -> jl 0x16223d */
  display_assert((char *)0x002a1a58, (char *)0x002a18c0, 729, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x162276 */
  display_assert((char *)0x0029e134, (char *)0x002a18c0, 732, 0);
  system_exit(0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x162327 */
  display_assert((char *)0x002a1a30, (char *)0x002a18c0, 748, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16235c */
  display_assert((char *)0x002a1a04, (char *)0x002a18c0, 749, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x162391 */
  display_assert((char *)0x002a19dc, (char *)0x002a18c0, 750, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(edx, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(eax, 0.0f);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  FUN_0010a5e0(ecx, 0.0f);
  FUN_00109e90((float *)(uintptr_t)edx, 0.0f, 0.0f, 0.0f);
  matrix_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_transform_vector((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  normalize3d((float *)0);
  /* relift: relift: fld dword ptr [0x253398] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  FUN_000d1dd0((float *)(uintptr_t)esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6c0] = esi */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x162560 */
void FUN_00162560(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16258f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 819, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16277d */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cb] */
  /* test (char)eax, (char)eax -> je 0x16277d */
  /* test edi, edi -> jne 0x1625d4 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 826, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 831, 0);
  system_exit(0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)edi);
  FUN_00178b40(49, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  FUN_000d1dd0((float *)(uintptr_t)esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb744] = esi */
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16277a */
  /* mem[0x005a5448] = eax */
  /* mem[0x005a5444] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5440] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x162790 */
void FUN_00162790(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x1627b9 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 921, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1627f6 */
  /* cmp (int16_t)eax, 1 -> je 0x1627f6 */
  /* cmp (int16_t)eax, 3 -> je 0x1627f6 */
  /* cmp (int16_t)eax, 4 -> je 0x1627f6 */
  /* cmp (int16_t)eax, 7 -> je 0x1627f6 */
  /* cmp (int16_t)eax, 5 -> je 0x1627f6 */
  /* cmp (int16_t)eax, 8 -> jne 0x162919 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cc] */
  /* test (char)eax, (char)eax -> je 0x162919 */
  D3DDevice_SetRenderState_CullMode(2305);
  /* relift: relift: mov (char)eax, byte ptr [0x3256f5] */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* relift: relift: mov (int16_t)esi, word ptr [0x3256bc] */
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(edx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00158ae0(0);

  (void)eax;
  (void)edx;
  (void)esi;
}

/* 0x162920 */
void FUN_00162920(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16294f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 968, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x162982 */
  /* cmp (int16_t)eax, 1 -> je 0x162982 */
  /* cmp (int16_t)eax, 3 -> je 0x162982 */
  /* cmp (int16_t)eax, 4 -> je 0x162982 */
  /* cmp (int16_t)eax, 7 -> je 0x162982 */
  /* cmp (int16_t)eax, 5 -> je 0x162982 */
  /* cmp (int16_t)eax, 8 -> jne 0x162f64 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cc] */
  /* test (char)eax, (char)eax -> je 0x162f64 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 981, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 995, 0);
  system_exit(0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)ebx);
  FUN_00178b40(40, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [esi + 0x6c], 1 -> je 0x162c2f */
  /* relift: relift: fld dword ptr [0x2533c8] */
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b94] = 3 */
  display_assert((char *)0x002a1b10, (char *)0x002a18c0, 1145, 0);
  system_exit(0);
  /* mem[0x005a5ac0] = 0x18200000 */
  /* mem[0x005a5b28] = 0xc0 */
  /* mem[0x005a5b48] = 0x380a1809 */
  /* mem[0x005a5b2c] = ebx */
  /* mem[0x005a5ac0] = 0x381a1819 */
  /* mem[0x005a5b48] = 0x380a1809 */
  /* mem[0x005a5b2c] = ebx */
  /* mem[0x005a5ac0] = 0x3a1a1a19 */
  /* mem[0x005a5b48] = 0x3a0a1a09 */
  /* mem[0x005a5ac4] = 0x181c0000 */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5b28] = edi */
  /* mem[0x005a5b74] = edi */
  display_assert((char *)0x002a1ad4, (char *)0x002a18c0, 1163, 0);
  system_exit(0);
  /* mem[0x005a5b4c] = 0x8204c20 */
  /* mem[0x005a5b4c] = 0x80c0000 */
  /* mem[0x005a5b4c] = 0x80c080c */
  /* mem[0x005a5b78] = edi */
  /* mem[0x005a5ac8] = 0x1c1b0000 */
  /* mem[0x005a5b30] = 0xc0 */
  display_assert((char *)0x002a1ad4, (char *)0x002a18c0, 1184, 0);
  system_exit(0);
  /* mem[0x005a5b50] = 0xc204b20 */
  /* mem[0x005a5b50] = 0xc0b0000 */
  /* mem[0x005a5b50] = 0xc0b0c0b */
  /* mem[0x005a5b7c] = edi */
  /* mem[0x005a5ae4] = 0x1c00 */
  /* mem[0x005a5ae0] = 0xc */
  FUN_00159070(0.0f);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0xc110000 */
  /* mem[0x005a5ae0] = 0x1c */
  display_assert((char *)0x002a1a94, (char *)0x002a18c0, 1206, 0);
  system_exit(0);
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x162f61 */
  /* mem[0x005a5468] = eax */
  /* mem[0x005a5464] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5460] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x162f90 */
void FUN_00162f90(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x162fb9 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1253, 0);
  system_exit(0);
  FUN_0016f910(11);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1631c8 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x1631c8 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);

  (void)eax;
}

/* 0x1631d0 */
void FUN_001631d0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x163205 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1311, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163580 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x163580 */
  /* test esi, esi -> jl 0x16322c */
  /* relift: cmp esi, dword ptr [0x5a37e0] -> jl 0x16324c */
  display_assert((char *)0x002a1a58, (char *)0x002a18c0, 1317, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x163285 */
  display_assert((char *)0x0029e134, (char *)0x002a18c0, 1320, 0);
  system_exit(0);
  /* cmp edi, -1 -> jne 0x163297 */
  normalize3d((float *)0);
  /* relift: relift: fld dword ptr [0x253398] */
  /* relift: relift: fld dword ptr [0x253398] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18c61 */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20400 */
  /* mem[0x005a5b48] = 0x484a0000 */
  /* mem[0x005a5b74] = 0x20c0 */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5ac4] = 0x4a204a20 */
  /* mem[0x005a5b2c] = 0x20500 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b78] = 0x10d00 */
  /* mem[0x005a5ac8] = 0x2c120c11 */
  /* mem[0x005a5b30] = ecx */
  /* mem[0x005a5b50] = 0xcd4b0809 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5acc] = 0xd0d1415 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ad0] = 0x1d1d151c */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b58] = 0xc091c09 */
  /* mem[0x005a5b84] = 0x110cd */
  /* mem[0x005a5ad4] = 0x1d1d0000 */
  /* mem[0x005a5b3c] = 0xd0 */
  /* mem[0x005a5b5c] = 0xc150d1d */
  /* mem[0x005a5b88] = 0x10cd */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1d330d00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x163590 */
void FUN_00163590(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x1635bf */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1472, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163903 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x163903 */
  /* test edi, edi -> jl 0x1635eb */
  /* relift: cmp edi, dword ptr [0x5a37e0] -> jl 0x16360b */
  display_assert((char *)0x002a1a58, (char *)0x002a18c0, 1478, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a1b40, (char *)0x002a18c0, 1481, 0);
  system_exit(0);
  /* relift: cmp dword ptr [eax + 0x1c], 0xbf800000 -> je 0x163688 */
  /* relift: cmp dword ptr [eax + 0x70], -1 -> jne 0x163660 */
  /* relift: cmp dword ptr [eax + 0x88], -1 -> je 0x163688 */
  /* relift: relift: mov word ptr [0x325170], 1 */
  real_rgb_color_brightness((float *)(uintptr_t)esi);
  /* relift: relift: fstp dword ptr [0x47dca8] */
  FUN_001631d0();
  /* relift: relift: mov word ptr [0x325170], 0 */
  real_rgb_color_brightness((float *)(uintptr_t)eax);
  /* relift: relift: fstp dword ptr [0x47dca8] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18c41 */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20400 */
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b48] = 0x484a0000 */
  /* mem[0x005a5b74] = 0x20c0 */
  /* mem[0x005a5ac4] = 0x4a204a20 */
  /* mem[0x005a5b2c] = 0x20500 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b78] = 0x10d00 */
  /* mem[0x005a5ac8] = 0x2c120c11 */
  /* mem[0x005a5b30] = ecx */
  /* mem[0x005a5b50] = 0xcd4b0809 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5acc] = 0xd0d1415 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ad0] = 0x1d1d151c */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b58] = 0xc091c09 */
  /* mem[0x005a5b84] = 0x110cd */
  /* mem[0x005a5ad4] = 0x1d1d0000 */
  /* mem[0x005a5b3c] = 0xd0 */
  /* mem[0x005a5b5c] = 0xc150d1d */
  /* mem[0x005a5b88] = 0x10cd */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1d200d00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x163910 */
void FUN_00163910(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16393f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1632, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163c39 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ce] */
  /* test (char)eax, (char)eax -> je 0x163c39 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 1639, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x163c36 */
  /* relift: relift: fld dword ptr [0x47dca8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x163c36 */
  /* test edi, edi -> jne 0x1639e6 */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 1645, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x325170] */
  FUN_00178b40(21, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  /* relift: relift: fld dword ptr [0x47dca8] */
  FUN_00159070(0.0f);
  /* relift: relift: fld dword ptr [0x47dca8] */
  /* mem[0x005a5af0] = eax */
  FUN_00159070(0.0f);
  /* mem[0x005a5b10] = eax */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5af4] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5b14] = eax */
  /* test (char)eax, 2 -> je 0x163b57 */
  /* mem[0x005a5b48] = 0x14a0000 */
  /* mem[0x005a5b4c] = 0x1cc8a40 */
  /* mem[0x005a5b7c] = 0x20d9 */
  /* mem[0x005a5b48] = 0x484a0000 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5b84] = eax */
  /* relift: test byte ptr [esi + 0x27c], 2 -> je 0x163bbb */
  /* mem[0x005a5b94] = 0x11008 */
  /* mem[0x005a5ad8] = ecx */
  /* mem[0x005a5adc] = ecx */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ad8] = eax */
  /* mem[0x005a5adc] = eax */
  /* mem[0x005a5b40] = eax */
  /* mem[0x005a5b44] = eax */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x163c36 */
  /* mem[0x005a5474] = eax */
  /* mem[0x005a5470] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a546c] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x163c40 */
void FUN_00163c40(void)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> jne 0x163c69 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1785, 0);
  system_exit(0);
  FUN_0016f910(12);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163fd2 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x163fd2 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x163fd2 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x18c21 */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ae8] = 0x800000ff */
  /* mem[0x005a5ac0] = 0x4b204b20 */
  /* mem[0x005a5b28] = 0x20400 */
  /* mem[0x005a5b48] = 0x484a0911 */
  /* mem[0x005a5b74] = 0x30c9 */
  /* mem[0x005a5aec] = 0xff */
  /* mem[0x005a5ac4] = 0x4a204a20 */
  /* mem[0x005a5b2c] = 0x20500 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b78] = 0x10d00 */
  /* mem[0x005a5ac8] = 0x2c120c11 */
  /* mem[0x005a5b30] = ecx */
  /* mem[0x005a5b50] = 0xcd4b0809 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5acc] = 0xd0d1415 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ad0] = 0x1d1d151c */
  /* mem[0x005a5b38] = eax */
  /* mem[0x005a5b58] = 0xc091c09 */
  /* mem[0x005a5b84] = 0x110cd */
  /* mem[0x005a5ad4] = 0x1d1d0000 */
  /* mem[0x005a5b3c] = 0xd0 */
  /* mem[0x005a5b5c] = 0xc150d1d */
  /* mem[0x005a5b88] = 0x10cd */
  /* mem[0x005a5b6c] = 0x80000000 */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = 0x1d110d00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
}

/* 0x163fe0 */
void FUN_00163fe0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x16400c */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1874, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1640c8 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x1640c8 */
  /* test eax, eax -> je 0x1640c1 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: relift: mov (char)ecx, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* relift: relift: mov dl, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(edx, 0, 0);
  /* relift: relift: mov byte ptr [0x47dca4], 0 */
  /* relift: relift: mov byte ptr [0x47dca4], 1 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1640d0 */
void FUN_001640d0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x1640ff */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1915, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x1643d5 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x1643d5 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x1643d5 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dca4] */
  /* test (char)eax, (char)eax -> jne 0x1643d5 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 1924, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1643d2 */
  /* relift: test byte ptr [esi + 0x27c], 4 -> je 0x1643d2 */
  FUN_00178b40(21, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  FUN_00159070(0.0f);
  /* mem[0x005a5af0] = eax */
  FUN_00159070(0.0f);
  /* mem[0x005a5b10] = eax */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5af4] = eax */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5b14] = eax */
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x1642eb */
  /* mem[0x005a5b48] = 0x14a0911 */
  /* mem[0x005a5b4c] = 0x1cc8a40 */
  /* mem[0x005a5b7c] = 0x20d9 */
  /* mem[0x005a5b48] = 0x484a0911 */
  /* mem[0x005a5b4c] = 0x48cc8a40 */
  /* mem[0x005a5b7c] = 0x20d0 */
  /* mem[0x005a5b84] = ecx */
  /* relift: test byte ptr [esi + 0x27c], 2 -> je 0x164353 */
  /* mem[0x005a5b94] = 0x11008 */
  /* mem[0x005a5ad8] = ecx */
  /* mem[0x005a5adc] = ecx */
  /* mem[0x005a5b94] = 0x11006 */
  /* mem[0x005a5ad8] = eax */
  /* mem[0x005a5adc] = eax */
  /* mem[0x005a5b40] = eax */
  /* mem[0x005a5b44] = eax */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x1643d2 */
  /* mem[0x005a5480] = eax */
  /* mem[0x005a547c] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5478] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1643e0 */
void FUN_001643e0(void)
{
  int eax = 0;
  int ebx = 0;

  /* cmp eax, ebx -> jne 0x16440c */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2069, 0);
  system_exit(0);
  FUN_0016f910(13);
  /* relift: cmp word ptr [0x3256bc], (int16_t)ebx -> jne 0x164585 */
  /* relift: cmp byte ptr [0x3256d0], (char)ebx -> je 0x164585 */
  /* relift: cmp byte ptr [0x3256d2], (char)ebx -> je 0x164585 */
  /* relift: cmp word ptr [0x3256b0], (int16_t)ebx -> jne 0x164585 */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(ebx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 1 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5ae8] = 0x80b050 */
  /* mem[0x005a5b48] = 0x8010000 */
  /* mem[0x005a5b74] = 0x20c0 */
  /* mem[0x005a5ac4] = 0x2c120c20 */
  /* mem[0x005a5b2c] = 0xc00 */
  /* mem[0x005a5ae0] = ebx */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ebx;
}

/* 0x164590 */
void FUN_00164590(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x1645bc */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2120, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x164684 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d0] */
  /* test (char)eax, (char)eax -> je 0x164684 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */
  /* test (char)eax, (char)eax -> je 0x164684 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x164684 */
  /* test eax, eax -> je 0x16467d */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: relift: mov (char)ecx, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* relift: relift: mov dl, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256ed] */
  D3DDevice_SetTextureStageState(edx, 0, 0);
  /* relift: relift: mov byte ptr [0x47dca4], 0 */
  /* relift: relift: mov byte ptr [0x47dca4], 1 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x164690 */
void FUN_00164690(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x1646bf */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2271, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x164ceb */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d1] */
  /* test (char)eax, (char)eax -> je 0x164ceb */
  /* relift: relift: mov (char)eax, byte ptr [0x5a5bc4] */
  /* test (char)eax, (char)eax -> je 0x164ceb */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x164ceb */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2280, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* test (char)eax, 1 -> je 0x164ce8 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x164764 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x164ce8 */
  /* test edi, edi -> jne 0x16478b */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 2287, 0);
  system_exit(0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(51, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x8c61 */
  /* mem[0x005a5b94] = 0x11005 */
  /* cmp eax, -1 -> jne 0x164bce */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x164b24 */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* test (char)eax, 0x41 -> jne 0x164b69 */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* test (char)eax, 0x41 -> jne 0x164bae */
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5b48] = 0x4a410b0b */
  /* mem[0x005a5b48] = 0x49480b0b */
  /* mem[0x005a5b74] = 0x20cd */
  /* mem[0x005a5b4c] = eax */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5b7c] = 0xd */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)edx);
  /* mem[0x005a5af4] = eax */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)ecx);
  /* mem[0x005a5b14] = eax */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5acc] = 0x2c120c11 */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b58] = 0x2c0d0c0b */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = eax */
  rasterizer_set_pixel_shader((void *)0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x164ce8 */
  /* mem[0x005a5498] = eax */
  /* mem[0x005a5494] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5490] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x164cf0 */
void FUN_00164cf0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x164d1f */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2462, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x165418 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */
  /* test (char)eax, (char)eax -> je 0x165418 */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2470, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  /* test (int16_t)edi, (int16_t)edi -> je 0x164d83 */
  /* cmp (int16_t)edi, 2 -> jne 0x164d9c */
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x164d8e */
  /* relift: cmp dword ptr [esi + 0x134], -1 -> jne 0x164d9c */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x164dc6 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x165415 */
  /* relift: cmp dword ptr [esi + 0x330], -1 -> je 0x165415 */
  /* test eax, eax -> jne 0x164dfa */
  display_assert((char *)0x002a19cc, (char *)0x002a18c0, 2495, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x164e05 */
  /* cmp (int16_t)edi, 3 -> jl 0x164e25 */
  display_assert((char *)0x002a1b78, (char *)0x002a18c0, 2496, 0);
  system_exit(0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_00178b40(42, 0, 0);
  shader_environment_texture_animation_evaluate();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  display_assert((char *)0x002a1b50, (char *)0x002a18c0, 2592, 0);
  system_exit(0);
  /* mem[0x005a5b98] = 0x18c61 */
  /* mem[0x005a5b98] = 0x62e21 */
  /* mem[0x005a5ba0] = 0 */
  /* mem[0x005a5b9c] = 0x111 */
  /* mem[0x005a5b94] = 0x11005 */
  /* cmp (int16_t)edi, 2 -> je 0x1651f5 */
  /* relift: cmp dword ptr [esi + 0x134], -1 -> je 0x1651f5 */
  /* mem[0x005a5b48] = 0x49480b0b */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x165237 */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* test (char)eax, 0x41 -> jne 0x16527c */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* test (char)eax, 0x41 -> jne 0x1652c1 */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5b48] = 0x4a410b0b */
  /* mem[0x005a5b4c] = eax */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5b74] = 0x20cd */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b7c] = 0xd */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)eax);
  /* mem[0x005a5af4] = eax */
  real_a_rgb_color_to_pixel32(0.0f, (float *)(uintptr_t)edx);
  /* mem[0x005a5b14] = eax */
  /* mem[0x005a5acc] = 0x2c120c11 */
  /* mem[0x005a5b34] = eax */
  /* mem[0x005a5b54] = 0x2c020c01 */
  /* mem[0x005a5b80] = eax */
  /* mem[0x005a5b58] = 0x2c0d0c0b */
  /* mem[0x005a5b84] = eax */
  /* mem[0x005a5ae0] = 0xc0f0000 */
  /* mem[0x005a5ae4] = ecx */
  rasterizer_set_pixel_shader((void *)0);
  /* relift: cmp word ptr [0x3256b0], 0 -> je 0x1653bb */
  /* cmp (int16_t)edi, 2 -> jne 0x1653bb */
  FUN_0015de60();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x165415 */
  /* mem[0x005a5498] = eax */
  /* mem[0x005a5494] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5490] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x165420 */
void FUN_00165420(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp eax, ebx -> jne 0x165452 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2699, 0);
  system_exit(0);
  /* relift: cmp byte ptr [0x3256d3], (char)ebx -> je 0x16576f */
  display_assert((char *)0x002a18b8, (char *)0x002a18c0, 2706, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x24], 3 -> jne 0x1654ae */
  display_assert((char *)0x002a1c44, (char *)0x002a18c0, 2707, 0);
  system_exit(0);
  shader_type_is_valid_for_environment();
  /* test (char)eax, (char)eax -> jne 0x1654e1 */
  display_assert((char *)0x002a1c0c, (char *)0x002a18c0, 2708, 0);
  system_exit(0);
  /* cmp edi, ebx -> jne 0x165508 */
  display_assert((char *)0x002a1774, (char *)0x002a18c0, 2709, 0);
  system_exit(0);
  shader_is_decal((void *)(uintptr_t)esi);
  /* test (char)eax, (char)eax -> je 0x165547 */
  /* mem[0x0047dc88] = ecx */
  rasterizer_transparent_geometry_group_new();
  /* cmp esi, ebx -> je 0x16574f */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* cmp eax, ebx -> jne 0x165612 */
  rasterizer_memory_pool_copy(0, 116);
  /* relift: cmp word ptr [edi + 0x24], 7 -> jne 0x1656e3 */
  FUN_001792C0(0);
  /* relift: cmp word ptr [edi + 0x24], 7 -> jne 0x1656e3 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)ecx, 8 -> je 0x1656e3 */
  /* relift: cmp dword ptr [ebp - 4], ebx -> je 0x1656c1 */
  display_assert((char *)0x002a1bcc, (char *)0x002a18c0, 2782, 0);
  system_exit(0);
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)esi, 0);
  FUN_001845b0((void *)(uintptr_t)esi, 0);
  /* relift: cmp dword ptr [ebp - 4], ebx -> je 0x1656f2 */
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)esi, 0);
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16576d */
  /* mem[0x005a54a8] = esi */
  /* mem[0x005a54a0] = edx */
  /* mem[0x005a54a4] = eax */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a549c] = ecx */
  /* relift: cmp byte ptr [0x47dcac], (char)ebx -> jne 0x16576d */
  error(0, (char *)0x002a1744);
  /* relift: relift: mov byte ptr [0x47dcac], 1 */
  /* cmp esi, 0x52 -> jge 0x16579b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1657a9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1657be */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1657ca */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1657d6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1657e2 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1657ee */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1657fa */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x165806 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x165812 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16581e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16582a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x165836 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x165845 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x165854 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x165863 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x165872 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x165881 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x165890 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16589f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1658ae */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1658bd */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1658cc */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1658db */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1658ea */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1658f9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x165908 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x165917 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x165925 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16593c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x165949 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x165956 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x165963 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x165970 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x165980 */
void FUN_00165980(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_Clear(edx, (void *)(uintptr_t)ecx, eax, edx, 0.0f, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1659a0 */
void FUN_001659a0(void)
{
  int eax = 0;

  debug_malloc(20480, 0, (char *)0x002a1cc8, 248);
  /* mem[0x0047df00] = eax */
  /* mem[0x0047df04] = 0 */
  error(0, (char *)0x002a1c70);

  (void)eax;
}

/* 0x1659f0 */
void FUN_001659f0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x165a00 */
void FUN_00165a00(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x165a10 */
void FUN_00165a10(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> je 0x165a2c */
  debug_free((void *)(uintptr_t)eax, (char *)0x002a1cc8, 279);
  /* cmp esi, 0x52 -> jge 0x165a4f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x165a62 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x165a7f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x165a8f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x165a9f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x165aaf */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x165abf */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x165acf */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x165adf */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x165aef */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x165aff */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x165b0f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x165b1f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x165b32 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x165b45 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x165b58 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x165b6b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x165b7e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x165b91 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x165ba4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x165bb7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x165bca */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x165bdd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x165bf0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x165c03 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x165c16 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x165c29 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x165c3c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x165c4a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x165c60 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x165c71 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x165c82 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x165c93 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x165ca0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x165cb0 */
void FUN_00165cb0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x165cdc */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 423, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x165dbb */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d4] */
  /* test (char)eax, (char)eax -> je 0x165dbb */
  /* test edi, edi -> jne 0x165d21 */
  display_assert((char *)0x002a18b8, (char *)0x002a1cc8, 430, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test esi, esi -> jne 0x165d53 */
  display_assert((char *)0x002a19cc, (char *)0x002a1cc8, 435, 0);
  system_exit(0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)edi);
  FUN_00178b40(0, 0, 0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x165db8 */
  /* mem[0x005a54b4] = eax */
  /* mem[0x005a54b0] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a54ac] = ecx */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x165dd0 */
void FUN_00165dd0(void)
{
  FUN_0016fa40(17);
}

/* 0x165de0 */
void FUN_00165de0(void)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  /* cmp (int16_t)eax, 4 -> jl 0x165e20 */
  display_assert((char *)0x002a1d18, (char *)0x002a1cc8, 484, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x165e47 */
  display_assert((char *)0x002a1d0c, (char *)0x002a1cc8, 485, 0);
  system_exit(0);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0x165ea0 */
void FUN_00165ea0(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256d5] */
  /* test (char)eax, (char)eax -> je 0x165fb3 */
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x165fb3 */
  /* cmp eax, 0x80 -> jge 0x165f8f */
  /* mem[0x0047df04] = eax */
  /* relift: relift: mov (char)ecx, byte ptr [0x47df38] */
  rasterizer_memory_pool_copy(0, 0);
  /* mem[0x0047dcb4] = eax */
  /* relift: relift: mov word ptr [0x47dcb0], (int16_t)ecx */
  /* relift: relift: mov byte ptr [0x47df38], 1 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x47dcb0] */
  /* relift: relift: mov (char)eax, byte ptr [0x47df44] */
  /* test (char)eax, (char)eax -> jne 0x165fb3 */
  error(0, (char *)0x002a1d48);
  /* relift: relift: mov byte ptr [0x47df44], 1 */

  (void)eax;
  (void)ecx;
}

/* 0x165fc0 */
void FUN_00165fc0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x165fd0 */
void FUN_00165fd0(void)
{
  int eax = 0;

  random_math_get_local_seed_address();
  random_seed_step((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x166010 */
void FUN_00166010(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc2] */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x166205 */
  /* cmp (int16_t)eax, 4 -> jge 0x166205 */
  /* relift: cmp ecx, dword ptr [esi*8 + 0x47df14] -> je 0x16619e */
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a1d90, (char *)0x002a1cc8, 92, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16619e */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d5] */
  /* test (char)eax, (char)eax -> je 0x16619e */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x16619e */
  /* test ecx, ecx -> je 0x16619e */
  /* relift: cmp word ptr [ecx + 2], 0 -> jle 0x16619e */
  /* relift: cmp dword ptr [ecx + 0x44], -1 -> je 0x16619e */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: mov (int16_t)edx, word ptr [0x5a5daa] */
  /* relift: relift: fld dword ptr [0x5a5df4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16619e */
  /* relift: relift: fld dword ptr [0x5a5dd0] */
  /* relift: relift: fld dword ptr [0x5a5dcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fld dword ptr [0x253f44] */
  /* test (int16_t)edx, (int16_t)edx -> je 0x1661a9 */
  /* relift: relift: fld dword ptr [0x5a5df4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16619e */
  /* mem[0x0047ddc4] = 0 */
  /* test (char)eax, 0x41 -> jne 0x166184 */
  /* mem[0x0047ddc4] = 0x3f800000 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x166210 */
void FUN_00166210(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test ebx, ebx -> jne 0x16623a */
  display_assert((char *)0x002a1dd0, (char *)0x002a1cc8, 163, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x16625e */
  display_assert((char *)0x002a1dc8, (char *)0x002a1cc8, 164, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1663ee */
  /* relift: relift: fld dword ptr [0x2533c8] */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)eax);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  /* test (char)eax, 1 -> jne 0x1663ed */
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_001d9e70(0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_seed_step((void *)(uintptr_t)eax);
  perpendicular2d((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx);
  /* relift: relift: fld dword ptr [0x2533c8] */
  magnitude3d((float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);
  random_math_get_local_seed_address();
  random_real_range((void *)(uintptr_t)eax, 0.0f, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x166400 */
void FUN_00166400(void)
{
  int eax = 0;

  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x166439 */
  display_assert((char *)0x002a1e14, (char *)0x002a1cc8, 290, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5de8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16646c */
  display_assert((char *)0x0029f040, (char *)0x002a1cc8, 291, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16649f */
  display_assert((char *)0x0029f008, (char *)0x002a1cc8, 292, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1664c8 */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 293, 0);
  system_exit(0);
  FUN_0016f910(17);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x16688a */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d4] */
  /* test (char)eax, (char)eax -> je 0x16688a */
  /* relift: relift: fld dword ptr [0x5a5dd0] */
  /* relift: relift: fld dword ptr [0x5a5dcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* test (char)eax, 0x41 -> jne 0x166553 */
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* test (char)eax, 0x41 -> jne 0x166590 */
  /* relift: test byte ptr [0x5a5da8], 2 -> je 0x1665d2 */
  /* relift: relift: fcomp dword ptr [0x2546a0] */
  /* relift: cmp word ptr [0x47df30], 0x14 -> jge 0x1665d4 */
  error(0, (char *)0x002a1dd8);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* relift: relift: fld dword ptr [0x5a5db8] */
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b94] = 0x11002 */
  FUN_000d1e90(0.0f, 0.0f);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* mem[0x005a5ae8] = eax */
  /* relift: relift: fld dword ptr [0x5a5de4] */
  FUN_000d1e90(0.0f, 0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x2191209 */
  /* mem[0x005a5b28] = 0xc00 */
  /* mem[0x005a5b48] = 0x11180118 */
  /* mem[0x005a5b74] = 0x48 */
  real_a_rgb_color_to_pixel32(0.0f, (void *)0x005a5dac);
  /* mem[0x005a5aec] = eax */
  FUN_000d1dd0((void *)0x005a5dd8);
  /* mem[0x005a5b0c] = eax */
  /* mem[0x005a5ac4] = 0x283c311c */
  /* mem[0x005a5b2c] = eax */
  /* mem[0x005a5b4c] = 0x108021c */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ae0] = 0xc3d000f */
  /* mem[0x005a5ae4] = 0xd243c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
}

/* 0x166890 */
void FUN_00166890(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> je 0x1668c9 */
  /* cmp (int16_t)edi, 1 -> je 0x1668c9 */
  display_assert((char *)0x002a20e4, (char *)0x002a1cc8, 499, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1668f2 */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 500, 0);
  system_exit(0);
  /* relift: relift: mov word ptr [0x47ddc8], (int16_t)edi */
  FUN_0016f910(18);
  FUN_00166010();
  /* test (char)eax, (char)eax -> je 0x1677c8 */
  /* relift: relift: fld dword ptr [0x47ddc4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a20c8, (char *)0x002a1cc8, 514, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x167261 */
  /* relift: relift: mov (char)eax, byte ptr [0x325172] */
  tag_get('mtib', 0);
  csmemset((void *)(uintptr_t)edx, 0, 76);
  /* relift: cmp word ptr [ebx + 2], (int16_t)esi -> jle 0x166a18 */
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* relift: cmp (int16_t)esi, word ptr [ebx + 2] -> jl 0x1669e0 */
  csmemcpy((void *)(uintptr_t)esi, (void *)0x005a5bc8, 52);
  /* relift: relift: mov byte ptr [0x325172], 0 */
  FUN_00166210();
  /* relift: relift: mov (int16_t)edx, word ptr [0x5a5bc2] */
  FUN_0017cf00();
  matrix_inverse((float *)(uintptr_t)eax, (float *)(uintptr_t)edx);
  matrix4x3_multiply((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix4x3_multiply((void *)0x005a5c2c, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  csmemcpy((void *)(uintptr_t)eax, (void *)0x005a5c2c, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x5a5bf0] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  matrix_transform_vector((float *)0, (float *)0, (float *)0);
  /* relift: relift: fcomp dword ptr [0x25bb10] */
  /* test (char)eax, 0x41 -> jne 0x166d93 */
  floor(0.0f);
  /* test (int16_t)edi, (int16_t)edi -> jle 0x166cfb */
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  /* test (char)eax, 1 -> jne 0x166d91 */
  error(0, (char *)0x002a2070);
  tag_get('mtib', 0);
  /* test eax, eax -> jg 0x166e02 */
  display_assert((char *)0x002a203c, (char *)0x002a1cc8, 653, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x166fe3 */
  /* relift: relift: fld dword ptr [0x5a5e18] */
  floor(0.0f);
  /* relift: relift: fcomp qword ptr [0x2602c0] */
  /* relift: relift: fld qword ptr [0x2602c0] */
  floor(0.0f);
  /* relift: relift: fcomp qword ptr [0x2573d8] */
  /* test (char)eax, 0x41 -> jne 0x166e88 */
  /* relift: relift: fld qword ptr [0x2573d8] */
  floor(0.0f);
  floor(0.0f);
  /* test (int16_t)edi, (int16_t)edi -> jge 0x166fa8 */
  /* relift: relift: mov (char)eax, byte ptr [0x47df32] */
  /* test (char)eax, (char)eax -> jne 0x166fa6 */
  error(0, (char *)0x002a1ff8);
  error(0, (char *)0x002a1fe8);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  error(0, (char *)0x002a1fd8);
  error(0, (char *)0x002a1fc8);
  error(0, (char *)0x002a1fb8);
  error(0, (char *)0x002a1fac);
  error(0, (char *)0x002a1f94);
  /* relift: relift: mov byte ptr [0x47df32], 1 */
  /* cmp edx, ecx -> jl 0x166fd5 */
  display_assert((char *)0x002a1f50, (char *)0x002a1cc8, 682, 0);
  system_exit(0);
  /* relift: relift: fld qword ptr [0x2a1f48] */
  FUN_001d9e70(0.0f, 0.0f);
  /* relift: relift: fld qword ptr [0x28c8d0] */
  FUN_001d9e70(0.0f, 0.0f);
  /* relift: relift: fld dword ptr [0x47ddc4] */
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* relift: relift: mov byte ptr [0x47dd89], 0 */
  /* relift: relift: mov byte ptr [0x47dd88], 0 */
  /* relift: relift: mov byte ptr [0x47dd89], (char)eax */
  /* test ecx, ecx -> jle 0x167254 */
  /* relift: relift: mov byte ptr [0x47dd88], 1 */
  /* relift: relift: mov byte ptr [0x47dd88], 0 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dd89] */
  /* test (char)eax, (char)eax -> jne 0x167277 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dd88] */
  /* test (char)eax, (char)eax -> je 0x1677c6 */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x1672b9 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x167295 */
  /* test (char)ecx, 2 -> jne 0x1672b9 */
  /* test (int16_t)eax, (int16_t)eax -> jne 0x1672b5 */
  /* test (char)ecx, 2 -> je 0x1672a3 */
  /* test eax, eax -> jg 0x1672b5 */
  FUN_001792d0();
  /* test (char)eax, (char)eax -> je 0x1672b9 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d6] */
  /* test (char)eax, (char)eax -> je 0x1672b9 */
  D3DDevice_Clear(esi, (void *)(uintptr_t)esi, ecx, 0, 0.0f, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = esi */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = esi */
  D3DDevice_SetRenderState_ZBias(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x167425 */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* test (char)eax, 4 -> je 0x16745f */
  /* mem[0x005a5b94] = edi */
  /* mem[0x005a5ae4] = 0x3300 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a1f2c, (char *)0x002a1cc8, 856, edi);
  system_exit(0);
  /* mem[0x005a5b98] = edi */
  /* mem[0x005a5b94] = edi */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x167526 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, edi);
  system_exit(0);
  /* mem[0x005a5ae8] = ecx */
  /* mem[0x005a5ac0] = 0x28110820 */
  /* mem[0x005a5b28] = 0xc00 */
  /* mem[0x005a5ae4] = 0x3c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (char)eax, byte ptr [0x47dd88] */
  /* test (char)eax, (char)eax -> je 0x1677c6 */
  /* cmp (int16_t)eax, 4 -> jne 0x1676cc */
  FUN_001906b0((void *)(uintptr_t)ecx, 0);
  /* test (char)eax, 4 -> jne 0x1676d8 */
  D3DDevice_SetRenderState_PSTextureModes();
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(edi, 0, 0);
  D3DDevice_SetTextureStageState(edi, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* test (char)eax, (char)eax -> je 0x1676b7 */
  FUN_00167ff0(0, (char *)0x002a1e90);
  /* cmp (int16_t)eax, 3 -> je 0x1676d8 */
  /* cmp (int16_t)eax, 8 -> jne 0x1676ec */
  D3DDevice_SetRenderState_PSTextureModes();
  D3DDevice_SetTextureStageState(0, 0, 0);
  FUN_00184610((void *)(uintptr_t)esi);
  FUN_00178b40(0, 0, 0);
  /* test eax, eax -> je 0x16771b */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x16771b */
  rasterizer_set_model_skinning((void *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x16778a */
  FUN_00174510((void *)(uintptr_t)esi, 0);
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16778a */
  /* mem[0x005a54d0] = ecx */
  /* mem[0x005a54cc] = eax */
  FUN_0017ed90();
  /* mem[0x005a54c8] = ecx */
  /* cmp eax, ecx -> jl 0x1675b0 */
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x1677c6 */
  error(0, (char *)0x002a1e54);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1677d0 */
void FUN_001677d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* test eax, eax -> jne 0x1677fc */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 988, 0);
  system_exit(0);
  FUN_00166010();
  /* test (char)eax, (char)eax -> je 0x167912 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x47ddc8] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x16783a */
  /* cmp (int16_t)eax, 1 -> je 0x16783a */
  display_assert((char *)0x002a2180, (char *)0x002a1cc8, 992, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x47dd89] */
  /* test (char)eax, (char)eax -> je 0x167912 */
  /* test eax, eax -> jne 0x167870 */
  display_assert((char *)0x002a215c, (char *)0x002a1cc8, 996, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc2] */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x167881 */
  /* cmp (int16_t)eax, 4 -> jl 0x1678a1 */
  display_assert((char *)0x002a20f8, (char *)0x002a1cc8, 997, 0);
  system_exit(0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)eax);
  FUN_00178b40(0, 0, 0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16790f */
  /* mem[0x005a54c0] = eax */
  /* mem[0x005a54bc] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a54b8] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x167920 */
void FUN_00167920(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16794f */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 1036, 0);
  system_exit(0);
  FUN_00166010();
  /* test (char)eax, (char)eax -> je 0x167ec6 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dd89] */
  /* relift: relift: mov (char)eax, byte ptr [0x47dd88] */
  /* relift: relift: mov (int16_t)eax, word ptr [0x47ddc8] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x1679c3 */
  /* cmp (int16_t)eax, 1 -> je 0x1679c3 */
  display_assert((char *)0x002a2180, (char *)0x002a1cc8, 1045, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1679ec */
  display_assert((char *)0x002a215c, (char *)0x002a1cc8, 1047, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc2] */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1679fd */
  /* cmp (int16_t)eax, 4 -> jl 0x167a1d */
  display_assert((char *)0x002a20f8, (char *)0x002a1cc8, 1048, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x167ab4 */
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)ebx, (int16_t)ecx -> jl 0x167a2e */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 0x11004 */
  /* mem[0x005a5b98] = ecx */
  FUN_000d1dd0((float *)0);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1dd0((void *)0x0047dda0);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5b48] = 0x8010902 */
  /* mem[0x005a5b74] = 0x3089 */
  FUN_000d1dd0((void *)0x0047ddac);
  /* mem[0x005a5aec] = eax */
  FUN_000d1dd0((void *)0x0047ddb8);
  /* mem[0x005a5b0c] = eax */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5b4c] = 0xa010b02 */
  /* mem[0x005a5b78] = 0x30ab */
  /* mem[0x005a5ac4] = eax */
  /* mem[0x005a5b30] = 0xd0 */
  /* mem[0x005a5ac8] = ecx */
  /* mem[0x005a5b7c] = edi */
  /* mem[0x005a5acc] = 0x1c1d0000 */
  /* mem[0x005a5b34] = 0xc0 */
  /* mem[0x005a5b50] = ecx */
  /* mem[0x005a5b80] = edi */
  /* mem[0x005a5b54] = ecx */
  /* test esi, esi -> je 0x167d58 */
  /* mem[0x005a5b6c] = esi */
  FUN_000d1dd0((void *)0x005a5dd8);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0x8010f00 */
  /* mem[0x005a5ae4] = 0xc011c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_End();
  /* relift: cmp word ptr [0x47ddc8], 0 -> jne 0x167ed0 */
  /* test (char)ebx, (char)ebx -> je 0x167eda */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x305 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = esi */
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = esi */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_End();
  /* relift: cmp word ptr [0x47ddc8], 0 -> je 0x167eda */
  FUN_0016fa40(18);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x167ee0 */
void FUN_00167ee0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256d5] */
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x167fdc */
  FUN_00166010();
  /* test (char)eax, (char)eax -> je 0x167fdc */
  display_assert((char *)0x0029f510, (char *)0x002a1cc8, 1177, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x167f61 */
  display_assert((char *)0x002a1dd0, (char *)0x002a1cc8, 1178, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* mem[0x0047df34] = esi */
  /* relift: relift: mov byte ptr [0x47df38], 0 */
  /* mem[0x005a54c4] = ecx */

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x167ff0 */
void FUN_00167ff0(int a1, const char *call_text)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  vsprintf((char *)(uintptr_t)edx, (char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* relift: FUN_00201c48(0, 0, 1023); */
  /* test eax, eax -> jge 0x168044 */
  csstrcpy((char *)(uintptr_t)ecx, (char *)0x002a240c);
  /* cmp edi, 0x8876081f -> jg 0x168114 */
  /* cmp edi, 0x88760819 -> jg 0x1680ce */
  /* cmp edi, 0x80070057 -> jg 0x16809c */
  /* cmp edi, 0x80004005 -> je 0x168088 */
  /* cmp edi, 0x8007000e -> jne 0x168178 */
  /* cmp edi, 0x8876017c -> je 0x1680ba */
  /* cmp edi, 0x88760818 -> jne 0x168178 */
  /* cmp eax, 4 -> ja 0x168178 */
  /* cmp eax, 0x4b -> ja 0x168178 */
  error(0, (char *)0x002a21a8);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x168230 */
void FUN_00168230(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_CreateTexture(eax, edx, ecx, eax, edx, ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x168250 */
void FUN_00168250(void)
{
  D3DDevice_CreateVolumeTexture();
}

/* 0x168280 */
void FUN_00168280(void)
{
  int eax = 0;

  D3DDevice_CreateCubeTexture();
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x1682c0 */
void FUN_001682c0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DTexture_LockRect((void *)(uintptr_t)ecx, eax, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x168300 */
void FUN_00168300(void)
{
  D3DVolumeTexture_LockBox();
}

/* 0x168340 */
void FUN_00168340(void)
{
  D3DCubeTexture_LockRect();
}

/* 0x168370 */
char FUN_00168370(void *bitmap)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x002a27a8, 51, ebx);
  system_exit(0);
  /* relift: test byte ptr [esi + 0xe], (char)ebx -> jne 0x1683be */
  display_assert((char *)0x002a2760, (char *)0x002a27a8, 52, ebx);
  system_exit(0);
  FUN_00183120((void *)(uintptr_t)esi);
  /* test ecx, ecx -> je 0x1684e7 */
  display_assert((char *)0x00261d30, (char *)0x002a27a8, 91, ebx);
  system_exit(0);
  D3DDevice_CreateCubeTexture();
  /* test eax, eax -> jge 0x1684bb */
  D3DDevice_CreateVolumeTexture();
  /* test eax, eax -> jl 0x168474 */
  D3DDevice_CreateTexture(edi, edx, eax, 0, 0, 0, (void *)0);
  /* test eax, eax -> jl 0x1684ab */
  FUN_00167ff0(0, (char *)0x002a24b0);
  /* test (char)ebx, (char)ebx -> jne 0x1684e1 */
  error(0, (char *)0x002a247c);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x168500 */
void FUN_00168500(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x002a27a8, 141, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1686b0 */
  /* test eax, eax -> je 0x1686b0 */
  /* test eax, eax -> je 0x1686b0 */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0x14] -> jg 0x16869c */
  D3DTexture_LockRect((void *)(uintptr_t)edx, ecx, (void *)(uintptr_t)eax, (void *)0, 0);
  /* test (char)ebx, (char)ebx -> jne 0x1685a6 */
  FUN_00167ff0(0, (char *)0x002a2890);
  error(0, (char *)0x002a286c);
  /* test eax, eax -> je 0x168588 */
  bitmap_mipmap_address((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_width((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [esi + 0xe], 2 -> je 0x1685f8 */
  bitmap_mipmap_get_pixel_data_size((void *)(uintptr_t)esi, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)edi, eax);
  bitmap_format_bits_per_pixel(0);
  display_assert((char *)0x002a2820, (char *)0x002a27a8, 177, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle2d_long();
  rasterizer_xbox_bitmap_swizzle2d_word();
  rasterizer_xbox_bitmap_swizzle2d_byte();
  /* test (char)ebx, (char)ebx -> jne 0x1686af */
  error(0, (char *)0x002a27ec);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1686c0 */
void FUN_001686c0(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x002a27a8, 203, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1688bd */
  /* test eax, eax -> je 0x1688bd */
  /* test eax, eax -> je 0x1688bd */
  /* relift: cmp (int16_t)esi, word ptr [edi + 0x14] -> jg 0x1688a9 */
  D3DVolumeTexture_LockBox();
  /* test (char)ebx, (char)ebx -> jne 0x168766 */
  FUN_00167ff0(0, (char *)0x002a2918);
  error(0, (char *)0x002a286c);
  /* test eax, eax -> je 0x168748 */
  bitmap_mipmap_address((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_width((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)edi, 0);
  bitmap_mipmap_get_depth((void *)(uintptr_t)edi, 0);
  /* test (int16_t)eax, (int16_t)eax -> jle 0x16889f */
  bitmap_mipmap_get_pixel_data_size((void *)(uintptr_t)edi, 0);
  csmemcpy((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx, eax);
  bitmap_format_bits_per_pixel(0);
  display_assert((char *)0x002a2820, (char *)0x002a27a8, 249, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle3d_long();
  rasterizer_xbox_bitmap_swizzle3d_word();
  rasterizer_xbox_bitmap_swizzle3d_byte();
  /* test (char)ebx, (char)ebx -> jne 0x1688bc */
  error(0, (char *)0x002a27ec);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x1688d0 */
void FUN_001688d0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00263768, (char *)0x002a27a8, 276, 0);
  system_exit(0);
  /* test eax, eax -> je 0x168ad0 */
  /* test eax, eax -> je 0x168ad0 */
  /* test eax, eax -> je 0x168ad0 */
  /* relift: cmp (int16_t)eax, word ptr [esi + 0x14] -> jg 0x168abc */
  /* cmp (int16_t)edi, 6 -> jge 0x16899b */
  D3DCubeTexture_LockRect();
  /* test (char)ebx, (char)ebx -> jne 0x1689ab */
  FUN_00167ff0(0, (char *)0x002a29a8);
  error(0, (char *)0x002a286c);
  /* test eax, eax -> je 0x168982 */
  bitmap_cube_map_address((void *)(uintptr_t)esi, 0, 0, 0, 0);
  bitmap_mipmap_width((void *)(uintptr_t)esi, 0);
  bitmap_mipmap_get_height((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [esi + 0xe], 2 -> je 0x168a18 */
  bitmap_mipmap_get_pixel_data_size((void *)(uintptr_t)esi, 0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)edi, edx);
  bitmap_format_bits_per_pixel(0);
  display_assert((char *)0x002a2820, (char *)0x002a27a8, 319, 0);
  system_exit(0);
  rasterizer_xbox_bitmap_swizzle2d_long();
  rasterizer_xbox_bitmap_swizzle2d_word();
  rasterizer_xbox_bitmap_swizzle2d_byte();
  /* test (char)ebx, (char)ebx -> jne 0x168acf */
  error(0, (char *)0x002a27ec);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x168ae0 */
void FUN_00168ae0(void)
{
  int eax = 0;
  int esi = 0;

  texture_cache_bitmap_delete();
  /* test esi, esi -> je 0x168b08 */
  /* test eax, eax -> je 0x168b08 */
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
  (void)esi;
}

/* 0x168b10 */
void FUN_00168b10(void *bitmap)
{
  int ebx = 0;
  int esi = 0;

  /* cmp esi, ebx -> jne 0x168b3b */
  display_assert((char *)0x00263768, (char *)0x002a27a8, 112, 0);
  system_exit(0);
  /* relift: relift: mov word ptr [0x325652], 1 */
  display_assert((char *)0x00261d30, (char *)0x002a27a8, 128, 0);
  system_exit(0);
  /* relift: relift: mov word ptr [0x325652], (int16_t)ebx */
  FUN_001688d0();
  /* relift: relift: mov word ptr [0x325652], (int16_t)ebx */
  FUN_001686c0();
  /* relift: relift: mov word ptr [0x325652], (int16_t)ebx */
  FUN_00168500();
  /* relift: relift: mov word ptr [0x325652], (int16_t)ebx */

  (void)ebx;
  (void)esi;
}

/* 0x168bc0 */
void FUN_00168bc0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_CreateVertexBuffer(ecx, eax, edx, ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x168be0 */
void FUN_00168be0(void)
{
  int eax = 0;

  D3DDevice_CreateIndexBuffer();
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x168c40 */
void FUN_00168c40(void)
{
  D3DVertexBuffer_Lock();
}

/* 0x168c70 */
void FUN_00168c70(void)
{
  int eax = 0;

  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
}

/* 0x168ca0 */
void FUN_00168ca0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x168cd0 */
void FUN_00168cd0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_00180050(0);
  display_assert((char *)0x002a19cc, (char *)0x002a2b58, 24, 0);
  system_exit(0);
  /* cmp ecx, eax -> je 0x168d41 */
  /* test eax, eax -> je 0x168d41 */
  display_assert((char *)0x002a2b2c, (char *)0x002a2b58, 25, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x168d47 */
  /* test eax, eax -> jne 0x168d54 */
  /* test (char)ebx, (char)ebx -> je 0x168d99 */
  D3DDevice_CreateVertexBuffer(eax, 0, 0, 0, (void *)(uintptr_t)edx);
  /* test eax, eax -> jl 0x168d73 */
  FUN_00167ff0(0, (char *)0x002a2a90);
  /* test eax, eax -> jne 0x168d8e */
  /* test (char)ebx, (char)ebx -> jne 0x168d99 */
  /* test eax, eax -> je 0x168e0c */
  /* test (char)ebx, (char)ebx -> je 0x168e10 */
  /* relift: relift: mov word ptr [0x325652], 2 */
  D3DVertexBuffer_Lock();
  /* relift: relift: mov word ptr [0x325652], (int16_t)edi */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)ebx, ecx);
  /* test (char)ebx, (char)ebx -> jne 0x168e29 */
  csmemset((void *)(uintptr_t)esi, 0, 20);
  error(0, (char *)0x002a2a54);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x168e40 */
void FUN_00168e40(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> je 0x168e5f */
  /* test eax, eax -> je 0x168e5f */
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
  (void)esi;
}

/* 0x168e70 */
void FUN_00168e70(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x168e9c */
  display_assert((char *)0x002a2c90, (char *)0x002a2b58, 115, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x168ec0 */
  display_assert((char *)0x002a2c84, (char *)0x002a2b58, 116, 0);
  system_exit(0);
  /* test ebx, ebx -> jg 0x168ee4 */
  display_assert((char *)0x00257c5c, (char *)0x002a2b58, 117, 0);
  system_exit(0);
  display_assert((char *)0x002a0c9c, (char *)0x002a2b58, 128, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x168f48 */
  csmemset((void *)(uintptr_t)esi, 0, 16);
  error(0, (char *)0x002a2c48);
  D3DDevice_CreateIndexBuffer();
  /* test eax, eax -> jl 0x168f60 */
  FUN_00167ff0(0, (char *)0x002a2ba0);
  /* test eax, eax -> jne 0x168f82 */
  /* test (char)ebx, (char)ebx -> jne 0x168f8f */
  /* test eax, eax -> je 0x168f26 */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edi, edi);

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x168fd0 */
void _rasterizer_dynamic_unlit_geometry_draw(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> je 0x168fef */
  /* test eax, eax -> je 0x168fef */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* cmp esi, 0x52 -> jge 0x16901b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x169029 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16903e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16904a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x169056 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x169062 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16906e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16907a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x169086 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x169092 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16909e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1690aa */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1690b6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1690c5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1690d4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1690e3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1690f2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x169101 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x169110 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16911f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16912e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16913d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16914c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x16915b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x16916a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x169179 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x169188 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x169197 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1691a5 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x1691bc */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1691c9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1691d6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1691e3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1691f0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x169200 */
void FUN_00169200(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1693b4 */
  /* relift: relift: mov (int16_t)esi, word ptr [0x5a5bfa] */
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  /* relift: relift: fld dword ptr [0x5a5d84] */
  /* relift: relift: fld dword ptr [0x5a5d74] */
  /* relift: relift: fld dword ptr [0x5a5d64] */
  /* relift: relift: fld dword ptr [0x5a5d88] */
  /* relift: relift: fld dword ptr [0x5a5d78] */
  /* relift: relift: fld dword ptr [0x5a5d68] */
  /* relift: relift: fld dword ptr [0x5a5d60] */
  /* relift: relift: fld dword ptr [0x5a5d74] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1693ac */
  /* relift: relift: fld dword ptr [0x5a5d8c] */
  /* relift: relift: fld dword ptr [0x5a5d7c] */
  /* relift: relift: fld dword ptr [0x5a5d6c] */
  /* relift: relift: fld dword ptr [0x5a5d80] */
  /* relift: relift: fld dword ptr [0x5a5d70] */
  /* relift: relift: fld dword ptr [0x5a5d60] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x16937e */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* cmp esi, 0x52 -> jge 0x1693df */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1693f2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16940f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16941f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16942f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16943f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16944f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16945f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16946f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16947f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16948f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16949f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1694af */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1694c2 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1694d5 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1694e8 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1694fb */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16950e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x169521 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x169534 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x169547 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16955a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16956d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x169580 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x169593 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1695a6 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1695b9 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x1695cc */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1695da */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x1695f0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x169601 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x169612 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x169623 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x169630 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x169650 */
void FUN_00169650(void)
{
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);

  (void)edx;
}

/* 0x169670 */
void FUN_00169670(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_SetVertexData4f(ecx, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x1696d0 */
void FUN_001696d0(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1696fd */
  display_assert((char *)0x0026184c, (char *)0x002a2ca0, 323, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x169726 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 324, 0);
  system_exit(0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1010101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae8] = 0xc0000000 */
  /* mem[0x005a5ac0] = 0x19110000 */
  /* mem[0x005a5b28] = 0x100c0 */
  /* mem[0x005a5ae0] = 0x18 */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00158140(0, 0, 0, 0, 0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);

  (void)eax;
  (void)esi;
}

/* 0x169a50 */
void FUN_00169a50(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x169a69 */
  /* cmp (int16_t)edi, 8 -> jl 0x169a89 */
  display_assert((char *)0x002a3090, (char *)0x002a2ca0, 427, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x169a97 */
  /* cmp (int16_t)esi, 8 -> jl 0x169ab7 */
  display_assert((char *)0x002a3048, (char *)0x002a2ca0, 428, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x169ae0 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 429, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x169fb2 */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x304 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5ae8] = 0xff000000 */
  /* mem[0x005a5ac0] = 0x8a009a0 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0xaa00ba0 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0x1c110c11 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ae0] = 0xc */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x169d50 */
  FUN_00158140(0, 0, 0, 0, 0);
  /* mem[0x005a5ae8] = edx */
  rasterizer_set_pixel_shader((void *)0);
  D3DDevice_Begin(0);
  /* test (char)eax, (char)eax -> je 0x169e00 */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169e24 */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169e4e */
  FUN_00167ff0(0, (char *)0x002a2f48);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169e72 */
  FUN_00167ff0(0, (char *)0x002a2f04);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169e9c */
  FUN_00167ff0(0, (char *)0x002a2e88);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169ec0 */
  FUN_00167ff0(0, (char *)0x002a2e44);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169eea */
  FUN_00167ff0(0, (char *)0x002a2dc8);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x169f0e */
  FUN_00167ff0(0, (char *)0x002a2d84);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x169f38 */
  FUN_00167ff0(0, (char *)0x002a2d08);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x169f58 */
  FUN_00167ff0(0, (char *)0x0029f728);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);
  /* test (char)eax, (char)eax -> jne 0x169fb2 */
  error(0, (char *)0x002a2cd8);

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x169fd0 */
void FUN_00169fd0(int *param_1)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16a002 */
  display_assert((char *)0x0029dc40, (char *)0x002a2ca0, 583, 0);
  system_exit(0);
  normalize3d((float *)0);
  /* relift: relift: fld qword ptr [0x25b3f0] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16a0a0 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  FUN_0017ffc0((float *)(uintptr_t)eax, edx);
  FUN_00169200();
  /* test (char)eax, (char)eax -> je 0x16a8ec */
  floor(0.0f);
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x282d3c] */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  /* test (char)eax, 0x41 -> jne 0x16a8ec */
  FUN_00178b40(56, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5b6c] = ebx */
  /* mem[0x005a5ae4] = 0x1100 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2f(ebx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();
  FUN_00178b40(56, 0, 0);
  rasterizer_set_texture_direct(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x1000000 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 0 */
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ac0] = 0x18200000 */
  /* mem[0x005a5b28] = 0x200c0 */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_End();
  FUN_001696d0();
  FUN_001696d0();
  FUN_00169a50();
  FUN_00178b40(56, 0, 0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(2305);
  SetRenderStateSmart(67, 0x00010101);
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 770);
  SetRenderStateSmart(63, 0);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  D3DDevice_SetRenderState_ZBias(0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 1 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5ae8] = 0xb0b080 */
  /* mem[0x005a5b08] = 0xffffff */
  /* mem[0x005a5ac0] = 0x48200000 */
  /* mem[0x005a5b28] = 0xc0 */
  /* mem[0x005a5b4c] = 0x3c011c02 */
  /* mem[0x005a5b78] = 0xc00 */
  /* mem[0x005a5ae0] = 0xc080000 */
  /* mem[0x005a5ae4] = 0x1400 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_Begin(0);
  /* test (char)ebx, (char)ebx -> je 0x16a717 */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a74b */
  FUN_00167ff0(0, (char *)0x002a3280);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a76f */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a7a9 */
  FUN_00167ff0(0, (char *)0x002a3220);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a7cd */
  FUN_00167ff0(0, (char *)0x002a2f04);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a7fb */
  FUN_00167ff0(0, (char *)0x002a31c0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a81f */
  FUN_00167ff0(0, (char *)0x002a2e44);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a84d */
  FUN_00167ff0(0, (char *)0x002a3160);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x16a871 */
  FUN_00167ff0(0, (char *)0x002a2d84);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x16a896 */
  FUN_00167ff0(0, (char *)0x002a3100);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x16a8b4 */
  FUN_00167ff0(0, (char *)0x0029f728);
  error(0, (char *)0x002a30d4);
  /* cmp esi, 0x52 -> jge 0x16a91b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16a929 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16a93e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16a94a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16a956 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16a962 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16a96e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16a97a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16a986 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16a992 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16a99e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16a9aa */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16a9b6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16a9c5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16a9d4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16a9e3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16a9f2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16aa01 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16aa10 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16aa1f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16aa2e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16aa3d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16aa4c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x16aa5b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x16aa6a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x16aa79 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x16aa88 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16aa97 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16aaa5 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16aabc */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16aac9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x16aad6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16aae3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x16aaf0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x16ab00 */
void FUN_0016ab00(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)edi, 3 -> jl 0x16ab35 */
  display_assert((char *)0x002a3330, (char *)0x002a3380, 106, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x16ab40 */
  /* cmp (int16_t)ebx, 9 -> jl 0x16ab5d */
  display_assert((char *)0x002a32e8, (char *)0x002a3380, 107, 0);
  system_exit(0);
  /* mem[0x005a5af0] = eax */
  /* mem[0x005a5aec] = esi */
  /* mem[0x005a5b54] = edx */
  /* mem[0x005a5b60] = 0x8040b1d */
  /* mem[0x005a5b8c] = ecx */
  /* mem[0x005a5b64] = eax */
  /* mem[0x005a5b60] = ecx */
  /* mem[0x005a5b8c] = 0x800 */
  /* mem[0x005a5b64] = 0x8040b1d */
  /* mem[0x005a5b90] = ecx */
  /* mem[0x005a5ae0] = 0x330c0300 */
  /* mem[0x005a5ae4] = 0x1800 */
  /* mem[0x005a5afc] = edx */
  /* mem[0x005a5b1c] = eax */
  /* mem[0x005a5b6c] = edx */
  /* mem[0x005a5b70] = eax */
  /* mem[0x005a5ae0] = 0x340f010d */
  /* mem[0x005a5ae4] = 0xc111800 */
  /* relift: relift: mov (char)eax, byte ptr [0x325173] */
  /* test (char)eax, (char)eax -> je 0x16ada3 */
  /* mem[0x005a5b98] = 0x18421 */
  /* mem[0x005a5b94] = 0x11008 */
  /* mem[0x005a5ae8] = 0xff0000 */
  /* mem[0x005a5b08] = 0xff00 */
  /* mem[0x005a5ac0] = 0xa200000 */
  /* mem[0x005a5b28] = 0xc0 */
  /* mem[0x005a5b48] = 0xa020a01 */
  /* mem[0x005a5b74] = 0x30cd */
  /* mem[0x005a5ac4] = 0x1c200000 */
  /* mem[0x005a5b2c] = 0x90 */
  /* mem[0x005a5b4c] = 0x4200c01 */
  /* mem[0x005a5b78] = 0x400 */
  /* mem[0x005a5ac8] = 0xc200d15 */
  /* mem[0x005a5b30] = 0xcd */
  /* mem[0x005a5b50] = 0x3c201c01 */
  /* mem[0x005a5b7c] = ecx */
  /* mem[0x005a5b80] = 0x900 */
  /* mem[0x005a5b58] = 0xb05040c */
  /* mem[0x005a5b84] = 0xb4 */
  /* mem[0x005a5b5c] = 0x22014e1 */
  /* mem[0x005a5b88] = 0xd00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov byte ptr [0x325173], 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6c8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6d4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6f4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb72c] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb738] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb764] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb73c] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb768] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb744] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb748] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6b8] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = esi */
  /* cmp esi, 0x52 -> jge 0x16af0f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16af22 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16af3f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16af4f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16af5f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16af6f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16af7f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16af8f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16af9f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16afaf */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16afbf */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16afcf */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16afdf */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16aff2 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16b005 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16b018 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16b02b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16b03e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16b051 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16b064 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16b077 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x16b08a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x16b09d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x16b0b0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x16b0c3 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x16b0d6 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x16b0e9 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x16b0fc */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x16b10a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x16b120 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x16b131 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x16b142 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x16b153 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x16b160 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x16b180 */
void FUN_0016b180(void)
{
  int eax = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16b1b5 */
  /* relift: relift: mov byte ptr [0x325173], 1 */
  /* relift: relift: mov byte ptr [0x47e002], (char)eax */
  FUN_0016f910(0);
  FUN_0016f910(0);

  (void)eax;
}

/* 0x16b1c0 */
void FUN_0016b1c0(void)
{
  int eax = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16b230 */
  /* test eax, eax -> jne 0x16b1f2 */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 1491, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x47e004] */
  /* test (char)eax, (char)eax -> je 0x16b200 */
  FUN_00165fc0();
  /* relift: relift: mov (char)eax, byte ptr [0x47e005] */
  /* test (char)eax, (char)eax -> jne 0x16b226 */
  FUN_00158ae0(0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  /* mem[0x0047dff8] = 0 */

  (void)eax;
}

/* 0x16b240 */
void FUN_0016b240(void)
{
  int eax = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16b265 */
  /* relift: relift: mov (char)eax, byte ptr [0x47e002] */
  /* test (char)eax, (char)eax -> je 0x16b25d */
  FUN_0016fa40(0);
  FUN_0016fa40(0);

  (void)eax;
}

/* 0x16b270 */
void FUN_0016b270(int a0, float a1, float a2, float a3)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x16b2b0 */
void FUN_0016b2b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a3380, 245, ebx);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16beca */
  /* test eax, eax -> jne 0x16b31c */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 251, ebx);
  system_exit(0);
  display_assert((char *)0x002a18b8, (char *)0x002a3380, 252, ebx);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x16b543 */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(ebx, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [esi + 0x28], 4 -> jne 0x16b65b */
  /* relift: relift: mov (char)eax, byte ptr [0x47e003] */
  /* test (char)eax, (char)eax -> je 0x16b637 */
  /* relift: cmp word ptr [eax + 0x50], 0 -> jle 0x16b647 */
  /* relift: cmp dword ptr [esi + 0x330], -1 -> jne 0x16b65b */
  /* test ebx, ebx -> je 0x16b66c */
  rasterizer_widget_draw_sprite2d(0);
  FUN_00178b40(10, 0, 0);
  /* relift: cmp word ptr [0x3256ba], 1 -> jl 0x16b69e */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x5a5dbc] */
  /* test (char)eax, 0x41 -> je 0x16b7d1 */
  display_assert((char *)0x002a3538, (char *)0x002a3380, 436, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b804 */
  display_assert((char *)0x002a1e14, (char *)0x002a3380, 437, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5de8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b837 */
  display_assert((char *)0x0029f040, (char *)0x002a3380, 438, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5dec] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x16b86a */
  display_assert((char *)0x0029f008, (char *)0x002a3380, 439, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d4] */
  /* test (char)eax, (char)eax -> je 0x16bd8f */
  /* relift: test byte ptr [ecx], 4 -> jne 0x16bd8f */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16b8e6 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fld dword ptr [0x5a5dc0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16b945 */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: mov (char)eax, byte ptr [0x5a5da8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x5a5dd8] */
  /* relift: relift: fld dword ptr [0x5a5ddc] */
  /* relift: relift: fld dword ptr [0x5a5de0] */
  /* test (char)eax, 0x41 -> jne 0x16ba04 */
  /* test (char)eax, 0x41 -> jne 0x16ba3c */
  /* test (char)eax, 0x41 -> jne 0x16ba74 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16baa7 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16bad7 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x16bb07 */
  /* relift: relift: fld dword ptr [0x5a5dac] */
  /* relift: relift: fld dword ptr [0x5a5db0] */
  /* relift: relift: fld dword ptr [0x5a5db4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bb4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a3510, (char *)0x002a3380, 478, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bb8b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34ec, (char *)0x002a3380, 479, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bbcb */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34c8, (char *)0x002a3380, 480, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc0b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a34a4, (char *)0x002a3380, 481, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a3480, (char *)0x002a3380, 482, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bc8b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a345c, (char *)0x002a3380, 483, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bccb */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a342c, (char *)0x002a3380, 484, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bd0b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a33fc, (char *)0x002a3380, 485, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x16bd4b */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002a33cc, (char *)0x002a3380, 486, 0);
  system_exit(0);
  FUN_000d1c90((float *)(uintptr_t)edx);
  FUN_000d1dd0((float *)(uintptr_t)eax);
  FUN_000d1dd0((float *)(uintptr_t)ecx);
  FUN_0016ab00();
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb720] = 0xa021819 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb74c] = 0x20cd */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = 0xc111a00 */
  FUN_0015e650();
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb720] = 0xa020a01 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb74c] = 0x30cd */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb6bc] = 0xc111800 */
  /* mem[0x005a555c] = eax */
  /* mem[0x005a54e0] = edx */
  /* mem[0x005a54dc] = ecx */
  FUN_0017ed90();
  /* mem[0x005a54d8] = ecx */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x16bed0 */
void FUN_0016bed0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16c080 */
  /* test edi, edi -> jne 0x16bf08 */
  display_assert((char *)0x0029f510, (char *)0x002a3380, 587, 0);
  system_exit(0);
  /* test (char)ebx, (char)ebx -> jne 0x16bf31 */
  FUN_00158ae0(0);
  rasterizer_set_frustum_z(0.0f, 0.0f);
  /* relift: relift: mov (char)eax, byte ptr [0x3256f9] */
  /* mem[0x0047dff8] = edi */
  /* relift: relift: mov byte ptr [0x47dffc], 0 */
  /* relift: relift: mov byte ptr [0x47e005], (char)ebx */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x16bf81 */
  /* relift: cmp word ptr [edi + 0x8c], (int16_t)ecx -> jne 0x16bf81 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16bf81 */
  /* relift: relift: mov word ptr [0x47e000], (int16_t)ecx */
  /* relift: cmp word ptr [edi + 0x8c], (int16_t)eax -> jne 0x16bf97 */
  /* relift: relift: mov word ptr [0x47e000], (int16_t)eax */
  rasterizer_set_model_skinning((void *)(uintptr_t)edx);
  rasterizer_set_model_lighting((void *)(uintptr_t)eax);
  /* mem[0x005a5560] = eax */
  /* mem[0x005a5564] = eax */
  /* relift: relift: mov word ptr [0x47e000], 0 */
  /* test (char)eax, 4 -> jne 0x16c044 */
  /* test (char)eax, 0x40 -> je 0x16c03b */
  /* relift: relift: fld dword ptr [0x5a5dd0] */
  /* relift: relift: fld dword ptr [0x5a5dcc] */
  /* relift: relift: fld dword ptr [0x5a5dc8] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: mov byte ptr [0x47e003], 1 */
  /* relift: relift: mov byte ptr [0x47e003], 0 */
  /* relift: relift: mov (char)eax, byte ptr [0x47e002] */
  /* test (char)eax, (char)eax -> jne 0x16c068 */
  FUN_00167ee0();
  /* relift: relift: mov byte ptr [0x47e004], 1 */
  /* relift: relift: mov byte ptr [0x47e004], 0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x16c090 */
void FUN_0016c090(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* relift: relift: mov (char)eax, byte ptr [0x3256c5] */
  /* test (char)eax, (char)eax -> je 0x16c58e */
  /* test edi, edi -> je 0x16c0dd */
  /* relift: cmp word ptr [edi + 0x24], 4 -> jne 0x16c0dd */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* test (char)ecx, 8 -> je 0x16c0dd */
  /* relift: cmp word ptr [0x47e000], 1 -> jne 0x16c10c */
  /* test edi, edi -> je 0x16c106 */
  /* relift: cmp word ptr [edi + 0x24], 4 -> jne 0x16c106 */
  FUN_001906b0((void *)(uintptr_t)edi, 0);
  /* relift: cmp word ptr [eax + 0x28], 0 -> jne 0x16c10c */
  /* test (char)ebx, (char)ebx -> jne 0x16c56b */
  /* test edi, edi -> jne 0x16c13c */
  display_assert((char *)0x002a18b8, (char *)0x002a3380, 1301, 0);
  system_exit(0);
  shader_type_is_valid_for_model();
  /* test (char)eax, (char)eax -> jne 0x16c16f */
  display_assert((char *)0x002a3618, (char *)0x002a3380, 1302, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16c196 */
  display_assert((char *)0x002a1774, (char *)0x002a3380, 1303, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16c1bf */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 1304, 0);
  system_exit(0);
  shader_is_decal((void *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> je 0x16c1e4 */
  /* test (char)ebx, 2 -> je 0x16c1fa */
  /* mem[0x0047dfe8] = 0xffffffff */
  /* relift: cmp word ptr [0x47e000], 1 -> jne 0x16c212 */
  /* relift: cmp word ptr [edi + 0x24], 4 -> je 0x16c212 */
  rasterizer_secondary_geometry_group_new();
  rasterizer_transparent_geometry_group_new();
  rasterizer_transparent_geometry_group_to_presorted_index(ebx);
  /* test ebx, ebx -> je 0x16c542 */
  /* test ecx, ecx -> jne 0x16c2d5 */
  display_assert((char *)0x002a35e8, (char *)0x002a3380, 1356, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: cmp word ptr [edx + 0x24], 4 -> je 0x16c408 */
  display_assert((char *)0x002a35ac, (char *)0x002a3380, 1389, 0);
  system_exit(0);
  /* relift: relift: mov (char)ecx, byte ptr [0x5a5570] */
  /* relift: test byte ptr [ebp - 0xc], 2 -> je 0x16c45c */
  FUN_00174ce0();
  rasterizer_transparent_geometry_group_draw((void *)(uintptr_t)ebx, 0);
  FUN_001749b0();
  /* relift: relift: mov byte ptr [0x325173], 1 */
  /* relift: relift: mov (char)ecx, byte ptr [0x47dffc] */
  /* test (char)ecx, (char)ecx -> jne 0x16c4bf */
  rasterizer_memory_pool_copy(0, 0);
  /* mem[0x0047df54] = eax */
  /* relift: relift: mov word ptr [0x47df50], (int16_t)ecx */
  rasterizer_memory_pool_copy(0, 116);
  /* mem[0x0047df4c] = eax */
  rasterizer_memory_pool_copy(0, 0);
  /* mem[0x0047df48] = eax */
  /* relift: relift: mov byte ptr [0x47dffc], 1 */
  /* relift: relift: mov (int16_t)ecx, word ptr [0x47df50] */
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x16c538 */
  /* mem[0x005a54f0] = esi */
  /* mem[0x005a54e8] = edx */
  /* mem[0x005a54ec] = eax */
  FUN_0017ed90();
  /* mem[0x005a54e4] = ecx */
  /* relift: relift: mov (char)eax, byte ptr [0x47e006] */
  /* test (char)eax, (char)eax -> jne 0x16c538 */
  error(0, (char *)0x002a1744);
  /* relift: relift: mov byte ptr [0x47e006], 1 */
  /* test eax, eax -> je 0x16c585 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x16c5a0 */
void FUN_0016c5a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x16c5d2 */
  display_assert((char *)0x0029dc40, (char *)0x002a3380, 671, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256c4] */
  /* test (char)eax, (char)eax -> je 0x16d9c9 */
  /* test eax, eax -> jne 0x16c608 */
  display_assert((char *)0x002a33b8, (char *)0x002a3380, 675, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16c62f */
  display_assert((char *)0x002a18b8, (char *)0x002a3380, 676, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax + 0x24], 0xa -> jne 0x16c694 */
  FUN_001906b0((void *)(uintptr_t)eax, 10);
  /* cmp (int16_t)eax, 1 -> jl 0x16c694 */
  /* cmp (int16_t)eax, 4 -> jg 0x16c694 */
  /* test ecx, ecx -> je 0x16c694 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0016c090();
  /* test esi, esi -> je 0x16c6e1 */
  rasterizer_memory_pool_alloc(0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x47e000] */
  /* cmp (int16_t)eax, 1 -> jne 0x16c74f */
  /* relift: cmp word ptr [esi + 0x24], 4 -> je 0x16c717 */
  display_assert((char *)0x002a3974, (char *)0x002a3380, 729, 0);
  system_exit(0);
  FUN_0017cbd0(0, 0, 0, 0, 0, 0, 0, (float *)(uintptr_t)ecx, 0);
  FUN_001592e0(0);
  /* test (int16_t)eax, (int16_t)eax -> jne 0x16d9b3 */
  /* relift: cmp word ptr [eax + 0x24], 3 -> jne 0x16c788 */
  FUN_0016b2b0();
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  /* relift: cmp word ptr [0x47e000], 0 -> je 0x16c7cb */
  display_assert((char *)0x002a393c, (char *)0x002a3380, 771, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x16c880 */
  /* relift: test byte ptr [ecx], 8 -> je 0x16c885 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_ZBias(edx);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  /* relift: test byte ptr [esi + 0x28], 4 -> jne 0x16c968 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = 0x7f */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
