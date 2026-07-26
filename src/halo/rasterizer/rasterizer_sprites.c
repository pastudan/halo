/* Render sprites by forwarding to the dynavob geometry renderer (0x17cfa0). */
void rasterizer_sprites_render(void *render_data, void *vertices)
{
  FUN_0015f8e0(render_data, vertices);
}
/* --- rasterizer_sprites.obj batch drafts (2026-07-26) --- */

/* 0x17cd60 */
void FUN_0017cd60(int object_handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cd70 */
void FUN_0017cd70(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cd80 */
void FUN_0017cd80(void)
{
  int eax = 0;

  FUN_0016fa40(11);
  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */

  (void)eax;
}

/* 0x17cd90 */
void FUN_0017cd90(void)
{
  int eax = 0;

  FUN_0016fa40(11);
  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);

  (void)eax;
}

/* 0x17cda0 */
void FUN_0017cda0(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x163c69 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 1785, 0);
  system_exit(0);
  FUN_0016f910(12);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x163fd2 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256cf] */
  /* test (char)eax, (char)eax -> je 0x163fd2 */
  /* relift: cmp word ptr [0x3256b0], 0 -> jne 0x163fd2 */

  (void)eax;
}

/* 0x17cdb0 */
void FUN_0017cdb0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cdc0 */
void FUN_0017cdc0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cde0 */
void FUN_0017cde0(void)
{
  int eax = 0;

  FUN_0016fa40(12);
  /* test eax, eax -> jne 0x1609df */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 2163, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256bc], 0 -> jne 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d0] */
  /* test (char)eax, (char)eax -> je 0x160ba4 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256d2] */

  (void)eax;
}

/* 0x17cdf0 */
void FUN_0017cdf0(void)
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

  (void)eax;
  (void)ebx;
}

/* 0x17ce00 */
void FUN_0017ce00(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ce10 */
void FUN_0017ce10(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ce30 */
void FUN_0017ce30(void)
{
  FUN_0016fa40(13);
  FUN_0016f910(14);
  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
}

/* 0x17ce40 */
void FUN_0017ce40(void)
{
  FUN_0016f910(14);
  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
}

/* 0x17ce50 */
void FUN_0017ce50(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ce60 */
void FUN_0017ce60(void)
{
  int eax = 0;

  FUN_0016fa40(14);
  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */

  (void)eax;
}

/* 0x17ce70 */
void FUN_0017ce70(void)
{
  int eax = 0;

  FUN_0016f910(15);
  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);

  (void)eax;
}

/* 0x17ce80 */
void FUN_0017ce80(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ce90 */
void FUN_0017ce90(void)
{
  int eax = 0;

  FUN_0016fa40(15);
  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);

  (void)eax;
}

/* 0x17cea0 */
void FUN_0017cea0(void)
{
  int eax = 0;

  FUN_0016f910(16);
  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */

  (void)eax;
}

/* 0x17ceb0 */
void FUN_0017ceb0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cec0 */
void FUN_0017cec0(void)
{
  int eax = 0;

  FUN_001749b0();
  FUN_0016fa40(16);
  /* test eax, eax -> jne 0x160c56 */
  display_assert((char *)0x0029dc40, (char *)0x002a18c0, 17, 0);
  system_exit(0);
  FUN_0016f910(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256bc] */
  /* test (int16_t)eax, (int16_t)eax -> je 0x160c99 */
  /* cmp (int16_t)eax, 2 -> je 0x160c99 */
  /* cmp (int16_t)eax, 6 -> je 0x160c99 */
  /* cmp (int16_t)eax, 3 -> je 0x160c99 */

  (void)eax;
}

/* 0x17ced0 */
void FUN_0017ced0(void)
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

  (void)eax;
}

/* 0x17cee0 */
void FUN_0017cee0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cef0 */
void FUN_0017cef0(void)
{
  int edi = 0;

  FUN_0016fa40(17);
  /* cmp (int16_t)eax, 4 -> jl 0x165e20 */
  display_assert((char *)0x002a1d18, (char *)0x002a1cc8, 484, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x165e47 */

  (void)edi;
}

/* 0x17cf00 */
void FUN_0017cf00(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf10 */
void FUN_0017cf10(int pass_index)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf20 */
void FUN_0017cf20(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf30 */
void FUN_0017cf30(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x16794f */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 1036, 0);
  system_exit(0);
  FUN_00166010();
  /* test (char)eax, (char)eax -> je 0x167ec6 */
  /* relift: relift: mov (char)eax, byte ptr [0x47dd89] */

  (void)eax;
}

/* 0x17cf40 */
void FUN_0017cf40(void)
{
  FUN_0016f910(27);
  FUN_0016fa40(27);
  display_assert((char *)0x002a16bc, (char *)0x002a16c4, 220, 0);
  system_exit(0);
}

/* 0x17cf50 */
void FUN_0017cf50(void)
{
  int edi = 0;

  FUN_0016fa40(27);
  display_assert((char *)0x002a16bc, (char *)0x002a16c4, 220, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x15f273 */

  (void)edi;
}

/* 0x17cf60 */
void FUN_0017cf60(uint32_t source, uint32_t param, int arg3, int arg4, uint32_t handle, int subcount2, float *origin, uint32_t widget_flags)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf70 */
void FUN_0017cf70(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf80 */
void FUN_0017cf80(int arg1, int arg2, uint32_t handle, int subcount2)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cf90 */
void FUN_0017cf90(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cfb0 */
void FUN_0017cfb0(int object_handle, int datum, float *position, int callback)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cfc0 */
void FUN_0017cfc0(int param_1, int param_2)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cfd0 */
char FUN_0017cfd0(int param_1, int param_2, short param_3)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x17cfe0 */
void FUN_0017cfe0(int tex_flags)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17cff0 */
void FUN_0017cff0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d000 */
void FUN_0017d000(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d010 */
void FUN_0017d010(float *position, float radius, float *scale2d, float angle, uint32_t color)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d020 */
void FUN_0017d020(void)
{
  int eax = 0;

  D3DDevice_Begin(eax);
  D3DDevice_End();
  /* relift: relift: mov (char)eax, byte ptr [0x3256fc] */
  D3DDevice_GetVisibilityTestResult();

  (void)eax;
}

/* 0x17d040 */
void FUN_0017d040(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d050 */
void FUN_0017d050(void)
{
  int ebx = 0;

  interface_get_tag_index(12);
  FUN_00076ff0(0, 0);
  interface_get_tag_index(13);
  FUN_00076ff0(0, 0);
  display_assert((char *)0x0029dc40, (char *)0x002a399c, 27, ebx);
  system_exit(0);

  (void)ebx;
}

/* 0x17d060 */
void FUN_0017d060(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d070 */
void FUN_0017d070(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d080 */
void FUN_0017d080(void)
{
  int edx = 0;

  FUN_0015a7f0((float *)(uintptr_t)edx, (float *)0, (float *)0, (float *)0);
  FUN_0015a7f0((float *)(uintptr_t)edx, (float *)0, (float *)0, (float *)0);
  FUN_0015a7f0((float *)(uintptr_t)edx, (float *)0, (float *)0, (float *)0);

  (void)edx;
}

/* 0x17d150 */
void FUN_0017d150(void)
{
  FUN_0015a7f0((float *)0, (float *)0, (float *)0, (float *)0);
}

/* 0x17d1a0 */
void FUN_0017d1a0(int param_1)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;

  /* test (char)ebx, (char)ebx -> jne 0x17d292 */
  /* relift: cmp word ptr [0x4761d8], 0x20 -> jl 0x17d1dc */
  display_assert((char *)0x00253440, (char *)0x002af1ec, 740, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x4761d8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: mov word ptr [0x4761d8], (int16_t)eax */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  FUN_0014df70(0, (float *)0, (float *)0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x17d253 */
  /* mem[0x0047e4cc] = edx */
  /* relift: cmp word ptr [0x4761d8], 1 -> jg 0x17d27d */
  display_assert((char *)0x00253418, (char *)0x002af1ec, 756, 0);
  system_exit(0);
  FUN_0016b180();
  /* mem[0x0047e4cc] = 0xffffffff */
  FUN_0016b180();

  (void)eax;
  (void)ebx;
  (void)edx;
}

/* 0x17d2b0 */
void FUN_0017d2b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_001d90e0();
  /* cmp edi, esi -> jne 0x17d2e8 */
  display_assert((char *)0x0025bc3c, (char *)0x002af1ec, 830, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256bf] */
  /* test (char)eax, (char)eax -> je 0x17d8e4 */
  /* relift: cmp eax, dword ptr [0x47e4cc] -> jne 0x17d8e4 */
  display_assert((char *)0x002af2d0, (char *)0x002af1ec, 857, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_0017ffc0((float *)(uintptr_t)edx, ecx);
  display_assert((char *)0x002af2a8, (char *)0x002af1ec, 878, 0);
  system_exit(0);
  /* relift: cmp (int16_t)ebx, word ptr [edx + 4] -> jl 0x17d484 */
  display_assert((char *)0x002af280, (char *)0x002af1ec, 879, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x17d4a4 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002af254, (char *)0x002af1ec, 880, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x17d4f9 */
  matrix_transform_point((float *)(uintptr_t)edx, (float *)(uintptr_t)esi, (float *)0);
  matrix_scale_transform_vector((float *)(uintptr_t)eax, (float *)0, (float *)0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x17d52e */
  matrix_transform_point((float *)(uintptr_t)eax, (float *)(uintptr_t)esi, (float *)0);
  matrix_scale_transform_vector((float *)(uintptr_t)ecx, (float *)0, (float *)0);
  normalize3d((float *)0);
  /* test ebx, ebx -> jle 0x17d66f */
  /* cmp edi, ebx -> jl 0x17d5b5 */
  /* cmp (char)eax, 0xc -> jae 0x17d62d */
  /* test esi, esi -> jle 0x17d61a */
  /* relift: cmp word ptr [ecx + eax*2 + 0xc], (int16_t)ebx -> je 0x17d617 */
  /* cmp eax, ebx -> jl 0x17d600 */
  /* cmp eax, esi -> jne 0x17d62d */
  /* cmp (char)eax, 0xc -> jae 0x17d66f */
  /* test esi, esi -> jle 0x17d65c */
  /* cmp ebx, eax -> je 0x17d659 */
  /* cmp eax, ebx -> jl 0x17d640 */
  /* cmp eax, esi -> jne 0x17d66f */
  /* cmp edi, ebx -> jne 0x17d776 */
  /* cmp ebx, 0x800 -> jge 0x17d776 */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x255e94] */
  /* cmp eax, edx -> jl 0x17d354 */
  csstrcpy((char *)0x005ab100, (char *)0x002af250);
  /* test ecx, ecx -> jle 0x17d826 */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002af248);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x17d7e0 */
  FUN_0008dc30((char *)0x005ab100, (char *)0x002af244);
  /* test ecx, ecx -> jle 0x17d88b */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002af248);
  FUN_0008dc30((char *)0x005ab100, (char *)(uintptr_t)edx);
  /* cmp eax, ecx -> jl 0x17d844 */
  FUN_00189150(0, (float *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)eax);
  FUN_00189cb0(0, (void *)(uintptr_t)esi, (void *)0x005ab100, 0);
  FUN_00189150(0, (float *)(uintptr_t)esi, 0.0f, (void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17d8f0 */
void FUN_0017d8f0(void)
{
  game_time_get();
}

/* 0x17d910 */
void rasterizer_screen_effects_initialize(void)
{
  int eax = 0;

  game_state_malloc((char *)0x002af368, (char *)0, 120);
  /* mem[0x0047e4d4] = eax */
  display_assert((char *)0x002af314, (char *)0x002af334, 54, 0);
  system_exit(0);

  (void)eax;
}

/* 0x17d950 */
void FUN_0017d950(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x17d97c */
  csmemset((void *)(uintptr_t)eax, 0, 120);

  (void)eax;
}

/* 0x17d980 */
void FUN_0017d980(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d990 */
void FUN_0017d990(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d9a0 */
void FUN_0017d9a0(int a0, float a1)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17d9d0 */
void FUN_0017d9d0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17da00 */
void FUN_0017da00(int a0)
{
  int eax = 0;
  int ecx = 0;

  /* test eax, eax -> je 0x17da34 */
  /* test (char)ecx, (char)ecx -> jne 0x17da1a */
  /* test (char)ecx, (char)ecx -> jne 0x17da30 */
  csmemset((void *)(uintptr_t)eax, 0, 56);

  (void)eax;
  (void)ecx;
}

/* 0x17da40 */
void FUN_0017da40(int a0, int a1, float a2, float a3, float a4)
{
  int eax = 0;
  int ecx = 0;

  /* cmp eax, ecx -> je 0x17da9e */
  game_time_get();

  (void)eax;
  (void)ecx;
}

/* 0x17dab0 */
void FUN_0017dab0(int a0, float a1, float a2, float a3, int a4, float a5)
{
  int eax = 0;
  int ebx = 0;

  /* cmp eax, ebx -> je 0x17db18 */
  game_time_get();

  (void)eax;
  (void)ebx;
}

/* 0x17db20 */
void FUN_0017db20(int a0, float a1, float a2)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17db40 */
void rasterizer_screen_effect_set_video(int a0, float a1)
{
  int eax = 0;
  int esi = 0;

  /* cmp eax, esi -> je 0x17dc5d */
  /* cmp eax, esi -> jne 0x17db81 */
  display_assert((char *)0x0029da1c, (char *)0x002af334, 225, 0);
  system_exit(0);
  /* relift: cmp dword ptr [eax + 0x128], -1 -> je 0x17dc4e */
  /* relift: cmp dword ptr [eax + 0x138], -1 -> je 0x17dc4e */
  csmemset((void *)(uintptr_t)eax, 0, 56);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get(0x6269746d, 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  error(0, (char *)0x002af380);

  (void)eax;
  (void)esi;
}

/* 0x17dc60 */
void FUN_0017dc60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17dc70 */
void *rasterizer_screen_effect_get_cinematic_parameters(void *effect)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  /* cmp ecx, ebx -> je 0x17deb4 */
  /* relift: cmp byte ptr [ecx + 0x38], (char)ebx -> je 0x17deb4 */
  game_time_get();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0017d8f0();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x17dd11 */
  FUN_0017d8f0();
  game_time_get();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  FUN_0017d8f0();
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x17dd9e */
  FUN_0017d8f0();
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)eax);
  scalars_interpolate_and_clamp_0_to_1(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)edx);
  scalars_interpolate_and_clamp_0_to_1(0.0f, 0.0f, 0.0f, (float *)(uintptr_t)ecx);
  csmemcmp((void *)(uintptr_t)edx, (void *)0, 0);
  /* test eax, eax -> jne 0x17de29 */
  /* relift: relift: fcomp dword ptr [0x253f44] */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x17de71 */
  display_assert((char *)0x002af3d0, (char *)0x002af334, 336, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* relift: relift: fcomp dword ptr [0x253f44] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 1 -> jne 0x17dead */
  return NULL;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

/* 0x17dec0 */
void FUN_0017dec0(int a0)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17dee0 */
void FUN_0017dee0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17df10 */
void FUN_0017df10(void)
{
  int eax = 0;
  int edx = 0;

  /* cmp eax, 0x2000 -> jge 0x17df54 */
  /* relift: cmp dword ptr [0x47e4f4], 0x2000 -> jge 0x17df54 */
  /* mem[0x0047e4f4] = edx */
  /* relift: relift: mov (char)eax, byte ptr [0x47e4f8] */
  /* test (char)eax, (char)eax -> jne 0x17df73 */
  error(0, (char *)0x002af460);
  /* relift: relift: mov byte ptr [0x47e4f8], 1 */

  (void)eax;
  (void)edx;
}

/* 0x17df80 */
void FUN_0017df80(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;

  debug_malloc(0x00078000, 0, (char *)0x002af4b8, 96);
  /* mem[0x0047e4dc] = eax */
  debug_malloc(0x00078000, 0, (char *)0x002af4b8, 97);
  /* mem[0x0047e4e4] = eax */
  debug_malloc(0x00078000, 0, (char *)0x002af4b8, 98);
  /* mem[0x0047e4ec] = eax */
  /* test ecx, ecx -> je 0x17dff0 */
  /* test eax, eax -> je 0x17dff0 */
  /* relift: relift: mov byte ptr [0x47e4d8], (char)ebx */
  error(0, (char *)0x002af48c);
  /* relift: relift: mov byte ptr [0x47e4d8], (char)eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
}

/* 0x17e010 */
void FUN_0017e010(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17e030 */
void FUN_0017e030(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17e040 */
void FUN_0017e040(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x47e4d8] */
  /* test (char)eax, (char)eax -> je 0x17e113 */
  /* test eax, eax -> jne 0x17e076 */
  display_assert((char *)0x002af524, (char *)0x002af4b8, 137, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e09f */
  display_assert((char *)0x002af50c, (char *)0x002af4b8, 138, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e0c8 */
  display_assert((char *)0x002af4e8, (char *)0x002af4b8, 139, 0);
  system_exit(0);
  debug_free((void *)(uintptr_t)eax, (char *)0x002af4b8, 141);
  debug_free((void *)(uintptr_t)ecx, (char *)0x002af4b8, 142);
  debug_free((void *)(uintptr_t)edx, (char *)0x002af4b8, 143);
  /* relift: relift: mov byte ptr [0x47e4d8], 0 */

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x17e130 */
void FUN_0017e130(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17e190 */
void FUN_0017e190(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x47e4d8] */
  /* test eax, eax -> jle 0x17e5a0 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256dd] */
  /* test (char)eax, (char)eax -> je 0x17e5a0 */
  /* test eax, eax -> jne 0x17e1ea */
  display_assert((char *)0x002af524, (char *)0x002af4b8, 320, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e213 */
  display_assert((char *)0x002af50c, (char *)0x002af4b8, 321, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e23c */
  display_assert((char *)0x002af4e8, (char *)0x002af4b8, 322, 0);
  system_exit(0);
  display_assert((char *)0x002af668, (char *)0x002af4b8, 323, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x47e4e8], esi -> jle 0x17e295 */
  display_assert((char *)0x002af620, (char *)0x002af4b8, 324, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x47e4f0], esi -> jle 0x17e2bd */
  display_assert((char *)0x002af5d0, (char *)0x002af4b8, 325, 0);
  system_exit(0);
  /* relift: cmp dword ptr [0x47e4f4], esi -> jle 0x17e2e5 */
  display_assert((char *)0x002af588, (char *)0x002af4b8, 326, 0);
  system_exit(0);
  qsort((void *)(uintptr_t)ecx, eax, 60, (void *)0x0017e130);
  /* relift: relift: mov word ptr [0x325652], 0xd */
  rasterizer_widget_set_zbuffer_enable(0, 0);
  rasterizer_widget_draw_sprite3d(0);
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)esi, 0);
  rasterizer_widget_end(0);
  FUN_0015a560(0);
  rasterizer_draw_dynamic_vertices(0, 0, 0, 0);
  FUN_0015a290();
  error(0, (char *)0x002af540);
  rasterizer_widget_submit_occlusion_test(0);
  /* test (char)eax, (char)eax -> je 0x17e4ca */
  /* test eax, eax -> jle 0x17e4ca */
  rasterizer_widget_set_zbuffer_enable(0, 0);
  rasterizer_widget_draw_sprite3d(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)esi, 0);
  rasterizer_widget_end(0);
  FUN_0015a560(0);
  rasterizer_draw_dynamic_vertices(0, 0, 0, 0);
  FUN_0015a290();
  rasterizer_widget_submit_occlusion_test(0);
  error(0, (char *)0x002af540);
  rasterizer_widget_submit_occlusion_test(0);
  /* relift: cmp edx, dword ptr [0x47e4f0] -> jge 0x17e594 */
  rasterizer_widget_set_zbuffer_enable(0, 0);
  /* cmp edi, -1 -> je 0x17e57b */
  rasterizer_widget_draw_sprite3d(0);
  /* test eax, eax -> je 0x17e55d */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)esi, edx);
  rasterizer_widget_end(0);
  FUN_0015a560(0);
  rasterizer_draw_dynamic_vertices(0, 0, 0, 0);
  FUN_0015a290();
  rasterizer_widget_submit_occlusion_test(0);
  error(0, (char *)0x002af540);
  rasterizer_widget_submit_occlusion_test(0);
  /* relift: relift: mov word ptr [0x325652], 0 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17e5b0 */
void FUN_0017e5b0(float *vert_ws, float *vert_offset, int transform_a, int transform_b)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x47e4d8] */
  /* test (char)eax, (char)eax -> je 0x17e7ef */
  /* relift: relift: mov (char)eax, byte ptr [0x3256dd] */
  /* test (char)eax, (char)eax -> je 0x17e7ef */
  /* test edi, edi -> je 0x17e5f1 */
  /* test ebx, ebx -> je 0x17e5f1 */
  /* test esi, esi -> je 0x17e5f4 */
  /* test eax, eax -> jne 0x17e614 */
  display_assert((char *)0x002af6b0, (char *)0x002af4b8, 171, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e63d */
  display_assert((char *)0x002af524, (char *)0x002af4b8, 172, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e666 */
  display_assert((char *)0x002af50c, (char *)0x002af4b8, 173, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e68f */
  display_assert((char *)0x002af4e8, (char *)0x002af4b8, 174, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x17e6b4 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17e7ec */
  /* relift: cmp dword ptr [esi], 0x3f800000 -> jne 0x17e6d2 */
  /* relift: cmp dword ptr [ecx], 0x3f800000 -> jne 0x17e6d2 */
  FUN_0017df10();
  /* cmp eax, -1 -> je 0x17e7ec */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  FUN_000d1c90((float *)(uintptr_t)eax);
  FUN_000d1c90((float *)(uintptr_t)ecx);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x17e7e3 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x17e800 */
void FUN_0017e800(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x47e4d8] */
  /* test (char)eax, (char)eax -> je 0x17eb02 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256dd] */
  /* test (char)eax, (char)eax -> je 0x17eb02 */
  /* test edi, edi -> je 0x17e84f */
  /* test eax, eax -> je 0x17e84f */
  /* test ebx, ebx -> je 0x17e84f */
  /* test esi, esi -> je 0x17e852 */
  /* test eax, eax -> je 0x17e852 */
  /* test eax, eax -> jne 0x17e872 */
  display_assert((char *)0x002af6d0, (char *)0x002af4b8, 229, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e89b */
  display_assert((char *)0x002af524, (char *)0x002af4b8, 230, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e8c4 */
  display_assert((char *)0x002af50c, (char *)0x002af4b8, 231, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17e8ed */
  display_assert((char *)0x002af4e8, (char *)0x002af4b8, 232, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x17e924 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x17e924 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17eaff */
  /* relift: cmp dword ptr [esi], 0x3f800000 -> jne 0x17e94d */
  /* relift: cmp dword ptr [edx], 0x3f800000 -> jne 0x17e94d */
  /* relift: cmp dword ptr [eax], 0x3f800000 -> jne 0x17e94d */
  FUN_0017df10();
  /* cmp eax, -1 -> je 0x17eaff */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  /* relift: relift: fld dword ptr [0x5a5bc8] */
  /* relift: relift: fld dword ptr [0x5a5bcc] */
  /* relift: relift: fld dword ptr [0x5a5bd0] */
  FUN_000d1c90((float *)(uintptr_t)eax);
  FUN_000d1c90((float *)(uintptr_t)ecx);
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x17eaa3 */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* test (char)eax, 0x41 -> jne 0x17eaf1 */
  /* test (char)eax, 0x41 -> jne 0x17eaf6 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17eb10 */
void FUN_0017eb10(float *vert_a, float *vert_b, int param_3)
{
  int eax = 0;
  int ecx = 0;

  FUN_0017e5b0((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0, 0);

  (void)eax;
  (void)ecx;
}

/* 0x17eb30 */
void FUN_0017eb30(float *point0, float *point1, float *point2, void *color)
{
  FUN_0017e800();
}

/* 0x17eb50 */
void FUN_0017eb50(void)
{
  int eax = 0;

  debug_malloc(0x00024000, 0, (char *)0x002af728, 41);
  /* mem[0x0047ec40] = eax */
  error(0, (char *)0x002af710);

  (void)eax;
}

/* 0x17eb90 */
void FUN_0017eb90(void)
{
  csmemset((void *)0x005a5400, 0, 368);
}

/* 0x17ebb0 */
void FUN_0017ebb0(void *param)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test ebx, ebx -> je 0x17ed19 */
  system_milliseconds();
  /* relift: relift: mov (int16_t)esi, word ptr [0x47ed50] */
  /* test (int16_t)esi, (int16_t)esi -> je 0x17ecf1 */
  /* cmp (int16_t)edx, 1 -> jle 0x17ec29 */
  /* cmp ecx, edi -> ja 0x17ec21 */
  /* relift: cmp ecx, dword ptr [ebp - 4] -> jbe 0x17ec29 */
  /* test (int16_t)edx, (int16_t)edx -> jg 0x17ec10 */
  /* relift: relift: mov (int16_t)esi, word ptr [0x47ed50] */
  /* cmp ecx, 1 -> ja 0x17ec52 */
  /* cmp ecx, 1 -> ja 0x17ec87 */
  /* mem[0x0047ec60] = eax */
  /* relift: relift: mov word ptr [0x47ed50], 0x3c */
  /* relift: relift: mov word ptr [0x47ed50], (int16_t)eax */
  /* relift: relift: mov word ptr [0x47ed50], 0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x17ed30 */
void FUN_0017ed30(void)
{
  int eax = 0;
  int ecx = 0;

  /* relift: relift: mov byte ptr [0x3256b8], 1 */
  system_milliseconds();
  /* mem[0x0047ec48] = eax */
  /* mem[0x0047ec4c] = 0 */
  /* mem[0x0047ec50] = eax */
  /* mem[0x0047ec54] = ecx */

  (void)eax;
  (void)ecx;
}

/* 0x17ed70 */
void FUN_0017ed70(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ed90 */
void FUN_0017ed90(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17edd0 */
void rasterizer_frame_statistics_count_static_vertices(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  rasterizer_widget_begin(0);
  display_assert((char *)0x002af788, (char *)0x002af728, 217, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17ee59 */
  display_assert((char *)0x002af760, (char *)0x002af728, 218, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)ecx, (void *)(uintptr_t)eax, eax);
  FUN_00091da0();
  /* test edi, edi -> jle 0x17eeb5 */
  /* cmp (int16_t)ebx, (int16_t)eax -> je 0x17eeb0 */
  /* cmp ecx, edi -> jl 0x17eea0 */
  rasterizer_widget_set_texture(0);
  /* cmp (int16_t)eax, 3 -> je 0x17eee1 */
  /* cmp (int16_t)eax, 4 -> je 0x17eee1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x17ef00 */
void FUN_0017ef00(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  FUN_001d90e0();
  /* relift: relift: mov (int16_t)eax, word ptr [0x32565e] */
  rect2d_offset((void *)(uintptr_t)eax, 0, 32);
  interface_draw_text(0, 0, 0, 0, 0, 0);
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002afde8);
  draw_string_set_tab_stops((void *)(uintptr_t)ecx, 0);
  draw_string_set_color((void *)(uintptr_t)edx);
  rasterizer_text_draw((void *)(uintptr_t)edx, (void *)0, (void *)(uintptr_t)ecx, 0, (char *)(uintptr_t)eax);
  /* relift: relift: mov (char)eax, byte ptr [0x3256b8] */
  /* test (char)eax, (char)eax -> je 0x17f21f */
  system_milliseconds();
  /* relift: relift: fld dword ptr [0x5a5410] */
  /* relift: relift: fld dword ptr [0x5a540c] */
  /* relift: relift: fld dword ptr [0x5a5408] */
  /* relift: relift: fld dword ptr [0x5a5400] */
  crt_sprintf((char *)(uintptr_t)edx, (char *)0x002afdc8);
  /* relift: relift: fld dword ptr [0x5a5410] */
  /* relift: relift: fld dword ptr [0x5a540c] */
  /* relift: relift: fld dword ptr [0x5a5408] */
  /* relift: relift: fld dword ptr [0x5a5400] */
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002afdac);
  draw_string_set_tab_stops((void *)(uintptr_t)edx, 0);
  draw_string_set_color((void *)(uintptr_t)eax);
  rasterizer_text_draw((void *)(uintptr_t)eax, (void *)0, (void *)(uintptr_t)edx, 0, (char *)(uintptr_t)ecx);
  /* relift: relift: mov (int16_t)eax, word ptr [0x3256ba] */
  draw_string_set_tab_stops((void *)(uintptr_t)eax, 0);
  draw_string_set_color((void *)(uintptr_t)ecx);
  crt_sprintf((char *)(uintptr_t)eax, (char *)0x002afd74);

  (void)eax;
  (void)ecx;
  (void)edx;
}
/* --- rasterizer_sprites.obj orphan shells (2026-07-26) --- */

/* orphan 0x17d030 */
int FUN_0017d030(float *position, int vis_index, int index)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}
