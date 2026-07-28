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

/* bsp3d_clip_line_to_leaves (0x146e30) — XBE naked draft (batch 80). */
#if defined(__clang__)
static void *(*const b146e30_elem)(void *, int, int) = tag_block_get_element;
static void (*const b146e30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b146e30_exitfn)(int) = system_exit;
static int (*const b146e30_c146e30)(void *nodes, int node_index, float *p0, float *p1, void (*callback)(float *, float *, unsigned int, void *), void *data) = bsp3d_clip_line_to_leaves;

__attribute__((naked, noinline))
int bsp3d_clip_line_to_leaves(void *nodes __attribute__((unused)), int node_index __attribute__((unused)), float *p0 __attribute__((unused)), float *p1 __attribute__((unused)), void (*callback)(float * __attribute__((unused)), float * __attribute__((unused)), unsigned int __attribute__((unused)), void *) __attribute__((unused)), void *data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x28, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0x8(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0xc\n\t"
      "pushl %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl $0, -0xc(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movl (%%edi), %%eax\n\t"
      "pushl $0x10\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "addl $0x18, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%eax)\n\t"
      "flds (%%eax)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%ecx)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_1\n\t"
      "movl %%esi, 0x5a8d20\n\t"
      ".Lbsp3d_clip_line_to_leaves_1:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movl 0x5a8d20, %%eax\n\t"
      "fcomps 0x29ca2c\n\t"
      "incl %%eax\n\t"
      "movl %%eax, 0x5a8d20\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lbsp3d_clip_line_to_leaves_2\n\t"
      "movb $1, %%dl\n\t"
      "jmp .Lbsp3d_clip_line_to_leaves_3\n\t"
      ".Lbsp3d_clip_line_to_leaves_2:\n\t"
      "xorb %%dl, %%dl\n\t"
      ".Lbsp3d_clip_line_to_leaves_3:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "movb %%dl, 0xe(%%ebp)\n\t"
      "fcomps 0x29ca28\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lbsp3d_clip_line_to_leaves_4\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      ".Lbsp3d_clip_line_to_leaves_4:\n\t"
      "fcoms 0x29ca2c\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lbsp3d_clip_line_to_leaves_5\n\t"
      "movb $1, %%bl\n\t"
      "jmp .Lbsp3d_clip_line_to_leaves_6\n\t"
      ".Lbsp3d_clip_line_to_leaves_5:\n\t"
      "xorb %%bl, %%bl\n\t"
      ".Lbsp3d_clip_line_to_leaves_6:\n\t"
      "fcomps 0x29ca28\n\t"
      "movb %%bl, -0x4(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_7\n\t"
      "movb $1, %%al\n\t"
      "jmp .Lbsp3d_clip_line_to_leaves_8\n\t"
      ".Lbsp3d_clip_line_to_leaves_7:\n\t"
      "xorb %%al, %%al\n\t"
      ".Lbsp3d_clip_line_to_leaves_8:\n\t"
      "testb %%dl, %%dl\n\t"
      "movb %%al, -0x3(%%ebp)\n\t"
      "je .Lbsp3d_clip_line_to_leaves_9\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_10\n\t"
      ".Lbsp3d_clip_line_to_leaves_9:\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .Lbsp3d_clip_line_to_leaves_13\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lbsp3d_clip_line_to_leaves_13\n\t"
      ".Lbsp3d_clip_line_to_leaves_10:\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "flds (%%eax)\n\t"
      "fsubs (%%ebx)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "flds 0x4(%%eax)\n\t"
      "fsubs 0x4(%%ebx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x8(%%ebx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%ecx)\n\t"
      "fmuls 0x8(%%ebx)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls 0x8(%%ecx)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls 0x4(%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls (%%ecx)\n\t"
      ".byte 0xde, 0xc1\n\t"
      ".byte 0xde, 0xf9\n\t"
      "fchs\n\t"
      "fsts -0x8(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_11\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomps 0x2533c8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lbsp3d_clip_line_to_leaves_12\n\t"
      ".Lbsp3d_clip_line_to_leaves_11:\n\t"
      "pushl $1\n\t"
      "pushl $0x49\n\t"
      "pushl $0x29ca08\n\t"
      "pushl $0x29c9f8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lbsp3d_clip_line_to_leaves_12:\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds (%%ebx)\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds 0x4(%%ebx)\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmuls -0x8(%%ebp)\n\t"
      "fadds 0x8(%%ebx)\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "jmp .Lbsp3d_clip_line_to_leaves_14\n\t"
      ".Lbsp3d_clip_line_to_leaves_13:\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      ".Lbsp3d_clip_line_to_leaves_14:\n\t"
      "addl $4, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movl %%edi, -0x8(%%ebp)\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".Lbsp3d_clip_line_to_leaves_15:\n\t"
      "movb 0xe(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_16\n\t"
      "movb -0x4(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_16\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%si, %%si\n\t"
      "sete %%al\n\t"
      "movb 0xe(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_21\n\t"
      "movb -0x4(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_21\n\t"
      ".Lbsp3d_clip_line_to_leaves_16:\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%si, %%si\n\t"
      "sete %%al\n\t"
      "leal -0x28(%%ebp), %%edx\n\t"
      "movb 0xe(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_17\n\t"
      "movl %%ebx, %%edx\n\t"
      ".Lbsp3d_clip_line_to_leaves_17:\n\t"
      "movb -0x4(%%ebp,%%eax,1), %%cl\n\t"
      "testb %%cl, %%cl\n\t"
      "leal -0x28(%%ebp), %%ecx\n\t"
      "jne .Lbsp3d_clip_line_to_leaves_18\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      ".Lbsp3d_clip_line_to_leaves_18:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jns .Lbsp3d_clip_line_to_leaves_20\n\t"
      "cmpl $-1, %%eax\n\t"
      "je .Lbsp3d_clip_line_to_leaves_21\n\t"
      "testl %%edi, %%edi\n\t"
      "je .Lbsp3d_clip_line_to_leaves_19\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "andl $0x7fffffff, %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%%edi\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "addl $0x10, %%esp\n\t"
      ".Lbsp3d_clip_line_to_leaves_19:\n\t"
      "incl -0xc(%%ebp)\n\t"
      "jmp .Lbsp3d_clip_line_to_leaves_21\n\t"
      ".Lbsp3d_clip_line_to_leaves_20:\n\t"
      "movl 0x1c(%%ebp), %%ebx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[c146e30]\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%ebx\n\t"
      "addl $0x18, %%esp\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      ".Lbsp3d_clip_line_to_leaves_21:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "incl %%esi\n\t"
      "incl %%eax\n\t"
      "addl $4, %%edx\n\t"
      "cmpw $2, %%si\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "jl .Lbsp3d_clip_line_to_leaves_15\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b146e30_elem), [assert] "m"(b146e30_assert), [exitfn] "m"(b146e30_exitfn), [c146e30] "m"(b146e30_c146e30)
      : "memory");
}
#else
#error "bsp3d_clip_line_to_leaves: clang naked draft required"
#endif


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

