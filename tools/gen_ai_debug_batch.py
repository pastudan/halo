#!/usr/bin/env python3
"""Generate ai_debug.obj batch draft implementations + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
IMPL = ROOT / "tools" / "ai_debug_batch_impl.c"
FRAG = ROOT / "tools" / "ai_debug_batch_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "ai_debug_batch_disasm.txt"
OBJECT = "ai_debug.obj"

DECLS = {
    "0x490c0": "void FUN_000490C0(void);",
    "0x49270": "void ai_debug_sound_point_set(void);",
    "0x49280": "void FUN_00049280(void);",
    "0x49300": "void FUN_00049300(void);",
    "0x493b0": "void FUN_000493B0(void);",
    "0x493d0": "void ai_debug_get_last_path(float *vec_a, float *vec_b);",
    "0x49430": "void ai_debug_lineoffire_addpill(float *vec_a, float *vec_b, int param_3, char param_4);",
    "0x494e0": "void FUN_000494e0(void);",
    "0x495b0": "void FUN_000495b0(void);",
    "0x496c0": "char ai_debug_highlight_cluster(int16_t cluster_index, void *out);",
    "0x497c0": "void FUN_000497c0(void);",
    "0x498d0": "void FUN_000498d0(void);",
    "0x49990": "void FUN_00049990(void);",
    "0x49ac0": "char *ai_debug_describe_actor(int actor_handle, int object_handle, char with_actor, char *buf, int buf_size);",
    "0x49c70": "void FUN_00049c70(void);",
    "0x49d60": "void FUN_00049d60(void);",
    "0x49f60": "void ai_debug_vocalize(int a0, int a1);",
    "0x4a030": "void FUN_0004a030(void);",
    "0x4a220": "void ai_debug_speak(int a0);",
    "0x4a290": "void ai_debug_speak_list(int a0);",
    "0x4a460": "void FUN_0004a460(int a0, int a1, void *buf, int buf_size, int max_entries);",
    "0x4a650": "void ai_debug_communication_suppress(int a0, int a1);",
    "0x4a680": "void ai_debug_communication_ignore(int a0, int a1);",
    "0x4a6b0": "void ai_debug_communication_focus(int a0, int a1);",
    "0x4a6e0": "void ai_debug_idle_look_clear(int actor_handle);",
    "0x4a710": "void ai_debug_idle_look_addprop(int index, float value);",
    "0x4a770": "void FUN_0004a770(void);",
    "0x4a8c0": "void FUN_0004a8c0(void);",
    "0x4a9f0": "void FUN_0004a9f0(void);",
    "0x4afa0": "void ai_debug_change_selected_encounter(int encounter_index);",
    "0x4b0f0": "void ai_debug_teleport_to(int actor_index);",
    "0x4b220": "void FUN_0004b220(void);",
    "0x4b2b0": "void FUN_0004b2b0(void);",
    "0x4b320": "void FUN_0004b320(void);",
    "0x4b670": "void FUN_0004b670(void);",
    "0x4b770": "void ai_debug_lineofsight(void);",
    "0x4b7a0": "void FUN_0004b7a0(void);",
    "0x4b810": "void FUN_0004b810(void);",
    "0x4bc70": "void FUN_0004bc70(void);",
    "0x4c170": "void ai_debug_change_selected_actor(int actor_index);",
    "0x4c2a0": "void FUN_0004c2a0(void);",
    "0x4c560": "void FUN_0004c560(void);",
    "0x4c890": "void FUN_0004c890(void);",
    "0x4c920": "void FUN_0004c920(void);",
    "0x52ab0": "void FUN_00052ab0(void);",
    "0x52b60": "void FUN_00052b60(void);",
    "0x52bb0": "void FUN_00052bb0(void);",
    "0x534d0": "void FUN_000534d0(void);",
    "0x53620": "void set_real_point3d(void);",
    "0x53640": "void ai_debug_lineoffire_success(void);",
    "0x53650": "void FUN_00053650(void);",
    "0x53670": "void ai_debug_lineofsight_reset(void);",
    "0x53680": "void FUN_00053680(void);",
    "0x53790": "void FUN_00053790(void);",
    "0x53800": "void FUN_00053800(void);",
    "0x53890": "void FUN_00053890(void);",
    "0x538d0": "void FUN_000538d0(void);",
    "0x538f0": "void FUN_000538f0(void);",
    "0x53960": "void FUN_00053960(void);",
    "0x539c0": "void FUN_000539c0(void);",
    "0x53a20": "void FUN_00053a20(void);",
    "0x53a90": "void FUN_00053a90(void);",
    "0x53af0": "void FUN_00053af0(void);",
}

OVERRIDES = r'''
void ai_debug_sound_point_set(void)
{
}

void ai_debug_lineoffire_success(void)
{
}

void ai_debug_lineofsight_reset(void)
{
}

void set_real_point3d(void)
{
  csmemset((void *)0x5abaa0, 0, 0xeec);
  *(char *)0x5abaa4 = 1;
}

void ai_debug_get_last_path(float *vec_a, float *vec_b)
{
  *(char *)0x5acab8 = 1;
  *(char *)0x5acab9 = 0;
  *(uint32_t *)0x5acabc = *(uint32_t *)vec_a;
  *(uint32_t *)0x5acac0 = *(uint32_t *)((char *)vec_a + 4);
  *(uint32_t *)0x5acac4 = *(uint32_t *)((char *)vec_a + 8);
  *(uint32_t *)0x5acac8 = *(uint32_t *)vec_b;
  *(uint32_t *)0x5acacc = *(uint32_t *)((char *)vec_b + 4);
  *(uint32_t *)0x5acad0 = *(uint32_t *)((char *)vec_b + 8);
  *(uint32_t *)0x5acad4 = 0;
}

void ai_debug_communication_suppress(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca14, 0x39, 0x42ce0);
}

void ai_debug_communication_ignore(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca1c, 0x39, 0x42ce0);
}

void ai_debug_communication_focus(int a0, int a1)
{
  FUN_0004a460(a0, a1, (void *)0x5aca24, 0xd1, 0x1a67e0);
}

void ai_debug_idle_look_clear(int actor_handle)
{
  *(char *)0x6323d4 = (actor_handle != -1);
  *(int32_t *)0x6323d8 = actor_handle;
  *(uint16_t *)0x6323dc = 0;
}

void ai_debug_idle_look_addprop(int index, float value)
{
  if (index < 0 || index >= 0x200) {
    display_assert("index>=0 && index<MAXIMUM_AI_DEBUG_IDLE_LOOK_PROPS",
                   "c:\\halo\\SOURCE\\ai\\ai_debug.c", 0x2a1, 1);
    system_exit(-1);
  }
  *(float *)(0x62a3b8 + index * 0x40) = value;
}

void ai_debug_change_selected_encounter(int encounter_index)
{
  ai_debug_select_encounter(encounter_index);
}

void ai_debug_change_selected_actor(int actor_index)
{
  ai_debug_select_actor(*(int32_t *)0x5ac9f4, actor_index);
}
'''


def write_disasm() -> None:
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    kb = json.loads((ROOT / "kb.json").read_text())
    obj = next(o for o in kb["objects"] if o["name"] == OBJECT)
    fns = sorted(obj["functions"], key=lambda f: int(f["addr"], 16))
    addrs = [(int(f["addr"], 16), f) for f in fns]
    addr_name: dict[int, str] = {}
    for o in kb["objects"]:
        for f in o.get("functions", []):
            m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", f.get("decl") or "")
            if m:
                addr_name[int(f["addr"], 16)] = m.group(1)

    def get_bytes(va: int, end: int) -> bytes:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= va < s + sec.header.virtual_size:
                return bytes(sec.data[va - s : end - s])
        raise RuntimeError(hex(va))

    lines: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        data = get_bytes(va, min(end, va + 0x3000))
        insns = list(md.disasm(data, va))
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", DECLS.get(f["addr"], ""))
        label = name.group(1) if name else f["addr"]
        lines.append(f"\n=== {label} @ {f['addr']} end~{end:08x} ===")
        for ins in insns[:200]:
            if ins.address >= end:
                break
            line = f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}"
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                t = int(ins.op_str, 16)
                line += f"  ; {addr_name.get(t, '')}"
            lines.append(line)
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def parse_override_names(text: str) -> set[str]:
    names: set[str] = set()
    for m in re.finditer(r"^[\w\s\*]+\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(", text, re.M):
        names.add(m.group(1))
    return names


def gen_stub(name: str, decl: str) -> str:
    if name in override_names:
        return ""
    body = re.search(r"\(([^)]*)\)", decl)
    params = body.group(1).strip() if body else ""
    if params and params != "void":
        lines = []
        for p in params.split(","):
            p = p.strip()
            tok = re.sub(r"\[[^\]]*\]", "", p)
            tok = re.split(r"\s+", tok.replace("*", " ").strip())
            if tok:
                lines.append(f"  (void){tok[-1]};")
        inner = "\n".join(lines) if lines else ""
    else:
        inner = ""
    ret = decl.split("(", 1)[0]
    if ret.strip().startswith("char *") or ret.strip().endswith("*"):
        return f"{decl.split(';')[0]}\n{{\n{inner}\n  return NULL;\n}}\n"
    if " char " in f" {ret} " or ret.strip().startswith("char"):
        return f"{decl.split(';')[0]}\n{{\n{inner}\n  return 0;\n}}\n"
    return f"{decl.split(';')[0]}\n{{\n{inner}\n}}\n"


def gen_impl() -> str:
    parts = ["/* --- ai_debug.obj batch drafts (2026-07-26) --- */\n"]
    parts.append(OVERRIDES)
    for addr in sorted(DECLS.keys(), key=lambda x: int(x, 16)):
        decl = DECLS[addr]
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl).group(1)
        stub = gen_stub(name, decl)
        if stub:
            parts.append(f"/* {addr} */\n{stub}")
    return "\n".join(parts)


override_names = parse_override_names(OVERRIDES)


def main() -> None:
    write_disasm()
    text = gen_impl()
    IMPL.write_text(text)
    FRAG.write_text(text)
    print(f"wrote {IMPL} ({len(DECLS)} drafts, {len(override_names)} overrides)")


if __name__ == "__main__":
    main()
