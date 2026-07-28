#include <stdint.h>
/* Render sprites by forwarding to the dynavob geometry renderer (0x17cfa0). */
void rasterizer_sprites_render(void *render_data, void *vertices)
{
  FUN_0015f8e0(render_data, vertices);
}
/* --- rasterizer_sprites.obj batch drafts (2026-07-26) --- */

/* FUN_0017cd60 (0x17cd60) — readable C lift. */
void FUN_0017cd60(int object_handle)
{
  FUN_00163590(object_handle);
}

/* FUN_0017cd70 (0x17cd70) — readable C lift. */
void FUN_0017cd70(void)
{
  FUN_00163910();
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

/* FUN_0017cdb0 (0x17cdb0) — readable C lift. */
void FUN_0017cdb0(void)
{
  ((void(*)(void))FUN_00163fe0)();
}

/* FUN_0017cdc0 (0x17cdc0) — readable C lift. */
void FUN_0017cdc0(void)
{
  FUN_001640d0();
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

/* FUN_0017ce00 (0x17ce00) — readable C lift. */
void FUN_0017ce00(void)
{
  ((void(*)(void))FUN_00164590)();
}

/* FUN_0017ce10 (0x17ce10) — readable C lift. */
void FUN_0017ce10(void)
{
  FUN_001609b0();
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

/* FUN_0017ce50 (0x17ce50) — readable C lift. */
void FUN_0017ce50(void)
{
  FUN_00164690();
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

/* FUN_0017ce70 (0x17ce70) — readable C lift (jmp thunk). */
void FUN_0017ce70(void)
{
  FUN_00160bf0();
}



/* FUN_0017ce80 (0x17ce80) — readable C lift. */
void FUN_0017ce80(void)
{
  FUN_00164cf0();
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

/* FUN_0017ceb0 (0x17ceb0) — readable C lift (auto_lift_trivial). */
void FUN_00165420(void);
void FUN_0017ceb0(void) {
  FUN_00165420();
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

/* FUN_0017cee0 (0x17cee0) — readable C lift. */
void FUN_0017cee0(void)
{
  ((void(*)(void))FUN_00165cb0)();
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

/* FUN_0017cf00 (0x17cf00) — readable C lift. */
void FUN_0017cf00(void)
{
  ((void(*)(void))FUN_00165de0)();
}

/* FUN_0017cf10 (0x17cf10) — readable C lift. */
void FUN_0017cf10(int pass_index)
{
  FUN_00166890(pass_index);
}

/* FUN_0017cf20 (0x17cf20) — readable C lift (auto_lift_trivial). */
void FUN_0017cf20(void) {
  ((void(*)(void))FUN_001677d0)();
}



/* FUN_0017cf30 (0x17cf30) — readable C lift (jmp thunk to 0x167920). */
void FUN_0017cf30(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x16794f */
  display_assert((char *)0x0029dc40, (char *)0x002a1cc8, 1036, 0);
  system_exit(0);
  /* FUN_00166010(obj, out, addend); */
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

/* FUN_0017cf50 (0x17cf50) — readable C lift (jmp thunk to 0x15f200). */
void FUN_0017cf50(void)
{
  FUN_0015f200();
}

/* FUN_0017cf60 (0x17cf60) — readable C lift. */
void FUN_0017cf60(uint32_t source, uint32_t param, int arg3, int arg4, uint32_t handle, int subcount2, float *origin, uint32_t widget_flags)
{
  FUN_0015f630(source, param, arg3, arg4, handle, subcount2, origin, widget_flags);
}

/* FUN_0017cf70 (0x17cf70) — readable C lift (jmp thunk to 0x15f210). */
void FUN_0017cf70(void)
{
  FUN_0015f210();
}


/* FUN_0017cf80 (0x17cf80) — readable C lift. */
void FUN_0017cf80(int arg1, int arg2, uint32_t handle, int subcount2)
{
  ((void(*)(int, int, uint32_t, int))FUN_0015f540)(arg1, arg2, handle, subcount2);
}

/* FUN_0017cf90 (0x17cf90) — readable C lift (jmp thunk to 0x15f220). */
void FUN_0017cf90(void)
{
  FUN_0015f220();
}


/* FUN_0017cfb0 (0x17cfb0) — readable C lift. */
void FUN_0017cfb0(int object_handle, int datum, float *position, int callback)
{
  FUN_0017ae90(object_handle, datum, position, callback);
}

/* FUN_0017cfc0 (0x17cfc0) — readable C lift. */
void FUN_0017cfc0(int param_1, int param_2)
{
  FUN_0017b000(param_1, param_2);
}

/* FUN_0017cfd0 (0x17cfd0) — readable C lift. */
char FUN_0017cfd0(int param_1, int param_2, short param_3)
{
  return FUN_0017b480(param_1, param_2, param_3);
}

/* FUN_0017cfe0 (0x17cfe0) — readable C lift. */
void FUN_0017cfe0(int tex_flags)
{
  FUN_0017b540(tex_flags);
}

/* FUN_0017cff0 (0x17cff0) — readable C lift (jmp thunk to 0x17b580). */
void FUN_0017cff0(void)
{
  ((void(*)(void))FUN_0017b580)();
}


/* FUN_0017d000 (0x17d000) — readable C lift. */
void FUN_0017d000(void)
{
  FUN_0017b5c0();
}

/* FUN_0017d010 (0x17d010) — readable C lift (jmp thunk). */
void FUN_0017d010(float *position, float radius, float *scale2d, float angle, uint32_t color)
{
  FUN_0017b7d0(position, radius, scale2d, angle, color);
}

/* FUN_0017d020 (0x17d020) — readable C lift (jmp thunk). */
void FUN_0017d020(void)
{
  FUN_0017ad90();
}



/* FUN_0017d040 (0x17d040) — readable C lift. */
void FUN_0017d040(void)
{
  (void)((int(*)(void))FUN_0017adc0)();
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

/* FUN_0017d060 (0x17d060) — readable C lift. */
void FUN_0017d060(void)
{
  FUN_0016e160();
}

/* FUN_0017d070 (0x17d070) — readable C lift. */
void FUN_0017d070(void)
{
  FUN_0016e2e0();
}

/* FUN_0017d080 (0x17d080) — readable C lift. */
void FUN_0017d080(float *v, float t, float *color)
{
  float scale;
  float p0[3];
  float p1[3];

  scale = t * *(float *)0x253398;
  p0[0] = v[0] - scale; p0[1] = v[1]; p0[2] = v[2];
  p1[0] = v[0] + scale; p1[1] = v[1]; p1[2] = v[2];
  FUN_0015a7f0(p0, p1, color, color);
  p0[0] = v[0]; p0[1] = v[1] - scale; p0[2] = v[2];
  p1[0] = v[0]; p1[1] = v[1] + scale; p1[2] = v[2];
  FUN_0015a7f0(p0, p1, color, color);
  p0[0] = v[0]; p0[1] = v[1]; p0[2] = v[2] - scale;
  p1[0] = v[0]; p1[1] = v[1]; p1[2] = v[2] + scale;
  FUN_0015a7f0(p0, p1, color, color);
}



/* FUN_0017d150 (0x17d150) — readable C lift. */
void FUN_0017d150(float *a, float *b, float t, float *color)
{
  float local[3];

  local[0] = a[0] + t * b[0];
  local[1] = a[1] + t * b[1];
  local[2] = a[2] + t * b[2];
  FUN_0015a7f0(a, local, color, color);
}



/* FUN_0017d1a0 (0x17d1a0) — readable C lift: optional debug ray, then FUN_0016b180. */
void FUN_0017d1a0(int flag)
{
  short depth; float dir[3]; unsigned char hit[0x5c];
  if ((char)flag != 0) { *(int *)0x47e4cc = -1; FUN_0016b180(flag); return; }
  if (*(short *)0x4761d8 >= 0x20) {
    display_assert((const char *)0x253440,(const char *)0x2af1ec,0x2e4,1); system_exit(-1);
  }
  depth=*(short *)0x4761d8; *(short *)0x4761d8=(short)(depth+1);
  dir[0]=*(float *)0x5a5bd4 * *(float *)0x2af240;
  dir[1]=*(float *)0x5a5bd8 * *(float *)0x2af240;
  dir[2]=*(float *)0x5a5bdc * *(float *)0x2af240;
  *(short *)(0x5a8c80+(int)depth*2)=0x15;
  if (FUN_0014df70(0xfff80u,(float *)0x5a5bc8,dir,(int)*(short *)0x506548,(short *)hit))
    *(int *)0x47e4cc=*(int *)(hit+0x38);
  if (*(short *)0x4761d8<=1) {
    display_assert((const char *)0x253418,(const char *)0x2af1ec,0x2f4,1); system_exit(-1);
  }
  (*(short *)0x4761d8)--; FUN_0016b180(flag);
}


/* FUN_0017d2b0 (0x17d2b0) — readable C lift (restored pre-naked). */
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


/* FUN_0017d8f0 (0x17d8f0) — readable C lift. */
float FUN_0017d8f0(void)
{
  return (float)game_time_get() * *(float *)0x2546a4;
}



/* rasterizer_screen_effects_initialize (0x17d910) — readable C lift. */
void rasterizer_screen_effects_initialize(void)
{
  void *p;

  p = game_state_malloc((const char *)0x2af368, 0, 0x78);
  *(void **)0x47e4d4 = p;
  if (!p) {
    display_assert((const char *)0x2af314, (const char *)0x2af334, 0x36, 1);
    system_exit(-1);
  }
}



/* FUN_0017d950 (0x17d950) — readable C lift. */
void FUN_0017d950(void)
{
  void *p;

  p = *(void **)0x47e4d4;
  if (!p)
    return;
  csmemset(p, 0, 0x78);
  p = *(void **)0x47e4d4;
  *(uint32_t *)((char *)p + 0x64) = 0x3f800000;
  *(uint32_t *)((char *)p + 0x68) = 0x3f800000;
  *(uint32_t *)((char *)p + 0x6c) = 0x3f800000;
  *(uint32_t *)((char *)p + 0x70) = 0x3f800000;
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

/* FUN_0017d9a0 (0x17d9a0) — readable C lift. */
void FUN_0017d9a0(short index, float value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr && index >= 0 && index < 4) {
    *(float *)(spr + 0x64 + (int)index * 4) = value;
  }
}

/* FUN_0017d9d0 (0x17d9d0) — readable C lift. */
float FUN_0017d9d0(short index)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (!spr || index < 0 || index >= 4) {
    return *(float *)0x2533c0;
  }
  return *(float *)(spr + 0x64 + (int)index * 4);
}

/* FUN_0017da00 (0x17da00) — readable C lift. */
void FUN_0017da00(int a0)
{
  unsigned char *p;

  p = *(unsigned char **)0x47e4d4;
  if (!p)
    return;
  if (a0 || !p[0x39]) {
    csmemset(p, 0, 0x38);
    p = *(unsigned char **)0x47e4d4;
    p[0x39] = 1;
  }
  p[0x38] = 1;
}



/* FUN_0017da40 (0x17da40) — readable C lift. */
void FUN_0017da40(int a0, int a1, float a2, float a3, float a4)
{
  unsigned char *p;
  float t;

  p = *(unsigned char **)0x47e4d4;
  if (!p)
    return;
  p[0x23] = 0;
  *(unsigned short *)(p + 0x24) = 0;
  *(unsigned int *)(p + 0x28) = 0;
  *(unsigned int *)(p + 0x2c) = 0;
  *(unsigned int *)(p + 0x30) = 0;
  *(unsigned int *)(p + 0x34) = 0;
  *(unsigned short *)(p + 0) = (unsigned short)a0;
  *(unsigned short *)(p + 2) = (unsigned short)a1;
  *(float *)(p + 0x3c) = a2;
  *(float *)(p + 0x40) = a3;
  t = (float)game_time_get() * *(float *)0x2546a4;
  p = *(unsigned char **)0x47e4d4;
  *(float *)(p + 0x44) = t;
  *(float *)(p + 0x48) = t + a4;
}



/* FUN_0017dab0 (0x17dab0) — readable C lift. */
void FUN_0017dab0(int a0, float a1, float a2, float a3, int a4, float a5)
{
  unsigned char *p;
  float t;

  p = *(unsigned char **)0x47e4d4;
  if (!p)
    return;
  p[0x23] = 0;
  *(unsigned short *)(p + 0x24) = 0;
  *(unsigned int *)(p + 0x28) = 0;
  *(unsigned int *)(p + 0x2c) = 0;
  *(unsigned int *)(p + 0x30) = 0;
  *(unsigned int *)(p + 0x34) = 0;
  *(int *)(p + 0x4c) = a0;
  *(float *)(p + 0x50) = a1;
  *(float *)(p + 0x54) = a2;
  *(float *)(p + 0x58) = a3;
  t = (float)game_time_get() * *(float *)0x2546a4;
  p = *(unsigned char **)0x47e4d4;
  *(float *)(p + 0x5c) = t;
  *(float *)(p + 0x60) = t + a5;
  p[0x20] = (unsigned char)a4;
  p[0x21] = 0;
  p[0x22] = 0;
}



/* FUN_0017db20 (0x17db20) — readable C lift. */
void FUN_0017db20(int a, int b, int c)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x14) = a;
    *(int *)(spr + 0x18) = b;
    *(int *)(spr + 0x1c) = c;
  }
}

/* rasterizer_screen_effect_set_video (0x17db40) — readable C lift (restored pre-naked). */
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


/* FUN_0017dc60 (0x17dc60) — readable C lift. */
void FUN_0017dc60(void)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    spr[0x38] = 0;
  }
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

/* FUN_0017dec0 (0x17dec0) — readable C lift. */
void FUN_0017dec0(int value)
{
  char *spr;

  spr = *(char **)0x47e4d4;
  if (spr) {
    *(int *)(spr + 0x74) = value;
  }
}

/* FUN_0017dee0 (0x17dee0) — readable C lift. */
float FUN_0017dee0(void)
{
  char *spr;
  float v;

  spr = *(char **)0x47e4d4;
  v = *(float *)0x2af1ac;
  if (spr) {
    if (*(float *)(spr + 0x74) > *(float *)0x2533c0) {
      v = *(float *)(spr + 0x74);
    }
  }
  return v;
}

/* FUN_0017df10 (0x17df10) — readable C lift. */
int FUN_0017df10(int *counter)
{
  int v;

  v = *counter;
  if (v >= 0x2000 || *(int *)0x47e4f4 >= 0x2000) {
    if (!*(unsigned char *)0x47e4f8) {
      error(2, (const char *)0x2af460);
      *(unsigned char *)0x47e4f8 = 1;
    }
    return -1;
  }
  *counter = v + 1;
  *(int *)0x47e4f4 = *(int *)0x47e4f4 + 1;
  if (*(short *)0x3256ba == 2)
    *(int *)0x5a5540 = *(int *)0x5a5540 + 1;
  return v;
}



/* FUN_0017df80 (0x17df80) — readable C lift. */
char FUN_0017df80(void)
{
  void *a;
  void *b;
  void *c;

  a = debug_malloc(0x78000, 0, (const char *)0x2af4b8, 0x60);
  *(void **)0x47e4dc = a;
  b = debug_malloc(0x78000, 0, (const char *)0x2af4b8, 0x61);
  *(void **)0x47e4e4 = b;
  c = debug_malloc(0x78000, 0, (const char *)0x2af4b8, 0x62);
  *(void **)0x47e4ec = c;
  if (a && b && c) {
    *(unsigned char *)0x47e4d8 = 1;
    return 1;
  }
  error(2, (const char *)0x2af48c);
  *(unsigned char *)0x47e4d8 = 0;
  return 0;
}



/* FUN_0017e010 (0x17e010) — readable C lift. */
void FUN_0017e010(void)
{
  *(int *)0x47e4e0 = 0;
  *(int *)0x47e4e8 = 0;
  *(int *)0x47e4f0 = 0;
  *(int *)0x47e4f4 = 0;
}

/* 0x17e030 */
void FUN_0017e030(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* FUN_0017e040 (0x17e040) — readable C lift. */
void FUN_0017e040(void)
{
  void *a;
  void *b;
  void *c;

  if (!*(unsigned char *)0x47e4d8)
    return;
  a = *(void **)0x47e4dc;
  if (!a) {
    display_assert((const char *)0x2af524, (const char *)0x2af4b8, 0x89, 1);
    system_exit(-1);
  }
  b = *(void **)0x47e4e4;
  if (!b) {
    display_assert((const char *)0x2af50c, (const char *)0x2af4b8, 0x8a, 1);
    system_exit(-1);
  }
  c = *(void **)0x47e4ec;
  if (!c) {
    display_assert((const char *)0x2af4e8, (const char *)0x2af4b8, 0x8b, 1);
    system_exit(-1);
  }
  debug_free(*(void **)0x47e4dc, (const char *)0x2af4b8, 0x8d);
  debug_free(*(void **)0x47e4e4, (const char *)0x2af4b8, 0x8e);
  debug_free(*(void **)0x47e4ec, (const char *)0x2af4b8, 0x8f);
  *(unsigned char *)0x47e4d8 = 0;
}



/* FUN_0017e130 (0x17e130) — readable C lift. */
int FUN_0017e130(unsigned char *a, unsigned char *b)
{
  int ecx;
  float fa;
  float fb;

  ecx = 0;
  if (!a[0x38]) {
    if (!b[0x38]) {
      fa = *(float *)(a + 0x34);
      fb = *(float *)(b + 0x34);
      if (fa > fb)
        ecx = 1;
      if (fa < fb)
        return -1;
      return ecx;
    }
  } else {
    ecx = -(*(short *)(a + 0x30));
  }
  if (b[0x38])
    ecx += *(short *)(b + 0x30);
  return ecx;
}



/* FUN_0017e190 (0x17e190) — readable C lift (restored pre-naked). */
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


/* FUN_0017e5b0 (0x17e5b0) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b17e5b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e5b0_exitfn)(int) = system_exit;
static void (*const b17e5b0_c17df10)(void) = FUN_0017df10;
static unsigned int (*const b17e5b0_d1c90)(float *) = FUN_000d1c90;

__attribute__((naked, noinline))
void FUN_0017e5b0(float *vert_ws __attribute__((unused)), float *vert_offset __attribute__((unused)), int transform_a __attribute__((unused)), int transform_b __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e5b0_13\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e5b0_13\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0017e5b0_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017e5b0_1\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0017e5b0_2\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_3\n\t"
      "jmp .LFUN_0017e5b0_2\n\t"
      ".LFUN_0017e5b0_1:\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e5b0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xab\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af6b0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_3:\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_4\n\t"
      "pushl $1\n\t"
      "pushl $0xac\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_4:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0xad\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_5:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e5b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0xae\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e5b0_6:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e5b0_7\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e5b0_12\n\t"
      ".LFUN_0017e5b0_7:\n\t"
      "cmpl $0x3f800000, (%%esi)\n\t"
      "jne .LFUN_0017e5b0_8\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "cmpl $0x3f800000, (%%ecx)\n\t"
      "jne .LFUN_0017e5b0_8\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0x47e4e8, %%eax\n\t"
      "jmp .LFUN_0017e5b0_9\n\t"
      ".LFUN_0017e5b0_8:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x47e4f0, %%eax\n\t"
      ".LFUN_0017e5b0_9:\n\t"
      "pushl %%eax\n\t"
      "call *%[c17df10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0017e5b0_12\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x47e4e4, %%ecx\n\t"
      "jne .LFUN_0017e5b0_10\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      ".LFUN_0017e5b0_10:\n\t"
      "flds 0x5a5bc8\n\t"
      "addl %%ecx, %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movw $2, 0x30(%%esi)\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e5b0_11\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_0017e5b0_11:\n\t"
      "movb -0x1(%%ebp), %%dl\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%dl, 0x38(%%esi)\n\t"
      ".LFUN_0017e5b0_12:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e5b0_13:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e5b0_assert), [exitfn] "m"(b17e5b0_exitfn), [c17df10] "m"(b17e5b0_c17df10), [d1c90] "m"(b17e5b0_d1c90)
      : "memory");
}
#else
#error "FUN_0017e5b0: clang naked draft required"
#endif


/* FUN_0017e800 (0x17e800) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b17e800_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e800_exitfn)(int) = system_exit;
static void (*const b17e800_c17df10)(void) = FUN_0017df10;
static unsigned int (*const b17e800_d1c90)(float *) = FUN_000d1c90;

__attribute__((naked, noinline))
void FUN_0017e800(int a0, int a1, int a2, int a3, int a4, int a5)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e800_16\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e800_16\n\t"
      "pushl %%ebx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "je .LFUN_0017e800_1\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e800_1\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017e800_1\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "je .LFUN_0017e800_2\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e800_2\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_3\n\t"
      "jmp .LFUN_0017e800_2\n\t"
      ".LFUN_0017e800_1:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      ".LFUN_0017e800_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xe5\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af6d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_3:\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_4\n\t"
      "pushl $1\n\t"
      "pushl $0xe6\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_4:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_5\n\t"
      "pushl $1\n\t"
      "pushl $0xe7\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_5:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e800_6\n\t"
      "pushl $1\n\t"
      "pushl $0xe8\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e800_6:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e800_7\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017e800_7\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_15\n\t"
      ".LFUN_0017e800_7:\n\t"
      "cmpl $0x3f800000, (%%esi)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "cmpl $0x3f800000, (%%edx)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "cmpl $0x3f800000, (%%eax)\n\t"
      "jne .LFUN_0017e800_8\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0x47e4e0, %%eax\n\t"
      "jmp .LFUN_0017e800_9\n\t"
      ".LFUN_0017e800_8:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl $0x47e4f0, %%eax\n\t"
      ".LFUN_0017e800_9:\n\t"
      "pushl %%eax\n\t"
      "call *%[c17df10]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_0017e800_15\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "imull $0x3c, %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x47e4dc, %%ecx\n\t"
      "jne .LFUN_0017e800_10\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      ".LFUN_0017e800_10:\n\t"
      "flds 0x5a5bc8\n\t"
      "addl %%ecx, %%eax\n\t"
      "fsubs (%%edi)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%esi, %%ecx\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5bc8\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x5a5bcc\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x5a5bd0\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "movw $3, 0x30(%%esi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl (%%eax), %%edx\n\t"
      "leal 0x10(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "leal 0x20(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%ebx), %%eax\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, 0x2c(%%esi)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e800_12\n\t"
      ".LFUN_0017e800_11:\n\t"
      "fld %%st(0)\n\t"
      ".LFUN_0017e800_12:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_13\n\t"
      "fcoms -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017e800_14\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "popl %%edi\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%al, 0x38(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017e800_13:\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      ".LFUN_0017e800_14:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstps 0x34(%%esi)\n\t"
      "movb %%al, 0x38(%%esi)\n\t"
      ".LFUN_0017e800_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e800_16:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e800_assert), [exitfn] "m"(b17e800_exitfn), [c17df10] "m"(b17e800_c17df10), [d1c90] "m"(b17e800_d1c90)
      : "memory");
}
#else
#error "FUN_0017e800: clang naked draft required"
#endif


/* FUN_0017eb10 (0x17eb10) — readable C lift. */
void FUN_0017eb10(float *vert_a, float *vert_b, int param_3)
{
  FUN_0017e5b0(vert_a, vert_b, param_3, param_3);
}

/* FUN_0017eb30 (0x17eb30) — readable C lift. */
void FUN_0017eb30(float *point0, float *point1, float *point2, void *color)
{
  FUN_0017e800(point0, point1, point2, color, color, color);
}

/* FUN_0017eb50 (0x17eb50) — readable C lift. */
char FUN_0017eb50(void)
{
  void *p;

  p = debug_malloc(0x24000, 0, (const char *)0x2af728, 0x29);
  *(void **)0x47ec40 = p;
  if (!p) {
    error(2, (const char *)0x2af710);
    return 0;
  }
  return 1;
}



/* FUN_0017eb90 (0x17eb90) — readable C lift. */
void FUN_0017eb90(void)
{
  csmemset((void *)0x5a5400, 0, 0x170);
}

/* FUN_0017ebb0 (0x17ebb0) — readable C lift (restored pre-naked). */
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


/* FUN_0017ed30 (0x17ed30) — readable C lift. */
void FUN_0017ed30(void)
{
  *(unsigned char *)0x3256b8 = 1;
  *(unsigned int *)0x47ec48 = system_milliseconds();
  *(unsigned int *)0x47ec4c = 0;
  *(unsigned int *)0x47ec50 = *(unsigned int *)0x325668;
  *(unsigned int *)0x47ec54 = *(unsigned int *)0x32566c;
}



/* FUN_0017ed70 (0x17ed70) — readable C lift. */
char FUN_0017ed70(unsigned short a, unsigned short b)
{
  return a > b;
}

/* FUN_0017ed90 (0x17ed90) — readable C lift. */
int FUN_0017ed90(short *a, short *b)
{
  if (!a) {
    return 0;
  }
  if (!b) {
    return 0;
  }
  if (a[0] == 1) {
    return *(int *)(a + 2) + 2;
  }
  if (a[0] == 0) {
    return *(int *)(b + 2);
  }
  return 0;
}

/* rasterizer_frame_statistics_count_static_vertices (0x17edd0) — readable C lift (restored pre-naked). */
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


/* FUN_0017ef00 (0x17ef00) — readable C lift (restored pre-naked). */
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

/* FUN_0017d030 (0x17d030) — readable C lift. */
int FUN_0017d030(float *position, int vis_index, int index)
{
  return FUN_0017ba10(position, vis_index, index);
}

