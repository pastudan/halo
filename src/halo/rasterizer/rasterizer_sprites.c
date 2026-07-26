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

/* FUN_0017d2b0 (0x17d2b0) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b17d2b0_chkstk)(void) = FUN_001d90e0;
static void (*const b17d2b0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17d2b0_exitfn)(int) = system_exit;
static float * (*const b17d2b0_c17ffc0)(float *param_1, unsigned int param_2) = FUN_0017ffc0;
static void (*const b17d2b0_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b17d2b0_mscale)(float *, float *, float *) = matrix_scale_transform_vector;
static float (*const b17d2b0_norm)(float *) = normalize3d;
static char * (*const b17d2b0_c8dff0)(char *destination, const char *source) = csstrcpy;
static int (*const b17d2b0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static char * (*const b17d2b0_c8dc30)(char *destination, const char *source) = FUN_0008dc30;
static void (*const b17d2b0_c189150)(char flag, float *position, float scale, void *color) = FUN_00189150;
static void (*const b17d2b0_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;

__attribute__((naked, noinline))
void FUN_0017d2b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl $0x20280, %%eax\n\t"
      "call *%[chkstk]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%edi\n\t"
      "jne .LFUN_0017d2b0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x33e\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x25bc3c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_1:\n\t"
      "movb 0x3256bf, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017d2b0_37\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl 0x47e4cc, %%eax\n\t"
      "jne .LFUN_0017d2b0_37\n\t"
      "cmpw $1, 0x44(%%edi)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl $0xffffffff, -0x28(%%ebp)\n\t"
      "je .LFUN_0017d2b0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x359\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af2d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_2:\n\t"
      "movl 0x48(%%edi), %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%esi, -0x14(%%ebp)\n\t"
      "jle .LFUN_0017d2b0_28\n\t"
      "leal -0x2025c(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "jmp .LFUN_0017d2b0_4\n\t"
      ".LFUN_0017d2b0_3:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "jmp .LFUN_0017d2b0_4\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_4:\n\t"
      "movl 0x3c(%%edi), %%ecx\n\t"
      "movzwl (%%ecx,%%eax,2), %%eax\n\t"
      "movzwl %%ax, %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl 0x30(%%edi), %%eax\n\t"
      "shll $5, %%esi\n\t"
      "movsbl 0x1c(%%esi,%%eax,1), %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "movl $0x55555556, %%eax\n\t"
      "imull %%ecx\n\t"
      "movswl 0x1e(%%esi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movsbl 0x1d(%%esi), %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%edx, %%edi\n\t"
      "movl $0x55555556, %%eax\n\t"
      "fmuls 0x290dd8\n\t"
      "imull %%ecx\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x80(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, -0x5c(%%ebp)\n\t"
      "movl $0, -0x58(%%ebp)\n\t"
      "movl $0, -0x54(%%ebp)\n\t"
      "movl $0, -0x50(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "movl $0, -0x48(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x44(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x3c(%%ebp)\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, -0x74(%%ebp)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, -0x70(%%ebp)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x4(%%ecx), %%di\n\t"
      "movl %%eax, -0x6c(%%ebp)\n\t"
      "jl .LFUN_0017d2b0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x36e\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af2a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_5:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "cmpw 0x4(%%edx), %%bx\n\t"
      "jl .LFUN_0017d2b0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af280\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_0017d2b0_7\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_0017d2b0_8\n\t"
      ".LFUN_0017d2b0_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x2af1ec\n\t"
      "pushl $0x2af254\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017d2b0_8:\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_0017d2b0_9\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "leal -0x5c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x50(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl (%%edx), %%eax\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[mscale]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0017d2b0_9:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_0017d2b0_10\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movswl %%bx, %%edi\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[xfrmpt]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0x74(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[mscale]\n\t"
      "addl $0x18, %%esp\n\t"
      ".LFUN_0017d2b0_10:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "leal -0x68(%%ebp), %%edx\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "flds -0x40(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_0017d2b0_21\n\t"
      "leal -0x20280(%%ebp), %%ecx\n\t"
      ".LFUN_0017d2b0_11:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_12\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fcomps 0x4(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_12\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x8(%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0017d2b0_13\n\t"
      ".LFUN_0017d2b0_12:\n\t"
      "incl %%edi\n\t"
      "addl $0x40, %%ecx\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jl .LFUN_0017d2b0_11\n\t"
      "jmp .LFUN_0017d2b0_21\n\t"
      ".LFUN_0017d2b0_13:\n\t"
      "movb 0x3c(%%ecx), %%al\n\t"
      "cmpb $0xc, %%al\n\t"
      "jae .LFUN_0017d2b0_17\n\t"
      "movzbl %%al, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0017d2b0_16\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_0017d2b0_14:\n\t"
      "movw -0x14(%%ebp), %%bx\n\t"
      "cmpw %%bx, 0xc(%%ecx,%%eax,2)\n\t"
      "je .LFUN_0017d2b0_15\n\t"
      "movzbl 0x3c(%%ecx), %%ebx\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_0017d2b0_14\n\t"
      ".LFUN_0017d2b0_15:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0017d2b0_16:\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_0017d2b0_17\n\t"
      "movw -0x14(%%ebp), %%dx\n\t"
      "movw %%dx, 0xc(%%ecx,%%esi,2)\n\t"
      "incb 0x3c(%%ecx)\n\t"
      ".LFUN_0017d2b0_17:\n\t"
      "movb 0x3d(%%ecx), %%al\n\t"
      "cmpb $0xc, %%al\n\t"
      "jae .LFUN_0017d2b0_21\n\t"
      "movzbl %%al, %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%esi, %%esi\n\t"
      "jle .LFUN_0017d2b0_20\n\t"
      "xorl %%eax, %%eax\n\t"
      "nop\n\t"
      ".LFUN_0017d2b0_18:\n\t"
      "movswl 0x24(%%ecx,%%eax,2), %%ebx\n\t"
      "movzwl -0x10(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "je .LFUN_0017d2b0_19\n\t"
      "movzbl 0x3d(%%ecx), %%ebx\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jl .LFUN_0017d2b0_18\n\t"
      ".LFUN_0017d2b0_19:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_0017d2b0_20:\n\t"
      "movswl %%dx, %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .LFUN_0017d2b0_21\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "movw %%dx, 0x24(%%ecx,%%esi,2)\n\t"
      "incb 0x3d(%%ecx)\n\t"
      ".LFUN_0017d2b0_21:\n\t"
      "cmpl %%ebx, %%edi\n\t"
      "jne .LFUN_0017d2b0_27\n\t"
      "cmpl $0x800, %%ebx\n\t"
      "jge .LFUN_0017d2b0_27\n\t"
      "flds -0x20(%%ebp)\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "fsubs 0x5a5bc8\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "leal -0x24(%%ecx), %%eax\n\t"
      "fsubs 0x5a5bcc\n\t"
      "movl %%edx, (%%eax)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "fsubs 0x5a5bd0\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "movw -0x14(%%ebp), %%ax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movw -0x10(%%ebp), %%dx\n\t"
      "fld %%st(2)\n\t"
      "movw %%ax, -0x18(%%ecx)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "movw %%dx, (%%ecx)\n\t"
      "movb $1, 0x18(%%ecx)\n\t"
      "movb $1, 0x19(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fld %%st(0)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0017d2b0_22\n\t"
      "fdivrs 0x2533c8\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xde, 0xcc\n\t"
      "fxch %%st(2)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "jmp .LFUN_0017d2b0_23\n\t"
      ".LFUN_0017d2b0_22:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_0017d2b0_23:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x5a5bd8\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmuls 0x5a5bd4\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x64(%%ebp)\n\t"
      ".byte 0xde, 0xc2\n\t"
      "fxch %%st(2)\n\t"
      "fmuls -0x68(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_0017d2b0_24\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps -0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0017d2b0_25\n\t"
      ".LFUN_0017d2b0_24:\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_0017d2b0_26\n\t"
      ".LFUN_0017d2b0_25:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      ".LFUN_0017d2b0_26:\n\t"
      "incl %%ebx\n\t"
      "addl $0x40, %%ecx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      ".LFUN_0017d2b0_27:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0x48(%%ecx), %%edx\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $2, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jl .LFUN_0017d2b0_3\n\t"
      ".LFUN_0017d2b0_28:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "jle .LFUN_0017d2b0_36\n\t"
      "leal -0x20244(%%ebp), %%ebx\n\t"
      "jmp .LFUN_0017d2b0_29\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_29:\n\t"
      "cmpl -0x28(%%ebp), %%edi\n\t"
      "leal -0x3c(%%ebx), %%esi\n\t"
      "jne .LFUN_0017d2b0_34\n\t"
      "pushl $0x2af250\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dff0]\n\t"
      "movzbl (%%ebx), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0017d2b0_31\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017d2b0_30:\n\t"
      "xorl %%edx, %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movswl 0xc(%%esi,%%eax,2), %%eax\n\t"
      "setne %%dl\n\t"
      "leal -0x180(%%ebp), %%ecx\n\t"
      "decl %%edx\n\t"
      "andl $0xfffffff4, %%edx\n\t"
      "addl $0x2c, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2af248\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x180(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl (%%ebx), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0017d2b0_30\n\t"
      ".LFUN_0017d2b0_31:\n\t"
      "pushl $0x2af244\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl 0x3d(%%esi), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jle .LFUN_0017d2b0_33\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_0017d2b0_32:\n\t"
      "xorl %%edx, %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movswl 0x24(%%esi,%%eax,2), %%eax\n\t"
      "setne %%dl\n\t"
      "leal -0x280(%%ebp), %%ecx\n\t"
      "decl %%edx\n\t"
      "andl $0xfffffff4, %%edx\n\t"
      "addl $0x2c, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2af248\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "leal -0x280(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8dc30]\n\t"
      "movzbl 0x3d(%%esi), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0017d2b0_32\n\t"
      ".LFUN_0017d2b0_33:\n\t"
      "movl 0x2ee6d0, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x3d000000\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189150]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5ab100\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "addl $0x20, %%esp\n\t"
      "jmp .LFUN_0017d2b0_35\n\t"
      ".LFUN_0017d2b0_34:\n\t"
      "movl 0x2ee6c4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3d000000\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "call *%[c189150]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_0017d2b0_35:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%edi\n\t"
      "addl $0x40, %%ebx\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%edi, 0x10(%%ebp)\n\t"
      "jl .LFUN_0017d2b0_29\n\t"
      ".LFUN_0017d2b0_36:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017d2b0_37:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [chkstk] "m"(b17d2b0_chkstk), [assert] "m"(b17d2b0_assert), [exitfn] "m"(b17d2b0_exitfn), [c17ffc0] "m"(b17d2b0_c17ffc0), [xfrmpt] "m"(b17d2b0_xfrmpt), [mscale] "m"(b17d2b0_mscale), [norm] "m"(b17d2b0_norm), [c8dff0] "m"(b17d2b0_c8dff0), [c1d90f0] "m"(b17d2b0_c1d90f0), [c8dc30] "m"(b17d2b0_c8dc30), [c189150] "m"(b17d2b0_c189150), [c189cb0] "m"(b17d2b0_c189cb0)
      : "memory");
}
#else
#error "FUN_0017d2b0: clang naked draft required"
#endif


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

/* FUN_0017e190 (0x17e190) — XBE naked draft (batch 302). */
#if defined(__clang__)
static void (*const b17e190_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e190_exitfn)(int) = system_exit;
static void __cdecl (*const b17e190_c1d9260)(void *base, size_t nmemb, size_t size, int (__cdecl *compar)(const void *, const void *)) = qsort;
static int (*const b17e190_rzbuf)(int, int) = rasterizer_widget_set_zbuffer_enable;
static int (*const b17e190_rspr)(int) = rasterizer_widget_draw_sprite3d;
static void * (*const b17e190_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void (*const b17e190_rend)(int) = rasterizer_widget_end;
static void (*const b17e190_c15a560)(char additive) = FUN_0015a560;
static void __cdecl (*const b17e190_c15d5b0)(int first_primitive_index, int primitive_count, int dynamic_vertex_buffer_index, short vertices_per_primitive) = rasterizer_draw_dynamic_vertices;
static void (*const b17e190_c15a290)(void) = FUN_0015a290;
static void (*const b17e190_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void (*const b17e190_rocc)(int) = rasterizer_widget_submit_occlusion_test;

__attribute__((naked, noinline))
void FUN_0017e190(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movb 0x47e4d8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "je .LFUN_0017e190_25\n\t"
      "movl 0x47e4f4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0017e190_25\n\t"
      "movb 0x3256dd, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e190_25\n\t"
      "movl 0x47e4dc, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_1\n\t"
      "pushl $1\n\t"
      "pushl $0x140\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af524\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_1:\n\t"
      "movl 0x47e4e4, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_2\n\t"
      "pushl $1\n\t"
      "pushl $0x141\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af50c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_2:\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017e190_3\n\t"
      "pushl $1\n\t"
      "pushl $0x142\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af4e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_3:\n\t"
      "movl 0x47e4e0, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl $0x2000, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "pushl %%edi\n\t"
      "jle .LFUN_0017e190_4\n\t"
      "pushl $1\n\t"
      "pushl $0x143\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af668\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_4:\n\t"
      "cmpl %%esi, 0x47e4e8\n\t"
      "jle .LFUN_0017e190_5\n\t"
      "pushl $1\n\t"
      "pushl $0x144\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af620\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_5:\n\t"
      "cmpl %%esi, 0x47e4f0\n\t"
      "jle .LFUN_0017e190_6\n\t"
      "pushl $1\n\t"
      "pushl $0x145\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af5d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_6:\n\t"
      "cmpl %%esi, 0x47e4f4\n\t"
      "jle .LFUN_0017e190_7\n\t"
      "pushl $1\n\t"
      "pushl $0x146\n\t"
      "pushl $0x2af4b8\n\t"
      "pushl $0x2af588\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017e190_7:\n\t"
      "movl 0x47e4f0, %%eax\n\t"
      "movl 0x47e4ec, %%ecx\n\t"
      "pushl $0x17e130\n\t"
      "pushl $0x3c\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d9260]\n\t"
      "movl 0x47e4e0, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movw $0xd, 0x325652\n\t"
      "jle .LFUN_0017e190_13\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_0017e190_18\n\t"
      "pushl %%esi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_0017e190_11\n\t"
      "movl 0x47e4e0, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_0017e190_10\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e190_9\n\t"
      ".LFUN_0017e190_8:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      ".LFUN_0017e190_9:\n\t"
      "movl 0x47e4dc, %%ecx\n\t"
      "movswl 0x30(%%edi,%%ecx,1), %%edx\n\t"
      "leal (%%edi,%%ecx,1), %%esi\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x30(%%esi), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%edx, %%ebx\n\t"
      "addl $0x3c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_8\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e190_10:\n\t"
      "pushl %%esi\n\t"
      "call *%[rend]\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c15a560]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl $3\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "jmp .LFUN_0017e190_12\n\t"
      ".LFUN_0017e190_11:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_12:\n\t"
      "pushl %%esi\n\t"
      "call *%[rocc]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_13:\n\t"
      "movl 0x47e4e8, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0017e190_19\n\t"
      "leal (%%eax,%%eax,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_0017e190_18\n\t"
      "pushl %%esi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_0017e190_17\n\t"
      "movl 0x47e4e8, %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jle .LFUN_0017e190_16\n\t"
      "xorl %%edi, %%edi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017e190_15\n\t"
      ".LFUN_0017e190_14:\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017e190_15:\n\t"
      "movl 0x47e4e4, %%edx\n\t"
      "movswl 0x30(%%edi,%%edx,1), %%ecx\n\t"
      "leal (%%edi,%%edx,1), %%esi\n\t"
      "shll $4, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%ebx, %%edx\n\t"
      "shll $4, %%edx\n\t"
      "addl %%eax, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c8e0b0]\n\t"
      "movswl 0x30(%%esi), %%eax\n\t"
      "addl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x3c, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_14\n\t"
      "movl -0x10(%%ebp), %%esi\n\t"
      ".LFUN_0017e190_16:\n\t"
      "pushl %%esi\n\t"
      "call *%[rend]\n\t"
      "pushl $0x10\n\t"
      "pushl $1\n\t"
      "call *%[c15a560]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $2\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "pushl %%esi\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_17:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%esi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_19\n\t"
      ".LFUN_0017e190_18:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_19:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "je .LFUN_0017e190_24\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0017e190_20:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "cmpl 0x47e4f0, %%edx\n\t"
      "jge .LFUN_0017e190_24\n\t"
      "movl 0x47e4ec, %%eax\n\t"
      "movswl 0x30(%%ebx,%%eax,1), %%ecx\n\t"
      "leal (%%ebx,%%eax,1), %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl $9\n\t"
      "call *%[rzbuf]\n\t"
      "movl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_0017e190_22\n\t"
      "pushl %%edi\n\t"
      "call *%[rspr]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017e190_21\n\t"
      "movswl 0x30(%%esi), %%edx\n\t"
      "shll $4, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl %%edi\n\t"
      "call *%[rend]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c15a560]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x30(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x28, %%esp\n\t"
      "call *%[c15a290]\n\t"
      "pushl %%edi\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_23\n\t"
      ".LFUN_0017e190_21:\n\t"
      "pushl $0x2af540\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "pushl %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[rocc]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .LFUN_0017e190_23\n\t"
      ".LFUN_0017e190_22:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0017e190_23:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "incl %%edx\n\t"
      "addl $0x3c, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jne .LFUN_0017e190_20\n\t"
      ".LFUN_0017e190_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x325652\n\t"
      "popl %%ebx\n\t"
      ".LFUN_0017e190_25:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17e190_assert), [exitfn] "m"(b17e190_exitfn), [c1d9260] "m"(b17e190_c1d9260), [rzbuf] "m"(b17e190_rzbuf), [rspr] "m"(b17e190_rspr), [c8e0b0] "m"(b17e190_c8e0b0), [rend] "m"(b17e190_rend), [c15a560] "m"(b17e190_c15a560), [c15d5b0] "m"(b17e190_c15d5b0), [c15a290] "m"(b17e190_c15a290), [c8f390] "m"(b17e190_c8f390), [rocc] "m"(b17e190_rocc)
      : "memory");
}
#else
#error "FUN_0017e190: clang naked draft required"
#endif


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

/* FUN_0017e800 (0x17e800) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b17e800_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17e800_exitfn)(int) = system_exit;
static void (*const b17e800_c17df10)(void) = FUN_0017df10;
static unsigned int (*const b17e800_d1c90)(float *) = FUN_000d1c90;

__attribute__((naked, noinline))
void FUN_0017e800(void)
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

/* FUN_0017ebb0 (0x17ebb0) — XBE naked draft (batch 300). */
#if defined(__clang__)
static unsigned int (*const b17ebb0_c8e370)(void) = system_milliseconds;

__attribute__((naked, noinline))
void FUN_0017ebb0(void *param __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "pushl %%ebx\n\t"
      "je .LFUN_0017ebb0_15\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "je .LFUN_0017ebb0_15\n\t"
      "pushl %%esi\n\t"
      "call *%[c8e370]\n\t"
      "movw 0x47ed50, %%si\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_0017ebb0_13\n\t"
      "movl 0x47ec60, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl 0x47ed50, %%edx\n\t"
      "decl %%edx\n\t"
      "testw %%dx, %%dx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, %%edi\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "jle .LFUN_0017ebb0_4\n\t"
      "movswl %%dx, %%esi\n\t"
      "leal 0x47ec60(,%%esi,4), %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_0017ebb0_1:\n\t"
      "cmpw $1, %%dx\n\t"
      "jle .LFUN_0017ebb0_3\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "subl (%%esi), %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "ja .LFUN_0017ebb0_2\n\t"
      "movl %%ecx, %%edi\n\t"
      ".LFUN_0017ebb0_2:\n\t"
      "cmpl -0x4(%%ebp), %%ecx\n\t"
      "jbe .LFUN_0017ebb0_3\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_0017ebb0_3:\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "movl %%ecx, (%%esi)\n\t"
      "decl %%edx\n\t"
      "subl $4, %%esi\n\t"
      "testw %%dx, %%dx\n\t"
      "jg .LFUN_0017ebb0_1\n\t"
      "movw 0x47ed50, %%si\n\t"
      ".LFUN_0017ebb0_4:\n\t"
      "movl 0x47ec60, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "subl %%edx, %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "ja .LFUN_0017ebb0_5\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_5:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_6\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_6:\n\t"
      "fdivrs 0x254cb8\n\t"
      "movswl %%si, %%edx\n\t"
      "movl %%eax, %%ecx\n\t"
      "movw %%si, 0x4(%%ebx)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "fstps (%%ebx)\n\t"
      "subl 0x47ec5c(,%%edx,4), %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "ja .LFUN_0017ebb0_7\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_7:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fmuls 0x254cb8\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_8\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_8:\n\t"
      "cmpl $1, %%edi\n\t"
      ".byte 0xde, 0xf9\n\t"
      "movl %%edi, %%ecx\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "ja .LFUN_0017ebb0_9\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_9:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_10\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_10:\n\t"
      "fdivrs 0x254cb8\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "cmpl $1, %%ecx\n\t"
      "popl %%edi\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "ja .LFUN_0017ebb0_11\n\t"
      "movl $1, %%ecx\n\t"
      ".LFUN_0017ebb0_11:\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "jge .LFUN_0017ebb0_12\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_0017ebb0_12:\n\t"
      "fdivrs 0x254cb8\n\t"
      "fstps 0xc(%%ebx)\n\t"
      ".LFUN_0017ebb0_13:\n\t"
      "movl %%eax, 0x47ec60\n\t"
      "movswl %%si, %%eax\n\t"
      "incl %%eax\n\t"
      "cmpl $0x3c, %%eax\n\t"
      "popl %%esi\n\t"
      "jle .LFUN_0017ebb0_14\n\t"
      "movw $0x3c, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017ebb0_14:\n\t"
      "movw %%ax, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017ebb0_15:\n\t"
      "movw $0, 0x47ed50\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c8e370] "m"(b17ebb0_c8e370)
      : "memory");
}
#else
#error "FUN_0017ebb0: clang naked draft required"
#endif


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
