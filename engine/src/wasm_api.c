/*
 * WASM export surface for Track B. Prefer engine_* names; phys_* aliases keep
 * the existing web/src/physics.js bridge working during the migration.
 */
#include "../include/collision_bsp.h"
#include "../include/player_control.h"

#define WASM_EXPORT(name) __attribute__((export_name(name)))

static float g_state[10];

static void set_constants_impl(float run_f_ps, float run_b_ps, float run_s_ps,
                               float run_accel_ps, float air_accel_ps,
                               float jump_v, float gravity,
                               float eye_h, float coll_h, float radius) {
    player_constants_t c;
    c.run_forward  = run_f_ps / 30.0f;
    c.run_backward = run_b_ps / 30.0f;
    c.run_sideways = run_s_ps / 30.0f;
    c.run_accel    = run_accel_ps / 30.0f;
    c.air_accel    = air_accel_ps / 30.0f;
    c.jump_velocity = jump_v;
    c.gravity      = gravity;
    c.eye_height   = eye_h;
    c.coll_height  = coll_h;
    c.radius       = radius;
    player_control_set_constants(&c);
}

WASM_EXPORT("engine_arena") u8 *engine_arena_export(void) { return engine_arena(); }
WASM_EXPORT("phys_arena") u8 *phys_arena_export(void) { return engine_arena(); }

WASM_EXPORT("engine_arena_size") u32 engine_arena_size_export(void) { return engine_arena_size(); }
WASM_EXPORT("phys_arena_size") u32 phys_arena_size_export(void) { return engine_arena_size(); }

WASM_EXPORT("engine_load_bsp")
i32 engine_load_bsp_export(u32 slot, u32 offset, u32 length) {
    return collision_load_bsp(slot, offset, length);
}
WASM_EXPORT("phys_load_bsp")
i32 phys_load_bsp_export(u32 slot, u32 offset, u32 length) {
    return collision_load_bsp(slot, offset, length);
}

WASM_EXPORT("engine_set_constants")
void engine_set_constants_export(float a, float b, float c, float d, float e,
                                 float f, float g, float h, float i, float j) {
    set_constants_impl(a, b, c, d, e, f, g, h, i, j);
}
WASM_EXPORT("phys_set_constants")
void phys_set_constants_export(float a, float b, float c, float d, float e,
                               float f, float g, float h, float i, float j) {
    set_constants_impl(a, b, c, d, e, f, g, h, i, j);
}

WASM_EXPORT("engine_spawn") void engine_spawn_export(float x, float y, float z) {
    player_control_spawn(x, y, z);
}
WASM_EXPORT("phys_spawn") void phys_spawn_export(float x, float y, float z) {
    player_control_spawn(x, y, z);
}

WASM_EXPORT("engine_input")
void engine_input_export(float fwd, float side, float face_x, float face_y, i32 jump) {
    player_control_input(fwd, side, face_x, face_y, jump);
}
WASM_EXPORT("phys_input")
void phys_input_export(float fwd, float side, float face_x, float face_y, i32 jump) {
    player_control_input(fwd, side, face_x, face_y, jump);
}

WASM_EXPORT("engine_tick") void engine_tick_export(void) { player_control_update(1.0f); }
WASM_EXPORT("phys_tick") void phys_tick_export(void) { player_control_update(1.0f); }

WASM_EXPORT("engine_state") float *engine_state_export(void) {
    player_control_state(g_state);
    return g_state;
}
WASM_EXPORT("phys_state") float *phys_state_export(void) {
    player_control_state(g_state);
    return g_state;
}

WASM_EXPORT("engine_ray")
float engine_ray_export(float x, float y, float z, float dx, float dy, float dz) {
    trace_t tr;
    if (collision_cast((vec3){x, y, z}, (vec3){dx, dy, dz}, &tr)) return tr.t;
    return -1.0f;
}
WASM_EXPORT("phys_ray")
float phys_ray_export(float x, float y, float z, float dx, float dy, float dz) {
    trace_t tr;
    if (collision_cast((vec3){x, y, z}, (vec3){dx, dy, dz}, &tr)) return tr.t;
    return -1.0f;
}

WASM_EXPORT("engine_core_id")
float engine_core_id_export(void) { return 2.0f; }
