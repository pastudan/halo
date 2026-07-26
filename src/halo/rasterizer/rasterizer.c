/* MSVC CRT pow(): compiles to the _CIpow intrinsic (0x1d9e70 dispatcher,
 * body at 0x1d9e94 uses fyl2x). Not in decl.h; declared locally as in
 * objects.c so the compiler emits the intrinsic. */
double pow(double x, double y);

/* rasterizer_plasma_energy_draw (FUN_0016eef0): emit the plasma-energy
 * transparent shader (shader type 10) for one geometry group. Binds the two
 * noise-map textures (primary at shader+0xe0, secondary at shader+0x128),
 * sets fixed-function / render state, computes the two animation scroll
 * matrices (vs const block A: 6 vec4) and the perpendicular/parallel tint
 * colour rows (block B: 3 vec4) into vertex-shader constants, then installs
 * the plasma pixel shader and draws.
 * Original TU: c:\halo\SOURCE\rasterizer\xbox\rasterizer_xbox_plasma_energy.c
 */
void FUN_0016eef0(void *group)
{
  char *grp = (char *)group;
  char *p; /* plasma shader params base = FUN_001906b0(..)+0x28 */
  int *params; /* grp+0x6c: {color_table, pow_table} pointer pair */
  float *color_table; /* params[0]: 12-byte-stride colour entries */
  float *pow_table; /* params[1]: exponent-table floats [EBP-0xc] */
  float *tint; /* [EBX] tint rgb triple */
  float alpha_c; /* [EBP-8] default 1.0 */
  float alpha_s; /* [EBP-4] default 0.0 */
  float t; /* DAT_005a5e18 scroll time */
  float adiv; /* t / primary_noise_map_animation_period */
  float bdiv; /* t / secondary_noise_map_animation_period */
  float dupA; /* shader+0xa8 diagonal duplicate (primary) */
  float dupB; /* shader+0xf0 diagonal duplicate (secondary) */
  float vsA[24]; /* [EBP-0x9c] vertex-shader const block A (6 vec4) */
  float vsB[12]; /* [EBP-0x3c] vertex-shader const block B (3 vec4) */
  short idx;

  if (*(int *)0x476ab0 == 0) {
    display_assert("global_d3d_device",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                   "plasma_energy.c",
                   0x15, 1);
    system_exit(-1);
  }
  if (*(char *)0x3256fb == 0) {
    return;
  }

  p = (char *)FUN_001906b0(*(void **)(grp + 0xc), 10) + 0x28;
  tint = *(float **)0x2ee708;
  alpha_c = 1.0f;
  alpha_s = 0.0f;

  params = *(int **)(grp + 0x6c);
  if (params != 0) {
    color_table = *(float **)params;
    if (color_table != 0) {
      idx = *(short *)(p + 0x58);
      if (idx >= 1 && idx <= 4) {
        tint = (float *)((char *)color_table + (idx - 1) * 12);
      }
    }
    pow_table = *(float **)(params + 1);
    if (pow_table != 0) {
      idx = *(short *)(p + 4);
      if (idx >= 1 && idx <= 4) {
        alpha_c =
          (float)pow((double)pow_table[idx - 1], (double)*(float *)(p + 8));
      }
      idx = *(short *)(p + 0xc);
      if (idx >= 1 && idx <= 4) {
        alpha_s =
          (float)pow((double)pow_table[idx - 1], (double)*(float *)(p + 0x14)) *
          *(float *)(p + 0x10);
      }
    }
  }

  /* Bind the two noise-map textures and their fixed-function stage state. */
  rasterizer_set_texture(0, 1, 0, *(int *)(p + 0xb8),
                         *(unsigned short *)(grp + 0x10));
  SetTextureStageStateSmart(0, 0xa, 1);
  SetTextureStageStateSmart(0, 0xb, 1);
  SetTextureStageStateSmart(0, 0xc, 1);
  SetTextureStageStateSmart(0, 0xd, 2);
  SetTextureStageStateSmart(0, 0xe, 2);
  SetTextureStageStateSmart(0, 0xf, 2);
  rasterizer_set_texture(1, 1, 0, *(int *)(p + 0x100),
                         *(unsigned short *)(grp + 0x10));
  SetTextureStageStateSmart(1, 0xa, 1);
  SetTextureStageStateSmart(1, 0xb, 1);
  SetTextureStageStateSmart(1, 0xc, 1);
  SetTextureStageStateSmart(1, 0xd, 2);
  SetTextureStageStateSmart(1, 0xe, 2);
  SetTextureStageStateSmart(1, 0xf, 2);

  D3DDevice_SetRenderState_CullMode(0);
  /* 0x10101 is correct despite the delinked disasm showing $0x101: the
   * imm carries a dir32 reloc to XBE_FILE_HEADER_00010000, so the real
   * value is 0x10000 (XBE base) + 0x101 addend = 0x10101. */
  D3DDevice_SetRenderState_Simple(NV097_SET_COLOR_MASK_CMD, NV097_COLOR_MASK_RGB);
  *(uint32_t *)0x1fb7a4 = 0x10101;
  D3DDevice_SetRenderState_Simple(0x40304, 1);
  *(uint32_t *)0x1fb784 = 1;
  D3DDevice_SetRenderState_Simple(0x40344, 0x302);
  *(uint32_t *)0x1fb790 = 0x302;
  D3DDevice_SetRenderState_Simple(0x40348, 1);
  *(uint32_t *)0x1fb794 = 1;
  D3DDevice_SetRenderState_Simple(0x40350, 0x8006);
  *(uint32_t *)0x1fb7c0 = 0x8006;
  D3DDevice_SetRenderState_Simple(0x40300, 0);
  *(uint32_t *)0x1fb788 = 0;
  D3DDevice_SetRenderState_ZEnable(1);
  D3DDevice_SetRenderState_Simple(0x4035c, 0);
  *(uint32_t *)0x1fb798 = 0;
  D3DDevice_SetRenderState_Simple(0x40354, 0x203);
  *(uint32_t *)0x1fb77c = 0x203;
  D3DDevice_SetRenderState_ZBias(0);

  FUN_00178b40(0xf, FUN_00184610(grp), 0);

  if (!(*(float *)(p + 0x98) != 0.0f)) {
    display_assert("plasma->primary_noise_map_animation_period!=0.0f",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                   "plasma_energy.c",
                   0x69, 1);
    system_exit(-1);
  }
  if (!(*(float *)(p + 0xe0) != 0.0f)) {
    display_assert("plasma->secondary_noise_map_animation_period!=0.0f",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                   "plasma_energy.c",
                   0x6a, 1);
    system_exit(-1);
  }

  if (alpha_s < *(float *)0x2a39e0) {
    alpha_s = 0.0f;
  }

  /* Vertex-shader const block A (register -0x51): two scroll matrices.
   * Rows 0-2 scale t/primary_period by shader+0xc4/0xc8/0xcc with the
   * shader+0xd0 duplicate on the diagonal; rows 3-5 use t/secondary_period
   * with shader+0x10c/0x110/0x114 and the shader+0x118 duplicate. alpha_s
   * rides in A[2]. */
  t = *(float *)0x5a5e18;
  adiv = t / *(float *)(p + 0x98);
  bdiv = t / *(float *)(p + 0xe0);
  dupA = *(float *)(p + 0xa8);
  dupB = *(float *)(p + 0xf0);
  vsA[0] = dupA;
  vsA[1] = 0.0f;
  vsA[2] = alpha_s;
  vsA[3] = adiv * *(float *)(p + 0x9c);
  vsA[4] = 0.0f;
  vsA[5] = dupA;
  vsA[6] = 0.0f;
  vsA[7] = adiv * *(float *)(p + 0xa0);
  vsA[8] = 0.0f;
  vsA[9] = 0.0f;
  vsA[10] = dupA;
  vsA[11] = adiv * *(float *)(p + 0xa4);
  vsA[12] = dupB;
  vsA[13] = 0.0f;
  vsA[14] = 0.0f;
  vsA[15] = bdiv * *(float *)(p + 0xe4);
  vsA[16] = 0.0f;
  vsA[17] = dupB;
  vsA[18] = 0.0f;
  vsA[19] = bdiv * *(float *)(p + 0xe8);
  vsA[20] = 0.0f;
  vsA[21] = 0.0f;
  vsA[22] = dupB;
  vsA[23] = bdiv * *(float *)(p + 0xec);

  /* Block B (register -0x54): identity row, (perp-parallel)*colour row, and
   * parallel*colour row.  perp rgba = shader+0x64/0x68/0x6c/0x60,
   * parallel rgba = shader+0x74/0x78/0x7c/0x70; alpha uses alpha_c. */
  vsB[0] = 1.0f;
  vsB[1] = 1.0f;
  vsB[2] = 1.0f;
  vsB[3] = 1.0f;
  vsB[4] = (*(float *)(p + 0x3c) - *(float *)(p + 0x4c)) * tint[0];
  vsB[5] = (*(float *)(p + 0x40) - *(float *)(p + 0x50)) * tint[1];
  vsB[6] = (*(float *)(p + 0x44) - *(float *)(p + 0x54)) * tint[2];
  vsB[7] = (*(float *)(p + 0x38) - *(float *)(p + 0x48)) * alpha_c;
  vsB[8] = *(float *)(p + 0x4c) * tint[0];
  vsB[9] = *(float *)(p + 0x50) * tint[1];
  vsB[10] = *(float *)(p + 0x54) * tint[2];
  vsB[11] = alpha_c * *(float *)(p + 0x48);

  D3DDevice_SetVertexShaderConstant(-0x51, vsA, 6);
  D3DDevice_SetVertexShaderConstant(-0x54, vsB, 3);

  /* Pixel-shader state block for the plasma-energy shader. */
  csmemset((void *)0x5a5ac0, 0, 0xf0);
  *(uint32_t *)0x5a5b98 = 0x42;
  *(uint32_t *)0x5a5b94 = 0x104;
  *(uint32_t *)0x5a5ac0 = 0x820a920;
  *(uint32_t *)0x5a5b28 = 0xc00;
  *(uint32_t *)0x5a5b48 = 0x1920b820;
  *(uint32_t *)0x5a5b74 = 0xc00;
  *(uint32_t *)0x5a5ac4 = 0x1c1c0c0c;
  *(uint32_t *)0x5a5b2c = 0x24c00;
  *(uint32_t *)0x5a5b4c = 0;
  *(uint32_t *)0x5a5b78 = 0;
  *(uint32_t *)0x5a5ac8 = 0x5c5c;
  *(uint32_t *)0x5a5b30 = 0x4d00;
  *(uint32_t *)0x5a5b50 = 0;
  *(uint32_t *)0x5a5b7c = 0;
  *(uint32_t *)0x5a5acc = 0x14150000;
  *(uint32_t *)0x5a5b34 = 0x40;
  *(uint32_t *)0x5a5b54 = 0x1c051da0;
  *(uint32_t *)0x5a5b80 = 0xc00;
  *(uint32_t *)0x5a5ae0 = 0xc0f0000;
  *(uint32_t *)0x5a5ae4 = 0x1c1c1400;
  rasterizer_set_pixel_shader((void *)0x5a5ac0);
  FUN_00174510(grp, 0);
}

/* rasterizer_transparent_geometry_group_draw (0x174d10) — XBE naked draft (batch 79). */
#if defined(__clang__)
static void (*const b174d10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b174d10_exitfn)(int) = system_exit;
static char (*const b174d10_c184570)(void *group) = FUN_00184570;
static void (*const b174d10_c1845b0)(void *group, int a2) = FUN_001845b0;
static void * (*const b174d10_c184460)(short group_presorted_index) = rasterizer_transparent_geometry_group_get;
static void (*const b174d10_c174d10)(void *group, int dirty) = rasterizer_transparent_geometry_group_draw;
static int (*const b174d10_c184610)(void *group) = FUN_00184610;
static void (*const b174d10_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void __stdcall (*const b174d10_c1e96d0)(uint32_t mode) = D3DDevice_SetRenderState_CullMode;
static void (*const b174d10_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b174d10_c1ea290)(uint32_t enable) = D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const b174d10_c1e98e0)(uint32_t value) = D3DDevice_SetRenderState_ZBias;
static void *(*const b174d10_memset)(void *, int, unsigned int) = csmemset;
static float (*const b174d10_rmreal)(unsigned int *) = random_math_real;
static unsigned int (*const b174d10_cd1dd0)(float *color) = FUN_000d1dd0;
static void (*const b174d10_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b174d10_c156710)(void *a1) = rasterizer_set_model_skinning;
static void __stdcall (*const b174d10_c1eb8d0)(int register_index, const void *data, uint32_t count) = D3DDevice_SetVertexShaderConstant;
static void (*const b174d10_c174510)(void *group, int a2) = FUN_00174510;
static int (*const b174d10_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void (*const b174d10_c189cb0)(char flag, void *position, void *string, int color) = FUN_00189cb0;
static void (*const b174d10_ce2220)(int state, int value) = SetRenderStateSmart;
static char (*const b174d10_c190980)(void *shader) = shader_ignores_effect;
static void (*const b174d10_c156ab0)(void *lighting) = rasterizer_set_model_lighting;
static void * (*const b174d10_c1843b0)(void *group) = rasterizer_transparent_geometry_next_group;
static char (*const b174d10_c190930)(void *shader) = shader_is_water_decal;
static void (*const b174d10_c1595c0)(void) = FUN_001595c0;
static int (*const b174d10_c190710)(void *shader) = shader_get_vertex_shader_permutation;
static void (*const b174d10_c156c30)(float near_z, float far_z) = rasterizer_set_frustum_z;
static char (*const b174d10_c1908a0)(void *shader) = shader_is_decal;
static void * (*const b174d10_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void (*const b174d10_c158ae0)(int mode) = FUN_00158ae0;
static void (*const b174d10_c159900)(void *group) = FUN_00159900;
static void (*const b174d10_c155c20)(int stage, void *bitmap_data) = rasterizer_set_texture_bitmap_data;
static void (*const b174d10_ce2470)(int stage, int state, int value) = SetTextureStageStateSmart;
static void (*const b174d10_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void (*const b174d10_c1580b0)(int framebuffer_blend_function) = FUN_001580b0;
static void (*const b174d10_c190e10)(void *map_animation, void *external_animation, float u_scale, float v_scale, float u_offset, float v_offset, float rotation, float time, float *out_u, float *out_v) = FUN_00190e10;
static void (*const b174d10_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static float (*const b174d10_c13070)(float *a, float *b) = FUN_00013070;
static void __stdcall (*const b174d10_c1eb2d0)(uint32_t stream, void *vertex_buffer, uint32_t stride) = D3DDevice_SetStreamSource;
static void * (*const b174d10_c8e0b0)(void *destination, void *source, size_t size) = csmemcpy;
static void *(*const b174d10_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b174d10_tag)(int, int) = tag_get;
static double (*const b174d10_c1d9c2b)(double x) = floor;
static void (*const b174d10_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = D3DDevice_SetTextureStageState;
static float (*const b174d10_c99500)(float *plane, float *point) = plane3d_distance_to_point;
static char (*const b174d10_c17c2f0)(void *shader, void *state) = FUN_0017c2f0;
static uint32_t (*const b174d10_c99530)(float alpha, float *color) = real_a_rgb_color_to_pixel32;
static float (*const b174d10_c10a5e0)(int16_t function_type, float input) = FUN_0010a5e0;
static unsigned int (*const b174d10_d1c90)(float *) = FUN_000d1c90;
static int (*const b174d10_c190c00)(int a0) = numeric_countdown_timer_get;
static char (*const b174d10_c17bca0)(void *shader, void *state) = FUN_0017bca0;
static void (*const b174d10_c179de0)(void *group) = FUN_00179de0;
static uint32_t (*const b174d10_c159070)(float a1) = FUN_00159070;
static void (*const b174d10_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static void (*const b174d10_c1584f0)(int stage, int target, int max_mipmap) = FUN_001584f0;
static void (*const b174d10_c16eef0)(void *group) = FUN_0016eef0;
static void (*const b174d10_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b174d10_c184390)(short *out_count) = rasterizer_secondary_geometry_groups_get;

__attribute__((naked, noinline))
void rasterizer_transparent_geometry_group_draw(void *group __attribute__((unused)), int dirty __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x550, %%esp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "movl $1, %%esi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb $0, -0x2d(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_1\n\t"
      "pushl %%esi\n\t"
      "pushl $0xe8\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_2\n\t"
      "pushl %%esi\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_2:\n\t"
      "movl 0x98(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_3\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_317\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c184570]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_317\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c1845b0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x94(%%edi), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_4\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c184460]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c174d10]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_4:\n\t"
      "movb 0x3256c2, %%al\n\t"
      "testb %%al, %%al\n\t"
      "pushl %%ebx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_44\n\t"
      "testb $2, (%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "cmpl $-1, 0x90(%%edi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "movl $6, %%eax\n\t"
      "movw %%ax, -0xc8(%%ebp)\n\t"
      "movw %%ax, -0xc6(%%ebp)\n\t"
      "movw %%ax, -0xc4(%%ebp)\n\t"
      "movw %%ax, -0xc2(%%ebp)\n\t"
      "movl $0xd, %%eax\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "movw %%ax, -0xc0(%%ebp)\n\t"
      "movw %%ax, -0xbe(%%ebp)\n\t"
      "movl $0x41, %%eax\n\t"
      "pushl %%edi\n\t"
      "movw %%ax, -0xbc(%%ebp)\n\t"
      "movw %%ax, -0xba(%%ebp)\n\t"
      "movw %%bx, -0xb8(%%ebp)\n\t"
      "movw %%bx, -0xb6(%%ebp)\n\t"
      "movw %%bx, -0xb4(%%ebp)\n\t"
      "movw %%bx, -0xb2(%%ebp)\n\t"
      "call *%[c184610]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x3256ea, %%ax\n\t"
      "cmpw $0x3e8, %%ax\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_5\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_6\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_5:\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_6:\n\t"
      "testw %%si, %%si\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_7\n\t"
      "cmpw $0xc, %%si\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x118\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a52e0\n\t"
      "call *%[assert]\n\t"
      "pushl %%ebx\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_8:\n\t"
      "movswl %%si, %%edx\n\t"
      "movw -0xc8(%%ebp,%%edx,2), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_9\n\t"
      "pushl $1\n\t"
      "pushl $0x119\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a52b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_9:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c178b40]\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c1e96d0]\n\t"
      "movl $0x10101, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movzbl 0xb(%%ebp), %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl $0x10101, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%esi, 0x1fb784\n\t"
      "movl $1, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x40344, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x40348, %%ecx\n\t"
      "movl %%esi, 0x1fb790\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x8006, %%edx\n\t"
      "movl $0x40350, %%ecx\n\t"
      "movl %%esi, 0x1fb794\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0x8006, 0x1fb7c0\n\t"
      "call *%[c1e9350]\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "movl %%ebx, 0x1fb798\n\t"
      "call *%[c1e9350]\n\t"
      "pushl %%ebx\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "call *%[c1e98e0]\n\t"
      "pushl $0xf0\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movswl 0x3256ea, %%eax\n\t"
      "addl 0x90(%%edi), %%eax\n\t"
      "leal -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x2c(%%ebp)\n\t"
      "call *%[rmreal]\n\t"
      "leal -0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "call *%[rmreal]\n\t"
      "leal -0x8(%%ebp), %%eax\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "call *%[rmreal]\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "addl $0x18, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_10\n\t"
      "fld %%st(0)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_11\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_10:\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_11:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_13\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_12\n\t"
      "fld %%st(0)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_14\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_12:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_14\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_13:\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_14:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_15\n\t"
      "flds -0x24(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_16\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_15:\n\t"
      "fld %%st(1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_16:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_17\n\t"
      "flds -0x28(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_19\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_17:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_18\n\t"
      "flds -0x24(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_19\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_18:\n\t"
      "fld %%st(1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_19:\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "movb 0xb(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "fdivrs 0x2a52b4\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xe2\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x256140\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xe2\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x256140\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fxch %%st(2)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds 0x256140\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fstp %%st(1)\n\t"
      "fstp %%st(0)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_24\n\t"
      "flds 0x325724\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_21\n\t"
      "flds 0x325724\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_20\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_22\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_20:\n\t"
      "flds 0x325724\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_22\n\t"
      "fstp %%st(0)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_21:\n\t"
      "flds 0x29d598\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_22:\n\t"
      "cmpw $0x3e8, 0x3256ea\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_23\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_24\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_23:\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_24:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_25\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_26\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_25:\n\t"
      "movl $1, %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl $0x156\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a528c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_27\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_26:\n\t"
      "movl $1, %%esi\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_27:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_28\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_29\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_28:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x157\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a5264\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_29:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_30\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_31\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_30:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x158\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a523c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_31:\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cd1dd0]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%eax, 0x5a5b6c\n\t"
      "movl %%esi, 0x5a5b94\n\t"
      "movl %%esi, 0x5a5ae0\n\t"
      "call *%[c156510]\n\t"
      "movl 0x60(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_32\n\t"
      "movw 0x64(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_32\n\t"
      "movw %%cx, -0x18(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_33\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_32:\n\t"
      "movl 0x31fc60, %%edx\n\t"
      "movw %%si, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_33:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c156710]\n\t"
      "movb (%%edi), %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "movl $0x3f800000, -0xb0(%%ebp)\n\t"
      "movl $0, -0xac(%%ebp)\n\t"
      "movl $0, -0xa8(%%ebp)\n\t"
      "movl $0, -0xa4(%%ebp)\n\t"
      "movl $0, -0xa0(%%ebp)\n\t"
      "movl $0x3f800000, -0x9c(%%ebp)\n\t"
      "movl $0, -0x98(%%ebp)\n\t"
      "movl $0, -0x94(%%ebp)\n\t"
      "movl $0, -0x90(%%ebp)\n\t"
      "movl $0, -0x8c(%%ebp)\n\t"
      "movl $0x3f800000, -0x88(%%ebp)\n\t"
      "movl $0, -0x84(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_34\n\t"
      "movl 0x5a5c64, %%ecx\n\t"
      "movl 0x5a5c70, %%edx\n\t"
      "movl 0x5a5c7c, %%eax\n\t"
      "movl %%ecx, -0xb0(%%ebp)\n\t"
      "movl 0x5a5bc8, %%ecx\n\t"
      "movl %%edx, -0xac(%%ebp)\n\t"
      "movl 0x5a5c68, %%edx\n\t"
      "movl %%eax, -0xa8(%%ebp)\n\t"
      "movl 0x5a5c74, %%eax\n\t"
      "movl %%ecx, -0xa4(%%ebp)\n\t"
      "movl 0x5a5c80, %%ecx\n\t"
      "movl %%edx, -0xa0(%%ebp)\n\t"
      "movl 0x5a5bcc, %%edx\n\t"
      "movl %%eax, -0x9c(%%ebp)\n\t"
      "movl 0x5a5c6c, %%eax\n\t"
      "movl %%ecx, -0x98(%%ebp)\n\t"
      "movl 0x5a5c78, %%ecx\n\t"
      "movl %%edx, -0x94(%%ebp)\n\t"
      "movl 0x5a5c84, %%edx\n\t"
      "movl %%eax, -0x90(%%ebp)\n\t"
      "movl 0x5a5bd0, %%eax\n\t"
      "movl %%ecx, -0x8c(%%ebp)\n\t"
      "movl %%edx, -0x88(%%ebp)\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_34:\n\t"
      "pushl $3\n\t"
      "leal -0xb0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x58\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "call *%[c174510]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "flds 0x70(%%edi)\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "leal -0x550(%%ebp), %%edx\n\t"
      "pushl $0x2a5234\n\t"
      "pushl %%edx\n\t"
      "call *%[c1d90f0]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      "addl $0x10, %%esp\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_35\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_37\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_35:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_36\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_37\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_36:\n\t"
      "fstps -0x28(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_37:\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x254644\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_38\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_40\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_38:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_39\n\t"
      "movl $0x3f800000, -0x24(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_40\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_39:\n\t"
      "fsts -0x24(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_40:\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_41\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_43\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_41:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_42\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_43\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_42:\n\t"
      "fstps -0x20(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_43:\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x550(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x74(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c189cb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_44:\n\t"
      "cmpw $2, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_50\n\t"
      "movl 0x8(%%edi), %%ebx\n\t"
      "cmpl 0x47e4b8, %%ebx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_51\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_51\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%edi, %%esi\n\t"
      "call *%[c184610]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0xd\n\t"
      "call *%[c178b40]\n\t"
      "pushl $0\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x40\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x203\n\t"
      "pushl $0x39\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $0\n\t"
      "call *%[c1e98e0]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $1, 0x5a5b94\n\t"
      "call *%[c156510]\n\t"
      "addl $0x10, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_45:\n\t"
      "cmpl %%ebx, 0x8(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_50\n\t"
      "cmpw $2, 0x14(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_50\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190980]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_49\n\t"
      "movl 0x60(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_46\n\t"
      "movw 0x64(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_46\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_47\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_46:\n\t"
      "movl 0x31fc60, %%ecx\n\t"
      "movw $1, -0x18(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_47:\n\t"
      "leal -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "call *%[c156710]\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_48\n\t"
      "movl 0x68(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c156ab0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_48:\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c174510]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_49:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1843b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_45\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_50:\n\t"
      "movl $1, %%esi\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_51:\n\t"
      "testb $2, (%%edi)\n\t"
      "movl $4, %%ebx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "movb 0x3256fa, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_52\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "cmpw %%bx, 0x24(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "cmpw %%si, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "movl 0x47e4b8, %%ecx\n\t"
      "cmpl %%ecx, 0x8(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_53\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_52:\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_53\n\t"
      "cmpw $7, 0x24(%%eax)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      "pushl %%eax\n\t"
      "call *%[c190930]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_54\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_53:\n\t"
      "call *%[c1595c0]\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_54:\n\t"
      "testb $2, (%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "cmpw %%si, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "cmpw %%bx, 0x24(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      "pushl %%edi\n\t"
      "call *%[c1843b0]\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_55\n\t"
      "cmpw %%si, 0x14(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_55\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "cmpl 0x8(%%edi), %%edx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_55\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_55\n\t"
      "cmpw %%bx, 0x24(%%eax)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_56\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_55:\n\t"
      "movb $1, -0x2d(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_56:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_57\n\t"
      "movl 0x50(%%edi), %%eax\n\t"
      "movl 0x4c(%%edi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *0x48(%%edi)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_308\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_57:\n\t"
      "pushl %%eax\n\t"
      "call *%[c190710]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "call *%[c184610]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "testb $2, (%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_60\n\t"
      "movl 0x60(%%edi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_58\n\t"
      "movw 0x64(%%edi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_58\n\t"
      "movw %%ax, -0x18(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_59\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_58:\n\t"
      "movl 0x31fc60, %%edx\n\t"
      "movw %%si, -0x18(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_59:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c156710]\n\t"
      "movl 0x68(%%edi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_60\n\t"
      "pushl %%eax\n\t"
      "call *%[c156ab0]\n\t"
      "addl $4, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_60:\n\t"
      "testb $8, (%%edi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_62\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_61\n\t"
      "pushl $0x44800000\n\t"
      "pushl $0x3b800000\n\t"
      "call *%[c156c30]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_61:\n\t"
      "pushl $0\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x81\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x10, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_63\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_62:\n\t"
      "pushl %%esi\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x40\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x203\n\t"
      "pushl $0x39\n\t"
      "call *%[ce2220]\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1908a0]\n\t"
      "movl 0x32570c, %%esi\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl %%esi, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x81\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x24, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_63:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_64:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "movl $1, %%ebx\n\t"
      "jns .Lrasterizer_transparent_geometry_group_draw_68\n\t"
      "cmpw %%bx, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_65\n\t"
      "testw %%ax, %%ax\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_306\n\t"
      "movl 0x3256a0, %%edx\n\t"
      "movl 0x32569c, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c156c30]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_69\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_65:\n\t"
      "testw %%ax, %%ax\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_67\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_66\n\t"
      "cmpw %%bx, 0x24(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_66\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movb 0x28(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $4, %%cl\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_66:\n\t"
      "pushl $3\n\t"
      "call *%[c158ae0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_69\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_67:\n\t"
      "pushl $2\n\t"
      "call *%[c158ae0]\n\t"
      "pushl $0\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_69\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_68:\n\t"
      "testw %%ax, %%ax\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_306\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_69:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "movswl 0x24(%%eax), %%ecx\n\t"
      "decl %%ecx\n\t"
      "cmpl $9, %%ecx\n\t"
      "ja .Lrasterizer_transparent_geometry_group_draw_304\n\t"
      "jmp *.Lrasterizer_transparent_geometry_group_draw_jt0(,%%ecx,4)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_70:\n\t"
      "movswl 0x14(%%edi), %%eax\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_71\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x2ab\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a51f4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_71:\n\t"
      "movb 0x47e4c0, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_316\n\t"
      "pushl %%edi\n\t"
      "call *%[c159900]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_72:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_73\n\t"
      "cmpw $2, 0x5c(%%esi)\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_74\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_73:\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_74:\n\t"
      "movl 0x5c(%%edi), %%ecx\n\t"
      "movb 0x28(%%esi), %%bl\n\t"
      "pushl %%ecx\n\t"
      "shrb $1, %%bl\n\t"
      "pushl $0\n\t"
      "andb $1, %%bl\n\t"
      "call *%[c155c20]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x2e(%%esi), %%dl\n\t"
      "andl $2, %%edx\n\t"
      "orl $1, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xa\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x2e(%%esi), %%al\n\t"
      "andl $4, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x2e(%%esi), %%cl\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x2e(%%esi), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xe\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x2e(%%esi), %%al\n\t"
      "andb $1, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xf\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "addl $0x44, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_75\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c155e80]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x5e(%%esi), %%dl\n\t"
      "andl $2, %%edx\n\t"
      "orl $1, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xa\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x5e(%%esi), %%al\n\t"
      "andl $4, %%eax\n\t"
      "orl $2, %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xb\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x5e(%%esi), %%cl\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x5e(%%esi), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xe\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x5e(%%esi), %%al\n\t"
      "andb $1, %%al\n\t"
      "addl $0x44, %%esp\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xf\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_75:\n\t"
      "pushl $0\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x2a(%%esi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1580b0]\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x41\n\t"
      "call *%[c178b40]\n\t"
      "movb (%%edi), %%al\n\t"
      "addl $0x30, %%esp\n\t"
      "testb $0x20, %%al\n\t"
      "movl $0x3f800000, -0x108(%%ebp)\n\t"
      "movl $0, -0x104(%%ebp)\n\t"
      "movl $0, -0x100(%%ebp)\n\t"
      "movl $0, -0xfc(%%ebp)\n\t"
      "movl $0, -0xf8(%%ebp)\n\t"
      "movl $0x3f800000, -0xf4(%%ebp)\n\t"
      "movl $0, -0xf0(%%ebp)\n\t"
      "movl $0, -0xec(%%ebp)\n\t"
      "movl $0, -0xe8(%%ebp)\n\t"
      "movl $0, -0xe4(%%ebp)\n\t"
      "movl $0x3f800000, -0xe0(%%ebp)\n\t"
      "movl $0, -0xdc(%%ebp)\n\t"
      "movl $0x3f800000, -0x1f0(%%ebp)\n\t"
      "movl $0, -0x1ec(%%ebp)\n\t"
      "movl $0, -0x1e8(%%ebp)\n\t"
      "movl $0, -0x1e4(%%ebp)\n\t"
      "movl $0, -0x1e0(%%ebp)\n\t"
      "movl $0x3f800000, -0x1dc(%%ebp)\n\t"
      "movl $0, -0x1d8(%%ebp)\n\t"
      "movl $0, -0x1d4(%%ebp)\n\t"
      "movl $0, -0x1d0(%%ebp)\n\t"
      "movl $0, -0x1cc(%%ebp)\n\t"
      "movl $0, -0x1c8(%%ebp)\n\t"
      "movl $0, -0x1c4(%%ebp)\n\t"
      "movl $0, -0x1c0(%%ebp)\n\t"
      "movl $0, -0x1bc(%%ebp)\n\t"
      "movl $0, -0x1b8(%%ebp)\n\t"
      "movl $0, -0x1b4(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_76\n\t"
      "movl 0x5a5c64, %%ecx\n\t"
      "movl 0x5a5c70, %%edx\n\t"
      "movl 0x5a5c7c, %%eax\n\t"
      "movl %%ecx, -0x108(%%ebp)\n\t"
      "movl 0x5a5bc8, %%ecx\n\t"
      "movl %%edx, -0x104(%%ebp)\n\t"
      "movl 0x5a5c68, %%edx\n\t"
      "movl %%eax, -0x100(%%ebp)\n\t"
      "movl 0x5a5c74, %%eax\n\t"
      "movl %%ecx, -0xfc(%%ebp)\n\t"
      "movl 0x5a5c80, %%ecx\n\t"
      "movl %%edx, -0xf8(%%ebp)\n\t"
      "movl 0x5a5bcc, %%edx\n\t"
      "movl %%eax, -0xf4(%%ebp)\n\t"
      "movl 0x5a5c6c, %%eax\n\t"
      "movl %%ecx, -0xf0(%%ebp)\n\t"
      "movl 0x5a5c78, %%ecx\n\t"
      "movl %%edx, -0xec(%%ebp)\n\t"
      "movl 0x5a5c84, %%edx\n\t"
      "movl %%eax, -0xe8(%%ebp)\n\t"
      "movl 0x5a5bd0, %%eax\n\t"
      "movl %%ecx, -0xe4(%%ebp)\n\t"
      "movl %%edx, -0xe0(%%ebp)\n\t"
      "movl %%eax, -0xdc(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_76:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_77\n\t"
      "movl 0x5a5e18, %%eax\n\t"
      "leal -0x1c0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x40(%%edi), %%ecx\n\t"
      "leal -0x1d0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal 0x60(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c190e10]\n\t"
      "addl $0x28, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_77:\n\t"
      "pushl $3\n\t"
      "leal -0x108(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x58\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_78\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_79\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_78:\n\t"
      "pushl $0x2a5160\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_79:\n\t"
      "pushl $4\n\t"
      "leal -0x1f0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x51\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_80\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_81\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_80:\n\t"
      "pushl $0x2a50e8\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_81:\n\t"
      "movb 0x325718, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_87\n\t"
      "cmpw $2, 0x5c(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_87\n\t"
      "cmpl $-1, 0x58(%%esi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_87\n\t"
      "cmpb $0, (%%edi)\n\t"
      "js .Lrasterizer_transparent_geometry_group_draw_87\n\t"
      "flds 0x9c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_82\n\t"
      "flds 0x9c(%%esi)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_83\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_82:\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_83:\n\t"
      "movb 0x32568c, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_84\n\t"
      "flds 0x2a50e0\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_85\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_84:\n\t"
      "flds 0x2a50dc\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_85:\n\t"
      "flds 0x5a5c04\n\t"
      "movl 0x5a5bd4, %%ecx\n\t"
      "flds 0x5a5c08\n\t"
      "movl 0x5a5bd8, %%edx\n\t"
      "fld %%st(0)\n\t"
      "movl 0x5a5bdc, %%eax\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "pushl $0x5a5bc8\n\t"
      "fxch %%st(1)\n\t"
      "pushl $0x5a5bd4\n\t"
      ".byte 0xd8, 0xe2\n\t"
      "movl %%ecx, -0x90(%%ebp)\n\t"
      "movl %%edx, -0x8c(%%ebp)\n\t"
      "movl %%eax, -0x88(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fsts -0xa0(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fchs\n\t"
      "fstps -0x9c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls 0x98(%%esi)\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds 0x5a5c04\n\t"
      "fadds 0x25bb10\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "call *%[c13070]\n\t"
      "addl $8, %%esp\n\t"
      "fchs\n\t"
      "pushl $2\n\t"
      "fstps -0x84(%%ebp)\n\t"
      "leal -0xa0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x3f\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_86\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_87\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_86:\n\t"
      "pushl $0x2a5048\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_87:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl $0x18201415, 0x5a5ac0\n\t"
      "movl $0xc4, 0x5a5b28\n\t"
      "movl $0xc, 0x5a5ae0\n\t"
      "movl $0x1c00, 0x5a5ae4\n\t"
      "movl $0xc00, %%edx\n\t"
      "movl $0xc0, %%ecx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_88\n\t"
      "movl $0x8080000, 0x5a5b48\n\t"
      "movl %%ecx, 0x5a5b74\n\t"
      "movl $0xc0c0000, 0x5a5b4c\n\t"
      "movl %%ecx, 0x5a5b78\n\t"
      "movl $0x250c0508, 0x5a5b50\n\t"
      "movl %%edx, 0x5a5b7c\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_89\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_88:\n\t"
      "movl $0x8050000, 0x5a5b48\n\t"
      "movl $0xc0, 0x5a5b74\n\t"
      "movl $1, %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_89:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_90\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl $0x1c190000, 0x5a5ac0(%%eax)\n\t"
      "movl %%ecx, 0x5a5b28(%%eax)\n\t"
      "movl $0xc090000, 0x5a5b48(%%eax)\n\t"
      "movl %%ecx, 0x5a5b74(%%eax)\n\t"
      "incl %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_90:\n\t"
      "movb 0x325718, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_93\n\t"
      "cmpw $2, 0x5c(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_93\n\t"
      "cmpl $-1, 0x58(%%esi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_93\n\t"
      "cmpb $0, (%%edi)\n\t"
      "js .Lrasterizer_transparent_geometry_group_draw_93\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $1\n\t"
      "movl $0x54421, 0x5a5b98\n\t"
      "movl $0x110000, 0x5a5ba0\n\t"
      "movl $0, 0x5a5b9c\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movl 0x47e4bc, %%edx\n\t"
      "addl $0x3c, %%esp\n\t"
      "pushl $2\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "call *%[c1eb2d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_91\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_92\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_91:\n\t"
      "pushl $0x2a4fc8\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_92:\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0xc00, %%edx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_94\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_93:\n\t"
      "movb 0xb(%%ebp), %%cl\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "setne %%al\n\t"
      "shll $5, %%eax\n\t"
      "orl $1, %%eax\n\t"
      "movl %%eax, 0x5a5b98\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_94:\n\t"
      "movb 0x3256d4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_102\n\t"
      "testb $4, (%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_102\n\t"
      "movswl 0x2a(%%esi), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .Lrasterizer_transparent_geometry_group_draw_101\n\t"
      "jmp *.Lrasterizer_transparent_geometry_group_draw_jt1(,%%eax,4)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_95:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl $0x1c140000, 0x5a5ac0(%%eax)\n\t"
      "movl %%edx, 0x5a5b28(%%eax)\n\t"
      "movl %%ecx, 0x5a5b94\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_96:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl $0xc142034, 0x5a5b48(%%eax)\n\t"
      "movl %%edx, 0x5a5b74(%%eax)\n\t"
      "movl %%ecx, 0x5a5b94\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_97:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl $0xc14a034, 0x5a5b48(%%eax)\n\t"
      "movl %%edx, 0x5a5b74(%%eax)\n\t"
      "movl %%ecx, 0x5a5b94\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_98:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_100\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_99:\n\t"
      "movswl %%bx, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "movl $0x1c140000, 0x5a5ac0(%%eax)\n\t"
      "movl %%edx, 0x5a5b28(%%eax)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_100:\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl $0xc140000, 0x5a5b48(%%eax)\n\t"
      "movl %%edx, 0x5a5b74(%%eax)\n\t"
      "movl %%ecx, 0x5a5b94\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_101:\n\t"
      "pushl $1\n\t"
      "pushl $0x3a2\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x29fac4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_102:\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl %%ecx, 0x5a5b94\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_103:\n\t"
      "pushl $5\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movw 0x10(%%edi), %%dx\n\t"
      "leal 0x48(%%eax), %%ebx\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl (%%ebx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movw %%dx, -0x34(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_105\n\t"
      "xorl %%esi, %%esi\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_104\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_104:\n\t"
      "pushl $0xa0\n\t"
      "leal -0x450(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x10\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl $0xffffffff, -0x3c0(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%eax, -0x444(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "leal -0x450(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c174d10]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "cmpl (%%ebx), %%esi\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_104\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_105:\n\t"
      "movl -0x40(%%ebp), %%ecx\n\t"
      "movl -0x38(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x18\n\t"
      "call *%[c178b40]\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movb 0x29(%%esi), %%al\n\t"
      "andb $4, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffff6ff, %%eax\n\t"
      "addl $0x901, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x29(%%esi), %%cl\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x7f\n\t"
      "pushl $0x3d\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x2c(%%esi), %%dx\n\t"
      "pushl %%edx\n\t"
      "call *%[c1580b0]\n\t"
      "movb 0x29(%%esi), %%al\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jns .Lrasterizer_transparent_geometry_group_draw_110\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_110\n\t"
      "movl 0x54(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x54(%%esi), %%eax\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_110\n\t"
      "pushl $0x64\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x28(%%eax), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movw 0x60(%%eax), %%bx\n\t"
      "movzbw 0x28(%%esi), %%cx\n\t"
      "movl 0x6c(%%edi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $8, %%bx\n\t"
      "setne %%al\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "decl %%eax\n\t"
      "andl $3, %%eax\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "shll $2, %%esi\n\t"
      "fmuls (%%eax,%%esi,1)\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x10c(%%ebp)\n\t"
      "movl -0x10c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_106\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_107\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_106:\n\t"
      "movl 0x6c(%%edi), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "fmuls (%%edx,%%esi,1)\n\t"
      "subl $8, %%esp\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x110(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "cmpl %%eax, -0x110(%%ebp)\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_107\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "fmuls (%%ecx,%%esi,1)\n\t"
      "subl $8, %%esp\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x114(%%ebp)\n\t"
      "movl -0x114(%%ebp), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_107:\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_109\n\t"
      "movswl %%bx, %%esi\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_108:\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "idivl %%esi\n\t"
      "decl %%ecx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_108\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_109:\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%bx, %%ecx\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl %%edx, -0x34(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_110:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl 0x54(%%ebx), %%ecx\n\t"
      "addl $0x54, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_140\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_111:\n\t"
      "movswl %%cx, %%esi\n\t"
      "cmpl (%%ebx), %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_127\n\t"
      "pushl $0x64\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x2a(%%edx), %%bx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $2, %%eax\n\t"
      "movw %%ax, -0xd6(%%ebp)\n\t"
      "movw %%ax, -0xd4(%%ebp)\n\t"
      "movw %%ax, -0xd2(%%ebp)\n\t"
      "movl $3, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movw $0, -0xd8(%%ebp)\n\t"
      "movl $1, -0x134(%%ebp)\n\t"
      "movl %%eax, -0x130(%%ebp)\n\t"
      "movl %%eax, -0x12c(%%ebp)\n\t"
      "movl %%eax, -0x128(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_112\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_113\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_112:\n\t"
      "movswl %%bx, %%eax\n\t"
      "movw -0xd8(%%ebp,%%eax,2), %%cx\n\t"
      "movw %%cx, -0x14(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_113:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "testb $4, (%%edx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_114\n\t"
      "testw %%bx, %%bx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_115\n\t"
      "pushl $1\n\t"
      "pushl $0x406\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4f00\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_114:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_116\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_115:\n\t"
      "cmpw $4, %%bx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_117\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_116:\n\t"
      "pushl $1\n\t"
      "pushl $0x407\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4ec4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_117:\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x28(%%ecx), %%edx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, -0x14(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_118\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "testb $2, (%%edx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_118\n\t"
      "movl $3, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_121\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_118:\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_119\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_120\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_119:\n\t"
      "movswl %%bx, %%eax\n\t"
      "movl -0x134(%%ebp,%%eax,4), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_120:\n\t"
      "cmpw $0, -0x14(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_122\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_121:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "testb $4, (%%ecx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_122\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_124\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_122:\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_123\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_124\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_123:\n\t"
      "movswl -0xc(%%ebp), %%edx\n\t"
      "movl -0x134(%%ebp,%%edx,4), %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_124:\n\t"
      "pushl %%eax\n\t"
      "pushl $0xa\n\t"
      "pushl %%esi\n\t"
      "call *%[ce2470]\n\t"
      "pushl %%ebx\n\t"
      "pushl $0xb\n\t"
      "pushl %%esi\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_125\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_126\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_125:\n\t"
      "movswl -0xc(%%ebp), %%eax\n\t"
      "movl -0x134(%%ebp,%%eax,4), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_126:\n\t"
      "pushl %%eax\n\t"
      "pushl $0xc\n\t"
      "pushl %%esi\n\t"
      "call *%[ce2470]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movb (%%ebx), %%cl\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xe\n\t"
      "pushl %%esi\n\t"
      "call *%[ce2470]\n\t"
      "movb (%%ebx), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xf\n\t"
      "pushl %%esi\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x18, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_127:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x54(%%edx), %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "leal 0x54(%%edx), %%ebx\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_134\n\t"
      "cmpw %%ax, -0x10(%%ebp)\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_128\n\t"
      "cmpw %%ax, 0x2a(%%edx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_133\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_128:\n\t"
      "pushl $0x64\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x54(%%ebp)\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_129\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testb $0x40, 0x29(%%ecx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_130\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls 0x70(%%edi)\n\t"
      "fchs\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls 0x70(%%edi)\n\t"
      "fchs\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_130\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_129:\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_131\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_130:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "testb $8, 0x29(%%edx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_132\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_131:\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_132:\n\t"
      "shll $5, %%esi\n\t"
      "leal -0x320(%%ebp,%%esi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5a5e18, %%ecx\n\t"
      "leal -0x330(%%ebp,%%esi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x50(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x54(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x6c(%%edi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x2c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190e10]\n\t"
      "addl $0x28, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_136\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_133:\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_134\n\t"
      "testb $8, 0x29(%%edx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_134\n\t"
      "flds 0x5a5c64\n\t"
      "shll $5, %%esi\n\t"
      "fstps -0x330(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c68\n\t"
      "fstps -0x32c(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c6c\n\t"
      "fstps -0x328(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c70\n\t"
      "fstps -0x320(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c74\n\t"
      "fstps -0x31c(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c78\n\t"
      "fstps -0x318(%%ebp,%%esi,1)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_135\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_134:\n\t"
      "shll $5, %%esi\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, -0x330(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x32c(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x328(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x320(%%ebp,%%esi,1)\n\t"
      "movl %%ecx, -0x31c(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x318(%%ebp,%%esi,1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_135:\n\t"
      "movl %%eax, -0x324(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x314(%%ebp,%%esi,1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_136:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "cmpw $4, %%cx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_111\n\t"
      "pushl $8\n\t"
      "leal -0x330(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-0x51\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_141\n\t"
      "pushl $0x2a4e30\n\t"
      "pushl $0\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_137:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_138:\n\t"
      "movb 0x3256d4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x60(%%eax), %%esi\n\t"
      "cmpl $1, %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_139\n\t"
      "movl $1, %%esi\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_139:\n\t"
      "testb $0x10, (%%edi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_144\n\t"
      "cmpw $0, 0x2c(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_144\n\t"
      "pushl $0x5a5bc8\n\t"
      "pushl $0x5a5dc8\n\t"
      "call *%[c99500]\n\t"
      "fdivs 0x5a5dec\n\t"
      "addl $8, %%esp\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_142\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_143\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_140:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_137\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_141:\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl $0x5a5ac0\n\t"
      "pushl %%eax\n\t"
      "call *%[c17c2f0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_137\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_138\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_142:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_143\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_143:\n\t"
      "fmuls 0x5a5de4\n\t"
      "movswl %%si, %%esi\n\t"
      "pushl $0x5a5dd8\n\t"
      "shll $2, %%esi\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x5a5ae8(%%esi)\n\t"
      "movl $0x310c1101, 0x5a5b48(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "movl $0xc00, 0x5a5b74(%%esi)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_144:\n\t"
      "cmpw $1, 0x14(%%edi)\n\t"
      "movw 0x30(%%eax), %%cx\n\t"
      "movl $0, -0x180(%%ebp)\n\t"
      "movl $0, -0x17c(%%ebp)\n\t"
      "movl $0, -0x178(%%ebp)\n\t"
      "movl $0, -0x174(%%ebp)\n\t"
      "movl $0, -0x170(%%ebp)\n\t"
      "movl $0, -0x16c(%%ebp)\n\t"
      "movl $0, -0x168(%%ebp)\n\t"
      "movl $0, -0x164(%%ebp)\n\t"
      "movl $0, -0x160(%%ebp)\n\t"
      "movl $0, -0x15c(%%ebp)\n\t"
      "movl $0x3f800000, -0x158(%%ebp)\n\t"
      "movl $0, -0x154(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_147\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x18(%%edi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_145\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_146\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_145:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_146\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_146:\n\t"
      "fstps -0x158(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_147:\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_148\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_148\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_148\n\t"
      "flds -0x158(%%ebp)\n\t"
      "movswl %%cx, %%edx\n\t"
      "fmuls -0x4(%%eax,%%edx,4)\n\t"
      "fstps -0x158(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_148:\n\t"
      "pushl $3\n\t"
      "leal -0x180(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x54\n\t"
      "call *%[c1eb8d0]\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_149\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_150\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_149:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_150:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movswl 0x2e(%%ebx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_153\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_152\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_151\n\t"
      "pushl $1\n\t"
      "pushl $0x4a1\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x6c(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_155\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_151:\n\t"
      "movl $5, %%ecx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_154\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_152:\n\t"
      "movl $0x15, %%ecx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_154\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_153:\n\t"
      "movl $0x14, %%ecx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_154:\n\t"
      "movl %%ecx, -0x6c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_155:\n\t"
      "movswl 0x2c(%%ebx), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .Lrasterizer_transparent_geometry_group_draw_162\n\t"
      "jmp *.Lrasterizer_transparent_geometry_group_draw_jt2(,%%eax,4)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_156:\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0x1c00, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5ac0(%%eax)\n\t"
      "movl $0xc00, 0x5a5b28(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_157:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl $0x20, %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc002000, %%edx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_159\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_158:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl $0x20, %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc00a000, %%edx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_159:\n\t"
      "movl %%edx, 0x5a5b48(%%eax)\n\t"
      "movl $0xc00, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_160:\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc00, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5b48(%%eax)\n\t"
      "movl $0xc00, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_161:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0x1c00, %%edx\n\t"
      "shll $0x10, %%edx\n\t"
      "movl %%edx, 0x5a5ac0(%%eax)\n\t"
      "movl $0xc00, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%edx, 0x5a5b28(%%eax)\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5b48(%%eax)\n\t"
      "movl %%edx, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_163\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_162:\n\t"
      "pushl $1\n\t"
      "pushl $0x4c0\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x29fac4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_163:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x60(%%eax), %%ecx\n\t"
      "addl $0x60, %%eax\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_164:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x70\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "flds 0x8(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_165\n\t"
      "pushl $1\n\t"
      "pushl $0x4d3\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4d38\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_165:\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_166\n\t"
      "testb $4, (%%esi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_166\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_167\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_166:\n\t"
      "flds 0x5a5e18\n\t"
      "xorl %%edx, %%edx\n\t"
      "fdivs 0x8(%%esi)\n\t"
      "movw 0x6(%%esi), %%dx\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c10a5e0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_167:\n\t"
      "flds 0x1c(%%esi)\n\t"
      "fsubs 0xc(%%esi)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fsubs 0x10(%%esi)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fsubs 0x14(%%esi)\n\t"
      "fstps -0xb8(%%ebp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fsubs 0x18(%%esi)\n\t"
      "fstps -0xb4(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds 0xc(%%esi)\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x10(%%esi)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xb8(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "fmuls -0xb4(%%ebp)\n\t"
      "fadds 0x18(%%esi)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_168\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_169\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_168:\n\t"
      "pushl $1\n\t"
      "pushl $0x4e8\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4cfc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_169:\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_170\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_171\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_170:\n\t"
      "pushl $1\n\t"
      "pushl $0x4e9\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4cc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_171:\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_172\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_173\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_172:\n\t"
      "pushl $1\n\t"
      "pushl $0x4ea\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4c84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_173:\n\t"
      "movw 0x4(%%esi), %%si\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_180\n\t"
      "cmpw $5, %%si\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_180\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_180\n\t"
      "movl (%%eax), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_180\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal -0xc(%%ecx,%%eax,4), %%esi\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_174\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_175\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_174:\n\t"
      "pushl $1\n\t"
      "pushl $0x4f5\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a37d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_175:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_176\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_177\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_176:\n\t"
      "pushl $1\n\t"
      "pushl $0x4f6\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a3798\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_177:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_178\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_179\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_178:\n\t"
      "pushl $1\n\t"
      "pushl $0x4f7\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a375c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_179:\n\t"
      "flds -0x60(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_180:\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[d1c90]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, 0x5a5ae8(,%%ebx,4)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%ebx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "cmpl (%%edx), %%ebx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_164\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_181:\n\t"
      "pushl $6\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movw 0x10(%%edi), %%ax\n\t"
      "leal 0x48(%%ebx), %%esi\n\t"
      "movw %%ax, -0x14(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%ebx, -0x34(%%ebp)\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_183\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_182:\n\t"
      "pushl $0xa0\n\t"
      "leal -0x4f0(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x10\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl $0xffffffff, -0x460(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x73686472\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x4e4(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x4f0(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c174d10]\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x28, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_182\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_183:\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x18\n\t"
      "call *%[c178b40]\n\t"
      "movb 0x29(%%ebx), %%cl\n\t"
      "andb $4, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xfffff6ff, %%ecx\n\t"
      "addl $0x901, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x29(%%ebx), %%dl\n\t"
      "andl $1, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x7f\n\t"
      "pushl $0x3d\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2c(%%ebx), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1580b0]\n\t"
      "movb 0x29(%%ebx), %%al\n\t"
      "addl $0x38, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jns .Lrasterizer_transparent_geometry_group_draw_190\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_190\n\t"
      "movl 0x54(%%ebx), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "leal 0x54(%%ebx), %%eax\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_190\n\t"
      "pushl $0xdc\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x78(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6269746d\n\t"
      "call *%[tag]\n\t"
      "movw 0x60(%%eax), %%dx\n\t"
      "movb 0x60(%%ebx), %%al\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $2, %%al\n\t"
      "movw %%dx, -0x14(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_184\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190c00]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_190\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_184:\n\t"
      "movzbw 0x28(%%ebx), %%cx\n\t"
      "movl 0x6c(%%edi), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "cmpw $8, -0x14(%%ebp)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "setne %%al\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "decl %%eax\n\t"
      "andl $3, %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl 0x4(%%edx), %%eax\n\t"
      "shll $2, %%esi\n\t"
      "fmuls (%%eax,%%esi,1)\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x11c(%%ebp)\n\t"
      "movl -0x11c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_185\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_187\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_185:\n\t"
      "movl 0x6c(%%edi), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "fmuls (%%edx,%%esi,1)\n\t"
      "subl $8, %%esp\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x124(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "cmpl %%eax, -0x124(%%ebp)\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_186\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_187\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_186:\n\t"
      "movl 0x6c(%%edi), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "fmuls (%%edx,%%esi,1)\n\t"
      "subl $8, %%esp\n\t"
      "fadds 0x253398\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x120(%%ebp)\n\t"
      "movl -0x120(%%ebp), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_187:\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_189\n\t"
      "movswl -0x14(%%ebp), %%esi\n\t"
      "movzwl %%cx, %%ecx\n\t"
      "nop\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_188:\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "idivl %%esi\n\t"
      "decl %%ecx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_188\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_189:\n\t"
      "movswl -0x14(%%ebp), %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "movl %%edx, -0x14(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_190:\n\t"
      "movl $0, 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_191:\n\t"
      "movl 0x54(%%ebx), %%ecx\n\t"
      "movswl %%dx, %%esi\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_206\n\t"
      "pushl $0xdc\n\t"
      "leal 0x54(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x2a(%%ebx), %%dx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl $2, %%eax\n\t"
      "movw %%ax, -0xce(%%ebp)\n\t"
      "movw %%ax, -0xcc(%%ebp)\n\t"
      "movw %%ax, -0xca(%%ebp)\n\t"
      "movl $3, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "movw %%dx, -0x10(%%ebp)\n\t"
      "movw $0, -0xd0(%%ebp)\n\t"
      "movl $1, -0x144(%%ebp)\n\t"
      "movl %%eax, -0x140(%%ebp)\n\t"
      "movl %%eax, -0x13c(%%ebp)\n\t"
      "movl %%eax, -0x138(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_192\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_193\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_192:\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "movw -0xd0(%%ebp,%%eax,2), %%cx\n\t"
      "movw %%cx, -0xc(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_193:\n\t"
      "testb $4, (%%ebx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_194\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_194\n\t"
      "pushl $1\n\t"
      "pushl $0x567\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4bc0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_194:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_195\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_196\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_195:\n\t"
      "pushl $1\n\t"
      "pushl $0x568\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4b84\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_196:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x78(%%eax), %%ecx\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_197\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testb $4, (%%eax)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_197\n\t"
      "movl $3, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_200\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_197:\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_198\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_199\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_198:\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x144(%%ebp,%%ecx,4), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_199:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_201\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_200:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "testb $8, (%%edx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_201\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_203\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_201:\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_202\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_203\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_202:\n\t"
      "movswl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x144(%%ebp,%%ecx,4), %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_203:\n\t"
      "pushl %%eax\n\t"
      "movl $0xa, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl %%ebx\n\t"
      "movl $0xb, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_204\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_205\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_204:\n\t"
      "movswl -0x10(%%ebp), %%edx\n\t"
      "movl -0x144(%%ebp,%%edx,4), %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_205:\n\t"
      "pushl %%eax\n\t"
      "movl $0xc, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "movb (%%ebx), %%al\n\t"
      "andb $1, %%al\n\t"
      "negb %%al\n\t"
      "movl $0xe, %%edx\n\t"
      "movl %%esi, %%ecx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1e9410]\n\t"
      "movb (%%ebx), %%cl\n\t"
      "andb $1, %%cl\n\t"
      "negb %%cl\n\t"
      "movl $0xf, %%edx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl -0x34(%%ebp), %%ebx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_206:\n\t"
      "movl 0x54(%%ebx), %%ecx\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_213\n\t"
      "cmpw %%ax, %%dx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_207\n\t"
      "cmpw %%ax, 0x2a(%%ebx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_212\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_207:\n\t"
      "pushl $0xdc\n\t"
      "leal 0x54(%%ebx), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x54(%%eax), %%edx\n\t"
      "movl 0x58(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_208\n\t"
      "testb $0x40, 0x29(%%ebx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_209\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x70(%%edi)\n\t"
      "fchs\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x70(%%edi)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_209\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_208:\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_210\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_209:\n\t"
      "testb $8, 0x29(%%ebx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_211\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_210:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_211:\n\t"
      "shll $5, %%esi\n\t"
      "leal -0x3a0(%%ebp,%%esi,1), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl 0x5a5e18, %%edx\n\t"
      "leal -0x3b0(%%ebp,%%esi,1), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x64(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x60(%%eax), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x5c(%%eax), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x6c(%%edi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $0xa4, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c190e10]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl $0x28, %%esp\n\t"
      "xorl %%eax, %%eax\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_215\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_212:\n\t"
      "cmpl %%ecx, %%esi\n\t"
      "jge .Lrasterizer_transparent_geometry_group_draw_213\n\t"
      "testb $8, 0x29(%%ebx)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_213\n\t"
      "flds 0x5a5c64\n\t"
      "shll $5, %%esi\n\t"
      "fstps -0x3b0(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c68\n\t"
      "fstps -0x3ac(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c6c\n\t"
      "fstps -0x3a8(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c70\n\t"
      "fstps -0x3a0(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c74\n\t"
      "fstps -0x39c(%%ebp,%%esi,1)\n\t"
      "flds 0x5a5c78\n\t"
      "fstps -0x398(%%ebp,%%esi,1)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_214\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_213:\n\t"
      "shll $5, %%esi\n\t"
      "movl $0x3f800000, %%ecx\n\t"
      "movl %%ecx, -0x3b0(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x3ac(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x3a8(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x3a0(%%ebp,%%esi,1)\n\t"
      "movl %%ecx, -0x39c(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x398(%%ebp,%%esi,1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_214:\n\t"
      "movl %%eax, -0x3a4(%%ebp,%%esi,1)\n\t"
      "movl %%eax, -0x394(%%ebp,%%esi,1)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_215:\n\t"
      "incl %%edx\n\t"
      "cmpw $4, %%dx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_191\n\t"
      "pushl $8\n\t"
      "leal -0x3b0(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $-0x51\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_216\n\t"
      "pushl $0x2a4e30\n\t"
      "pushl $0\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_217\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_216:\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl $0x5a5ac0\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17bca0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_218\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_217:\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_218:\n\t"
      "movb 0x3256d4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      "testb $0x10, (%%edi)\n\t"
      "movw 0x54(%%ebx), %%si\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_221\n\t"
      "cmpw $0, 0x2c(%%ebx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_221\n\t"
      "pushl $0x5a5bc8\n\t"
      "pushl $0x5a5dc8\n\t"
      "call *%[c99500]\n\t"
      "fdivs 0x5a5dec\n\t"
      "addl $8, %%esp\n\t"
      "fchs\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_219\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_220\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_219:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_220\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_220:\n\t"
      "flds 0x5a5de4\n\t"
      "movswl %%si, %%esi\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "pushl $0x5a5dd8\n\t"
      "shll $2, %%esi\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fstp %%st(0)\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x5a5ae8(%%esi)\n\t"
      "movl $0x310c1101, 0x5a5b48(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "movl $0xc00, 0x5a5b74(%%esi)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_221:\n\t"
      "cmpw $1, 0x14(%%edi)\n\t"
      "movw 0x30(%%ebx), %%cx\n\t"
      "movl $0, -0x1b0(%%ebp)\n\t"
      "movl $0, -0x1ac(%%ebp)\n\t"
      "movl $0, -0x1a8(%%ebp)\n\t"
      "movl $0, -0x1a4(%%ebp)\n\t"
      "movl $0, -0x1a0(%%ebp)\n\t"
      "movl $0, -0x19c(%%ebp)\n\t"
      "movl $0, -0x198(%%ebp)\n\t"
      "movl $0, -0x194(%%ebp)\n\t"
      "movl $0, -0x190(%%ebp)\n\t"
      "movl $0, -0x18c(%%ebp)\n\t"
      "movl $0x3f800000, -0x188(%%ebp)\n\t"
      "movl $0, -0x184(%%ebp)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_224\n\t"
      "testb $1, 0x60(%%ebx)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_224\n\t"
      "flds 0x2533c8\n\t"
      "fsubs 0x18(%%edi)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_222\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_223\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_222:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_223\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_223:\n\t"
      "fstps -0x188(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_224:\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_225\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_225\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_225\n\t"
      "flds -0x188(%%ebp)\n\t"
      "movswl %%cx, %%ecx\n\t"
      "fmuls -0x4(%%eax,%%ecx,4)\n\t"
      "fstps -0x188(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_225:\n\t"
      "pushl $3\n\t"
      "leal -0x1b0(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-0x54\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_226\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_227\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_226:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_227:\n\t"
      "movswl 0x2e(%%ebx), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_230\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_229\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_228\n\t"
      "pushl $1\n\t"
      "pushl $0x603\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4d68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_232\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_228:\n\t"
      "movl $5, %%ecx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_231\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_229:\n\t"
      "movl $0x15, %%ecx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_231\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_230:\n\t"
      "movl $0x14, %%ecx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_231:\n\t"
      "movl %%ecx, -0x70(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_232:\n\t"
      "movswl 0x2c(%%ebx), %%eax\n\t"
      "cmpl $7, %%eax\n\t"
      "ja .Lrasterizer_transparent_geometry_group_draw_239\n\t"
      "jmp *.Lrasterizer_transparent_geometry_group_draw_jt3(,%%eax,4)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_233:\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0x1c00, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5ac0(%%eax)\n\t"
      "movl $0xc00, 0x5a5b28(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_234:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl $0x20, %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc002000, %%edx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_236\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_235:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "xorl $0x20, %%edx\n\t"
      "shll $0x10, %%ecx\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc00a000, %%edx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_236:\n\t"
      "movl %%edx, 0x5a5b48(%%eax)\n\t"
      "movl $0xc00, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_237:\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0xc00, %%ecx\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5b48(%%eax)\n\t"
      "movl $0xc00, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_238:\n\t"
      "movl %%ecx, %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "shll $2, %%eax\n\t"
      "orl $0x1c00, %%edx\n\t"
      "shll $0x10, %%edx\n\t"
      "movl %%edx, 0x5a5ac0(%%eax)\n\t"
      "movl $0xc00, %%edx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl %%edx, 0x5a5b28(%%eax)\n\t"
      "shll $0x10, %%ecx\n\t"
      "movl %%ecx, 0x5a5b48(%%eax)\n\t"
      "movl %%edx, 0x5a5b74(%%eax)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_240\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_239:\n\t"
      "pushl $1\n\t"
      "pushl $0x622\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x29fac4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_240:\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_241:\n\t"
      "pushl %%edi\n\t"
      "call *%[c179de0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_242:\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movw 0x8a(%%esi), %%bx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $2, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_243\n\t"
      "movb 0x5a5bc4, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_245\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_243:\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_245\n\t"
      "testb $8, 0x28(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_244\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_245\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_244:\n\t"
      "movl $1, %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_245:\n\t"
      "movl 0x70(%%esi), %%ecx\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_246\n\t"
      "flds 0x54(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_246\n\t"
      "flds 0x58(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_246\n\t"
      "flds 0x5c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrasterizer_transparent_geometry_group_draw_250\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_246:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%cl\n\t"
      "andb $4, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xfffff6ff, %%ecx\n\t"
      "addl $0x901, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3e\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x300\n\t"
      "pushl $0x3f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x8006\n\t"
      "pushl $0x4a\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0x3d\n\t"
      "call *%[ce2220]\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2e\n\t"
      "call *%[c178b40]\n\t"
      "flds 0x3c(%%edi)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      "addl $0x14, %%esp\n\t"
      "movl $0x3f800000, -0x278(%%ebp)\n\t"
      "movl $0x3f800000, -0x274(%%ebp)\n\t"
      "fstps -0x280(%%ebp)\n\t"
      "movl $0, -0x270(%%ebp)\n\t"
      "flds 0x40(%%edi)\n\t"
      "movl $0, -0x26c(%%ebp)\n\t"
      "fmuls 0x60(%%esi)\n\t"
      "movl $0, -0x268(%%ebp)\n\t"
      "movl $0, -0x264(%%ebp)\n\t"
      "movl $0, -0x260(%%ebp)\n\t"
      "fstps -0x27c(%%ebp)\n\t"
      "movl $0, -0x25c(%%ebp)\n\t"
      "pushl $3\n\t"
      "leal -0x280(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x54\n\t"
      "movl $0, -0x258(%%ebp)\n\t"
      "movl $0, -0x254(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_247\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_248\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_247:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_248:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $1, %%eax\n\t"
      "leal 0x54(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x5a5b98\n\t"
      "movl %%eax, 0x5a5b94\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "movl $0x8010000, 0x5a5b48\n\t"
      "movl $0xc0, 0x5a5b74\n\t"
      "cmpw $1, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_249\n\t"
      "movl 0x18(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c159070]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5b08\n\t"
      "movl $0x14320000, 0x5a5ac0\n\t"
      "movl $0x40, 0x5a5b28\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_249:\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $0x140c2000, 0x5a5ae0\n\t"
      "movl $0x1400, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_250:\n\t"
      "flds 0x8c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_251\n\t"
      "flds 0x9c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_275\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_251:\n\t"
      "cmpl $-1, 0xb8(%%esi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_252\n\t"
      "cmpw $2, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_275\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_252:\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_253\n\t"
      "cmpw $3, %%bx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_254\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_253:\n\t"
      "pushl $1\n\t"
      "pushl $0x69e\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4b28\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_254:\n\t"
      "movl 0xcc(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $3\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movl 0x476204, %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c155cf0]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xc\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x48, %%esp\n\t"
      "pushl $1\n\t"
      "pushl $0xe\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xf\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movl 0x476204, %%edx\n\t"
      "movl 0x1c(%%edx), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "call *%[c155cf0]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xc\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x48, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xe\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xf\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpw $2, %%bx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_255\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $3\n\t"
      "call *%[c1584f0]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xf\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x48, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_256\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_255:\n\t"
      "movl 0xb8(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "pushl $3\n\t"
      "call *%[c155e80]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xc\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $3\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_256:\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "andb $4, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffff6ff, %%eax\n\t"
      "addl $0x901, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x302\n\t"
      "pushl $0x3e\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x8006\n\t"
      "pushl $0x4a\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x2b\n\t"
      "call *%[c178b40]\n\t"
      "flds 0x3c(%%edi)\n\t"
      "fmuls 0xbc(%%esi)\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x2b0(%%ebp), %%edx\n\t"
      "fstps -0x2b0(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x40(%%edi)\n\t"
      "pushl $-0x54\n\t"
      "fmuls 0xbc(%%esi)\n\t"
      "movl $0x43a00000, -0x2a8(%%ebp)\n\t"
      "movl $0x43700000, -0x2a4(%%ebp)\n\t"
      "movl $0, -0x2a0(%%ebp)\n\t"
      "fstps -0x2ac(%%ebp)\n\t"
      "movl $0, -0x29c(%%ebp)\n\t"
      "movl $0, -0x298(%%ebp)\n\t"
      "movl $0, -0x294(%%ebp)\n\t"
      "movl $0, -0x290(%%ebp)\n\t"
      "movl $0, -0x28c(%%ebp)\n\t"
      "movl $0, -0x288(%%ebp)\n\t"
      "movl $0, -0x284(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_257\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_258\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_257:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_258:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movswl %%bx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_261\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_260\n\t"
      "decl %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_259\n\t"
      "pushl $1\n\t"
      "pushl $0x707\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a1b50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_262\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_259:\n\t"
      "movl $0x8c61, 0x5a5b98\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_262\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_260:\n\t"
      "movl $0x18c61, 0x5a5b98\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_262\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_261:\n\t"
      "movl $0x62e21, 0x5a5b98\n\t"
      "movl $0, 0x5a5ba0\n\t"
      "movl $0x111, 0x5a5b9c\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_262:\n\t"
      "testw %%bx, %%bx\n\t"
      "movl $0x11005, 0x5a5b94\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_263\n\t"
      "cmpl $-1, 0xcc(%%esi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_263\n\t"
      "movl $0x49480b0b, 0x5a5b48\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_273\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_263:\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_264\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x7c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_266\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_264:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_265\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x7c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_266\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_265:\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_266:\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_267\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x78(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_269\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_267:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_268\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x78(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_269\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_268:\n\t"
      "fstps -0x78(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_269:\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls 0x253398\n\t"
      "fsubrs 0x253398\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrasterizer_transparent_geometry_group_draw_270\n\t"
      "fstp %%st(0)\n\t"
      "movl $0, -0x74(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_272\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_270:\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_271\n\t"
      "fstp %%st(0)\n\t"
      "movl $0x3f800000, -0x74(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_272\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_271:\n\t"
      "fstps -0x74(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_272:\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "movl $0x4a410b0b, 0x5a5b48\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_273:\n\t"
      "movl $0x20cd, 0x5a5b74\n\t"
      "movl $0xc0c0d0d, 0x5a5b4c\n\t"
      "movl $0xcd, 0x5a5b78\n\t"
      "cmpw $1, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_274\n\t"
      "movl 0x18(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c159070]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5b0c\n\t"
      "movl $0x14320000, 0x5a5ac4\n\t"
      "movl $0x40, 0x5a5b2c\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_274:\n\t"
      "leal 0x8c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl $0xc0c0d0d, 0x5a5b50\n\t"
      "movl $0xd, 0x5a5b7c\n\t"
      "call *%[d1c90]\n\t"
      "leal 0x9c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x5a5af4\n\t"
      "call *%[d1c90]\n\t"
      "movl %%eax, 0x5a5b14\n\t"
      "movl $0xc00, %%eax\n\t"
      "movl %%eax, 0x5a5b34\n\t"
      "movl %%eax, 0x5a5b80\n\t"
      "movl %%eax, 0x5a5b84\n\t"
      "movl $0x2c120c11, 0x5a5acc\n\t"
      "movl $0x2c020c01, 0x5a5b54\n\t"
      "movl $0x2c0d0c0b, 0x5a5b58\n\t"
      "movl $0xc0f0000, 0x5a5ae0\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "andb $8, %%al\n\t"
      "negb %%al\n\t"
      "pushl $0x5a5ac0\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffffff4, %%eax\n\t"
      "addl $0x14, %%eax\n\t"
      "shll $0x10, %%eax\n\t"
      "orl $0x1c002000, %%eax\n\t"
      "movl %%eax, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_275:\n\t"
      "movl 0x164(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_276\n\t"
      "cmpl %%eax, 0x178(%%esi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_276:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movl 0x178(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x10(%%edi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "call *%[c155e80]\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $1\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%cl\n\t"
      "andb $4, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0xfffff6ff, %%ecx\n\t"
      "addl $0x901, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x302\n\t"
      "pushl $0x3e\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x303\n\t"
      "pushl $0x3f\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl $0x8006\n\t"
      "pushl $0x4a\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0\n\t"
      "pushl $0x3d\n\t"
      "call *%[ce2220]\n\t"
      "movl 0x5c(%%edi), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_277\n\t"
      "pushl %%eax\n\t"
      "pushl $2\n\t"
      "call *%[c155c20]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_278\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_277:\n\t"
      "pushl $0\n\t"
      "pushl $-1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "call *%[c155e80]\n\t"
      "pushl $3\n\t"
      "pushl $0xa\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $3\n\t"
      "pushl $0xb\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xd\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "pushl $2\n\t"
      "pushl $0xe\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $2\n\t"
      "pushl $0xf\n\t"
      "pushl $2\n\t"
      "call *%[ce2470]\n\t"
      "addl $0xc, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_278:\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "movl -0x38(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x19\n\t"
      "call *%[c178b40]\n\t"
      "flds 0x154(%%esi)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x220(%%ebp), %%ecx\n\t"
      "fstps -0x220(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x154(%%esi)\n\t"
      "pushl $-0x54\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "movl $0, -0x210(%%ebp)\n\t"
      "movl $0, -0x20c(%%ebp)\n\t"
      "movl $0, -0x208(%%ebp)\n\t"
      "fstps -0x21c(%%ebp)\n\t"
      "movl $0, -0x204(%%ebp)\n\t"
      "flds 0x168(%%esi)\n\t"
      "movl $0, -0x200(%%ebp)\n\t"
      "fmuls 0x3c(%%edi)\n\t"
      "movl $0, -0x1fc(%%ebp)\n\t"
      "movl $0, -0x1f8(%%ebp)\n\t"
      "movl $0, -0x1f4(%%ebp)\n\t"
      "fstps -0x218(%%ebp)\n\t"
      "flds 0x168(%%esi)\n\t"
      "fmuls 0x40(%%edi)\n\t"
      "fstps -0x214(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_279\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_280\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_279:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_280:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0xc0, %%eax\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $0x421, 0x5a5b98\n\t"
      "movl $3, 0x5a5b94\n\t"
      "movl $0x18190000, 0x5a5ac0\n\t"
      "movl %%eax, 0x5a5b28\n\t"
      "movl $0x8090000, 0x5a5b48\n\t"
      "movl $0x100c0, 0x5a5b74\n\t"
      "movl $0x1c140000, 0x5a5ac4\n\t"
      "movl %%eax, 0x5a5b2c\n\t"
      "movl $0xa200420, 0x5a5b4c\n\t"
      "movl $0xd00, 0x5a5b78\n\t"
      "movl $0xc0d0000, 0x5a5b50\n\t"
      "movl %%eax, 0x5a5b7c\n\t"
      "movl $0xc, 0x5a5ae0\n\t"
      "movl $0x1c00, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "movl 0x5c(%%edi), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "setne %%dl\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_281:\n\t"
      "pushl $9\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "flds 0x2533c8\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x6c(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "movl $0x3f800000, -0x3c(%%ebp)\n\t"
      "movl $0x3f800000, -0x44(%%ebp)\n\t"
      "movl $0x3f800000, -0x4c(%%ebp)\n\t"
      "movl $0x3f800000, -0x48(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_286\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_286\n\t"
      "movw 0xd8(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_282\n\t"
      "cmpw $4, %%cx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_282\n\t"
      "movswl %%cx, %%ecx\n\t"
      "flds -0x4(%%eax,%%ecx,4)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_282:\n\t"
      "movw 0xda(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_283\n\t"
      "cmpw $4, %%cx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_283\n\t"
      "movswl %%cx, %%edx\n\t"
      "flds -0x4(%%eax,%%edx,4)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_283:\n\t"
      "movw 0xdc(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_284\n\t"
      "cmpw $4, %%cx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_284\n\t"
      "movswl %%cx, %%ecx\n\t"
      "flds -0x4(%%eax,%%ecx,4)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_284:\n\t"
      "movw 0xde(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_285\n\t"
      "cmpw $4, %%cx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_285\n\t"
      "movswl %%cx, %%edx\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%eax,%%edx,4)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_285:\n\t"
      "movw 0xe0(%%esi), %%cx\n\t"
      "cmpw %%bx, %%cx\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_286\n\t"
      "cmpw $4, %%cx\n\t"
      "jg .Lrasterizer_transparent_geometry_group_draw_286\n\t"
      "movswl %%cx, %%ecx\n\t"
      "flds -0x4(%%eax,%%ecx,4)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_286:\n\t"
      "movb 0x3256c3, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_296\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%ecx\n\t"
      "flds 0x5a5e18\n\t"
      "fdivs 0x325724\n\t"
      "fstps (%%esp)\n\t"
      "pushl $2\n\t"
      "call *%[c10a5e0]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x325728\n\t"
      "addl $8, %%esp\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_287\n\t"
      "movl 0x325728, %%edx\n\t"
      "movl %%edx, -0x3c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_288\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_287:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_288:\n\t"
      "flds 0x32572c\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_289\n\t"
      "movl 0x32572c, %%ecx\n\t"
      "movl %%ecx, -0x44(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_290\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_289:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_290:\n\t"
      "flds 0x325730\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_291\n\t"
      "movl 0x325730, %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_292\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_291:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, -0x4c(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_292:\n\t"
      "flds 0x325734\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_293\n\t"
      "flds 0x325734\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_294\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_293:\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_294:\n\t"
      "flds 0x325738\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_295\n\t"
      "movl 0x325738, %%edx\n\t"
      "movl %%edx, -0x48(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_296\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_295:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl %%eax, -0x48(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_296:\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0xa0(%%esi)\n\t"
      "fstps -0x150(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0xa4(%%esi)\n\t"
      "fstps -0x14c(%%ebp)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fmuls 0xa8(%%esi)\n\t"
      "fstps -0x148(%%ebp)\n\t"
      "fmuls 0x253f78\n\t"
      "fcoms 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_297\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_297:\n\t"
      "flds 0x2533c8\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "testb $8, %%al\n\t"
      ".byte 0xd8, 0xf1\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_298\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "movl 0xbc(%%esi), %%ecx\n\t"
      "fmuls 0xac(%%esi)\n\t"
      "movl 0xb8(%%esi), %%edx\n\t"
      "leal 0x7c(%%esi), %%eax\n\t"
      "movl %%ecx, -0x118(%%ebp)\n\t"
      "movl -0x4c(%%ebp), %%ecx\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0xb0(%%esi)\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, -0x68(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x3c(%%ebp)\n\t"
      "fmuls 0xb4(%%esi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "call *%[c99530]\n\t"
      "leal 0x88(%%esi), %%edx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c99530]\n\t"
      "movl -0x118(%%ebp), %%edx\n\t"
      "leal 0x94(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c99530]\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0x150(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_299\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_298:\n\t"
      "movl -0x4c(%%ebp), %%edx\n\t"
      "leal 0x7c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c99530]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "leal 0x88(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99530]\n\t"
      "leal 0x94(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[c99530]\n\t"
      "movl -0x48(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "leal -0x150(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99530]\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "leal 0xac(%%esi), %%edx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_299:\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c99530]\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "addl $0x28, %%esp\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "pushl $1\n\t"
      "pushl $0xa\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $1\n\t"
      "pushl $0xb\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "andb $0x10, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "addl $2, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0xd\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%cl\n\t"
      "andb $0x10, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "addl $2, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xe\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%dl\n\t"
      "andb $0x10, %%dl\n\t"
      "addl $0x44, %%esp\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0xf\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "andb $2, %%al\n\t"
      "negb %%al\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0xfffff6ff, %%eax\n\t"
      "addl $0x901, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x28(%%esi), %%cl\n\t"
      "shrl $2, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $2, %%ecx\n\t"
      "orl $0x8001, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3e\n\t"
      "call *%[ce2220]\n\t"
      "movb 0x28(%%esi), %%dl\n\t"
      "andb $8, %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0xffff8301, %%edx\n\t"
      "addl $0x8001, %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x3f\n\t"
      "call *%[ce2220]\n\t"
      "pushl %%ebx\n\t"
      "pushl $0x4b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x8006\n\t"
      "pushl $0x4a\n\t"
      "call *%[ce2220]\n\t"
      "addl $0x44, %%esp\n\t"
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "movl -0x38(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x16\n\t"
      "call *%[c178b40]\n\t"
      "movl 0x3c(%%edi), %%edx\n\t"
      "movl 0x40(%%edi), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x250(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x54\n\t"
      "movl $0x3f800000, -0x250(%%ebp)\n\t"
      "movl $0x3f800000, -0x24c(%%ebp)\n\t"
      "movl $0x3f800000, -0x248(%%ebp)\n\t"
      "movl $0x3f800000, -0x244(%%ebp)\n\t"
      "movl %%edx, -0x240(%%ebp)\n\t"
      "movl $0, -0x23c(%%ebp)\n\t"
      "movl $0, -0x238(%%ebp)\n\t"
      "movl $0, -0x234(%%ebp)\n\t"
      "movl $0, -0x230(%%ebp)\n\t"
      "movl %%eax, -0x22c(%%ebp)\n\t"
      "movl $0, -0x228(%%ebp)\n\t"
      "movl $0, -0x224(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_300\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_301\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_300:\n\t"
      "pushl $0x2a4d98\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_301:\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $4\n\t"
      "pushl $0x15\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl $0x20c00, %%eax\n\t"
      "movl %%eax, 0x5a5b28\n\t"
      "movl %%eax, 0x5a5b74\n\t"
      "movl -0x34(%%ebp), %%eax\n\t"
      "movl %%edx, 0x5a5ae8\n\t"
      "movl %%edx, 0x5a5b10\n\t"
      "movl %%ecx, 0x5a5b08\n\t"
      "movl %%ecx, 0x5a5b0c\n\t"
      "movl $0xc00, %%ecx\n\t"
      "movl %%eax, 0x5a5aec\n\t"
      "movl %%eax, 0x5a5af0\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl $1, 0x5a5b98\n\t"
      "movl $0x11104, 0x5a5b94\n\t"
      "movl $0x12081208, 0x5a5ac0\n\t"
      "movl $0x1120e820, 0x5a5b48\n\t"
      "movl $0x6c200000, 0x5a5ac4\n\t"
      "movl $0xc0, 0x5a5b2c\n\t"
      "movl $0x3c011c02, 0x5a5b4c\n\t"
      "movl %%ecx, 0x5a5b78\n\t"
      "movl $0x820b120, 0x5a5ac8\n\t"
      "movl %%ecx, 0x5a5b30\n\t"
      "movb 0x28(%%esi), %%dl\n\t"
      "andb $4, %%dl\n\t"
      "addl $0x18, %%esp\n\t"
      "negb %%dl\n\t"
      "movl %%eax, 0x5a5af4\n\t"
      "movl $0x4c00, %%eax\n\t"
      "movl %%eax, 0x5a5b34\n\t"
      "movl %%eax, 0x5a5b80\n\t"
      "movb 0x3256c3, %%al\n\t"
      "movl %%ecx, 0x5a5b7c\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0xe0, %%edx\n\t"
      "addl $2, %%edx\n\t"
      "orl $0xc201c00, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%edx, 0x5a5b50\n\t"
      "movl %%ebx, 0x5a5b14\n\t"
      "movl $0x12201120, 0x5a5acc\n\t"
      "movl $0xc200120, 0x5a5b54\n\t"
      "movl $0xc180000, 0x5a5ae0\n\t"
      "movl $0x1c00, 0x5a5ae4\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_302\n\t"
      "cmpw $0, 0x3256ea\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_302\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $0\n\t"
      "pushl $0x15\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "pushl $0\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl $1, %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpw %%ax, 0x3256ea\n\t"
      "movl %%eax, 0x5a5b98\n\t"
      "setle %%cl\n\t"
      "movl %%eax, 0x5a5b94\n\t"
      "decl %%ecx\n\t"
      "andl $0x10, %%ecx\n\t"
      "addl $8, %%ecx\n\t"
      "movl %%ecx, 0x5a5ae0\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_302:\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "pushl $0\n\t"
      "pushl $0x15\n\t"
      "pushl $0\n\t"
      "call *%[ce2470]\n\t"
      "addl $0x18, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_303:\n\t"
      "pushl %%edi\n\t"
      "call *%[c16eef0]\n\t"
      "addl $4, %%esp\n\t"
      "jmp .Lrasterizer_transparent_geometry_group_draw_305\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_304:\n\t"
      "pushl $0x2a4b04\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_305:\n\t"
      "movl -0x80(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw $2, %%ax\n\t"
      "movl %%eax, -0x80(%%ebp)\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_64\n\t"
      "movl $1, %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_306:\n\t"
      "testb $8, (%%edi)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_307\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_307\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c156c30]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_307:\n\t"
      "cmpb $0, (%%edi)\n\t"
      "jns .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "cmpw %%bx, 0x14(%%edi)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_309\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c156c30]\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_308:\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_309:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_310\n\t"
      "movl 0x8(%%edi), %%edx\n\t"
      "movl %%edx, 0x47e4b8\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_310:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x96(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_311\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c184460]\n\t"
      "addl $4, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[c174d10]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_311:\n\t"
      "movb -0x2d(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_315\n\t"
      "leal 0xa(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c184390]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_312\n\t"
      "pushl $1\n\t"
      "pushl $0x8e0\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a4afc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_312:\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpw %%si, 0xa(%%ebp)\n\t"
      "jle .Lrasterizer_transparent_geometry_group_draw_315\n\t"
      "movl $1, %%ebx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_313:\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "movswl %%si, %%eax\n\t"
      "leal (%%eax,%%eax,4), %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "leal (%%ecx,%%edx,1), %%eax\n\t"
      "movl 0x98(%%eax), %%ecx\n\t"
      "cmpl 0x8(%%edi), %%ecx\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_314\n\t"
      "cmpw %%bx, 0x14(%%eax)\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_314\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c174d10]\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x3256ea\n\t"
      "je .Lrasterizer_transparent_geometry_group_draw_314\n\t"
      "movb $1, 0x47e4c0\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_314:\n\t"
      "incl %%esi\n\t"
      "cmpw 0xa(%%ebp), %%si\n\t"
      "jl .Lrasterizer_transparent_geometry_group_draw_313\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_315:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrasterizer_transparent_geometry_group_draw_316\n\t"
      "pushl $0x2a4ac0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_316:\n\t"
      "popl %%ebx\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_317:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_jt0:\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_72\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_304\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_304\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_70\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_103\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_181\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_241\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_242\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_281\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_303\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_jt1:\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_95\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_96\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_97\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_98\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_98\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_96\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_98\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_99\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_jt2:\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_156\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_157\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_158\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_160\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_160\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_157\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_160\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_161\n\t"
      ".text\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrasterizer_transparent_geometry_group_draw_jt3:\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_233\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_234\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_235\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_237\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_237\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_234\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_237\n\t"
      ".long .Lrasterizer_transparent_geometry_group_draw_238\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b174d10_assert), [exitfn] "m"(b174d10_exitfn), [c184570] "m"(b174d10_c184570), [c1845b0] "m"(b174d10_c1845b0), [c184460] "m"(b174d10_c184460), [c174d10] "m"(b174d10_c174d10), [c184610] "m"(b174d10_c184610), [c178b40] "m"(b174d10_c178b40), [c1e96d0] "m"(b174d10_c1e96d0), [c1e9350] "m"(b174d10_c1e9350), [c1ea290] "m"(b174d10_c1ea290), [c1e98e0] "m"(b174d10_c1e98e0), [memset] "m"(b174d10_memset), [rmreal] "m"(b174d10_rmreal), [cd1dd0] "m"(b174d10_cd1dd0), [c156510] "m"(b174d10_c156510), [c156710] "m"(b174d10_c156710), [c1eb8d0] "m"(b174d10_c1eb8d0), [c174510] "m"(b174d10_c174510), [c1d90f0] "m"(b174d10_c1d90f0), [c189cb0] "m"(b174d10_c189cb0), [ce2220] "m"(b174d10_ce2220), [c190980] "m"(b174d10_c190980), [c156ab0] "m"(b174d10_c156ab0), [c1843b0] "m"(b174d10_c1843b0), [c190930] "m"(b174d10_c190930), [c1595c0] "m"(b174d10_c1595c0), [c190710] "m"(b174d10_c190710), [c156c30] "m"(b174d10_c156c30), [c1908a0] "m"(b174d10_c1908a0), [c1906b0] "m"(b174d10_c1906b0), [c158ae0] "m"(b174d10_c158ae0), [c159900] "m"(b174d10_c159900), [c155c20] "m"(b174d10_c155c20), [ce2470] "m"(b174d10_ce2470), [c155e80] "m"(b174d10_c155e80), [c1580b0] "m"(b174d10_c1580b0), [c190e10] "m"(b174d10_c190e10), [c167ff0] "m"(b174d10_c167ff0), [c13070] "m"(b174d10_c13070), [c1eb2d0] "m"(b174d10_c1eb2d0), [c8e0b0] "m"(b174d10_c8e0b0), [elem] "m"(b174d10_elem), [tag] "m"(b174d10_tag), [c1d9c2b] "m"(b174d10_c1d9c2b), [c1e9410] "m"(b174d10_c1e9410), [c99500] "m"(b174d10_c99500), [c17c2f0] "m"(b174d10_c17c2f0), [c99530] "m"(b174d10_c99530), [c10a5e0] "m"(b174d10_c10a5e0), [d1c90] "m"(b174d10_d1c90), [c190c00] "m"(b174d10_c190c00), [c17bca0] "m"(b174d10_c17bca0), [c179de0] "m"(b174d10_c179de0), [c159070] "m"(b174d10_c159070), [c155cf0] "m"(b174d10_c155cf0), [c1584f0] "m"(b174d10_c1584f0), [c16eef0] "m"(b174d10_c16eef0), [c8f390] "m"(b174d10_c8f390), [c184390] "m"(b174d10_c184390)
      : "memory");
}
#else
#error "rasterizer_transparent_geometry_group_draw: clang naked draft required"
#endif


void rasterizer_frame_begin(float *elapsed)
{
  char val;

  val = *(char *)0x3256c8;
  if (val < 2) {
    *(char *)0x3256d4 = val;
    *(char *)0x3256d3 = val;
    *(char *)0x3256d2 = val;
    *(char *)0x3256d1 = val;
    *(char *)0x3256d0 = val;
    *(char *)0x3256cf = val;
    *(char *)0x3256ce = val;
    *(char *)0x3256cd = val;
    *(char *)0x3256cc = val;
    *(char *)0x3256ca = val;
    *(char *)0x3256cb = val;
    *(char *)0x3256c9 = val;
    *(char *)0x3256d5 = val;
    *(char *)0x3256c8 = 2;
  }
  if (*(float *)0x325694 == *(float *)0x2533c0)
    *(int *)0x325694 = *(int *)0x2af1ac;
  if (*(float *)0x325698 == *(float *)0x2533c0)
    *(int *)0x325698 = *(int *)0x2af1b0;
  if (*(float *)0x32569c == *(float *)0x2533c0)
    *(int *)0x32569c = *(int *)0x2af1b4;
  if (*(float *)0x3256a0 == *(float *)0x2533c0)
    *(int *)0x3256a0 = *(int *)0x2af1b8;
  ((void (*)(float *))0x157940)(elapsed);
}

int rasterizer_windows_begin(void)
{
  return ((int (*)(void))0x1559d0)();
}

static void sanitize_window_screen_flash(window_parameters_t *parameters)
{
  int32_t *flash_type = (int32_t *)((char *)parameters + 0x238);
  float *flash_scale = (float *)((char *)parameters + 0x23c);
  float *flash_color = (float *)((char *)parameters + 0x240);

  if (*flash_type == 0) {
    return;
  }

  if (!(*flash_scale >= 0.0f && *flash_scale <= 1.0f)) {
    *flash_scale = 0.0f;
    *flash_type = 0;
    return;
  }

  if (!(flash_color[0] >= 0.0f && flash_color[0] <= 1.0f &&
        flash_color[1] >= 0.0f && flash_color[1] <= 1.0f &&
        flash_color[2] >= 0.0f && flash_color[2] <= 1.0f &&
        flash_color[3] >= 0.0f && flash_color[3] <= 1.0f)) {
    *flash_type = 0;
    *flash_scale = 0.0f;
    flash_color[0] = 0.0f;
    flash_color[1] = 0.0f;
    flash_color[2] = 0.0f;
    flash_color[3] = 0.0f;
  }
}

int rasterizer_window_begin(window_parameters_t *a1)
{
  sanitize_window_screen_flash(a1);
  return ((int (*)(window_parameters_t *))0x158df0)(a1);
}

void rasterizer_window_end(void)
{
  ((void (*)(void))0x158f90)();
}

void rasterizer_windows_end(void)
{
  ((void (*)(void))0x155a40)();
}

void rasterizer_frame_end(void)
{
  ((void (*)(void))0x155a70)();
}

void rasterizer_set_vblank_callback(void *cb)
{
  ((void (*)(void *))0x155c10)(cb);
}

/* 0x172a30
 *
 * FUN_00172a30
 *
 * Shadow-pass begin / shadow-generate setup. Programs the D3D render
 * states, pixel shader, and vertex-shader constants for the shadow
 * generation pass, then stashes the shadow projection matrix, RGB color,
 * and object bounding radius into the module-global shadow parameter block
 * (0x47e46c..).
 *
 * Asserts the D3D device exists. When rendering is enabled
 * (*(short *)0x5a5bc0 == 0) and the shadow feature flag is set
 * (*(char *)0x3256ca != 0):
 *   1. Validates the matrix/color pointers, each RGB component (in [0,1]),
 *      and the object bounding radius (> 0).
 *   2. Sets cull mode, four "simple" render states (each mirrored into a
 *      module global at 0x1fb7a4/784/788/78c), disables Z test and Z bias.
 *   3. Clears and programs the 0xf0-byte pixel-shader state block at
 *      0x5a5ac0, then binds it.
 *   4. Builds five vertex-shader constant registers - a shadow-projection
 *      transform scaled by 1/radius - and uploads them at register -0x44.
 *   5. Stashes the 13-dword matrix, RGB color, and radius into the shadow
 *      parameter block, and clears the associated state bytes.
 *   6. Optionally writes the radius back through out_radius.
 *   7. If the render-mode word (*(short *)0x3256ba) == 2, bumps the
 *      per-frame counter at 0x5a5430.
 *
 * param_1:                unused (present for the cdecl caller ABI).
 * shadow_matrix:          shadow projection matrix (13 dwords / 4x3-ish).
 * shadow_color:           RGB shadow color (3 floats, each in [0,1]).
 * object_bounding_radius: bounding radius (> 0); its reciprocal scales the
 *                         projection transform.
 * out_radius:             optional; receives object_bounding_radius.
 *
 * Returns 1 (AL).
 */
char FUN_00172a30(int param_1, const float *shadow_matrix,
                  const float *shadow_color, float object_bounding_radius,
                  float *out_radius)
{
  float vs_const[20];
  float inv_r;
  const unsigned long *src;
  unsigned long *dst;
  int i;

  (void)param_1;

  if (*(void **)0x476ab0 == 0) {
    display_assert(
      "global_d3d_device",
      "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x93, 1);
    system_exit(-1);
  }
  if (*(short *)0x5a5bc0 == 0 && *(char *)0x3256ca != 0) {
    if (shadow_matrix == 0) {
      display_assert(
        "shadow_matrix",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x99,
        1);
      system_exit(-1);
    }
    if (shadow_color == 0) {
      display_assert(
        "shadow_color",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x9a,
        1);
      system_exit(-1);
    }
    if (!(shadow_color[0] >= 0.0f) || !(shadow_color[0] <= 1.0f)) {
      display_assert(
        "shadow_color->red >=0.0f && shadow_color->red <=1.0f",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x9b,
        1);
      system_exit(-1);
    }
    if (!(shadow_color[1] >= 0.0f) || !(shadow_color[1] <= 1.0f)) {
      display_assert(
        "shadow_color->green>=0.0f && shadow_color->green<=1.0f",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x9c,
        1);
      system_exit(-1);
    }
    if (!(shadow_color[2] >= 0.0f) || !(shadow_color[2] <= 1.0f)) {
      display_assert(
        "shadow_color->blue >=0.0f && shadow_color->blue <=1.0f",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x9d,
        1);
      system_exit(-1);
    }
    if (!(object_bounding_radius > 0.0f)) {
      display_assert(
        "object_bounding_radius>0.0f",
        "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_shadows.c", 0x9e,
        1);
      system_exit(-1);
    }

    /* Render state: cull, four "simple" states (mirrored to module globals),
     * Z test/bias off. Each mirror store is paired with its state by value;
     * MSVC schedules the store into the following call's setup window. */
    D3DDevice_SetRenderState_CullMode(0x901);
    D3DDevice_SetRenderState_Simple(NV097_SET_COLOR_MASK_CMD, NV097_COLOR_MASK_RGB);
    *(unsigned long *)0x1fb7a4 = 0x10101;
    D3DDevice_SetRenderState_Simple(0x40304, 0);
    *(unsigned long *)0x1fb784 = 0;
    D3DDevice_SetRenderState_Simple(0x40300, 1);
    *(unsigned long *)0x1fb788 = 1;
    D3DDevice_SetRenderState_Simple(0x40340, 0x7f);
    *(unsigned long *)0x1fb78c = 0x7f;
    D3DDevice_SetRenderState_ZEnable(0);
    D3DDevice_SetRenderState_ZBias(0);

    /* Program and bind the shadow-generation pixel-shader state block. */
    csmemset((void *)0x5a5ac0, 0, 0xf0);
    *(int *)0x5a5b98 = 1;
    *(int *)0x5a5b94 = 1;
    *(int *)0x5a5ae0 = 0x20;
    *(int *)0x5a5ae4 = 0x1800;
    rasterizer_set_pixel_shader((void *)0x5a5ac0);

    /* Vertex-shader constants: rows 0/1 are the shadow projection scaled by
     * 1/radius; the trailing constants are fixed. All 20 floats form one
     * contiguous buffer that SetVertexShaderConstant uploads (5 registers). */
    inv_r = 1.0f / object_bounding_radius;
    vs_const[8] = 0.0f;
    vs_const[9] = 0.0f;
    vs_const[10] = 0.0f;
    vs_const[11] = 0.5f;
    vs_const[12] = 0.0f;
    vs_const[0] = inv_r * shadow_matrix[1];
    vs_const[1] = inv_r * shadow_matrix[2];
    vs_const[2] = inv_r * shadow_matrix[3];
    vs_const[3] = -((shadow_matrix[10] * shadow_matrix[1] +
                     shadow_matrix[11] * shadow_matrix[2] +
                     shadow_matrix[12] * shadow_matrix[3]) *
                    inv_r);
    vs_const[4] = inv_r * shadow_matrix[4];
    vs_const[5] = inv_r * shadow_matrix[5];
    vs_const[6] = inv_r * shadow_matrix[6];
    vs_const[7] = -((shadow_matrix[10] * shadow_matrix[4] +
                     shadow_matrix[11] * shadow_matrix[5] +
                     shadow_matrix[12] * shadow_matrix[6]) *
                    inv_r);
    vs_const[13] = 0.0f;
    vs_const[14] = 0.0f;
    vs_const[15] = 1.0f;
    vs_const[16] = 0.0f;
    vs_const[17] = 0.0f;
    vs_const[18] = 0.0f;
    vs_const[19] = 0.0f;
    D3DDevice_SetVertexShaderConstant(-0x44, vs_const, 5);

    FUN_00158140(2, 0,
                 (*(unsigned char *)0x3256f7 != 0) ? 0x88888888u : 0u, 1, 0);
    FUN_00158ae0(0);

    /* Stash the 13-dword matrix, then the RGB color, then the radius. */
    src = (const unsigned long *)shadow_matrix;
    dst = (unsigned long *)0x47e47c;
    for (i = 0xd; i != 0; i--) {
      *dst = *src;
      src++;
      dst++;
    }
    *(float *)0x47e46c = shadow_color[0];
    *(float *)0x47e470 = shadow_color[1];
    *(float *)0x47e474 = shadow_color[2];
    *(float *)0x47e478 = object_bounding_radius;
    if (out_radius != 0) {
      *out_radius = object_bounding_radius;
    }
    *(int *)0x47e4b0 = 0;
    *(char *)0x47e4b4 = 0;
    *(char *)0x47e4b5 = 0;
    *(char *)0x3251fc = 0;
    if (*(short *)0x3256ba == 2) {
      *(int *)0x5a5430 = *(int *)0x5a5430 + 1;
    }
  }
  return 1;
}
/* --- rasterizer.obj batch drafts (2026-07-26) --- */

/* 0x16f480 */
void FUN_0016f480(const char *message, int16_t profile_index, char condition)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x16f4a4 */
  display_assert((char *)0x00294af0, (char *)0x002a3ca4, 60, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x16f4f0 */
  /* relift: cmp word ptr [0x47e468], 3 -> jge 0x16f4f0 */
  error(0, (char *)0x002a3c7c);
  error(0, (char *)0x002a3c5c);

  (void)eax;
  (void)esi;
}

/* 0x16f500 */
void FUN_0016f500(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x16f5e8 */
  /* cmp (int16_t)esi, 0x1d -> jge 0x16f5e8 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* test (char)ebx, (char)ebx -> je 0x16f579 */
  /* relift: relift: mov (int16_t)edx, word ptr [0x47e460] */
  /* relift: relift: mov word ptr [0x47e460], (int16_t)edx */
  /* relift: relift: mov (int16_t)eax, word ptr [0x47e460] */
  /* relift: relift: mov (int16_t)edx, word ptr [0x47e460] */
  /* relift: relift: mov word ptr [0x47e460], (int16_t)edx */
  /* relift: relift: mov (int16_t)eax, word ptr [0x47e460] */
  /* relift: relift: mov (int16_t)ecx, word ptr [0x47e460] */
  /* relift: relift: mov word ptr [0x47e460], (int16_t)ecx */
  /* relift: relift: mov (int16_t)edx, word ptr [0x47e460] */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x16f610 */
void FUN_0016f610(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x16f692 */
  /* cmp (int16_t)esi, 0x10 -> jge 0x16f692 */
  QueryPerformanceCounter((void *)(uintptr_t)eax);
  /* test (char)ebx, 1 -> je 0x16f67b */
  /* relift: relift: mov word ptr [0x47e454], (int16_t)esi */
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16f6b6 */
  /* relift: relift: mov (char)eax, byte ptr [0x325704] */
  /* test (char)eax, (char)eax -> jne 0x16f6b6 */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x16f6c0 */
void FUN_0016f6c0(void)
{
  csmemset((void *)0x0047e108, 0, 128);
  csmemset((void *)0x0047e088, 0, 128);
  csmemset((void *)0x0047e008, 0, 128);
  QueryPerformanceFrequency((void *)0x00325178);
}

/* 0x16f730 */
void FUN_0016f730(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* cmp eax, ebx -> jne 0x16f760 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 194, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x47e460] */
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f79a */
  error(0, (char *)0x002a3c5c);
  /* relift: relift: mov (char)ecx, byte ptr [0x47e460] */
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f7d4 */
  error(0, (char *)0x002a3c5c);
  /* relift: relift: mov dl, byte ptr [0x47e460] */
  /* relift: cmp word ptr [0x47e468], (int16_t)esi -> jge 0x16f80f */
  error(0, (char *)0x002a3c5c);
  /* relift: relift: mov word ptr [0x47e460], (int16_t)ebx */
  /* relift: cmp byte ptr [0x325704], (char)ebx -> je 0x16f875 */
  /* mem[0x0047e45c] = ebx */
  /* relift: relift: mov word ptr [0x325184], (int16_t)ebx */
  /* relift: relift: mov word ptr [0x325180], 0xffff */
  /* mem[0x0047e440] = ebx */
  /* mem[0x0047e444] = ebx */
  /* relift: relift: mov word ptr [0x47e450], (int16_t)eax */
  D3DDevice_InsertCallback(ebx, (void *)0x0016f610, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x16f880 */
void FUN_0016f880(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x16f8a0 */
void FUN_0016f8a0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x16f8dd */
  /* relift: cmp word ptr [0x47e458], 0 -> jg 0x16f8d4 */
  display_assert((char *)0x002a3d48, (char *)0x002a3ca4, 244, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x47e458], 0x64 -> jl 0x16f907 */
  display_assert((char *)0x002a3d2c, (char *)0x002a3ca4, 249, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16f93c */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 259, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16f953 */
  /* relift: relift: mov (char)eax, byte ptr [0x325704] */
  /* test (char)eax, (char)eax -> je 0x16fa35 */
  /* relift: cmp word ptr [0x325184], 0 -> jne 0x16fa35 */
  /* relift: cmp word ptr [0x47e458], 0 -> jne 0x16fa35 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16f980 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16f9a0 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 265, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16f9c9 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 266, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  FUN_0016f480((char *)(uintptr_t)ecx, 0, 0);
  D3DDevice_InsertCallback(esi, (void *)0x0016f500, edx);
  /* relift: relift: mov word ptr [0x325180], (int16_t)edi */
  /* test eax, eax -> jne 0x16fa6d */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 294, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16fa84 */
  /* relift: relift: mov (char)eax, byte ptr [0x325704] */
  /* test (char)eax, (char)eax -> je 0x16fb72 */
  /* relift: cmp word ptr [0x325184], 0 -> jne 0x16fb72 */
  /* relift: cmp word ptr [0x47e458], 0 -> jne 0x16fb72 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16fab1 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fad1 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 300, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x16fafa */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 301, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  D3DDevice_InsertCallback(0, (void *)0x0016f500, ebx);
  /* relift: relift: mov word ptr [0x325180], 0xffff */
  /* mem[0x0047e45c] = eax */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x16fb80 */
void rasterizer_initialize(void)
{
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x16fb93 */
  /* cmp (int16_t)esi, 0x1d -> jl 0x16fbc0 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 363, 0);
  system_exit(0);

  (void)esi;
}

/* 0x16fbd0 */
void FUN_0016fbd0(void)
{
  int eax = 0;
  int edx = 0;
  int edi = 0;

  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: mov (char)eax, byte ptr [0x325704] */
  /* test (char)eax, (char)eax -> je 0x16fcea */
  /* test eax, eax -> jne 0x16fc24 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 375, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x1d -> jne 0x16fc64 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fc91 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 391, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  /* test edx, eax -> je 0x16fce2 */
  /* relift: relift: fld dword ptr [0x255e94] */

  (void)eax;
  (void)edx;
  (void)edi;
}

/* 0x16fcf0 */
void FUN_0016fcf0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  /* relift: relift: mov (char)ecx, byte ptr [0x325704] */
  /* test (char)ecx, (char)ecx -> je 0x16fdc4 */
  /* test eax, eax -> jne 0x16fd37 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 415, 0);
  system_exit(0);
  /* cmp (int16_t)edi, 0x1d -> jne 0x16fd45 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x16fd50 */
  /* cmp (int16_t)edi, 0x1d -> jl 0x16fd70 */
  display_assert((char *)0x002a3db8, (char *)0x002a3ca4, 430, 0);
  system_exit(0);
  FUN_0016f480((char *)(uintptr_t)eax, 0, 0);
  /* test edx, eax -> je 0x16fdc1 */
  /* cmp eax, 0x7fffffff -> jbe 0x16fdc4 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)edi;
}

/* 0x16fdd0 */
void FUN_0016FDD0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  /* relift: cmp word ptr [0x3256ba], 3 -> je 0x16fded */
  /* relift: relift: mov (char)eax, byte ptr [0x325704] */
  /* test (char)eax, (char)eax -> je 0x16fe9d */
  /* test eax, eax -> jne 0x16fe16 */
  display_assert((char *)0x0029dc40, (char *)0x002a3ca4, 455, 0);
  system_exit(0);
  /* cmp eax, 0x7fffffff -> jbe 0x16fe41 */
  /* mem[0x0047e448] = eax */
  /* mem[0x0047e44c] = edx */
  D3DDevice_InsertCallback(0, (void *)0x0016f610, ecx);
  FUN_0008f810(0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x16feb0 */
void FUN_0016FEB0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x16fec0 */
void FUN_0016fec0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp esi, 0x52 -> jge 0x16feeb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x16fef9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x16ff0e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x16ff1a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x16ff26 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x16ff32 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x16ff3e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x16ff4a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x16ff56 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x16ff62 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x16ff6e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x16ff7a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x16ff86 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x16ff95 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x16ffa4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x16ffb3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x16ffc2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x16ffd1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x16ffe0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x16ffef */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x16fffe */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17000d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17001c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x17002b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17003a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x170049 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x170058 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x170067 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x170075 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17008c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x170099 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1700a6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1700b3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1700c0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1700d0 */
void FUN_001700d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x1700f7 */
  display_assert((char *)0x002a3e7c, (char *)0x002a3e80, 30, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a3e60, (char *)0x002a3e80, 31, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* cmp esi, 0x52 -> jge 0x17017f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x170192 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1701af */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1701bf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1701cf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1701df */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1701ef */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1701ff */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17020f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17021f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17022f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17023f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17024f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x170262 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x170275 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x170288 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17029b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1702ae */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1702c1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1702d4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1702e7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1702fa */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17030d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x170320 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x170333 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x170346 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x170359 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x17036c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x17037a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x170390 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1703a1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1703b2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1703c3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1703d0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1703f0 */
void FUN_001703f0(void)
{
  int eax = 0;
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)edx;
}

/* 0x170440 */
void FUN_00170440(void *params, short pass, short pass_count)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* test ebx, ebx -> jne 0x17046d */
  display_assert((char *)0x0029f510, (char *)0x002a3e80, 47, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x170493 */
  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 48, 0);
  system_exit(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* test eax, eax -> je 0x17051d */
  /* relift: cmp word ptr [ebp + 8], 0 -> jg 0x170519 */
  /* relift: cmp word ptr [ebp + 0xc], (int16_t)edx -> je 0x170519 */
  /* relift: cmp word ptr [ebx + 2], 0 -> je 0x17051d */
  /* test (char)eax, (char)eax -> je 0x170532 */
  /* test (char)eax, (char)eax -> je 0x170549 */
  /* relift: test byte ptr [edi + 0xe], 0x10 -> je 0x1705f1 */
  FUN_001700d0();
  /* relift: test byte ptr [ecx + 0xe], 0x10 -> je 0x170613 */
  FUN_001700d0();
  FUN_001700d0();
  FUN_001700d0();
  /* relift: cmp edi, dword ptr [ebx + 8] -> jne 0x1708c2 */
  /* cmp edx, esi -> jne 0x1708e3 */
  /* relift: cmp edx, dword ptr [ebx + 8] -> jne 0x170918 */
  /* test (char)eax, (char)eax -> je 0x170955 */
  display_assert((char *)0x002a3edc, (char *)0x002a3e80, 176, 0);
  system_exit(0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170980 */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 177, 0);
  system_exit(0);
  /* test ebx, ebx -> je 0x17098f */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* cmp (int16_t)eax, 2 -> jne 0x170bf6 */
  /* test (char)eax, (char)eax -> je 0x170a8d */
  display_assert((char *)0x002a3edc, (char *)0x002a3e80, 198, 0);
  system_exit(0);
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170ab8 */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 199, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* relift: cmp word ptr [ebp + 8], 1 -> jne 0x170c6e */
  /* test (char)eax, (char)eax -> je 0x170c6e */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x170c2f */
  display_assert((char *)0x002a3ec0, (char *)0x002a3e80, 223, 0);
  system_exit(0);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  random_math_get_local_seed_address();
  random_math_real((void *)(uintptr_t)eax);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x170c90 */
void FUN_00170c90(void *effect)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 251, 0);
  system_exit(0);
  FUN_0016f910(26);
  rasterizer_screen_effect_get_cinematic_parameters((void *)(uintptr_t)eax);
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0x170d1d */
  /* test eax, eax -> jne 0x170d1d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x170d1d */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x170d1d */
  /* test (char)eax, (char)eax -> je 0x171b94 */
  /* relift: relift: mov (char)eax, byte ptr [0x325700] */
  /* test (char)eax, (char)eax -> je 0x171b94 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x171b94 */
  /* test eax, eax -> jne 0x170d77 */
  display_assert((char *)0x002a4460, (char *)0x002a3e80, 276, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x170d9e */
  display_assert((char *)0x002a443c, (char *)0x002a3e80, 277, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi], 0 -> je 0x170dc4 */
  display_assert((char *)0x002a4404, (char *)0x002a3e80, 278, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 0 -> je 0x170deb */
  display_assert((char *)0x002a43d4, (char *)0x002a3e80, 279, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  display_assert((char *)0x002a439c, (char *)0x002a3e80, 280, 0);
  system_exit(0);
  /* test eax, eax -> je 0x170e42 */
  display_assert((char *)0x002a436c, (char *)0x002a3e80, 281, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 2], 1 -> jne 0x170e70 */
  /* test eax, eax -> je 0x170e70 */
  display_assert((char *)0x002a4340, (char *)0x002a3e80, 286, 0);
  system_exit(0);
  FUN_00178b40(38, 0, 0);
  /* relift: cmp word ptr [ebp - 0xc], 1 -> jne 0x170ec9 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x170ec1 */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 313, 0);
  system_exit(0);
  /* test (char)ecx, 1 -> jne 0x170ed7 */
  /* test (char)eax, (char)eax -> je 0x171065 */
  /* cmp (int16_t)ecx, 1 -> je 0x170f1e */
  display_assert((char *)0x002a4330, (char *)0x002a3e80, 334, 0);
  system_exit(0);
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)ecx);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: test byte ptr [edx + 0xe], 0x10 -> je 0x170ffd */
  display_assert((char *)0x002a42fc, (char *)0x002a3e80, 351, 0);
  system_exit(0);
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* relift: cmp word ptr [esi + 2], 0 -> jne 0x171133 */
  /* relift: cmp word ptr [ebp - 0xc], 1 -> jne 0x1710c6 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x1710aa */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 371, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x1711d4 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)ecx);
  /* test (int16_t)ecx, (int16_t)ecx -> jne 0x1710de */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x1711d4 */
  /* cmp (int16_t)ecx, 1 -> jne 0x171111 */
  /* test eax, eax -> je 0x1710cb */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171100 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* cmp (int16_t)edi, 1 -> jne 0x1711d4 */
  display_assert((char *)0x002a42b8, (char *)0x002a3e80, 398, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17114c */
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171158 */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x171158 */
  /* cmp (int16_t)edi, 1 -> jne 0x171165 */
  /* cmp (int16_t)edi, 2 -> jne 0x171172 */
  /* cmp (int16_t)edi, 3 -> jne 0x1711d4 */
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x171070 */
  D3DDevice_SetRenderState_CullMode(ebx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  D3DDevice_SetRenderState_ZEnable(ebx);
  D3DDevice_SetRenderState_ZBias(ebx);
  FUN_00170440((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)edi, -1 -> je 0x171258 */
  FUN_00158140(0, 0, ebx, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 0);
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x1712a9 */
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = 8 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* cmp (int16_t)eax, 1 -> jne 0x17143f */
  /* mem[0x005a5b98] = 0x421 */
  /* mem[0x005a5b94] = 4 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x17130a */
  FUN_00159070(0.0f);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ac0] = 0x3120111a */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x3120110a */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0xc091c19 */
  /* mem[0x005a5b78] = 0xc4 */
  /* mem[0x005a5b50] = 0x8080000 */
  /* mem[0x005a5b7c] = 0xd0 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jl 0x17137b */
  /* cmp (int16_t)eax, 3 -> jl 0x17139b */
  display_assert((char *)0x002a4230, (char *)0x002a3e80, 497, 0);
  system_exit(0);
  /* mem[0x005a5b54] = 0xd0d0820 */
  /* mem[0x005a5b80] = ecx */
  /* mem[0x005a5ae0] = 0x2c0d0800 */
  /* mem[0x005a5ae4] = 0x400 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  display_assert((char *)0x002a41f0, (char *)0x002a3e80, 513, 0);
  system_exit(0);
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  csmemset((void *)0x005a5ac0, 0, 0);
  /* relift: cmp word ptr [esi + 2], (int16_t)ebx -> jne 0x171592 */
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)ecx -> jne 0x1714ed */
  /* relift: cmp word ptr [ebp - 8], (int16_t)ebx -> je 0x1714c2 */
  display_assert((char *)0x002a4338, (char *)0x002a3e80, 529, ecx);
  system_exit(0);
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5ae4] = 0x800 */
  /* cmp (int16_t)eax, (int16_t)ebx -> jne 0x171516 */
  /* mem[0x005a5b98] = ecx */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* cmp (int16_t)eax, (int16_t)ecx -> jne 0x17156e */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b48] = 0x9200000 */
  /* mem[0x005a5ae4] = 0x800 */
  /* mem[0x005a5b48] = 0x8200000 */
  /* mem[0x005a5ae4] = ebx */
  display_assert((char *)0x002a42b8, (char *)0x002a3e80, 584, ecx);
  system_exit(0);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b48] = 0x89208a20 */
  /* mem[0x005a5b74] = esi */
  FUN_00159070(0.0f);
  /* mem[0x005a5aec] = eax */
  /* mem[0x005a5b4c] = 0xcc118b11 */
  /* mem[0x005a5b78] = esi */
  /* mem[0x005a5b50] = 0xcc20a020 */
  /* mem[0x005a5b7c] = esi */
  /* mem[0x005a5b54] = 0x3809180c */
  /* mem[0x005a5b80] = esi */
  /* mem[0x005a5ae4] = 0x800 */
  /* mem[0x005a5b48] = 0x88208920 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b4c] = 0x8a208b20 */
  /* mem[0x005a5b78] = 0x30d00 */
  /* mem[0x005a5b50] = 0xcc20cd20 */
  /* mem[0x005a5b7c] = eax */
  /* mem[0x005a5b54] = 0xcc20a020 */
  /* mem[0x005a5b80] = 0xc00 */
  /* mem[0x005a5ae4] = ebx */
  /* mem[0x005a5ae0] = 0xc */
  FUN_00159070(0.0f);
  FUN_00159070(0.0f);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x171746 */
  /* mem[0x005a5ae0] = 0x3c0c2d00 */
  /* mem[0x005a5ae4] = eax */
  /* cmp edx, ecx -> jne 0x171853 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x171853 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x1717b7 */
  FUN_00159070(0.0f);
  FUN_000d1dd0((float *)0);
  /* test (char)eax, (char)eax -> je 0x171821 */
  FUN_000d1dd0((float *)(uintptr_t)eax);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0x1d0f000c */
  /* mem[0x005a5ae4] = ecx */
  FUN_000d1dd0((float *)(uintptr_t)edx);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5ae0] = 0x1d0f0c00 */
  /* mem[0x005a5ae4] = eax */
  /* cmp (int16_t)edi, 8 -> jle 0x171879 */
  display_assert((char *)0x002a41bc, (char *)0x002a3e80, 705, 0);
  system_exit(0);
  /* mem[0x005a5b94] = ecx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: cmp word ptr [ebp - 0xc], (int16_t)esi -> jne 0x1718e5 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0 */
  SetRenderStateSmart(63, 771);
  SetRenderStateSmart(74, 32774);
  /* relift: cmp eax, dword ptr [ebp - 0x10] -> jne 0x17191a */
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 771);
  SetRenderStateSmart(63, 0);
  SetRenderStateSmart(74, 32774);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  main_get_window_count();
  /* cmp (int16_t)eax, 1 -> jle 0x1719dd */
  /* relift: cmp word ptr [ebp - 0xc], 1 -> je 0x1719dd */
  D3DDevice_Begin(0);
  /* test (char)eax, (char)eax -> je 0x171a0b */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171a2e */
  FUN_00167ff0(0, (char *)0x002a4168);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171a56 */
  FUN_00167ff0(0, (char *)0x002a4100);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171a7b */
  FUN_00167ff0(0, (char *)0x002a40a8);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171aa0 */
  FUN_00167ff0(0, (char *)0x002a4040);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171ac6 */
  FUN_00167ff0(0, (char *)0x002a3ff0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171aeb */
  FUN_00167ff0(0, (char *)0x002a3f88);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x171b0f */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x171b34 */
  FUN_00167ff0(0, (char *)0x002a3f20);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x171b54 */
  FUN_00167ff0(0, (char *)0x0029f728);
  /* relift: relift: mov (int16_t)ecx, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_0016fa40(26);
  error(0, (char *)0x002a3ef4);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x171bc0 */
void FUN_00171bc0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x171bef */
  display_assert((char *)0x0029dc40, (char *)0x002a3e80, 786, 0);
  system_exit(0);
  FUN_0016f910(28);
  /* relift: relift: mov (char)eax, byte ptr [0x3256ff] */
  /* test (char)eax, (char)eax -> je 0x1720d3 */
  /* relift: cmp word ptr [0x5a5df8], 0 -> je 0x1720d3 */
  /* relift: relift: fld dword ptr [0x5a5e00] */
  /* relift: relift: fld dword ptr [0x5a5e04] */
  /* relift: relift: fld dword ptr [0x5a5e08] */
  /* relift: relift: fld dword ptr [0x5a5e0c] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_000d1c90((float *)0);
  FUN_000d1c90((float *)(uintptr_t)ecx);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 1 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x303 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x800b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x8002 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8008 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x8002 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8007 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x307 */
  SetRenderStateSmart(63, 32770);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(75, 0);
  SetRenderStateSmart(62, 0);
  SetRenderStateSmart(63, 32770);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(75, 0);
  display_assert((char *)0x002a4488, (char *)0x002a3e80, 875, edx);
  system_exit(0);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae8] = esi */
  /* mem[0x005a5ac0] = ebx */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = edi */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* relift: relift: mov (int16_t)esi, word ptr [0x5a5bfa] */
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_End();
  FUN_0016fa40(28);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x172520 */
void FUN_00172520(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  FUN_0016f910(0);
  /* cmp edx, 0x16 -> jge 0x172540 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x172551 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x172562 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x172573 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x172580 */
  D3DDevice_SetTextureState_BumpEnv();
  /* test eax, eax -> jne 0x1725bc */
  display_assert((char *)0x0029dc40, (char *)0x002a44b0, 239, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x172621 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ca] */
  /* test (char)eax, (char)eax -> je 0x172621 */
  /* test esi, esi -> jne 0x1725f7 */
  display_assert((char *)0x0029f510, (char *)0x002a44b0, 245, 0);
  system_exit(0);
  rasterizer_set_model_skinning((void *)(uintptr_t)eax);
  /* mem[0x0047e4b0] = esi */
  /* relift: relift: mov byte ptr [0x47e4b5], 1 */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x172640 */
void FUN_00172640(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x172650 */
void FUN_00172650(void)
{
  int eax = 0;
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)edx;
}

/* 0x1726a0 */
void FUN_001726a0(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1726c9 */
  display_assert((char *)0x0029dc40, (char *)0x002a44b0, 563, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x17271d */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ca] */
  /* test (char)eax, (char)eax -> je 0x17271d */
  /* relift: relift: mov (char)eax, byte ptr [0x47e4b5] */
  /* test (char)eax, (char)eax -> jne 0x1726f4 */
  error(0, (char *)0x002a44ec);
  /* relift: relift: mov (char)eax, byte ptr [0x3251fc] */
  /* test (char)eax, (char)eax -> jne 0x17271d */
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);
  /* relift: relift: mov byte ptr [0x3251fc], 1 */

  (void)eax;
}

/* 0x172720 */
void rasterizer_window_get_fog(void)
{
  FUN_0016fa40(0);
}

/* 0x172730 */
void FUN_00172730(void)
{
  int eax = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x17275f */
  display_assert((char *)0x0029dc40, (char *)0x002a44b0, 31, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256ca] */
  /* test (char)eax, (char)eax -> je 0x172a1f */
  /* relift: relift: mov (char)eax, byte ptr [0x3256f6] */
  /* test (char)eax, (char)eax -> je 0x172a1f */
  FUN_001584f0(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x172780 */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(38, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ac0] = 0x8a009a0 */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0xaa00ba0 */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5ae0] = 0xc20001c */
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

  (void)eax;
  (void)edi;
}

/* 0x172de0 */
void FUN_00172de0(void *decal, int param_2, void *param_3, void *param_4)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x172e0f */
  display_assert((char *)0x0029dc40, (char *)0x002a44b0, 274, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x173087 */
  /* relift: relift: mov (char)eax, byte ptr [0x3256ca] */
  /* test (char)eax, (char)eax -> je 0x173087 */
  display_assert((char *)0x002a18b8, (char *)0x002a44b0, 280, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x24], 4 -> jne 0x173084 */
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  display_assert((char *)0x002a19cc, (char *)0x002a44b0, 286, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x172eba */
  display_assert((char *)0x002a2c90, (char *)0x002a44b0, 287, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x172ee3 */
  display_assert((char *)0x002a33b8, (char *)0x002a44b0, 288, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x172eed */
  D3DDevice_SetRenderState_CullMode(2305);
  FUN_00178b40(39, 0, 0);
  /* test (char)eax, 4 -> je 0x172f19 */
  D3DDevice_SetRenderState_PSTextureModes();
  D3DDevice_SetRenderState_PSTextureModes();
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  FUN_00190e10((void *)(uintptr_t)esi, (void *)(uintptr_t)eax, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, (float *)0, (float *)0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  FUN_0015e430();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x173084 */
  /* mem[0x005a5500] = edx */
  /* mem[0x005a54fc] = ecx */
  FUN_0017ed90();
  /* mem[0x005a54f8] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x173090 */
void FUN_00173090(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp eax, ebx -> jne 0x1730c2 */
  display_assert((char *)0x0029dc40, (char *)0x002a44b0, 404, 0);
  system_exit(0);
  /* relift: cmp word ptr [0x5a5bc0], (int16_t)ebx -> jne 0x17363d */
  /* relift: cmp byte ptr [0x3256ca], (char)ebx -> je 0x17363d */
  /* relift: cmp byte ptr [0x3256f6], (char)ebx -> je 0x1730f9 */
  FUN_00172730();
  /* relift: relift: mov (char)ecx, byte ptr [0x3256f6] */
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
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = ebx */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = 0x301 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb78c] = ebx */
  D3DDevice_SetRenderState_ZEnable(edi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x202 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = ebx */
  D3DDevice_SetRenderState_ZBias(ebx);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x21 */
  /* mem[0x005a5b94] = 4 */
  FUN_000d1dd0((void *)0x0047e46c);
  /* mem[0x005a5ae8] = eax */
  /* relift: relift: mov (char)eax, byte ptr [0x3256f7] */
  /* mem[0x005a5b08] = 0xffffff */
  /* mem[0x005a5b48] = 0x14200000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5b4c] = 0x290c0821 */
  /* mem[0x005a5b78] = 0xcd */
  /* mem[0x005a5b50] = 0x2c200c2d */
  /* mem[0x005a5b7c] = 0xc00 */
  /* mem[0x005a5b54] = 0x2c020000 */
  /* mem[0x005a5b80] = 0x20d0 */
  /* mem[0x005a5ae0] = 0x2c */
  /* mem[0x005a5ae4] = 0xd00 */
  /* mem[0x005a5ae0] = 0xc */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = ebx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)edx);
  FUN_00178b40(29, 0, 0);
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* relift: relift: fld dword ptr [0x47e478] */
  /* relift: relift: fld dword ptr [0x47e478] */
  /* relift: relift: fld dword ptr [0x47e480] */
  /* relift: relift: fld dword ptr [0x47e484] */
  /* relift: relift: fld dword ptr [0x47e488] */
  /* relift: relift: fld dword ptr [0x47e4a4] */
  /* relift: relift: fld dword ptr [0x47e4ac] */
  /* relift: relift: fld dword ptr [0x47e4a8] */
  /* relift: relift: fld dword ptr [0x47e48c] */
  /* relift: relift: fld dword ptr [0x47e490] */
  /* relift: relift: fld dword ptr [0x47e494] */
  /* relift: relift: fld dword ptr [0x47e4a4] */
  /* relift: relift: fld dword ptr [0x47e4ac] */
  /* relift: relift: fld dword ptr [0x47e4a8] */
  /* relift: relift: fld dword ptr [0x47e498] */
  /* relift: relift: fld dword ptr [0x47e49c] */
  /* relift: relift: fld dword ptr [0x47e4a0] */
  /* relift: relift: fld dword ptr [0x47e4a4] */
  /* relift: relift: fld dword ptr [0x47e4ac] */
  /* relift: relift: fld dword ptr [0x47e4a8] */
  /* relift: relift: fld dword ptr [0x47e498] */
  /* relift: relift: fld dword ptr [0x47e49c] */
  /* relift: relift: fld dword ptr [0x47e4a0] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  /* relift: cmp byte ptr [0x3251fc], (char)ebx -> jne 0x1735dc */
  /* relift: relift: mov (int16_t)edx, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, ebx, 0, 0);
  /* relift: relift: mov byte ptr [0x3251fc], 1 */
  /* relift: relift: mov byte ptr [0x47e4b4], 1 */
  FUN_00158ae0(0);
  FUN_0015dc10();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x17363b */
  /* mem[0x005a543c] = eax */
  /* mem[0x005a5438] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5434] = ecx */
  /* cmp esi, 0x52 -> jge 0x17366b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x173679 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17368e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x17369a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1736a6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1736b2 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1736be */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1736ca */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1736d6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x1736e2 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1736ee */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1736fa */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x173706 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x173715 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x173724 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x173733 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x173742 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x173751 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x173760 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x17376f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x17377e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17378d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17379c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1737ab */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1737ba */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1737c9 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1737d8 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x1737e7 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1737f5 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17380c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x173819 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x173826 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x173833 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x173840 */
  D3DDevice_SetTextureState_BumpEnv();
  /* cmp esi, 0x52 -> jge 0x17386f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x173882 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17389f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1738af */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1738bf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1738cf */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x1738df */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x1738ef */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x1738ff */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17390f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17391f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17392f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17393f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x173952 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x173965 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x173978 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17398b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x17399e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1739b1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1739c4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1739d7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1739ea */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1739fd */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x173a10 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x173a23 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x173a36 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x173a49 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x173a5c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x173a6a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x173a80 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x173a91 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x173aa2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x173ab3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x173ac0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x173ae0 */
void FUN_00173ae0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x173af0 */
void FUN_00173af0(void)
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

/* 0x173b40 */
void FUN_00173b40(float *params)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test eax, eax -> jne 0x173b6f */
  display_assert((char *)0x0029dc40, (char *)0x002a45f8, 13, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256da] */
  /* test (char)eax, (char)eax -> je 0x1741c4 */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x1741c4 */
  display_assert((char *)0x0029f510, (char *)0x002a45f8, 18, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x173bd4 */
  display_assert((char *)0x002a18a4, (char *)0x002a45f8, 20, 0);
  system_exit(0);
  /* test eax, eax -> je 0x173bff */
  /* test eax, eax -> jne 0x173c06 */
  display_assert((char *)0x002a1878, (char *)0x002a45f8, 22, 0);
  system_exit(0);
  /* test eax, eax -> je 0x173c28 */
  /* relift: cmp dword ptr [esi], 0 -> je 0x173c28 */
  display_assert((char *)0x002a1840, (char *)0x002a45f8, 24, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 1 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_001580b0(0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* test edx, edx -> je 0x173cb9 */
  /* test edx, edx -> je 0x173cdb */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  /* test eax, eax -> je 0x173e63 */
  /* test eax, eax -> je 0x173e7c */
  /* test eax, eax -> je 0x173e97 */
  /* test eax, eax -> je 0x173ead */
  /* test eax, eax -> je 0x173ec2 */
  /* test eax, eax -> je 0x173ed5 */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x173fdd */
  rasterizer_set_texture_bitmap_data(0, (void *)(uintptr_t)eax);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  D3DDevice_SetTextureStageState(ecx, 0, 0);
  D3DDevice_SetTextureStageState(edx, 0, 0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp (int16_t)ebx, 3 -> jl 0x173f30 */
  FUN_00178b40(0, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = ecx */
  /* test ecx, ecx -> jne 0x174048 */
  /* test ecx, ecx -> jne 0x174062 */
  /* test eax, eax -> je 0x1740b0 */
  /* test eax, eax -> je 0x1740c8 */
  FUN_000d1c90((float *)(uintptr_t)eax);
  /* mem[0x005a5ae8] = eax */
  FUN_000d1c90((float *)(uintptr_t)ecx);
  /* mem[0x005a5b08] = eax */
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* mem[0x005a5aec] = eax */
  FUN_000d1c90((float *)(uintptr_t)esi);
  /* mem[0x005a5af8] = eax */
  FUN_000d1c90((float *)(uintptr_t)esi);
  /* mem[0x005a5afc] = eax */
  FUN_000d1c90((float *)(uintptr_t)esi);
  /* mem[0x005a5b00] = eax */
  FUN_000d1c90((float *)(uintptr_t)esi);
  /* mem[0x005a5b04] = eax */
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b28] = eax */
  /* mem[0x005a5b48] = 0x8010902 */
  /* mem[0x005a5ac0] = 0x18111912 */
  /* mem[0x005a5b4c] = 0xa010804 */
  /* mem[0x005a5b78] = eax */
  /* mem[0x005a5ac4] = 0x1a111814 */
  /* mem[0x005a5b2c] = eax */
  /* mem[0x005a5b94] = 0x11102 */
  /* mem[0x005a5ae0] = 0xc */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_CullMode(2305);
  FUN_00178b40(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x1741d0 */
void FUN_001741d0(float *quad)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x1741fc */
  display_assert((char *)0x0029dc40, (char *)0x002a45f8, 216, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256da] */
  /* test (char)eax, (char)eax -> je 0x1742df */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x1742df */
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, eax);
  /* test (char)ebx, (char)ebx -> je 0x174243 */
  FUN_00167ff0(0, (char *)0x002a4768);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x17426d */
  FUN_00167ff0(0, (char *)0x002a46e8);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x17429d */
  FUN_00167ff0(0, (char *)0x002a4660);
  D3DDevice_End();
  FUN_00167ff0(0, (char *)0x0029f728);
  error(0, (char *)0x002a4630);
  /* cmp esi, 0x52 -> jge 0x17430b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x174319 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17432e */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x17433a */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x174346 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x174352 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17435e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17436a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x174376 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x174382 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17438e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17439a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1743a6 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1743b5 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1743c4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1743d3 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1743e2 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1743f1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x174400 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x17440f */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x17441e */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17442d */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17443c */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x17444b */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17445a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x174469 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x174478 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x174487 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x174495 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x1744ac */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1744b9 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1744c6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1744d3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x1744e0 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1744f0 */
void FUN_001744f0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_CreateVertexBuffer(ecx, eax, edx, ecx, (void *)(uintptr_t)eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x174510 */
void FUN_00174510(void *group, int a2)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x174538 */
  display_assert((char *)0x0026276c, (char *)0x002a4800, 109, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17459d */
  /* test (char)eax, (char)eax -> je 0x174563 */
  display_assert((char *)0x002a47f0, (char *)0x002a4800, 113, 0);
  system_exit(0);
  /* test eax, eax -> je 0x174582 */
  FUN_0015e430();
  FUN_0015e0f0();
  /* test eax, eax -> je 0x1745dc */
  FUN_0015de60();
  FUN_0015dc10();
  /* test (char)eax, (char)eax -> je 0x174603 */
  display_assert((char *)0x002a47f0, (char *)0x002a4800, 156, 0);
  system_exit(0);
  /* test eax, eax -> jl 0x174622 */
  FUN_0015d8b0();
  /* cmp (int16_t)edi, 3 -> je 0x17466a */
  /* cmp (int16_t)edi, 4 -> je 0x17466a */
  display_assert((char *)0x002a47c0, (char *)0x002a4800, 180, ebx);
  system_exit(0);
  rasterizer_draw_dynamic_vertices(0, 0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x1746af */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1746c2 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1746df */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1746ef */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1746ff */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x17470f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17471f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17472f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17473f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17474f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17475f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17476f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17477f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x174792 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1747a5 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1747b8 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x1747cb */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1747de */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1747f1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x174804 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x174817 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17482a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17483d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x174850 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x174863 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x174876 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x174889 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x17489c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1748aa */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x1748c0 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1748d1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x1748e2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1748f3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x174900 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetStreamSource(edx, (void *)(uintptr_t)ecx, eax);
  D3DDevice_BeginVisibilityTest();
  D3DDevice_EndVisibilityTest();
  D3DDevice_GetVisibilityTestResult();
  D3DResource_Release((void *)(uintptr_t)eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x174980 */
void FUN_00174980(void)
{
  D3DVertexBuffer_Lock();
}

/* 0x1749b0 */
void FUN_001749b0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* test (char)eax, (char)eax -> je 0x174b55 */
  /* test (char)eax, (char)eax -> je 0x174b55 */
  /* mem[0x0047e4c4] = 0 */
  D3DDevice_EndVisibilityTest();
  /* test eax, eax -> jl 0x1749fc */
  FUN_00167ff0(0, (char *)0x002a4894);
  D3DDevice_GetVisibilityTestResult();
  /* cmp eax, 0x88760828 -> je 0x174a10 */
  /* test (char)ebx, (char)ebx -> je 0x174a35 */
  /* test eax, eax -> jl 0x174a35 */
  FUN_00167ff0(0, (char *)0x002a4890);
  /* mem[0x0047e4c4] = eax */
  main_get_window_count();
  /* cmp ecx, eax -> jne 0x174b41 */
  /* cmp esi, -1 -> je 0x174b40 */
  /* relift: relift: mov (int16_t)edx, word ptr [0x5a5bfa] */
  crt_sprintf((char *)(uintptr_t)ecx, (char *)0x002a4888);
  draw_string_set_style_justify_flags(0, 0, 0);
  draw_string_set_color((void *)(uintptr_t)ecx);
  FUN_0019B7E0();
  FUN_00158ae0(0);
  rasterizer_text_draw((void *)(uintptr_t)eax, (void *)0, (void *)0, 0, (char *)(uintptr_t)edx);
  error(0, (char *)0x002a4848);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x174b60 */
void FUN_00174b60(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x174b90 */
void FUN_00174b90(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x174bd0 */
int FUN_00174bd0(void)
{
  int eax = 0;
  int ebx = 0;
  int edx = 0;
  int esi = 0;
  int ebp = 0;

  D3DDevice_CreateVertexBuffer(16384, 0, esi, 0, (void *)0x0047e4bc);
  /* cmp eax, esi -> jl 0x174bf9 */
  FUN_00167ff0(0, (char *)0x002a49c8);
  /* relift: relift: mov word ptr [0x325652], 2 */
  D3DVertexBuffer_Lock();
  /* test (char)ebx, (char)ebx -> je 0x174c31 */
  FUN_00167ff0(0, (char *)0x002a4908);
  /* relift: relift: mov word ptr [0x325652], (int16_t)esi */
  /* relift: cmp dword ptr [ebp - 4], esi -> je 0x174c9a */
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0);
  error(0, (char *)0x002a48d4);
  return 0;

  (void)eax;
  (void)ebx;
  (void)edx;
  (void)esi;
  (void)ebp;
}

/* 0x174cc0 */
void FUN_00174cc0(void)
{
  int eax = 0;

  /* test eax, eax -> je 0x174cd9 */
  D3DResource_Release((void *)(uintptr_t)eax);
  /* mem[0x0047e4bc] = 0 */

  (void)eax;
}

/* 0x174ce0 */
void FUN_00174ce0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x178820 */
void FUN_00178820(void)
{
  D3DDevice_CreateVertexShader();
  D3DDevice_DeleteVertexShader();
}

/* 0x178850 */
void FUN_00178850(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;

  /* mem[0x00325240] = eax */
  /* mem[0x00325230] = eax */
  /* mem[0x00325460] = eax */
  /* mem[0x00325610] = eax */
  /* mem[0x00325220] = eax */
  /* mem[0x003252c0] = eax */
  /* mem[0x00325580] = eax */
  /* mem[0x00325410] = esi */
  /* mem[0x003252b0] = esi */
  /* mem[0x00325200] = 0x2ada64 */
  /* mem[0x00325210] = 0x2ada74 */
  /* mem[0x00325620] = 0x2adaac */
  /* mem[0x00325300] = edx */
  /* mem[0x00325510] = eax */
  /* mem[0x003253d0] = eax */
  /* mem[0x00325480] = eax */
  /* mem[0x00325350] = eax */
  /* mem[0x00325490] = eax */
  /* mem[0x003255b0] = edx */
  /* mem[0x003255a0] = edx */
  /* mem[0x003253a0] = eax */
  /* mem[0x003254a0] = eax */
  /* mem[0x003254c0] = edx */
  /* mem[0x00325530] = eax */
  /* mem[0x00325260] = eax */
  /* mem[0x00325280] = eax */
  /* mem[0x003252a0] = ecx */
  /* mem[0x00325290] = ecx */
  /* mem[0x003253b0] = ecx */
  /* mem[0x00325310] = ecx */
  /* mem[0x00325600] = ecx */
  /* mem[0x00325470] = ecx */
  /* mem[0x003252d0] = ecx */
  /* mem[0x00325250] = ecx */
  /* mem[0x00325380] = eax */
  /* mem[0x00325500] = eax */
  /* mem[0x00325420] = eax */
  /* mem[0x00325330] = eax */
  /* mem[0x00325430] = eax */
  /* mem[0x003254f0] = ecx */
  /* mem[0x003253f0] = ecx */
  /* mem[0x003255c0] = ecx */
  /* mem[0x00325590] = ecx */
  /* mem[0x003254d0] = ecx */
  /* mem[0x003255e0] = ecx */
  /* mem[0x003254e0] = eax */
  /* mem[0x003253c0] = eax */
  /* mem[0x003254b0] = eax */
  /* mem[0x003255d0] = eax */
  /* mem[0x00325390] = edx */
  /* mem[0x003253e0] = ecx */
  /* mem[0x003255f0] = ecx */
  /* mem[0x00325440] = ecx */
  /* mem[0x00325520] = ecx */
  /* mem[0x00325340] = eax */
  /* mem[0x00325370] = eax */
  /* mem[0x00325320] = ecx */
  /* mem[0x003252e0] = ecx */
  /* mem[0x00325360] = eax */
  /* mem[0x00325400] = ecx */
  /* mem[0x003252f0] = ecx */
  /* mem[0x00325450] = eax */
  /* mem[0x00325270] = eax */
  /* mem[0x00325560] = eax */
  /* mem[0x00325570] = eax */
  /* mem[0x00325550] = eax */
  /* mem[0x00325540] = eax */
  /* relift: cmp dword ptr [esi], 0 -> jne 0x178a36 */
  display_assert((char *)0x002adc9c, (char *)0x002adcd8, 242, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x178a5d */
  display_assert((char *)0x002adc6c, (char *)0x002adcd8, 243, 0);
  system_exit(0);
  D3DDevice_CreateVertexShader();
  /* test (char)ebx, (char)ebx -> je 0x178a7b */
  /* test eax, eax -> jl 0x178a7b */
  FUN_00167ff0(0, (char *)0x002adb80);
  error(0, (char *)0x002adb44);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
}

/* 0x178ab0 */
void FUN_00178ab0(void)
{
  int eax = 0;
  int ebx = 0;

  D3DDevice_DeleteVertexShader();
  /* test (char)ebx, (char)ebx -> je 0x178ad0 */
  FUN_00167ff0(0, (char *)0x002add58);
  error(0, (char *)0x002add24);
  D3DDevice_SetVertexShader(eax);
  D3DDevice_LoadVertexShader();
  D3DDevice_SelectVertexShader();
  D3DDevice_GetVertexShaderSize();

  (void)eax;
  (void)ebx;
}

/* 0x178b40 */
void FUN_00178b40(int a1, int a2, int a3)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* cmp (int16_t)ebx, 0x43 -> jl 0x178b80 */
  display_assert((char *)0x002ae5e0, (char *)0x002ae628, 135, 0);
  system_exit(0);
  /* cmp eax, 0x41 -> ja 0x178cd9 */
  display_assert((char *)0x002ae5b8, (char *)0x002ae628, 876, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x178d08 */
  /* cmp (int16_t)eax, 0xc -> jl 0x178d28 */
  display_assert((char *)0x002a52e0, (char *)0x002ae628, 879, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x178d36 */
  /* cmp (int16_t)ebx, (int16_t)edi -> jl 0x178d56 */
  display_assert((char *)0x002ae57c, (char *)0x002ae628, 880, 0);
  system_exit(0);
  display_assert((char *)0x002ae530, (char *)0x002ae628, 881, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x178e2f */
  D3DDevice_GetVertexShaderSize();
  /* test (char)eax, (char)eax -> je 0x178de4 */
  FUN_00167ff0(0, (char *)0x002ae498);
  /* cmp esi, 0x88 -> jle 0x178e2c */
  display_assert((char *)0x002ae45c, (char *)0x002ae628, 930, 0);
  system_exit(0);
  /* relift: cmp (int16_t)esi, word ptr [ecx*8 + 0x325634] -> je 0x178e8d */
  /* cmp (int16_t)eax, 3 -> jl 0x178e31 */
  /* test esi, esi -> jne 0x178e75 */
  display_assert((char *)0x002ae434, (char *)0x002ae628, 969, 0);
  system_exit(0);
  D3DDevice_SetVertexShader(esi);
  /* test (char)eax, (char)eax -> je 0x178f68 */
  /* cmp (int16_t)eax, 3 -> jge 0x178e45 */
  /* test (char)eax, (char)eax -> je 0x178ed5 */
  D3DDevice_SelectVertexShader();
  /* test (char)eax, (char)eax -> je 0x178ebf */
  FUN_00167ff0(0, (char *)0x002ae3e8);
  /* test edi, edi -> jne 0x178f0f */
  display_assert((char *)0x002ae434, (char *)0x002ae628, 956, 0);
  system_exit(0);
  D3DDevice_LoadVertexShader();
  /* test (char)eax, (char)eax -> je 0x178f23 */
  FUN_00167ff0(0, (char *)0x002ae390);
  D3DDevice_SelectVertexShader();
  /* test (char)eax, (char)eax -> je 0x178f4e */
  FUN_00167ff0(0, (char *)0x002ae338);
  FUN_00167ff0(0, (char *)0x002ae2f0);
  /* relift: cmp word ptr [0x3256ba], 0 -> je 0x178fb1 */
  /* mem[0x005a5558] = ecx */
  /* relift: relift: mov word ptr [0x325630], (int16_t)ecx */
  error(0, (char *)0x0029dffc);
  /* cmp esi, 0x52 -> jge 0x1790bb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x1790c9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x1790de */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x1790ea */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x1790f6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x179102 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17910e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17911a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x179126 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x179132 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17913e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17914a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x179156 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x179165 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x179174 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x179183 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x179192 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x1791a1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x1791b0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x1791bf */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x1791ce */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x1791dd */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x1791ec */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1791fb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17920a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x179219 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x179228 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x179237 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x179245 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17925c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x179269 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x179276 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x179283 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x179290 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x1792a0 */
void FUN_001792a0(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1792c0 */
void FUN_001792C0(int param_1)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x1792d0 */
void FUN_001792d0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x47e4c9] */
  /* cmp esi, 0x52 -> jge 0x1792ff */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x179312 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17932f */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x17933f */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x17934f */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x17935f */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17936f */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17937f */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17938f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17939f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1793af */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1793bf */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1793cf */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x1793e2 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x1793f5 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x179408 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17941b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x17942e */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x179441 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x179454 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x179467 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17947a */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17948d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x1794a0 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x1794b3 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x1794c6 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x1794d9 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x1794ec */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x1794fa */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x179510 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x179521 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x179532 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x179543 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x179550 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x179570 */
void FUN_00179570(void)
{
  int eax = 0;
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
  (void)edx;
}

/* 0x1795c0 */
void FUN_001795c0(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x1795ee */
  display_assert((char *)0x002a18b8, (char *)0x002ae750, 47, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x179614 */
  display_assert((char *)0x0029dc40, (char *)0x002ae750, 48, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d6] */
  /* test (char)eax, (char)eax -> je 0x179dd5 */
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 0);
  csmemset((void *)(uintptr_t)ebx, 0, 0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* cmp esi, ecx -> jge 0x17972d */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp (int16_t)edi, 4 -> jl 0x179710 */
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = esi */
  D3DDevice_SetRenderState_ZEnable(esi);
  D3DDevice_SetRenderState_ZBias(esi);
  FUN_00178b40(38, 0, 0);
  display_assert((char *)0x002ae72c, (char *)0x002ae750, 124, 0);
  system_exit(0);
  /* relift: relift: fld dword ptr [0x5a5e18] */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)eax, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b74] = eax */
  /* mem[0x005a5b80] = eax */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* mem[0x005a5b98] = 0x8421 */
  /* mem[0x005a5b94] = 0x11004 */
  /* mem[0x005a5b48] = 0x31481149 */
  /* mem[0x005a5b4c] = 0x314a114b */
  /* mem[0x005a5b78] = 0xd00 */
  /* mem[0x005a5b50] = 0x31cc11cd */
  /* mem[0x005a5b7c] = 0x30c00 */
  /* mem[0x005a5b54] = 0xcc20a020 */
  /* mem[0x005a5ae0] = 0x310c0100 */
  /* mem[0x005a5ae4] = esi */
  display_assert((char *)0x002ae6e8, (char *)0x002ae750, 159, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> je 0x17998d */
  display_assert((char *)0x002ae6a0, (char *)0x002ae750, 160, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x1799c9 */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, 0);
  system_exit(0);
  /* mem[0x005a5ae8] = ecx */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x179a3a */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, 0);
  system_exit(0);
  /* mem[0x005a5aec] = edx */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x179abf */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, 0);
  system_exit(0);
  /* mem[0x005a5af0] = eax */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00158ae0(0);
  /* cmp (int16_t)eax, 1 -> jle 0x179bab */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x179b6d */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x00269fe0, (char *)0x00269ffc, 291, 0);
  system_exit(0);
  /* mem[0x005a5b6c] = eax */
  /* mem[0x005a5b6c] = 0x7f7fff */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00158140(0, 0, 0, 0, 0);
  D3DDevice_Begin(0);
  /* test (char)ebx, (char)ebx -> je 0x179c04 */
  FUN_00167ff0(0, (char *)0x002a3004);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x179c28 */
  FUN_00167ff0(0, (char *)0x002a2fc4);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x179c6e */
  FUN_00167ff0(0, (char *)0x002a2f48);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x179c92 */
  FUN_00167ff0(0, (char *)0x002a2f04);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x179cc6 */
  FUN_00167ff0(0, (char *)0x002a2e88);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x179cea */
  FUN_00167ff0(0, (char *)0x002a2e44);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x179d0f */
  FUN_00167ff0(0, (char *)0x002a2dc8);
  D3DDevice_SetVertexData2s(0, 0, 0);
  /* test (char)ebx, (char)ebx -> je 0x179d33 */
  FUN_00167ff0(0, (char *)0x002a2d84);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  /* test (char)ebx, (char)ebx -> je 0x179d58 */
  FUN_00167ff0(0, (char *)0x002a2d08);
  D3DDevice_End();
  /* test (char)ebx, (char)ebx -> je 0x179d76 */
  FUN_00167ff0(0, (char *)0x0029f728);
  /* relift: relift: mov (int16_t)edx, word ptr [0x5a5bc0] */
  FUN_00158140(0, 0, 0, 0, 0);
  FUN_00158ae0(0);
  error(0, (char *)0x002ae670);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x179de0 */
void FUN_00179de0(void *group)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x179e0e */
  display_assert((char *)0x0026276c, (char *)0x002ae750, 238, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x179e37 */
  display_assert((char *)0x0029dc40, (char *)0x002ae750, 239, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d6] */
  /* test (char)eax, (char)eax -> je 0x17a69b */
  FUN_001906b0((void *)(uintptr_t)eax, 0);
  shader_get_vertex_shader_permutation((void *)(uintptr_t)ecx);
  FUN_00184610((void *)(uintptr_t)edi);
  /* relift: test byte ptr [edi], 0x12 -> jne 0x179f39 */
  D3DDevice_SetRenderState_CullMode(esi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = esi */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = 1 */
  FUN_00178b40(20, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = 1 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)edi, 0);
  /* relift: test byte ptr [edi], 0x10 -> jne 0x179f47 */
  /* relift: relift: mov (char)eax, byte ptr [0x47e4c8] */
  /* test (char)eax, (char)eax -> je 0x179f67 */
  FUN_001795c0();
  /* relift: relift: mov byte ptr [0x47e4c8], 0 */
  /* relift: test byte ptr [esi + 0x28], 1 -> je 0x17a16f */
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
  D3DDevice_SetRenderState_CullMode(0);
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
  /* mem[0x001fb798] = edx */
  FUN_00178b40(20, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x61 */
  /* mem[0x005a5b94] = 2 */
  FUN_00159070(0.0f);
  /* mem[0x005a5ae8] = eax */
  FUN_00159070(0.0f);
  /* mem[0x005a5b08] = eax */
  /* mem[0x005a5ac0] = 0x29120911 */
  /* mem[0x005a5b28] = 0xc00 */
  /* mem[0x005a5ac4] = 0x1c180000 */
  /* mem[0x005a5b2c] = 0xc0 */
  /* mem[0x005a5ae0] = 0 */
  /* mem[0x005a5ae4] = 0x1c00 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)edi, 0);
  /* relift: test byte ptr [esi + 0x28], 2 -> je 0x17a29f */
  rasterizer_set_texture(0, 0, 0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetRenderState_CullMode(0);
  SetRenderStateSmart(67, 0x00010101);
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 0);
  SetRenderStateSmart(63, 768);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  SetRenderStateSmart(57, 515);
  SetRenderStateSmart(64, 0);
  FUN_00178b40(20, 0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = eax */
  /* mem[0x005a5b94] = eax */
  /* mem[0x005a5ae0] = ecx */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  FUN_00174510((void *)(uintptr_t)edi, 0);
  /* cmp (int16_t)eax, 4 -> jle 0x17a2b3 */
  FUN_001584f0(0, 0, 0);
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
  D3DDevice_SetRenderState_CullMode(0);
  SetRenderStateSmart(67, 0x00010101);
  SetRenderStateSmart(59, 0);
  SetRenderStateSmart(62, 0);
  SetRenderStateSmart(63, 0);
  SetRenderStateSmart(74, 32774);
  SetRenderStateSmart(60, 0);
  SetRenderStateSmart(123, 0);
  SetRenderStateSmart(57, 515);
  SetRenderStateSmart(64, 0);
  FUN_00178b40(23, 0, 0);
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0x64621 */
  /* mem[0x005a5b9c] = 0x111 */
  /* mem[0x005a5b74] = 0xcd */
  /* mem[0x005a5b48] = 0xb0b0120 */
  /* mem[0x005a5b4c] = eax */
  /* mem[0x005a5b94] = 4 */
  /* mem[0x005a5b78] = ecx */
  /* mem[0x005a5b50] = eax */
  /* mem[0x005a5b7c] = ecx */
  /* mem[0x005a5b54] = 0x2d0c0d0b */
  /* mem[0x005a5b80] = 0xc00 */
  /* mem[0x005a5ae0] = 0x330c0000 */
  /* mem[0x005a5b94] = 2 */
  /* mem[0x005a5b78] = 0xc0 */
  /* mem[0x005a5ae0] = 0x2d0f0b00 */
  /* mem[0x005a5ae4] = eax */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17a64e */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x17a5ef */
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_00013070((void *)0x005a5bd4, (float *)(uintptr_t)ecx);
  /* relift: relift: fld dword ptr [0x2533c8] */
  FUN_000d1dd0((float *)0);
  /* mem[0x005a5ae8] = eax */
  /* mem[0x005a5ae8] = 0xffffff */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetTextureStageState(eax, 0, 0);
  FUN_00174510((void *)(uintptr_t)edi, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  /* cmp esi, 0x52 -> jge 0x17a6bb */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x17a6c9 */
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17a6de */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x17a6ea */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x17a6f6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x17a702 */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17a70e */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17a71a */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17a726 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17a732 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17a73e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17a74a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17a756 */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x17a765 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x17a774 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x17a783 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17a792 */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x17a7a1 */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x17a7b0 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x17a7bf */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x17a7ce */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17a7dd */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17a7ec */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x17a7fb */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17a80a */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x17a819 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x17a828 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x17a837 */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x17a845 */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17a85c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x17a869 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x17a876 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x17a883 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x17a890 */
  D3DDevice_SetTextureState_BumpEnv();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17a8a0 */
void FUN_0017a8a0(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17aa54 */
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
  /* test (char)eax, 0x41 -> jne 0x17aa4c */
  /* relift: relift: fld dword ptr [0x5a5d8c] */
  /* relift: relift: fld dword ptr [0x5a5d7c] */
  /* relift: relift: fld dword ptr [0x5a5d6c] */
  /* relift: relift: fld dword ptr [0x5a5d80] */
  /* relift: relift: fld dword ptr [0x5a5d70] */
  /* relift: relift: fld dword ptr [0x5a5d60] */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> je 0x17aa1e */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* cmp esi, 0x52 -> jge 0x17aa7f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x17aa92 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  D3DDevice_SetRenderState_PSTextureModes();
  /* cmp esi, 0x75 -> jne 0x17aaaf */
  D3DDevice_SetRenderState_VertexBlend();
  /* cmp esi, 0x76 -> jne 0x17aabf */
  D3DDevice_SetRenderState_FogColor();
  /* cmp esi, 0x77 -> jne 0x17aacf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x17aadf */
  D3DDevice_SetRenderState_BackFillMode();
  /* cmp esi, 0x79 -> jne 0x17aaef */
  D3DDevice_SetRenderState_TwoSidedLighting();
  /* cmp esi, 0x7a -> jne 0x17aaff */
  D3DDevice_SetRenderState_NormalizeNormals();
  /* cmp esi, 0x7b -> jne 0x17ab0f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17ab1f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17ab2f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17ab3f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17ab4f */
  D3DDevice_SetRenderState_FrontFace();
  /* cmp esi, 0x80 -> jne 0x17ab62 */
  D3DDevice_SetRenderState_TextureFactor();
  /* cmp esi, 0x81 -> jne 0x17ab75 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x17ab88 */
  D3DDevice_SetRenderState_LogicOp();
  /* cmp esi, 0x83 -> jne 0x17ab9b */
  D3DDevice_SetRenderState_EdgeAntiAlias();
  /* cmp esi, 0x84 -> jne 0x17abae */
  D3DDevice_SetRenderState_MultiSampleAntiAlias();
  /* cmp esi, 0x85 -> jne 0x17abc1 */
  D3DDevice_SetRenderState_MultiSampleMask();
  /* cmp esi, 0x86 -> jne 0x17abd4 */
  D3DDevice_SetRenderState_MultiSampleType();
  /* cmp esi, 0x87 -> jne 0x17abe7 */
  D3DDevice_SetRenderState_ShadowFunc();
  /* cmp esi, 0x88 -> jne 0x17abfa */
  D3DDevice_SetRenderState_LineWidth();
  /* cmp esi, 0x89 -> jne 0x17ac0d */
  D3DDevice_SetRenderState_Dxt1NoiseEnable();
  /* cmp esi, 0x8a -> jne 0x17ac20 */
  D3DDevice_SetRenderState_YuvEnable();
  /* cmp esi, 0x8b -> jne 0x17ac33 */
  D3DDevice_SetRenderState_OcclusionCullEnable();
  /* cmp esi, 0x8c -> jne 0x17ac46 */
  D3DDevice_SetRenderState_StencilCullEnable();
  /* cmp esi, 0x8d -> jne 0x17ac59 */
  D3DDevice_SetRenderState_RopZCmpAlwaysRead();
  /* cmp esi, 0x8e -> jne 0x17ac6c */
  D3DDevice_SetRenderState_RopZRead();
  /* cmp esi, 0x8f -> jne 0x17ac7a */
  D3DDevice_SetRenderState_DoNotCullUncompressed();
  /* cmp edx, 0x16 -> jge 0x17ac90 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x17aca1 */
  D3DDevice_SetTextureState_TexCoordIndex();
  /* cmp edx, 0x1d -> jne 0x17acb2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x17acc3 */
  D3DDevice_SetTextureState_ColorKeyColor();
  /* cmp edx, 0x1b -> jg 0x17acd0 */
  D3DDevice_SetTextureState_BumpEnv();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_BeginVisibilityTest();
  D3DDevice_EndVisibilityTest();
  D3DDevice_GetVisibilityTestResult();

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17ad20 */
void FUN_0017ad20(void)
{
  int edx = 0;

  D3DDevice_SetVertexData2f(edx, 0.0f, 0.0f);

  (void)edx;
}

/* 0x17ad40 */
void FUN_0017ad40(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;

  D3DDevice_SetVertexData4f(ecx, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(edx, 0, 0);
  D3DDevice_SetVertexDataColor(ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
}

/* 0x17ad90 */
void FUN_0017ad90(void)
{
  int eax = 0;

  D3DDevice_Begin(eax);
  D3DDevice_End();

  (void)eax;
}

/* 0x17adc0 */
void FUN_0017adc0(void)
{
  int eax = 0;
  int esi = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256fc] */
  D3DDevice_GetVisibilityTestResult();
  /* cmp esi, 0x88760828 -> jne 0x17ae1f */
  rasterizer_spin_begin();
  D3DDevice_GetVisibilityTestResult();
  /* cmp esi, 0x88760828 -> je 0x17ae02 */
  rasterizer_spin_end();
  /* test esi, esi -> jl 0x17ae27 */
  FUN_00167ff0(0, (char *)0x002a4890);
  display_assert((char *)0x002ae7c8, (char *)0x002ae7f0, 574, 0);
  system_exit(0);
  error(0, (char *)0x002ae788);

  (void)eax;
  (void)esi;
}

/* 0x17ae90 */
void FUN_0017ae90(void)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;

  /* cmp eax, ebx -> je 0x17aff3 */
  rasterizer_transparent_geometry_group_new();
  display_assert((char *)0x002a1774, (char *)0x002ae7f0, 88, 0);
  system_exit(0);
  /* cmp esi, ebx -> je 0x17afd3 */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: cmp byte ptr [0x47e4ca], (char)ebx -> jne 0x17aff1 */
  error(0, (char *)0x002a1744);
  /* relift: relift: mov byte ptr [0x47e4ca], 1 */

  (void)eax;
  (void)ebx;
  (void)esi;
}

/* 0x17b000 */
void FUN_0017b000(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 154, edi);
  system_exit(0);
  display_assert((char *)0x002ae82c, (char *)0x002ae7f0, 266, edi);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(2305);
  /* relift: relift: mov (char)eax, byte ptr [0x3256fd] */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = esi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(edi);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = esi */
  D3DDevice_SetRenderState_ZBias(ecx);
  FUN_00178b40(56, 0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b94] = edi */
  /* mem[0x005a5ae0] = 0x20 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  D3DDevice_SetRenderState_CullMode(2305);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7a4] = 0x10101 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb790] = 0x302 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb794] = edi */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb7c0] = 0x8006 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(edx);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb77c] = 0x203 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb798] = esi */
  D3DDevice_SetRenderState_ZBias(0);
  FUN_0017cfe0(0x3f800000);
  FUN_00178b40(56, 0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)edx, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = edi */
  /* mem[0x005a5b94] = 3 */
  /* mem[0x005a5b48] = 0x8080000 */
  /* mem[0x005a5b74] = 0xc0 */
  /* mem[0x005a5b4c] = 0xc0c0000 */
  /* mem[0x005a5b78] = 0xd0 */
  /* mem[0x005a5b50] = 0x4082415 */
  /* mem[0x005a5b7c] = 0x45 */
  /* mem[0x005a5ae0] = 0x50f0004 */
  /* mem[0x005a5ae4] = 0xc0d1400 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17b480 */
char FUN_0017b480(int param_1, int param_2, short param_3)
{
  int eax = 0;
  int ebx = 0;

  /* test eax, eax -> jne 0x17b4ac */
  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 285, 0);
  system_exit(0);
  rasterizer_set_texture_non_blocking();
  rasterizer_set_texture_direct_non_blocking();
  /* test (char)ebx, (char)ebx -> jne 0x17b532 */
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  D3DDevice_SetTextureStageState(0, 0, 0);
  return 0;

  (void)eax;
  (void)ebx;
}

/* 0x17b540 */
void FUN_0017b540(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x17b56c */
  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 318, 0);
  system_exit(0);
  D3DDevice_SetVertexData2f(10, 0.0f, 0.0f);

  (void)eax;
}

/* 0x17b580 */
void FUN_0017b580(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x17b5ac */
  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 334, 0);
  system_exit(0);
  D3DDevice_SetRenderState_ZEnable(eax);

  (void)eax;
}

/* 0x17b5c0 */
void FUN_0017b5c0(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test esi, esi -> jne 0x17b5ee */
  display_assert((char *)0x0025bb20, (char *)0x002ae7f0, 356, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17b617 */
  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 357, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17b7c9 */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  display_assert((char *)0x002ae850, (char *)0x002ae7f0, 369, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17b6c1 */
  /* test edi, edi -> je 0x17b6ed */
  FUN_001d9068();
  FUN_001d9068();
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, eax);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData2f(0, 0.0f, 0.0f);
  D3DDevice_End();

  (void)eax;
  (void)esi;
  (void)edi;
}

/* 0x17b7d0 */
void FUN_0017b7d0(void)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x17b7fe */
  display_assert((char *)0x0025bb20, (char *)0x002ae7f0, 425, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x17b827 */
  display_assert((char *)0x0029dc40, (char *)0x002ae7f0, 426, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 0x41 -> jne 0x17ba06 */
  FUN_0017a8a0();
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fcomp qword ptr [0x2533d0] */
  display_assert((char *)0x002ae850, (char *)0x002ae7f0, 437, 0);
  system_exit(0);
  /* test eax, eax -> je 0x17b902 */
  D3DDevice_Begin(0);
  D3DDevice_SetVertexDataColor(0, eax);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData2s(0, 0, 0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_End();

  (void)eax;
  (void)esi;
}

/* 0x17ba10 */
int FUN_0017ba10(float *position, int vis_index, int index)
{
  int eax = 0;

  /* relift: relift: mov (char)eax, byte ptr [0x3256fc] */
  /* test (char)eax, (char)eax -> je 0x17bc79 */
  FUN_0017a8a0();
  /* test (char)eax, (char)eax -> je 0x17bbbd */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x17ba5b */
  /* relift: relift: fld dword ptr [0x2533c8] */
  /* test (char)eax, 0x41 -> jne 0x17ba72 */
  /* relift: relift: fld dword ptr [0x2ae8d4] */
  /* test (char)eax, 0x41 -> jne 0x17baa4 */
  /* relift: relift: fld dword ptr [0x26a600] */
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x2ae8d4] */
  /* test (char)eax, 0x41 -> jne 0x17baed */
  /* relift: relift: fld dword ptr [0x26a600] */
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x2ae8d4] */
  /* test (char)eax, 0x41 -> jne 0x17bb36 */
  /* relift: relift: fld dword ptr [0x26a600] */
  floor(0.0f);
  /* relift: relift: fld dword ptr [0x2ae8d4] */
  /* test (char)eax, 0x41 -> jne 0x17bb7f */
  /* relift: relift: fld dword ptr [0x26a600] */
  floor(0.0f);
  D3DDevice_BeginVisibilityTest();
  D3DDevice_Begin(0);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_SetVertexData4f(0, 0.0f, 0.0f, 0.0f, 0.0f);
  D3DDevice_End();
  D3DDevice_EndVisibilityTest();
  FUN_00167ff0(0, (char *)0x002a4894);
  error(0, (char *)0x002ae898);
  return 1;

  (void)eax;
}

/* 0x17bca0 */
char FUN_0017bca0(void *shader, void *state)
{
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a18b8, (char *)0x002ae9d0, 100, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x17bcf3 */
  display_assert((char *)0x0029e09c, (char *)0x002ae9d0, 101, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  csmemset((void *)(uintptr_t)edi, 0, 240);
  /* relift: cmp dword ptr [ebx], 0 -> jle 0x17be2a */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 220);
  /* cmp esi, ecx -> je 0x17bde1 */
  error(0, (char *)0x002ae9a8);
  return 0;

  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x17be50 */
void FUN_0017be50(void)
{
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x17be5b */
  /* cmp (int16_t)esi, 0x19 -> jl 0x17be7b */
  display_assert((char *)0x002aeca8, (char *)0x002aed00, 212, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x17be86 */
  /* cmp (int16_t)edi, 8 -> jl 0x17bea6 */
  display_assert((char *)0x002aec48, (char *)0x002aed00, 213, 0);
  system_exit(0);
  /* cmp ecx, -1 -> jne 0x17bec3 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x17bedb */
  /* cmp (int16_t)esi, 9 -> jl 0x17bf06 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 233, 0);
  system_exit(0);

  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x17bf20 */
void FUN_0017bf20(void)
{
  int esi = 0;

  /* test esi, esi -> jne 0x17bf44 */
  display_assert((char *)0x002aef34, (char *)0x002aed00, 246, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x17bf53 */
  /* cmp (int16_t)eax, 6 -> jl 0x17bf73 */
  display_assert((char *)0x002aeeb8, (char *)0x002aed00, 247, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x17bf82 */
  /* cmp (int16_t)eax, 2 -> jl 0x17bfa2 */
  display_assert((char *)0x002aee30, (char *)0x002aed00, 248, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x17bfb1 */
  /* cmp (int16_t)eax, 2 -> jl 0x17bfd1 */
  display_assert((char *)0x002aeda8, (char *)0x002aed00, 249, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x52], 1 -> jne 0x17bff0 */
  /* relift: test byte ptr [esi], 1 -> je 0x17bff8 */

  (void)esi;
}

/* 0x17c000 */
void FUN_0017c000(void)
{
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x17c00b */
  /* cmp (int16_t)esi, 0x19 -> jl 0x17c02b */
  display_assert((char *)0x002aeca8, (char *)0x002aed00, 266, 0);
  system_exit(0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x17c036 */
  /* cmp (int16_t)edi, 8 -> jl 0x17c056 */
  display_assert((char *)0x002aec48, (char *)0x002aed00, 267, 0);
  system_exit(0);
  /* cmp ecx, -1 -> jne 0x17c073 */
  /* test (int16_t)esi, (int16_t)esi -> jl 0x17c08b */
  /* cmp (int16_t)esi, 9 -> jl 0x17c0b6 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 287, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x17c0f4 */
  display_assert((char *)0x002aef34, (char *)0x002aed00, 300, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x17c103 */
  /* cmp (int16_t)eax, 6 -> jl 0x17c123 */
  display_assert((char *)0x002aef40, (char *)0x002aed00, 301, 0);
  system_exit(0);

  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x17c140 */
void FUN_0017c140(void)
{
  int esi = 0;

  display_assert((char *)0x002af04c, (char *)0x002aed00, 316, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 0x28], -1 -> jne 0x17c182 */
  error(0, (char *)0x002af00c);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  error(0, (char *)0x002aefc0);

  (void)esi;
}

/* 0x17c1b0 */
void FUN_0017c1b0(void)
{
  int ecx = 0;
  int esi = 0;

  display_assert((char *)0x002aef34, (char *)0x002aed00, 340, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c201 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c1ee */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x17c259 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c201 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c201 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x17c259 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c218 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c218 */
  /* cmp (int16_t)ecx, (int16_t)eax -> je 0x17c259 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c242 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c22f */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x17c259 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c242 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c242 */
  /* cmp (int16_t)eax, (int16_t)ecx -> je 0x17c259 */
  /* test (int16_t)ecx, (int16_t)ecx -> je 0x17c26e */
  /* test (int16_t)eax, (int16_t)eax -> je 0x17c26e */
  /* cmp (int16_t)ecx, (int16_t)eax -> jne 0x17c26e */
  error(0, (char *)0x002af140);
  /* relift: cmp word ptr [esi + 0x4e], 0 -> jne 0x17c27c */
  /* relift: cmp word ptr [esi + 0x52], 0 -> je 0x17c298 */
  /* relift: cmp word ptr [esi + 0x54], 0 -> je 0x17c298 */
  error(0, (char *)0x002af0f0);
  /* relift: cmp word ptr [esi + 0x68], (int16_t)eax -> je 0x17c2a9 */
  /* relift: cmp word ptr [esi + 0x6c], (int16_t)eax -> jne 0x17c2be */
  error(0, (char *)0x002af0a0);
  /* relift: test byte ptr [esi], 1 -> je 0x17c2e8 */
  /* relift: cmp word ptr [esi + 0x4e], 0 -> jne 0x17c2d1 */
  /* relift: cmp word ptr [esi + 0x52], 0 -> je 0x17c2e8 */
  error(0, (char *)0x002af050);

  (void)ecx;
  (void)esi;
}

/* 0x17c2f0 */
char FUN_0017c2f0(void *shader, void *state)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a18b8, (char *)0x002aed00, 388, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x17c34b */
  display_assert((char *)0x0029e09c, (char *)0x002aed00, 389, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  csmemset((void *)(uintptr_t)edi, 0, 240);
  /* test eax, eax -> jg 0x17c392 */
  /* test ecx, ecx -> jg 0x17c38e */
  error(0, (char *)0x002af17c);
  /* test eax, eax -> jle 0x17c3a3 */
  /* relift: cmp dword ptr [ebx], 0 -> jle 0x17c407 */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 100);
  /* test (char)ecx, (char)ecx -> je 0x17c3fd */
  FUN_0017c140();
  /* cmp eax, ecx -> jl 0x17c3e0 */
  /* cmp eax, ecx -> jle 0x17c754 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 112);
  /* test (char)eax, (char)eax -> je 0x17c468 */
  FUN_0017c1b0();
  FUN_000d1c90((float *)(uintptr_t)edx);
  FUN_0017be50();
  FUN_0017be50();
  FUN_0017be50();
  FUN_0017be50();
  /* cmp (int16_t)esi, 9 -> jl 0x17c4ed */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 233, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jl 0x17c529 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 233, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jl 0x17c565 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 233, 0);
  system_exit(0);
  FUN_0017bf20();
  FUN_0017c000();
  FUN_0017c000();
  FUN_0017c000();
  FUN_0017c000();
  /* cmp (int16_t)esi, 9 -> jl 0x17c632 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 287, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jl 0x17c66e */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 287, 0);
  system_exit(0);
  /* cmp (int16_t)esi, 9 -> jl 0x17c6a7 */
  display_assert((char *)0x002aed50, (char *)0x002aed00, 287, 0);
  system_exit(0);
  /* cmp (int16_t)eax, 6 -> jl 0x17c6e0 */
  display_assert((char *)0x002aef40, (char *)0x002aed00, 301, 0);
  system_exit(0);
  /* relift: test byte ptr [ebx], 2 -> je 0x17c6f3 */
  return 1;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x17c790 */
void rasterizer_window_set_fog(void)
{
  int eax = 0;

  game_state_malloc((char *)0x002af214, (char *)0, 16);
  /* mem[0x0047e4d0] = eax */
  display_assert((char *)0x002af1bc, (char *)0x002af1ec, 289, 0);
  system_exit(0);

  (void)eax;
}

/* 0x17c7d0 */
void FUN_0017C7D0(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x1559f9 */
  display_assert((char *)0x0029dc40, (char *)0x0029dc0c, 1331, 0);
  system_exit(0);

  (void)eax;
}

/* 0x17c8e0 */
void rasterizer_environment_fog_screen_draw(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c8f0 */
void rasterizer_environment_fog_screen_end(void *screen_fog)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c930 */
void rasterizer_dynamic_lit_geometry_draw(void *param_1, void *param_2)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c940 */
void rasterizer_dynamic_screen_geometry_draw(void)
{
  int eax = 0;

  rasterizer_memory_pool_delete();
  FUN_0015e9e0();
  FUN_00184690();
  FUN_00178ab0();
  FUN_0017e040();
  FUN_0017ff60();
  rasterizer_text_cache_dispose();
  FUN_0015c680();
  FUN_0016fec0();
  FUN_00165a10();
  FUN_0017d990();
  texture_cache_delete();
  /* test eax, eax -> je 0x155be4 */
  D3DDevice_Release();
  /* mem[0x00476ab0] = 0 */
  /* test eax, eax -> je 0x155bf7 */

  (void)eax;
}

/* 0x17c960 */
void rasterizer_psuedo_dynamic_screen_quad_draw(int param_1)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c970 */
int rasterizer_widget_submit(int mode)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x17c980 */
void *rasterizer_widget_begin(int handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return NULL;
}

/* 0x17c990 */
void rasterizer_widget_set_texture(int handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c9a0 */
void rasterizer_widget_set_tint_factor(int handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c9b0 */
int rasterizer_widget_set_zbuffer_enable(int param_1, int param_2)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x17c9c0 */
short rasterizer_widget_draw_sprite2d(int dynamic_vertex_buffer_index)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x17c9d0 */
int rasterizer_widget_draw_sprite3d(int zbuf_result)
{
  /* relift: no calls detected — manual review */
  (void)0;
  return 0;
}

/* 0x17c9e0 */
void rasterizer_widget_end(int handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17c9f0 */
void rasterizer_widget_submit_occlusion_test(int handle)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ca00 */
void rasterizer_widget_get_occlusion_test_result(void)
{
  int eax = 0;

  /* test eax, eax -> jne 0x15a726 */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 81, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);

  (void)eax;
}

/* 0x17ca10 */
void rasterizer_hud_motion_sensor_blip_begin(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ca20 */
void rasterizer_hud_motion_sensor_blip_draw(void)
{
  /* relift: no calls detected — manual review */
  (void)0;
}

/* 0x17ca30 */
void rasterizer_hud_motion_sensor_blip_end(void)
{
  int eax = 0;
  int ecx = 0;

  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);
  D3DDevice_SetVertexData4f(ecx, 0.0f, 0.0f, 0.0f, 0.0f);

  (void)eax;
  (void)ecx;
}

/* 0x17ca40 */
void FUN_0017ca40(void)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  /* test eax, eax -> jne 0x15aa6f */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 167, 0);
  system_exit(0);
  D3DDevice_SetRenderState_CullMode(0);
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb784] = 0 */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* mem[0x001fb788] = 0 */
  D3DDevice_SetRenderState_ZEnable(0);
  D3DDevice_SetRenderState_ZBias(0);
  FUN_00178b40(0, 0, 0);
  /* relift: relift: mov (int16_t)eax, word ptr [0x5a5bfa] */
  /* relift: relift: fld dword ptr [0x255e94] */
  /* relift: relift: fld dword ptr [0x25eeac] */
  D3DDevice_SetVertexShaderConstant(0, (void *)0, 0);
  csmemset((void *)0x005a5ac0, 0, 240);
  /* mem[0x005a5b98] = 0 */
  /* mem[0x005a5b94] = 1 */
  /* mem[0x005a5ae0] = 4 */
  rasterizer_set_pixel_shader((void *)0x005a5ac0);
  /* test edi, edi -> je 0x15abfb */
  /* test eax, eax -> je 0x15abfb */
  /* test esi, esi -> jne 0x15ac1b */
  display_assert((char *)0x0029f6f8, (char *)0x0029f6c0, 221, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x15ac44 */
  display_assert((char *)0x0029dc40, (char *)0x0029f6c0, 222, 0);

  (void)eax;
  (void)esi;
  (void)edi;
}
