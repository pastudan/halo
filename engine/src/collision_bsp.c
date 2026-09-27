/*
 * collision_bsp.c — structure collision BSP queries (Track B).
 *
 * Portable slice of Track A `collision_bsp_test_vector` (0x149480) /
 * `FUN_00148eb0` (0x148eb0) in stianeklund/halo `physics/collision_bsp.c`.
 * HCB1 blobs replace Xbox tag_block bases; leaf→surface uses the same
 * 2D-BSP walk as the original leaf path (via FUN_00148780 on Xbox).
 *
 * Semantics (PC Trial / HCB1 extract + RE):
 *   bsp3d children: >=0 node; -1 SOLID; sign bit set → open leaf.
 *   On plane straddle: near child is back if dir·n > 0 else front; then far.
 *   Hit = open leaf → solid transition at last crossed plane.
 */
#include "../include/collision_bsp.h"

typedef struct { i32 plane, back, front; } bsp3d_node_t;
typedef struct { float i, j, k, d; } plane_t;
typedef struct { u16 flags; i16 ref_count; i32 first_ref; } leaf_t;
typedef struct { i32 plane, node; } bsp2d_ref_t;
typedef struct { float i, j, d; i32 left, right; } bsp2d_node_t;
typedef struct { i32 plane, first_edge; u8 flags; i8 breakable; i16 material; } surface_t;
typedef struct { i32 sv, ev, fe, re, ls, rs; } edge_t;
typedef struct { float x, y, z; i32 first_edge; } vertex_t;

typedef struct {
    const bsp3d_node_t *nodes;   u32 n_nodes;
    const plane_t      *planes;  u32 n_planes;
    const leaf_t       *leaves;  u32 n_leaves;
    const bsp2d_ref_t  *refs;    u32 n_refs;
    const bsp2d_node_t *nodes2d; u32 n_nodes2d;
    const surface_t    *surfs;   u32 n_surfs;
    const edge_t       *edges;   u32 n_edges;
    const vertex_t     *verts;   u32 n_verts;
    int loaded;
} cbsp_t;

#define MAX_BSPS 4
static cbsp_t g_bsps[MAX_BSPS];

#define ARENA_BYTES (12u * 1024u * 1024u)
static u8 g_arena[ARENA_BYTES];

u8 *engine_arena(void) { return g_arena; }
u32 engine_arena_size(void) { return ARENA_BYTES; }

static u32 rd_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

i32 collision_load_bsp(u32 slot, u32 offset, u32 length) {
    if (slot >= MAX_BSPS) return 0;
    const u8 *p = g_arena + offset;
    if (length < 36 || p[0] != 'H' || p[1] != 'C' || p[2] != 'B' || p[3] != '1')
        return 0;
    u32 c[8];
    for (int i = 0; i < 8; i++) c[i] = rd_u32(p + 4 + 4 * i);
    const u8 *cur = p + 36;
    cbsp_t *b = &g_bsps[slot];
    b->nodes   = (const bsp3d_node_t *)cur; b->n_nodes   = c[0]; cur += c[0] * 12;
    b->planes  = (const plane_t *)cur;      b->n_planes  = c[1]; cur += c[1] * 16;
    b->leaves  = (const leaf_t *)cur;       b->n_leaves  = c[2]; cur += c[2] * 8;
    b->refs    = (const bsp2d_ref_t *)cur;  b->n_refs    = c[3]; cur += c[3] * 8;
    b->nodes2d = (const bsp2d_node_t *)cur; b->n_nodes2d = c[4]; cur += c[4] * 20;
    b->surfs   = (const surface_t *)cur;    b->n_surfs   = c[5]; cur += c[5] * 12;
    b->edges   = (const edge_t *)cur;       b->n_edges   = c[6]; cur += c[6] * 24;
    b->verts   = (const vertex_t *)cur;     b->n_verts   = c[7]; cur += c[7] * 16;
    if ((u32)(cur - p) > length) { b->loaded = 0; return 0; }
    b->loaded = 1;
    return 1;
}

#define IS_LEAF(c)  ((c) != -1 && ((u32)(c) & 0x80000000u))
#define LEAF_IDX(c) ((i32)((u32)(c) & 0x7fffffffu))

static float plane_dist(const cbsp_t *b, i32 pl_ref, vec3 p) {
    const plane_t *pl = &b->planes[pl_ref & 0x7fffffff];
    float d = p.x * pl->i + p.y * pl->j + p.z * pl->k - pl->d;
    return pl_ref < 0 ? -d : d;
}

static void project_2d(const plane_t *pl, int flipped, vec3 p, float *u, float *v) {
    float ai = vfabs(pl->i), aj = vfabs(pl->j), ak = vfabs(pl->k);
    int axis = (ak >= aj && ak >= ai) ? 2 : (aj >= ai ? 1 : 0);
    float comp = axis == 0 ? pl->i : axis == 1 ? pl->j : pl->k;
    /* Xbox FUN_00148780: pos = 1 iff plane[axis] > 0 (fcomp; test ah,41h) */
    int sign = comp > 0.0f;
    if (flipped) sign = !sign;
    const float c[3] = {p.x, p.y, p.z};
    int a1 = (axis + 1) % 3, a2 = (axis + 2) % 3;
    if (sign) { *u = c[a1]; *v = c[a2]; }
    else      { *u = c[a2]; *v = c[a1]; }
}

static i32 bsp2d_walk(const cbsp_t *b, i32 node, float u, float v) {
    while (node >= 0) {
        const bsp2d_node_t *n = &b->nodes2d[node];
        node = (u * n->i + v * n->j - n->d) >= 0.0f ? n->right : n->left;
    }
    if (node == -1) return -1;
    return LEAF_IDX(node);
}

static i32 leaf_surface_at(const cbsp_t *b, i32 leaf, i32 pl_ref, vec3 P) {
    if (leaf < 0) return -1;
    const leaf_t *L = &b->leaves[leaf];
    i32 want = pl_ref & 0x7fffffff;
    for (i32 r = L->first_ref; r < L->first_ref + L->ref_count; r++) {
        const bsp2d_ref_t *ref = &b->refs[r];
        if ((ref->plane & 0x7fffffff) != want) continue;
        float u, v;
        project_2d(&b->planes[want], ref->plane < 0, P, &u, &v);
        i32 s = bsp2d_walk(b, ref->node, u, v);
        if (s >= 0) return s;
    }
    return -1;
}

/* Xbox edge[5]==surface → side 1; vert0=edge[side], next=edge[2+side] */
static void edge_side(const edge_t *e, i32 surface_index,
                      i32 *v0i, i32 *v1i, i32 *next) {
    if (e->rs == surface_index) {
        *v0i = e->ev;
        *v1i = e->sv;
        *next = e->re;
    } else {
        *v0i = e->sv;
        *v1i = e->ev;
        *next = e->fe;
    }
}

/* collision_surface_test_point2d (0x1479e0) — ey*dx-ex*dy <= 0 all edges */
static int surface_test_point2d(const cbsp_t *b, i32 surface_index, vec3 p) {
    if (surface_index < 0 || (u32)surface_index >= b->n_surfs) return 0;
    const surface_t *S = &b->surfs[surface_index];
    int flipped = S->plane < 0;
    const plane_t *pl = &b->planes[S->plane & 0x7fffffff];
    i32 first = S->first_edge;
    i32 edge_i = first;
    float px, py;
    project_2d(pl, flipped, p, &px, &py);
    int guard = 0;
    do {
        const edge_t *e = &b->edges[edge_i];
        i32 v0i, v1i, next;
        edge_side(e, surface_index, &v0i, &v1i, &next);
        const vertex_t *v0 = &b->verts[v0i];
        const vertex_t *v1 = &b->verts[v1i];
        float u0, v0p, u1, v1p;
        project_2d(pl, flipped, (vec3){v0->x, v0->y, v0->z}, &u0, &v0p);
        project_2d(pl, flipped, (vec3){v1->x, v1->y, v1->z}, &u1, &v1p);
        float dx = px - u0, dy = py - v0p;
        float ex = u1 - u0, ey = v1p - v0p;
        if (ey * dx - ex * dy > 0.0f) return 0;
        edge_i = next;
        if (++guard > 10000) return 0;
    } while (edge_i != first);
    return 1;
}

/* Portable closest-on-poly + plane unproject (find_closest + project_point2d) */
static int surface_snap(const cbsp_t *b, i32 surface_index, vec3 p, vec3 *out) {
    if (surface_index < 0 || (u32)surface_index >= b->n_surfs) return 0;
    const surface_t *S = &b->surfs[surface_index];
    int flipped = S->plane < 0;
    const plane_t *pl = &b->planes[S->plane & 0x7fffffff];
    float px, py;
    project_2d(pl, flipped, p, &px, &py);

    i32 first = S->first_edge;
    i32 edge_i = first;
    float best_u = px, best_v = py;
    int inside = 1;
    float best_d2 = 1e30f;
    int guard = 0;
    do {
        const edge_t *e = &b->edges[edge_i];
        i32 v0i, v1i, next;
        edge_side(e, surface_index, &v0i, &v1i, &next);
        const vertex_t *a = &b->verts[v0i];
        const vertex_t *c = &b->verts[v1i];
        float u0, v0p, u1, v1p;
        project_2d(pl, flipped, (vec3){a->x, a->y, a->z}, &u0, &v0p);
        project_2d(pl, flipped, (vec3){c->x, c->y, c->z}, &u1, &v1p);
        float dx = px - u0, dy = py - v0p;
        float ex = u1 - u0, ey = v1p - v0p;
        if (ey * dx - ex * dy > 0.0f) {
            inside = 0;
            float len2 = ex * ex + ey * ey;
            float t = len2 > 1e-12f ? (ex * dx + ey * dy) / len2 : 0.0f;
            if (t < 0.0f) t = 0.0f;
            else if (t > 1.0f) t = 1.0f;
            float cu = u0 + ex * t, cv = v0p + ey * t;
            float ddx = px - cu, ddy = py - cv;
            float d2 = ddx * ddx + ddy * ddy;
            if (d2 < best_d2) {
                best_d2 = d2;
                best_u = cu;
                best_v = cv;
            }
        }
        edge_i = next;
        if (++guard > 10000) break;
    } while (edge_i != first);

    float u = inside ? px : best_u;
    float v = inside ? py : best_v;

    /* Unproject 2D → 3D on plane (0x992d0 project_point2d) */
    float ai = vfabs(pl->i), aj = vfabs(pl->j), ak = vfabs(pl->k);
    int axis = (ak >= aj && ak >= ai) ? 2 : (aj >= ai ? 1 : 0);
    int sign = (axis == 0 ? pl->i : axis == 1 ? pl->j : pl->k) > 0.0f;
    if (flipped) sign = !sign;
    int a1 = (axis + 1) % 3, a2 = (axis + 2) % 3;
    float o[3];
    if (sign) { o[a1] = u; o[a2] = v; }
    else      { o[a2] = u; o[a1] = v; }
    float naxis = axis == 0 ? pl->i : axis == 1 ? pl->j : pl->k;
    float na = a1 == 0 ? pl->i : a1 == 1 ? pl->j : pl->k;
    float nb = a2 == 0 ? pl->i : a2 == 1 ? pl->j : pl->k;
    if (vfabs(naxis) < 1e-8f) o[axis] = 0.0f;
    else o[axis] = (pl->d - na * o[a1] - nb * o[a2]) / naxis;
    *out = (vec3){o[0], o[1], o[2]};
    return 1;
}

int collision_surface_test(i32 slot, i32 surface, vec3 p) {
    if (slot < 0 || slot >= MAX_BSPS || !g_bsps[slot].loaded) return 0;
    return surface_test_point2d(&g_bsps[slot], surface, p);
}

int collision_surface_snap(i32 slot, i32 surface, vec3 p, vec3 *out) {
    if (slot < 0 || slot >= MAX_BSPS || !g_bsps[slot].loaded || !out) return 0;
    return surface_snap(&g_bsps[slot], surface, p, out);
}

typedef struct {
    vec3 p0, d;
    i32 last_leaf;
    i32 cross_plane;
    float cross_t;
    float cross_sign;
} seg_t;

static int test_vector_r(const cbsp_t *b, i32 node, float t0, float t1,
                         seg_t *seg, trace_t *out) {
    if (node == -1) {
        if (seg->last_leaf >= 0) {
            vec3 P = add(seg->p0, scale(seg->d, seg->cross_t));
            i32 surf = leaf_surface_at(b, seg->last_leaf, seg->cross_plane, P);
            const plane_t *pl = &b->planes[seg->cross_plane & 0x7fffffff];
            float sgn = seg->cross_sign;
            out->t = seg->cross_t;
            out->normal = (vec3){pl->i * sgn, pl->j * sgn, pl->k * sgn};
            out->surface = surf;
            out->hit = 1;
            return 1;
        }
        seg->last_leaf = -2;
        return 0;
    }
    if (IS_LEAF(node)) { seg->last_leaf = LEAF_IDX(node); return 0; }

    const bsp3d_node_t *n = &b->nodes[node];
    vec3 P0 = add(seg->p0, scale(seg->d, t0));
    vec3 P1 = add(seg->p0, scale(seg->d, t1));
    float d0 = plane_dist(b, n->plane, P0);
    float d1 = plane_dist(b, n->plane, P1);

    if (d0 >= 0.0f && d1 >= 0.0f) return test_vector_r(b, n->front, t0, t1, seg, out);
    if (d0 <  0.0f && d1 <  0.0f) return test_vector_r(b, n->back,  t0, t1, seg, out);

    /* Split t matches FUN_00148eb0: t = -d_origin / dir_dot along segment.
       near/far by dir·n (not endpoint side) — same as Xbox 0x148f80. */
    float dir_dot = d1 - d0;
    float tm = t0 + (t1 - t0) * d0 / (d0 - d1);
    i32 near_c = dir_dot > 0.0f ? n->back : n->front;
    i32 far_c  = dir_dot > 0.0f ? n->front : n->back;

    if (test_vector_r(b, near_c, t0, tm, seg, out)) return 1;
    /* FUN_00148eb0: skip far when result[0] <= t_split (no room past plane) */
    if (!(out->t > tm)) return 0;

    seg->cross_plane = n->plane;
    seg->cross_t = tm;
    seg->cross_sign = ((d0 >= 0.0f) ? 1.0f : -1.0f) * ((n->plane < 0) ? -1.0f : 1.0f);
    return test_vector_r(b, far_c, tm, t1, seg, out);
}

int collision_cast(vec3 p0, vec3 d, trace_t *out) {
    out->hit = 0;
    out->t = 1.0f;
    out->slot = -1;
    int hit = 0;
    for (int i = 0; i < MAX_BSPS; i++) {
        if (!g_bsps[i].loaded) continue;
        /* result[0] seed = max_t (Xbox wrapper); overwritten on hit */
        trace_t tr = {0};
        tr.t = 1.0f;
        tr.slot = i;
        seg_t seg = {p0, d, -3, 0, 0.0f, 1.0f};
        if (test_vector_r(&g_bsps[i], 0, 0.0f, 1.0f, &seg, &tr) && tr.t < out->t) {
            *out = tr;
            out->slot = i;
            hit = 1;
        }
    }
    out->hit = hit;
    return hit;
}
