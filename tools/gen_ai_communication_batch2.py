#!/usr/bin/env python3
"""Generate ai_communication.obj batch2 draft implementations + disassembly."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "tools" / "ai_communication_batch2_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "ai_communication_batch2_disasm.txt"
IMPL = ROOT / "tools" / "ai_communication_batch2_impl.c"
OBJECT = "ai_communication.obj"

DECLS = {
    "0x430d0": "int16_t ai_communication_consider_speech(void *packet /* @<ecx> */, int unit /* @<eax> */, int param /* @<edx> */, int stack_a, int16_t dialogue_type, int16_t start_tick, int stack_b, char flag, float *timer, char *out_buf);",
    "0x432b0": "void FUN_000432b0(int unit /* @<ebx> */, int actor /* @<eax> */, int target /* @<edi> */, int stack_a, short priority);",
    "0x43360": "void FUN_00043360(int unit /* @<edi> */, short priority /* @<bx> */, int actor /* @<esi> */, int stack_a);",
    "0x433b0": "int16_t ai_conversation_status(int16_t conversation_index);",
    "0x435b0": "void ai_conversation_finish(int handle, char param_b, char param_c);",
    "0x43740": "int FUN_00043740(int16_t conversation_index, char allow_finish);",
    "0x43870": "char ai_conversation_line_begin(int conversation_handle);",
    "0x43a20": "char FUN_00043a20(int conversation_handle);",
    "0x43ce0": "void FUN_00043ce0(int actor /* @<eax> */);",
    "0x43db0": "void actor_communication_update(int actor_handle);",
    "0x43ea0": "void FUN_00043ea0(void *comm /* @<ecx> */, int actor /* @<eax> */, int stack_a);",
    "0x43f20": "void ai_communication_update_speech_timers(int unit /* @<eax> */, int16_t type, int a, int16_t dialogue_index, int16_t reply_index);",
    "0x441c0": "float ai_communication_get_player_rating(int unit, char use_teams, int *out_unit, int *out_handle);",
    "0x44660": "void ai_conversation_unit_died(int unit_handle, char param_2);",
    "0x447d0": "void ai_conversation_find_participant(int conversation_handle, int16_t participant_index, char *found_out, char *required_out, float *rating_out, int *handle_out);",
    "0x44fd0": "void FUN_00044fd0(int unit_handle, uint16_t priority, uint16_t type, void *comm_data);",
    "0x45290": "void FUN_00045290(int unit_handle, uint16_t priority, uint16_t type, void *comm_data);",
    "0x454a0": "void FUN_000454a0(int actor /* @<eax> */, int stack_a, float *pos, int stack_c, float radius, float rating, int16_t anim_a, int16_t anim_b, int stack_d, int stack_e, char flags);",
    "0x45830": "int FUN_00045830(int type /* @<ebx> */, int unit /* @<eax> */, int actor /* @<edi> */, int target /* @<esi> */, int16_t subtype, int16_t index, float max_dist);",
    "0x458f0": "int ai_communication_find_global_actor_to_talk(int comm_type, int unit, int16_t subtype, int16_t index, int stack_a, int stack_b, float max_dist, int mode);",
    "0x45a10": "char ai_conversation_begin(int conversation_handle, char *flag_out);",
    "0x460e0": "void FUN_000460e0(int actor /* @<eax> */, int stack_a, float *pos, int stack_c, float radius, float rating, int16_t anim_a, int16_t anim_b, int stack_d, int stack_e, char flags);",
    "0x46530": "void FUN_00046530(int unit_handle, uint16_t priority, uint16_t type, int unk, int unk2, void *comm_data);",
    "0x46b60": "char FUN_00046b60(int16_t conversation_index, char allow_finish);",
    "0x46cb0": "void ai_conversation_update(void);",
    "0x46f10": "void FUN_00046f10(int16_t type, int unit_handle, int param3, int param4, int16_t param5, int16_t param6, int16_t param7);",
}


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

    chunks: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        size = end - va
        data = get_bytes(va, min(end, va + 0x3000))
        insns = list(md.disasm(data, va))
        lines: list[str] = []
        calls = 0
        for x in insns:
            if x.address >= end:
                break
            line = f"  {x.address:08x}: {x.mnemonic:8} {x.op_str}"
            if x.mnemonic == "call" and x.op_str.startswith("0x"):
                t = int(x.op_str, 16)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
                calls += 1
            lines.append(line)
        name = re.search(
            r"([A-Za-z_][A-Za-z0-9_]*)\s*\(",
            f.get("decl", "void FUN(void);"),
        ).group(1)
        header = (
            f"\n=== {name} @ {f['addr']} size={size} end~{end:08x} "
            f"insns={len(lines)} calls={calls} ===\n"
        )
        body = "\n".join(lines[:400])
        if len(lines) > 400:
            body += f"\n  ... ({len(lines) - 400} more insns)"
        chunks.append(header + body)
    DISASM_OUT.parent.mkdir(exist_ok=True)
    DISASM_OUT.write_text("\n".join(chunks) + ("\n" if chunks else ""))


def main() -> None:
    OUT.write_text(IMPL.read_text())
    write_disasm()
    print("wrote", OUT, len(DECLS), "functions")


if __name__ == "__main__":
    main()
