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

/* rasterizer_transparent_geometry_group_draw: draw one sorted transparent
 * geometry group, dispatching per shader type (generic/chicago/glass/meter/
 * plasma/water), handling extra layers via self-recursion, predicted shader
 * pre-pass, debug tint mode, and secondary (dirty) group passes (0x174d10) */
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
