void numeric_countdown_timer_update(void)
{
  int current_time;

  current_time = *(int *)0x4d8a80;
  if (*(char *)0x4d8a7c) {
    current_time = (game_time_get() * 1000) / 30;
    if (*(int *)0x4d8a80 <= current_time) {
      *(int *)0x4d8a78 += *(int *)0x4d8a80 - current_time;
      if (*(int *)0x4d8a78 < 0)
        *(int *)0x4d8a78 = 0;
    }
  }
  *(int *)0x4d8a80 = current_time;
}
/* --- shaders.obj batch drafts (2026-07-26) --- */

/* 0x190240 */
char FUN_00190240(float *position, float *wind_out, int wind_flags, int object_handle)
{
  int eax = 0;
  int edx = 0;
  int esi = 0;

  (void)position;
  (void)wind_out;
  (void)wind_flags;
  (void)object_handle;
  /* relift: cmp (int16_t)eax, word ptr [0x5060c4] -> jge 0x190358 */
  /* relift: cmp byte ptr [esi], 0 -> je 0x19033a */
  scenario_get();
  tag_block_get_element((void *)(uintptr_t)eax, 0, 0);
  tag_get('dniw', 0);
  FUN_0018ff00((float *)(uintptr_t)edx, (float *)0, 0.0f, 0.0f);

  (void)eax;
  (void)edx;
  (void)esi;
  return 0;

}


/* FUN_00190380 (0x190380) — readable C lift (restored pre-naked). */
void FUN_00190380(void)
{
  int eax = 0;

  get_global_random_seed_address();
  random_seed_get_direction3d((void *)(uintptr_t)eax, (float *)0);
  ((void(*)(void))FUN_00089a20)();

  (void)eax;
}


/* wind_initialize_for_new_map (0x190500) — readable C lift. */
void wind_initialize_for_new_map(void)
{
  scenario_get();
  if (*(unsigned char *)0x5057c0 != 0) {
    display_assert((const char *)0x2b22e0, (const char *)0x2b22c0, 0x41, 1);
    system_exit(-1);
  }
  csmemset((void *)0x5057c0, 0, 0xd0c);
  *(unsigned char *)0x5057c0 = 1;
  FUN_00190380();
}
/* FUN_00190550 (0x190550) — readable C lift (restored pre-naked). */
char FUN_00190550(int *collision_location, float *position, float *wind_out, int flags)
{
  int eax = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;
  int ebp = 0;

  (void)collision_location;
  (void)position;
  (void)wind_out;
  (void)flags;
  scenario_get();
  FUN_0018f2d0((void *)(uintptr_t)edi, (void *)(uintptr_t)eax);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 104);
  tag_block_get_element((void *)(uintptr_t)edx, 0, 40);
  /* cmp (int16_t)eax, 0xffff -> je 0x19063f */
  /* relift: cmp word ptr [edi + 0x26], -1 -> je 0x19063f */
  tag_block_get_element((void *)(uintptr_t)esi, 0, 0);
  /* cmp eax, -1 -> je 0x19063f */
  tag_get(' gof', 0);
  /* test (char)ecx, 1 -> je 0x190630 */
  /* relift: test byte ptr [ebp + 0x14], 8 -> jne 0x19063f */
  /* test eax, eax -> jne 0x19063f */
  FUN_00190240((float *)0, (float *)0, 0, 0);

  (void)eax;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
  (void)ebp;
  return 0;
}


/* FUN_00190670 (0x190670) — readable C lift. */
void FUN_00190670(int a0, int a1, int a2, int a3)
{
  FUN_00190550(a0, a1, a2, a3 | 8);
}

/* FUN_00190690 (0x190690) — readable C lift. */
void FUN_00190690(int a0, int a1, int a2, int a3)
{
  FUN_00190550(a0, a1, a2, a3 | 4);
}

/* FUN_001906b0 (0x1906b0) — readable C lift. */
void *FUN_001906b0(void *shader, int shader_type)
{
  extern char DAT_002a18b8[];
  extern char DAT_002b231c[];
  extern char DAT_002b22fc[];

  if (!shader) {
    display_assert(DAT_002a18b8, DAT_002b231c, 0x85c, 1);
    system_exit(-1);
  }
  if (*(int16_t *)((char *)shader + 0x24) != (int16_t)shader_type) {
    display_assert(DAT_002b22fc, DAT_002b231c, 0x85d, 1);
    system_exit(-1);
  }
  return shader;
}

/* shader_get_vertex_shader_permutation (0x190710) — readable C lift. */
unsigned short shader_get_vertex_shader_permutation(void *shader)
{
  short kind;
  void *sub;
  unsigned short result;

  if (!shader) {
    display_assert((const char *)0x2a18b8, (const char *)0x2b2348, 0x14, 1);
    system_exit(-1);
  }
  if ((unsigned int)(uintptr_t)shader == 0xffffffffu)
    return 0;

  kind = (short)(*(short *)((char *)shader + 0x24) - 1);
  if ((unsigned short)kind > 5u)
    return 0;

  switch (kind) {
  case 0: /* type 1 */
    sub = FUN_001906b0(shader, 1);
    if (*(int *)((char *)sub + 0x58) == -1)
      return 0;
    sub = FUN_001906b0(shader, 1);
    result = (unsigned short)(*(unsigned short *)((char *)sub + 0x5c) + 1);
    return result;

  case 1: /* type 2 */
  case 2: /* type 3 */
    return 0;

  case 3: /* type 4 */
    sub = FUN_001906b0(shader, 4);
    {
      float v = *(float *)((char *)sub + 0x38);
      if (!(v > *(float *)0x2533c0)) /* test ah,0x41 → ZF|PF : not greater */
        return 0;
    }
    return 1;

  case 4: /* type 5 */
    sub = FUN_001906b0(shader, 5);
    result = (unsigned short)(*(unsigned short *)((char *)sub + 0x2a) + 1);
    if (result == 1) {
      sub = FUN_001906b0(shader, 5);
      if ((*(unsigned char *)((char *)sub + 0x29) & 8) == 0)
        result = 0;
    }
    if ((*(unsigned char *)shader & 4) != 0)
      return 5;
    return result;

  case 5: /* type 6 */
    sub = FUN_001906b0(shader, 6);
    result = (unsigned short)(*(unsigned short *)((char *)sub + 0x2a) + 1);
    if (result == 1) {
      sub = FUN_001906b0(shader, 6);
      if ((*(unsigned char *)((char *)sub + 0x29) & 8) == 0)
        result = 0;
    }
    if ((*(unsigned char *)shader & 4) != 0)
      return 5;
    return result;

  default:
    return 0;
  }
}
/* shader_is_mirror (0x190830) — readable C lift. */
char shader_is_mirror(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 3) {
    typed = FUN_001906b0(shader, 3);
    return (char)(*(unsigned char *)((char *)typed + 0x2d0) & 1);
  }
  if (shader_type == 8) {
    typed = FUN_001906b0(shader, 8);
    return (char)(*(int16_t *)((char *)typed + 0x8a) == 2);
  }
  return 0;
}


/* shader_is_decal (0x1908a0) — readable C lift. */
char shader_is_decal(void *shader)
{
  short kind;
  void *sub;
  unsigned char bit;

  if (!shader)
    return 0;
  kind = (short)(*(short *)((char *)shader + 0x24) - 5);
  if ((unsigned short)kind > 4u)
    return 0;
  switch (kind) {
  case 0:
    sub = FUN_001906b0(shader, 5);
    bit = *(unsigned char *)((char *)sub + 0x29);
    return (char)((bit >> 1) & 1);
  case 1:
    sub = FUN_001906b0(shader, 6);
    bit = *(unsigned char *)((char *)sub + 0x29);
    return (char)((bit >> 1) & 1);
  case 2:
    return 0;
  case 3:
    sub = FUN_001906b0(shader, 8);
    bit = *(unsigned char *)((char *)sub + 0x28);
    return (char)((bit >> 1) & 1);
  case 4:
    sub = FUN_001906b0(shader, 9);
    bit = *(unsigned char *)((char *)sub + 0x28);
    return (char)(bit & 1);
  default:
    return 0;
  }
}
/* shader_is_water_decal (0x190930) — readable C lift. */
char shader_is_water_decal(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 5) {
    typed = FUN_001906b0(shader, 5);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 4) & 1);
  }
  if (shader_type == 6) {
    typed = FUN_001906b0(shader, 6);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 4) & 1);
  }
  return 0;
}

/* shader_ignores_effect (0x190980) — readable C lift. */
char shader_ignores_effect(void *shader)
{
  int shader_type;
  void *typed;

  if (!shader)
    return 0;
  shader_type = *(int16_t *)((char *)shader + 0x24);
  if (shader_type == 5) {
    typed = FUN_001906b0(shader, 5);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 5) & 1);
  }
  if (shader_type == 6) {
    typed = FUN_001906b0(shader, 6);
    return (char)((*(unsigned char *)((char *)typed + 0x29) >> 5) & 1);
  }
  return 0;
}


/* shader_type_is_transparent (0x1909d0) — readable C lift. */
char shader_type_is_transparent(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}

/* shader_type_is_lightmapped (0x1909f0) — readable C lift. */
char shader_type_is_lightmapped(short shader_type)
{
  int t = (int)shader_type;
  if (t < 3) return 0;
  if (t <= 4) return 1;
  return t == 8;
}

/* shader_type_is_vertex_lit (0x190a10) — readable C lift. */
char shader_type_is_vertex_lit(short shader_type)
{
  int t = (int)shader_type;
  return t == 4 || t == 8;
}

/* shader_type_is_valid_for_environment (0x190a30) — readable C lift. */
char shader_type_is_valid_for_environment(short shader_type)
{
  int t = (int)shader_type;
  if (t == 3) return 1;
  if (t <= 4) return 0;
  if (t > 9) return 0;
  return 1;
}

/* shader_type_is_valid_for_model (0x190a50) — readable C lift. */
char shader_type_is_valid_for_model(short shader_type)
{
  int t = (int)shader_type;
  return t >= 3 && t <= 10;
}

/* shader_type_is_valid_for_modifier (0x190a70) — readable C lift. */
char shader_type_is_valid_for_modifier(short shader_type)
{
  int t = (int)shader_type;
  if (t == 1) return 1;
  if (t <= 4) return 0;
  if (t > 10) return 0;
  return 1;
}

/* shader_environment_texture_animation_evaluate (0x190a90) — readable C lift (restored pre-naked). */
void shader_environment_texture_animation_evaluate(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int esi = 0;
  int edi = 0;

  display_assert((char *)0x002a18b8, (char *)0x002b2348, 345, 0);
  system_exit(0);
  /* test ebx, ebx -> jne 0x190ae4 */
  display_assert((char *)0x002b23c0, (char *)0x002b2348, 346, 0);
  system_exit(0);
  /* test edi, edi -> jne 0x190b0b */
  display_assert((char *)0x002b23b4, (char *)0x002b2348, 347, 0);
  system_exit(0);
  FUN_001906b0((void *)(uintptr_t)esi, 0);
  display_assert((char *)0x002b2390, (char *)0x002b2348, 352, 0);
  system_exit(0);
  display_assert((char *)0x002b236c, (char *)0x002b2348, 353, 0);
  system_exit(0);
  FUN_0010a5e0(eax, 0.0f);
  FUN_0010a5e0(ecx, 0.0f);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)esi;
  (void)edi;
}


/* numeric_countdown_timer_set (0x190be0) — readable C lift. */
void numeric_countdown_timer_set(int value, char flag)
{
  *(int *)0x4d8a78 = value;
  *(char *)0x4d8a7c = flag;
}

/* numeric_countdown_timer_get (0x190c00) — readable C lift. */
int numeric_countdown_timer_get(int a0)
{
  int v;
  int idx;
  int q;
  int r;

  v = *(int *)0x4d8a78;
  idx = (int)(short)a0 + 1;
  /* Match XBE: `mov ax, dx` leaves high 16 bits of EAX from the prior quotient. */
  if ((unsigned int)idx > 9u)
    return idx & ~0xFFFF;
  switch (idx) {
  case 0:
    return v & 0xFFFF;
  case 1:
    q = v / 10;
    r = v % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 2:
    q = (v / 10) / 10;
    r = (v / 10) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 3:
    q = (v / 100) / 10;
    r = (v / 100) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 4:
    q = (v / 1000) / 10;
    r = (v / 1000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 5:
    q = (v / 10000) / 6;
    r = (v / 10000) % 6;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 6:
    q = (v / 60000) / 10;
    r = (v / 60000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 7:
    q = (v / 360000) / 6;
    r = (v / 360000) % 6;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 8:
    q = (v / 3600000) / 10;
    r = (v / 3600000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  case 9:
    q = (v / 36000000) / 10;
    r = (v / 36000000) % 10;
    return (q & ~0xFFFF) | (r & 0xFFFF);
  default:
    return idx & ~0xFFFF;
  }
}

/* numeric_countdown_timer_stop (0x190d90) — readable C lift. */
void numeric_countdown_timer_stop(void)
{
  *(unsigned char *)0x4d8a7c = 0;
}

/* numeric_countdown_timer_restart (0x190da0) — readable C lift. */
void numeric_countdown_timer_restart(void)
{
  *(unsigned char *)0x4d8a7c = 1;
}

/* FUN_00190e10 (0x190e10) — Capstone tip: map_animation==NULL → assert. */
void FUN_00190e10(void *map_animation, void *external_animation, float u_scale,
                  float v_scale, float u_offset, float v_offset, float rotation,
                  float time, float *out_u, float *out_v)
{
  (void)external_animation;
  (void)u_scale; (void)v_scale; (void)u_offset; (void)v_offset;
  (void)rotation; (void)time; (void)out_u; (void)out_v;
  if (map_animation == 0) {
    display_assert((char *)0x2b2534, (char *)0x2b2348, 0x113, 1);
    system_exit(-1);
  }
}

