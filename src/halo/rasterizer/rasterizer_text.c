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


/* FUN_001808f0 (0x1808f0) — readable C lift (restored pre-naked). */

unsigned int FUN_001808f0(float *param_1)
{
  float decoded_i;
  float decoded_j;
  float decoded_k;
  float *decoded;
  unsigned int i_11;
  unsigned int j_11;
  unsigned int packed;
  int tmp;
  float local_buf[3];

  if (param_1 == 0) {
    display_assert("parameters",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x45,
                   1);
    system_exit(-1);
  }
  if (*param_1 < -1.0f || *param_1 > 1.0f || param_1[1] < -1.0f ||
      param_1[1] > 1.0f || param_1[2] < -1.0f || param_1[2] > 1.0f) {
    display_assert("invalid vector",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x4e,
                   1);
    system_exit(-1);
  }
  tmp = (int)floor((double)(*param_1 * *(float *)0x2b0118));
  i_11 = (unsigned int)tmp & 0x7ff;
  tmp = (int)floor((double)(param_1[1] * *(float *)0x2b0118));
  j_11 = (unsigned int)tmp & 0x7ff;
  tmp = (int)floor((double)(param_1[2] * *(float *)0x2b0114));
  packed = (((unsigned int)tmp & 0x3ff) << 11 | j_11) << 11 | i_11;

  decoded = FUN_0017ffc0(local_buf, packed);
  decoded_i = decoded[0];
  decoded_j = decoded[1];
  decoded_k = decoded[2];

  if ((float)*(double *)0x28b800 <= fabsf(decoded_i - *param_1)) {
    display_assert("fabs(v2.i - v->i)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5c,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_j - param_1[1])) {
    display_assert("fabs(v2.j - v->j)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5d,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_k - param_1[2])) {
    display_assert("fabs(v2.k - v->k)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x5e,
                   1);
    system_exit(-1);
  }
  return packed;
}


/* FUN_00180b10 (0x180b10) — readable C lift (restored pre-naked). */

unsigned int FUN_00180b10(float *param_1)
{
  float ci;
  float cj;
  float ck;
  float *decoded;
  float decoded_i;
  float decoded_j;
  float decoded_k;
  unsigned int i_11;
  unsigned int j_11;
  unsigned int packed;
  int tmp;
  float local_buf[3];

  if (param_1 == 0) {
    display_assert("parameters",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x68,
                   1);
    system_exit(-1);
  }
  if (*param_1 < -1.0f) {
    ci = -1.0f;
  } else if (*param_1 > 1.0f) {
    ci = 1.0f;
  } else {
    ci = *param_1;
  }
  tmp = (int)floor((double)(ci * *(float *)0x2b0118));
  i_11 = (unsigned int)tmp & 0x7ff;

  if (param_1[1] < -1.0f) {
    cj = -1.0f;
  } else if (param_1[1] > 1.0f) {
    cj = 1.0f;
  } else {
    cj = param_1[1];
  }
  tmp = (int)floor((double)(cj * *(float *)0x2b0118));
  j_11 = (unsigned int)tmp & 0x7ff;

  if (param_1[2] < -1.0f) {
    ck = -1.0f;
  } else if (param_1[2] > 1.0f) {
    ck = 1.0f;
  } else {
    ck = param_1[2];
  }
  tmp = (int)floor((double)(ck * *(float *)0x2b0114));
  packed = (((unsigned int)tmp & 0x3ff) << 11 | j_11) << 11 | i_11;

  decoded = FUN_0017ffc0(local_buf, packed);
  decoded_i = decoded[0];
  decoded_j = decoded[1];
  decoded_k = decoded[2];

  if ((float)*(double *)0x28b800 <= fabsf(decoded_i - *param_1)) {
    display_assert("fabs(v2.i - v->i)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x76,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_j - param_1[1])) {
    display_assert("fabs(v2.j - v->j)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x77,
                   1);
    system_exit(-1);
  }
  if ((float)*(double *)0x28b800 <= fabsf(decoded_k - param_1[2])) {
    display_assert("fabs(v2.k - v->k)<0.01f",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_geometry.c", 0x78,
                   1);
    system_exit(-1);
  }
  return packed;
}


/* FUN_00180d10 (0x180d10) — readable C lift (restored pre-naked). */
void FUN_00180d10(short param_1, int param_2, int param_3, int param_4,
                  void *param_5, int param_6)
{

  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002b0084, (char *)0x002afe38, 194, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x180d64 */
  display_assert((char *)0x00263b58, (char *)0x002afe38, 195, 0);
  system_exit(0);
  error(0, (char *)0x002b0140);
  /* cmp eax, ecx -> je 0x180dc2 */
  display_assert((char *)0x002b0008, (char *)0x002afe38, 239, 0);
  system_exit(0);
  /* cmp ecx, eax -> je 0x180dee */
  display_assert((char *)0x002affc4, (char *)0x002afe38, 240, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180b10((float *)(uintptr_t)esi);
  FUN_00180b10((float *)(uintptr_t)ecx);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  /* cmp ecx, eax -> je 0x180eb2 */
  display_assert((char *)0x002aff48, (char *)0x002afe38, 221, 0);
  system_exit(0);
  /* cmp edx, eax -> je 0x180ee0 */
  display_assert((char *)0x002afef8, (char *)0x002afe38, 222, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180890(0.0f);
  FUN_00180890(0.0f);
  /* cmp eax, ecx -> je 0x180f54 */
  display_assert((char *)0x002afeb0, (char *)0x002afe38, 201, 0);
  system_exit(0);
  /* cmp ecx, eax -> je 0x180f80 */
  display_assert((char *)0x002afe68, (char *)0x002afe38, 202, 0);
  system_exit(0);
  /* test ebx, ebx -> jle 0x180fde */
  FUN_00180b10((float *)(uintptr_t)eax);
  FUN_00180b10((float *)(uintptr_t)esi);
  FUN_00180b10((float *)(uintptr_t)ecx);
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x18100b */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x18100b */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


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

/* FUN_00181900 (0x181900) — readable C lift (restored pre-naked). */

void FUN_00181900(short param_1)
{
  int scenario; /* scenario base ptr */
  int light_block; /* scenario->scenery_lights[param_1] element ptr */
  int lf_block_base; /* scenario->lens_flare_block ptr */
  int lf_mark_base; /* scenario->lens_flare_marker_block ptr */
  int entry; /* current light_marker_block entry ptr */
  int lf_instance; /* lens_flare_instance element ptr */
  int loop_end; /* count of light_marker entries */
  int i; /* loop counter */
  /* params struct for FUN_00181670: 0x28-byte contiguous buffer.
   * Layout (confirmed from disassembly at 0x181a2c..0x181a67):
   *   +0x00: tag_get('lens', def->tag_index) result
   *   +0x04: entry->xyz[0] (float, from puVar2[0..2])
   *   +0x08: entry->xyz[1]
   *   +0x0c: entry->xyz[2]
   *   +0x10: FUN_00180b10(&dir_vec) = compressed normal of direction
   *   +0x14: FUN_00180b10(&perp_vec) = compressed normal of perpendicular
   *   +0x18: 0xffffffff (color/alpha = -1)
   *   +0x1c: 0xffff word (light_index = -1 -> scenery path)
   *   +0x1e: entry_index >> 16 (hi word of scenery marker index)
   *   +0x20: entry_index & 0xffff (lo word)
   *   +0x22: DAT_0050654a (compressed window index byte)
   *   +0x23: 0
   */
  int params[10]; /* 0x28 = 40 bytes = 10 ints; accessed as byte/short/int */
  float dir[3]; /* direction vector (from entry bytes 0xc/0xd/0xe * scale) */
  float perp[3]; /* perpendicular vector (from perpendicular3d of dir) */
  int entry_idx; /* combined scenery marker index (hi<<16 | lo) */

  if (*(char *)0x3256d7 == 0) {
    return;
  }
  if (*(short *)0x46e008 > 1) {
    return;
  }
  if (*(short *)0x46e008 == 1 && *(short *)0x31fa98 > 1) {
    return;
  }

  scenario = (int)scenario_get();
  /* tag_block_get_element(scenario+0x134, param_1, 0x68) */
  light_block =
    (int)tag_block_get_element((void *)(scenario + 0x134), (int)param_1, 0x68);
  loop_end = (int)*(short *)(light_block + 0x42);
  if (loop_end <= 0) {
    return;
  }

  lf_mark_base = scenario + 0x128;
  lf_block_base = scenario + 0x11c;

  i = 0;
  do {
    /* light_marker_block entry */
    entry_idx = (int)*(unsigned short *)(light_block + 0x40) + i;
    entry = (int)tag_block_get_element((void *)lf_mark_base, entry_idx, 0x10);

    /* lens_flare_instance element */
    lf_instance = (int)tag_block_get_element(
      (void *)lf_block_base, (int)*(unsigned char *)(entry + 0xf), 0x10);

    /* Extract signed bytes from entry for direction vector */
    dir[0] = (float)(int)*(signed char *)(entry + 0xc) * *(float *)0x2820c0;
    dir[1] = (float)(int)*(signed char *)(entry + 0xd) * *(float *)0x2820c0;
    dir[2] = (float)(int)*(signed char *)(entry + 0xe) * *(float *)0x2820c0;

    /* Compute perpendicular and normalize both */
    perpendicular3d(dir, perp);
    normalize3d(dir);
    normalize3d(perp);

    /* Build params buffer (byte-level stores into int array). */
    *(int *)((char *)params + 0x00) =
      (int)tag_get(0x6c656e73, *(int *)(lf_instance + 0xc));
    *(int *)((char *)params + 0x04) = *(int *)(entry + 0x00);
    *(int *)((char *)params + 0x08) = *(int *)(entry + 0x04);
    *(int *)((char *)params + 0x0c) = *(int *)(entry + 0x08);
    *(unsigned int *)((char *)params + 0x10) = (unsigned int)FUN_00180b10(dir);
    *(unsigned int *)((char *)params + 0x14) = (unsigned int)FUN_00180b10(perp);
    *(int *)((char *)params + 0x18) = -1;
    *(short *)((char *)params + 0x1c) = -1;
    *(short *)((char *)params + 0x1e) = (short)(entry_idx >> 16);
    *(short *)((char *)params + 0x20) = (short)entry_idx;
    *(unsigned char *)((char *)params + 0x22) = *(unsigned char *)0x50654a;
    *(unsigned char *)((char *)params + 0x23) = 0;

    FUN_00181670(params);

    i++;
  } while (i < loop_end);
}


/* FUN_00181a90 (0x181a90) — readable C lift (restored pre-naked). */

void FUN_00181a90(void)
{
  int *entry; /* pointer to queued lens flare slot (from FUN_00181020) */
  int definition; /* *entry = definition tag ptr */
  float *dir_result; /* return of FUN_0017ffc0 (3-float direction vec) */
  short occlusion_dir; /* *(short *)(definition + 0x14) */
  int vis_param; /* *(int *)(definition + 0x10) as int (passes to thunk) */
  int lf_count; /* DAT_004d0480 */
  int i; /* loop index */
  float perp[3]; /* perpendicular output (12 bytes, EBP-0x2c) */
  float dir[3]; /* direction vec copied from FUN_0017ffc0 result */
  float pos[3]; /* output position vec for occlusion test (EBP-0x14) */

  FUN_0016f910(0x17);

  if (*(char *)0x3256d7 == 0) {
    FUN_0016fa40(0x17);
    return;
  }
  if (*(short *)0x46e008 > 1) {
    FUN_0016fa40(0x17);
    return;
  }
  if (*(short *)0x46e008 == 1 && *(short *)0x31fa98 > 1) {
    FUN_0016fa40(0x17);
    return;
  }

  if (*(short *)0x5a5bc0 != 0) {
    FUN_0016fa40(0x17);
    return;
  }

  lf_count = *(int *)0x4d0480;
  if (lf_count <= 0) {
    FUN_0016fa40(0x17);
    return;
  }

  FUN_0017cfc0(6, 1);

  lf_count = *(int *)0x4d0480;
  if (lf_count > 0) {
    i = 0;
    do {
      /* FUN_00181020 takes index via SI register; build system provides
       * a thunk that loads the arg into SI before the call. */
      entry = FUN_00181020((short)i);
      definition = *entry;

      /* FUN_0017ffc0(&perp, entry[4]) fills perp[] and returns a
       * pointer to a 3-float direction vec; copy it into dir[]. */
      dir_result = FUN_0017ffc0(perp, (unsigned int)entry[4]);
      dir[0] = dir_result[0];
      dir[1] = dir_result[1];
      dir[2] = dir_result[2];

      /* MOVZX byte [entry+0x22]; AND 0xffffff7f (clear bit 7) → compare
       * with window index */
      if ((*(unsigned char *)((char *)entry + 0x22) & 0x7f) ==
          *(unsigned short *)0x5a5bc2) {
        occlusion_dir = *(short *)(definition + 0x14);
        vis_param = *(int *)(definition + 0x10);

        if (occlusion_dir == 0) {
          /* Negate scale; use global forward direction (0x5a5bd4) */
          vector3d_scale_add((float *)(entry + 1), (float *)0x5a5bd4,
                             -*(float *)(definition + 0x10), pos);
        } else if (occlusion_dir == 1) {
          /* Scale along dir[] by definition field * constant */
          vector3d_scale_add((float *)(entry + 1), dir,
                             *(float *)(definition + 0x10) * *(float *)0x254e68,
                             pos);
        } else if (occlusion_dir == 2) {
          /* Use object/light position directly */
          pos[0] = *(float *)(entry + 1);
          pos[1] = *(float *)(entry + 2);
          pos[2] = *(float *)(entry + 3);
        } else {
          display_assert(
            "### ERROR unsupported lens flare occlusion offset direction",
            "c:\\halo\\SOURCE\\rasterizer\\rasterizer_lights.c", 0x1e2, 1);
          system_exit(-1);
        }

        entry[9] = FUN_0017d030(pos, vis_param, i);
      }

      i++;
    } while (i < *(int *)0x4d0480);
  }

  /* FUN_0017d020 (thunk → FUN_0017ad90) is called after the loop whenever
   * the first lf_count check passed (i.e. when lf_count > 0), matching
   * the original control-flow shape (0x181bfd falls through to 0x181c02
   * regardless of the inner lf_count re-check). */
  FUN_0017d020();

  FUN_0016fa40(0x17);
}


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

/* FUN_00183390 (0x183390) — readable C lift (restored pre-naked). */

int FUN_00183390(int param_1)
{
  int total_size;
  int iVar8;
  unsigned short face_count;
  short sVar2;
  short sVar3;
  int local_c;
  short face_index;
  int swizzle_buf;
  int mip_src;
  int mip_size;
  int row_pitch;
  short adjusted_face_index;
  short local_1c;
  int local_20;

  total_size = FUN_00183290((void *)param_1);
  iVar8 = 0;
  /* face_count: 1 for 2D textures, 6 for cubemaps */
  face_count = (unsigned short)(*(short *)(param_1 + 10) != 2) - 1 & 5;
  local_1c = (short)(face_count + 1);
  if (*(int *)(param_1 + 0x2c) == 0) {
    display_assert("bitmap->base_address",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x225,
                   1);
    system_exit(-1);
  }
  swizzle_buf = (int)debug_malloc(
    total_size, 0, "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x228);
  if (swizzle_buf == 0) {
    error(2, "### ERROR rasterizer_xbox_bitmap_rebuild_hardware_format "
             "failed (out of memory)");
    return 0;
  }
  FUN_00182e00(param_1);
  face_index = 0;
  if (local_1c > 0) {
    do {
      sVar2 = FUN_00183120((void *)param_1);
      if (-1 < (int)sVar2) {
        local_c = 0;
        local_20 = (int)sVar2;
        do {
          mip_src = (int)bitmap_mipmap_address((void *)param_1, local_c);
          mip_size =
            bitmap_mipmap_get_pixel_data_size((void *)param_1, local_c);
          if (*(short *)(param_1 + 10) == 2) {
            mip_size = mip_size / 6;
          }
          adjusted_face_index = *(short *)((int)0x2b0860 + (int)face_index * 2);
          if ((*(unsigned char *)(param_1 + 0xe) & 0x10) == 0) {
            /* non-swizzled: copy face mipmap data */
            csmemcpy((void *)(swizzle_buf + iVar8),
                     (void *)((int)adjusted_face_index * mip_size + mip_src),
                     (unsigned int)mip_size);
            iVar8 = iVar8 + mip_size;
          } else {
            /* swizzled/tiled: must be face 0, mip 0 */
            if ((face_index != 0) || (adjusted_face_index != 0)) {
              display_assert(
                "face_index==0 && adjusted_face_index==0",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24c, 1);
              system_exit(-1);
            }
            if ((short)local_c != 0) {
              display_assert(
                "mipmap_index==0",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24d, 1);
              system_exit(-1);
            }
            if ((*(unsigned char *)(param_1 + 0xe) & 2) != 0) {
              display_assert(
                "!TEST_FLAG(bitmap->flags, _bitmap_compressed_bit)",
                "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x24e, 1);
              system_exit(-1);
            }
            row_pitch = bitmap_mipmap_get_row_pitch((void *)param_1, local_c);
            sVar3 = 0;
            if (0 < *(short *)(param_1 + 6)) {
              do {
                csmemcpy((void *)(swizzle_buf + iVar8), (void *)mip_src,
                         (unsigned int)row_pitch);
                csmemset((void *)(swizzle_buf + iVar8 + row_pitch), 0,
                         (unsigned int)(-row_pitch & 0x3f));
                mip_src = mip_src + row_pitch;
                iVar8 = iVar8 + row_pitch + (-row_pitch & 0x3f);
                sVar3 = sVar3 + 1;
              } while (sVar3 < *(short *)(param_1 + 6));
            }
          }
          local_c = local_c + 1;
        } while ((short)local_c <= (short)local_20);
      }
      /* align offset to 128 bytes at end of each face */
      csmemset((void *)(swizzle_buf + iVar8), 0, (unsigned int)(-iVar8 & 0x7f));
      iVar8 = iVar8 + (-iVar8 & 0x7f);
      face_index = face_index + 1;
    } while (face_index < local_1c);
  }
  if (iVar8 != total_size) {
    display_assert("offset==size",
                   "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x271,
                   1);
    system_exit(-1);
  }
  csmemcpy(*(void **)(param_1 + 0x2c), (void *)swizzle_buf,
           (unsigned int)total_size);
  debug_free((void *)swizzle_buf,
             "c:\\halo\\SOURCE\\rasterizer\\rasterizer_swizzle.c", 0x275);
  return 1;
}


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

/* FUN_00181180 (0x181180) — readable C lift (restored pre-naked). */
void FUN_00181180(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;
  int ebp = 0;

  FUN_0016f910(24);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d7] */
  /* test (char)eax, (char)eax -> je 0x181293 */
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x181293 */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x181293 */
  /* relift: cmp word ptr [ebp - 4], 0 -> jl 0x1811db */
  /* cmp esi, eax -> jl 0x1811f8 */
  display_assert((char *)0x002b0174, (char *)0x002b01b4, 67, 0);
  system_exit(0);
  FUN_00181060((void *)0);
  /* test eax, eax -> jle 0x18123a */
  FUN_0017d040();
  /* cmp eax, 0xff -> jge 0x18123f */
  /* test (char)ecx, (char)ecx -> jne 0x181242 */
  /* cmp (char)ecx, (char)eax -> jbe 0x18125e */
  /* cmp esi, eax -> jl 0x1811d0 */
  /* mem[0x004d0480] = 0 */
  FUN_0016fa40(24);

  (void)eax;
  (void)ecx;
  (void)esi;
  (void)ebp;
}


/* FUN_001812c0 (0x1812c0) — readable C lift (restored pre-naked). */
void FUN_001812c0(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1812ef */
  display_assert((char *)0x0029f510, (char *)0x002b01b4, 240, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18130f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b039c, (char *)0x002b01b4, 241, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18134f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b035c, (char *)0x002b01b4, 242, 0);
  system_exit(0);
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* test (char)eax, 1 -> jne 0x18138f */
  /* relift: relift: fcomp dword ptr [0x2533c8] */
  display_assert((char *)0x002b031c, (char *)0x002b01b4, 243, 0);
  system_exit(0);
  /* cmp ecx, 0x80 -> jge 0x1813f3 */
  /* mem[0x005a37e0] = ecx */
  /* mem[0x005a5548] = ecx */
  error(0, (char *)0x002b02ec);

  (void)eax;
  (void)ecx;
  (void)esi;
}


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




/* rasterizer_xbox_bitmap_swizzle2d_byte (0x182840) — readable C lift (restored pre-naked). */
void rasterizer_xbox_bitmap_swizzle2d_byte(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 147, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x18289c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 148, 0);
  system_exit(0);
  ((void(*)(void))FUN_00182610)();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182908 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1828f9 */

  (void)esi;
  (void)edi;
  (void)ebp;
}



/* rasterizer_xbox_bitmap_swizzle2d_word (0x182910) — readable C lift (restored pre-naked). */
void rasterizer_xbox_bitmap_swizzle2d_word(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 176, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x18296c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 177, 0);
  system_exit(0);
  ((void(*)(void))FUN_00182610)();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x1829da */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x1829cb */

  (void)esi;
  (void)edi;
  (void)ebp;
}



/* rasterizer_xbox_bitmap_swizzle2d_long (0x1829f0) — readable C lift (restored pre-naked). */
void rasterizer_xbox_bitmap_swizzle2d_long(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 205, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182a4c */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 206, 0);
  system_exit(0);
  ((void(*)(void))FUN_00182610)();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182ab8 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182aa9 */

  (void)esi;
  (void)edi;
  (void)ebp;
}



/* rasterizer_xbox_bitmap_swizzle3d_byte (0x182ac0) — readable C lift (restored pre-naked). */
void rasterizer_xbox_bitmap_swizzle3d_byte(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 235, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182b1f */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 236, 0);
  system_exit(0);
  ((void(*)(void))FUN_00182610)();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182bc8 */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182bb9 */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182ba0 */

  (void)esi;
  (void)edi;
  (void)ebp;
}



/* rasterizer_xbox_bitmap_swizzle3d_word (0x182bd0) — readable C lift (restored pre-naked). */
void rasterizer_xbox_bitmap_swizzle3d_word(void)
{
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  display_assert((char *)0x002b08ac, (char *)0x002b087c, 270, 0);
  system_exit(0);
  /* relift: cmp dword ptr [ebp + 0xc], edi -> jne 0x182c2f */
  display_assert((char *)0x002b07dc, (char *)0x002b087c, 271, 0);
  system_exit(0);
  ((void(*)(void))FUN_00182610)();
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182cda */
  /* test (int16_t)eax, (int16_t)eax -> jle 0x182ccb */
  /* test (int16_t)esi, (int16_t)esi -> jle 0x182cb2 */

  (void)esi;
  (void)edi;
  (void)ebp;
}



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

/* FUN_00181670 (0x181670) — readable C lift (restored pre-naked). */
void FUN_00181670(int *params)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x18169b */
  display_assert((char *)0x0029f510, (char *)0x002b01b4, 266, 0);
  system_exit(0);
  /* relift: cmp dword ptr [edi], 0 -> jne 0x1816c0 */
  display_assert((char *)0x002b05d4, (char *)0x002b01b4, 267, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [0x5a5bc2] -> je 0x1816f2 */
  display_assert((char *)0x002b0568, (char *)0x002b01b4, 268, 0);
  system_exit(0);
  /* relift: relift: mov (char)eax, byte ptr [0x3256d7] */
  /* test (char)eax, (char)eax -> je 0x1818fa */
  /* relift: relift: mov (int16_t)eax, word ptr [0x46e008] */
  /* cmp (int16_t)eax, 1 -> jg 0x1818fa */
  /* relift: cmp word ptr [0x31fa98], 1 -> jg 0x1818fa */
  /* relift: cmp word ptr [0x5a5bc0], 0 -> jne 0x1818fa */
  /* cmp ecx, 0x400 -> jge 0x1818db */
  /* relift: relift: fcomp dword ptr [0x2533c0] */
  /* relift: relift: fld dword ptr [0x5a5bdc] */
  /* relift: relift: fld dword ptr [0x5a5bd8] */
  /* relift: relift: fld dword ptr [0x5a5bd4] */
  /* relift: test dword ptr [edi + 0x18], 0xff000000 -> jbe 0x1818fa */
  /* mem[0x004d0480] = ecx */
  FUN_00181020(0);
  csmemcpy((void *)(uintptr_t)ebx, (void *)(uintptr_t)edi, 40);
  /* relift: cmp word ptr [edi + 0x1c], -1 -> jne 0x18186e */
  /* cmp (int16_t)eax, 0xffff -> jne 0x181822 */
  /* test (int16_t)edi, (int16_t)edi -> jl 0x1817fd */
  /* cmp (int16_t)edi, 8 -> jl 0x1818c6 */
  display_assert((char *)0x002b0508, (char *)0x002b01b4, 310, 0);
  system_exit(0);
  /* cmp esi, 0x10000 -> jl 0x181858 */
  display_assert((char *)0x002b04a0, (char *)0x002b01b4, 321, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x181886 */
  /* cmp (int16_t)eax, 0x380 -> jl 0x1818a6 */
  display_assert((char *)0x002b0450, (char *)0x002b01b4, 338, 0);
  system_exit(0);
  /* relift: cmp (int16_t)eax, word ptr [esi] -> je 0x1818c6 */
  csmemset((void *)(uintptr_t)ecx, 0, 32);
  /* relift: relift: mov (char)eax, byte ptr [0x4d0484] */
  /* test (char)eax, (char)eax -> jne 0x1818fa */
  error(0, (char *)0x002b0418);
  /* relift: relift: mov byte ptr [0x4d0484], 1 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

