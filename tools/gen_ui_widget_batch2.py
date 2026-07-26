#!/usr/bin/env python3
"""Generate ui_widget.obj batch2 draft fragment + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
IMPL = ROOT / "tools" / "ui_widget_batch2_impl.c"
FRAG = ROOT / "tools" / "ui_widget_batch2_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "ui_widget_batch2_disasm.txt"
UI_WIDGET_C = ROOT / "src" / "halo" / "interface" / "ui_widget.c"
OBJECT = "ui_widget.obj"
MARKER = "/* --- ui_widget.obj batch2 drafts (2026-07-26) --- */"

DECLS = {
    "0xe3e80": "void draw_bitmap_in_rect(int bitmap, int16_t *src_rect, int16_t *dst_rect, int16_t *clip_rect, int flags, int param_6, int param_7);",
    "0xe4ad0": "void FUN_000e4ad0(void *icon_state /* @<esi> */, int16_t *cursor /* @<ebx> */, int string_index);",
    "0xe4da0": "int16_t remap_sticks_for_local_player(int16_t icon_type, int local_player_index);",
    "0xe5180": "int FUN_000e5180(wchar_t *text, wchar_t *replacement, void **pool_block);",
    "0xe5b10": "void FUN_000e5b10(void *widget /* @<ebx> */, void *draw_state /* @<esi> */);",
    "0xe5de0": "void draw_string_and_hack_in_icons(int16_t *rect, int param_2, int param_3, int param_4, wchar_t *text, int local_player_index);",
    "0xe6140": "void FUN_000e6140(void *widget /* @<eax> */, void *draw_state /* @<ecx> */);",
    "0xe6450": "void FUN_000e6450(void *draw_state, void *widget /* @<esi> */, int param_3, int param_4);",
    "0xe73c0": "void FUN_000e73c0(void *widget, int16_t *bounds, float opacity_scale, char param_4, char visible);",
    "0xe7760": "void render_ui_widgets_postgame(int16_t local_player_index, int16_t *bounds);",
    "0xe98c0": "char FUN_000e98c0(void *widget);",
    "0xe9a90": "char FUN_000e9a90(void *widget);",
    "0xe9dd0": "char FUN_000e9dd0(void *widget);",
    "0xea210": "char display_scenario_help(void *widget);",
    "0xea3e0": "char network_game_server_list_initialize(void *widget);",
    "0xea570": "char network_game_join_game_from_server_list(void *widget);",
    "0xea900": "char FUN_000ea900(void *widget, void *event_data);",
    "0xeaa10": "char FUN_000eaa10(void *widget);",
    "0xeaba0": "char FUN_000eaba0(void *widget, void *event_data);",
    "0xead60": "char multiplayer_level_select(void *widget, void *event_data);",
    "0xeaec0": "char FUN_000eaec0(void *widget);",
    "0xeb020": "char FUN_000eb020(void *widget);",
    "0xeb150": "char FUN_000eb150(void *widget);",
    "0xeb4f0": "char FUN_000eb4f0(void *widget);",
    "0xeb710": "char FUN_000eb710(void *widget);",
    "0xeba70": "char FUN_000eba70(void *widget);",
    "0xebff0": "char FUN_000ebff0(void *widget);",
    "0xec2c0": "char FUN_000ec2c0(void *widget);",
    "0xec840": "char FUN_000ec840(void *widget);",
    "0xecb60": "char FUN_000ecb60(void *widget);",
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

    lines: list[str] = []
    for i, (va, f) in enumerate(addrs):
        if f["addr"] not in DECLS:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        data = get_bytes(va, min(end, va + 0x3000))
        insns = list(md.disasm(data, va))
        trimmed = [x for x in insns if x.address < end]
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", DECLS[f["addr"]]).group(1)
        lines.append(
            f"\n=== {name} @ {f['addr']} end~{end:08x} insns={len(trimmed)} ==="
        )
        for ins in trimmed[:400]:
            line = f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}"
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                t = int(ins.op_str.split()[0], 16)
                nm = addr_name.get(t, "")
                if nm:
                    line += f"  ; {nm}"
            lines.append(line)
        if len(trimmed) > 400:
            lines.append(f"  ... ({len(trimmed) - 400} more insns)")
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def append_to_ui_widget_c() -> None:
    text = UI_WIDGET_C.read_text()
    fragment = IMPL.read_text()
    if MARKER in text:
        before = text.split(MARKER, 1)[0]
        if not before.endswith("\n"):
            before += "\n"
        UI_WIDGET_C.write_text(before + fragment)
        print("replaced batch2 fragment in", UI_WIDGET_C)
        return
    if not text.endswith("\n"):
        text += "\n"
    UI_WIDGET_C.write_text(text + fragment)
    print("appended batch2 fragment to", UI_WIDGET_C)


def main() -> None:
    if not IMPL.exists():
        raise SystemExit(f"missing {IMPL} — run tools/build_ui_widget_batch2_impl.py first")
    write_disasm()
    FRAG.write_text(IMPL.read_text())
    append_to_ui_widget_c()
    print("wrote", FRAG, len(DECLS), "functions")


if __name__ == "__main__":
    main()
