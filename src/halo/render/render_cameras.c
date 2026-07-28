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

/* render_camera_view_to_screen (0x186050) — readable C lift (restored pre-naked). */
char render_camera_view_to_screen(int *param_1, int *param_2, void *param_3, void *param_4)
{
  int eax = 0;
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test edi, edi -> jne 0x18607d */
  display_assert((char *)0x00266e9c, (char *)0x002b12b4, 978, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1860a4 */
  display_assert((char *)0x002b14b8, (char *)0x002b12b4, 979, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x1860cb */
  display_assert((char *)0x002b14d0, (char *)0x002b12b4, 980, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x1860f2 */
  display_assert((char *)0x002b14c0, (char *)0x002b12b4, 981, 0);
  system_exit(0);
  display_assert((char *)0x002b1454, (char *)0x002b12b4, 988, 0);
  system_exit(0);
  /* test (char)eax, 1 -> jne 0x18621d */
  /* test (char)eax, 1 -> jne 0x18621d */
  return 0;

  (void)eax;
  (void)ebx;
  (void)esi;
  (void)edi;
}


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

/* render_camera_screen_to_world (0x186330) — readable C lift (restored pre-naked). */
void render_camera_screen_to_world(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00266e9c, (char *)0x002b12b4, 1052, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x186387 */
  display_assert((char *)0x002b14b8, (char *)0x002b12b4, 1053, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1863ae */
  display_assert((char *)0x002b14c0, (char *)0x002b12b4, 1054, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x1863d5 */
  display_assert((char *)0x002b14f8, (char *)0x002b12b4, 1055, 0);
  system_exit(0);
  /* test eax, eax -> jne 0x1863fc */
  display_assert((char *)0x002b14e8, (char *)0x002b12b4, 1056, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> jne 0x186426 */
  display_assert((char *)0x002b1454, (char *)0x002b12b4, 1058, 0);
  system_exit(0);
  render_camera_screen_to_view((void *)(uintptr_t)esi, (void *)(uintptr_t)ebx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix_scale_transform_vector((float *)(uintptr_t)ebx, (float *)0, (float *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


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

/* render_camera_debug_frustum (0x186d40) — readable C lift (restored pre-naked). */
void render_camera_debug_frustum(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  /* test (char)eax, (char)eax -> je 0x186ee0 */
  /* test edi, edi -> jne 0x186d80 */
  display_assert((char *)0x00266e9c, (char *)0x002b12b4, 1083, 0);
  system_exit(0);
  /* test esi, esi -> jne 0x186da7 */
  display_assert((char *)0x002b14b8, (char *)0x002b12b4, 1084, 0);
  system_exit(0);
  matrix_transform_point((float *)0, (float *)0, (float *)0);
  FUN_00189270(0, (float *)(uintptr_t)esi, (float *)(uintptr_t)ebx, (void *)(uintptr_t)ecx);
  FUN_00189270(0, (float *)(uintptr_t)edi, (float *)(uintptr_t)eax, (void *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* render_camera_mirror (0x186ef0) — readable C lift (restored pre-naked). */
void render_camera_mirror(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  normalize3d((float *)0);
  FUN_0010a480(0);
  /* test (char)eax, (char)eax -> jne 0x187033 */
  display_assert((char *)0x002b1554, (char *)0x002b12b4, 207, 0);
  system_exit(0);
  FUN_0010c8e0((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  FUN_0010c8e0((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)edi);
  real_vector3d_valid((float *)(uintptr_t)ecx);
  /* test (char)eax, (char)eax -> jne 0x18708b */
  display_assert((char *)0x002b152c, (char *)0x002b12b4, 217, 0);
  system_exit(0);
  real_vector3d_valid((float *)(uintptr_t)edi);
  /* test (char)eax, (char)eax -> jne 0x1870b8 */
  display_assert((char *)0x002b1508, (char *)0x002b12b4, 218, 0);
  system_exit(0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


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

/* render_contrail (0x188010) — readable C lift (restored pre-naked). */
void render_contrail(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_00077040(0, 0, 0);
  xbox_texture_cache_get_hardware_format((void *)(uintptr_t)eax, 0, 0);
  /* test eax, eax -> je 0x18875d */
  rasterizer_widget_submit(0);
  rasterizer_widget_set_zbuffer_enable(0, 0);
  /* cmp edi, -1 -> je 0x18875d */
  rasterizer_widget_begin(0);
  rasterizer_widget_draw_sprite3d(0);
  /* test esi, esi -> je 0x1880fc */
  /* test edi, edi -> jne 0x18811f */
  display_assert((char *)0x002b1728, (char *)0x002b1740, 136, 0);
  system_exit(0);
  /* test (char)eax, 0x40 -> je 0x188136 */
  datum_get((void *)(uintptr_t)eax, 0);
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* test (char)ecx, 0x20 -> je 0x1881aa */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* cmp eax, -1 -> je 0x188332 */
  object_get_and_verify_type(0, 0);
  tag_get('ejbo', 0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* cmp (int16_t)eax, 0xffff -> je 0x188332 */
  /* test eax, eax -> je 0x1883e4 */
  datum_get((void *)(uintptr_t)ecx, 0);
  /* test eax, eax -> je 0x18842f */
  datum_get((void *)(uintptr_t)ecx, 0);
  magnitude3d((float *)(uintptr_t)edx);
  /* test eax, eax -> je 0x1884f6 */
  datum_get((void *)(uintptr_t)ecx, 0);
  normalize3d((float *)0);
  normalize3d((float *)0);
  ((void(*)(void))FUN_00187f80)();
  /* test (char)eax, 0x41 -> jne 0x188656 */
  FUN_000d1c90((float *)(uintptr_t)edx);
  /* test dl, 1 -> jne 0x1886a9 */
  /* relift: test byte ptr [ecx], 2 -> jne 0x1886b8 */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x1886ed */
  rasterizer_widget_set_texture(0);
  rasterizer_widget_end(0);
  FUN_0017cf60(eax, edx, 0, 0, edi, 0, (float *)(uintptr_t)eax, 0);
  rasterizer_widget_set_tint_factor(0);
  rasterizer_widget_submit_occlusion_test(0);
  tag_get_name(0);
  error(0, (char *)0x002b16f8);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}



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


