/* --- bink.obj batch drafts (2026-07-26) --- */

/* 0x22df80 */
int __stdcall BinkSoundUseDirectSound(void *dsound_proc, void *dsound_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;
  int ebp = 0;

  /* test ecx, ecx -> je 0x22df9e */
  /* test eax, eax -> je 0x22dfa3 */
  /* cmp eax, ecx -> je 0x22dfaa */
  /* test eax, eax -> je 0x22dfa3 */
  /* mem[0x00639b88] = eax */
  /* test eax, eax -> je 0x22dfba */
  /* mem[0x00639b8c] = eax */
  /* test edx, edx -> je 0x22dff0 */
  /* cmp eax, ebx -> jae 0x22e0b2 */
  /* relift: FUN_00232430(0, 0); */
  /* test eax, eax -> je 0x22e2bb */
  /* test eax, eax -> je 0x22e2aa */
  /* relift: cmp eax, dword ptr [ebp + 0x2f4] -> ja 0x22e135 */
  /* relift: cmp ecx, dword ptr [ebp + 0x3a0] -> jle 0x22e2a8 */
  /* test eax, eax -> je 0x22e2a8 */
  /* test eax, eax -> je 0x22e2a8 */
  /* cmp ecx, eax -> jbe 0x22e172 */
  /* test edx, edx -> je 0x22e1d7 */
  /* test edi, edi -> je 0x22e1b5 */
  /* test edi, edi -> je 0x22e1d3 */
  /* test eax, eax -> je 0x22e212 */
  /* test eax, eax -> je 0x22e230 */
  /* test edi, edi -> je 0x22e261 */
  /* test eax, eax -> je 0x22e277 */
  /* test eax, eax -> je 0x22e295 */
  /* test eax, eax -> jne 0x22e110 */
  /* relift: FUN_002324f0(0, 0); */
  /* test eax, eax -> jne 0x22e2f2 */
  /* relift: FUN_002328c0(0, 0); */
  /* mem[0x00639b9c] = eax */
  /* mem[0x004ee930] = ecx */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
  (void)ebp;
}

/* 0x22e320 */
void __stdcall BinkSetMemory(unsigned int size)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* mem[0x00639ba0] = eax */
  /* mem[0x00639bac] = eax */
  /* mem[0x00639ba4] = eax */
  /* mem[0x00639ba8] = eax */
  /* cmp ecx, eax -> jbe 0x22e394 */
  /* cmp edx, esi -> jl 0x22e387 */
  /* test edi, edi -> jle 0x22e3d8 */
  /* relift: test byte ptr [ebx + ecx*4], 1 -> je 0x22e3d0 */
  /* cmp ecx, edi -> jl 0x22e3c3 */
  /* cmp edx, 0x32 -> jae 0x22e41a */
  /* relift: cmp ecx, dword ptr [esp + 8] -> je 0x22e430 */
  /* relift: FUN_00232460(0, 0); */
  /* relift: FUN_00232430(0, 0); */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: FUN_00232600(0, 0); */
  /* relift: cmp ecx, dword ptr [esp + 8] -> je 0x22e4e5 */
  /* cmp eax, -1 -> je 0x22e51a */
  /* relift: FUN_0022e0c0(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x22e530 */
int __stdcall BinkCopyToBuffer(void *bink_handle, void *dest, int pitch, int height, int x, int y, unsigned int flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp dword ptr [esp + 0x14], ebx -> jne 0x22e54f */
  /* relift: FUN_00234110(0); */
  /* cmp ebp, ebx -> jge 0x22e59a */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x22e6cd */
  /* test eax, eax -> je 0x22e6cd */
  /* test eax, eax -> jne 0x22e6cd */
  /* relift: FUN_0022e2d0(0, 0); */
  /* relift: FUN_002328c0(0, 0); */
  /* cmp ecx, eax -> jb 0x22e6c3 */
  /* relift: cmp ecx, dword ptr [esi + 0x248] -> jbe 0x22e6b9 */
  /* test edi, 0x80000 -> jne 0x22e6af */
  /* relift: test dword ptr [esi + 0x20], 0x80000 -> jne 0x22e6af */
  /* test eax, eax -> jne 0x22e742 */
  /* test eax, eax -> jne 0x22e742 */
  /* cmp eax, 0x4b -> jae 0x22e742 */
  /* relift: FUN_00232430(0, 0); */
  /* test eax, eax -> je 0x22e734 */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: test dword ptr [esi + 0x20], 0x8000000 -> jne 0x22e742 */
  /* relift: FUN_00232600(0, 0); */
  /* test dl, dl -> jne 0x22e760 */
  /* relift: cmp eax, dword ptr [esi + 0xe4] -> jb 0x22e921 */
  /* cmp eax, 9 -> ja 0x22ead7 */
  /* test eax, eax -> je 0x22e7e5 */
  /* relift: FUN_00246030(0, 0, 0, 0); */
  /* relift: FUN_00244b40(0, 0, 0, 0); */
  /* test eax, eax -> je 0x22e8dc */
  /* relift: FUN_00249ab0(0, 0, 0, 0); */
  /* test eax, eax -> je 0x22e8dc */
  /* relift: FUN_00248980(0, 0, 0, 0); */
  /* relift: FUN_002473f0(0, 0, 0, 0); */
  /* cmp eax, 9 -> ja 0x22ead7 */
  /* test eax, eax -> je 0x22e993 */
  /* relift: FUN_00246080(0, 0, 0, 0); */
  /* relift: FUN_00244b90(0, 0, 0, 0); */
  /* test eax, eax -> je 0x22ea93 */
  /* relift: FUN_00249b00(0, 0, 0, 0); */
  /* test eax, eax -> je 0x22ea93 */
  /* relift: FUN_002489d0(0, 0, 0, 0); */
  /* relift: FUN_00247440(0, 0, 0, 0); */
  return 1;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x22eb40 */
int __stdcall BinkDoFrame(void *bink_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp ebx, ebp -> je 0x22eb5a */
  /* relift: cmp eax, dword ptr [ebx + 0xc] -> jne 0x22eb64 */
  /* relift: FUN_002328c0(0, 0); */
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  memmove((void *)(uintptr_t)eax, (void *)0, 0);
  /* cmp eax, ebp -> jne 0x22ece6 */
  /* relift: cmp dword ptr [ebx + 0x21c], -1 -> je 0x22ecf5 */
  /* relift: FUN_0022e0c0(0); */
  /* relift: cmp dword ptr [ebx + 0x1c], ebp -> je 0x22ed23 */
  /* test ecx, ecx -> je 0x22ee97 */
  /* relift: FUN_00232460(0, 0); */
  /* test ebp, ebp -> je 0x22ee7c */
  /* relift: FUN_0023ec50(0, 0, 0, 0); */
  /* cmp ecx, ebp -> jbe 0x22edd0 */
  /* cmp ecx, esi -> jbe 0x22eddc */
  /* cmp eax, ecx -> jae 0x22ee4c */
  /* test eax, eax -> je 0x22ee28 */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: FUN_002328c0(0, 0); */
  /* test eax, eax -> je 0x22efe0 */
  /* test eax, eax -> jne 0x22eef6 */
  /* test eax, eax -> jne 0x22ef65 */
  /* test eax, eax -> jne 0x22ef65 */
  /* cmp eax, 0x4b -> jae 0x22ef65 */
  /* relift: FUN_00232430(0, 0); */
  /* test eax, eax -> je 0x22ef57 */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: test dword ptr [ebx + 0x20], 0x8000000 -> jne 0x22ef65 */
  /* relift: FUN_00232600(0, 0); */
  /* relift: FUN_00238070(0, 0, 0, 0); */
  /* cmp eax, esi -> je 0x22eff3 */
  /* relift: FUN_0022e0c0(0); */
  /* relift: FUN_002328c0(0, 0); */
  /* relift: FUN_002328c0(0, 0); */
  /* test edx, edx -> je 0x22f09c */
  /* relift: test byte ptr [esi + eax*4 - 4], 1 -> jne 0x22f16f */
  /* test edi, edi -> jl 0x22f0fa */
  /* relift: test byte ptr [esi + edi*4], 1 -> jne 0x22f113 */
  /* relift: cmp eax, dword ptr [ecx + 8] -> jae 0x22f110 */
  /* relift: cmp eax, dword ptr [ecx + 8] -> jae 0x22f141 */
  /* test dl, dl -> jne 0x22f16f */
  /* cmp eax, esi -> jae 0x22f141 */
  /* test dl, dl -> jne 0x22f16f */
  /* cmp eax, esi -> jb 0x22f130 */
  /* cmp eax, 1 -> jl 0x22f16e */
  /* relift: test byte ptr [ecx], 1 -> jne 0x22f16e */
  /* cmp eax, 1 -> jge 0x22f160 */
  /* test edx, edx -> je 0x22f1d9 */
  /* relift: cmp ecx, dword ptr [eax + 0x258] -> jbe 0x22f1d9 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x22f1e0 */
int __stdcall BinkWait(void *bink_handle)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> je 0x22f207 */
  /* test eax, eax -> jne 0x22f200 */
  /* test eax, eax -> je 0x22f207 */
  /* test eax, eax -> je 0x22f210 */
  /* relift: FUN_0022e2d0(0, 0); */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x22f236 */
  /* relift: FUN_0022e0c0(0); */
  /* relift: FUN_002328c0(0, 0); */
  /* test eax, eax -> je 0x22f25b */
  /* relift: FUN_0022f180(0, 0); */
  /* test eax, eax -> jne 0x22f395 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x22f289 */
  /* test eax, eax -> je 0x22f395 */
  /* test eax, eax -> je 0x22f38a */
  /* cmp ecx, eax -> jl 0x22f395 */
  /* relift: cmp ecx, dword ptr [esi + 0x248] -> jle 0x22f35d */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> jne 0x22f32f */
  /* cmp eax, ecx -> jae 0x22f382 */
  /* test eax, eax -> jne 0x22f3cf */
  /* relift: FUN_00232430(0, 0); */
  /* test eax, eax -> je 0x22f3cf */
  /* relift: FUN_002324f0(0, 0); */
  /* cmp esi, edi -> jne 0x22f3f3 */
  /* relift: FUN_002328c0(0, 0); */
  /* cmp ecx, edi -> je 0x22f412 */
  /* relift: FUN_0022f180(0, 0); */
  /* cmp eax, edi -> jne 0x22f437 */
  /* relift: cmp dword ptr [esi + 0xfc], edi -> je 0x22f437 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x22f471 */
  /* relift: FUN_0022e0c0(0); */
  return 0;

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x22f480 */
void __stdcall BinkGetSummary(void *bink_handle, void *summary)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> je 0x22f644 */
  /* test ebx, ebx -> je 0x22f643 */
  /* relift: FUN_002328c0(0, 0); */
  /* test ecx, ecx -> je 0x22f4be */
  /* relift: FUN_0022f180(0); */
  /* relift: FUN_002328c0(0, 0); */

  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x22f650 */
void __stdcall BinkGetFrameBuffersInfo(void *bink_handle, void *frame_info, unsigned int frame_count)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002328c0(0, 0, 0, 0); */
  /* test ecx, ecx -> je 0x22f67b */
  /* relift: FUN_0022f180(0, 0); */
  /* test ebx, ebx -> je 0x22f694 */
  /* relift: cmp ebx, dword ptr [esi + 0x284] -> jb 0x22f69b */
  /* cmp ebx, eax -> jbe 0x22f6ae */
  /* test ebx, ebx -> jne 0x22f6ae */
  /* test eax, eax -> jle 0x22f801 */
  /* relift: cmp byte ptr [edi + ebx], 0 -> jne 0x22f80f */
  /* cmp edi, eax -> jl 0x22f7f6 */
  /* cmp edx, ecx -> jl 0x22f7f0 */
  /* test ecx, ecx -> jle 0x22f864 */
  /* relift: cmp byte ptr [edi + edx], 0 -> jne 0x22f864 */
  /* cmp edi, eax -> jl 0x22f852 */
  /* cmp ebx, ecx -> jl 0x22f850 */
  /* relift: cmp byte ptr [ebx], 0 -> jne 0x22f8a1 */
  /* cmp edi, ecx -> jl 0x22f890 */
  /* cmp edx, eax -> jl 0x22f880 */
  /* test ebx, ebx -> jl 0x22f8ef */
  /* relift: cmp byte ptr [edi], 0 -> jne 0x22f8ef */
  /* cmp edx, ecx -> jl 0x22f8e0 */
  /* relift: cmp dword ptr [edi + 8], 0x20 -> jl 0x22f9bc */
  /* relift: FUN_0022f7a0(0); */
  /* relift: FUN_0022f7a0(0, 0, 0); */
  /* relift: cmp dword ptr [edi + 0xc], 0x20 -> jl 0x22faa4 */
  /* relift: FUN_0022f7a0(0); */
  /* relift: FUN_0022f7a0(0, 0, 0); */
  /* cmp eax, ebx -> jle 0x22faa4 */
  /* test ebx, 0x4000000 -> je 0x22fad2 */
  /* relift: test dword ptr [esi + 0x20], 0x80000 -> jne 0x22fb02 */
  /* test eax, eax -> je 0x22fb02 */
  /* relift: cmp dword ptr [esi + 0xb4], -1 -> jne 0x22fe1a */
  /* relift: FUN_0022f7a0(0, 0, 0, 0); */
  /* cmp eax, ebp -> je 0x22fcb9 */
  /* relift: FUN_0022f910(0, 0, 0, 0); */
  /* test ecx, ecx -> jle 0x22fcb9 */
  /* cmp ecx, edx -> jle 0x22fbdf */
  /* cmp eax, ebx -> jl 0x22fbd0 */
  /* cmp edi, -1 -> je 0x22fcb9 */
  /* relift: FUN_0022f910(0, 0, 0, 0); */
  /* relift: FUN_0022f910(0, 0, 0); */
  /* cmp eax, ebx -> jae 0x22fd09 */
  /* cmp ecx, edi -> jl 0x22fcf5 */
  /* cmp eax, 0x30000000 -> ja 0x22fd53 */
  /* cmp eax, 0x10000000 -> je 0x22fd33 */
  /* cmp eax, 0x20000000 -> jne 0x22fd90 */
  /* cmp eax, 0x40000000 -> je 0x22fd61 */
  /* cmp eax, 0x50000000 -> jne 0x22fd90 */
  /* cmp ecx, edx -> jbe 0x22fdb3 */
  /* cmp eax, ecx -> jbe 0x22fdd0 */
  /* relift: cmp dword ptr [eax + 0x21c], -1 -> je 0x22fe46 */
  /* test ecx, ecx -> je 0x22fe77 */
  /* relift: cmp dword ptr [ecx + 0x21c], -1 -> je 0x22fe77 */
  /* test eax, eax -> je 0x22fe77 */
  /* test ecx, ecx -> je 0x22fea7 */
  /* relift: cmp dword ptr [ecx + 0x21c], -1 -> je 0x22fea7 */
  /* test eax, eax -> je 0x22fea7 */
  /* test ecx, ecx -> je 0x22fed7 */
  /* relift: cmp dword ptr [ecx + 0x21c], -1 -> je 0x22fed7 */
  /* test eax, eax -> je 0x22fed7 */
  /* test eax, eax -> je 0x22ff08 */
  /* test eax, eax -> je 0x22ff28 */
  /* test eax, eax -> je 0x22ff48 */
  /* test esi, esi -> je 0x22ffa4 */
  /* relift: cmp ebx, dword ptr [esi + 0xf0] -> jae 0x22ffa4 */
  /* relift: FUN_0023cd10(0); */
  /* test ebp, ebp -> je 0x22ffa4 */
  /* relift: FUN_002314b0(28); */
  /* test edx, edx -> jne 0x22ffac */
  /* relift: FUN_0023ce50(0); */
  /* test esi, esi -> je 0x230053 */
  /* test eax, eax -> je 0x23004d */
  /* relift: FUN_0023ce50(0); */
  /* relift: FUN_00231520(0); */
  /* test edi, edi -> jle 0x2300b2 */
  /* test edx, edx -> jne 0x2300bc */
  /* cmp ecx, edx -> jl 0x230090 */
  /* relift: FUN_0023ec50(0, 0, 0, 0); */
  /* cmp ecx, ebp -> jbe 0x23010c */
  /* cmp eax, 0x10 -> jne 0x230130 */
  /* cmp esi, ecx -> jb 0x230142 */
  /* test esi, esi -> je 0x2302c7 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x2302c7 */
  /* test ecx, ecx -> je 0x2302c7 */
  /* test eax, eax -> je 0x2302c3 */
  /* relift: FUN_00232460(0, 0); */
  /* relift: FUN_002324f0(0, 0); */
  /* test eax, eax -> jne 0x2302c3 */
  /* relift: FUN_00232460(0, 0, 0); */
  /* cmp eax, 1 -> je 0x23029d */
  /* relift: cmp eax, dword ptr [esi + 0xec] -> je 0x23029d */
  /* relift: FUN_002324f0(0, 0); */
  /* test edi, edi -> je 0x2302d8 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x2302e7 */
  /* relift: FUN_0022e0c0(0); */
  /* test eax, eax -> je 0x23030a */
  /* relift: FUN_002301a0(0, 0); */
  /* relift: FUN_002301a0(0, 0); */
  /* test ecx, ecx -> je 0x230345 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x230388 */
  /* relift: FUN_0022e0c0(0); */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x230390 */
void *__stdcall BinkOpen(const char *filename, unsigned int flags)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: FUN_002328c0(0, 0); */
  /* test ebx, 0x2000000 -> je 0x2303f7 */
  /* test eax, eax -> je 0x2303f7 */
  /* mem[0x00639bac] = 0 */
  /* test eax, eax -> jne 0x230432 */
  /* test (char)eax, (char)eax -> jne 0x230427 */
  /* relift: FUN_0022df50(0x002c27c0); */
  /* cmp eax, 0x664b4942 -> je 0x230479 */
  /* cmp eax, 0x674b4942 -> je 0x230479 */
  /* cmp eax, 0x684b4942 -> je 0x230479 */
  /* cmp eax, 0x694b4942 -> je 0x230479 */
  /* relift: FUN_0022df50(0x002c27ac); */
  /* test eax, eax -> jne 0x230499 */
  /* test (char)ecx, (char)ecx -> jne 0x230483 */
  /* cmp ebx, 0x70000000 -> je 0x230591 */
  /* test ebx, ebx -> je 0x23053a */
  /* cmp edx, 0x10000000 -> je 0x23058a */
  /* cmp edx, 0x20000000 -> jne 0x230591 */
  /* cmp edx, 0x40000000 -> je 0x230583 */
  /* cmp edx, 0x50000000 -> jne 0x230591 */
  /* cmp edx, 0x664b4942 -> je 0x2305b4 */
  /* cmp edx, 0x674b4942 -> je 0x2305b4 */
  /* cmp edx, 0x684b4942 -> jne 0x2305bd */
  /* cmp eax, -1 -> je 0x230603 */
  /* mem[0x00639b9c] = 0xffffffff */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_00236210(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* test eax, eax -> jne 0x23081a */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022dec0(1032); */
  /* test eax, eax -> je 0x2308e5 */
  /* relift: FUN_0022e360(0, 0, 0, 0); */
  /* test eax, 0x100000 -> je 0x2309be */
  /* relift: FUN_0022de60(0, 0); */
  /* test edi, edi -> jne 0x2309f0 */
  /* relift: FUN_0022de60(0, 0); */
  /* test edi, edi -> jne 0x2309f0 */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022dec0(0); */
  /* test edi, edi -> je 0x230a4e */
  /* test ecx, 0x1000000 -> je 0x230a73 */
  /* cmp eax, ebx -> je 0x230a73 */
  /* mem[0x00639ba0] = ebx */
  /* test ecx, 0x400000 -> je 0x230a9c */
  /* cmp eax, ebx -> je 0x230a9c */
  /* mem[0x00639ba4] = ebx */
  /* test eax, eax -> je 0x230ac7 */
  /* relift: test dword ptr [ebp + 0xc], eax -> je 0x230bcb */
  /* relift: FUN_0022df30(0, 0); */
  /* relift: FUN_00231520(0); */
  /* relift: FUN_00231520(0); */
  /* test (char)ecx, (char)ecx -> jne 0x230b50 */
  /* relift: test dword ptr [ebp + 0xc], 0x4000000 -> jne 0x230b79 */
  /* relift: FUN_0022de60(0, 0); */
  /* relift: FUN_0022df30(0, 0); */
  /* relift: FUN_002302d0(0, 0); */
  /* relift: FUN_002328c0(0, 0); */
  /* cmp edx, eax -> jne 0x230c9d */
  /* test (char)ecx, 0x40 -> je 0x230cd7 */
  /* cmp edi, ebx -> jne 0x230cb7 */
  /* cmp eax, edx -> jge 0x230cd5 */
  /* relift: cmp dword ptr [ecx], edi -> je 0x230cd1 */
  /* relift: cmp eax, dword ptr [esi + 0xf0] -> jl 0x230cc1 */
  /* cmp eax, edx -> jl 0x230cd7 */
  /* mem[0x00639ba8] = ebx */
  /* test eax, eax -> jne 0x230d23 */
  BinkSoundUseDirectSound((void *)0x00231e80, (void *)0);
  /* test eax, eax -> je 0x230edb */
  /* test ecx, ecx -> je 0x230d77 */
  /* test eax, eax -> je 0x230d77 */
  __allmul();
  __aulldiv();
  /* test eax, eax -> je 0x230edb */
  /* mem[0x00639b90] = edx */
  /* relift: FUN_002314b0(0); */
  /* relift: FUN_0023cd10(0); */
  /* test eax, eax -> jne 0x230eef */
  /* test eax, eax -> jne 0x230f03 */
  /* relift: cmp dword ptr [esi + 0x21c], -1 -> je 0x230f44 */
  /* test eax, eax -> jne 0x230f27 */
  /* relift: FUN_00232130(20); */
  /* mem[0x00639b98] = eax */
  /* relift: FUN_00232390(0); */
  /* relift: FUN_002321c0(0, 0, 0x0022e4d0, 0x0022e4f0); */
  /* relift: test dword ptr [esi + 0x20], 0x8000000 -> jne 0x230f8e */
  /* test eax, eax -> jne 0x230f8e */
  /* test eax, eax -> jne 0x230f72 */
  /* relift: FUN_00232130(0); */
  /* mem[0x00639b94] = eax */
  /* relift: FUN_00232390(0); */
  /* relift: FUN_002321c0(0, 0, 0x0022e3f0, 0x0022e440); */
  /* relift: test dword ptr [ebp + 0xc], 0x200000 -> jne 0x230fdb */
  /* test eax, eax -> jne 0x230fd0 */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x230ff0 */
int __stdcall BinkNextFrame(void *bink_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp esi, ebp -> je 0x231143 */
  /* relift: cmp eax, dword ptr [esi + 0x3a0] -> jg 0x2310e4 */
  /* relift: FUN_00232490(0, 0, 0, 0); */
  /* relift: FUN_002301a0(0, 0); */
  /* cmp eax, 0x5a -> jae 0x2310aa */
  /* test eax, eax -> je 0x2310a8 */
  /* cmp eax, 0x5a -> jb 0x231083 */
  /* relift: FUN_0022e000(0, 0); */
  /* relift: FUN_002301a0(0, 0); */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: FUN_002324f0(0, 0); */
  /* relift: FUN_0022e0c0(0); */
  /* relift: FUN_002328c0(0, 0); */
  /* cmp ecx, ebp -> je 0x23111a */
  /* relift: cmp eax, dword ptr [esi + 8] -> jb 0x231137 */
  /* relift: FUN_002302d0(0, 0); */
  /* relift: FUN_002302d0(0, 0); */
  /* test esi, esi -> je 0x23120e */
  /* test edi, edi -> jne 0x23116d */
  /* relift: test byte ptr [esp + 0x1c], 1 -> jne 0x2311fa */
  /* cmp ebx, edi -> je 0x231201 */
  /* relift: FUN_0022f0a0(0, 0, 0); */
  /* cmp ebp, ebx -> jbe 0x2311ac */
  /* relift: FUN_002302d0(0, 0); */
  /* cmp ebp, edi -> je 0x231201 */
  /* relift: FUN_0022f3e0(0, 0); */
  /* relift: cmp eax, dword ptr [esi + 0x2ac] -> je 0x2311c5 */
  BinkDoFrame((void *)(uintptr_t)esi);
  /* relift: tail-call BinkNextFrame(); */
  /* relift: cmp dword ptr [esi + 0xc], edi -> je 0x2311e1 */
  BinkDoFrame((void *)(uintptr_t)esi);
  /* relift: tail-call BinkNextFrame(); */
  /* relift: cmp dword ptr [esi + 0xc], edi -> jne 0x2311d0 */
  /* relift: FUN_0022f3e0(0, 0); */
  /* relift: FUN_002302d0(0, 0); */
  return 1;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x231220 */
void __stdcall BinkClose(void *bink_handle)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* cmp esi, ebx -> je 0x231323 */
  /* relift: FUN_0022f3e0(0, 0); */
  /* relift: test dword ptr [esi + 0x20], 0x8000000 -> jne 0x231251 */
  /* relift: cmp dword ptr [esi + 0x108], ebx -> jne 0x231251 */
  /* relift: FUN_002326e0(0, 0, 0, 0); */
  /* mem[0x00639b98] = ebx */
  /* mem[0x00639b94] = ebx */
  /* relift: cmp dword ptr [esi + 0x21c], edi -> je 0x2312ba */
  /* relift: FUN_0023ce50(0); */
  /* cmp eax, ebx -> je 0x2312d8 */
  /* relift: test dword ptr [esi + 0x20], 0x4000000 -> jne 0x2312f1 */
  /* mem[0x00639b98] = ebx */
  /* relift: FUN_00231520(0); */
  /* cmp eax, ebx -> je 0x231301 */
  /* relift: FUN_00231520(0); */
  /* cmp eax, ebx -> je 0x231311 */
  /* relift: FUN_00231520(0); */
  /* relift: FUN_00231520(0, 0); */
  /* test (char)ecx, (char)ecx -> jne 0x231370 */
  /* test ebp, ebp -> je 0x23138a */
  /* relift: FUN_001d8b2e(0); */
  /* relift: FUN_001d8b49(0); */
  /* test (char)ecx, (char)ecx -> jne 0x2313a0 */
  /* test (char)eax, (char)eax -> jne 0x2313b2 */
  /* relift: FUN_001d8b2e(0); */
  /* relift: FUN_001d8b49(0); */
  /* test (char)ebx, 0x40 -> je 0x23141d */
  /* test (char)eax, (char)eax -> jne 0x2313f1 */
  /* relift: FUN_001d8b2e(0); */
  /* relift: FUN_001d8b49(0); */
  /* test esi, esi -> je 0x23145a */
  /* test (char)eax, (char)eax -> jne 0x231426 */
  /* relift: FUN_001d8b2e(0); */
  /* relift: FUN_001d8b49(0); */
  /* test (char)ebx, 0x20 -> je 0x231477 */
  /* relift: FUN_00231330(0); */
  /* cmp esi, 0xf -> jle 0x231466 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x231490 */
void __stdcall BinkSetSoundSystem(void *open_proc, void *close_proc)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* mem[0x0063d5f0] = eax */
  /* mem[0x0063d5f4] = ecx */
  /* test esi, esi -> je 0x231514 */
  /* cmp esi, -1 -> je 0x231514 */
  /* test eax, eax -> je 0x2314da */
  /* test eax, eax -> je 0x2314da */
  /* cmp eax, -1 -> je 0x231514 */
  _malloc();
  /* test eax, eax -> je 0x231514 */
  /* test eax, eax -> je 0x231546 */
  FUN_001dde24();
  /* test ecx, ecx -> je 0x23164f */
  /* cmp edi, 0x7fff -> jle 0x23160a */
  IDirectSoundBuffer_SetFrequency();
  IDirectSoundBuffer_SetVolume((void *)(uintptr_t)edx, 0);
  IDirectSoundBuffer_SetHeadroom();
  IDirectSoundBuffer_SetMixBins();
  IDirectSoundBuffer_Lock();
  IDirectSoundBuffer_Unlock();
  IDirectSoundBuffer_Lock();
  /* test edi, edi -> je 0x231725 */
  IDirectSoundBuffer_Unlock();
  IDirectSoundBuffer_Play((void *)(uintptr_t)eax, 0, 0, 0);
  IDirectSoundBuffer_Stop();
  /* test eax, eax -> jne 0x2318cd */
  /* test eax, eax -> je 0x2318cd */
  /* test eax, eax -> jne 0x2317b3 */
  IDirectSoundBuffer_GetCurrentPosition();
  /* cmp eax, ebp -> ja 0x2317eb */
  /* cmp edx, ebx -> ja 0x231806 */
  /* cmp eax, edx -> jg 0x2318cd */
  /* relift: FUN_002328c0(0, 0); */
  /* cmp ecx, edx -> jae 0x231862 */
  /* cmp eax, 0x400 -> jae 0x231871 */
  /* relift: cmp eax, dword ptr [edi + 0x50] -> jae 0x231889 */
  /* test ecx, ecx -> je 0x2318cd */
  /* test eax, eax -> je 0x2318cd */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
