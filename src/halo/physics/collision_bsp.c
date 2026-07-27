#include <stdint.h>
/* collision_bsp.obj (physics/collision_bsp.c)
 *
 * Declarations for tag_block_get_element, display_assert and system_exit come
 * from the generated decl.h via kb.json.
 */

/* collision_surface_edge_count (0x1473b0) — readable C lift from XBE leaf. */
short collision_surface_edge_count(int bsp, int surface_index)
{
  int *surface;
  int first_edge;
  int edge;
  int count = 0;
  void *surfaces = (char *)bsp + 0x3c;
  void *edges = (char *)bsp + 0x48;

  surface = (int *)tag_block_get_element(surfaces, surface_index, 0xc);
  first_edge = surface[1];
  edge = first_edge;
  do {
    int *edge_el = (int *)tag_block_get_element(edges, edge, 0x18);
    int next_is_right = (edge_el[5] == surface_index);
    edge = edge_el[2 + next_is_right];
    count++;
  } while (edge != first_edge);
  return (short)count;
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

/* render_debug_collision_bsp (0x147660) — readable C lift from XBE leaf. */
void render_debug_collision_bsp(int bsp, int matrix_or_flag)
{
  int count = *(int *)(bsp + 0x48);
  int i;
  for (i = 0; i < count; i++) {
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

/* collision_surface_perimeter (0x147710) — readable C lift from XBE leaf.
 * Sum edge lengths around a surface's winged-edge loop. */
float collision_surface_perimeter(int bsp, int surface_index)
{
  int *surface;
  int first_edge;
  int edge;
  float sum;
  void *surfaces = (char *)bsp + 0x3c;
  void *edges = (char *)bsp + 0x48;
  void *vertices = (char *)bsp + 0x54;

  surface = (int *)tag_block_get_element(surfaces, surface_index, 0xc);
  first_edge = surface[1];
  edge = first_edge;
  sum = 0.0f;
  do {
    int *edge_el = (int *)tag_block_get_element(edges, edge, 0x18);
    int side = (edge_el[5] == surface_index);
    float *v0 = (float *)tag_block_get_element(vertices, edge_el[side], 0x10);
    float *v1 = (float *)tag_block_get_element(vertices, edge_el[1 - side], 0x10);
    float dx = v1[0] - v0[0];
    float dy = v1[1] - v0[1];
    float dz = v1[2] - v0[2];
    sum += sqrtf(dx * dx + dy * dy + dz * dz);
    edge = edge_el[2 + side];
  } while (edge != first_edge);
  return sum;
}


/* collision_surface_area — restored readable C from b5350bf74 */
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

/* collision_surface_test_line2d — restored readable C from b5350bf74 */
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

/* collision_surface_project_point2d (0x147990) — readable C lift. */
float *collision_surface_project_point2d(void *bsp, int surface_index, int projection, int sign, float *point, float *out_point)
{
  int *surface;
  float *plane;
  int plane_index;

  surface = (int *)tag_block_get_element((char *)bsp + 0x3c, surface_index, 0xc);
  plane_index = *surface & 0x7fffffff;
  plane = (float *)tag_block_get_element((char *)bsp + 0xc, plane_index, 0x10);
  project_point2d(point, plane, (int16_t)projection, (uint8_t)sign, out_point);
  return out_point;
}

/* collision_surface_test_point2d (0x1479e0) — readable C lift from XBE leaf.
 * Winged-edge walk: project edge endpoints to 2D; reject if 2D cross > 0. */
char collision_surface_test_point2d(int bsp, int surface_index, int projection, int sign, float *point)
{
  int *surface;
  int first_edge;
  int edge;
  float a[2];
  float b[2];
  void *surfaces = (char *)bsp + 0x3c;
  void *edges = (char *)bsp + 0x48;
  void *vertices = (char *)bsp + 0x54;

  surface = (int *)tag_block_get_element(surfaces, surface_index, 0xc);
  first_edge = surface[1];
  edge = first_edge;
  do {
    int *edge_el = (int *)tag_block_get_element(edges, edge, 0x18);
    int side = (edge_el[5] == surface_index);
    float *v0 = (float *)tag_block_get_element(vertices, edge_el[side], 0x10);
    float *v1 = (float *)tag_block_get_element(vertices, edge_el[1 - side], 0x10);
    float cross;

    FUN_00061df0(v0, (short)projection, (unsigned char)sign, a);
    FUN_00061df0(v1, (short)projection, (unsigned char)sign, b);
    cross = (point[1] - b[1]) * (point[0] - a[0]) - (point[0] - b[0]) * (point[1] - a[1]);
    if (cross > *(float *)0x2533c0)
      return 0;
    edge = edge_el[2 + side];
  } while (edge != first_edge);
  return 1;
}



/* collision_surface_find_closest_point2d (0x147ae0) — XBE naked draft (batch 227). */
#if defined(__clang__)
static void *(*const b147ae0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b147ae0_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = (void *)FUN_00061df0;

__attribute__((naked, noinline))
int collision_surface_find_closest_point2d(int bsp __attribute__((unused)), int surface_index __attribute__((unused)), int projection __attribute__((unused)), int sign __attribute__((unused)), float *point __attribute__((unused)), float *out_point __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "leal 0x48(%%esi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x54, %%esi\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      ".Lcollision_surface_find_closest_point2d_1:\n\t"
      "movl -0x18(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ecx, 0x14(%%esi)\n\t"
      "sete %%bl\n\t"
      "movzbl %%bl, %%eax\n\t"
      "movl (%%esi,%%eax,4), %%edx\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%cl\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl (%%esi,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "leal -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      "call *%[c61df0]\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "leal -0x34(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c61df0]\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "addl $0x44, %%esp\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fsubs -0x2c(%%ebp)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fsubs -0x28(%%ebp)\n\t"
      "fsts -0x20(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcollision_surface_find_closest_point2d_3\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcollision_surface_find_closest_point2d_2\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lcollision_surface_find_closest_point2d_4\n\t"
      ".Lcollision_surface_find_closest_point2d_2:\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcollision_surface_find_closest_point2d_11\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstp %%st(0)\n\t"
      "movb $1, %%dl\n\t"
      "jmp .Lcollision_surface_find_closest_point2d_5\n\t"
      ".Lcollision_surface_find_closest_point2d_3:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      ".Lcollision_surface_find_closest_point2d_4:\n\t"
      "movb 0xb(%%ebp), %%dl\n\t"
      ".Lcollision_surface_find_closest_point2d_5:\n\t"
      "cmpl -0x14(%%ebp), %%edi\n\t"
      "je .Lcollision_surface_find_closest_point2d_8\n\t"
      "movb -0x4(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lcollision_surface_find_closest_point2d_7\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcollision_surface_find_closest_point2d_6\n\t"
      "testb %%dl, %%dl\n\t"
      "jne .Lcollision_surface_find_closest_point2d_9\n\t"
      ".Lcollision_surface_find_closest_point2d_6:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl -0x28(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcollision_surface_find_closest_point2d_7:\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcollision_surface_find_closest_point2d_9\n\t"
      "movb -0x3(%%ebp), %%bl\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lcollision_surface_find_closest_point2d_6\n\t"
      "jmp .Lcollision_surface_find_closest_point2d_9\n\t"
      ".Lcollision_surface_find_closest_point2d_8:\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "movb %%dl, -0x5(%%ebp)\n\t"
      ".Lcollision_surface_find_closest_point2d_9:\n\t"
      "movl -0x1c(%%ebp), %%edi\n\t"
      "movl 0x8(%%esi,%%edi,4), %%edi\n\t"
      "cmpl -0x14(%%ebp), %%edi\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "movb %%dl, -0x4(%%ebp)\n\t"
      "jne .Lcollision_surface_find_closest_point2d_1\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lcollision_surface_find_closest_point2d_12\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcollision_surface_find_closest_point2d_13\n\t"
      "movb -0x5(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lcollision_surface_find_closest_point2d_13\n\t"
      ".Lcollision_surface_find_closest_point2d_10:\n\t"
      "movl (%%ecx), %%edx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl %%edx, (%%eax)\n\t"
      "movl 0x4(%%ecx), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcollision_surface_find_closest_point2d_11:\n\t"
      "fdivrs -0xc(%%ebp)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps (%%eax)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds -0x28(%%ebp)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "xorb %%al, %%al\n\t"
      "fstp %%st(0)\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcollision_surface_find_closest_point2d_12:\n\t"
      "movb -0x2(%%ebp), %%dl\n\t"
      "testb %%dl, %%dl\n\t"
      "je .Lcollision_surface_find_closest_point2d_10\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lcollision_surface_find_closest_point2d_10\n\t"
      ".Lcollision_surface_find_closest_point2d_13:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "cmpl %%ecx, 0x14(%%eax)\n\t"
      "sete %%cl\n\t"
      "movzbl %%cl, %%edx\n\t"
      "movl (%%eax,%%edx,4), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x1c(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c61df0]\n\t"
      "addl $0x28, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b147ae0_elem), [c61df0] "m"(b147ae0_c61df0)
      : "memory");
}
#else
#error "collision_surface_find_closest_point2d: clang naked draft required"
#endif



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

/* FUN_001491d0 (0x1491d0) — readable C lift (restored pre-naked). */


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



/* FUN_00148240 (0x148240) — readable C lift from XBE leaf.
 * Like collision_surface_test_point2d, with optional breakable-surface skip. */
char FUN_00148240(int bsp, unsigned short flags, int breakable_surfaces,
                  int surface_index, int projection, int sign, float *point2d)
{
  int *surface;
  int first_edge;
  int edge;
  float a[2];
  float b[2];
  unsigned char *surf_bytes;
  unsigned int breakable_index;
  unsigned int bit;
  void *surfaces;
  void *edges;
  void *vertices;

  surfaces = (char *)bsp + 0x3c;
  edges = (char *)bsp + 0x48;
  vertices = (char *)bsp + 0x54;

  surface = (int *)tag_block_get_element(surfaces, surface_index, 0xc);
  surf_bytes = (unsigned char *)surface;
  if (surf_bytes[8] & 8) {
    breakable_index = surf_bytes[9];
    if ((int)breakable_index < (int)(short)flags) {
      bit = 1u << (breakable_index & 0x1fu);
      if ((((unsigned int *)breakable_surfaces)[breakable_index >> 5] & bit) == 0)
        return 0;
    }
  }

  first_edge = surface[1];
  edge = first_edge;
  do {
    int *edge_el;
    int side;
    float *v0;
    float *v1;
    float cross;

    edge_el = (int *)tag_block_get_element(edges, edge, 0x18);
    side = (edge_el[5] == surface_index);
    v0 = (float *)tag_block_get_element(vertices, edge_el[side], 0x10);
    v1 = (float *)tag_block_get_element(vertices, edge_el[1 - side], 0x10);
    FUN_00061df0(v0, (short)projection, (unsigned char)sign, a);
    FUN_00061df0(v1, (short)projection, (unsigned char)sign, b);
    cross = (b[1] - a[1]) * (point2d[0] - a[0]) -
            (b[0] - a[0]) * (point2d[1] - a[1]);
    if (cross > *(float *)0x2533c0)
      return 0;
    edge = edge_el[2 + side];
  } while (edge != first_edge);
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

static void __attribute__((unused)) collision_bsp_vector_remember_leaf(collision_bsp_vector_state *state,
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


/* FUN_00148780 (0x148780) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void *(*const b148780_elem)(void *, int, int) = tag_block_get_element;
static void (*const b148780_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = (void *)FUN_00061df0;
static uint32_t (*const b148780_c146d40)(void *bsp2d_nodes, float *point2d, int node_index) = (void *)FUN_00146d40;
static char (*const b148780_c148240)(int bsp /* */, unsigned short flags, int breakable_surfaces, int surface_index, int projection, int sign, float *point2d) = (void *)FUN_00148240;

__attribute__((naked, noinline))
int FUN_00148780(int leaf_index /* */ __attribute__((unused)), int bsp __attribute__((unused)), unsigned short flags __attribute__((unused)), int breakable_surfaces __attribute__((unused)), float *origin __attribute__((unused)), float *direction __attribute__((unused)), int plane_index __attribute__((unused)), float t __attribute__((unused)), int two_sided __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x20, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "leal 0x18(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%edi\n\t"
      "movswl 0x2(%%eax), %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%edx, %%edi\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jge .LFUN_00148780_9\n\t"
      ".LFUN_00148780_1:\n\t"
      "pushl $8\n\t"
      "leal 0x24(%%ebx), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jne .LFUN_00148780_8\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "addl $0xc, %%esp\n\t"
      "fabs\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fabs\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fabs\n\t"
      "fcom %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00148780_2\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00148780_3\n\t"
      "fstp %%st(0)\n\t"
      "movl $2, %%edi\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00148780_5\n\t"
      ".LFUN_00148780_2:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00148780_3:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00148780_4\n\t"
      "movl $1, %%edi\n\t"
      "jmp .LFUN_00148780_5\n\t"
      ".LFUN_00148780_4:\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_00148780_5:\n\t"
      "movswl %%di, %%edx\n\t"
      "flds (%%ecx,%%edx,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148780_6\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00148780_7\n\t"
      ".LFUN_00148780_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00148780_7:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "flds 0x20(%%ebp)\n\t"
      "andl $0x80000000, %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "movzbl %%al, %%edx\n\t"
      "negl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "setne %%al\n\t"
      "movb %%al, -0x8(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "leal -0x20(%%ebp), %%edx\n\t"
      "fmuls (%%eax)\n\t"
      "fadds (%%ecx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "pushl %%edx\n\t"
      "call *%[c61df0]\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "addl $0x30, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c146d40]\n\t"
      "movl %%eax, %%esi\n\t"
      "movb 0x24(%%ebp), %%al\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00148780_10\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c148240]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00148780_10\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_00148780_8:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "incl %%edi\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jl .LFUN_00148780_1\n\t"
      ".LFUN_00148780_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148780_10:\n\t"
      "popl %%edi\n\t"
      "movl %%esi, %%eax\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b148780_elem), [c61df0] "m"(b148780_c61df0), [c146d40] "m"(b148780_c146d40), [c148240] "m"(b148780_c148240)
      : "memory");
}
#else
#error "FUN_00148780: clang naked draft required"
#endif


/* FUN_00148eb0 (0x148eb0) — XBE naked draft (batch 227). */
#if defined(__clang__)
static void *(*const b148eb0_elem)(void *, int, int) = tag_block_get_element;
static char (*const b148eb0_c148eb0)(void *state, int node_index, float t0, float t1) = (void *)FUN_00148eb0;
static int (*const b148eb0_c148780)(int leaf_index /* */, int bsp, unsigned short flags, int breakable_surfaces, float *origin, float *direction, int plane_index, float t, int two_sided) = (void *)FUN_00148780;

__attribute__((naked, noinline))
char FUN_00148eb0(void *state __attribute__((unused)), int node_index __attribute__((unused)), float t0 __attribute__((unused)), float t1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "js .LFUN_00148eb0_9\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00148eb0_1\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00148eb0_1\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_00148eb0_2\n\t"
      ".LFUN_00148eb0_1:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00148eb0_2:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00148eb0_3\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00148eb0_3\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_00148eb0_4\n\t"
      ".LFUN_00148eb0_3:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_00148eb0_4:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00148eb0_7\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00148eb0_7\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148eb0_5\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00148eb0_6\n\t"
      ".LFUN_00148eb0_5:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00148eb0_6:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "fdivs 0xc(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%dl\n\t"
      "fchs\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "movl 0x4(%%edi,%%edx,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c148eb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00148eb0_20\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00148eb0_26\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x24(%%esi)\n\t"
      "pushl %%eax\n\t"
      "movzbl %%bl, %%edx\n\t"
      "movl 0x4(%%edi,%%edx,4), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "jmp .LFUN_00148eb0_8\n\t"
      ".LFUN_00148eb0_7:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl 0x4(%%edi,%%eax,4), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      ".LFUN_00148eb0_8:\n\t"
      "pushl %%esi\n\t"
      "call *%[c148eb0]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00148eb0_26\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148eb0_9:\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "cmpl $-1, %%eax\n\t"
      "movb $3, %%bl\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "movb %%bl, 0xf(%%ebp)\n\t"
      "movb $0, -0x8(%%ebp)\n\t"
      "je .LFUN_00148eb0_10\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $8\n\t"
      "pushl %%eax\n\t"
      "addl $0x18, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movb (%%eax), %%dl\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $1, %%dl\n\t"
      "setne %%al\n\t"
      "incb %%al\n\t"
      "movb %%al, 0xf(%%ebp)\n\t"
      "movb %%al, %%bl\n\t"
      ".LFUN_00148eb0_10:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $1, %%edx\n\t"
      "je .LFUN_00148eb0_12\n\t"
      "movb 0x20(%%esi), %%al\n\t"
      "cmpb $1, %%al\n\t"
      "je .LFUN_00148eb0_11\n\t"
      "cmpb $2, %%al\n\t"
      "jne .LFUN_00148eb0_12\n\t"
      ".LFUN_00148eb0_11:\n\t"
      "cmpb $3, %%bl\n\t"
      "jne .LFUN_00148eb0_12\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "jmp .LFUN_00148eb0_17\n\t"
      ".LFUN_00148eb0_12:\n\t"
      "testb $2, %%cl\n\t"
      "je .LFUN_00148eb0_14\n\t"
      "cmpb $3, 0x20(%%esi)\n\t"
      "jne .LFUN_00148eb0_14\n\t"
      "cmpb $1, %%bl\n\t"
      "je .LFUN_00148eb0_13\n\t"
      "cmpb $2, %%bl\n\t"
      "jne .LFUN_00148eb0_14\n\t"
      ".LFUN_00148eb0_13:\n\t"
      "movl %%edi, %%eax\n\t"
      "jmp .LFUN_00148eb0_17\n\t"
      ".LFUN_00148eb0_14:\n\t"
      "testb $4, %%cl\n\t"
      "jne .LFUN_00148eb0_23\n\t"
      "cmpb $2, 0x20(%%esi)\n\t"
      "jne .LFUN_00148eb0_23\n\t"
      "cmpb $2, %%bl\n\t"
      "jne .LFUN_00148eb0_23\n\t"
      "testl %%edx, %%edx\n\t"
      "je .LFUN_00148eb0_15\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "jmp .LFUN_00148eb0_16\n\t"
      ".LFUN_00148eb0_15:\n\t"
      "movl %%edi, %%eax\n\t"
      ".LFUN_00148eb0_16:\n\t"
      "movb $1, -0x8(%%ebp)\n\t"
      ".LFUN_00148eb0_17:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00148eb0_23\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x24(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x14(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "pushl %%edx\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c148780]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $0x20, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00148eb0_22\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "pushl $0xc\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movb 0x8(%%edi), %%al\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $2, %%al\n\t"
      "je .LFUN_00148eb0_18\n\t"
      "testb $8, (%%esi)\n\t"
      "jne .LFUN_00148eb0_21\n\t"
      ".LFUN_00148eb0_18:\n\t"
      "testb $8, %%al\n\t"
      "je .LFUN_00148eb0_19\n\t"
      "testb $0x10, (%%esi)\n\t"
      "jne .LFUN_00148eb0_21\n\t"
      ".LFUN_00148eb0_19:\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl %%ebx, 0x8(%%eax)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl (%%edi), %%edx\n\t"
      "movl %%edx, 0xc(%%ecx)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movb 0x8(%%edi), %%cl\n\t"
      "movb %%cl, 0x10(%%eax)\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "movb 0x9(%%edi), %%al\n\t"
      "movb %%al, 0x11(%%edx)\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movw 0xa(%%edi), %%dx\n\t"
      "addl $0xc, %%esp\n\t"
      "movw %%dx, 0x12(%%ecx)\n\t"
      ".LFUN_00148eb0_20:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148eb0_21:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      ".LFUN_00148eb0_22:\n\t"
      "movb 0xf(%%ebp), %%bl\n\t"
      ".LFUN_00148eb0_23:\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_00148eb0_25\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "movl 0x14(%%eax), %%ecx\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jge .LFUN_00148eb0_24\n\t"
      "movl %%edi, 0x18(%%eax,%%ecx,4)\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "incl 0x14(%%eax)\n\t"
      "movl %%edi, 0x1c(%%esi)\n\t"
      "popl %%edi\n\t"
      "movb %%bl, 0x20(%%esi)\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148eb0_24:\n\t"
      "movl %%edi, 0x414(%%eax)\n\t"
      ".LFUN_00148eb0_25:\n\t"
      "movl %%edi, 0x1c(%%esi)\n\t"
      "movb %%bl, 0x20(%%esi)\n\t"
      ".LFUN_00148eb0_26:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b148eb0_elem), [c148eb0] "m"(b148eb0_c148eb0), [c148780] "m"(b148eb0_c148780)
      : "memory");
}
#else
#error "FUN_00148eb0: clang naked draft required"
#endif


/* collision_bsp_test_vector (0x149480) — readable C lift from XBE leaf.
 * Thin wrapper: build vector state and walk BSP from node 0. */
char collision_bsp_test_vector(int collision_flags, int bsp, short flags,
                               int breakable_surfaces, int origin, int direction,
                               float max_t, float *result)
{
  int log_fn;
  collision_bsp_vector_state state;
  float t1;
  char hit;

  log_fn = 4 + (bsp == *(int *)0x5064dc ? 1 : 0);
  collision_log_add_call((short)log_fn);
  collision_log_query_counter((void *)0x46f090);

  state.collision_flags = collision_flags;
  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.pad_u16 = 0;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.direction = (float *)direction;
  state.result = result;
  state.last_leaf = -1;
  state.leaf_side = 0;
  state.pad_u8[0] = 0;
  state.pad_u8[1] = 0;
  state.pad_u8[2] = 0;
  state.plane_index = -1;

  /* result[0] = max_t unless ordered-negative (NaN keeps max_t). */
  if (max_t < 0.0f) {
    result[0] = 0.0f;
  } else {
    result[0] = max_t;
  }
  result[5] = 0.0f; /* +0x14 leaf count */

  if (max_t < 0.0f) {
    t1 = 0.0f;
  } else if (max_t > 1.0f) {
    t1 = 1.0f;
  } else {
    t1 = max_t;
  }

  hit = FUN_00148eb0(&state, 0, 0.0f, t1);
  collision_log_add_time((short)log_fn, *(unsigned int *)0x46f090,
                         *(int *)0x46f094);
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


/* FUN_00147ed0 (0x147ed0) — XBE naked draft (batch 227). */
#if defined(__clang__)
static void *(*const b147ed0_elem)(void *, int, int) = tag_block_get_element;
static bool (*const b147ed0_c10bc70)(float *line_start, float *line_end, float *sphere_center, float sphere_radius) = (void *)fast_vector_intersects_sphere;
static void (*const b147ed0_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = (void *)FUN_00061df0;

__attribute__((naked, noinline))
void FUN_00147ed0(void *state /* */ __attribute__((unused)), int surface_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "addl $0x3c, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movb 0x8(%%eax), %%cl\n\t"
      "addl $0xc, %%esp\n\t"
      "testb $8, %%cl\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_00147ed0_1\n\t"
      "movzbl 0x9(%%eax), %%ecx\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "jge .LFUN_00147ed0_1\n\t"
      "movl 0x8(%%esi), %%edi\n\t"
      "movl %%ecx, %%edx\n\t"
      "andl $0x1f, %%ecx\n\t"
      "movl $1, %%ebx\n\t"
      "shll %%cl, %%ebx\n\t"
      "shrl $5, %%edx\n\t"
      "testl %%ebx, (%%edi,%%edx,4)\n\t"
      "je .LFUN_00147ed0_16\n\t"
      ".LFUN_00147ed0_1:\n\t"
      "flds 0x10(%%esi)\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "fld %%st(0)\n\t"
      "leal -0xc(%%ebp), %%eax\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "leal (%%ebx), %%ebx\n\t"
      ".LFUN_00147ed0_2:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0x18\n\t"
      "addl $0x48, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpl %%edx, 0x14(%%ebx)\n\t"
      "sete %%al\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl (%%ebx,%%eax,4), %%edi\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x10\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      ".byte 0xf3, 0x0f, 0x10, 0x01\n\t"
      ".byte 0x0f, 0x16, 0x41, 0x04\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      ".byte 0xf3, 0x0f, 0x10, 0x09\n\t"
      ".byte 0x0f, 0x16, 0x49, 0x04\n\t"
      ".byte 0x0f, 0x5c, 0xc1\n\t"
      ".byte 0x0f, 0x59, 0xc0\n\t"
      ".byte 0xf3, 0x0f, 0x10, 0xd0\n\t"
      ".byte 0x0f, 0xc6, 0xc0, 0x0e\n\t"
      ".byte 0xf3, 0x0f, 0x58, 0xd0\n\t"
      ".byte 0x0f, 0xc6, 0xc0, 0x39\n\t"
      ".byte 0xf3, 0x0f, 0x58, 0xd0\n\t"
      ".byte 0xf3, 0x0f, 0x11, 0x10\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps -0x28(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jp .LFUN_00147ed0_6\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movl 0x808(%%eax), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "jle .LFUN_00147ed0_4\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".LFUN_00147ed0_3:\n\t"
      "cmpl %%edi, 0x80c(%%eax,%%ecx,4)\n\t"
      "je .LFUN_00147ed0_5\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl 0x808(%%eax), %%ecx\n\t"
      "jl .LFUN_00147ed0_3\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      ".LFUN_00147ed0_4:\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jge .LFUN_00147ed0_5\n\t"
      "movl %%edi, 0x80c(%%eax,%%ecx,4)\n\t"
      "incl 0x808(%%eax)\n\t"
      ".LFUN_00147ed0_5:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00147ed0_6:\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx,%%edx,4), %%ebx\n\t"
      "cmpl 0x4(%%eax), %%ebx\n\t"
      "jne .LFUN_00147ed0_2\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      ".LFUN_00147ed0_7:\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "addl $0x48, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpl %%edx, 0x14(%%ebx)\n\t"
      "sete %%al\n\t"
      "movb %%al, -0x2(%%ebp)\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl (%%ebx,%%eax,4), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "addl $0x54, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl (%%esi), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movb -0x2(%%ebp), %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%dl\n\t"
      "pushl $0x10\n\t"
      "addl $0x54, %%ecx\n\t"
      "movl (%%ebx,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%edi)\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x24(%%ebp), %%ecx\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "call *%[c10bc70]\n\t"
      "addl $0x34, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00147ed0_11\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movl 0x404(%%eax), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%ecx, -0x2c(%%ebp)\n\t"
      "jle .LFUN_00147ed0_9\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00147ed0_8:\n\t"
      "movl 0x408(%%eax,%%ecx,4), %%ecx\n\t"
      "cmpl -0xc(%%ebp), %%ecx\n\t"
      "je .LFUN_00147ed0_10\n\t"
      "movl 0x404(%%eax), %%edi\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jl .LFUN_00147ed0_8\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      ".LFUN_00147ed0_9:\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jge .LFUN_00147ed0_10\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movl %%edx, 0x408(%%eax,%%ecx,4)\n\t"
      "incl 0x404(%%eax)\n\t"
      ".LFUN_00147ed0_10:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00147ed0_11:\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebx,%%eax,4), %%ebx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "cmpl 0x4(%%ecx), %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "jne .LFUN_00147ed0_7\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00147ed0_13\n\t"
      "movl %%ecx, %%edx\n\t"
      "movl 0x4(%%edx), %%edi\n\t"
      "nop\n\t"
      ".LFUN_00147ed0_12:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x18\n\t"
      "addl $0x48, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "cmpl %%ecx, 0x14(%%edi)\n\t"
      "sete %%bl\n\t"
      "movzbl %%bl, %%eax\n\t"
      "movl (%%edi,%%eax,4), %%edx\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "addl $0x54, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%cl\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $0x10\n\t"
      "addl $0x54, %%eax\n\t"
      "movl (%%edi,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x21e(%%esi), %%dl\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x21c(%%esi), %%ax\n\t"
      "leal -0x20(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c61df0]\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x21e(%%esi), %%al\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x21c(%%esi), %%cx\n\t"
      "leal -0x18(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c61df0]\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fsubs 0x220(%%esi)\n\t"
      "addl $0x44, %%esp\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fsubs 0x224(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fsubs 0x220(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fsubs 0x224(%%esi)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "fxch %%st(2)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      ".byte 0xde, 0xea\n\t"
      "fxch %%st(1)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "fstp %%st(0)\n\t"
      "jnp .LFUN_00147ed0_16\n\t"
      "movl -0x28(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x8(%%edi,%%edx,4), %%edi\n\t"
      "cmpl 0x4(%%eax), %%edi\n\t"
      "jne .LFUN_00147ed0_12\n\t"
      ".LFUN_00147ed0_13:\n\t"
      "movl 0x14(%%esi), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testl %%edx, %%edx\n\t"
      "jle .LFUN_00147ed0_15\n\t"
      "xorl %%eax, %%eax\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00147ed0_14:\n\t"
      "movl 0x4(%%esi,%%eax,4), %%eax\n\t"
      "cmpl 0x8(%%ebp), %%eax\n\t"
      "je .LFUN_00147ed0_16\n\t"
      "movl (%%esi), %%edi\n\t"
      "incl %%ecx\n\t"
      "movswl %%cx, %%eax\n\t"
      "cmpl %%edi, %%eax\n\t"
      "jl .LFUN_00147ed0_14\n\t"
      ".LFUN_00147ed0_15:\n\t"
      "cmpl $0x100, %%edx\n\t"
      "jge .LFUN_00147ed0_16\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0x4(%%esi,%%edx,4)\n\t"
      "incl (%%esi)\n\t"
      ".LFUN_00147ed0_16:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b147ed0_elem), [c10bc70] "m"(b147ed0_c10bc70), [c61df0] "m"(b147ed0_c61df0)
      : "memory");
}
#else
#error "FUN_00147ed0: clang naked draft required"
#endif


/* FUN_001486e0 (0x1486e0) — readable C lift from XBE leaf.
 * 2D BSP walk for sphere test; leaf → FUN_00147ed0. */
void FUN_001486e0(void *state, int node_index)
{
  float *node;
  float d;
  float radius;
  char side_pos;
  char side_neg;

  for (;;) {
    if (node_index < 0) {
      FUN_00147ed0(state, node_index & 0x7fffffff);
      return;
    }
    node = (float *)tag_block_get_element(
        (char *)*(void **)state + 0x30, node_index, 0x14);
    radius = *(float *)((char *)state + 0x10);
    d = node[1] * *(float *)((char *)state + 0x224) +
        *(float *)((char *)state + 0x220) * node[0] - node[2];
    side_pos = (d <= radius);
    side_neg = (d >= -radius);
    if (side_pos)
      FUN_001486e0(state, ((int *)node)[3]);
    if (!side_neg)
      return;
    node_index = ((int *)node)[4];
  }
}

/* bsp3d_test_sphere_recursive (0x148b90) — XBE naked draft (batch 225). */
#if defined(__clang__)
static void *(*const b148b90_elem)(void *, int, int) = tag_block_get_element;
static void (*const b148b90_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b148b90_exitfn)(int) = system_exit;
static void (*const b148b90_c148b90)(void *state, int node_index) = (void *)bsp3d_test_sphere_recursive;
static void (*const b148b90_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = (void *)FUN_00061df0;
static void (*const b148b90_c1486e0)(void *state, int node_index) = (void *)FUN_001486e0;

__attribute__((naked, noinline))
void bsp3d_test_sphere_recursive(void *state __attribute__((unused)), int node_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x14, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "js .Lbsp3d_test_sphere_recursive_5\n\t"
      ".Lbsp3d_test_sphere_recursive_1:\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "fcoms 0x10(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lbsp3d_test_sphere_recursive_2\n\t"
      "movb $1, %%cl\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_3\n\t"
      ".Lbsp3d_test_sphere_recursive_2:\n\t"
      "xorb %%cl, %%cl\n\t"
      ".Lbsp3d_test_sphere_recursive_3:\n\t"
      "flds 0x10(%%esi)\n\t"
      "fchs\n\t"
      "fxch %%st(1)\n\t"
      "fcompp\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbsp3d_test_sphere_recursive_9\n\t"
      "testb %%cl, %%cl\n\t"
      "movb $1, %%al\n\t"
      "jne .Lbsp3d_test_sphere_recursive_10\n\t"
      ".Lbsp3d_test_sphere_recursive_4:\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl 0x4(%%edi,%%eax,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .Lbsp3d_test_sphere_recursive_1\n\t"
      ".Lbsp3d_test_sphere_recursive_5:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lbsp3d_test_sphere_recursive_25\n\t"
      "movl (%%esi), %%ecx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $8\n\t"
      "addl $0x18, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movl 0xc0c(%%eax), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "jge .Lbsp3d_test_sphere_recursive_6\n\t"
      "movl %%edi, 0xc10(%%eax,%%ecx,4)\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "incl 0xc0c(%%eax)\n\t"
      ".Lbsp3d_test_sphere_recursive_6:\n\t"
      "movl 0x4(%%ebx), %%edi\n\t"
      "movswl 0x2(%%ebx), %%edx\n\t"
      "addl %%edi, %%edx\n\t"
      "cmpl %%edx, %%edi\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "jge .Lbsp3d_test_sphere_recursive_25\n\t"
      ".Lbsp3d_test_sphere_recursive_7:\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl $8\n\t"
      "addl $0x24, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jle .Lbsp3d_test_sphere_recursive_24\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lbsp3d_test_sphere_recursive_8:\n\t"
      "cmpl %%eax, 0x1c(%%esi,%%ecx,4)\n\t"
      "je .Lbsp3d_test_sphere_recursive_15\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl 0x18(%%esi), %%ecx\n\t"
      "jl .Lbsp3d_test_sphere_recursive_8\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_24\n\t"
      ".Lbsp3d_test_sphere_recursive_9:\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_4\n\t"
      ".Lbsp3d_test_sphere_recursive_10:\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .Lbsp3d_test_sphere_recursive_11\n\t"
      "cmpl $0x80, %%eax\n\t"
      "jl .Lbsp3d_test_sphere_recursive_12\n\t"
      ".Lbsp3d_test_sphere_recursive_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x206\n\t"
      "pushl $0x29cafc\n\t"
      "pushl $0x29cb24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbsp3d_test_sphere_recursive_12:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "orl $0x80000000, %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esi,%%edx,4)\n\t"
      "incl 0x18(%%esi)\n\t"
      "movl 0x4(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c148b90]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "js .Lbsp3d_test_sphere_recursive_13\n\t"
      "cmpl $0x80, %%eax\n\t"
      "jl .Lbsp3d_test_sphere_recursive_14\n\t"
      ".Lbsp3d_test_sphere_recursive_13:\n\t"
      "pushl $1\n\t"
      "pushl $0x210\n\t"
      "pushl $0x29cafc\n\t"
      "pushl $0x29cb24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbsp3d_test_sphere_recursive_14:\n\t"
      "movl (%%edi), %%ecx\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "andl $0x7fffffff, %%ecx\n\t"
      "movl %%ecx, 0x1c(%%esi,%%edx,4)\n\t"
      "incl 0x18(%%esi)\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c148b90]\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "decl %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x18(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lbsp3d_test_sphere_recursive_15:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "flds 0x4(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%edi)\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "fadds (%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds (%%edi)\n\t"
      "fabs\n\t"
      "flds 0x4(%%edi)\n\t"
      "fabs\n\t"
      "flds 0x8(%%edi)\n\t"
      "fabs\n\t"
      "fcom %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lbsp3d_test_sphere_recursive_16\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lbsp3d_test_sphere_recursive_17\n\t"
      "fstp %%st(0)\n\t"
      "movl $2, %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_19\n\t"
      ".Lbsp3d_test_sphere_recursive_16:\n\t"
      "fstp %%st(0)\n\t"
      ".Lbsp3d_test_sphere_recursive_17:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "jne .Lbsp3d_test_sphere_recursive_18\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_19\n\t"
      ".Lbsp3d_test_sphere_recursive_18:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".Lbsp3d_test_sphere_recursive_19:\n\t"
      "testw %%bx, %%bx\n\t"
      "movw %%bx, 0x21c(%%esi)\n\t"
      "jl .Lbsp3d_test_sphere_recursive_20\n\t"
      "cmpw $2, %%bx\n\t"
      "jle .Lbsp3d_test_sphere_recursive_21\n\t"
      ".Lbsp3d_test_sphere_recursive_20:\n\t"
      "pushl $1\n\t"
      "pushl $0x350\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x25ed5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbsp3d_test_sphere_recursive_21:\n\t"
      "movswl %%bx, %%edx\n\t"
      "flds (%%edi,%%edx,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbsp3d_test_sphere_recursive_22\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lbsp3d_test_sphere_recursive_23\n\t"
      ".Lbsp3d_test_sphere_recursive_22:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lbsp3d_test_sphere_recursive_23:\n\t"
      "movl -0x4(%%ebp), %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "andl $0x80000000, %%ecx\n\t"
      "negl %%ecx\n\t"
      "sbbl %%ecx, %%ecx\n\t"
      "movzbl %%al, %%edx\n\t"
      "negl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "setne %%al\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x21c(%%esi), %%dx\n\t"
      "leal 0x220(%%esi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movb %%al, 0x21e(%%esi)\n\t"
      "pushl %%eax\n\t"
      "leal -0x14(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[c61df0]\n\t"
      "movl 0x4(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c1486e0]\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "movl -0x8(%%ebp), %%ebx\n\t"
      "addl $0x18, %%esp\n\t"
      ".Lbsp3d_test_sphere_recursive_24:\n\t"
      "movswl 0x2(%%ebx), %%edx\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "incl %%edi\n\t"
      "addl %%ecx, %%edx\n\t"
      "cmpl %%edx, %%edi\n\t"
      "movl %%edi, 0xc(%%ebp)\n\t"
      "jl .Lbsp3d_test_sphere_recursive_7\n\t"
      ".Lbsp3d_test_sphere_recursive_25:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b148b90_elem), [assert] "m"(b148b90_assert), [exitfn] "m"(b148b90_exitfn), [c148b90] "m"(b148b90_c148b90), [c61df0] "m"(b148b90_c61df0), [c1486e0] "m"(b148b90_c1486e0)
      : "memory");
}
#else
#error "bsp3d_test_sphere_recursive: clang naked draft required"
#endif


/* collision_bsp_test_sphere (0x1493b0) — readable C lift from XBE leaf.
 * Thin wrapper: build sphere state, recurse from node 0, return any-hit. */
int collision_bsp_test_sphere(int bsp, short flags, int breakable_surfaces,
                              int origin, float radius, int *results)
{
  int log_fn;
  collision_bsp_sphere_state state;

  log_fn = 6 + (bsp == *(int *)0x5064dc ? 1 : 0);
  collision_log_add_call((short)log_fn);
  collision_log_query_counter((void *)0x46f098);

  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.pad0 = 0;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.radius = radius;
  state.results = results;
  state.plane_stack_count = 0;
  results[0xc0c / 4] = 0;
  results[0] = 0;
  results[0x404 / 4] = 0;
  results[0x808 / 4] = 0;

  bsp3d_test_sphere_recursive(&state, 0);
  collision_log_add_time((short)log_fn, *(unsigned int *)0x46f098,
                         *(int *)0x46f09c);

  if (results[0] > 0 || results[0x404 / 4] > 0) {
    return 1;
  }
  return 0;
}



/* FUN_00147380 (0x147380) — readable C lift; thin wrapper (node_flags=-1). */
int FUN_00147380(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
  return FUN_001470b0(a0, a1, -1, a2, a3, a4, a5, a6);
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

/* FUN_00148440 (0x148440) — XBE naked draft (batch 223). */
#if defined(__clang__)
static void *(*const b148440_elem)(void *, int, int) = tag_block_get_element;
static char (*const b148440_c148440)(void *state, int node_index, float t0, float t1) = (void *)FUN_00148440;

__attribute__((naked, noinline))
char FUN_00148440(void *state __attribute__((unused)), int node_index __attribute__((unused)), float t0 __attribute__((unused)), float t1 __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "js .LFUN_00148440_7\n\t"
      ".LFUN_00148440_1:\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x14(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fcoms 0x14(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00148440_2\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x14(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00148440_2\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_00148440_3\n\t"
      ".LFUN_00148440_2:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00148440_3:\n\t"
      "flds 0x14(%%esi)\n\t"
      "fchs\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00148440_4\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps -0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00148440_4\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_00148440_5\n\t"
      ".LFUN_00148440_4:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_00148440_5:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00148440_6\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00148440_8\n\t"
      ".LFUN_00148440_6:\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl 0x4(%%edi,%%eax,4), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_00148440_1\n\t"
      ".LFUN_00148440_7:\n\t"
      "cmpl $-1, %%eax\n\t"
      "jne .LFUN_00148440_25\n\t"
      "movl 0x28(%%esi), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00148440_25\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0xc, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x28(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jns .LFUN_00148440_23\n\t"
      "flds (%%eax)\n\t"
      "movl 0x1c(%%esi), %%esi\n\t"
      "fchs\n\t"
      "popl %%edi\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fchs\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x8(%%eax)\n\t"
      "movb $1, %%al\n\t"
      "fchs\n\t"
      "fstps 0x8(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148440_8:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148440_9\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00148440_10\n\t"
      ".LFUN_00148440_9:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00148440_10:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00148440_17\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0xc(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0x14(%%esi)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fsubs 0x14(%%esi)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fchs\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148440_11\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00148440_12\n\t"
      ".LFUN_00148440_11:\n\t"
      "fsts 0xc(%%ebp)\n\t"
      ".LFUN_00148440_12:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148440_13\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .LFUN_00148440_14\n\t"
      ".LFUN_00148440_13:\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "fstp %%st(0)\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00148440_14:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00148440_15\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00148440_16\n\t"
      ".LFUN_00148440_15:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148440_16\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      ".LFUN_00148440_16:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00148440_18\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00148440_19\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00148440_19\n\t"
      ".LFUN_00148440_17:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl %%ecx, 0xc(%%ebp)\n\t"
      ".LFUN_00148440_18:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%edx, -0x4(%%ebp)\n\t"
      ".LFUN_00148440_19:\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%dl\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x4(%%edi,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c148440]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "movb %%al, 0xf(%%ebp)\n\t"
      "je .LFUN_00148440_20\n\t"
      "movl 0x18(%%esi), %%ecx\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps (%%ecx)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00148440_24\n\t"
      "movl (%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x14(%%ebp)\n\t"
      ".LFUN_00148440_20:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl (%%edi), %%eax\n\t"
      "je .LFUN_00148440_21\n\t"
      "orl $0x80000000, %%eax\n\t"
      "jmp .LFUN_00148440_22\n\t"
      ".LFUN_00148440_21:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      ".LFUN_00148440_22:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movzbl %%bl, %%ecx\n\t"
      "movl 0x4(%%edi,%%ecx,4), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c148440]\n\t"
      "movb 0xf(%%ebp), %%cl\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orb %%cl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148440_23:\n\t"
      "movl (%%eax), %%edx\n\t"
      "movl 0x1c(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "movl %%edx, 0x4(%%ecx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%ecx)\n\t"
      ".LFUN_00148440_24:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00148440_25:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b148440_elem), [c148440] "m"(b148440_c148440)
      : "memory");
}
#else
#error "FUN_00148440: clang naked draft required"
#endif


/* collision_bsp_test_pill_new (0x148b20) — readable C (pack pill state, seed FLT_MAX, walk). */
char collision_bsp_test_pill_new(int bsp, short flags, int breakable_surfaces, int origin, int direction, float radius, float *result, float *normal_out)
{
  collision_bsp_pill_state state;

  state.bsp = bsp;
  state.flags = (unsigned short)flags;
  state.breakable_surfaces = breakable_surfaces;
  state.origin = (float *)origin;
  state.direction = (float *)direction;
  state.radius = radius;
  state.result = result;
  state.normal_out = normal_out;
  state.field_20 = -1;
  state.leaf_side = 0;
  state.plane_index = -1;
  *(unsigned int *)result = 0x7f7fffffu;
  return FUN_00148440(&state, 0, 0.0f, 1.0f);
}


/* FUN_00149570 (0x149570) — XBE naked draft (batch 227). */
#if defined(__clang__)
static void *(*const b149570_elem)(void *, int, int) = tag_block_get_element;
static char (*const b149570_c149570)(void *state, int node_index) = (void *)FUN_00149570;
static char (*const b149570_c1491d0)(void *state /* */, int surface_index) = (void *)FUN_001491d0;

__attribute__((naked, noinline))
char FUN_00149570(void *state __attribute__((unused)), int node_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "js .LFUN_00149570_8\n\t"
      "pushl %%edi\n\t"
      "pushl $0x14\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "addl $0x30, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds 0x220(%%esi)\n\t"
      "movl %%eax, %%edi\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "addl $0xc, %%esp\n\t"
      "flds (%%edi)\n\t"
      "fmuls 0x21c(%%esi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "flds 0x228(%%esi)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "flds 0x224(%%esi)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fadds 0x29cb64\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149570_1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149570_2\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_00149570_3\n\t"
      ".LFUN_00149570_1:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00149570_2:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00149570_3:\n\t"
      "flds 0xc(%%esi)\n\t"
      "fchs\n\t"
      "fsubs 0x29cb64\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00149570_4\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00149570_4\n\t"
      "xorb %%bl, %%bl\n\t"
      "jmp .LFUN_00149570_5\n\t"
      ".LFUN_00149570_4:\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_00149570_5:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00149570_6\n\t"
      "movl 0xc(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c149570]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00149570_7\n\t"
      ".LFUN_00149570_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .LFUN_00149570_10\n\t"
      "movl 0x10(%%edi), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c149570]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149570_10\n\t"
      ".LFUN_00149570_7:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149570_8:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1491d0]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149570_9\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149570_9:\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149570_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      "nop\n\t"
      :
      : [elem] "m"(b149570_elem), [c149570] "m"(b149570_c149570), [c1491d0] "m"(b149570_c1491d0)
      : "memory");
}
#else
#error "FUN_00149570: clang naked draft required"
#endif



/* -------------------------------------------------------------------------
 * FUN_00149680 (0x149680) — pill BSP recursive walker (vector+radius).
 *
 * Sibling of FUN_00148eb0 for the pill path. State:
 *   +0 bsp, +4 origin*, +8 dir*, +0xc radius, +0x10 result*,
 *   +0x14 plane_stack_count, +0x18 plane_stack[], +0x218 projection,
 *   +0x21a sign, +0x21c… point2d working area.
 * Leaf: project hit → bsp2d surface → FUN_00148240 → fill result; also
 * tries FUN_00149570 on projected origin for edge hits.
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

/* FUN_00149680 (0x149680) — XBE naked draft (batch 2269). */
#if defined(__clang__)
static void *(*const b149680_elem)(void *, int, int) = tag_block_get_element;
static void (*const b149680_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b149680_exitfn)(int) = system_exit;
static char (*const b149680_c149680)(void *state, int node_index) = (void *)FUN_00149680;
static void (*const b149680_c61df0)(void *point, short projection, unsigned char sign, void *out_projected) = (void *)FUN_00061df0;
static uint32_t (*const b149680_c146d40)(void *bsp2d_nodes, float *point2d, int node_index) = (void *)FUN_00146d40;
static char (*const b149680_c148240)(int bsp /* */, unsigned short flags, int breakable_surfaces, int surface_index, int projection, int sign, float *point2d) = (void *)FUN_00148240;
static char (*const b149680_c149570)(void *state, int node_index) = (void *)FUN_00149570;

__attribute__((naked, noinline))
char FUN_00149680(void *state __attribute__((unused)), int node_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x4c, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "xorb %%bl, %%bl\n\t"
      "testl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "js .LFUN_00149680_14\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl (%%esi), %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%ecx\n\t"
      "pushl $0x10\n\t"
      "pushl %%ecx\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "flds 0x8(%%ecx)\n\t"
      "addl $0x18, %%esp\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%ecx)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "fmuls (%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%eax)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsts -0x10(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "flds 0xc(%%esi)\n\t"
      "fadds 0x29ca28\n\t"
      "fld %%st(1)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149680_1\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $0x41, %%ah\n\t"
      "jnp .LFUN_00149680_2\n\t"
      "xorb %%cl, %%cl\n\t"
      "jmp .LFUN_00149680_3\n\t"
      ".LFUN_00149680_1:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00149680_2:\n\t"
      "movb $1, %%cl\n\t"
      ".LFUN_00149680_3:\n\t"
      "flds 0xc(%%esi)\n\t"
      "fchs\n\t"
      "fsubs 0x29ca28\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fcomps -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00149680_4\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps -0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00149680_4\n\t"
      "xorb %%al, %%al\n\t"
      "jmp .LFUN_00149680_5\n\t"
      ".LFUN_00149680_4:\n\t"
      "movb $1, %%al\n\t"
      ".LFUN_00149680_5:\n\t"
      "testb %%cl, %%cl\n\t"
      "je .LFUN_00149680_13\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_13\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00149680_6\n\t"
      "movb $1, %%bl\n\t"
      "jmp .LFUN_00149680_7\n\t"
      ".LFUN_00149680_6:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".LFUN_00149680_7:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jl .LFUN_00149680_8\n\t"
      "cmpl $0x80, %%eax\n\t"
      "jl .LFUN_00149680_9\n\t"
      ".LFUN_00149680_8:\n\t"
      "pushl $1\n\t"
      "pushl $0x498\n\t"
      "pushl $0x29cafc\n\t"
      "pushl $0x29cb24\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149680_9:\n\t"
      "testb %%bl, %%bl\n\t"
      "movl (%%edi), %%eax\n\t"
      "je .LFUN_00149680_10\n\t"
      "orl $0x80000000, %%eax\n\t"
      "jmp .LFUN_00149680_11\n\t"
      ".LFUN_00149680_10:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      ".LFUN_00149680_11:\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "movl %%eax, 0x18(%%esi,%%ecx,4)\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "incl %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%dl\n\t"
      "movl %%ecx, 0x14(%%esi)\n\t"
      "movl 0x4(%%edi,%%edx,4), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c149680]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_12\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00149680_12:\n\t"
      "movl 0x14(%%esi), %%eax\n\t"
      "movzbl %%bl, %%ecx\n\t"
      "decl %%eax\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movl 0x4(%%edi,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c149680]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_34\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149680_13:\n\t"
      "movzbl %%al, %%eax\n\t"
      "movl 0x4(%%edi,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c149680]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_35\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149680_14:\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .LFUN_00149680_35\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl (%%esi), %%edx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "movl %%eax, %%edi\n\t"
      "pushl $8\n\t"
      "addl $0x18, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, -0x20(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "movswl 0x2(%%eax), %%eax\n\t"
      "addl %%ebx, %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "jge .LFUN_00149680_32\n\t"
      ".LFUN_00149680_15:\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $8\n\t"
      "addl $0x24, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "xorl %%edx, %%edx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .LFUN_00149680_31\n\t"
      "movl (%%eax), %%eax\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00149680_16:\n\t"
      "cmpl %%eax, 0x18(%%esi,%%ecx,4)\n\t"
      "je .LFUN_00149680_17\n\t"
      "movl 0x14(%%esi), %%edi\n\t"
      "incl %%edx\n\t"
      "movswl %%dx, %%ecx\n\t"
      "cmpl %%edi, %%ecx\n\t"
      "jl .LFUN_00149680_16\n\t"
      "jmp .LFUN_00149680_31\n\t"
      ".LFUN_00149680_17:\n\t"
      "movl (%%esi), %%edx\n\t"
      "pushl $0x10\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "flds 0x8(%%eax)\n\t"
      "addl $0xc, %%esp\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .LFUN_00149680_19\n\t"
      "flds 0x2533c8\n\t"
      "fdivs -0xc(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fchs\n\t"
      "fxch %%st(1)\n\t"
      "fabs\n\t"
      "fmuls 0xc(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fsts 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00149680_18\n\t"
      "movl $0, 0xc(%%ebp)\n\t"
      "jmp .LFUN_00149680_19\n\t"
      ".LFUN_00149680_18:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00149680_19\n\t"
      "movl $0x3f800000, 0xc(%%ebp)\n\t"
      ".LFUN_00149680_19:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "flds (%%eax)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00149680_31\n\t"
      "flds (%%edi)\n\t"
      "fabs\n\t"
      "flds 0x4(%%edi)\n\t"
      "fabs\n\t"
      "flds 0x8(%%edi)\n\t"
      "fabs\n\t"
      "fcom %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00149680_20\n\t"
      "fcomp %%st(2)\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00149680_21\n\t"
      "fstp %%st(0)\n\t"
      "movl $2, %%ebx\n\t"
      "fstp %%st(0)\n\t"
      "jmp .LFUN_00149680_23\n\t"
      ".LFUN_00149680_20:\n\t"
      "fstp %%st(0)\n\t"
      ".LFUN_00149680_21:\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00149680_22\n\t"
      "movl $1, %%ebx\n\t"
      "jmp .LFUN_00149680_23\n\t"
      ".LFUN_00149680_22:\n\t"
      "xorl %%ebx, %%ebx\n\t"
      ".LFUN_00149680_23:\n\t"
      "testw %%bx, %%bx\n\t"
      "movw %%bx, 0x218(%%esi)\n\t"
      "jl .LFUN_00149680_24\n\t"
      "cmpw $2, %%bx\n\t"
      "jle .LFUN_00149680_25\n\t"
      ".LFUN_00149680_24:\n\t"
      "pushl $1\n\t"
      "pushl $0x350\n\t"
      "pushl $0x25ed80\n\t"
      "pushl $0x25ed5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00149680_25:\n\t"
      "movswl %%bx, %%ecx\n\t"
      "flds (%%edi,%%ecx,4)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_00149680_26\n\t"
      "movl $1, %%eax\n\t"
      "jmp .LFUN_00149680_27\n\t"
      ".LFUN_00149680_26:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".LFUN_00149680_27:\n\t"
      "movl -0x10(%%ebp), %%ebx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movl (%%ebx), %%edx\n\t"
      "movl 0x4(%%esi), %%ecx\n\t"
      "andl $0x80000000, %%edx\n\t"
      "negl %%edx\n\t"
      "sbbl %%edx, %%edx\n\t"
      "negl %%edx\n\t"
      "movzbl %%al, %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "setne %%dl\n\t"
      "movb %%dl, 0x21a(%%esi)\n\t"
      "fmuls (%%eax)\n\t"
      "fadds (%%ecx)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "leal -0x34(%%ebp), %%eax\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fsts -0x2c(%%ebp)\n\t"
      "xorl %%edx, %%edx\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "movw 0x218(%%esi), %%dx\n\t"
      "fld %%st(2)\n\t"
      "fmuls (%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "pushl %%edx\n\t"
      "fld %%st(1)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x4(%%edi)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fmuls (%%edi)\n\t"
      "fadd %%st(2), %%st(0)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds -0x2c(%%ebp)\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "call *%[c61df0]\n\t"
      "movl 0x4(%%ebx), %%ecx\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl $0x30, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c146d40]\n\t"
      "movl %%eax, %%ebx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movb 0x21a(%%esi), %%dl\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x218(%%esi), %%ax\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "movl (%%esi), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl $0\n\t"
      "pushl $0\n\t"
      "call *%[c148240]\n\t"
      "addl $0x34, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_30\n\t"
      "movl (%%esi), %%ecx\n\t"
      "pushl $0xc\n\t"
      "addl $0x3c, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl (%%ecx), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_00149680_28\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "flds (%%edi)\n\t"
      "fchs\n\t"
      "addl $4, %%eax\n\t"
      "fstps (%%eax)\n\t"
      "flds 0x4(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x4(%%eax)\n\t"
      "flds 0x8(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0x8(%%eax)\n\t"
      "flds 0xc(%%edi)\n\t"
      "fchs\n\t"
      "fstps 0xc(%%eax)\n\t"
      "jmp .LFUN_00149680_29\n\t"
      ".LFUN_00149680_28:\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "addl $4, %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, 0xc(%%edx)\n\t"
      ".LFUN_00149680_29:\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl %%ebx, 0x14(%%ecx)\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movw 0xa(%%eax), %%cx\n\t"
      "movw %%cx, 0x1a(%%edx)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00149680_30:\n\t"
      "flds -0x18(%%ebp)\n\t"
      "movl 0x4(%%esi), %%eax\n\t"
      "fchs\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "movw 0x218(%%esi), %%cx\n\t"
      "leal 0x21c(%%esi), %%edx\n\t"
      "pushl %%edx\n\t"
      "fadds (%%eax)\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "fstps -0x40(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x3c(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movb 0x21a(%%esi), %%al\n\t"
      "fstps -0x38(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c61df0]\n\t"
      "flds -0xc(%%ebp)\n\t"
      "movl 0x8(%%esi), %%eax\n\t"
      "fchs\n\t"
      "fld %%st(0)\n\t"
      "fmuls (%%edi)\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movb 0x21a(%%esi), %%cl\n\t"
      "xorl %%edx, %%edx\n\t"
      "fadds (%%eax)\n\t"
      "movw 0x218(%%esi), %%dx\n\t"
      "fstps -0x4c(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%eax)\n\t"
      "fstps -0x48(%%ebp)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%eax)\n\t"
      "leal 0x224(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "fstps -0x44(%%ebp)\n\t"
      "leal -0x4c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c61df0]\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c149570]\n\t"
      "movl -0x14(%%ebp), %%ebx\n\t"
      "addl $0x28, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00149680_31\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_00149680_31:\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "movswl 0x2(%%eax), %%ecx\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "incl %%ebx\n\t"
      "addl %%edx, %%ecx\n\t"
      "cmpl %%ecx, %%ebx\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "jl .LFUN_00149680_15\n\t"
      "movl -0x20(%%ebp), %%edi\n\t"
      ".LFUN_00149680_32:\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl 0x1c(%%eax), %%ecx\n\t"
      "cmpl $0x100, %%ecx\n\t"
      "jge .LFUN_00149680_33\n\t"
      "movl %%edi, 0x20(%%eax,%%ecx,4)\n\t"
      "movl 0x10(%%esi), %%esi\n\t"
      "movl 0x1c(%%esi), %%eax\n\t"
      "incl %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x1c(%%esi)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149680_33:\n\t"
      "movl %%edi, 0x41c(%%eax)\n\t"
      ".LFUN_00149680_34:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00149680_35:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b149680_elem), [assert] "m"(b149680_assert), [exitfn] "m"(b149680_exitfn), [c149680] "m"(b149680_c149680), [c61df0] "m"(b149680_c61df0), [c146d40] "m"(b149680_c146d40), [c148240] "m"(b149680_c148240), [c149570] "m"(b149680_c149570)
      : "memory");
}
#else
#error "FUN_00149680: clang naked draft required"
#endif



/* -------------------------------------------------------------------------
 * Object / structure query wrappers (collision_bsp.obj high addresses).
 * ported:false until verified.
 * ------------------------------------------------------------------------- */

/* FUN_0014dc30 (0x14dc30) — readable C lift from XBE leaf.
 * Point-in-structure / cluster object collision probe. */
char FUN_0014dc30(int flags, float *pos, int param_3)
{
  uint32_t leaf;
  char check_objects;
  int cluster;
  int obj;
  int flags_save;
  int iter;

  if ((flags & 0xe0) == 0)
    return 0;
  flags_save = flags;
  leaf = bsp3d_find_leaf(FUN_0018e420(), 0, pos);
  check_objects = (char)((flags_save >> 7) & 1);
  if (*(unsigned char *)0x4761f8)
    check_objects = 0;
  if ((int)leaf == -1)
    return 1;
  if (!check_objects)
    return 0;
  leaf &= 0x7fffffffu;
  cluster = *(short *)((char *)tag_block_get_element(
                           (char *)scenario_get() + 0xe0, (int)leaf, 0x10) +
                       8);
  iter = flags_save;
  obj = cluster_partition_object_iter_first(&iter, (int16_t)cluster);
  while (obj != -1) {
    if (FUN_0014db10(obj, flags_save, (int)pos, param_3))
      return 1;
    obj = cluster_partition_object_iter_next(&iter);
  }
  return 0;
}

/* FUN_0014e7d0 (0x14e7d0) — XBE naked draft (batch 232). */
#if defined(__clang__)
static void *(*const b14e7d0_gbsp)(void) = global_collision_bsp_get;
static char (*const b14e7d0_c149c60)(int *block_ptr, void *transformed_2c, void *transformed_20, float scale, float best_dist, float *result) = (void *)FUN_00149c60;
static void * (*const b14e7d0_c18e3c0)(void) = (void *)scenario_get;
static void *(*const b14e7d0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b14e7d0_c18f180)(void *location_out, void *point) = (void *)scenario_location_from_point;

__attribute__((naked, noinline))
char FUN_0014e7d0(uint32_t collision_flags __attribute__((unused)), float *point __attribute__((unused)), float *offset_vec __attribute__((unused)), float p4 __attribute__((unused)), int unit_handle __attribute__((unused)), void *result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x420, %%esp\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x1c(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "leal -0x420(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl $0x7f7fffff\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "xorb %%bl, %%bl\n\t"
      "movw $0xffff, (%%esi)\n\t"
      "movl $0x7f7fffff, 0x14(%%esi)\n\t"
      "call *%[gbsp]\n\t"
      "pushl %%eax\n\t"
      "call *%[c149c60]\n\t"
      "addl $0x18, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014e7d0_1\n\t"
      "movl -0x420(%%ebp), %%eax\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "testb $0x20, 0x8(%%ebp)\n\t"
      "je .LFUN_0014e7d0_1\n\t"
      "movl -0x41c(%%ebp), %%edx\n\t"
      "movl -0x418(%%ebp), %%eax\n\t"
      "leal 0x24(%%esi), %%ecx\n\t"
      "movl %%edx, (%%ecx)\n\t"
      "movl -0x414(%%ebp), %%edx\n\t"
      "movl %%eax, 0x4(%%ecx)\n\t"
      "movl -0x410(%%ebp), %%eax\n\t"
      "movl %%edx, 0x8(%%ecx)\n\t"
      "movl %%eax, 0xc(%%ecx)\n\t"
      "movw -0x406(%%ebp), %%ax\n\t"
      "movl -0x40c(%%ebp), %%ecx\n\t"
      "movb %%bl, 0x4c(%%esi)\n\t"
      "movb %%bl, 0x4d(%%esi)\n\t"
      "movw $2, (%%esi)\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movl %%ecx, 0x44(%%esi)\n\t"
      "movl $0xffffffff, 0x48(%%esi)\n\t"
      "movw %%ax, 0x4e(%%esi)\n\t"
      "movb $1, %%bl\n\t"
      ".LFUN_0014e7d0_1:\n\t"
      "movl -0x404(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .LFUN_0014e7d0_6\n\t"
      "movl -0x400(%%ebp), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "jne .LFUN_0014e7d0_2\n\t"
      "orl %%eax, %%eax\n\t"
      "jmp .LFUN_0014e7d0_3\n\t"
      ".LFUN_0014e7d0_2:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0014e7d0_3:\n\t"
      "movl -0x404(%%ebp), %%edx\n\t"
      "movw %%ax, 0x8(%%esi)\n\t"
      "movl -0x404(%%ebp,%%edx,4), %%eax\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, 0xc(%%esi)\n\t"
      "jne .LFUN_0014e7d0_4\n\t"
      "orl %%eax, %%eax\n\t"
      "jmp .LFUN_0014e7d0_5\n\t"
      ".LFUN_0014e7d0_4:\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "call *%[c18e3c0]\n\t"
      "addl $0xe0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movswl 0x8(%%eax), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_0014e7d0_5:\n\t"
      "movw %%ax, 0x10(%%esi)\n\t"
      ".LFUN_0014e7d0_6:\n\t"
      "testb %%bl, %%bl\n\t"
      "jne .LFUN_0014e7d0_7\n\t"
      "movl $0x3f800000, 0x14(%%esi)\n\t"
      ".LFUN_0014e7d0_7:\n\t"
      "flds 0x14(%%esi)\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "fld %%st(0)\n\t"
      "leal 0x18(%%esi), %%eax\n\t"
      "fmuls (%%edi)\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%esi\n\t"
      "pushl %%esi\n\t"
      "fadds (%%ecx)\n\t"
      "fstps (%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmuls 0x4(%%edi)\n\t"
      "fadds 0x4(%%ecx)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fmuls 0x8(%%edi)\n\t"
      "fadds 0x8(%%ecx)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[c18f180]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [gbsp] "m"(b14e7d0_gbsp), [c149c60] "m"(b14e7d0_c149c60), [c18e3c0] "m"(b14e7d0_c18e3c0), [elem] "m"(b14e7d0_elem), [c18f180] "m"(b14e7d0_c18f180)
      : "memory");
}
#else
#error "FUN_0014e7d0: clang naked draft required"
#endif


/* FUN_0014e940 (0x14e940) — readable C lift from XBE leaf.
 * Pill test against global collision BSP; fills a collision-result blob. */
char FUN_0014e940(int unused, float *origin, float *direction, float radius,
                  int pad0, void *result)
{
  float t;
  float normal[3];
  char hit;
  unsigned char *res;
  float *res_f;
  void *bsp;
  unsigned int flt_max_bits;
  (void)unused;
  (void)pad0;

  res = (unsigned char *)result;
  res_f = (float *)result;

  *(short *)(res + 0x00) = (short)-1;
  *(int *)(res + 0x04) = -1;
  *(short *)(res + 0x08) = (short)-1;
  *(int *)(res + 0x0c) = -1;
  *(short *)(res + 0x10) = (short)-1;
  res_f[5] = 1.0f; /* +0x14 */
  hit = 0;
  t = 0.0f;

  bsp = global_collision_bsp_get();
  if (collision_bsp_test_pill_new((int)bsp, 0, 0, (int)origin, (int)direction,
                                  radius, &t, normal)) {
    res_f[5] = t;
    res_f[9] = normal[0];
    res_f[10] = normal[1];
    res_f[11] = normal[2];
    *(short *)(res + 0x00) = 2;
    flt_max_bits = 0x7f7fffffu;
    res_f[12] = *(float *)&flt_max_bits; /* +0x30 */
    *(short *)(res + 0x34) = (short)-1;
    *(int *)(res + 0x44) = -1;
    *(int *)(res + 0x48) = -1;
    res[0x4c] = 0;
    res[0x4d] = 0;
    *(short *)(res + 0x4e) = (short)-1;
    hit = 1;
  }

  t = res_f[5];
  res_f[6] = origin[0] + t * direction[0];
  res_f[7] = origin[1] + t * direction[1];
  res_f[8] = origin[2] + t * direction[2];
  res_f[9] = 0.0f;
  res_f[10] = 0.0f;
  res_f[11] = 0.0f;
  return hit;
}


/* FUN_0014e640 (0x14e640) — readable C lift (restored pre-naked). */
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




/* FUN_0014dce0 (0x14dce0) — XBE naked draft (batch 232). */
#if defined(__clang__)
static void *(*const b14dce0_get)(int, int) = object_get_and_verify_type;
static bool (*const b14dce0_c10bc70)(float *line_start, float *line_end, float *sphere_center, float sphere_radius) = (void *)fast_vector_intersects_sphere;
static char (*const b14dce0_c1509c0)(int *out, int obj_idx) = (void *)FUN_001509c0;
static char (*const b14dce0_c150b60)(void *features, float *origin, float *direction, float *out_t_plane) = (void *)FUN_00150b60;
static int (*const b14dce0_c14c8e0)(int *out, int object_handle) = (void *)FUN_0014c8e0;
static char (*const b14dce0_c14cb00)(int param_1, void *param_2, void *param_3, void *param_4, int16_t *param_5) = (void *)FUN_0014cb00;
static void (*const b14dce0_c10a1c0)(float *matrix, float *in_plane, float *out_plane) = (void *)FUN_0010a1c0;
static void (*const b14dce0_c994d0)(float *plane_in, float *plane_out) = (void *)plane_negate;
static int (*const b14dce0_c14da80)(int tag_data, int16_t collision_fn_index) = (void *)FUN_0014da80;
static char (*const b14dce0_c14dce0)(int object_handle, unsigned int type_mask, int param_3, int origin, int direction, int exclude_handle, void *collision_result) = (void *)FUN_0014dce0;

__attribute__((naked, noinline))
char FUN_0014dce0(int object_handle __attribute__((unused)), unsigned int type_mask __attribute__((unused)), int param_3 __attribute__((unused)), int origin __attribute__((unused)), int direction __attribute__((unused)), int exclude_handle __attribute__((unused)), void *collision_result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x484, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      ".LFUN_0014dce0_1:\n\t"
      "pushl $-1\n\t"
      "pushl %%edi\n\t"
      "call *%[get]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%edi\n\t"
      "movl %%ebx, 0x8(%%ebp)\n\t"
      "je .LFUN_0014dce0_6\n\t"
      "testb $1, 0x4(%%ebx)\n\t"
      "jne .LFUN_0014dce0_6\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x64(%%ebx), %%cx\n\t"
      "movl $1, %%eax\n\t"
      "addl $8, %%ecx\n\t"
      "shll %%cl, %%eax\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "testl %%eax, %%ecx\n\t"
      "je .LFUN_0014dce0_6\n\t"
      "flds 0x5c(%%ebx)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "leal 0x50(%%ebx), %%edx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10bc70]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_6\n\t"
      "movb 0x64(%%ebx), %%cl\n\t"
      "movl $1, %%edx\n\t"
      "shll %%cl, %%edx\n\t"
      "testb $2, %%dl\n\t"
      "je .LFUN_0014dce0_2\n\t"
      "testl $0x400000, 0xc(%%ebp)\n\t"
      "je .LFUN_0014dce0_2\n\t"
      "leal -0x64(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c1509c0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_4\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal -0x18(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x64(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c150b60]\n\t"
      "addl $0x10, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_4\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps -0x18(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0014dce0_4\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "leal 0x24(%%esi), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x14(%%esi)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      "movw $3, (%%esi)\n\t"
      "movl %%edx, 0xc(%%eax)\n\t"
      "movw %%cx, 0x34(%%esi)\n\t"
      "movl %%edi, 0x38(%%esi)\n\t"
      "movw %%cx, 0x3c(%%esi)\n\t"
      "movw %%cx, 0x3e(%%esi)\n\t"
      "movw %%cx, 0x40(%%esi)\n\t"
      "movl %%ecx, 0x44(%%esi)\n\t"
      "movl %%ecx, 0x48(%%esi)\n\t"
      "movb $0, 0x4c(%%esi)\n\t"
      "movb $0, 0x4d(%%esi)\n\t"
      "movw %%cx, 0x4e(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_0014dce0_5\n\t"
      ".LFUN_0014dce0_2:\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[c14c8e0]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_4\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "leal -0x484(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c14cb00]\n\t"
      "addl $0x14, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_4\n\t"
      "flds 0x14(%%esi)\n\t"
      "fcomps -0x47c(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .LFUN_0014dce0_4\n\t"
      "movswl -0x484(%%ebp), %%edx\n\t"
      "movl -0x478(%%ebp), %%ecx\n\t"
      "imull $0x34, %%edx, %%edx\n\t"
      "movl -0x47c(%%ebp), %%eax\n\t"
      "leal 0x24(%%esi), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "addl -0x1c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movw $3, (%%esi)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "call *%[c10a1c0]\n\t"
      "movl -0x470(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .LFUN_0014dce0_3\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c994d0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_0014dce0_3:\n\t"
      "movl -0x46a(%%ebp), %%eax\n\t"
      "movl -0x24(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c14da80]\n\t"
      "movw -0x482(%%ebp), %%dx\n\t"
      "movw -0x480(%%ebp), %%cx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "movw %%ax, 0x34(%%esi)\n\t"
      "movw -0x484(%%ebp), %%ax\n\t"
      "movw %%dx, 0x3c(%%esi)\n\t"
      "movl -0x474(%%ebp), %%edx\n\t"
      "movw %%ax, 0x3e(%%esi)\n\t"
      "movl -0x470(%%ebp), %%eax\n\t"
      "movw %%cx, 0x40(%%esi)\n\t"
      "movb -0x46c(%%ebp), %%cl\n\t"
      "movl %%edx, 0x44(%%esi)\n\t"
      "movb -0x46b(%%ebp), %%dl\n\t"
      "movl %%eax, 0x48(%%esi)\n\t"
      "movw -0x46a(%%ebp), %%ax\n\t"
      "movb %%cl, 0x4c(%%esi)\n\t"
      "addl $8, %%esp\n\t"
      "movl %%edi, 0x38(%%esi)\n\t"
      "movb %%dl, 0x4d(%%esi)\n\t"
      "movw %%ax, 0x4e(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movl $0xffffffff, %%ecx\n\t"
      "jmp .LFUN_0014dce0_5\n\t"
      ".LFUN_0014dce0_4:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_0014dce0_5:\n\t"
      "movl 0xc8(%%ebx), %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_0014dce0_7\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[c14dce0]\n\t"
      "addl $0x1c, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_0014dce0_6\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      ".LFUN_0014dce0_6:\n\t"
      "orl $0xffffffff, %%ecx\n\t"
      ".LFUN_0014dce0_7:\n\t"
      "movl 0xc4(%%ebx), %%edi\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "jne .LFUN_0014dce0_1\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [get] "m"(b14dce0_get), [c10bc70] "m"(b14dce0_c10bc70), [c1509c0] "m"(b14dce0_c1509c0), [c150b60] "m"(b14dce0_c150b60), [c14c8e0] "m"(b14dce0_c14c8e0), [c14cb00] "m"(b14dce0_c14cb00), [c10a1c0] "m"(b14dce0_c10a1c0), [c994d0] "m"(b14dce0_c994d0), [c14da80] "m"(b14dce0_c14da80), [c14dce0] "m"(b14dce0_c14dce0)
      : "memory");
}
#else
#error "FUN_0014dce0: clang naked draft required"
#endif


/* FUN_0014ea10 (0x14ea10) — readable C lift (restored pre-naked). */
char FUN_0014ea10(unsigned int type_mask, int first_handle, float *origin,
                  float radius, float param_5, float param_6, int exclude_handle,
                  int result)
{
  int handle;
  char *obj;
  char hit;
  float dx, dy, dz;
  float rr;
  unsigned int type_bit;
  int type_id;
  int child;

  (void)param_5;
  (void)param_6;
  (void)result;
  hit = 0;
  handle = first_handle;

  while (handle != -1) {
    if (handle != exclude_handle) {
      obj = (char *)object_get_and_verify_type(handle, -1);
      if (obj && (obj[4] & 1) == 0 && (*(int *)(obj + 4) & 0x1000000) == 0) {
        if (!((obj[0xb6] & 4) != 0 && *(short *)(obj + 0x64) == 0)) {
          dx = *(float *)(obj + 0x50) - origin[0];
          dy = *(float *)(obj + 0x54) - origin[1];
          dz = *(float *)(obj + 0x58) - origin[2];
          rr = *(float *)(obj + 0x5c) + radius;
          if (dx * dx + dy * dy + dz * dz <= rr * rr) {
            type_id = *(short *)(obj + 0x64);
            type_bit = 1u << (type_id + 8);
            if ((type_mask & type_bit) != 0) {
              /* TODO: dispatch 0x14ec10 jump table per object type */
              hit = 1;
              child = *(int *)(obj + 0xc8);
              if (child != -1) {
                if (FUN_0014ea10(type_mask, child, origin, radius, param_5,
                                 param_6, exclude_handle, result)) {
                  hit = 1;
                }
              }
            }
          }
        }
      }
    }
    obj = (char *)object_get_and_verify_type(handle, -1);
    if (!obj) {
      break;
    }
    handle = *(int *)(obj + 0xc4);
  }
  return hit;
}

