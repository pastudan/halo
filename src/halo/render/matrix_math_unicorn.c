#include <stdint.h>

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
void __stdcall matrix_build_perspective_projection(void *matrix_out, float fov,
                                                   float aspect, float z_near,
                                                   float z_far)
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
