/* Render camera utilities. */

#define MAXIMUM_RENDER_CAMERA_WARNING_CONDITIONS 64

static char render_camera_warnings_initialized; /* 0x4d0e18 */
static float render_camera_warning_values
  [MAXIMUM_RENDER_CAMERA_WARNING_CONDITIONS]; /* 0x4d0d18
                                               */

/* render_camera_check_warning_condition - 0x185770
 * Tracks maximum frustum-integrity violation distances per condition ID.
 * Logs when a condition exceeds its previous worst value. */
void render_camera_check_warning_condition(int16_t id, float value)
{
  assert_halt(id >= 0 && id < MAXIMUM_RENDER_CAMERA_WARNING_CONDITIONS);

  if (!render_camera_warnings_initialized) {
    csmemset(render_camera_warning_values, 0,
             sizeof(render_camera_warning_values));
    render_camera_warnings_initialized = 1;
  }

  if (value > 0.05f && value > render_camera_warning_values[id]) {
    error(2,
          "### ERROR cameras: frustum-integrity condition #%d violated by %f",
          (int)id, (double)value);
    render_camera_warning_values[id] = value;
  }
}

/* Typedefs for math helpers called via hardcoded address. */
typedef float (*normalize_vector3_fn)(float *v);
typedef void (*matrix4x3_inverse_fn)(float *src, float *dst);
typedef void (*matrix4x3_transform_point_fn)(float *mat, float *in, float *out);
typedef void (*matrix4x3_transform_plane_fn)(float *mat, float *in, float *out);
typedef int (*valid_real_matrix4x3_fn)(float *mat);

#define normalize_vector3 ((normalize_vector3_fn)0x13010)
#define matrix4x3_inverse ((matrix4x3_inverse_fn)0x109150)
#define matrix4x3_transform_point ((matrix4x3_transform_point_fn)0x109590)
#define matrix4x3_transform_plane ((matrix4x3_transform_plane_fn)0x10a1c0)
#define valid_real_matrix4x3 ((valid_real_matrix4x3_fn)0xf6d00)

/* Compute the adjusted FOV tangent for the render camera.
 * Uses FPTAN: tan(fov * half_constant) * aspect_ratio */
double render_camera_get_adjusted_field_of_view_tangent(float fov)
{
#if defined(_MSC_VER) && !defined(__clang__)
  double result;
  __asm {
    fld fov
    fmul dword ptr ds:[253398h]
    fptan
    fstp st(0)
    fmul dword ptr ds:[2b1504h]
    fstp result
  }
  return result;
#else
  double result;
  asm volatile("flds %[f]\n\t"
               "fmuls 0x253398\n\t"
               "fptan\n\t"
               "fstp %%st(0)\n\t"
               "fmuls 0x2b1504"
               : "=t"(result)
               : [f] "m"(fov)
               : "memory");
  return result;
#endif
}

/* Build the full view frustum from a camera, optional viewport bounds, and
 * projection flag.  Populates the frustum structure with:
 *   - viewport bounds (float[4])
 *   - world-to-view / view-to-world matrices (matrix4x3 each)
 *   - 6 clip planes (left, right, bottom, top, near, far)
 *   - z_near / z_far copies
 *   - 4 far-plane frustum corners + camera position + projection center
 *   - AABB (min/max xyz) of the frustum corners
 *   - optional projection matrix and scale factors
 * Assertions guard field-of-view, z ordering, and viewport sanity.
 * Ends with 22 frustum-integrity warning checks (distances of corners
 * and projection center to each clip plane). */
void render_camera_build_frustum(camera_t *camera, float *bounds,
                                 float *frustum, bool do_projection)
{
  float *forward = (float *)&camera->unk_12; /* +0x0c */
  float *up = (float *)&camera->unk_24; /* +0x18 */
  float *pos = (float *)&camera->unk_0; /* +0x00 */
  float *proj_data = (float *)camera->unk_68; /* +0x44 */

  /* Compute viewport pixel dimensions. */
  int width_px =
    (int)camera->viewport_bounds.x1 - (int)camera->viewport_bounds.x0;
  int height_px =
    (int)camera->viewport_bounds.y1 - (int)camera->viewport_bounds.y0;
  float width_f = (float)width_px;
  float height_f = (float)height_px;

  /* Copy or default the viewport bounds (frustum[0..3]). */
  if (bounds == 0) {
    frustum[2] = -1.0f;
    frustum[0] = -1.0f;
    frustum[3] = 1.0f;
    frustum[1] = 1.0f;
  } else {
    frustum[0] = bounds[0];
    frustum[1] = bounds[1];
    frustum[2] = bounds[2];
    frustum[3] = bounds[3];
  }

  /* Compute half-ranges and viewport centers. */
  float half_w_range = (frustum[1] - frustum[0]) * 0.5f;
  float half_h_range = (frustum[3] - frustum[2]) * 0.5f;
  float center_x = (frustum[0] + frustum[1]) / half_w_range * -0.5f;
  float center_y = (frustum[2] + frustum[3]) / half_h_range * -0.5f;

  /* Compute tan(vfov/2) and inverse tangent scale factors.
   * inv_tan_x accounts for the aspect ratio correction. */
  float tan_half_fov;
#if defined(_MSC_VER) && !defined(__clang__)
  {
    float vfov = camera->vertical_field_of_view;
    __asm {
      fld vfov
      fmul dword ptr ds:[253398h]
      fptan
      fstp st(0)
      fstp tan_half_fov
    }
  }
#else
  asm volatile("flds %[f]\n\t"
               "fmuls 0x253398\n\t"
               "fptan\n\t"
               "fstp %%st(0)"
               : "=t"(tan_half_fov)
               : [f] "m"(camera->vertical_field_of_view)
               : "memory");
#endif

  float inv_tan_x = 1.0f / (half_w_range / height_f * width_f * tan_half_fov);
  float inv_tan_y = 1.0f / (tan_half_fov * half_h_range);

  /* Assertions. */
  assert_halt(camera->vertical_field_of_view <
              *(float *)0x2b16f4); /* _pi - _real_epsilon */
  if (camera->vertical_field_of_view <= *(float *)0x253f44) {
    char *msg = csprintf((char *)0x5ab100,
                         "### FATAL ERROR: field of view set to %f (0x%x)",
                         (double)camera->vertical_field_of_view,
                         *(int *)&camera->vertical_field_of_view);
    display_assert(msg, "c:\\halo\\SOURCE\\render\\render_cameras.c", 0x1b0,
                   true);
    system_exit(-1);
  }
  assert_halt(camera->z_near >= 0.0f);
  assert_halt(camera->z_far > camera->z_near);
  assert_halt(camera->viewport_bounds.x0 < camera->viewport_bounds.x1);
  assert_halt(camera->viewport_bounds.y0 < camera->viewport_bounds.y1);

  /* Build the view-to-world matrix (frustum[0x11..0x1d]).
   * Columns are: right (cross product), up (double cross), -forward,
   * then the camera position as the translation row. */
  float right[3], up2[3], neg_fwd[3];

  /* right = up x forward */
  right[0] = up[2] * forward[1] - up[1] * forward[2];
  right[1] = up[0] * forward[2] - up[2] * forward[0];
  right[2] = up[1] * forward[0] - forward[1] * up[0];

  /* up2 = right x forward  (re-orthogonalized up) */
  up2[0] = right[1] * forward[2] - right[2] * forward[1];
  up2[1] = right[2] * forward[0] - right[0] * forward[2];
  up2[2] = right[0] * forward[1] - right[1] * forward[0];

  /* neg_fwd = -forward */
  neg_fwd[0] = -forward[0];
  neg_fwd[1] = -forward[1];
  neg_fwd[2] = -forward[2];

  normalize_vector3(right);
  normalize_vector3(up2);
  normalize_vector3(neg_fwd);

  /* Store view_to_world matrix at frustum[0x12..0x1d].
   * frustum[0x11] = scale (1.0). */
  frustum[0x12] = right[0];
  frustum[0x13] = right[1];
  frustum[0x14] = right[2];
  frustum[0x15] = up2[0];
  frustum[0x16] = up2[1];
  frustum[0x17] = up2[2];
  frustum[0x18] = neg_fwd[0];
  frustum[0x19] = neg_fwd[1];
  frustum[0x1a] = neg_fwd[2];
  frustum[0x1b] = pos[0];
  frustum[0x1c] = pos[1];
  frustum[0x1d] = pos[2];
  frustum[0x11] = 1.0f;

  /* Compute world_to_view = inverse(view_to_world).
   * frustum[4..0x10] = world_to_view matrix. */
  float *view_to_world = &frustum[0x11];
  float *world_to_view = &frustum[4];
  matrix4x3_inverse(view_to_world, world_to_view);

  assert_halt(valid_real_matrix4x3(world_to_view));
  assert_halt(valid_real_matrix4x3(view_to_world));

  /* Build clip planes.  Each plane is stored as (nx, ny, nz, d).
   * Plane normals are constructed in view space, normalized, then
   * the distance d is computed as dot(normal, global_forward) where
   * global_forward is the vector at **(float**)0x31fc1c. */
  float *global_fwd = *(float **)0x31fc1c;
  float plane_vs[4]; /* view-space plane: (x, y, z, d) */

  /* Left plane (frustum[0x1e..0x21]) */
  plane_vs[0] = -inv_tan_x;
  plane_vs[1] = 0.0f;
  plane_vs[2] = center_x + 1.0f;
  float saved_cx_plus_1 = plane_vs[2];
  normalize_vector3(plane_vs);
  plane_vs[3] = plane_vs[0] * global_fwd[0] + plane_vs[1] * global_fwd[1] +
                plane_vs[2] * global_fwd[2];
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x1e]);

  /* Right plane (frustum[0x22..0x25]) */
  plane_vs[0] = inv_tan_x;
  plane_vs[1] = 0.0f;
  plane_vs[2] = 1.0f - center_x;
  normalize_vector3(plane_vs);
  plane_vs[3] = plane_vs[0] * global_fwd[0] + plane_vs[1] * global_fwd[1] +
                plane_vs[2] * global_fwd[2];
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x22]);

  /* Bottom plane (frustum[0x26..0x29]) */
  plane_vs[0] = 0.0f;
  plane_vs[1] = -inv_tan_y;
  plane_vs[2] = center_y + 1.0f;
  float saved_cy_plus_1 = plane_vs[2];
  normalize_vector3(plane_vs);
  plane_vs[3] = plane_vs[0] * global_fwd[0] + plane_vs[1] * global_fwd[1] +
                plane_vs[2] * global_fwd[2];
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x26]);

  /* Top plane (frustum[0x2a..0x2d]) */
  plane_vs[0] = 0.0f;
  plane_vs[1] = inv_tan_y;
  plane_vs[2] = 1.0f - center_y;
  normalize_vector3(plane_vs);
  plane_vs[3] = plane_vs[0] * global_fwd[0] + plane_vs[1] * global_fwd[1] +
                plane_vs[2] * global_fwd[2];
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x2a]);

  /* Near plane (frustum[0x2e..0x31]) */
  plane_vs[0] = 0.0f;
  plane_vs[1] = 0.0f;
  plane_vs[2] = 1.0f;
  plane_vs[3] = -camera->z_near;
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x2e]);

  /* Far plane (frustum[0x32..0x35]) */
  plane_vs[0] = 0.0f;
  plane_vs[1] = 0.0f;
  plane_vs[2] = -1.0f;
  plane_vs[3] = camera->z_far;
  matrix4x3_transform_plane(view_to_world, plane_vs, &frustum[0x32]);

  /* Store z_near and z_far copies. */
  frustum[0x36] = camera->z_near;
  frustum[0x37] = camera->z_far;

  /* Compute scale factors for projection. */
  float scale_x = 1.0f / inv_tan_x;
  float scale_y = 1.0f / inv_tan_y;

  float half_z = (camera->z_far + camera->z_near) * 0.5f;

  /* Compute 4 far-plane frustum corners in world space.
   * Each corner is a view-space direction scaled by -z_far, then
   * transformed by view_to_world into world space. */
  float corner_lx = saved_cx_plus_1 * -(scale_x * camera->z_far);
  float corner_rx = (center_x - 1.0f) * -(scale_x * camera->z_far);
  float corner_by = saved_cy_plus_1 * -(scale_y * camera->z_far);
  float corner_ty = (center_y - 1.0f) * -(scale_y * camera->z_far);

  float corner_vs[3];

  /* Corner 0: left-bottom-far => frustum[0x38..0x3a] */
  corner_vs[0] = corner_lx;
  corner_vs[1] = corner_by;
  corner_vs[2] = -camera->z_far;
  matrix4x3_transform_point(view_to_world, corner_vs, &frustum[0x38]);

  /* Corner 1: right-bottom-far => frustum[0x3b..0x3d] */
  corner_vs[0] = corner_rx;
  corner_vs[1] = corner_by;
  corner_vs[2] = -camera->z_far;
  matrix4x3_transform_point(view_to_world, corner_vs, &frustum[0x3b]);

  /* Corner 2: left-top-far => frustum[0x3e..0x40] */
  corner_vs[0] = corner_lx;
  corner_vs[1] = corner_ty;
  corner_vs[2] = -camera->z_far;
  matrix4x3_transform_point(view_to_world, corner_vs, &frustum[0x3e]);

  /* Corner 3: right-top-far => frustum[0x41..0x43] */
  corner_vs[0] = corner_rx;
  corner_vs[1] = corner_ty;
  corner_vs[2] = -camera->z_far;
  matrix4x3_transform_point(view_to_world, corner_vs, &frustum[0x41]);

  /* Camera position => frustum[0x44..0x46] */
  frustum[0x44] = pos[0];
  frustum[0x45] = pos[1];
  frustum[0x46] = pos[2];

  /* Projection center => frustum[0x47..0x49] */
  float proj_center_vs[3];
  proj_center_vs[0] = -(scale_x * half_z * center_x);
  proj_center_vs[1] = -(scale_y * half_z * center_y);
  proj_center_vs[2] = -half_z;
  matrix4x3_transform_point(view_to_world, proj_center_vs, &frustum[0x47]);

  /* Compute AABB of frustum corners (frustum[0x4a..0x4f]).
   * Initialize from corner 0, then expand with corners 1-3. */
  float *corner0 = &frustum[0x38];
  frustum[0x4b] = corner0[0]; /* max_x = corner0.x */
  frustum[0x4a] = corner0[0]; /* min_x = corner0.x */
  frustum[0x4d] = corner0[1]; /* max_y */
  frustum[0x4c] = corner0[1]; /* min_y */
  frustum[0x4f] = corner0[2]; /* max_z */
  frustum[0x4e] = corner0[2]; /* min_z */

  {
    float *cp = &frustum[0x3c]; /* start at corner1[0] (= 0x3b+1?) */
    int i;
    /* The loop walks 4 iterations starting at frustum[0x3c-1] = 0x3b.
     * ECX starts at ESI+0xF0 = frustum + 0x3c. The comparisons use
     * [ECX-4], [ECX], [ECX+4] => frustum[0x3b], [0x3c], [0x3d] etc.
     * Actually the disasm starts ECX at ESI+0xF0 and accesses
     * [ECX-4], [ECX], [ECX+4]. Let me trace: */
    /* Initial: ECX = &frustum[0x3c] (= ESI + 0xF0).
     * Iteration 0: [ECX-4]=frustum[0x3b], [ECX]=frustum[0x3c],
     *              [ECX+4]=frustum[0x3d]
     * Iteration 1: ECX += 3 => &frustum[0x3f]:
     *              [ECX-4]=frustum[0x3e], etc.
     * ...4 iterations covering corners 1,2,3 and one more. */
    /* Actually: from the disasm, ECX = ESI+0xF0, EDX=4, loop body
     * uses [ECX-4], [ECX], [ECX+4], increments ECX by 0xC (3 floats),
     * decrements EDX, loops while EDX != 0.
     * So 4 iterations at offsets: 0xF0, 0xFC, 0x108, 0x114
     * = frustum[0x3c], [0x3f], [0x42], [0x45]
     * Corner data starts at [0x3b] with stride 3:
     * iter0: [0x3b,0x3c,0x3d] = corner 1 (indices 0x3b-0x3d)
     * iter1: [0x3e,0x3f,0x40] = corner 2
     * iter2: [0x41,0x42,0x43] = corner 3
     * iter3: [0x44,0x45,0x46] = camera position */
    cp = &frustum[0x3c];
    for (i = 4; i != 0; i--) {
      if (frustum[0x4a] > cp[-1])
        frustum[0x4a] = cp[-1];
      if (frustum[0x4c] > cp[0])
        frustum[0x4c] = cp[0];
      if (frustum[0x4e] > cp[1])
        frustum[0x4e] = cp[1];
      if (frustum[0x4b] < cp[-1])
        frustum[0x4b] = cp[-1];
      if (frustum[0x4d] < cp[0])
        frustum[0x4d] = cp[0];
      if (frustum[0x4f] < cp[1])
        frustum[0x4f] = cp[1];
      cp += 3;
    }
  }

  /* Projection matrix block (frustum[0x50..0x62]). */
  if (!do_projection) {
    /* No projection: zero the matrix and scale, clear flag. */
    csmemset(&frustum[0x51], 0, 0x40);
    csmemset(&frustum[0x61], 0, 0x8);
    *(unsigned char *)&frustum[0x50] = 0;
  } else {
    /* Build the projection matrix from the camera's projection
     * data at camera->unk_68 (+0x44, 4 floats). */
    if (camera->z_near == 0.0f) {
      /* z_near == 0: transform the projection data through
       * world_to_view to get the view-space direction. */
      matrix4x3_transform_plane(world_to_view, proj_data, plane_vs);
      /* plane_vs now contains the view-space values. */
    } else {
      /* z_near != 0: use default forward direction. */
      plane_vs[0] = 0.0f;
      plane_vs[2] = 1.0f;
      plane_vs[3] = -camera->z_near;
      plane_vs[1] = 0.0f;
    }

    /* Compute adjusted projection parameters. */
    float inv_z = 1.0f / plane_vs[2];
    float neg_proj_d = -(plane_vs[3] * inv_z);
    float abs_x = inv_z * plane_vs[0];
    float abs_y = inv_z * plane_vs[1];
    if (abs_x < 0.0f)
      abs_x = -abs_x;
    if (abs_y < 0.0f)
      abs_y = -abs_y;
    float denom =
      (camera->z_far - neg_proj_d) * (abs_x + abs_y + *(double *)0x2573d8);
    float proj_scale = camera->z_far / denom;

    plane_vs[0] = inv_z * proj_scale * plane_vs[0];
    plane_vs[1] = inv_z * proj_scale * plane_vs[1];
    plane_vs[3] = -(proj_scale * neg_proj_d);

    /* If the adjusted distance is positive and z_near is zero,
     * flip all signs (face the other way). */
    if (plane_vs[3] > 0.0f && camera->z_near == 0.0f) {
      plane_vs[0] = -plane_vs[0];
      plane_vs[1] = -plane_vs[1];
      proj_scale = -proj_scale;
      plane_vs[3] = -plane_vs[3];
    }

    /* Write the 4x4 projection matrix. */
    csmemset(&frustum[0x51], 0, 0x40);
    frustum[0x53] = -plane_vs[0];
    frustum[0x57] = -plane_vs[1];
    frustum[0x51] = inv_tan_x;
    frustum[0x56] = inv_tan_y;
    frustum[0x5c] = -1.0f;
    frustum[0x59] = -center_x;
    frustum[0x5f] = plane_vs[3];
    *(unsigned char *)&frustum[0x50] = 1;
    frustum[0x5a] = -center_y;
    frustum[0x5b] = -proj_scale;
    frustum[0x61] = inv_tan_x * width_f * 0.5f;
    frustum[0x62] = inv_tan_y * height_f * 0.5f;
  }

  /* Frustum integrity checks: measure signed distances from key
   * points (corners, camera position, projection center) to each
   * clip plane.  The absolute distance is passed to the warning
   * function along with a condition ID (0..0x15). */
  float *left_p = &frustum[0x1e];
  float *right_p = &frustum[0x22];
  float *bottom_p = &frustum[0x26];
  float *top_p = &frustum[0x2a];
  float *near_p = &frustum[0x2e];
  float *far_p = &frustum[0x32];
  float *c0 = &frustum[0x38];
  float *c1 = &frustum[0x3b];
  float *c2 = &frustum[0x3e];
  float *c3 = &frustum[0x41];
  float *cam_pos = &frustum[0x44];
  float *proj_ctr = &frustum[0x47];
  float d;

  /* Corners vs left plane */
  d = c0[0] * left_p[0] + c0[1] * left_p[1] + c0[2] * left_p[2] - left_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(0, d);

  d = c2[0] * left_p[0] + c2[1] * left_p[1] + c2[2] * left_p[2] - left_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(1, d);

  d = cam_pos[0] * left_p[0] + cam_pos[1] * left_p[1] + cam_pos[2] * left_p[2] -
      left_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(2, d);

  /* Corners vs right plane */
  d = c1[0] * right_p[0] + c1[1] * right_p[1] + c1[2] * right_p[2] - right_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(3, d);

  d = c3[0] * right_p[0] + c3[1] * right_p[1] + c3[2] * right_p[2] - right_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(4, d);

  d = cam_pos[0] * right_p[0] + cam_pos[1] * right_p[1] +
      cam_pos[2] * right_p[2] - right_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(5, d);

  /* Corners vs bottom plane */
  d = c0[0] * bottom_p[0] + c0[1] * bottom_p[1] + c0[2] * bottom_p[2] -
      bottom_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(6, d);

  d = c1[0] * bottom_p[0] + c1[1] * bottom_p[1] + c1[2] * bottom_p[2] -
      bottom_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(7, d);

  d = cam_pos[0] * bottom_p[0] + cam_pos[1] * bottom_p[1] +
      cam_pos[2] * bottom_p[2] - bottom_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(8, d);

  /* Corners vs top plane */
  d = c2[0] * top_p[0] + c2[1] * top_p[1] + c2[2] * top_p[2] - top_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(9, d);

  d = c3[0] * top_p[0] + c3[1] * top_p[1] + c3[2] * top_p[2] - top_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(10, d);

  d = cam_pos[0] * top_p[0] + cam_pos[1] * top_p[1] + cam_pos[2] * top_p[2] -
      top_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(11, d);

  /* Corners vs far plane */
  d = c0[0] * far_p[0] + c0[1] * far_p[1] + c0[2] * far_p[2] - far_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(12, d);

  d = c1[0] * far_p[0] + c1[1] * far_p[1] + c1[2] * far_p[2] - far_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(13, d);

  d = c2[0] * far_p[0] + c2[1] * far_p[1] + c2[2] * far_p[2] - far_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(14, d);

  d = c3[0] * far_p[0] + c3[1] * far_p[1] + c3[2] * far_p[2] - far_p[3];
  if (d < 0.0f)
    d = -d;
  render_camera_check_warning_condition(15, d);

  /* Projection center vs all 6 planes (no fabs — signed distance). */
  d = proj_ctr[0] * left_p[0] + proj_ctr[1] * left_p[1] +
      proj_ctr[2] * left_p[2] - left_p[3];
  render_camera_check_warning_condition(16, d);

  d = proj_ctr[0] * right_p[0] + proj_ctr[1] * right_p[1] +
      proj_ctr[2] * right_p[2] - right_p[3];
  render_camera_check_warning_condition(17, d);

  d = proj_ctr[0] * bottom_p[0] + proj_ctr[1] * bottom_p[1] +
      proj_ctr[2] * bottom_p[2] - bottom_p[3];
  render_camera_check_warning_condition(18, d);

  d = proj_ctr[0] * top_p[0] + proj_ctr[1] * top_p[1] + proj_ctr[2] * top_p[2] -
      top_p[3];
  render_camera_check_warning_condition(19, d);

  d = proj_ctr[0] * near_p[0] + proj_ctr[1] * near_p[1] +
      proj_ctr[2] * near_p[2] - near_p[3];
  render_camera_check_warning_condition(20, d);

  d = proj_ctr[0] * far_p[0] + proj_ctr[1] * far_p[1] + proj_ctr[2] * far_p[2] -
      far_p[3];
  render_camera_check_warning_condition(21, d);
}
/* --- render_cameras.obj batch drafts (2026-07-26) --- */

/* render_camera_new (0x185810) — readable C lift. */
void render_camera_new(void *camera)
{
  csmemset(camera, 0, 0x54);
}

/* render_camera_hack_frustum_z (0x185830) — readable C lift from XBE leaf. */
void render_camera_hack_frustum_z(void *camera, float z_near, float z_far)
{
  float denom;

  if (camera == 0 || *(unsigned char *)((char *)camera + 0x140) == 0) {
    display_assert((const char *)0x2b12dc, (const char *)0x2b12b4, 0x10f, 1);
    system_exit(-1);
  }

  if (z_near == -1.0f && z_far == -1.0f) {
    *(unsigned int *)0x4d0d08 = *(unsigned int *)((char *)camera + 0x14c);
    *(unsigned int *)0x4d0d0c = *(unsigned int *)((char *)camera + 0x15c);
    *(unsigned int *)0x4d0d10 = *(unsigned int *)((char *)camera + 0x16c);
    *(unsigned int *)0x4d0d14 = *(unsigned int *)((char *)camera + 0x17c);
    return;
  }

  if (z_near == 0.0f && z_far == 0.0f) {
    *(unsigned int *)((char *)camera + 0x14c) = *(unsigned int *)0x4d0d08;
    *(unsigned int *)((char *)camera + 0x15c) = *(unsigned int *)0x4d0d0c;
    *(unsigned int *)((char *)camera + 0x16c) = *(unsigned int *)0x4d0d10;
    *(unsigned int *)((char *)camera + 0x17c) = *(unsigned int *)0x4d0d14;
    return;
  }

  denom = z_far - z_near;
  *(unsigned int *)((char *)camera + 0x14c) = 0;
  *(unsigned int *)((char *)camera + 0x15c) = 0;
  *(float *)((char *)camera + 0x16c) = -((z_near + z_far) / denom);
  *(float *)((char *)camera + 0x17c) = (z_near * z_far * -2.0f) / denom;
}

/* render_camera_build_frustum_bounds (0x185950) — readable C lift. */
void render_camera_build_frustum_bounds(void)
{
  int edi = 0;

  display_assert((char *)0x00266e9c, (char *)0x002b12b4, 305, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1859a3 */
  display_assert((char *)0x002b1304, (char *)0x002b12b4, 306, 0);
  system_exit(0);

  (void)edi;
}



/* render_frustum_sphere_diameter_in_pixels (0x185a70) — readable C lift. */
float render_frustum_sphere_diameter_in_pixels(void *frustum, float *center, float radius)
{
  float *f = (float *)frustum;
  float z;

  z = f[0x34 / 4] * center[2] + f[0x28 / 4] * center[1] + f[0x1c / 4] * center[0] + f[0x40 / 4];
  if (z < *(float *)0x2533c0)
    z = -z;
  if (!(z > *(float *)0x25496c))
    z = *(float *)0x25496c;
  return (f[0x188 / 4] / z) * radius + (f[0x188 / 4] / z) * radius;
}

/* render_frustum_cube_view_fraction (0x185ad0) — XBE naked draft (batch 107). */
#if defined(__clang__)
static void (*const b185ad0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b185ad0_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
float render_frustum_cube_view_fraction(void *frustum __attribute__((unused)), float *bounds __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lrender_frustum_cube_view_fraction_1\n\t"
      "pushl $1\n\t"
      "pushl $0x36c\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_1:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrender_frustum_cube_view_fraction_2\n\t"
      "pushl $1\n\t"
      "pushl $0x36d\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x26184c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_2:\n\t"
      "flds (%%edi)\n\t"
      "fcomps 0x4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_3\n\t"
      "pushl $1\n\t"
      "pushl $0x36e\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_3:\n\t"
      "flds 0x8(%%edi)\n\t"
      "fcomps 0xc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_4\n\t"
      "pushl $1\n\t"
      "pushl $0x36f\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1488\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_4:\n\t"
      "flds 0x10(%%edi)\n\t"
      "fcomps 0x14(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_5\n\t"
      "pushl $1\n\t"
      "pushl $0x370\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1470\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_5:\n\t"
      "flds 0x10(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lrender_frustum_cube_view_fraction_31\n\t"
      "flds 0x14(%%edi)\n\t"
      "fcomps 0x2533c0\n\t"
      "flds 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .Lrender_frustum_cube_view_fraction_32\n\t"
      "fdivs 0x10(%%edi)\n\t"
      "movl 0x144(%%esi), %%eax\n\t"
      "movl 0x164(%%esi), %%ecx\n\t"
      "movl 0x158(%%esi), %%edx\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x168(%%esi), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movb 0x140(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x14(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "jne .Lrender_frustum_cube_view_fraction_6\n\t"
      "pushl $1\n\t"
      "pushl $0x384\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1454\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_6:\n\t"
      "flds 0x154(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_7\n\t"
      "pushl $1\n\t"
      "pushl $0x387\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b142c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_7:\n\t"
      "flds 0x174(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_8\n\t"
      "pushl $1\n\t"
      "pushl $0x388\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1404\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_8:\n\t"
      "flds 0x148(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_9\n\t"
      "pushl $1\n\t"
      "pushl $0x389\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b13dc\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_9:\n\t"
      "flds 0x178(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_10\n\t"
      "pushl $1\n\t"
      "pushl $0x38a\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b13b4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_10:\n\t"
      "flds 0x150(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_11\n\t"
      "pushl $1\n\t"
      "pushl $0x38b\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b138c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_11:\n\t"
      "flds 0x160(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_12\n\t"
      "pushl $1\n\t"
      "pushl $0x38c\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1364\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_12:\n\t"
      "cmpl $0xbf800000, 0x170(%%esi)\n\t"
      "je .Lrender_frustum_cube_view_fraction_13\n\t"
      "pushl $1\n\t"
      "pushl $0x38d\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b133c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_13:\n\t"
      "flds 0x180(%%esi)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_frustum_cube_view_fraction_14\n\t"
      "pushl $1\n\t"
      "pushl $0x38e\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1314\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_frustum_cube_view_fraction_14:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_15\n\t"
      "fld %%st(0)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_16\n\t"
      ".Lrender_frustum_cube_view_fraction_15:\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".Lrender_frustum_cube_view_fraction_16:\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_17\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_cube_view_fraction_18\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_18\n\t"
      ".Lrender_frustum_cube_view_fraction_17:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x255e94\n\t"
      ".Lrender_frustum_cube_view_fraction_18:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x10(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x14(%%edi)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_19\n\t"
      "fld %%st(0)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_20\n\t"
      ".Lrender_frustum_cube_view_fraction_19:\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".Lrender_frustum_cube_view_fraction_20:\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_21\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_cube_view_fraction_22\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_22\n\t"
      ".Lrender_frustum_cube_view_fraction_21:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x255e94\n\t"
      ".Lrender_frustum_cube_view_fraction_22:\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_23\n\t"
      "flds 0x8(%%ebp)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_24\n\t"
      ".Lrender_frustum_cube_view_fraction_23:\n\t"
      "fld %%st(0)\n\t"
      ".Lrender_frustum_cube_view_fraction_24:\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_25\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_26\n\t"
      ".Lrender_frustum_cube_view_fraction_25:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_26\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".Lrender_frustum_cube_view_fraction_26:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0xc(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc1\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_27\n\t"
      "flds 0x8(%%ebp)\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_28\n\t"
      ".Lrender_frustum_cube_view_fraction_27:\n\t"
      "fld %%st(0)\n\t"
      ".Lrender_frustum_cube_view_fraction_28:\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_29\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c8\n\t"
      "jmp .Lrender_frustum_cube_view_fraction_30\n\t"
      ".Lrender_frustum_cube_view_fraction_29:\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_view_fraction_30\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x8(%%ebp)\n\t"
      ".Lrender_frustum_cube_view_fraction_30:\n\t"
      ".byte 0xd8, 0xe2\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xe3\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fmuls 0x25337c\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_cube_view_fraction_32\n\t"
      "fstp %%st(0)\n\t"
      ".Lrender_frustum_cube_view_fraction_31:\n\t"
      "flds 0x2533c0\n\t"
      ".Lrender_frustum_cube_view_fraction_32:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b185ad0_assert), [exitfn] "m"(b185ad0_exitfn)
      : "memory");
}
#else
#error "render_frustum_cube_view_fraction: clang naked draft required"
#endif


/* render_frustum_get_projection_bounds (0x185f80) — readable C lift. */
void render_frustum_get_projection_bounds(void *frustum, float *bounds)
{
  float neg_x;
  float neg_y;
  float inv_x;
  float inv_y;
  float one;

  if (!frustum || !*(unsigned char *)((char *)frustum + 0x140)) {
    display_assert((const char *)0x2b12dc, (const char *)0x2b12b4, 0x3a7, 1);
    system_exit(-1);
  }
  if (!bounds) {
    display_assert((const char *)0x26184c, (const char *)0x2b12b4, 0x3a8, 1);
    system_exit(-1);
  }
  one = *(float *)0x2533c8;
  neg_x = -*(float *)((char *)frustum + 0x164);
  neg_y = -*(float *)((char *)frustum + 0x168);
  inv_x = *(float *)0x255e94 / *(float *)((char *)frustum + 0x144);
  inv_y = *(float *)0x255e94 / *(float *)((char *)frustum + 0x158);
  bounds[0] = (neg_x - one) * inv_x;
  bounds[1] = (neg_x + one) * inv_x;
  bounds[2] = (one - neg_y) * inv_y;
  bounds[3] = (neg_y + one) * inv_y;
}

/* render_camera_view_to_screen (0x186050) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void (*const b186050_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b186050_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
char render_camera_view_to_screen(int *param_1 __attribute__((unused)), int *param_2 __attribute__((unused)), void *param_3 __attribute__((unused)), void *param_4 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrender_camera_view_to_screen_1\n\t"
      "pushl $1\n\t"
      "pushl $0x3d2\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_view_to_screen_1:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrender_camera_view_to_screen_2\n\t"
      "pushl $1\n\t"
      "pushl $0x3d3\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_view_to_screen_2:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrender_camera_view_to_screen_3\n\t"
      "pushl $1\n\t"
      "pushl $0x3d4\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_view_to_screen_3:\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrender_camera_view_to_screen_4\n\t"
      "pushl $1\n\t"
      "pushl $0x3d5\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_view_to_screen_4:\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_camera_view_to_screen_6\n\t"
      "flds 0x255e94\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fdivs 0x8(%%ebx)\n\t"
      "movb 0x140(%%eax), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "fstps 0x8(%%ebp)\n\t"
      "jne .Lrender_camera_view_to_screen_5\n\t"
      "pushl $1\n\t"
      "pushl $0x3dc\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1454\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_view_to_screen_5:\n\t"
      "flds 0x144(%%eax)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds 0x164(%%eax)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x158(%%eax)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      "flds 0x168(%%eax)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      "fchs\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "fcomps 0x255e94\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_camera_view_to_screen_6\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_camera_view_to_screen_6\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x255e94\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_camera_view_to_screen_6\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_camera_view_to_screen_6\n\t"
      "movswl 0x2c(%%edi), %%edx\n\t"
      "movswl 0x30(%%edi), %%ecx\n\t"
      "movswl 0x2e(%%edi), %%eax\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movswl 0x32(%%edi), %%ecx\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "subl %%eax, %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "movb $1, %%al\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fadds 0x2533c8\n\t"
      "fmuls 0x253398\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fiaddl 0x8(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "movswl 0x2c(%%edi), %%edx\n\t"
      "flds 0x4(%%esi)\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "fadds 0x2533c8\n\t"
      "popl %%edi\n\t"
      "fmuls 0x253398\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fiaddl 0xc(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_camera_view_to_screen_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b186050_assert), [exitfn] "m"(b186050_exitfn)
      : "memory");
}
#else
#error "render_camera_view_to_screen: clang naked draft required"
#endif


/* render_camera_screen_to_view (0x186230) — readable C lift from XBE leaf. */
void render_camera_screen_to_view(void *camera, void *frustum, float *screen_point,
                                  float *view_vector)
{
  if (!camera) {
    display_assert((const char *)0x266e9c, (const char *)0x2b12b4, 0x3fa, 1);
    system_exit(-1);
  }
  if (!frustum) {
    display_assert((const char *)0x2b14b8, (const char *)0x2b12b4, 0x3fb, 1);
    system_exit(-1);
  }
  if (!screen_point) {
    display_assert((const char *)0x2b14c0, (const char *)0x2b12b4, 0x3fc, 1);
    system_exit(-1);
  }
  if (!view_vector) {
    display_assert((const char *)0x2b14dc, (const char *)0x2b12b4, 0x3fd, 1);
    system_exit(-1);
  }
  if (!*(unsigned char *)((char *)frustum + 0x140)) {
    display_assert((const char *)0x2b1454, (const char *)0x2b12b4, 0x404, 1);
    system_exit(-1);
  }
  view_vector[0] = (screen_point[0] - *(float *)((char *)frustum + 0x164)) /
                   *(float *)((char *)frustum + 0x144);
  view_vector[1] = -((*(float *)((char *)frustum + 0x168) + screen_point[1]) /
                     *(float *)((char *)frustum + 0x158));
  view_vector[2] = -1.0f;
}

/* render_camera_screen_to_world (0x186330) — XBE naked draft (batch 127). */
#if defined(__clang__)
static void (*const b186330_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b186330_exitfn)(int) = system_exit;
static void (*const b186330_c186230)(void *camera, void *frustum, float *screen_point, float *view_vector) = render_camera_screen_to_view;
static void (*const b186330_mscale)(float *, float *, float *) = matrix_scale_transform_vector;

__attribute__((naked, noinline))
void render_camera_screen_to_world(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "pushl %%edi\n\t"
      "jne .Lrender_camera_screen_to_world_1\n\t"
      "pushl $1\n\t"
      "pushl $0x41c\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_1:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "testl %%ebx, %%ebx\n\t"
      "jne .Lrender_camera_screen_to_world_2\n\t"
      "pushl $1\n\t"
      "pushl $0x41d\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_2:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrender_camera_screen_to_world_3\n\t"
      "pushl $1\n\t"
      "pushl $0x41e\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_3:\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrender_camera_screen_to_world_4\n\t"
      "pushl $1\n\t"
      "pushl $0x41f\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_4:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .Lrender_camera_screen_to_world_5\n\t"
      "pushl $1\n\t"
      "pushl $0x420\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14e8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_5:\n\t"
      "movb 0x140(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_camera_screen_to_world_6\n\t"
      "pushl $1\n\t"
      "pushl $0x422\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1454\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_screen_to_world_6:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c186230]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0x44, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, 0x8(%%edi)\n\t"
      "call *%[mscale]\n\t"
      "addl $0x1c, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b186330_assert), [exitfn] "m"(b186330_exitfn), [c186230] "m"(b186330_c186230), [mscale] "m"(b186330_mscale)
      : "memory");
}
#else
#error "render_camera_screen_to_world: clang naked draft required"
#endif


/* render_camera_build_clipped_frustum_bounds (0x186480) — readable C lift (restored pre-naked). */
int render_camera_build_clipped_frustum_bounds(camera_t *camera, float *in_bounds, float *out_bounds)
{
  int eax = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00266e9c, (char *)0x002b12b4, 342, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1864d9 */
  display_assert((char *)0x002819b0, (char *)0x002b12b4, 343, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x186500 */
  display_assert((char *)0x002b1304, (char *)0x002b12b4, 344, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x1865ae */
  /* test (char)eax, 1 -> je 0x1865a8 */
  return 0;

  (void)eax;
  (void)esi;
  (void)edi;
}

/* render_camera_triangle_frontfacing (0x1865e0) — readable C lift. */
char render_camera_triangle_frontfacing(float *p0, float *p1, float *p2, float *p3)
{
  float e0x = p1[0] - p0[0];
  float e0y = p1[1] - p0[1];
  float e0z = p1[2] - p0[2];
  float e1x = p2[0] - p1[0];
  float e1y = p2[1] - p1[1];
  float e1z = p2[2] - p1[2];
  float e2x = p3[0] - p2[0];
  float e2y = p3[1] - p2[1];
  float e2z = p3[2] - p2[2];
  float cx = e1y * e2z - e1z * e2y;
  float cy = e1z * e2x - e1x * e2z;
  float cz = e1x * e2y - e1y * e2x;
  float d = e0x * cx + e0y * cy + e0z * cz;
  return (char)(d > *(float *)0x26a810);
}


/* render_frustum_build_point_flags (0x186690) — readable C lift from XBE leaf.
 * OR together outside-bits for four frustum planes (dist > 0). */
unsigned short render_frustum_build_point_flags(void *frustum, float *point)
{
  unsigned short flags;
  float dist;
  float zero;

  zero = *(float *)0x2533c0;
  flags = 0;

  dist = *(float *)((char *)frustum + 0x7c) * point[1] +
         *(float *)((char *)frustum + 0x80) * point[2] +
         *(float *)((char *)frustum + 0x78) * point[0] -
         *(float *)((char *)frustum + 0x84);
  if (dist > zero)
    flags = 1;

  dist = *(float *)((char *)frustum + 0x8c) * point[1] +
         *(float *)((char *)frustum + 0x90) * point[2] +
         *(float *)((char *)frustum + 0x88) * point[0] -
         *(float *)((char *)frustum + 0x94);
  if (dist > zero)
    flags |= 2;

  dist = *(float *)((char *)frustum + 0x9c) * point[1] +
         *(float *)((char *)frustum + 0xa0) * point[2] +
         point[0] * *(float *)((char *)frustum + 0x98) -
         *(float *)((char *)frustum + 0xa4);
  if (dist > zero)
    flags |= 8;

  dist = *(float *)((char *)frustum + 0xac) * point[1] +
         *(float *)((char *)frustum + 0xb0) * point[2] +
         point[0] * *(float *)((char *)frustum + 0xa8) -
         *(float *)((char *)frustum + 0xb4);
  if (dist > zero)
    flags |= 4;

  return flags;
}

/* render_frustum_triangle_visible (0x186790) — readable C lift. */
char render_frustum_triangle_visible(void *frustum, float *p0, float *p1, float *p2)
{
  unsigned int f0;
  unsigned int f1;
  unsigned int f2;
  unsigned int mask;

  f0 = (unsigned int)(unsigned short)render_frustum_build_point_flags(frustum, p0);
  if (f0 == 0)
    return 1;
  mask = f0 & 0x3f;
  f1 = (unsigned int)(unsigned short)render_frustum_build_point_flags(frustum, p1);
  if (f1 == 0)
    return 1;
  mask &= f1;
  f2 = (unsigned int)(unsigned short)render_frustum_build_point_flags(frustum, p2);
  if (f2 == 0)
    return 1;
  return (char)((mask & f2) == 0);
}


/* render_frustum_cube_visible (0x1867f0) — XBE naked draft (batch 111). */
#if defined(__clang__)


__attribute__((naked, noinline))
short render_frustum_cube_visible(void *param_1 __attribute__((unused)), int param_2 __attribute__((unused)), int param_3 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x60, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "flds 0x12c(%%ecx)\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "fcomps (%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_cube_visible_1\n\t"
      "flds 0x134(%%ecx)\n\t"
      "fcomps 0x8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_cube_visible_1\n\t"
      "flds 0x13c(%%ecx)\n\t"
      "fcomps 0x10(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_cube_visible_1\n\t"
      "flds 0x128(%%ecx)\n\t"
      "fcomps 0x4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_cube_visible_1\n\t"
      "flds 0x130(%%ecx)\n\t"
      "fcomps 0xc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_cube_visible_1\n\t"
      "flds 0x138(%%ecx)\n\t"
      "fcomps 0x14(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_2\n\t"
      ".Lrender_frustum_cube_visible_1:\n\t"
      "xorw %%ax, %%ax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_frustum_cube_visible_2:\n\t"
      "flds (%%edi)\n\t"
      "pushl %%ebx\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fsts -0x30(%%ebp)\n\t"
      "movl $0x3f, 0x8(%%ebp)\n\t"
      "fsts -0x48(%%ebp)\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "flds 0x4(%%edi)\n\t"
      "movl $8, 0xc(%%ebp)\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fsts -0x24(%%ebp)\n\t"
      "fsts -0x3c(%%ebp)\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "fsts -0x50(%%ebp)\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fsts -0x14(%%ebp)\n\t"
      "fsts -0x38(%%ebp)\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fsts -0x34(%%ebp)\n\t"
      "fsts -0x40(%%ebp)\n\t"
      "fsts -0x4c(%%ebp)\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      ".Lrender_frustum_cube_visible_3:\n\t"
      "flds -0x4(%%edx)\n\t"
      "fmuls 0x78(%%ecx)\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x7c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x80(%%ecx)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x84(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_4\n\t"
      "movl $1, %%esi\n\t"
      "jmp .Lrender_frustum_cube_visible_5\n\t"
      ".Lrender_frustum_cube_visible_4:\n\t"
      "xorl %%esi, %%esi\n\t"
      ".Lrender_frustum_cube_visible_5:\n\t"
      "flds 0x88(%%ecx)\n\t"
      "fmuls -0x4(%%edx)\n\t"
      "flds 0x90(%%ecx)\n\t"
      "fmuls 0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x8c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x94(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_6\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_7\n\t"
      ".Lrender_frustum_cube_visible_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_7:\n\t"
      "flds 0xa0(%%ecx)\n\t"
      "orl %%eax, %%esi\n\t"
      "fmuls 0x4(%%edx)\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0x9c(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x98(%%ecx)\n\t"
      "fmuls -0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xa4(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_8\n\t"
      "movl $8, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_9\n\t"
      ".Lrender_frustum_cube_visible_8:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_9:\n\t"
      "flds 0xb0(%%ecx)\n\t"
      "orl %%eax, %%esi\n\t"
      "fmuls 0x4(%%edx)\n\t"
      "flds (%%edx)\n\t"
      "fmuls 0xac(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0xa8(%%ecx)\n\t"
      "fmuls -0x4(%%edx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xb4(%%ecx)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_10\n\t"
      "movl $4, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_11\n\t"
      ".Lrender_frustum_cube_visible_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_11:\n\t"
      "orl %%eax, %%esi\n\t"
      "andl %%esi, 0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "orl %%esi, %%ebx\n\t"
      "addl $0xc, %%edx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jne .Lrender_frustum_cube_visible_3\n\t"
      "testw %%bx, %%bx\n\t"
      "jne .Lrender_frustum_cube_visible_12\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movw $2, %%ax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_frustum_cube_visible_12:\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "je .Lrender_frustum_cube_visible_14\n\t"
      ".Lrender_frustum_cube_visible_13:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "xorw %%ax, %%ax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_frustum_cube_visible_14:\n\t"
      "movb 0x10(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_frustum_cube_visible_28\n\t"
      "movl $0x3f, %%esi\n\t"
      "addl $0xe8, %%ecx\n\t"
      "movl $5, %%ebx\n\t"
      "jmp .Lrender_frustum_cube_visible_15\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_frustum_cube_visible_15:\n\t"
      "flds -0x8(%%ecx)\n\t"
      "fcomps (%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_frustum_cube_visible_16\n\t"
      "movl $1, %%edx\n\t"
      "jmp .Lrender_frustum_cube_visible_17\n\t"
      ".Lrender_frustum_cube_visible_16:\n\t"
      "xorl %%edx, %%edx\n\t"
      ".Lrender_frustum_cube_visible_17:\n\t"
      "flds -0x8(%%ecx)\n\t"
      "fcomps 0x4(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_18\n\t"
      "movl $2, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_19\n\t"
      ".Lrender_frustum_cube_visible_18:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_19:\n\t"
      "flds -0x4(%%ecx)\n\t"
      "orl %%eax, %%edx\n\t"
      "fcomps 0x8(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_frustum_cube_visible_20\n\t"
      "movl $8, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_21\n\t"
      ".Lrender_frustum_cube_visible_20:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_21:\n\t"
      "flds -0x4(%%ecx)\n\t"
      "orl %%eax, %%edx\n\t"
      "fcomps 0xc(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_22\n\t"
      "movl $4, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_23\n\t"
      ".Lrender_frustum_cube_visible_22:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_23:\n\t"
      "flds (%%ecx)\n\t"
      "orl %%eax, %%edx\n\t"
      "fcomps 0x10(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .Lrender_frustum_cube_visible_24\n\t"
      "movl $0x10, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_25\n\t"
      ".Lrender_frustum_cube_visible_24:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_25:\n\t"
      "flds (%%ecx)\n\t"
      "orl %%eax, %%edx\n\t"
      "fcomps 0x14(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lrender_frustum_cube_visible_26\n\t"
      "movl $0x20, %%eax\n\t"
      "jmp .Lrender_frustum_cube_visible_27\n\t"
      ".Lrender_frustum_cube_visible_26:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lrender_frustum_cube_visible_27:\n\t"
      "orl %%edx, %%eax\n\t"
      "andl %%eax, %%esi\n\t"
      "addl $0xc, %%ecx\n\t"
      "decl %%ebx\n\t"
      "jne .Lrender_frustum_cube_visible_15\n\t"
      "testw %%si, %%si\n\t"
      "jne .Lrender_frustum_cube_visible_13\n\t"
      ".Lrender_frustum_cube_visible_28:\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movw $1, %%ax\n\t"
      "popl %%edi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "render_frustum_cube_visible: clang naked draft required"
#endif


/* render_frustum_sphere_visible (0x186ac0) — XBE naked draft (batch 119). */
#if defined(__clang__)
static float (*const b186ac0_c99500)(float *plane, float *point) = plane3d_distance_to_point;

__attribute__((naked, noinline))
int render_frustum_sphere_visible(void *frustum __attribute__((unused)), float *center __attribute__((unused)), float radius __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "flds (%%esi)\n\t"
      "pushl %%edi\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "fcomps 0x12c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "fcomps 0x134(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x10(%%ebp)\n\t"
      "fcomps 0x13c(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadds (%%esi)\n\t"
      "fcomps 0x128(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_sphere_visible_1\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadds 0x4(%%esi)\n\t"
      "fcomps 0x130(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_sphere_visible_1\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadds 0x8(%%esi)\n\t"
      "fcomps 0x138(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lrender_frustum_sphere_visible_1\n\t"
      "leal 0x78(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c99500]\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "leal 0x88(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99500]\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "leal 0x98(%%edi), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[c99500]\n\t"
      "fsts -0x4(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "leal 0xa8(%%edi), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c99500]\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "leal 0xb8(%%edi), %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[c99500]\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lrender_frustum_sphere_visible_1\n\t"
      "pushl %%esi\n\t"
      "addl $0xc8, %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[c99500]\n\t"
      "fsts -0xc(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_frustum_sphere_visible_2\n\t"
      ".Lrender_frustum_sphere_visible_1:\n\t"
      "popl %%edi\n\t"
      "xorw %%ax, %%ax\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_frustum_sphere_visible_2:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fchs\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_frustum_sphere_visible_3\n\t"
      "flds 0x8(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_frustum_sphere_visible_3\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_frustum_sphere_visible_3\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_frustum_sphere_visible_3\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "movw $2, %%ax\n\t"
      "jnp .Lrender_frustum_sphere_visible_4\n\t"
      ".Lrender_frustum_sphere_visible_3:\n\t"
      "movw $1, %%ax\n\t"
      ".Lrender_frustum_sphere_visible_4:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c99500] "m"(b186ac0_c99500)
      : "memory");
}
#else
#error "render_frustum_sphere_visible: clang naked draft required"
#endif


/* render_camera_world_to_screen (0x186c70) — readable C lift. */
char render_camera_world_to_screen(void *cam1, void *cam2, void *world_pos,
                                  float *screen_out)
{
  float view[3];

  if (!cam1) {
    display_assert((const char *)0x266e9c, (const char *)0x2b12b4, 0x3c1, 1);
    system_exit(-1);
  }
  if (!cam2) {
    display_assert((const char *)0x2b14b8, (const char *)0x2b12b4, 0x3c2, 1);
    system_exit(-1);
  }
  if (!world_pos) {
    display_assert((const char *)0x2b14f8, (const char *)0x2b12b4, 0x3c3, 1);
    system_exit(-1);
  }
  if (!screen_out) {
    display_assert((const char *)0x2b14c0, (const char *)0x2b12b4, 0x3c4, 1);
    system_exit(-1);
  }
  matrix_transform_point((float *)((char *)cam2 + 0x10), (float *)world_pos,
                         view);
  return render_camera_view_to_screen((int *)cam1, (int *)cam2, view,
                                     screen_out);
}

/* render_camera_debug_frustum (0x186d40) — XBE naked draft (batch 121). */
#if defined(__clang__)
static void (*const b186d40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b186d40_exitfn)(int) = system_exit;
static void (*const b186d40_xfrmpt)(float *, float *, float *) = matrix_transform_point;
static void (*const b186d40_c189270)(char flag, float *point_a, float *point_b, void *color) = FUN_00189270;

__attribute__((naked, noinline))
void render_camera_debug_frustum(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x88, %%esp\n\t"
      "movb 0x4d0e1a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lrender_camera_debug_frustum_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrender_camera_debug_frustum_1\n\t"
      "pushl $1\n\t"
      "pushl $0x43b\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x266e9c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_debug_frustum_1:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "testl %%esi, %%esi\n\t"
      "jne .Lrender_camera_debug_frustum_2\n\t"
      "pushl $1\n\t"
      "pushl $0x43c\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b14b8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_debug_frustum_2:\n\t"
      "addl $0x44, %%esi\n\t"
      "leal -0x88(%%ebp), %%eax\n\t"
      "movl %%esi, -0x1c(%%ebp)\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "movl $3, -0xc(%%ebp)\n\t"
      "jmp .Lrender_camera_debug_frustum_3\n\t"
      "leal (%%esp), %%esp\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_camera_debug_frustum_3:\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "movl $0xffffffff, -0x10(%%ebp)\n\t"
      "movl $3, %%ebx\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "jmp .Lrender_camera_debug_frustum_4\n\t"
      "leal (%%esp), %%esp\n\t"
      "movl %%edi, %%edi\n\t"
      ".Lrender_camera_debug_frustum_4:\n\t"
      "flds 0x28(%%edi)\n\t"
      "movswl 0x36(%%edi), %%edx\n\t"
      "fmuls 0x253398\n\t"
      "movswl 0x3a(%%edi), %%ecx\n\t"
      "movswl 0x38(%%edi), %%eax\n\t"
      "fptan\n\t"
      "subl %%edx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movswl 0x34(%%edi), %%ecx\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl $0xbf800000, 0x8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "fildl -0x14(%%ebp)\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "fimull -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fidivl -0x14(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps 0x4(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[xfrmpt]\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%edx\n\t"
      "addl $0x24, %%esi\n\t"
      "decl %%ebx\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "jne .Lrender_camera_debug_frustum_4\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "incl %%edx\n\t"
      "addl $0xc, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrender_camera_debug_frustum_3\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "leal -0x70(%%ebp), %%ebx\n\t"
      "movl $3, -0x8(%%ebp)\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lrender_camera_debug_frustum_5:\n\t"
      "leal -0x88(%%ebp), %%edi\n\t"
      "leal -0x88(%%ebp), %%esi\n\t"
      "movl $3, -0xc(%%ebp)\n\t"
      ".Lrender_camera_debug_frustum_6:\n\t"
      "movl 0x2ee6d0, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl 0x2ee6d0, %%edx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl $1\n\t"
      "call *%[c189270]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x20, %%esp\n\t"
      "addl $0x24, %%esi\n\t"
      "addl $0xc, %%edi\n\t"
      "decl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jne .Lrender_camera_debug_frustum_6\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%ecx\n\t"
      "addl $0x24, %%ebx\n\t"
      "decl %%eax\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "jne .Lrender_camera_debug_frustum_5\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".Lrender_camera_debug_frustum_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b186d40_assert), [exitfn] "m"(b186d40_exitfn), [xfrmpt] "m"(b186d40_xfrmpt), [c189270] "m"(b186d40_c189270)
      : "memory");
}
#else
#error "render_camera_debug_frustum: clang naked draft required"
#endif


/* render_camera_mirror (0x186ef0) — XBE naked draft (batch 108). */
#if defined(__clang__)
static float (*const b186ef0_norm)(float *) = normalize3d;
static int (*const b186ef0_c10a480)(int p) = FUN_0010a480;
static void (*const b186ef0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b186ef0_exitfn)(int) = system_exit;
static void (*const b186ef0_c10c8e0)(float *v, float *n, float *out) = FUN_0010c8e0;
static int (*const b186ef0_c84a10)(float *vector) = real_vector3d_valid;

__attribute__((naked, noinline))
void render_camera_mirror(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x38, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%edx, -0x28(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%edx\n\t"
      "movl 0xc(%%ecx), %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%edi\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl $0x15, %%ecx\n\t"
      "movl %%ebx, %%esi\n\t"
      "movl %%edx, %%edi\n\t"
      "rep movsl\n\t"
      "flds 0x10(%%eax)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lrender_camera_mirror_6\n\t"
      "flds -0x20(%%ebp)\n\t"
      "leal 0xc(%%ebx), %%esi\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fabs\n\t"
      "fcompl 0x2b1580\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_camera_mirror_5\n\t"
      "flds -0x28(%%ebp)\n\t"
      "leal -0xc(%%ebp), %%edx\n\t"
      "fmuls (%%ebx)\n\t"
      "pushl %%edx\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fchs\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds (%%ebx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x2b1578\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x2b1578\n\t"
      "fadds -0x24(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x2b1578\n\t"
      "fadds -0x20(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "call *%[norm]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fmuls -0x10(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ecx, -0x34(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "movl %%edx, -0x30(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "call *%[c10a480]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_camera_mirror_1\n\t"
      "pushl $1\n\t"
      "pushl $0xcf\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1554\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_mirror_1:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      ".Lrender_camera_mirror_2:\n\t"
      "leal 0xc(%%edx), %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x38(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "call *%[c10c8e0]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "leal 0x18(%%esi), %%edi\n\t"
      "pushl %%edi\n\t"
      "leal -0x38(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal 0x18(%%ebx), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c10c8e0]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c84a10]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_camera_mirror_3\n\t"
      "pushl $1\n\t"
      "pushl $0xd9\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b152c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_mirror_3:\n\t"
      "pushl %%edi\n\t"
      "call *%[c84a10]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lrender_camera_mirror_4\n\t"
      "pushl $1\n\t"
      "pushl $0xda\n\t"
      "pushl $0x2b12b4\n\t"
      "pushl $0x2b1508\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_camera_mirror_4:\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls (%%ebx)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmuls 0x4(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "fmuls 0x25eeac\n\t"
      "flds -0x38(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds (%%ebx)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x30(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "movb 0x24(%%ebx), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstp %%st(0)\n\t"
      "sete %%dl\n\t"
      "movb %%dl, 0x24(%%esi)\n\t"
      "flds (%%edi)\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "fchs\n\t"
      "fstps (%%edi)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x8(%%edi)\n\t"
      "jmp .Lrender_camera_mirror_9\n\t"
      ".Lrender_camera_mirror_5:\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl -0x20(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "jmp .Lrender_camera_mirror_2\n\t"
      ".Lrender_camera_mirror_6:\n\t"
      "flds 0x14(%%ebx)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds 0x10(%%ebx)\n\t"
      "flds 0xc(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstp %%st(3)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fsts 0x8(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x10(%%ecx)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lrender_camera_mirror_7\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls 0xc(%%ebx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fmuls 0x14(%%ecx)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fsubrs 0x2533c8\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls 0x8(%%ebp)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fchs\n\t"
      "jmp .Lrender_camera_mirror_8\n\t"
      ".Lrender_camera_mirror_7:\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x2533c0\n\t"
      ".Lrender_camera_mirror_8:\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds (%%ebx)\n\t"
      "fstps (%%edx)\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps 0x4(%%edx)\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps 0x8(%%edx)\n\t"
      "fstp %%st(0)\n\t"
      ".Lrender_camera_mirror_9:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "movl $0, 0x3c(%%edx)\n\t"
      "addl $0x44, %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0xc(%%edx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(b186ef0_norm), [c10a480] "m"(b186ef0_c10a480), [assert] "m"(b186ef0_assert), [exitfn] "m"(b186ef0_exitfn), [c10c8e0] "m"(b186ef0_c10c8e0), [c84a10] "m"(b186ef0_c84a10)
      : "memory");
}
#else
#error "render_camera_mirror: clang naked draft required"
#endif


/* FUN_00187f80 (0x187f80) — readable C lift.
 * Camera facing attenuator; returns float in ST0. */
float FUN_00187f80(void *flags, short mode, float *point, float *forward)
{
  float dx;
  float dy;
  float dz;
  float dot;
  float len_sq;
  float len;
  float t;

  if (mode == 0)
    return *(float *)0x2533c8;
  dx = *(float *)0x506550 - point[0];
  dy = *(float *)0x506554 - point[1];
  dz = *(float *)0x506558 - point[2];
  dot = dz * forward[2] + dy * forward[1] + dx * forward[0];
  len_sq = dz * dz + dy * dy + dx * dx;
  if (len_sq == 0.0f)
    t = 0.0f;
  else {
    __asm__ volatile ("fsqrt" : "=t"(len) : "0"(len_sq));
    t = dot / len;
    if (!(t >= 0.0f))
      t = -t;
  }
  if ((*(unsigned char *)flags & 0x40) != 0)
    t = transition_function_evaluate(2, t);
  if (mode == 2)
    t = *(float *)0x2533c8 - t;
  return t;
}

/* render_contrail (0x188010) — XBE naked draft (batch 104). */
#if defined(__clang__)
static void * (*const b188010_c77040)(int tag_index, short sequence_index, short frame_index) = FUN_00077040;
static void *(*const b188010_xtex)(void *, bool, bool) = xbox_texture_cache_get_hardware_format;
static int (*const b188010_c17c970)(int mode) = rasterizer_widget_submit;
static int (*const b188010_rzbuf)(int, int) = rasterizer_widget_set_zbuffer_enable;
static void * (*const b188010_c17c980)(int handle) = rasterizer_widget_begin;
static int (*const b188010_rspr)(int) = rasterizer_widget_draw_sprite3d;
static void (*const b188010_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b188010_exitfn)(int) = system_exit;
static void *(*const b188010_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b188010_elem)(void *, int, int) = tag_block_get_element;
static void *(*const b188010_get)(int, int) = object_get_and_verify_type;
static void *(*const b188010_tag)(int, int) = tag_get;
static float (*const b188010_mag)(float *) = magnitude3d;
static float (*const b188010_norm)(float *) = normalize3d;
static void (*const b188010_c187f80)(void) = FUN_00187f80;
static unsigned int (*const b188010_d1c90)(float *) = FUN_000d1c90;
static void (*const b188010_c17c990)(int handle) = rasterizer_widget_set_texture;
static void (*const b188010_rend)(int) = rasterizer_widget_end;
static void (*const b188010_r7cf60)(unsigned int, unsigned int, int, int, unsigned int, int, float *, unsigned int) = FUN_0017cf60;
static void (*const b188010_c17c9a0)(int handle) = rasterizer_widget_set_tint_factor;
static void (*const b188010_rocc)(int) = rasterizer_widget_submit_occlusion_test;
static const char * (*const b188010_c1ba1f0)(int tag_index) = tag_get_name;
static void (*const b188010_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;

__attribute__((naked, noinline))
void render_contrail(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x9c, %%esp\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x16(%%esi), %%ax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x14(%%esi), %%cx\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl 0x3c(%%edx), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c77040]\n\t"
      "pushl $1\n\t"
      "pushl $0\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0x84(%%ebp)\n\t"
      "movw $0xf, 0x325652\n\t"
      "call *%[xtex]\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_contrail_29\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movw 0x2c(%%esi,%%eax,2), %%bx\n\t"
      "decw %%bx\n\t"
      "leal (%%ebx,%%ebx,1), %%eax\n\t"
      "leal 0x2(%%eax), %%edi\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl %%eax\n\t"
      "movl %%ebx, -0x8c(%%ebp)\n\t"
      "movl %%eax, -0x74(%%ebp)\n\t"
      "call *%[c17c970]\n\t"
      "movl %%eax, %%esi\n\t"
      "movswl %%di, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $6\n\t"
      "movl %%esi, -0x80(%%ebp)\n\t"
      "movl %%eax, -0x78(%%ebp)\n\t"
      "call *%[rzbuf]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edi, -0x88(%%ebp)\n\t"
      "je .Lrender_contrail_29\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .Lrender_contrail_29\n\t"
      "pushl %%esi\n\t"
      "call *%[c17c980]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%esi, -0x6c(%%ebp)\n\t"
      "call *%[rspr]\n\t"
      "movl 0x31fc1c, %%ecx\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, -0x30(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "leal 0x84(%%ecx), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x2c(%%eax)\n\t"
      "movl %%eax, -0x68(%%ebp)\n\t"
      "setne -0x1(%%ebp)\n\t"
      "testl %%esi, %%esi\n\t"
      "je .Lrender_contrail_1\n\t"
      "testl %%edi, %%edi\n\t"
      "jne .Lrender_contrail_2\n\t"
      ".Lrender_contrail_1:\n\t"
      "pushl $1\n\t"
      "pushl $0x88\n\t"
      "pushl $0x2b1740\n\t"
      "pushl $0x2b1728\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lrender_contrail_2:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "movl 0x18(%%edx), %%eax\n\t"
      "movl %%eax, -0x3c(%%ebp)\n\t"
      "movw 0x2(%%ecx), %%ax\n\t"
      "testb $0x40, %%al\n\t"
      "je .Lrender_contrail_3\n\t"
      "fmuls 0x10(%%edx)\n\t"
      ".Lrender_contrail_3:\n\t"
      "testb %%al, %%al\n\t"
      "fchs\n\t"
      "movl 0x1c(%%edx), %%edx\n\t"
      "fstps -0x7c(%%ebp)\n\t"
      "flds 0x20(%%ecx)\n\t"
      "movl %%edx, -0x64(%%ebp)\n\t"
      "jns .Lrender_contrail_4\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "fmuls 0x10(%%eax)\n\t"
      ".Lrender_contrail_4:\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "fadds -0x64(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x34(%%edx,%%eax,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "fstps -0x70(%%ebp)\n\t"
      "movl $0, -0x40(%%ebp)\n\t"
      "je .Lrender_contrail_24\n\t"
      "nop\n\t"
      ".Lrender_contrail_5:\n\t"
      "pushl %%eax\n\t"
      "movl 0x5aa8bc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movsbl 0x3(%%esi), %%ecx\n\t"
      "pushl $0x68\n\t"
      "pushl %%ecx\n\t"
      "addl $0x138, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0x64(%%eax), %%ecx\n\t"
      "flds 0x2533c8\n\t"
      "addl $0x14, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "je .Lrender_contrail_6\n\t"
      "fstp %%st(0)\n\t"
      "flds 0xc(%%esi)\n\t"
      ".Lrender_contrail_6:\n\t"
      "testb $0x10, %%cl\n\t"
      "flds 0x40(%%eax)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      "je .Lrender_contrail_7\n\t"
      "fmuls 0xc(%%esi)\n\t"
      "fsts -0x1c(%%ebp)\n\t"
      ".Lrender_contrail_7:\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x54(%%eax)\n\t"
      "fsubs 0x44(%%eax)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x44(%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x58(%%eax)\n\t"
      "fsubs 0x48(%%eax)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x48(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x5c(%%eax)\n\t"
      "fsubs 0x4c(%%eax)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x4c(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0x60(%%eax)\n\t"
      "fsubs 0x50(%%eax)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds 0x50(%%eax)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "movb 0x2(%%esi), %%al\n\t"
      "testb $2, %%al\n\t"
      "fstp %%st(0)\n\t"
      "je .Lrender_contrail_10\n\t"
      "movsbl 0x3(%%esi), %%edx\n\t"
      "pushl $0x68\n\t"
      "incl %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0x64(%%eax), %%ecx\n\t"
      "flds 0x4(%%esi)\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $0x20, %%cl\n\t"
      "movl $0x3f800000, -0x20(%%ebp)\n\t"
      "je .Lrender_contrail_8\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl %%edx, -0x20(%%ebp)\n\t"
      ".Lrender_contrail_8:\n\t"
      "testb $0x10, %%cl\n\t"
      "flds 0x40(%%eax)\n\t"
      "je .Lrender_contrail_9\n\t"
      "fmuls 0xc(%%esi)\n\t"
      ".Lrender_contrail_9:\n\t"
      "flds 0x54(%%eax)\n\t"
      "fsubs 0x44(%%eax)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fadds 0x44(%%eax)\n\t"
      "flds 0x58(%%eax)\n\t"
      "fsubs 0x48(%%eax)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fadds 0x48(%%eax)\n\t"
      "fstps -0x98(%%ebp)\n\t"
      "flds 0x5c(%%eax)\n\t"
      "fsubs 0x4c(%%eax)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fadds 0x4c(%%eax)\n\t"
      "fstps -0x94(%%ebp)\n\t"
      "flds 0x60(%%eax)\n\t"
      "fsubs 0x50(%%eax)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fadds 0x50(%%eax)\n\t"
      "fstps -0x90(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fadds -0x1c(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fsubs -0x18(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x18(%%ebp)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds -0x98(%%ebp)\n\t"
      "fsubs -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x14(%%ebp)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x94(%%ebp)\n\t"
      "fsubs -0x10(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0x90(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      ".Lrender_contrail_10:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lrender_contrail_11\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x6f626a65\n\t"
      "call *%[tag]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl 0xc(%%edx), %%ecx\n\t"
      "pushl $0x48\n\t"
      "pushl %%ecx\n\t"
      "addl $0x140, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movw 0x34(%%eax), %%ax\n\t"
      "addl $0x1c, %%esp\n\t"
      "decw %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lrender_contrail_11\n\t"
      "flds -0x14(%%ebp)\n\t"
      "movswl %%ax, %%eax\n\t"
      "addl $0x1e, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal (%%ebx,%%edx,4), %%eax\n\t"
      "fmuls (%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".Lrender_contrail_11:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl -0x3c(%%ebp), %%eax\n\t"
      "fmuls 0x253398\n\t"
      "movl -0x70(%%ebp), %%ecx\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "movl %%ecx, 0x10(%%edi)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "movl %%eax, %%edx\n\t"
      "movl -0x64(%%ebp), %%eax\n\t"
      "movl %%edx, 0x24(%%edi)\n\t"
      "movl %%eax, 0x28(%%edi)\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fadds 0x1c(%%esi)\n\t"
      "movswl 0x18(%%ecx), %%eax\n\t"
      "cmpl $4, %%eax\n\t"
      "leal 0x1c(%%esi), %%ebx\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fadds 0x24(%%esi)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "ja .Lrender_contrail_30\n\t"
      "jmp *.Lrender_contrail_jt(,%%eax,4)\n\t"
      ".Lrender_contrail_12:\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl %%edx, (%%edi)\n\t"
      "movl 0x20(%%esi), %%eax\n\t"
      "movl %%eax, 0x4(%%edi)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps 0x8(%%edi)\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl %%ecx, 0x18(%%edi)\n\t"
      "movl 0x20(%%esi), %%edx\n\t"
      "movl %%edx, 0x1c(%%edi)\n\t"
      "fadds 0x24(%%esi)\n\t"
      "fstps 0x20(%%edi)\n\t"
      "je .Lrender_contrail_21\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_contrail_13\n\t"
      "flds 0x20(%%eax)\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "fsubs 0x20(%%esi)\n\t"
      "movl $0, -0x44(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "fsubs 0x1c(%%eax)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "jmp .Lrender_contrail_20\n\t"
      ".Lrender_contrail_13:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x5aa8bc, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "flds 0x20(%%esi)\n\t"
      "fsubs 0x20(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "movl $0, -0x44(%%ebp)\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "flds 0x1c(%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "jmp .Lrender_contrail_20\n\t"
      ".Lrender_contrail_14:\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_contrail_15\n\t"
      "flds 0x20(%%eax)\n\t"
      "fsubs 0x20(%%esi)\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      "fsubs 0x1c(%%eax)\n\t"
      "jmp .Lrender_contrail_16\n\t"
      ".Lrender_contrail_15:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x5aa8bc, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "flds 0x20(%%esi)\n\t"
      "fsubs 0x20(%%eax)\n\t"
      "addl $8, %%esp\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "flds 0x1c(%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      ".Lrender_contrail_16:\n\t"
      "leal -0x60(%%ebp), %%edx\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "call *%[mag]\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x60(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps (%%edi)\n\t"
      "flds -0x5c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds 0x20(%%esi)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps 0x4(%%edi)\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fadds (%%ebx)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "fstps 0x18(%%edi)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps 0x1c(%%edi)\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "movl %%ecx, 0x20(%%edi)\n\t"
      "je .Lrender_contrail_21\n\t"
      "movl 0x31fc44, %%edx\n\t"
      "movl (%%edx), %%eax\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "movl %%eax, -0x4c(%%ebp)\n\t"
      "movl %%ecx, -0x48(%%ebp)\n\t"
      "movl %%edx, -0x44(%%ebp)\n\t"
      "jmp .Lrender_contrail_21\n\t"
      ".Lrender_contrail_17:\n\t"
      "movl -0x40(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lrender_contrail_18\n\t"
      "flds 0x506550\n\t"
      "fsubs 0x1c(%%eax)\n\t"
      "flds 0x506554\n\t"
      "fsubs 0x20(%%eax)\n\t"
      "flds 0x506558\n\t"
      "fsubs 0x24(%%eax)\n\t"
      "flds (%%ebx)\n\t"
      "fsubs 0x1c(%%eax)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x20(%%esi)\n\t"
      "fsubs 0x20(%%eax)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fsubs 0x24(%%eax)\n\t"
      "jmp .Lrender_contrail_19\n\t"
      ".Lrender_contrail_18:\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "movl 0x5aa8bc, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "flds 0x506550\n\t"
      "fsubs (%%ebx)\n\t"
      "addl $8, %%esp\n\t"
      "flds 0x506554\n\t"
      "fsubs 0x20(%%esi)\n\t"
      "flds 0x506558\n\t"
      "fsubs 0x24(%%esi)\n\t"
      "flds 0x1c(%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x20(%%eax)\n\t"
      "fsubs 0x20(%%esi)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds 0x24(%%eax)\n\t"
      "fsubs 0x24(%%esi)\n\t"
      ".Lrender_contrail_19:\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "leal -0x58(%%ebp), %%edx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "pushl %%edx\n\t"
      ".byte 0xd8, 0xca\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x24(%%ebp)\n\t"
      ".byte 0xd8, 0xcc\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x28(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "flds -0x2c(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "flds -0x58(%%ebp)\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds (%%ebx)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps (%%edi)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "flds 0x20(%%esi)\n\t"
      ".byte 0xd8, 0xe1\n\t"
      "fstps 0x4(%%edi)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x24(%%esi)\n\t"
      "fsubs -0x1c(%%ebp)\n\t"
      "fstps 0x8(%%edi)\n\t"
      "fxch %%st(1)\n\t"
      "fadds (%%ebx)\n\t"
      "fstps 0x18(%%edi)\n\t"
      "fadds 0x20(%%esi)\n\t"
      "fstps 0x1c(%%edi)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fadds 0x24(%%esi)\n\t"
      "fstps 0x20(%%edi)\n\t"
      "je .Lrender_contrail_21\n\t"
      "flds -0x50(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      "flds -0x50(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "flds -0x54(%%ebp)\n\t"
      "fmuls -0x2c(%%ebp)\n\t"
      "flds -0x58(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x44(%%ebp)\n\t"
      ".Lrender_contrail_20:\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      ".Lrender_contrail_21:\n\t"
      "movl -0x68(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2c(%%edx), %%ax\n\t"
      "leal -0x4c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c187f80]\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "addl $0x10, %%esp\n\t"
      "fsts -0x18(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lrender_contrail_22\n\t"
      "movl $0, -0x18(%%ebp)\n\t"
      "jmp .Lrender_contrail_23\n\t"
      ".Lrender_contrail_22:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lrender_contrail_23\n\t"
      "movl $0x3f800000, -0x18(%%ebp)\n\t"
      ".Lrender_contrail_23:\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[d1c90]\n\t"
      "flds -0x7c(%%ebp)\n\t"
      "fadds -0x3c(%%ebp)\n\t"
      "movl %%eax, 0x2c(%%edi)\n\t"
      "movl %%eax, 0x14(%%edi)\n\t"
      "movl 0x34(%%esi), %%eax\n\t"
      "addl $4, %%esp\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "addl $0x30, %%edi\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%esi, -0x40(%%ebp)\n\t"
      "jne .Lrender_contrail_5\n\t"
      "movl -0x8c(%%ebp), %%ebx\n\t"
      "movl -0x6c(%%ebp), %%esi\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      ".Lrender_contrail_24:\n\t"
      "movl -0x78(%%ebp), %%eax\n\t"
      "movb (%%ecx), %%dl\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "shll $3, %%eax\n\t"
      "subl %%eax, %%edi\n\t"
      "testb $1, %%dl\n\t"
      "jne .Lrender_contrail_25\n\t"
      "movb $0, 0x17(%%edi)\n\t"
      "movb $0, 0x2f(%%edi)\n\t"
      ".Lrender_contrail_25:\n\t"
      "testb $2, (%%ecx)\n\t"
      "jne .Lrender_contrail_26\n\t"
      "movb $0, -0x1(%%eax,%%edi,1)\n\t"
      "movb $0, -0x19(%%eax,%%edi,1)\n\t"
      ".Lrender_contrail_26:\n\t"
      "testw %%bx, %%bx\n\t"
      "jle .Lrender_contrail_28\n\t"
      "movl $1, %%eax\n\t"
      "movzwl %%bx, %%edi\n\t"
      ".Lrender_contrail_27:\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "leal 0x1(%%eax), %%ecx\n\t"
      "movw %%cx, 0x4(%%esi)\n\t"
      "leal -0x1(%%eax), %%edx\n\t"
      "movw %%dx, (%%esi)\n\t"
      "addl $6, %%esi\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "addl $2, %%eax\n\t"
      "movw %%cx, (%%esi)\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "addl $6, %%esi\n\t"
      "decl %%edi\n\t"
      "jne .Lrender_contrail_27\n\t"
      ".Lrender_contrail_28:\n\t"
      "movswl 0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movswl 0x2c(%%ecx,%%eax,2), %%edx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "movl -0x80(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fdivrs 0x2533c8\n\t"
      "flds -0x38(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "fmuls -0x30(%%ebp)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "call *%[c17c990]\n\t"
      "movl -0x88(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "call *%[rend]\n\t"
      "movl -0x74(%%ebp), %%ecx\n\t"
      "movl -0x84(%%ebp), %%edx\n\t"
      "pushl $0\n\t"
      "leal -0x38(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl -0x68(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl $0\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[r7cf60]\n\t"
      "pushl %%esi\n\t"
      "call *%[c17c9a0]\n\t"
      "pushl %%edi\n\t"
      "call *%[rocc]\n\t"
      "addl $0x30, %%esp\n\t"
      ".Lrender_contrail_29:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movw $0, 0x325652\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lrender_contrail_30:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c1ba1f0]\n\t"
      "pushl %%eax\n\t"
      "pushl $0x2b16f8\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".section .rdata,\"dr\"\n\t"
      ".Lrender_contrail_jt:\n\t"
      ".long .Lrender_contrail_12\n\t"
      ".long .Lrender_contrail_14\n\t"
      ".long .Lrender_contrail_14\n\t"
      ".long .Lrender_contrail_30\n\t"
      ".long .Lrender_contrail_17\n\t"
      ".text\n\t"
      :
      : [c77040] "m"(b188010_c77040), [xtex] "m"(b188010_xtex), [c17c970] "m"(b188010_c17c970), [rzbuf] "m"(b188010_rzbuf), [c17c980] "m"(b188010_c17c980), [rspr] "m"(b188010_rspr), [assert] "m"(b188010_assert), [exitfn] "m"(b188010_exitfn), [dget] "m"(b188010_dget), [elem] "m"(b188010_elem), [get] "m"(b188010_get), [tag] "m"(b188010_tag), [mag] "m"(b188010_mag), [norm] "m"(b188010_norm), [c187f80] "m"(b188010_c187f80), [d1c90] "m"(b188010_d1c90), [c17c990] "m"(b188010_c17c990), [rend] "m"(b188010_rend), [r7cf60] "m"(b188010_r7cf60), [c17c9a0] "m"(b188010_c17c9a0), [rocc] "m"(b188010_rocc), [c1ba1f0] "m"(b188010_c1ba1f0), [c8f390] "m"(b188010_c8f390)
      : "memory");
}
#else
#error "render_contrail: clang naked draft required"
#endif


/* FUN_001887b0 (0x1887b0) — XBE naked draft (batch 134). */
#if defined(__clang__)
static int (*const b1887b0_c1198f0)(data_t *data, int prev_index) = data_next_index;
static void *(*const b1887b0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void *(*const b1887b0_tag)(int, int) = tag_get;
static void (*const b1887b0_c188010)(void) = render_contrail;

__attribute__((naked, noinline))
void FUN_001887b0(int a0)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movb 0x32574a, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_001887b0_5\n\t"
      "movl 0x5aa8c0, %%eax\n\t"
      "pushl $-1\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .LFUN_001887b0_5\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_001887b0_2\n\t"
      ".LFUN_001887b0_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      ".LFUN_001887b0_2:\n\t"
      "movl 0x5aa8c0, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x636f6e74\n\t"
      "call *%[tag]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "xorl %%esi, %%esi\n\t"
      "leal 0x2c(%%edi), %%ebx\n\t"
      "nop\n\t"
      ".LFUN_001887b0_3:\n\t"
      "movb 0x18(%%eax), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "testl %%edx, %%ecx\n\t"
      "je .LFUN_001887b0_4\n\t"
      "cmpw $2, (%%ebx)\n\t"
      "jl .LFUN_001887b0_4\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "call *%[c188010]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_001887b0_4:\n\t"
      "incl %%esi\n\t"
      "addl $2, %%ebx\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_001887b0_3\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl 0x5aa8c0, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c1198f0]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jne .LFUN_001887b0_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_001887b0_5:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1198f0] "m"(b1887b0_c1198f0), [dget] "m"(b1887b0_dget), [tag] "m"(b1887b0_tag), [c188010] "m"(b1887b0_c188010)
      : "memory");
}
#else
#error "FUN_001887b0: clang naked draft required"
#endif


void FUN_00188880(void) {
  FUN_001887b0(-0xd);
}


