/* collision_bsp.obj (physics/collision_bsp.c)
 *
 * Declarations for tag_block_get_element, display_assert and system_exit come
 * from the generated decl.h via kb.json.
 */

/* 0x1473b0 - collision_surface_edge_count
 *
 * Counts the edges around one collision-BSP surface by walking its circular
 * edge loop. Same winged-edge traversal as collision_surface_polygon but
 * without gathering geometry.
 *
 * bsp base holds tag_block headers at fixed offsets:
 *   +0x3c surfaces (stride 0xc): surface[+4] = first-edge index
 *   +0x48 edges    (stride 0x18): edge[+0x14] = owning-surface index,
 *                                 edge[+8]/edge[+0xc] = the two half-edge
 *                                 next-edge links
 *
 * `side` = (edge[+0x14] == surface_index) selects this surface's half-edge
 * slot: next-edge index at edge[+8 | +0xc]. The do-while increments the count
 * once per edge and terminates when the next-edge index returns to the
 * surface's first-edge index. The original returns the count in AX only (high
 * half of EAX is leftover garbage from the terminator index), so the faithful
 * return type is short.
 */
short collision_surface_edge_count(int bsp, int surface_index)
{
  short edge_count;
  int first_edge;
  int edge_index;
  int *edge;

  edge_count = 0;
  first_edge = *(int *)((char *)tag_block_get_element((void *)(bsp + 0x3c),
                                                      surface_index, 0xc) +
                        4);
  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
    edge_count = (short)(edge_count + 1);
    edge_index = edge[2 + (edge[5] == surface_index)];
  } while (edge_index != first_edge);
  return edge_count;
}

/* 0x147410 - collision_surface_polygon
 *
 * Walks a collision-BSP surface's circular edge loop and gathers the surface's
 * polygon vertices (xyz float triples, stride 0xc) into out_points. Returns the
 * 16-bit vertex count.
 *
 * bsp base holds three tag_block headers at fixed offsets:
 *   +0x3c surfaces (stride 0xc): surface[+4] = first-edge index
 *   +0x48 edges    (stride 0x18)
 *   +0x54 vertices (stride 0x10): first 0xc bytes = xyz float32
 *
 * Winged-edge orientation: `side` = (edge[+0x14] == surface_index). The edge
 * stores its two half-edge slots interleaved; `side` selects this surface's
 * slot -> vertex index at edge[+0 | +4], next-edge index at edge[+8 | +0xc].
 *
 * The loop is do-while (the first vertex is always copied); it terminates when
 * the next-edge index returns to the surface's first-edge index. The original
 * returns the count in AX only (high half of EAX is leftover garbage from the
 * terminator index), so the faithful return type is short.
 */
short collision_surface_polygon(int bsp, int surface_index, void *out_points)
{
  short point_count;
  int first_edge;
  int edge_index;
  int *edge;
  unsigned int *vertex;
  unsigned int *out;
  int side;

  point_count = 0;
  first_edge = *(int *)((char *)tag_block_get_element((void *)(bsp + 0x3c),
                                                      surface_index, 0xc) +
                        4);
  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
    side = (edge[5] == surface_index);
    vertex = (unsigned int *)tag_block_get_element((void *)(bsp + 0x54),
                                                   edge[side], 0x10);
    if (point_count > 7) {
      display_assert("point_count<MAXIMUM_VERTICES_PER_COLLISION_SURFACE",
                     "c:\\halo\\SOURCE\\physics\\collision_bsp.c", 0xe1, 1);
      system_exit(-1);
    }
    out = (unsigned int *)((char *)out_points + point_count * 0xc);
    out[0] = vertex[0];
    out[1] = vertex[1];
    out[2] = vertex[2];
    edge_index = edge[2 + side];
    point_count = (short)(point_count + 1);
  } while (edge_index != first_edge);
  return point_count;
}

/* render_debug.c -- debug primitive rendering
 * (c:\halo\SOURCE\render\render_debug.c)
 *
 * The debug renderer keeps a per-frame cache of debug primitives (points,
 * lines, boxes, text, ...) submitted through the cache writer at 0x188ec0.
 * Each cache record is 0x38 (56) bytes; the leading short is the primitive
 * type. render_debug (0x18ac50) flushes the cache once per frame: it runs the
 * fixed set of debug sub-renderers, walks the cache dispatching each record to
 * its draw routine, then clears the cache when the game frame advances.
 */

#include "x87_math.h"

/* Per-frame debug primitive cache record (0x38 bytes, array based at 0x4d1220).
 * The payload is a tagged union keyed by `type`; individual offsets are reused
 * per primitive kind, so the fields carry raw-offset names. */
typedef struct debug_primitive {
  short type; /* +0x00 primitive type (0..9)          */
  short pad02; /* +0x02                                */
  float f04; /* +0x04                                */
  float f08; /* +0x08                                */
  float f0c; /* +0x0c                                */
  float f10; /* +0x10                                */
  unsigned short s14; /* +0x14                                */
  unsigned char b16; /* +0x16                                */
  unsigned char pad17; /* +0x17                                */
  float f18; /* +0x18                                */
  float f1c; /* +0x1c                                */
  float f20; /* +0x20                                */
  float f24; /* +0x24                                */
  float f28; /* +0x28                                */
  float f2c; /* +0x2c                                */
  float f30; /* +0x30                                */
  float f34; /* +0x34                                */
} debug_primitive; /* sizeof == 0x38 */

typedef char
  debug_primitive_size_check[sizeof(debug_primitive) == 0x38 ? 1 : -1];

#define debug_primitives ((debug_primitive *)0x4d1220)
#define debug_primitive_count (*(short *)0x4d8224)
#define debug_primitive_frame (*(short *)0x4d8220)

/* Per-frame debug string arena: char[0x400] at 0x4d0e20, ending at 0x4d121f
 * (immediately before the primitive cache at 0x4d1220). Text primitives intern
 * their string here; the cursor at 0x4d8228 counts bytes used (max 0x3ff). */
#define debug_string_pool ((char *)0x4d0e20)
#define debug_string_pool_count (*(short *)0x4d8228)
#define debug_string_overflow_warned (*(char *)0x4d822b)

/* Draw one collision-BSP vertex as a debug point (0x147520, collision_bsp.obj).
 * Fetches collision vertex `vertex_index` (0x10-byte record) from the tag_block
 * at bsp+0x54, optionally transforms it through `matrix` into a local scratch
 * point, then submits it to the cached debug-point drawer (0x189150) with the
 * given scale and color. When matrix is NULL the raw vertex position is drawn
 * directly. */
void render_debug_collision_vertex(int bsp, int vertex_index, float *matrix,
                                   float scale, void *color)
{
  float *point;
  float transformed[3];

  point =
    (float *)tag_block_get_element((void *)(bsp + 0x54), vertex_index, 0x10);
  if (matrix != 0) {
    matrix_transform_point(matrix, point, transformed);
    point = transformed;
  }
  FUN_00189150(1, point, scale, color);
}

/* 0x147570 - render_debug_collision_edge
 *
 * Draws one collision-BSP edge as a debug line. The edge tag_block lives at
 * bsp+0x48 (stride 0x18); the first two dwords of an edge element are its two
 * endpoint vertex indices (v0, v1). Vertices live at bsp+0x54 (stride 0x10),
 * xyz float32 in the leading 0xc bytes.
 *
 * When matrix_or_flag is non-NULL it is a transform matrix pointer: each
 * endpoint is passed through matrix_transform_point into a local vec3 scratch
 * and the transformed points are drawn. When NULL the raw tag_block vertex
 * pointers are drawn directly. The debug color pointer is forwarded unchanged.
 *
 * Endpoint order is not swapped: point_a = vertex[edge v0], point_b =
 * vertex[edge v1]; the draw call is (flag=1, point_a, point_b, color).
 * matrix_transform_point/FUN_00189270 return void in kb.json, so the
 * transformed points are read from the scratch buffers, not a returned ptr.
 */
void render_debug_collision_edge(int bsp, int edge_index, int matrix_or_flag,
                                 void *color)
{
  int *edge;
  float *point_a;
  float *point_b;
  float xformed_a[3];
  float xformed_b[3];

  edge = (int *)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
  point_a = (float *)tag_block_get_element((void *)(bsp + 0x54), edge[0], 0x10);
  point_b = (float *)tag_block_get_element((void *)(bsp + 0x54), edge[1], 0x10);
  if (matrix_or_flag != 0) {
    matrix_transform_point((float *)matrix_or_flag, point_a, xformed_a);
    matrix_transform_point((float *)matrix_or_flag, point_b, xformed_b);
    point_a = xformed_a;
    point_b = xformed_b;
  }
  FUN_00189270(1, point_a, point_b, color);
}

/* 0x1475f0 - render_debug_collision_surface
 *
 * Walks the circular doubly-linked edge list of one collision-BSP surface and
 * renders each bounding edge via render_debug_collision_edge.
 *
 * bsp+0x3c = surfaces tag_block (stride 0xc); surface element field +4 is the
 * index of the surface's first bounding edge. bsp+0x48 = edges tag_block
 * (stride 0x18). Per edge: field +0x14 is the edge's "side A" (left) surface
 * reference; fields +8 and +0xc are the two edge links.
 *
 * Link selection: if the edge's +0x14 surface equals this surface_index (we own
 * the edge on side A) advance via the +0xc link, otherwise via the +8 link.
 * Encoded exactly as the original: base +8 plus (cond)*4 as a byte offset; kept
 * verbatim because the (cond)*4 codegen matters for VC71 match.
 *
 * Terminator: do-while until the walk wraps back to the first edge. param_3
 * (matrix-or-flag) and param_4 (debug color) are forwarded to the edge draw
 * unchanged.
 */
void render_debug_collision_surface(int bsp, int surface_index,
                                    int matrix_or_flag, void *color)
{
  int surface;
  int edge;
  int first_edge;
  int edge_index;
  int left_surface;

  surface =
    (int)tag_block_get_element((void *)(bsp + 0x3c), surface_index, 0xc);
  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  do {
    edge = (int)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
    left_surface = *(int *)(edge + 0x14);
    render_debug_collision_edge(bsp, edge_index, matrix_or_flag, color);
    edge_index =
      *(int *)(edge + 8 + (unsigned int)(left_surface == surface_index) * 4);
  } while (edge_index != first_edge);
}

/* 0x147660 - render_debug_collision_bsp
 *
 * Draws every edge of a collision BSP for debug visualization. The edge
 * tag_block header lives at bsp+0x48; its element count (bsp+0x48+0 first
 * dword) is the loop bound. Each edge is rendered by
 * render_debug_collision_edge, with param_2 forwarded unchanged
 * (transform-matrix pointer or flag) and the debug color pointer read from the
 * global at 0x2ee6d4.
 *
 * The original is a do-while guarded by an outer `count > 0` test, which is the
 * canonical MSVC codegen for this for-loop.
 */
void render_debug_collision_bsp(int bsp, int matrix_or_flag)
{
  int i;

  for (i = 0; i < *(int *)(bsp + 0x48); i++) {
    render_debug_collision_edge(bsp, i, matrix_or_flag, *(void **)0x2ee6d4);
  }
}

/* 0x1476a0 - collision_edge_length
 *
 * Returns the 3D Euclidean length of a collision-BSP edge. The edge element
 * (bsp+0x48, stride 0x18) holds its two endpoint vertex indices in the first
 * two dwords. Each vertex (bsp+0x54, stride 0x10) begins with an xyz float32
 * triple. Result = sqrt(dx^2 + dy^2 + dz^2).
 *
 * The original x87 codegen (float10/FSQRT) loads the three component
 * differences in x, y, z order (offsets 0, 4, 8), each taken as
 * vertex_b - vertex_a, squares them, and sums; kept inline in that order for
 * VC71 match (confirmed against the delinked reference: flds 0/4/8).
 */
float collision_edge_length(int bsp, int edge_index)
{
  unsigned int *edge;
  float *vertex_a;
  float *vertex_b;

  edge = (unsigned int *)tag_block_get_element((void *)(bsp + 0x48), edge_index,
                                               0x18);
  vertex_a =
    (float *)tag_block_get_element((void *)(bsp + 0x54), edge[0], 0x10);
  vertex_b =
    (float *)tag_block_get_element((void *)(bsp + 0x54), edge[1], 0x10);
  return sqrtf((vertex_b[0] - vertex_a[0]) * (vertex_b[0] - vertex_a[0]) +
               (vertex_b[1] - vertex_a[1]) * (vertex_b[1] - vertex_a[1]) +
               (vertex_b[2] - vertex_a[2]) * (vertex_b[2] - vertex_a[2]));
}

/* 0x147710 - collision_surface_perimeter
 *
 * Sums the edge lengths around a collision-BSP surface's winged-edge loop and
 * returns the total perimeter (float in ST0).
 *
 * Layout mirrors collision_surface_polygon (same three tag_block headers on the
 * bsp base): +0x3c surfaces (stride 0xc, surface[+4] = first-edge index),
 * +0x48 edges (stride 0x18), +0x54 vertices (stride 0x10, xyz float32 at +0).
 *
 * Winged-edge orientation: side = (edge[+0x14] == surface_index). side selects
 * this surface's half-edge slot -> vertex_a at edge[side], vertex_b at
 * edge[!side], next-edge index at edge[2 + side] (byte +0x8 | +0xc). The loop
 * is do-while (at least one edge) and terminates when the next-edge index
 * returns to the surface's first-edge index.
 *
 * The per-edge SQRT sums the squared component differences (vertex_b -
 * vertex_a) in y, z, x order (edge indices [1], [2], [0]) to match the original
 * x87 FADD scheduling; the running total is accumulated as sqrtf(...) + total.
 */
float collision_surface_perimeter(int bsp, int surface_index)
{
  int *edge;
  float *vertex_a;
  float *vertex_b;
  int first_edge;
  int edge_index;
  unsigned char side;
  float total;
  float dx, dy, dz;

  total = 0.0f;
  first_edge = *(int *)((char *)tag_block_get_element((void *)(bsp + 0x3c),
                                                      surface_index, 0xc) +
                        4);
  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
    side = (edge[5] == surface_index);
    vertex_a =
      (float *)tag_block_get_element((void *)(bsp + 0x54), edge[side], 0x10);
    vertex_b =
      (float *)tag_block_get_element((void *)(bsp + 0x54), edge[!side], 0x10);
    dy = vertex_b[1] - vertex_a[1];
    dz = vertex_b[2] - vertex_a[2];
    dx = vertex_b[0] - vertex_a[0];
    total = sqrtf(dy * dy + dz * dz + dx * dx) + total;
    edge_index = edge[2 + side];
  } while (edge_index != first_edge);
  return total;
}

/* 0x1477f0 - collision_surface_area
 *
 * Computes the signed projected area of a collision-BSP surface polygon by
 * fan-triangulating its edge loop from a fixed anchor vertex and summing
 * dot(cross(e0, e1), plane_normal) over each triangle, where the plane normal
 * comes from the surface's plane designator. Returns the accumulated area if
 * positive, else 0.0f (both the >0 branch and the fall-through return 0.0f).
 *
 * bsp base tag_block headers (see collision_surface_polygon):
 *   +0x3c surfaces (stride 0xc): surface[0] = plane designator,
 *                                surface[+4] = first-edge index
 *   +0x48 edges    (stride 0x18): +0x14 = owning surface index;
 *                                 +0/+4 = start/end vertex refs;
 *                                 +8/+0xc = next-edge refs (winged-edge slots)
 *   +0x54 vertices (stride 0x10): first 0xc bytes = xyz float32
 *
 * `side` = (edge[+0x14] == surface_index) selects this surface's half-edge
 * slot each iteration. The anchor vertex and plane normal are fetched once
 * before the loop; each iteration walks the two vertices of the current edge.
 *
 * The plane normal is written contiguously into plane[3] by
 * bsp3d_get_plane_from_designator (out_plane), so it reads back as
 * plane[0..2]. Cross-product and accumulation operand order preserved exactly
 * from the disassembly (x87 FLD/FMUL/FSUBP order); getting any subtraction
 * backwards negates the area.
 */
float collision_surface_area(int bsp, int surface_index)
{
  float plane[3];
  volatile float cross_x; /* volatile = store-once/reload-each-use; the
                             original spills exactly these four to stack
                             slots and keeps pa_xyz, qa_z, cross_z
                             ST-resident */
  volatile float cross_y;
  float cross_z;
  float pa_x, pa_y, pa_z;          /* edge[side] vertex - anchor */
  volatile float qa_x, qa_y;       /* edge[!side] vertex - anchor */
  float qa_z;
  float *anchor;
  float *v0;
  float *v1;
  int *surface;
  int edges_block;
  int verts_block;
  int edge;
  unsigned char side;
  unsigned char is_owner;
  float area;

  area = 0.0f;
  surface =
    (int *)tag_block_get_element((void *)(bsp + 0x3c), surface_index, 0xc);
  edges_block = bsp + 0x48;
  edge = (int)tag_block_get_element((void *)edges_block, surface[1], 0x18);
  side = (*(int *)(edge + 0x14) == surface_index);
  verts_block = bsp + 0x54;
  anchor = (float *)tag_block_get_element((void *)verts_block,
                                          *(int *)(edge + side * 4), 0x10);
  bsp3d_get_plane_from_designator(bsp, (unsigned int)surface[0], plane);
  edge = (int)tag_block_get_element((void *)edges_block,
                                    *(int *)(edge + 8 + side * 4), 0x18);
  is_owner = (*(int *)(edge + 0x14) == surface_index);
  side = is_owner;
  if (*(int *)(edge + 8 + side * 4) != surface[1]) {
    do {
      v1 = (float *)tag_block_get_element((void *)verts_block,
                                          *(int *)(edge + side * 4), 0x10);
      v0 = (float *)tag_block_get_element(
        (void *)verts_block, *(int *)(edge + (!is_owner) * 4), 0x10);
      pa_x = v1[0] - anchor[0];
      pa_y = v1[1] - anchor[1];
      pa_z = v1[2] - anchor[2];
      qa_x = v0[0] - anchor[0];
      qa_y = v0[1] - anchor[1];
      qa_z = v0[2] - anchor[2];
      cross_x = qa_z * pa_y - qa_y * pa_z;
      cross_y = pa_z * qa_x - qa_z * pa_x;
      cross_z = pa_x * qa_y - qa_x * pa_y;
      area = plane[2] * cross_z + plane[1] * cross_y + cross_x * plane[0] +
             area;
      edge = (int)tag_block_get_element((void *)edges_block,
                                        *(int *)(edge + 8 + side * 4), 0x18);
      is_owner = (*(int *)(edge + 0x14) == surface_index);
      side = is_owner;
    } while (*(int *)(edge + 8 + side * 4) != surface[1]);
    if (area > 0.0f) {
      return area;
    }
  }
  return 0.0f;
}

/* 0x147d10 - collision_surface_test_line2d
 *
 * Clips a 2D line (point + direction) against one collision-BSP surface's
 * bounding-edge loop, returning whether the line's entering and leaving
 * parameters bracket a non-empty interval (i.e. the line crosses the surface's
 * interior). Same tag_block geometry as collision_surface_polygon:
 *   bsp+0x3c surfaces (stride 0xc): surface[+4] = first-edge index
 *   bsp+0x48 edges    (stride 0x18)
 *   bsp+0x54 vertices (stride 0x10): first 0xc bytes = xyz float32
 *
 * Winged edge: `side` = (edge[5] == surface_index) tells which half-edge slot
 * belongs to this surface. Both endpoints (edge[0], edge[1]) are always read;
 * the next-edge link is edge[2 + side] and the neighbor-surface index across
 * the edge is edge[!side + 4] (i.e. edge[+0x10] or edge[+0x14]).
 *
 * out_result is a MIXED 6-dword record, NOT six floats:
 *   +0x00 float  enter_t   (max entering parameter; init -FLT_MAX)
 *   +0x04 int    enter_edge (edge index; init -1)
 *   +0x08 int    enter_surface (neighbor surface index; init -1)
 *   +0x0c float  leave_t   (min leaving parameter; init +FLT_MAX)
 *   +0x10 int    leave_edge (init -1)
 *   +0x14 int    leave_surface (init -1)
 * The four index slots are raw dword stores (the current edge index and the
 * neighbor-surface index). Ghidra prints the index stores as (float)..., but
 * the disassembly is a plain MOV: they are int32 fields, not int->float
 * conversions (lift-silent-bugs Check 1). They are written through the
 * int-aliased pointer.
 *
 * Per edge, edge_cross = 2D cross of the edge vector (v1-v0) with the ray
 * direction; pt_cross = 2D cross of (point-v0) with (v1-v0). FPU load/subtract
 * order verified against the delinked reference (cross-product operand order,
 * lift-decompiler-traps Trap 4). When edge_cross==0 (ray parallel to edge) and
 * the point sits on the inner side, both enter/leave are forced to a crossing
 * interval. Otherwise t = pt_cross/edge_cross updates the entering or leaving
 * bound depending on sign(edge_cross) vs side. Returns 1 iff leave_t < enter_t.
 */
int collision_surface_test_line2d(int bsp, int surface_index, int param3,
                                  int param4, float *point, float *direction,
                                  float *out_result)
{
  int first_edge;
  int edge_index;
  int *edge;
  float *v0;
  float *v1;
  unsigned char side;         /* sete to a byte slot in the original */
  volatile float edge_cross;  /* store-once/reload: the original spills it
                                 to the out_result param home slot and
                                 reloads it 3x (==0 test, divide, sign) */
  float pt_cross;
  float ex, ey; /* v1 - v0 (edge vector), kept ST-resident */
  float cx, cy; /* point - v0, kept ST-resident */
  int *out_i;

  out_i = (int *)out_result;

  first_edge = *(int *)((char *)tag_block_get_element((void *)(bsp + 0x3c),
                                                      surface_index, 0xc) +
                        4);
  edge_index = first_edge;

  out_result[0] = -3.4028235e+38f;
  out_i[1] = -1;
  out_i[2] = -1;
  out_result[3] = 3.4028235e+38f;
  out_i[4] = -1;
  out_i[5] = -1;

  do {
    edge = (int *)tag_block_get_element((void *)(bsp + 0x48), edge_index, 0x18);
    side = (edge[5] == surface_index);
    v0 = (float *)tag_block_get_element((void *)(bsp + 0x54), edge[0], 0x10);
    v1 = (float *)tag_block_get_element((void *)(bsp + 0x54), edge[1], 0x10);

    ex = v1[0] - v0[0];
    ey = v1[1] - v0[1];
    cx = point[0] - v0[0];
    cy = point[1] - v0[1];
    edge_cross = ey * direction[0] - ex * direction[1];
    pt_cross = ex * cy - cx * ey;

    if (edge_cross != 0.0f) {
      pt_cross = pt_cross / edge_cross;
      if ((edge_cross < 0.0f) != side) {
        if (pt_cross > out_result[0]) {
          out_result[0] = pt_cross;
          out_i[1] = edge_index;
          out_i[2] = edge[!side + 4];
        }
      } else if (pt_cross < out_result[3]) {
        out_result[3] = pt_cross;
        out_i[4] = edge_index;
        out_i[5] = edge[!side + 4];
      }
    } else if ((pt_cross < 0.0f) != side) {
      out_result[0] = 3.4028235e+38f;
      out_i[1] = edge_index;
      out_i[2] = edge[!side + 4];
      out_result[3] = -3.4028235e+38f;
      out_i[4] = edge_index;
      out_i[5] = edge[!side + 4];
    }

    edge_index = edge[side + 2];
  } while (edge_index != first_edge);

  if (out_result[0] > out_result[3]) {
    return 1;
  }
  return 0;
}


/* -------------------------------------------------------------------------
 * collision_surface_project_point2d (0x147990)
 *
 * Load surface plane, then project_point2d (0x992d0) to unproject a 2D point
 * onto that plane (writes 3 floats). Returns out_point.
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
int collision_surface_project_point2d(int bsp, int surface_index,
                                      int projection, int sign, float *point,
                                      float *out_point)
{
  char *surface;
  int plane_index;
  float *plane;

  surface =
    (char *)tag_block_get_element((char *)bsp + 0x3c, surface_index, 0xc);
  plane_index = *(int *)surface & 0x7fffffff;
  plane =
    (float *)tag_block_get_element((char *)bsp + 0xc, plane_index, 0x10);
  project_point2d(point, plane, (short)projection, (unsigned char)sign,
                  out_point);
  return (int)out_point;
}


/* -------------------------------------------------------------------------
 * collision_surface_test_point2d (0x1479e0)
 *
 * Point-in-projected-polygon for one surface (same edge-cross test as
 * FUN_00148240, without the breakable bitset gate). point is 2D in the
 * projection/sign frame (callers often pass XYZ and use projection=2).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
char collision_surface_test_point2d(int bsp, int surface_index, int projection,
                                    int sign, float *point)
{
  char *surface;
  int first_edge;
  int edge_index;
  int *edge;
  int side;
  float *vert0;
  float *vert1;
  float proj0[2];
  float proj1[2];
  float dx, dy, ex, ey, cross;

  surface =
    (char *)tag_block_get_element((char *)bsp + 0x3c, surface_index, 0xc);
  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((char *)bsp + 0x48, edge_index, 0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[side], 0x10);
    vert1 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[!side],
                                           0x10);
    FUN_00061df0(vert0, (short)projection, (unsigned char)sign, proj0);
    FUN_00061df0(vert1, (short)projection, (unsigned char)sign, proj1);

    dx = point[0] - proj0[0];
    dy = point[1] - proj0[1];
    ex = proj1[0] - proj0[0];
    ey = proj1[1] - proj0[1];
    cross = ey * dx - ex * dy;
    if (cross > *(float *)0x2533c0) {
      return 0;
    }

    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  return 1;
}


/* -------------------------------------------------------------------------
 * collision_surface_find_closest_point2d (0x147ae0)
 *
 * Closest 2D point on a surface polygon to `point` (same projection/sign
 * frame as test_point2d). Returns 1 with out=point when accepted inside;
 * else 0 with out on the boundary (edge foot or vertex).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
int collision_surface_find_closest_point2d(int bsp, int surface_index,
                                           int projection, int sign,
                                           float *point, float *out_point)
{
  char *surface;
  int first_edge;
  int edge_index;
  int *edge;
  int side;
  float *vert0;
  float *vert1;
  float proj0[2];
  float proj1[2];
  float dx, dy, ex, ey, cross, t_numer, edge_len_sq, t;
  unsigned char before_start;
  unsigned char on_segment;
  unsigned char prev_before_start;
  unsigned char prev_on_segment;
  unsigned char first_before_start;
  unsigned char first_on_segment;

  surface =
    (char *)tag_block_get_element((char *)bsp + 0x3c, surface_index, 0xc);
  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  prev_before_start = 0;
  prev_on_segment = 0;
  first_before_start = 0;
  first_on_segment = 0;

  do {
    edge = (int *)tag_block_get_element((char *)bsp + 0x48, edge_index, 0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[side], 0x10);
    vert1 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[!side],
                                           0x10);
    FUN_00061df0(vert0, (short)projection, (unsigned char)sign, proj0);
    FUN_00061df0(vert1, (short)projection, (unsigned char)sign, proj1);

    dx = point[0] - proj0[0];
    dy = point[1] - proj0[1];
    ex = proj1[0] - proj0[0];
    ey = proj1[1] - proj0[1];
    /* outside half-plane when cross > 0 (same sign as test_point2d fail) */
    cross = ey * dx - ex * dy;

    if (cross > *(float *)0x2533c0) {
      t_numer = ex * dx + ey * dy;
      if (t_numer < *(float *)0x2533c0) {
        before_start = 1;
        on_segment = 0;
      } else {
        edge_len_sq = ex * ex + ey * ey;
        /* 0 <= t_numer <= len² → foot on segment; return immediately */
        if (!(t_numer > edge_len_sq)) {
          t = t_numer / edge_len_sq;
          out_point[0] = ex * t + proj0[0];
          out_point[1] = ey * t + proj0[1];
          return 0;
        }
        before_start = 0;
        on_segment = 1;
      }
    } else {
      before_start = 0;
      on_segment = 0;
    }

    if (edge_index != first_edge) {
      if (prev_on_segment) {
        if (before_start || !on_segment) {
          out_point[0] = proj0[0];
          out_point[1] = proj0[1];
          return 0;
        }
      } else if (before_start && !prev_before_start) {
        out_point[0] = proj0[0];
        out_point[1] = proj0[1];
        return 0;
      }
    } else {
      first_before_start = before_start;
      first_on_segment = on_segment;
    }

    prev_before_start = before_start;
    prev_on_segment = on_segment;
    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  if (on_segment) {
    if (first_before_start || !first_on_segment)
      goto project_first_vertex;
  } else if (first_before_start && !before_start) {
    goto project_first_vertex;
  }

  out_point[0] = point[0];
  out_point[1] = point[1];
  return 1;

project_first_vertex:
  edge = (int *)tag_block_get_element((char *)bsp + 0x48, edge_index, 0x18);
  side = (edge[5] == surface_index) ? 1 : 0;
  vert0 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[side], 0x10);
  FUN_00061df0(vert0, (short)projection, (unsigned char)sign, out_point);
  return 0;
}


/* -------------------------------------------------------------------------
 * FUN_00148370 (0x148370) — ray vs sphere (endpoint of pill edge).
 *
 * XBE: origin@eax center@ecx direction@edx out_t@esi; stack = radius (float).
 * If origin inside/on sphere → *out_t=0 success. Else nearer root in (0,1].
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
char FUN_00148370(float *origin, float *center, float *direction, float *out_t,
                  float radius)
{
  float w_x, w_y, w_z;
  float c, b, d2, disc, t;

  w_x = center[0] - origin[0];
  w_y = center[1] - origin[1];
  w_z = center[2] - origin[2];
  c = w_x * w_x + w_y * w_y + w_z * w_z - radius * radius;

  /* fcomp c,0; test ah,41h / jp → quadratic when c > 0 */
  if (!(c > *(float *)0x2533c0)) {
    *out_t = *(float *)0x2533c0;
    return 1;
  }

  b = w_x * direction[0] + w_z * direction[2] + w_y * direction[1];
  /* need b > 0 (sphere ahead) */
  if (!(b > *(float *)0x2533c0)) {
    return 0;
  }

  d2 = direction[0] * direction[0] + direction[1] * direction[1] +
       direction[2] * direction[2];
  disc = b * b - d2 * c;
  if (disc < *(float *)0x2533c0) {
    return 0;
  }

  t = (b - sqrtf(disc)) / d2;
  if (t > *(float *)0x2533c8) {
    return 0;
  }
  *out_t = t;
  return 1;
}


/* -------------------------------------------------------------------------
 * FUN_00148910 (0x148910) — ray vs pill edge (cylinder + endpoint spheres).
 *
 * XBE: out_t@eax origin@ebx edge_a@ecx direction@edx edge_delta@edi;
 * stack: radius (float by value), out_u (float*).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
char FUN_00148910(float *out_t, float *origin, float *edge_a, float *direction,
                  float *edge_delta, float radius, float *out_u)
{
  float w_x, w_y, w_z;
  float edge_len_sq;
  float e_dot_d;
  float a;
  float w_dot_e;
  float b;
  float disc;
  float sqrt_disc;
  float inv_a;
  float t0, t1, t;
  float u_num;
  float end_pt[3];

  w_x = origin[0] - edge_a[0];
  w_y = origin[1] - edge_a[1];
  w_z = origin[2] - edge_a[2];

  edge_len_sq = edge_delta[2] * edge_delta[2] + edge_delta[0] * edge_delta[0] +
                edge_delta[1] * edge_delta[1];
  e_dot_d = edge_delta[2] * direction[2] + edge_delta[1] * direction[1] +
            edge_delta[0] * direction[0];
  a = (direction[0] * direction[0] + direction[1] * direction[1] +
       direction[2] * direction[2]) *
        edge_len_sq -
      e_dot_d * e_dot_d;

  /* reject a == 0 (parallel / degenerate) — test ah,0x44 / jnp */
  if (a == *(float *)0x2533c0) {
    return 0;
  }

  w_dot_e = w_z * edge_delta[2] + w_x * edge_delta[0] + w_y * edge_delta[1];
  b = w_dot_e * e_dot_d -
      (w_x * direction[0] + w_z * direction[2] + w_y * direction[1]) *
        edge_len_sq;

  disc = b * b -
         ((w_z * w_z + w_x * w_x + w_y * w_y - radius * radius) * edge_len_sq -
          w_dot_e * w_dot_e) *
           a;
  if (disc < *(float *)0x2533c0) {
    return 0;
  }

  sqrt_disc = sqrtf(disc);
  inv_a = *(float *)0x2533c8 / a;
  t0 = -(b + sqrt_disc) * inv_a;
  if (t0 > *(float *)0x2533c8) {
    return 0;
  }
  t1 = -(b - sqrt_disc) * inv_a;
  if (t1 < *(float *)0x2533c0) {
    return 0;
  }

  if (t0 < *(float *)0x2533c0) {
    t = *(float *)0x2533c0;
  } else {
    t = t0;
  }

  u_num = e_dot_d * t + w_dot_e;
  if (u_num < *(float *)0x2533c0) {
    if (!FUN_00148370(origin, edge_a, direction, out_t, radius)) {
      return 0;
    }
    *out_u = *(float *)0x2533c0;
    return 1;
  }
  if (u_num > edge_len_sq) {
    end_pt[0] = edge_a[0] + edge_delta[0];
    end_pt[1] = edge_a[1] + edge_delta[1];
    end_pt[2] = edge_a[2] + edge_delta[2];
    if (!FUN_00148370(origin, end_pt, direction, out_t, radius)) {
      return 0;
    }
    *out_u = *(float *)0x2533c8;
    return 1;
  }

  *out_t = t;
  *out_u = u_num / edge_len_sq;
  return 1;
}


/* -------------------------------------------------------------------------
 * FUN_001491d0 (0x1491d0) — test one surface's edges as pill segments.
 *
 * XBE: state@esi, surface_index stack. State: +0 bsp, +4 origin*, +8 dir*,
 * +0xc radius (float), +0x10 result*. Walks surface edges; on hit fills
 * result t/normal/surface. ported:false until verified.
 * ------------------------------------------------------------------------- */
typedef struct collision_bsp_edge_test_state {
  int bsp;
  float *origin;
  float *direction;
  float radius;
  float *result;
} collision_bsp_edge_test_state;

char FUN_001491d0(void *state_v, int surface_index)
{
  collision_bsp_edge_test_state *state;
  char *surface;
  int first_edge;
  int edge_index;
  int *edge;
  int side;
  float *vert0;
  float *vert1;
  float edge_delta[3];
  float t;
  float u;
  float *result;
  float *origin;
  float *direction;
  float hit_pos[3];
  float nx, ny, nz, len;
  char hit;

  state = (collision_bsp_edge_test_state *)state_v;
  hit = 0;
  surface =
    (char *)tag_block_get_element((char *)state->bsp + 0x3c, surface_index, 0xc);
  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  origin = state->origin;
  direction = state->direction;
  result = state->result;

  do {
    edge = (int *)tag_block_get_element((char *)state->bsp + 0x48, edge_index,
                                        0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)state->bsp + 0x54, edge[side],
                                           0x10);
    vert1 = (float *)tag_block_get_element((char *)state->bsp + 0x54,
                                           edge[!side], 0x10);
    edge_delta[0] = vert1[0] - vert0[0];
    edge_delta[1] = vert1[1] - vert0[1];
    edge_delta[2] = vert1[2] - vert0[2];

    if (FUN_00148910(&t, origin, vert0, direction, edge_delta, state->radius,
                     &u)) {
      /* keep hit only if t < result[0] (current best) */
      if (result[0] > t) {
        result[0] = t;
        hit_pos[0] = direction[0] * t + origin[0];
        hit_pos[1] = direction[1] * t + origin[1];
        hit_pos[2] = direction[2] * t + origin[2];
        /* normal ≈ hit_pos - point_on_edge */
        nx = hit_pos[0] - (vert0[0] + edge_delta[0] * u);
        ny = hit_pos[1] - (vert0[1] + edge_delta[1] * u);
        nz = hit_pos[2] - (vert0[2] + edge_delta[2] * u);
        len = sqrtf(nx * nx + ny * ny + nz * nz);
        if (!(len < (float)*(double *)0x2533d0)) {
          nx *= *(float *)0x2533c8 / len;
          ny *= *(float *)0x2533c8 / len;
          nz *= *(float *)0x2533c8 / len;
        }
        result[1] = nx;
        result[2] = ny;
        result[3] = nz;
        *(int *)((char *)result + 0x10) = 0x7f7fffff; /* +inf marker */
        *(int *)((char *)result + 0x14) = surface_index;
        *(short *)((char *)result + 0x1a) = *(short *)(surface + 0xa);
        hit = 1;
      }
    }

    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  return hit;
}


/* -------------------------------------------------------------------------
 * FUN_00148240 (0x148240) — two-sided / breakable surface acceptance.
 *
 * XBE ABI: bsp @<eax>; stack = flags, breakable_surfaces, surface_index,
 * projection, sign, point2d. Returns 1 if point2d is inside the projected
 * surface polygon (all edge crosses <= 0) and breakable bit allows it.
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
char FUN_00148240(int bsp, unsigned short flags, int breakable_surfaces,
                  int surface_index, int projection, int sign, float *point2d)
{
  char *surface;
  unsigned char breakable_index;
  int bit;
  int word;
  int first_edge;
  int edge_index;
  int *edge;
  int side;
  float *vert0;
  float *vert1;
  float proj0[2];
  float proj1[2];
  float dx, dy, ex, ey, cross;

  surface = (char *)tag_block_get_element((char *)bsp + 0x3c, surface_index, 0xc);

  /* surface flags bit 3 (0x8): breakable — require bit set in bitset */
  if ((surface[8] & 8) != 0) {
    breakable_index = (unsigned char)surface[9];
    if ((int)breakable_index < (short)flags) {
      bit = 1 << (breakable_index & 0x1f);
      word = (int)(breakable_index >> 5);
      if ((((int *)breakable_surfaces)[word] & bit) == 0) {
        return 0;
      }
    }
  }

  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((char *)bsp + 0x48, edge_index, 0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[side], 0x10);
    vert1 = (float *)tag_block_get_element((char *)bsp + 0x54, edge[!side],
                                           0x10);
    FUN_00061df0(vert0, (short)projection, (unsigned char)sign, proj0);
    FUN_00061df0(vert1, (short)projection, (unsigned char)sign, proj1);

    dx = point2d[0] - proj0[0];
    dy = point2d[1] - proj0[1];
    ex = proj1[0] - proj0[0];
    ey = proj1[1] - proj0[1];
    /* x87: fmul/fxch/fsubp → ey*dx - ex*dy; fail iff > 0 */
    cross = ey * dx - ex * dy;
    if (cross > *(float *)0x2533c0) {
      return 0;
    }

    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  return 1;
}


/* -------------------------------------------------------------------------
 * collision_bsp_test_vector (0x149480) + FUN_00148eb0 (0x148eb0)
 *
 * Ray/segment test against a collision BSP. Wrapper builds a 0x28-byte state
 * and calls the recursive walker at node 0 with t in [0, scale].
 *
 * State layout (wrapper stack at 0x149480):
 *   +0x00 int     collision_flags
 *   +0x04 int     bsp
 *   +0x08 uint16  flags
 *   +0x0c int     breakable_surfaces
 *   +0x10 float*  origin
 *   +0x14 float*  direction
 *   +0x18 float*  result
 *   +0x1c int     last_leaf
 *   +0x20 uint8   leaf_side
 *   +0x24 int     plane_index
 *
 * Marked ported:false in kb.json until VC71 / equivalence sign-off.
 * ------------------------------------------------------------------------- */

typedef struct collision_bsp_vector_state {
  int collision_flags;
  int bsp;
  unsigned short flags;
  unsigned short pad_u16;
  int breakable_surfaces;
  float *origin;
  float *direction;
  float *result;
  int last_leaf;
  unsigned char leaf_side;
  unsigned char pad_u8[3];
  int plane_index;
} collision_bsp_vector_state;

static void collision_bsp_vector_remember_leaf(collision_bsp_vector_state *state,
                                              int leaf_index,
                                              unsigned char leaf_class)
{
  int *result_i;
  int count;

  if (leaf_index != -1) {
    result_i = (int *)state->result;
    count = result_i[5];
    if (count < 0x100) {
      result_i[6 + count] = leaf_index;
      result_i[5] = count + 1;
    } else {
      result_i[0x105] = leaf_index;
    }
  }
  state->last_leaf = leaf_index;
  state->leaf_side = leaf_class;
}


/* 0x148780 — leaf plane-ref walk → 2D BSP surface index.
 * XBE ABI: leaf_index @<eax>; reverse thunk → cdecl first arg (see
 * docs/references/abi-and-calling-conventions.md). Returns surface or -1.
 * ported:false until verified. */
int FUN_00148780(int leaf_index, int bsp, unsigned short flags,
                 int breakable_surfaces, float *origin, float *direction,
                 int plane_index, float t, int two_sided)
{
  short *leaf;
  int ref_i;
  int ref_end;
  int *ref;
  float *plane;
  int axis;
  int sign;
  float point[3];
  float point2d[2];
  uint32_t surface_index;
  float ax, ay, az;
  int high;
  int pos;

  leaf = (short *)tag_block_get_element((char *)bsp + 0x18, leaf_index, 8);
  ref_i = *(int *)(leaf + 2); /* leaf[+4] as int — first bsp2d ref */
  ref_end = ref_i + leaf[1];  /* leaf[+2] ref count (int16) */

  for (; ref_i < ref_end; ref_i++) {
    ref = (int *)tag_block_get_element((char *)bsp + 0x24, ref_i, 8);
    if ((ref[0] & 0x7fffffff) != plane_index) {
      continue;
    }

    plane = (float *)tag_block_get_element((char *)bsp + 0xc, plane_index, 0x10);
    ax = xbox_fabsf(plane[0]);
    ay = xbox_fabsf(plane[1]);
    az = xbox_fabsf(plane[2]);
    /* Same branch shape as breakable_surfaces / XBE fcom chain */
    if (az < ay || az < ax) {
      if (ay < ax)
        axis = 0;
      else
        axis = 1;
    } else {
      axis = 2;
    }

    /* fcomp [0x2533c0]; test ah,41h / jne → pos=0 when plane[axis] <= 0 */
    pos = 1;
    if (plane[axis] <= *(float *)0x2533c0)
      pos = 0;
    /* neg/sbb/neg of high bit → 0/1; setne vs pos */
    high = (ref[0] & 0x80000000) ? 1 : 0;
    sign = (pos != high) ? 1 : 0;

    point[0] = direction[0] * t + origin[0];
    point[1] = direction[1] * t + origin[1];
    point[2] = direction[2] * t + origin[2];

    FUN_00061df0(point, (short)axis, (unsigned char)sign, point2d);
    surface_index = FUN_00146d40((char *)bsp + 0x30, point2d, ref[1]);

    if (!two_sided) {
      return (int)surface_index;
    }
    /* bsp @<eax> — forward thunk / cdecl first arg */
    if (FUN_00148240(bsp, flags, breakable_surfaces, (int)surface_index, axis,
                     sign, point2d)) {
      return (int)surface_index;
    }
  }
  return -1;
}

char FUN_00148eb0(void *state_v, int node_index, float t0, float t1)
{
  collision_bsp_vector_state *state;
  uint32_t *node;
  float *plane;
  float *origin;
  float *direction;
  float d0;
  float dir_dot;
  float d_t0;
  float d_t1;
  char back_touch;
  char front_touch;
  char dir_positive;
  float t_split;
  int child;
  int leaf_index;
  unsigned char leaf_class;
  unsigned char leaf_flags;
  int surface_index;
  char *surface;
  char *result_b;
  int two_sided;
  int flags;

  state = (collision_bsp_vector_state *)state_v;

  if (node_index >= 0) {
    node = (uint32_t *)tag_block_get_element((void *)state->bsp, node_index,
                                             0xc);
    plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                           (int)node[0], 0x10);
    origin = state->origin;
    direction = state->direction;

    d0 = (plane[1] * origin[1] + plane[2] * origin[2] + plane[0] * origin[0]) -
         plane[3];
    dir_dot = plane[1] * direction[1] + plane[2] * direction[2] +
              plane[0] * direction[0];
    d_t0 = dir_dot * t0 + d0;
    d_t1 = dir_dot * t1 + d0;

    /* cl = back (any d < 0); al = front (any d >= 0) — see asm 0x148f32 */
    back_touch =
      (char)(d_t0 < *(float *)0x2533c0 || d_t1 < *(float *)0x2533c0);
    front_touch =
      (char)(d_t0 >= *(float *)0x2533c0 || d_t1 >= *(float *)0x2533c0);

    if (back_touch && front_touch) {
      dir_positive = (char)(dir_dot > *(float *)0x2533c0);
      t_split = -(d0 / dir_dot);
      /* near = back when dir_dot > 0, else front */
      child = (int)node[1 + (dir_positive ? 0 : 1)];
      if (FUN_00148eb0(state, child, t0, t_split)) {
        return 1;
      }
      /* continue far only if result[0] > t_split (asm test ah,41h / jnp) */
      if (!(state->result[0] > t_split)) {
        return 0;
      }
      state->plane_index = (int)node[0];
      child = (int)node[1 + (dir_positive ? 1 : 0)];
      return FUN_00148eb0(state, child, t_split, t1) ? 1 : 0;
    }

    child = (int)node[1 + (front_touch ? 1 : 0)];
    return FUN_00148eb0(state, child, t0, t1) ? 1 : 0;
  }

  /* ---- leaf / solid terminal (node_index < 0) ---- */
  leaf_index = -1;
  leaf_class = 3;
  two_sided = 0;
  surface_index = -1;
  flags = state->collision_flags;

  if (node_index != -1) {
    leaf_index = node_index & 0x7fffffff;
    leaf_flags = *(unsigned char *)tag_block_get_element(
      (char *)state->bsp + 0x18, leaf_index, 8);
    leaf_class = (unsigned char)(((leaf_flags & 1) != 0) + 1);
  }

  if ((flags & 1) != 0 &&
      (state->leaf_side == 1 || state->leaf_side == 2) && leaf_class == 3) {
    surface_index = state->last_leaf;
  } else if ((flags & 2) != 0 && state->leaf_side == 3 &&
             (leaf_class == 1 || leaf_class == 2)) {
    surface_index = leaf_index;
  } else if ((flags & 4) == 0 && state->leaf_side == 2 && leaf_class == 2) {
    if ((flags & 1) != 0) {
      surface_index = state->last_leaf;
    } else {
      surface_index = leaf_index;
    }
    two_sided = 1;
  } else {
    collision_bsp_vector_remember_leaf(state, leaf_index, leaf_class);
    return 0;
  }

  if (surface_index == -1) {
    collision_bsp_vector_remember_leaf(state, leaf_index, leaf_class);
    return 0;
  }

  surface_index = FUN_00148780(
    surface_index, state->bsp, state->flags, state->breakable_surfaces,
    state->origin, state->direction, state->plane_index, t0, two_sided);
  if (surface_index == -1) {
    collision_bsp_vector_remember_leaf(state, leaf_index, leaf_class);
    return 0;
  }

  surface = (char *)tag_block_get_element((char *)state->bsp + 0x3c,
                                          surface_index, 0xc);
  if ((surface[8] & 2) != 0 && (flags & 8) != 0) {
    collision_bsp_vector_remember_leaf(state, leaf_index, leaf_class);
    return 0;
  }
  if ((surface[8] & 8) != 0 && (flags & 0x10) != 0) {
    collision_bsp_vector_remember_leaf(state, leaf_index, leaf_class);
    return 0;
  }

  result_b = (char *)state->result;
  *(float *)result_b = t0;
  plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                         state->plane_index, 0x10);
  *(float **)(result_b + 4) = plane;
  *(int *)(result_b + 8) = surface_index;
  *(int *)(result_b + 0xc) = *(int *)surface;
  result_b[0x10] = surface[8];
  result_b[0x11] = surface[9];
  *(short *)(result_b + 0x12) = *(short *)(surface + 0xa);
  return 1;
}

char collision_bsp_test_vector(int collision_flags, int bsp, short flags,
                               int breakable_surfaces, int origin, int direction,
                               float max_t, float *result)
{
  collision_bsp_vector_state state;
  short log_fn;
  float scale;
  char hit;

  log_fn = (short)(4 + (bsp == *(int *)0x5064dc ? 1 : 0));
  collision_log_add_call(log_fn);
  collision_log_query_counter((void *)0x46f090);

  state.collision_flags = collision_flags;
  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.direction = (float *)direction;
  state.result = result;
  state.last_leaf = -1;
  state.leaf_side = 0;
  state.plane_index = -1;

  /* fcomp [0x2533c0]; test ah,5 / jp: result = max_t when max_t >= 0, else 0 */
  if (max_t < *(float *)0x2533c0) {
    result[0] = *(float *)0x2533c0;
  } else {
    result[0] = max_t;
  }
  *(int *)((char *)result + 0x14) = 0;

  /* scale / t1: max_t < 0 → 0; max_t > 1 → 1; else max_t
   * (fcomp 0x2533c0 / 0x2533c8; test ah,5 / ah,41h) */
  if (max_t < *(float *)0x2533c0) {
    scale = *(float *)0x2533c0;
  } else if (max_t > *(float *)0x2533c8) {
    scale = *(float *)0x2533c8;
  } else {
    scale = max_t;
  }

  hit = FUN_00148eb0(&state, 0, *(float *)0x2533c0, scale);
  collision_log_add_time(log_fn, *(unsigned int *)0x46f090, *(int *)0x46f094);
  return hit;
}


/* -------------------------------------------------------------------------
 * Sphere path: collision_bsp_test_sphere (0x1493b0) +
 * bsp3d_test_sphere_recursive (0x148b90) + FUN_001486e0 (0x1486e0).
 *
 * State layout (wrapper stack, size 0x228):
 *   +0x00 bsp, +0x04 flags, +0x08 breakable_surfaces, +0x0c origin*,
 *   +0x10 radius, +0x14 results*, +0x18 plane_stack_count,
 *   +0x1c plane_stack[0x80], +0x21c projection, +0x21e sign,
 *   +0x220 point2d[2].
 * Results: counts at +0, +0x404, +0x808; leaf list count at +0xc0c.
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
typedef struct collision_bsp_sphere_state {
  int bsp;
  unsigned short flags;
  unsigned short pad0;
  int breakable_surfaces;
  float *origin;
  float radius;
  int *results;
  int plane_stack_count;
  int plane_stack[0x80];
  short projection;
  unsigned char sign;
  unsigned char pad1;
  float point2d[2];
} collision_bsp_sphere_state;


/* -------------------------------------------------------------------------
 * FUN_00147ed0 (0x147ed0) — sphere vs one surface (verts / edges / interior).
 *
 * XBE: state @<eax>, surface_index stack. Records hits into results buckets:
 *   +0 surface indices, +0x404 edge indices, +0x808 vertex indices.
 * Calls fast_vector_intersects_sphere on edges. ported:false until verified.
 * ------------------------------------------------------------------------- */
void FUN_00147ed0(void *state_v, int surface_index)
{
  collision_bsp_sphere_state *state;
  char *surface;
  unsigned char breakable_index;
  int bit;
  int *breakable;
  float radius_sq;
  int first_edge;
  int edge_index;
  int *edge;
  int side;
  float *vert;
  float *vert0;
  float *vert1;
  float *origin;
  float edge_delta[3];
  float dx, dy, dz;
  float dist_sq;
  int *results;
  int count;
  int i;
  char hit;
  float proj0[2];
  float proj1[2];
  float cross;
  float ex, ey;

  state = (collision_bsp_sphere_state *)state_v;
  surface =
    (char *)tag_block_get_element((char *)state->bsp + 0x3c, surface_index, 0xc);

  if ((surface[8] & 8) != 0) {
    breakable_index = (unsigned char)surface[9];
    if ((int)breakable_index < (int)state->flags) {
      breakable = (int *)state->breakable_surfaces;
      bit = 1 << (breakable_index & 0x1f);
      if ((breakable[breakable_index >> 5] & bit) == 0) {
        return;
      }
    }
  }

  radius_sq = state->radius * state->radius;
  hit = 0;
  first_edge = *(int *)(surface + 4);
  edge_index = first_edge;
  origin = state->origin;
  results = state->results;

  do {
    edge = (int *)tag_block_get_element((char *)state->bsp + 0x48, edge_index,
                                        0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert = (float *)tag_block_get_element((char *)state->bsp + 0x54, edge[side],
                                          0x10);
    dx = vert[0] - origin[0];
    dy = vert[1] - origin[1];
    dz = vert[2] - origin[2];
    dist_sq = dx * dx + dy * dy + dz * dz;
    if (!(dist_sq > radius_sq)) {
      count = results[0x808 / 4];
      for (i = 0; i < count; i++) {
        if (results[0x80c / 4 + i] == edge[side]) {
          break;
        }
      }
      if (i >= count && count < 0x100) {
        results[0x80c / 4 + count] = edge[side];
        results[0x808 / 4] = count + 1;
      }
      hit = 1;
    }
    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((char *)state->bsp + 0x48, edge_index,
                                        0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)state->bsp + 0x54, edge[side],
                                           0x10);
    vert1 = (float *)tag_block_get_element((char *)state->bsp + 0x54,
                                           edge[!side], 0x10);
    edge_delta[0] = vert1[0] - vert0[0];
    edge_delta[1] = vert1[1] - vert0[1];
    edge_delta[2] = vert1[2] - vert0[2];
    if (fast_vector_intersects_sphere(vert0, edge_delta, origin, state->radius)) {
      count = results[0x404 / 4];
      for (i = 0; i < count; i++) {
        if (results[0x408 / 4 + i] == edge_index) {
          break;
        }
      }
      if (i >= count && count < 0x100) {
        results[0x408 / 4 + count] = edge_index;
        results[0x404 / 4] = count + 1;
      }
      hit = 1;
    }
    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

  if (hit) {
    goto record_surface;
  }

  edge_index = first_edge;
  do {
    edge = (int *)tag_block_get_element((char *)state->bsp + 0x48, edge_index,
                                        0x18);
    side = (edge[5] == surface_index) ? 1 : 0;
    vert0 = (float *)tag_block_get_element((char *)state->bsp + 0x54, edge[side],
                                           0x10);
    vert1 = (float *)tag_block_get_element((char *)state->bsp + 0x54,
                                           edge[!side], 0x10);
    FUN_00061df0(vert0, state->projection, state->sign, proj0);
    FUN_00061df0(vert1, state->projection, state->sign, proj1);
    dx = state->point2d[0] - proj0[0];
    dy = state->point2d[1] - proj0[1];
    ex = proj1[0] - proj0[0];
    ey = proj1[1] - proj0[1];
    cross = ey * dx - ex * dy;
    if (cross > *(float *)0x2533c0) {
      return;
    }
    edge_index = edge[2 + side];
  } while (edge_index != first_edge);

record_surface:
  count = results[0];
  for (i = 0; i < count; i++) {
    if (results[1 + i] == surface_index) {
      return;
    }
  }
  if (count < 0x100) {
    results[1 + count] = surface_index;
    results[0] = count + 1;
  }
}

void FUN_001486e0(void *state_v, int node_index)
{
  collision_bsp_sphere_state *state;
  float *node;
  float d;
  char front_hit;
  char back_hit;

  state = (collision_bsp_sphere_state *)state_v;
  if (node_index < 0) {
    FUN_00147ed0(state, node_index & 0x7fffffff);
    return;
  }

  node = (float *)tag_block_get_element((char *)state->bsp + 0x30, node_index,
                                        0x14);
  d = node[1] * state->point2d[1] + state->point2d[0] * node[0] - node[2];

  /* d < radius → front child may hit */
  if (d < state->radius) {
    front_hit = 1;
  } else {
    front_hit = 0;
  }
  /* d > -radius → back child may hit (test ah,1 after fcompp vs -radius) */
  if (d > -state->radius) {
    back_hit = 1;
  } else {
    back_hit = 0;
  }

  if (front_hit) {
    FUN_001486e0(state, *(int *)((char *)node + 0xc));
  }
  if (back_hit) {
    FUN_001486e0(state, *(int *)((char *)node + 0x10));
  }
}

void bsp3d_test_sphere_recursive(void *state_v, int node_index)
{
  collision_bsp_sphere_state *state;
  int *bsp3d_node;
  float *plane;
  float *origin;
  float d;
  char near_front;
  char al;
  int child;
  short *leaf;
  int ref_i;
  int ref_end;
  int *ref;
  int plane_index;
  int i;
  int *results;
  float proj_pt[3];
  int axis;
  int high;
  int pos;
  float ax, ay, az;

  state = (collision_bsp_sphere_state *)state_v;

node_loop:
  if (node_index < 0) {
    goto leaf_path;
  }

  bsp3d_node =
    (int *)tag_block_get_element((char *)state->bsp, node_index, 0xc);
  plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                         bsp3d_node[0], 0x10);
  origin = state->origin;
  d = origin[2] * plane[2] + origin[1] * plane[1] + origin[0] * plane[0] -
      plane[3];

  /* near_front (cl): d < radius */
  near_front = (d < state->radius) ? 1 : 0;

  /* if d <= -radius → only child +4 (al=0); else if straddling both; else +8 */
  if (!(d > -state->radius)) {
    al = 0;
    goto pick_child;
  }
  if (near_front) {
    /* straddling: push plane with high bit, recurse front, then back */
    if (state->plane_stack_count < 0 || state->plane_stack_count >= 0x80) {
      display_assert((const char *)0x29cb24, (const char *)0x29cafc, 0x206, 1);
      system_exit(-1);
    }
    state->plane_stack[state->plane_stack_count] =
      bsp3d_node[0] | (int)0x80000000;
    state->plane_stack_count++;
    bsp3d_test_sphere_recursive(state, bsp3d_node[1]);
    state->plane_stack_count--;

    if (state->plane_stack_count < 0 || state->plane_stack_count >= 0x80) {
      display_assert((const char *)0x29cb24, (const char *)0x29cafc, 0x210, 1);
      system_exit(-1);
    }
    state->plane_stack[state->plane_stack_count] =
      bsp3d_node[0] & 0x7fffffff;
    state->plane_stack_count++;
    bsp3d_test_sphere_recursive(state, bsp3d_node[2]);
    state->plane_stack_count--;
    return;
  }
  al = 1;

pick_child:
  child = bsp3d_node[al + 1];
  node_index = child;
  if (node_index >= 0) {
    goto node_loop;
  }

leaf_path:
  if (node_index == -1) {
    return;
  }

  node_index &= 0x7fffffff;
  results = state->results;
  if (results[0xc0c / 4] < 0x100) {
    results[0xc10 / 4 + results[0xc0c / 4]] = node_index;
    results[0xc0c / 4]++;
  }

  leaf = (short *)tag_block_get_element((char *)state->bsp + 0x18, node_index,
                                        8);
  ref_i = *(int *)(leaf + 2);
  ref_end = ref_i + leaf[1];
  for (; ref_i < ref_end; ref_i++) {
    ref = (int *)tag_block_get_element((char *)state->bsp + 0x24, ref_i, 8);
    /* match plane against stack */
    if (state->plane_stack_count <= 0) {
      continue;
    }
    plane_index = ref[0];
    for (i = 0; i < state->plane_stack_count; i++) {
      if (state->plane_stack[i] == plane_index) {
        break;
      }
    }
    if (i >= state->plane_stack_count) {
      continue;
    }

    /* project origin onto leaf plane → point2d, then 2D BSP */
    plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                           plane_index & 0x7fffffff, 0x10);
    origin = state->origin;
    d = -(origin[1] * plane[1] + origin[2] * plane[2] + origin[0] * plane[0] -
          plane[3]);
    proj_pt[0] = d * plane[0] + origin[0];
    proj_pt[1] = d * plane[1] + origin[1];
    proj_pt[2] = d * plane[2] + origin[2];

    ax = xbox_fabsf(plane[0]);
    ay = xbox_fabsf(plane[1]);
    az = xbox_fabsf(plane[2]);
    if (az >= ay && az >= ax) {
      axis = 2;
    } else if (ay >= ax) {
      axis = 1;
    } else {
      axis = 0;
    }
    pos = (plane[axis] > *(float *)0x2533c0) ? 1 : 0;
    high = (ref[0] & (int)0x80000000) ? 1 : 0;
    state->projection = (short)axis;
    state->sign = (unsigned char)(pos != high);
    FUN_00061df0(proj_pt, (short)axis, state->sign, state->point2d);
    FUN_001486e0(state, ref[1]);
  }
}

int collision_bsp_test_sphere(int bsp, short flags, int breakable_surfaces,
                              int origin, float radius, int *results)
{
  collision_bsp_sphere_state state;
  short log_fn;

  log_fn = (short)(6 + (bsp == *(int *)0x5064dc ? 1 : 0));
  collision_log_add_call(log_fn);
  collision_log_query_counter((void *)0x46f098);

  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.pad0 = 0;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.radius = radius;
  state.results = results;
  state.plane_stack_count = 0;
  state.projection = 0;
  state.sign = 0;

  results[0xc0c / 4] = 0;
  results[0] = 0;
  results[0x404 / 4] = 0;
  results[0x808 / 4] = 0;

  bsp3d_test_sphere_recursive(&state, 0);
  collision_log_add_time(log_fn, *(unsigned int *)0x46f098, *(int *)0x46f09c);

  if (results[0] > 0 || results[0x404 / 4] > 0) {
    return 1;
  }
  return 0;
}


/* -------------------------------------------------------------------------
 * FUN_00147380 (0x147380) — thin wrapper: FUN_001470b0 with flags = -1.
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
int FUN_00147380(int tag_base, uint32_t node_index, float *verts, int counts,
                 float epsilon,
                 void (*callback)(float *, int, unsigned int, unsigned int,
                                  void *),
                 void *ctx)
{
  return FUN_001470b0(tag_base, node_index, (uint32_t)-1, verts, counts, epsilon,
                      callback, ctx);
}

/* -------------------------------------------------------------------------
 * Pill path: collision_bsp_test_pill_new (0x148b20) + FUN_00148440 (0x148440)
 * + FUN_00149570 (0x149570) 2D BSP → FUN_001491d0.
 *
 * Pill state (wrapper stack):
 *   +0 bsp, +4 flags, +8 breakable, +0xc origin*, +0x10 direction*,
 *   +0x14 radius, +0x18 result*, +0x1c normal*, +0x20 unused0,
 *   +0x24 leaf_side?, +0x28 plane_index (-1).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */
typedef struct collision_bsp_pill_state {
  int bsp;
  unsigned short flags;
  unsigned short pad0;
  int breakable_surfaces;
  float *origin;
  float *direction;
  float radius;
  float *result;
  float *normal_out;
  int field_20;
  unsigned char leaf_side;
  unsigned char pad1[3];
  int plane_index;
} collision_bsp_pill_state;

char FUN_00148440(void *state_v, int node_index, float t0, float t1)
{
  collision_bsp_pill_state *state;
  int *bsp3d_node;
  float *plane;
  float *origin;
  float *direction;
  float d0, d1, d_end;
  float neg_r;
  char front_open;
  char back_open;
  char hit_a;
  char hit_b;
  int child;
  float t_near, inv, t_enter, t_leave;
  float *result;
  float *normal;
  int plane_idx;
  char dir_pos;

  state = (collision_bsp_pill_state *)state_v;

node_loop:
  if (node_index < 0) {
    goto leaf;
  }

  bsp3d_node =
    (int *)tag_block_get_element((char *)state->bsp, node_index, 0xc);
  plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                         bsp3d_node[0], 0x10);
  origin = state->origin;
  direction = state->direction;
  d0 = origin[2] * plane[2] + origin[1] * plane[1] + origin[0] * plane[0] -
       plane[3];
  /* dir·n stored then endpoints */
  d_end = direction[2] * plane[2] + direction[1] * plane[1] +
          direction[0] * plane[0];
  /* ebp+0xc overwritten with d_end in asm; d at t1 = d_end*t1 + d0 */
  d1 = d_end * t1 + d0;
  /* front_open if d0 < radius OR d1 < radius */
  front_open = 0;
  if (d0 < state->radius || d1 < state->radius) {
    front_open = 1;
  }
  neg_r = -state->radius;
  /* both endpoints <= -radius → closed on back; else open */
  back_open = 1;
  if (d0 <= neg_r && d1 <= neg_r) {
    back_open = 0;
  }

  if (front_open && back_open) {
    goto straddle;
  }

  child = bsp3d_node[(back_open ? 1 : 0) + 1];
  node_index = child;
  if (node_index >= 0) {
    goto node_loop;
  }

leaf:
  if (node_index != -1) {
    return 0;
  }
  plane_idx = state->plane_index;
  if (plane_idx == -1) {
    return 0;
  }
  plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                         plane_idx & 0x7fffffff, 0x10);
  result = state->result;
  normal = state->normal_out;
  *result = t0;
  if (plane_idx < 0) {
    normal[0] = -plane[0];
    normal[1] = -plane[1];
    normal[2] = -plane[2];
  } else {
    normal[0] = plane[0];
    normal[1] = plane[1];
    normal[2] = plane[2];
  }
  return 1;

straddle:
  /* clip t interval against expanded plane slab ± radius */
  /* d_end == 0 → parallel special */
  if (d_end == *(float *)0x2533c0) {
    t_enter = t1;
    t_leave = t0;
  } else {
    inv = *(float *)0x2533c8 / d_end;
    t_enter = -((d0 + state->radius) * inv);
    t_leave = -((d0 - state->radius) * inv);
    if (t_enter > t_leave) {
      t_near = t_enter;
      t_enter = t_leave;
      t_leave = t_near;
    }
  }
  /* clamp enter/leave into [t0,t1] */
  if (t_enter < t0) {
    t_enter = t0;
  }
  if (t_enter > t1) {
    t_enter = t1;
  }
  if (t_leave < t0) {
    /* empty — only far side? asm sets leave=t0 enter=t1 paths */
    t_leave = t0;
  }
  if (t_leave > t1) {
    t_leave = t1;
  }

  /* near child first: child index by !(d_end > 0) → sete on bl where bl=(d_end>0) */
  dir_pos = (d_end > *(float *)0x2533c0) ? 1 : 0;
  {
    child = bsp3d_node[(!dir_pos) + 1];
    hit_a = FUN_00148440(state, child, t0, t_enter);
    if (hit_a) {
      if (!(state->result[0] < t_leave)) {
        /* keep searching far if hit t >= leave */
        t1 = state->result[0];
      } else {
        return 1;
      }
    }
    state->plane_index = bsp3d_node[0];
    if (dir_pos) {
      state->plane_index |= (int)0x80000000;
    } else {
      state->plane_index &= 0x7fffffff;
    }
    child = bsp3d_node[dir_pos + 1];
    hit_b = FUN_00148440(state, child, t_leave, t1);
    return (char)(hit_b | hit_a);
  }
}

char collision_bsp_test_pill_new(int bsp, short flags, int breakable_surfaces,
                                 int origin, int direction, float radius,
                                 float *result, float *normal_out)
{
  collision_bsp_pill_state state;
  char hit;

  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.pad0 = 0;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.direction = (float *)direction;
  state.radius = radius;
  state.result = result;
  state.normal_out = normal_out;
  state.field_20 = -1;
  state.leaf_side = 0;
  state.plane_index = -1;
  *(unsigned int *)result = 0x7f7fffff;

  hit = FUN_00148440(&state, 0, *(float *)0x2533c0, *(float *)0x2533c8);
  return hit;
}

/* FUN_00149570 — 2D BSP node walk for pill; leaf → FUN_001491d0.
 * Uses point2d at +0x21c/+0x220/+0x224/+0x228 and radius at +0xc (pill edge state).
 * For our edge-test state layout this is the collision_bsp_edge_test_state
 * extended; keep using void* and offsets matching XBE. */
char FUN_00149570(void *state_v, int node_index)
{
  char *state;
  float *node;
  float d0, d1;
  float rad, eps;
  float neg;
  char front_hit;
  char back_hit;
  char hit;

  state = (char *)state_v;
  if (node_index < 0) {
    hit = FUN_001491d0(state_v, node_index & 0x7fffffff);
    return hit;
  }

  node = (float *)tag_block_get_element((char *)(*(int *)state) + 0x30,
                                        node_index, 0x14);
  /* point2d at +0x21c (x) and +0x220 (y); direction2d at +0x224/+0x228 */
  d0 = *(float *)(state + 0x220) * node[1] +
       *(float *)(state + 0x21c) * node[0] - node[2];
  d1 = *(float *)(state + 0x228) * node[1] +
       *(float *)(state + 0x224) * node[0] + d0;

  rad = *(float *)(state + 0xc);
  eps = *(float *)0x29cb64;
  front_hit = 0;
  if (d0 < rad + eps || d1 < rad + eps) {
    front_hit = 1;
  }
  neg = -(rad)-eps;
  back_hit = 1;
  if (d0 <= neg && d1 <= neg) {
    back_hit = 0;
  }

  if (front_hit) {
    if (FUN_00149570(state_v, *(int *)((char *)node + 0xc))) {
      return 1;
    }
  }
  if (back_hit) {
    if (FUN_00149570(state_v, *(int *)((char *)node + 0x10))) {
      return 1;
    }
  }
  return 0;
}


/* -------------------------------------------------------------------------
 * FUN_00149680 (0x149680) — pill BSP recursive walker (vector+radius).
 *
 * Sibling of FUN_00148eb0 for the pill path. State:
 *   +0 bsp, +4 origin*, +8 dir*, +0xc radius, +0x10 result*,
 *   +0x14 plane_stack_count, +0x18 plane_stack[], +0x218 projection,
 *   +0x21a sign, +0x21c… point2d working area.
 * Leaf: project hit → bsp2d surface → FUN_00148240 → fill result; also
 * tries FUN_00149570 on projected origin for edge hits.
 * ported:false — large interim draft; tighten against ASM under VC71.
 * ------------------------------------------------------------------------- */
typedef struct collision_bsp_pill_walk_state {
  int bsp;
  float *origin;
  float *direction;
  float radius;
  float *result;
  int plane_stack_count;
  int plane_stack[0x80];     /* +0x18 .. +0x217 */
  short projection;          /* +0x218 */
  unsigned char sign;        /* +0x21a */
  unsigned char pad2;
  float point2d[2];          /* +0x21c */
  float dir2d[2];            /* +0x224 */
} collision_bsp_pill_walk_state;

char FUN_00149680(void *state_v, int node_index)
{
  collision_bsp_pill_walk_state *state;
  int *bsp3d_node;
  float *plane;
  float *origin;
  float *direction;
  float d0, d_dir, d1;
  float eps, neg;
  char front_open;
  char back_open;
  char hit;
  char dir_pos;
  int child;
  short *leaf;
  int ref_i, ref_end;
  int *ref;
  int i;
  float t;
  float ax, ay, az;
  int axis;
  int high, pos;
  float point[3];
  float point2d[2];
  uint32_t surface_index;
  char *surface;
  float *result;
  float adj;
  float dist;
  float op[3];

  state = (collision_bsp_pill_walk_state *)state_v;
  hit = 0;
  eps = *(float *)0x29ca28;

  if (node_index < 0) {
    goto leaf_path;
  }

  bsp3d_node =
    (int *)tag_block_get_element((char *)state->bsp, node_index, 0xc);
  plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                         bsp3d_node[0], 0x10);
  origin = state->origin;
  direction = state->direction;
  d0 = origin[2] * plane[2] + origin[1] * plane[1] + origin[0] * plane[0] -
       plane[3];
  d_dir = direction[2] * plane[2] + direction[1] * plane[1] +
          direction[0] * plane[0];
  d1 = d_dir + d0;

  front_open = 0;
  if (d0 < state->radius + eps || d1 < state->radius + eps) {
    front_open = 1;
  }
  neg = -state->radius - eps;
  back_open = 1;
  if (d0 <= neg && d1 <= neg) {
    back_open = 0;
  }

  if (front_open && back_open) {
    if (state->plane_stack_count < 0 || state->plane_stack_count >= 0x80) {
      display_assert((const char *)0x29cb24, (const char *)0x29cafc, 0x498, 1);
      system_exit(-1);
    }
    dir_pos = (d_dir > *(float *)0x2533c0) ? 1 : 0;
    state->plane_stack[state->plane_stack_count] =
      dir_pos ? (bsp3d_node[0] | (int)0x80000000)
              : (bsp3d_node[0] & 0x7fffffff);
    state->plane_stack_count++;
    child = bsp3d_node[(!dir_pos) + 1];
    if (FUN_00149680(state, child)) {
      hit = 1;
    }
    state->plane_stack_count--;
    child = bsp3d_node[dir_pos + 1];
    if (FUN_00149680(state, child)) {
      return 1;
    }
    return hit;
  }

  child = bsp3d_node[(back_open ? 1 : 0) + 1];
  if (FUN_00149680(state, child)) {
    return 1;
  }
  return 0;

leaf_path:
  if (node_index == -1) {
    return 0;
  }
  node_index &= 0x7fffffff;
  leaf = (short *)tag_block_get_element((char *)state->bsp + 0x18, node_index,
                                        8);
  ref_i = *(int *)(leaf + 2);
  ref_end = ref_i + leaf[1];
  for (; ref_i < ref_end; ref_i++) {
    ref = (int *)tag_block_get_element((char *)state->bsp + 0x24, ref_i, 8);
    if (state->plane_stack_count <= 0) {
      continue;
    }
    for (i = 0; i < state->plane_stack_count; i++) {
      if (state->plane_stack[i] == ref[0]) {
        break;
      }
    }
    if (i >= state->plane_stack_count) {
      continue;
    }

    plane = (float *)tag_block_get_element((char *)state->bsp + 0xc,
                                           ref[0] & 0x7fffffff, 0x10);
    origin = state->origin;
    direction = state->direction;
    d0 = origin[2] * plane[2] + origin[1] * plane[1] + origin[0] * plane[0] -
         plane[3];
    d_dir = direction[2] * plane[2] + direction[1] * plane[1] +
            direction[0] * plane[0];
    t = *(float *)0x2533c0;
    if (d_dir != *(float *)0x2533c0) {
      t = -(d0) / d_dir;
      /* shrink by radius/|d_dir| */
      adj = xbox_fabsf(d_dir);
      adj = state->radius / adj;
      t = t - adj;
      if (t < *(float *)0x2533c0) {
        t = *(float *)0x2533c0;
      } else if (t > *(float *)0x2533c8) {
        t = *(float *)0x2533c8;
      }
    }
    if (!(state->result[0] > t)) {
      continue;
    }

    ax = xbox_fabsf(plane[0]);
    ay = xbox_fabsf(plane[1]);
    az = xbox_fabsf(plane[2]);
    if (az >= ay && az >= ax) {
      axis = 2;
    } else if (ay >= ax) {
      axis = 1;
    } else {
      axis = 0;
    }
    pos = (plane[axis] > *(float *)0x2533c0) ? 1 : 0;
    high = (ref[0] & (int)0x80000000) ? 1 : 0;
    state->projection = (short)axis;
    state->sign = (unsigned char)(pos != high);

    point[0] = direction[0] * t + origin[0];
    point[1] = direction[1] * t + origin[1];
    point[2] = direction[2] * t + origin[2];
    /* project onto plane then to 2d — simplified: project point */
    dist = -(point[0] * plane[0] + point[1] * plane[1] + point[2] * plane[2] -
             plane[3]);
    point[0] = dist * plane[0] + point[0];
    point[1] = dist * plane[1] + point[1];
    point[2] = dist * plane[2] + point[2];
    FUN_00061df0(point, state->projection, state->sign, point2d);
    surface_index =
      FUN_00146d40((char *)state->bsp + 0x30, point2d, ref[1]);
    if (!FUN_00148240(state->bsp, 0, 0, (int)surface_index, axis,
                      (int)state->sign, point2d)) {
      /* still try edge path below */
    } else {
      surface = (char *)tag_block_get_element((char *)state->bsp + 0x3c,
                                              (int)surface_index, 0xc);
      result = state->result;
      result[0] = t;
      if (ref[0] < 0) {
        result[1] = -plane[0];
        result[2] = -plane[1];
        result[3] = -plane[2];
      } else {
        result[1] = plane[0];
        result[2] = plane[1];
        result[3] = plane[2];
      }
      *(int *)((char *)result + 0x14) = (int)surface_index;
      *(short *)((char *)result + 0x1a) = *(short *)(surface + 0xa);
      hit = 1;
    }

    /* edge test via 2D BSP at projected origin */
    dist = -d0;
    op[0] = dist * plane[0] + origin[0];
    op[1] = dist * plane[1] + origin[1];
    op[2] = dist * plane[2] + origin[2];
    FUN_00061df0(op, state->projection, state->sign, state->point2d);
    state->dir2d[0] = *(float *)0x2533c0;
    state->dir2d[1] = *(float *)0x2533c0;
    if (FUN_00149570(state, ref[1])) {
      hit = 1;
    }
  }
  return hit;
}


/* -------------------------------------------------------------------------
 * Object / structure query wrappers (collision_bsp.obj high addresses).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */

/* 0x14dc30 — point in structure leaf → iterate cluster objects. */
char FUN_0014dc30(int flags, float *pos, int param_3)
{
  void *bsp;
  uint32_t leaf;
  char solid_bit;
  void *scenario;
  void *cluster;
  int obj;
  int iter_state;

  if ((flags & 0xe0) == 0) {
    return 0;
  }

  bsp = FUN_0018e420();
  leaf = bsp3d_find_leaf(bsp, 0, pos);
  solid_bit = (char)((flags >> 7) & 1);
  if (*(unsigned char *)0x4761f8) {
    solid_bit = 0;
  }
  if (leaf == (uint32_t)-1) {
    return 1;
  }
  if (!solid_bit) {
    return 0;
  }

  scenario = scenario_get();
  cluster = tag_block_get_element((char *)scenario + 0xe0, (int)(leaf & 0x7fffffff),
                                  0x10);
  iter_state = 0;
  obj = cluster_partition_object_iter_first(
    &iter_state, *(short *)((char *)cluster + 8));
  while (obj != -1) {
    if (FUN_0014db10(obj, flags, (int)pos, param_3)) {
      return 1;
    }
    obj = cluster_partition_object_iter_next(&iter_state);
  }
  return 0;
}

/* 0x14e7d0 — structure BSP test via FUN_00149c60; fill collision result. */
char FUN_0014e7d0(uint32_t collision_flags, float *point, float *offset_vec,
                  float p4, int unit_handle, void *result_v)
{
  char *result;
  char hit;
  char buf[0x420];
  void *bsp;
  int count;
  int leaf0;
  int leaf1;
  short mat;
  float t;
  float *plane_or;
  unsigned int inf_bits;
  void *scenario;
  void *cluster;

  (void)unit_handle;
  result = (char *)result_v;
  hit = 0;
  *(short *)result = (short)0xffff;
  *(unsigned int *)(result + 0x14) = 0x7f7fffff;
  inf_bits = 0x7f7fffff;

  bsp = global_collision_bsp_get();
  if (FUN_00149c60((int *)bsp, point, offset_vec, p4, *(float *)&inf_bits,
                   (float *)buf)) {
    t = *(float *)buf;
    *(float *)(result + 0x14) = t;
    if ((collision_flags & 0x20) != 0) {
      plane_or = (float *)(buf + 4);
      *(float *)(result + 0x24) = plane_or[0];
      *(float *)(result + 0x28) = plane_or[1];
      *(float *)(result + 0x2c) = plane_or[2];
      *(float *)(result + 0x30) = plane_or[3];
      mat = *(short *)(buf + 0x1a);
      result[0x4c] = 0;
      result[0x4d] = 0;
      *(short *)result = 2;
      *(short *)(result + 0x34) = mat;
      *(int *)(result + 0x44) = *(int *)(buf + 0x14);
      *(int *)(result + 0x48) = -1;
      *(short *)(result + 0x4e) = mat;
      hit = 1;
    }
  }

  count = *(int *)(buf + 0x1c);
  if (count > 0) {
    leaf0 = *(int *)(buf + 0x20);
    *(int *)(result + 4) = leaf0;
    scenario = scenario_get();
    if (leaf0 == -1) {
      mat = 0;
    } else {
      cluster = tag_block_get_element((char *)scenario + 0xe0, leaf0 & 0x7fffffff,
                                      0x10);
      mat = *(short *)((char *)cluster + 8);
    }
    *(short *)(result + 8) = mat;

    leaf1 = *((int *)(buf + 0x1c) + count);
    *(int *)(result + 0xc) = leaf1;
    if (leaf1 == -1) {
      mat = 0;
    } else {
      cluster = tag_block_get_element((char *)scenario + 0xe0, leaf1 & 0x7fffffff,
                                      0x10);
      mat = *(short *)((char *)cluster + 8);
    }
    *(short *)(result + 0x10) = mat;
  }

  if (!hit) {
    *(float *)(result + 0x14) = *(float *)0x2533c8;
  }
  t = *(float *)(result + 0x14);
  *(float *)(result + 0x18) = offset_vec[0] * t + point[0];
  *(float *)(result + 0x1c) = offset_vec[1] * t + point[1];
  *(float *)(result + 0x20) = offset_vec[2] * t + point[2];
  scenario_location_from_point(result + 0x18, result + 0xc);
  return hit;
}

/* 0x14e940 — global structure pill test → fill result. */
char FUN_0014e940(int unused, float *origin, float *direction, float radius,
                  int pad0, int pad1, void *result_v)
{
  char *result;
  float t_slot;
  float normal[3];
  char hit;
  float t;
  void *bsp;

  (void)unused;
  (void)pad0;
  (void)pad1;
  result = (char *)result_v;
  hit = 0;
  *(short *)result = (short)0xffff;
  *(int *)(result + 4) = -1;
  *(short *)(result + 8) = (short)0xffff;
  *(int *)(result + 0xc) = -1;
  *(short *)(result + 0x10) = (short)0xffff;
  *(float *)(result + 0x14) = *(float *)0x2533c8;

  /* pill_new writes t into the stack slot we pass; keep result ptr in `result` */
  t_slot = 0; /* placeholder; address of t_slot passed as float* */
  bsp = global_collision_bsp_get();
  /* Match XBE: pass &stack_slot_for_t — use local t_slot */
  hit = collision_bsp_test_pill_new((int)bsp, 0, 0, (int)origin, (int)direction,
                                    radius, &t_slot, normal);
  if (hit) {
    *(float *)(result + 0x24) = normal[0];
    *(float *)(result + 0x28) = normal[1];
    *(float *)(result + 0x2c) = normal[2];
    *(float *)(result + 0x14) = t_slot;
    *(short *)result = 2;
    *(unsigned int *)(result + 0x30) = 0x7f7fffff;
    *(short *)(result + 0x34) = (short)0xffff;
    *(int *)(result + 0x44) = -1;
    *(int *)(result + 0x48) = -1;
    result[0x4c] = 0;
    result[0x4d] = 0;
    *(short *)(result + 0x4e) = (short)0xffff;
  }

  t = *(float *)(result + 0x14);
  *(float *)(result + 0x18) = direction[0] * t + origin[0];
  *(float *)(result + 0x1c) = direction[1] * t + origin[1];
  *(float *)(result + 0x20) = direction[2] * t + origin[2];
  /* XBE clears normal at +0x24 after computing point — odd but match */
  *(int *)(result + 0x24) = 0;
  *(int *)(result + 0x28) = 0;
  *(int *)(result + 0x2c) = 0;
  return hit;
}


/* 0x14e640 — model collision type-3 path: transform, test, fill result. */
char FUN_0014e640(void *model, float *origin, float *offset, void *result_v)
{
  char *result;
  char *model_b;
  float end_pt[3];
  float neg_dir[3];
  char xform[0x28];
  char hit_buf[0x448];
  int node_base;
  int stride_off;
  short first_idx;
  int plane_src;
  float t;
  char ok;
  short ax_s;

  result = (char *)result_v;
  model_b = (char *)model;
  *(short *)result = (short)0xffff;
  *(unsigned int *)(result + 0x14) = 0x7f7fffff;

  if (*(short *)model_b != 3) {
    return 0;
  }

  end_pt[0] = origin[0] + offset[0];
  end_pt[1] = origin[1] + offset[1];
  end_pt[2] = origin[2] + offset[2];
  neg_dir[0] = -offset[0];
  neg_dir[1] = -offset[1];
  neg_dir[2] = -offset[2];

  ok = (char)FUN_0014c8e0((int *)xform, *(int *)(model_b + 0x38));
  if (!ok) {
    return 0;
  }
  /* cdecl: (xform, flag=1, end_pt, neg_dir, hit_buf) — verify vs kb:
     char FUN_0014cb00(int param_1, void *param_2, void *param_3, void *param_4, int16_t *param_5);
     pushes: hit_buf, neg_dir, end_pt, 1, xform → (xform, 1, end_pt, neg_dir, hit_buf) */
  if (!FUN_0014cb00((int)(int *)xform, (void *)1, end_pt, neg_dir, (int16_t *)hit_buf)) {
    return 0;
  }

  first_idx = *(short *)hit_buf;
  t = *(float *)0x2533c8 - *(float *)(hit_buf + 8);
  *(float *)(result + 0x14) = t;
  *(short *)result = 3;

  /* node_base at xform+0xc (ebp-0x1c if xform at -0x28 → +0xc) */
  node_base = *(int *)(xform + 0xc);
  stride_off = (int)first_idx * 0x34;
  plane_src = node_base + stride_off;
  /* pushes: out=result+0x24, in=[hit+0xc], matrix=plane_src
     decl FUN_0010a1c0(matrix, in_plane, out_plane) */
  FUN_0010a1c0((float *)plane_src, *(float **)(hit_buf + 0xc),
               (float *)(result + 0x24));

  if (*(int *)(hit_buf + 0x14) < 0) {
    plane_negate((float *)(result + 0x24), (float *)(result + 0x24));
  }

  ax_s = FUN_0014da80(*(int *)(xform + 4), *(short *)(hit_buf + 0x1a));
  *(short *)(result + 0x34) = ax_s;
  *(int *)(result + 0x38) = *(int *)(model_b + 0x38);
  *(short *)(result + 0x3c) = *(short *)(hit_buf + 2);
  *(short *)(result + 0x3e) = first_idx;
  *(short *)(result + 0x40) = *(short *)(hit_buf + 4);
  *(int *)(result + 0x44) = *(int *)(hit_buf + 0x10);
  *(int *)(result + 0x48) = *(int *)(hit_buf + 0x14);
  result[0x4c] = hit_buf[0x18];
  result[0x4d] = hit_buf[0x19];
  *(short *)(result + 0x4e) = *(short *)(hit_buf + 0x1a);

  *(float *)(result + 0x18) = offset[0] * t + origin[0];
  *(float *)(result + 0x1c) = offset[1] * t + origin[1];
  *(float *)(result + 0x20) = offset[2] * t + origin[2];
  return 1;
}
