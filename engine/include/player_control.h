#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "halo_math.h"
#include "collision_bsp.h"

typedef struct {
    float run_forward, run_backward, run_sideways;  /* wu/tick */
    float run_accel, air_accel;                     /* wu/tick^2 */
    float jump_velocity;                            /* wu/tick */
    float gravity;                                  /* wu/tick^2 */
    float eye_height;                               /* wu */
    float coll_height;                              /* wu */
    float radius;                                   /* wu */
} player_constants_t;

void player_control_set_constants(const player_constants_t *c);
void player_control_spawn(float x, float y, float z);
void player_control_input(float fwd, float side, float face_x, float face_y, i32 jump);
void player_control_update(float dt_ticks); /* Halo: typically 1.0 per 30Hz tick */
void player_control_state(float out[10]);   /* feet xyz, vel xyz, grounded, eye, n.z, pad */

#endif
