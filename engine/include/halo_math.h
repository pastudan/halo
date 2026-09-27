#ifndef HALO_MATH_H
#define HALO_MATH_H

typedef struct { float x, y, z; } vec3;

static inline float vfabs(float v) { return __builtin_fabsf(v); }
static inline float vsqrt(float v) { return __builtin_sqrtf(v); }
static inline float vmin(float a, float b) { return a < b ? a : b; }
static inline float vmax(float a, float b) { return a > b ? a : b; }
static inline float dot(vec3 a, vec3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
static inline vec3 add(vec3 a, vec3 b) { return (vec3){a.x+b.x, a.y+b.y, a.z+b.z}; }
static inline vec3 sub(vec3 a, vec3 b) { return (vec3){a.x-b.x, a.y-b.y, a.z-b.z}; }
static inline vec3 scale(vec3 a, float s) { return (vec3){a.x*s, a.y*s, a.z*s}; }

#endif
