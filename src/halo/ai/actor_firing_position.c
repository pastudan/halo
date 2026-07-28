#include <stdint.h>
/* --- actor_firing_position.obj batch drafts (2026-07-26) --- */

/* FUN_00024000 (0x24000) — readable C lift. */
void FUN_00024000(void *unused, float score, int type, void *position, void *ctx)
{
  extern char DAT_00254c5c[];
  extern char DAT_00254c8c[];
  (void)unused;
  (void)type;
  (void)position;
  /* Bounds live in XBE rdata — use absolute VAs (not DAT_ relocs). */
  if (score < *(float *)0x2533c0 || !(score < *(float *)0x254cb8)) {
    display_assert(DAT_00254c5c, DAT_00254c8c, 0x81, 1);
    system_exit(-1);
  }
  *(float *)((char *)ctx + 0x38) = *(float *)((char *)ctx + 0x38) + score;
}

/* FUN_00024060 (0x24060) — XBE naked draft (batch 139). */
#if defined(__clang__)
static void (*const b24060_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const b24060_exitfn)(int) = system_exit;

__attribute__((naked, noinline))
void FUN_00024060(void)
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "movw 0x10(%%ebp), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "jle .LFUN_00024060_6\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x14(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "addl $8, %%esi\n\t"
      "movzwl %%ax, %%ebx\n\t"
      "nop\n\t"
      ".LFUN_00024060_1:\n\t"
      "movb 0x28(%%esi), %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_00024060_5\n\t"
      "flds 0x18(%%edi)\n\t"
      "movl $0, 0x10(%%ebp)\n\t"
      "fmuls 0x253398\n\t"
      "fstps 0x14(%%ebp)\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x14(%%ebp)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024060_2\n\t"
      "movl $0x41000000, 0x10(%%ebp)\n\t"
      "jmp .LFUN_00024060_4\n\t"
      ".LFUN_00024060_2:\n\t"
      "flds (%%esi)\n\t"
      "fcomps 0x18(%%edi)\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jp .LFUN_00024060_4\n\t"
      "flds 0x18(%%edi)\n\t"
      "fsubs (%%esi)\n\t"
      "flds 0x2533c8\n\t"
      "fdivs 0x14(%%ebp)\n\t"
      ".byte 0xde, 0xc9\n\t"
      "fmuls 0x253f78\n\t"
      "fsts 0x10(%%ebp)\n\t"
      "fcomps 0x2533c0\n\t"
      "fnstsw %%ax\n\t"
      "testb $1, %%ah\n\t"
      "jne .LFUN_00024060_3\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fcomps 0x254cb8\n\t"
      "fnstsw %%ax\n\t"
      "testb $5, %%ah\n\t"
      "jnp .LFUN_00024060_4\n\t"
      ".LFUN_00024060_3:\n\t"
      "pushl $1\n\t"
      "pushl $0x81\n\t"
      "pushl $0x254c8c\n\t"
      "pushl $0x254c5c\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_00024060_4:\n\t"
      "flds 0x10(%%ebp)\n\t"
      "fadds 0x30(%%esi)\n\t"
      "fstps 0x30(%%esi)\n\t"
      ".LFUN_00024060_5:\n\t"
      "addl $0x3c, %%esi\n\t"
      "decl %%ebx\n\t"
      "jne .LFUN_00024060_1\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      ".LFUN_00024060_6:\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [assert] "m"(b24060_assert), [exitfn] "m"(b24060_exitfn)
      : "memory");
}
#else
#error "FUN_00024060: clang naked draft required"
#endif


/* FUN_00024130 (0x24130) — readable C lift (restored pre-naked). */
void FUN_00024130(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int esi = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)eax, 0);
  actor_combat_get_firing_variant_definition(0);
  /* test (char)eax, 0x41 -> je 0x2424e */
  /* test (char)eax, 0x41 -> jne 0x2424e */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x2424e */
  /* test (char)eax, (char)eax -> je 0x24244 */
  /* test (char)eax, 0x41 -> jne 0x241f5 */
  /* test (char)eax, 1 -> jne 0x24218 */
  display_assert((char *)0x00254c5c, (char *)0x00254c8c, 129, 0);
  system_exit(0);
  /* relift: cmp word ptr [edx + 0x256], 0 -> jle 0x24360 */
  /* test (int16_t)ebx, (int16_t)ebx -> jle 0x24360 */
  /* relift: cmp word ptr [edx + 0x254], (int16_t)edi -> jle 0x24340 */
  /* test (int16_t)eax, (int16_t)eax -> je 0x242ae */
  /* cmp (int16_t)eax, 1 -> jne 0x242f8 */
  actor_perception_aiming_vector_test_blockage();
  /* test (int16_t)esi, (int16_t)esi -> jne 0x242eb */
  /* cmp (int16_t)ecx, (int16_t)eax -> jle 0x242e6 */
  /* cmp (int16_t)esi, 1 -> jne 0x242f8 */
  /* cmp (int16_t)ebx, (int16_t)eax -> jg 0x242f8 */
  /* relift: cmp (int16_t)edi, word ptr [edx + 0x254] -> jl 0x24293 */
  /* cmp (int16_t)ebx, 2 -> jl 0x24313 */
  /* cmp (int16_t)ebx, 1 -> jl 0x24321 */
  /* cmp (int16_t)eax, 2 -> jl 0x24332 */
  /* cmp (int16_t)eax, 1 -> jl 0x24340 */

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)esi;
  (void)edi;
}


/* FUN_00024370 (0x24370) — readable C lift. */
int FUN_00024370(int actor_handle, void *actor, void *fp)
{
  void *unit;
  int local;
  char ok;
  void *scenario;

  unit = datum_get(*(data_t **)0x6325a4, actor_handle);
  tag_get(0x61637472, *(int *)((char *)unit + 0x58));
  if (*((unsigned char *)actor + 0x44) == 0) {
    if (fp == 0)
      return 1;
    return (int)(unsigned char)*((unsigned char *)fp + 0x30);
  }
  if (fp == 0) {
    *(float *)((char *)actor + 0x660) += *(float *)0x254cc0;
    return 1;
  }
  local = 0;
  ok = actor_path_3d_available(actor_handle, *(float **)fp, (float *)&local);
  if (ok) {
    scenario = scenario_get();
    ok = path_3d_available((int)scenario, (int *)((char *)unit + 0x12c), local, *(int **)fp, (unsigned char *)0, (float *)0);
    if (ok)
      FUN_00024000(actor, 15.0f, 0x19, (void *)0, (void *)0);
    else
      goto fail_flags;
  } else {
fail_flags:
    *((unsigned char *)fp + 0x31) = 1;
    if (*((unsigned char *)actor + 0x14) == 0)
      *((unsigned char *)fp + 0x30) = 0;
  }
  return (fp == 0) ? 1 : (int)(unsigned char)*((unsigned char *)fp + 0x30);
}

/* FUN_00024450 (0x24450) — readable C lift (restored pre-naked). */
void FUN_00024450(void)
{
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;
  int edi = 0;

  datum_get((void *)(uintptr_t)ecx, 0);
  game_time_get();
  encounter_mark_examined_pursuit_position(0, 0, eax, 0);
  encounter_pursuit_position_already_examined(0, 0, ecx, 0, (void *)(uintptr_t)edx, (void *)(uintptr_t)ecx);
  /* test dl, dl -> je 0x24530 */
  /* test (char)ebx, (char)ebx -> je 0x24542 */
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0, (void *)0);
  /* test (char)ebx, (char)ebx -> jne 0x24542 */
  /* test dl, dl -> jne 0x24542 */
  /* test dl, dl -> je 0x245c4 */
  /* cmp edx, eax -> jl 0x24576 */
  /* cmp ecx, eax -> jge 0x2457d */
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0, (void *)0);
  FUN_00024000((void *)(uintptr_t)edi, 0.0f, 0, (void *)0, (void *)0);

  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
  (void)edi;
}



/* post_evaluator_hide (0x245d0) — readable C lift. */
int post_evaluator_hide(void *unused, void *ctx, void *cand)
{
  float score;
  int kind;
  (void)unused;
  if (*(unsigned char *)((char *)ctx + 0x5fc) == 0)
    goto done;
  if (cand == 0) {
    *(float *)((char *)ctx + 0x660) =
        *(float *)((char *)ctx + 0x660) + *(float *)0x254cc8;
    return 1;
  }
  kind = *(short *)((char *)cand + 6);
  score = 0.0f;
  if ((unsigned)kind > 4u) {
    display_assert((const char *)0, (const char *)0x254c8c, 0x45d, 1);
    system_exit(-1);
  } else if (kind == 2) {
    score = 12.0f;
  } else if (kind == 4) {
    score = 10.0f;
  } else if (kind == 1) {
    if (*(unsigned char *)((char *)ctx + 8) != 0)
      score = 6.0f;
    else {
      *((unsigned char *)cand + 0x31) = 1;
      if (*(unsigned char *)((char *)ctx + 0x14) == 0)
        *((unsigned char *)cand + 0x30) = 0;
    }
  } else if (kind == 3) {
    score = 4.0f;
  } else {
    *((unsigned char *)cand + 0x31) = 1;
    if (*(unsigned char *)((char *)ctx + 0x14) == 0)
      *((unsigned char *)cand + 0x30) = 0;
  }
  FUN_00024000(ctx, score, 0x12, 0, ctx);
done:
  if (cand == 0)
    return 1;
  return *(unsigned char *)((char *)cand + 0x30);
}

/* FUN_000246b0 (0x246b0) — readable C lift. */
int FUN_000246b0(int unused, void *actor, void *fp)
{
  float v;
  float score;
  int kind;

  (void)unused;
  if (*((unsigned char *)actor + 0x5fc) == 0) {
    if (fp == 0)
      return 1;
    return (int)(unsigned char)*((unsigned char *)fp + 0x30);
  }
  if (fp == 0) {
    *(float *)((char *)actor + 0x660) += *(float *)0x254cd0;
    return 1;
  }
  score = 0.0f;
  kind = (int)*(short *)((char *)fp + 6);
  if (kind == 0) {
    score = 20.0f;
  } else if (kind == 1) {
    score = 10.0f;
  } else {
    v = *(float *)((char *)actor + 0x600) - *(float *)0x254ccc;
    if (v >= 0.0f && (v * v) <= *(float *)((char *)fp + 0x2c)) {
      /* early call with score 0 */
    } else {
      *((unsigned char *)fp + 0x31) = 1;
      if (*((unsigned char *)actor + 0x14) == 0)
        *((unsigned char *)fp + 0x30) = 0;
    }
  }
  FUN_00024000(actor, score, 0x14, (void *)0, (void *)0);
  if (fp == 0)
    return 1;
  return (int)(unsigned char)*((unsigned char *)fp + 0x30);
}


/* FUN_00024770 (0x24770) — readable C lift. */
int FUN_00024770(int unused, void *actor, void *fp)
{
  float score;
  int kind;
  unsigned char flag628;

  (void)unused;
  if (*((unsigned char *)actor + 0x5fc) == 0) {
    if (fp == 0)
      return 1;
    return (int)(unsigned char)*((unsigned char *)fp + 0x30);
  }
  if (fp == 0) {
    flag628 = *((unsigned char *)actor + 0x628);
    if (flag628)
      *(float *)((char *)actor + 0x660) += *(float *)0x254640; /* 6.0 */
    else
      *(float *)((char *)actor + 0x660) += *(float *)0x254cc0; /* 15.0 */
    return 1;
  }
  score = 0.0f;
  kind = (int)*(short *)((char *)fp + 6);
  flag628 = *((unsigned char *)actor + 0x628);
  if (kind == 0) {
    score = flag628 ? 6.0f : 15.0f;
    /* asm: 0x40c00000=6.0 when flag628, else 0x41700000=15.0 */
    if (flag628)
      score = 6.0f;
    else
      score = 15.0f;
  } else if (kind == 1) {
    if (flag628)
      score = 2.5f; /* 0x40200000 */
    else
      score = 5.0f; /* 0x40a00000 */
  } else {
    if (!flag628) {
      *((unsigned char *)fp + 0x31) = 1;
      if (*((unsigned char *)actor + 0x14) == 0)
        *((unsigned char *)fp + 0x30) = 0;
    }
  }
  FUN_00024000(actor, score, 0xe, (void *)0, (void *)0);
  if (fp == 0)
    return 1;
  return (int)(unsigned char)*((unsigned char *)fp + 0x30);
}


/* FUN_00024850 (0x24850) — readable C lift.
 * actor@edi state@ebx. */
void FUN_00024850(int actor_handle, int flag, char *actor, void *state)
{
  void **entry = (void **)0x254bf8;

  if (!*entry)
    return;
  for (; *entry; entry = (void **)((char *)entry + 8)) {
    unsigned bit = 1u << (unsigned char)actor[4];
    if ((bit & (unsigned)(int)*(short *)((char *)entry - 4)) == 0)
      continue;
    ((void (*)(int, char *, void *, void *))*entry)(actor_handle, actor, flag, state);
  }
}
/* FUN_00024890 (0x24890) — readable C lift. */
char FUN_00024890(int actor_handle, void *state, char *actor)
{
  extern char DAT_00254cd4[];
  extern char DAT_00254c8c[];
  char valid;
  int16_t *entry;
  char (*fn)(int, char *, void *);

  valid = 1;
  entry = (int16_t *)0x254c2c;
  while (*(int *)((char *)entry + 4) != 0) {
    int bit = 1 << (int)(unsigned char)actor[4];
    if ((int)entry[0] & bit) {
      fn = *(char (**)(int, char *, void *))((char *)entry + 4);
      valid = fn(actor_handle, actor, state);
    }
    entry += 4;
    if (!valid) {
      break;
    }
  }
  if (*(char *)((char *)state + 0x30) != valid) {
    display_assert(DAT_00254cd4, DAT_00254c8c, 0x4ee, 1);
    system_exit(-1);
  }
  return valid;
}

/* FUN_00024900 (0x24900) — readable C lift.
 * query_buf@edi. */
char FUN_00024900(int actor_handle, void *query_buf)
{
  char *qb = (char *)query_buf;
  void **entry;
  char ok = 1;

  *(int *)(qb + 0x660) = 0;
  for (entry = (void **)0x254c30; *entry; entry = (void **)((char *)entry + 8)) {
    unsigned bit = 1u << (unsigned char)qb[4];
    if (bit & (unsigned)(int)*(short *)((char *)entry - 4)) {
      ok = ((char (*)(int, void *, int))*entry)(actor_handle, query_buf, 0);
    }
    if (!ok)
      break;
  }
  return ok;
}
/* FUN_00024950 (0x24950) — readable C lift. */
int FUN_00024950(int index1, int index2)
{
  char *base;
  char *a;
  char *b;
  float fa;
  float fb;

  base = *(char **)0x331f04;
  a = base + index1 * 0x3c;
  b = base + index2 * 0x3c;
  if (base == 0) {
    display_assert((const char *)0x254d88, (const char *)0x254c8c, 0x50f, 1);
    system_exit(-1);
  }
  if (index1 < 0 || index1 >= (int)*(int16_t *)0x331f00) {
    display_assert((const char *)0x254d40, (const char *)0x254c8c, 0x510, 1);
    system_exit(-1);
  }
  if (index2 < 0 || index2 >= (int)*(int16_t *)0x331f00) {
    display_assert((const char *)0x254cf8, (const char *)0x254c8c, 0x511, 1);
    system_exit(-1);
  }
  if (a[0x30] != b[0x30]) {
    return a[0x30] == 0;
  }
  if (a[0x31] != b[0x31]) {
    return a[0x31] != 0;
  }
  fa = *(float *)(a + 0x38);
  fb = *(float *)(b + 0x38);
  if (fa < fb) {
    return 1;
  }
  return 0;
}

/* actor_get_firing_position_group (0x24a60) — readable C lift. */
int actor_get_firing_position_group(int actor_handle, short param_2, int param_3)
{
  char *actor;
  void *scenario;
  void *block;
  void *entry;
  char flag;
  int idx;
  int tmp;

  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  if (*(int *)(actor + 0x34) == -1)
    return 0;
  scenario = global_scenario_get();
  block = tag_block_get_element((char *)scenario + 0x42c,
                                *(int *)(actor + 0x34) & 0xffff, 0xb0);
  entry = tag_block_get_element((char *)block + 0x80, *(short *)(actor + 0x3a),
                                0xe8);
  flag = actor[0x98];
  tmp = (short)param_3 - 1;
  if (tmp == 0)
    flag = 1;
  else if (tmp == 1)
    flag = 0;
  if (param_2 == 1)
    return *(int *)((char *)entry + 0x54 + 5 * 4);
  if (param_2 == 4) {
    idx = (actor[0x374] != 0) ? 5 : 2;
  } else if (param_2 == 5) {
    return *(int *)((char *)entry + 0x54 + 6 * 4);
  } else if (actor[0x374] != 0) {
    idx = 3 + (flag != 0);
  } else {
    idx = (flag != 0);
  }
  if (idx < 0 || idx >= 7) {
    display_assert((const char *)0x254db4, (const char *)0x254c8c, 0x584, 1);
    system_exit(-1);
  }
  return *(int *)((char *)entry + 0x54 + idx * 4);
}

/* actor_clear_discarded_firing_positions (0x24b80) — readable C lift (ai campaign). */
void actor_clear_discarded_firing_positions(int actor_handle, int param2)
{
  unsigned char *a = (unsigned char *)datum_get(*(void **)0x6325a4, actor_handle);
  *(uint16_t *)(a + 0x3c6) = 0;
  uint16_t *slot = (uint16_t *)(a + 0x3ca);
  for (int i = 0; i < 4; i++)
    slot[i] = 0xffff;
  if (a[0x3d8]) {
    if (!param2 || a[0x3d9])
      a[0x3d8] = 0;
  }
}


/* FUN_00024be0 (0x24be0) — readable C lift. */
void FUN_00024be0(int actor_handle, short param_2, char param_3)
{
  char *actor;
  int idx;
  int next;
  void *block;
  float *pos;

  if (param_2 == (short)-1)
    return;
  actor = (char *)datum_get(*(data_t **)0x6325a4, actor_handle);
  idx = *(int16_t *)(actor + 0x3c6);
  actor[0x3c8 + idx * 4] = param_3;
  *(int16_t *)(actor + 0x3ca + idx * 4) = param_2;
  next = idx + 1;
  next &= 0x80000003;
  if (next < 0)
    next = ((next - 1) | -4) + 1;
  *(int16_t *)(actor + 0x3c6) = (int16_t)next;
  block = tag_block_get_element(
      (char *)global_scenario_get() + 0x42c,
      *(unsigned short *)(actor + 0x34),
      0xb0);
  pos = (float *)tag_block_get_element((char *)block + 0x98, param_2, 0x18);
  actor[0x3d9] = param_3;
  actor[0x3d8] = 1;
  *(float *)(actor + 0x3dc) = pos[0];
  *(float *)(actor + 0x3e0) = pos[1];
  *(float *)(actor + 0x3e4) = pos[2];
}



