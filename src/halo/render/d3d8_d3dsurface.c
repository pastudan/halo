/* --- D3D8:d3dsurface.obj batch drafts (2026-07-26) --- */

extern int DbgPrint(uintptr_t fmt, ...);

/* D3DDevice_PersistDisplay (0x1e9190) — Capstone tip: device+0x408==0 → E_FAIL. */
int __stdcall D3DDevice_PersistDisplay(void)
{
  void *device;
  void *front;

  front = ((void *(*)(void))*(void **)0x2532ac)();
  if (front) {
    ((void (__stdcall *)(void *))*(void **)0x2531f4)(front);
    ((void (__stdcall *)(int))*(void **)0x2532b8)(0);
  }
  device = *(void **)0x1fe6a0;
  if (!*(unsigned int *)((char *)device + 0x408))
    return (int)0x80004005;
  return 0;
}


/* Get2DSurfaceDesc (0x1f4140) — Capstone tip: fill D3DSURFACE_DESC from texture.
 * Snapshot stubs FUN_001f3ff0 as ret-only (same as Lock2DSurface/FUN_001f4270):
 * post-call the XBE reloads the stdcall arg slots (texture, level, desc). */
void __stdcall Get2DSurfaceDesc(void *texture, unsigned int level, void *desc)
{
  unsigned int *d;
  unsigned int type;
  unsigned int o0, o2, o3, o4;
  unsigned char fmt;
  unsigned char flags;
  void *device;
  unsigned int g;

  d = (unsigned int *)desc;
  fmt = *((unsigned char *)texture + 0xd);
  d[0] = (unsigned int)fmt;
  type = D3DResource_GetType(texture);
  d[1] = type;
  d[2] = 0;
  if (level == 0) {
    flags = *(unsigned char *)(0x1f9d58u + (unsigned int)fmt);
    if ((signed char)flags < 0)
      d[2] = 1;
    else if (flags & 0x40)
      d[2] = 2;
  }
  device = *(void **)0x1fe6a0;
  if (*(unsigned int *)((char *)texture + 4) ==
          *(unsigned int *)((char *)device + 0x2154) &&
      ((g = *(unsigned int *)0x1fb8b0), (g & 0x3000u) != 0))
    d[4] = g;
  else
    d[4] = 0x11;
  o0 = o2 = o3 = o4 = 0;
  FUN_001f3ff0(texture, level, &o0, d, &o2, &o3, &o4);
  (void)o0;
  (void)o2;
  (void)o3;
  (void)o4;
  /* Ret-only stub: XBE stores the untouched arg slots into desc. */
  d[5] = (unsigned int)(uintptr_t)texture;
  d[6] = (unsigned int)(uintptr_t)desc;
  d[3] = level;
}


/* Lock2DSurface (0x1f44f0) — Capstone tip: flags|0x20 + rect==NULL. */
void __stdcall Lock2DSurface(void *texture, unsigned int face, unsigned int level,
                             void *locked_rect, void *rect, unsigned int flags)
{
  unsigned int *lr;
  unsigned char flag_byte;
  unsigned int out0, out1, out2, out3, out4;
  unsigned int bits;

  lr = (unsigned int *)locked_rect;
  flag_byte = (unsigned char)flags;
  out0 = out1 = out2 = out3 = out4 = 0;
  if (!(flag_byte & 0x20))
    D3D_BlockOnResource(texture);

  FUN_001f4270(texture, face, level, &out0, &out1, &out2, &out3, &out4);

  bits = flags;
  if (flag_byte & 0x40)
    bits |= 0xf0000000u;

  lr[0] = (unsigned int)(uintptr_t)texture;
  lr[1] = bits;
  (void)rect;
}


/* mat4x4_transform_vec4 (0x1ff03f) — readable C lift: D3D row-major vec4*xform. */
float *__stdcall mat4x4_transform_vec4(float *out, float *in, float *matrix)
{
  float x;
  float y;
  float z;
  float w;

  x = in[0];
  y = in[1];
  z = in[2];
  w = in[3];
  out[0] = x * matrix[0] + y * matrix[4] + z * matrix[8] + w * matrix[12];
  out[1] = x * matrix[1] + y * matrix[5] + z * matrix[9] + w * matrix[13];
  out[2] = x * matrix[2] + y * matrix[6] + z * matrix[10] + w * matrix[14];
  out[3] = x * matrix[3] + y * matrix[7] + z * matrix[11] + w * matrix[15];
  return out;
}

/* matrix_build_perspective_projection (0x1ff913) — readable C lift.
 * kb names fov/aspect; XBE treats them as frustum width/height at near plane. */
void __stdcall matrix_build_perspective_projection(void *matrix_out, float fov, float aspect, float z_near, float z_far)
{
  float *m;
  float two_n;
  float q;

  m = (float *)matrix_out;
  two_n = z_near + z_near;
  m[0] = two_n / fov;
  m[1] = 0.0f;
  m[2] = 0.0f;
  m[3] = 0.0f;
  m[4] = 0.0f;
  m[5] = two_n / aspect;
  m[6] = 0.0f;
  m[7] = 0.0f;
  m[8] = 0.0f;
  m[9] = 0.0f;
  q = z_far / (z_far - z_near);
  m[10] = q;
  m[11] = 1.0f;
  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = -(z_near * q);
  m[15] = 0.0f;
}

/* matrix_build_ortho_projection (0x1ffc57) — Capstone full leaf: 2/sx, 2/sy, 1/(f-n). */
void __stdcall matrix_build_ortho_projection(void *matrix_out, float scale_x, float scale_y,
                                             float z_near, float z_far)
{
  float *m;
  float q;

  m = (float *)matrix_out;
  m[0] = 2.0f / scale_x;
  m[1] = 0.0f;
  m[2] = 0.0f;
  m[3] = 0.0f;
  m[4] = 0.0f;
  m[5] = 2.0f / scale_y;
  m[6] = 0.0f;
  m[7] = 0.0f;
  m[8] = 0.0f;
  m[9] = 0.0f;
  q = 1.0f / (z_far - z_near);
  m[10] = q;
  m[11] = 0.0f;
  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = -(z_near * q);
  m[15] = 1.0f;
}

