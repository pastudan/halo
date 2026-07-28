#include <stdint.h>
/* 0xc5730 — Append a source file's contents to the HS source buffer.
 * Reallocates the buffer at 0x46b6e8 to hold source_size + file_size + 1,
 * copies the file data, updates source_size at 0x46b6e4, and null-terminates.
 * Returns pointer to the appended data, or NULL on allocation failure. */
char *hs_compile_initialize(int source_file_size, void *source_ptr)
{
  int old_size;
  char *new_buf;
  char *dest;

  dest = 0;
  old_size = *(int *)0x46b6e4;
  new_buf =
    (char *)debug_realloc(*(void **)0x46b6e8, old_size + source_file_size + 1,
                          "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0xfd);
  if (new_buf != 0) {
    dest = new_buf + *(int *)0x46b6e4;
    *(char **)0x46b6e8 = new_buf;
    csmemcpy(dest, source_ptr, source_file_size);
    *(int *)0x46b6e4 = *(int *)0x46b6e4 + source_file_size;
    *(char *)(*(int *)0x46b6e8 + *(int *)0x46b6e4) = 0;
  }
  return dest;
}

/* 0xc57d0 — Search the HS source string table for a name. The source buffer
 * at 0x46b6ec is a packed sequence of null-terminated strings; returns the
 * byte offset of the matching string, or -1 if not found. */
int FUN_000c57d0(char *str)
{
  int offset;

  offset = 0;
  while (offset < *(int *)0x46b6f0) {
    if (csstrcmp(str, (const char *)(*(int *)0x46b6ec + offset)) == 0)
      return offset;
    offset += csstrlen((const char *)(*(int *)0x46b6ec + offset)) + 1;
  }

  return -1;
}

/* 0xc5840 — Resolve expression as a global variable reference. Looks up the
 * node's name via hs_find_global_by_name. If found, validates type
 * compatibility and sets the variable_ref flag (bit 2). If the node's type
 * is unparsed (0), propagates the global's type.
 */
bool FUN_000c5840(int datum_index)
{
  char *node;
  int16_t type;
  int global_ref;
  int16_t global_type;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  type = *(int16_t *)(node + 0x4);

  if ((type < 4 || type > 0x30) && type != 0) {
    display_assert(
      "hs_type_valid(expression->type) || expression->type==_hs_unparsed",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x4e4, 1);
    system_exit(-1);
  }

  global_ref = (int)hs_find_global_by_name(
    (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));
  *(int *)(node + 0x10) = global_ref;

  if (global_ref == -1) {
    if (*(uint8_t *)0x46b808 == 0)
      return false;
    *(const char **)0x46b6fc = "this is not a valid variable name.";
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return false;
  }

  global_type = hs_global_get_type((uint16_t) * (int16_t *)(node + 0x10));

  if (*(int16_t *)(node + 0x4) != 0 &&
      !hs_types_compatible(global_type, *(int16_t *)(node + 0x4))) {
    const char *global_name =
      hs_global_get_name((uint16_t) * (int16_t *)(node + 0x10));
    crt_sprintf(
      (char *)0x46b704,
      "i expected a value of type %s, but the variable %s has type %s",
      ((const char **)(void *)0x2f14a8)[(int)*(int16_t *)(node + 0x4)],
      global_name,
      ((const char **)(void *)0x2f14a8)[(int)(int16_t)global_type]);
    *(const char **)0x46b6fc = (const char *)0x46b704;
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return false;
  }

  if (*(int16_t *)(node + 0x4) == 0) {
    *(int16_t *)(node + 0x4) = global_type;
  }
  *(uint8_t *)(node + 0x6) |= 4;
  return true;
}

/* 0xc5960 — Resolve the function/script index for an expression node.
 * Looks up the first child (predicate) at datum_index->field_0x10. If the
 * predicate is already type 2 (function call), copies its function_index.
 * Otherwise tries hs_find_function_by_name, then hs_find_script_by_name
 * on the predicate's name string. Sets the is_script flag (bit 1) if
 * resolved as a script.
 */
void FUN_000c5960(int datum_index)
{
  char *node;
  char *node2;
  char *predicate;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  node2 = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  predicate = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node2 + 0x10));

  if (*(int16_t *)(predicate + 0x4) != 2) {
    int16_t fn_idx;
    char *name = (char *)(*(int *)(predicate + 0xc) + *(int *)0x46b6e8);

    fn_idx = hs_find_function_by_name(name);
    *(int16_t *)(node + 0x2) = fn_idx;
    *(int16_t *)(predicate + 0x4) = 2;

    if (*(int16_t *)(node + 0x2) == -1) {
      int16_t script_idx = hs_find_script_by_name(name);
      *(int16_t *)(node + 0x2) = script_idx;
      if (script_idx != -1) {
        *(uint8_t *)(node + 0x6) |= 2;
      }
    }

    *(int16_t *)(predicate + 0x2) = *(int16_t *)(node + 0x2);
    return;
  }

  if (*(int16_t *)(predicate + 0x2) == -1) {
    display_assert("predicate->function_index!=NONE",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x520, 1);
    system_exit(-1);
  }

  *(int16_t *)(node + 0x2) = *(int16_t *)(predicate + 0x2);
}

/* 0xc5a20 — Compile a boolean literal expression. Compares the source string
 * against known true/false synonyms and stores 1 or 0 in the value field. */
bool FUN_000c5a20(int datum_index)
{
  char *node;
  char *str;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  str = (char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8);

  if (*(int16_t *)(node + 0x4) != 5) {
    display_assert("expression->type==_hs_type_boolean",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5b3, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != *(int16_t *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5b4, 1);
    system_exit(-1);
  }

  if (csstrcmp(str, "false") == 0 || csstrcmp(str, "off") == 0 ||
      csstrcmp(str, "0") == 0) {
    *(char *)(node + 0x10) = 0;
    return true;
  }

  if (csstrcmp(str, "true") == 0 || csstrcmp(str, "on") == 0 ||
      csstrcmp(str, "1") == 0) {
    *(char *)(node + 0x10) = 1;
    return true;
  }

  *(const char **)0x46b6fc = "i expected \"true\" or \"false\".";
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return false;
}

/* 0xc5b50 — Validate and parse a real (float) literal from an HS expression.
 * Checks each character is a digit or single decimal point, then calls atof
 * to store the parsed value. Sets compile error on invalid input. */
bool FUN_000c5b50(int datum_index)
{
  char c;
  char seen_dot;
  char *node;
  char *str;
  bool result;

  result = true;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  str = (char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8);
  seen_dot = 0;

  if (*(int16_t *)(node + 0x4) != 6) {
    display_assert("expression->type==_hs_type_real",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5d6, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != *(int16_t *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5d7, 1);
    system_exit(-1);
  }

  if (*str == '-') {
    str = str + 1;
  }

  c = *str;
  if (c != '\0') {
    do {
      if (isdigit((int)c) == 0) {
        if (seen_dot || *str != '.') {
          *(const char **)0x46b6fc = "this is not a valid real number.";
          *(int *)0x46b700 = *(int *)(node + 0xc);
          result = false;
          goto done;
        }
        seen_dot = 1;
      }
      c = str[1];
      str = str + 1;
    } while (c != '\0');
  }

done:
  *(float *)(node + 0x10) =
    (float)atof((const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));

  return result;
}

/* 0xc5c40 — Validate and parse an integer literal (short or long) from an HS
 * expression. Checks each character is a digit, then calls atol. For short
 * integers (type 7) validates range [-32768, 32767]. */
bool FUN_000c5c40(int datum_index)
{
  char c;
  char *node;
  char *str;
  long val;
  bool result;

  result = true;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  str = (char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8);

  if (*(int16_t *)(node + 0x4) != 7 && *(int16_t *)(node + 0x4) != 8) {
    display_assert("expression->type==_hs_type_short_integer || "
                   "expression->type==_hs_type_long_integer",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5f7, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != *(int16_t *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5f8, 1);
    system_exit(-1);
  }

  if (*str == '-') {
    str = str + 1;
  }

  c = *str;
  while (c != '\0') {
    if (isdigit((int)c) == 0) {
      *(const char **)0x46b6fc = "this is not a valid integer.";
      *(int *)0x46b700 = *(int *)(node + 0xc);
      result = false;
      break;
    }
    c = str[1];
    str = str + 1;
  }

  val = atol((const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));

  if (result) {
    if (*(int16_t *)(node + 0x4) == 8)
      goto store_long;
    if (val > 0x7fff || val < (long)-0x8000) {
      *(const char **)0x46b6fc = "shorts must be in the range [-32767, 32768].";
      *(int *)0x46b700 = *(int *)(node + 0xc);
      result = false;
    }
  }

  if (*(int16_t *)(node + 0x4) != 8) {
    *(int16_t *)(node + 0x10) = (int16_t)val;
    return result;
  }

store_long:
  *(long *)(node + 0x10) = val;
  return result;
}

/* 0xc5d60 — Compile a string literal expression. Asserts type is
 * _hs_type_string (9), stores the string pointer (source_offset + source_base)
 * in the value field, and always returns true. */
bool FUN_000c5d60(int datum_index)
{
  char *node;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);

  if (*(int16_t *)(node + 0x4) != 9) {
    display_assert("expression->type==_hs_type_string",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x61e, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != *(int16_t *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x61f, 1);
    system_exit(-1);
  }

  *(int *)(node + 0x10) = *(int *)(node + 0xc) + *(int *)0x46b6e8;
  return true;
}

/* 0xc5de0 — Compile a script name reference. Asserts type is _hs_type_script
 * (10), looks up the script by name, stores the index in the value field. */
bool FUN_000c5de0(int datum_index)
{
  int16_t script_idx;
  char *node;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);

  if (*(int16_t *)(node + 0x4) != 10) {
    display_assert("expression->type==_hs_type_script",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x62d, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != *(int16_t *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x62e, 1);
    system_exit(-1);
  }

  script_idx = hs_find_script_by_name(
    (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));
  if (script_idx != -1) {
    *(int16_t *)(node + 0x10) = script_idx;
    return true;
  }

  *(const char **)0x46b6fc = "this is not a valid script name.";
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return false;
}

/* 0xc5e90 — Compile a tag reference expression. Asserts type is a tag reference
 * (0x18..0x1f), looks up the matching scenario source file by name and tag
 * group, stores the tag datum index from element+0x24 into node+0x10.
 * Always returns true regardless of whether a match is found. */
bool FUN_000c5e90(int datum_index)
{
  char *node;
  char *scenario;
  int tag_group;
  int i;
  char *element;
  int cmp;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  scenario = (char *)global_scenario_get();

  if (*(int16_t *)(node + 0x4) < 0x18 || *(int16_t *)(node + 0x4) > 0x1f) {
    display_assert("HS_TYPE_IS_TAG_REFERENCE(expression->type)",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x69e, 1);
    system_exit(-1);
  }

  tag_group = *(int *)(0x26f2cc + (int)*(int16_t *)(node + 0x4) * 4);

  i = 0;
  if (*(int *)(scenario + 0x4b4) > 0) {
    do {
      element = (char *)tag_block_get_element((void *)(scenario + 0x4b4),
                                              (int)(int16_t)i, 0x28);
      cmp = csstrcmp(*(const char **)(element + 0x1c),
                     (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));
      if (cmp == 0 && *(int *)(element + 0x18) == tag_group) {
        *(int *)(node + 0x10) = *(int *)(element + 0x24);
        break;
      }
      i++;
    } while ((int)(int16_t)i < *(int *)(scenario + 0x4b4));
  }

  return true;
}

/* 0xc6130 — Generic tag-block name lookup for HS literal compilation.
 * Iterates elements in tag_block (passed via EBX), comparing the string at
 * element+offset against the node's source string using case-insensitive match.
 * On match, stores the element index (as short) into node+0x10.
 * On failure, formats "this is not a valid %s name" error. */
bool FUN_000c6130(int datum_index, void *tag_block, int element_size,
                  short offset)
{
  char *node;
  int i;
  char *element;
  int cmp;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);

  if (element_size > 0x7fff) {
    display_assert("element_size<=SHORT_MAX",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x6f1, 1);
    system_exit(-1);
  }
  if ((int)offset + 0x1f >= element_size) {
    display_assert("offset+TAG_STRING_LENGTH<element_size",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x6f2, 1);
    system_exit(-1);
  }

  i = 0;
  if (*(int *)tag_block > 0) {
    do {
      element = (char *)tag_block_get_element(tag_block, i, element_size);
      cmp =
        crt_stricmp(element + (int)offset,
                    (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));
      if (cmp == 0) {
        *(int *)(node + 0x10) = (int)(int16_t)i;
        return true;
      }
      i++;
    } while ((int)(int16_t)i < *(int *)tag_block);
  }

  crt_sprintf((char *)0x46b704, "this is not a valid %s name",
              ((const char **)0x2f14a8)[(int)*(int16_t *)(node + 0x4)]);
  *(const char **)0x46b6fc = (const char *)0x46b704;
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return false;
}

/* 0xc6230 — Compile trigger_volume literal. Asserts type==0xb, then delegates
 * to FUN_000c6130 searching scenario+0x360 (trigger volumes, elem size 0x60,
 * name at offset 4). */
bool FUN_000c6230(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0xb) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_trigger_volume",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x711, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x360), 0x60, 4);
}

/* 0xc62a0 — Compile cutscene_flag literal (type 0xc). */
bool FUN_000c62a0(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0xc) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_cutscene_flag",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x719, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x4e4), 0x5c, 4);
}

/* 0xc6310 — Compile cutscene_camera_point literal (type 0xd). */
bool FUN_000c6310(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0xd) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_cutscene_camera_point",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x721, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x4f0), 0x68, 4);
}

/* 0xc6380 — Compile cutscene_title literal (type 0xe). */
bool FUN_000c6380(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0xe) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_cutscene_title",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x729, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x4fc), 0x60, 4);
}

/* 0xc63f0 — Compile cutscene_recording literal (type 0xf). */
bool FUN_000c63f0(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0xf) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_cutscene_recording",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x731, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x36c), 0x40, 0);
}

/* 0xc6460 — Compile device_group literal (type 0x10). */
bool FUN_000c6460(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x10) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_device_group",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x739, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x288), 0x34, 0);
}

/* 0xc64d0 — Compile AI encounter/squad literal (type 0x11).
 * Asserts type==_hs_type_ai and constant_type==type, then delegates to
 * FUN_000540f0 to look up an AI encounter or squad by name from the scenario.
 */
bool FUN_000c64d0(int datum_index)
{
  char *node;
  bool result;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)((char *)datum_get(*(data_t **)0x5aa6c8, datum_index) + 0x4) !=
      0x11) {
    display_assert("hs_syntax_get(expression_index)->type==_hs_type_ai",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x744, 1);
    system_exit(-1);
  }
  if (*(short *)(node + 0x2) != *(short *)(node + 0x4)) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x745, 1);
    system_exit(-1);
  }
  result = FUN_000540f0((void *)global_scenario_get(),
                        (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8),
                        (int *)(node + 0x10));
  if (!result) {
    *(const char **)0x46b6fc = "this is not a valid ai encounter or squad.";
    *(int *)0x46b700 = *(int *)(node + 0xc);
  }
  return result;
}

/* 0xc6580 — Compile ai_command_list literal (type 0x12). */
bool FUN_000c6580(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x12) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_ai_command_list",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x755, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x438), 0x60, 0);
}

/* 0xc65f0 — Compile starting_profile literal (type 0x13). */
bool FUN_000c65f0(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x13) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_starting_profile",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x75d, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x348), 0x68, 0);
}

/* 0xc6660 — Compile conversation literal (type 0x14). */
bool FUN_000c6660(int datum_index)
{
  char *node;
  char *scenario;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x14) {
    display_assert(
      "hs_syntax_get(expression_index)->type==_hs_type_conversation",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x765, 1);
    system_exit(-1);
  }
  scenario = (char *)global_scenario_get();
  return FUN_000c6130(datum_index, (void *)(scenario + 0x468), 0x74, 0);
}

/* 0xc6810 — Compile object name literal (types 0x25-0x2a).
 * "none" resolves to -1. Otherwise adds 6 to type (mapping object types to
 * enum range 0x2b-0x30), delegates to FUN_000c66d0, then restores type. */
bool FUN_000c6810(int datum_index)
{
  char *node;
  bool result;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) < 0x25 || *(short *)(node + 0x4) > 0x2a) {
    display_assert("HS_TYPE_IS_OBJECT(expression->type)",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x79a, 1);
    system_exit(-1);
  }
  if (csstrcmp((const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8),
               (const char *)0x254384) == 0) {
    *(int *)(node + 0x10) = -1;
    return true;
  }
  *(short *)(node + 0x4) += 6;
  *(short *)(node + 0x2) = *(short *)(node + 0x4);
  result = FUN_000c66d0(datum_index);
  *(short *)(node + 0x4) -= 6;
  return result;
}

/* 0xc68b0 — Compile navpoint literal (type 0x15).
 * Looks up a waypoint by name from the HUD globals tag (hudg+0x160,
 * element size 0x68). Returns false if no HUD globals tag is available. */
bool FUN_000c68b0(int datum_index)
{
  char *node;
  int tag_index;
  char *hud_tag;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x15) {
    display_assert("hs_syntax_get(expression_index)->type==_hs_type_navpoint",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x7b1, 1);
    system_exit(-1);
  }
  tag_index = interface_get_tag_index(6);
  if (tag_index == -1) {
    return false;
  }
  hud_tag = (char *)tag_get(0x68756467, interface_get_tag_index(6));
  return FUN_000c6130(datum_index, (void *)(hud_tag + 0x160), 0x68, 0);
}

/* 0xc69d0 — Compile object_list literal (type 0x17).
 * Temporarily sets type/constant_type to 0x2b (enum range for FUN_000c66d0),
 * delegates to FUN_000c66d0, then restores type to 0x17. */
bool FUN_000c69d0(int datum_index)
{
  char *node;
  bool result;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(short *)(node + 0x4) != 0x17) {
    display_assert("expression->type==_hs_type_object_list",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x7cf, 1);
    system_exit(-1);
  }
  *(short *)(node + 0x2) = 0x2b;
  *(short *)(node + 0x4) = 0x2b;
  result = FUN_000c66d0(datum_index);
  *(short *)(node + 0x4) = 0x17;
  return result;
}

/* Compile an HS function-call expression node (0xc73a0).
 *
 * Called from hs_type_check when a syntax node has flag bit 0 set (function
 * expression node). Receives the node's datum_index in EDI (register arg).
 *
 * The node's type field (node+0x4, int16_t) drives the dispatch:
 *   0           — unparsed/unknown; fall through to dispatch table
 *   1           — special form placeholder; emit "expected script/var" error
 *   4           — void expression; emit "void in non-void slot" error, fail
 *  [4..0x30]   — typed expression; dispatch to table at 0x27bb80[type*4]
 *
 * If hs_compile_globals.validating (0x46b808) is 0 or the node has flag bit 2
 * set, first attempts to resolve the expression as a global variable reference
 * via FUN_000c5840. If that succeeds, returns the result directly.
 *
 * Otherwise dispatches through the function-pointer table at 0x27bb80[type*4]
 * (indexed by the expression's type). Each table entry is a cdecl function
 * taking datum_index and returning bool. If the table entry is NULL, emits an
 * "unsupported expression type" error using the type-name table at 0x2f14a8
 * and returns false.
 *
 * Returns true if compilation succeeded, false on error (sets
 * hs_compile_globals.error at 0x46b6fc and error offset at 0x46b700).
 */

/* 0xc6a70 — Intern a string into the HS string constant pool.
 * Returns the byte offset of the string in the pool, deduplicating
 * via FUN_000c57d0. Asserts if the pool is full. */
int FUN_000c6a70(char *str)
{
  int offset;
  int len;

  offset = FUN_000c57d0(str);
  if (offset == -1) {
    len = (int)(short)(csstrlen(str) + 1);
    if (len < *(int *)0x46b6f4) {
      csmemcpy((char *)(*(int *)0x46b6ec + *(int *)0x46b6f0), str, len);
      offset = *(int *)0x46b6f0;
      *(int *)0x46b6f0 = *(int *)0x46b6f0 + len;
      *(int *)0x46b6f4 = *(int *)0x46b6f4 - len;
      return offset;
    }
    display_assert("ran out of script string constant memory",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x264, 1);
    system_exit(-1);
  }
  return offset;
}

/* FUN_000c6b00 (0xc6b00) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const bc6b00_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const bc6b00_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static int (*const bc6b00_c8df60)(const char *s1) = csstrlen;
static int16_t (*const bc6b00_cc3ee0)(const char *name) = hs_find_global_by_name;
static bool (*const bc6b00_cc7d80)(int datum_index, int16_t check_type) = hs_type_check;
static scenario_t * (*const bc6b00_c18e380)(void) = global_scenario_get;
static int16_t (*const bc6b00_c1b9ad0)(void *tag_block) = tag_block_add_element;
static void *(*const bc6b00_elem)(void *, int, int) = tag_block_get_element;
static char * (*const bc6b00_c8dff0)(char *destination, const char *source) = csstrcpy;

__attribute__((naked, noinline))
bool FUN_000c6b00(int datum_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0xc, %%esp\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "xorb %%bl, %%bl\n\t"
      "pushl %%eax\n\t"
      "movb %%bl, -0x1(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000c6b00_8\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0xc(%%ebp)\n\t"
      "je .LFUN_000c6b00_8\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "je .LFUN_000c6b00_8\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .LFUN_000c6b00_8\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ebx\n\t"
      "movl 0x46b6e8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%ebx\n\t"
      "xorl %%edi, %%edi\n\t"
      ".LFUN_000c6b00_1:\n\t"
      "movswl %%di, %%ecx\n\t"
      "movl 0x2f14a8(,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c6b00_3\n\t"
      "incl %%edi\n\t"
      "cmpw $0x31, %%di\n\t"
      "jl .LFUN_000c6b00_1\n\t"
      ".LFUN_000c6b00_2:\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl $0x27c5d8, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x46b700\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6b00_3:\n\t"
      "cmpw $4, %%di\n\t"
      "jl .LFUN_000c6b00_2\n\t"
      "cmpw $0x31, %%di\n\t"
      "jge .LFUN_000c6b00_2\n\t"
      "movl -0xc(%%ebp), %%esi\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ebx\n\t"
      "addl 0x46b6e8, %%ebx\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_000c6b00_7\n\t"
      "pushl %%ebx\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x1f, %%eax\n\t"
      "ja .LFUN_000c6b00_7\n\t"
      "pushl %%ebx\n\t"
      "call *%[cc3ee0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "jne .LFUN_000c6b00_6\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movb $1, 0x46b806\n\t"
      "movb $1, 0x46b807\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c6b00_5\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4a8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c1b9ad0]\n\t"
      "addl $4, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000c6b00_4\n\t"
      "movswl %%ax, %%edx\n\t"
      "pushl $0x5c\n\t"
      "pushl %%edx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x4a8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%esi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8dff0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0x14, %%esp\n\t"
      "movw %%di, 0x20(%%esi)\n\t"
      "movl %%eax, 0x28(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "jmp .LFUN_000c6b00_5\n\t"
      ".LFUN_000c6b00_4:\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "movl $0x27c5ac, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movl %%eax, 0x46b700\n\t"
      ".LFUN_000c6b00_5:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb $0, 0x46b806\n\t"
      "movb $0, 0x46b807\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6b00_6:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x27c580, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6b00_7:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl $0x27c544, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6b00_8:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl $0x27c510, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc6b00_dget), [c8dcb0] "m"(bc6b00_c8dcb0), [c8df60] "m"(bc6b00_c8df60), [cc3ee0] "m"(bc6b00_cc3ee0), [cc7d80] "m"(bc6b00_cc7d80), [c18e380] "m"(bc6b00_c18e380), [c1b9ad0] "m"(bc6b00_c1b9ad0), [elem] "m"(bc6b00_elem), [c8dff0] "m"(bc6b00_c8dff0)
      : "memory");
}
#else
#error "FUN_000c6b00: clang naked draft required"
#endif


/* FUN_000c6d90 (0xc6d90) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const bc6d90_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int (*const bc6d90_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static int (*const bc6d90_c8df60)(const char *s1) = csstrlen;
static scenario_t * (*const bc6d90_c18e380)(void) = global_scenario_get;
static int16_t (*const bc6d90_cc3d50)(const char *name) = hs_find_script_by_name;
static int16_t (*const bc6d90_c1b9ad0)(void *tag_block) = tag_block_add_element;
static void *(*const bc6d90_elem)(void *, int, int) = tag_block_get_element;
static int (*const bc6d90_c119610)(data_t *data) = data_new_at_index;
static bool (*const bc6d90_cc7d80)(int datum_index, int16_t check_type) = hs_type_check;
static char * (*const bc6d90_c8dff0)(char *destination, const char *source) = csstrcpy;

__attribute__((naked, noinline))
bool FUN_000c6d90(int datum_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $0x1c, %%esp\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "movl 0x8(%%ebp), %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "addl $0x10, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "je .LFUN_000c6d90_24\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%esi\n\t"
      "movl 0x46b6e8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%esi\n\t"
      "xorl %%ebx, %%ebx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "leal (%%esp), %%esp\n\t"
      ".LFUN_000c6d90_1:\n\t"
      "movswl %%bx, %%ecx\n\t"
      "movl 0x2f156c(,%%ecx,4), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c6d90_3\n\t"
      "incl %%ebx\n\t"
      "cmpw $5, %%bx\n\t"
      "jl .LFUN_000c6d90_1\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      ".LFUN_000c6d90_2:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl $0x27c790, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_3:\n\t"
      "cmpw $-1, %%bx\n\t"
      "movl %%ebx, -0xc(%%ebp)\n\t"
      "je .LFUN_000c6d90_2\n\t"
      "cmpw $3, %%bx\n\t"
      "je .LFUN_000c6d90_4\n\t"
      "cmpw $4, %%bx\n\t"
      "je .LFUN_000c6d90_4\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl $4, -0x8(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "jmp .LFUN_000c6d90_11\n\t"
      ".LFUN_000c6d90_4:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ebx\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "je .LFUN_000c6d90_9\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edi\n\t"
      "movl 0x46b6e8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "addl %%eax, %%edi\n\t"
      "xorl %%esi, %%esi\n\t"
      ".LFUN_000c6d90_5:\n\t"
      "movswl %%si, %%eax\n\t"
      "movl 0x2f14a8(,%%eax,4), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edi\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "je .LFUN_000c6d90_8\n\t"
      "incl %%esi\n\t"
      "cmpw $0x31, %%si\n\t"
      "jl .LFUN_000c6d90_5\n\t"
      "movl $0xffffffff, -0x8(%%ebp)\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      ".LFUN_000c6d90_6:\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $4, %%si\n\t"
      "jl .LFUN_000c6d90_7\n\t"
      "cmpw $0x31, %%si\n\t"
      "jl .LFUN_000c6d90_10\n\t"
      ".LFUN_000c6d90_7:\n\t"
      "movl $0x27c76c, 0x46b6fc\n\t"
      "pushl %%ebx\n\t"
      "jmp .LFUN_000c6d90_16\n\t"
      ".LFUN_000c6d90_8:\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "jmp .LFUN_000c6d90_6\n\t"
      ".LFUN_000c6d90_9:\n\t"
      "movl $0x27c730, 0x46b6fc\n\t"
      "jmp .LFUN_000c6d90_15\n\t"
      ".LFUN_000c6d90_10:\n\t"
      "movl -0xc(%%ebp), %%ebx\n\t"
      ".LFUN_000c6d90_11:\n\t"
      "cmpl $-1, %%edi\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "je .LFUN_000c6d90_20\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%eax\n\t"
      "movl %%eax, -0x14(%%ebp)\n\t"
      "je .LFUN_000c6d90_20\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%esi\n\t"
      "addl 0x46b6e8, %%esi\n\t"
      "pushl %%esi\n\t"
      "movl %%esi, -0x18(%%ebp)\n\t"
      "call *%[c8df60]\n\t"
      "addl $0xc, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jbe .LFUN_000c6d90_19\n\t"
      "pushl %%esi\n\t"
      "call *%[c8df60]\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $0x1f, %%eax\n\t"
      "ja .LFUN_000c6d90_19\n\t"
      "call *%[c18e380]\n\t"
      "pushl %%esi\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[cc3d50]\n\t"
      "movswl %%ax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "addl $0x49c, %%edi\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_000c6d90_12\n\t"
      "pushl %%edi\n\t"
      "call *%[c1b9ad0]\n\t"
      "movl %%eax, %%esi\n\t"
      "addl $4, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "jne .LFUN_000c6d90_17\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl $0x27c710, 0x46b6fc\n\t"
      "pushl %%ecx\n\t"
      "jmp .LFUN_000c6d90_25\n\t"
      ".LFUN_000c6d90_12:\n\t"
      "pushl $0x5c\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movw 0x20(%%eax), %%cx\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $4, %%cx\n\t"
      "jne .LFUN_000c6d90_13\n\t"
      "movw 0x22(%%eax), %%dx\n\t"
      "cmpw -0x8(%%ebp), %%dx\n\t"
      "jne .LFUN_000c6d90_13\n\t"
      "cmpw $3, %%bx\n\t"
      "je .LFUN_000c6d90_17\n\t"
      ".LFUN_000c6d90_13:\n\t"
      "cmpw $3, %%cx\n\t"
      "jne .LFUN_000c6d90_14\n\t"
      "movw -0x8(%%ebp), %%cx\n\t"
      "cmpw %%cx, 0x22(%%eax)\n\t"
      "jne .LFUN_000c6d90_14\n\t"
      "cmpw $4, %%bx\n\t"
      "jne .LFUN_000c6d90_14\n\t"
      "popl %%edi\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_14:\n\t"
      "movl $0x27c6d0, 0x46b6fc\n\t"
      ".LFUN_000c6d90_15:\n\t"
      "movl 0x8(%%ebp), %%edx\n\t"
      "pushl %%edx\n\t"
      ".LFUN_000c6d90_16:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_17:\n\t"
      "pushl $0x5c\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "call *%[elem]\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, -0x1c(%%ebp)\n\t"
      "call *%[c119610]\n\t"
      "movl %%eax, %%ebx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[c119610]\n\t"
      "addl $0x14, %%esp\n\t"
      "cmpl $-1, %%ebx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl %%esi, -0x10(%%ebp)\n\t"
      "je .LFUN_000c6d90_18\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .LFUN_000c6d90_18\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "movl %%eax, %%edi\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl -0x10(%%ebp), %%eax\n\t"
      "movl %%eax, 0x10(%%edi)\n\t"
      "movl $0xffffffff, 0x8(%%edi)\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl -0x14(%%ebp), %%ecx\n\t"
      "movl %%eax, 0xc(%%edi)\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw %%ax, 0x6(%%edi)\n\t"
      "movl -0x8(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "movl %%ecx, 0x8(%%esi)\n\t"
      "movl $0xffffffff, 0xc(%%esi)\n\t"
      "movw %%ax, 0x2(%%esi)\n\t"
      "movw $1, 0x6(%%esi)\n\t"
      "movw $2, 0x4(%%esi)\n\t"
      "call *%[cc7d80]\n\t"
      "addl $0x20, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c6d90_26\n\t"
      "movl -0x18(%%ebp), %%edx\n\t"
      "movl -0x1c(%%ebp), %%esi\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[c8dff0]\n\t"
      "movw -0xc(%%ebp), %%ax\n\t"
      "addl $8, %%esp\n\t"
      "movw %%di, 0x22(%%esi)\n\t"
      "popl %%edi\n\t"
      "movw %%ax, 0x20(%%esi)\n\t"
      "movl %%ebx, 0x24(%%esi)\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_18:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl $0x27bca4, 0x46b6fc\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_19:\n\t"
      "movl $0x27c69c, 0x46b6fc\n\t"
      "pushl %%edi\n\t"
      "jmp .LFUN_000c6d90_23\n\t"
      ".LFUN_000c6d90_20:\n\t"
      "cmpw $3, %%bx\n\t"
      "jne .LFUN_000c6d90_21\n\t"
      "movl $0x27c660, 0x46b6fc\n\t"
      "jmp .LFUN_000c6d90_22\n\t"
      ".LFUN_000c6d90_21:\n\t"
      "cmpw $4, %%bx\n\t"
      "movl $0x27c628, 0x46b6fc\n\t"
      "je .LFUN_000c6d90_22\n\t"
      "movl $0x27c5f4, 0x46b6fc\n\t"
      ".LFUN_000c6d90_22:\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "pushl %%eax\n\t"
      ".LFUN_000c6d90_23:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c6d90_24:\n\t"
      "movl $0x27c5f4, 0x46b6fc\n\t"
      "pushl %%esi\n\t"
      ".LFUN_000c6d90_25:\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "movl %%eax, 0x46b700\n\t"
      "addl $8, %%esp\n\t"
      ".LFUN_000c6d90_26:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc6d90_dget), [c8dcb0] "m"(bc6d90_c8dcb0), [c8df60] "m"(bc6d90_c8df60), [c18e380] "m"(bc6d90_c18e380), [cc3d50] "m"(bc6d90_cc3d50), [c1b9ad0] "m"(bc6d90_c1b9ad0), [elem] "m"(bc6d90_elem), [c119610] "m"(bc6d90_c119610), [cc7d80] "m"(bc6d90_cc7d80), [c8dff0] "m"(bc6d90_c8dff0)
      : "memory");
}
#else
#error "FUN_000c6d90: clang naked draft required"
#endif


/* 0xc71c0 — Parse an atom (non-parenthesized token) from the HS source.
 * Quoted strings: scan to closing '"', null-terminate, report unterminated.
 * Bare tokens: scan until ')', ';', whitespace, or NUL.
 * Both paths lowercase the result via csstr_tolower. */
void FUN_000c71c0(int datum_index, char **cursor)
{
  char *node;
  char *p;
  char ch;
  int16_t i;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  p = *cursor;
  if (*p == '"') {
    *cursor = p + 1;
    *(int *)(node + 0xc) = (int)(*cursor - *(char **)0x46b6e8);
    while (**cursor != '\0' && **cursor != '"')
      (*cursor)++;
    if (**cursor == '\0') {
      *(const char **)0x46b6fc = "this quoted constant is unterminated.";
      *(int *)0x46b700 = *(int *)(node + 0xc) - 1;
    }
    **cursor = '\0';
    (*cursor)++;
    csstr_tolower(*(char **)0x46b6e8 + *(int *)(node + 0xc));
    return;
  }

  *(int *)(node + 0xc) = (int)(p - *(char **)0x46b6e8);
  if (**cursor != '\0') {
    for (;;) {
      ch = **cursor;
      if (ch == ')' || ch == ';')
        break;
      for (i = 0; i < 2; i++) {
        if (ch == *(char *)(0x27bb78 + i))
          goto done;
      }
      for (i = 0; i < 2; i++) {
        if (ch == *(char *)(0x27bb7c + i))
          goto done;
      }
      (*cursor)++;
      if (**cursor == '\0')
        break;
    }
  }
done:
  csstr_tolower(*(char **)0x46b6e8 + *(int *)(node + 0xc));
}

/* 0xc72b0 — Skip whitespace and comments in the HS source buffer. Advances
 * the cursor past spaces/tabs (0x27bb78 table), newlines (0x27bb7c table),
 * single-line comments (;...newline), and block comments (;*...*;).
 * Sets error at 0x46b6fc for unterminated block comments. */
void FUN_000c72b0(char **cursor)
{
  char *p;
  char ch;
  int16_t state;
  int16_t i;

  state = 0;
  do {
    switch (state) {
    case 0:
      p = *cursor;
      ch = *p;
      if (ch == ';') {
        *cursor = p + 1;
        state = 1;
        if (p[1] == '*') {
          state = 2;
          *cursor = p + 2;
        }
        break;
      }
      for (i = 0; i < 2; i++) {
        if (ch == *(char *)(0x27bb78 + i))
          goto skip_char;
      }
      for (i = 0; i < 2; i++) {
        if (ch == *(char *)(0x27bb7c + i))
          goto skip_char;
      }
      return;

    case 1:
      p = *cursor;
      if (*p == '\0')
        return;
      for (i = 0; i < 2; i++) {
        if (*p == *(char *)(0x27bb7c + i)) {
          state = 0;
          break;
        }
      }
      goto skip_char;

    case 2:
      p = *cursor;
      if (*p == '\0') {
        *(const char **)0x46b6fc = "unterminated comment.";
        return;
      }
      if (*p == '*' && p[1] == ';') {
        state = 0;
        *cursor = p + 1;
      }
      (*cursor)++;
      break;

    default:
      display_assert("!\"unreachable\"", "c:\\halo\\SOURCE\\hs\\hs_compile.c",
                     0x46c, 1);
      system_exit(-1);
      break;
    }
    continue;
  skip_char:
    *cursor = p + 1;
  } while (state != 3);
}

bool FUN_000c73a0(int datum_index)
{
  char *node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  int16_t type = *(int16_t *)(node + 0x4);

  if (!((type >= 4 && type <= 0x30) || type == 1 || type == 0)) {
    display_assert(
      "hs_type_valid(expression->type) || expression->type==_hs_special_form"
      " || expression->type==_hs_unparsed",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x4af, 1);
    system_exit(-1);
  }

  if (type == 1) {
    *(const char **)0x46b6fc = "i expected a script or variable definition.";
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return false;
  }

  if (type == 4) {
    *(const char **)0x46b6fc =
      "the value of this expression (in a <void> slot) can never be used.";
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return false;
  }

  /* Attempt variable-reference resolution when not strictly validating or
   * when the node already carries the variable-resolved flag (bit 2). */
  if (*(uint8_t *)0x46b808 == 0 || (*(uint8_t *)(node + 0x6) & 0x4)) {
    bool result = FUN_000c5840(datum_index);
    if (result)
      return result;
  }

  type = *(int16_t *)(node + 0x4);
  if (type != 0 && *(const char **)0x46b6fc == NULL &&
      (*(uint8_t *)0x46b808 == 0 || !(*(uint8_t *)(node + 0x6) & 0x4))) {
    typedef bool (*hs_type_compile_fn_t)(int datum_index);
    hs_type_compile_fn_t fn =
      ((hs_type_compile_fn_t *)(void *)0x27bb80)[(int)type];
    if (fn == NULL) {
      crt_sprintf((char *)0x46b704,
                  "expressions of type %s are currently unsupported.",
                  ((const char **)(void *)0x2f14a8)[(int)type]);
      *(const char **)0x46b6fc = (const char *)0x46b704;
      *(int *)0x46b700 = *(int *)(node + 0xc);
      return false;
    }
    return fn(datum_index);
  }

  return false;
}

/* FUN_000c74c0 (0xc74c0) — XBE naked draft (batch 69). */
#if defined(__clang__)
static void *(*const bc74c0_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bc74c0_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bc74c0_exitfn)(int) = system_exit;
static int (*const bc74c0_c8dcb0)(const char *s1, const char *s2) = csstrcmp;
static bool (*const bc74c0_cc6b00)(int datum_index) = FUN_000c6b00;
static bool (*const bc74c0_cc6d90)(int datum_index) = FUN_000c6d90;
static void (*const bc74c0_cc5960)(int datum_index) = FUN_000c5960;
static scenario_t * (*const bc74c0_c18e380)(void) = global_scenario_get;
static void *(*const bc74c0_elem)(void *, int, int) = tag_block_get_element;
static bool (*const bc74c0_ccb070)(int16_t actual_type, int16_t desired_type) = hs_types_compatible;
static int (*const bc74c0_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static void * (*const bc74c0_cc3d00)(int16_t function_index) = hs_function_table_get;

__attribute__((naked, noinline))
bool FUN_000c74c0(int datum_index __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movb $0, -0x1(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, %%esi\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%edi\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl %%eax, -0x8(%%ebp)\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpw $4, %%ax\n\t"
      "jl .LFUN_000c74c0_1\n\t"
      "cmpw $0x31, %%ax\n\t"
      "jl .LFUN_000c74c0_2\n\t"
      ".LFUN_000c74c0_1:\n\t"
      "cmpw $1, %%ax\n\t"
      "je .LFUN_000c74c0_2\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000c74c0_2\n\t"
      "pushl $1\n\t"
      "pushl $0x534\n\t"
      "pushl $0x27bd0c\n\t"
      "pushl $0x27c8c0\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000c74c0_2:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movb 0x6(%%eax), %%cl\n\t"
      "addl $8, %%esp\n\t"
      "testb $1, %%cl\n\t"
      "je .LFUN_000c74c0_17\n\t"
      "cmpw $1, 0x4(%%esi)\n\t"
      "jne .LFUN_000c74c0_5\n\t"
      "movl -0x8(%%ebp), %%esi\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl 0x46b6e8, %%ecx\n\t"
      "pushl $0x27b978\n\t"
      "pushl %%ecx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c74c0_3\n\t"
      "pushl %%ebx\n\t"
      "call *%[cc6b00]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_3:\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "addl 0x46b6e8, %%edx\n\t"
      "pushl $0x25bb40\n\t"
      "pushl %%edx\n\t"
      "call *%[c8dcb0]\n\t"
      "addl $8, %%esp\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c74c0_4\n\t"
      "pushl %%ebx\n\t"
      "call *%[cc6d90]\n\t"
      "addl $4, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_4:\n\t"
      "movl $0x27caa4, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x46b700\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_5:\n\t"
      "movl %%ebx, %%eax\n\t"
      "call *%[cc5960]\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .LFUN_000c74c0_16\n\t"
      "testb $2, 0x6(%%esi)\n\t"
      "je .LFUN_000c74c0_9\n\t"
      "movswl %%ax, %%ecx\n\t"
      "pushl $0x5c\n\t"
      "pushl %%ecx\n\t"
      "call *%[c18e380]\n\t"
      "addl $0x49c, %%eax\n\t"
      "pushl %%eax\n\t"
      "call *%[elem]\n\t"
      "movl %%eax, %%edi\n\t"
      "movw 0x20(%%edi), %%ax\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000c74c0_6\n\t"
      "cmpw $4, %%ax\n\t"
      "je .LFUN_000c74c0_6\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl $0x27ca84, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_6:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000c74c0_7\n\t"
      "pushl %%eax\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x22(%%edi), %%ax\n\t"
      "pushl %%eax\n\t"
      "call *%[ccb070]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000c74c0_7\n\t"
      "movswl 0x22(%%edi), %%ecx\n\t"
      "movswl 0x4(%%esi), %%eax\n\t"
      "movl 0x2f14a8(,%%ecx,4), %%edx\n\t"
      "movl 0x2f14a8(,%%eax,4), %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl $0x27ca54\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "addl $0x10, %%esp\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_7:\n\t"
      "cmpw $0, 0x4(%%esi)\n\t"
      "jne .LFUN_000c74c0_8\n\t"
      "movw 0x22(%%edi), %%ax\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      ".LFUN_000c74c0_8:\n\t"
      "movb $1, -0x1(%%ebp)\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_9:\n\t"
      "pushl %%eax\n\t"
      "call *%[cc3d00]\n\t"
      "movl %%eax, %%edi\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "addl $4, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .LFUN_000c74c0_10\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw (%%edi), %%cx\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[ccb070]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .LFUN_000c74c0_10\n\t"
      "movswl (%%edi), %%edx\n\t"
      "movswl 0x4(%%esi), %%ecx\n\t"
      "movl 0x2f14a8(,%%edx,4), %%eax\n\t"
      "movl 0x2f14a8(,%%ecx,4), %%edx\n\t"
      "pushl %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl $0x27ca20\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "addl $0x10, %%esp\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%eax\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x46b700\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_10:\n\t"
      "movb 0x46b806, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c74c0_12\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "cmpw $0x13, %%ax\n\t"
      "je .LFUN_000c74c0_11\n\t"
      "cmpw $0x14, %%ax\n\t"
      "jne .LFUN_000c74c0_12\n\t"
      ".LFUN_000c74c0_11:\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl $0x27c9f8, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_12:\n\t"
      "movb 0x46b807, %%al\n\t"
      "testb %%al, %%al\n\t"
      "je .LFUN_000c74c0_13\n\t"
      "cmpw $4, 0x2(%%esi)\n\t"
      "jne .LFUN_000c74c0_13\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl $0x27c9b8, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_13:\n\t"
      "cmpw $0, 0x4(%%esi)\n\t"
      "jne .LFUN_000c74c0_14\n\t"
      "movw (%%edi), %%ax\n\t"
      "cmpw $3, %%ax\n\t"
      "je .LFUN_000c74c0_14\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      ".LFUN_000c74c0_14:\n\t"
      "movl 0x8(%%edi), %%eax\n\t"
      "testl %%eax, %%eax\n\t"
      "jne .LFUN_000c74c0_15\n\t"
      "pushl $1\n\t"
      "pushl $0x58c\n\t"
      "pushl $0x27bd0c\n\t"
      "pushl $0x27c9a8\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".LFUN_000c74c0_15:\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x2(%%esi), %%ax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *0x8(%%edi)\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movb %%al, -0x1(%%ebp)\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_16:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "movl $0x27c978, 0x46b6fc\n\t"
      "movl 0xc(%%ecx), %%edx\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".LFUN_000c74c0_17:\n\t"
      "cmpw $1, 0x4(%%esi)\n\t"
      "movl $0x27c960, %%eax\n\t"
      "je .LFUN_000c74c0_18\n\t"
      "movl $0x27c950, %%eax\n\t"
      ".LFUN_000c74c0_18:\n\t"
      "pushl %%eax\n\t"
      "pushl $0x27c928\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "addl $0xc, %%esp\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "movb -0x1(%%ebp), %%al\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "popl %%esi\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc74c0_dget), [assert] "m"(bc74c0_assert), [exitfn] "m"(bc74c0_exitfn), [c8dcb0] "m"(bc74c0_c8dcb0), [cc6b00] "m"(bc74c0_cc6b00), [cc6d90] "m"(bc74c0_cc6d90), [cc5960] "m"(bc74c0_cc5960), [c18e380] "m"(bc74c0_c18e380), [elem] "m"(bc74c0_elem), [ccb070] "m"(bc74c0_ccb070), [c1d90f0] "m"(bc74c0_c1d90f0), [cc3d00] "m"(bc74c0_cc3d00)
      : "memory");
}
#else
#error "FUN_000c74c0: clang naked draft required"
#endif


/* Mark an HS syntax node (and its children) as needing recompilation
 * (0xc7b10). Sets dirty flag (bit 3) on the node.
 *
 * If the node is a non-function expression (bit 0 of flags == 0), recursively
 * marks all children in the sibling linked list (node+0x10 = first child,
 * node+0x8 = next sibling).
 *
 * If the node is a function expression (bit 0 of flags == 1):
 *   - If type == 2 (call expression): re-interns the function name string
 *     into the compile-time string buffer and stores the new offset in
 *     node+0xc. If node+0xc was -1, looks up the function descriptor via
 *     hs_function_table_get and interns the name at descriptor+4. Otherwise
 *     re-interns the existing string at (node+0xc + compiled_source_base).
 *   - If type != 2 but flag bit 2 is set or type >= 9: same re-intern of
 *     node+0xc + compiled_source_base into node+0xc.
 */
void FUN_000c7b10(int datum_index)
{
  char *node;
  char *node2;
  int16_t type;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  *(uint8_t *)(node + 0x6) |= 0x8;

  /* Re-read the node flags to test bit 0 (function vs expression). */
  node2 = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (!(*(uint8_t *)(node2 + 0x6) & 0x1)) {
    /* Non-function node: recurse into children. */
    int child = *(int *)(node + 0x10);
    while (child != -1) {
      char *child_node;
      FUN_000c7b10(child);
      child_node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
      child = *(int *)(child_node + 0x8);
    }
    return;
  }

  /* Function node: re-intern the string constant for recompilation. */
  type = *(int16_t *)(node + 0x4);
  if (type == 2) {
    int str_offset = *(int *)(node + 0xc);
    char *str_ptr;
    if (str_offset == -1) {
      /* No string interned yet: look up function name from descriptor. */
      void *fn_desc =
        hs_function_table_get((int16_t) * (uint16_t *)(node + 0x2));
      str_ptr = *(char **)((char *)fn_desc + 0x4);
    } else {
      str_ptr = (char *)(str_offset + *(int *)0x46b6e8);
    }
    *(int *)(node + 0xc) = FUN_000c6a70(str_ptr);
    return;
  }

  if ((*(uint8_t *)(node + 0x6) & 0x4) || type >= 9) {
    char *str_ptr = (char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8);
    *(int *)(node + 0xc) = FUN_000c6a70(str_ptr);
  }
}

/* 0xc7be0 — Allocate and initialize a new HS syntax node, then dispatch to
 * the atom parser (FUN_000c71c0) or parenthesized expression parser
 * (FUN_000c7ca0) depending on whether the cursor points to '('. */
int FUN_000c7be0(char **cursor)
{
  int datum_index;
  char *node;

  datum_index = data_new_at_index(*(data_t **)0x5aa6c8);

  if (*(char **)0x46b6fc != 0) {
    display_assert("!hs_compile_globals.error",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x39e, 1);
    system_exit(-1);
  }

  if (datum_index == -1) {
    *(const char **)0x46b6fc = "i couldn't allocate a syntax node.";
    return -1;
  }

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  *(int16_t *)(node + 0x6) = 0;
  *(int16_t *)(node + 0x4) = 0;
  *(int16_t *)(node + 0x2) = -1;
  *(int *)(node + 0x8) = -1;
  *(uint16_t *)(node + 0x6) = (uint16_t)(**cursor != '(');

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(uint8_t *)(node + 0x6) & 1) {
    FUN_000c71c0(datum_index, cursor);
    return datum_index;
  }

  FUN_000c7ca0(cursor, datum_index);
  return datum_index;
}

/* 0xc7ca0 — Parse a parenthesized HS expression. Advances cursor past '(',
 * then loops: skip whitespace (null-terminating gaps), parse sub-expressions
 * via FUN_000c7be0, and chain them via each node's next_node field (+0x8).
 * Stops at ')' (null-terminates it) or NUL (unmatched paren error).
 * Sets "this expression is empty." if no children were parsed. */
void FUN_000c7ca0(char **cursor, int datum_index)
{
  char *node;
  char *pre_ws;
  int *link_ptr;
  int child_index;
  char *child_node;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  *(int *)(node + 0xc) = (int)(*cursor - *(char **)0x46b6e8);
  (*cursor)++;
  link_ptr = (int *)(node + 0x10);

  if (*(char **)0x46b6fc == 0) {
    do {
      pre_ws = *cursor;
      FUN_000c72b0(cursor);
      if (*cursor != pre_ws)
        *pre_ws = '\0';

      if (**cursor == '\0') {
        *(const char **)0x46b6fc = "this left parenthesis is unmatched.";
        *(int *)0x46b700 = *(int *)(node + 0xc);
        break;
      }

      if (**cursor == ')') {
        **cursor = '\0';
        (*cursor)++;
        break;
      }

      child_index = FUN_000c7be0(cursor);
      *link_ptr = child_index;
      if (child_index != -1) {
        child_node = (char *)datum_get(*(data_t **)0x5aa6c8, child_index);
        link_ptr = (int *)(child_node + 0x8);
      }
    } while (*(char **)0x46b6fc == 0);
  }

  if (link_ptr == (int *)(node + 0x10) && *(char **)0x46b6fc == 0) {
    *(const char **)0x46b6fc = "this expression is empty.";
    *(int *)0x46b700 = *(int *)(node + 0xc);
  }
}

/* Type-check an HS syntax node (0xc7d80).
 * If the node is untyped (type==0), sets its type to check_type and
 * dispatches to FUN_000c73a0 (function-call nodes) or FUN_000c74c0
 * (expression nodes) based on the node's flag bit 0. Returns true
 * if the node was already typed. */
bool hs_type_check(int datum_index, int16_t check_type)
{
  char *node;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);

  if (*(int *)0x46b6fc != 0) {
    display_assert("!hs_compile_globals.error",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x48e, 1);
    system_exit(-1);
  }

  if (!((check_type >= 4 && check_type <= 0x30) || check_type == 1 ||
        check_type == 0)) {
    display_assert(
      "hs_type_valid(expected_type) || expected_type==_hs_special_form"
      " || expected_type==_hs_unparsed",
      "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x491, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 4) != 0)
    return true;

  *(int16_t *)(node + 4) = check_type;

  {
    char *node2 = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
    if (*(uint8_t *)(node2 + 6) & 1) {
      *(int16_t *)(node + 2) = check_type;
      return FUN_000c73a0(datum_index);
    }
  }

  return FUN_000c74c0(datum_index);
}

int FUN_000c5310(int parent_handle, int sibling_handle);
int16_t FUN_0018ea50(void *param_1, const char *name);

/* FUN_000c6a30 (0xc6a30) — readable C lift: find string index in name table. */
int16_t FUN_000c6a30(const char *str, const char **names /*@<ebx>*/, int16_t count /*@<di>*/)
{
  int16_t i;

  for (i = 0; i < count; i++) {
    if (csstrcmp(str, names[i]) == 0)
      return i;
  }
  return -1;
}

/* hs_parse_enum (0xc5f60) — readable C lift (restored pre-naked). */
bool hs_parse_enum(int datum_index)
{
  char *node;
  int16_t type;
  int16_t *enum_hdr;
  const char **names;
  int16_t count;
  int16_t i;
  char *str;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  type = *(int16_t *)(node + 0x4);

  if (type < 0x20 || type > 0x24) {
    display_assert("HS_TYPE_IS_ENUM(expression->type)",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x6bc, 1);
    system_exit(-1);
  }

  if (*(int16_t *)(node + 0x2) != type) {
    display_assert("expression->constant_type==expression->type",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x6bd, 1);
    system_exit(-1);
  }

  enum_hdr = (int16_t *)(0x2726b4 + (int)type * 8);
  count = *enum_hdr;
  if (count == 0) {
    display_assert("enum->count>0", "c:\\halo\\SOURCE\\hs\\hs_compile.c",
                   0x6be, 1);
    system_exit(-1);
  }

  names = *(const char ***)((char *)enum_hdr + 4);
  str = (char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8);

  i = 0;
  while (i < count) {
    if (crt_stricmp(str, names[(int)i]) == 0) {
      *(int16_t *)(node + 0x10) = i;
      return true;
    }
    i++;
  }

  crt_sprintf((char *)0x46b704, "this is not a valid %s",
              ((const char **)0x2f14a8)[(int)type]);
  if (count > 1) {
    FUN_0008dc30((char *)0x46b704, (const char *)0x27c028);
    i = 0;
    while (i < count - 1) {
      FUN_0008dc30((char *)0x46b704, names[(int)i]);
      FUN_0008dc30((char *)0x46b704, (const char *)0x27c024);
      i++;
    }
    if (count > 1)
      FUN_0008dc30((char *)0x46b704, (const char *)0x27c020);
    FUN_0008dc30((char *)0x46b704, (const char *)0x27c028);
    FUN_0008dc30((char *)0x46b704, names[(int)(count - 1)]);
    FUN_0008dc30((char *)0x46b704, (const char *)0x27c01c);
  }

  *(const char **)0x46b6fc = (const char *)0x46b704;
  *(int *)0x46b700 = *(int *)(node + 0xc);
  *(int16_t *)(node + 0x10) = i;
  return false;
}


/* FUN_000c66d0 (0xc66d0) — readable C lift: resolve HS enum script name. */
bool FUN_000c66d0(int datum_index)
{
  char *node;
  int16_t type;
  int16_t enum_idx;
  char *elem;
  int mask;
  int bit;
  char ok;

  ok = 0;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  type = *(int16_t *)(node + 4);
  if (type < 0x2b || type > 0x30) {
    display_assert((const char *)0x27c3f4, (const char *)0x27bd0c, 0x771, 1);
    system_exit(-1);
  }
  enum_idx = FUN_0018ea50(
      global_scenario_get(),
      (const char *)(*(int *)(node + 0xc) + *(int *)0x46b6e8));
  if (enum_idx == -1) {
    *(int *)0x46b6fc = 0x27c384;
    *(int *)0x46b700 = *(int *)(node + 0xc);
    return ok;
  }
  elem = (char *)tag_block_get_element(
      (char *)global_scenario_get() + 0x204, (int)enum_idx, 0x24);
  if (*(int16_t *)(elem + 0x20) == -1) {
    display_assert((const char *)0x27c3cc, (const char *)0x27bd0c, 0x77a, 1);
    system_exit(-1);
  }
  mask = (int)*(int16_t *)(0x26f2ca + (int)type * 2);
  bit = 1 << (*(unsigned char *)(elem + 0x20));
  if ((bit & mask) != 0) {
    *(int16_t *)(node + 0x10) = enum_idx;
    return 1;
  }
  crt_sprintf((char *)0x46b704, (const char *)0x27c3a8,
              *(const char **)(0x2f14a8 + (int)type * 4));
  *(int *)0x46b6fc = 0x46b704;
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return 0;
}


/* FUN_000c6940 (0xc6940) — readable C lift. */
bool FUN_000c6940(int datum_index)
{
  char *node;
  void *scenario;
  void *tag;

  node = (char *)datum_get(*(data_t **)0x5aa6c8, datum_index);
  if (*(int16_t *)(node + 4) != 0x16) {
    display_assert((const char *)0x27c480, (const char *)0x27bd0c, 0x7bf, true);
    system_exit(-1);
  }
  scenario = global_scenario_get();
  if (*(int *)((char *)scenario + 0x5a0) == -1)
    return false;
  scenario = global_scenario_get();
  tag = tag_get(0x686d7420, *(int *)((char *)scenario + 0x5a0));
  return FUN_000c6130(datum_index, (char *)tag + 0x20, 0x40, 0);
}



/* hs_macro_function_parse (0xc7e50) — readable C lift from XBE leaf. */
char hs_macro_function_parse(int16_t function_index, int root_datum)
{
  char *fn;
  char *node;
  int child;
  int16_t i;
  int16_t nparams;
  int16_t ftype;
  char ok;
  int16_t check_type;

  ok = 1;
  fn = (char *)hs_function_table_get(function_index);
  node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  child = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(node + 0x10)) + 8);
  ftype = *(int16_t *)fn;
  if (ftype < 4 || ftype >= 0x31) {
    display_assert((const char *)0x27ccc0, (const char *)0x27bd0c, 0x819, true);
    system_exit(-1);
  }
  nparams = *(int16_t *)(fn + 0x18);
  for (i = 0; i < nparams && child != -1; i++) {
    check_type = *(int16_t *)(fn + 0x1a + (int)i * 2);
    if (!hs_type_check(child, check_type)) {
      ok = 0;
      break;
    }
    child = *(int *)((char *)datum_get(*(data_t **)0x5aa6c8, child) + 8);
  }
  if (!ok)
    return 0;
  if (i == nparams && child == -1)
    return 1;
  crt_sprintf((char *)0x46b704, (const char *)0x27cc90, *(int *)(fn + 4), (int)nparams);
  *(void **)0x46b6fc = (void *)0x46b704;
  node = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  *(int *)0x46b700 = *(int *)(node + 0xc);
  return 0;
}


/* hs_parse_begin (0xc7f70) — XBE naked draft (batch 119). */
#if defined(__clang__)
static void *(*const bc7f70_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static void (*const bc7f70_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bc7f70_exitfn)(int) = system_exit;
static bool (*const bc7f70_cc7d80)(int datum_index, int16_t check_type) = hs_type_check;
static void * (*const bc7f70_cc3d00)(int16_t function_index) = hs_function_table_get;
static int (*const bc7f70_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;

__attribute__((naked, noinline))
char hs_parse_begin(int16_t function_index __attribute__((unused)), int root_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movb $1, %%bl\n\t"
      "call *%[dget]\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%edx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "movl 0x8(%%ebp), %%eax\n\t"
      "addl $0x18, %%esp\n\t"
      "testw %%ax, %%ax\n\t"
      "je .Lhs_parse_begin_1\n\t"
      "cmpw $1, %%ax\n\t"
      "je .Lhs_parse_begin_1\n\t"
      "pushl $1\n\t"
      "pushl $0x15\n\t"
      "pushl $0x27cdc0\n\t"
      "pushl $0x27cd70\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhs_parse_begin_1:\n\t"
      "movl $0, -0x8(%%ebp)\n\t"
      "jmp .Lhs_parse_begin_3\n\t"
      ".Lhs_parse_begin_2:\n\t"
      "movl 0xc(%%ebp), %%edi\n\t"
      ".Lhs_parse_begin_3:\n\t"
      "cmpl $-1, %%esi\n\t"
      "je .Lhs_parse_begin_10\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "addl $8, %%esp\n\t"
      "cmpw $0, 0x8(%%ebp)\n\t"
      "jne .Lhs_parse_begin_6\n\t"
      "cmpl $-1, %%edi\n\t"
      "jne .Lhs_parse_begin_4\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "movw 0x4(%%edx), %%ax\n\t"
      "jmp .Lhs_parse_begin_5\n\t"
      ".Lhs_parse_begin_4:\n\t"
      "movl $4, %%eax\n\t"
      ".Lhs_parse_begin_5:\n\t"
      "pushl %%eax\n\t"
      "pushl %%esi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movb %%al, %%bl\n\t"
      "jne .Lhs_parse_begin_8\n\t"
      "jmp .Lhs_parse_begin_7\n\t"
      ".Lhs_parse_begin_6:\n\t"
      "movl -0x4(%%ebp), %%ecx\n\t"
      "xorl %%edx, %%edx\n\t"
      "movw 0x4(%%ecx), %%dx\n\t"
      "pushl %%edx\n\t"
      "pushl %%esi\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "movb %%al, %%bl\n\t"
      ".Lhs_parse_begin_7:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $0, 0x4(%%eax)\n\t"
      "jne .Lhs_parse_begin_8\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lhs_parse_begin_8\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movw 0x4(%%eax), %%dx\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      ".Lhs_parse_begin_8:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "incl %%ecx\n\t"
      "testb %%bl, %%bl\n\t"
      "movl %%edi, %%esi\n\t"
      "movl %%ecx, -0x8(%%ebp)\n\t"
      "jne .Lhs_parse_begin_2\n\t"
      ".Lhs_parse_begin_9:\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movb %%bl, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_begin_10:\n\t"
      "testb %%bl, %%bl\n\t"
      "je .Lhs_parse_begin_9\n\t"
      "movl -0x8(%%ebp), %%eax\n\t"
      "cmpw $1, %%ax\n\t"
      "jge .Lhs_parse_begin_11\n\t"
      "movl 0x8(%%ebp), %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cc3d00]\n\t"
      "movl 0x4(%%eax), %%edx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x27cd34\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "addl $0x18, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_begin_11:\n\t"
      "cmpw $0x20, %%ax\n\t"
      "jle .Lhs_parse_begin_9\n\t"
      "cmpw $1, 0x8(%%ebp)\n\t"
      "jne .Lhs_parse_begin_9\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%edi\n\t"
      "pushl %%edx\n\t"
      "movl $0x27cce8, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "popl %%esi\n\t"
      "movl %%eax, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc7f70_dget), [assert] "m"(bc7f70_assert), [exitfn] "m"(bc7f70_exitfn), [cc7d80] "m"(bc7f70_cc7d80), [cc3d00] "m"(bc7f70_cc3d00), [c1d90f0] "m"(bc7f70_c1d90f0)
      : "memory");
}
#else
#error "hs_parse_begin: clang naked draft required"
#endif


/* hs_parse_if (0xc8120) — readable C lift (restored pre-naked). */
char hs_parse_if(int16_t function_index, int root_datum)
{
  char *expr;
  char *head;
  int cond;
  int then_arg;
  int else_arg;
  char result;

  if (function_index != 2) {
    display_assert("function_index==_hs_function_if",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x5b, 1);
    system_exit(-1);
  }

  result = 0;
  expr = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  expr = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  head = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(expr + 0x10));
  cond = *(int *)(head + 0x8);
  if (cond == -1)
    goto too_many;

  head = (char *)datum_get(*(data_t **)0x5aa6c8, cond);
  then_arg = *(int *)(head + 0x8);
  if (then_arg == -1)
    goto too_many;

  head = (char *)datum_get(*(data_t **)0x5aa6c8, then_arg);
  else_arg = *(int *)(head + 0x8);
  if (else_arg != -1) {
    head = (char *)datum_get(*(data_t **)0x5aa6c8, else_arg);
    if (*(int *)(head + 0x8) != -1)
      goto too_many;
  }

  if (!hs_type_check(cond, 5))
    return result;

  if (hs_type_check(then_arg, *(int16_t *)(expr + 0x4))) {
    if (*(int16_t *)(expr + 0x4) == 0) {
      head = (char *)datum_get(*(data_t **)0x5aa6c8, then_arg);
      *(int16_t *)(expr + 0x4) = *(int16_t *)(head + 0x4);
    }
    if (else_arg == -1 || hs_type_check(else_arg, *(int16_t *)(expr + 0x4)))
      return 1;
    return result;
  }

  if (*(int *)0x46b6fc != 0 || *(int16_t *)(expr + 0x4) != 0 || else_arg == -1)
    return result;

  if (!hs_type_check(else_arg, 0))
    return result;

  head = (char *)datum_get(*(data_t **)0x5aa6c8, else_arg);
  *(int16_t *)(expr + 0x4) = *(int16_t *)(head + 0x4);
  result = hs_type_check(then_arg, *(int16_t *)(expr + 0x4));
  return result;

too_many:
  expr = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  *(const char **)0x46b6fc = (const char *)0x27cdf0;
  *(int *)0x46b700 = *(int *)(expr + 0xc);
  return result;
}


/* hs_parse_cond (0xc82e0) — readable C lift: fold cond child into root node. */
char hs_parse_cond(int16_t function_index, int root_datum)
{
  char *root;
  char *child_node;
  char *parent;
  int child;
  short saved_type;
  short saved_flags;
  int i;
  (void)function_index;
  root = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  parent = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(root + 0x10));
  child = FUN_000c5310(root_datum, *(int *)(parent + 8));
  if (child == -1)
    return 0;
  root = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  child_node = (char *)datum_get(*(data_t **)0x5aa6c8, child);
  saved_type = *(short *)(root + 4);
  saved_flags = *(short *)root;
  *(int *)(child_node + 8) = *(int *)(root + 8);
  /* rep movsd 5 dwords from child_node -> root */
  for (i = 0; i < 5; i++)
    ((int *)root)[i] = ((int *)child_node)[i];
  *(short *)root = saved_flags;
  return hs_type_check(root_datum, saved_type) ? 1 : 0;
}
/* hs_parse_set (0xc8380) — XBE naked draft (batch 114). */
#if defined(__clang__)
static void *(*const bc8380_dget)(void *, int) = (void *(*)(void *, int))datum_get;
static int16_t (*const bc8380_cc3ee0)(const char *name) = hs_find_global_by_name;
static int16_t (*const bc8380_cc3e60)(uint16_t script_ref) = hs_global_get_type;
static bool (*const bc8380_ccb070)(int16_t actual_type, int16_t desired_type) = hs_types_compatible;
static int (*const bc8380_c1d90f0)(char *buffer, const char *format, ...) = crt_sprintf;
static bool (*const bc8380_cc5840)(int datum_index) = FUN_000c5840;
static void (*const bc8380_assert)(const char *, const char *, int, bool) = display_assert;
static void (*const bc8380_exitfn)(int) = system_exit;
static bool (*const bc8380_cc7d80)(int datum_index, int16_t check_type) = hs_type_check;

__attribute__((naked, noinline))
char hs_parse_set(int16_t function_index __attribute__((unused)), int root_datum __attribute__((unused)))
{
  __asm__ volatile(
      "pushl %%ebp\n\t"
      "movl %%esp, %%ebp\n\t"
      "subl $8, %%esp\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "movl 0xc(%%ebp), %%ebx\n\t"
      "pushl %%edi\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x10(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%edi\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "addl $0x18, %%esp\n\t"
      "cmpl $-1, %%edi\n\t"
      "movl %%eax, -0x4(%%ebp)\n\t"
      "je .Lhs_parse_set_8\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edi\n\t"
      "pushl %%ecx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%esi\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%esi\n\t"
      "movl %%esi, -0x8(%%ebp)\n\t"
      "je .Lhs_parse_set_7\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%esi\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "addl $8, %%esp\n\t"
      "cmpl $-1, %%ecx\n\t"
      "jne .Lhs_parse_set_6\n\t"
      "pushl %%edi\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movl 0x46b6e8, %%edx\n\t"
      "movl %%eax, %%esi\n\t"
      "movl 0xc(%%esi), %%ecx\n\t"
      "addl %%edx, %%ecx\n\t"
      "pushl %%ecx\n\t"
      "call *%[cc3ee0]\n\t"
      "addl $0xc, %%esp\n\t"
      "cmpw $0xffff, %%ax\n\t"
      "je .Lhs_parse_set_4\n\t"
      "pushl %%eax\n\t"
      "call *%[cc3e60]\n\t"
      "movl -0x4(%%ebp), %%edx\n\t"
      "xorl %%ecx, %%ecx\n\t"
      "movw %%ax, 0x4(%%esi)\n\t"
      "movw 0x4(%%edx), %%cx\n\t"
      "addl $4, %%esp\n\t"
      "testw %%cx, %%cx\n\t"
      "je .Lhs_parse_set_1\n\t"
      "pushl %%ecx\n\t"
      "pushl %%eax\n\t"
      "call *%[ccb070]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lhs_parse_set_1\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "call *%[dget]\n\t"
      "movswl 0x4(%%eax), %%ecx\n\t"
      "movswl 0x4(%%esi), %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "pushl $0x27cee0\n\t"
      "pushl $0x46b704\n\t"
      "call *%[c1d90f0]\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl $0x46b704, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "addl $0x20, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_set_1:\n\t"
      "movl %%edi, %%eax\n\t"
      "call *%[cc5840]\n\t"
      "testb %%al, %%al\n\t"
      "jne .Lhs_parse_set_2\n\t"
      "pushl $1\n\t"
      "pushl $0x126\n\t"
      "pushl $0x27cdc0\n\t"
      "pushl $0x27ced4\n\t"
      "call *%[assert]\n\t"
      "pushl $-1\n\t"
      "call *%[exitfn]\n\t"
      "addl $0x14, %%esp\n\t"
      ".Lhs_parse_set_2:\n\t"
      "movl -0x4(%%ebp), %%eax\n\t"
      "cmpw $0, 0x4(%%eax)\n\t"
      "jne .Lhs_parse_set_3\n\t"
      "movw 0x4(%%esi), %%dx\n\t"
      "movw %%dx, 0x4(%%eax)\n\t"
      ".Lhs_parse_set_3:\n\t"
      "movl -0x8(%%ebp), %%ecx\n\t"
      "xorl %%eax, %%eax\n\t"
      "movw 0x4(%%esi), %%ax\n\t"
      "pushl %%eax\n\t"
      "pushl %%ecx\n\t"
      "call *%[cc7d80]\n\t"
      "addl $8, %%esp\n\t"
      "testb %%al, %%al\n\t"
      "je .Lhs_parse_set_5\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movb $1, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_set_4:\n\t"
      "movl $0x27ceac, 0x46b6fc\n\t"
      "movl 0xc(%%esi), %%edx\n\t"
      "movl %%edx, 0x46b700\n\t"
      ".Lhs_parse_set_5:\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_set_6:\n\t"
      "pushl %%esi\n\t"
      "pushl %%eax\n\t"
      "movl $0x27ce8c, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0x8(%%eax), %%ecx\n\t"
      "movl 0x5aa6c8, %%edx\n\t"
      "pushl %%ecx\n\t"
      "pushl %%edx\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%eax\n\t"
      "addl $0x10, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%eax, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_set_7:\n\t"
      "movl 0x5aa6c8, %%ecx\n\t"
      "pushl %%ebx\n\t"
      "pushl %%ecx\n\t"
      "movl $0x27ce6c, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%edx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%esi\n\t"
      "popl %%edi\n\t"
      "movl %%edx, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      ".Lhs_parse_set_8:\n\t"
      "movl 0x5aa6c8, %%eax\n\t"
      "pushl %%ebx\n\t"
      "pushl %%eax\n\t"
      "movl $0x27ce40, 0x46b6fc\n\t"
      "call *%[dget]\n\t"
      "movl 0xc(%%eax), %%ecx\n\t"
      "addl $8, %%esp\n\t"
      "popl %%edi\n\t"
      "movl %%ecx, 0x46b700\n\t"
      "xorb %%al, %%al\n\t"
      "popl %%ebx\n\t"
      "movl %%ebp, %%esp\n\t"
      "popl %%ebp\n\t"
      "ret\n\t"
      :
      : [dget] "m"(bc8380_dget), [cc3ee0] "m"(bc8380_cc3ee0), [cc3e60] "m"(bc8380_cc3e60), [ccb070] "m"(bc8380_ccb070), [c1d90f0] "m"(bc8380_c1d90f0), [cc5840] "m"(bc8380_cc5840), [assert] "m"(bc8380_assert), [exitfn] "m"(bc8380_exitfn), [cc7d80] "m"(bc8380_cc7d80)
      : "memory");
}
#else
#error "hs_parse_set: clang naked draft required"
#endif


/* FUN_000c85b0 (0xc85b0) — readable C lift (restored pre-naked). */
char FUN_000c85b0(int16_t function_index, int root_datum)
{
  char *syntax;
  char *link_node;
  char *node;
  int link;
  int depth;
  char ok;
  void *entry;
  const char *name;

  if (function_index != 5 && function_index != 6) {
    display_assert("function_index==_hs_function_and || "
                   "function_index==_hs_function_or",
                   "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x15d, 1);
    system_exit(-1);
  }

  syntax = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  node = (char *)datum_get(*(data_t **)0x5aa6c8, *(int *)(syntax + 0x10));
  link = *(int *)(node + 0x8);
  ok = 1;
  depth = 0;

  while (link != -1) {
    if (*(int *)0x46b6fc != 0) {
      display_assert("!hs_compile_globals.error",
                     "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x48e, 1);
      system_exit(-1);
    }

    link_node = (char *)datum_get(*(data_t **)0x5aa6c8, link);
    if (*(int16_t *)(link_node + 0x4) == 0) {
      *(int16_t *)(link_node + 0x4) = 5;
      node = (char *)datum_get(*(data_t **)0x5aa6c8, link);
      if ((*(uint8_t *)(node + 0x6) & 1) != 0) {
        *(int16_t *)(link_node + 0x2) = 5;
        ok = FUN_000c73a0(link);
      } else {
        ok = FUN_000c74c0(link);
      }
    }

    node = (char *)datum_get(*(data_t **)0x5aa6c8, link);
    link = *(int *)(node + 0x8);
    depth++;
    if (!ok)
      break;
  }

  if (ok)
    return 1;

  if (depth >= 2)
    return ok;

  entry = hs_function_table_get(function_index);
  name = *(const char **)((char *)entry + 4);
  crt_sprintf((char *)0x46b704, "too few arguments to function `%s`", name);
  syntax = (char *)datum_get(*(data_t **)0x5aa6c8, root_datum);
  *(const char **)0x46b6fc = (const char *)0x46b704;
  *(int *)0x46b700 = *(int *)(syntax + 0xc);
  return 0;
}


/* Recompile all HS scripts and globals in the current scenario (0xc93f0).
 * First resizes the scenario's HS string data block (scenario+0x488) to the
 * current source_size, then initialises the compile globals for a new pass.
 * Iterates every syntax node in the scripts block (scenario+0x4a8) and the
 * globals block (scenario+0x49c), marking each for recompilation via
 * FUN_000c7b10.  Calls hs_scripts_dispose() to release the compiled state,
 * then resizes the string block down to (accumulated_string_size + 0x400).
 * Both resize failures share the same assert/exit path (single error block in
 * binary at 0xc94c2). */
void hs_compile_recompile_scripts(void)
{
  scenario_t *scenario = global_scenario_get();

  if (tag_data_resize((void *)((char *)scenario + 0x488), *(int *)0x46b6e4)) {
    /* Initialise compile globals for the recompilation pass. */
    *(int *)0x46b6ec = *(int *)((char *)scenario + 0x494);
    *(int *)0x46b6f0 = 0;
    *(int *)0x46b6f4 = *(int *)0x46b6e4;

    /* Mark every node in the scripts block (scenario+0x4a8) dirty.
     * global_scenario_get() is called each iteration to get a fresh
     * scenario pointer for the block argument (matches binary). */
    {
      int16_t i = 0;
      while ((int)i < *(int *)((char *)scenario + 0x4a8)) {
        void *elem = tag_block_get_element(
          (void *)((char *)global_scenario_get() + 0x4a8), (int)i, 0x5c);
        FUN_000c7b10(*(int *)((char *)elem + 0x28));
        i++;
      }
    }

    /* Mark every node in the globals block (scenario+0x49c) dirty.
     * Count is reloaded from the block's own first word each iteration. */
    {
      void *block = (void *)((char *)scenario + 0x49c);
      int16_t i = 0;
      while ((int)i < *(int *)block) {
        void *elem = tag_block_get_element(block, (int)i, 0x5c);
        FUN_000c7b10(*(int *)((char *)elem + 0x24));
        i++;
      }
    }

    hs_scripts_dispose();

    if (tag_data_resize((void *)((char *)scenario + 0x488),
                        *(int *)0x46b6f0 + 0x400)) {
      return;
    }
  }

  display_assert("increase MAXIMUM_HS_STRING_DATA_PER_SCENARIO",
                 "c:\\halo\\SOURCE\\hs\\hs_compile.c", 0x16d, 1);
  system_exit(-1);
}
