/* --- D3D8:d3dsurface.obj batch drafts (2026-07-26) --- */

/* 0x1e9190 */
int __stdcall D3DDevice_PersistDisplay(void)
{
  return 0;
}

/* 0x1f4140 */
void __stdcall Get2DSurfaceDesc(void *texture, unsigned int level, void *desc)
{
  (void)texture;
  (void)level;
  (void)desc;
}

/* 0x1f44f0 */
void __stdcall Lock2DSurface(void *texture, unsigned int face, unsigned int level, void *locked_rect, void *rect, unsigned int flags)
{
  (void)texture;
  (void)face;
  (void)level;
  (void)locked_rect;
  (void)rect;
  (void)flags;
}

/* 0x1ff03f */
float *__stdcall mat4x4_transform_vec4(float *out, float *in, float *matrix)
{
  (void)out;
  (void)in;
  (void)matrix;
  return NULL;
}

/* 0x1ff913 */
void __stdcall matrix_build_perspective_projection(void *matrix_out, float fov, float aspect, float z_near, float z_far)
{
  (void)matrix_out;
  (void)fov;
  (void)aspect;
  (void)z_near;
  (void)z_far;
}

/* 0x1ffc57 */
void __stdcall matrix_build_ortho_projection(void *matrix_out, float scale_x, float scale_y, float z_near, float z_far)
{
  (void)matrix_out;
  (void)scale_x;
  (void)scale_y;
  (void)z_near;
  (void)z_far;
}
