#ifndef COLLISION_BSP_H
#define COLLISION_BSP_H

#include "halo_math.h"

typedef unsigned int u32;
typedef int i32;
typedef short i16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char i8;

typedef struct {
    float t;
    vec3 normal;
    i32 surface;
    i32 slot; /* which loaded BSP produced the hit */
    i32 hit;
} trace_t;

/* Load HCB1 blob at arena+offset into slot. Returns 1 on success. */
i32 collision_load_bsp(u32 slot, u32 offset, u32 length);

/* Cast p0 → p0+d over all loaded BSPs. t in [0,1] over d. */
int collision_cast(vec3 p0, vec3 d, trace_t *out);

/* Track A collision_surface_test_point2d — 1 if p is inside surface poly. */
int collision_surface_test(i32 slot, i32 surface, vec3 p);

/* Track A find_closest_point2d + plane unproject — snap p onto surface. */
int collision_surface_snap(i32 slot, i32 surface, vec3 p, vec3 *out);

u8 *engine_arena(void);
u32 engine_arena_size(void);

#endif
