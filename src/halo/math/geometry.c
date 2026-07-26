/* MSVC 7.1 FABS intrinsic: declared+pragma here so fabs() inlines to a single
 * FABS instruction instead of a CRT call. */
extern double __cdecl fabs(double);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(fabs)
#else
/* clang builds with -fno-builtin, which ignores the intrinsic pragma above and
 * emits a real CRT call to fabs. The original inlines a single x87 FABS. Force
 * clang to inline via the always-available builtin so the codegen matches the
 * binary (and so equivalence harnesses don't see an external fabs stub). */
#define fabs __builtin_fabs
#endif

/* 0x994d0 — Negate all four components of a plane */
void plane_negate(float *plane_in, float *plane_out)
{
  plane_out[0] = -plane_in[0];
  plane_out[1] = -plane_in[1];
  plane_out[2] = -plane_in[2];
  plane_out[3] = -plane_in[3];
}

/* 0x106390 — Perimeter of a closed 2D polygon.
 * vertices is a flat array of (x,y) pairs; vertex_count is the vertex count.
 * Seeds the accumulator with the closing edge dist(vertex[0], vertex[last]),
 * then walks the vertex[i] -> vertex[i+1] edges (vertex_count-1 of them).
 * Term ordering under each sqrt matches the original codegen: x-term first for
 * the closing edge, y-term first inside the loop. Source:
 * c:\halo\SOURCE\math\geometry.c */
float convex_hull2d_perimeter(int16_t vertex_count, float *vertices)
{
  float perimeter;
  uint16_t remaining;

  perimeter = sqrtf((vertices[0] - vertices[vertex_count * 2 + -2]) *
                      (vertices[0] - vertices[vertex_count * 2 + -2]) +
                    (vertices[1] - vertices[vertex_count * 2 + -1]) *
                      (vertices[1] - vertices[vertex_count * 2 + -1]));

  if (1 < vertex_count) {
    remaining = (uint16_t)(vertex_count - 1);
    do {
      remaining = remaining - 1;
      perimeter =
        sqrtf((vertices[3] - vertices[1]) * (vertices[3] - vertices[1]) +
              (vertices[2] - vertices[0]) * (vertices[2] - vertices[0])) +
        perimeter;
      vertices = vertices + 2;
    } while (remaining != 0);
  }
  return perimeter;
}

/* convex_hull2d_test_vector (0x1063f0) — XBE naked draft (batch 84). */
#if defined(__clang__)


__attribute__((naked, noinline))
bool convex_hull2d_test_vector(int16_t num_verts __attribute__((unused)), float *polygon2d __attribute__((unused)), float *ray_origin __attribute__((unused)), float *ray_dir __attribute__((unused)), float *out_tmin __attribute__((unused)), float *out_tmax __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movw 0x8(%%ebp), %%cx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "testw %%cx, %%cx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $0xff7fffff, -0x4(%%ebp)\n\t"
      "movl $0x7f7fffff, -0x8(%%ebp)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jle .Lconvex_hull2d_test_vector_8\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "movswl %%cx, %%ebx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      ".Lconvex_hull2d_test_vector_1:\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal 0x1(%%eax), %%esi\n\t"
      "xorl %%edx, %%edx\n\t"
      "cmpl %%ebx, %%esi\n\t"
      "setge %%dl\n\t"
      "decl %%edx\n\t"
      "andl %%esi, %%edx\n\t"
      "flds (%%ecx,%%edx,8)\n\t"
      "leal 0x4(%%ecx,%%eax,8), %%esi\n\t"
      "fsubs (%%ecx,%%eax,8)\n\t"
      "flds 0x4(%%ecx,%%edx,8)\n\t"
      "fsubs (%%esi)\n\t"
      "flds (%%edi)\n\t"
      "fsubs (%%ecx,%%eax,8)\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "flds 0x4(%%edi)\n\t"
      "fsubs (%%esi)\n\t"
      "fld %%st(2)\n\t"
      "fmuls (%%eax)\n\t"
      "fld %%st(4)\n\t"
      "fmuls 0x4(%%eax)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0xc(%%ebp)\n\t"
      ".byte 0xde, 0xcb\n\t"
      ".byte 0xd8, 0xc9\n\t"
      ".byte 0xde, 0xea\n\t"
      "fstp %%st(0)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fabs\n\t"
      "fcompl 0x2533d0\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lconvex_hull2d_test_vector_6\n\t"
      "fdivs -0xc(%%ebp)\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_hull2d_test_vector_2\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Lconvex_hull2d_test_vector_3\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "jmp .Lconvex_hull2d_test_vector_4\n\t"
      ".Lconvex_hull2d_test_vector_2:\n\t"
      "flds -0x8(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_hull2d_test_vector_3\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "jmp .Lconvex_hull2d_test_vector_4\n\t"
      ".Lconvex_hull2d_test_vector_3:\n\t"
      "fstp %%st(0)\n\t"
      ".Lconvex_hull2d_test_vector_4:\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fcomps -0x8(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "jne .Lconvex_hull2d_test_vector_7\n\t"
      ".Lconvex_hull2d_test_vector_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_hull2d_test_vector_6:\n\t"
      "fcomps 0x253f44\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lconvex_hull2d_test_vector_5\n\t"
      ".Lconvex_hull2d_test_vector_7:\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "incl %%eax\n\t"
      "cmpw 0x8(%%ebp), %%ax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "jl .Lconvex_hull2d_test_vector_1\n\t"
      ".Lconvex_hull2d_test_vector_8:\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_hull2d_test_vector_9\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      ".Lconvex_hull2d_test_vector_9:\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "je .Lconvex_hull2d_test_vector_10\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "movl %%edx, (%%eax)\n\t"
      ".Lconvex_hull2d_test_vector_10:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "convex_hull2d_test_vector: clang naked draft required"
#endif


/* Sutherland-Hodgman 2D polygon clip against a line.
 * Source: c:\halo\SOURCE\math\geometry.c */
int16_t convex_polygon2d_clip_to_plane(int16_t count, float *points,
                                       float *line, int16_t max_count,
                                       float *out_points, uint32_t *out_bitmask,
                                       uint8_t *changed, float epsilon)
{
  /* _chkstk(0x1014): clip_buffer is a 512-float-pair local, not static. */
  float clip_buffer[0x200 * 2];
  int16_t out_count;
  uint32_t mask;
  bool any_above;
  bool any_below;
  bool previous_inside;
  bool current_inside;
  int16_t i;
  int byte_size;
  float *previous_point;
  float *current_point;
  float distance;
  float t;
  float clamped_t;
  float dx;
  float dy;
  int out_idx;

  out_count = 0;
  mask = 0;
  any_above = false;
  any_below = false;

  if (count < 3) {
    display_assert("count>=NUMBER_OF_VERTICES_PER_TRIANGLE",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x546, true);
    system_exit(-1);
  }

  if (changed != NULL) {
    *changed = 0;
  }

  if (points == out_points) {
    if (count > 0x200) {
      display_assert("count<=CLIP_BUFFER_SIZE",
                     "c:\\halo\\SOURCE\\math\\geometry.c", 0x54d, true);
      system_exit(-1);
    }
    csmemcpy(clip_buffer, points, (int)count << 3);
    points = clip_buffer;
  }

  byte_size = (int)count * 8;

  previous_point = points + (int)count * 2 - 2;
  previous_inside =
    *(float *)0x2533c0 <=
    (previous_point[0] * line[0] + previous_point[1] * line[1]) - line[2];

  if (count < 1) {
    goto zero_result;
  }

  for (i = 0; i < count; ++i) {
    current_point = points + (int)i * 2;
    distance =
      (line[0] * current_point[0] + current_point[1] * line[1]) - line[2];
    current_inside = *(float *)0x2533c0 <= distance;

    if (distance > epsilon) {
      any_above = true;
    } else if (distance < -epsilon) {
      any_below = true;
    }

    if (current_inside != previous_inside) {
      if (out_count == max_count) {
        goto overflow;
      }

      if (changed != NULL) {
        *changed = 1;
      }

      dx = previous_point[0] - current_point[0];
      dy = previous_point[1] - current_point[1];
      t =
        -((line[0] * current_point[0] + current_point[1] * line[1]) - line[2]) /
        (dy * line[1] + dx * line[0]);

      clamped_t = *(float *)0x2533c0;
      if (*(float *)0x2533c0 <= t) {
        clamped_t = t;
        if (*(float *)0x2533c8 < t) {
          clamped_t = *(float *)0x2533c8;
        }
      }

      out_points[(int)out_count * 2] = clamped_t * dx + current_point[0];
      mask |= (uint32_t)1 << ((uint8_t)out_count & 0x1f);
      out_count += 1;
      out_points[((int)out_count - 1) * 2 + 1] =
        clamped_t * dy + current_point[1];

      if (out_count != 1) {
        out_idx = (int)out_count;
        if (((float)fabs(out_points[out_idx * 2 - 2] - out_points[0]) <
               epsilon &&
             (float)fabs(out_points[out_idx * 2 - 1] - out_points[1]) <
               epsilon) ||
            ((float)fabs(out_points[out_idx * 2 - 2] -
                         out_points[out_idx * 2 - 4]) < epsilon &&
             (float)fabs(out_points[out_idx * 2 - 1] -
                         out_points[out_idx * 2 - 3]) < epsilon)) {
          out_count -= 1;
        }
      }
    }

    if (current_inside) {
      if (out_count == max_count) {
        goto overflow;
      }

      out_points[(int)out_count * 2] = current_point[0];
      out_points[(int)out_count * 2 + 1] = current_point[1];

      if (out_bitmask == NULL ||
          ((uint32_t)1 << ((uint8_t)i & 0x1f) & *out_bitmask) == 0) {
        mask &= ~((uint32_t)1 << ((uint8_t)out_count & 0x1f));
      } else {
        mask |= (uint32_t)1 << ((uint8_t)out_count & 0x1f);
      }
      out_count += 1;

      if (out_count != 1) {
        out_idx = (int)out_count;
        if (((float)fabs(out_points[out_idx * 2 - 2] - out_points[0]) <
               epsilon &&
             (float)fabs(out_points[out_idx * 2 - 1] - out_points[1]) <
               epsilon) ||
            ((float)fabs(out_points[out_idx * 2 - 2] -
                         out_points[out_idx * 2 - 4]) < epsilon &&
             (float)fabs(out_points[out_idx * 2 - 1] -
                         out_points[out_idx * 2 - 3]) < epsilon)) {
          out_count -= 1;
        }
      }
    }

    previous_point = current_point;
    previous_inside = current_inside;
  }

  if (out_count == -1) {
    goto overflow;
  }

  if (out_count < 3) {
  zero_result:
    out_count = 0;
  }

  if (any_above) {
    if (!any_below) {
      if (count < 0 || count > max_count) {
        display_assert("count>=0 && count<=maximum_count",
                       "c:\\halo\\SOURCE\\math\\geometry.c", 0x5a1, true);
        system_exit(-1);
      }
      csmemcpy(out_points, points, byte_size);
      out_count = count;
    }
  } else {
    out_count = 0;
  }

  goto done;

overflow:
  out_count = -1;
  if (count < 0 || count > max_count) {
    display_assert("count>=0 && count<=maximum_count",
                   "c:\\halo\\SOURCE\\math\\geometry.c", 0x5a8, true);
    system_exit(-1);
  }
  csmemcpy(out_points, points, byte_size);

done:
  if (out_bitmask != NULL) {
    *out_bitmask = mask;
  }

  return out_count;
}

/* 0x106900 — Reject a 2D polygon whose vertex coordinates are not finite.
 * Walks vertex_count (x,y) pairs (8 bytes each) and returns 0 as soon as any
 * x or y float has all exponent bits set (IEEE 754 infinity or NaN); returns
 * 1 when every coordinate is finite. Returns a byte (bool): the original sets
 * AL only for the true path, leaving the loop's last-read dword in the upper
 * bytes of EAX. Loop counter stays 16-bit to match the original codegen.
 * Source: c:\halo\SOURCE\math\geometry.c */
bool convex_polygon2d_verify(int16_t vertex_count, uint32_t *vertices)
{
  int16_t i;

  i = 0;
  if (0 < vertex_count) {
    do {
      if ((vertices[i * 2] & 0x7f800000) == 0x7f800000 ||
          (vertices[i * 2 + 1] & 0x7f800000) == 0x7f800000) {
        return 0;
      }
      i = i + 1;
    } while (i < vertex_count);
  }
  return 1;
}

/* convex_polygon3d_verify (0x106dc0) — XBE naked draft (batch 83). */
#if defined(__clang__)


__attribute__((naked, noinline))
bool convex_polygon3d_verify(int16_t vertex_count __attribute__((unused)), float *vertices __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x30, %%esp\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds (%%ecx)\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "pushl %%ebx\n\t"
      "flds 0x4(%%ecx)\n\t"
      "pushl %%esi\n\t"
      "fsubs 0x10(%%ecx)\n\t"
      "pushl %%edi\n\t"
      "flds 0x8(%%ecx)\n\t"
      "xorl %%edi, %%edi\n\t"
      "testw %%ax, %%ax\n\t"
      "fsubs 0x14(%%ecx)\n\t"
      "flds 0x18(%%ecx)\n\t"
      "fsubs 0xc(%%ecx)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x1c(%%ecx)\n\t"
      "fsubs 0x10(%%ecx)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x20(%%ecx)\n\t"
      "fsubs 0x14(%%ecx)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xca\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "jle .Lconvex_polygon3d_verify_5\n\t"
      "movswl %%ax, %%edx\n\t"
      "decl %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      ".Lconvex_polygon3d_verify_1:\n\t"
      "testw %%di, %%di\n\t"
      "jne .Lconvex_polygon3d_verify_2\n\t"
      "movswl %%ax, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal -0xc(%%ecx,%%eax,4), %%esi\n\t"
      "jmp .Lconvex_polygon3d_verify_3\n\t"
      ".Lconvex_polygon3d_verify_2:\n\t"
      "movswl %%di, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal -0xc(%%ecx,%%edx,4), %%esi\n\t"
      ".Lconvex_polygon3d_verify_3:\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "movswl %%di, %%edx\n\t"
      "leal (%%edx,%%edx,2), %%eax\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "leal (%%ecx,%%eax,4), %%eax\n\t"
      "movl %%ecx, %%edx\n\t"
      "je .Lconvex_polygon3d_verify_4\n\t"
      "leal 0xc(%%eax), %%edx\n\t"
      ".Lconvex_polygon3d_verify_4:\n\t"
      "movl (%%eax), %%ebx\n\t"
      "movl %%ebx, -0x4(%%ebp)\n\t"
      "andl $0x7f800000, %%ebx\n\t"
      "cmpl $0x7f800000, %%ebx\n\t"
      "je .Lconvex_polygon3d_verify_6\n\t"
      "movl 0x4(%%eax), %%ebx\n\t"
      "movl %%ebx, -0x8(%%ebp)\n\t"
      "andl $0x7f800000, %%ebx\n\t"
      "cmpl $0x7f800000, %%ebx\n\t"
      "je .Lconvex_polygon3d_verify_6\n\t"
      "movl 0x8(%%eax), %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "andl $0x7f800000, %%ebx\n\t"
      "cmpl $0x7f800000, %%ebx\n\t"
      "je .Lconvex_polygon3d_verify_6\n\t"
      "flds (%%esi)\n\t"
      "fsubs (%%eax)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "flds (%%edx)\n\t"
      "fsubs (%%eax)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x4(%%edx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "flds 0x8(%%edx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fxch %%st(1)\n\t"
      ".byte 0xd8, 0xcb\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xca\n\t"
      "fld %%st(0)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xea\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      ".byte 0xd8, 0xc9\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmuls -0x20(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls -0x24(%%ebp)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fcomps 0x28c038\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $5, %%ah\n\t"
      "jnp .Lconvex_polygon3d_verify_6\n\t"
      "movw 0x8(%%ebp), %%ax\n\t"
      "incl %%edi\n\t"
      "cmpw %%ax, %%di\n\t"
      "jl .Lconvex_polygon3d_verify_1\n\t"
      ".Lconvex_polygon3d_verify_5:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lconvex_polygon3d_verify_6:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      :
      : "memory");
}
#else
#error "convex_polygon3d_verify: clang naked draft required"
#endif


/* 0x106f50 — Build an initial simplex (tetrahedron) from a point cloud: the
 * seed step of a convex-hull/quickhull. Selects four extremal points, emits
 * 4 vertices (stride 0xc), 6 edges (stride 0x20) and 4 surfaces (stride 0x1c)
 * with their connectivity constants, then marks the remaining capacity slots
 * as unused (byte-0 at each slot start). Returns 1 on success, 0 on a
 * degenerate/failed seed. Point selection:
 *   p0 = min-X point; p1 = point farthest from p0;
 *   p2 = point farthest from the p0-p1 line; p3 = point farthest from the
 *   (p0,p1,p2) plane (with a winding swap when p3 is on the plane front).
 * Surface planes come from FUN_001037b0 (plane-from-3-points).
 * Source: c:\halo\SOURCE\math\geometry.c:1710 */
bool FUN_00106f50(int16_t point_count, float *points, int16_t vertices_capacity,
                  char *vertices, int16_t edges_capacity, char *edges,
                  int16_t surfaces_capacity, char *surfaces)
{
  char *vbase;
  float *p0;
  float *p1;
  float *p2;
  float *p3;
  float *pfVar5;
  float *scan;
  float plane[4];
  float edge_x;
  float edge_y;
  float edge_z;
  float len_sq;
  float dz;
  float t;
  float proj_y;
  float proj_z;
  float perp_x;
  float perp_y;
  float perp_dist;
  float best;
  float best_dist;
  unsigned int n;
  int i;
  int min_x_index;
  int far_index;
  int line_index;
  int plane_index;
  int saved_far;

  vbase = vertices;
  min_x_index = -1;
  far_index = -1;
  line_index = -1;
  plane_index = -1;

  if (points == (float *)0) {
    display_assert("points", "c:\\halo\\SOURCE\\math\\geometry.c", 0x6ae, 1);
    system_exit(-1);
  }
  if (vertices == (char *)0) {
    display_assert("vertices", "c:\\halo\\SOURCE\\math\\geometry.c", 0x6af, 1);
    system_exit(-1);
  }
  if (edges == (char *)0) {
    display_assert("edges", "c:\\halo\\SOURCE\\math\\geometry.c", 0x6b0, 1);
    system_exit(-1);
  }
  if (surfaces == (char *)0) {
    display_assert("surfaces", "c:\\halo\\SOURCE\\math\\geometry.c", 0x6b1, 1);
    system_exit(-1);
  }

  if (3 < vertices_capacity && 5 < edges_capacity && 3 < surfaces_capacity &&
      0 < point_count) {
    /* Pass 1: find the point with the minimum X coordinate. */
    i = 0;
    scan = points;
    best = 3.402823466e+38f;
    do {
      if (*scan < best) {
        best = *scan;
        min_x_index = i;
      }
      i = i + 1;
      scan = scan + 3;
    } while ((int16_t)i < point_count);

    if ((int16_t)min_x_index != -1) {
      p0 = points + (int16_t)min_x_index * 3;

      /* Pass 2: find the point farthest (squared distance) from p0. */
      i = 0;
      scan = points + 2;
      best = 0.0f;
      do {
        if (best < (*p0 - scan[-2]) * (*p0 - scan[-2]) +
                     (p0[1] - scan[-1]) * (p0[1] - scan[-1]) +
                     (p0[2] - *scan) * (p0[2] - *scan)) {
          far_index = i;
          best = (*p0 - scan[-2]) * (*p0 - scan[-2]) +
                 (p0[1] - scan[-1]) * (p0[1] - scan[-1]) +
                 (p0[2] - *scan) * (p0[2] - *scan);
        }
        i = i + 1;
        scan = scan + 3;
      } while ((int16_t)i < point_count);

      if ((int16_t)far_index != -1 && 0.01f <= best) {
        p1 = points + (int16_t)far_index * 3;

        /* Pass 3: find the point farthest from the p0-p1 line. */
        i = 0;
        scan = points + 2;
        edge_x = *p1 - *p0;
        edge_y = p1[1] - p0[1];
        edge_z = p1[2] - p0[2];
        len_sq = edge_x * edge_x + edge_y * edge_y + edge_z * edge_z;
        best = 0.0f;
        do {
          dz = *scan - p0[2];
          t = ((scan[-2] - *p0) * edge_x + (scan[-1] - p0[1]) * edge_y +
               dz * edge_z) /
              len_sq;
          proj_y = edge_y * t;
          proj_z = edge_z * t;
          perp_x = (scan[-2] - *p0) - edge_x * t;
          perp_y = (scan[-1] - p0[1]) - proj_y;
          perp_dist =
            perp_x * perp_x + perp_y * perp_y + (dz - proj_z) * (dz - proj_z);
          if (best < perp_dist) {
            line_index = i;
            best = perp_dist;
          }
          i = i + 1;
          scan = scan + 3;
        } while ((int16_t)i < point_count);

        if ((int16_t)line_index != -1 && 0.01f <= best) {
          /* Pass 4: plane through (p0,p1,p2); find the farthest point. */
          best_dist = 0.0f;
          FUN_001037b0(plane, p0, p1, points + (int16_t)line_index * 3);
          saved_far = far_index;
          i = 0;
          scan = points + 2;
          do {
            perp_dist =
              (plane[2] * *scan + plane[1] * scan[-1] + plane[0] * scan[-2]) -
              plane[3];
            if (fabs(best_dist) < fabs(perp_dist)) {
              best_dist = perp_dist;
              plane_index = i;
            }
            i = i + 1;
            scan = scan + 3;
          } while ((int16_t)i < point_count);

          if ((int16_t)plane_index != -1 && 0.01f <= fabs(best_dist)) {
            if (0.0f < best_dist) {
              far_index = line_index;
              line_index = saved_far;
            }

            /* Emit 4 vertices (stride 0xc). */
            *(int *)(vbase + 4) = 0;
            *(int *)(vbase + 0x10) = 0;
            *(int16_t *)(vbase + 2) = (int16_t)min_x_index;
            *vbase = 1;
            vbase[0xc] = 1;
            vbase[0x18] = 1;
            *(int16_t *)(vbase + 0x1a) = (int16_t)line_index;
            *(int16_t *)(vbase + 0xe) = (int16_t)far_index;
            *(int16_t *)(vbase + 0x26) = (int16_t)plane_index;
            *(int *)(vbase + 0x1c) = 1;
            vbase[0x24] = 1;
            *(int *)(vbase + 0x28) = 3;

            /* Emit 6 edges (stride 0x20). */
            *(int *)(edges + 0x10) = 3;
            *(int *)(edges + 0x58) = 3;
            *(int *)(edges + 0x68) = 3;
            *(int *)(edges + 0x78) = 3;
            *(int *)(edges + 0x84) = 3;
            *(int *)(edges + 0xa4) = 3;
            *(int *)(edges + 0xb0) = 3;
            *(int *)(edges + 0xb8) = 3;
            *(int *)(edges + 4) = 0;
            *(int *)(edges + 0x14) = 0;
            *(int *)(edges + 0x34) = 0;
            *(int *)(edges + 0x48) = 0;
            *(int *)(edges + 0x4c) = 0;
            *(int *)(edges + 0x54) = 0;
            *(int *)(edges + 100) = 0;
            *(int *)(edges + 0x8c) = 0;
            *(int *)(edges + 0x98) = 2;
            *(int *)(edges + 0xa8) = 2;
            *(int *)(edges + 0xb4) = 2;
            *edges = 1;
            *(int *)(edges + 8) = 1;
            *(int *)(edges + 0xc) = 1;
            *(int *)(edges + 0x18) = 1;
            edges[0x20] = 1;
            *(int *)(edges + 0x24) = 1;
            edges[0x40] = 1;
            edges[0x60] = 1;
            *(int *)(edges + 0x74) = 1;
            edges[0x80] = 1;
            *(int *)(edges + 0x88) = 1;
            *(int *)(edges + 0x94) = 1;
            edges[0xa0] = 1;
            *(int *)(edges + 0xac) = 1;
            *(int *)(edges + 0x28) = 2;
            *(int *)(edges + 0x2c) = 2;
            *(int *)(edges + 0x30) = 4;
            *(int *)(edges + 0x38) = 2;
            *(int *)(edges + 0x44) = 2;
            *(int *)(edges + 0x50) = 5;
            *(int *)(edges + 0x6c) = 4;
            *(int *)(edges + 0x70) = 2;
            *(int *)(edges + 0x90) = 5;

            /* Emit 4 surfaces (stride 0x1c); planes via FUN_001037b0. */
            *surfaces = 1;
            pfVar5 = points + (int16_t)line_index * 3;
            p2 = points + (int16_t)far_index * 3;
            FUN_001037b0((float *)(surfaces + 4), p0, p2, pfVar5);
            *(int *)(surfaces + 0x14) = 0;
            surfaces[0x1c] = 1;
            p3 = points + (int16_t)plane_index * 3;
            FUN_001037b0((float *)(surfaces + 0x20), p0, p3, p2);
            *(int *)(surfaces + 0x30) = 0;
            surfaces[0x38] = 1;
            FUN_001037b0((float *)(surfaces + 0x3c), p2, p3, pfVar5);
            *(int *)(surfaces + 0x4c) = 1;
            surfaces[0x54] = 1;
            FUN_001037b0((float *)(surfaces + 0x58), p0, pfVar5, p3);
            *(int *)(surfaces + 0x68) = 2;

            /* Mark remaining capacity slots as unused. */
            if (4 < vertices_capacity) {
              vbase = vbase + 0x30;
              n = (unsigned int)(unsigned short)(vertices_capacity - 4);
              do {
                *vbase = 0;
                vbase = vbase + 0xc;
                n = n - 1;
              } while (n != 0);
            }
            if (6 < edges_capacity) {
              edges = edges + 0xc0;
              n = (unsigned int)(unsigned short)(edges_capacity - 6);
              do {
                *edges = 0;
                edges = edges + 0x20;
                n = n - 1;
              } while (n != 0);
            }
            if (4 < surfaces_capacity) {
              surfaces = surfaces + 0x70;
              n = (unsigned int)(unsigned short)(surfaces_capacity - 4);
              do {
                *surfaces = 0;
                surfaces = surfaces + 0x1c;
                n = n - 1;
              } while (n != 0);
            }
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
/* --- geometry.obj batch drafts (2026-07-26) --- */

/* 0x106960 */
int16_t convex_polygon3d_clip_to_plane(int16_t count, float *verts, float *plane, int16_t max_count, float *out_verts, uint32_t *out_bitmask, float epsilon, void *changed)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001d90e0();
  display_assert((char *)0x0028c010, (char *)0x0028be44, 1493, 0);
  system_exit(0);
  /* test eax, eax -> je 0x1069ad */
  /* relift: cmp eax, dword ptr [ebp + 0x18] -> jne 0x106a02 */
  /* cmp (int16_t)edi, 0x200 -> jle 0x1069dc */
  display_assert((char *)0x0028bff8, (char *)0x0028be44, 1500, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, ecx);
  /* test (char)eax, 1 -> jne 0x106a40 */
  /* test (char)eax, 1 -> je 0x106a8d */
  /* test (char)eax, 0x41 -> jne 0x106a9f */
  /* relift: cmp byte ptr [ebp + 0x13], (char)ebx -> je 0x106c04 */
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0x14] -> je 0x106d18 */
  /* test eax, eax -> je 0x106ad0 */
  /* test (char)eax, 0x41 -> jne 0x106b3d */
  /* test (char)eax, 0x41 -> jne 0x106bc0 */
  /* test (char)eax, 0x41 -> jne 0x106bc0 */
  /* test (char)eax, 0x41 -> je 0x106c03 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, 0x41 -> jne 0x106c04 */
  /* test (char)eax, (char)eax -> je 0x106cd3 */
  /* relift: cmp (int16_t)esi, word ptr [ebp + 0x14] -> jge 0x106d18 */
  /* test (char)eax, 0x41 -> jne 0x106c8f */
  /* test (char)eax, 0x41 -> jne 0x106c8f */
  /* test (char)eax, 0x41 -> je 0x106cd2 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* test (char)eax, 0x41 -> jne 0x106cd3 */
  /* cmp (int16_t)esi, -1 -> je 0x106d1b */
  /* test (char)eax, (char)eax -> jne 0x106d0f */
  /* test (char)eax, (char)eax -> jne 0x106d6b */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x106d29 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x14] -> jle 0x106d49 */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1591, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, eax);
  /* test (char)eax, (char)eax -> jne 0x106d5d */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x106d79 */
  /* relift: cmp (int16_t)eax, word ptr [ebp + 0x14] -> jle 0x106d9c */
  display_assert((char *)0x0028bfd4, (char *)0x0028be44, 1584, 0);
  system_exit(0);
  csmemcpy((void *)(uintptr_t)edx, (void *)(uintptr_t)ecx, ecx);
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}
