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
static double anim_floor(double x)
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


/* overlay_animation_apply_continuous_scaled (0x121940) — Interpolate keyframed
 * scale data for a single node in a compressed animation.
 *
 * Scalar (single-float) sibling of animation_get_node_orientations. Resolves
 * the two bracketing keyframes for a given fractional frame and either copies
 * the exact keyframe scale or interpolates between two scales using
 * scalars_interpolate (scalar lerp).
 *
 * The animation's tag_data (at animation+0xa0) contains:
 *   +0x1c: offset to a per-component packed descriptor array (4 bytes each,
 *          low 12 bits = keyframe_count, high 4 bits = data_offset_index).
 *   +0x20: offset to keyframe_frame_indices (unsigned short array).
 *   +0x24: offset to default_scales (float array, 4 bytes per node).
 *   +0x28: offset to keyframe_data (float array, 4 bytes per keyframe).
 *
 * Branch structure mirrors animation_get_node_orientations:
 *   1. Before first keyframe: lerp default_scale[scale_count] -> keyframe[0]
 *      with kf0_frame=0, kf1_frame=first_keyframe_frame.
 *   2. At last keyframe: lerp keyframe[last] -> default_scale[scale_count]
 *      with kf0_frame=last_frame, kf1_frame=last_frame+1.
 *   3. Between keyframes: binary search via FUN_00120d10, then lerp the two
 *      bracketing keyframe entries.
 * If frame == kf0_frame exactly, copy this_kf_scale directly (no blend).
 *
 * Note: scale_count is a 16-bit selector indexing the descriptor array; it
 * is also used as the index into default_scales (default_scales[scale_count]).
 * After masking the descriptor, the local param_3 slot holds keyframe_count.
 *
 * Confirmed: cdecl, 5 args, void return (stack cleanup ADD ESP,0x10 at
 * 0x121c1c). Confirmed: CALL tag_data_get_pointer(animation+0xa0,
 * *(int*)(animation+0x88), 0) at 0x12195b. Confirmed: CALL anim_floor (CRT
 * 0x1d9c2b) at 0x121a4f via push double + FSTP [ESP]. Confirmed: CALL
 * FUN_00120d10(keyframe_frame_indices=EBX, target_frame=ECX,
 *            keyframe_count@<edi>=[EBP+0x10]) at 0x121b1d.
 * Confirmed: CALL scalars_interpolate(this_kf, next_kf, blend, out) at
 * 0x121c17. Confirmed: Assert lines 0x64a, 0x64c, 0x662, 0x663, 0x677, 0x688,
 * 0x689 (the 0x64e "keyframe_count>=0" assert is dead after the &0xfff mask and
 * was eliminated by the optimizer). Confirmed: Element size 4 bytes (float) —
 * LEA EDX+EAX*0x4 at 0x121a39. Confirmed: Frame indices array stride 2 bytes —
 * LEA ECX+EAX*0x2 at 0x121a44.
 */
void overlay_animation_apply_continuous_scaled(void *animation, float frame,
                                               unsigned short scale_count,
                                               short node_index,
                                               void *out_scale)
{
  char *anim;
  char *tag_data_base;
  unsigned int descriptor;
  unsigned short keyframe_count;
  int data_offset_index;
  char *default_scales;
  char *keyframe_data;
  unsigned short *keyframe_frame_indices;
  int frame_count_i;
  float frame_floor_f;
  short frame_index;
  int kf_count_i;
  unsigned short kf0_frame;
  unsigned short kf1_frame;
  float this_kf_scale;
  float next_kf_scale;
  short kf_idx;
  float this_frame_f;
  float blend;
  (void)node_index;

  anim = (char *)animation;

  /* Resolve tag_data pointer */
  tag_data_base =
    (char *)tag_data_get_pointer(anim + 0xa0, *(int *)(anim + 0x88), 0);

  /* Read packed descriptor for this scale component */
  descriptor =
    *(unsigned int *)(tag_data_base + *(int *)(tag_data_base + 0x1c) +
                      (short)scale_count * 4);
  keyframe_count = (unsigned short)(descriptor & 0xfff);
  data_offset_index = (int)(short)(descriptor >> 0xc);

  /* Default scales and keyframe arrays are relative to tag_data_base */
  default_scales = tag_data_base + *(int *)(tag_data_base + 0x24);
  keyframe_data =
    tag_data_base + *(int *)(tag_data_base + 0x28) + data_offset_index * 4;
  keyframe_frame_indices =
    (unsigned short *)(tag_data_base + *(int *)(tag_data_base + 0x20) +
                       data_offset_index * 2);

  /* Assert: real_frame_index >= 0.0f */
  if (frame < 0.0f) {
    display_assert("real_frame_index>=0.0f",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x64a, 1);
    system_exit(-1);
  }

  /* Assert: real_frame_index < (real)animation->frame_count */
  frame_count_i = (int)*(short *)(anim + 0x22);
  if (frame >= (float)frame_count_i) {
    display_assert("real_frame_index<(real)animation->frame_count",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x64c, 1);
    system_exit(-1);
  }

  /* If keyframe_count == 0, return the default scale for this slot */
  if (keyframe_count == 0) {
    *(int *)out_scale = *(int *)(default_scales + (int)(short)scale_count * 4);
    return;
  }

  /* Compute integer frame index from floor(frame) */
  frame_floor_f = (float)anim_floor((double)frame);
  frame_index = (short)(int)frame_floor_f;

  /* Assert: frame_index >= 0 && frame_index <=
   * keyframe_frame_indices[keyframe_count-1] */
  kf_count_i = (int)(short)keyframe_count;
  if (frame_index < 0 ||
      (int)frame_index >
        (int)(unsigned int)keyframe_frame_indices[kf_count_i - 1]) {
    display_assert(
      "frame_index>=0 && frame_index<=keyframe_frame_indices[keyframe_count-1]",
      "c:\\halo\\SOURCE\\models\\model_animations.c", 0x662, 1);
    system_exit(-1);
  }

  /* Assert: keyframe_frame_indices[keyframe_count-1] == animation->frame_count
   * - 1 */
  if ((unsigned int)keyframe_frame_indices[kf_count_i - 1] !=
      (unsigned int)((int)*(short *)(anim + 0x22) - 1)) {
    display_assert(
      "keyframe_frame_indices[keyframe_count-1]==animation->frame_count-1",
      "c:\\halo\\SOURCE\\models\\model_animations.c", 0x663, 1);
    system_exit(-1);
  }

  /* Determine which two keyframes bracket the current frame */
  kf0_frame = keyframe_frame_indices[0];

  if ((int)frame_index < (int)(unsigned int)kf0_frame) {
    /* Before the first keyframe: interpolate default_scale -> first keyframe */
    this_kf_scale = *(float *)(default_scales + (int)(short)scale_count * 4);
    next_kf_scale = *(float *)keyframe_data;
    kf1_frame = kf0_frame;
    kf0_frame = 0;
  } else {
    kf1_frame = keyframe_frame_indices[kf_count_i - 1];

    if ((int)frame_index == (int)(unsigned int)kf1_frame) {
      /* At the last keyframe: interpolate last keyframe -> default_scale */
      this_kf_scale = *(float *)(keyframe_data + (kf_count_i - 1) * 4);
      next_kf_scale = *(float *)(default_scales + (int)(short)scale_count * 4);
      kf0_frame = kf1_frame;
      kf1_frame = kf1_frame + 1;
    } else {
      /* Between two keyframes: binary search */
      kf_idx = FUN_00120d10(keyframe_frame_indices, (short)(int)frame_floor_f,
                            keyframe_count);

      if (kf_idx < 0 || (int)kf_idx >= kf_count_i - 1) {
        display_assert("keyframe_index>=0 && keyframe_index<keyframe_count-1",
                       "c:\\halo\\SOURCE\\models\\model_animations.c", 0x677,
                       1);
        system_exit(-1);
      }

      kf0_frame = keyframe_frame_indices[(int)kf_idx];
      kf1_frame = keyframe_frame_indices[(int)kf_idx + 1];
      this_kf_scale = *(float *)(keyframe_data + (int)kf_idx * 4);
      next_kf_scale = *(float *)(keyframe_data + ((int)kf_idx + 1) * 4);
    }
  }

  /* If frame == this_keyframe_frame exactly, copy directly */
  this_frame_f = (float)(int)(short)kf0_frame;
  if (frame == this_frame_f) {
    *(float *)out_scale = this_kf_scale;
    return;
  }

  /* Compute blend factor and interpolate */
  blend = (frame - this_frame_f) /
          (float)((int)(short)kf1_frame - (int)(short)kf0_frame);

  /* Assert: real_frame_index >= (real)this_keyframe_frame_index */
  if (frame < this_frame_f) {
    display_assert("real_frame_index>=(real)this_keyframe_frame_index",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x688, 1);
    system_exit(-1);
  }

  /* Assert: real_frame_index < (real)next_keyframe_frame_index */
  if (frame >= (float)(int)(short)kf1_frame) {
    display_assert("real_frame_index< (real)next_keyframe_frame_index",
                   "c:\\halo\\SOURCE\\models\\model_animations.c", 0x689, 1);
    system_exit(-1);
  }

  scalars_interpolate(this_kf_scale, next_kf_scale, blend, (float *)out_scale);
}

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

/* 0x120250 */
void FUN_00120250(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0011fd50();
  /* test (char)eax, (char)eax -> jne 0x12028a */
  /* relift: cmp byte ptr [esi], 0 -> jne 0x12028a */
  display_assert((char *)0x002906c4, (char *)0x002905b0, 96, 0);
  system_exit(0);
  /* cmp (int16_t)edi, (int16_t)ecx -> jg 0x120337 */
  /* cmp (int16_t)edx, (int16_t)eax -> jg 0x120337 */
  /* cmp edx, eax -> jge 0x120337 */
  data_new_at_index((void *)(uintptr_t)eax);
  /* cmp ebx, -1 -> je 0x120337 */
  FUN_0011fef0();
  FUN_0011ff70();
  /* test (char)eax, (char)eax -> jne 0x120337 */
  datum_delete((void *)(uintptr_t)edx, 0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x120340 */
void FUN_00120340(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0011fd50();
  /* relift: cmp byte ptr [esi], 0 -> jne 0x120373 */
  display_assert((char *)0x00290710, (char *)0x002905b0, 138, 0);
  system_exit(0);
  /* relift: cmp word ptr [eax + 0x2e], (int16_t)ebx -> jle 0x1203be */
  /* relift: cmp word ptr [edi], 0 -> je 0x1203b1 */
  /* test (char)eax, (char)eax -> jne 0x1203b1 */
  datum_delete((void *)(uintptr_t)eax, 0);
  /* relift: cmp (int16_t)ebx, word ptr [ecx + 0x2e] -> jl 0x120381 */
  FUN_0011ff70();
  display_assert((char *)0x002906fc, (char *)0x002905b0, 157, 0);
  system_exit(0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}

/* 0x120400 */
void FUN_00120400(void)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  FUN_0011fd50();
  /* relift: cmp byte ptr [esi], 0 -> jne 0x120431 */
  display_assert((char *)0x00290710, (char *)0x002905b0, 170, 0);
  system_exit(0);
  FUN_0011ff70();
  /* test (char)eax, (char)eax -> je 0x12046b */
  /* relift: cmp word ptr [edi + 0x2e], (int16_t)edx -> jle 0x120467 */
  /* relift: cmp word ptr [ecx], 0 -> je 0x12045a */
  /* relift: cmp (int16_t)edx, word ptr [edi + 0x2e] -> jl 0x120450 */

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x120470 */
void FUN_00120470(void)
{
  FUN_0011fd50();
  datum_delete((void *)0, 0);
  FUN_0011ff70();
}

/* 0x1204a0 */
void FUN_001204a0(void)
{
  int eax = 0;

  FUN_0011fd50();
  FUN_0011ff70();
  /* test (char)eax, (char)eax -> je 0x1204da */
  FUN_0011ff70();

  (void)eax;
}

/* 0x120620 */
char FUN_00120620(int animation)
{
  int eax = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x120641 */
  display_assert((char *)0x00290cd8, (char *)0x00290ce4, 38, 0);
  system_exit(0);
  /* relift: test byte ptr [esi + 0x3a], 1 -> je 0x120660 */
  /* test (char)eax, (char)eax -> jne 0x12065a */
  /* test eax, eax -> jne 0x120660 */
  return 0;

  (void)eax;
  (void)esi;
}

/* 0x120670 */
void build_damage_animation_index(void)
{
  int ebx = 0;
  int esi = 0;
  int edi = 0;

  /* test (int16_t)edi, (int16_t)edi -> jl 0x120684 */
  /* cmp (int16_t)edi, 4 -> jl 0x1206a1 */
  display_assert((char *)0x00290d98, (char *)0x00290ce4, 55, 0);
  system_exit(0);
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x1206af */
  /* cmp (int16_t)ebx, 4 -> jl 0x1206cc */
  display_assert((char *)0x00290d48, (char *)0x00290ce4, 56, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jl 0x1206da */
  /* cmp (int16_t)esi, 0xb -> jl 0x1206f7 */
  display_assert((char *)0x00290d10, (char *)0x00290ce4, 57, 0);
  system_exit(0);

  (void)ebx;
  (void)esi;
  (void)edi;
}

/* 0x120710 */
void FUN_00120710(int anim_entry, int tick_out, int damage_time_out)
{
  /* relift: no calls detected — manual review */
}

/* 0x120790 */
void animation_set_frame_size(void)
{
  int eax = 0;
  int ecx = 0;
  int esi = 0;

  /* test esi, esi -> jne 0x1207bb */
  display_assert((char *)0x00290cd8, (char *)0x00290ce4, 123, 0);
  system_exit(0);
  /* relift: cmp word ptr [esi + 0x2c], 0 -> jle 0x120801 */
  /* relift: test dword ptr [esi + ecx*4 + 0x6c], eax -> je 0x1207ea */
  /* relift: test dword ptr [esi + ecx*4 + 0x5c], eax -> je 0x1207f3 */
  /* relift: test dword ptr [esi + ecx*4 + 0x7c], eax -> je 0x1207fc */

  (void)eax;
  (void)ecx;
  (void)esi;
}

/* 0x120930 */
void quaternion_decompress_6byte_renormalized(void)
{
  quaternion_decompress_6byte((void *)0, (void *)0);
  sphere_intersects_rectangle3d((void *)0);
}

/* 0x120950 */
void quaternion_compress_8byte(void)
{
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
}

/* 0x1209b0 */
void quaternion_compress_6byte(void)
{
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
  FUN_001d9068();
}

/* 0x120a40 */
void animation_graph_node_matrices_from_orientations(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_get(0x616e7472, 0);
  matrix4x3_from_forward_up_position((void *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_00109500((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix4x3_multiply((float *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi);
  /* relift: cmp word ptr [ebx + 0x20], (int16_t)edi -> je 0x120b42 */
  /* cmp (int16_t)esi, 0x40 -> jl 0x120b2f */
  display_assert((char *)0x00290ddc, (char *)0x00290ce4, 1250, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebx + 0x22], (int16_t)edi -> je 0x120b80 */
  /* cmp (int16_t)esi, 0x40 -> jl 0x120b6d */
  display_assert((char *)0x00290ddc, (char *)0x00290ce4, 1256, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp - 8], (int16_t)esi -> jne 0x120a97 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x120ba0 */
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

/* 0x120cb0 */
short FUN_00120cb0(int animation_graph_tag_index, const char *name)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  tag_get(0x616e7472, 0);
  /* test eax, eax -> jle 0x120cfb */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 180);
  crt_stricmp((char *)(uintptr_t)ebx, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0x120d04 */
  /* cmp eax, ecx -> jl 0x120cd7 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x120ee0 */
void animation_frame_get_xy_translation(void)
{
  int eax = 0;

  /* relift: cmp word ptr [eax + 0x26], 1 -> jne 0x120f0b */
  FUN_00120590((void *)(uintptr_t)eax, 0, 0);

  (void)eax;
}

/* 0x120fd0 */
void inverse_kinematics_adjust_matrices(float *composed_matrix, int node_matrix_b, int node_matrix_c, int node_matrix_d)
{
  normalize3d((void *)0);
  normalize3d((void *)0);
  normalize3d((void *)0);
  normalize3d((void *)0);
  normalize3d((void *)0);
}

/* 0x121330 */
void FUN_00121330(void *animation, float frame, unsigned short rotation_count, short node_index, void *out_rotation)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_data_get_pointer((void *)(uintptr_t)eax, 0, 0);
  /* test (char)eax, 1 -> je 0x12139f */
  display_assert((char *)0x002911a4, (char *)0x00290ce4, 1428, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x1213d6 */
  display_assert((char *)0x00291174, (char *)0x00290ce4, 1430, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 0 -> jge 0x121402 */
  display_assert((char *)0x00291160, (char *)0x00290ce4, 1432, 0);
  system_exit(0);
  /* relift: cmp word ptr [ebp + 0x10], 0 -> jne 0x121428 */
  quaternion_decompress_6byte((void *)(uintptr_t)eax, (float *)(uintptr_t)esi);
  sphere_intersects_rectangle3d((float *)(uintptr_t)esi);
  floor(0.0f);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x121472 */
  /* cmp edx, ecx -> jle 0x121492 */
  display_assert((char *)0x00291118, (char *)0x00290ce4, 1451, 0);
  system_exit(0);
  /* cmp edx, ecx -> je 0x1214c7 */
  display_assert((char *)0x002910d0, (char *)0x00290ce4, 1452, 0);
  system_exit(0);
  /* cmp eax, ecx -> jge 0x1214e8 */
  /* cmp eax, edx -> jne 0x12150f */
  FUN_00120d10((void *)(uintptr_t)ebx, 0, 0);
  /* test (int16_t)edi, (int16_t)edi -> jl 0x12152e */
  /* cmp edx, esi -> jl 0x12154e */
  display_assert((char *)0x00290ea4, (char *)0x00290ce4, 1472, 0);
  system_exit(0);
  quaternion_decompress_6byte((void *)(uintptr_t)esi, (float *)(uintptr_t)edi);
  sphere_intersects_rectangle3d((float *)(uintptr_t)edi);
  /* test (char)eax, 1 -> je 0x1215db */
  display_assert((char *)0x00291098, (char *)0x00290ce4, 1491, 0);
  system_exit(0);
  /* test (char)eax, 0x41 -> je 0x121608 */
  display_assert((char *)0x00291064, (char *)0x00290ce4, 1492, 0);
  system_exit(0);
  quaternion_decompress_6byte((void *)(uintptr_t)esi, (float *)(uintptr_t)eax);
  quaternion_decompress_6byte((void *)(uintptr_t)edi, (float *)(uintptr_t)ecx);
  quaternions_interpolate_and_normalize((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x121c30 */
int animation_update_internal(int update_kind, int animation_graph_tag_index, short *state, int *out_sound)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  tag_get(0x616e7472, 0);
  display_assert((char *)0x00282dc4, (char *)0x00290ce4, 147, 0);
  system_exit(0);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 180);
  /* cmp (int16_t)eax, 0xffff -> je 0x121cbe */
  /* relift: cmp (int16_t)edx, word ptr [esi + 2] -> jne 0x121cbe */
  tag_block_get_element((void *)(uintptr_t)ebx, 0, 0);
  /* cmp (int16_t)ecx, (int16_t)eax -> jl 0x121d23 */
  /* test (int16_t)ecx, (int16_t)ecx -> jle 0x121cf9 */
  /* cmp ecx, eax -> jg 0x121ceb */
  model_animation_choose_random(0, 0, eax);
  /* cmp edx, eax -> jne 0x121d3f */
  /* relift: cmp word ptr [edi + 0x2e], 0 -> jne 0x121d3f */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0x34] -> je 0x121d4b */
  /* relift: cmp (int16_t)ecx, word ptr [edi + 0x36] -> jne 0x121d55 */
  return 0;

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}

/* 0x122060 */
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

/* 0x122240 */
void overlay_animation_apply(void *animation, int frame, void *node_output)
{
  (void)animation;
  (void)frame;
  (void)node_output;
}

/* 0x122450 */
void overlay_animation_apply_scaled(void *animation, int frame, float scale,
                                    void *node_output)
{
  (void)animation;
  (void)scale;
  (void)frame;
  (void)node_output;
}

/* 0x122690 */
void FUN_00122690(void *animation, float frame, void *node_data)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  FUN_001daf7e();
  floor(0.0f);
  error(0, (char *)0x00291388);
  /* cmp (int16_t)edi, (int16_t)ecx -> jl 0x122734 */
  /* relift: cmp word ptr [esi + 0x20], 1 -> jne 0x122a43 */
  /* relift: test byte ptr [esi + 0x3a], 1 -> je 0x12275e */
  /* test (char)eax, (char)eax -> jne 0x122758 */
  /* test eax, eax -> jne 0x12275e */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [ebp - 0x10], 1 -> je 0x1228e0 */
  /* test (char)eax, (char)eax -> je 0x122818 */
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  quaternions_interpolate_and_normalize((float *)0, (float *)0, 0.0f, (float *)0);
  FUN_0010b9c0((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, (float *)(uintptr_t)eax);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  points_interpolate((float *)0, (float *)0, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> je 0x122983 */
  overlay_animation_apply_continuous_scaled((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)(uintptr_t)eax);
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> jne 0x122a42 */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* cmp edi, ecx -> je 0x122a0b */
  display_assert((char *)0x002912a0, (char *)0x00290ce4, 693, 0);
  system_exit(0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* cmp ebx, eax -> je 0x122a42 */
  display_assert((char *)0x00291310, (char *)0x00290ce4, 694, 0);
  system_exit(0);
  FUN_001daf7e();
  floor(0.0f);
  error(0, (char *)0x002913d0);
  /* cmp (int16_t)edi, (int16_t)ecx -> jl 0x122b01 */
  /* relift: cmp word ptr [esi + 0x20], 1 -> jne 0x122e3e */
  /* relift: test byte ptr [esi + 0x3a], 1 -> je 0x122b2b */
  /* test (char)eax, (char)eax -> jne 0x122b25 */
  /* test eax, eax -> jne 0x122b2b */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [ebp - 0x10], 1 -> je 0x122cc8 */
  /* test (char)eax, (char)eax -> je 0x122be8 */
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  quaternions_interpolate_and_normalize((float *)0, (float *)0, 0.0f, (float *)0);
  quaternions_interpolate_and_normalize((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)ecx);
  FUN_0010b9c0((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)(uintptr_t)eax);
  /* test (char)eax, (char)eax -> je 0x122cfd */
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)(uintptr_t)eax);
  points_interpolate((float *)0, (float *)0, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> je 0x122d78 */
  overlay_animation_apply_continuous_scaled((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)(uintptr_t)eax);
  scalars_interpolate(0.0f, 0.0f, 0.0f, (float *)0);
  /* test (char)eax, (char)eax -> jne 0x122e3d */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* cmp edi, ecx -> je 0x122e06 */
  display_assert((char *)0x002912a0, (char *)0x00290ce4, 820, 0);
  system_exit(0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* cmp ebx, eax -> je 0x122e3d */
  display_assert((char *)0x00291310, (char *)0x00290ce4, 821, 0);
  system_exit(0);
  /* cmp eax, ecx -> jl 0x12345c */
  FUN_00120620(0);
  FUN_001d9068();
  FUN_001daf7e();
  /* cmp (int16_t)ebx, (int16_t)eax -> jl 0x122f2a */
  /* cmp edx, ecx -> jge 0x122f47 */
  /* test (char)eax, 1 -> jne 0x122f69 */
  csprintf((char *)0x005ab100, (char *)0x00291418);
  display_assert((char *)(uintptr_t)eax, (char *)0, 0, 0);
  system_exit(0);
  FUN_001d9068();
  FUN_001daf7e();
  /* cmp (int16_t)eax, (int16_t)ecx -> jl 0x123049 */
  /* cmp ecx, edx -> jge 0x12306d */
  /* test (int16_t)eax, (int16_t)eax -> jl 0x12345c */
  /* relift: cmp (int16_t)eax, word ptr [ebp - 0x2c] -> jge 0x12345c */
  /* test (int16_t)ebx, (int16_t)ebx -> jl 0x12345c */
  /* cmp (int16_t)ebx, (int16_t)edi -> jge 0x12345c */
  /* cmp edx, ecx -> jne 0x1230a5 */
  /* relift: cmp ecx, dword ptr [ebp - 0x28] -> jne 0x1230b1 */
  FUN_00120500((void *)(uintptr_t)esi, 0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  FUN_00120500((void *)(uintptr_t)esi, 0);
  /* relift: test byte ptr [ebp - 0x30], 1 -> je 0x1232af */
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  FUN_00121330((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  quaternion_decompress_8byte((void *)(uintptr_t)ecx, (float *)0);
  quaternion_decompress_8byte((void *)(uintptr_t)eax, (float *)0);
  quaternion_decompress_8byte((void *)(uintptr_t)edx, (float *)0);
  quaternion_decompress_8byte((void *)(uintptr_t)ecx, (float *)0);
  quaternions_interpolate_and_normalize((float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, 0.0f, (float *)(uintptr_t)edx);
  quaternions_interpolate_and_normalize((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, 0.0f, (float *)(uintptr_t)eax);
  quaternions_interpolate_and_normalize((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax, 0.0f, (float *)(uintptr_t)ecx);
  FUN_0010b9c0((float *)(uintptr_t)edx, (float *)(uintptr_t)eax, (float *)(uintptr_t)eax);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  animation_get_node_orientations((void *)(uintptr_t)esi, 0.0f, 0, 0, (void *)0);
  FUN_00121d60((void *)(uintptr_t)eax, (void *)(uintptr_t)edx, 0, (void *)(uintptr_t)eax);
  component_vectors_from_normal3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  FUN_001d90e0();
  display_assert((char *)0x00291440, (char *)0x00290ce4, 221, 0);
  system_exit(0);
  /* test (int16_t)esi, (int16_t)esi -> jne 0x1234f7 */
  FUN_00121d60((void *)(uintptr_t)edi, (void *)(uintptr_t)ebx, 0, (void *)(uintptr_t)eax);
  FUN_00121d60((void *)(uintptr_t)edi, (void *)(uintptr_t)ebx, 0, (void *)0);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 76);
  /* cmp (char)ecx, 0xff -> je 0x1238f3 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  /* test (char)ecx, (char)ecx -> jne 0x1238f3 */
  /* cmp (int16_t)eax, 0xffff -> je 0x1238f3 */
  tag_block_get_element((void *)(uintptr_t)eax, 0, 48);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)eax, 0, 32);
  tag_get('rdhs', 0);
  shader_type_is_valid_for_model();
  /* test (char)eax, (char)eax -> je 0x1238d6 */
  /* relift: test byte ptr [esi], 1 -> jne 0x1238d6 */
  shader_type_is_transparent(ecx);
  /* test (char)eax, (char)eax -> je 0x1237fa */
  /* relift: cmp word ptr [ebp - 0xc], 2 -> jne 0x1238d6 */
  /* relift: test byte ptr [ebp + 0x20], 2 -> je 0x1236da */
  display_assert((char *)0x00291538, (char *)0x00291564, 442, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x1236f1 */
  /* relift: cmp edx, dword ptr [eax + 0xb8] -> jl 0x123711 */
  display_assert((char *)0x002914d8, (char *)0x00291564, 445, 0);
  system_exit(0);
  /* test (int16_t)eax, (int16_t)eax -> jl 0x123728 */
  /* relift: cmp ecx, dword ptr [edx + 0xb8] -> jl 0x123748 */
  display_assert((char *)0x00291470, (char *)0x00291564, 446, 0);
  system_exit(0);
  matrix_transform_point((float *)(uintptr_t)edx, (float *)0, (float *)0);
  FUN_0017cbd0(0, 0, 0, 0, 0, 0, 0, (float *)(uintptr_t)edx, 0);
  /* relift: cmp word ptr [ebp - 8], 0x20 -> jge 0x1238d6 */
  /* relift: cmp word ptr [ebp + edi - 0x220], -1 -> je 0x1238d6 */
  /* test (char)eax, (char)eax -> jne 0x1238d6 */
  /* test (char)eax, (char)eax -> jg 0x1237d9 */
  /* test (char)eax, (char)eax -> jle 0x1238d6 */
  /* relift: cmp word ptr [ebx + 0x24], 4 -> jne 0x123871 */
  FUN_001906b0((void *)(uintptr_t)ebx, 0);
  /* test (char)ecx, 8 -> je 0x123871 */
  /* relift: cmp word ptr [ebp - 0xc], 1 -> jne 0x1238d6 */
  /* relift: test byte ptr [ebp + 0x20], 2 -> je 0x123845 */
  display_assert((char *)0x00291538, (char *)0x00291564, 491, 0);
  system_exit(0);
  FUN_0017cbc0(0, 0, 0, 0, 0, 0, 0);
  /* relift: cmp word ptr [ebp - 0xc], 0 -> jne 0x1238d6 */
  FUN_0017ccd0((void *)(uintptr_t)ebx, 0, (void *)(uintptr_t)esi, (void *)0);
  FUN_0017cbc0(0, 0, 0, 0, 0, 0, 0);
  FUN_0017d2b0();
  /* cmp eax, ecx -> jl 0x12363f */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x123974 */
  /* relift: cmp (int16_t)ecx, word ptr [ebp + edi - 0x21c] -> jne 0x123945 */
  /* test (int16_t)ecx, (int16_t)ecx -> jg 0x12394d */
  /* cmp (int16_t)eax, (int16_t)ebx -> jl 0x123930 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x123990 */
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

/* 0x123b30 */
void FUN_00123b30(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  tag_block_get_element((void *)(uintptr_t)eax, 0, 156);
  component_vectors_from_normal3d((float *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx);
  /* test (int16_t)edi, (int16_t)edi -> jne 0x123be0 */
  /* test ecx, ecx -> jne 0x123bb8 */
  /* test eax, eax -> jne 0x123bc4 */
  matrix4x3_from_forward_up_position((void *)(uintptr_t)esi, (float *)(uintptr_t)eax, (float *)(uintptr_t)ecx, (float *)(uintptr_t)edx);
  matrix4x3_multiply((float *)(uintptr_t)esi, (float *)(uintptr_t)ecx, (float *)(uintptr_t)esi);
  /* relift: cmp word ptr [ebx + 0x24], -1 -> jne 0x123c07 */
  display_assert((char *)0x00291584, (char *)0x00291564, 650, 0);
  system_exit(0);
  matrix4x3_multiply((float *)(uintptr_t)ecx, (float *)0, (float *)0);
  /* cmp (int16_t)ebx, -1 -> je 0x123c5b */
  /* relift: cmp word ptr [ebp - 8], (int16_t)ecx -> jne 0x123b5a */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x123c70 */
void FUN_00123c70(void *mode_tag, void *out_matrices, void *node_data, float *position, float *forward, float *up)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  matrix4x3_from_forward_up_position((void *)(uintptr_t)eax, (float *)(uintptr_t)edx, (float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 0);
  FUN_00109500((float *)(uintptr_t)ecx, (float *)(uintptr_t)eax);
  matrix4x3_multiply((float *)(uintptr_t)edi, (float *)(uintptr_t)edx, (float *)(uintptr_t)esi);
  /* cmp (int16_t)eax, 0xffff -> je 0x123d4d */
  /* cmp (int16_t)ebx, -1 -> je 0x123d66 */
  /* relift: cmp word ptr [ebp - 4], (int16_t)ecx -> jne 0x123cc0 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
}

/* 0x123d80 */
void FUN_00123d80(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edi = 0;

  /* test ecx, ecx -> je 0x123dc1 */
  /* relift: cmp byte ptr [ecx], 0 -> je 0x123dc1 */
  tag_get('edom', 0);
  tag_block_get_element((void *)(uintptr_t)ecx, 0, 64);
  crt_stricmp((char *)(uintptr_t)ecx, (char *)(uintptr_t)eax);
  /* test eax, eax -> je 0x123e14 */
  /* cmp (int16_t)ebx, (int16_t)edi -> jle 0x123dca */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edi;
}

/* 0x123e20 */
void animation_get_root_matrix(void)
{
  tag_block_get_element((void *)0, 0, 0);
}

/* 0x123e50 */
void FUN_00123e50(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;

  tag_get('edom', 0);
  /* test eax, eax -> jle 0x123ea4 */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 156);
  csstrcmp((char *)(uintptr_t)eax, (char *)(uintptr_t)ebx);
  /* test eax, eax -> je 0x123ead */
  /* cmp eax, ecx -> jl 0x123e80 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
}

/* 0x123ed0 */
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
