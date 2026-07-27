/* kb object stubs -> xdk/xnet/wsock.c */

/* --- XNET:wsock.obj batch drafts (2026-07-26) --- */

/* 0x222df7 */
int FUN_00222df7(void *key)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int lift_a1 = 0;

  /* test ecx, ecx -> jne 0x222e09 */
  /* test ecx, ecx -> jne 0x222e1f */
  /* relift: FUN_002262c4(0, 0); */
  /* test ecx, ecx -> jne 0x222e43 */
  /* cmp eax, 0xa -> jb 0x222e8c */
  /* cmp eax, 0x64 -> jb 0x222e7e */
  /* cmp esi, eax -> jb 0x222e62 */
  /* cmp ebx, 0x10 -> jae 0x222ec6 */
  /* test ebx, ebx -> jle 0x222ec6 */
  /* test ecx, ecx -> jne 0x222edf */
  /* test ecx, ecx -> jne 0x222ef4 */
  /* test edx, edx -> je 0x222f48 */
  /* relift: cmp dword ptr [esp + 4], 0 -> je 0x222f5a */
  /* relift: FUN_0024ba93(0, 0, 0, 0x00222f6c); */
  /* test edx, edx -> je 0x222fcf */
  /* relift: cmp dword ptr [esp + 4], 0 -> je 0x222fe1 */
  /* test ecx, ecx -> jne 0x223036 */
  /* relift: FUN_0024ba93(0, 24, 64, 0x00222f79); */
  /* relift: FUN_0024ba93(0, 24, 64, 0x00222f79); */
  /* relift: FUN_0024ba93(0, 0, 0, 0x00222f6c); */
  /* relift: FUN_0024ba93(0, 24, 64, 0x00222f79); */
  /* relift: FUN_0024ba93(0, 0, 0, 0x00222f6c); */
  /* cmp eax, ebx -> je 0x22310e */
  FUN_001d0362();
  /* cmp eax, ebx -> jne 0x2231bb */
  /* cmp esi, ebx -> je 0x223176 */
  /* relift: FUN_0024ba93(0, 24); */
  /* relift: FUN_0024ba93(0, 0, 0, 0x00222f6c); */
  /* mem[0x004ee4b0] = ecx */
  /* relift: FUN_00223676(0); */
  /* cmp esi, ebx -> jge 0x2231ad */
  /* relift: FUN_00225c89(0, 0); */
  /* mem[0x004ee4b0] = ebx */
  /* relift: FUN_00228a69(0, 0); */
  /* cmp eax, ebx -> je 0x2231ce */
  /* relift: cmp dword ptr [ebp + 0xc], ebx -> je 0x2231c8 */
  /* mem[0x004ee4b4] = ebx */
  /* test esi, esi -> je 0x2231f2 */
  /* relift: FUN_002230e5(0, 0); */
  /* relift: FUN_002230e5(0, 0, 0); */
  /* cmp eax, ebx -> jne 0x223244 */
  /* cmp eax, esi -> je 0x22326c */
  FUN_001d0362();
  /* cmp eax, esi -> je 0x2232a4 */
  /* relift: cmp dword ptr [esp + 0xc], esi -> je 0x22329c */
  /* relift: cmp dword ptr [ecx], esi -> je 0x2232a4 */
  /* relift: cmp dword ptr [eax + 0x964], esi -> jne 0x2232bc */
  /* relift: FUN_00225ad7(0, 0); */
  /* relift: cmp dword ptr [eax + 0x960], esi -> jne 0x2232b6 */
  /* mem[0x004ee4b4] = esi */
  /* relift: FUN_00225c89(0, 0); */
  /* cmp eax, esi -> je 0x2232e5 */
  /* mem[0x004ee4b0] = esi */
  /* relift: FUN_00223248(0); */
  /* relift: FUN_00223248(0); */
  /* test eax, eax -> je 0x223309 */
  SetLastError(eax);
  /* test eax, eax -> je 0x2233b3 */
  /* test ecx, ecx -> je 0x2233b3 */
  /* cmp ecx, 0xffff -> ja 0x2233b3 */
  /* relift: cmp dword ptr [eax], 0 -> je 0x2233a7 */
  /* relift: cmp dword ptr [eax + 4], 0 -> je 0x2233b3 */
  /* test ecx, ecx -> jne 0x22339b */
  /* test edx, edx -> je 0x2233ce */
  /* relift: cmp byte ptr [eax], 0x20 -> je 0x2233e0 */
  /* cmp edi, 4 -> jae 0x2234ac */
  /* test (char)ecx, (char)ecx -> je 0x2234b9 */
  /* cmp (char)ecx, 0x30 -> jne 0x223473 */
  /* cmp dl, 0x78 -> je 0x22340d */
  /* cmp dl, 0x58 -> jne 0x22345d */
  /* cmp (char)ecx, 0x30 -> jb 0x22342a */
  /* cmp (char)ecx, 0x39 -> ja 0x22342a */
  /* cmp (char)ecx, 0x61 -> jb 0x223440 */
  /* cmp (char)ecx, 0x66 -> ja 0x223440 */
  /* cmp (char)ecx, 0x41 -> jb 0x223457 */
  /* cmp (char)ecx, 0x46 -> ja 0x223457 */
  /* cmp edx, eax -> je 0x2234b1 */
  /* cmp (char)ecx, 0x30 -> jb 0x223497 */
  /* cmp (char)ecx, 0x37 -> jbe 0x22345d */
  /* cmp (char)ecx, 0x31 -> jb 0x2234ac */
  /* cmp (char)ecx, 0x39 -> ja 0x2234ac */
  /* cmp (char)ecx, 0x30 -> jb 0x223497 */
  /* cmp (char)ecx, 0x39 -> jbe 0x22347d */
  /* relift: cmp byte ptr [eax], 0x20 -> je 0x223496 */
  /* relift: cmp byte ptr [eax], 0x2e -> jne 0x2234a2 */
  /* relift: cmp byte ptr [eax], 0 -> je 0x2234b9 */
  CreateEventA((void *)(uintptr_t)eax, 0, 0, (char *)(uintptr_t)eax);
  /* relift: cmp edx, dword ptr [esp + 4] -> je 0x223619 */
  /* test eax, eax -> jne 0x223604 */
  /* test esi, esi -> je 0x223664 */
  /* cmp esi, -1 -> je 0x223664 */
  /* cmp eax, 0x2b434f53 -> jne 0x22364f */
  SetLastError(eax);
  /* relift: FUN_0022724d(0, 0); */
  /* test eax, eax -> jl 0x2236ba */
  /* relift: FUN_0022955c(0x02000000); */
  /* cmp eax, esi -> jne 0x2236c8 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> je 0x22371b */
  /* test eax, eax -> jne 0x22371b */
  __allmul();
  /* relift: FUN_002236be(0, 0); */
  /* relift: FUN_002236be(0); */
  /* relift: FUN_002236be(0); */
  /* test eax, eax -> jne 0x223919 */
  /* relift: test byte ptr [ecx + 0xc], 2 -> jne 0x223972 */
  /* relift: FUN_0022a8d5(0, 0); */
  /* test eax, eax -> je 0x223a51 */
  /* relift: FUN_00226412(0); */
  /* relift: FUN_00226045(0); */
  /* relift: cmp dword ptr [esi], esi -> jne 0x223b29 */
  /* test edi, edi -> je 0x223b5b */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x223b6a */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x223b7f */
  /* relift: FUN_0022c3f4(0, 0); */
  /* test (char)eax, 0x20 -> jne 0x223bb3 */
  /* relift: FUN_0022b513(0, 0, 0); */
  /* test eax, eax -> jl 0x223bc6 */
  SetLastError(eax);
  /* cmp ecx, ebx -> je 0x223bf9 */
  /* relift: cmp dword ptr [ecx + 0x964], ebx -> jg 0x223c0b */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* cmp esi, ebx -> jne 0x223c22 */
  /* relift: cmp dword ptr [ebp + 0xc], 0x8004667e -> je 0x223c72 */
  /* relift: cmp dword ptr [ebp + 0xc], 0x4004667f -> je 0x223c3b */
  /* relift: test byte ptr [esi + 0xc], 2 -> jne 0x223c5f */
  /* cmp edi, edx -> jne 0x223c55 */
  /* test edx, edx -> jne 0x223c62 */
  /* relift: FUN_002236be(0xfffdffff, 0); */
  SetLastError(ebx);
  /* cmp esi, eax -> jle 0x223cc3 */
  /* test esi, esi -> jg 0x223cca */
  /* cmp edx, eax -> jle 0x223cdd */
  /* test edx, edx -> jg 0x223ce3 */
  /* relift: cmp byte ptr [ecx + 0x7c], 1 -> jbe 0x223d04 */
  /* relift: cmp edx, dword ptr [ecx + 0x5c] -> jge 0x223d04 */
  /* test ecx, ecx -> je 0x223d6c */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jle 0x223d6c */
  /* relift: FUN_0022361e(0, 0); */
  /* test edx, edx -> je 0x223dec */
  /* relift: cmp dword ptr [ebp + 0xc], 0xffff -> je 0x223d73 */
  /* cmp ecx, eax -> jg 0x223e40 */
  /* cmp ecx, 0xffffff7f -> je 0x223e27 */
  /* cmp ecx, -5 -> je 0x223e1f */
  /* cmp ecx, ebx -> je 0x223e12 */
  /* cmp ecx, edi -> je 0x223e07 */
  /* cmp ecx, 0x20 -> je 0x223df4 */
  /* cmp ecx, 0x80 -> jne 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], (char)ebx -> je 0x223e8d */
  SetLastError(0);
  /* test (char)ebx, (char)eax -> jne 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], (char)ebx -> je 0x223e8d */
  /* relift: test byte ptr [edx + 0xc], 2 -> je 0x223e8d */
  /* test (char)eax, 2 -> je 0x223e8d */
  /* relift: cmp dword ptr [esi], edi -> jae 0x223dc9 */
  /* test ecx, ecx -> je 0x223eca */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x223ed1 */
  /* relift: FUN_0022361e(0); */
  /* test edx, edx -> je 0x223f29 */
  /* relift: test byte ptr [edx + 0xc], 0x10 -> jne 0x223eed */
  SetLastError(eax);
  /* test ecx, ecx -> je 0x223f40 */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x223f47 */
  /* relift: FUN_0022361e(0); */
  /* test edx, edx -> je 0x223fa0 */
  /* relift: test byte ptr [edx + 0xc], 0x20 -> jne 0x223f63 */
  SetLastError(eax);
  /* test eax, eax -> jle 0x22401f */
  /* relift: cmp dword ptr [eax], 0x1387 -> jb 0x224013 */
  /* test esi, esi -> je 0x2240ab */
  /* test (char)eax, 0x10 -> je 0x22406b */
  /* test (char)ecx, 1 -> jne 0x224068 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + 0xc] -> jne 0x224068 */
  /* test ecx, eax -> jne 0x224083 */
  /* test ecx, edi -> jne 0x224083 */
  /* test edi, 0x40000 -> je 0x224083 */
  /* test esi, esi -> je 0x2240ab */
  /* relift: cmp dword ptr [ebp - 4], 0 -> jg 0x223ff3 */
  /* relift: FUN_002236be(0, 16); */
  /* test edi, edi -> je 0x2240d3 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2240e2 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2240f7 */
  /* test (char)eax, 0x20 -> je 0x224105 */
  /* test (char)eax, 0x10 -> jne 0x224110 */
  /* relift: FUN_0022a590(0, 0); */
  /* test eax, eax -> jl 0x224124 */
  SetLastError(eax);
  /* test edx, edx -> je 0x22415e */
  /* relift: cmp dword ptr [ebx], eax -> je 0x2241c4 */
  /* relift: cmp edx, dword ptr [ebp + 0x10] -> jl 0x2241b3 */
  /* relift: cmp edx, dword ptr [ebp + 0x10] -> jne 0x2241e6 */
  /* relift: FUN_0022361e(0); */
  xapi_GetLastError();
  /* relift: cmp eax, dword ptr [ebp - 0x10] -> jl 0x224194 */
  /* test (char)eax, 2 -> je 0x2242d2 */
  /* relift: cmp dword ptr [esi + 0x40], 0 -> jge 0x22425e */
  /* cmp ebx, ecx -> jne 0x224257 */
  /* relift: FUN_0022a8d5(0, 0); */
  /* test (char)ecx, 0x20 -> je 0x2242f3 */
  /* relift: cmp eax, dword ptr [esi + 0x58] -> jae 0x2242ad */
  /* test eax, ebx -> je 0x2242f3 */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> jl 0x2242f3 */
  /* relift: FUN_002236be(0, 128); */
  /* relift: cmp dword ptr [ebp + 0x10], 0 -> je 0x224314 */
  /* relift: FUN_002236be(0xffff03ff, 0); */
  /* relift: FUN_00224223(0, lift_a1, 0, 0); */
  /* test eax, eax -> je 0x224347 */
  __allmul();
  /* relift: FUN_002236be(0, 0); */
  /* test esi, esi -> jl 0x22439e */
  /* relift: cmp edx, dword ptr [ebp + 0x14] -> jne 0x224415 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 8] -> jne 0x224415 */
  /* relift: cmp edx, dword ptr [ebp + 0xc] -> je 0x2243f9 */
  /* test edx, edx -> jne 0x224415 */
  /* relift: cmp (int16_t)edx, word ptr [ebp + 0x10] -> je 0x224409 */
  /* test (int16_t)edx, (int16_t)edx -> jne 0x224415 */
  /* test edi, edi -> je 0x224427 */
  /* cmp edi, ebx -> jae 0x224415 */
  /* test edx, edx -> je 0x224464 */
  /* relift: cmp dword ptr [esp + 4], 0 -> je 0x224476 */
  /* cmp (char)ecx, 0xe0 -> jne 0x224490 */
  /* cmp eax, -1 -> je 0x224490 */
  /* relift: cmp dword ptr [ecx + 0x968], edx -> jb 0x2244cf */
  /* relift: FUN_00226013(0, 0); */
  /* cmp edx, ebx -> je 0x2245fe */
  /* cmp edx, ebx -> je 0x2245fe */
  /* relift: cmp dword ptr [ebp + 8], ebx -> je 0x2245e7 */
  /* relift: FUN_00226045(0, 0); */
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jle 0x22466e */
  /* relift: FUN_0022361e(0, 0); */
  /* test edi, edi -> jne 0x224680 */
  SetLastError(10093);
  /* relift: cmp dword ptr [ebp + 0xc], 6 -> je 0x22480a */
  /* relift: cmp dword ptr [ebp + 0xc], 0xffff -> jne 0x224801 */
  /* cmp ecx, 0xffffff7f -> je 0x22477a */
  /* cmp ecx, -5 -> je 0x224755 */
  /* cmp ecx, 4 -> je 0x224737 */
  /* cmp ecx, 0x20 -> je 0x224711 */
  /* cmp ecx, 0x80 -> jne 0x2247ae */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x2247ae */
  /* relift: test byte ptr [edi + 0xc], 2 -> jne 0x2247ae */
  /* relift: FUN_002236be(0xfffeffff, 0); */
  /* relift: test dword ptr [edi + 0xc], eax -> je 0x224745 */
  /* test esi, esi -> jne 0x224763 */
  /* relift: test dword ptr [edi + 0xc], eax -> je 0x22476a */
  /* test esi, esi -> je 0x22476a */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x2247ae */
  /* relift: FUN_00223caf(0, *(int *)((char *)edi + 0x58), 0); */
  /* relift: test byte ptr [edi + 0xc], 2 -> je 0x224816 */
  /* relift: FUN_002236be(0xffefffff, 0); */
  SetLastError(0);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)lift_a1;
}

/* 0x22486b */
int xnet_getpeername(int socket, void *name, int *namelen)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x224876 */
int xnet_getsockname(int socket, void *name, int *namelen)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;
  int lift_a3 = 0;

  /* test edi, edi -> je 0x224892 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x224899 */
  /* relift: FUN_0022361e(0); */
  /* test esi, esi -> je 0x2248f8 */
  /* relift: test byte ptr [esi + 0xc], 0x10 -> je 0x2248b5 */
  /* relift: cmp dword ptr [ecx + 4], 0 -> je 0x2248c6 */
  /* relift: FUN_00223faa(0, 0); */
  /* test eax, eax -> jl 0x2248e0 */
  SetLastError(eax);
  /* cmp ebx, esi -> je 0x224919 */
  /* relift: cmp dword ptr [ebx + 0x964], esi -> jg 0x22492b */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* cmp edi, esi -> jne 0x224942 */
  /* test dl, 0x20 -> je 0x224956 */
  /* test dl, 2 -> je 0x224956 */
  /* relift: FUN_0022c6b8(0, 0, 0); */
  /* relift: FUN_0022bde3(0, 0); */
  /* test esi, esi -> jl 0x224997 */
  SetLastError(eax);
  /* relift: FUN_0022bde3(0, 0); */
  /* test esi, esi -> jl 0x224997 */
  /* relift: FUN_00224326(0, 8192, 0); */
  /* relift: FUN_002236be(0, 128); */
  /* test esi, esi -> jl 0x224997 */
  /* cmp edi, esi -> je 0x224a0c */
  /* relift: cmp dword ptr [edi + 0x964], esi -> jg 0x224a1e */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test ebx, ebx -> jne 0x224a35 */
  /* relift: test byte ptr [ebx + 0xc], 2 -> je 0x224adf */
  /* relift: cmp byte ptr [ebx + 0x7c], 1 -> jne 0x224adf */
  /* relift: FUN_0022a904(0, 0); */
  /* test esi, esi -> jne 0x224a84 */
  /* relift: test byte ptr [ebx + 0xe], 2 -> jne 0x224a8a */
  /* relift: FUN_00224326(0, 4096, 0); */
  /* test eax, eax -> je 0x224a49 */
  /* test eax, eax -> jl 0x224a93 */
  /* test esi, esi -> je 0x224ae6 */
  /* relift: FUN_002236be(0, 0x01000000); */
  /* test ecx, ecx -> je 0x224ae6 */
  /* test edx, edx -> je 0x224ae6 */
  SetLastError(0);
  /* relift: cmp dword ptr [ecx + 0x964], edi -> jg 0x224b42 */
  SetLastError(10093);
  /* cmp eax, edi -> je 0x224b6b */
  SetLastError(10022);
  /* cmp eax, 1 -> jne 0x224bba */
  /* test eax, eax -> je 0x224df4 */
  /* relift: FUN_00224145(name, 0, 0, 54272); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* relift: FUN_00224145(namelen, 0, 0, 10240); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* relift: FUN_00224145(lift_a3, 0, 0, 32768); */
  /* test ebx, ebx -> jne 0x224dfd */
  /* test esi, esi -> je 0x224d69 */
  __allmul();
  __allmul();
  /* relift: cmp dword ptr [ebp + 8], ebx -> jle 0x224cf6 */
  /* relift: FUN_00224223(0, 0, 0); */
  /* test eax, eax -> jne 0x224cf6 */
  /* relift: cmp eax, dword ptr [ebp + 8] -> jl 0x224cc5 */
  /* relift: cmp dword ptr [ebp + 0x18], eax -> jne 0x224d72 */
  /* cmp ebx, 3 -> jle 0x224d38 */
  /* test edx, edx -> je 0x224d2d */
  /* test eax, eax -> jl 0x224d58 */
  /* cmp eax, ebx -> jl 0x224d72 */
  /* cmp eax, 0x102 -> je 0x224d72 */
  /* cmp eax, ecx -> je 0x224d7d */
  /* cmp eax, ecx -> je 0x224d86 */
  /* cmp eax, ecx -> je 0x224d8f */
  /* relift: FUN_00224223(0, 0, 0); */
  /* test eax, eax -> je 0x224de8 */
  /* cmp edi, edx -> jae 0x224dd3 */
  /* relift: cmp dword ptr [ecx], ebx -> je 0x224dd1 */
  /* cmp edi, edx -> jb 0x224dc5 */
  /* cmp edi, edx -> jne 0x224de5 */
  /* cmp edx, 0x40 -> jae 0x224de5 */
  /* test eax, eax -> jle 0x224e36 */
  /* test edi, edi -> je 0x224e2e */
  /* relift: cmp dword ptr [esi], 0 -> je 0x224e2e */
  /* relift: FUN_002236be(0xffff03ff, 0); */
  /* relift: cmp dword ptr [ebp - 0x10], eax -> je 0x224e52 */
  /* relift: cmp dword ptr [ebp - 0x10], 0 -> je 0x224e52 */
  /* relift: cmp dword ptr [ebp - 4], eax -> je 0x224e65 */
  /* relift: cmp dword ptr [ebp - 4], 0 -> je 0x224e65 */
  /* relift: cmp dword ptr [ebp - 0xc], eax -> je 0x224e78 */
  /* relift: cmp dword ptr [ebp - 0xc], 0 -> je 0x224e78 */
  /* test ebx, ebx -> je 0x224e82 */
  /* relift: cmp dword ptr [ebx + 0x20], 0 -> je 0x224e9e */
  /* test eax, eax -> jne 0x224eb0 */
  /* cmp eax, ecx -> jne 0x224ebb */
  /* test eax, eax -> jne 0x224ed3 */
  /* relift: cmp eax, dword ptr [esi + 0x58] -> jae 0x224f31 */
  /* test eax, eax -> jne 0x224f5e */
  /* cmp esi, eax -> je 0x22501d */
  /* relift: cmp dword ptr [edi + 0x30], esi -> jne 0x224fe9 */
  /* relift: cmp dword ptr [edi + 0x20], esi -> jne 0x224ff1 */
  /* test edi, edi -> je 0x225031 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x225038 */
  /* relift: cmp dword ptr [esp + 8], 0 -> je 0x22504d */
  /* relift: cmp dword ptr [esp + 8], 2 -> je 0x22504d */
  /* test ecx, ecx -> je 0x225066 */
  /* cmp ecx, 1 -> je 0x225066 */
  /* cmp ecx, 2 -> je 0x225066 */
  /* test eax, eax -> je 0x225078 */
  /* cmp eax, 6 -> je 0x225078 */
  /* cmp eax, 0x11 -> jne 0x2250aa */
  /* test ecx, ecx -> jne 0x225083 */
  /* test eax, eax -> jne 0x225094 */
  /* cmp ecx, edx -> je 0x2250ba */
  SetLastError(eax);
  /* relift: FUN_00224493(0, 0, 0); */
  /* test esi, esi -> jne 0x2250da */
  SetLastError(10055);
  /* relift: FUN_002236be(0, 0x01000000); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x20), 0); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x30), 0); */
  /* relift: FUN_00223b1b(0); */
  /* relift: FUN_00223b00(0); */
  /* relift: cmp dword ptr [edi], edi -> jne 0x225150 */
  /* test eax, eax -> je 0x225182 */
  /* relift: FUN_002267c6(0); */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  (void)lift_a3;
}

/* 0x225197 */
int xnet_bind(int socket, void *name, int namelen)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test ebx, ebx -> je 0x2251da */
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x2251e4 */
  /* relift: FUN_0022361e(0); */
  /* relift: cmp dword ptr [esi + 0xc], edi -> jne 0x22524b */
  /* relift: cmp dword ptr [ebp + 0x14], 0 -> je 0x22524b */
  WaitForSingleObject(*(int *)((char *)esi + 0x10), 0);
  /* relift: FUN_00224fcf(0, 0, 0); */
  /* cmp eax, edi -> je 0x22526a */
  /* test eax, eax -> jl 0x225271 */
  SetLastError(eax);
  /* test ebp, ebp -> je 0x2252aa */
  /* relift: cmp dword ptr [ebp + 0x964], 0 -> jg 0x2252b9 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2252ce */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x20), 0); */
  /* relift: FUN_00224fcf(0, *(int *)((char *)esi + 0x30), 0); */
  /* test (char)eax, 0x20 -> jne 0x22533d */
  /* test (char)eax, 0x10 -> jne 0x22533d */
  /* test (char)eax, 8 -> je 0x225358 */
  /* test eax, eax -> je 0x225388 */
  /* test eax, eax -> jne 0x225388 */
  /* cmp eax, edx -> je 0x2253f8 */
  /* relift: cmp dword ptr [ebp + 8], edx -> je 0x2253ce */
  /* test ecx, 0x20000 -> je 0x2253ea */
  /* cmp esi, edx -> je 0x2253e0 */
  /* relift: cmp byte ptr [ebx + 0x7c], 7 -> jae 0x2253f8 */
  /* relift: FUN_0022c458(0, 0); */
  /* relift: FUN_0022af86(0, 0); */
  /* cmp esi, 0x800703e5 -> jne 0x225498 */
  /* relift: cmp dword ptr [ebp + 8], 0 -> jne 0x2254c4 */
  __allmul();
  /* relift: cmp dword ptr [ebp - 0x14], esi -> jne 0x225485 */
  /* relift: FUN_00224fcf(0, 0, 0x8007274c); */
  /* test eax, eax -> je 0x2254c4 */
  /* relift: cmp dword ptr [esi + 0x14], 0 -> jne 0x2254f3 */
  /* test (char)eax, 4 -> je 0x22550e */
  /* test eax, eax -> je 0x225544 */
  /* test eax, eax -> jne 0x225544 */
  /* relift: cmp eax, dword ptr [edi + 0x58] -> jb 0x225581 */
  /* test ebx, ebx -> je 0x225595 */
  /* relift: FUN_00224f01(0, 0); */
  /* cmp ebx, eax -> je 0x2255ef */
  /* test ebx, ebx -> jl 0x2255c6 */
  /* relift: FUN_0022c517(0, 0); */
  /* relift: test byte ptr [edi + 0xe], 2 -> jne 0x2255b8 */
  /* relift: cmp dword ptr [edi + 0x30], 0 -> jne 0x2255b8 */
  /* relift: FUN_00224326(0, 2048, *(int *)((char *)edi + 0x50)); */
  /* test eax, eax -> jge 0x225581 */
  /* relift: FUN_0022b612(0, 0); */
  /* cmp eax, ecx -> je 0x2255ed */
  /* relift: FUN_0022bd4e(0, name); */
  /* relift: FUN_002236be(0, 0x0400000c); */
  /* relift: FUN_00225114(0); */
  /* relift: test byte ptr [ecx + 0xf], 1 -> je 0x225689 */
  /* relift: FUN_002236be(0, 0x02000000); */
  /* relift: FUN_00224606(0); */
  /* test edi, edi -> je 0x2256d1 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2256e0 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2256f4 */
  /* relift: FUN_0022530d(0, 0); */
  /* test eax, eax -> jl 0x225728 */
  SetLastError(eax);
  /* test ebx, ebx -> je 0x225761 */
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x225770 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test edi, edi -> jne 0x225784 */
  /* relift: FUN_0022530d(0, 0, 0); */
  SetLastError(eax);
  /* relift: cmp dword ptr [ecx + 0x964], 0 -> jg 0x22580f */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test ebx, ebx -> jne 0x225823 */
  /* relift: FUN_0022530d(0, 0); */
  SetLastError(eax);
  /* test edi, edi -> je 0x2258ba */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x2258c9 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x2258dd */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x225914 */
  SetLastError(eax);
  /* test edi, edi -> je 0x22594d */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x22595c */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x225970 */
  /* relift: FUN_002233b8(0, 0); */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x2259ad */
  SetLastError(eax);
  /* relift: cmp dword ptr [ebx + 0x964], 0 -> jg 0x2259f1 */
  /* relift: FUN_0022361e(0); */
  /* test esi, esi -> je 0x225ac9 */
  /* relift: FUN_002233b8(0, 0); */
  /* test (char)ecx, 2 -> jne 0x225a91 */
  /* test edi, edi -> je 0x225a91 */
  /* test eax, eax -> je 0x225a8a */
  /* relift: cmp word ptr [edi + 2], 0 -> je 0x225a8a */
  /* cmp dl, 0xe0 -> jne 0x225a4e */
  /* cmp eax, -1 -> jne 0x225a8a */
  /* cmp (char)eax, 0x7f -> jne 0x225a59 */
  /* cmp eax, 0x100007f -> jne 0x225a8a */
  /* cmp eax, -1 -> jne 0x225a6d */
  /* test ecx, 0x10000 -> jne 0x225a6d */
  /* test (char)ecx, 0x10 -> jne 0x225a85 */
  /* relift: FUN_00223faa(0); */
  /* test eax, eax -> jl 0x225ab1 */
  /* relift: FUN_002254cd(0, 0); */
  /* test eax, eax -> jl 0x225ab1 */
  SetLastError(eax);
  /* relift: test byte ptr [edi + 3], 2 -> je 0x225b25 */
  /* relift: FUN_00225601(0, 0); */
  /* cmp eax, esi -> jne 0x225af2 */
  /* relift: FUN_00225601(0, 0); */
  /* cmp eax, esi -> jne 0x225b0a */
  /* test edi, edi -> je 0x225b37 */
  /* relift: cmp dword ptr [edi + 0x964], 0 -> jg 0x225b46 */
  SetLastError(10093);
  /* relift: FUN_0022361e(0, 0); */
  /* test esi, esi -> jne 0x225b5b */
  /* relift: FUN_00224606(0); */
  /* relift: FUN_002236be(0xfeffffff, 0); */
  /* relift: FUN_00225601(0, 0); */
  /* test eax, eax -> jge 0x225b72 */
  /* test eax, eax -> je 0x225b72 */
  SetLastError(eax);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* 0x2251ad */
int xnet_accept(int socket, void *addr, int *addrlen)
{
  (void)socket;
  (void)addr;
  (void)addrlen;
  return -1;
}

/* 0x225bb6 */
int xnet_recv(int socket, void *buf, int len, int flags)
{
  int eax = 0;

  /* relift: FUN_002257e7(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x225c0a */
  return 0;

  (void)eax;
}

/* 0x225c20 */
int xnet_send(int socket, const char *buf, int len, int flags)
{
  int eax = 0;

  /* relift: FUN_002259cf(0, 0, 0, 0); */
  /* test eax, eax -> jne 0x225c73 */
  /* relift: FUN_002297f4(0, 0); */
  /* relift: FUN_00225ad7(0, 0); */
  /* relift: FUN_0022955c(0x20000000); */
  /* relift: FUN_00227b03(0, 0); */
  return 0;

  (void)eax;
}

/* 0x225cc6 */
int xnet_closesocket(int socket)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x225cd1 */
int xnet_recvfrom(int socket, void *buf, int len, int flags, void *from, int *fromlen)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: cmp eax, dword ptr [esp + 8] -> je 0x225d50 */
  /* test eax, eax -> jne 0x225d3d */
  /* relift: cmp dword ptr [ecx + 4], eax -> jne 0x225d6a */
  /* test ecx, ecx -> jne 0x225d74 */
  /* cmp edi, edx -> je 0x225dd1 */
  /* relift: cmp esi, dword ptr [edi + 8] -> jbe 0x225dd1 */
  /* relift: cmp esi, dword ptr [ecx + 8] -> jb 0x225db9 */
  /* relift: cmp esi, dword ptr [eax + 8] -> jae 0x225dfd */
  /* relift: FUN_00225d7d(0, 0); */
  /* relift: cmp ebx, dword ptr [eax + 8] -> jb 0x225e3c */
  /* cmp eax, esi -> jne 0x225e1a */
  /* test edx, edx -> je 0x225e60 */
  /* test eax, eax -> je 0x225e7f */
  /* test (char)eax, (char)eax -> jne 0x225e7f */
  /* cmp eax, 5 -> ja 0x225f51 */
  /* relift: cmp dword ptr [ecx], ecx -> jne 0x225f65 */
  /* cmp eax, 5 -> jbe 0x225f44 */
  /* relift: cmp (int16_t)ebx, word ptr [esi + 4] -> jbe 0x225f6c */
  /* cmp eax, ecx -> jne 0x225fbc */
  /* relift: FUN_00225f13(0, 0); */
  /* test edx, edx -> je 0x226040 */
  /* relift: cmp byte ptr [edx + 1], (char)ebx -> jne 0x226090 */
  /* relift: cmp byte ptr [edx + 1], (char)ebx -> jne 0x2260b1 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x2260c5 */
  /* cmp (int16_t)eax, (int16_t)edx -> ja 0x2260d5 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}
