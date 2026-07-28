#include <stdint.h>
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

/* rasterizer_transparent_geometry_group_draw (0x174d10) — readable C lift (restored pre-naked). */
void rasterizer_transparent_geometry_group_draw(void *group, int dirty)
{
  char *grp = (char *)group;
  char success; /* [EBP-0x1] draw success accumulator */
  char draw_secondary; /* [EBP-0x2d] draw dirty secondary groups after */
  char *sh;
  int vertex_type; /* [EBP-0x38] */
  int permutation; /* [EBP-0x40] */
  int pass; /* [EBP-0x80] two-pass layer loop */
  char has_multi; /* [EBP+0xb] case-1 secondary-map flag */
  short sec_count; /* [EBP+0xa] secondary group count */
  char *sec;
  short si;
  char *rec;
  char *next;

  success = 1;
  draw_secondary = 0;
  if (grp == (char *)0) {
    display_assert("group",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                   "transparent_geometry.c",
                   0xe8, 1);
    system_exit(-1);
  }
  if (*(int *)0x476ab0 == 0) {
    display_assert("global_d3d_device",
                   "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                   "transparent_geometry.c",
                   0xe9, 1);
    system_exit(-1);
  }
  if (*(int *)(grp + 0x98) != 0 && (char)dirty == 0) {
    return;
  }
  if (FUN_00184570(grp) == 0) {
    return;
  }
  FUN_001845b0(grp, 0);
  if (*(short *)(grp + 0x94) != -1) {
    rasterizer_transparent_geometry_group_draw(
      rasterizer_transparent_geometry_group_get(*(short *)(grp + 0x94)), dirty);
  }

  /* rasterizer_debug_transparents: draw with random per-group tint */
  if (*(char *)0x3256c2 != 0) {
    if ((*grp & 2) == 0 && *(int *)(grp + 0xc) != 0 &&
        *(int *)(grp + 0x90) != -1) {
      short vertex_shader_table[12];
      char solid_color; /* [EBP+0xb] debug value forces solid color */
      unsigned int seed;
      float argb[4]; /* [EBP-0x2c] alpha,red,green,blue */
      float blue;
      float minimum;
      float maximum;
      float range_scale;
      float tint;
      float dim;
      float skin_xform[12]; /* [EBP-0xb0] */
      struct {
        void *matrices;
        short node_count;
      } skinning; /* [EBP-0x1c] */
      char text_buffer[96]; /* [EBP-0x550] */

      vertex_shader_table[0] = 6;
      vertex_shader_table[1] = 6;
      vertex_shader_table[2] = 6;
      vertex_shader_table[3] = 6;
      vertex_shader_table[4] = 0xd;
      vertex_shader_table[5] = 0xd;
      vertex_shader_table[6] = 0x41;
      vertex_shader_table[7] = 0x41;
      vertex_shader_table[8] = -1;
      vertex_shader_table[9] = -1;
      vertex_shader_table[10] = -1;
      vertex_shader_table[11] = -1;
      vertex_type = (short)FUN_00184610(grp);
      if (*(short *)0x3256ea >= 1000 || *(short *)0x3256ea < 0) {
        solid_color = 1;
      } else {
        solid_color = 0;
      }
      if ((short)vertex_type < 0 || (short)vertex_type >= 0xc) {
        display_assert(
          "vertex_type>=0 && vertex_type<NUMBER_OF_RASTERIZER_VERTEX_TYPES",
          "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
          "geometry.c",
          0x118, 1);
        system_exit(-1);
      }
      if (vertex_shader_table[(short)vertex_type] == -1) {
        display_assert("vertex_shader_table[vertex_type]!=NONE",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x119, 1);
        system_exit(-1);
      }
      FUN_00178b40(
        (int)(0xffff0000u |
              (unsigned short)vertex_shader_table[(short)vertex_type]),
        vertex_type, 0);
      D3DDevice_SetRenderState_CullMode(0);
      D3DDevice_SetRenderState_Simple(NV097_SET_COLOR_MASK_CMD, NV097_COLOR_MASK_RGB);
      *(uint32_t *)0x1fb7a4 = 0x10101;
      D3DDevice_SetRenderState_Simple(0x40304, (unsigned char)solid_color);
      *(uint32_t *)0x1fb784 = (unsigned char)solid_color;
      D3DDevice_SetRenderState_Simple(0x40344, 1);
      *(uint32_t *)0x1fb790 = 1;
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
      csmemset((void *)0x5a5ac0, 0, 0xf0);
      seed = (unsigned int)((int)*(short *)0x3256ea + *(int *)(grp + 0x90));
      argb[0] = 1.0f;
      argb[1] = random_math_real(&seed);
      argb[2] = random_math_real(&seed);
      blue = random_math_real(&seed);
      /* normalize color so channels span [0.15, 0.33]; MIN/MAX macros
       * re-evaluate their arguments as in the original */
      minimum = (argb[1] <= ((argb[2] <= blue) ? argb[2] : blue)) ?
                  argb[1] :
                  ((argb[2] <= blue) ? argb[2] : blue);
      maximum = (argb[1] <= ((blue < argb[2]) ? argb[2] : blue)) ?
                  ((blue < argb[2]) ? argb[2] : blue) :
                  argb[1];
      range_scale = *(float *)0x2a52b4 / (maximum - minimum);
      argb[1] = (argb[1] - minimum) * range_scale + *(float *)0x256140;
      argb[2] = (argb[2] - minimum) * range_scale + *(float *)0x256140;
      argb[3] = (blue - minimum) * range_scale + *(float *)0x256140;
      if (solid_color != 0) {
        tint = *(float *)0x325724;
        if (tint < *(float *)0x2533c0) {
          tint = *(float *)0x29d598;
        } else if (tint > *(float *)0x2533c8) {
          tint = 1.0f;
        } else if (tint == *(float *)0x2533c0) {
          tint = *(float *)0x29d598;
        }
        if (*(short *)0x3256ea >= 1000) {
          argb[1] = argb[1] * tint;
          argb[2] = argb[2] * tint;
          argb[3] = tint * argb[3];
        } else {
          argb[1] = tint;
          argb[2] = tint;
          argb[3] = tint;
        }
      }
      if (!(argb[1] >= *(float *)0x2533c0 && argb[1] <= *(float *)0x2533c8)) {
        display_assert("color.red >=0.0f && color.red <=1.0f",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x156, 1);
        system_exit(-1);
      }
      if (!(argb[2] >= *(float *)0x2533c0 && argb[2] <= *(float *)0x2533c8)) {
        display_assert("color.green>=0.0f && color.green<=1.0f",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x157, 1);
        system_exit(-1);
      }
      if (!(argb[3] >= *(float *)0x2533c0 && argb[3] <= *(float *)0x2533c8)) {
        display_assert("color.blue >=0.0f && color.blue <=1.0f",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x158, 1);
        system_exit(-1);
      }
      *(uint32_t *)0x5a5b6c = FUN_000d1dd0(&argb[1]);
      *(uint32_t *)0x5a5b94 = 1;
      *(uint32_t *)0x5a5ae0 = 1;
      rasterizer_set_pixel_shader((void *)0x5a5ac0);
      if (*(void **)(grp + 0x60) != (void *)0 && *(short *)(grp + 0x64) != 0) {
        skinning.matrices = *(void **)(grp + 0x60);
        skinning.node_count = *(short *)(grp + 0x64);
      } else {
        skinning.matrices = *(void **)0x31fc60;
        skinning.node_count = 1;
      }
      rasterizer_set_model_skinning(&skinning);
      skin_xform[0] = 1.0f;
      skin_xform[1] = 0.0f;
      skin_xform[2] = 0.0f;
      skin_xform[3] = 0.0f;
      skin_xform[4] = 0.0f;
      skin_xform[5] = 1.0f;
      skin_xform[6] = 0.0f;
      skin_xform[7] = 0.0f;
      skin_xform[8] = 0.0f;
      skin_xform[9] = 0.0f;
      skin_xform[10] = 1.0f;
      skin_xform[11] = 0.0f;
      if ((*grp & 0x20) != 0) {
        skin_xform[0] = *(float *)0x5a5c64;
        skin_xform[1] = *(float *)0x5a5c70;
        skin_xform[2] = *(float *)0x5a5c7c;
        skin_xform[3] = *(float *)0x5a5bc8;
        skin_xform[4] = *(float *)0x5a5c68;
        skin_xform[5] = *(float *)0x5a5c74;
        skin_xform[6] = *(float *)0x5a5c80;
        skin_xform[7] = *(float *)0x5a5bcc;
        skin_xform[8] = *(float *)0x5a5c6c;
        skin_xform[9] = *(float *)0x5a5c78;
        skin_xform[10] = *(float *)0x5a5c84;
        skin_xform[11] = *(float *)0x5a5bd0;
      }
      D3DDevice_SetVertexShaderConstant(0x58, skin_xform, 3);
      success = 1;
      FUN_00174510(grp, 0);
      if (solid_color == 0) {
        crt_sprintf(text_buffer, "%.03f", (double)*(float *)(grp + 0x70));
        argb[1] = argb[1] * *(float *)0x254644;
        if (argb[1] < *(float *)0x2533c0) {
          argb[1] = 0.0f;
        } else if (argb[1] > *(float *)0x2533c8) {
          argb[1] = 1.0f;
        }
        dim = argb[1] * *(float *)0x254644;
        if (dim < *(float *)0x2533c0) {
          argb[2] = 0.0f;
          argb[3] = 0.0f;
        } else if (dim > *(float *)0x2533c8) {
          argb[2] = 1.0f;
          argb[3] = 1.0f;
        } else {
          argb[2] = dim;
          argb[3] = dim;
        }
        FUN_00189cb0(0, grp + 0x74, text_buffer, (int)argb);
      }
    }
    goto tail;
  }

  /* predicted shaders: pre-set state for run of type-2 groups w/ same tag */
  if (*(short *)(grp + 0x14) == 2 && *(int *)(grp + 8) != *(int *)0x47e4b8 &&
      (char)dirty == 0) {
    char *g2;
    int first_tag;
    struct {
      void *matrices;
      short node_count;
    } skinning2;

    first_tag = *(int *)(grp + 8);
    g2 = grp;
    vertex_type = FUN_00184610(grp);
    FUN_00178b40(0xd, vertex_type, 0);
    SetRenderStateSmart(0x7f, 0);
    SetRenderStateSmart(0x43, 0);
    SetRenderStateSmart(0x3b, 0);
    SetRenderStateSmart(0x3c, 0);
    SetRenderStateSmart(0x7b, 1);
    SetRenderStateSmart(0x40, 1);
    SetRenderStateSmart(0x39, 0x203);
    D3DDevice_SetRenderState_ZBias(0);
    csmemset((void *)0x5a5ac0, 0, 0xf0);
    *(uint32_t *)0x5a5b94 = 1;
    rasterizer_set_pixel_shader((void *)0x5a5ac0);
    do {
      if (*(int *)(g2 + 8) != first_tag || *(short *)(g2 + 0x14) != 2) {
        break;
      }
      if (shader_ignores_effect(*(void **)(g2 + 0xc)) == 0) {
        if (*(void **)(g2 + 0x60) != (void *)0 && *(short *)(g2 + 0x64) != 0) {
          skinning2.node_count = *(short *)(g2 + 0x64);
          skinning2.matrices = *(void **)(g2 + 0x60);
        } else {
          skinning2.node_count = 1;
          skinning2.matrices = *(void **)0x31fc60;
        }
        rasterizer_set_model_skinning(&skinning2);
        if (*(int *)(grp + 0x68) != 0) {
          rasterizer_set_model_lighting(*(void **)(g2 + 0x68));
        }
        FUN_00174510(g2, 0);
      }
      g2 = (char *)rasterizer_transparent_geometry_next_group(g2);
    } while (g2 != (char *)0);
  }

  if ((*grp & 2) == 0) {
    if (*(short *)0x5a5bc0 == 0 && (char)dirty == 0) {
      sh = *(char **)(grp + 0xc);
      if (*(char *)0x3256fa == 0) {
        if (sh == (char *)0 ||
            (*(short *)(sh + 0x24) != 7 && shader_is_water_decal(sh) == 0)) {
          FUN_001595c0();
        }
      } else if (sh != (char *)0 && *(short *)(sh + 0x24) == 4 &&
                 *(short *)(grp + 0x14) == 1 &&
                 *(int *)(grp + 8) != *(int *)0x47e4b8) {
        FUN_001595c0();
      }
    }
    if ((*grp & 2) == 0 && *(short *)0x5a5bc0 == 0 &&
        *(short *)(grp + 0x14) == 1 && *(int *)(grp + 0xc) != 0 &&
        *(short *)(*(char **)(grp + 0xc) + 0x24) == 4 && (char)dirty == 0) {
      next = (char *)rasterizer_transparent_geometry_next_group(grp);
      if (next == (char *)0 || *(short *)(next + 0x14) != 1 ||
          *(int *)(next + 8) != *(int *)(grp + 8) ||
          *(int *)(next + 0xc) == 0 ||
          *(short *)(*(char **)(next + 0xc) + 0x24) != 4) {
        draw_secondary = 1;
      }
    }
  }

  if (*(int *)(grp + 0xc) == 0) {
    /* group with no shader: invoke user callback stored in the record */
    (*(void (**)(int, int))(grp + 0x48))(*(int *)(grp + 0x4c),
                                         *(int *)(grp + 0x50));
    goto tail;
  }

  permutation = shader_get_vertex_shader_permutation(*(void **)(grp + 0xc));
  vertex_type = FUN_00184610(grp);
  if ((*grp & 2) == 0) {
    struct {
      void *matrices;
      short node_count;
    } skinning3;
    if (*(void **)(grp + 0x60) != (void *)0 && *(short *)(grp + 0x64) != 0) {
      skinning3.node_count = *(short *)(grp + 0x64);
      skinning3.matrices = *(void **)(grp + 0x60);
    } else {
      skinning3.node_count = 1;
      skinning3.matrices = *(void **)0x31fc60;
    }
    rasterizer_set_model_skinning(&skinning3);
    if (*(int *)(grp + 0x68) != 0) {
      rasterizer_set_model_lighting(*(void **)(grp + 0x68));
    }
  }
  if ((*grp & 8) != 0) {
    if (*(short *)0x5a5bc0 == 0) {
      rasterizer_set_frustum_z(0.00390625f, 1024.0f);
    }
    SetRenderStateSmart(0x7b, 0);
    SetRenderStateSmart(0x81, 0);
  } else {
    SetRenderStateSmart(0x7b, 1);
    SetRenderStateSmart(0x40, 0);
    SetRenderStateSmart(0x39, 0x203);
    SetRenderStateSmart(0x81,
                        -(int)(shader_is_decal(*(void **)(grp + 0xc)) != 0) &
                          *(int *)0x32570c);
  }

  pass = 0;
  do {
    if ((char)*grp < 0) {
      if (*(short *)(grp + 0x14) == 1) {
        if ((short)pass > 0) {
          break;
        }
        rasterizer_set_frustum_z(*(float *)0x32569c, *(float *)0x3256a0);
      } else if ((short)pass != 0) {
        FUN_00158ae0(2);
        SetRenderStateSmart(0x7b, 0);
      } else {
        sh = *(char **)(grp + 0xc);
        if (sh != (char *)0 && *(short *)(sh + 0x24) == 1) {
          char *senv = (char *)FUN_001906b0(sh, 1);
          if ((*(unsigned char *)(senv + 0x28) & 4) != 0) {
            goto next_pass;
          }
        }
        FUN_00158ae0(3);
      }
    } else if ((short)pass > 0) {
      break;
    }

    sh = *(char **)(grp + 0xc);
    switch (*(short *)(sh + 0x24)) {
    case 1: {
      /* shader_environment-style multitexture path */
      char *env;
      char env_flags_bit1; /* BL: (shader->flags >> 1) & 1 */
      float skin_xform1[12]; /* [EBP-0x108] */
      float texanim1[16]; /* [EBP-0x1f0] rows 2,3 written by texture anim */
      float fog_consts[8]; /* [EBP-0xa0] */
      float opacity;
      float fog_scale;
      int stage_count;
      int idx;

      env = (char *)FUN_001906b0(sh, 1);
      /* has_multi = secondary map used as a regular multitexture stage.
       * A z-sprite secondary map (env+0x5c == 2) is NOT a multitexture
       * stage — it goes through the dedicated z-sprite final-combiner
       * path instead (original 0x175830: jne keeps 1, i.e. != 2). */
      if (*(int *)(env + 0x58) != -1 && *(short *)(env + 0x5c) != 2) {
        has_multi = 1;
      } else {
        has_multi = 0;
      }
      env_flags_bit1 = (char)((*(unsigned char *)(env + 0x28) >> 1) & 1);
      rasterizer_set_texture_bitmap_data(0, *(void **)(grp + 0x5c));
      SetTextureStageStateSmart(0, 0xa,
                                (*(unsigned char *)(env + 0x2e) & 2) | 1);
      SetTextureStageStateSmart(
        0, 0xb, ((*(unsigned char *)(env + 0x2e) & 4) | 2) >> 1);
      SetTextureStageStateSmart(
        0, 0xd, 2 - (int)((*(unsigned char *)(env + 0x2e) & 1) != 0));
      SetTextureStageStateSmart(
        0, 0xe, 2 - (int)((*(unsigned char *)(env + 0x2e) & 1) != 0));
      SetTextureStageStateSmart(
        0, 0xf, 2 - (int)((*(unsigned char *)(env + 0x2e) & 1) != 0));
      if (*(int *)(env + 0x58) != -1) {
        rasterizer_set_texture(1, 0, 1, *(int *)(env + 0x58),
                               *(unsigned short *)(grp + 0x10));
        SetTextureStageStateSmart(1, 0xa,
                                  (*(unsigned char *)(env + 0x5e) & 2) | 1);
        SetTextureStageStateSmart(
          1, 0xb, ((*(unsigned char *)(env + 0x5e) & 4) | 2) >> 1);
        SetTextureStageStateSmart(
          1, 0xd, 2 - (int)((*(unsigned char *)(env + 0x5e) & 1) != 0));
        SetTextureStageStateSmart(
          1, 0xe, 2 - (int)((*(unsigned char *)(env + 0x5e) & 1) != 0));
        SetTextureStageStateSmart(
          1, 0xf, 2 - (int)((*(unsigned char *)(env + 0x5e) & 1) != 0));
      }
      SetRenderStateSmart(0x7f, 0);
      SetRenderStateSmart(0x43, 0x10101);
      SetRenderStateSmart(0x3b, 1);
      SetRenderStateSmart(0x3c, 0);
      FUN_001580b0(*(unsigned short *)(env + 0x2a));
      FUN_00178b40(0x41, vertex_type, permutation);
      skin_xform1[0] = 1.0f;
      skin_xform1[1] = 0.0f;
      skin_xform1[2] = 0.0f;
      skin_xform1[3] = 0.0f;
      skin_xform1[4] = 0.0f;
      skin_xform1[5] = 1.0f;
      skin_xform1[6] = 0.0f;
      skin_xform1[7] = 0.0f;
      skin_xform1[8] = 0.0f;
      skin_xform1[9] = 0.0f;
      skin_xform1[10] = 1.0f;
      skin_xform1[11] = 0.0f;
      texanim1[0] = 1.0f;
      texanim1[1] = 0.0f;
      texanim1[2] = 0.0f;
      texanim1[3] = 0.0f;
      texanim1[4] = 0.0f;
      texanim1[5] = 1.0f;
      texanim1[6] = 0.0f;
      texanim1[7] = 0.0f;
      texanim1[8] = 0.0f;
      texanim1[9] = 0.0f;
      texanim1[10] = 0.0f;
      texanim1[11] = 0.0f;
      texanim1[12] = 0.0f;
      texanim1[13] = 0.0f;
      texanim1[14] = 0.0f;
      texanim1[15] = 0.0f;
      if ((*grp & 0x20) != 0) {
        skin_xform1[0] = *(float *)0x5a5c64;
        skin_xform1[1] = *(float *)0x5a5c70;
        skin_xform1[2] = *(float *)0x5a5c7c;
        skin_xform1[3] = *(float *)0x5a5bc8;
        skin_xform1[4] = *(float *)0x5a5c68;
        skin_xform1[5] = *(float *)0x5a5c74;
        skin_xform1[6] = *(float *)0x5a5c80;
        skin_xform1[7] = *(float *)0x5a5bcc;
        skin_xform1[8] = *(float *)0x5a5c6c;
        skin_xform1[9] = *(float *)0x5a5c78;
        skin_xform1[10] = *(float *)0x5a5c84;
        skin_xform1[11] = *(float *)0x5a5bd0;
      }
      if (has_multi != 0) {
        FUN_00190e10(env + 0x60, *(void **)(grp + 0x6c), *(float *)(grp + 0x3c),
                     *(float *)(grp + 0x40), 0.0f, 0.0f, 0.0f,
                     *(float *)0x5a5e18, &texanim1[8], &texanim1[12]);
      }
      D3DDevice_SetVertexShaderConstant(0x58, skin_xform1, 3);
      if (success != 0) {
        success = 1;
      } else {
        success = 0;
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__INVERSE_OFFSET, "
                     "vsh_constants__inverse, VSH_CONSTANTS__INVERSE_COUNT)");
      }
      D3DDevice_SetVertexShaderConstant(-0x51, texanim1, 4);
      if (success != 0) {
        success = 1;
      } else {
        success = 0;
        FUN_00167ff0(
          0, "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, "
             "VSH_CONSTANTS__TEXANIM_OFFSET, vsh_constants__texanim, 4)");
      }
      if (*(char *)0x325718 != 0 && *(short *)(env + 0x5c) == 2 &&
          *(int *)(env + 0x58) != -1 && (char)*grp >= 0) {
        /* z-sprite fog constants */
        opacity = 1.0f;
        if (*(float *)(env + 0x9c) != *(float *)0x2533c0) {
          opacity = *(float *)(env + 0x9c);
        }
        fog_scale = *(float *)0x2a50dc;
        if (*(char *)0x32568c != 0) {
          fog_scale = *(float *)0x2a50e0;
        }
        fog_consts[4] = *(float *)0x5a5bd4;
        fog_consts[5] = *(float *)0x5a5bd8;
        fog_consts[6] = *(float *)0x5a5bdc;
        fog_consts[0] = (*(float *)0x5a5c08 * fog_scale) /
                        (*(float *)0x5a5c08 - *(float *)0x5a5c04);
        fog_consts[1] = -(fog_consts[0] * *(float *)0x5a5c04);
        fog_consts[2] = opacity * *(float *)(env + 0x98);
        fog_consts[3] = *(float *)0x5a5c04 + *(float *)0x25bb10;
        fog_consts[7] = -FUN_00013070((float *)0x5a5bd4, (float *)0x5a5bc8);
        D3DDevice_SetVertexShaderConstant(-0x3f, fog_consts, 2);
        if (success != 0) {
          success = 1;
        } else {
          success = 0;
          FUN_00167ff0(0,
                       "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                       "device, VSH_CONSTANTS__ZSPRITE_OFFSET, "
                       "vsh_constants__zsprite, VSH_CONSTANTS__ZSPRITE_COUNT)");
        }
      }
      csmemset((void *)0x5a5ac0, 0, 0xf0);
      *(uint32_t *)0x5a5ac0 = 0x18201415;
      *(uint32_t *)0x5a5b28 = 0xc4;
      *(uint32_t *)0x5a5ae0 = 0xc;
      *(uint32_t *)0x5a5ae4 = 0x1c00;
      if (env_flags_bit1 != 0) {
        *(uint32_t *)0x5a5b48 = 0x8080000;
        *(uint32_t *)0x5a5b74 = 0xc0;
        *(uint32_t *)0x5a5b4c = 0xc0c0000;
        *(uint32_t *)0x5a5b78 = 0xc0;
        *(uint32_t *)0x5a5b50 = 0x250c0508;
        *(uint32_t *)0x5a5b7c = 0xc00;
        stage_count = 3;
      } else {
        *(uint32_t *)0x5a5b48 = 0x8050000;
        *(uint32_t *)0x5a5b74 = 0xc0;
        stage_count = 1;
      }
      if (has_multi != 0) {
        idx = (short)stage_count * 4;
        *(uint32_t *)(0x5a5ac0 + idx) = 0x1c190000;
        *(uint32_t *)(0x5a5b28 + idx) = 0xc0;
        *(uint32_t *)(0x5a5b48 + idx) = 0xc090000;
        *(uint32_t *)(0x5a5b74 + idx) = 0xc0;
        stage_count = stage_count + 1;
      }
      if (*(char *)0x325718 == 0 || *(short *)(env + 0x5c) != 2 ||
          *(int *)(env + 0x58) == -1 || (char)*grp < 0) {
        *(uint32_t *)0x5a5b98 = ((unsigned int)(has_multi != 0) << 5) | 1;
      } else {
        *(uint32_t *)0x5a5b98 = 0x54421;
        *(uint32_t *)0x5a5ba0 = 0x110000;
        *(uint32_t *)0x5a5b9c = 0;
        SetTextureStageStateSmart(1, 0xa, 1);
        SetTextureStageStateSmart(1, 0xb, 1);
        SetTextureStageStateSmart(1, 0xd, 2);
        SetTextureStageStateSmart(1, 0xe, 2);
        SetTextureStageStateSmart(1, 0xf, 2);
        D3DDevice_SetStreamSource(1, *(void **)0x47e4bc, 2);
        if (success != 0) {
          success = 1;
        } else {
          success = 0;
          FUN_00167ff0(0,
                       "IDirect3DDevice8_SetStreamSource(global_d3d_device, 1, "
                       "rasterizer_xbox_transparent_geometry_texcoord_stream, "
                       "2*sizeof(byte))");
        }
        rasterizer_set_texture(1, 0, 0, *(int *)(env + 0x58),
                               *(unsigned short *)(grp + 0x10));
      }
      if (*(char *)0x3256d4 != 0 && (*grp & 4) == 0) {
        switch (*(short *)(env + 0x2a)) {
        case 0:
          idx = (short)stage_count * 4;
          *(uint32_t *)(0x5a5ac0 + idx) = 0x1c140000;
          *(uint32_t *)(0x5a5b28 + idx) = 0xc00;
          stage_count = stage_count + 1;
          *(int *)0x5a5b94 = (short)stage_count;
          break;
        case 1:
        case 5:
          idx = (short)stage_count * 4;
          *(uint32_t *)(0x5a5b48 + idx) = 0xc142034;
          *(uint32_t *)(0x5a5b74 + idx) = 0xc00;
          stage_count = stage_count + 1;
          *(int *)0x5a5b94 = (short)stage_count;
          break;
        case 2:
          idx = (short)stage_count * 4;
          *(uint32_t *)(0x5a5b48 + idx) = 0xc14a034;
          *(uint32_t *)(0x5a5b74 + idx) = 0xc00;
          stage_count = stage_count + 1;
          *(int *)0x5a5b94 = (short)stage_count;
          break;
        case 3:
        case 4:
        case 6:
          idx = (short)stage_count * 4;
          *(uint32_t *)(0x5a5b48 + idx) = 0xc140000;
          *(uint32_t *)(0x5a5b74 + idx) = 0xc00;
          stage_count = stage_count + 1;
          *(int *)0x5a5b94 = (short)stage_count;
          break;
        case 7:
          idx = (short)stage_count * 4;
          *(uint32_t *)(0x5a5ac0 + idx) = 0x1c140000;
          *(uint32_t *)(0x5a5b28 + idx) = 0xc00;
          *(uint32_t *)(0x5a5b48 + idx) = 0xc140000;
          *(uint32_t *)(0x5a5b74 + idx) = 0xc00;
          stage_count = stage_count + 1;
          *(int *)0x5a5b94 = (short)stage_count;
          break;
        default:
          display_assert("### ERROR unsupported framebuffer blend function",
                         "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                         "transparent_geometry.c",
                         0x3a2, 1);
          system_exit(-1);
        }
      } else {
        *(int *)0x5a5b94 = (short)stage_count;
      }
      goto set_shader_and_draw;
    }

    case 4:
      /* model effect: only valid for object groups; drawn via decal path */
      if (*(short *)(grp + 0x14) != 1) {
        display_assert(
          "### ERROR unsupported model effect type in transparent group",
          "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
          "geometry.c",
          0x2ab, 1);
        system_exit(-1);
      }
      if (*(char *)0x47e4c0 != 0) {
        return;
      }
      FUN_00159900(grp);
      break;
    case 5: {
      /* shader_transparent_generic */
      char *gen;
      char *layers;
      char *map;
      char *stage;
      char *bitm;
      int frame_index; /* [EBP-0x34] */
      int n;
      int m;
      int j;
      short gtype;
      short first_map_type; /* [EBP-0x14] */
      short first_map_type_table[4]; /* [EBP-0xd8] */
      int op_table[4]; /* [EBP-0x134] */
      int colorop;
      int alphaop;
      float u;
      float v;
      float anim_out[32]; /* [EBP-0x330] 4 stages x 8 floats */
      char sub_group[0xa0]; /* [EBP-0x450] */
      int nstages;
      unsigned int fade_mode_value; /* [EBP-0x6c] */
      float fade_consts[12]; /* [EBP-0x180] */
      float t;
      float c[4]; /* [EBP-0x64] stage argb color */
      float da;
      float dr;
      float dg;
      float db;
      float *pf;
      char ok;
      int bcount;
      int limit;
      int eidx;
      int fvi;
      int k;
      float x;
      unsigned int blendrow;

      gen = (char *)FUN_001906b0(sh, 5);
      frame_index = *(unsigned short *)(grp + 0x10);
      layers = gen + 0x48;
      if (*(int *)layers > 0) {
        n = 0;
        do {
          csmemcpy(sub_group, grp, 0xa0);
          *(int *)(sub_group + 0x90) = -1;
          map = (char *)tag_block_get_element(layers, (short)n, 0x10);
          *(void **)(sub_group + 0xc) =
            tag_get(0x73686472, *(int *)(map + 0xc));
          rasterizer_transparent_geometry_group_draw(sub_group, dirty);
          n = n + 1;
        } while ((int)(short)n < *(int *)layers);
      }
      FUN_00178b40(0x18, vertex_type, permutation);
      SetRenderStateSmart(
        0x7f,
        (int)((-(unsigned int)((*(unsigned char *)(gen + 0x29) & 4) != 0) &
               0xfffff6ff) +
              0x901));
      SetRenderStateSmart(0x43, 0x10101);
      SetRenderStateSmart(0x3b, 1);
      SetRenderStateSmart(0x3c, *(unsigned char *)(gen + 0x29) & 1);
      SetRenderStateSmart(0x3d, 0x7f);
      FUN_001580b0(*(unsigned short *)(gen + 0x2c));
      if ((char)*(char *)(gen + 0x29) < 0 && *(int *)(grp + 0x6c) != 0 &&
          *(int *)(gen + 0x54) > 0) {
        /* numeric-counter driven first map index */
        map = (char *)tag_block_get_element(gen + 0x54, 0, 0x64);
        bitm = (char *)tag_get(0x6269746d, *(int *)(map + 0x28));
        bcount = *(short *)(bitm + 0x60);
        limit = (short)*(unsigned char *)(gen + 0x28);
        eidx = ((bcount != 8) - 1 & 3);
        x = (float)limit *
              *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) + eidx * 4) +
            *(float *)0x253398;
        /* PIN(FLOOR(...)) re-evaluates the floor expression per compare */
        if ((int)floor((double)x) < 0) {
          fvi = 0;
        } else if ((int)floor(
                     (double)((float)limit *
                                *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) +
                                           eidx * 4) +
                              *(float *)0x253398)) > limit) {
          fvi = limit;
        } else {
          fvi = (int)floor(
            (double)((float)limit *
                       *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) +
                                  eidx * 4) +
                     *(float *)0x253398));
        }
        for (k = *(short *)(grp + 0x10); k > 0; k--) {
          fvi = (int)(short)fvi / (int)(short)bcount;
        }
        frame_index = (int)(short)fvi % (int)(short)bcount;
      }
      m = 0;
      do {
        if ((int)(short)m < *(int *)(gen + 0x54)) {
          map = (char *)tag_block_get_element(gen + 0x54, (short)m, 0x64);
          gtype = *(short *)(gen + 0x2a);
          first_map_type_table[0] = 0;
          first_map_type_table[1] = 2;
          first_map_type_table[2] = 2;
          first_map_type_table[3] = 2;
          op_table[0] = 1;
          op_table[1] = 3;
          op_table[2] = 3;
          op_table[3] = 3;
          if ((short)m == 0) {
            first_map_type = first_map_type_table[gtype];
          } else {
            first_map_type = 0;
          }
          if ((*gen & 4) != 0 && gtype != 0) {
            display_assert(
              "!TEST_FLAG(shader_transparent_generic->shader.radiosity.flags, "
              "_shader_radiosity_FILTHY_transparent_lit_bit) || "
              "shader_transparent_generic->generic.type==_shader_transparent_"
              "generic_type_2d_map",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x406, 1);
            system_exit(-1);
          }
          if (gtype < 0 || gtype > 3) {
            display_assert(
              "type>=0 && type<NUMBER_OF_SHADER_TRANSPARENT_GENERIC_TYPES",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x407, 1);
            system_exit(-1);
          }
          rasterizer_set_texture((short)m, first_map_type, 0,
                                 *(int *)(map + 0x28), frame_index);
          if (first_map_type == 0 && (*map & 2) != 0) {
            colorop = 3;
          } else if ((short)m != 0) {
            colorop = 1;
          } else {
            colorop = op_table[gtype];
          }
          if (first_map_type == 0 && (*map & 4) != 0) {
            alphaop = 3;
          } else if ((short)m != 0) {
            alphaop = 1;
          } else {
            alphaop = op_table[gtype];
          }
          SetTextureStageStateSmart((short)m, 0xa, colorop);
          SetTextureStageStateSmart((short)m, 0xb, alphaop);
          SetTextureStageStateSmart((short)m, 0xc,
                                    ((short)m != 0) ? 1 : op_table[gtype]);
          D3DDevice_SetTextureStageState((short)m, 0xd, 2);
          SetTextureStageStateSmart((short)m, 0xe, 2 - (int)((*map & 1) != 0));
          SetTextureStageStateSmart((short)m, 0xf, 2 - (int)((*map & 1) != 0));
        }
        if ((int)(short)m < *(int *)(gen + 0x54) &&
            ((short)m > 0 || *(short *)(gen + 0x2a) == 0)) {
          map = (char *)tag_block_get_element(gen + 0x54, (short)m, 0x64);
          u = *(float *)(map + 4);
          v = *(float *)(map + 8);
          if ((short)m == 0) {
            if ((*(unsigned char *)(gen + 0x29) & 0x40) != 0) {
              u = -(u * *(float *)(grp + 0x70));
              v = -(v * *(float *)(grp + 0x70));
            }
            if ((*(unsigned char *)(gen + 0x29) & 8) == 0) {
              u = u * *(float *)(grp + 0x3c);
              v = v * *(float *)(grp + 0x40);
            }
          } else {
            u = u * *(float *)(grp + 0x3c);
            v = v * *(float *)(grp + 0x40);
          }
          FUN_00190e10(map + 0x2c, *(void **)(grp + 0x6c), u, v,
                       *(float *)(map + 0xc), *(float *)(map + 0x10),
                       *(float *)(map + 0x14), *(float *)0x5a5e18,
                       &anim_out[(short)m * 8], &anim_out[(short)m * 8 + 4]);
        } else if ((int)(short)m < *(int *)(gen + 0x54) &&
                   (*(unsigned char *)(gen + 0x29) & 8) != 0) {
          anim_out[(short)m * 8] = *(float *)0x5a5c64;
          anim_out[(short)m * 8 + 1] = *(float *)0x5a5c68;
          anim_out[(short)m * 8 + 2] = *(float *)0x5a5c6c;
          anim_out[(short)m * 8 + 4] = *(float *)0x5a5c70;
          anim_out[(short)m * 8 + 5] = *(float *)0x5a5c74;
          anim_out[(short)m * 8 + 6] = *(float *)0x5a5c78;
          anim_out[(short)m * 8 + 3] = 0.0f;
          anim_out[(short)m * 8 + 7] = 0.0f;
        } else {
          anim_out[(short)m * 8] = 1.0f;
          anim_out[(short)m * 8 + 1] = 0.0f;
          anim_out[(short)m * 8 + 2] = 0.0f;
          anim_out[(short)m * 8 + 4] = 0.0f;
          anim_out[(short)m * 8 + 5] = 1.0f;
          anim_out[(short)m * 8 + 6] = 0.0f;
          anim_out[(short)m * 8 + 3] = 0.0f;
          anim_out[(short)m * 8 + 7] = 0.0f;
        }
        m = m + 1;
      } while ((short)m < 4);
      D3DDevice_SetVertexShaderConstant(-0x51, anim_out, 8);
      if (success != 0) {
        ok = FUN_0017c2f0(*(void **)(grp + 0xc), (void *)0x5a5ac0);
        if (ok == 0) {
          success = 0;
        } else {
          success = 1;
        }
      } else {
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__TEXANIM_OFFSET, "
                     "vsh_constants__texanim, VSH_CONSTANTS__TEXANIM_COUNT)");
        success = 0;
      }
      if (*(char *)0x3256d4 == 0) {
        goto generic_stage_colors;
      }
      nstages = *(int *)(gen + 0x60);
      if (nstages < 1) {
        nstages = 1;
      }
      if ((*grp & 0x10) != 0 && *(short *)(gen + 0x2c) == 0) {
        /* fog-plane driven fade into an extra combiner stage */
        t = -(plane3d_distance_to_point((float *)0x5a5dc8, (float *)0x5a5bc8) /
              *(float *)0x5a5dec);
        if (t < *(float *)0x2533c0) {
          t = 0.0f;
        } else if (t > *(float *)0x2533c8) {
          t = 1.0f;
        }
        ((uint32_t *)0x5a5ae8)[(short)nstages] = real_a_rgb_color_to_pixel32(
          t * *(float *)0x5a5de4, (float *)0x5a5dd8);
        *(uint32_t *)(0x5a5b48 + (short)nstages * 4) = 0x310c1101;
        *(uint32_t *)(0x5a5b74 + (short)nstages * 4) = 0xc00;
        goto generic_stage_colors;
      }
      fade_consts[0] = 0.0f;
      fade_consts[1] = 0.0f;
      fade_consts[2] = 0.0f;
      fade_consts[3] = 0.0f;
      fade_consts[4] = 0.0f;
      fade_consts[5] = 0.0f;
      fade_consts[6] = 0.0f;
      fade_consts[7] = 0.0f;
      fade_consts[8] = 0.0f;
      fade_consts[9] = 0.0f;
      fade_consts[10] = 1.0f;
      fade_consts[11] = 0.0f;
      if (*(short *)(grp + 0x14) == 1) {
        t = *(float *)0x2533c8 - *(float *)(grp + 0x18);
        if (t < *(float *)0x2533c0) {
          fade_consts[10] = 0.0f;
        } else if (t > *(float *)0x2533c8) {
          fade_consts[10] = 1.0f;
        } else {
          fade_consts[10] = t;
        }
      }
      if (*(short *)(gen + 0x30) > 0 && *(int *)(grp + 0x6c) != 0 &&
          *(int *)(*(int *)(grp + 0x6c) + 4) != 0) {
        fade_consts[10] =
          fade_consts[10] * *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) - 4 +
                                       *(short *)(gen + 0x30) * 4);
      }
      D3DDevice_SetVertexShaderConstant(-0x54, fade_consts, 3);
      if (success != 0) {
        success = 1;
      } else {
        success = 0;
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__TEXSCALE_OFFSET, "
                     "vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT)");
      }
      if (*(short *)(gen + 0x2e) == 0) {
        fade_mode_value = 0x14;
      } else if (*(short *)(gen + 0x2e) == 1) {
        fade_mode_value = 0x15;
      } else {
        if (*(short *)(gen + 0x2e) != 2) {
          display_assert("### ERROR unsupported framebuffer fade mode",
                         "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                         "transparent_geometry.c",
                         0x4a1, 1);
          system_exit(-1);
        }
        fade_mode_value = 5;
      }
      switch (*(short *)(gen + 0x2c)) {
      case 0:
        *(uint32_t *)(0x5a5ac0 + (short)nstages * 4) =
          (fade_mode_value | 0x1c00) << 0x10;
        *(uint32_t *)(0x5a5b28 + (short)nstages * 4) = 0xc00;
        break;
      case 1:
      case 5:
        blendrow =
          (fade_mode_value ^ 0x20) | fade_mode_value << 0x10 | 0xc002000;
        *(uint32_t *)(0x5a5b48 + (short)nstages * 4) = blendrow;
        *(uint32_t *)(0x5a5b74 + (short)nstages * 4) = 0xc00;
        break;
      case 2:
        blendrow =
          (fade_mode_value ^ 0x20) | fade_mode_value << 0x10 | 0xc00a000;
        *(uint32_t *)(0x5a5b48 + (short)nstages * 4) = blendrow;
        *(uint32_t *)(0x5a5b74 + (short)nstages * 4) = 0xc00;
        break;
      case 3:
      case 4:
      case 6:
        *(uint32_t *)(0x5a5b48 + (short)nstages * 4) = (fade_mode_value | 0xc00)
                                                       << 0x10;
        *(uint32_t *)(0x5a5b74 + (short)nstages * 4) = 0xc00;
        break;
      case 7:
        *(uint32_t *)(0x5a5ac0 + (short)nstages * 4) =
          (fade_mode_value | 0x1c00) << 0x10;
        *(uint32_t *)(0x5a5b28 + (short)nstages * 4) = 0xc00;
        *(uint32_t *)(0x5a5b48 + (short)nstages * 4) = (fade_mode_value | 0xc00)
                                                       << 0x10;
        *(uint32_t *)(0x5a5b74 + (short)nstages * 4) = 0xc00;
        break;
      default:
        display_assert("### ERROR unsupported framebuffer blend function",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x4c0, 1);
        system_exit(-1);
      }
    generic_stage_colors:
      j = 0;
      if (*(int *)(gen + 0x60) > 0) {
        do {
          stage = (char *)tag_block_get_element(gen + 0x60, (short)j, 0x70);
          if (*(float *)(stage + 8) == *(float *)0x2533c0) {
            display_assert("stage->constant_color0_animation_period!=0.0f",
                           "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_"
                           "xbox_transparent_geometry.c",
                           0x4d3, 1);
            system_exit(-1);
          }
          if (*(int *)(grp + 0x6c) != 0 && (*stage & 4) != 0) {
            t = **(float **)(*(int *)(grp + 0x6c) + 4);
          } else {
            t = FUN_0010a5e0(*(short *)(stage + 6),
                             *(float *)0x5a5e18 / *(float *)(stage + 8));
          }
          da = *(float *)(stage + 0x1c) - *(float *)(stage + 0xc);
          dr = *(float *)(stage + 0x20) - *(float *)(stage + 0x10);
          dg = *(float *)(stage + 0x24) - *(float *)(stage + 0x14);
          db = *(float *)(stage + 0x28) - *(float *)(stage + 0x18);
          c[0] = t * da + *(float *)(stage + 0xc);
          c[1] = t * dr + *(float *)(stage + 0x10);
          c[2] = dg * t + *(float *)(stage + 0x14);
          c[3] = t * db + *(float *)(stage + 0x18);
#if !defined(_MSC_VER) || defined(__clang__)
          /* The original stores each channel to a 32-bit float (FSTP) and the
           * range asserts below reload the rounded value; clang keeps the
           * channels in x87 registers (FST + FUCOMI) and compares at 80-bit
           * extended precision.  When t == 1.0 the lerp lo + round32(hi-lo)*t
           * can land half a ULP above 1.0 (e.g. needler core stage 6 with the
           * weapon A-out pegged at 1.0), which passes the original's rounded
           * compare but trips the extended-precision one.  Force the same
           * store+reload rounding before comparing. */
          asm volatile("" : "+m"(c[0]), "+m"(c[1]), "+m"(c[2]), "+m"(c[3]));
#endif
          if (!(c[1] >= *(float *)0x2533c0 && c[1] <= *(float *)0x2533c8)) {
            display_assert(
              "constant_color0.red >=0.0f && constant_color0.red <=1.0f",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x4e8, 1);
            system_exit(-1);
          }
          if (!(c[2] >= *(float *)0x2533c0 && c[2] <= *(float *)0x2533c8)) {
            display_assert(
              "constant_color0.green>=0.0f && constant_color0.green<=1.0f",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x4e9, 1);
            system_exit(-1);
          }
          if (!(c[3] >= *(float *)0x2533c0 && c[3] <= *(float *)0x2533c8)) {
            display_assert(
              "constant_color0.blue >=0.0f && constant_color0.blue <=1.0f",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x4ea, 1);
            system_exit(-1);
          }
          if (*(short *)(stage + 4) > 0 && *(short *)(stage + 4) < 5 &&
              *(int **)(grp + 0x6c) != (int *)0 &&
              **(int **)(grp + 0x6c) != 0) {
            pf = (float *)(**(int **)(grp + 0x6c) - 0xc +
                           *(short *)(stage + 4) * 0xc);
            if (!(pf[0] >= *(float *)0x2533c0 && pf[0] <= *(float *)0x2533c8)) {
              display_assert(
                "external_color->red >=0.0f && external_color->red <=1.0f",
                "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                "transparent_geometry.c",
                0x4f5, 1);
              system_exit(-1);
            }
            if (!(pf[1] >= *(float *)0x2533c0 && pf[1] <= *(float *)0x2533c8)) {
              display_assert(
                "external_color->green>=0.0f && external_color->green<=1.0f",
                "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                "transparent_geometry.c",
                0x4f6, 1);
              system_exit(-1);
            }
            if (!(pf[2] >= *(float *)0x2533c0 && pf[2] <= *(float *)0x2533c8)) {
              display_assert(
                "external_color->blue >=0.0f && external_color->blue <=1.0f",
                "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                "transparent_geometry.c",
                0x4f7, 1);
              system_exit(-1);
            }
            c[1] = c[1] * pf[0];
            c[2] = c[2] * pf[1];
            c[3] = c[3] * pf[2];
          }
          ((uint32_t *)0x5a5ae8)[(short)j] = FUN_000d1c90(c);
          j = j + 1;
        } while ((int)(short)j < *(int *)(gen + 0x60));
      }
      goto set_shader_and_draw;
    }
    case 6: {
      /* shader_transparent_chicago */
      char *chi;
      char *layers2;
      char *map2;
      char *bitm2;
      int frame_index2; /* [EBP-0x14] */
      int m2; /* loop counter (param slot reuse in original) */
      short ctype;
      short first_map_type2; /* [EBP-0xc] */
      short first_map_type_table2[4]; /* [EBP-0xd0] */
      int op_table2[4]; /* [EBP-0x144] */
      int colorop2;
      int alphaop2;
      float u2;
      float v2;
      float anim_out2[32]; /* [EBP-0x3b0] */
      char sub_group2[0xa0]; /* [EBP-0x4f0] */
      short nstages2;
      unsigned int fade_mode_value2; /* [EBP-0x70] */
      float fade_consts2[12]; /* [EBP-0x1b0] */
      float t2;
      char ok2;
      int bcount2;
      int limit2;
      int eidx2;
      int fvi2;
      int k2;
      float x2;
      unsigned int blendrow2;

      chi = (char *)FUN_001906b0(sh, 6);
      frame_index2 = *(unsigned short *)(grp + 0x10);
      layers2 = chi + 0x48;
      /* NOTE: original re-reads the layer count each iteration and always
       * fetches element 0 -- faithful reproduction of the binary */
      while (*(int *)layers2 > 0) {
        csmemcpy(sub_group2, grp, 0xa0);
        *(int *)(sub_group2 + 0x90) = -1;
        map2 = (char *)tag_block_get_element(layers2, 0, 0x10);
        *(void **)(sub_group2 + 0xc) =
          tag_get(0x73686472, *(int *)(map2 + 0xc));
        rasterizer_transparent_geometry_group_draw(sub_group2, dirty);
      }
      FUN_00178b40(0x18, vertex_type, permutation);
      SetRenderStateSmart(
        0x7f,
        (int)((-(unsigned int)((*(unsigned char *)(chi + 0x29) & 4) != 0) &
               0xfffff6ff) +
              0x901));
      SetRenderStateSmart(0x43, 0x10101);
      SetRenderStateSmart(0x3b, 1);
      SetRenderStateSmart(0x3c, *(unsigned char *)(chi + 0x29) & 1);
      SetRenderStateSmart(0x3d, 0x7f);
      FUN_001580b0(*(unsigned short *)(chi + 0x2c));
      if ((char)*(char *)(chi + 0x29) < 0 && *(int *)(grp + 0x6c) != 0 &&
          *(int *)(chi + 0x54) > 0) {
        map2 = (char *)tag_block_get_element(chi + 0x54, 0, 0xdc);
        bitm2 = (char *)tag_get(0x6269746d, *(int *)(map2 + 0x78));
        bcount2 = *(short *)(bitm2 + 0x60);
        frame_index2 = (short)bcount2;
        if ((*(unsigned char *)(chi + 0x60) & 2) != 0) {
          frame_index2 =
            numeric_countdown_timer_get(*(unsigned short *)(grp + 0x10));
        } else {
          limit2 = (short)*(unsigned char *)(chi + 0x28);
          eidx2 = ((bcount2 != 8) - 1 & 3);
          x2 = (float)limit2 *
                 *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) + eidx2 * 4) +
               *(float *)0x253398;
          /* PIN(FLOOR(...)) re-evaluates the floor expression per compare */
          if ((int)floor((double)x2) < 0) {
            fvi2 = 0;
          } else if ((int)floor((
                       double)((float)limit2 *
                                 *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) +
                                            eidx2 * 4) +
                               *(float *)0x253398)) > limit2) {
            fvi2 = limit2;
          } else {
            fvi2 = (int)floor(
              (double)((float)limit2 *
                         *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) +
                                    eidx2 * 4) +
                       *(float *)0x253398));
          }
          for (k2 = *(short *)(grp + 0x10); k2 > 0; k2--) {
            fvi2 = (int)(short)fvi2 / (int)(short)frame_index2;
          }
          frame_index2 = (int)(short)fvi2 % (int)(short)frame_index2;
        }
      }
      m2 = 0;
      do {
        if ((int)(short)m2 < *(int *)(chi + 0x54)) {
          map2 = (char *)tag_block_get_element(chi + 0x54, (short)m2, 0xdc);
          ctype = *(short *)(chi + 0x2a);
          first_map_type_table2[0] = 0;
          first_map_type_table2[1] = 2;
          first_map_type_table2[2] = 2;
          first_map_type_table2[3] = 2;
          op_table2[0] = 1;
          op_table2[1] = 3;
          op_table2[2] = 3;
          op_table2[3] = 3;
          if ((short)m2 == 0) {
            first_map_type2 = first_map_type_table2[ctype];
          } else {
            first_map_type2 = 0;
          }
          if ((*chi & 4) != 0 && ctype != 0) {
            display_assert(
              "!TEST_FLAG(shader_transparent_chicago->shader.radiosity.flags, "
              "_shader_radiosity_FILTHY_transparent_lit_bit) || "
              "shader_transparent_chicago->chicago.type==_shader_transparent_"
              "chicago_type_2d_map",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x567, 1);
            system_exit(-1);
          }
          if (ctype < 0 || ctype > 3) {
            display_assert(
              "type>=0 && type<NUMBER_OF_SHADER_TRANSPARENT_CHICAGO_TYPES",
              "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_transparent_"
              "geometry.c",
              0x568, 1);
            system_exit(-1);
          }
          rasterizer_set_texture((short)m2, first_map_type2, 0,
                                 *(int *)(map2 + 0x78), frame_index2);
          if (first_map_type2 == 0 && (*map2 & 4) != 0) {
            colorop2 = 3;
          } else if ((short)m2 != 0) {
            colorop2 = 1;
          } else {
            colorop2 = op_table2[ctype];
          }
          if (first_map_type2 == 0 && (*map2 & 8) != 0) {
            alphaop2 = 3;
          } else if ((short)m2 != 0) {
            alphaop2 = 1;
          } else {
            alphaop2 = op_table2[ctype];
          }
          D3DDevice_SetTextureStageState((short)m2, 0xa, colorop2);
          D3DDevice_SetTextureStageState((short)m2, 0xb, alphaop2);
          D3DDevice_SetTextureStageState(
            (short)m2, 0xc, ((short)m2 != 0) ? 1 : op_table2[ctype]);
          D3DDevice_SetTextureStageState((short)m2, 0xd, 2);
          D3DDevice_SetTextureStageState((short)m2, 0xe,
                                         2 - (int)((*map2 & 1) != 0));
          D3DDevice_SetTextureStageState((short)m2, 0xf,
                                         2 - (int)((*map2 & 1) != 0));
        }
        if ((int)(short)m2 < *(int *)(chi + 0x54) &&
            ((short)m2 > 0 || *(short *)(chi + 0x2a) == 0)) {
          map2 = (char *)tag_block_get_element(chi + 0x54, (short)m2, 0xdc);
          u2 = *(float *)(map2 + 0x54);
          v2 = *(float *)(map2 + 0x58);
          if ((short)m2 == 0) {
            if ((*(unsigned char *)(chi + 0x29) & 0x40) != 0) {
              u2 = -(u2 * *(float *)(grp + 0x70));
              v2 = -(v2 * *(float *)(grp + 0x70));
            }
            if ((*(unsigned char *)(chi + 0x29) & 8) == 0) {
              u2 = u2 * *(float *)(grp + 0x3c);
              v2 = v2 * *(float *)(grp + 0x40);
            }
          } else {
            u2 = u2 * *(float *)(grp + 0x3c);
            v2 = v2 * *(float *)(grp + 0x40);
          }
          FUN_00190e10(map2 + 0xa4, *(void **)(grp + 0x6c), u2, v2,
                       *(float *)(map2 + 0x5c), *(float *)(map2 + 0x60),
                       *(float *)(map2 + 0x64), *(float *)0x5a5e18,
                       &anim_out2[(short)m2 * 8],
                       &anim_out2[(short)m2 * 8 + 4]);
        } else if ((int)(short)m2 < *(int *)(chi + 0x54) &&
                   (*(unsigned char *)(chi + 0x29) & 8) != 0) {
          anim_out2[(short)m2 * 8] = *(float *)0x5a5c64;
          anim_out2[(short)m2 * 8 + 1] = *(float *)0x5a5c68;
          anim_out2[(short)m2 * 8 + 2] = *(float *)0x5a5c6c;
          anim_out2[(short)m2 * 8 + 4] = *(float *)0x5a5c70;
          anim_out2[(short)m2 * 8 + 5] = *(float *)0x5a5c74;
          anim_out2[(short)m2 * 8 + 6] = *(float *)0x5a5c78;
          anim_out2[(short)m2 * 8 + 3] = 0.0f;
          anim_out2[(short)m2 * 8 + 7] = 0.0f;
        } else {
          anim_out2[(short)m2 * 8] = 1.0f;
          anim_out2[(short)m2 * 8 + 1] = 0.0f;
          anim_out2[(short)m2 * 8 + 2] = 0.0f;
          anim_out2[(short)m2 * 8 + 4] = 0.0f;
          anim_out2[(short)m2 * 8 + 5] = 1.0f;
          anim_out2[(short)m2 * 8 + 6] = 0.0f;
          anim_out2[(short)m2 * 8 + 3] = 0.0f;
          anim_out2[(short)m2 * 8 + 7] = 0.0f;
        }
        m2 = m2 + 1;
      } while ((short)m2 < 4);
      D3DDevice_SetVertexShaderConstant(-0x51, anim_out2, 8);
      if (success == 0) {
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__TEXANIM_OFFSET, "
                     "vsh_constants__texanim, VSH_CONSTANTS__TEXANIM_COUNT)");
        success = 0;
      } else {
        ok2 = FUN_0017bca0(*(void **)(grp + 0xc), (void *)0x5a5ac0);
        success = 1;
        if (ok2 == 0) {
          success = 0;
        }
      }
      if (*(char *)0x3256d4 == 0) {
        goto set_shader_and_draw;
      }
      nstages2 = *(short *)(chi + 0x54);
      if ((*grp & 0x10) != 0 && *(short *)(chi + 0x2c) == 0) {
        t2 = -(plane3d_distance_to_point((float *)0x5a5dc8, (float *)0x5a5bc8) /
               *(float *)0x5a5dec);
        if (t2 < *(float *)0x2533c0) {
          t2 = 0.0f;
        } else if (t2 > *(float *)0x2533c8) {
          t2 = 1.0f;
        }
        ((uint32_t *)0x5a5ae8)[nstages2] = real_a_rgb_color_to_pixel32(
          *(float *)0x5a5de4 * t2, (float *)0x5a5dd8);
        *(uint32_t *)(0x5a5b48 + nstages2 * 4) = 0x310c1101;
        *(uint32_t *)(0x5a5b74 + nstages2 * 4) = 0xc00;
        goto set_shader_and_draw;
      }
      fade_consts2[0] = 0.0f;
      fade_consts2[1] = 0.0f;
      fade_consts2[2] = 0.0f;
      fade_consts2[3] = 0.0f;
      fade_consts2[4] = 0.0f;
      fade_consts2[5] = 0.0f;
      fade_consts2[6] = 0.0f;
      fade_consts2[7] = 0.0f;
      fade_consts2[8] = 0.0f;
      fade_consts2[9] = 0.0f;
      fade_consts2[10] = 1.0f;
      fade_consts2[11] = 0.0f;
      if (*(short *)(grp + 0x14) == 1 &&
          (*(unsigned char *)(chi + 0x60) & 1) == 0) {
        t2 = *(float *)0x2533c8 - *(float *)(grp + 0x18);
        if (t2 < *(float *)0x2533c0) {
          fade_consts2[10] = 0.0f;
        } else if (t2 > *(float *)0x2533c8) {
          fade_consts2[10] = 1.0f;
        } else {
          fade_consts2[10] = t2;
        }
      }
      if (*(short *)(chi + 0x30) > 0 && *(int *)(grp + 0x6c) != 0 &&
          *(int *)(*(int *)(grp + 0x6c) + 4) != 0) {
        fade_consts2[10] =
          fade_consts2[10] * *(float *)(*(int *)(*(int *)(grp + 0x6c) + 4) - 4 +
                                        *(short *)(chi + 0x30) * 4);
      }
      D3DDevice_SetVertexShaderConstant(-0x54, fade_consts2, 3);
      if (success != 0) {
        success = 1;
      } else {
        success = 0;
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__TEXSCALE_OFFSET, "
                     "vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT)");
      }
      if (*(short *)(chi + 0x2e) == 0) {
        fade_mode_value2 = 0x14;
      } else if (*(short *)(chi + 0x2e) == 1) {
        fade_mode_value2 = 0x15;
      } else {
        if (*(short *)(chi + 0x2e) != 2) {
          display_assert("### ERROR unsupported framebuffer fade mode",
                         "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                         "transparent_geometry.c",
                         0x603, 1);
          system_exit(-1);
        }
        fade_mode_value2 = 5;
      }
      switch (*(short *)(chi + 0x2c)) {
      case 0:
        *(uint32_t *)(0x5a5ac0 + nstages2 * 4) = (fade_mode_value2 | 0x1c00)
                                                 << 0x10;
        *(uint32_t *)(0x5a5b28 + nstages2 * 4) = 0xc00;
        break;
      case 1:
      case 5:
        blendrow2 =
          (fade_mode_value2 ^ 0x20) | fade_mode_value2 << 0x10 | 0xc002000;
        *(uint32_t *)(0x5a5b48 + nstages2 * 4) = blendrow2;
        *(uint32_t *)(0x5a5b74 + nstages2 * 4) = 0xc00;
        break;
      case 2:
        blendrow2 =
          (fade_mode_value2 ^ 0x20) | fade_mode_value2 << 0x10 | 0xc00a000;
        *(uint32_t *)(0x5a5b48 + nstages2 * 4) = blendrow2;
        *(uint32_t *)(0x5a5b74 + nstages2 * 4) = 0xc00;
        break;
      case 3:
      case 4:
      case 6:
        *(uint32_t *)(0x5a5b48 + nstages2 * 4) = (fade_mode_value2 | 0xc00)
                                                 << 0x10;
        *(uint32_t *)(0x5a5b74 + nstages2 * 4) = 0xc00;
        break;
      case 7:
        *(uint32_t *)(0x5a5ac0 + nstages2 * 4) = (fade_mode_value2 | 0x1c00)
                                                 << 0x10;
        *(uint32_t *)(0x5a5b28 + nstages2 * 4) = 0xc00;
        *(uint32_t *)(0x5a5b48 + nstages2 * 4) = (fade_mode_value2 | 0xc00)
                                                 << 0x10;
        *(uint32_t *)(0x5a5b74 + nstages2 * 4) = 0xc00;
        break;
      default:
        display_assert("### ERROR unsupported framebuffer blend function",
                       "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                       "transparent_geometry.c",
                       0x622, 1);
        system_exit(-1);
      }
      goto set_shader_and_draw;
    }

    case 7:
      FUN_00179de0(grp);
      break;
    case 8: {
      /* shader_transparent_glass */
      char *gls;
      short reflection_type;
      float glass_consts[12]; /* diffuse [EBP-0x280] */
      float refl_consts[12]; /* reflection [EBP-0x2b0] */
      float bump_consts[12]; /* bump/specular [EBP-0x220] */
      float bump_color[3]; /* [EBP-0x7c] */
      float bc;

      gls = (char *)FUN_001906b0(sh, 8);
      reflection_type = *(short *)(gls + 0x8a);
      if (reflection_type == 2) {
        if (*(char *)0x5a5bc4 == 0 || *(short *)0x5a5bc0 != 0) {
          break;
        }
      } else if (reflection_type == 0 &&
                 ((*(unsigned char *)(gls + 0x28) & 8) != 0 ||
                  *(int *)(gls + 0xcc) == -1)) {
        reflection_type = 1;
      }
      if (*(int *)(gls + 0x70) != -1 ||
          *(float *)(gls + 0x54) != *(float *)0x2533c0 ||
          *(float *)(gls + 0x58) != *(float *)0x2533c0 ||
          *(float *)(gls + 0x5c) != *(float *)0x2533c0) {
        /* diffuse pass */
        rasterizer_set_texture(0, 0, 1, *(int *)(gls + 0x70),
                               *(unsigned short *)(grp + 0x10));
        SetTextureStageStateSmart(0, 0xa, 1);
        SetTextureStageStateSmart(0, 0xb, 1);
        SetTextureStageStateSmart(0, 0xd, 2);
        SetTextureStageStateSmart(0, 0xe, 2);
        SetTextureStageStateSmart(0, 0xf, 2);
        SetRenderStateSmart(
          0x7f,
          (int)((-(unsigned int)((*(unsigned char *)(gls + 0x28) & 4) != 0) &
                 0xfffff6ff) +
                0x901));
        SetRenderStateSmart(0x43, 0x10101);
        SetRenderStateSmart(0x3b, 1);
        SetRenderStateSmart(0x3e, 0);
        SetRenderStateSmart(0x3f, 0x300);
        SetRenderStateSmart(0x4a, 0x8006);
        SetRenderStateSmart(0x3c, 1);
        SetRenderStateSmart(0x3d, 0);
        FUN_00178b40(0x2e, vertex_type, permutation);
        glass_consts[0] = *(float *)(grp + 0x3c) * *(float *)(gls + 0x60);
        glass_consts[1] = *(float *)(grp + 0x40) * *(float *)(gls + 0x60);
        glass_consts[2] = 1.0f;
        glass_consts[3] = 1.0f;
        glass_consts[4] = 0.0f;
        glass_consts[5] = 0.0f;
        glass_consts[6] = 0.0f;
        glass_consts[7] = 0.0f;
        glass_consts[8] = 0.0f;
        glass_consts[9] = 0.0f;
        glass_consts[10] = 0.0f;
        glass_consts[11] = 0.0f;
        D3DDevice_SetVertexShaderConstant(-0x54, glass_consts, 3);
        if (success != 0) {
          success = 1;
        } else {
          success = 0;
          FUN_00167ff0(
            0, "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, "
               "VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, "
               "VSH_CONSTANTS__TEXSCALE_COUNT)");
        }
        csmemset((void *)0x5a5ac0, 0, 0xf0);
        *(uint32_t *)0x5a5b98 = 1;
        *(uint32_t *)0x5a5b94 = 1;
        *(uint32_t *)0x5a5ae8 = FUN_000d1dd0((float *)(gls + 0x54));
        *(uint32_t *)0x5a5b48 = 0x8010000;
        *(uint32_t *)0x5a5b74 = 0xc0;
        if (*(short *)(grp + 0x14) == 1) {
          *(uint32_t *)0x5a5b08 = FUN_00159070(*(float *)(grp + 0x18));
          *(uint32_t *)0x5a5ac0 = 0x14320000;
          *(uint32_t *)0x5a5b28 = 0x40;
        }
        *(uint32_t *)0x5a5ae0 = 0x140c2000;
        *(uint32_t *)0x5a5ae4 = 0x1400;
        rasterizer_set_pixel_shader((void *)0x5a5ac0);
        FUN_00174510(grp, 0);
      }
      if ((*(float *)(gls + 0x8c) > *(float *)0x2533c0 ||
           *(float *)(gls + 0x9c) > *(float *)0x2533c0) &&
          (*(int *)(gls + 0xb8) != -1 || reflection_type == 2)) {
        /* reflection pass */
        if (reflection_type < 0 || reflection_type > 2) {
          display_assert("reflection_type>=0 && "
                         "reflection_type<NUMBER_OF_SHADER_TRANSPARENT_GLASS_"
                         "REFLECTION_TYPES",
                         "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                         "transparent_geometry.c",
                         0x69e, 1);
          system_exit(-1);
        }
        rasterizer_set_texture(0, 0, 3, *(int *)(gls + 0xcc),
                               *(unsigned short *)(grp + 0x10));
        SetTextureStageStateSmart(0, 0xa, 1);
        SetTextureStageStateSmart(0, 0xb, 1);
        SetTextureStageStateSmart(0, 0xd, 2);
        SetTextureStageStateSmart(0, 0xe, 2);
        SetTextureStageStateSmart(0, 0xf, 2);
        rasterizer_set_texture_direct(1, *(int *)(*(int *)0x476204 + 0x1c), 0);
        SetTextureStageStateSmart(1, 0xa, 3);
        SetTextureStageStateSmart(1, 0xb, 3);
        SetTextureStageStateSmart(1, 0xc, 3);
        SetTextureStageStateSmart(1, 0xd, 2);
        SetTextureStageStateSmart(1, 0xe, 1);
        SetTextureStageStateSmart(1, 0xf, 1);
        rasterizer_set_texture_direct(2, *(int *)(*(int *)0x476204 + 0x1c), 0);
        SetTextureStageStateSmart(2, 0xa, 3);
        SetTextureStageStateSmart(2, 0xb, 3);
        SetTextureStageStateSmart(2, 0xc, 3);
        SetTextureStageStateSmart(2, 0xd, 2);
        SetTextureStageStateSmart(2, 0xe, 1);
        SetTextureStageStateSmart(2, 0xf, 1);
        if (reflection_type == 2) {
          FUN_001584f0(3, 1, 0);
          SetTextureStageStateSmart(3, 0xa, 3);
          SetTextureStageStateSmart(3, 0xb, 3);
          SetTextureStageStateSmart(3, 0xd, 2);
          SetTextureStageStateSmart(3, 0xe, 2);
          SetTextureStageStateSmart(3, 0xf, 1);
        } else {
          rasterizer_set_texture(3, 2, 0, *(int *)(gls + 0xb8),
                                 *(unsigned short *)(grp + 0x10));
          SetTextureStageStateSmart(3, 0xa, 3);
          SetTextureStageStateSmart(3, 0xb, 3);
          SetTextureStageStateSmart(3, 0xc, 3);
          SetTextureStageStateSmart(3, 0xd, 2);
          SetTextureStageStateSmart(3, 0xe, 2);
          SetTextureStageStateSmart(3, 0xf, 2);
        }
        SetRenderStateSmart(
          0x7f,
          (int)((-(unsigned int)((*(unsigned char *)(gls + 0x28) & 4) != 0) &
                 0xfffff6ff) +
                0x901));
        SetRenderStateSmart(0x43, 0x10101);
        SetRenderStateSmart(0x3b, 1);
        SetRenderStateSmart(0x3e, 0x302);
        SetRenderStateSmart(0x3f, 1);
        SetRenderStateSmart(0x4a, 0x8006);
        SetRenderStateSmart(0x3c, 0);
        FUN_00178b40(0x2b, vertex_type, reflection_type);
        refl_consts[0] = *(float *)(grp + 0x3c) * *(float *)(gls + 0xbc);
        refl_consts[1] = *(float *)(grp + 0x40) * *(float *)(gls + 0xbc);
        refl_consts[2] = 320.0f;
        refl_consts[3] = 240.0f;
        refl_consts[4] = 0.0f;
        refl_consts[5] = 0.0f;
        refl_consts[6] = 0.0f;
        refl_consts[7] = 0.0f;
        refl_consts[8] = 0.0f;
        refl_consts[9] = 0.0f;
        refl_consts[10] = 0.0f;
        refl_consts[11] = 0.0f;
        D3DDevice_SetVertexShaderConstant(-0x54, refl_consts, 3);
        if (success != 0) {
          success = 1;
        } else {
          success = 0;
          FUN_00167ff0(
            0, "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, "
               "VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, "
               "VSH_CONSTANTS__TEXSCALE_COUNT)");
        }
        csmemset((void *)0x5a5ac0, 0, 0xf0);
        if (reflection_type == 0) {
          *(uint32_t *)0x5a5b98 = 0x62e21;
          *(uint32_t *)0x5a5ba0 = 0;
          *(uint32_t *)0x5a5b9c = 0x111;
        } else if (reflection_type == 1) {
          *(uint32_t *)0x5a5b98 = 0x18c61;
        } else {
          if (reflection_type != 2) {
            display_assert("### ERROR unsupported reflection type",
                           "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_"
                           "xbox_transparent_geometry.c",
                           0x707, 1);
            system_exit(-1);
          }
          *(uint32_t *)0x5a5b98 = 0x8c61;
        }
        *(uint32_t *)0x5a5b94 = 0x11005;
        if (reflection_type != 0 && *(int *)(gls + 0xcc) != -1) {
          *(uint32_t *)0x5a5b48 = 0x49480b0b;
        } else {
          bc = *(float *)0x253398 - *(float *)0x5a5bd4 * *(float *)0x253398;
          if (bc < *(float *)0x2533c0) {
            bump_color[0] = 0.0f;
          } else if (bc > *(float *)0x2533c8) {
            bump_color[0] = 1.0f;
          } else {
            bump_color[0] = bc;
          }
          bc = *(float *)0x253398 - *(float *)0x5a5bd8 * *(float *)0x253398;
          if (bc < *(float *)0x2533c0) {
            bump_color[1] = 0.0f;
          } else if (bc > *(float *)0x2533c8) {
            bump_color[1] = 1.0f;
          } else {
            bump_color[1] = bc;
          }
          bc = *(float *)0x253398 - *(float *)0x5a5bdc * *(float *)0x253398;
          if (bc < *(float *)0x2533c0) {
            bump_color[2] = 0.0f;
          } else if (bc > *(float *)0x2533c8) {
            bump_color[2] = 1.0f;
          } else {
            bump_color[2] = bc;
          }
          *(uint32_t *)0x5a5ae8 = FUN_000d1dd0(bump_color);
          *(uint32_t *)0x5a5b48 = 0x4a410b0b;
        }
        *(uint32_t *)0x5a5b74 = 0x20cd;
        *(uint32_t *)0x5a5b4c = 0xc0c0d0d;
        *(uint32_t *)0x5a5b78 = 0xcd;
        if (*(short *)(grp + 0x14) == 1) {
          *(uint32_t *)0x5a5b0c = FUN_00159070(*(float *)(grp + 0x18));
          *(uint32_t *)0x5a5ac4 = 0x14320000;
          *(uint32_t *)0x5a5b2c = 0x40;
        }
        *(uint32_t *)0x5a5b50 = 0xc0c0d0d;
        *(uint32_t *)0x5a5b7c = 0xd;
        *(uint32_t *)0x5a5af4 = FUN_000d1c90((float *)(gls + 0x8c));
        *(uint32_t *)0x5a5b14 = FUN_000d1c90((float *)(gls + 0x9c));
        *(uint32_t *)0x5a5b34 = 0xc00;
        *(uint32_t *)0x5a5b80 = 0xc00;
        *(uint32_t *)0x5a5b84 = 0xc00;
        *(uint32_t *)0x5a5acc = 0x2c120c11;
        *(uint32_t *)0x5a5b54 = 0x2c020c01;
        *(uint32_t *)0x5a5b58 = 0x2c0d0c0b;
        *(uint32_t *)0x5a5ae0 = 0xc0f0000;
        *(uint32_t *)0x5a5ae4 =
          ((-(unsigned int)((*(unsigned char *)(gls + 0x28) & 8) != 0) &
            0xfffffff4) +
           0x14) *
            0x10000 |
          0x1c002000;
        rasterizer_set_pixel_shader((void *)0x5a5ac0);
        FUN_00174510(grp, 0);
      }
      if (*(int *)(gls + 0x164) != -1 || *(int *)(gls + 0x178) != -1) {
        /* bump/specular pass */
        rasterizer_set_texture(0, 0, 1, *(int *)(gls + 0x164),
                               *(unsigned short *)(grp + 0x10));
        SetTextureStageStateSmart(0, 0xa, 1);
        SetTextureStageStateSmart(0, 0xb, 1);
        SetTextureStageStateSmart(0, 0xd, 2);
        SetTextureStageStateSmart(0, 0xe, 2);
        SetTextureStageStateSmart(0, 0xf, 2);
        rasterizer_set_texture(1, 0, 2, *(int *)(gls + 0x178),
                               *(unsigned short *)(grp + 0x10));
        SetTextureStageStateSmart(1, 0xa, 1);
        SetTextureStageStateSmart(1, 0xb, 1);
        SetTextureStageStateSmart(1, 0xd, 2);
        SetTextureStageStateSmart(1, 0xe, 2);
        SetTextureStageStateSmart(1, 0xf, 2);
        SetRenderStateSmart(
          0x7f,
          (int)((-(unsigned int)((*(unsigned char *)(gls + 0x28) & 4) != 0) &
                 0xfffff6ff) +
                0x901));
        SetRenderStateSmart(0x43, 0x10101);
        SetRenderStateSmart(0x3b, 1);
        SetRenderStateSmart(0x3e, 0x302);
        SetRenderStateSmart(0x3f, 0x303);
        SetRenderStateSmart(0x4a, 0x8006);
        SetRenderStateSmart(0x3c, 1);
        SetRenderStateSmart(0x3d, 0);
        if (*(int *)(grp + 0x5c) == 0) {
          rasterizer_set_texture(2, 0, 0, -1, 0);
          SetTextureStageStateSmart(2, 0xa, 3);
          SetTextureStageStateSmart(2, 0xb, 3);
          SetTextureStageStateSmart(2, 0xd, 2);
          SetTextureStageStateSmart(2, 0xe, 2);
          SetTextureStageStateSmart(2, 0xf, 2);
        } else {
          rasterizer_set_texture_bitmap_data(2, *(void **)(grp + 0x5c));
          SetTextureStageStateSmart(2, 0xa, 3);
          SetTextureStageStateSmart(2, 0xb, 3);
          SetTextureStageStateSmart(2, 0xd, 2);
          SetTextureStageStateSmart(2, 0xe, 2);
          SetTextureStageStateSmart(2, 0xf, 2);
        }
        FUN_00178b40(0x19, vertex_type, permutation);
        bump_consts[0] = *(float *)(gls + 0x154) * *(float *)(grp + 0x3c);
        bump_consts[1] = *(float *)(gls + 0x154) * *(float *)(grp + 0x40);
        bump_consts[2] = *(float *)(gls + 0x168) * *(float *)(grp + 0x3c);
        bump_consts[3] = *(float *)(gls + 0x168) * *(float *)(grp + 0x40);
        bump_consts[4] = 0.0f;
        bump_consts[5] = 0.0f;
        bump_consts[6] = 0.0f;
        bump_consts[7] = 0.0f;
        bump_consts[8] = 0.0f;
        bump_consts[9] = 0.0f;
        bump_consts[10] = 0.0f;
        bump_consts[11] = 0.0f;
        D3DDevice_SetVertexShaderConstant(-0x54, bump_consts, 3);
        if (success != 0) {
          success = 1;
        } else {
          success = 0;
          FUN_00167ff0(
            0, "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_device, "
               "VSH_CONSTANTS__TEXSCALE_OFFSET, vsh_constants__texscale, "
               "VSH_CONSTANTS__TEXSCALE_COUNT)");
        }
        csmemset((void *)0x5a5ac0, 0, 0xf0);
        *(uint32_t *)0x5a5b98 = 0x421;
        *(uint32_t *)0x5a5b94 = 3;
        *(uint32_t *)0x5a5ac0 = 0x18190000;
        *(uint32_t *)0x5a5b28 = 0xc0;
        *(uint32_t *)0x5a5b48 = 0x8090000;
        *(uint32_t *)0x5a5b74 = 0x100c0;
        *(uint32_t *)0x5a5ac4 = 0x1c140000;
        *(uint32_t *)0x5a5b2c = 0xc0;
        *(uint32_t *)0x5a5b4c = 0xa200420;
        *(uint32_t *)0x5a5b78 = 0xd00;
        *(uint32_t *)0x5a5b50 = 0xc0d0000;
        *(uint32_t *)0x5a5b7c = 0xc0;
        *(uint32_t *)0x5a5ae0 = 0xc;
        *(uint32_t *)0x5a5ae4 = 0x1c00;
        rasterizer_set_pixel_shader((void *)0x5a5ac0);
        FUN_00174510(grp, *(int *)(grp + 0x5c) != 0);
      }
      break;
    }

    case 9: {
      /* shader_transparent_meter */
      char *met;
      float brightness; /* [EBP-0x3c] */
      float power; /* [EBP-0x44] */
      float gradient; /* [EBP-0x4c] */
      float met_alpha; /* [EBP-0x48] */
      float flash; /* rides FPU stack in original */
      float tint[3]; /* [EBP-0x150] */
      float flash_color[3]; /* [EBP-0x28] */
      float inv_flash;
      float x9;
      float t9;
      short src;
      int *ext9;
      uint32_t px1;
      uint32_t px2;
      uint32_t px3;
      uint32_t px4;
      uint32_t px_final;
      float px_final_alpha;
      float *px_final_color;
      float px3_alpha;
      float meter_consts[12]; /* [EBP-0x250] */

      met = (char *)FUN_001906b0(sh, 9);
      brightness = 1.0f;
      power = 1.0f;
      gradient = 1.0f;
      met_alpha = 1.0f;
      flash = 1.0f;
      if (*(int *)(grp + 0x6c) != 0 &&
          *(int *)(*(int *)(grp + 0x6c) + 4) != 0) {
        ext9 = (int *)*(int *)(*(int *)(grp + 0x6c) + 4);
        src = *(short *)(met + 0xd8);
        if (src > 0 && src < 5) {
          brightness = *((float *)ext9 + (src - 1));
        }
        src = *(short *)(met + 0xda);
        if (src > 0 && src < 5) {
          power = *((float *)ext9 + (src - 1));
        }
        src = *(short *)(met + 0xdc);
        if (src > 0 && src < 5) {
          gradient = *((float *)ext9 + (src - 1));
        }
        src = *(short *)(met + 0xde);
        if (src > 0 && src < 5) {
          flash = *((float *)ext9 + (src - 1));
        }
        src = *(short *)(met + 0xe0);
        if (src > 0 && src < 5) {
          met_alpha = *((float *)ext9 + (src - 1));
        }
      }
      if (*(char *)0x3256c3 != 0) {
        /* rasterizer_debug_meters override */
        t9 = FUN_0010a5e0(2, *(float *)0x5a5e18 / *(float *)0x325724);
        if (*(float *)0x325728 >= *(float *)0x2533c0) {
          brightness = *(float *)0x325728;
        } else {
          brightness = t9;
        }
        if (*(float *)0x32572c >= *(float *)0x2533c0) {
          power = *(float *)0x32572c;
        } else {
          power = t9;
        }
        if (*(float *)0x325730 >= *(float *)0x2533c0) {
          gradient = *(float *)0x325730;
        } else {
          gradient = t9;
        }
        if (*(float *)0x325734 >= *(float *)0x2533c0) {
          flash = *(float *)0x325734;
        } else {
          flash = t9;
        }
        if (*(float *)0x325738 >= *(float *)0x2533c0) {
          met_alpha = *(float *)0x325738;
        } else {
          met_alpha = t9;
        }
      }
      tint[0] = power * *(float *)(met + 0xa0);
      tint[1] = power * *(float *)(met + 0xa4);
      tint[2] = power * *(float *)(met + 0xa8);
      x9 = flash * *(float *)0x253f78;
      if (x9 <= *(float *)0x2533c8) {
        x9 = 1.0f;
      }
      inv_flash = *(float *)0x2533c8 / x9;
      if ((*(unsigned char *)(met + 0x28) & 8) != 0) {
        flash_color[0] = brightness * *(float *)(met + 0xac);
        flash_color[1] = brightness * *(float *)(met + 0xb0);
        flash_color[2] = brightness * *(float *)(met + 0xb4);
        px3_alpha = *(float *)(met + 0xbc);
        px1 = real_a_rgb_color_to_pixel32(gradient, (float *)(met + 0x7c));
        px2 = real_a_rgb_color_to_pixel32(inv_flash, (float *)(met + 0x88));
        px3 = real_a_rgb_color_to_pixel32(px3_alpha, (float *)(met + 0x94));
        px4 = real_a_rgb_color_to_pixel32(met_alpha, tint);
        px_final_alpha = *(float *)(met + 0xb8);
        px_final_color = flash_color;
      } else {
        px1 = real_a_rgb_color_to_pixel32(gradient, (float *)(met + 0x7c));
        px2 = real_a_rgb_color_to_pixel32(inv_flash, (float *)(met + 0x88));
        px3 = real_a_rgb_color_to_pixel32(*(float *)0x2533c0,
                                          (float *)(met + 0x94));
        px4 = real_a_rgb_color_to_pixel32(met_alpha, tint);
        px_final_alpha = brightness;
        px_final_color = (float *)(met + 0xac);
      }
      px_final = real_a_rgb_color_to_pixel32(px_final_alpha, px_final_color);
      rasterizer_set_texture(0, 0, 1, *(int *)(met + 0x58),
                             *(unsigned short *)(grp + 0x10));
      SetTextureStageStateSmart(0, 0xa, 1);
      SetTextureStageStateSmart(0, 0xb, 1);
      SetTextureStageStateSmart(
        0, 0xd, 2 - (int)((*(unsigned char *)(met + 0x28) & 0x10) != 0));
      SetTextureStageStateSmart(
        0, 0xe, 2 - (int)((*(unsigned char *)(met + 0x28) & 0x10) != 0));
      SetTextureStageStateSmart(0, 0xf, 2);
      SetRenderStateSmart(
        0x7f,
        (int)((-(unsigned int)((*(unsigned char *)(met + 0x28) & 2) != 0) &
               0xfffff6ff) +
              0x901));
      SetRenderStateSmart(0x43, 0x10101);
      SetRenderStateSmart(0x3b, 1);
      SetRenderStateSmart(
        0x3e, (int)((~((unsigned int)*(unsigned char *)(met + 0x28) >> 2) & 2) |
                    0x8001));
      SetRenderStateSmart(
        0x3f,
        (int)((-(unsigned int)((*(unsigned char *)(met + 0x28) & 8) != 0) &
               0xffff8301) +
              0x8001));
      SetRenderStateSmart(0x4b, px_final);
      SetRenderStateSmart(0x4a, 0x8006);
      SetRenderStateSmart(0x3c, 0);
      FUN_00178b40(0x16, vertex_type, permutation);
      meter_consts[0] = 1.0f;
      meter_consts[1] = 1.0f;
      meter_consts[2] = 1.0f;
      meter_consts[3] = 1.0f;
      meter_consts[4] = *(float *)(grp + 0x3c);
      meter_consts[5] = 0.0f;
      meter_consts[6] = 0.0f;
      meter_consts[7] = 0.0f;
      meter_consts[8] = 0.0f;
      meter_consts[9] = *(float *)(grp + 0x40);
      meter_consts[10] = 0.0f;
      meter_consts[11] = 0.0f;
      D3DDevice_SetVertexShaderConstant(-0x54, meter_consts, 3);
      if (success != 0) {
        success = 1;
      } else {
        success = 0;
        FUN_00167ff0(0,
                     "IDirect3DDevice8_SetVertexShaderConstant(global_d3d_"
                     "device, VSH_CONSTANTS__TEXSCALE_OFFSET, "
                     "vsh_constants__texscale, VSH_CONSTANTS__TEXSCALE_COUNT)");
      }
      csmemset((void *)0x5a5ac0, 0, 0xf0);
      SetTextureStageStateSmart(0, 0x15, 4);
      *(uint32_t *)0x5a5b28 = 0x20c00;
      *(uint32_t *)0x5a5b74 = 0x20c00;
      *(uint32_t *)0x5a5ae8 = px4;
      *(uint32_t *)0x5a5b10 = px4;
      *(uint32_t *)0x5a5b08 = px2;
      *(uint32_t *)0x5a5b0c = px2;
      *(uint32_t *)0x5a5aec = px1;
      *(uint32_t *)0x5a5af0 = px1;
      *(uint32_t *)0x5a5b98 = 1;
      *(uint32_t *)0x5a5b94 = 0x11104;
      *(uint32_t *)0x5a5ac0 = 0x12081208;
      *(uint32_t *)0x5a5b48 = 0x1120e820;
      *(uint32_t *)0x5a5ac4 = 0x6c200000;
      *(uint32_t *)0x5a5b2c = 0xc0;
      *(uint32_t *)0x5a5b4c = 0x3c011c02;
      *(uint32_t *)0x5a5b78 = 0xc00;
      *(uint32_t *)0x5a5ac8 = 0x820b120;
      *(uint32_t *)0x5a5b30 = 0xc00;
      *(uint32_t *)0x5a5af4 = px3;
      *(uint32_t *)0x5a5b34 = 0x4c00;
      *(uint32_t *)0x5a5b80 = 0x4c00;
      *(uint32_t *)0x5a5b7c = 0xc00;
      *(uint32_t *)0x5a5b50 =
        ((-(unsigned int)((*(unsigned char *)(met + 0x28) & 4) != 0) & 0xe0) +
         2) |
        0xc201c00;
      *(uint32_t *)0x5a5b14 = px_final;
      *(uint32_t *)0x5a5acc = 0x12201120;
      *(uint32_t *)0x5a5b54 = 0xc200120;
      *(uint32_t *)0x5a5ae0 = 0xc180000;
      *(uint32_t *)0x5a5ae4 = 0x1c00;
      if (*(char *)0x3256c3 != 0 && *(short *)0x3256ea != 0) {
        csmemset((void *)0x5a5ac0, 0, 0xf0);
        SetTextureStageStateSmart(0, 0x15, 0);
        SetRenderStateSmart(0x3b, 0);
        *(uint32_t *)0x5a5b98 = 1;
        *(uint32_t *)0x5a5b94 = 1;
        *(uint32_t *)0x5a5ae0 = ((*(short *)0x3256ea < 2) - 1 & 0x10) + 8;
      }
      rasterizer_set_pixel_shader((void *)0x5a5ac0);
      FUN_00174510(grp, 0);
      SetTextureStageStateSmart(0, 0x15, 0);
      break;
    }

    case 10:
      FUN_0016eef0(grp);
      break;

    default:
      error(2, "### ERROR unsupported shader type");
      success = 0;
      break;
    }

    goto next_pass;

  set_shader_and_draw:
    /* shared tail for shader types 1/5/6 (0x17744d) */
    rasterizer_set_pixel_shader((void *)0x5a5ac0);
    FUN_00174510(grp, 0);

  next_pass:
    pass = pass + 1;
  } while ((short)pass < 2);

  if ((*grp & 8) != 0 && *(short *)0x5a5bc0 == 0) {
    rasterizer_set_frustum_z(*(float *)0x2533c0, *(float *)0x2533c0);
  }
  if ((char)*grp < 0 && *(short *)(grp + 0x14) == 1) {
    rasterizer_set_frustum_z(*(float *)0x2533c0, *(float *)0x2533c0);
  }

tail:
  if ((char)dirty == 0) {
    *(int *)0x47e4b8 = *(int *)(grp + 8);
  }
  if (*(short *)(grp + 0x96) != -1) {
    rasterizer_transparent_geometry_group_draw(
      rasterizer_transparent_geometry_group_get(*(short *)(grp + 0x96)), dirty);
  }
  if (draw_secondary != 0) {
    sec = (char *)rasterizer_secondary_geometry_groups_get(&sec_count);
    if ((char)dirty != 0) {
      display_assert("!dirty",
                     "c:\\halo\\SOURCE\\rasterizer\\xbox\\rasterizer_xbox_"
                     "transparent_geometry.c",
                     0x8e0, 1);
      system_exit(-1);
    }
    for (si = 0; si < sec_count; si++) {
      rec = sec + (int)si * 0xa0;
      if (*(int *)(rec + 0x98) == *(int *)(grp + 8) &&
          *(short *)(rec + 0x14) == 1) {
        rasterizer_transparent_geometry_group_draw(rec, 1);
        if (*(short *)0x3256ea != 0) {
          *(char *)0x47e4c0 = 1;
        }
      }
    }
  }
  if (success == 0) {
    error(2, "### ERROR rasterizer_transparent_geometry_group_draw failed");
  }
}


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

/* FUN_0016f480 (0x16f480) — readable C lift from XBE leaf. */
void FUN_0016f480(const char *message, int16_t profile_index, char condition)
{
  extern char DAT_00294af0[];
  extern char DAT_002a3ca4[];
  extern char DAT_002a3c7c[];
  extern char DAT_002a3c5c[];

  if (message == 0) {
    display_assert(DAT_00294af0, DAT_002a3ca4, 0x3c, true);
    system_exit(-1);
  }
  if (condition != 0) {
    return;
  }
  if (*(short *)0x47e468 >= 3) {
    return;
  }
  if (profile_index != -1) {
    error(2, DAT_002a3c7c, (int)profile_index, message);
  } else {
    error(2, DAT_002a3c5c, -1, message);
  }
  *(short *)0x47e468 = (short)(*(short *)0x47e468 + 1);
}




/* FUN_0016f500 (0x16f500) — readable C lift. */
void FUN_0016f500(unsigned int packed)
{
  short idx;
  char high_bit;
  unsigned int counter[2];
  int off;
  unsigned int lo, hi, start_lo, start_hi;
  unsigned long long cur, start, delta;

  idx = (short)packed;
  high_bit = (char)((packed >> 31) & 1);
  if (idx < 0 || idx >= 0x1d) {
    *(unsigned short *)0x47e460 = (unsigned short)(*(unsigned short *)0x47e460 | 1);
    return;
  }

  QueryPerformanceCounter(counter);
  off = (int)idx * 8;
  if (high_bit) {
    if (*(unsigned int *)(0x47e358 + off) | *(unsigned int *)(0x47e35c + off)) {
      *(unsigned short *)0x47e460 = (unsigned short)(*(unsigned short *)0x47e460 | 2);
    }
    *(unsigned int *)(0x47e358 + off) = counter[0];
    *(unsigned int *)(0x47e35c + off) = counter[1];
    return;
  }

  if ((*(unsigned int *)(0x47e358 + off) | *(unsigned int *)(0x47e35c + off)) == 0) {
    *(unsigned short *)0x47e460 = (unsigned short)(*(unsigned short *)0x47e460 | 4);
    return;
  }

  start_lo = *(unsigned int *)(0x47e358 + off);
  start_hi = *(unsigned int *)(0x47e35c + off);
  cur = ((unsigned long long)counter[1] << 32) | counter[0];
  start = ((unsigned long long)start_hi << 32) | start_lo;
  delta = cur - start;
  *(unsigned int *)(0x47e270 + off) = (unsigned int)delta;
  *(unsigned int *)(0x47e274 + off) = (unsigned int)(delta >> 32);
  *(unsigned int *)(0x47e358 + off) = 0;
  *(unsigned int *)(0x47e35c + off) = 0;
}

/* FUN_0016f610 (0x16f610) — readable C lift. */
void FUN_0016f610(unsigned int packed)
{
  short idx;
  unsigned int counter[2];
  int off;
  unsigned int lo, hi, start_lo, start_hi;
  unsigned long long cur, start, delta;

  idx = (short)(packed >> 1);
  if (idx < 0 || idx >= 0x10)
    return;

  QueryPerformanceCounter(counter);
  if (packed & 1) {
    off = (int)idx * 8;
    lo = counter[0];
    hi = counter[1];
    start_lo = *(unsigned int *)(0x47e108 + off);
    start_hi = *(unsigned int *)(0x47e10c + off);
    *(unsigned int *)(0x47e088 + off) = lo;
    *(unsigned int *)(0x47e08c + off) = hi;
    cur = ((unsigned long long)hi << 32) | lo;
    start = ((unsigned long long)start_hi << 32) | start_lo;
    delta = cur - start;
    *(unsigned int *)(0x47e008 + off) = (unsigned int)delta;
    *(unsigned int *)(0x47e00c + off) = (unsigned int)(delta >> 32);
    *(short *)0x47e454 = idx;
  } else {
    *(unsigned int *)(0x47e108 + (int)idx * 8) = counter[0];
    *(unsigned int *)(0x47e10c + (int)idx * 8) = counter[1];
  }
}

/* FUN_0016f6c0 (0x16f6c0) — readable C lift from XBE leaf. */
char FUN_0016f6c0(void)
{
  int i;

  for (i = 0; i < 0x1d; i++) {
    *(int *)(0x47e358 + i * 8) = 0;
    *(int *)(0x47e35c + i * 8) = 0;
    *(int *)(0x47e270 + i * 8) = 0;
    *(int *)(0x47e274 + i * 8) = 0;
  }
  csmemset((void *)0x47e108, 0, 0x80);
  csmemset((void *)0x47e088, 0, 0x80);
  csmemset((void *)0x47e008, 0, 0x80);
  QueryPerformanceFrequency((void *)0x325178);
  return 1;
}




/* FUN_0016f730 (0x16f730) — readable C lift. */
void FUN_0016f730(void)
{
  unsigned char flags;
  int slot;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a3ca4, 0xc2, true);
    system_exit(-1);
  }

  flags = *(unsigned char *)0x47e460;
  if ((flags & 1) != 0 && *(short *)0x47e468 < 3) {
    error(2, (const char *)0x2a3c5c, -1, (const char *)0x2a3d08);
    *(short *)0x47e468 = (short)(*(short *)0x47e468 + 1);
  }

  flags = *(unsigned char *)0x47e460;
  if (((flags >> 1) & 1) != 0 && *(short *)0x47e468 < 3) {
    error(2, (const char *)0x2a3c5c, -1, (const char *)0x2a3cf4);
    *(short *)0x47e468 = (short)(*(short *)0x47e468 + 1);
  }

  flags = *(unsigned char *)0x47e460;
  if (((flags >> 2) & 1) != 0 && *(short *)0x47e468 < 3) {
    error(2, (const char *)0x2a3c5c, -1, (const char *)0x2a3ce0);
    *(short *)0x47e468 = (short)(*(short *)0x47e468 + 1);
  }

  *(unsigned short *)0x47e460 = 0;

  if (*(short *)0x3256ba != 3 && !*(unsigned char *)0x325704)
    return;

  slot = (int)*(short *)0x47e450 + 1;
  slot &= 0x8000000f;
  if (slot < 0)
    slot = ((slot - 1) | -16) + 1;

  *(int *)0x47e45c = 0;
  *(short *)0x325184 = 0;
  *(short *)0x325180 = (short)0xffff;
  *(int *)0x47e440 = 0;
  *(int *)0x47e444 = 0;
  *(short *)0x47e450 = (short)slot;

  D3DDevice_InsertCallback(0, (void *)(unsigned)0x16f610, (unsigned int)(slot << 1));
}

/* FUN_0016f8a0 (0x16f8a0) — readable C lift from XBE leaf. */
void FUN_0016f8a0(char decrement)
{
  extern char DAT_002a3d48[];
  extern char DAT_002a3ca4[];
  extern char DAT_002a3d2c[];

  if (decrement) {
    if (*(short *)0x47e458 <= 0) {
      display_assert(DAT_002a3d48, DAT_002a3ca4, 0xf4, true);
      system_exit(-1);
    }
    *(short *)0x47e458 = (short)(*(short *)0x47e458 - 1);
    return;
  }
  if (*(short *)0x47e458 >= 0x64) {
    display_assert(DAT_002a3d2c, DAT_002a3ca4, 0xf9, true);
    system_exit(-1);
  }
  *(short *)0x47e458 = (short)(*(short *)0x47e458 + 1);
}




/* rasterizer_initialize (0x16fb80) — readable C lift from XBE leaf. */
void *rasterizer_initialize(int16_t index)
{
  extern char DAT_002a3db8[];
  extern char DAT_002a3ca4[];

  if (index < 0 || index >= 0x1d) {
    display_assert(DAT_002a3db8, DAT_002a3ca4, 0x16b, true);
    system_exit(-1);
  }
  return *(void **)(0x325188 + (int)index * 4);
}




/* FUN_0016fbd0 (0x16fbd0) — readable C lift. */
float FUN_0016fbd0(short index)
{
  float acc;
  int i;
  unsigned int bit;
  int lo;

  acc = *(float *)0x2533c0;
  if (*(short *)0x3256ba != 3 && *(char *)0x325704 == 0)
    return acc;

  if (*(int *)0x476ab0 == 0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a3ca4, 0x177, true);
    system_exit(-1);
  }

  if (index == 0x1d) {
    for (i = 0; i < 0x1d; i++) {
      lo = *(int *)(0x47e270 + i * 8);
      acc += (float)lo;
    }
    return acc / (float)*(int *)0x325178;
  }

  if (index < 0 || index >= 0x1d) {
    display_assert((const char *)0x2a3db8, (const char *)0x2a3ca4, 0x187, true);
    system_exit(-1);
  }

  FUN_0016f480((const char *)0x2a3e40, index, (char)(*(short *)0x325180 == -1));
  bit = 1u << (int)index;
  if ((*(unsigned int *)0x47e45c & bit) == 0)
    return *(float *)0x255e94;

  lo = *(int *)(0x47e270 + (int)index * 8);
  return (float)lo / (float)*(int *)0x325178;
}


/* FUN_0016fcf0 (0x16fcf0) — readable C lift. */
int FUN_0016fcf0(short profile_index)
{
  unsigned int mask;
  int lo;
  int hi;

  if (*(short *)0x3256ba != 3 && !*(char *)0x325704)
    return 0;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a3ca4, 0x19f, true);
    system_exit(-1);
  }
  if (profile_index == 0x1d)
    return 0;
  if (profile_index < 0 || profile_index >= 0x1d) {
    display_assert((const char *)0x2a3db8, (const char *)0x2a3ca4, 0x1ae, true);
    system_exit(-1);
  }

  FUN_0016f480((const char *)0x2a3e40, profile_index, *(short *)0x325180 == -1);

  mask = 1u << (unsigned)(int)profile_index;
  if ((*(unsigned int *)0x47e45c & mask) == 0)
    return -1;

  lo = *(int *)(0x47e188 + (int)profile_index * 8);
  hi = *(int *)(0x47e18c + (int)profile_index * 8);
  if (hi < 0)
    return lo;
  if (hi > 0 || (unsigned int)lo > 0x7fffffff)
    return 0x7fffffff;
  return lo;
}


/* FUN_0016FDD0 (0x16fdd0) — readable C lift. */
void FUN_0016FDD0(void)
{
  unsigned int lo, hi;
  unsigned int neg_lo, neg_hi;
  int value;
  int idx;
  float scaled;
  int fbits;

  if (*(short *)0x3256ba != 3 && *(char *)0x325704 == 0)
    return;

  if (*(int *)0x476ab0 == 0) {
    display_assert((const char *)0x29dc40, (const char *)0x2a3ca4, 0x1c7, true);
    system_exit(-1);
  }

  lo = *(unsigned int *)0x47e440;
  hi = *(unsigned int *)0x47e444;
  {
    unsigned long long v = ((unsigned long long)hi << 32) | lo;
    unsigned long long n = 0ull - v;
    neg_lo = (unsigned int)n;
    neg_hi = (unsigned int)(n >> 32);
  }

  if ((int)neg_hi > 0 || ((int)neg_hi == 0 && neg_lo > 0x7fffffff))
    value = 0x7fffffff;
  else
    value = (int)neg_lo;

  *(int *)0x47e448 = value;
  *(int *)0x47e44c = value >> 31;

  idx = (int)*(short *)0x47e450;
  D3DDevice_InsertCallback(1, (void *)FUN_0016f610, (unsigned int)(idx + idx + 1));

  idx = (int)*(short *)0x47e454;
  scaled = (float)*(int *)(0x47e008 + idx * 8) * *(float *)0x254cb8 /
           (float)*(int *)0x325178;
  fbits = *(int *)&scaled;
  FUN_0008f810(fbits, *(int *)0x47e448);
}




/* FUN_0016FEB0 (0x16feb0) -- empty no-op.
 *
 * The entire function is a single instruction:
 *
 *   0016feb0:  c3            RET
 *
 * No prologue, no frame, no FPU, no memory access, no callees. Under the
 * cdecl `void (void)` signature in kb.json this is a release-build no-op:
 * a debug/profiling hook whose body compiled out. Called unconditionally
 * from FUN_00158f90 (rasterizer_xbox_decals.c).
 *
 * kb.json assigns 0x16feb0 to rasterizer.obj; its address neighbours here
 * are rasterizer_initialize (0x16fb80) and 0x16fec0.
 */
void FUN_0016FEB0(void)
{
}

/* FUN_0016fec0 (0x16fec0) — readable C lift (ret thunk). */
__attribute__((noinline))
void FUN_0016fec0(void)
{
  __asm__ volatile("");
}



/* FUN_001700d0 (0x1700d0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x1701af */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x1701bf */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1701cf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1701df */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1701ef */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x1701ff */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x17020f */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17021f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17022f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17023f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17024f */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x170262 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x170275 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x170288 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x17029b */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x1702ae */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x1702c1 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x1702d4 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x1702e7 */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x1702fa */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x17030d */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x170320 */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x170333 */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x170346 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x170359 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x17036c */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x17037a */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x170390 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1703a1 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x1703b2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1703c3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x1703d0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_001703f0 (0x1703f0) — readable C lift. */
int FUN_001703f0(int a, int b, int c)
{
  D3DDevice_SetVertexData2f(a, b, c);
  return 0;
}

/* FUN_00170440 (0x170440) — readable C lift (restored pre-naked). */
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


/* FUN_00170c90 (0x170c90) — readable C lift (restored pre-naked). */
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


/* FUN_00171bc0 (0x171bc0) — readable C lift (restored pre-naked). */
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


/* FUN_00172520 (0x172520) — readable C lift from XBE leaf. */
void FUN_00172520(void)
{
  FUN_0016f910(4);
}

/* FUN_00172640 (0x172640) — readable C lift. */
void FUN_00172640(void)
{
  *(unsigned int *)0x47e4b0 = 0;
}

/* FUN_00172650 (0x172650) — readable C lift. */
int FUN_00172650(int a, int b, int c)
{
  D3DDevice_SetVertexData2f(a, b, c);
  return 0;
}

/* FUN_001726a0 (0x1726a0) — readable C lift. */
void FUN_001726a0(void)
{
  if (!*(int *)0x476ab0) {
    display_assert((char *)0x29dc40, (char *)0x2a44b0, 0x233, 1);
    system_exit(-1);
  }
  if (*(short *)0x5a5bc0 != 0)
    return;
  if (!*(unsigned char *)0x3256ca)
    return;
  if (!*(unsigned char *)0x47e4b5)
    error(2, (const char *)0x2a44ec);
  if (*(unsigned char *)0x3251fc)
    return;
  FUN_00158140((int)*(unsigned short *)0x5a5bc0, 0, 0, 0, 1);
  *(unsigned char *)0x3251fc = 1;
}
/* rasterizer_window_get_fog (0x172720) — readable C lift. */
void rasterizer_window_get_fog(void)
{
  FUN_0016fa40(4);
}

/* FUN_00172730 (0x172730) — readable C lift (restored pre-naked). */
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


/* FUN_00172de0 (0x172de0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
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
  ((void(*)(void))FUN_0017ed90)();
  /* mem[0x005a54f8] = ecx */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_00173090 (0x173090) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))FUN_0015dc10)();
  /* relift: cmp word ptr [0x3256ba], 2 -> jne 0x17363b */
  /* mem[0x005a543c] = eax */
  /* mem[0x005a5438] = edx */
  rasterizer_frame_statistics_count_static_vertices();
  /* mem[0x005a5434] = ecx */
  /* cmp esi, 0x52 -> jge 0x17366b */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x173679 */
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x17368e */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x17369a */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1736a6 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1736b2 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1736be */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x1736ca */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x1736d6 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x1736e2 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x1736ee */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x1736fa */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x173706 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x173715 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x173724 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x173733 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x173742 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x173751 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x173760 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x17376f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x17377e */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x17378d */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x17379c */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x1737ab */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x1737ba */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x1737c9 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x1737d8 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x1737e7 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x1737f5 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x17380c */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x173819 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x173826 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x173833 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x173840 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  /* cmp esi, 0x52 -> jge 0x17386f */
  D3DDevice_SetRenderState_Simple(0, 0);
  /* cmp esi, 0x74 -> jge 0x173882 */
  D3DDevice_SetRenderState_Deferred(0, 0);
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x17389f */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x1738af */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x1738bf */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x1738cf */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x1738df */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x1738ef */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x1738ff */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x17390f */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17391f */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17392f */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x17393f */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x173952 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x173965 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x173978 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x17398b */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x17399e */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x1739b1 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x1739c4 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x1739d7 */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x1739ea */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x1739fd */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x173a10 */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x173a23 */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x173a36 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x173a49 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x173a5c */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x173a6a */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x173a80 */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x173a91 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x173aa2 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x173ab3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x173ac0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();
  D3DDevice_SetVertexShaderConstant(0, (void *)(uintptr_t)ecx, eax);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_00173ae0 (0x173ae0) — readable C lift. */
void FUN_00173ae0(void)
{
}



/* FUN_00173af0 (0x173af0) — readable C lift. */
int FUN_00173af0(int a, int b, int c)
{
  D3DDevice_SetVertexData2f(a, b, c);
  return 0;
}

/* FUN_00173b40 (0x173b40) — readable C lift (restored pre-naked). */
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


/* FUN_001741d0 (0x1741d0) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))D3DDevice_SetRenderState_PSTextureModes)();
  /* cmp esi, 0x75 -> jne 0x17432e */
  ((void(*)(void))D3DDevice_SetRenderState_VertexBlend)();
  /* cmp esi, 0x76 -> jne 0x17433a */
  ((void(*)(void))D3DDevice_SetRenderState_FogColor)();
  /* cmp esi, 0x77 -> jne 0x174346 */
  D3DDevice_SetRenderState_FillMode(edi);
  /* cmp esi, 0x78 -> jne 0x174352 */
  ((void(*)(void))D3DDevice_SetRenderState_BackFillMode)();
  /* cmp esi, 0x79 -> jne 0x17435e */
  ((void(*)(void))D3DDevice_SetRenderState_TwoSidedLighting)();
  /* cmp esi, 0x7a -> jne 0x17436a */
  ((void(*)(void))D3DDevice_SetRenderState_NormalizeNormals)();
  /* cmp esi, 0x7b -> jne 0x174376 */
  D3DDevice_SetRenderState_ZEnable(edi);
  /* cmp esi, 0x7c -> jne 0x174382 */
  D3DDevice_SetRenderState_StencilEnable(edi);
  /* cmp esi, 0x7d -> jne 0x17438e */
  D3DDevice_SetRenderState_StencilFail(edi);
  /* cmp esi, 0x7f -> jne 0x17439a */
  D3DDevice_SetRenderState_CullMode(edi);
  /* cmp esi, 0x7e -> jne 0x1743a6 */
  ((void(*)(void))D3DDevice_SetRenderState_FrontFace)();
  /* cmp esi, 0x80 -> jne 0x1743b5 */
  ((void(*)(void))D3DDevice_SetRenderState_TextureFactor)();
  /* cmp esi, 0x81 -> jne 0x1743c4 */
  D3DDevice_SetRenderState_ZBias(edi);
  /* cmp esi, 0x82 -> jne 0x1743d3 */
  ((void(*)(void))D3DDevice_SetRenderState_LogicOp)();
  /* cmp esi, 0x83 -> jne 0x1743e2 */
  ((void(*)(void))D3DDevice_SetRenderState_EdgeAntiAlias)();
  /* cmp esi, 0x84 -> jne 0x1743f1 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleAntiAlias)();
  /* cmp esi, 0x85 -> jne 0x174400 */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleMask)();
  /* cmp esi, 0x86 -> jne 0x17440f */
  ((void(*)(void))D3DDevice_SetRenderState_MultiSampleType)();
  /* cmp esi, 0x87 -> jne 0x17441e */
  ((void(*)(void))D3DDevice_SetRenderState_ShadowFunc)();
  /* cmp esi, 0x88 -> jne 0x17442d */
  ((void(*)(void))D3DDevice_SetRenderState_LineWidth)();
  /* cmp esi, 0x89 -> jne 0x17443c */
  ((void(*)(void))D3DDevice_SetRenderState_Dxt1NoiseEnable)();
  /* cmp esi, 0x8a -> jne 0x17444b */
  ((void(*)(void))D3DDevice_SetRenderState_YuvEnable)();
  /* cmp esi, 0x8b -> jne 0x17445a */
  ((void(*)(void))D3DDevice_SetRenderState_OcclusionCullEnable)();
  /* cmp esi, 0x8c -> jne 0x174469 */
  ((void(*)(void))D3DDevice_SetRenderState_StencilCullEnable)();
  /* cmp esi, 0x8d -> jne 0x174478 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZCmpAlwaysRead)();
  /* cmp esi, 0x8e -> jne 0x174487 */
  ((void(*)(void))D3DDevice_SetRenderState_RopZRead)();
  /* cmp esi, 0x8f -> jne 0x174495 */
  ((void(*)(void))D3DDevice_SetRenderState_DoNotCullUncompressed)();
  /* cmp edx, 0x16 -> jge 0x1744ac */
  D3DDevice_SetTextureStageState(eax, 0, 0);
  /* cmp edx, 0x1c -> jne 0x1744b9 */
  ((void(*)(void))D3DDevice_SetTextureState_TexCoordIndex)();
  /* cmp edx, 0x1d -> jne 0x1744c6 */
  D3DDevice_SetTextureState_BorderColor(ecx, eax);
  /* cmp edx, 0x1e -> jne 0x1744d3 */
  ((void(*)(void))D3DDevice_SetTextureState_ColorKeyColor)();
  /* cmp edx, 0x1b -> jg 0x1744e0 */
  ((void(*)(void))D3DDevice_SetTextureState_BumpEnv)();

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



/* FUN_001744f0 (0x1744f0) — readable C lift. */
int FUN_001744f0(int a, int b, int c)
{
  return D3DDevice_CreateVertexBuffer(a, b, c, 0, 0);
}



/* FUN_00174510 (0x174510) — XBE naked draft (batch 313). */
#if defined(__clang__)
static void (*const b174510_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b174510_exitfn)(int) = system_exit;
static void (*const b174510_c15e430)(void) = (void *)FUN_0015e430;
static void (*const b174510_c15e0f0)(void) = (void *)FUN_0015e0f0;
static void (*const b174510_c15de60)(void) = (void *)FUN_0015de60;
static void (*const b174510_c15dc10)(void) = (void *)FUN_0015dc10;
static void (*const b174510_c15d8b0)(void) = (void *)FUN_0015d8b0;
static void __cdecl (*const b174510_c15d5b0)(int first_primitive_index, int primitive_count, int dynamic_vertex_buffer_index, short vertices_per_primitive) = rasterizer_draw_dynamic_vertices;

__attribute__((naked, noinline))
void FUN_00174510(void *group __attribute__((unused)), int a2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00174510_1\n\t"
      "pushl $1\n\t"
      "pushl $0x6d\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00174510_1:\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00174510_4\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00174510_2\n\t"
      "pushl $1\n\t"
      "pushl $0x71\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a47f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00174510_2:\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00174510_3\n\t"
      "movl 0x4c(%%esi), %%ecx\n\t"
      "movl 0x48(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x50(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c15e430]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00174510_3:\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "movl 0x4c(%%esi), %%edx\n\t"
      "pushl %%eax\n\t"
      "movl 0x48(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c15e0f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00174510_4:\n\t"
      "movl 0x58(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00174510_6\n\t"
      "movb 0xc(%%ebp), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "movl 0x50(%%esi), %%edx\n\t"
      "je .LFUN_00174510_5\n\t"
      "leal 0x14(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4c(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c15de60]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00174510_5:\n\t"
      "movl 0x44(%%esi), %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl 0x4c(%%esi), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c15dc10]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00174510_6:\n\t"
      "movb 0xc(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00174510_7\n\t"
      "pushl $1\n\t"
      "pushl $0x9c\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a47f0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00174510_7:\n\t"
      "movl 0x44(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00174510_8\n\t"
      "movl 0x54(%%esi), %%edx\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4c(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c15d8b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00174510_8:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movw 0x44(%%esi), %%di\n\t"
      "negw %%di\n\t"
      "cmpw $3, %%di\n\t"
      "je .LFUN_00174510_9\n\t"
      "cmpw $4, %%di\n\t"
      "je .LFUN_00174510_9\n\t"
      "movl 0x50(%%esi), %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "subl $2, %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "je .LFUN_00174510_10\n\t"
      "pushl %%ebx\n\t"
      "pushl $0xb4\n\t"
      "pushl $0x2a4800\n\t"
      "pushl $0x2a47c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00174510_10\n\t"
      ".LFUN_00174510_9:\n\t"
      "movl 0x50(%%esi), %%eax\n\t"
      "movswl %%di, %%ecx\n\t"
      "cdq\n\t"
      "subl $2, %%ecx\n\t"
      "idivl %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      ".LFUN_00174510_10:\n\t"
      "movl 0x54(%%esi), %%edx\n\t"
      "pushl %%edi\n\t"
      "movswl %%bx, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "call *%[c15d5b0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b174510_assert), [exitfn] "m"(b174510_exitfn), [c15e430] "m"(b174510_c15e430), [c15e0f0] "m"(b174510_c15e0f0), [c15de60] "m"(b174510_c15de60), [c15dc10] "m"(b174510_c15dc10), [c15d8b0] "m"(b174510_c15d8b0), [c15d5b0] "m"(b174510_c15d5b0)
      : "memory");
}
#else
#error "FUN_00174510: clang naked draft required"
#endif


/* FUN_00174980 (0x174980) — readable C lift. */
int FUN_00174980(int a, int b)
{
  ((void (__stdcall *)(int, int, int, int, int))D3DVertexBuffer_Lock)(a, b, 0, 0, 0);
  return 0;
}

/* FUN_001749b0 (0x1749b0) — XBE naked draft (batch 362). */
#if defined(__clang__)
static void (*const b1749b0_c1e8a70)(void) = (void *)D3DDevice_EndVisibilityTest;
static void (*const b1749b0_c167ff0)(int a1, const char *call_text) = (void *)FUN_00167ff0;
static void (*const b1749b0_c1e7030)(void) = (void *)D3DDevice_GetVisibilityTestResult;
static int16_t (*const b1749b0_c100b00)(void) = (void *)main_get_window_count;
static int (*const b1749b0_c1d90f0)(char *buffer, const char *format, ...) = (void *)crt_sprintf;
static void (*const b1749b0_c19b800)(short style, short justify, int flags) = (void *)draw_string_set_style_justify_flags;
static void (*const b1749b0_c19b640)(const void *color) = (void *)draw_string_set_color;
static void (*const b1749b0_c19b7e0)(void) = (void *)FUN_0019B7E0;
static void (*const b1749b0_c158ae0)(int mode) = (void *)FUN_00158ae0;
static void (*const b1749b0_c183e60)(void *screen_pos, short *bounds, const void *color, int flags, const char *text) = (void *)rasterizer_text_draw;
static void (*const b1749b0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_001749b0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x11c, %%esp\n\t"
      "movl 0x325740, %%eax\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001749b0_9\n\t"
      "testb %%ah, %%ah\n\t"
      "je .LFUN_001749b0_9\n\t"
      "cmpw $0, 0x5a5bc2\n\t"
      "movl $0xffffffff, -0x14(%%ebp)\n\t"
      "jne .LFUN_001749b0_1\n\t"
      "movl $0, 0x47e4c4\n\t"
      ".LFUN_001749b0_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl $0xfff\n\t"
      "call *%[c1e8a70]\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001749b0_2\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001749b0_3\n\t"
      ".LFUN_001749b0_2:\n\t"
      "pushl $0x2a4894\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_001749b0_3:\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0xfff\n\t"
      "call *%[c1e7030]\n\t"
      "cmpl $0x88760828, %%eax\n\t"
      "je .LFUN_001749b0_3\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_001749b0_4\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_001749b0_4\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_001749b0_5\n\t"
      ".LFUN_001749b0_4:\n\t"
      "pushl $0x2a4890\n\t"
      "pushl %%eax\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001749b0_5:\n\t"
      "movl 0x47e4c4, %%eax\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl %%eax, 0x47e4c4\n\t"
      "call *%[c100b00]\n\t"
      "movswl 0x5a5bc2, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_001749b0_8\n\t"
      "movl 0x46bd0c, %%edx\n\t"
      "pushl %%esi\n\t"
      "movl 0x54(%%edx), %%esi\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_001749b0_7\n\t"
      "movl 0x47e4c4, %%edx\n\t"
      "fildl 0x47e4c4\n\t"
      "testl %%edx, %%edx\n\t"
      "movl 0x5a5bfc, %%eax\n\t"
      "movl 0x5a5c00, %%ecx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jge .LFUN_001749b0_6\n\t"
      "fadds 0x25fb8c\n\t"
      ".LFUN_001749b0_6:\n\t"
      "movl 0x5a5bf4, %%ecx\n\t"
      "movl 0x5a5bf8, %%eax\n\t"
      "movw 0x5a5bfa, %%dx\n\t"
      "subw 0x5a5bf6, %%dx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movswl %%ax, %%ecx\n\t"
      "movswl %%dx, %%eax\n\t"
      "imull %%eax, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "leal -0x11c(%%ebp), %%ecx\n\t"
      "fidivl -0x10(%%ebp)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2a4888\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1d90f0]\n\t"
      "movl -0x6(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addw $-0x32, -0x6(%%ebp)\n\t"
      "pushl $0\n\t"
      "addl $0xffffff60, %%edx\n\t"
      "addl $-0x32, %%eax\n\t"
      "pushl $1\n\t"
      "pushl $-1\n\t"
      "movw %%dx, -0xa(%%ebp)\n\t"
      "movw %%ax, -0xc(%%ebp)\n\t"
      "call *%[c19b800]\n\t"
      "movl 0x2ee6e0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c19b640]\n\t"
      "pushl %%esi\n\t"
      "call *%[c19b7e0]\n\t"
      "pushl $0\n\t"
      "call *%[c158ae0]\n\t"
      "leal -0x11c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "call *%[c183e60]\n\t"
      "addl $0x3c, %%esp\n\t"
      ".LFUN_001749b0_7:\n\t"
      "popl %%esi\n\t"
      ".LFUN_001749b0_8:\n\t"
      "testb %%bl, %%bl\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_001749b0_9\n\t"
      "pushl $0x2a4848\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_001749b0_9:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1e8a70] "m"(b1749b0_c1e8a70), [c167ff0] "m"(b1749b0_c167ff0), [c1e7030] "m"(b1749b0_c1e7030), [c100b00] "m"(b1749b0_c100b00), [c1d90f0] "m"(b1749b0_c1d90f0), [c19b800] "m"(b1749b0_c19b800), [c19b640] "m"(b1749b0_c19b640), [c19b7e0] "m"(b1749b0_c19b7e0), [c158ae0] "m"(b1749b0_c158ae0), [c183e60] "m"(b1749b0_c183e60), [c8f390] "m"(b1749b0_c8f390)
      : "memory");
}
#else
#error "FUN_001749b0: clang naked draft required"
#endif


/* FUN_00174b60 (0x174b60) — readable C lift: plane/vec4 subtract. */
void FUN_00174b60(float *a, float *b, float *out)
{
  out[0] = a[0] - b[0];
  out[1] = a[1] - b[1];
  out[2] = a[2] - b[2];
  out[3] = a[3] - b[3];
}

/* FUN_00174b90 (0x174b90) — readable C lift: out = a + t*b (vec4). */
void FUN_00174b90(float *a, float *b, float t, float *out)
{
  out[0] = t * b[0] + a[0];
  out[1] = t * b[1] + a[1];
  out[2] = t * b[2] + a[2];
  out[3] = t * b[3] + a[3];
}

/* FUN_00174bd0 (0x174bd0) — readable C lift. */
char FUN_00174bd0(char flag)
{
  int hr;
  char ok;
  void *data;
  unsigned char pattern[8];
  int i;
  (void)flag;

  data = 0;
  hr = D3DDevice_CreateVertexBuffer(0x4000, 8, 0, 1, (void **)0x47e4bc);
  if (hr < 0) {
    ok = 0;
    FUN_00167ff0(hr, (const char *)0x2a49c8);
  } else {
    ok = 1;
  }

  *(short *)0x325652 = 2;
  ((void (__stdcall *)(void *, int, int, void **, int))D3DVertexBuffer_Lock)(
      *(void **)0x47e4bc, 0, 0x4000, &data, 0);
  if (!ok) {
    FUN_00167ff0(0, (const char *)0x2a4908);
    ok = 0;
  } else {
    ok = 1;
  }
  *(short *)0x325652 = 0;

  if (!ok || data == 0) {
    error(2, (const char *)0x2a48d4);
    return 0;
  }

  pattern[0] = 0;
  pattern[1] = 0;
  pattern[2] = 0;
  pattern[3] = 0xff;
  pattern[4] = 0xff;
  pattern[5] = 0xff;
  pattern[6] = 0xff;
  pattern[7] = 0;
  for (i = 0; i < 0x400; i++) {
    csmemcpy(data, pattern, 8);
    data = (char *)data + 8;
  }
  return 1;
}



/* FUN_00174cc0 (0x174cc0) — readable C lift. */
void FUN_00174cc0(void)
{
  void *resource = *(void **)0x47e4bc;
  if (resource) {
    D3DResource_Release(resource);
    *(void **)0x47e4bc = 0;
  }
}

/* FUN_00174ce0 (0x174ce0) — readable C lift. */
void FUN_00174ce0(void)
{
  unsigned int v;

  v = *(unsigned int *)0x325740;
  *(unsigned int *)0x47e4b8 = 0;
  *(unsigned char *)0x47e4c0 = 0;
  if ((unsigned char)v == 0)
    return;
  if ((unsigned char)(v >> 8) == 0)
    return;
  if (*(short *)0x5a5bc2 == -1)
    return;
  D3DDevice_BeginVisibilityTest();
}



/* FUN_00178820 (0x178820) — readable C lift. */
int FUN_00178820(int a, int b)
{
  return ((int (__stdcall *)(int, int, int, int))D3DDevice_CreateVertexShader)(a, b, 0, 0);
}

/* FUN_00178850 (0x178850) — readable C lift (restored pre-naked). */
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
  ((void(*)(void))D3DDevice_CreateVertexShader)();
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



/* FUN_00178ab0 (0x178ab0) — readable C lift. */
void FUN_00178ab0(void)
{
  char ok;
  int i;
  unsigned int *slot;

  ok = 1;
  slot = (unsigned int *)0x325208;
  for (i = 0; i < 0x43; i++) {
    D3DDevice_DeleteVertexShader(slot[0]);
    if (!ok) {
      FUN_00167ff0(0, (const char *)0x2add58);
      ok = 0;
    } else {
      ok = 1;
    }
    slot += 4;
  }
  if (!ok)
    error(2, (const char *)0x2add24);
}


/* FUN_00178b40 (0x178b40) — XBE naked draft (batch 301). */
#if defined(__clang__)
static void (*const b178b40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b178b40_exitfn)(int) = system_exit;
static void (*const b178b40_c1eb540)(void) = (void *)D3DDevice_GetVertexShaderSize;
static void (*const b178b40_c167ff0)(int a1, const char *call_text) = FUN_00167ff0;
static void __stdcall (*const b178b40_c1eb7f0)(uint32_t shader) = (void *)D3DDevice_SetVertexShader;
static void (*const b178b40_c1eb4d0)(void) = (void *)D3DDevice_SelectVertexShader;
static void (*const b178b40_c1eb400)(void) = (void *)D3DDevice_LoadVertexShader;
static void (*const b178b40_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void FUN_00178b40(int a1 __attribute__((unused)), int a2 __attribute__((unused)), int a3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "testw %%bx, %%bx\n\t"
      "pushl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $1, %%edi\n\t"
      "jl .LFUN_00178b40_1\n\t"
      "cmpw $0x43, %%bx\n\t"
      "jl .LFUN_00178b40_2\n\t"
      ".LFUN_00178b40_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x87\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae5e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_2:\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl $0x41, %%eax\n\t"
      "ja .LFUN_00178b40_34\n\t"
      "movzbl 0x179058(%%eax), %%eax\n\t"
      "jmp *.LFUN_00178b40_jt(,%%eax,4)\n\t"
      ".LFUN_00178b40_3:\n\t"
      "movl $0x2addc8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_4:\n\t"
      "movl $0x2adde0, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_5:\n\t"
      "movl $2, %%edi\n\t"
      "movl $0x2addf8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_6:\n\t"
      "movl $0x2ade28, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_7:\n\t"
      "movl $0x2ade40, %%esi\n\t"
      "movl $4, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_8:\n\t"
      "movl $0x2adea0, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_9:\n\t"
      "movl $0x2adeb8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_10:\n\t"
      "movl $0x2aded0, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_11:\n\t"
      "movl $0x2adee8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_12:\n\t"
      "movl $0x2adf00, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_13:\n\t"
      "movl $0x2adf18, %%esi\n\t"
      "movl $3, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_14:\n\t"
      "movl $0x2adf60, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_15:\n\t"
      "movl $0x2adf78, %%esi\n\t"
      "movl $3, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_16:\n\t"
      "movl $0x2adfc0, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_17:\n\t"
      "movl $0x2adfd8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_18:\n\t"
      "movl $0x2adff0, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_19:\n\t"
      "movl $0x2ae008, %%esi\n\t"
      "movl $6, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_20:\n\t"
      "movl $0x2ae098, %%esi\n\t"
      "movl $4, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_21:\n\t"
      "movl $0x2ae0f8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_22:\n\t"
      "movl $0x2ae110, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_23:\n\t"
      "movl $0x2ae128, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_24:\n\t"
      "movl $0x2ae140, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_25:\n\t"
      "movl $0x2ae158, %%esi\n\t"
      "movl $6, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_26:\n\t"
      "movl $0x2ae1e8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_27:\n\t"
      "movl $0x2ae200, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_28:\n\t"
      "movl $0x2ae218, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_29:\n\t"
      "movl $0x2ae230, %%esi\n\t"
      "movl $3, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_30:\n\t"
      "movl $0x2ae278, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_31:\n\t"
      "movl $0x2ae290, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_32:\n\t"
      "movl $0x2ae2a8, %%esi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_33:\n\t"
      "movl $0x2ae2c0, %%esi\n\t"
      "movl $2, %%edi\n\t"
      "jmp .LFUN_00178b40_35\n\t"
      ".LFUN_00178b40_34:\n\t"
      "pushl $1\n\t"
      "pushl $0x36c\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae5b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_35:\n\t"
      "movw 0xc(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00178b40_36\n\t"
      "cmpw $0xc, %%ax\n\t"
      "jl .LFUN_00178b40_37\n\t"
      ".LFUN_00178b40_36:\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2a52e0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_37:\n\t"
      "movw 0x10(%%ebp), %%bx\n\t"
      "testw %%bx, %%bx\n\t"
      "jl .LFUN_00178b40_38\n\t"
      "cmpw %%di, %%bx\n\t"
      "jl .LFUN_00178b40_39\n\t"
      ".LFUN_00178b40_38:\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae57c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_39:\n\t"
      "movswl 0xc(%%ebp), %%edx\n\t"
      "movswl %%di, %%ecx\n\t"
      "imull %%edx, %%ecx\n\t"
      "movswl %%bx, %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "cmpw $-1, (%%esi,%%ecx,2)\n\t"
      "leal (%%esi,%%ecx,2), %%esi\n\t"
      "jne .LFUN_00178b40_40\n\t"
      "pushl $1\n\t"
      "pushl $0x371\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae530\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_40:\n\t"
      "movswl (%%esi), %%esi\n\t"
      "cmpw 0x325630, %%si\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "je .LFUN_00178b40_61\n\t"
      "movl 0x325640, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00178b40_45\n\t"
      "xorl %%esi, %%esi\n\t"
      "movl $0x325638, %%edi\n\t"
      "movl $3, %%ebx\n\t"
      "jmp .LFUN_00178b40_41\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00178b40_41:\n\t"
      "movswl -0x4(%%edi), %%edx\n\t"
      "leal 0xc(%%ebp), %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "movl 0x325208(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1eb540]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_42\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00178b40_43\n\t"
      ".LFUN_00178b40_42:\n\t"
      "pushl $0x2ae498\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00178b40_43:\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl %%esi, (%%edi)\n\t"
      "addl %%edx, %%esi\n\t"
      "addl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00178b40_41\n\t"
      "cmpl $0x88, %%esi\n\t"
      "jle .LFUN_00178b40_44\n\t"
      "pushl $1\n\t"
      "pushl $0x3a2\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae45c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_44:\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_00178b40_45:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00178b40_46:\n\t"
      "movswl %%ax, %%ecx\n\t"
      "cmpw 0x325634(,%%ecx,8), %%si\n\t"
      "je .LFUN_00178b40_49\n\t"
      "incl %%eax\n\t"
      "cmpw $3, %%ax\n\t"
      "jl .LFUN_00178b40_46\n\t"
      ".LFUN_00178b40_47:\n\t"
      "movswl %%si, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "movl 0x325208(%%ecx), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_00178b40_48\n\t"
      "pushl $1\n\t"
      "pushl $0x3c9\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae434\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_48:\n\t"
      "pushl %%esi\n\t"
      "call *%[c1eb7f0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_56\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00178b40_57\n\t"
      ".LFUN_00178b40_49:\n\t"
      "cmpw $3, %%ax\n\t"
      "jge .LFUN_00178b40_47\n\t"
      "movswl %%ax, %%esi\n\t"
      "shll $3, %%esi\n\t"
      "movb 0x325636(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_51\n\t"
      "movl 0x325638(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0\n\t"
      "call *%[c1eb4d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_50\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00178b40_60\n\t"
      ".LFUN_00178b40_50:\n\t"
      "pushl $0x2ae3e8\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_00178b40_60\n\t"
      ".LFUN_00178b40_51:\n\t"
      "movswl 0x325634(%%esi), %%eax\n\t"
      "movl 0x325638(%%esi), %%ebx\n\t"
      "shll $4, %%eax\n\t"
      "movl 0x325208(%%eax), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00178b40_52\n\t"
      "pushl $1\n\t"
      "pushl $0x3bc\n\t"
      "pushl $0x2ae628\n\t"
      "pushl $0x2ae434\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00178b40_52:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eb400]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_53\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_00178b40_54\n\t"
      ".LFUN_00178b40_53:\n\t"
      "pushl $0x2ae390\n\t"
      "pushl $0\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00178b40_54:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c1eb4d0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00178b40_55\n\t"
      "movb $1, %%bl\n\t"
      "movb %%bl, 0x325636(%%esi)\n\t"
      "jmp .LFUN_00178b40_59\n\t"
      ".LFUN_00178b40_55:\n\t"
      "pushl $0x2ae338\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x325636(%%esi)\n\t"
      "jmp .LFUN_00178b40_59\n\t"
      ".LFUN_00178b40_56:\n\t"
      "pushl $0x2ae2f0\n\t"
      "pushl $0\n\t"
      "xorb %%bl, %%bl\n\t"
      "call *%[c167ff0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00178b40_57:\n\t"
      "movl $0x325636, %%eax\n\t"
      "movl $3, %%ecx\n\t"
      ".LFUN_00178b40_58:\n\t"
      "movb $0, (%%eax)\n\t"
      "addl $8, %%eax\n\t"
      "decl %%ecx\n\t"
      "jne .LFUN_00178b40_58\n\t"
      ".LFUN_00178b40_59:\n\t"
      "cmpw $0, 0x3256ba\n\t"
      "je .LFUN_00178b40_60\n\t"
      "movswl 0x8(%%ebp), %%edx\n\t"
      "movl 0x5a5558, %%ecx\n\t"
      "shll $4, %%edx\n\t"
      "movl 0x32520c(%%edx), %%eax\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, 0x5a5558\n\t"
      ".LFUN_00178b40_60:\n\t"
      "testb %%bl, %%bl\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "movw %%cx, 0x325630\n\t"
      "jne .LFUN_00178b40_61\n\t"
      "pushl $0x29dffc\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00178b40_61:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "movl %%edi, %%edi\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00178b40_jt:\n\t"
      ".long .LFUN_00178b40_3\n\t"
      ".long .LFUN_00178b40_4\n\t"
      ".long .LFUN_00178b40_5\n\t"
      ".long .LFUN_00178b40_24\n\t"
      ".long .LFUN_00178b40_17\n\t"
      ".long .LFUN_00178b40_18\n\t"
      ".long .LFUN_00178b40_20\n\t"
      ".long .LFUN_00178b40_23\n\t"
      ".long .LFUN_00178b40_32\n\t"
      ".long .LFUN_00178b40_9\n\t"
      ".long .LFUN_00178b40_26\n\t"
      ".long .LFUN_00178b40_13\n\t"
      ".long .LFUN_00178b40_31\n\t"
      ".long .LFUN_00178b40_27\n\t"
      ".long .LFUN_00178b40_25\n\t"
      ".long .LFUN_00178b40_30\n\t"
      ".long .LFUN_00178b40_11\n\t"
      ".long .LFUN_00178b40_33\n\t"
      ".long .LFUN_00178b40_19\n\t"
      ".long .LFUN_00178b40_6\n\t"
      ".long .LFUN_00178b40_22\n\t"
      ".long .LFUN_00178b40_12\n\t"
      ".long .LFUN_00178b40_15\n\t"
      ".long .LFUN_00178b40_29\n\t"
      ".long .LFUN_00178b40_28\n\t"
      ".long .LFUN_00178b40_10\n\t"
      ".long .LFUN_00178b40_16\n\t"
      ".long .LFUN_00178b40_8\n\t"
      ".long .LFUN_00178b40_14\n\t"
      ".long .LFUN_00178b40_21\n\t"
      ".long .LFUN_00178b40_7\n\t"
      ".long .LFUN_00178b40_34\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b178b40_assert), [exitfn] "m"(b178b40_exitfn), [c1eb540] "m"(b178b40_c1eb540), [c167ff0] "m"(b178b40_c167ff0), [c1eb7f0] "m"(b178b40_c1eb7f0), [c1eb4d0] "m"(b178b40_c1eb4d0), [c1eb400] "m"(b178b40_c1eb400), [c8f390] "m"(b178b40_c8f390)
      : "memory");
}
#else
#error "FUN_00178b40: clang naked draft required"
#endif


/* FUN_001792a0 (0x1792a0) — readable C lift. */
void FUN_001792a0(char flag)
{
  *(char *)0x47e4c8 = (char)(flag == 0);
  *(char *)0x47e4c9 = flag;
}

/* FUN_001792C0 (0x1792c0) — readable C lift. */
void FUN_001792C0(char flag)
{
  *(char *)0x47e4c9 = flag;
}

/* FUN_001792d0 (0x1792d0) — readable C lift. */
char FUN_001792d0(void)
{
  return *(char *)0x47e4c9;
}

/* FUN_00179570 (0x179570) — readable C lift. */
int FUN_00179570(int a, int b, int c)
{
  D3DDevice_SetVertexData2f(a, b, c);
  return 0;
}

/* FUN_001795c0 (0x1795c0) — readable C lift (restored pre-naked). */
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


/* FUN_00179de0 (0x179de0) — XBE naked draft (batch 298). */
#if defined(__clang__)
static void (*const b179de0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b179de0_exitfn)(int) = system_exit;
static void * (*const b179de0_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static int (*const b179de0_c190710)(void *shader) = shader_get_vertex_shader_permutation;
static short (*const b179de0_c184610)(void *group) = FUN_00184610;
static void __stdcall (*const b179de0_c1e96d0)(uint32_t mode) = (void *)D3DDevice_SetRenderState_CullMode;
static void (*const b179de0_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b179de0_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void (*const b179de0_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void *(*const b179de0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b179de0_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b179de0_c174510)(void *group, int a2) = FUN_00174510;
static void (*const b179de0_c1795c0)(void) = (void *)FUN_001795c0;
static void (*const b179de0_c155e80)(int stage, int a2, int bitmap_type, int bitmap_index, int frame_index) = rasterizer_set_texture;
static void __stdcall (*const b179de0_c1e9410)(uint32_t stage, uint32_t state, uint32_t value) = (void *)D3DDevice_SetTextureStageState;
static void (*const b179de0_c155cf0)(int stage, int bitmap_tag_index, int frame_index) = rasterizer_set_texture_direct;
static uint32_t (*const b179de0_c159070)(float a1) = FUN_00159070;
static void (*const b179de0_ce2220)(int state, int value) = SetRenderStateSmart;
static void (*const b179de0_c1584f0)(int stage, int target, int max_mipmap) = FUN_001584f0;
static void __stdcall (*const b179de0_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static float (*const b179de0_c13070)(float *a, float *b) = FUN_00013070;
static unsigned int (*const b179de0_cd1dd0)(float *color) = FUN_000d1dd0;

__attribute__((naked, noinline))
void FUN_00179de0(void *group __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x44, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00179de0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xee\n\t"
      "pushl $0x2ae750\n\t"
      "pushl $0x26276c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00179de0_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00179de0_2\n\t"
      "pushl $1\n\t"
      "pushl $0xef\n\t"
      "pushl $0x2ae750\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00179de0_2:\n\t"
      "movb 0x3256d6, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00179de0_18\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $7\n\t"
      "pushl %%eax\n\t"
      "call *%[c1906b0]\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c190710]\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "call *%[c184610]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movw 0x28(%%esi), %%ax\n\t"
      "andw $8, %%ax\n\t"
      "je .LFUN_00179de0_3\n\t"
      "testb $0x12, (%%edi)\n\t"
      "jne .LFUN_00179de0_3\n\t"
      "xorl %%esi, %%esi\n\t"
      "pushl %%esi\n\t"
      "call *%[c1e96d0]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl %%esi, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl %%esi, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $1\n\t"
      "movl %%esi, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $1, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "call *%[c1e9350]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x14\n\t"
      "movl $1, 0x1fb798\n\t"
      "call *%[c178b40]\n\t"
      "pushl $0xf0\n\t"
      "pushl %%esi\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl $1, 0x5a5b94\n\t"
      "call *%[c156510]\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0x24, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00179de0_3:\n\t"
      "testb $0x10, (%%edi)\n\t"
      "jne .LFUN_00179de0_4\n\t"
      "testw %%ax, %%ax\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "je .LFUN_00179de0_5\n\t"
      ".LFUN_00179de0_4:\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      ".LFUN_00179de0_5:\n\t"
      "movb 0x47e4c8, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00179de0_6\n\t"
      "movl 0xc(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1795c0]\n\t"
      "addl $4, %%esp\n\t"
      "movb $0, 0x47e4c8\n\t"
      ".LFUN_00179de0_6:\n\t"
      "testb $1, 0x28(%%esi)\n\t"
      "je .LFUN_00179de0_7\n\t"
      "movl 0x58(%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x10(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0x476204, %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "call *%[c155cf0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $1, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0\n\t"
      "call *%[c1e96d0]\n\t"
      "movl $0x1000000, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl $0x1000000, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $1\n\t"
      "movl $0, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "movzbl 0xb(%%ebp), %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "call *%[c1e9350]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x14\n\t"
      "movl %%edx, 0x1fb798\n\t"
      "call *%[c178b40]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0x61, 0x5a5b98\n\t"
      "movl $2, 0x5a5b94\n\t"
      "movl 0x6c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c159070]\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "movl 0x7c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c159070]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%eax, 0x5a5b08\n\t"
      "movl $0x29120911, 0x5a5ac0\n\t"
      "movl $0xc00, 0x5a5b28\n\t"
      "movl $0x1c180000, 0x5a5ac4\n\t"
      "movl $0xc0, 0x5a5b2c\n\t"
      "movl $0, 0x5a5ae0\n\t"
      "movl $0x1c00, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_00179de0_7:\n\t"
      "testb $2, 0x28(%%esi)\n\t"
      "je .LFUN_00179de0_8\n\t"
      "movl 0x58(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x10(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0\n\t"
      "call *%[c1e96d0]\n\t"
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
      "pushl $0\n\t"
      "pushl $0x3c\n\t"
      "call *%[ce2220]\n\t"
      "pushl $1\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x203\n\t"
      "pushl $0x39\n\t"
      "call *%[ce2220]\n\t"
      "movzbl 0xb(%%ebp), %%edx\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%edx\n\t"
      "pushl $0x40\n\t"
      "call *%[ce2220]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl $0x14\n\t"
      "call *%[c178b40]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $1, %%eax\n\t"
      "movl %%eax, 0x5a5b98\n\t"
      "movl %%eax, 0x5a5b94\n\t"
      "movb 0x28(%%esi), %%cl\n\t"
      "andb $4, %%cl\n\t"
      "negb %%cl\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "andl $0x13, %%ecx\n\t"
      "shll $0x18, %%ecx\n\t"
      "orl $0x200800, %%ecx\n\t"
      "movl %%ecx, 0x5a5ae0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $0x2c, %%esp\n\t"
      ".LFUN_00179de0_8:\n\t"
      "movw 0xd8(%%esi), %%ax\n\t"
      "cmpw $4, %%ax\n\t"
      "jle .LFUN_00179de0_9\n\t"
      "movl $4, %%eax\n\t"
      "jmp .LFUN_00179de0_10\n\t"
      ".LFUN_00179de0_9:\n\t"
      "movswl %%ax, %%eax\n\t"
      ".LFUN_00179de0_10:\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "pushl $0\n\t"
      "call *%[c1584f0]\n\t"
      "addl $0xc, %%esp\n\t"
      "pushl $1\n\t"
      "movl $0xa, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $1\n\t"
      "movl $0xb, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "movl 0xa8(%%esi), %%eax\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x10(%%edi), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl $0\n\t"
      "pushl $2\n\t"
      "pushl $3\n\t"
      "call *%[c155e80]\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "movl $0xa, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xb, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $3\n\t"
      "movl $0xc, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xd, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xe, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $2\n\t"
      "movl $0xf, %%edx\n\t"
      "movl $3, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0\n\t"
      "call *%[c1e96d0]\n\t"
      "pushl $0x10101\n\t"
      "pushl $0x43\n\t"
      "call *%[ce2220]\n\t"
      "movl (%%edi), %%ecx\n\t"
      "shrl $4, %%ecx\n\t"
      "notl %%ecx\n\t"
      "andl $1, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x3b\n\t"
      "call *%[ce2220]\n\t"
      "movb 0x28(%%esi), %%dl\n\t"
      "andb $1, %%dl\n\t"
      "negb %%dl\n\t"
      "sbbl %%edx, %%edx\n\t"
      "andl $0x303, %%edx\n\t"
      "incl %%edx\n\t"
      "pushl %%edx\n\t"
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
      "pushl $1\n\t"
      "pushl $0x7b\n\t"
      "call *%[ce2220]\n\t"
      "pushl $0x203\n\t"
      "pushl $0x39\n\t"
      "call *%[ce2220]\n\t"
      "movzbl 0xb(%%ebp), %%eax\n\t"
      "addl $0x40, %%esp\n\t"
      "pushl %%eax\n\t"
      "pushl $0x40\n\t"
      "call *%[ce2220]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x17\n\t"
      "call *%[c178b40]\n\t"
      "flds 0xbc(%%esi)\n\t"
      "movl 0xc4(%%esi), %%edx\n\t"
      "fcos\n\t"
      "addl $0x14, %%esp\n\t"
      "pushl $3\n\t"
      "leal -0x44(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "pushl $-0x54\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl $0, -0x34(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0, -0x28(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "fmuls 0xc0(%%esi)\n\t"
      "fmuls 0x5a5e18\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "flds 0xbc(%%esi)\n\t"
      "fsin\n\t"
      "fmuls 0xc0(%%esi)\n\t"
      "fmuls 0x5a5e18\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "movl $0x64621, 0x5a5b98\n\t"
      "movl $0x111, 0x5a5b9c\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $4, %%al\n\t"
      "movl $0xc0c0000, %%eax\n\t"
      "movl $0xcd, 0x5a5b74\n\t"
      "movl $0xb0b0120, 0x5a5b48\n\t"
      "movl %%eax, 0x5a5b4c\n\t"
      "je .LFUN_00179de0_11\n\t"
      "movl $0xc0, %%ecx\n\t"
      "movl $4, 0x5a5b94\n\t"
      "movl %%ecx, 0x5a5b78\n\t"
      "movl %%eax, 0x5a5b50\n\t"
      "movl %%ecx, 0x5a5b7c\n\t"
      "movl $0x2d0c0d0b, 0x5a5b54\n\t"
      "movl $0xc00, 0x5a5b80\n\t"
      "movl $0x330c0000, 0x5a5ae0\n\t"
      "jmp .LFUN_00179de0_12\n\t"
      ".LFUN_00179de0_11:\n\t"
      "movl $2, 0x5a5b94\n\t"
      "movl $0xc0, 0x5a5b78\n\t"
      "movl $0x2d0f0b00, 0x5a5ae0\n\t"
      "movl %%eax, 0x5a5ae4\n\t"
      ".LFUN_00179de0_12:\n\t"
      "flds 0x88(%%edi)\n\t"
      "leal 0x80(%%edi), %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "flds (%%ecx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00179de0_16\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00179de0_13\n\t"
      "flds 0x2533c0\n\t"
      "jmp .LFUN_00179de0_15\n\t"
      ".LFUN_00179de0_13:\n\t"
      "flds 0x5a5bd8\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      "flds 0x5a5bdc\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00179de0_14\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00179de0_15\n\t"
      ".LFUN_00179de0_14:\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a5bd4\n\t"
      "call *%[c13070]\n\t"
      "fchs\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00179de0_15:\n\t"
      "flds 0x2533c8\n\t"
      "leal -0x14(%%ebp), %%edx\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "pushl %%edx\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x80(%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x70(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x84(%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls 0x74(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls 0x88(%%esi)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x78(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "call *%[cd1dd0]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%eax, 0x5a5ae8\n\t"
      "jmp .LFUN_00179de0_17\n\t"
      ".LFUN_00179de0_16:\n\t"
      "movl $0xffffff, 0x5a5ae8\n\t"
      ".LFUN_00179de0_17:\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[c156510]\n\t"
      "flds 0xe0(%%esi)\n\t"
      "fchs\n\t"
      "addl $4, %%esp\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "movl $0x10, %%edx\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "call *%[c174510]\n\t"
      "addl $8, %%esp\n\t"
      "pushl $0\n\t"
      "movl $0x10, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "call *%[c1e9410]\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00179de0_18:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b179de0_assert), [exitfn] "m"(b179de0_exitfn), [c1906b0] "m"(b179de0_c1906b0), [c190710] "m"(b179de0_c190710), [c184610] "m"(b179de0_c184610), [c1e96d0] "m"(b179de0_c1e96d0), [c1e9350] "m"(b179de0_c1e9350), [c1ea290] "m"(b179de0_c1ea290), [c178b40] "m"(b179de0_c178b40), [memset] "m"(b179de0_memset), [c156510] "m"(b179de0_c156510), [c174510] "m"(b179de0_c174510), [c1795c0] "m"(b179de0_c1795c0), [c155e80] "m"(b179de0_c155e80), [c1e9410] "m"(b179de0_c1e9410), [c155cf0] "m"(b179de0_c155cf0), [c159070] "m"(b179de0_c159070), [ce2220] "m"(b179de0_ce2220), [c1584f0] "m"(b179de0_c1584f0), [c1eb8d0] "m"(b179de0_c1eb8d0), [c13070] "m"(b179de0_c13070), [cd1dd0] "m"(b179de0_cd1dd0)
      : "memory");
}
#else
#error "FUN_00179de0: clang naked draft required"
#endif


/* FUN_0017a8a0 (0x17a8a0) — XBE naked draft (batch 306). */
#if defined(__clang__)
static void (*const b17a8a0_xfrmpt)(float *, float *, float *) = matrix_transform_point;

__attribute__((naked, noinline))
void FUN_0017a8a0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fcomps 0x2533c0\n\t"
      "xorb %%cl, %%cl\n\t"
      "pushl %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017a8a0_3\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movw 0x5a5bfa, %%si\n\t"
      "movl 0x5a5bf8, %%edi\n\t"
      "movl 0x5a5bf4, %%edx\n\t"
      "subw 0x5a5bf6, %%si\n\t"
      "leal -0x1c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x5a5c2c\n\t"
      "subl %%edx, %%edi\n\t"
      "call *%[xfrmpt]\n\t"
      "flds 0x5a5d84\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds 0x5a5d74\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d64\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d94\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x5a5d88\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds 0x5a5d78\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d68\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d98\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "flds 0x5a5d60\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x5a5d74\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017a8a0_2\n\t"
      "flds 0x5a5d8c\n\t"
      "movswl %%si, %%edx\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "flds 0x5a5d7c\n\t"
      "movswl %%di, %%eax\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d6c\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d9c\n\t"
      "fdivrs 0x2533c8\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "flds 0x5a5d80\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "flds 0x5a5d70\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5d60\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds 0x5a5d90\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "fadds 0x2533c8\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%ebx)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fsubs 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_0017a8a0_1\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      ".LFUN_0017a8a0_1:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "popl %%edi\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "popl %%esi\n\t"
      "fmuls -0xc(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps (%%eax)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x4(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017a8a0_2:\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017a8a0_3:\n\t"
      "popl %%edi\n\t"
      "movb %%cl, %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [xfrmpt] "m"(b17a8a0_xfrmpt)
      : "memory");
}
#else
#error "FUN_0017a8a0: clang naked draft required"
#endif


/* FUN_0017ad20 (0x17ad20) — readable C lift. */
int FUN_0017ad20(int a, int b, int c)
{
  D3DDevice_SetVertexData2f(a, b, c);
  return 0;
}

/* FUN_0017ad40 (0x17ad40) — readable C lift. */
void FUN_0017ad40(int a0, int a1, int a2, int a3, int a4, int a5)
{
  D3DDevice_SetVertexData4f(a1, a2, a3, a4, a5);
}

/* 0x17ad90 */
void FUN_0017ad90(void)
{
  int eax = 0;

  D3DDevice_Begin(eax);
  ((void (*)(void))D3DDevice_End)();

  (void)eax;
}

/* FUN_0017adc0 (0x17adc0) — readable C lift. */
int FUN_0017adc0(int test_id)
{
  int result;
  int hr;
  char ok;
  int unused;

  result = -1;
  if (*(char *)0x3256fc == 0)
    return 1;

  unused = 0;
  hr = ((int (__stdcall *)(int, int *, int *))D3DDevice_GetVisibilityTestResult)(
      test_id, &result, &unused);
  if (hr == (int)0x88760828) {
    ((void (*)(int))rasterizer_spin_begin)(0x1a);
    do {
      hr = ((int (__stdcall *)(int, int *, int *))D3DDevice_GetVisibilityTestResult)(
          test_id, &result, &unused);
    } while (hr == (int)0x88760828);
    rasterizer_spin_end();
  }

  if (hr < 0) {
    ok = 0;
    FUN_00167ff0(hr, (const char *)0x2a4890);
  } else {
    ok = 1;
  }

  if (result < 0) {
    display_assert((const char *)0x2ae7c8, (const char *)0x2ae7f0, 0x23e, true);
    system_exit(-1);
  }

  if (!ok)
    error(2, (const char *)0x2ae788);

  return result;
}



/* FUN_0017ae90 (0x17ae90) — readable C lift. */
void FUN_0017ae90(int object_handle, int datum, float *position, int callback)
{
  void *group;
  float dx;
  float dy;
  float dz;
  float *dst;
  float *q;

  if (!callback)
    return;
  group = rasterizer_transparent_geometry_group_new();
  if (!position) {
    display_assert((const char *)0x2a1774, (const char *)0x2ae7f0, 0x58, 1);
    system_exit(-1);
  }
  if (!group) {
    if (!*(unsigned char *)0x47e4ca) {
      error(2, (const char *)0x2a1744);
      *(unsigned char *)0x47e4ca = 1;
    }
    return;
  }

  dx = position[0] - *(float *)0x5a5bc8;
  dy = position[1] - *(float *)0x5a5bcc;
  dz = position[2] - *(float *)0x5a5bd0;

  *(int *)((char *)group + 0x48) = callback;
  *(int *)((char *)group + 0x4c) = object_handle;
  *(int *)((char *)group + 0x50) = datum;
  *(int *)((char *)group + 0) = 0;
  *(int *)((char *)group + 4) = 0;
  *(int *)((char *)group + 8) = 0;
  *(int *)((char *)group + 0xc) = 0;
  *(short *)((char *)group + 0x10) = 0;
  *(short *)((char *)group + 0x14) = 0;
  *(int *)((char *)group + 0x58) = 0;
  *(int *)((char *)group + 0x5c) = 0;
  *(int *)((char *)group + 0x44) = -1;
  *(int *)((char *)group + 0x54) = -1;

  *(float *)((char *)group + 0x70) =
      -(*(float *)0x5a5bd4 * dx + *(float *)0x5a5bd8 * dy + *(float *)0x5a5bdc * dz);

  dst = (float *)((char *)group + 0x74);
  dst[0] = position[0];
  dst[1] = position[1];
  dst[2] = position[2];

  q = (float *)((char *)group + 0x80);
  q[0] = 0.0f;
  q[1] = 0.0f;
  q[2] = 0.0f;
  q[3] = 0.0f;

  *(int *)((char *)group + 0x98) = 0;
  *(unsigned char *)((char *)group + 0x9d) = 0;
  *(int *)((char *)group + 0x60) = 0;
  *(short *)((char *)group + 0x64) = 0;
  *(int *)((char *)group + 0x68) = 0;
  *(int *)((char *)group + 0x6c) = 0;
  *(float *)((char *)group + 0x40) = 1.0f;
  *(float *)((char *)group + 0x3c) = 1.0f;
  *(short *)((char *)group + 0x94) = -1;
  *(short *)((char *)group + 0x96) = -1;
}

/* FUN_0017b000 (0x17b000) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b17b000_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17b000_exitfn)(int) = system_exit;
static void __stdcall (*const b17b000_c1e96d0)(uint32_t mode) = (void *)D3DDevice_SetRenderState_CullMode;
static void (*const b17b000_c1e9350)(uint32_t reg, uint32_t value) = D3DDevice_SetRenderState_Simple;
static void __stdcall (*const b17b000_c1ea290)(uint32_t enable) = (void *)D3DDevice_SetRenderState_ZEnable;
static void __stdcall (*const b17b000_c1e98e0)(uint32_t value) = (void *)D3DDevice_SetRenderState_ZBias;
static void (*const b17b000_c178b40)(int a1, int a2, int a3) = FUN_00178b40;
static void __stdcall (*const b17b000_c1eb8d0)(int register_index, const void *data, uint32_t count) = (void *)D3DDevice_SetVertexShaderConstant;
static void *(*const b17b000_memset)(void *, int, unsigned int) = csmemset;
static void (*const b17b000_c156510)(void *state) = rasterizer_set_pixel_shader;
static void (*const b17b000_c17cfe0)(int tex_flags) = FUN_0017cfe0;

__attribute__((naked, noinline))
void FUN_0017b000(int param_1 __attribute__((unused)), int param_2 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x50, %%esp\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $1, %%edi\n\t"
      "jne .LFUN_0017b000_1\n\t"
      "pushl %%edi\n\t"
      "pushl $0x9a\n\t"
      "pushl $0x2ae7f0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017b000_1:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "subl $5, %%eax\n\t"
      "je .LFUN_0017b000_3\n\t"
      "decl %%eax\n\t"
      "je .LFUN_0017b000_2\n\t"
      "pushl %%edi\n\t"
      "pushl $0x10a\n\t"
      "pushl $0x2ae7f0\n\t"
      "pushl $0x2ae82c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017b000_2:\n\t"
      "pushl $0x901\n\t"
      "call *%[c1e96d0]\n\t"
      "movb 0x3256fd, %%al\n\t"
      "negb %%al\n\t"
      "movl $0x40358, %%ecx\n\t"
      "sbbl %%eax, %%eax\n\t"
      "andl $0x10101, %%eax\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl %%esi, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "pushl %%edi\n\t"
      "movl $0, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movzbl 0x3256fd, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "call *%[c1e9350]\n\t"
      "movl 0x32570c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%esi, 0x1fb798\n\t"
      "call *%[c1e98e0]\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl $0x38\n\t"
      "call *%[c178b40]\n\t"
      "movw 0x5a5bfa, %%ax\n\t"
      "subw 0x5a5bf6, %%ax\n\t"
      "movl 0x5a5bf4, %%edx\n\t"
      "movl 0x5a5bf8, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "subl %%edx, %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movswl %%cx, %%eax\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl $0, -0x48(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "pushl $5\n\t"
      "leal -0x50(%%ebp), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds 0x255e94\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds 0x25eeac\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl $-0x44\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%edi, 0x5a5b94\n\t"
      "movl $0x20, 0x5a5ae0\n\t"
      "call *%[c156510]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_0017b000_3:\n\t"
      "pushl $0x901\n\t"
      "call *%[c1e96d0]\n\t"
      "movl $0x10101, %%edx\n\t"
      "movl $0x40358, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40304, %%ecx\n\t"
      "movl $0x10101, 0x1fb7a4\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x302, %%edx\n\t"
      "movl $0x40344, %%ecx\n\t"
      "movl %%edi, 0x1fb784\n\t"
      "call *%[c1e9350]\n\t"
      "movl %%edi, %%edx\n\t"
      "movl $0x40348, %%ecx\n\t"
      "movl $0x302, 0x1fb790\n\t"
      "call *%[c1e9350]\n\t"
      "movl $0x8006, %%edx\n\t"
      "movl $0x40350, %%ecx\n\t"
      "movl %%edi, 0x1fb794\n\t"
      "call *%[c1e9350]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movl $0x40300, %%ecx\n\t"
      "movl $0x8006, 0x1fb7c0\n\t"
      "call *%[c1e9350]\n\t"
      "movzwl 0xc(%%ebp), %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "andl %%edi, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl $0, 0x1fb788\n\t"
      "call *%[c1ea290]\n\t"
      "movl $0x203, %%edx\n\t"
      "movl $0x40354, %%ecx\n\t"
      "call *%[c1e9350]\n\t"
      "shrl $1, %%esi\n\t"
      "andl %%edi, %%esi\n\t"
      "movl %%esi, %%edx\n\t"
      "movl $0x4035c, %%ecx\n\t"
      "movl $0x203, 0x1fb77c\n\t"
      "call *%[c1e9350]\n\t"
      "pushl $0\n\t"
      "movl %%esi, 0x1fb798\n\t"
      "call *%[c1e98e0]\n\t"
      "pushl $0x3f800000\n\t"
      "call *%[c17cfe0]\n\t"
      "pushl $0\n\t"
      "pushl $6\n\t"
      "pushl $0x38\n\t"
      "call *%[c178b40]\n\t"
      "movw 0x5a5bfa, %%ax\n\t"
      "subw 0x5a5bf6, %%ax\n\t"
      "movl 0x5a5bf8, %%ecx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movl 0x5a5bf4, %%edx\n\t"
      "addl $0x10, %%esp\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "subl %%edx, %%ecx\n\t"
      "movswl %%cx, %%ecx\n\t"
      "fdivrs 0x2533c8\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl $0, -0x4c(%%ebp)\n\t"
      "movl $0, -0x48(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "movl $0, -0x38(%%ebp)\n\t"
      "movl $0, -0x30(%%ebp)\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "flds 0x255e94\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds 0x25eeac\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "pushl $5\n\t"
      "leal -0x50(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $-0x44\n\t"
      "movl $0x3f800000, -0x28(%%ebp)\n\t"
      "movl $0, -0x24(%%ebp)\n\t"
      "movl $0, -0x20(%%ebp)\n\t"
      "movl $0, -0x1c(%%ebp)\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "movl $0x3f800000, -0x14(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "call *%[c1eb8d0]\n\t"
      "pushl $0xf0\n\t"
      "pushl $0\n\t"
      "pushl $0x5a5ac0\n\t"
      "call *%[memset]\n\t"
      "pushl $0x5a5ac0\n\t"
      "movl %%edi, 0x5a5b98\n\t"
      "movl $3, 0x5a5b94\n\t"
      "movl $0x8080000, 0x5a5b48\n\t"
      "movl $0xc0, 0x5a5b74\n\t"
      "movl $0xc0c0000, 0x5a5b4c\n\t"
      "movl $0xd0, 0x5a5b78\n\t"
      "movl $0x4082415, 0x5a5b50\n\t"
      "movl $0x45, 0x5a5b7c\n\t"
      "movl $0x50f0004, 0x5a5ae0\n\t"
      "movl $0xc0d1400, 0x5a5ae4\n\t"
      "call *%[c156510]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17b000_assert), [exitfn] "m"(b17b000_exitfn), [c1e96d0] "m"(b17b000_c1e96d0), [c1e9350] "m"(b17b000_c1e9350), [c1ea290] "m"(b17b000_c1ea290), [c1e98e0] "m"(b17b000_c1e98e0), [c178b40] "m"(b17b000_c178b40), [c1eb8d0] "m"(b17b000_c1eb8d0), [memset] "m"(b17b000_memset), [c156510] "m"(b17b000_c156510), [c17cfe0] "m"(b17b000_c17cfe0)
      : "memory");
}
#else
#error "FUN_0017b000: clang naked draft required"
#endif


/* FUN_0017b480 (0x17b480) — readable C lift. */
char FUN_0017b480(int stage, int bitmap_index, short frame)
{
  char ok;

  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2ae7f0, 0x11d, 1);
    system_exit(-1);
  }
  if (bitmap_index != -1)
    ok = ((char (*)(int, int, int, int, int))(void *)rasterizer_set_texture_non_blocking)(
        stage, 0, 1, bitmap_index, (int)frame);
  else
    ok = ((char (*)(int, int, int))(void *)rasterizer_set_texture_direct_non_blocking)(
        stage, *(int *)(*(char **)0x476204 + 0x6c), (int)frame);
  if (!ok) {
    D3DDevice_SetTextureStageState(0, 0xa, 4);
    D3DDevice_SetTextureStageState(0, 0xb, 4);
    D3DDevice_SetTextureStageState(0, 0xd, 2);
    D3DDevice_SetTextureStageState(0, 0xe, 2);
    D3DDevice_SetTextureStageState(0, 0xf, 2);
  }
  return ok;
}

/* FUN_0017b540 (0x17b540) — readable C lift. */
void FUN_0017b540(int tex_flags)
{
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2ae7f0, 0x13e, 1);
    system_exit(-1);
  }
  D3DDevice_SetVertexData2f(0xa, tex_flags, 0);
}

/* FUN_0017b580 (0x17b580) — readable C lift. */
void FUN_0017b580(unsigned char enable)
{
  if (!*(int *)0x476ab0) {
    display_assert((const char *)0x29dc40, (const char *)0x2ae7f0, 0x14e, 1);
    system_exit(-1);
  }
  D3DDevice_SetRenderState_ZEnable(enable);
}


/* FUN_0017b5c0 (0x17b5c0) — readable C lift (restored pre-naked). */
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


/* FUN_0017b7d0 (0x17b7d0) — XBE naked draft (batch 308). */
#if defined(__clang__)
static void (*const b17b7d0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17b7d0_exitfn)(int) = system_exit;
static void (*const b17b7d0_c17a8a0)(void) = (void *)FUN_0017a8a0;
static void __stdcall (*const b17b7d0_c1ed450)(uint32_t primitive_type) = (void *)D3DDevice_Begin;
static void __stdcall (*const b17b7d0_c1ed400)(unsigned int reg, unsigned int color) = (void *)D3DDevice_SetVertexDataColor;
static void __stdcall (*const b17b7d0_c1ed320)(unsigned int reg, int a, int b) = (void *)D3DDevice_SetVertexData2s;
static void __stdcall (*const b17b7d0_c1ed2c0)(uint32_t reg, float a, float b, float c, float d) = (void *)D3DDevice_SetVertexData4f;
static void (*const b17b7d0_c1ed490)(void) = (void *)D3DDevice_End;

__attribute__((naked, noinline))
void FUN_0017b7d0(float *position __attribute__((unused)), float radius __attribute__((unused)), float *scale2d __attribute__((unused)), float angle __attribute__((unused)), uint32_t color __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_0017b7d0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x1a9\n\t"
      "pushl $0x2ae7f0\n\t"
      "pushl $0x25bb20\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017b7d0_1:\n\t"
      "movl 0x476ab0, %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_0017b7d0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x1aa\n\t"
      "pushl $0x2ae7f0\n\t"
      "pushl $0x29dc40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017b7d0_2:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0017b7d0_8\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "leal -0x20(%%ebp), %%ebx\n\t"
      "call *%[c17a8a0]\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "je .LFUN_0017b7d0_8\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_0017b7d0_4\n\t"
      "flds 0x14(%%ebp)\n\t"
      "fmuls 0x253d4c\n\t"
      "fld %%st(0)\n\t"
      "fcos\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fsin\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x2533c8\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_0017b7d0_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1b5\n\t"
      "pushl $0x2ae7f0\n\t"
      "pushl $0x2ae850\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017b7d0_3:\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .LFUN_0017b7d0_5\n\t"
      ".LFUN_0017b7d0_4:\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_0017b7d0_5:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_0017b7d0_6\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "jmp .LFUN_0017b7d0_7\n\t"
      ".LFUN_0017b7d0_6:\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      "movl $0x3f800000, 0x8(%%ebp)\n\t"
      ".LFUN_0017b7d0_7:\n\t"
      "pushl $7\n\t"
      "call *%[c1ed450]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $9\n\t"
      "call *%[c1ed400]\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "movl -0x18(%%ebp), %%esi\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%esi\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "call *%[c1ed2c0]\n\t"
      "pushl $0\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%esi\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0xc(%%ebp)\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "call *%[c1ed2c0]\n\t"
      "pushl $1\n\t"
      "pushl $1\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%esi\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "call *%[c1ed2c0]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl $4\n\t"
      "call *%[c1ed320]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "pushl $0x3f800000\n\t"
      "pushl %%esi\n\t"
      "subl $8, %%esp\n\t"
      "fstps 0x4(%%esp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x8(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0\n\t"
      "call *%[c1ed2c0]\n\t"
      "call *%[c1ed490]\n\t"
      ".LFUN_0017b7d0_8:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17b7d0_assert), [exitfn] "m"(b17b7d0_exitfn), [c17a8a0] "m"(b17b7d0_c17a8a0), [c1ed450] "m"(b17b7d0_c1ed450), [c1ed400] "m"(b17b7d0_c1ed400), [c1ed320] "m"(b17b7d0_c1ed320), [c1ed2c0] "m"(b17b7d0_c1ed2c0), [c1ed490] "m"(b17b7d0_c1ed490)
      : "memory");
}
#else
#error "FUN_0017b7d0: clang naked draft required"
#endif


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
  ((void(*)(void))D3DDevice_EndVisibilityTest)();
  FUN_00167ff0(0, (char *)0x002a4894);
  error(0, (char *)0x002ae898);
  return 1;

  (void)eax;
}


/* FUN_0017bca0 (0x17bca0) — readable C lift. */
char FUN_0017bca0(void *shader, void *state)
{
  void *sh;
  int *block;
  int count;
  int flags;
  int i;
  char ok;
  void *elem;
  int w;
  int w2;
  int bit;
  int idx;
  int v;
  int v2;

  ok = 1;
  if (!shader) {
    display_assert((const char *)0x2a18b8, (const char *)0x2ae9d0, 0x64, 1);
    system_exit(-1);
  }
  if (!state) {
    display_assert((const char *)0x29e09c, (const char *)0x2ae9d0, 0x65, 1);
    system_exit(-1);
  }
  sh = FUN_001906b0(shader, 6);
  csmemset(state, 0, 0xf0);
  block = (int *)((char *)sh + 0x54);
  *(int *)((char *)state + 0xd4) = (block[0] + 1) | 0x11000;
  count = block[0];
  if (count <= 0) {
    error(2, (const char *)0x2ae9a8);
    ok = 0;
  } else {
    flags = 0;
    if (count > 3)
      flags = 1;
    flags <<= 5;
    if (count > 2)
      flags |= 1;
    flags <<= 5;
    if (count > 1)
      flags |= 1;
    flags <<= 5;
    bit = (*(short *)((char *)sh + 0x2a) != 0) ? 1 : 0;
    flags |= bit + bit + 1;
    *(int *)((char *)state + 0xd8) = flags;

    if (block[0] > 0) {
      for (i = 0; i < block[0]; i++) {
        elem = tag_block_get_element(block, i, 0xdc);
        if (i != block[0] - 1) {
          w = *(short *)((char *)elem + 0x2e);
          v = ((int *)0x2ae974)[w] * (i + 1) + ((int *)0x2ae940)[w];
          ((int *)state)[i + 1] = v;
          w2 = *(short *)((char *)elem + 0x2c);
          idx = (((*(unsigned char *)elem) >> 1) & 1) * 0xd + w2;
          v2 = ((int *)0x2ae974)[w2] * (i + 1) + ((int *)0x2ae8d8)[idx];
          ((int *)((char *)state + 0x8c))[i] = v2;
        } else {
          *(int *)state = 0x18200000;
          *(int *)((char *)state + 0x88) = 0x8200000;
        }
        ((int *)((char *)state + 0x68))[i] = 0xc00;
        ((int *)((char *)state + 0xb4))[i] = 0xc00;
      }
      ok = 1;
    }
  }
  *(int *)((char *)state + 0x20) = 0xc;
  *(int *)((char *)state + 0x24) = 0x1c00;
  return ok;
}

/* FUN_0017be50 (0x17be50) — readable C lift. */
int FUN_0017be50(short si_val /* @<esi> */, short di_val /* @<edi> */)
{
  int idx;
  int v;

  if ((short)si_val < 0 || (short)si_val >= 0x19) {
    display_assert((char *)0x2aeca8, (char *)0x2aed00, 0xd4, 1);
    system_exit(-1);
  }
  if ((short)di_val < 0 || (short)di_val >= 8) {
    display_assert((char *)0x2aec48, (char *)0x2aed00, 0xd5, 1);
    system_exit(-1);
  }
  idx = (int)(short)si_val;
  v = *(int *)(0x2aea20 + idx * 4);
  if (v != -1)
    return *(int *)(0x2aeaec + (int)(short)di_val * 4) | v;
  return *(int *)(0x2aeb30 + ((int)(short)di_val + idx * 8) * 4);
}
/* FUN_0017bf20 (0x17bf20) — readable C lift. */
unsigned int FUN_0017bf20(void *shader /*@<esi>*/)
{
  short v;
  unsigned int flags;

  if (shader == 0) {
    display_assert((const char *)0x2aef34, (const char *)0x2aed00, 0xf6, 1);
    system_exit(-1);
  }
  v = *(short *)((char *)shader + 0x56);
  if (v < 0 || v >= 6) {
    display_assert((const char *)0x2aeeb8, (const char *)0x2aed00, 0xf7, 1);
    system_exit(-1);
  }
  v = *(short *)((char *)shader + 0x4e);
  if (v < 0 || v >= 2) {
    display_assert((const char *)0x2aee30, (const char *)0x2aed00, 0xf8, 1);
    system_exit(-1);
  }
  v = *(short *)((char *)shader + 0x52);
  if (v < 0 || v >= 2) {
    display_assert((const char *)0x2aeda8, (const char *)0x2aed00, 0xf9, 1);
    system_exit(-1);
  }
  flags = *(unsigned int *)(0x2aec18 + 4 * *(short *)((char *)shader + 0x56));
  if (*(short *)((char *)shader + 0x4e) == 1)
    flags |= 2;
  if (*(short *)((char *)shader + 0x52) == 1)
    flags |= 1;
  if ((*(unsigned char *)shader & 1) != 0)
    flags |= 4;
  return flags;
}

/* FUN_0017c000 (0x17c000) — readable C lift. */
int FUN_0017c000(short stage /*@<esi>*/, short index /*@<edi>*/)
{
  int base;
  if ((short)stage < 0 || (short)stage >= 0x19) {
    display_assert((const char *)0x2aeca8, (const char *)0x2aed00, 0x10a, 1);
    system_exit(-1);
  }
  if ((short)index < 0 || (short)index >= 8) {
    display_assert((const char *)0x2aec48, (const char *)0x2aed00, 0x10b, 1);
    system_exit(-1);
  }
  base = ((int *)0x2aea88)[(int)(short)stage];
  if (base != -1)
    return ((int *)0x2aeb0c)[(int)(short)index] | base;
  return ((int *)0x2aeb30)[(int)(short)index + (int)(short)stage * 8];
}

/* FUN_0017c140 (0x17c140) — readable C lift. */
char FUN_0017c140(void *obj, short index)
{
  char ok;

  ok = 1;
  if (!obj) {
    display_assert((const char *)0x2af04c, (const char *)0x2aed00, 0x13c, true);
    system_exit(-1);
  }
  if (*(int *)((char *)obj + 0x28) == -1) {
    error(2, (const char *)0x2af00c, (int)index);
    ok = 0;
  }
  if (*(float *)((char *)obj + 0x18) != *(float *)0x2533c0) {
    error(2, (const char *)0x2aefc0, (int)index);
    return 0;
  }
  return ok;
}

/* FUN_0017c1b0 (0x17c1b0) — readable C lift. */
char FUN_0017c1b0(void *shader, short index)
{
  char ok;
  short a;
  short c;

  ok = 1;
  if (!shader) {
    display_assert((const char *)0x2aef34, (const char *)0x2aed00, 0x154, true);
    system_exit(-1);
  }

  a = *(short *)((char *)shader + 0x4c);
  if (a != 0) {
    c = *(short *)((char *)shader + 0x50);
    if (c != 0 && a == c)
      goto dup_map;
    if (a != 0) {
      c = *(short *)((char *)shader + 0x54);
      if (c != 0 && a == c)
        goto dup_map;
    }
  }

  c = *(short *)((char *)shader + 0x50);
  if (c != 0) {
    a = *(short *)((char *)shader + 0x54);
    if (a != 0 && c == a)
      goto dup_map;
  }

  a = *(short *)((char *)shader + 0x68);
  if (a != 0) {
    c = *(short *)((char *)shader + 0x6a);
    if (c != 0 && a == c)
      goto dup_map;
    if (a != 0) {
      c = *(short *)((char *)shader + 0x6c);
      if (c != 0 && a == c)
        goto dup_map;
    }
  }

  c = *(short *)((char *)shader + 0x6a);
  if (c != 0) {
    a = *(short *)((char *)shader + 0x6c);
    if (a != 0 && c == a) {
dup_map:
      error(2, (const char *)0x2af140, (int)index);
      ok = 0;
    }
  }

  if (*(short *)((char *)shader + 0x4e) != 0 || *(short *)((char *)shader + 0x52) != 0) {
    if (*(short *)((char *)shader + 0x54) != 0) {
      error(2, (const char *)0x2af0f0, (int)index);
      ok = 0;
    }
  }

  if (*(short *)((char *)shader + 0x68) == 3 || *(short *)((char *)shader + 0x6c) == 3) {
    error(2, (const char *)0x2af0a0, (int)index);
    ok = 0;
  }

  if ((*(unsigned char *)shader & 1) != 0) {
    if (*(short *)((char *)shader + 0x4e) != 0 || *(short *)((char *)shader + 0x52) != 0) {
      error(2, (const char *)0x2af050, (int)index);
      return 0;
    }
  }
  return ok;
}

/* FUN_0017c2f0 (0x17c2f0) — XBE naked draft (batch 300). */
#if defined(__clang__)
static void (*const b17c2f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b17c2f0_exitfn)(int) = system_exit;
static void * (*const b17c2f0_c1906b0)(void *shader, int shader_type) = FUN_001906b0;
static void *(*const b17c2f0_memset)(void *, int, unsigned int) = csmemset;
static void (*const b17c2f0_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void *(*const b17c2f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b17c2f0_c17c140)(void) = (void *)FUN_0017c140;
static void (*const b17c2f0_c17c1b0)(void) = (void *)FUN_0017c1b0;
static unsigned int (*const b17c2f0_d1c90)(float *) = FUN_000d1c90;
static void (*const b17c2f0_c17be50)(void) = (void *)FUN_0017be50;
static void (*const b17c2f0_c17bf20)(void) = (void *)FUN_0017bf20;
static void (*const b17c2f0_c17c000)(void) = (void *)FUN_0017c000;

__attribute__((naked, noinline))
char FUN_0017c2f0(void *shader __attribute__((unused)), void *state __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jne .LFUN_0017c2f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x184\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2a18b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_0017c2f0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x185\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x29e09c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_2:\n\t"
      "pushl $5\n\t"
      "pushl %%esi\n\t"
      "call *%[c1906b0]\n\t"
      "pushl $0xf0\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, 0x8(%%ebp)\n\t"
      "call *%[memset]\n\t"
      "movl 0x54(%%esi), %%eax\n\t"
      "leal 0x54(%%esi), %%ebx\n\t"
      "addl $0x14, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jg .LFUN_0017c2f0_4\n\t"
      "movl 0x60(%%esi), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jg .LFUN_0017c2f0_3\n\t"
      "pushl $0x2af17c\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0017c2f0_10\n\t"
      ".LFUN_0017c2f0_3:\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0017c2f0_5\n\t"
      ".LFUN_0017c2f0_4:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpw %%cx, 0x2a(%%esi)\n\t"
      "setne %%cl\n\t"
      "leal 0x1(%%ecx,%%ecx,1), %%ecx\n\t"
      "movl %%ecx, %%esi\n\t"
      "jmp .LFUN_0017c2f0_6\n\t"
      ".LFUN_0017c2f0_5:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_0017c2f0_6:\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl $3, %%eax\n\t"
      "setg %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "shll $5, %%edx\n\t"
      "cmpl $2, %%eax\n\t"
      "setg %%cl\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl $1, %%eax\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "setg %%cl\n\t"
      "xorl %%edi, %%edi\n\t"
      "orl %%ecx, %%edx\n\t"
      "shll $5, %%edx\n\t"
      "orl %%esi, %%edx\n\t"
      "movl %%edx, 0xd8(%%eax)\n\t"
      "cmpl $0, (%%ebx)\n\t"
      "jle .LFUN_0017c2f0_9\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_0017c2f0_7:\n\t"
      "pushl $0x64\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movb -0x1(%%ebp), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_0017c2f0_8\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c17c140]\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      ".LFUN_0017c2f0_8:\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "incl %%edi\n\t"
      "movswl %%di, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jl .LFUN_0017c2f0_7\n\t"
      ".LFUN_0017c2f0_9:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      ".LFUN_0017c2f0_10:\n\t"
      "movl 0x60(%%esi), %%eax\n\t"
      "addl $0x60, %%esi\n\t"
      "cmpl $1, %%eax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jge .LFUN_0017c2f0_11\n\t"
      "movl $1, %%eax\n\t"
      ".LFUN_0017c2f0_11:\n\t"
      "incl %%eax\n\t"
      "orl $0x11100, %%eax\n\t"
      "movl %%eax, 0xd4(%%edi)\n\t"
      "movl (%%esi), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jle .LFUN_0017c2f0_30\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .LFUN_0017c2f0_13\n\t"
      ".LFUN_0017c2f0_12:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_0017c2f0_13:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl $0x70\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0017c2f0_14\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c17c1b0]\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      ".LFUN_0017c2f0_14:\n\t"
      "leal 0x2c(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[d1c90]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, 0x48(%%ecx,%%edx,4)\n\t"
      "movw 0x3e(%%ebx), %%di\n\t"
      "movw 0x3c(%%ebx), %%si\n\t"
      "addl $4, %%esp\n\t"
      "call *%[c17be50]\n\t"
      "movw 0x42(%%ebx), %%di\n\t"
      "movw 0x40(%%ebx), %%si\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "call *%[c17be50]\n\t"
      "movw 0x46(%%ebx), %%di\n\t"
      "movw 0x44(%%ebx), %%si\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c17be50]\n\t"
      "movw 0x4a(%%ebx), %%di\n\t"
      "movw 0x48(%%ebx), %%si\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "call *%[c17be50]\n\t"
      "movw 0x4c(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_15\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_16\n\t"
      ".LFUN_0017c2f0_15:\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_16:\n\t"
      "movswl %%si, %%eax\n\t"
      "movw 0x50(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl 0x2aebd0(,%%eax,4), %%ecx\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_17\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_18\n\t"
      ".LFUN_0017c2f0_17:\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_18:\n\t"
      "movswl %%si, %%edx\n\t"
      "movw 0x54(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl 0x2aebd0(,%%edx,4), %%eax\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_19\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_20\n\t"
      ".LFUN_0017c2f0_19:\n\t"
      "pushl $1\n\t"
      "pushl $0xe9\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_20:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movl 0x2aebd0(,%%ecx,4), %%edi\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c17bf20]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "shll $8, %%ecx\n\t"
      "orl %%edx, %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x88(%%esi,%%edx,4)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "shll $4, %%eax\n\t"
      "andl $0xf, %%edi\n\t"
      "orl %%edi, %%eax\n\t"
      "shll $4, %%eax\n\t"
      "andl $0xf, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "shll $4, %%eax\n\t"
      "andl $0xf, %%ecx\n\t"
      "orl %%ecx, %%eax\n\t"
      "movl %%eax, 0xb4(%%esi,%%edx,4)\n\t"
      "movw 0x5a(%%ebx), %%di\n\t"
      "movw 0x58(%%ebx), %%si\n\t"
      "call *%[c17c000]\n\t"
      "movw 0x5e(%%ebx), %%di\n\t"
      "movw 0x5c(%%ebx), %%si\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "call *%[c17c000]\n\t"
      "movw 0x62(%%ebx), %%di\n\t"
      "movw 0x60(%%ebx), %%si\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "call *%[c17c000]\n\t"
      "movw 0x66(%%ebx), %%di\n\t"
      "movw 0x64(%%ebx), %%si\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[c17c000]\n\t"
      "movw 0x68(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_21\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_22\n\t"
      ".LFUN_0017c2f0_21:\n\t"
      "pushl $1\n\t"
      "pushl $0x11f\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_22:\n\t"
      "movswl %%si, %%edx\n\t"
      "movw 0x6a(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl 0x2aebf4(,%%edx,4), %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_23\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_24\n\t"
      ".LFUN_0017c2f0_23:\n\t"
      "pushl $1\n\t"
      "pushl $0x11f\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_24:\n\t"
      "movswl %%si, %%ecx\n\t"
      "movw 0x6c(%%ebx), %%si\n\t"
      "testw %%si, %%si\n\t"
      "movl 0x2aebf4(,%%ecx,4), %%edi\n\t"
      "jl .LFUN_0017c2f0_25\n\t"
      "cmpw $9, %%si\n\t"
      "jl .LFUN_0017c2f0_26\n\t"
      ".LFUN_0017c2f0_25:\n\t"
      "pushl $1\n\t"
      "pushl $0x11f\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aed50\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_26:\n\t"
      "movw 0x6e(%%ebx), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "movswl %%si, %%edx\n\t"
      "movl 0x2aebf4(,%%edx,4), %%esi\n\t"
      "jl .LFUN_0017c2f0_27\n\t"
      "cmpw $6, %%ax\n\t"
      "jl .LFUN_0017c2f0_28\n\t"
      ".LFUN_0017c2f0_27:\n\t"
      "pushl $1\n\t"
      "pushl $0x12d\n\t"
      "pushl $0x2aed00\n\t"
      "pushl $0x2aef40\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_0017c2f0_28:\n\t"
      "movswl 0x6e(%%ebx), %%eax\n\t"
      "movl 0x2aec30(,%%eax,4), %%ecx\n\t"
      "testb $2, (%%ebx)\n\t"
      "je .LFUN_0017c2f0_29\n\t"
      "orl $4, %%ecx\n\t"
      ".LFUN_0017c2f0_29:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl -0x20(%%ebp), %%edx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "shll $8, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "shll $8, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "shll $8, %%eax\n\t"
      "orl %%edx, %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "shll $4, %%ecx\n\t"
      "movl %%eax, (%%ebx,%%edx,4)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "andl $0xf, %%esi\n\t"
      "orl %%esi, %%ecx\n\t"
      "shll $4, %%ecx\n\t"
      "andl $0xf, %%eax\n\t"
      "orl %%eax, %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "shll $4, %%ecx\n\t"
      "andl $0xf, %%edi\n\t"
      "orl %%edi, %%ecx\n\t"
      "incl %%eax\n\t"
      "movl %%ecx, 0x68(%%ebx,%%edx,4)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "jl .LFUN_0017c2f0_12\n\t"
      "movl %%ebx, %%edi\n\t"
      "jmp .LFUN_0017c2f0_31\n\t"
      ".LFUN_0017c2f0_30:\n\t"
      "movl $0xc0, %%eax\n\t"
      "movl $0x8200000, 0x88(%%edi)\n\t"
      "movl %%eax, 0xb4(%%edi)\n\t"
      "movl $0x18200000, (%%edi)\n\t"
      "movl %%eax, 0x68(%%edi)\n\t"
      ".LFUN_0017c2f0_31:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl $0xc, 0x20(%%edi)\n\t"
      "movl $0x1c00, 0x24(%%edi)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b17c2f0_assert), [exitfn] "m"(b17c2f0_exitfn), [c1906b0] "m"(b17c2f0_c1906b0), [memset] "m"(b17c2f0_memset), [c8f390] "m"(b17c2f0_c8f390), [elem] "m"(b17c2f0_elem), [c17c140] "m"(b17c2f0_c17c140), [c17c1b0] "m"(b17c2f0_c17c1b0), [d1c90] "m"(b17c2f0_d1c90), [c17be50] "m"(b17c2f0_c17be50), [c17bf20] "m"(b17c2f0_c17bf20), [c17c000] "m"(b17c2f0_c17c000)
      : "memory");
}
#else
#error "FUN_0017c2f0: clang naked draft required"
#endif


/* rasterizer_window_set_fog (0x17c790) — readable C lift. */
void rasterizer_window_set_fog(void)
{
  void *p;

  p = game_state_malloc((const char *)0x2af214, 0, 0x10);
  *(void **)0x47e4d0 = p;
  if (p == 0) {
    display_assert((const char *)0x2af1bc, (const char *)0x2af1ec, 0x121, 1);
    system_exit(-1);
  }
  FUN_00157010();
}

/* FUN_0017C7D0 (0x17c7d0) — readable C lift (jmp thunk). */
void FUN_0017C7D0(void)
{
  _rasterizer_reset_state();
}



/* rasterizer_environment_fog_screen_draw (0x17c8e0) — readable C lift (jmp thunk). */
void rasterizer_environment_fog_screen_draw(void)
{
  _rasterizer_window_get_fog(0);
}

/* rasterizer_environment_fog_screen_end (0x17c8f0) — XBE naked draft (batch 397). */
/* rasterizer_environment_fog_screen_end — readable C lift (jmp thunk). */
void rasterizer_environment_fog_screen_end(void *screen_fog)
{
  FUN_001579d0();
}

/* rasterizer_dynamic_lit_geometry_draw (0x17c930) — readable C lift. */
void rasterizer_dynamic_lit_geometry_draw(void *param_1, void *param_2)
{
  rasterizer_present(param_1, param_2);
}

/* 0x17c940 */
void rasterizer_dynamic_screen_geometry_draw(void)
{
  int eax = 0;

  rasterizer_memory_pool_delete();
  FUN_0015e9e0();
  FUN_00184690(0);
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
  ((void (*)(void))D3DDevice_Release)();
  /* mem[0x00476ab0] = 0 */
  /* test eax, eax -> je 0x155bf7 */

  (void)eax;
}

/* rasterizer_psuedo_dynamic_screen_quad_draw (0x17c960) — readable C lift. */
void rasterizer_psuedo_dynamic_screen_quad_draw(int param_1)
{
  FUN_0016f8a0(param_1);
}

/* rasterizer_widget_submit (0x17c970) — readable C lift. */
int rasterizer_widget_submit(int mode)
{
  return FUN_0015d170(mode);
}

/* 0x17c980 */
/* rasterizer_widget_begin — readable C lift (jmp thunk). */
void *rasterizer_widget_begin(int handle)
{
  FUN_0015ea70(handle);
}



/* rasterizer_widget_set_texture — readable C lift (jmp thunk). */
void rasterizer_widget_set_texture(int handle)
{
  FUN_0015eb90(handle);
}

/* rasterizer_widget_set_tint_factor (0x17c9a0) — readable C lift (nop/ret thunk). */
void rasterizer_widget_set_tint_factor(int handle)
{
  (void)handle;
}

/* rasterizer_widget_set_zbuffer_enable (0x17c9b0) — readable C lift. */
int rasterizer_widget_set_zbuffer_enable(int param_1, int param_2)
{
  return FUN_0015d310(param_1, param_2);
}

/* rasterizer_widget_draw_sprite2d (0x17c9c0) — readable C lift. */
short rasterizer_widget_draw_sprite2d(int dynamic_vertex_buffer_index)
{
  return FUN_0015d480(dynamic_vertex_buffer_index);
}

/* rasterizer_widget_draw_sprite3d (0x17c9d0) — readable C lift. */
int rasterizer_widget_draw_sprite3d(int zbuf_result)
{
  return FUN_0015ec50(zbuf_result);
}

/* rasterizer_widget_end (0x17c9e0) — XBE naked draft (batch 398). */
/* rasterizer_widget_end — readable C lift (jmp thunk). */
void rasterizer_widget_end(int handle)
{
  FUN_0015ee80();
}

/* rasterizer_widget_submit_occlusion_test (0x17c9f0) — readable C lift (nop/ret thunk). */
void rasterizer_widget_submit_occlusion_test(int handle)
{
  (void)handle;
}

/* rasterizer_widget_get_occlusion_test_result (0x17ca00) — readable C lift (jmp thunk). */
void rasterizer_widget_get_occlusion_test_result(void)
{
  FUN_0015a700();
}



/* rasterizer_hud_motion_sensor_blip_begin (0x17ca10) — readable C lift (jmp thunk). */
void rasterizer_hud_motion_sensor_blip_begin(void)
{
  FUN_0015a7f0(0, 0, 0, 0);
}

/* rasterizer_hud_motion_sensor_blip_draw (0x17ca20) — readable C lift (jmp thunk). */
void rasterizer_hud_motion_sensor_blip_draw(void)
{
  FUN_0015a8f0(0, 0, 0, 0, 0, 0);
}

/* rasterizer_hud_motion_sensor_blip_end (0x17ca30) — readable C lift (jmp thunk). */
void rasterizer_hud_motion_sensor_blip_end(void)
{
  FUN_0015a4c0();
}



/* FUN_0017ca40 (0x17ca40) — readable C lift (jmp thunk). */
void FUN_0017ca40(void)
{
  FUN_0015aa40();
}


