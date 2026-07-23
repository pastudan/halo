/*
 * halo_phys.c — Halo 1 player physics core (wasm32, freestanding).
 *
 * Runs in native Halo conventions: right-handed, z-up, world units (1 wu =
 * 10 feet), fixed 30 ticks/second. All conversion to three.js space happens
 * on the JS side.
 *
 * Collision queries run against the game's real collision BSP, extracted to
 * .cbsp by tools/extract_collision.py. Structure semantics (validated against
 * b30.map geometry):
 *   - bsp3d node children: >= 0 -> child node; == -1 -> SOLID volume;
 *     sign bit set -> leaf index (child & 0x7fffffff). Leaves are open space.
 *   - A vector hits geometry only when it crosses a splitting plane from an
 *     OPEN LEAF into -1 (solid). Solid-to-solid crossings (e.g. the infinite
 *     boundary planes of another level's BSP) are not geometry. The surface
 *     at the crossing is resolved through the leaf's bsp2d references for
 *     that plane (projected to the plane's dominant-axis 2D coordinates).
 *   - Plane references in bsp2d_references carry a sign bit meaning
 *     "flipped plane" (mirrors the 2D projection).
 *
 * Movement model mirrors the original engine's biped update structured after
 * halo-re kb.json naming (player_control / point_physics / collision_usage):
 * ground acceleration toward a desired velocity from the globals tag player
 * information, weak airborne acceleration, tag jump velocity, engine gravity
 * constant, collide-and-slide against the BSP, step-up/step-down ground
 * snapping, slope limit by surface normal.
 */

#define WASM_EXPORT(name) __attribute__((export_name(name)))

typedef unsigned int u32;
typedef int i32;
typedef short i16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char i8;

/* ------------------------------------------------------------------ math */
typedef struct { float x, y, z; } vec3;

static inline float vfabs(float v) { return __builtin_fabsf(v); }
static inline float vsqrt(float v) { return __builtin_sqrtf(v); }
static inline float vmin(float a, float b) { return a < b ? a : b; }
static inline float vmax(float a, float b) { return a > b ? a : b; }
static inline float dot(vec3 a, vec3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
static inline vec3 add(vec3 a, vec3 b) { return (vec3){a.x+b.x, a.y+b.y, a.z+b.z}; }
static inline vec3 sub(vec3 a, vec3 b) { return (vec3){a.x-b.x, a.y-b.y, a.z-b.z}; }
static inline vec3 scale(vec3 a, float s) { return (vec3){a.x*s, a.y*s, a.z*s}; }

/* ------------------------------------------------------- collision structs */
typedef struct { i32 plane, back, front; } bsp3d_node_t;         /* 12 */
typedef struct { float i, j, k, d; } plane_t;                    /* 16 */
typedef struct { u16 flags; i16 ref_count; i32 first_ref; } leaf_t; /* 8 */
typedef struct { i32 plane, node; } bsp2d_ref_t;                 /* 8 */
typedef struct { float i, j, d; i32 left, right; } bsp2d_node_t; /* 20 */
typedef struct { i32 plane, first_edge; u8 flags; i8 breakable; i16 material; } surface_t; /* 12 */
typedef struct { i32 sv, ev, fe, re, ls, rs; } edge_t;           /* 24 */
typedef struct { float x, y, z; i32 first_edge; } vertex_t;      /* 16 */

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

WASM_EXPORT("phys_arena") u8 *phys_arena(void) { return g_arena; }
WASM_EXPORT("phys_arena_size") u32 phys_arena_size(void) { return ARENA_BYTES; }

static u32 rd_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

WASM_EXPORT("phys_load_bsp")
i32 phys_load_bsp(u32 slot, u32 offset, u32 length) {
    if (slot >= MAX_BSPS) return 0;
    const u8 *p = g_arena + offset;
    if (length < 36 || p[0] != 'H' || p[1] != 'C' || p[2] != 'B' || p[3] != '1')
        return 0;
    u32 c[8];
    for (int i = 0; i < 8; i++) c[i] = rd_u32(p + 4 + 4*i);
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

/* --------------------------------------------------------- BSP raycasting */
#define IS_LEAF(c)  ((c) != -1 && ((u32)(c) & 0x80000000u))
#define LEAF_IDX(c) ((i32)((u32)(c) & 0x7fffffffu))

typedef struct {
    float t;        /* param along the segment [0,1] */
    vec3 normal;    /* plane normal facing the incoming ray */
    i32 surface;    /* surface index or -1 */
    i32 hit;
} trace_t;

static float plane_dist(const cbsp_t *b, i32 pl_ref, vec3 p) {
    const plane_t *pl = &b->planes[pl_ref & 0x7fffffff];
    float d = p.x*pl->i + p.y*pl->j + p.z*pl->k - pl->d;
    return pl_ref < 0 ? -d : d;
}

/* project a 3D point to the dominant-axis 2D frame of a plane */
static void project_2d(const plane_t *pl, int flipped, vec3 p, float *u, float *v) {
    float ai = vfabs(pl->i), aj = vfabs(pl->j), ak = vfabs(pl->k);
    int axis = (ak >= aj && ak >= ai) ? 2 : (aj >= ai ? 1 : 0);
    float comp = axis == 0 ? pl->i : axis == 1 ? pl->j : pl->k;
    int sign = comp >= 0.0f;
    if (flipped) sign = !sign;
    const float c[3] = {p.x, p.y, p.z};
    int a1 = (axis + 1) % 3, a2 = (axis + 2) % 3;
    if (sign) { *u = c[a1]; *v = c[a2]; }
    else      { *u = c[a2]; *v = c[a1]; }
}

static i32 bsp2d_walk(const cbsp_t *b, i32 node, float u, float v) {
    while (node >= 0) {
        const bsp2d_node_t *n = &b->nodes2d[node];
        node = (u*n->i + v*n->j - n->d) >= 0.0f ? n->right : n->left;
    }
    if (node == -1) return -1;
    return LEAF_IDX(node);
}

/* resolve the surface hit when crossing `pl_ref`'s plane at point P,
   coming from open leaf `leaf` */
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

typedef struct {
    vec3 p0, d;
    i32 last_leaf;    /* most recent terminal region visited along the ray:
                         >=0 open leaf, -2 solid, -3 none yet */
    i32 cross_plane;  /* most recently crossed splitting plane ref */
    float cross_t;    /* t of that crossing */
    float cross_sign; /* +1 if the ray came from the plane's front side */
} seg_t;

/* Traverse terminal regions along the ray in order. A hit is the transition
   from an open leaf into a solid region; the boundary is the most recently
   crossed splitting plane. (Solid children may themselves be subtrees that
   only resolve to -1 deeper down, so the check happens at the terminal,
   not at the crossing.) */
static int test_vector_r(const cbsp_t *b, i32 node, float t0, float t1,
                         seg_t *seg, trace_t *out) {
    if (node == -1) {
        if (seg->last_leaf >= 0) {
            /* open leaf -> solid: hit at the last crossed plane */
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
        seg->last_leaf = -2;  /* solid -> solid: not geometry */
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

    float tm = t0 + (t1 - t0) * d0 / (d0 - d1);
    i32 near_c = d0 >= 0.0f ? n->front : n->back;
    i32 far_c  = d0 >= 0.0f ? n->back  : n->front;

    if (test_vector_r(b, near_c, t0, tm, seg, out)) return 1;

    seg->cross_plane = n->plane;
    seg->cross_t = tm;
    seg->cross_sign = ((d0 >= 0.0f) ? 1.0f : -1.0f) * ((n->plane < 0) ? -1.0f : 1.0f);
    return test_vector_r(b, far_c, tm, t1, seg, out);
}

/* cast p0 -> p0+d over all loaded bsps; t in [0,1] over d */
static int cast_all(vec3 p0, vec3 d, trace_t *out) {
    out->hit = 0;
    out->t = 1.0f;
    int hit = 0;
    for (int i = 0; i < MAX_BSPS; i++) {
        if (!g_bsps[i].loaded) continue;
        trace_t tr = {0};
        seg_t seg = {p0, d, -3, 0, 0.0f, 1.0f};
        if (test_vector_r(&g_bsps[i], 0, 0.0f, 1.0f, &seg, &tr) && tr.t < out->t) {
            *out = tr;
            hit = 1;
        }
    }
    out->hit = hit;
    return hit;
}

/* -------------------------------------------------------------- constants */
static struct {
    float run_forward, run_backward, run_sideways;  /* wu/tick */
    float run_accel, air_accel;                     /* wu/tick^2 */
    float jump_velocity;                            /* wu/tick */
    float gravity;                                  /* wu/tick^2 */
    float eye_height;                               /* wu */
    float coll_height;                              /* wu */
    float radius;                                   /* wu */
} C;

WASM_EXPORT("phys_set_constants")
void phys_set_constants(float run_f_ps, float run_b_ps, float run_s_ps,
                        float run_accel_ps, float air_accel_ps,
                        float jump_v, float gravity,
                        float eye_h, float coll_h, float radius) {
    /* speeds arrive in wu/s; accelerations in wu/s-per-tick; jump+gravity per-tick */
    C.run_forward  = run_f_ps / 30.0f;
    C.run_backward = run_b_ps / 30.0f;
    C.run_sideways = run_s_ps / 30.0f;
    C.run_accel    = run_accel_ps / 30.0f;
    C.air_accel    = air_accel_ps / 30.0f;
    C.jump_velocity = jump_v;
    C.gravity      = gravity;
    C.eye_height   = eye_h;
    C.coll_height  = coll_h;
    C.radius       = radius;
}

/* ------------------------------------------------------------ player state */
#define MAX_SLOPE_Z    0.55f   /* min ground normal z to stand on (~57 deg) */
#define STEP_HEIGHT    0.30f   /* wu */
#define SKIN           0.02f   /* wu */
#define TERMINAL_VEL   0.13f   /* wu/tick */
#define SEA_FLOOR_Z   -3.0f    /* absolute failsafe */

static struct {
    vec3 pos;       /* feet */
    vec3 vel;       /* wu/tick */
    int grounded;
    vec3 ground_normal;
    /* inputs */
    float in_fwd, in_side;    /* -1..1 */
    float face_x, face_y;     /* unit facing (horizontal) */
    int in_jump;
    int jump_latch;
} S;

static float g_state[10];

WASM_EXPORT("phys_spawn")
void phys_spawn(float x, float y, float z) {
    S.pos = (vec3){x, y, z};
    S.vel = (vec3){0, 0, 0};
    S.grounded = 0;
}

WASM_EXPORT("phys_input")
void phys_input(float fwd, float side, float face_x, float face_y, i32 jump) {
    S.in_fwd = vmax(-1.0f, vmin(1.0f, fwd));
    S.in_side = vmax(-1.0f, vmin(1.0f, side));
    S.face_x = face_x;
    S.face_y = face_y;
    S.in_jump = jump;
}

/* body ray heights (relative to feet) used for wall sweeps */
static const float BODY_H[2] = {0.20f, 0.55f};

/* sweep the body horizontally along `move`, slide on hits; returns final move */
static vec3 slide_move(vec3 move) {
    for (int iter = 0; iter < 4; iter++) {
        float len = vsqrt(dot(move, move));
        if (len < 1e-6f) break;

        trace_t best = {0};
        best.hit = 0;
        best.t = 2.0f;
        /* extend the cast by radius so the body doesn't clip walls */
        vec3 dir = scale(move, 1.0f / len);
        vec3 ext = scale(dir, len + C.radius);
        for (int h = 0; h < 2; h++) {
            vec3 o = S.pos;
            o.z += BODY_H[h];
            trace_t tr;
            if (cast_all(o, ext, &tr) && tr.t < best.t) best = tr;
        }
        if (!best.hit) {
            S.pos = add(S.pos, move);
            break;
        }
        float hit_dist = best.t * (len + C.radius);
        float allowed = vmax(0.0f, hit_dist - C.radius - SKIN);
        S.pos = add(S.pos, scale(dir, vmin(allowed, len)));
        if (allowed >= len) break;

        /* slide remaining motion along the plane */
        float rem = len - allowed;
        vec3 rest = scale(dir, rem);
        float into = dot(rest, best.normal);
        move = sub(rest, scale(best.normal, into));
        /* also cancel velocity into the plane */
        float vin = dot(S.vel, best.normal);
        if (vin < 0.0f) S.vel = sub(S.vel, scale(best.normal, vin));
    }
    return move;
}

WASM_EXPORT("phys_tick")
void phys_tick(void) {
    /* ---- desired horizontal velocity (wu/tick) */
    float fx = S.face_x, fy = S.face_y;
    float rx = fy, ry = -fx;   /* right = forward x up (z-up, RH) */
    float speed_f = S.in_fwd >= 0.0f ? C.run_forward : C.run_backward;
    float dvx = fx * S.in_fwd * speed_f + rx * S.in_side * C.run_sideways;
    float dvy = fy * S.in_fwd * speed_f + ry * S.in_side * C.run_sideways;
    /* clamp combined speed to run_forward */
    float dlen = vsqrt(dvx*dvx + dvy*dvy);
    if (dlen > C.run_forward) {
        dvx *= C.run_forward / dlen;
        dvy *= C.run_forward / dlen;
    }

    /* ---- accelerate toward desired */
    float acc = S.grounded ? C.run_accel : C.air_accel;
    float ax = dvx - S.vel.x, ay = dvy - S.vel.y;
    float alen = vsqrt(ax*ax + ay*ay);
    if (alen > acc && alen > 0.0f) { ax *= acc / alen; ay *= acc / alen; }
    S.vel.x += ax;
    S.vel.y += ay;

    /* ---- jump / gravity */
    if (S.grounded && S.in_jump && !S.jump_latch) {
        S.vel.z = C.jump_velocity;
        S.grounded = 0;
        S.jump_latch = 1;
    }
    if (!S.in_jump) S.jump_latch = 0;
    if (!S.grounded) {
        S.vel.z -= C.gravity;
        if (S.vel.z < -TERMINAL_VEL) S.vel.z = -TERMINAL_VEL;
    }

    /* ---- horizontal move with slide */
    slide_move((vec3){S.vel.x, S.vel.y, 0.0f});

    /* ---- vertical: ceilings */
    if (S.vel.z > 0.0f) {
        vec3 o = S.pos;
        o.z += C.coll_height;
        trace_t tr;
        if (cast_all(o, (vec3){0, 0, S.vel.z + SKIN}, &tr)) {
            S.pos.z += vmax(0.0f, tr.t * (S.vel.z + SKIN) - SKIN);
            S.vel.z = 0.0f;
        } else {
            S.pos.z += S.vel.z;
        }
        S.grounded = 0;
    } else {
        /* ---- ground: cast down from step height */
        float up = S.grounded ? STEP_HEIGHT : 0.0f;
        float down = up - S.vel.z + (S.grounded ? STEP_HEIGHT : SKIN);
        vec3 o = S.pos;
        o.z += up;
        trace_t tr;
        if (cast_all(o, (vec3){0, 0, -down}, &tr)) {
            float hit_z = o.z - tr.t * down;
            if (tr.normal.z >= MAX_SLOPE_Z) {
                S.pos.z = hit_z;
                S.vel.z = 0.0f;
                S.grounded = 1;
                S.ground_normal = tr.normal;
            } else {
                /* too steep: treat as air, but don't sink through */
                S.pos.z += S.vel.z;
                if (S.pos.z < hit_z) S.pos.z = hit_z;
                S.grounded = 0;
            }
        } else {
            S.pos.z += S.vel.z;
            S.grounded = 0;
        }
    }

    /* failsafe floor (deep sea bed exists in the BSP, this is belt+braces) */
    if (S.pos.z < SEA_FLOOR_Z) {
        S.pos.z = SEA_FLOOR_Z;
        S.vel.z = 0.0f;
        S.grounded = 1;
    }
}

WASM_EXPORT("phys_state")
float *phys_state(void) {
    g_state[0] = S.pos.x;
    g_state[1] = S.pos.y;
    g_state[2] = S.pos.z;
    g_state[3] = S.vel.x;
    g_state[4] = S.vel.y;
    g_state[5] = S.vel.z;
    g_state[6] = S.grounded ? 1.0f : 0.0f;
    g_state[7] = C.eye_height;
    g_state[8] = S.ground_normal.z;
    g_state[9] = 0.0f;
    return g_state;
}

/* debug: returns hit t in [0,1] or -1 */
WASM_EXPORT("phys_ray")
float phys_ray(float x, float y, float z, float dx, float dy, float dz) {
    trace_t tr;
    if (cast_all((vec3){x, y, z}, (vec3){dx, dy, dz}, &tr)) return tr.t;
    return -1.0f;
}
