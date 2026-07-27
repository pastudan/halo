/* FUN_0017ff50: stub (0x17ff50) */
void FUN_0017ff50(void)
{
}

/* rasterizer_frame_statistics.c */

/* FUN_0017ff60 (0x17ff60) — readable C lift. */
extern char DAT_002af728[];
void FUN_0017ff60(void)
{
  void *p;

  p = *(void **)0x47ec40;
  if (p != NULL)
    debug_free(p, DAT_002af728, 0x345);
}

/* rasterizer_geometry.c */

/* scale byte 0-255 to float via constant at 0x261518 (0x17ff80) */
float FUN_0017ff80(unsigned char param_1)
{
  return (float)param_1 * *(float *)0x261518;
}

/* scale signed short to float: (2*param_1 + 1.0f) * scale (0x17ffa0) */
float FUN_0017ffa0(short param_1)
{
  return ((float)(int)param_1 + (float)(int)param_1 + *(float *)0x2533c8) *
         *(float *)0x2647f4;
}

/* decode packed 32-bit normal to float[3] output, returns param_1 (0x17ffc0) */
float *FUN_0017ffc0(float *param_1, unsigned int param_2)
{
  float fVar1;
  fVar1 = (float)(int)((param_2 >> 0xb) << 0x15) * *(float *)0x29ba04;
  *param_1 =
    ((float)(int)(param_2 << 0x15) * *(float *)0x29ba04 + *(float *)0x2533c8) *
    *(float *)0x2afe34;
  param_1[1] = (fVar1 + *(float *)0x2533c8) * *(float *)0x2afe34;
  param_1[2] = ((float)(int)(param_2 & 0xffc00000) * *(float *)0x2afe30 +
                *(float *)0x2533c8) *
               *(float *)0x28c8e0;
  return param_1;
}

/* FUN_00180050 (0x180050) — readable C lift from XBE leaf. */
int FUN_00180050(short param_1)
{
  extern char DAT_002a0228[];
  extern char DAT_002afe38[];

  if (param_1 < 0 || param_1 >= 0xc) {
    display_assert(DAT_002a0228, DAT_002afe38, 0xaa, true);
    system_exit(-1);
  }
  return (int)*(short *)(0x2afe14 + (int)param_1 * 2);
}




/* FUN_001800b0 (0x1800b0) — readable C lift (restored pre-naked). */

void FUN_001800b0(short param_1, int param_2, int param_3, int param_4,
                  int param_5, int param_6)
{
  /* Three 12-byte (3-float) scratch buffers for FUN_0017ffc0 output */
  float buf_c[3]; /* at EBP-0xc */
  float buf_18[3]; /* at EBP-0x18 */
  float buf_24[3]; /* at EBP-0x24 */

  /* temp for MOVSX + FILD idiom: param_1 slot reused as int temp */
  int temp_int;

  float weight0;
  float *result;
  int i;
  int count;
  unsigned int *in32;
  unsigned int *out32;
  unsigned char *in8;
  signed short *in16;
  unsigned char node0_byte;
  unsigned char node1_byte;

  if (param_3 == 0) {
    display_assert("uncompressed",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x118,
                   1);
    system_exit(-1);
  }
  if (param_5 == 0) {
    display_assert("compressed",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x119,
                   1);
    system_exit(-1);
  }

  if (param_1 == 1) {
    /* environment_vertex: uncompressed=56 bytes, compressed=32 bytes */
    count = param_2;
    if (param_2 * 0x38 != param_4) {
      display_assert("count*sizeof(struct "
                     "environment_vertex_uncompressed)==uncompressed_size",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c",
                     0x11f, 1);
      system_exit(-1);
    }
    if ((count << 5) != param_6) {
      display_assert(
        "count*sizeof(struct environment_vertex_compressed)==compressed_size",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x120, 1);
      system_exit(-1);
    }
    if (count > 0) {
      /* ESI = out+0x18, EDI = in+0x10 at loop entry */
      out32 = (unsigned int *)(param_3 + 0x18);
      in32 = (unsigned int *)(param_5 + 0x10);
      for (i = 0; i < count; i++) {
        /* copy position xyz (3 dwords) from in[0..8] to out[0..8] */
        out32[-6] = in32[-4];
        out32[-5] = in32[-3];
        out32[-4] = in32[-2];
        /* unpack normal from in[12] into buf_24 */
        result = FUN_0017ffc0(buf_24, in32[-1]);
        out32[-3] = ((unsigned int *)result)[0];
        out32[-2] = ((unsigned int *)result)[1];
        out32[-1] = ((unsigned int *)result)[2];
        /* unpack binormal from in[16] into buf_18 */
        result = FUN_0017ffc0(buf_18, in32[0]);
        out32[0] = ((unsigned int *)result)[0];
        out32[1] = ((unsigned int *)result)[1];
        out32[2] = ((unsigned int *)result)[2];
        /* unpack tangent from in[20] into buf_c */
        result = FUN_0017ffc0(buf_c, in32[1]);
        out32[3] = ((unsigned int *)result)[0];
        out32[4] = ((unsigned int *)result)[1];
        out32[5] = ((unsigned int *)result)[2];
        /* copy texcoords (2 raw dwords) from in[24..28] to out[48..52] */
        out32[6] = in32[2];
        out32[7] = in32[3];
        /* advance: out += 56 bytes = 14 dwords, in += 32 bytes = 8 dwords */
        out32 += 14;
        in32 += 8;
      }
    }
  } else if (param_1 == 3) {
    /* environment_lightmap_vertex: uncompressed=20 bytes, compressed=8 bytes */
    count = param_2;
    if (param_2 * 0x14 != param_4) {
      display_assert(
        "count*sizeof(struct "
        "environment_lightmap_vertex_uncompressed)==uncompressed_size",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x133, 1);
      system_exit(-1);
    }
    if (param_2 * 8 != param_6) {
      display_assert("count*sizeof(struct "
                     "environment_lightmap_vertex_compressed)==compressed_size",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c",
                     0x134, 1);
      system_exit(-1);
    }
    if (count > 0) {
      /* ESI = out+0x10, EDI = in+0x6 at loop entry */
      out32 = (unsigned int *)(param_3 + 0x10);
      in16 = (signed short *)(param_5 + 6);
      for (i = 0; i < count; i++) {
        /* unpack normal from in[0] into buf_24 */
        result = FUN_0017ffc0(buf_24, *(unsigned int *)(in16 - 3));
        out32[-4] = ((unsigned int *)result)[0];
        out32[-3] = ((unsigned int *)result)[1];
        out32[-2] = ((unsigned int *)result)[2];
        /* texcoord u: (s16 * 2 + 1) * (1/65535) -- in[4] */
        temp_int = (int)in16[-1];
        *(float *)(out32 - 1) =
          ((float)temp_int + (float)temp_int + 1.0f) * (1.0f / 65535.0f);
        /* texcoord v: (s16 * 2 + 1) * (1/65535) -- in[6] */
        temp_int = (int)in16[0];
        *(float *)out32 =
          ((float)temp_int + (float)temp_int + 1.0f) * (1.0f / 65535.0f);
        /* advance: out += 20 bytes = 5 dwords, in += 8 bytes = 4 shorts */
        out32 += 5;
        in16 += 4;
      }
    }
  } else {
    if (param_1 != 5) {
      error(2, "### ERROR can't uncompress this type of vertex buffer");
      return;
    }
    /* model_vertex: uncompressed=68 bytes, compressed=32 bytes */
    count = param_2;
    if (param_2 * 0x44 != param_4) {
      display_assert(
        "count*sizeof(struct model_vertex_uncompressed)==uncompressed_size",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x145, 1);
      system_exit(-1);
    }
    if ((count << 5) != param_6) {
      display_assert(
        "count*sizeof(struct model_vertex_compressed)==compressed_size",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x146, 1);
      system_exit(-1);
    }
    if (count > 0) {
      /* ESI = out+0x18, EDI = in+0x10 at loop entry */
      out32 = (unsigned int *)(param_3 + 0x18);
      in32 = (unsigned int *)(param_5 + 0x10);
      for (i = 0; i < count; i++) {
        /* copy position xyz from in[0..8] to out[0..8] */
        out32[-6] = in32[-4];
        out32[-5] = in32[-3];
        out32[-4] = in32[-2];
        /* unpack normal from in[12] into buf_c */
        result = FUN_0017ffc0(buf_c, in32[-1]);
        out32[-3] = ((unsigned int *)result)[0];
        out32[-2] = ((unsigned int *)result)[1];
        out32[-1] = ((unsigned int *)result)[2];
        /* unpack binormal from in[16] into buf_18 */
        result = FUN_0017ffc0(buf_18, in32[0]);
        out32[0] = ((unsigned int *)result)[0];
        out32[1] = ((unsigned int *)result)[1];
        out32[2] = ((unsigned int *)result)[2];
        /* unpack tangent from in[20] into buf_24 */
        result = FUN_0017ffc0(buf_24, in32[1]);
        out32[3] = ((unsigned int *)result)[0];
        out32[4] = ((unsigned int *)result)[1];
        out32[5] = ((unsigned int *)result)[2];
        /* texcoord u: (s16*2+1)*(1/65535) from in[24] */
        temp_int = (int)*(signed short *)((int)in32 + 8);
        *(float *)(out32 + 6) =
          ((float)temp_int + (float)temp_int + 1.0f) * (1.0f / 65535.0f);
        /* texcoord v: (s16*2+1)*(1/65535) from in[26] */
        temp_int = (int)*(signed short *)((int)in32 + 10);
        *(float *)(out32 + 7) =
          ((float)temp_int + (float)temp_int + 1.0f) * (1.0f / 65535.0f);
        /* node_index[0] = in[28] / 3 (assert in[28] % 3 == 0) */
        in8 = (unsigned char *)in32;
        node0_byte = in8[12];
        node1_byte = in8[13];
        if ((unsigned int)node0_byte % 3 != 0) {
          display_assert("src->nodes[0]%3==0",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c",
                         0x155, 1);
          system_exit(-1);
        }
        if ((unsigned int)node1_byte % 3 != 0) {
          display_assert("src->nodes[1]%3==0",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c",
                         0x156, 1);
          system_exit(-1);
        }
        /* node_index stored as short = byte / 3 */
        *(short *)(out32 + 8) = (short)((int)node0_byte / 3);
        *((short *)(out32 + 8) + 1) = (short)((int)node1_byte / 3);
        /* weight0 = in[30] * (1/255.0f); weight1 = 1.0f - weight0 */
        weight0 = (float)(int)in8[14] * (1.0f / 255.0f);
        *(float *)(out32 + 9) = weight0;
        *(float *)(out32 + 10) = 1.0f - weight0;
        /* advance: out += 68 bytes = 17 dwords, in += 32 bytes = 8 dwords */
        out32 += 17;
        in32 += 8;
      }
    }
  }
}


/* FUN_00180500 (0x180500) — readable C lift from XBE leaf. */
void FUN_00180500(float *src, float *dst)
{
  extern char DAT_0029cb70[];
  extern char DAT_002afe38[];
  extern char DAT_0025bb20[];

  if (src == 0) {
    display_assert(DAT_0029cb70, DAT_002afe38, 0x1b6, true);
    system_exit(-1);
  }
  if (dst == 0) {
    display_assert(DAT_0025bb20, DAT_002afe38, 0x1b7, true);
    system_exit(-1);
  }
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}




/* rasterizer_geometry_vertex_get_normal: unpack normal from compressed vertex
 * +0xc (0x180570) */
void FUN_00180570(int param_1, float *param_2)
{
  float local_out[3];
  float *result;
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1c2,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("normal",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1c3,
                   1);
    system_exit(-1);
  }
  result = FUN_0017ffc0(local_out, *(unsigned int *)(param_1 + 0x0c));
  param_2[0] = result[0];
  param_2[1] = result[1];
  param_2[2] = result[2];
}

/* FUN_001805f0 (0x1805f0) — readable C lift from XBE leaf. */
void FUN_001805f0(int *src, float *dst)
{
  extern char DAT_0029cb70[];
  extern char DAT_002afe38[];
  extern char DAT_002b0094[];

  if (src == 0) {
    display_assert(DAT_0029cb70, DAT_002afe38, 0x1ce, true);
    system_exit(-1);
  }
  if (dst == 0) {
    display_assert(DAT_002b0094, DAT_002afe38, 0x1cf, true);
    system_exit(-1);
  }
  *(int *)dst = src[6];
  *((int *)dst + 1) = src[7];
}




/* rasterizer_geometry_vertex_get_normal_packed: unpack normal from packed value
 * ptr (0x180660) */
void FUN_00180660(unsigned int *param_1, float *param_2)
{
  float local_out[3];
  float *result;
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1da,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("normal",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1db,
                   1);
    system_exit(-1);
  }
  result = FUN_0017ffc0(local_out, *param_1);
  param_2[0] = result[0];
  param_2[1] = result[1];
  param_2[2] = result[2];
}

/* rasterizer_geometry_vertex_get_texcoord_short: decode compressed short
 * texcoords from vertex to float[2] output (0x1806e0) */
void FUN_001806e0(int param_1, float *param_2)
{
  if (param_1 == 0) {
    display_assert("vertex",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1e6,
                   1);
    system_exit(-1);
  }
  if (param_2 == 0) {
    display_assert("texcoord",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x1e7,
                   1);
    system_exit(-1);
  }
  *param_2 = ((float)(int)*(short *)(param_1 + 4) +
              (float)(int)*(short *)(param_1 + 4) + *(float *)0x2533c8) *
             *(float *)0x2647f4;
  param_2[1] = ((float)(int)*(short *)(param_1 + 6) +
                (float)(int)*(short *)(param_1 + 6) + *(float *)0x2533c8) *
               *(float *)0x2647f4;
}

extern double floor(double);

/* FUN_001807d0 (0x1807d0) — readable C lift from XBE leaf. */
unsigned char FUN_001807d0(float param_1)
{
  float v;

  v = param_1;
  if (v < *(float *)0x2533c0)
    v = *(float *)0x2533c0;
  else if (v > *(float *)0x2533c8)
    v = *(float *)0x2533c8;
  v = v * *(float *)0x2602c8;
  return (unsigned char)(int)(v + 0.5f);
}


/* FUN_001808f0 (0x1808f0) — XBE naked draft (batch 317). */
#if defined(__clang__)
static void (*const b1808f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1808f0_exitfn)(int) = system_exit;
static char * (*const b1808f0_c8d9d0)(char *buffer, const char *format, ...) = (void *)csprintf;
static double (*const b1808f0_c1d9c2b)(double x) = (void *)floor;
static float * (*const b1808f0_c17ffc0)(float *param_1, unsigned int param_2) = (void *)FUN_0017ffc0;

__attribute__((naked, noinline))
unsigned int FUN_001808f0(float *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_001808f0_1\n\t"
      "pushl $1\n\t"
      "pushl $0x45\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2a3e7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_1:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001808f0_2\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_001808f0_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001808f0_2\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001808f0_3\n\t"
      ".LFUN_001808f0_2:\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "flds 0x8(%%esi)\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $1\n\t"
      "pushl $0x4e\n\t"
      "pushl $0x2afe38\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "subl $0x18, %%esp\n\t"
      "fstpl 0x10(%%esp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fstpl 0x8(%%esp)\n\t"
      "flds (%%esi)\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x2b011c\n\t"
      "pushl $0x5ab100\n\t"
      "call *%[c8d9d0]\n\t"
      "addl $0x2c, %%esp\n\t"
      "pushl %%eax\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_3:\n\t"
      "flds (%%esi)\n\t"
      "subl $8, %%esp\n\t"
      "fmuls 0x2b0118\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x2b0118\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "subl $8, %%esp\n\t"
      "andl $0x7ff, %%edi\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x2b0114\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "andl $0x7ff, %%ebx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x3ff, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "orl %%ebx, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "orl %%edi, %%ebx\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_4\n\t"
      "pushl $1\n\t"
      "pushl $0x5c\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_4:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_5\n\t"
      "pushl $1\n\t"
      "pushl $0x5d\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_5:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_001808f0_6\n\t"
      "pushl $1\n\t"
      "pushl $0x5e\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001808f0_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1808f0_assert), [exitfn] "m"(b1808f0_exitfn), [c8d9d0] "m"(b1808f0_c8d9d0), [c1d9c2b] "m"(b1808f0_c1d9c2b), [c17ffc0] "m"(b1808f0_c17ffc0)
      : "memory");
}
#else
#error "FUN_001808f0: clang naked draft required"
#endif


/* FUN_00180b10 (0x180b10) — XBE naked draft (batch 305). */
#if defined(__clang__)
static void (*const b180b10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180b10_exitfn)(int) = system_exit;
static double (*const b180b10_c1d9c2b)(double x) = (void *)floor;
static float * (*const b180b10_c17ffc0)(float *param_1, unsigned int param_2) = (void *)FUN_0017ffc0;

__attribute__((naked, noinline))
unsigned int FUN_00180b10(float *param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00180b10_1\n\t"
      "pushl $1\n\t"
      "pushl $0x68\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2a3e7c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_1:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_2\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_4\n\t"
      ".LFUN_00180b10_2:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_3\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_4\n\t"
      ".LFUN_00180b10_3:\n\t"
      "flds (%%esi)\n\t"
      ".LFUN_00180b10_4:\n\t"
      "fmuls 0x2b0118\n\t"
      "pushl %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "movl -0x4(%%ebp), %%ebx\n\t"
      "andl $0x7ff, %%ebx\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_5\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_7\n\t"
      ".LFUN_00180b10_5:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_6\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_7\n\t"
      ".LFUN_00180b10_6:\n\t"
      "flds 0x4(%%esi)\n\t"
      ".LFUN_00180b10_7:\n\t"
      "fmuls 0x2b0118\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x255e94\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "andl $0x7ff, %%edi\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00180b10_8\n\t"
      "flds 0x255e94\n\t"
      "jmp .LFUN_00180b10_10\n\t"
      ".LFUN_00180b10_8:\n\t"
      "flds 0x8(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00180b10_9\n\t"
      "flds 0x2533c8\n\t"
      "jmp .LFUN_00180b10_10\n\t"
      ".LFUN_00180b10_9:\n\t"
      "flds 0x8(%%esi)\n\t"
      ".LFUN_00180b10_10:\n\t"
      "fmuls 0x2b0114\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "andl $0x3ff, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "orl %%edi, %%eax\n\t"
      "shll $0xb, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "orl %%ebx, %%edi\n\t"
      "leal -0x10(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fsubs (%%esi)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "popl %%ebx\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_11\n\t"
      "pushl $1\n\t"
      "pushl $0x76\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00fc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_11:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fsubs 0x4(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_12\n\t"
      "pushl $1\n\t"
      "pushl $0x77\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00e4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fsubs 0x8(%%esi)\n\t"
      "fabs\n\t"
      "fcompl 0x28b800\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00180b10_13\n\t"
      "pushl $1\n\t"
      "pushl $0x78\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b00cc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180b10_13:\n\t"
      "movl %%edi, %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180b10_assert), [exitfn] "m"(b180b10_exitfn), [c1d9c2b] "m"(b180b10_c1d9c2b), [c17ffc0] "m"(b180b10_c17ffc0)
      : "memory");
}
#else
#error "FUN_00180b10: clang naked draft required"
#endif


/* FUN_00180d10 (0x180d10) — XBE naked draft (batch 304). */
#if defined(__clang__)
static void (*const b180d10_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b180d10_exitfn)(int) = system_exit;
static void (*const b180d10_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;
static unsigned int (*const b180d10_c180b10)(float *param_1) = (void *)FUN_00180b10;
static short (*const b180d10_c180890)(float f) = (void *)FUN_00180890;

__attribute__((naked, noinline))
void FUN_00180d10(short type __attribute__((unused)), int count __attribute__((unused)), int compressed_out __attribute__((unused)), int compressed_size __attribute__((unused)), void *uncompressed __attribute__((unused)), int uncompressed_size __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .LFUN_00180d10_1\n\t"
      "pushl $1\n\t"
      "pushl $0xc2\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0084\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_1:\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00180d10_2\n\t"
      "pushl $1\n\t"
      "pushl $0xc3\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x263b58\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_2:\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00180d10_11\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00180d10_7\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00180d10_3\n\t"
      "pushl $0x2b0140\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x44, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00180d10_4\n\t"
      "pushl $1\n\t"
      "pushl $0xef\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2b0008\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_4:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_5\n\t"
      "pushl $1\n\t"
      "pushl $0xf0\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2affc4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_5:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $0x10, %%edi\n\t"
      "addl $0x18, %%esi\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00180d10_6:\n\t"
      "leal -0x18(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x10(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "leal -0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0x8(%%edi)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0xa(%%edi)\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "movb $3, %%cl\n\t"
      "imulb %%cl\n\t"
      "movb %%al, 0xc(%%edi)\n\t"
      "movb 0x22(%%esi), %%al\n\t"
      "movb %%cl, %%dl\n\t"
      "imulb %%dl\n\t"
      "movb %%al, 0xd(%%edi)\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, 0xe(%%edi)\n\t"
      "addl $0x18, %%esp\n\t"
      "addl $0x44, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_6\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_7:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "leal (%%ebx,%%ebx,4), %%ecx\n\t"
      "shll $2, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_8\n\t"
      "pushl $1\n\t"
      "pushl $0xdd\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2aff48\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_8:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal (,%%ebx,8), %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "je .LFUN_00180d10_9\n\t"
      "pushl $1\n\t"
      "pushl $0xde\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afef8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_9:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $6, %%edi\n\t"
      "addl $0x10, %%esi\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00180d10_10:\n\t"
      "leal -0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, -0x6(%%edi)\n\t"
      "movl -0x4(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, -0x2(%%edi)\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c180890]\n\t"
      "movw %%ax, (%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x14, %%esi\n\t"
      "addl $8, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_10\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00180d10_11:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl %%ebx, %%eax\n\t"
      "imull $0x38, %%eax, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00180d10_12\n\t"
      "pushl $1\n\t"
      "pushl $0xc9\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afeb0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_12:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%ebx, %%ecx\n\t"
      "shll $5, %%ecx\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00180d10_13\n\t"
      "pushl $1\n\t"
      "pushl $0xca\n\t"
      "pushl $0x2afe38\n\t"
      "pushl $0x2afe68\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00180d10_13:\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jle .LFUN_00180d10_15\n\t"
      "addl $0x10, %%edi\n\t"
      "addl $0x18, %%esi\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00180d10_14:\n\t"
      "leal -0x18(%%esi), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "leal -0x10(%%edi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "leal -0xc(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c180b10]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x4(%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "leal 0xc(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, (%%edi)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%edx, 0x8(%%edi)\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x38, %%esi\n\t"
      "addl $0x20, %%edi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00180d10_14\n\t"
      ".LFUN_00180d10_15:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b180d10_assert), [exitfn] "m"(b180d10_exitfn), [c8f390] "m"(b180d10_c8f390), [c180b10] "m"(b180d10_c180b10), [c180890] "m"(b180d10_c180890)
      : "memory");
}
#else
#error "FUN_00180d10: clang naked draft required"
#endif


/* rasterizer_lights.c */

/* FUN_00181150 (0x181150) — readable C lift from XBE leaf. */
void FUN_00181150(void)
{
  csmemset((void *)0x4bed80, 0, 0x7722);
  csmemset((void *)0x47ed60, 0, 0x40020);
  *(int *)0x4d0480 = 0;
}




/* rasterizer_lights_reset_stat: zero stat counter at 0x5a37e0 (0x1812b0) */
void FUN_001812b0(void)
{
  *(int *)0x5a37e0 = 0;
}

/* FUN_00181410: stub (0x181410) */
void FUN_00181410(void)
{
}

/* FUN_00181900 (0x181900) — XBE naked draft (batch 369). */
#if defined(__clang__)
static void * (*const b181900_c18e3c0)(void) = (void *)global_scenario_get;
static void *(*const b181900_elem)(void *, int, int) = tag_block_get_element;
static void (*const b181900_perp)(float *, float *) = perpendicular3d;
static float (*const b181900_norm)(float *) = normalize3d;
static unsigned int (*const b181900_c180b10)(float *param_1) = (void *)FUN_00180b10;
static void *(*const b181900_tag)(int, int) = tag_get;
static void (*const b181900_c181670)(int *params) = (void *)FUN_00181670;

__attribute__((naked, noinline))
void FUN_00181900(short param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x54, %%esp\n\t"
      "movb 0x3256d7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181900_5\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181900_5\n\t"
      "jne .LFUN_00181900_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181900_5\n\t"
      ".LFUN_00181900_1:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c18e3c0]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl 0x8(%%ebp), %%eax\n\t"
      "pushl $0x68\n\t"
      "pushl %%eax\n\t"
      "leal 0x134(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw %%bx, 0x42(%%eax)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jbe .LFUN_00181900_4\n\t"
      "leal 0x128(%%esi), %%edx\n\t"
      "addl $0x11c, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181900_3\n\t"
      ".LFUN_00181900_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00181900_3:\n\t"
      "movzwl 0x40(%%eax), %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "addl %%ebx, %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movzbl 0xf(%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movsbl 0xd(%%esi), %%ecx\n\t"
      "movsbl 0xe(%%esi), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movsbl 0xc(%%esi), %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "fmuls 0x2820c0\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "call *%[perp]\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c180b10]\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x44(%%ebp)\n\t"
      "call *%[c180b10]\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6c656e73\n\t"
      "call *%[tag]\n\t"
      "movl %%eax, -0x54(%%ebp)\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, -0x50(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movw %%ax, -0x38(%%ebp)\n\t"
      "movb 0x50654a, %%al\n\t"
      "movl %%edi, %%edx\n\t"
      "leal -0x54(%%ebp), %%ecx\n\t"
      "sarl $0x10, %%edx\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x31(%%ebp)\n\t"
      "movw %%dx, -0x36(%%ebp)\n\t"
      "movw %%di, -0x34(%%ebp)\n\t"
      "movb %%al, -0x32(%%ebp)\n\t"
      "call *%[c181670]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "addl $0x3c, %%esp\n\t"
      "incl %%ebx\n\t"
      "movzwl 0x42(%%edx), %%eax\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "jl .LFUN_00181900_2\n\t"
      "popl %%edi\n\t"
      ".LFUN_00181900_4:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181900_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c18e3c0] "m"(b181900_c18e3c0), [elem] "m"(b181900_elem), [perp] "m"(b181900_perp), [norm] "m"(b181900_norm), [c180b10] "m"(b181900_c180b10), [tag] "m"(b181900_tag), [c181670] "m"(b181900_c181670)
      : "memory");
}
#else
#error "FUN_00181900: clang naked draft required"
#endif


/* FUN_00181a90 (0x181a90) — XBE naked draft (batch 356). */
#if defined(__clang__)
static void (*const b181a90_c16f910)(int16_t profile) = (void *)FUN_0016f910;
static void (*const b181a90_c17cfc0)(int param_1, int param_2) = (void *)FUN_0017cfc0;
static int * (*const b181a90_c181020)(short index) = (void *)FUN_00181020;
static float * (*const b181a90_c17ffc0)(float *param_1, unsigned int param_2) = (void *)FUN_0017ffc0;
static void (*const b181a90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181a90_exitfn)(int) = system_exit;
static float *(*const b181a90_vsca)(float *, float *, float, float *) = vector3d_scale_add;
static int (*const b181a90_c17d030)(float *position, int vis_index, int index) = (void *)FUN_0017d030;
static void (*const b181a90_c17d020)(void) = (void *)FUN_0017d020;
static void (*const b181a90_c16fa40)(int16_t profile) = (void *)FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00181a90(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl $0x17\n\t"
      "call *%[c16f910]\n\t"
      "movb 0x3256d7, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181a90_11\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181a90_11\n\t"
      "jne .LFUN_00181a90_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181a90_11\n\t"
      ".LFUN_00181a90_1:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x5a5bc0\n\t"
      "jne .LFUN_00181a90_10\n\t"
      "cmpl %%ebx, 0x4d0480\n\t"
      "jle .LFUN_00181a90_10\n\t"
      "pushl $1\n\t"
      "pushl $6\n\t"
      "call *%[c17cfc0]\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "jle .LFUN_00181a90_9\n\t"
      "pushl %%esi\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00181a90_2:\n\t"
      "movl %%ebx, %%esi\n\t"
      "call *%[c181020]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x10(%%edi), %%eax\n\t"
      "movl (%%edi), %%esi\n\t"
      "pushl %%eax\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movzbl 0x22(%%edi), %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw 0x5a5bc2, %%ax\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "jne .LFUN_00181a90_8\n\t"
      "movswl 0x14(%%esi), %%eax\n\t"
      "subl $0, %%eax\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "je .LFUN_00181a90_5\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00181a90_4\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00181a90_3\n\t"
      "pushl $1\n\t"
      "pushl $0x1e2\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b05ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00181a90_7\n\t"
      ".LFUN_00181a90_3:\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00181a90_7\n\t"
      ".LFUN_00181a90_4:\n\t"
      "flds 0x10(%%esi)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "fmuls 0x254e68\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%ecx\n\t"
      "leal 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "jmp .LFUN_00181a90_6\n\t"
      ".LFUN_00181a90_5:\n\t"
      "flds 0x10(%%esi)\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fchs\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl $0x5a5bd4\n\t"
      "leal 0x4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00181a90_6:\n\t"
      "call *%[vsca]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00181a90_7:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17d030]\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%eax, 0x24(%%edi)\n\t"
      ".LFUN_00181a90_8:\n\t"
      "movl 0x4d0480, %%ecx\n\t"
      "incl %%ebx\n\t"
      "movswl %%bx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jl .LFUN_00181a90_2\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      ".LFUN_00181a90_9:\n\t"
      "call *%[c17d020]\n\t"
      ".LFUN_00181a90_10:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181a90_11:\n\t"
      "pushl $0x17\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b181a90_c16f910), [c17cfc0] "m"(b181a90_c17cfc0), [c181020] "m"(b181a90_c181020), [c17ffc0] "m"(b181a90_c17ffc0), [assert] "m"(b181a90_assert), [exitfn] "m"(b181a90_exitfn), [vsca] "m"(b181a90_vsca), [c17d030] "m"(b181a90_c17d030), [c17d020] "m"(b181a90_c17d020), [c16fa40] "m"(b181a90_c16fa40)
      : "memory");
}
#else
#error "FUN_00181a90: clang naked draft required"
#endif


/* FUN_00181c20 (0x181c20) — readable C lift (restored pre-naked). */

void FUN_00181c20(void)
{
  /* atan2 from libm (used for flare screen-angle computation) */
  extern double atan2(double, double);

  /* Outer loop state */
  int lf_count; /* DAT_004d0480 */
  int i; /* outer loop counter (ESI, sign-extended as CX) */
  int outer_ctr; /* [EBP-0x78] inner loop index within outer */
  int *entry; /* lens flare queue entry: &DAT_004c6480 + i*0x28 (EBX) */
  unsigned char *light_data; /* return of FUN_00181060 (ESI after call) */
  float *dir_ptr; /* FUN_0017ffc0 return (3-float decoded direction) */
  int definition; /* entry[0] = tag definition ptr (EDI) */

  /* Relative position of flare to camera */
  float delta[3]; /* [EBP-0x18/-0x14/-0x10] entry - camera (contiguous array for normalize3d) */
  float view_dot; /* [EBP-0x1c] dot(fwd, delta) */

  /* Reflection billboard offset */
  float refl_off_x; /* [EBP-0x48] */
  float refl_off_y; /* [EBP-0x44] */
  float refl_off_z; /* [EBP-0x40] */

  /* Decoded perpendicular direction of the flare (from FUN_0017ffc0) */
  float dir_local[3]; /* [EBP-0xb4] buffer passed to FUN_0017ffc0 (12 bytes) */
  float dir_x; /* [EBP-0x68] copy of dir_ptr[0] = local_6c */
  float dir_y; /* [EBP-0x64] copy of dir_ptr[1] = local_68 */
  float dir_z; /* [EBP-0x60] copy of dir_ptr[2] = local_64 */

  /* Per-flare scalar values */
  float brightness_byte; /* [EBP-0x28] *light_data * scale = local_2c */
  float entry_x; /* [EBP-0x74] entry[1] (float) */
  float entry_y; /* [EBP-0x70] entry[2] */
  float entry_z; /* [EBP-0x6c] entry[3] */

  /* Occlusion/brightness accumulator */
  float brightness; /* [EBP-0xc] accumulated brightness = local_10 */
  float depth_scale; /* [EBP-0x4] = local_8 */
  float depth_bias; /* [EBP-0x8] = local_c */

  /* Corona rotation */
  float
    corona_rot; /* [EBP-0x9c] = local_9c, output of FUN_00181420 * def[0x84] */
  float flare_angle; /* [EBP-0xa0] = local_a0, fpatan result * scale */

  /* Visibility array [5]: [0]=1.0, [1]=near_clip, [2]=direction, [3]=backward,
   * [4]=rotation_fn */
  float vis[5]; /* [EBP-0x8c] = local_90 */

  /* Second loop (sun glow) */
  short sun_i; /* [sVar13] second loop counter */
  int sun_entry; /* pointer into lens flare queue for sun glow */

  /* Inner reflection loop */
  int refl_idx; /* [EBP-0x2c] reflection loop counter = local_30 */
  int refl_count; /* *(int *)(definition + 0xc4) */
  void *refl; /* tag_block_get_element result = puVar8 */
  int refl_ivar; /* iVar7 inner loop counter */

  /* Reflection color */
  unsigned int color; /* packed ARGB for FUN_0017d010 (uVar11) */
  unsigned int tex_flags; /* [EBP-0x5c] local_60 */
  float anim_alpha; /* [EBP-0x58] local_5c */
  float anim_r; /* [EBP-0x54] local_58 */
  float anim_g; /* [EBP-0x50] local_54 */
  float anim_b; /* [EBP-0x4c] local_50 */

  /* Animation color: alpha from scalars_interpolate, RGB[3] from FUN_0007c270.
   * In MSVC layout: anim_alpha_out at EBP-0x3c (local_40),
   * anim_rgb[0..2] at EBP-0x38/0x34/0x30 (local_3c/38/34). */
  float anim_alpha_out; /* [EBP-0x3c] = local_40, from scalars_interpolate */
  float anim_rgb[3];    /* [EBP-0x38..0x30] = local_3c/38/34, from FUN_0007c270 */

  /* Reflection size and position output */
  float refl_size;       /* current reflection size (local_8 reused = local_c in Ghidra) */
  float refl_anim;       /* animation period result (local_8 reused again) */
  float flare_size_angle; /* [EBP-0x24] = local_28, rotation + offset */
  float pos[3];          /* [EBP-0xa8..0xa0]: billboard position x/y/z */
  float scale2d[2];      /* [EBP-0x94] = local_98/local_94 */
  unsigned short refl_flags; /* *puVar8 */
  unsigned int stencil_mode; /* uVar15 */
  char occlusion_result; /* cVar4 return of FUN_0017cfd0 */
  int iVar1; /* iVar1 = i * 0x28 */

  FUN_0016f910(0x19);

  if (*(char *)0x3256d7 == '\0' || *(short *)0x5a5bc0 != 0 ||
      *(int *)0x4d0480 <= 0) {
    FUN_0016fa40(0x19);
    return;
  }

  FUN_0017cfc0(5, 0);

  lf_count = *(int *)0x4d0480;
  outer_ctr = 0;
  if (lf_count > 0) {
    i = 0;
    do {
      /* Bounds check */
      if ((short)outer_ctr < 0 || i >= lf_count) {
        display_assert(
          "lens_flare_index>=0 && lens_flare_index<local_lens_flare_count",
          "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 0x43, 1);
        system_exit(-1);
      }

      iVar1 = i * 0x28;
      /* entry = &DAT_004c6480 + i*0x28 (5*8 = 0x28 bytes per entry) */
      entry = (int *)((char *)0x4c6480 + iVar1);

      /* FUN_00181060 takes @eax = entry (lens_flare_params ptr).
       * Returns pointer to light color/alpha byte in the light table. */
      light_data = FUN_00181060((void *)entry);

      /* FUN_0017ffc0 decodes packed normal entry[4] into dir_local[3] */
      dir_ptr = FUN_0017ffc0(dir_local, (unsigned int)entry[4]);
      dir_x = dir_ptr[0];
      dir_y = dir_ptr[1];
      dir_z = dir_ptr[2];

      /* Filter by window index: byte[entry+0x22] & 0x7f == DAT_005a5bc2 */
      if (((*(unsigned char *)((char *)entry + 0x22) & 0x7f) ==
           *(unsigned short *)0x5a5bc2) &&
          (*(int *)((char *)entry + 0x24) > 0) &&
          (*(unsigned char *)((char *)entry + 0x1b) != 0) &&
          (*(int *)(entry[0] + 0xc4) > 0)) {
        definition = entry[0];
        entry_x = *(float *)((char *)entry + 4);
        entry_y = *(float *)((char *)entry + 8);
        entry_z = *(float *)((char *)entry + 0xc);

        /* Compute relative position to camera origin */
        delta[0] = entry_x - *(float *)0x5a5bc8;
        delta[1] = entry_y - *(float *)0x5a5bcc;
        delta[2] = entry_z - *(float *)0x5a5bd0;

        /* view_dot = dot(camera_fwd, delta) */
        view_dot = *(float *)0x5a5bd4 * delta[0] + *(float *)0x5a5bd8 * delta[1] +
                   *(float *)0x5a5bdc * delta[2];

        /* Reflection offset: 2*(view_fwd * dot - delta) */
        refl_off_x = *(float *)0x5a5bd4 * view_dot - delta[0];
        refl_off_y = *(float *)0x5a5bd8 * view_dot - delta[1];
        refl_off_z = *(float *)0x5a5bdc * view_dot - delta[2];
        refl_off_x = refl_off_x + refl_off_x;
        refl_off_y = refl_off_y + refl_off_y;
        refl_off_z = refl_off_z + refl_off_z;

        brightness_byte = (float)*light_data * *(float *)0x261518;

        /* Near-clip brightness: clamp (view_dot - near_end) / (near_start -
         * near_end) */
        if (*(float *)(definition + 0x1c) <= *(float *)0x2533c0) {
          brightness = 1.0f;
        } else {
          brightness =
            (view_dot - *(float *)(definition + 0x1c)) /
            (*(float *)(definition + 0x18) - *(float *)(definition + 0x1c));
          if (brightness < *(float *)0x2533c0) {
            brightness = 0.0f;
          } else if (*(float *)0x2533c8 < brightness) {
            brightness = 1.0f;
          }
        }

        /* FUN_0017ff80: scale byte to float */
        brightness = brightness_byte * brightness *
                     FUN_0017ff80(*(unsigned char *)((char *)entry + 0x1b));

        /* FUN_00181420: corona rotation size.
         * Takes @esi = entry (lens_flare_params), @di =
         * *(short*)(definition+0x80). Returns float (ST0) = corona rotation
         * size. */
        corona_rot =
          FUN_00181420((void *)entry, *(short *)(definition + 0x80)) *
          *(float *)(definition + 0x84);

        /* fpatan of screen-space projection */
        flare_angle = (float)atan2(*(float *)0x5a5c6c * delta[2] +
                                     *(float *)0x5a5c68 * delta[1] +
                                     delta[0] * *(float *)0x5a5c64,
                                   *(float *)0x5a5c78 * delta[2] +
                                     *(float *)0x5a5c74 * delta[1] +
                                     delta[0] * *(float *)0x5a5c70) *
                      *(float *)0x2b073c;

        /* depth scale: 1.0 / (far - near) */
        depth_scale = *(float *)0x2533c8 / (*(float *)(definition + 8) -
                                            *(float *)(definition + 0xc));
        depth_bias = -(depth_scale * *(float *)(definition + 0xc));

        /* Normalize delta (in-place, modifies delta[0]/y/z via &delta[0]) */
        normalize3d(&delta[0]);

        /* Visibility array:
         * [0] = 1.0 (always)
         * [1] = camera-facing: clamp(depth_bias - dot(dir, camera_pos) *
         * depth_scale) [2] = light-facing:  clamp(depth_bias - dot(dir, delta)
         * * depth_scale) [3] = backward:      clamp(dot(fwd, delta) *
         * depth_scale + depth_bias) [4] = rotation fn output (filled later if
         * brightness > 0) */
        vis[0] = 1.0f;

        {
          float v;
          v = depth_bias -
              (dir_x * *(float *)0x5a5bd4 + *(float *)0x5a5bd8 * dir_y +
               *(float *)0x5a5bdc * dir_z) *
                depth_scale;
          if (v < *(float *)0x2533c0) {
            vis[1] = 0.0f;
          } else if (*(float *)0x2533c8 < v) {
            vis[1] = 1.0f;
          } else {
            vis[1] = v;
          }
        }

        {
          float v;
          v =
            depth_bias -
            (dir_x * delta[0] + dir_y * delta[1] + dir_z * delta[2]) * depth_scale;
          if (v < *(float *)0x2533c0) {
            vis[2] = 0.0f;
          } else if (*(float *)0x2533c8 < v) {
            vis[2] = 1.0f;
          } else {
            vis[2] = v;
          }
        }

        {
          float v;
          v = (*(float *)0x5a5bdc * delta[2] + *(float *)0x5a5bd8 * delta[1] +
               delta[0] * *(float *)0x5a5bd4) *
                depth_scale +
              depth_bias;
          if (v < *(float *)0x2533c0) {
            vis[3] = 0.0f;
          } else if (*(float *)0x2533c8 < v) {
            vis[3] = 1.0f;
          } else {
            vis[3] = v;
          }
        }

        if (*(float *)0x2533c0 < brightness) {
          /* vis[4] = rotation function output for animation */
          vis[4] = FUN_0017ff80(*(unsigned char *)((char *)entry + 0x23));

          refl_idx = 0;
          refl_count = *(int *)(definition + 0xc4);
          if (refl_count > 0) {
            refl_ivar = 0;
            do {
              int saved_refl_idx;
              saved_refl_idx = refl_idx;

              /* tag_block_get_element(definition+0xc4, refl_ivar, 0x80) */
              refl = tag_block_get_element((void *)(definition + 0xc4),
                                           refl_ivar, 0x80);

              /* Compute reflection scale from animation:
               * ((max - min) * vis[4] + min) * vis[flags] * brightness */
              {
                float anim_val;
                anim_val = (*(float *)((char *)refl + 0x38) -
                            *(float *)((char *)refl + 0x34)) *
                             vis[4] +
                           *(float *)((char *)refl + 0x34);
                /* refl[0x3c] = vis-factor index (short, sign-extended) */
                anim_alpha = anim_val *
                             vis[(int)(*(short *)((char *)refl + 0x3c))] *
                             brightness;
              }

              if (refl_idx == 0) {
                brightness = anim_alpha;
              }

              if (*(float *)0x2533c0 < anim_alpha) {
                refl_size = (*(float *)((char *)refl + 0x2c) -
                             *(float *)((char *)refl + 0x28)) *
                              vis[4] +
                            *(float *)((char *)refl + 0x28);

                /* Check if all tint color components are zero */
                if (*(float *)((char *)refl + 0x40) == *(float *)0x2533c0 &&
                    *(float *)((char *)refl + 0x44) == *(float *)0x2533c0 &&
                    *(float *)((char *)refl + 0x48) == *(float *)0x2533c0 &&
                    *(float *)((char *)refl + 0x4c) == *(float *)0x2533c0) {
                  /* No tint: use alpha from light_data byte, color from entry
                   */
                  color = (unsigned int)FUN_00180770(anim_alpha) << 0x18 |
                          (*(unsigned int *)((char *)entry + 0x18) & 0xffffff);
                  tex_flags = 0x3f800000;
                } else {
                  /* Has tint: build ARGB from animation color */
                  anim_r = *(float *)((char *)refl + 0x44);
                  anim_g = *(float *)((char *)refl + 0x48);
                  anim_b = *(float *)((char *)refl + 0x4c);
                  /* anim_alpha already set above */

                  if (*(short *)((char *)refl + 0x72) > 1) {
                    /* Has animation: compute animated color */
                    if (*(float *)((char *)refl + 0x74) == *(float *)0x2533c0) {
                      display_assert(
                        "reflection->animation_period!=0.0f",
                        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c",
                        0x28b, 1);
                      system_exit(-1);
                    }
                    refl_anim = FUN_0010a5e0(
                      *(short *)((char *)refl + 0x72),
                      (*(float *)0x5a5e18 + *(float *)((char *)refl + 0x78)) /
                        *(float *)((char *)refl + 0x74));

                    /* Interpolate RGB into anim_rgb[3] (EBP-0x38..EBP-0x30):
                     * output, mode, lower, upper, t */
                    FUN_0007c270(
                      anim_rgb,
                      (unsigned int)(*(unsigned char *)((char *)refl + 0x70) &
                                     3),
                      (float *)((char *)refl + 0x54),
                      (float *)((char *)refl + 0x64), refl_anim);

                    /* Interpolate alpha into anim_alpha_out (EBP-0x3c):
                     * lower=entry[0x50], upper=entry[0x60], t, output */
                    scalars_interpolate(*(float *)((char *)refl + 0x50),
                                       *(float *)((char *)refl + 0x60),
                                       refl_anim, &anim_alpha_out);

                    /* Validate animation_color.alpha */
                    if (anim_alpha_out < *(float *)0x2533c0 ||
                        (anim_alpha_out < *(float *)0x2533c8 ==
                         (anim_alpha_out == *(float *)0x2533c8))) {
                      display_assert(
                        "animation_color.alpha>=0.0f && "
                        "animation_color.alpha<=1.0f",
                        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c",
                        0x29b, 1);
                      system_exit(-1);
                    }
                    /* Validate animation_color.red */
                    if (anim_rgb[0] < *(float *)0x2533c0 ||
                        (anim_rgb[0] < *(float *)0x2533c8 ==
                         (anim_rgb[0] == *(float *)0x2533c8))) {
                      display_assert(
                        "animation_color.red >=0.0f && animation_color.red "
                        "<=1.0f",
                        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c",
                        0x29c, 1);
                      system_exit(-1);
                    }
                    /* Validate animation_color.green */
                    if (anim_rgb[1] < *(float *)0x2533c0 ||
                        (anim_rgb[1] < *(float *)0x2533c8 ==
                         (anim_rgb[1] == *(float *)0x2533c8))) {
                      display_assert(
                        "animation_color.green>=0.0f && "
                        "animation_color.green<=1.0f",
                        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c",
                        0x29d, 1);
                      system_exit(-1);
                    }
                    /* Validate animation_color.blue */
                    if (anim_rgb[2] < *(float *)0x2533c0 ||
                        (anim_rgb[2] < *(float *)0x2533c8 ==
                         (anim_rgb[2] == *(float *)0x2533c8))) {
                      display_assert(
                        "animation_color.blue >=0.0f && animation_color.blue "
                        "<=1.0f",
                        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c",
                        0x29e, 1);
                      system_exit(-1);
                    }

                    anim_alpha = anim_alpha_out * anim_alpha;
                    anim_r    = anim_r * anim_rgb[0];
                    anim_g    = anim_g * anim_rgb[1];
                    anim_b    = anim_b * anim_rgb[2];
                  }

                  {
                    /* Pack ARGB: FUN_000d1c90 takes float[4] = {alpha,r,g,b}
                     * at [EBP-0x58] = {anim_alpha, anim_r, anim_g, anim_b}.
                     * These four contiguous slots map to local_5c/58/54/50. */
                    float argb4[4];
                    argb4[0] = anim_alpha;
                    argb4[1] = anim_r;
                    argb4[2] = anim_g;
                    argb4[3] = anim_b;
                    color = FUN_000d1c90(argb4);
                  }
                  tex_flags = *(unsigned int *)((char *)refl + 0x40);
                }

                /* Reflection position */
                if (refl_idx == 0) {
                  flare_size_angle =
                    corona_rot + *(float *)((char *)refl + 0x20);
                  scale2d[0] = *(float *)(definition + 0xa0);
                  scale2d[1] = *(float *)(definition + 0xa4);
                } else {
                  flare_size_angle = *(float *)((char *)refl + 0x20);
                  scale2d[0] = 1.0f;
                  scale2d[1] = 1.0f;
                }

                refl_flags = *(unsigned short *)refl;

                /* Optional rotation offset */
                if (refl_flags & 1) {
                  flare_size_angle = flare_size_angle + flare_angle;
                }

                /* Optional scale by brightness */
                if (refl_flags & 4) {
                  refl_size = (brightness_byte + *(float *)0x2533c8) *
                              refl_size * *(float *)0x253398;
                }

                /* Optional scale by view dot */
                if (refl_flags & 2) {
                  refl_size = refl_size * view_dot;
                }

                /* Billboard position: entry_xyz + offset * refl_size */
                {
                  float fVar2;
                  fVar2 = *(float *)((char *)refl + 0x1c);
                  pos[0] = refl_off_x * fVar2 + entry_x;
                  pos[1] = refl_off_y * fVar2 + entry_y;
                  pos[2] = refl_off_z * fVar2 + entry_z;
                }

                /* FUN_0017cfd0: check occlusion / stencil */
                occlusion_result =
                  FUN_0017cfd0(0, *(unsigned int *)(definition + 0x2c),
                               *(unsigned short *)((char *)refl + 4));
                if (occlusion_result != '\0') {
                  break; /* exit inner loop */
                }

                FUN_0017cfe0(tex_flags);

                /* stencil mode */
                if ((refl_flags & 8) != 0 &&
                    (char)(*(unsigned char *)((char *)entry + 0x22)) < 0) {
                  stencil_mode = 2;
                } else {
                  stencil_mode = 0;
                }
                FUN_00158ae0((short)stencil_mode);

                /* Draw the lens flare reflection:
                 * FUN_0017d010(&pos, refl_size, &scale2d,
                 *              flare_size_angle * deg2rad_scale, color) */
                FUN_0017d010(pos, refl_size, scale2d,
                             flare_size_angle * *(float *)0x253d4c, color);

                saved_refl_idx = refl_idx;
              }

              refl_idx = saved_refl_idx + 1;
              refl_ivar = (int)(short)refl_idx;
              refl_count = *(int *)(definition + 0xc4);
            } while (refl_ivar < refl_count);
          }
        }
      }

      outer_ctr = outer_ctr + 1;
      i = (int)(short)outer_ctr;
      lf_count = *(int *)0x4d0480;
    } while (i < lf_count);
  }

  FUN_00158ae0(0);
  FUN_0017ad90();

  /* Second pass: render sun glow overlays (DAT_003256fe guard) */
  if (*(char *)0x3256fe != '\0') {
    lf_count = *(int *)0x4d0480;
    if (lf_count > 0) {
      sun_i = 0;
      i = 0;
      do {
        if (sun_i < 0 || i >= lf_count) {
          display_assert(
            "lens_flare_index>=0 && lens_flare_index<local_lens_flare_count",
            "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 0x43, 1);
          system_exit(-1);
        }

        sun_entry = (int)((char *)0x4c6480 + (int)(short)sun_i * 0x28);
        if (*(int *)((char *)sun_entry + 0x24) > 0 &&
            ((*(unsigned char *)((char *)sun_entry + 0x22) & 0x7f) ==
             *(unsigned short *)0x5a5bc2)) {
          int sun_def;
          sun_def = *(int *)sun_entry;
          if (*(int *)(sun_def + 0x10) == 0x42480000 ||
              (*(unsigned char *)(sun_def + 0x30) & 1) != 0) {
            FUN_00169fd0((int *)sun_entry);
          }
        }

        sun_i = sun_i + 1;
        i = (int)sun_i;
        lf_count = *(int *)0x4d0480;
      } while (i < lf_count);
    }
  }

  FUN_0016fa40(0x19);
}


/* rasterizer_memory_pool.c */

/* rasterizer_memory_pool_new (0x1824e0) — readable C lift from XBE leaf. */
char rasterizer_memory_pool_new(void)
{
  extern char DAT_002b077c[];
  extern char DAT_002b0740[];
  void *pool;

  pool = debug_malloc(0x18000, false, DAT_002b077c, 0x13);
  *(void **)0x4d0488 = pool;
  if (pool == 0) {
    error(2, DAT_002b0740);
    return 0;
  }
  return 1;
}




/* rasterizer_memory_pool_reset: reset pool allocation cursor to zero (0x182520)
 */
void rasterizer_memory_pool_reset(void)
{
  *(int *)0x4d048c = 0;
}

/* rasterizer_memory_pool_alloc (0x182530) — readable C lift from XBE leaf. */
void *rasterizer_memory_pool_alloc(void *data, int size)
{
  extern char DAT_002b07b0[];
  int used;
  void *dest;

  used = *(int *)0x4d048c;
  if (used + size > 0x18000) {
    error(2, DAT_002b07b0);
    return 0;
  }
  dest = (char *)*(void **)0x4d0488 + used;
  *(int *)0x4d048c = used + size;
  if (data != 0) {
    csmemcpy(dest, data, (size_t)size);
  }
  return dest;
}




/* rasterizer_memory_pool_copy (0x182590) — readable C lift from XBE leaf. */
int rasterizer_memory_pool_copy(int data, int size)
{
  extern char DAT_002b07dc[];
  extern char DAT_002b077c[];

  if (data == 0) {
    display_assert(DAT_002b07dc, DAT_002b077c, 0x42, true);
    system_exit(-1);
  }
  return (int)(uintptr_t)rasterizer_memory_pool_alloc((void *)(uintptr_t)data, size);
}




/* FUN_001825d0: stub (0x1825d0) */
void FUN_001825d0(void)
{
}

/* rasterizer_memory_pool_delete (0x1825e0) — readable C lift from XBE leaf. */
void rasterizer_memory_pool_delete(void)
{
  extern char DAT_002b077c[];
  void *pool;

  pool = *(void **)0x4d0488;
  if (pool != 0) {
    debug_free(pool, DAT_002b077c, 0x50);
  }
  *(void **)0x4d0488 = 0;
  *(void **)0x4d048c = 0;
}




/* rasterizer_swizzle.c */

/* rasterizer_swizzle_compute_masks (0x182690) — readable C lift (restored pre-naked). */
void rasterizer_swizzle_compute_masks(short param_1, short param_2,
                                      unsigned short param_3,
                                      unsigned short param_4,
                                      unsigned int *param_5)
{
  int16_t sVar1;
  int16_t sVar2;
  int16_t param_1_min;
  unsigned char bVar5;
  unsigned short uVar3;
  unsigned int uVar6;
  unsigned int uVar4;
  int upper;

  sVar1 = FUN_00108db0((unsigned int)(int)param_1);
  sVar2 = FUN_00108db0((unsigned int)(int)param_2);

  /* param_1_min = min(sVar1, sVar2) */
  param_1_min = sVar2;
  if (sVar1 <= sVar2) {
    param_1_min = sVar1;
  }
  bVar5 = (unsigned char)param_1_min;
  uVar3 = (unsigned short)((1 << (bVar5 & 0x1f)) - 1);

  if ((short)uVar3 < 0x40) {
    uVar6 = (unsigned int)*(
      unsigned short *)((int)0x2b07e0 + (int)(short)(param_3 & uVar3) * 2);
    uVar4 = (unsigned int)*(
      unsigned short *)((int)0x2b07e0 + (int)(short)(param_4 & uVar3) * 2);
  } else {
    upper = (int)(short)uVar3 >> 6;
    if (upper > 0x3f) {
      display_assert("upper_mask<=63",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x56,
                     1);
      system_exit(-1);
    }
    uVar6 = (unsigned int)*(
              unsigned short *)((int)0x2b07e0 +
                                (((int)(short)param_3 >> 6) & upper) * 2)
              << 0xc |
            (unsigned int)*(unsigned short *)((int)0x2b07e0 +
                                              ((int)(short)param_3 & 0x3f) * 2);
    uVar4 = (unsigned int)*(
              unsigned short *)((int)0x2b07e0 +
                                (((int)(short)param_4 >> 6) & upper) * 2)
              << 0xc |
            (unsigned int)*(unsigned short *)((int)0x2b07e0 +
                                              ((int)(short)param_4 & 0x3f) * 2);
  }
  uVar4 = uVar4 << 1;
  if (param_1_min < sVar1) {
    param_5[1] = uVar4;
    *param_5 = uVar6 | ((int)(short)param_3 >> (bVar5 & 0x1f))
                         << (bVar5 * 2 & 0x1f);
    return;
  }
  if (param_1_min < sVar2) {
    uVar4 = uVar4 | ((int)(short)param_4 >> (bVar5 & 0x1f))
                      << (bVar5 * 2 & 0x1f);
  }
  *param_5 = uVar6;
  param_5[1] = uVar4;
}


/* rasterizer_swizzle_interleave_bits (0x1827c0) — readable C lift. */
void rasterizer_swizzle_interleave_bits(short w, short h, short d, unsigned int x,
                                        unsigned int y, unsigned int z,
                                        unsigned int *out)
{
  unsigned int ox = 0;
  unsigned int oy = 0;
  unsigned int oz = 0;
  int pos = 0;
  unsigned int bit = 1;
  int old_pos;
  short xs = (short)x;
  short ys = (short)y;
  short zs = (short)z;

  do {
    old_pos = pos;
    if ((short)bit < w) {
      ox |= (unsigned int)(xs & 1) << pos;
      xs = (short)(xs >> 1);
      pos++;
    }
    if ((short)bit < h) {
      oy |= (unsigned int)(ys & 1) << pos;
      ys = (short)(ys >> 1);
      pos++;
    }
    if ((short)bit < d) {
      oz |= (unsigned int)(zs & 1) << pos;
      zs = (short)(zs >> 1);
      pos++;
    }
    bit <<= 1;
  } while (old_pos != pos);

  out[0] = ox;
  out[1] = oy;
  out[2] = oz;
}

/* rasterizer_swizzle_bitmap_mipmaps: compute total swizzle buffer size
 * needed for all mipmaps of a bitmap (0x183290).
 * Returns total byte count, aligned to 128 bytes (or x6 for cubemaps). */
int FUN_00183290(void *param_1)
{
  int bitmap;
  short sVar2;
  short height;
  int iVar4;
  int mip_size;
  int mip_index;
  int row_pitch;
  int local_8;

  bitmap = (int)param_1;
  iVar4 = 0;
  local_8 = 0;
  sVar2 = FUN_00183120((void *)param_1);
  mip_index = 0;
  if (-1 < (int)sVar2) {
    do {
      mip_size = bitmap_mipmap_get_pixel_data_size((void *)bitmap, mip_index);
      if ((*(unsigned char *)(bitmap + 0xe) & 0x10) != 0) {
        /* swizzled/tiled: add per-row padding */
        if ((short)mip_index != 0) {
          display_assert("mipmap_index==0",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c",
                         0x1fa, 1);
          system_exit(-1);
        }
        if ((*(unsigned char *)(bitmap + 0xe) & 2) != 0) {
          display_assert("!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit)",
                         "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c",
                         0x1fb, 1);
          system_exit(-1);
        }
        row_pitch = bitmap_mipmap_get_row_pitch((void *)bitmap, mip_index);
        height = (short)bitmap_mipmap_get_height((void *)bitmap, mip_index);
        mip_size = mip_size + (int)height * (-row_pitch & 0x3f);
      }
      if (*(short *)(bitmap + 10) == 2) {
        /* cubemap: divide per-face */
        mip_size = mip_size / 6;
      }
      iVar4 = local_8 + mip_size;
      mip_index = mip_index + 1;
      local_8 = iVar4;
    } while ((short)mip_index <= sVar2);
  }
  /* align total to 128 bytes */
  iVar4 = iVar4 + (-iVar4 & 0x7f);
  if (*(short *)(bitmap + 10) == 2) {
    /* cubemap: multiply back by 6 */
    return iVar4 * 6;
  }
  return iVar4;
}

/* FUN_00183390 (0x183390) — XBE naked draft (batch 314). */
#if defined(__clang__)
static int (*const b183390_c183290)(void *bitmap) = (void *)FUN_00183290;
static void (*const b183390_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b183390_exitfn)(int) = system_exit;
static void * (*const b183390_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static void (*const b183390_c182e00)(int param_1) = (void *)FUN_00182e00;
static int16_t (*const b183390_c183120)(void *bitmap) = (void *)FUN_00183120;
static void * (*const b183390_c7d000)(void *bitmap, short mipmap_index) = (void *)bitmap_mipmap_address;
static int (*const b183390_c7d960)(void *bitmap, int mipmap_index) = (void *)bitmap_mipmap_get_pixel_data_size;
static int (*const b183390_c7d9f0)(void *bitmap, int mipmap_index) = (void *)bitmap_mipmap_get_row_pitch;
static void * (*const b183390_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static void *(*const b183390_memset)(void *, int, unsigned int) = csmemset;
static void (*const b183390_c8ef70)(void *ptr, const char *file, int line) = (void *)debug_free;
static void (*const b183390_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
int FUN_00183390(int bitmap __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c183290]\n\t"
      "movl %%eax, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $4, %%esp\n\t"
      "xorl %%edi, %%edi\n\t"
      "cmpw $2, 0xa(%%ebx)\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "setne %%al\n\t"
      "decl %%eax\n\t"
      "andl $5, %%eax\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x18(%%ebp)\n\t"
      "movl 0x2c(%%ebx), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00183390_1\n\t"
      "pushl $1\n\t"
      "pushl $0x225\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_1:\n\t"
      "pushl $0x228\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ee60]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "je .LFUN_00183390_17\n\t"
      "pushl %%ebx\n\t"
      "call *%[c182e00]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0, -0x18(%%ebp)\n\t"
      "movl $0, -0x10(%%ebp)\n\t"
      "jle .LFUN_00183390_14\n\t"
      ".LFUN_00183390_2:\n\t"
      "pushl %%ebx\n\t"
      "call *%[c183120]\n\t"
      "xorl %%esi, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "movl %%esi, -0xc(%%ebp)\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jl .LFUN_00183390_13\n\t"
      "jmp .LFUN_00183390_4\n\t"
      ".LFUN_00183390_3:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      ".LFUN_00183390_4:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d000]\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c7d960]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl -0x10(%%ebp), %%eax\n\t"
      "movw 0x2b0860(,%%eax,2), %%cx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw $2, 0xa(%%ebx)\n\t"
      "jne .LFUN_00183390_5\n\t"
      "movl $0x2aaaaaab, %%eax\n\t"
      "imull %%esi\n\t"
      "movl %%edx, %%eax\n\t"
      "shrl $0x1f, %%eax\n\t"
      "addl %%eax, %%edx\n\t"
      "movl %%edx, %%esi\n\t"
      ".LFUN_00183390_5:\n\t"
      "testb $0x10, 0xe(%%ebx)\n\t"
      "je .LFUN_00183390_16\n\t"
      "cmpw $0, -0x10(%%ebp)\n\t"
      "jne .LFUN_00183390_6\n\t"
      "testw %%cx, %%cx\n\t"
      "je .LFUN_00183390_7\n\t"
      ".LFUN_00183390_6:\n\t"
      "pushl $1\n\t"
      "pushl $0x24c\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b0988\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_7:\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "testw %%si, %%si\n\t"
      "je .LFUN_00183390_8\n\t"
      "pushl $1\n\t"
      "pushl $0x24d\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x29dfec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_8:\n\t"
      "testb $2, 0xe(%%ebx)\n\t"
      "je .LFUN_00183390_9\n\t"
      "pushl $1\n\t"
      "pushl $0x24e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264df0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_9:\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c7d9f0]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, %%ebx\n\t"
      "negl %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "andl $0x3f, %%ebx\n\t"
      "cmpw $0, 0x6(%%ecx)\n\t"
      "movl $0, -0x14(%%ebp)\n\t"
      "jle .LFUN_00183390_11\n\t"
      ".LFUN_00183390_10:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "addl %%esi, %%edi\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "addl %%esi, %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%ebx, %%edi\n\t"
      "incl %%eax\n\t"
      "cmpw 0x6(%%edx), %%ax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jl .LFUN_00183390_10\n\t"
      ".LFUN_00183390_11:\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      ".LFUN_00183390_12:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw -0x20(%%ebp), %%ax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jle .LFUN_00183390_3\n\t"
      ".LFUN_00183390_13:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%edi, %%esi\n\t"
      "negl %%esi\n\t"
      "andl $0x7f, %%esi\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%edx\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "call *%[memset]\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "incl %%eax\n\t"
      "cmpw -0x18(%%ebp), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .LFUN_00183390_2\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      ".LFUN_00183390_14:\n\t"
      "cmpl -0x1c(%%ebp), %%edi\n\t"
      "je .LFUN_00183390_15\n\t"
      "pushl $1\n\t"
      "pushl $0x271\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b0978\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00183390_15:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl 0x2c(%%ebx), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x275\n\t"
      "pushl $0x2b087c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00183390_16:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movswl %%cx, %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "imull %%esi, %%eax\n\t"
      "pushl %%esi\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl %%edi, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8e0b0]\n\t"
      "addl $0xc, %%esp\n\t"
      "addl %%esi, %%edi\n\t"
      "jmp .LFUN_00183390_12\n\t"
      ".LFUN_00183390_17:\n\t"
      "pushl $0x2b0928\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c183290] "m"(b183390_c183290), [assert] "m"(b183390_assert), [exitfn] "m"(b183390_exitfn), [c8ee60] "m"(b183390_c8ee60), [c182e00] "m"(b183390_c182e00), [c183120] "m"(b183390_c183120), [c7d000] "m"(b183390_c7d000), [c7d960] "m"(b183390_c7d960), [c7d9f0] "m"(b183390_c7d9f0), [c8e0b0] "m"(b183390_c8e0b0), [memset] "m"(b183390_memset), [c8ef70] "m"(b183390_c8ef70), [c8f390] "m"(b183390_c8f390)
      : "memory");
}
#else
#error "FUN_00183390: clang naked draft required"
#endif


/* rasterizer_text_cache_initialize: init hardware text cache (0x183650) */
int rasterizer_text_cache_initialize(void)
{
  int texture_handle;
  char success;

  if (*(char *)0x4d04a0 != 0) {
    display_assert("!hardware_character_cache.initialized",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x76, 1);
    system_exit(-1);
  }

  texture_handle = (int)bitmap_2d_new(128, 128, 0, 9);
  if (texture_handle != 0) {
    csmemset((void *)0x4d04a0, 0, 0x810);
    success = FUN_00168370((void *)texture_handle);
    if (success != 0) {
      *(int *)0x4d04ac = texture_handle;
      *(char *)0x4d04a0 = 1;
      return 1;
    }
  }

  error(2, "### ERROR failed to initialize hardware text cache");
  return 0;
}

/* rasterizer_text_set_shadow_color: set text shadow color (0x1836e0) */
void rasterizer_text_set_shadow_color(const void *color)
{
  *(int *)0x4d0cb0 = (int)color;
}

/* rasterizer_text_cache_flush: invalidate all cached characters (0x1836f0) */
void rasterizer_text_cache_flush(void)
{
  int *slot;
  int i;

  if (*(char *)0x4d04a0 != 0) {
    slot = (int *)0x4d04b0;
    for (i = 0; i < 256; i++) {
      if (*slot != 0) {
        *(short *)(*slot + 0xc) = -1;
      }
      *slot = 0;
      slot += 2;
    }
  }
}

/* rasterizer_text_cache_dispose (0x183720) — readable C lift from XBE leaf. */
void rasterizer_text_cache_dispose(void)
{
  if (*(unsigned char *)0x4d04a0 != 0) {
    rasterizer_text_cache_flush();
    bitmap_delete(*(void **)0x4d04ac);
    *(unsigned char *)0x4d04a0 = 0;
  }
}




/* rasterizer_text.c — hardware character cache and text rendering.
 *
 * Address range: 0x183650 - 0x184060
 */

#define HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH 128
#define HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT 128
#define MAXIMUM_HARDWARE_CHARACTERS 256

/* Hardware character cache (0x4d04a0, 0x810 bytes):
 *   +0x00 (byte):   initialized
 *   +0x02 (ushort): read_index   (wraps at 256)
 *   +0x04 (ushort): write_index  (wraps at 256)
 *   +0x06 (short):  cursor_x
 *   +0x08 (short):  cursor_y
 *   +0x0a (short):  max_char_height
 *   +0x0c (int):    texture_handle
 *   +0x10-0x810:    character_table[256] entries (8 bytes each):
 *       +0x0 (int*):   character pointer
 *       +0x4 (short):  screen_x
 *       +0x6 (short):  screen_y
 */

/* rasterizer_text_get_character_position (0x183770) — readable C lift.
 *
 * index @<ax>, out_y @<ebx>, out_x on stack. Reads cached glyph UV/position
 * from the 8-byte slot table at 0x4d04b0.
 */
void rasterizer_text_get_character_position(short index /* @<ax> */,
                                            short *out_y /* @<ebx> */,
                                            short *out_x)
{
  short *slot;

  if (*(char *)0x4d04a0 == 0) {
    display_assert((const char *)0x2b0a9c, (const char *)0x2b0a0c, 0x255, true);
    system_exit(-1);
  }
  if (index < 0 || index >= 0x100) {
    display_assert((const char *)0x2b0a48, (const char *)0x2b0a0c, 0x256, true);
    system_exit(-1);
  }
  if (out_x == NULL || out_y == NULL) {
    display_assert((const char *)0x2b0a38, (const char *)0x2b0a0c, 0x257, true);
    system_exit(-1);
  }

  slot = (short *)(0x4d04b0 + (int)index * 8);
  *out_x = slot[2];
  *out_y = slot[3];
}


/* rasterizer_text_evict_character (0x183820) — readable C lift from XBE leaf. */
void rasterizer_text_evict_character(int **slot)
{
  extern char DAT_002b0aec[];
  extern char DAT_002b0a0c[];
  extern char DAT_002b0ac4[];
  int *entry;

  if (slot == 0) {
    display_assert(DAT_002b0aec, DAT_002b0a0c, 0x262, true);
    system_exit(-1);
  }
  entry = *slot;
  if (entry == 0) {
    return;
  }
  *(short *)((char *)entry + 0xc) = (short)0xffff;
  entry = *slot;
  if (*(short *)((char *)entry + 0xe) == *(short *)0x325748) {
    error(3, DAT_002b0ac4);
  }
  *slot = 0;
}




/* rasterizer_text_cache_character: cache a hardware character into the texture cache.
 * Original ABI: EDI=character pointer, stack=font pointer
 */
void rasterizer_text_cache_character(void *font_character, void *font)
{
  int character = (int)font_character;
  short char_width;
  short char_height;
  int **character_slot;
  short hw_index;
  short y;
  short x;
  short *pixel_out;
  unsigned char *pixel_data;
  int i;
  int cache_top;
  int cache_bottom;
  unsigned short read_index;
  unsigned short write_index;

  if (*(char *)0x4d04a0 == 0) {
    display_assert("hardware_character_cache.initialized",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x279, 1);
    system_exit(-1);
  }

  hw_index = *(short *)(character + 0xc);

  if (hw_index == -1) {
    char_width = *(short *)(character + 4);
    char_height = *(short *)(character + 6);

    if (char_width > 128) {
      display_assert(
        "font_character->bitmap_width<=HARDWARE_CHARACTER_CACHE_BITMAP_WIDTH",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x285, 1);
      system_exit(-1);
    }
    if (char_height > 128) {
      display_assert(
        "font_character->bitmap_height<=HARDWARE_CHARACTER_CACHE_BITMAP_HEIGHT",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x286, 1);
      system_exit(-1);
    }

    *(short *)(character + 0xe) = *(short *)0x325748;

    /* Advance to next row if needed. Original writes _DAT_004d04a8 =
       (uint)cursor_y as a single 32-bit store, which zero-extends cursor_y
       into the high half — i.e. max_char_height (0x4d04aa) is reset to 0. */
    if (128 < (int)*(short *)0x4d04a6 + (int)char_width) {
      *(short *)0x4d04a8 += *(short *)0x4d04aa;
      *(short *)0x4d04a6 = 0;
      *(short *)0x4d04aa = 0;
    }

    /* Wrap back to top if needed, evicting characters. Original writes
       _DAT_004d04a8 = 0 as a single 32-bit store, clearing both cursor_y
       (0x4d04a8) and max_char_height (0x4d04aa). */
    if (128 < (int)*(short *)0x4d04a8 + (int)char_height) {
      *(short *)0x4d04a6 = 0;
      *(short *)0x4d04a8 = 0;
      *(short *)0x4d04aa = 0;

      read_index = *(unsigned short *)0x4d04a2;
      write_index = *(unsigned short *)0x4d04a4;

      if (read_index != write_index) {
        i = read_index & 0xFF;
        while (i != (write_index & 0xFF)) {
          if (*(short *)(0x4d04b6 + i * 8) <= 0) {
            break;
          }
          rasterizer_text_evict_character((int **)(0x4d04b0 + i * 8));
          i = (i + 1) & 0xFF;
        }
        *(unsigned short *)0x4d04a2 = (unsigned short)i;
      }
    }

    /* Evict characters that overlap */
    if (*(short *)0x4d04aa < char_height) {
      cache_top = *(short *)0x4d04a8 + *(short *)0x4d04aa;
      cache_bottom = char_height + (int)*(short *)0x4d04a8;

      read_index = *(unsigned short *)0x4d04a2;
      write_index = *(unsigned short *)0x4d04a4;

      if (read_index != write_index) {
        i = read_index & 0xFF;
        /* Original is a FIFO drain: break at the first slot whose y is
           outside [cache_top, cache_bottom); only the contiguous front
           entries are evicted and read_index advances past them. cache_bottom
           is exclusive. The prior lift instead scanned the whole queue and
           then set read_index = write_index, draining the entire character
           cache whenever a taller glyph arrived, which dropped already-cached
           menu text. */
        do {
          if (*(short *)(0x4d04b6 + i * 8) < (short)cache_top ||
              (short)cache_bottom <= *(short *)(0x4d04b6 + i * 8)) {
            break;
          }
          rasterizer_text_evict_character((int **)(0x4d04b0 + i * 8));
          i = (i + 1) & 0xFF;
        } while (i != (write_index & 0xFF));
        *(unsigned short *)0x4d04a2 = (unsigned short)i;
      }
      /* Original writes _DAT_004d04a8 = CONCAT22(char_height, cursor_y):
         a 32-bit store that sets max_char_height (0x4d04aa, high half) to
         char_height while leaving cursor_y (0x4d04a8, low half) UNCHANGED.
         The prior lift mistranslated this as `cursor_y += char_height`,
         which advanced the pen down a full row each character until a
         glyph was placed at cursor_y=128, overflowing the 128-tall cache
         texture (bitmaps.c:421 "y>=0 && y<bitmap->height"). */
      *(short *)0x4d04aa = char_height;
    }

    /* Handle full cache: evict oldest character. Original compares
       (byte)(write_index + 1) against read_index, so the +1 wraps at 256;
       truncate to unsigned char before comparing or the 255->0 wrap is
       missed and the cache-full case is never detected. */
    if ((unsigned char)(*(unsigned char *)0x4d04a4 + 1) ==
        *(unsigned char *)0x4d04a2) {
      character_slot = (int **)(0x4d04b0 + *(short *)0x4d04a2 * 8);
      rasterizer_text_evict_character(character_slot);
      *(unsigned short *)0x4d04a2 =
        (unsigned short)(unsigned char)(*(unsigned char *)0x4d04a2 + 1);
    }

    /* Allocate slot and copy bitmap to texture */
    i = *(short *)0x4d04a4;
    *(short *)(character + 0xc) = (short)i;
    *(int *)(0x4d04b0 + i * 8) = character;
    *(short *)(0x4d04b4 + i * 8) = *(short *)0x4d04a6;
    *(short *)(0x4d04b6 + i * 8) = *(short *)0x4d04a8;

    pixel_data =
      (unsigned char *)(*(int *)((int)font + 0x94) + *(int *)(character + 0x10));

    for (y = 0; y < char_height; y++) {
      pixel_out = (short *)bitmap_2d_address(
        *(void **)0x4d04ac, *(short *)(0x4d04b4 + i * 8),
        *(short *)(0x4d04b6 + i * 8) + y, 0);
      for (x = 0; x < char_width; x++) {
        *pixel_out = (short)((*pixel_data << 8) | 0xfff);
        pixel_data++;
        pixel_out++;
      }
    }

    FUN_00168b10(*(void **)0x4d04ac);

    *(short *)0x4d04a6 += char_width;
    *(unsigned short *)0x4d04a4 =
      (unsigned short)(unsigned char)(*(unsigned char *)0x4d04a4 + 1);
  } else {
    if (hw_index < 0 || hw_index >= 256) {
      display_assert(
        "font_character->hardware_character_index>=0 && "
        "font_character->hardware_character_index<MAXIMUM_HARDWARE_CHARACTERS",
        "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x27d, 1);
      system_exit(-1);
    }
    if (character != *(int *)(0x4d04b0 + hw_index * 8)) {
      display_assert("font_character==hardware_character_cache.characters[font_"
                     "character->hardware_character_index].character",
                     "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c", 0x27e,
                     1);
      system_exit(-1);
    }
  }
}


/* rasterizer_text_draw_cached_char (0x183c00) — readable C lift (restored pre-naked). */
void rasterizer_text_draw_cached_char(void *arg0, void *font,
                                      void *font_character, unsigned int color,
                                      short x, short y, int cache_offset_x,
                                      int cache_offset_y, short width,
                                      short height)
{
  float quad_verts[20];
  short cache_x;
  short cache_y;
  short tx;
  short ty;

  rasterizer_text_cache_character(font_character, font);

  if (*(short *)((int)font_character + 0xc) != -1) {
    rasterizer_text_get_character_position(
      *(short *)((int)font_character + 0xc), &cache_y, &cache_x);
    tx = (short)(cache_x + (short)cache_offset_x);
    ty = (short)(cache_y + (short)cache_offset_y);

    /* vert0 TL */
    quad_verts[0] = (float)x;
    quad_verts[1] = (float)y;
    quad_verts[2] = (float)tx;
    quad_verts[3] = (float)ty;
    *(unsigned int *)&quad_verts[4] = color;
    /* vert1 TR */
    quad_verts[5] = (float)(x + width);
    quad_verts[6] = (float)y;
    quad_verts[7] = (float)(tx + width);
    quad_verts[8] = (float)ty;
    *(unsigned int *)&quad_verts[9] = color;
    /* vert2 BR */
    quad_verts[10] = (float)(x + width);
    quad_verts[11] = (float)(y + height);
    quad_verts[12] = (float)(tx + width);
    quad_verts[13] = (float)(ty + height);
    *(unsigned int *)&quad_verts[14] = color;
    /* vert3 BL */
    quad_verts[15] = (float)x;
    quad_verts[16] = (float)(y + height);
    quad_verts[17] = (float)tx;
    quad_verts[18] = (float)(ty + height);
    *(unsigned int *)&quad_verts[19] = color;

    FUN_001741d0(quad_verts);
  }
}


/* rasterizer_text_draw_cached_chars (0x183cf0) — readable C lift (restored pre-naked). */
void rasterizer_text_draw_cached_chars(void *arg0, void *font,
                                       void *font_character, unsigned int color,
                                       short x, short y, int cache_offset_x,
                                       int cache_offset_y, short width,
                                       short height)
{
  float quad_verts[20];
  short cache_x;
  short cache_y;
  short tx;
  short ty;
  unsigned int draw_color;
  unsigned int shadow_color;
  float x_base;
  float x_right;
  float y_base;
  float y_bottom;
  float shadow_off_x;
  float shadow_off_y;
  int first_pass;
  int was_first;

  rasterizer_text_cache_character(font_character, font);

  if (*(short *)((int)font_character + 0xc) != -1) {
    shadow_off_x = 1.0f;
    shadow_off_y = 1.0f;
    shadow_color = *(unsigned int *)0x4d0cb0;
    if (*(unsigned int *)0x4d0cb0 == 0) {
      shadow_color = color & 0xff000000;
    }
    x_base = (float)x;
    x_right = (float)(width + x);
    y_base = (float)y;
    y_bottom = (float)(height + y);
    first_pass = 1;

    while (1) {
      rasterizer_text_get_character_position(
        *(short *)((int)font_character + 0xc), &cache_y, &cache_x);
      was_first = first_pass;
      tx = (short)(cache_x + (short)cache_offset_x);
      ty = (short)(cache_y + (short)cache_offset_y);
      draw_color = shadow_color;
      if (first_pass == 0) {
        draw_color = color;
      }

      /* vert0 TL */
      quad_verts[0] = x_base + shadow_off_x;
      quad_verts[1] = y_base + shadow_off_y;
      quad_verts[2] = (float)tx;
      quad_verts[3] = (float)ty;
      *(unsigned int *)&quad_verts[4] = draw_color;
      /* vert1 TR */
      quad_verts[5] = x_right + shadow_off_x;
      quad_verts[6] = y_base + shadow_off_y;
      quad_verts[7] = (float)(tx + width);
      quad_verts[8] = (float)ty;
      *(unsigned int *)&quad_verts[9] = draw_color;
      /* vert2 BR */
      quad_verts[10] = x_right + shadow_off_x;
      quad_verts[11] = y_bottom + shadow_off_y;
      quad_verts[12] = (float)(tx + width);
      quad_verts[13] = (float)(ty + height);
      *(unsigned int *)&quad_verts[14] = draw_color;
      /* vert3 BL */
      quad_verts[15] = x_base + shadow_off_x;
      quad_verts[16] = y_bottom + shadow_off_y;
      quad_verts[17] = (float)tx;
      quad_verts[18] = (float)(ty + height);
      *(unsigned int *)&quad_verts[19] = draw_color;

      FUN_001741d0(quad_verts);

      if (was_first == 0) {
        break;
      }
      first_pass = 0;
      shadow_off_x = 0.0f;
      shadow_off_y = 0.0f;
    }
  }
}


/* rasterizer_text_draw: draw ASCII string (0x183e60) */
void rasterizer_text_draw(void *screen_pos, short *bounds, const void *color,
                          int flags, const char *text)
{
  int draw_bounds[4];
  int clip_bounds[4];
  float texel_width;
  float texel_height;
  float widget_params[35];
  void *texture;
  int font_width;
  int font_height;
  int max_width;
  int max_height;
  int clamp_x;
  int clamp_y;

  if (*(char *)0x3256da == 0 || *(short *)0x5a5bc0 != 0) {
    return;
  }

  *(short *)0x325748 += 1;

  if (text == (const char *)0) {
    display_assert("string", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c",
                   0xb4, 1);
    system_exit(-1);
  }

  texture = (void *)(*(int *)0x4d04ac);
  if ((*(char *)0x4d04a0 != 0) && texture != (void *)0 && *text != 0) {
    csstrlen(text);

    if (screen_pos == (void *)0) {
      draw_bounds[0] = *(int *)0x506584;
      draw_bounds[1] = *(int *)0x506588;
      rect2d_offset((short *)draw_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      draw_bounds[0] = *(int *)screen_pos;
      draw_bounds[1] = *(int *)((char *)screen_pos + 4);
    }

    if (bounds == (short *)0) {
      clip_bounds[0] = *(int *)0x50657c;
      clip_bounds[1] = *(int *)0x506580;
      rect2d_offset((short *)clip_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      max_width = (int)bounds[2];
      if ((int)(*(short *)0x506580 - *(short *)0x50657c) <= (int)bounds[2]) {
        max_width = (int)(*(short *)0x506580 - *(short *)0x50657c);
      }
      max_height = (int)(*(short *)0x506582 - *(short *)0x50657e);
      if ((int)bounds[3] < max_height) {
        max_height = (int)bounds[3];
      }
      clamp_x = (int)bounds[0];
      if (bounds[0] < 0) {
        clamp_x = 0;
      }
      clamp_y = (int)bounds[1];
      if (bounds[1] < 0) {
        clamp_y = 0;
      }
      FUN_001089a0(clip_bounds, clamp_y, clamp_x, max_height, max_width);
      texture = (void *)(*(int *)0x4d04ac);
    }

    csmemset(widget_params, 0, 0x8c);
    font_width = (int)*(short *)((int)texture + 4);
    font_height = (int)*(short *)((int)texture + 6);
    texel_width = *(float *)0x2533c8 / (float)font_width;
    texel_height = *(float *)0x2533c8 / (float)font_height;

    *(unsigned int *)&widget_params[3] = (unsigned int)texture;
    widget_params[10] = 1.0f;
    widget_params[11] = 1.0f;
    widget_params[16] = texel_width;
    widget_params[17] = texel_height;

    FUN_00173b40(widget_params);
    FUN_0019c5d0(rasterizer_text_draw_cached_chars, draw_bounds, color,
                 clip_bounds, flags, (char *)text);
    FUN_00173ae0();
  }
}

/* rasterizer_draw_string: draw wide-character string (0x184060) */
void rasterizer_draw_string(void *screen_pos, short *bounds, const void *color,
                            int flags, unsigned short *text)
{
  int draw_bounds[4];
  int clip_bounds[4];
  float texel_width;
  float texel_height;
  float widget_params[35];
  void *texture;
  int font_width;
  int font_height;
  int max_width;
  int max_height;
  int clamp_x;
  int clamp_y;

  if (*(char *)0x3256da == 0 || *(short *)0x5a5bc0 != 0) {
    return;
  }

  *(short *)0x325748 += 1;

  if (text == (unsigned short *)0) {
    display_assert("string", "c:\\halo\\SOURCE\\rasterizer\\rasterizer_text.c",
                   0x136, 1);
    system_exit(-1);
  }

  texture = (void *)(*(int *)0x4d04ac);
  if ((*(char *)0x4d04a0 != 0) && texture != (void *)0 && *text != 0) {
    ustrlen(text);

    if (screen_pos == (void *)0) {
      draw_bounds[0] = *(int *)0x506584;
      draw_bounds[1] = *(int *)0x506588;
      rect2d_offset((short *)draw_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      draw_bounds[0] = *(int *)screen_pos;
      draw_bounds[1] = *(int *)((char *)screen_pos + 4);
    }

    if (bounds == (short *)0) {
      clip_bounds[0] = *(int *)0x50657c;
      clip_bounds[1] = *(int *)0x506580;
      rect2d_offset((short *)clip_bounds, (short)(-*(short *)0x50657e),
                    (short)(-*(short *)0x50657c));
    } else {
      max_width = (int)bounds[2];
      if ((int)(*(short *)0x506580 - *(short *)0x50657c) <= (int)bounds[2]) {
        max_width = (int)(*(short *)0x506580 - *(short *)0x50657c);
      }
      max_height = (int)(*(short *)0x506582 - *(short *)0x50657e);
      if ((int)bounds[3] < max_height) {
        max_height = (int)bounds[3];
      }
      clamp_x = (int)bounds[0];
      if (bounds[0] < 0) {
        clamp_x = 0;
      }
      clamp_y = (int)bounds[1];
      if (bounds[1] < 0) {
        clamp_y = 0;
      }
      FUN_001089a0(clip_bounds, clamp_y, clamp_x, max_height, max_width);
      texture = (void *)(*(int *)0x4d04ac);
    }

    csmemset(widget_params, 0, 0x8c);
    font_width = (int)*(short *)((int)texture + 4);
    font_height = (int)*(short *)((int)texture + 6);
    texel_width = *(float *)0x2533c8 / (float)font_width;
    texel_height = *(float *)0x2533c8 / (float)font_height;

    *(unsigned int *)&widget_params[3] = (unsigned int)texture;
    widget_params[10] = 1.0f;
    widget_params[11] = 1.0f;
    widget_params[16] = texel_width;
    widget_params[17] = texel_height;

    FUN_00173b40(widget_params);
    FUN_0019c960(rasterizer_text_draw_cached_chars, draw_bounds, color,
                 clip_bounds, flags, text);
    FUN_00173ae0();
  }
}

/* rasterizer_transparent_geometry.c */


/* rasterizer_transparent_geometry_new (0x184260) — readable C lift. */
char rasterizer_transparent_geometry_new(void)
{
  void *a;
  void *b;
  void *c;

  a = debug_malloc(0xf000, 0, (const char *)0x2b0ca8, 0x29);
  *(void **)0x4d0cec = a;
  b = debug_malloc(0x300, 0, (const char *)0x2b0ca8, 0x2b);
  *(void **)0x4d0cfc = b;
  c = debug_malloc(0x1400, 0, (const char *)0x2b0ca8, 0x2e);
  *(void **)0x4d0cf0 = c;
  *(int *)0x4d0cf8 = 0;
  *(int *)0x4d0cf4 = 0;
  if (!a || !b || !c) {
    error(2, (const char *)0x2b0c6c);
    return 0;
  }
  if (!FUN_00174bd0(0))
    return 0;
  return 1;
}



/* rasterizer_transparent_geometry_begin (0x184300) — readable C lift from XBE leaf. */
void rasterizer_transparent_geometry_begin(void)
{
  *(int *)0x4d0cf4 = 0;
  *(short *)0x4d0d00 = 0;
  csmemset((void *)0x4d0cbc, 0, 0x30);
  *(int *)0x4d0cf8 = 0;
}




/* rasterizer_transparent_geometry_group_new (0x184330) — readable C lift. */
void *rasterizer_transparent_geometry_group_new(void)
{
  int index;
  char *base;
  char *group;

  index = *(int *)0x4d0cf4;
  if (index >= 0x180)
    return NULL;
  base = *(char **)0x4d0cec;
  group = base + index * 0xa0;
  *(int *)(group + 0x90) = index;
  *(int *)0x4d0cf4 = index + 1;
  return group;
}

/* rasterizer_secondary_geometry_group_new (0x184360) — readable C lift. */
void *rasterizer_secondary_geometry_group_new(void)
{
  int index;
  char *base;
  char *group;

  index = *(int *)0x4d0cf8;
  if (index >= 0x20)
    return NULL;
  base = *(char **)0x4d0cf0;
  group = base + index * 0xa0;
  *(int *)(group + 0x90) = index;
  *(int *)0x4d0cf8 = index + 1;
  return group;
}

/* rasterizer_secondary_geometry_groups_get (0x184390) — readable C lift. */
void *rasterizer_secondary_geometry_groups_get(uint16_t *out_count)
{
  if (out_count != NULL)
    *out_count = *(uint16_t *)0x4d0cf8;
  return *(void **)0x4d0cf0;
}

/* rasterizer_transparent_geometry_next_group (0x1843b0) — readable C lift.
 *
 * Advance from group->presorted_index (+0x90) to the next presorted group
 * entry (stride 0xa0), or return NULL at the end of the list.
 */
void *rasterizer_transparent_geometry_next_group(void *group)
{
  int cur;
  int16_t next;
  int16_t sorted;

  if (group == NULL)
    return NULL;

  cur = *(int *)((char *)group + 0x90);
  next = (int16_t)((int16_t)cur + 1);
  if (cur < 0 || cur >= *(int *)0x4d0cf4) {
    display_assert((const char *)0x2b0d00, (const char *)0x2b0ca8, 0x89, true);
    system_exit(-1);
  }
  if (next >= *(int *)0x4d0cf4)
    return NULL;
  if (next < 0) {
    display_assert((const char *)0x2b0ce4, (const char *)0x2b0ca8, 0x8d, true);
    system_exit(-1);
  }

  sorted = *(int16_t *)(*(char **)0x4d0cfc + (int)next * 2);
  return *(char **)0x4d0cec + (int)sorted * 0xa0;
}


/* rasterizer_transparent_geometry_group_get (0x184460) — readable C lift from XBE leaf. */
void *rasterizer_transparent_geometry_group_get(short group_presorted_index)
{
  extern char DAT_002b0d50[];
  extern char DAT_002b0ca8[];

  if (group_presorted_index < 0 ||
      (int)group_presorted_index >= *(int *)0x4d0cf4) {
    display_assert(DAT_002b0d50, DAT_002b0ca8, 0xbc, true);
    system_exit(-1);
  }
  return (void *)(*(int *)0x4d0cec + (int)group_presorted_index * 0xa0);
}




/* rasterizer_transparent_geometry_group_to_presorted_index (0x1844b0) — readable C lift. */
short rasterizer_transparent_geometry_group_to_presorted_index(unsigned int group)
{
  unsigned int base;
  unsigned int count;
  int idx;

  base = *(unsigned int *)0x4d0cec;
  count = *(unsigned int *)0x4d0cf4;
  if (group < base || group >= base + count * 160u)
    return -1;

  idx = (int)((group - base) / 160u);
  if (idx < 0 || idx >= (int)count) {
    display_assert((const char *)0x2b0d50, (const char *)0x2b0ca8, 0xcb, 1);
    system_exit(-1);
    base = *(unsigned int *)0x4d0cec;
  }
  if ((group - base) % 160u != 0) {
    display_assert((const char *)0x2b0da8, (const char *)0x2b0ca8, 0xcc, 1);
    system_exit(-1);
  }
  return (short)idx;
}

/* --- rasterizer_text.obj batch drafts (2026-07-26) --- */

/* FUN_00180770 (0x180770) — readable C lift from XBE leaf. */
unsigned char FUN_00180770(float alpha)
{
  extern char DAT_002b00a0[];
  extern char DAT_002afe38[];
  float scaled;

  if (alpha < *(float *)0x2533c0 || alpha > *(float *)0x2533c8) {
    display_assert(DAT_002b00a0, DAT_002afe38, 0x2a, true);
    system_exit(-1);
  }
  scaled = alpha * *(float *)0x2602c8;
  /* fistp uses RC=round-nearest (FPCW=0x027f). */
  return (unsigned char)(int)(scaled + 0.5f);
}


/* compress_real_to_int16 (0x180820) — readable C lift from XBE leaf. */
int16_t compress_real_to_int16(float value)
{
  extern char DAT_002b00b8[];
  extern char DAT_002afe38[];
  float lo = *(float *)0x255e94;
  float hi = *(float *)0x2533c8;
  float scaled;
  int tmp;

  if (!(value >= lo) || !(value <= hi)) {
    display_assert(DAT_002b00b8, DAT_002afe38, 0x37, true);
    system_exit(-1);
  }
  scaled = (float)floor((double)(value * *(float *)0x2b00b4));
  tmp = (int)scaled;
  return (int16_t)tmp;
}



/* FUN_00180890 (0x180890) — readable C lift from XBE leaf. */
short FUN_00180890(float f)
{
  float v;
  float scaled;

  v = f;
  if (v < *(float *)0x255e94)
    v = *(float *)0x255e94;
  else if (v > *(float *)0x2533c8)
    v = *(float *)0x2533c8;
  scaled = (float)floor((double)(v * *(float *)0x2b00b4));
  return (short)(int)scaled;
}


/* 0x181060 */
unsigned char *FUN_00181060(void *lens_flare_params)
{
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x181084 */
  display_assert((char *)0x002b02d4, (char *)0x002b01b4, 76, 0);
  system_exit(0);
  /* cmp esi, 4 -> jl 0x1810cf */
  display_assert((char *)0x002a1d18, (char *)0x002b01b4, 87, 0);
  system_exit(0);
  /* test edi, edi -> jl 0x1810db */
  /* cmp edi, 0x10008 -> jl 0x1810f8 */
  display_assert((char *)0x002b0250, (char *)0x002b01b4, 88, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x18110d */
  /* cmp (int16_t)eax, 0x380 -> jl 0x18112a */
  display_assert((char *)0x002b01e8, (char *)0x002b01b4, 94, 0);
  system_exit(0);
  return NULL;

  (void)esi;
  (void)edi;
}

/* FUN_00181180 (0x181180) — XBE naked draft (batch 333). */
#if defined(__clang__)
static void (*const b181180_c16f910)(int16_t profile) = (void *)FUN_0016f910;
static void (*const b181180_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181180_exitfn)(int) = system_exit;
static unsigned char * (*const b181180_c181060)(void *lens_flare_params) = (void *)FUN_00181060;
static void (*const b181180_c17d040)(void) = (void *)FUN_0017d040;
static void (*const b181180_c16fa40)(int16_t profile) = (void *)FUN_0016fa40;

__attribute__((naked, noinline))
void FUN_00181180(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x18\n\t"
      "call *%[c16f910]\n\t"
      "movb 0x3256d7, %%al\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181180_12\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181180_12\n\t"
      "jne .LFUN_00181180_1\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181180_12\n\t"
      ".LFUN_00181180_1:\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "pushl %%esi\n\t"
      "xorl %%esi, %%esi\n\t"
      "cmpl %%esi, %%eax\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      "jle .LFUN_00181180_11\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      ".LFUN_00181180_2:\n\t"
      "cmpw $0, -0x4(%%ebp)\n\t"
      "jl .LFUN_00181180_3\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181180_4\n\t"
      ".LFUN_00181180_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x43\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181180_4:\n\t"
      "leal (%%esi,%%esi,4), %%edi\n\t"
      "leal 0x4c6480(,%%edi,8), %%edi\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[c181060]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x24(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_00181180_5\n\t"
      "pushl %%esi\n\t"
      "call *%[c17d040]\n\t"
      "imull $0xff, %%eax, %%eax\n\t"
      "movl 0x24(%%edi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "sarl $1, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "idivl %%ecx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0xff, %%eax\n\t"
      "jge .LFUN_00181180_6\n\t"
      "movb %%al, %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .LFUN_00181180_7\n\t"
      ".LFUN_00181180_5:\n\t"
      "movb $0, (%%ebx)\n\t"
      "jmp .LFUN_00181180_10\n\t"
      ".LFUN_00181180_6:\n\t"
      "orb $0xff, %%cl\n\t"
      ".LFUN_00181180_7:\n\t"
      "movb (%%ebx), %%al\n\t"
      "cmpb %%al, %%cl\n\t"
      "jbe .LFUN_00181180_8\n\t"
      "movzbl %%al, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "movzbl %%cl, %%ecx\n\t"
      "addl %%ecx, %%eax\n\t"
      "cdq\n\t"
      "andl $3, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "sarl $2, %%eax\n\t"
      "jmp .LFUN_00181180_9\n\t"
      ".LFUN_00181180_8:\n\t"
      "jae .LFUN_00181180_10\n\t"
      "movzbl %%al, %%eax\n\t"
      "movzbl %%cl, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "cdq\n\t"
      "subl %%edx, %%eax\n\t"
      "sarl $1, %%eax\n\t"
      ".LFUN_00181180_9:\n\t"
      "movb %%al, (%%ebx)\n\t"
      ".LFUN_00181180_10:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "movswl %%ax, %%esi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl 0x4d0480, %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .LFUN_00181180_2\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00181180_11:\n\t"
      "movl $0, 0x4d0480\n\t"
      "popl %%esi\n\t"
      ".LFUN_00181180_12:\n\t"
      "pushl $0x18\n\t"
      "call *%[c16fa40]\n\t"
      "addl $4, %%esp\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c16f910] "m"(b181180_c16f910), [assert] "m"(b181180_assert), [exitfn] "m"(b181180_exitfn), [c181060] "m"(b181180_c181060), [c17d040] "m"(b181180_c17d040), [c16fa40] "m"(b181180_c16fa40)
      : "memory");
}
#else
#error "FUN_00181180: clang naked draft required"
#endif


/* FUN_001812c0 (0x1812c0) — XBE naked draft (batch 323). */
#if defined(__clang__)
static void (*const b1812c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1812c0_exitfn)(int) = system_exit;
static void (*const b1812c0_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_001812c0(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .LFUN_001812c0_1\n\t"
      "pushl $1\n\t"
      "pushl $0xf0\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x29f510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_1:\n\t"
      "flds 0x28(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_2\n\t"
      "flds 0x28(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_3\n\t"
      ".LFUN_001812c0_2:\n\t"
      "pushl $1\n\t"
      "pushl $0xf1\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b039c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_3:\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_4\n\t"
      "flds 0x2c(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_5\n\t"
      ".LFUN_001812c0_4:\n\t"
      "pushl $1\n\t"
      "pushl $0xf2\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b035c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_5:\n\t"
      "flds 0x30(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_001812c0_6\n\t"
      "flds 0x30(%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_001812c0_7\n\t"
      ".LFUN_001812c0_6:\n\t"
      "pushl $1\n\t"
      "pushl $0xf3\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b031c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_001812c0_7:\n\t"
      "movl 0x5a37e0, %%ecx\n\t"
      "cmpl $0x80, %%ecx\n\t"
      "jge .LFUN_001812c0_8\n\t"
      "movl %%ecx, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "imull $0x38, %%edi, %%edi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x5a37e0\n\t"
      "addl $0x5a37e4, %%edi\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "movl $0xe, %%ecx\n\t"
      "rep movsl\n\t"
      "jne .LFUN_001812c0_9\n\t"
      "movl 0x5a5548, %%ecx\n\t"
      "incl %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x5a5548\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_001812c0_8:\n\t"
      "pushl $0x2b02ec\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_001812c0_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1812c0_assert), [exitfn] "m"(b1812c0_exitfn), [c8f390] "m"(b1812c0_c8f390)
      : "memory");
}
#else
#error "FUN_001812c0: clang naked draft required"
#endif


/* FUN_00181420 (0x181420) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b181420_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181420_exitfn)(int) = system_exit;
static float * (*const b181420_c17ffc0)(float *param_1, unsigned int param_2) = (void *)FUN_0017ffc0;
static void (*const b181420_cross)(float *, float *, float *) = cross_product3d;

__attribute__((naked, noinline))
float FUN_00181420(void *lens_flare_params __attribute__((unused)), short rotation_fn __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl $0x3f800000, -0x8(%%ebp)\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "jne .LFUN_00181420_1\n\t"
      "pushl $1\n\t"
      "pushl $0x76\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b02d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181420_1:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c17ffc0]\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x8(%%eax), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $4, %%eax\n\t"
      "movl %%ecx, -0x20(%%ebp)\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "ja .LFUN_00181420_7\n\t"
      "jmp *.LFUN_00181420_jt(,%%eax,4)\n\t"
      ".LFUN_00181420_2:\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "pushl $0x5a5c64\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cross]\n\t"
      "flds -0x28(%%ebp)\n\t"
      "movl 0x5a5bdc, %%ecx\n\t"
      "movl 0x5a5bd8, %%eax\n\t"
      "movl 0x5a5bd4, %%edx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "addl $0x18, %%esp\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_3:\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_6\n\t"
      ".LFUN_00181420_4:\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%eax\n\t"
      "pushl $0x5a5c64\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "leal -0x30(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x24(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[cross]\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "addl $0x18, %%esp\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_5:\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x5a5bc8\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      ".LFUN_00181420_6:\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x5a5c6c\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c68\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c64\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c84\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "flds 0x5a5c80\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5c7c\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fchs\n\t"
      "jmp .LFUN_00181420_9\n\t"
      ".LFUN_00181420_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x97\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b03dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181420_8:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      ".LFUN_00181420_9:\n\t"
      "testw %%di, %%di\n\t"
      "je .LFUN_00181420_10\n\t"
      "fld %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00181420_10\n\t"
      "fpatan\n\t"
      "fmuls 0x29c120\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00181420_10:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".LFUN_00181420_jt:\n\t"
      ".long .LFUN_00181420_8\n\t"
      ".long .LFUN_00181420_2\n\t"
      ".long .LFUN_00181420_3\n\t"
      ".long .LFUN_00181420_4\n\t"
      ".long .LFUN_00181420_5\n\t"
      ".text\n\t"
      :
      : [assert] "m"(b181420_assert), [exitfn] "m"(b181420_exitfn), [c17ffc0] "m"(b181420_c17ffc0), [cross] "m"(b181420_cross)
      : "memory");
}
#else
#error "FUN_00181420: clang naked draft required"
#endif


/* FUN_00182610 (0x182610) — readable C lift from XBE leaf. */
void FUN_00182610(int16_t mask_si, int16_t width, int16_t height)
{
  unsigned int bit;
  unsigned int step;
  unsigned int tmp;
  unsigned int mask_z;

  *(int *)0x4d0490 = 0;
  *(int *)0x4d0494 = 0;
  *(int *)0x4d0498 = 0;
  bit = 1;
  step = 1;
  mask_z = 0;
  do {
    tmp = 0;
    if (step < (unsigned int)(int)mask_si) {
      *(unsigned int *)0x4d0498 |= bit;
      bit <<= 1;
      tmp = bit;
    }
    if (step < (unsigned int)(int)width) {
      *(unsigned int *)0x4d0494 |= bit;
      bit <<= 1;
      tmp = bit;
    }
    if (step < (unsigned int)(int)height) {
      mask_z |= bit;
      bit <<= 1;
      tmp = bit;
    }
    step <<= 1;
  } while (tmp != 0);
  *(unsigned int *)0x4d0490 = mask_z;
}




/* rasterizer_xbox_bitmap_swizzle2d_byte (0x182840) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b182840_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182840_exitfn)(int) = system_exit;
static void (*const b182840_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_byte(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_1\n\t"
      "pushl $1\n\t"
      "pushl $0x93\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_2\n\t"
      "pushl $1\n\t"
      "pushl $0x94\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_byte_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_byte_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movb (%%ebx,%%edx,1), %%dl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movb %%dl, (%%ecx,%%esi,1)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_byte_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_byte_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182840_assert), [exitfn] "m"(b182840_exitfn), [c182610] "m"(b182840_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_byte: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle2d_word (0x182910) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b182910_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182910_exitfn)(int) = system_exit;
static void (*const b182910_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_word(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_1\n\t"
      "pushl $1\n\t"
      "pushl $0xb0\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_2\n\t"
      "pushl $1\n\t"
      "pushl $0xb1\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_word_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_word_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movw (%%edx,%%ebx,2), %%dx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movw %%dx, (%%esi,%%ecx,2)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_word_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_word_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182910_assert), [exitfn] "m"(b182910_exitfn), [c182610] "m"(b182910_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_word: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle2d_long (0x1829f0) — XBE naked draft (batch 332). */
#if defined(__clang__)
static void (*const b1829f0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b1829f0_exitfn)(int) = system_exit;
static void (*const b1829f0_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle2d_long(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_1\n\t"
      "pushl $1\n\t"
      "pushl $0xcd\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_2\n\t"
      "pushl $1\n\t"
      "pushl $0xce\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_2:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl $1\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_long_6\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "movl 0x4d0498, %%eax\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_3:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle2d_long_5\n\t"
      "movzwl %%si, %%edx\n\t"
      "movl %%edx, 0x14(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_4:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl (%%edx,%%ebx,4), %%edx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "orl %%edi, %%ecx\n\t"
      "movl %%edx, (%%esi,%%ecx,4)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "incl %%ebx\n\t"
      "andl %%eax, %%edi\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_4\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_5:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "decl -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle2d_long_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle2d_long_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b1829f0_assert), [exitfn] "m"(b1829f0_exitfn), [c182610] "m"(b1829f0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle2d_long: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_byte (0x182ac0) — XBE naked draft (batch 324). */
#if defined(__clang__)
static void (*const b182ac0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182ac0_exitfn)(int) = system_exit;
static void (*const b182ac0_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_byte(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_1\n\t"
      "pushl $1\n\t"
      "pushl $0xeb\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_2\n\t"
      "pushl $1\n\t"
      "pushl $0xec\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_byte_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movb (%%ebx,%%ecx,1), %%cl\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movb %%cl, (%%edx,%%esi,1)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_byte_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_byte_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182ac0_assert), [exitfn] "m"(b182ac0_exitfn), [c182610] "m"(b182ac0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_byte: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_word (0x182bd0) — XBE naked draft (batch 325). */
#if defined(__clang__)
static void (*const b182bd0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182bd0_exitfn)(int) = system_exit;
static void (*const b182bd0_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_word(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_1\n\t"
      "pushl $1\n\t"
      "pushl $0x10e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_2\n\t"
      "pushl $1\n\t"
      "pushl $0x10f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_word_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movw (%%ecx,%%ebx,2), %%cx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movw %%cx, (%%esi,%%edx,2)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_word_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_word_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182bd0_assert), [exitfn] "m"(b182bd0_exitfn), [c182610] "m"(b182bd0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_word: clang naked draft required"
#endif


/* rasterizer_xbox_bitmap_swizzle3d_long (0x182cf0) — XBE naked draft (batch 325). */
#if defined(__clang__)
static void (*const b182cf0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182cf0_exitfn)(int) = system_exit;
static void (*const b182cf0_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;

__attribute__((naked, noinline))
void rasterizer_xbox_bitmap_swizzle3d_long(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "xorl %%edi, %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpl %%edi, %%eax\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_1\n\t"
      "pushl $1\n\t"
      "pushl $0x131\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ac\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_1:\n\t"
      "cmpl %%edi, 0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_2\n\t"
      "pushl $1\n\t"
      "pushl $0x132\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b07dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_2:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c182610]\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "addl $12, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_8\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      "movzwl %%ax, %%edx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_3:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_7\n\t"
      "movzwl %%ax, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_4:\n\t"
      "testw %%si, %%si\n\t"
      "jle .Lrasterizer_xbox_bitmap_swizzle3d_long_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "orl %%ecx, %%eax\n\t"
      "movzwl %%si, %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl (%%ecx,%%ebx,4), %%ecx\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%eax, %%edx\n\t"
      "orl %%edi, %%edx\n\t"
      "movl %%ecx, (%%esi,%%edx,4)\n\t"
      "movl 0x4d0498, %%ecx\n\t"
      "subl %%ecx, %%edi\n\t"
      "andl %%ecx, %%edi\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "incl %%ebx\n\t"
      "decl %%ecx\n\t"
      "movl %%ecx, 0x18(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_5\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "movl 0x4d0494, %%ecx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_6:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "subl %%ecx, %%edx\n\t"
      "andl %%ecx, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_4\n\t"
      "movl 0x4d0490, %%edx\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_7:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "subl %%edx, %%eax\n\t"
      "andl %%edx, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "decl -0x10(%%ebp)\n\t"
      "jne .Lrasterizer_xbox_bitmap_swizzle3d_long_3\n\t"
      ".Lrasterizer_xbox_bitmap_swizzle3d_long_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182cf0_assert), [exitfn] "m"(b182cf0_exitfn), [c182610] "m"(b182cf0_c182610)
      : "memory");
}
#else
#error "rasterizer_xbox_bitmap_swizzle3d_long: clang naked draft required"
#endif


/* FUN_00182e00 (0x182e00) — XBE naked draft (batch 303). */
#if defined(__clang__)
static void (*const b182e00_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b182e00_exitfn)(int) = system_exit;
static int (*const b182e00_c7d960)(void *bitmap, int mipmap_index) = (void *)bitmap_mipmap_get_pixel_data_size;
static void * (*const b182e00_c7d000)(void *bitmap, short mipmap_index) = (void *)bitmap_mipmap_address;
static void * (*const b182e00_c8ee60)(uint32_t size, bool zero, const char *file, int line) = (void *)debug_malloc;
static short (*const b182e00_c7d6e0)(void *bitmap, int mipmap_index) = (void *)bitmap_mipmap_width;
static short (*const b182e00_c7d780)(void *bitmap, short mipmap_index) = (void *)bitmap_mipmap_get_height;
static int (*const b182e00_c7d820)(void *bitmap, short mipmap_index) = (void *)bitmap_mipmap_get_depth;
static short (*const b182e00_c7c840)(short format) = (void *)bitmap_format_bits_per_pixel;
static void (*const b182e00_c182610)(int16_t, int16_t, int16_t) = (void *)FUN_00182610;
static void (*const b182e00_c1829f0)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_long;
static void (*const b182e00_c182910)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_word;
static void (*const b182e00_c182840)(void) = (void *)rasterizer_xbox_bitmap_swizzle2d_byte;
static void (*const b182e00_c182cf0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_long;
static void (*const b182e00_c182bd0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_word;
static void (*const b182e00_c182ac0)(void) = (void *)rasterizer_xbox_bitmap_swizzle3d_byte;
static void * (*const b182e00_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static void (*const b182e00_c8ef70)(void *ptr, const char *file, int line) = (void *)debug_free;
static void (*const b182e00_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_00182e00(int param_1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00182e00_1\n\t"
      "pushl $1\n\t"
      "pushl $0x14e\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x263768\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_1:\n\t"
      "movl 0x2c(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00182e00_2\n\t"
      "pushl $1\n\t"
      "pushl $0x14f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x264c30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_2:\n\t"
      "movw 0xe(%%edi), %%ax\n\t"
      "testb $0x12, %%al\n\t"
      "jne .LFUN_00182e00_28\n\t"
      "testb $1, %%al\n\t"
      "jne .LFUN_00182e00_3\n\t"
      "pushl $1\n\t"
      "pushl $0x159\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2a2760\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00182e00_3:\n\t"
      "pushl %%ebx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x14(%%edi)\n\t"
      "movl %%ebx, -0x10(%%ebp)\n\t"
      "jl .LFUN_00182e00_27\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_00182e00_5\n\t"
      ".LFUN_00182e00_4:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "jmp .LFUN_00182e00_5\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00182e00_5:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d960]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "call *%[c7d000]\n\t"
      "pushl $0x15f\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[c8ee60]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[c7d6e0]\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[c7d780]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c7d820]\n\t"
      "addl $0x38, %%esp\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_00182e00_25\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0xc(%%edi), %%cx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c7c840]\n\t"
      "movswl %%ax, %%eax\n\t"
      "cdq\n\t"
      "andl $7, %%edx\n\t"
      "addl %%edx, %%eax\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "sarl $3, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "call *%[c182610]\n\t"
      "movswl 0xa(%%edi), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "subl $0, %%eax\n\t"
      "je .LFUN_00182e00_19\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_14\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_6\n\t"
      "pushl $1\n\t"
      "pushl $0x1b4\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x261d30\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_6:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl $0x2aaaaaab, %%eax\n\t"
      "imull -0x18(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl %%edx, %%ecx\n\t"
      "shrl $0x1f, %%ecx\n\t"
      "addl %%ecx, %%edx\n\t"
      "movl %%edi, %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl $6, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00182e00_8\n\t"
      ".LFUN_00182e00_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00182e00_8:\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00182e00_11\n\t"
      "decl %%ecx\n\t"
      "je .LFUN_00182e00_10\n\t"
      "subl $2, %%ecx\n\t"
      "je .LFUN_00182e00_9\n\t"
      "pushl $1\n\t"
      "pushl $0x1a9\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_13\n\t"
      ".LFUN_00182e00_9:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1829f0]\n\t"
      "jmp .LFUN_00182e00_12\n\t"
      ".LFUN_00182e00_10:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c182910]\n\t"
      "jmp .LFUN_00182e00_12\n\t"
      ".LFUN_00182e00_11:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "addl %%edi, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c182840]\n\t"
      ".LFUN_00182e00_12:\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00182e00_13:\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl %%ecx, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jne .LFUN_00182e00_7\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_14:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_18\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_17\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00182e00_16\n\t"
      "pushl $1\n\t"
      "pushl $0x18f\n\t"
      ".LFUN_00182e00_15:\n\t"
      "pushl $0x2b087c\n\t"
      "pushl $0x2b08ec\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_16:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182cf0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_17:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182bd0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_18:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182ac0]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00182e00_24\n\t"
      ".LFUN_00182e00_19:\n\t"
      "movswl -0x14(%%ebp), %%eax\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_22\n\t"
      "decl %%eax\n\t"
      "je .LFUN_00182e00_21\n\t"
      "subl $2, %%eax\n\t"
      "je .LFUN_00182e00_20\n\t"
      "pushl $1\n\t"
      "pushl $0x17b\n\t"
      "jmp .LFUN_00182e00_15\n\t"
      ".LFUN_00182e00_20:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1829f0]\n\t"
      "jmp .LFUN_00182e00_23\n\t"
      ".LFUN_00182e00_21:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c182910]\n\t"
      "jmp .LFUN_00182e00_23\n\t"
      ".LFUN_00182e00_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c182840]\n\t"
      ".LFUN_00182e00_23:\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00182e00_24:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c8e0b0]\n\t"
      "pushl $0x1b8\n\t"
      "pushl $0x2b087c\n\t"
      "pushl %%esi\n\t"
      "call *%[c8ef70]\n\t"
      "addl $0x18, %%esp\n\t"
      "orb $8, 0xe(%%edi)\n\t"
      "jmp .LFUN_00182e00_26\n\t"
      ".LFUN_00182e00_25:\n\t"
      "pushl $0x2b08b0\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00182e00_26:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x14(%%edi), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_00182e00_4\n\t"
      "popl %%esi\n\t"
      ".LFUN_00182e00_27:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00182e00_28:\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b182e00_assert), [exitfn] "m"(b182e00_exitfn), [c7d960] "m"(b182e00_c7d960), [c7d000] "m"(b182e00_c7d000), [c8ee60] "m"(b182e00_c8ee60), [c7d6e0] "m"(b182e00_c7d6e0), [c7d780] "m"(b182e00_c7d780), [c7d820] "m"(b182e00_c7d820), [c7c840] "m"(b182e00_c7c840), [c182610] "m"(b182e00_c182610), [c1829f0] "m"(b182e00_c1829f0), [c182910] "m"(b182e00_c182910), [c182840] "m"(b182e00_c182840), [c182cf0] "m"(b182e00_c182cf0), [c182bd0] "m"(b182e00_c182bd0), [c182ac0] "m"(b182e00_c182ac0), [c8e0b0] "m"(b182e00_c8e0b0), [c8ef70] "m"(b182e00_c8ef70), [c8f390] "m"(b182e00_c8f390)
      : "memory");
}
#else
#error "FUN_00182e00: clang naked draft required"
#endif


/* FUN_00183120 (0x183120) — readable C lift: bitmap mip dimension helper. */
int16_t FUN_00183120(void *bitmap)
{
  unsigned short flags;
  int width;
  int height;
  int depth;
  int dim;
  int h4;
  int w4;
  int16_t stored;
  int16_t computed;

  if (!bitmap_verify(bitmap, 0)) {
    display_assert((const char *)0x264da0, (const char *)0x2b087c, 0x1cb, 1);
    system_exit(-1);
  }
  flags = *(unsigned short *)((char *)bitmap + 0xe);
  if ((flags & 1) == 0 || (flags & 0x10) != 0)
    return 0;
  width = (int)*(short *)((char *)bitmap + 4);
  height = (int)*(short *)((char *)bitmap + 6);
  depth = (int)*(short *)((char *)bitmap + 8);
  stored = *(int16_t *)((char *)bitmap + 0x14);
  if ((flags & 2) != 0) {
    h4 = height / 4;
    w4 = width / 4;
    dim = h4;
    if (dim < depth)
      dim = depth;
    if (w4 > dim)
      dim = w4;
  } else {
    dim = height;
    if (dim < depth)
      dim = depth;
    if (width > dim)
      dim = width;
  }
  computed = FUN_00108db0((unsigned int)dim);
  if (stored <= computed)
    return 0;
  return FUN_00108db0((unsigned int)dim);
}


/* --- rasterizer_text.obj orphan shells (2026-07-26) --- */

/* orphan 0x181020 */
int *FUN_00181020(short index)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test (int16_t)esi, (int16_t)esi -> jl 0x181032 */
  /* cmp eax, ecx -> jl 0x18104f */
  display_assert((char *)0x002b0174, (char *)0x002b01b4, 67, 0);
  system_exit(0);
  return NULL;

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* FUN_00181670 (0x181670) — XBE naked draft (batch 309). */
#if defined(__clang__)
static void (*const b181670_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b181670_exitfn)(int) = system_exit;
static int * (*const b181670_c181020)(short index) = (void *)FUN_00181020;
static void * (*const b181670_c8e0b0)(void *destination, void *source, size_t size) = (void *)csmemcpy;
static void *(*const b181670_memset)(void *, int, unsigned int) = csmemset;
static void (*const b181670_c8f390)(unsigned __int16 a1, const char *a2, ...) = (void *)error;

__attribute__((naked, noinline))
void FUN_00181670(int *params __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .LFUN_00181670_1\n\t"
      "pushl $1\n\t"
      "pushl $0x10a\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x29f510\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_1:\n\t"
      "cmpl $0, (%%edi)\n\t"
      "jne .LFUN_00181670_2\n\t"
      "pushl $1\n\t"
      "pushl $0x10b\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b05d4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_2:\n\t"
      "movzbl 0x22(%%edi), %%eax\n\t"
      "andl $0xffffff7f, %%eax\n\t"
      "cmpw 0x5a5bc2, %%ax\n\t"
      "je .LFUN_00181670_3\n\t"
      "pushl $1\n\t"
      "pushl $0x10c\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0568\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_3:\n\t"
      "movb 0x3256d7, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00181670_16\n\t"
      "movw 0x46e008, %%ax\n\t"
      "cmpw $1, %%ax\n\t"
      "jg .LFUN_00181670_16\n\t"
      "jne .LFUN_00181670_4\n\t"
      "cmpw $1, 0x31fa98\n\t"
      "jg .LFUN_00181670_16\n\t"
      ".LFUN_00181670_4:\n\t"
      "cmpw $0, 0x5a5bc0\n\t"
      "jne .LFUN_00181670_16\n\t"
      "movl 0x4d0480, %%ecx\n\t"
      "cmpl $0x400, %%ecx\n\t"
      "jge .LFUN_00181670_15\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl (%%edi), %%edx\n\t"
      "fsubs 0x5a5bc8\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsubs 0x5a5bcc\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsubs 0x5a5bd0\n\t"
      "flds 0x1c(%%edx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00181670_5\n\t"
      "flds 0x5a5bdc\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds 0x5a5bd8\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x5a5bd4\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x1c(%%edx)\n\t"
      "fstp %%st(0)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jp .LFUN_00181670_16\n\t"
      "jmp .LFUN_00181670_6\n\t"
      ".LFUN_00181670_5:\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00181670_6:\n\t"
      "testl $0xff000000, 0x18(%%edi)\n\t"
      "jbe .LFUN_00181670_16\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl %%ecx, %%esi\n\t"
      "incl %%ecx\n\t"
      "movl %%ecx, 0x4d0480\n\t"
      "call *%[c181020]\n\t"
      "pushl $0x28\n\t"
      "movl %%eax, %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8e0b0]\n\t"
      "movw 0x1e(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $-1, 0x1c(%%edi)\n\t"
      "jne .LFUN_00181670_11\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_00181670_8\n\t"
      "movw $0x8000, 0x1e(%%ebx)\n\t"
      "movw 0x20(%%edi), %%di\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00181670_7\n\t"
      "cmpw $8, %%di\n\t"
      "jl .LFUN_00181670_14\n\t"
      ".LFUN_00181670_7:\n\t"
      "pushl $1\n\t"
      "pushl $0x136\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "jmp .LFUN_00181670_14\n\t"
      ".LFUN_00181670_8:\n\t"
      "movswl 0x20(%%edi), %%ecx\n\t"
      "movswl %%ax, %%esi\n\t"
      "shll $0x10, %%esi\n\t"
      "orl %%ecx, %%esi\n\t"
      "jl .LFUN_00181670_9\n\t"
      "cmpl $0x10000, %%esi\n\t"
      "jl .LFUN_00181670_10\n\t"
      ".LFUN_00181670_9:\n\t"
      "pushl $1\n\t"
      "pushl $0x141\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b04a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_10:\n\t"
      "leal 0x8(%%esi), %%edx\n\t"
      "sarl $0x10, %%esi\n\t"
      "orl $0xffff8000, %%esi\n\t"
      "movw %%dx, 0x20(%%ebx)\n\t"
      "movw %%si, 0x1e(%%ebx)\n\t"
      "jmp .LFUN_00181670_14\n\t"
      ".LFUN_00181670_11:\n\t"
      "movswl 0x1e(%%ebx), %%esi\n\t"
      "imull $0x22, %%esi, %%esi\n\t"
      "addl $0x4bed80, %%esi\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00181670_12\n\t"
      "cmpw $0x380, %%ax\n\t"
      "jl .LFUN_00181670_13\n\t"
      ".LFUN_00181670_12:\n\t"
      "pushl $1\n\t"
      "pushl $0x152\n\t"
      "pushl $0x2b01b4\n\t"
      "pushl $0x2b0450\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00181670_13:\n\t"
      "movw 0x1c(%%edi), %%ax\n\t"
      "cmpw (%%esi), %%ax\n\t"
      "je .LFUN_00181670_14\n\t"
      "pushl $0x20\n\t"
      "leal 0x2(%%esi), %%ecx\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "call *%[memset]\n\t"
      "movw 0x1c(%%ebx), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, (%%esi)\n\t"
      ".LFUN_00181670_14:\n\t"
      "cmpw $2, 0x3256ba\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "jne .LFUN_00181670_16\n\t"
      "incl 0x5a554c\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00181670_15:\n\t"
      "movb 0x4d0484, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00181670_16\n\t"
      "pushl $0x2b0418\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $8, %%esp\n\t"
      "movb $1, 0x4d0484\n\t"
      ".LFUN_00181670_16:\n\t"
      "popl %%edi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b181670_assert), [exitfn] "m"(b181670_exitfn), [c181020] "m"(b181670_c181020), [c8e0b0] "m"(b181670_c8e0b0), [memset] "m"(b181670_memset), [c8f390] "m"(b181670_c8f390)
      : "memory");
}
#else
#error "FUN_00181670: clang naked draft required"
#endif

