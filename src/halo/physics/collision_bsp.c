/* collision_bsp.obj (physics/collision_bsp.c)
 *
 * Declarations for tag_block_get_element, display_assert and system_exit come
 * from the generated decl.h via kb.json.
 */

/* collision_surface_edge_count (0x1473b0) — XBE naked draft (batch 93). */
#if defined(__clang__)
static void *(*const b1473b0_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
short collision_surface_edge_count(int bsp __attribute__((unused)), int surface_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "addl $0x3c, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "xorl %%edi, %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x4(%%eax), %%esi\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x48, %%ecx\n\t"
      "movl %%esi, %%eax\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "jmp .Lcollision_surface_edge_count_1\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lcollision_surface_edge_count_1:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "incl %%edi\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "sete %%cl\n\t"
      "movzbl %%cl, %%edx\n\t"
      "movl 0x8(%%eax,%%edx,4), %%eax\n\t"
      "cmpl %%esi, %%eax\n\t"
      "jne .Lcollision_surface_edge_count_1\n\t"
      "movw %%di, %%ax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1473b0_elem)
      : "memory");
}
#else
#error "collision_surface_edge_count: clang naked draft required"
#endif


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

/* render_debug_collision_bsp (0x147660) — XBE naked draft (batch 96). */
#if defined(__clang__)
static void (*const b147660_c147570)(int bsp, int edge_index, int matrix_or_flag, void *color) = render_debug_collision_edge;

__attribute__((naked, noinline))
void render_debug_collision_bsp(int bsp __attribute__((unused)), int matrix_or_flag __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "xorl %%esi, %%esi\n\t"
      "testl %%eax, %%eax\n\t"
      "jle .Lrender_debug_collision_bsp_2\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      ".Lrender_debug_collision_bsp_1:\n\t"
      "movl 0x2ee6d4, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[c147570]\n\t"
      "movl 0x48(%%edi), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "incl %%esi\n\t"
      "cmpl %%eax, %%esi\n\t"
      "jl .Lrender_debug_collision_bsp_1\n\t"
      "popl %%ebx\n\t"
      ".Lrender_debug_collision_bsp_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c147570] "m"(b147660_c147570)
      : "memory");
}
#else
#error "render_debug_collision_bsp: clang naked draft required"
#endif


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

/* collision_surface_perimeter (0x147710) — XBE naked draft (batch 86). */
#if defined(__clang__)
static void *(*const b147710_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
float collision_surface_perimeter(int bsp __attribute__((unused)), int surface_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "leal 0x48(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x54, %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%edi, 0x8(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lcollision_surface_perimeter_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl $0x18\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "cmpl %%ecx, 0x14(%%esi)\n\t"
      "sete %%bl\n\t"
      "movzbl %%bl, %%eax\n\t"
      "movl (%%esi,%%eax,4), %%edx\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "sete %%cl\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, %%edi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl (%%esi,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%edi)\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl 0x8(%%esi,%%ecx,4), %%esi\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "addl $0x24, %%esp\n\t"
      "flds 0x8(%%eax)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "cmpl %%eax, %%esi\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(2)\n\t"
      ".byte 0xde, 0xcb\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fld %%st(1)\n\t"
      ".byte 0xd8, 0xca\n\t"
      ".byte 0xde, 0xc3\n\t"
      "fxch %%st(2)\n\t"
      "fsqrt\n\t"
      "fstp %%st(2)\n\t"
      "fstp %%st(0)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jne .Lcollision_surface_perimeter_1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b147710_elem)
      : "memory");
}
#else
#error "collision_surface_perimeter: clang naked draft required"
#endif


/* collision_surface_area (0x1477f0) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void *(*const b1477f0_elem)(void *, int, int) = tag_block_get_element;
static void (*const b1477f0_c99640)(int structure_bsp, uint32_t plane_reference, float *out_plane) = bsp3d_get_plane_from_designator;

__attribute__((naked, noinline))
float collision_surface_area(int bsp __attribute__((unused)), int surface_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x3c, %%esp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl $0xc\n\t"
      "leal 0x3c(%%esi), %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl $0, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "pushl $0x18\n\t"
      "leal 0x48(%%esi), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "cmpl %%edi, 0x14(%%ebx)\n\t"
      "sete %%al\n\t"
      "movzbl %%al, %%ecx\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      "movl (%%ebx,%%ecx,4), %%ecx\n\t"
      "pushl $0x10\n\t"
      "leal 0x54(%%esi), %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal -0x3c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c99640]\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movl 0x8(%%ebx,%%edx,4), %%eax\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%esi), %%ebx\n\t"
      "addl $0x3c, %%esp\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "sete %%al\n\t"
      "movzbl %%al, %%ebx\n\t"
      "movb %%al, 0xb(%%ebp)\n\t"
      "movl 0x8(%%esi,%%ebx,4), %%eax\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lcollision_surface_area_2\n\t"
      ".Lcollision_surface_area_1:\n\t"
      "movl (%%esi,%%ebx,4), %%edx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movb 0xb(%%ebp), %%dl\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "testb %%dl, %%dl\n\t"
      "sete %%cl\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "movl (%%esi,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "fsubs (%%edi)\n\t"
      "pushl $0x18\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "movl 0x8(%%esi,%%ebx,4), %%ecx\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "pushl %%ecx\n\t"
      "flds (%%eax)\n\t"
      "pushl %%edx\n\t"
      "fsubs (%%edi)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%edi)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%edi)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xca\n\t"
      "flds -0x20(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xea\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x34(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x38(%%ebp)\n\t"
      "fmuls -0x28(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x3c(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[elem]\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "movl 0x14(%%esi), %%ecx\n\t"
      "addl $0x24, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "sete %%al\n\t"
      "movzbl %%al, %%ebx\n\t"
      "movl 0x8(%%esi,%%ebx,4), %%ecx\n\t"
      "movb %%al, 0xb(%%ebp)\n\t"
      "cmpl 0x4(%%edx), %%ecx\n\t"
      "jne .Lcollision_surface_area_1\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcollision_surface_area_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcollision_surface_area_2:\n\t"
      "flds 0x2533c0\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b1477f0_elem), [c99640] "m"(b1477f0_c99640)
      : "memory");
}
#else
#error "collision_surface_area: clang naked draft required"
#endif


/* collision_surface_test_line2d (0x147d10) — XBE naked draft (batch 82). */
#if defined(__clang__)
static void *(*const b147d10_elem)(void *, int, int) = tag_block_get_element;

__attribute__((naked, noinline))
int collision_surface_test_line2d(int bsp __attribute__((unused)), int surface_index __attribute__((unused)), int param3 __attribute__((unused)), int param4 __attribute__((unused)), float *point __attribute__((unused)), float *direction __attribute__((unused)), float *out_result __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%eax\n\t"
      "leal 0x3c(%%edi), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%eax), %%eax\n\t"
      "movl 0x20(%%ebp), %%esi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "leal 0x48(%%edi), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "addl $0x54, %%edi\n\t"
      "movl $0xff7fffff, (%%esi)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "movl %%eax, 0x8(%%esi)\n\t"
      "movl $0x7f7fffff, 0xc(%%esi)\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "movl %%edx, -0xc(%%ebp)\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      ".Lcollision_surface_test_line2d_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl $0x18\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl 0x14(%%edi), %%ebx\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "cmpl %%edx, %%ebx\n\t"
      "pushl %%ecx\n\t"
      "sete 0xb(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl 0x4(%%edi), %%edx\n\t"
      "pushl $0x10\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "addl $0x24, %%esp\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fld %%st(2)\n\t"
      "fmuls (%%eax)\n\t"
      "fld %%st(4)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x20(%%ebp)\n\t"
      ".byte 0xde, 0xcb\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xea\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jnp .Lcollision_surface_test_line2d_5\n\t"
      "fdivs 0x20(%%ebp)\n\t"
      "flds 0x20(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcollision_surface_test_line2d_2\n\t"
      "movl $1, %%eax\n\t"
      "jmp .Lcollision_surface_test_line2d_3\n\t"
      ".Lcollision_surface_test_line2d_2:\n\t"
      "xorl %%eax, %%eax\n\t"
      ".Lcollision_surface_test_line2d_3:\n\t"
      "movb 0xb(%%ebp), %%cl\n\t"
      "movzbl %%cl, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "je .Lcollision_surface_test_line2d_4\n\t"
      "fcoms (%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcollision_surface_test_line2d_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps (%%esi)\n\t"
      "movl %%eax, 0x4(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%al\n\t"
      "movl 0x10(%%edi,%%eax,4), %%ecx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "jmp .Lcollision_surface_test_line2d_9\n\t"
      ".Lcollision_surface_test_line2d_4:\n\t"
      "fcoms 0xc(%%esi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcollision_surface_test_line2d_8\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps 0xc(%%esi)\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "testb %%cl, %%cl\n\t"
      "sete %%al\n\t"
      "movl 0x10(%%edi,%%eax,4), %%ecx\n\t"
      "movl %%ecx, 0x14(%%esi)\n\t"
      "jmp .Lcollision_surface_test_line2d_9\n\t"
      ".Lcollision_surface_test_line2d_5:\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lcollision_surface_test_line2d_6\n\t"
      "movl $1, %%ecx\n\t"
      "jmp .Lcollision_surface_test_line2d_7\n\t"
      ".Lcollision_surface_test_line2d_6:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      ".Lcollision_surface_test_line2d_7:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "movzbl %%al, %%edx\n\t"
      "cmpl %%edx, %%ecx\n\t"
      "je .Lcollision_surface_test_line2d_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "testb %%al, %%al\n\t"
      "sete %%bl\n\t"
      "movl $0x7f7fffff, (%%esi)\n\t"
      "movl %%ecx, 0x4(%%esi)\n\t"
      "leal 0x10(%%edi,%%ebx,4), %%eax\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl %%ebx, 0x8(%%esi)\n\t"
      "movl $0xff7fffff, 0xc(%%esi)\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "movl (%%eax), %%eax\n\t"
      "movl %%eax, 0x14(%%esi)\n\t"
      "jmp .Lcollision_surface_test_line2d_9\n\t"
      ".Lcollision_surface_test_line2d_8:\n\t"
      "fstp %%st(0)\n\t"
      ".Lcollision_surface_test_line2d_9:\n\t"
      "movl 0x8(%%edi,%%edx,4), %%edi\n\t"
      "cmpl -0x10(%%ebp), %%edi\n\t"
      "movl %%edi, -0x4(%%ebp)\n\t"
      "jne .Lcollision_surface_test_line2d_1\n\t"
      "flds (%%esi)\n\t"
      "popl %%edi\n\t"
      "fcomps 0xc(%%esi)\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lcollision_surface_test_line2d_10\n\t"
      "movl $1, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lcollision_surface_test_line2d_10:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b147d10_elem)
      : "memory");
}
#else
#error "collision_surface_test_line2d: clang naked draft required"
#endif



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



/* 0x14dce0 — test one object (and children/siblings) against a segment. */
char FUN_0014dce0(int object_handle, unsigned int type_mask, int param_3,
                  int origin, int direction, int exclude_handle,
                  void *collision_result)
{
  char *result;
  char *obj;
  char hit;
  unsigned int type_bit;
  float *origin_v;
  float *dir_v;
  float radius;
  char xform[0x28];
  char hit_buf[0x484];
  char features[0x64];
  float out_plane[5];
  float t_hit;
  int child;
  short first_idx;
  int node_base;
  int plane_src;
  short mat;

  result = (char *)collision_result;
  hit = 0;
  origin_v = (float *)origin;
  dir_v = (float *)direction;

  while (object_handle != -1) {
    if (object_handle == exclude_handle) {
      obj = (char *)object_get_and_verify_type(object_handle, -1);
      if (!obj) {
        break;
      }
      object_handle = *(int *)(obj + 0xc4);
      continue;
    }

    obj = (char *)object_get_and_verify_type(object_handle, -1);
    if (!obj || (obj[4] & 1) != 0) {
      goto advance;
    }
    type_bit = 1u << ((unsigned)(*(unsigned short *)(obj + 0x64)) + 8);
    if ((type_mask & type_bit) == 0) {
      goto advance;
    }

    radius = *(float *)(obj + 0x5c);
    if (!fast_vector_intersects_sphere(origin_v, dir_v, (float *)(obj + 0x50),
                                       radius)) {
      goto advance;
    }

    if ((type_bit & 2) != 0 && (type_mask & 0x400000) != 0) {
      if (FUN_001509c0((int *)features, object_handle) &&
          FUN_00150b60(features, origin_v, dir_v, out_plane)) {
        t_hit = out_plane[0];
        if (*(float *)(result + 0x14) > t_hit) {
          *(float *)(result + 0x14) = t_hit;
          *(float *)(result + 0x24) = out_plane[1];
          *(float *)(result + 0x28) = out_plane[2];
          *(float *)(result + 0x2c) = out_plane[3];
          *(float *)(result + 0x30) = out_plane[4];
          *(short *)result = 3;
          hit = 1;
        }
      }
    } else if (FUN_0014c8e0((int *)xform, object_handle) &&
               FUN_0014cb00((int)(int *)xform, (void *)param_3, origin_v, dir_v,
                            (int16_t *)hit_buf)) {
      t_hit = *(float *)(hit_buf + 8);
      if (*(float *)(result + 0x14) > t_hit) {
        first_idx = *(short *)hit_buf;
        *(float *)(result + 0x14) = t_hit;
        *(short *)result = 3;
        node_base = *(int *)(xform + 0xc);
        plane_src = node_base + (int)first_idx * 0x34;
        FUN_0010a1c0((float *)plane_src, *(float **)(hit_buf + 0xc),
                     (float *)(result + 0x24));
        if (*(int *)(hit_buf + 0x14) < 0) {
          plane_negate((float *)(result + 0x24), (float *)(result + 0x24));
        }
        mat = (short)FUN_0014da80(*(int *)(xform + 4),
                                  *(short *)(hit_buf + 0x1a));
        *(short *)(result + 0x34) = mat;
        *(int *)(result + 0x38) = object_handle;
        *(short *)(result + 0x3c) = *(short *)(hit_buf + 2);
        *(short *)(result + 0x3e) = first_idx;
        *(short *)(result + 0x40) = *(short *)(hit_buf + 4);
        *(int *)(result + 0x44) = *(int *)(hit_buf + 0x10);
        *(int *)(result + 0x48) = *(int *)(hit_buf + 0x14);
        result[0x4c] = hit_buf[0x18];
        result[0x4d] = hit_buf[0x19];
        *(short *)(result + 0x4e) = *(short *)(hit_buf + 0x1a);
        hit = 1;
      }
    }

    child = *(int *)(obj + 0xc8);
    if (child != -1) {
      if (FUN_0014dce0(child, type_mask, param_3, origin, direction,
                       exclude_handle, collision_result)) {
        hit = 1;
      }
    }

  advance:
    obj = (char *)object_get_and_verify_type(object_handle, -1);
    if (!obj) {
      break;
    }
    object_handle = *(int *)(obj + 0xc4);
  }
  return hit;
}

/* 0x14ea10 — sphere vs object list. Type jump-table not fully lifted yet. */
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
