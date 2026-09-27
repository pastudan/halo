/*
 * player_control.c — biped movement slice (Track B).
 *
 * Named after halo-re kb.json module game/player_control.c
 * (`player_control_update`). Scaffolded against tag constants + structure BSP
 * until Track A yields binary-matched bodies.
 *
 * Phase 1 improvements over the POC capsule:
 *   - denser body-height sample set (knees / waist / chest / head)
 *   - radial offset samples around the collision radius (corner catching)
 *   - horizontal depenetration when already overlapping a wall
 */
#include "../include/player_control.h"

#define MAX_SLOPE_Z    0.55f
#define STEP_HEIGHT    0.30f
#define SKIN           0.02f
#define TERMINAL_VEL   0.13f
#define SEA_FLOOR_Z   -3.0f

static player_constants_t C;
static struct {
    vec3 pos;
    vec3 vel;
    int grounded;
    vec3 ground_normal;
    float in_fwd, in_side;
    float face_x, face_y;
    int in_jump;
    int jump_latch;
} S;

void player_control_set_constants(const player_constants_t *c) { C = *c; }

void player_control_spawn(float x, float y, float z) {
    S.pos = (vec3){x, y, z};
    S.vel = (vec3){0, 0, 0};
    S.grounded = 0;
    S.ground_normal = (vec3){0, 0, 1};
    S.jump_latch = 0;
}

void player_control_input(float fwd, float side, float face_x, float face_y, i32 jump) {
    S.in_fwd = vmax(-1.0f, vmin(1.0f, fwd));
    S.in_side = vmax(-1.0f, vmin(1.0f, side));
    S.face_x = face_x;
    S.face_y = face_y;
    S.in_jump = jump;
}

/* Body sample heights relative to feet (wu). Halo biped hull is taller than
   two rays — denser sampling reduces wall clip-through on thin geometry. */
static const float BODY_H[4] = {0.15f, 0.35f, 0.55f, 0.85f};

/* Unit offsets in the XY plane for cylinder-ish wall probes (scaled by radius). */
static const float RADIAL[8][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {0.7071f, 0.7071f}, {-0.7071f, 0.7071f},
    {0.7071f, -0.7071f}, {-0.7071f, -0.7071f},
};

static int cast_body(vec3 origin_feet, vec3 move_ext, float radial_scale, trace_t *best) {
    best->hit = 0;
    best->t = 2.0f;
    int hit = 0;
    for (int h = 0; h < 4; h++) {
        for (int r = 0; r < 8; r++) {
            vec3 o = origin_feet;
            o.z += BODY_H[h] * C.coll_height;
            o.x += RADIAL[r][0] * C.radius * radial_scale;
            o.y += RADIAL[r][1] * C.radius * radial_scale;
            trace_t tr;
            if (collision_cast(o, move_ext, &tr) && tr.t < best->t) {
                *best = tr;
                hit = 1;
            }
        }
        /* center column */
        {
            vec3 o = origin_feet;
            o.z += BODY_H[h] * C.coll_height;
            trace_t tr;
            if (collision_cast(o, move_ext, &tr) && tr.t < best->t) {
                *best = tr;
                hit = 1;
            }
        }
    }
    return hit;
}

static void depenetrate(void) {
    /* If any body sample is already in solid, nudge along hit normals. */
    for (int pass = 0; pass < 3; pass++) {
        int moved = 0;
        for (int h = 0; h < 4; h++) {
            for (int r = 0; r < 8; r++) {
                vec3 o = S.pos;
                o.z += BODY_H[h] * C.coll_height;
                o.x += RADIAL[r][0] * C.radius * 0.85f;
                o.y += RADIAL[r][1] * C.radius * 0.85f;
                /* short probe outward then reverse — if start is solid, cast
                   from slightly outside toward center finds the wall. */
                vec3 out = (vec3){RADIAL[r][0] * 0.05f, RADIAL[r][1] * 0.05f, 0};
                vec3 start = add(o, out);
                vec3 dir = scale(out, -2.0f);
                trace_t tr;
                if (collision_cast(start, dir, &tr) && tr.t < 0.5f && tr.normal.z < 0.4f) {
                    S.pos = add(S.pos, scale(tr.normal, SKIN + 0.01f));
                    moved = 1;
                }
            }
        }
        if (!moved) break;
    }
}

static void slide_move(vec3 move) {
    for (int iter = 0; iter < 5; iter++) {
        float len = vsqrt(dot(move, move));
        if (len < 1e-6f) break;

        vec3 dir = scale(move, 1.0f / len);
        vec3 ext = scale(dir, len + C.radius);
        trace_t best;
        if (!cast_body(S.pos, ext, 0.0f, &best)) {
            /* also probe with slight radial for corners */
            if (!cast_body(S.pos, ext, 0.35f, &best)) {
                S.pos = add(S.pos, move);
                break;
            }
        }
        float hit_dist = best.t * (len + C.radius);
        float allowed = vmax(0.0f, hit_dist - C.radius - SKIN);
        S.pos = add(S.pos, scale(dir, vmin(allowed, len)));
        if (allowed >= len - 1e-5f) break;

        float rem = len - allowed;
        vec3 rest = scale(dir, rem);
        float into = dot(rest, best.normal);
        move = sub(rest, scale(best.normal, into));
        float vin = dot(S.vel, best.normal);
        if (vin < 0.0f) S.vel = sub(S.vel, scale(best.normal, vin));
        /* kill residual into nearly-vertical walls harder */
        if (vfabs(best.normal.z) < 0.3f && into < 0.0f) {
            move.x *= 0.15f;
            move.y *= 0.15f;
        }
    }
}

void player_control_update(float dt_ticks) {
    (void)dt_ticks; /* fixed 1-tick updates for now; RE may use fractional */

    float fx = S.face_x, fy = S.face_y;
    float rx = fy, ry = -fx;
    float speed_f = S.in_fwd >= 0.0f ? C.run_forward : C.run_backward;
    float dvx = fx * S.in_fwd * speed_f + rx * S.in_side * C.run_sideways;
    float dvy = fy * S.in_fwd * speed_f + ry * S.in_side * C.run_sideways;
    float dlen = vsqrt(dvx * dvx + dvy * dvy);
    if (dlen > C.run_forward) {
        dvx *= C.run_forward / dlen;
        dvy *= C.run_forward / dlen;
    }

    float acc = S.grounded ? C.run_accel : C.air_accel;
    float ax = dvx - S.vel.x, ay = dvy - S.vel.y;
    float alen = vsqrt(ax * ax + ay * ay);
    if (alen > acc && alen > 0.0f) { ax *= acc / alen; ay *= acc / alen; }
    S.vel.x += ax;
    S.vel.y += ay;

    /* FUN_001a2290: launch along biped up (here: last ground normal), not +Z */
    if (S.grounded && S.in_jump && !S.jump_latch) {
        vec3 up = S.ground_normal;
        if (dot(up, up) < 1e-6f) up = (vec3){0, 0, 1};
        float along = dot(S.vel, up);
        if (along < C.jump_velocity) {
            float boost = C.jump_velocity - along;
            S.vel = add(S.vel, scale(up, boost));
        }
        S.grounded = 0;
        S.jump_latch = 1;
    }
    if (!S.in_jump) S.jump_latch = 0;
    if (!S.grounded) {
        S.vel.z -= C.gravity;
        if (S.vel.z < -TERMINAL_VEL) S.vel.z = -TERMINAL_VEL;
    }

    depenetrate();
    slide_move((vec3){S.vel.x, S.vel.y, 0.0f});

    if (S.vel.z > 0.0f) {
        vec3 o = S.pos;
        o.z += C.coll_height;
        trace_t tr;
        if (collision_cast(o, (vec3){0, 0, S.vel.z + SKIN}, &tr)) {
            S.pos.z += vmax(0.0f, tr.t * (S.vel.z + SKIN) - SKIN);
            S.vel.z = 0.0f;
        } else {
            S.pos.z += S.vel.z;
        }
        S.grounded = 0;
    } else {
        float up = S.grounded ? STEP_HEIGHT : 0.0f;
        float down = up - S.vel.z + (S.grounded ? STEP_HEIGHT : SKIN);
        vec3 o = S.pos;
        o.z += up;
        trace_t tr;
        if (collision_cast(o, (vec3){0, 0, -down}, &tr)) {
            float hit_z = o.z - tr.t * down;
            if (tr.normal.z >= MAX_SLOPE_Z) {
                S.pos.z = hit_z;
                S.vel.z = 0.0f;
                S.grounded = 1;
                S.ground_normal = tr.normal;
                /* If feet leave the hit poly, snap to closest boundary point */
                if (tr.surface >= 0 && tr.slot >= 0 &&
                    !collision_surface_test(tr.slot, tr.surface, S.pos)) {
                    vec3 snapped;
                    if (collision_surface_snap(tr.slot, tr.surface, S.pos, &snapped)) {
                        S.pos = snapped;
                    }
                }
            } else {
                S.pos.z += S.vel.z;
                if (S.pos.z < hit_z) S.pos.z = hit_z;
                S.grounded = 0;
            }
        } else {
            S.pos.z += S.vel.z;
            S.grounded = 0;
        }
    }

    if (S.pos.z < SEA_FLOOR_Z) {
        S.pos.z = SEA_FLOOR_Z;
        S.vel.z = 0.0f;
        S.grounded = 1;
    }
}

void player_control_state(float out[10]) {
    out[0] = S.pos.x;
    out[1] = S.pos.y;
    out[2] = S.pos.z;
    out[3] = S.vel.x;
    out[4] = S.vel.y;
    out[5] = S.vel.z;
    out[6] = S.grounded ? 1.0f : 0.0f;
    out[7] = C.eye_height;
    out[8] = S.ground_normal.z;
    out[9] = 1.0f; /* engine build marker (POC was 0) */
}
