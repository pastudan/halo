/* --- model_animations.obj batch drafts (2026-07-26) --- */

/* 0x120250 */
void FUN_00120250(void)
{

}

/* 0x120340 */
void FUN_00120340(void)
{

}

/* 0x120400 */
void FUN_00120400(void)
{

}

/* 0x120470 */
void FUN_00120470(void)
{

}

/* 0x1204a0 */
void FUN_001204a0(void)
{

}

/* 0x120620 */
char FUN_00120620(int animation)
{
  (void)animation;
  return 0;
}

/* 0x120670 */
void build_damage_animation_index(void)
{

}

/* 0x120710 */
void FUN_00120710(int anim_entry, int tick_out, int damage_time_out)
{
  (void)anim_entry;
  (void)tick_out;
  (void)damage_time_out;
}

/* 0x120790 */
void animation_set_frame_size(void)
{

}

/* 0x120930 */
void quaternion_decompress_6byte_renormalized(void)
{

}

/* 0x120950 */
void quaternion_compress_8byte(void)
{

}

/* 0x1209b0 */
void quaternion_compress_6byte(void)
{

}

/* 0x120a40 */
void animation_graph_node_matrices_from_orientations(void)
{

}

/* 0x120ba0 */
void interpolate_node_orientations(void)
{

}

/* 0x120cb0 */
short FUN_00120cb0(int animation_graph_tag_index, const char *name)
{
  (void)animation_graph_tag_index;
  (void)name;
  return 0;
}

/* 0x120ee0 */
void animation_frame_get_xy_translation(void)
{

}

/* 0x120fd0 */
void inverse_kinematics_adjust_matrices(float *composed_matrix, int node_matrix_b, int node_matrix_c, int node_matrix_d)
{
  (void)composed_matrix;
  (void)node_matrix_b;
  (void)node_matrix_c;
  (void)node_matrix_d;
}

/* 0x121330 */
void FUN_00121330(void *animation, float frame, unsigned short rotation_count, short node_index, void *out_rotation)
{
  (void)animation;
  (void)frame;
  (void)rotation_count;
  (void)node_index;
  (void)out_rotation;
}

/* 0x121c30 */
int animation_update_internal(int update_kind, int animation_graph_tag_index, short *state, int *out_sound)
{
  (void)update_kind;
  (void)animation_graph_tag_index;
  (void)state;
  (void)out_sound;
  return 0;
}

/* 0x122060 */
void replacement_animation_apply(void)
{

}

/* 0x122240 */
void overlay_animation_apply(void)
{

}

/* 0x122450 */
void overlay_animation_apply_scaled(void)
{

}

/* 0x122690 */
void FUN_00122690(void *animation, float frame, void *node_data)
{
  (void)animation;
  (void)frame;
  (void)node_data;
}

/* 0x123990 */
void FUN_00123990(void)
{

}

/* 0x123b30 */
void FUN_00123b30(void)
{

}

/* 0x123c70 */
void FUN_00123c70(void *mode_tag, void *out_matrices, void *node_data, float *position, float *forward, float *up)
{
  (void)mode_tag;
  (void)out_matrices;
  (void)node_data;
  (void)position;
  (void)forward;
  (void)up;
}

/* 0x123d80 */
void FUN_00123d80(void)
{

}

/* 0x123e20 */
void animation_get_root_matrix(void)
{

}

/* 0x123e50 */
void FUN_00123e50(void)
{

}

/* 0x123ed0 */
void FUN_00123ed0(int model_ref, float distance, void *node_matrices, void *arg4, void *node_transforms, void *node_matrices2, int lighting, void *position, int arg9, void *effect_record, int object_handle, int arg12, int render_flag)
{
  (void)model_ref;
  (void)distance;
  (void)node_matrices;
  (void)arg4;
  (void)node_transforms;
  (void)node_matrices2;
  (void)lighting;
  (void)position;
  (void)arg9;
  (void)effect_record;
  (void)object_handle;
  (void)arg12;
  (void)render_flag;
}
