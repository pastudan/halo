#!/usr/bin/env python3
"""Generate network_client_manager.obj batch draft fragment + disassembly artifact."""
from __future__ import annotations

import json
import re
from pathlib import Path

from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[1]
IMPL = ROOT / "tools" / "network_client_manager_batch_impl.c"
FRAG = ROOT / "tools" / "network_client_manager_batch_fragment.c"
DISASM_OUT = ROOT / "artifacts" / "network_client_manager_batch_disasm.txt"
OBJECT = "network_client_manager.obj"

DECLS = {
    "0x124730": "int16_t FUN_00124730(int model_ref, const char *marker_name, char *magic_table, int node_remap, int16_t node_count, void *node_matrices, char mirrored, void *out_markers, int16_t max_markers);",
    "0x124900": "void FUN_00124900(void *model);",
    "0x124a10": "void network_game_client_keep_alive(void *client);",
    "0x124aa0": "char network_game_client_initiate_join_game(void *client, void *game, void *join_token, void *address);",
    "0x124ba0": "char network_game_client_set_machine(void *client, void *machine);",
    "0x124c10": "void *network_game_client_get_machine(void *client);",
    "0x124c80": "void *FUN_00124c80(void *client);",
    "0x124d00": "int16_t FUN_00124d00(void *client);",
    "0x124d50": "char network_game_client_address_matches_server(void *client, void *source_address);",
    "0x124e20": "void network_game_client_game_out_of_sync(void *client);",
    "0x124e90": "void network_game_client_ponged(void *client, void *source, int timestamp);",
    "0x124f40": "void network_game_client_accepted_into_game(void *client, void *source, void *message);",
    "0x125050": "char network_game_client_game_settings_updated(void *client, void *message);",
    "0x125180": "int unstrip_player_index(int stripped_index);",
    "0x1251e0": "char network_game_client_game_has_started(void *client);",
    "0x125380": "char network_game_client_handle_game_update(void *client, void *message);",
    "0x125510": "char network_game_client_add_player_to_game(void *client, void *message);",
    "0x125660": "char network_game_client_switch_to_pregame(void *client);",
    "0x1258a0": "char network_game_client_add_player(void *client, int16_t local_player_index);",
    "0x125a90": "char network_game_client_update_local_player_data(void *client, void *player);",
    "0x125b90": "char FUN_00125b90(void *client, short request_type);",
    "0x125c60": "void network_game_client_countdown_timer_update(void *client, int16_t timer);",
    "0x125cb0": "char network_game_client_advertised_game_is_valid(void *game);",
    "0x125ce0": "char FUN_00125ce0(void *slot_array /* @<edi> */, void *advertised_game);",
    "0x125fb0": "void FUN_00125fb0(void *client /* @<esi> */, int16_t reason /* @<ax> */);",
    "0x126140": "char network_game_client_leave_game(void *client);",
    "0x1263a0": "char network_game_client_request_remove_player(void *client, void *record);",
    "0x126590": "char network_game_client_remove_player(void *client, void *message, int tick);",
    "0x126700": "void network_game_client_new_advertised_game(void *client, void *message);",
    "0x126750": "void network_game_client_game_shutdown(void *client);",
    "0x1267c0": "void network_game_client_reset(void *client, char flag);",
    "0x1268a0": "bool FUN_001268a0(void *server /* @<eax> */);",
    "0x126fe0": "void *FUN_00126fe0(void);",
    "0x1271a0": "void FUN_001271a0(void *client, void *source, int rejection_code);",
    "0x127260": "char FUN_00127260(void *client /* @<esi> */, void *message, int message_size, void *source_address);",
    "0x127310": "char FUN_00127310(void *client /* @<esi> */, void *message, int message_size, void *source_address);",
    "0x1273a0": "char FUN_001273a0(void *client /* @<esi> */, void *source_address /* @<edi> */, void *message, int message_size);",
    "0x127440": "char FUN_00127440(void *client /* @<esi> */, void *source_address /* @<edi> */, void *message, int message_size);",
    "0x1274e0": "char FUN_001274E0(void *client /* @<esi> */, void *source_address /* @<eax> */, void *message, int message_size);",
    "0x127610": "char FUN_00127610(void *client /* @<esi> */, void *source_address /* @<eax> */, void *message, int message_size);",
    "0x127710": "char FUN_00127710(void *client /* @<esi> */, void *source_address /* @<edi> */, void *message, int message_size);",
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
        if f.get("ported") is not None:
            continue
        end = addrs[i + 1][0] if i + 1 < len(addrs) else va + 0x200
        data = get_bytes(va, min(end, va + 0x3000))
        insns = list(md.disasm(data, va))
        trimmed = []
        for ins in insns:
            if ins.address >= end:
                break
            trimmed.append(ins)
            if ins.mnemonic in ("ret", "jmp") and ins.address > va:
                break
        name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", DECLS.get(f["addr"], ""))
        label = name.group(1) if name else f["addr"]
        lines.append(
            f"\n=== {label} @ {f['addr']} end~{end:08x} insns={len(trimmed)} ==="
        )
        for ins in trimmed:
            line = f"  {ins.address:08x}: {ins.mnemonic:<8} {ins.op_str}"
            if ins.mnemonic == "call" and ins.op_str.startswith("0x"):
                tgt = ins.op_str.split()[0]
                try:
                    t = int(tgt, 16)
                    line += f"  ; {addr_name.get(t, tgt)}"
                except ValueError:
                    pass
            lines.append(line)
    DISASM_OUT.parent.mkdir(parents=True, exist_ok=True)
    DISASM_OUT.write_text("\n".join(lines) + "\n")
    print(f"wrote {DISASM_OUT} ({len(lines)} lines)")


def main() -> None:
    write_disasm()
    FRAG.write_text(IMPL.read_text())
    print(f"wrote {FRAG} ({len(DECLS)} drafts)")


if __name__ == "__main__":
    main()
