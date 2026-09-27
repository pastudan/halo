/* FUN_00146d40 (0x146d40) — readable C lift from XBE leaf (2D BSP walk). */
uint32_t FUN_00146d40(void *bsp2d_nodes, float *point2d, int node_index)
{
  int node = node_index;
  if (node < 0) {
    goto done;
  }
  while (node >= 0) {
    float *el = (float *)tag_block_get_element(bsp2d_nodes, node, 0x14);
    float d = el[0] * point2d[0] + el[1] * point2d[1] - el[2];
    int side = (d < *(float *)0x2533c0) ? 0 : 1;
    node = ((int *)el)[3 + side];
  }
done:
  if (node == -1) {
    return 0xffffffffu;
  }
  return (uint32_t)(node & 0x7fffffff);
}

/* bsp3d_find_leaf (0x146db0) — readable C lift from XBE leaf. */
uint32_t bsp3d_find_leaf(void *bsp3d, int root, void *point)
{
  float *p = (float *)point;
  int node = root;
  while (node >= 0) {
    int *node_el = (int *)tag_block_get_element(bsp3d, node, 0xc);
    float *plane =
        (float *)tag_block_get_element((char *)bsp3d + 0xc, node_el[0], 0x10);
    float d = plane[0] * p[0] + plane[1] * p[1] + plane[2] * p[2] - plane[3];
    int side = (d < *(float *)0x2533c0) ? 0 : 1;
    node = node_el[1 + side];
  }
  if (node == -1) {
    return 0xffffffffu;
  }
  return (uint32_t)(node & 0x7fffffff);
}

/* bsp3d_clip_line_to_leaves (0x146e30) — Capstone readable C lift.
 * Recursively clip segment p0→p1 against BSP3D nodes; invoke callback for each
 * leaf the segment reaches. Returns accumulated leaf-visit count. */
int bsp3d_clip_line_to_leaves(void *nodes, int node_index, float *p0, float *p1,
                              void (*callback)(float *, float *, unsigned int, void *),
                              void *data)
{
  int *node;
  float *plane;
  float d0, d1;
  char d0_neg, d0_pos, d1_neg, d1_pos;
  char d0f[2];
  char d1f[2];
  float delta[3];
  float hit[3];
  float t;
  float zero;
  float one;
  int leaf_count;
  int side;
  int *children;

  leaf_count = 0;
  node = (int *)tag_block_get_element(nodes, node_index, 0xc);
  plane = (float *)tag_block_get_element((char *)nodes + 0xc, node[0], 0x10);

  d0 = plane[2] * p0[2] + plane[0] * p0[0] + plane[1] * p0[1] - plane[3];
  d1 = plane[2] * p1[2] + plane[0] * p1[0] + plane[1] * p1[1] - plane[3];

  if (node_index == 0)
    *(int *)0x5a8d20 = 0;
  (*(int *)0x5a8d20)++;

  d0_neg = (d0 < *(float *)0x29ca2c);
  d0_pos = (d0 > *(float *)0x29ca28);
  d1_neg = (d1 < *(float *)0x29ca2c);
  d1_pos = (d1 > *(float *)0x29ca28);
  d0f[0] = d0_neg;
  d0f[1] = d0_pos;
  d1f[0] = d1_neg;
  d1f[1] = d1_pos;

  zero = *(float *)0x2533c0;
  one = *(float *)0x2533c8;

  if ((d0_neg && d1_pos) || (d0_pos && d1_neg)) {
    delta[0] = p1[0] - p0[0];
    delta[1] = p1[1] - p0[1];
    delta[2] = p1[2] - p0[2];
    {
      float d0b = plane[2] * p0[2] + plane[0] * p0[0] + plane[1] * p0[1] - plane[3];
      float dir_dot = delta[2] * plane[2] + delta[1] * plane[1] + delta[0] * plane[0];
      t = -(d0b / dir_dot);
    }
    if (!(t > zero && t < one)) {
      display_assert((const char *)0x29c9f8, (const char *)0x29ca08, 0x49, 1);
      system_exit(-1);
    }
    hit[0] = delta[0] * t + p0[0];
    hit[1] = delta[1] * t + p0[1];
    hit[2] = delta[2] * t + p0[2];
  }

  children = node + 1;
  for (side = 0; side < 2; side++) {
    int other;
    float *q0;
    float *q1;
    int child;

    if (!d0f[side] && !d1f[side]) {
      other = !side;
      if (!d0f[other] && !d1f[other])
        continue;
    }

    other = !side;
    q0 = d0f[other] ? hit : p0;
    q1 = d1f[other] ? hit : p1;

    child = children[side];
    if (child < 0) {
      if (child == -1)
        continue;
      if (callback)
        callback(q0, q1, (unsigned int)(child & 0x7fffffff), data);
      leaf_count++;
    } else {
      leaf_count +=
          bsp3d_clip_line_to_leaves(nodes, child, q0, q1, callback, data);
    }
  }

  return leaf_count;
}




/* FUN_001470b0 (0x1470b0): recursively partition a convex polygon against the
 * BSP3D node tree rooted at `node_index`, invoking `callback` once per terminal
 * leaf the polygon reaches. Returns the accumulated leaf-callback count.
 *
 * Node record (nodes block at `tag_base`, stride 0xc = 3 dwords): [0]=plane
 * index, [1]=back child link, [2]=front child link. Plane record (planes block
 * at tag_base+0xc, stride 0x10 = 4 floats): [0..2]=normal xyz, [3]=distance d.
 *
 * `counts` (param_5) is an int16[2] aliased on one stack dword: on entry its
 * low half is the incoming vertex count; the two halves are reused as the
 * back/front child vertex counts. `verts` (param_4) is 3 floats/vertex;
 * `param_3` is a flags/plane-side accumulator whose high bit records the routed
 * side; param_6 is the coplanarity distance tolerance; param_8 is the callback
 * context.
 *
 * Each vertex's signed plane distance |dot(n,v) - d| is emitted in y,z,x source
 * order to match the original x87 scheduling. If every vertex is within param_6
 * of the plane the polygon is coplanar: its own normal is built as the cross
 * product (v2-v0) x (v1-v0) (component order and FSUBP direction verified vs
 * disasm 0x14717e-0x1471e2 -- getting this backwards silently flips the routed
 * side) and dotted with the plane normal; a positive dot routes the whole
 * polygon to the front child and sets param_3's sign bit, otherwise the back
 * child with the sign bit cleared. Otherwise the polygon spans the plane and is
 * clipped twice via convex_polygon3d_clip_to_plane -- once against the negated
 * plane into the back buffer, once against the plane into the front buffer --
 * with the two clipped counts stored into the two count halves.
 *
 * The two children are iterated back (link[1]) then front (link[2]); a side
 * with a zero count is skipped. A negative child link is terminal: 0xffffffff
 * is solid/no-leaf (skipped), any other negative value is a leaf index (high
 * sign bit stripped) reported via the callback; a non-negative link is recursed
 * into.
 */
int FUN_001470b0(int param_1, uint32_t param_2, uint32_t param_3,
                 float *param_4, int param_5, float param_6,
                 void (*param_7)(float *, int, unsigned int, unsigned int,
                                 void *),
                 void *param_8)
{
  int leaf_count;
  uint32_t *node;
  float *plane;
  short *counts;
  uint32_t *links;
  int vertex_count;
  int i;
  float *v;
  float dist;
  float e1x, e1y, e1z;
  float e2x, e2y, e2z;
  float normal_x, normal_y, normal_z;
  float side;
  float neg_plane[4];
  float *bufs[2];
  int cnt;
  uint32_t link;
  float back_buf[192];
  float front_buf[192];

  leaf_count = 0;
  counts = (short *)&param_5;
  vertex_count = *counts;

  node = (uint32_t *)tag_block_get_element((void *)param_1, (int)param_2, 0xc);
  plane =
    (float *)tag_block_get_element((void *)(param_1 + 0xc), (int)node[0], 0x10);
  links = node + 1;

  if (vertex_count < 3) {
    display_assert("point_count>=NUMBER_OF_VERTICES_PER_TRIANGLE",
                   "c:\\halo\\SOURCE\\physics\\bsp3d.c", 0x95, true);
    system_exit(-1);
  }
  if (0x3f < vertex_count) {
    display_assert("point_count<=MAXIMUM_VERTICES_PER_CLIPPED_POLYGON",
                   "c:\\halo\\SOURCE\\physics\\bsp3d.c", 0x97, true);
    system_exit(-1);
  }

  for (i = 0; i < vertex_count; i++) {
    v = param_4 + i * 3;
    dist = ((v[1] * plane[1] + v[2] * plane[2]) + v[0] * plane[0]) - plane[3];
    if (param_6 <= xbox_fabsf(dist)) {
      break;
    }
  }

  if (i == vertex_count) {
    /* Polygon lies in the plane: classify by its own normal vs the plane. */
    v = param_4;
    e1x = v[3] - v[0];
    e1y = v[4] - v[1];
    e1z = v[5] - v[2];
    e2x = v[6] - v[0];
    e2y = v[7] - v[1];
    e2z = v[8] - v[2];
    normal_x = e2y * e1z - e2z * e1y;
    normal_y = e2z * e1x - e2x * e1z;
    normal_z = e2x * e1y - e2y * e1x;
    side = normal_z * plane[2] + normal_y * plane[1] + normal_x * plane[0];

    if (*(float *)0x002533c0 < side) {
      counts[1] = (short)vertex_count;
      counts[0] = 0;
      bufs[1] = param_4;
      param_3 = param_3 | 0x80000000;
    } else {
      counts[0] = (short)vertex_count;
      counts[1] = 0;
      bufs[0] = param_4;
      param_3 = param_3 & 0x7fffffff;
    }
  } else {
    /* Polygon spans the plane: clip against both half-spaces. */
    neg_plane[0] = -plane[0];
    neg_plane[1] = -plane[1];
    neg_plane[2] = -plane[2];
    neg_plane[3] = -plane[3];
    counts[0] = convex_polygon3d_clip_to_plane(vertex_count, param_4, neg_plane,
                                               0x40, back_buf, 0, param_6, 0);
    counts[1] = convex_polygon3d_clip_to_plane(vertex_count, param_4, plane,
                                               0x40, front_buf, 0, param_6, 0);
    if (counts[0] == -1 || counts[1] == -1) {
      display_assert("back_count!=NONE && front_count!=NONE",
                     "c:\\halo\\SOURCE\\physics\\bsp3d.c", 0xb9, true);
      system_exit(-1);
    }
    bufs[0] = back_buf;
    bufs[1] = front_buf;
  }

  for (i = 0; i < 2; i++) {
    cnt = counts[i];
    if (cnt != 0) {
      link = links[i];
      if ((int)link < 0) {
        if (link != 0xffffffff) {
          if (param_7 != NULL) {
            param_7(bufs[i], cnt, link & 0x7fffffff, param_3, param_8);
          }
          leaf_count++;
        }
      } else {
        leaf_count += FUN_001470b0(param_1, link, param_3, bufs[i], cnt,
                                   param_6, param_7, param_8);
      }
    }
  }

  return leaf_count;
}
/* --- bsp3d.obj batch drafts (2026-07-26) --- */

/* FUN_00146be0 (0x146be0) — readable C lift (restored pre-naked). */
void FUN_00146be0(void *damage_params)
{
  char *scenario;
  char *jpt;
  char *block;
  char *surf;
  float *damage;
  float radius;
  float dx, dy, dz, limit;
  int count;
  int16_t i;
  unsigned int *bits;
  float *flags;

  scenario = (char *)scenario_get();
  damage = (float *)damage_params;
  jpt = (char *)tag_get(0x6a707421, *(int *)damage_params); /* '!tpj' */
  if (*(char *)0x46f08c == 0)
    return;
  if (*(float *)(jpt + 0x1d4) == *(float *)0x2533c0 &&
      *(float *)(jpt + 0x1d8) == *(float *)0x2533c0)
    return;

  radius = *(float *)(jpt + 4);
  if (radius > *(float *)0x2533d8)
    error(2, (char *)0x0029c9b8, (double)radius);

  block = scenario + 0x16c;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    if (!breakable_surface_extant(i))
      continue;
    surf = (char *)tag_block_get_element(block, (int)i, 0x30);
    limit = *(float *)(surf + 0xc) + radius;
    dx = damage[0x28 / 4] - *(float *)(surf + 0);
    dy = damage[0x2c / 4] - *(float *)(surf + 4);
    dz = damage[0x30 / 4] - *(float *)(surf + 8);
    if (limit * limit < dx * dx + dy * dy + dz * dz)
      continue;

    flags = breakable_surface_get(i);
    *flags = 0.0f;
    bits = (unsigned int *)breakable_surfaces_get_bsp_surface_data();
    bits[(unsigned int)i >> 5] &= ~(1u << ((unsigned int)i & 0x1f));
    FUN_00145ad0((unsigned short)i, damage_params, *(int *)(surf + 0x10));
  }
}

