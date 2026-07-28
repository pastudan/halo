/* FUN_00120500 (0x120500) — Get a pointer to a specific animation frame's data.
 *
 * Given an animation structure and a frame index, returns a pointer to the
 * frame data for that frame. If compression is active (flag bit 0 at
 * animation+0x3a set, and DAT_00322600 is nonzero), returns a pointer
 * offset by the compressed data offset (animation+0x88). Otherwise,
 * returns a pointer offset by frame_size * frame_index.
 *
 * The frame data itself lives in tag_data at animation+0xa0, resolved
 * via tag_data_get_pointer.
 *
 * Confirmed: cdecl, 2 args (animation ptr, frame_index short).
 * Confirmed: CALL tag_data_get_pointer(animation+0xa0, 0, 0) at 0x12052b.
 * Confirmed: Assert "frame_index>=0 && frame_index<animation->frame_count" at
 * 0x120555. Confirmed: CALL display_assert at 0x120555, system_exit(-1) at
 * 0x12055c. Confirmed: Compressed path returns ESI + [EDI+0x88] at 0x12056b.
 * Confirmed: Uncompressed path returns ESI + MOVSX([EDI+0x24]) * MOVSX(BX) at
 * 0x120578-0x120582.
 */
void *FUN_00120500(void *animation, short frame_index)
{
  int compressed;
  char *data;
  char *anim;

  anim = (char *)animation;

  if (((*(unsigned char *)(anim + 0x3a) & 1) != 0) && DAT_00322600 != '\0') {
    compressed = 1;
  } else {
    compressed = 0;
  }

  data = (char *)tag_data_get_pointer(anim + 0xa0, 0, 0);

  if (frame_index < 0 || frame_index >= *(short *)(anim + 0x22)) {
    display_assert("frame_index>=0 && frame_index<animation->frame_count",
                   "c:\\halo\\SOURCE\\models\\model_animation_definitions.c",
                   0x47a, 1);
    system_exit(-1);
  }

  if (compressed) {
    return (void *)(data + *(int *)(anim + 0x88));
  }
  return (void *)(data + (int)*(short *)(anim + 0x24) * (int)frame_index);
}

/* FUN_00120590 (0x120590) — Resolve a pointer to a specific animation frame's
 * raw data block via tag_data_get_pointer.
 *
 * Given an animation structure pointer, a frame_index, and the per-frame
 * stride (frame_size), bounds-checks frame_index against animation->frame_count
 * (int16 at +0x22), then calls tag_data_get_pointer on the tag_data block at
 * animation+0x48 with offset = frame_index * frame_size and size = frame_size.
 * The return value of tag_data_get_pointer is discarded; the call is for its
 * side effect of resolving the tag_data reference.
 *
 * Confirmed: cdecl, 3 args (animation ptr, frame_index short, frame_size
 * short). Confirmed: assert "frame_index>=0 &&
 * frame_index<animation->frame_count" at 0x1205a7. Confirmed: MOVSX
 * EAX,[EBP+0x10] (frame_size); MOVSX ECX,SI (frame_index); IMUL ECX,EAX; PUSH
 * EAX; PUSH ECX; ADD EDI,0x48; PUSH EDI; CALL tag_data_get_pointer at 0x1205d7.
 * Source: c:\halo\SOURCE\models\model_animation_definitions.c, line 0x48e
 * (1166).
 */
void FUN_00120590(void *animation, short frame_index, short frame_size)
{
  char *anim;
  int offset;
  int size;

  anim = (char *)animation;

  if (frame_index < 0 || frame_index >= *(short *)(anim + 0x22)) {
    display_assert("frame_index>=0 && frame_index<animation->frame_count",
                   "c:\\halo\\SOURCE\\models\\model_animation_definitions.c",
                   0x48e, 1);
    system_exit(-1);
  }

  size = (int)frame_size;
  offset = (int)frame_index * size;
  tag_data_get_pointer(anim + 0x48, offset, size);
}

/* FUN_001205f0 (0x1205f0) — look up a string in an indexed string table.
 * Returns "#<invalid>" if the index is out of range or the entry is NULL. */
const char *FUN_001205f0(void *string_table, int16_t index)
{
  int16_t *table = (int16_t *)string_table;
  const char *result;

  if (index >= *table || (result = *(const char **)(*(int32_t *)(table + 2) +
                                                    index * 8)) == NULL) {
    result = "#<invalid>";
  }
  return result;
}

/* quaternion_decompress_8byte (0x120810) — Convert 4 packed int16 values to
 * normalized floats.
 *
 * Reads 4 consecutive short values from src and writes 4 floats to dest,
 * each multiplied by (1.0f / 32767.0f) to normalize from [-32767,32767]
 * to approximately [-1.0, 1.0]. Used to decompress quaternion rotation
 * components stored as 16-bit integers in animation frame data.
 *
 * Confirmed: cdecl, 2 args (src shorts ptr, dest floats ptr).
 * Confirmed: Leaf function, no callees.
 * Confirmed: Multiplies by float constant at 0x290dd8 = 1.0f/32767.0f.
 * Confirmed: 4 iterations via MOVSX+FILD+FMUL+FSTP pattern in disassembly.
 */
void quaternion_decompress_8byte(short *src, float *dest)
{
  dest[0] = (float)(int)src[0] * (1.0f / 32767.0f);
  dest[1] = (float)(int)src[1] * (1.0f / 32767.0f);
  dest[2] = (float)(int)src[2] * (1.0f / 32767.0f);
  dest[3] = (float)(int)src[3] * (1.0f / 32767.0f);
}

/* quaternion_decompress_6byte (0x120870) — Decompress 3 packed uint16s into 4
 * normalized floats.
 *
 * Extracts 4 values from 3 consecutive unsigned shorts (48 bits total) by
 * interleaved bit manipulation, sign-extends each to int, converts to float,
 * and multiplies by (1.0f / 32767.0f). Used to decompress compressed
 * quaternion rotation data in animation frames (compressed path in
 * FUN_00121d60).
 *
 * Confirmed: cdecl, 2 args (compressed_data ushort ptr, dest floats ptr).
 * Confirmed: Leaf function, no callees.
 * Confirmed: Multiplies by float constant at 0x290dd8 = 1.0f/32767.0f.
 * Confirmed: 4 outputs via interleaved bit extraction + MOVSX + FILD + FMUL +
 * FSTP. Confirmed: Bit operations verified against disassembly at
 * 0x120870-0x12092a.
 */
void quaternion_decompress_6byte(void *compressed_data, float *dest)
{
  unsigned short *src;
  unsigned short w0, w1, w2;
  short s0, s1, s2, s3;

  src = (unsigned short *)compressed_data;
  w0 = src[0];
  w1 = src[1];
  w2 = src[2];

  s0 = (short)((w0 >> 12) | (w0 & 0xFFF0));
  s1 = (short)(((w1 >> 4) & 0xFF0) | (w0 & 0xF) | (w0 << 12));
  s2 = (short)((((w2 >> 4) & 0xF00) | (w1 & 0xF0)) >> 4 | (w1 << 8));
  s3 = (short)(((w2 >> 8) & 0xF) | (w2 << 4));

  dest[0] = (float)(int)s0 * (1.0f / 32767.0f);
  dest[1] = (float)(int)s1 * (1.0f / 32767.0f);
  dest[2] = (float)(int)s2 * (1.0f / 32767.0f);
  dest[3] = (float)(int)s3 * (1.0f / 32767.0f);
}

/* find_keyframe_index (0x120d10) — Binary search for a keyframe by frame index.
 *
 * Given a sorted array of keyframe frame indices and a target frame, returns
 * the keyframe index i such that:
 *   keyframe_frame_indices[i] <= target_frame_index <
 * keyframe_frame_indices[i+1]
 *
 * Uses binary search with lo/hi bounds. The keyframe_count parameter is passed
 * in EDI (register arg @<edi>).
 *
 * Asserts:
 *   keyframe_count > 1
 *   keyframe_frame_indices != NULL
 *   keyframe_frame_indices[0] > 0
 *   target_frame_index >= 0 && target_frame_index <
 * keyframe_frame_indices[keyframe_count-1] Infinite loop killer at 200
 * iterations Post-search: keyframe_index >= 0 && keyframe_index <
 * keyframe_count-1 Post-search: target in range [keyframe_frame_indices[i],
 * keyframe_frame_indices[i+1])
 *
 * Confirmed: keyframe_count@<edi> register arg per disassembly.
 * Confirmed: Binary search with lo=local_8, hi=keyframe_count-1.
 * Confirmed: RETURNS uint masked to 0xffff (MOVZX EAX,AX pattern at return).
 */
short FUN_00120d10(unsigned short *keyframe_frame_indices,
                   short target_frame_index, short keyframe_count)
{
  int lo;
  int hi;
  int mid;
  short kfc;
  int kf_idx;
  int i;

  kfc = keyframe_count;
  if (kfc < 2) {
    display_assert("keyframe_count>1",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x536, 1);
    system_exit(-1);
  }
  if (keyframe_frame_indices == (void *)0) {
    display_assert("keyframe_frame_indices",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x537, 1);
    system_exit(-1);
  }
  if ((short)keyframe_frame_indices[0] < 1) {
    display_assert("keyframe_frame_indices[0]>0",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x538, 1);
    system_exit(-1);
  }
  if (target_frame_index < 0 ||
      (short)keyframe_frame_indices[kfc - 1] <= target_frame_index) {
    display_assert(
      "target_frame_index>=0 && "
      "target_frame_index<keyframe_frame_indices[keyframe_count-1]",
      "c:\\halo\\SOURCE\\models\\model_animations.c", 0x539, 1);
    system_exit(-1);
  }

  lo = 0;
  hi = kfc - 1;
  i = 0;
  while (1) {
    mid = lo + hi;
    mid = mid >> 1;
    kf_idx = mid;

    if ((short)kf_idx < 0 || kfc <= (short)kf_idx) {
      display_assert("keyframe_index>=0 && keyframe_index<keyframe_count",
                     "c:\\halo\\SOURCE\\models\\model_animations.c", 0x53f, 1);
      system_exit(-1);
    }

    if ((short)(kf_idx + 1) >= kfc ||
        target_frame_index < (short)keyframe_frame_indices[kf_idx + 1]) {
      if (target_frame_index >= (short)keyframe_frame_indices[kf_idx]) {
        break;
      }
      hi = mid;
    } else {
      lo = mid;
    }

    i++;
    if (i > 199) {
      display_assert("++infinite_loop_killer<200",
                     "c:\\halo\\SOURCE\\models\\model_animations.c", 0x54c, 1);
      system_exit(-1);
    }
  }

  if ((short)kf_idx < 0 || kfc - 1 <= (short)kf_idx) {
    display_assert("keyframe_index>=0 && keyframe_index<keyframe_count-1",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x550, 1);
    system_exit(-1);
  }
  if (target_frame_index < (short)keyframe_frame_indices[kf_idx] ||
      (short)keyframe_frame_indices[kf_idx + 1] <= target_frame_index) {
    display_assert(
      "target_frame_index>=keyframe_frame_indices[keyframe_index] && "
      "target_frame_index<keyframe_frame_indices[keyframe_index+1]",
      "c:\\halo\\SOURCE\\models\\model_animations.c", 0x551, 1);
    system_exit(-1);
  }

  return (short)kf_idx;
}

/* model_animation_choose_random (0x120f20) — Choose a weighted random
 * animation.
 *
 * Gets the animation graph tag ('antr'), generates a random float [0,1) using
 * either the global or local random seed (based on update_kind), then walks the
 * animation chain starting at animation_index. For each animation element:
 * compares the random value against the weight threshold at element+0x44.
 * If random <= threshold, returns the current animation index. Otherwise
 * advances to the next animation via element+0x38.
 *
 * Confirmed: tag_get('antr', animation_graph_tag_index) at 0x120f2e.
 * Confirmed: update_kind==1 → get_global_random_seed_address() at 0x120f40.
 * Confirmed: update_kind==0 → random_math_get_local_seed_address() at 0x120f53.
 * Confirmed: random_math_real(seed) at 0x120f46/0x120f59.
 * Confirmed: tag_block_get_element(antr_tag+0x74, index, 0xb4) at 0x120f9e.
 * Confirmed: FCOMP [ECX+0x44] + JNP loop exit at 0x120fab-0x120fb3.
 * Confirmed: next animation at element+0x38 (int16_t) at 0x120fb5.
 */
int model_animation_choose_random(int update_kind,
                                  int animation_graph_tag_index,
                                  int16_t animation_index)
{
  char *antr_tag;
  float random_value;
  char *element;

  antr_tag = (char *)tag_get(0x616e7472, animation_graph_tag_index);
  if (update_kind == 1) {
    random_value =
      random_math_real((unsigned int *)get_global_random_seed_address());
  } else {
    random_value = random_math_real(random_math_get_local_seed_address());
    if (update_kind != 0) {
      display_assert("ASSERTION_SERIES(update_kind, 2)",
                     "c:\\halo\\SOURCE\\models\\model_animations.c", 0x3f0, 1);
      system_exit(-1);
    }
  }
  while (animation_index != -1) {
    element = (char *)tag_block_get_element(antr_tag + 0x74,
                                            (int)animation_index, 0xb4);
    if (random_value <= *(float *)(element + 0x44))
      break;
    animation_index = *(int16_t *)(element + 0x38);
  }
  return (int)animation_index;
}

/* floor: the original calls MSVC CRT floor (0x1d9c2b).
 * We provide a local implementation since we don't link the CRT math lib. */
static double __attribute__((unused)) anim_floor(double x)
{
  int i = (int)x;
  return (double)((x < (double)i) ? (i - 1) : i);
}

/* animation_get_node_orientations (0x121640) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void * (*const b121640_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;
static void (*const b121640_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b121640_exitfn)(int) = system_exit;
static double (*const b121640_c1d9c2b)(double x) = floor;
static short (*const b121640_c120d10)(unsigned short *keyframe_frame_indices, short target_frame_index, short keyframe_count) = FUN_00120d10;
static void (*const b121640_c10b7d0)(float *a, float *b, float blend, float *out) = points_interpolate;

__attribute__((naked, noinline))
void animation_get_node_orientations(void *animation __attribute__((unused)), float frame __attribute__((unused)), unsigned short translation_count __attribute__((unused)), short node_index __attribute__((unused)), void *out_translation __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x88(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "addl $0xa0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b1a0]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "movl 0x14(%%esi), %%edi\n\t"
      "leal (%%eax,%%edx,4), %%ecx\n\t"
      "movl (%%ecx,%%esi,1), %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl $0xfff, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "addl %%esi, %%edi\n\t"
      "shrl $0xc, %%ebx\n\t"
      "testb $1, %%ah\n\t"
      "je .Lanimation_get_node_orientations_1\n\t"
      "pushl $1\n\t"
      "pushl $0x5f2\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2911a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_1:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "movswl 0x22(%%edx), %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lanimation_get_node_orientations_2\n\t"
      "pushl $1\n\t"
      "pushl $0x5f4\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_2:\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      "jge .Lanimation_get_node_orientations_3\n\t"
      "pushl $1\n\t"
      "pushl $0x5f6\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291160\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      ".Lanimation_get_node_orientations_3:\n\t"
      "jne .Lanimation_get_node_orientations_4\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "leal (%%edi,%%ecx,4), %%edx\n\t"
      "movl (%%edx), %%ecx\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x4(%%eax)\n\t"
      "movl 0x8(%%edx), %%edx\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x8(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_get_node_orientations_4:\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,4), %%ecx\n\t"
      "addl %%esi, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "leal (%%ecx,%%eax,2), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "addl %%esi, %%ebx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Lanimation_get_node_orientations_5\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movzwl -0x2(%%ebx,%%edx,2), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jle .Lanimation_get_node_orientations_6\n\t"
      ".Lanimation_get_node_orientations_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x609\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291118\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_6:\n\t"
      "movswl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movzwl -0x2(%%ebx,%%esi,2), %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .Lanimation_get_node_orientations_7\n\t"
      "pushl $1\n\t"
      "pushl $0x60a\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2910d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_7:\n\t"
      "movw (%%ebx), %%dx\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "movzwl %%dx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .Lanimation_get_node_orientations_8\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edi,%%eax,4), %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edx, %%ebx\n\t"
      "jmp .Lanimation_get_node_orientations_12\n\t"
      ".Lanimation_get_node_orientations_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x2(%%ebx,%%esi,2), %%cx\n\t"
      "movzwl %%cx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .Lanimation_get_node_orientations_9\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "leal -0xc(%%edx,%%eax,4), %%esi\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x1(%%ecx), %%ebx\n\t"
      "leal (%%edi,%%eax,4), %%edi\n\t"
      "jmp .Lanimation_get_node_orientations_12\n\t"
      ".Lanimation_get_node_orientations_9:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c120d10]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jl .Lanimation_get_node_orientations_10\n\t"
      "movswl %%di, %%edx\n\t"
      "decl %%esi\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jl .Lanimation_get_node_orientations_11\n\t"
      ".Lanimation_get_node_orientations_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x61e\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x290ea4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_11:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movswl %%di, %%eax\n\t"
      "movw (%%ebx,%%eax,2), %%cx\n\t"
      "movw 0x2(%%ebx,%%eax,2), %%bx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal (%%esi,%%edx,4), %%esi\n\t"
      "leal 0xc(%%esi), %%edi\n\t"
      ".Lanimation_get_node_orientations_12:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Lanimation_get_node_orientations_13\n\t"
      "movl (%%esi), %%ecx\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl 0x4(%%esi), %%edx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl 0x8(%%esi), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_get_node_orientations_13:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fidivl 0x10(%%ebp)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "je .Lanimation_get_node_orientations_14\n\t"
      "pushl $1\n\t"
      "pushl $0x62f\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291098\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_14:\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Lanimation_get_node_orientations_15\n\t"
      "pushl $1\n\t"
      "pushl $0x630\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291064\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_get_node_orientations_15:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c10b7d0]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [c19b1a0] "m"(b121640_c19b1a0), [assert] "m"(b121640_assert), [exitfn] "m"(b121640_exitfn), [c1d9c2b] "m"(b121640_c1d9c2b), [c120d10] "m"(b121640_c120d10), [c10b7d0] "m"(b121640_c10b7d0)
      : "memory");
}
#else
#error "animation_get_node_orientations: clang naked draft required"
#endif


/* overlay_animation_apply_continuous_scaled (0x121940) — XBE naked draft (batch 55). */
#if defined(__clang__)
static void * (*const b121940_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;
static void (*const b121940_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b121940_exitfn)(int) = system_exit;
static double (*const b121940_c1d9c2b)(double x) = floor;
static short (*const b121940_c120d10)(unsigned short *keyframe_frame_indices, short target_frame_index, short keyframe_count) = FUN_00120d10;
static void (*const b121940_c10b820)(float a, float b, float blend, float *out) = scalars_interpolate;

__attribute__((naked, noinline))
void overlay_animation_apply_continuous_scaled(void *animation __attribute__((unused)), float frame __attribute__((unused)), unsigned short scale_count __attribute__((unused)), short node_index __attribute__((unused)), void *out_scale __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x10, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x88(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "addl $0xa0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b1a0]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl 0x10(%%ebp), %%edi\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x24(%%esi), %%eax\n\t"
      "movl 0x1c(%%esi), %%edx\n\t"
      "addl %%esi, %%eax\n\t"
      "shll $2, %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "addl %%edi, %%edx\n\t"
      "movl (%%edx,%%esi,1), %%eax\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl $0xfff, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "shrl $0xc, %%ebx\n\t"
      "testb $1, %%ah\n\t"
      "je .Loverlay_animation_apply_continuous_scaled_1\n\t"
      "pushl $1\n\t"
      "pushl $0x64a\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2911a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Loverlay_animation_apply_continuous_scaled_2\n\t"
      "pushl $1\n\t"
      "pushl $0x64c\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_2:\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      "jge .Loverlay_animation_apply_continuous_scaled_3\n\t"
      "pushl $1\n\t"
      "pushl $0x64e\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291160\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      ".Loverlay_animation_apply_continuous_scaled_3:\n\t"
      "jne .Loverlay_animation_apply_continuous_scaled_4\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl (%%edi,%%edx,1), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Loverlay_animation_apply_continuous_scaled_4:\n\t"
      "movl 0x28(%%esi), %%edx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%edx,%%eax,4), %%ecx\n\t"
      "addl %%esi, %%ecx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl 0x20(%%esi), %%ecx\n\t"
      "leal (%%ecx,%%eax,2), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "addl %%esi, %%ebx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x10(%%ebp)\n\t"
      "fistps -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .Loverlay_animation_apply_continuous_scaled_5\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movzwl -0x2(%%ebx,%%edx,2), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jle .Loverlay_animation_apply_continuous_scaled_6\n\t"
      ".Loverlay_animation_apply_continuous_scaled_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x662\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291118\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_6:\n\t"
      "movswl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movzwl -0x2(%%ebx,%%esi,2), %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .Loverlay_animation_apply_continuous_scaled_7\n\t"
      "pushl $1\n\t"
      "pushl $0x663\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2910d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_7:\n\t"
      "movw (%%ebx), %%ax\n\t"
      "movswl -0x8(%%ebp), %%edx\n\t"
      "movzwl %%ax, %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jge .Loverlay_animation_apply_continuous_scaled_8\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "flds (%%edi,%%edx,1)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "movl (%%eax), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edx, 0x8(%%ebp)\n\t"
      "jmp .Loverlay_animation_apply_continuous_scaled_13\n\t"
      ".Loverlay_animation_apply_continuous_scaled_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x2(%%ebx,%%esi,2), %%cx\n\t"
      "movzwl %%cx, %%eax\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .Loverlay_animation_apply_continuous_scaled_9\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "flds -0x4(%%edx,%%esi,4)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "leal 0x1(%%ecx), %%ebx\n\t"
      "flds (%%edi,%%eax,1)\n\t"
      "jmp .Loverlay_animation_apply_continuous_scaled_12\n\t"
      ".Loverlay_animation_apply_continuous_scaled_9:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c120d10]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jl .Loverlay_animation_apply_continuous_scaled_10\n\t"
      "movswl %%di, %%edx\n\t"
      "decl %%esi\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jl .Loverlay_animation_apply_continuous_scaled_11\n\t"
      ".Loverlay_animation_apply_continuous_scaled_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x677\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x290ea4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_11:\n\t"
      "movl -0xc(%%ebp), %%edx\n\t"
      "movswl %%di, %%eax\n\t"
      "movw (%%ebx,%%eax,2), %%cx\n\t"
      "movw 0x2(%%ebx,%%eax,2), %%bx\n\t"
      "flds (%%edx,%%eax,4)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0x4(%%edx,%%eax,4)\n\t"
      ".Loverlay_animation_apply_continuous_scaled_12:\n\t"
      "fstps 0x8(%%ebp)\n\t"
      ".Loverlay_animation_apply_continuous_scaled_13:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "fildl -0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .Loverlay_animation_apply_continuous_scaled_14\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "fstp %%st(0)\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, (%%ecx)\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Loverlay_animation_apply_continuous_scaled_14:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "fidivl -0x10(%%ebp)\n\t"
      "fstps -0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "je .Loverlay_animation_apply_continuous_scaled_15\n\t"
      "pushl $1\n\t"
      "pushl $0x688\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291098\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_15:\n\t"
      "fildl -0xc(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .Loverlay_animation_apply_continuous_scaled_16\n\t"
      "pushl $1\n\t"
      "pushl $0x689\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291064\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Loverlay_animation_apply_continuous_scaled_16:\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10b820]\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [c19b1a0] "m"(b121940_c19b1a0), [assert] "m"(b121940_assert), [exitfn] "m"(b121940_exitfn), [c1d9c2b] "m"(b121940_c1d9c2b), [c120d10] "m"(b121940_c120d10), [c10b820] "m"(b121940_c10b820)
      : "memory");
}
#else
#error "overlay_animation_apply_continuous_scaled: clang naked draft required"
#endif


/* FUN_00121d60 (0x121d60) — XBE naked draft (batch 53). */
#if defined(__clang__)
static void * (*const b121d60_c120500)(void *animation, short frame_index) = FUN_00120500;
static void (*const b121d60_c121330)(void *animation, float frame, unsigned short rotation_count, short node_index, void *out_rotation) = FUN_00121330;
static void (*const b121d60_c120810)(short *src, float *dest) = quaternion_decompress_8byte;
static void (*const b121d60_c120870)(void *compressed_data, float *dest) = quaternion_decompress_6byte;
static void (*const b121d60_c10ca30)(float *quaternion) = sphere_intersects_rectangle3d;
static void (*const b121d60_c121640)(void *animation, float frame, unsigned short translation_count, short node_index, void *out_translation) = animation_get_node_orientations;
static void (*const b121d60_c121940)(void *animation, float frame, unsigned short scale_count, short node_index, void *out_scale) = overlay_animation_apply_continuous_scaled;
static void (*const b121d60_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b121d60_exitfn)(int) = system_exit;
static void (*const b121d60_c123aa0)(void *mode_tag, void *out_node_data) = FUN_00123aa0;

__attribute__((naked, noinline))
void FUN_00121d60(void *mode_tag __attribute__((unused)), void *animation __attribute__((unused)), int animation_index __attribute__((unused)), void *out_node_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x24, %%esp\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "cmpw %%bx, 0x20(%%edi)\n\t"
      "jne .LFUN_00121d60_23\n\t"
      "cmpl %%ebx, %%edx\n\t"
      "je .LFUN_00121d60_2\n\t"
      "movl 0x28(%%edi), %%eax\n\t"
      "cmpl %%ebx, %%eax\n\t"
      "je .LFUN_00121d60_1\n\t"
      "movl 0x4(%%edx), %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00121d60_1\n\t"
      "cmpl %%ebx, %%ecx\n\t"
      "jne .LFUN_00121d60_23\n\t"
      ".LFUN_00121d60_1:\n\t"
      "movswl 0x2c(%%edi), %%eax\n\t"
      "cmpl %%eax, 0xb8(%%edx)\n\t"
      "jne .LFUN_00121d60_23\n\t"
      ".LFUN_00121d60_2:\n\t"
      "testb $1, 0x3a(%%edi)\n\t"
      "je .LFUN_00121d60_4\n\t"
      "movb 0x322600, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00121d60_3\n\t"
      "cmpl %%ebx, 0x88(%%edi)\n\t"
      "jne .LFUN_00121d60_4\n\t"
      ".LFUN_00121d60_3:\n\t"
      "movb $1, 0xf(%%ebp)\n\t"
      "jmp .LFUN_00121d60_5\n\t"
      ".LFUN_00121d60_4:\n\t"
      "movb $0, 0xf(%%ebp)\n\t"
      ".LFUN_00121d60_5:\n\t"
      "movl 0x10(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c120500]\n\t"
      "movl 0x98(%%edi), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "cmpw %%bx, 0x2c(%%edi)\n\t"
      "movl %%eax, %%ecx\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      "movl %%edx, -0x8(%%ebp)\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "movl %%ebx, -0x14(%%ebp)\n\t"
      "movl %%ebx, -0x20(%%ebp)\n\t"
      "jle .LFUN_00121d60_21\n\t"
      "pushl %%esi\n\t"
      "jmp .LFUN_00121d60_7\n\t"
      ".LFUN_00121d60_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_00121d60_7:\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "movswl %%bx, %%esi\n\t"
      "shll $5, %%esi\n\t"
      "addl %%edx, %%esi\n\t"
      "testb $0x1f, %%bl\n\t"
      "jne .LFUN_00121d60_8\n\t"
      "movw %%bx, %%ax\n\t"
      "sarw $5, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl 0x5c(%%edi,%%eax,4), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x6c(%%edi,%%eax,4), %%edx\n\t"
      "movl 0x7c(%%edi,%%eax,4), %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      ".LFUN_00121d60_8:\n\t"
      "testb $1, -0x10(%%ebp)\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "pushl %%esi\n\t"
      "je .LFUN_00121d60_10\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00121d60_9\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "movl %%edx, -0x24(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c121330]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00121d60_12\n\t"
      ".LFUN_00121d60_9:\n\t"
      "pushl %%ecx\n\t"
      "call *%[c120810]\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00121d60_12\n\t"
      ".LFUN_00121d60_10:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00121d60_11\n\t"
      "movl 0x4(%%ecx), %%edx\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edx,%%eax,2), %%eax\n\t"
      "addl %%ecx, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c120870]\n\t"
      "pushl %%esi\n\t"
      "call *%[c10ca30]\n\t"
      "addl $0xc, %%esp\n\t"
      "jmp .LFUN_00121d60_12\n\t"
      ".LFUN_00121d60_11:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c120810]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl $8, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00121d60_12:\n\t"
      "movl -0x10(%%ebp), %%ecx\n\t"
      "movb -0x18(%%ebp), %%al\n\t"
      "shrl $1, %%ecx\n\t"
      "testb $1, %%al\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "movl %%ecx, -0x10(%%ebp)\n\t"
      "je .LFUN_00121d60_14\n\t"
      "testb %%al, %%al\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "je .LFUN_00121d60_13\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c121640]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00121d60_16\n\t"
      ".LFUN_00121d60_13:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "addl $0xc, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00121d60_16\n\t"
      ".LFUN_00121d60_14:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00121d60_15\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl 0x14(%%eax), %%edx\n\t"
      "leal (%%edx,%%ecx,4), %%ecx\n\t"
      "addl %%eax, %%ecx\n\t"
      "movl (%%ecx), %%eax\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "movl %%eax, (%%edx)\n\t"
      "movl 0x4(%%ecx), %%eax\n\t"
      "movl %%eax, 0x4(%%edx)\n\t"
      "movl 0x8(%%ecx), %%ecx\n\t"
      "movl %%ecx, 0x8(%%edx)\n\t"
      "jmp .LFUN_00121d60_16\n\t"
      ".LFUN_00121d60_15:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "leal 0x10(%%esi), %%edx\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "movl 0x4(%%eax), %%ecx\n\t"
      "movl %%ecx, 0x4(%%edx)\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "movl %%eax, 0x8(%%edx)\n\t"
      "addl $0xc, -0x8(%%ebp)\n\t"
      ".LFUN_00121d60_16:\n\t"
      "movl -0x18(%%ebp), %%ecx\n\t"
      "movb -0x1c(%%ebp), %%al\n\t"
      "shrl $1, %%ecx\n\t"
      "testb $1, %%al\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "movl %%ecx, -0x18(%%ebp)\n\t"
      "je .LFUN_00121d60_18\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00121d60_17\n\t"
      "movswl 0x10(%%ebp), %%ecx\n\t"
      "addl $0x1c, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl -0x20(%%ebp), %%esi\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, -0x24(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "fildl -0x24(%%ebp)\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%edi\n\t"
      "call *%[c121940]\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%esi\n\t"
      "movl %%esi, -0x20(%%ebp)\n\t"
      "jmp .LFUN_00121d60_20\n\t"
      ".LFUN_00121d60_17:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl (%%eax), %%edx\n\t"
      "addl $4, %%eax\n\t"
      "movl %%edx, 0x1c(%%esi)\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "jmp .LFUN_00121d60_20\n\t"
      ".LFUN_00121d60_18:\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00121d60_19\n\t"
      "movl $0x3f800000, 0x1c(%%esi)\n\t"
      "jmp .LFUN_00121d60_20\n\t"
      ".LFUN_00121d60_19:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl (%%eax), %%ecx\n\t"
      "addl $4, %%eax\n\t"
      "movl %%ecx, 0x1c(%%esi)\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      ".LFUN_00121d60_20:\n\t"
      "movl -0x1c(%%ebp), %%edx\n\t"
      "shrl $1, %%edx\n\t"
      "incl %%ebx\n\t"
      "cmpw 0x2c(%%edi), %%bx\n\t"
      "movl %%edx, -0x1c(%%ebp)\n\t"
      "jl .LFUN_00121d60_6\n\t"
      "popl %%esi\n\t"
      ".LFUN_00121d60_21:\n\t"
      "movb 0xf(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00121d60_24\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c120500]\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "subl %%eax, %%ecx\n\t"
      "movswl 0x24(%%edi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "je .LFUN_00121d60_22\n\t"
      "pushl $1\n\t"
      "pushl $0x141\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291230\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121d60_22:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl 0x98(%%edi), %%edx\n\t"
      "movl 0x8c(%%edi), %%ecx\n\t"
      "subl %%edx, %%eax\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "je .LFUN_00121d60_24\n\t"
      "pushl $1\n\t"
      "pushl $0x142\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2911c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00121d60_23:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c123aa0]\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_00121d60_24:\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      "nop\n\t"
      :
      : [c120500] "m"(b121d60_c120500), [c121330] "m"(b121d60_c121330), [c120810] "m"(b121d60_c120810), [c120870] "m"(b121d60_c120870), [c10ca30] "m"(b121d60_c10ca30), [c121640] "m"(b121d60_c121640), [c121940] "m"(b121d60_c121940), [assert] "m"(b121d60_assert), [exitfn] "m"(b121d60_exitfn), [c123aa0] "m"(b121d60_c123aa0)
      : "memory");
}
#else
#error "FUN_00121d60: clang naked draft required"
#endif


/* FUN_00123aa0 (0x123aa0) — Fill default node transforms from mode tag.
 *
 * Iterates over the nodes in a model mode tag (tag block at mode_tag+0xb8,
 * element size 0x9c). For each node, copies the default rotation quaternion
 * from element+0x34 (4 floats) and default translation from element+0x28
 * (3 floats) into the output node_data array (stride 0x20 per node).
 * Sets scale to 1.0f for each node.
 *
 * This is the fallback path used by FUN_00121d60 when the animation type is
 * nonzero or the mode_tag node count doesn't match the animation.
 *
 * Confirmed: cdecl, 2 args (mode_tag ptr, out_node_data ptr).
 * Confirmed: CALL tag_block_get_element(mode_tag+0xb8, index, 0x9c) at
 * 0x123ac7. Confirmed: Copies element+0x34..0x43 (rotation) to out+0x00..0x0F.
 * Confirmed: Copies element+0x28..0x33 (translation) to out+0x10..0x1B.
 * Confirmed: Sets out+0x1c = 0x3f800000 (1.0f scale).
 * Confirmed: Loop counter is short via MOVSX at 0x123b0c; compared to [EDI] at
 * 0x123b19.
 */
void FUN_00123aa0(void *mode_tag, void *out_node_data)
{
  int param_1;
  int param_2;
  short sVar1;
  int iVar4;
  char *element;
  int *out;

  param_1 = (int)mode_tag;
  param_2 = (int)out_node_data;
  iVar4 = 0;
  sVar1 = 0;

  if (0 < *(int *)(param_1 + 0xb8)) {
    do {
      element =
        (char *)tag_block_get_element((void *)(param_1 + 0xb8), iVar4, 0x9c);
      out = (int *)(param_2 + iVar4 * 0x20);

      /* rotation quaternion from element+0x34 */
      out[0] = *(int *)(element + 0x34);
      out[1] = *(int *)(element + 0x38);
      out[2] = *(int *)(element + 0x3c);
      out[3] = *(int *)(element + 0x40);

      /* translation from element+0x28 */
      out[4] = *(int *)(element + 0x28);
      out[5] = *(int *)(element + 0x2c);
      out[6] = *(int *)(element + 0x30);

      /* scale = 1.0f */
      out[7] = 0x3f800000;

      sVar1 = sVar1 + 1;
      iVar4 = (int)sVar1;
    } while (iVar4 < *(int *)(param_1 + 0xb8));
  }
}
/* --- model_animations.obj batch drafts (2026-07-26) --- */

/* FUN_00120250 (0x120250) — XBE naked draft (batch 254). */
#if defined(__clang__)
static void (*const b120250_c11fd50)(void *pool) = FUN_0011fd50;
static void (*const b120250_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b120250_exitfn)(int) = system_exit;
static int (*const b120250_c119610)(data_t *data) = data_new_at_index;
static void *(*const b120250_c11fef0)(void *a, int b) = FUN_0011fef0;
static char (*const b120250_c11ff70)(void *anim) = FUN_0011ff70;
static void (*const b120250_c1196d0)(data_t *data, int datum_handle) = datum_delete;

__attribute__((naked, noinline))
void FUN_00120250(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "orl $0xffffffff, %%ebx\n\t"
      "call *%[c11fd50]\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00120250_1\n\t"
      "cmpb $0, (%%esi)\n\t"
      "jne .LFUN_00120250_1\n\t"
      "pushl $1\n\t"
      "pushl $0x60\n\t"
      "pushl $0x2905b0\n\t"
      "pushl $0x2906c4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00120250_1:\n\t"
      "movw 0x8(%%esi), %%cx\n\t"
      "movw 0xc(%%ebp), %%di\n\t"
      "cmpw %%cx, %%di\n\t"
      "jg .LFUN_00120250_2\n\t"
      "movw 0xa(%%esi), %%ax\n\t"
      "movw 0x10(%%ebp), %%dx\n\t"
      "cmpw %%ax, %%dx\n\t"
      "jg .LFUN_00120250_2\n\t"
      "movswl %%dx, %%edx\n\t"
      "movswl %%di, %%edi\n\t"
      "imull %%edx, %%edi\n\t"
      "movl 0x10(%%esi), %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "imull %%ecx, %%eax\n\t"
      "addl %%edi, %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jge .LFUN_00120250_2\n\t"
      "movl 0x18(%%esi), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%ebx\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_00120250_2\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c11fef0]\n\t"
      "movw 0xc(%%ebp), %%cx\n\t"
      "movw 0x10(%%ebp), %%dx\n\t"
      "movw %%cx, 0x8(%%eax)\n\t"
      "movw %%dx, 0xa(%%eax)\n\t"
      "movb (%%esi), %%dl\n\t"
      "addl $8, %%esp\n\t"
      "testb %%dl, %%dl\n\t"
      "sete %%cl\n\t"
      "movb %%cl, 0x2(%%eax)\n\t"
      "movl 0x10(%%esi), %%ecx\n\t"
      "movb 0x14(%%ebp), %%al\n\t"
      "addl %%edi, %%ecx\n\t"
      "testb %%al, %%al\n\t"
      "movl %%ecx, 0x10(%%esi)\n\t"
      "je .LFUN_00120250_2\n\t"
      "pushl %%esi\n\t"
      "call *%[c11ff70]\n\t"
      "addl $4, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00120250_2\n\t"
      "movl 0x10(%%esi), %%eax\n\t"
      "movl 0x18(%%esi), %%edx\n\t"
      "subl %%edi, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, 0x10(%%esi)\n\t"
      "call *%[c1196d0]\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "orl $0xffffffff, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00120250_2:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebx, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c11fd50] "m"(b120250_c11fd50), [assert] "m"(b120250_assert), [exitfn] "m"(b120250_exitfn), [c119610] "m"(b120250_c119610), [c11fef0] "m"(b120250_c11fef0), [c11ff70] "m"(b120250_c11ff70), [c1196d0] "m"(b120250_c1196d0)
      : "memory");
}
#else
#error "FUN_00120250: clang naked draft required"
#endif


/* FUN_00120340 (0x120340) — readable C lift. */
void FUN_00120340(void *anim)
{
  void *block;
  short *entry;
  int i;
  int n;
  int w;
  int h;

  FUN_0011fd50(anim);
  if (*(unsigned char *)anim == 0) {
    display_assert((const char *)0x290710, (const char *)0x2905b0, 0x8a, 1);
    system_exit(-1);
  }
  block = *(void **)((char *)anim + 0x18);
  entry = *(short **)((char *)block + 0x34);
  n = *(short *)((char *)block + 0x2e);
  for (i = 0; i < n; i++) {
    if (entry[0] != 0 && *((unsigned char *)entry + 2) == 0) {
      w = entry[4];
      h = entry[5];
      *(int *)((char *)anim + 0x10) -= w * h;
      datum_delete(*(void **)((char *)anim + 0x18), i);
    }
    entry = (short *)((char *)entry + 0xc);
  }
  *(unsigned char *)anim = 0;
  if (!FUN_0011ff70(anim)) {
    display_assert((const char *)0x2906fc, (const char *)0x2905b0, 0x9d, 1);
    system_exit(-1);
  }
}



/* FUN_00120400 (0x120400) — readable C lift. */
void FUN_00120400(void *anim)
{
  void *block;
  short *entry;
  int i;
  int n;

  FUN_0011fd50(anim);
  if (*(unsigned char *)anim == 0) {
    display_assert((const char *)0x290710, (const char *)0x2905b0, 0xaa, 1);
    system_exit(-1);
  }
  if (!FUN_0011ff70(anim))
    return;
  block = *(void **)((char *)anim + 0x18);
  entry = *(short **)((char *)block + 0x34);
  n = *(short *)((char *)block + 0x2e);
  for (i = 0; i < n; i++) {
    if (entry[0] != 0)
      *((unsigned char *)entry + 2) = 1;
    entry = (short *)((char *)entry + 0xc);
  }
  *(unsigned char *)anim = 0;
}



/* FUN_00120470 (0x120470) — readable C lift. */
void FUN_00120470(void *pool, int datum_handle)
{
  FUN_0011fd50(pool);
  datum_delete(*(data_t **)((char *)pool + 0x18), datum_handle);
  ((void (*)(void *))FUN_0011ff70)(pool);
}

/* FUN_001204a0 (0x1204a0) — readable C lift. */
char FUN_001204a0(void *anim, short a, short b)
{
  short old_a;
  short old_b;

  FUN_0011fd50(anim);
  old_a = *(short *)((char *)anim + 8);
  old_b = *(short *)((char *)anim + 0xa);
  *(short *)((char *)anim + 8) = a;
  *(short *)((char *)anim + 0xa) = b;
  if (FUN_0011ff70(anim))
    return 1;
  *(short *)((char *)anim + 8) = old_a;
  *(short *)((char *)anim + 0xa) = old_b;
  FUN_0011ff70(anim);
  return 0;
}



/* FUN_00120620 (0x120620) — readable C lift. */
char FUN_00120620(void *animation)
{
  extern char DAT_00290ce4[];
  extern char DAT_00290cd8[];
  if (!animation) {
    display_assert(DAT_00290cd8, DAT_00290ce4, 0x26, 1);
    system_exit(-1);
  }
  if (!(*(unsigned char *)((char *)animation + 0x3a) & 1))
    return 0;
  if (*(unsigned char *)0x322600)
    return 1;
  if (*(int *)((char *)animation + 0x88) == 0)
    return 1;
  return 0;
}

/* build_damage_animation_index (0x120670) — readable C lift from XBE leaf. */
int build_damage_animation_index(int16_t a, int16_t b, int16_t c)
{
  if (a < 0 || a >= 4) {
    extern char DAT_00290d98[];
    extern char DAT_00290ce4[];
    display_assert(DAT_00290d98, DAT_00290ce4, 0x37, 1);
    system_exit(-1);
  }
  if (b < 0 || b >= 4) {
    extern char DAT_00290d48[];
    extern char DAT_00290ce4[];
    display_assert(DAT_00290d48, DAT_00290ce4, 0x38, 1);
    system_exit(-1);
  }
  if (c < 0 || c >= 0xb) {
    extern char DAT_00290d10[];
    extern char DAT_00290ce4[];
    display_assert(DAT_00290d10, DAT_00290ce4, 0x39, 1);
    system_exit(-1);
  }
  return ((int)b + (int)a * 4) * 0xb + (int)c;
}



/* FUN_00120710 (0x120710) — readable C lift from XBE leaf.
 * Sum per-frame event times from anim+0x54; snapshot sum at frame
 * anim+0x34 into attack_time_out; write total into damage_time_out.
 * Event stride depends on signed type at anim+0x26 (1→8, 2→0xc, 3→0x10). */
void FUN_00120710(int anim_entry, int tick_out, int damage_time_out)
{
  char *anim;
  float acc;
  float at_damage;
  float *events;
  float *attack_time_out;
  float *total_time_out;
  int16_t count;
  int16_t damage_frame;
  int16_t event_type;
  int i;

  anim = (char *)anim_entry;
  attack_time_out = (float *)tick_out;
  total_time_out = (float *)damage_time_out;
  acc = *(float *)0x2533c0;
  at_damage = 0.0f;
  events = *(float **)(anim + 0x54);
  count = *(int16_t *)(anim + 0x22);
  if (count > 0) {
    event_type = *(int16_t *)(anim + 0x26);
    damage_frame = *(int16_t *)(anim + 0x34);
    for (i = 0; i < (int)count; i++) {
      if (event_type == 1) {
        acc += *events;
        events = (float *)((char *)events + 8);
      } else if (event_type == 2) {
        acc += *events;
        events = (float *)((char *)events + 0xc);
      } else if (event_type == 3) {
        acc += *events;
        events = (float *)((char *)events + 0x10);
      }
      if ((int16_t)i == damage_frame)
        at_damage = acc;
    }
  }
  if (total_time_out != NULL)
    *total_time_out = acc;
  if (attack_time_out != NULL)
    *attack_time_out = at_damage;
}


/* animation_set_frame_size (0x120790) — readable C lift from XBE leaf. */
void animation_set_frame_size(char *anim)
{
  int total;
  int i;
  int16_t node_count;

  if (anim == NULL) {
    display_assert("animation", "c:\\halo\\SOURCE\\models\\model_animations.c", 0x7b, true);
    system_exit(-1);
  }
  total = 0;
  node_count = *(int16_t *)(anim + 0x2c);
  if (node_count > 0) {
    for (i = 0; i < (int)node_count; i++) {
      unsigned int bit = 1u << (i & 0x1f);
      int word = i >> 5;
      if (*(unsigned int *)(anim + 0x6c + word * 4) & bit) {
        total += 8;
      }
      if (*(unsigned int *)(anim + 0x5c + word * 4) & bit) {
        total += 0xc;
      }
      if (*(unsigned int *)(anim + 0x7c + word * 4) & bit) {
        total += 4;
      }
    }
  }
  *(int16_t *)(anim + 0x24) = (int16_t)total;
}

/* quaternion_decompress_6byte_renormalized (0x120930) — readable C lift. */
void quaternion_decompress_6byte_renormalized(void *compressed, float *out)
{
  quaternion_decompress_6byte(compressed, out);
  sphere_intersects_rectangle3d(out);
}

/* quaternion_compress_8byte (0x120950) — readable C lift. */
void quaternion_compress_8byte(float *q, short *out)
{
  float scale;

  scale = *(float *)0x26a600; /* 32767.0f */
  out[0] = (short)(int64_t)(q[0] * scale);
  out[1] = (short)(int64_t)(q[1] * scale);
  out[2] = (short)(int64_t)(q[2] * scale);
  out[3] = (short)(int64_t)(q[3] * scale);
}

/* quaternion_compress_6byte (0x1209b0) — readable C lift from XBE leaf.
 * Packs 4 quaternion floats into 3 uint16s (inverse of decompress_6byte). */
void quaternion_compress_6byte(float *q, unsigned short *out)
{
  float scale;
  int v0, v1, v2, v3;
  unsigned int eax, ebx, ecx, edx, esi;

  scale = *(float *)0x26a600; /* 32767.0f */
  v1 = (int)(int64_t)(q[1] * scale);
  v2 = (int)(int64_t)(q[2] * scale);
  v3 = (int)(int64_t)(q[3] * scale);
  v0 = (int)(int64_t)(q[0] * scale);

  eax = (unsigned int)v0;
  esi = (unsigned int)v1;
  ebx = (unsigned int)v2;

  ecx = ((unsigned int)(unsigned short)esi) >> 12;
  edx = (ebx >> 8) & 0xff;
  eax &= 0xfff0u;
  esi &= 0xfff0u;
  esi <<= 4;
  eax |= ecx;
  out[0] = (unsigned short)eax;

  eax = (unsigned int)v3;
  esi |= edx;
  ebx = (ebx & 0xffffff00u) | (ebx & 0xf0u);
  edx = (ebx & 0xffu) << 8;
  eax = ((unsigned int)(unsigned short)eax) >> 4;
  out[1] = (unsigned short)esi;
  edx |= eax;
  out[2] = (unsigned short)edx;
}


/* animation_graph_node_matrices_from_orientations (0x120a40) — XBE naked draft (batch 261). */
#if defined(__clang__)
static void *(*const b120a40_tag)(int, int) = tag_get;
static void (*const b120a40_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void *(*const b120a40_elem)(void *, int, int) = tag_block_get_element;
static void (*const b120a40_c109500)(float *out, float *qsp) = FUN_00109500;
static void (*const b120a40_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b120a40_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b120a40_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void animation_graph_node_matrices_from_orientations(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf4, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl 0x1c(%%ebp), %%ecx\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x14(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x74(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[m4x3]\n\t"
      "movl 0x68(%%esi), %%edx\n\t"
      "leal 0x68(%%esi), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jle .Lanimation_graph_node_matrices_from_orientations_9\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "movw %%ax, -0xf4(%%ebp)\n\t"
      "jmp .Lanimation_graph_node_matrices_from_orientations_2\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "movl -0xc(%%ebp), %%ecx\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_2:\n\t"
      "movswl %%ax, %%edx\n\t"
      "movw -0xf4(%%ebp,%%edx,2), %%di\n\t"
      "movswl %%di, %%esi\n\t"
      "pushl $0x40\n\t"
      "incl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .Lanimation_graph_node_matrices_from_orientations_3\n\t"
      "leal -0x74(%%ebp), %%edi\n\t"
      "jmp .Lanimation_graph_node_matrices_from_orientations_4\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_3:\n\t"
      "movswl 0x24(%%ebx), %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "addl %%eax, %%edi\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_4:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109500]\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "addl 0xc(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c109850]\n\t"
      "movl -0x4(%%ebp), %%esi\n\t"
      "orl $0xffffffff, %%edi\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw %%di, 0x20(%%ebx)\n\t"
      "je .Lanimation_graph_node_matrices_from_orientations_6\n\t"
      "cmpw $0x40, %%si\n\t"
      "jl .Lanimation_graph_node_matrices_from_orientations_5\n\t"
      "pushl $1\n\t"
      "pushl $0x4e2\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x290ddc\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_5:\n\t"
      "movw 0x20(%%ebx), %%cx\n\t"
      "movswl %%si, %%eax\n\t"
      "incl %%esi\n\t"
      "movw %%cx, -0xf4(%%ebp,%%eax,2)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_6:\n\t"
      "cmpw %%di, 0x22(%%ebx)\n\t"
      "je .Lanimation_graph_node_matrices_from_orientations_8\n\t"
      "cmpw $0x40, %%si\n\t"
      "jl .Lanimation_graph_node_matrices_from_orientations_7\n\t"
      "pushl $1\n\t"
      "pushl $0x4e8\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x290ddc\n\t"
      "call *%[assert]\n\t"
      "pushl %%edi\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_7:\n\t"
      "movw 0x22(%%ebx), %%ax\n\t"
      "movswl %%si, %%edx\n\t"
      "incl %%esi\n\t"
      "movw %%ax, -0xf4(%%ebp,%%edx,2)\n\t"
      "movl %%esi, -0x4(%%ebp)\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_8:\n\t"
      "cmpw %%si, -0x8(%%ebp)\n\t"
      "jne .Lanimation_graph_node_matrices_from_orientations_1\n\t"
      "popl %%edi\n\t"
      "popl %%ebx\n\t"
      ".Lanimation_graph_node_matrices_from_orientations_9:\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b120a40_tag), [m4x3] "m"(b120a40_m4x3), [elem] "m"(b120a40_elem), [c109500] "m"(b120a40_c109500), [c109850] "m"(b120a40_c109850), [assert] "m"(b120a40_assert), [exitfn] "m"(b120a40_exitfn)
      : "memory");
}
#else
#error "animation_graph_node_matrices_from_orientations: clang naked draft required"
#endif


/* interpolate_node_orientations (0x120ba0) — readable C lift (restored pre-naked). */
void interpolate_node_orientations(void)
{
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00290e18, (char *)0x00290ce4, 1277, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)esi -> jl 0x120c19 */
  display_assert((char *)0x00290e00, (char *)0x00290ce4, 1278, 0);
  system_exit(0);
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x120c9e */
  quaternions_interpolate_and_normalize((float *)0, (float *)0, 0.0f, (float *)0);

  (void)ecx;
  (void)esi;
  (void)edi;
}


/* FUN_00120cb0 (0x120cb0) — readable C lift from XBE leaf. */
short FUN_00120cb0(int animation_graph_tag_index, const char *name)
{
  char *tag;
  char *block;
  int count;
  short i;

  tag = (char *)tag_get(0x616e7472, animation_graph_tag_index);
  block = tag + 0x74;
  count = *(int *)block;
  for (i = 0; i < count; i++) {
    char *el = (char *)tag_block_get_element(block, (int)i, 0xb4);
    if (crt_stricmp(name, el) == 0) {
      return i;
    }
  }
  return (short)0xffff;
}

/* animation_frame_get_xy_translation (0x120ee0) — readable C lift. */
void animation_frame_get_xy_translation(void *animation, short frame_index, int *out_xy)
{
  int *frame;
  if (*(short *)((char *)animation + 0x26) == 1) {
    frame = (int *)((void *(*)(void *, short, short))FUN_00120590)(animation, frame_index, 8);
    out_xy[0] = frame[0];
    out_xy[1] = frame[1];
  } else {
    out_xy[0] = 0;
    out_xy[1] = 0;
  }
}

/* inverse_kinematics_adjust_matrices (0x120fd0) — XBE naked draft (batch 246). */
#if defined(__clang__)
static float (*const b120fd0_norm)(float *) = normalize3d;

__attribute__((naked, noinline))
void inverse_kinematics_adjust_matrices(float *composed_matrix __attribute__((unused)), int node_matrix_b __attribute__((unused)), int node_matrix_c __attribute__((unused)), int node_matrix_d __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x34, %%esp\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "flds 0x28(%%edi)\n\t"
      "leal 0x28(%%edi), %%eax\n\t"
      "fsubs 0x28(%%ebx)\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "flds 0x4(%%eax)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "fsubs 0x2c(%%ebx)\n\t"
      "movl %%eax, -0x10(%%ebp)\n\t"
      "flds 0x8(%%eax)\n\t"
      "fsubs 0x30(%%ebx)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x28(%%ecx)\n\t"
      "fsubs (%%eax)\n\t"
      "flds 0x2c(%%ecx)\n\t"
      "fsubs 0x4(%%eax)\n\t"
      "flds 0x30(%%ecx)\n\t"
      "fsubs 0x8(%%eax)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x28(%%ebx)\n\t"
      "fsubs 0x28(%%esi)\n\t"
      "flds 0x2c(%%ebx)\n\t"
      "fsubs 0x2c(%%esi)\n\t"
      "flds 0x30(%%ebx)\n\t"
      "fsubs 0x30(%%esi)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fld %%st(2)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fld %%st(3)\n\t"
      "fmul %%st(4), %%st(0)\n\t"
      ".byte 0xde, 0xc1\n\t"
      "fsqrt\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "flds (%%eax)\n\t"
      "fsubs 0x28(%%ebx)\n\t"
      "flds 0x2c(%%edi)\n\t"
      "fsubs 0x2c(%%ebx)\n\t"
      "flds 0x30(%%edi)\n\t"
      "fsubs 0x30(%%ebx)\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x10(%%ebp)\n\t"
      "flds 0x28(%%esi)\n\t"
      "fsubs 0x28(%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x1c(%%ebp)\n\t"
      "leal -0x28(%%ebp), %%eax\n\t"
      "flds 0x2c(%%esi)\n\t"
      "pushl %%eax\n\t"
      "fsubs 0x2c(%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x18(%%ebp)\n\t"
      "flds 0x30(%%esi)\n\t"
      "fsubs 0x30(%%ebx)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x14(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x28(%%ebp)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(2), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x24(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(3), %%st(0)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x20(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "addl $4, %%esp\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds -0x20(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds -0x28(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "flds -0x24(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fadds 0xc(%%ebp)\n\t"
      "fmuls 0x291060\n\t"
      "fcoms 0x10(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .Linverse_kinematics_adjust_matrices_1\n\t"
      "flds -0x1c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x28(%%ebx)\n\t"
      "fstps 0x28(%%esi)\n\t"
      "flds -0x18(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x2c(%%ebx)\n\t"
      "fstps 0x2c(%%esi)\n\t"
      "flds -0x14(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fadds 0x30(%%ebx)\n\t"
      "fstps 0x30(%%esi)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "jmp .Linverse_kinematics_adjust_matrices_2\n\t"
      ".Linverse_kinematics_adjust_matrices_1:\n\t"
      "fstp %%st(0)\n\t"
      ".Linverse_kinematics_adjust_matrices_2:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "leal 0x4(%%ebx), %%esi\n\t"
      "fmuls 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls 0x10(%%ebp)\n\t"
      "fadd %%st(1), %%st(0)\n\t"
      "flds -0x4(%%ebp)\n\t"
      "fmuls -0x4(%%ebp)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadd %%st(0), %%st(0)\n\t"
      ".byte 0xde, 0xf9\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "fld %%st(0)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fsubr %%st(2), %%st(0)\n\t"
      "fsqrt\n\t"
      "flds -0x34(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fadds -0x4(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0x8(%%ebp)\n\t"
      "fld %%st(1)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fadds -0x8(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds -0x2c(%%ebp)\n\t"
      "fmul %%st(1), %%st(0)\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "fstp %%st(0)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fadds -0xc(%%ebp)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "fstp %%st(0)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "leal 0x1c(%%ebx), %%eax\n\t"
      "flds (%%esi)\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      "flds 0x10(%%ebx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x10(%%ebx)\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x18(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x18(%%ebx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x14(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%eax)\n\t"
      "fstps 0x4(%%eax)\n\t"
      "fstps 0x8(%%eax)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "flds 0x1c(%%ebx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds 0x20(%%ebx)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds (%%esi)\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x1c(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%esi)\n\t"
      "fmuls 0x20(%%ebx)\n\t"
      "flds 0x4(%%esi)\n\t"
      "fmuls 0x24(%%ebx)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x10(%%ebx)\n\t"
      "fstps 0x14(%%ebx)\n\t"
      "fstps 0x18(%%ebx)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls (%%esi)\n\t"
      "fadds 0x28(%%ebx)\n\t"
      "fstps -0x34(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "fadds 0x2c(%%ebx)\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "leal 0x4(%%edi), %%esi\n\t"
      "pushl %%esi\n\t"
      "fadds 0x30(%%ebx)\n\t"
      "leal 0x1c(%%edi), %%ebx\n\t"
      "fstps -0x2c(%%ebp)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls -0x1c(%%ebp)\n\t"
      "fsubs -0x4(%%ebp)\n\t"
      "fstps (%%esi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls -0x18(%%ebp)\n\t"
      "fsubs -0x8(%%ebp)\n\t"
      "fstps 0x4(%%esi)\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fmuls -0x14(%%ebp)\n\t"
      "fsubs -0xc(%%ebp)\n\t"
      "fstps 0x8(%%esi)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%ebx\n\t"
      "flds 0x14(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      "flds 0x10(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x10(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x18(%%edi)\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x18(%%edi)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "flds 0x14(%%edi)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps (%%ebx)\n\t"
      "fstps 0x4(%%ebx)\n\t"
      "fstps 0x8(%%ebx)\n\t"
      "call *%[norm]\n\t"
      "fstp %%st(0)\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "flds (%%ebx)\n\t"
      "movl -0x34(%%ebp), %%ecx\n\t"
      "fmuls 0x4(%%esi)\n\t"
      "movl -0x30(%%ebp), %%edx\n\t"
      "flds 0x4(%%ebx)\n\t"
      "addl $0x10, %%esp\n\t"
      "fmuls (%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls (%%esi)\n\t"
      "flds (%%ebx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "flds 0x4(%%ebx)\n\t"
      "fmuls 0x8(%%esi)\n\t"
      "flds 0x8(%%ebx)\n\t"
      "fmuls 0x4(%%esi)\n\t"
      ".byte 0xde, 0xe9\n\t"
      "fstps 0x10(%%edi)\n\t"
      "fstps 0x14(%%edi)\n\t"
      "fstps 0x18(%%edi)\n\t"
      "movl %%ecx, (%%eax)\n\t"
      "movl -0x2c(%%ebp), %%ecx\n\t"
      "movl %%edx, 0x4(%%eax)\n\t"
      "movl %%ecx, 0x8(%%eax)\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl 0x14(%%ebp), %%edi\n\t"
      "movl $0xd, %%ecx\n\t"
      "rep movsl\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [norm] "m"(b120fd0_norm)
      : "memory");
}
#else
#error "inverse_kinematics_adjust_matrices: clang naked draft required"
#endif


/* FUN_00121330 (0x121330) — XBE naked draft (batch 244). */
#if defined(__clang__)
static void * (*const b121330_c19b1a0)(void *tag_data, int offset, int size) = tag_data_get_pointer;
static void (*const b121330_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b121330_exitfn)(int) = system_exit;
static void (*const b121330_c120870)(void *compressed_data, float *dest) = quaternion_decompress_6byte;
static void (*const b121330_c10ca30)(float *quaternion) = sphere_intersects_rectangle3d;
static double (*const b121330_c1d9c2b)(double x) = floor;
static short (*const b121330_c120d10)(unsigned short *keyframe_frame_indices, short target_frame_index, short keyframe_count) = FUN_00120d10;
static void (*const b121330_c10cb60)(float *q1, float *q2, float t, float *out) = quaternions_interpolate_and_normalize;

__attribute__((naked, noinline))
void FUN_00121330(void *animation __attribute__((unused)), float frame __attribute__((unused)), unsigned short rotation_count __attribute__((unused)), short node_index __attribute__((unused)), void *out_rotation __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x2c, %%esp\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movl 0x88(%%eax), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl $0\n\t"
      "pushl %%ecx\n\t"
      "addl $0xa0, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c19b1a0]\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "fcomps 0x2533c0\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0x2c(%%esi,%%edx,4), %%eax\n\t"
      "movl 0x4(%%esi), %%edi\n\t"
      "movl %%eax, %%ebx\n\t"
      "andl $0xfff, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "addl $0xc, %%esp\n\t"
      "fnstsw %%ax\n\t"
      "addl %%esi, %%edi\n\t"
      "shrl $0xc, %%ebx\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00121330_1\n\t"
      "pushl $1\n\t"
      "pushl $0x594\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2911a4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_1:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "fildl -0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00121330_2\n\t"
      "pushl $1\n\t"
      "pushl $0x596\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291174\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_2:\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      "jge .LFUN_00121330_3\n\t"
      "pushl $1\n\t"
      "pushl $0x598\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291160\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0, 0x10(%%ebp)\n\t"
      ".LFUN_00121330_3:\n\t"
      "jne .LFUN_00121330_4\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%esi\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal (%%edi,%%edx,2), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[c120870]\n\t"
      "pushl %%esi\n\t"
      "call *%[c10ca30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00121330_4:\n\t"
      "movl 0x8(%%esi), %%edx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "leal (%%eax,%%eax,2), %%ecx\n\t"
      "leal (%%edx,%%ecx,2), %%ecx\n\t"
      "addl %%esi, %%ecx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "movl (%%esi), %%ecx\n\t"
      "leal (%%ecx,%%eax,2), %%ebx\n\t"
      "subl $8, %%esp\n\t"
      "addl %%esi, %%ebx\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0xc(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0xc(%%ebp)\n\t"
      "fistps -0x4(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "testw %%ax, %%ax\n\t"
      "jl .LFUN_00121330_5\n\t"
      "movswl 0x10(%%ebp), %%edx\n\t"
      "movzwl -0x2(%%ebx,%%edx,2), %%ecx\n\t"
      "movswl %%ax, %%edx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "jle .LFUN_00121330_6\n\t"
      ".LFUN_00121330_5:\n\t"
      "pushl $1\n\t"
      "pushl $0x5ab\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291118\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_6:\n\t"
      "movswl 0x10(%%ebp), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "movswl 0x22(%%eax), %%ecx\n\t"
      "movzwl -0x2(%%ebx,%%esi,2), %%edx\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%edx\n\t"
      "je .LFUN_00121330_7\n\t"
      "pushl $1\n\t"
      "pushl $0x5ac\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2910d0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_7:\n\t"
      "movw (%%ebx), %%dx\n\t"
      "movswl -0x4(%%ebp), %%eax\n\t"
      "movzwl %%dx, %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "jge .LFUN_00121330_8\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal (%%edi,%%eax,2), %%esi\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movl %%edx, %%ebx\n\t"
      "jmp .LFUN_00121330_12\n\t"
      ".LFUN_00121330_8:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw -0x2(%%ebx,%%esi,2), %%cx\n\t"
      "movzwl %%cx, %%edx\n\t"
      "cmpl %%edx, %%eax\n\t"
      "jne .LFUN_00121330_9\n\t"
      "movl -0x8(%%ebp), %%edx\n\t"
      "leal (%%esi,%%esi,2), %%eax\n\t"
      "leal -0x6(%%edx,%%eax,2), %%esi\n\t"
      "movswl 0x14(%%ebp), %%eax\n\t"
      "leal (%%eax,%%eax,2), %%eax\n\t"
      "leal 0x1(%%ecx), %%ebx\n\t"
      "leal (%%edi,%%eax,2), %%edi\n\t"
      "jmp .LFUN_00121330_12\n\t"
      ".LFUN_00121330_9:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "movl 0x10(%%ebp), %%edi\n\t"
      "pushl %%ecx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c120d10]\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, %%edi\n\t"
      "testw %%di, %%di\n\t"
      "jl .LFUN_00121330_10\n\t"
      "movswl %%di, %%edx\n\t"
      "decl %%esi\n\t"
      "cmpl %%esi, %%edx\n\t"
      "jl .LFUN_00121330_11\n\t"
      ".LFUN_00121330_10:\n\t"
      "pushl $1\n\t"
      "pushl $0x5c0\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x290ea4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_11:\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movswl %%di, %%eax\n\t"
      "movw (%%ebx,%%eax,2), %%cx\n\t"
      "movw 0x2(%%ebx,%%eax,2), %%bx\n\t"
      "leal (%%eax,%%eax,2), %%edx\n\t"
      "leal (%%esi,%%edx,2), %%esi\n\t"
      "leal 0x6(%%esi), %%edi\n\t"
      ".LFUN_00121330_12:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movl %%ecx, 0x10(%%ebp)\n\t"
      "fildl 0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x44, %%ah\n\t"
      "jp .LFUN_00121330_13\n\t"
      "movl 0x18(%%ebp), %%edi\n\t"
      "fstp %%st(0)\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c120870]\n\t"
      "pushl %%edi\n\t"
      "call *%[c10ca30]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_00121330_13:\n\t"
      "flds 0xc(%%ebp)\n\t"
      "movswl %%bx, %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "fsub %%st(1), %%st(0)\n\t"
      "subl %%ecx, %%eax\n\t"
      "movl %%eax, 0x10(%%ebp)\n\t"
      "fidivl 0x10(%%ebp)\n\t"
      "fstps 0x10(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomp %%st(1)\n\t"
      "fnstsw %%ax\n\t"
      "fstp %%st(0)\n\t"
      "testb $1, %%ah\n\t"
      "je .LFUN_00121330_14\n\t"
      "pushl $1\n\t"
      "pushl $0x5d3\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291098\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_14:\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $0x41, %%ah\n\t"
      "je .LFUN_00121330_15\n\t"
      "pushl $1\n\t"
      "pushl $0x5d4\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291064\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00121330_15:\n\t"
      "leal -0x2c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c120870]\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c120870]\n\t"
      "movl 0x18(%%ebp), %%edx\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "leal -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[c10cb60]\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c19b1a0] "m"(b121330_c19b1a0), [assert] "m"(b121330_assert), [exitfn] "m"(b121330_exitfn), [c120870] "m"(b121330_c120870), [c10ca30] "m"(b121330_c10ca30), [c1d9c2b] "m"(b121330_c1d9c2b), [c120d10] "m"(b121330_c120d10), [c10cb60] "m"(b121330_c10cb60)
      : "memory");
}
#else
#error "FUN_00121330: clang naked draft required"
#endif


/* animation_update_internal (0x121c30) — XBE naked draft (batch 250). */
#if defined(__clang__)
static void *(*const b121c30_tag)(int, int) = tag_get;
static void (*const b121c30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b121c30_exitfn)(int) = system_exit;
static void *(*const b121c30_elem)(void *, int, int) = tag_block_get_element;
static int (*const b121c30_c120f20)(int update_kind, int animation_graph_tag_index, int16_t animation_index) = model_animation_choose_random;

__attribute__((naked, noinline))
int animation_update_internal(int update_kind __attribute__((unused)), int animation_graph_tag_index __attribute__((unused)), short *state __attribute__((unused)), int *out_sound __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "pushl $0x616e7472\n\t"
      "call *%[tag]\n\t"
      "movl 0x10(%%ebp), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "testl %%esi, %%esi\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .Lanimation_update_internal_1\n\t"
      "pushl $1\n\t"
      "pushl $0x93\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x282dc4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lanimation_update_internal_1:\n\t"
      "movswl (%%esi), %%ecx\n\t"
      "pushl $0xb4\n\t"
      "pushl %%ecx\n\t"
      "leal 0x74(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[elem]\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%ecx, %%ecx\n\t"
      "movl %%eax, %%edi\n\t"
      "je .Lanimation_update_internal_3\n\t"
      "movw 0x3c(%%edi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lanimation_update_internal_2\n\t"
      "movw 0x3e(%%edi), %%dx\n\t"
      "cmpw 0x2(%%esi), %%dx\n\t"
      "jne .Lanimation_update_internal_2\n\t"
      "movswl %%ax, %%eax\n\t"
      "pushl $0x14\n\t"
      "pushl %%eax\n\t"
      "addl $0x54, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[elem]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "addl $0xc, %%esp\n\t"
      "movl %%ecx, (%%edx)\n\t"
      "jmp .Lanimation_update_internal_3\n\t"
      ".Lanimation_update_internal_2:\n\t"
      "movl $0xffffffff, (%%ecx)\n\t"
      ".Lanimation_update_internal_3:\n\t"
      "incw 0x2(%%esi)\n\t"
      "movw 0x2(%%esi), %%cx\n\t"
      "movw 0x22(%%edi), %%ax\n\t"
      "cmpw %%ax, %%cx\n\t"
      "jl .Lanimation_update_internal_6\n\t"
      "movw 0x2e(%%edi), %%cx\n\t"
      "testw %%cx, %%cx\n\t"
      "jle .Lanimation_update_internal_5\n\t"
      "movswl %%ax, %%eax\n\t"
      "movswl %%cx, %%ecx\n\t"
      "decl %%eax\n\t"
      "cmpl %%eax, %%ecx\n\t"
      "jg .Lanimation_update_internal_4\n\t"
      "movl %%ecx, %%eax\n\t"
      ".Lanimation_update_internal_4:\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl $4, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_update_internal_5:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x42(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[c120f20]\n\t"
      "addl $0xc, %%esp\n\t"
      "popl %%edi\n\t"
      "movw %%ax, (%%esi)\n\t"
      "movw $0, 0x2(%%esi)\n\t"
      "popl %%esi\n\t"
      "movl $3, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_update_internal_6:\n\t"
      "movswl %%cx, %%edx\n\t"
      "movswl %%ax, %%eax\n\t"
      "incl %%edx\n\t"
      "cmpl %%eax, %%edx\n\t"
      "jne .Lanimation_update_internal_7\n\t"
      "cmpw $0, 0x2e(%%edi)\n\t"
      "jne .Lanimation_update_internal_7\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $2, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_update_internal_7:\n\t"
      "cmpw 0x34(%%edi), %%cx\n\t"
      "je .Lanimation_update_internal_8\n\t"
      "cmpw 0x36(%%edi), %%cx\n\t"
      "jne .Lanimation_update_internal_9\n\t"
      ".Lanimation_update_internal_8:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $1, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lanimation_update_internal_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "xorl %%eax, %%eax\n\t"
      "popl %%ebx\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [tag] "m"(b121c30_tag), [assert] "m"(b121c30_assert), [exitfn] "m"(b121c30_exitfn), [elem] "m"(b121c30_elem), [c120f20] "m"(b121c30_c120f20)
      : "memory");
}
#else
#error "animation_update_internal: clang naked draft required"
#endif


/* replacement_animation_apply (0x122060) — readable C lift (restored pre-naked). */
void replacement_animation_apply(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  /* relift: cmp word ptr [esi + 0x20], 2 -> jne 0x12222c */
  /* cmp (int16_t)edi, (int16_t)ebx -> jl 0x12222a */
  /* relift: cmp (int16_t)edi, word ptr [esi + 0x22] -> jge 0x12222a */
  FUN_00120620(0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* test (char)ebx, 0x1f -> jne 0x1220e6 */
  /* relift: test byte ptr [ebp - 0xc], 1 -> je 0x12212e */
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  quaternion_decompress_8byte((void *)(uintptr_t)eax, (float *)0);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> je 0x1221c8 */
  overlay_animation_apply_continuous_scaled((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  /* test (char)eax, (char)eax -> jne 0x12222a */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* cmp ecx, eax -> je 0x12222a */
  display_assert((char *)0x002912a0, (char *)0x00290ce4, 391, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


/* overlay_animation_apply (0x122240) — readable C lift (restored pre-naked). */
void overlay_animation_apply(void *animation, int frame, void *node_output)
{
  (void)animation;
  (void)frame;
  (void)node_output;
}


/* overlay_animation_apply_scaled (0x122450) — readable C lift. */
void overlay_animation_apply_scaled(void *animation, int frame, float scale,
                                    void *node_output)
{
  (void)animation;
  (void)scale;
  (void)frame;
  (void)node_output;
}



/* FUN_00122690 (0x122690) — XBE naked draft (batch 250). */
#if defined(__clang__)
static void (*const b122690_c1daf7e)(void) = FUN_001daf7e;
static double (*const b122690_c1d9c2b)(double x) = floor;
static void (*const b122690_c8f390)(unsigned __int16 a1, const char *a2, ...) = error;
static void * (*const b122690_c120500)(void *animation, short frame_index) = FUN_00120500;
static void (*const b122690_c121330)(void *animation, float frame, unsigned short rotation_count, short node_index, void *out_rotation) = FUN_00121330;
static void (*const b122690_c10cb60)(float *q1, float *q2, float t, float *out) = quaternions_interpolate_and_normalize;
static void (*const b122690_c10b9c0)(float *q1, float *q2, float *out) = FUN_0010b9c0;
static void (*const b122690_c121640)(void *animation, float frame, unsigned short translation_count, short node_index, void *out_translation) = animation_get_node_orientations;
static void (*const b122690_c10b7d0)(float *a, float *b, float blend, float *out) = points_interpolate;
static void (*const b122690_c121940)(void *animation, float frame, unsigned short scale_count, short node_index, void *out_scale) = overlay_animation_apply_continuous_scaled;
static void (*const b122690_c10b820)(float a, float b, float blend, float *out) = scalars_interpolate;
static void (*const b122690_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b122690_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00122690(void *animation __attribute__((unused)), float frame __attribute__((unused)), void *node_data __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x7c, %%esp\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%esi\n\t"
      "fldl 0x2573d8\n\t"
      "pushl %%edi\n\t"
      "call *%[c1daf7e]\n\t"
      "fstps -0x4(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "subl $8, %%esp\n\t"
      "fabs\n\t"
      "fstpl (%%esp)\n\t"
      "call *%[c1d9c2b]\n\t"
      "fstps -0x30(%%ebp)\n\t"
      "addl $8, %%esp\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fistps -0x2c(%%ebp)\n\t"
      "flds 0xc(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "movl -0x2c(%%ebp), %%edi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "movl %%edi, -0x28(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00122690_1\n\t"
      "movswl 0x22(%%esi), %%eax\n\t"
      "movl %%eax, 0x8(%%ebp)\n\t"
      "fildl 0x8(%%ebp)\n\t"
      "fcomps 0xc(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00122690_2\n\t"
      ".LFUN_00122690_1:\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "flds 0xc(%%ebp)\n\t"
      "pushl %%ecx\n\t"
      "subl $8, %%esp\n\t"
      "fstpl (%%esp)\n\t"
      "pushl $0x291388\n\t"
      "pushl $2\n\t"
      "call *%[c8f390]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00122690_2:\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw 0x22(%%esi), %%cx\n\t"
      "cmpw %%cx, %%di\n\t"
      "jl .LFUN_00122690_3\n\t"
      "leal -0x1(%%ecx), %%eax\n\t"
      "movswl %%ax, %%edx\n\t"
      "movl %%edx, 0xc(%%ebp)\n\t"
      "movl %%eax, -0x28(%%ebp)\n\t"
      "movl $0x3f800000, -0x4(%%ebp)\n\t"
      "fildl 0xc(%%ebp)\n\t"
      "movl %%eax, %%edi\n\t"
      "fstps 0xc(%%ebp)\n\t"
      ".LFUN_00122690_3:\n\t"
      "cmpw $1, 0x20(%%esi)\n\t"
      "jne .LFUN_00122690_23\n\t"
      "testb $1, 0x3a(%%esi)\n\t"
      "je .LFUN_00122690_5\n\t"
      "movb 0x322600, %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00122690_4\n\t"
      "movl 0x88(%%esi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00122690_5\n\t"
      ".LFUN_00122690_4:\n\t"
      "movb $1, 0xb(%%ebp)\n\t"
      "jmp .LFUN_00122690_6\n\t"
      ".LFUN_00122690_5:\n\t"
      "movb $0, 0xb(%%ebp)\n\t"
      ".LFUN_00122690_6:\n\t"
      "movswl %%cx, %%ecx\n\t"
      "movswl %%di, %%eax\n\t"
      "decl %%ecx\n\t"
      "cmpl %%ecx, %%eax\n\t"
      "movl %%eax, -0x34(%%ebp)\n\t"
      "jne .LFUN_00122690_7\n\t"
      "movl $0, -0x2c(%%ebp)\n\t"
      "jmp .LFUN_00122690_8\n\t"
      ".LFUN_00122690_7:\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x2c(%%ebp)\n\t"
      ".LFUN_00122690_8:\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "call *%[c120500]\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[c120500]\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpw %%cx, 0x2c(%%esi)\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "movl %%ecx, -0x14(%%ebp)\n\t"
      "movl %%ecx, -0x1c(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_00122690_20\n\t"
      "movl %%edi, %%edi\n\t"
      ".LFUN_00122690_9:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movswl %%cx, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "testb $0x1f, %%cl\n\t"
      "movl %%eax, -0x20(%%ebp)\n\t"
      "jne .LFUN_00122690_10\n\t"
      "movw %%cx, %%ax\n\t"
      "sarw $5, %%ax\n\t"
      "movswl %%ax, %%eax\n\t"
      "movl 0x5c(%%esi,%%eax,4), %%edx\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "movl 0x6c(%%esi,%%eax,4), %%edx\n\t"
      "movl 0x7c(%%esi,%%eax,4), %%eax\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      ".LFUN_00122690_10:\n\t"
      "testb $1, -0x10(%%ebp)\n\t"
      "je .LFUN_00122690_13\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00122690_11\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "fildl -0x34(%%ebp)\n\t"
      "leal -0x7c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "fstps (%%esp)\n\t"
      "pushl %%esi\n\t"
      "call *%[c121330]\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00122690_12\n\t"
      ".LFUN_00122690_11:\n\t"
      "movswl (%%edi), %%ecx\n\t"
      "movswl 0x2(%%edi), %%edx\n\t"
      "movswl 0x4(%%edi), %%eax\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movswl 0x6(%%edi), %%ecx\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movswl (%%ebx), %%edx\n\t"
      "fmuls 0x290dd8\n\t"
      "addl $8, %%edi\n\t"
      "fstps -0x6c(%%ebp)\n\t"
      "addl $8, %%ebx\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "movswl -0x6(%%ebx), %%eax\n\t"
      "fmuls 0x290dd8\n\t"
      "fstps -0x68(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movswl -0x4(%%ebx), %%ecx\n\t"
      "fmuls 0x290dd8\n\t"
      "fstps -0x64(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "movswl -0x2(%%ebx), %%edx\n\t"
      "fmuls 0x290dd8\n\t"
      "fstps -0x60(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%eax, -0x38(%%ebp)\n\t"
      "leal -0x7c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "fmuls 0x290dd8\n\t"
      "leal -0x6c(%%ebp), %%eax\n\t"
      "fstps -0x5c(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%ecx, -0x38(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "fmuls 0x290dd8\n\t"
      "fstps -0x58(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "movl %%edx, -0x38(%%ebp)\n\t"
      "leal -0x5c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "fmuls 0x290dd8\n\t"
      "pushl %%eax\n\t"
      "fstps -0x54(%%ebp)\n\t"
      "fildl -0x38(%%ebp)\n\t"
      "fmuls 0x290dd8\n\t"
      "fstps -0x50(%%ebp)\n\t"
      "call *%[c10cb60]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00122690_12:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x7c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c10b9c0]\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00122690_13:\n\t"
      "movl -0x10(%%ebp), %%edx\n\t"
      "movb -0x18(%%ebp), %%al\n\t"
      "shrl $1, %%edx\n\t"
      "testb $1, %%al\n\t"
      "movl %%edx, -0x10(%%ebp)\n\t"
      "je .LFUN_00122690_16\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "leal -0x4c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "je .LFUN_00122690_14\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl 0xc(%%ebp), %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c121640]\n\t"
      "movl -0x14(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "jmp .LFUN_00122690_15\n\t"
      ".LFUN_00122690_14:\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movl %%ebx, %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl %%edi, %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "addl $0xc, %%edi\n\t"
      "addl $0xc, %%ebx\n\t"
      "call *%[c10b7d0]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00122690_15:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "flds -0x4c(%%ebp)\n\t"
      "fadds 0x10(%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fstps 0x10(%%eax)\n\t"
      "flds -0x48(%%ebp)\n\t"
      "fadds 0x14(%%eax)\n\t"
      "fstps 0x14(%%eax)\n\t"
      "flds -0x44(%%ebp)\n\t"
      "fadds 0x18(%%eax)\n\t"
      "fstps 0x18(%%eax)\n\t"
      ".LFUN_00122690_16:\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movb -0x24(%%ebp), %%al\n\t"
      "shrl $1, %%edx\n\t"
      "testb $1, %%al\n\t"
      "movl %%edx, -0x18(%%ebp)\n\t"
      "je .LFUN_00122690_19\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00122690_17\n\t"
      "movl 0xc(%%ebp), %%edx\n\t"
      "leal -0x30(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "movl -0x1c(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c121940]\n\t"
      "movl -0x1c(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "incl %%eax\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "jmp .LFUN_00122690_18\n\t"
      ".LFUN_00122690_17:\n\t"
      "movl (%%edi), %%eax\n\t"
      "movl (%%ebx), %%ecx\n\t"
      "movl %%eax, -0x40(%%ebp)\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "leal -0x30(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "movl -0x40(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "addl $4, %%edi\n\t"
      "movl %%ecx, -0x3c(%%ebp)\n\t"
      "addl $4, %%ebx\n\t"
      "call *%[c10b820]\n\t"
      "addl $0x10, %%esp\n\t"
      ".LFUN_00122690_18:\n\t"
      "movl -0x20(%%ebp), %%eax\n\t"
      "flds -0x30(%%ebp)\n\t"
      "fmuls 0x1c(%%eax)\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "fstps 0x1c(%%eax)\n\t"
      ".LFUN_00122690_19:\n\t"
      "movl -0x24(%%ebp), %%eax\n\t"
      "shrl $1, %%eax\n\t"
      "incl %%ecx\n\t"
      "cmpw 0x2c(%%esi), %%cx\n\t"
      "movl %%eax, -0x24(%%ebp)\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jl .LFUN_00122690_9\n\t"
      ".LFUN_00122690_20:\n\t"
      "movb 0xb(%%ebp), %%al\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_00122690_22\n\t"
      "movl -0x28(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[c120500]\n\t"
      "movswl 0x24(%%esi), %%ecx\n\t"
      "subl %%eax, %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%ecx, %%edi\n\t"
      "je .LFUN_00122690_21\n\t"
      "pushl $1\n\t"
      "pushl $0x2b5\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x2912a0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00122690_21:\n\t"
      "movl -0x2c(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c120500]\n\t"
      "subl %%eax, %%ebx\n\t"
      "movswl 0x24(%%esi), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl %%eax, %%ebx\n\t"
      "je .LFUN_00122690_22\n\t"
      "pushl $1\n\t"
      "pushl $0x2b6\n\t"
      "pushl $0x290ce4\n\t"
      "pushl $0x291310\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00122690_22:\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00122690_23:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [c1daf7e] "m"(b122690_c1daf7e), [c1d9c2b] "m"(b122690_c1d9c2b), [c8f390] "m"(b122690_c8f390), [c120500] "m"(b122690_c120500), [c121330] "m"(b122690_c121330), [c10cb60] "m"(b122690_c10cb60), [c10b9c0] "m"(b122690_c10b9c0), [c121640] "m"(b122690_c121640), [c10b7d0] "m"(b122690_c10b7d0), [c121940] "m"(b122690_c121940), [c10b820] "m"(b122690_c10b820), [assert] "m"(b122690_assert), [exitfn] "m"(b122690_exitfn)
      : "memory");
}
#else
#error "FUN_00122690: clang naked draft required"
#endif


/* FUN_00123990 (0x123990) — readable C lift (restored pre-naked). */
void FUN_00123990(void)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x00290e18, (char *)0x00291564, 579, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)esi -> jl 0x123a0a */
  display_assert((char *)0x00290e00, (char *)0x00291564, 580, 0);
  system_exit(0);
  /* test eax, eax -> jle 0x123a94 */
  quaternions_interpolate_and_normalize((float *)0, (float *)0, 0.0f, (float *)0);
  /* cmp eax, edx -> jl 0x123a20 */

  (void)eax;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00123b30 (0x123b30) — XBE naked draft (batch 268). */
#if defined(__clang__)
static void *(*const b123b30_elem)(void *, int, int) = tag_block_get_element;
static void (*const b123b30_c1094d0)(float *out_matrix, float *position, float *basis_data) = component_vectors_from_normal3d;
static void (*const b123b30_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void (*const b123b30_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;
static void (*const b123b30_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b123b30_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00123b30(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc0, %%esp\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ebx\n\t"
      "xorl %%eax, %%eax\n\t"
      "pushl %%esi\n\t"
      "addl $0xb8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "movw %%ax, -0xc0(%%ebp)\n\t"
      "movl $1, -0x4(%%ebp)\n\t"
      "movl %%ecx, -0xc(%%ebp)\n\t"
      "jmp .LFUN_00123b30_2\n\t"
      ".LFUN_00123b30_1:\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "leal (%%ecx), %%ecx\n\t"
      ".LFUN_00123b30_2:\n\t"
      "movswl %%ax, %%edx\n\t"
      "movw -0xc0(%%ebp,%%edx,2), %%di\n\t"
      "incl %%eax\n\t"
      "movswl %%di, %%esi\n\t"
      "pushl $0x9c\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movl -0xc(%%ebp), %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%ebx\n\t"
      "leal 0x34(%%ebx), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "leal 0x28(%%ebx), %%edx\n\t"
      "pushl %%edx\n\t"
      "leal -0x40(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1094d0]\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "jne .LFUN_00123b30_6\n\t"
      "movl 0x18(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "movl %%eax, %%edx\n\t"
      "jne .LFUN_00123b30_3\n\t"
      "movl 0x31fc44, %%edx\n\t"
      ".LFUN_00123b30_3:\n\t"
      "movl 0x14(%%ebp), %%ecx\n\t"
      "testl %%ecx, %%ecx\n\t"
      "jne .LFUN_00123b30_4\n\t"
      "movl 0x31fc3c, %%ecx\n\t"
      ".LFUN_00123b30_4:\n\t"
      "movl 0x10(%%ebp), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_00123b30_5\n\t"
      "movl 0x31fc1c, %%eax\n\t"
      ".LFUN_00123b30_5:\n\t"
      "movl 0xc(%%ebp), %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[m4x3]\n\t"
      "pushl %%esi\n\t"
      "leal -0x40(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%esi\n\t"
      "call *%[c109850]\n\t"
      "addl $0x1c, %%esp\n\t"
      "jmp .LFUN_00123b30_8\n\t"
      ".LFUN_00123b30_6:\n\t"
      "cmpw $-1, 0x24(%%ebx)\n\t"
      "jne .LFUN_00123b30_7\n\t"
      "pushl $1\n\t"
      "pushl $0x28a\n\t"
      "pushl $0x291564\n\t"
      "pushl $0x291584\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00123b30_7:\n\t"
      "movswl 0x24(%%ebx), %%ecx\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "imull $0x34, %%ecx, %%ecx\n\t"
      "addl %%eax, %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x40(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "addl %%eax, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109850]\n\t"
      "addl $0xc, %%esp\n\t"
      ".LFUN_00123b30_8:\n\t"
      "movw 0x20(%%ebx), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "je .LFUN_00123b30_9\n\t"
      "movswl %%cx, %%edx\n\t"
      "incl %%ecx\n\t"
      "movw %%ax, -0xc0(%%ebp,%%edx,2)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_00123b30_9:\n\t"
      "movw 0x22(%%ebx), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_00123b30_10\n\t"
      "movswl %%cx, %%eax\n\t"
      "incl %%ecx\n\t"
      "movw %%bx, -0xc0(%%ebp,%%eax,2)\n\t"
      "movl %%ecx, -0x4(%%ebp)\n\t"
      ".LFUN_00123b30_10:\n\t"
      "cmpw %%cx, -0x8(%%ebp)\n\t"
      "jne .LFUN_00123b30_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [elem] "m"(b123b30_elem), [c1094d0] "m"(b123b30_c1094d0), [m4x3] "m"(b123b30_m4x3), [c109850] "m"(b123b30_c109850), [assert] "m"(b123b30_assert), [exitfn] "m"(b123b30_exitfn)
      : "memory");
}
#else
#error "FUN_00123b30: clang naked draft required"
#endif


/* FUN_00123c70 (0x123c70) — XBE naked draft (batch 266). */
#if defined(__clang__)
static void (*const b123c70_m4x3)(void *, float *, float *, float *) = matrix4x3_from_forward_up_position;
static void *(*const b123c70_elem)(void *, int, int) = tag_block_get_element;
static void (*const b123c70_c109500)(float *out, float *qsp) = FUN_00109500;
static void (*const b123c70_c109850)(float *a, float *b, float *out) = matrix4x3_multiply;

__attribute__((naked, noinline))
void FUN_00123c70(void *mode_tag __attribute__((unused)), void *out_matrices __attribute__((unused)), void *node_data __attribute__((unused)), float *position __attribute__((unused)), float *forward __attribute__((unused)), float *up __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xf0, %%esp\n\t"
      "movl 0x1c(%%ebp), %%eax\n\t"
      "movl 0x18(%%ebp), %%ecx\n\t"
      "movl 0x14(%%ebp), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "leal -0x3c(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[m4x3]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0xb8(%%ecx), %%edx\n\t"
      "addl $0xb8, %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl %%eax, %%edx\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jle .LFUN_00123c70_7\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl $1, 0x8(%%ebp)\n\t"
      "movw %%ax, -0xf0(%%ebp)\n\t"
      "jmp .LFUN_00123c70_2\n\t"
      ".LFUN_00123c70_1:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "jmp .LFUN_00123c70_2\n\t"
      "leal (%%esp), %%esp\n\t"
      "nop\n\t"
      ".LFUN_00123c70_2:\n\t"
      "movswl %%ax, %%edx\n\t"
      "movw -0xf0(%%ebp,%%edx,2), %%di\n\t"
      "movswl %%di, %%esi\n\t"
      "pushl $0x9c\n\t"
      "incl %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[elem]\n\t"
      "addl $0xc, %%esp\n\t"
      "testw %%di, %%di\n\t"
      "movl %%eax, %%ebx\n\t"
      "jne .LFUN_00123c70_3\n\t"
      "leal -0x3c(%%ebp), %%edi\n\t"
      "jmp .LFUN_00123c70_4\n\t"
      ".LFUN_00123c70_3:\n\t"
      "movswl 0x24(%%ebx), %%edi\n\t"
      "movl 0xc(%%ebp), %%eax\n\t"
      "imull $0x34, %%edi, %%edi\n\t"
      "addl %%eax, %%edi\n\t"
      ".LFUN_00123c70_4:\n\t"
      "movl 0x10(%%ebp), %%edx\n\t"
      "movl %%esi, %%eax\n\t"
      "shll $5, %%eax\n\t"
      "addl %%edx, %%eax\n\t"
      "pushl %%eax\n\t"
      "leal -0x70(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[c109500]\n\t"
      "imull $0x34, %%esi, %%esi\n\t"
      "addl 0xc(%%ebp), %%esi\n\t"
      "pushl %%esi\n\t"
      "leal -0x70(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%edi\n\t"
      "call *%[c109850]\n\t"
      "movw 0x20(%%ebx), %%ax\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_00123c70_5\n\t"
      "movswl %%cx, %%edx\n\t"
      "incl %%ecx\n\t"
      "movw %%ax, -0xf0(%%ebp,%%edx,2)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_00123c70_5:\n\t"
      "movw 0x22(%%ebx), %%bx\n\t"
      "cmpw $-1, %%bx\n\t"
      "je .LFUN_00123c70_6\n\t"
      "movswl %%cx, %%eax\n\t"
      "incl %%ecx\n\t"
      "movw %%bx, -0xf0(%%ebp,%%eax,2)\n\t"
      "movl %%ecx, 0x8(%%ebp)\n\t"
      ".LFUN_00123c70_6:\n\t"
      "cmpw %%cx, -0x4(%%ebp)\n\t"
      "jne .LFUN_00123c70_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00123c70_7:\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [m4x3] "m"(b123c70_m4x3), [elem] "m"(b123c70_elem), [c109500] "m"(b123c70_c109500), [c109850] "m"(b123c70_c109850)
      : "memory");
}
#else
#error "FUN_00123c70: clang naked draft required"
#endif


/* FUN_00123d80 (0x123d80) — readable C lift from XBE leaf. */
int16_t FUN_00123d80(int tag_index, char *name)
{
  char *tag;
  short *block;
  short lo;
  short hi;
  short mid;
  char *elem;
  int cmp;

  if (tag_index == -1 || !name || name[0] == 0)
    return (int16_t)-1;
  tag = (char *)tag_get(0x6d6f6465, tag_index);
  block = (short *)(tag + 0xac);
  hi = (short)(block[0] - 1);
  lo = 0;
  if (hi < 0)
    return (int16_t)-1;
  while (lo <= hi) {
    mid = (short)((lo + hi) / 2);
    elem = (char *)tag_block_get_element(block, (int)mid, 0x40);
    cmp = crt_stricmp(elem, name);
    if (cmp == 0)
      return mid;
    if (cmp < 0)
      hi = (short)(mid - 1);
    else
      lo = (short)(mid + 1);
  }
  return (int16_t)-1;
}



/* animation_get_root_matrix (0x123e20) — readable C lift. */
void *animation_get_root_matrix(void *a0, short a1)
{
  return (char *)tag_block_get_element((char *)a0 + 0xb8, a1, 0x9c) + 0x68;
}

/* FUN_00123e50 (0x123e50) — readable C lift from XBE leaf. */
int16_t FUN_00123e50(int tag_index, char *name)
{
  char *tag;
  void *block;
  int count;
  int i;
  char *elem;

  if (tag_index == -1)
    return (int16_t)-1;
  tag = (char *)tag_get(0x6d6f6465, tag_index);
  block = tag + 0xb8;
  count = *(int *)block;
  if (count <= 0)
    return (int16_t)-1;
  for (i = 0; i < count; i++) {
    elem = (char *)tag_block_get_element(block, i, 0x9c);
    if (csstrcmp(elem, name) == 0)
      return (int16_t)i;
  }
  return (int16_t)-1;
}



/* FUN_00123ed0 (0x123ed0) — readable C lift. */
void FUN_00123ed0(int model_ref, float distance, void *node_matrices, void *arg4, void *node_transforms, void *node_matrices2, int lighting, void *position, int arg9, void *effect_record, int object_handle, int arg12, int render_flag)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_get(0x6d6f6465, 0);
  /* test (char)eax, (char)eax -> je 0x123f0f */
  profile_enter_private((void *)0x00322608);
  /* test eax, eax -> jne 0x123f33 */
  display_assert((char *)0x00291690, (char *)0x00291564, 82, 0);
  system_exit(0);
  /* relift: cmp dword ptr [esi + 4], 0x769c097 -> jne 0x123f4e */
  global_scenario_get();
  /* test (char)eax, 1 -> je 0x123f6c */
  /* relift: test byte ptr [ebp + 0x38], 2 -> je 0x1246fa */
  /* test eax, eax -> jne 0x123f7a */
  /* test eax, eax -> jne 0x123f88 */
  /* test eax, eax -> jne 0x123f96 */
  /* test eax, eax -> jne 0x123fa4 */
  /* test eax, eax -> jle 0x12403e */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 156);
  matrix4x3_multiply((float *)(uintptr_t)ecx, (float *)0, (float *)0);
  /* cmp esi, eax -> jl 0x123fd1 */
  /* test edx, edx -> jle 0x12403e */
  /* test (int16_t)ecx, (int16_t)ecx -> jg 0x124050 */
  /* test (int16_t)eax, (int16_t)eax -> jge 0x124083 */
  /* cmp (int16_t)eax, 4 -> jle 0x124092 */
  /* test (int16_t)ecx, (int16_t)ecx -> jl 0x1240a2 */
  /* cmp (int16_t)ecx, 5 -> jl 0x1240c2 */
  display_assert((char *)0x00291630, (char *)0x00291564, 169, 0);
  system_exit(0);
  /* test (char)eax, (char)eax -> je 0x124162 */
  tag_block_get_element((void *)(uintptr_t)edi, 0, 156);
  /* cmp (int16_t)eax, 0xffff -> je 0x12413f */
  FUN_00189270(0, (float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (void *)0);
  FUN_001894d0(0, (float *)(uintptr_t)esi, 0.0f);
  /* relift: cmp esi, dword ptr [edi] -> jl 0x124100 */
  /* test (char)eax, (char)eax -> je 0x124266 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_block_get_element((void *)(uintptr_t)edi, 0, 32);
  /* cmp edx, eax -> jne 0x124231 */
  component_vectors_from_normal3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  matrix4x3_multiply((float *)(uintptr_t)eax, (float *)0, (float *)0);
  FUN_001894d0(0, (float *)(uintptr_t)ecx, 0.0f);
  FUN_00189cb0(0, (void *)(uintptr_t)eax, (void *)(uintptr_t)ebx, 0);
  /* cmp eax, ecx -> jl 0x1241c0 */
  /* cmp eax, edx -> jl 0x124190 */
  /* test (char)eax, (char)eax -> jne 0x12427c */
  /* test (char)eax, (char)eax -> je 0x1245e5 */
  tag_block_get_element((void *)(uintptr_t)edx, 0, 76);
  /* cmp (char)ecx, 0xff -> je 0x124408 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}


