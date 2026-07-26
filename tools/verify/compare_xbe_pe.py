#!/usr/bin/env python3
"""Interim structural compare: original XBE function vs clang PE export.

Not a VC71 score — use when RXDK/Ghidra delinker are unavailable.
"""
from __future__ import annotations

import argparse
import json
import sys
from difflib import SequenceMatcher
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from xbe import Xbe

ROOT = Path(__file__).resolve().parents[2]


def mnemonics(data: bytes, va: int) -> list[str]:
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    return [insn.mnemonic for insn in md.disasm(data, va)]


def xbe_bytes(xbe: Xbe, va: int, end: int) -> bytes:
    for sec in xbe.sections.values():
        start = sec.header.virtual_addr
        if start <= va < start + sec.header.virtual_size:
            return bytes(sec.data[va - start : end - start])
    raise SystemExit(f"va {va:#x} not in XBE")


def pe_fn_bytes(pe: pefile.PE, name: str) -> tuple[bytes, int]:
    base = pe.OPTIONAL_HEADER.ImageBase
    addr = None
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if exp.name and exp.name.decode() == name:
            addr = base + exp.address
            break
    if addr is None:
        raise SystemExit(f"export {name} missing from PE")

    exports = sorted(
        base + exp.address
        for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols
        if exp.address
    )
    nxt = next((a for a in exports if a > addr), None)
    # Large XBE-shaped naked drafts (batch 50+) exceed 4KiB; rely on the next
    # export boundary, with a generous ceiling only when that boundary is missing.
    size = min((nxt - addr) if nxt else 0x800, 0x8000)
    off = pe.get_offset_from_rva(addr - base)
    data = pe.__data__[off : off + size]
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    # Strip trailing padding bytes, then drop trailing NOP instructions
    # (clang often emits multi-byte NOPs that may be truncated at the next export).
    # Keep a single 0x90 immediately after RET — XBE jump-table bodies often
    # align with that nop (batch 50 FUN_000f90d0).
    while len(data) > 16 and data[-1] in (0x90, 0xCC, 0x00):
        if data[-1] == 0x90 and data[-2] == 0xC3:
            break
        data = data[:-1]
    while True:
        insns = list(md.disasm(data, addr))
        if len(insns) < 2 or insns[-1].mnemonic != "nop":
            break
        # Keep only XBE-style single-byte align nop after RET; strip clang
        # multi-byte NOP padding (e.g. 66 2E 0F 1F 84 00 ...).
        if insns[-2].mnemonic == "ret" and insns[-1].size == 1:
            break
        data = data[: insns[-1].address - addr]
    # Truncate after final RET (+ optional single-byte nop) only when the
    # post-RET region looks like JT/pad residue (batch 56 FUN_001ad260).
    # Keep post-RET bodies that are still live via jump tables (early-ret
    # + continuation, e.g. batch 82 FUN_0011b2a0).
    insns = list(md.disasm(data, addr))
    ret_idxs = [i for i, ins in enumerate(insns) if ins.mnemonic == "ret"]
    if ret_idxs:
        ri = ret_idxs[-1]
        end_off = insns[ri].address + insns[ri].size - addr
        if (
            ri + 1 < len(insns)
            and insns[ri + 1].mnemonic == "nop"
            and insns[ri + 1].size == 1
            and insns[ri + 1].address == addr + end_off
        ):
            end_off += 1
        post = data[end_off:]
        post_insns = list(md.disasm(post, addr + end_off))
        real = [
            i
            for i in post_insns
            if i.mnemonic not in ("nop", "int3")
        ]
        # Jump-table dwords rarely decode into a long run of real ops.
        if len(real) < 8:
            data = data[:end_off]
    return data, addr


def xbe_mnemonics(data: bytes, va: int, skip: list[tuple[int, int]] | None = None) -> list[str]:
    """Disassemble XBE bytes, skipping absolute [start, end) jump-table gaps."""
    if not skip:
        return mnemonics(data, va)
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    ranges = sorted(skip)
    out: list[str] = []
    pos = 0
    while pos < len(data):
        abspos = va + pos
        for s, e in ranges:
            if s <= abspos < e:
                pos = e - va
                break
        else:
            chunk = list(md.disasm(data[pos : pos + 16], abspos))
            if not chunk:
                pos += 1
                continue
            insn = chunk[0]
            crossed = [s for s, e in ranges if insn.address < s < insn.address + insn.size]
            if crossed:
                pos = min(crossed) - va
                continue
            out.append(insn.mnemonic)
            pos += insn.size
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--xbe", default=str(ROOT / "halo-patched/cachebeta.xbe"))
    ap.add_argument("--pe", default=str(ROOT / "build/halo"))
    ap.add_argument(
        "--json-out",
        default=str(ROOT / "artifacts/verify_collision_structural.json"),
    )
    args = ap.parse_args()

    targets = [
        ("FUN_00147380", 0x147380, 0x1473b0),
        ("collision_surface_project_point2d", 0x147990, 0x1479d8),
        ("collision_surface_test_point2d", 0x1479e0, 0x147ad7),
        ("collision_surface_find_closest_point2d", 0x147ae0, 0x147d10),
        ("collision_bsp_test_vector", 0x149480, 0x149570),
        ("collision_bsp_test_sphere", 0x1493b0, 0x149480),
        ("collision_bsp_test_pill_new", 0x148b20, 0x148b90),
        ("bsp3d_test_sphere_recursive", 0x148b90, 0x148eb0),
        # refined hs_runtime / units / bipeds (2026-07-26 wave)
        ("FUN_000c9f90", 0xc9f90, 0xca010),
        ("hs_wake_by_name", 0xcb9a0, 0xcba00),
        ("FUN_001a8770", 0x1a8770, 0x1a8782),
        ("FUN_001a8890", 0x1a8890, 0x1a88ad),
        ("FUN_001a8910", 0x1a8910, 0x1a892e),
        ("FUN_001a8950", 0x1a8950, 0x1a898e),
        ("FUN_001a0db0", 0x1a0db0, 0x1a0e00),
        # collision_bsp extended
        ("FUN_00147ed0", 0x147ed0, 0x148240),
        ("FUN_00148240", 0x148240, 0x148365),
        ("FUN_00148440", 0x148440, 0x1486e0),
        ("FUN_00148370", 0x148370, 0x148440),
        ("FUN_001486e0", 0x1486e0, 0x148780),
        ("FUN_00148780", 0x148780, 0x148910),
        ("FUN_00148910", 0x148910, 0x148b20),
        ("FUN_00148eb0", 0x148eb0, 0x1491d0),
        ("FUN_001491d0", 0x1491d0, 0x1493b0),
        ("FUN_00149570", 0x149570, 0x149680),
        ("FUN_00149680", 0x149680, 0x149c60),
        ("FUN_0014dc30", 0x14dc30, 0x14dce0),
        ("FUN_0014dce0", 0x14dce0, 0x14df70),
        ("FUN_0014ea10", 0x14ea10, 0x14ec30),
        ("FUN_0014e640", 0x14e640, 0x14e7d0),
        ("FUN_0014e7d0", 0x14e7d0, 0x14e940),
        ("FUN_0014e940", 0x14e940, 0x14ea10),
        # path heap / obstacle avoidance (2026-07-26 wave)
        ("FUN_00060070", 0x60070, 0x600c0),
        ("FUN_000600c0", 0x600c0, 0x600f0),
        ("FUN_000600f0", 0x600f0, 0x60140),
        ("FUN_00060140", 0x60140, 0x601a0),
        ("FUN_000601a0", 0x601a0, 0x601e0),
        ("FUN_000601e0", 0x601e0, 0x601f0),
        ("FUN_000601f0", 0x601f0, 0x60200),
        ("FUN_00060200", 0x60200, 0x60260),
        ("FUN_00060330", 0x60330, 0x604e0),
        ("FUN_000604e0", 0x604e0, 0x60670),
        ("FUN_00060670", 0x60670, 0x60910),
        ("FUN_00060910", 0x60910, 0x60970),
        ("FUN_00060970", 0x60970, 0x609e0),
        ("path_add_step", 0x60c80, 0x60ea0),
        ("FUN_00060ea0", 0x60ea0, 0x61080),
        ("FUN_00061080", 0x61080, 0x61280),
        ("path_add_steps", 0x61280, 0x615b0),
        ("FUN_000615b0", 0x615b0, 0x616e0),
        ("FUN_000616e0", 0x616e0, 0x61750),
        ("FUN_00061750", 0x61750, 0x61bd8),
        ("find_turning_point", 0x63030, 0x633b0),
        ("FUN_000633b0", 0x633b0, 0x63710),
        ("FUN_00062e10", 0x62e10, 0x63030),
        ("FUN_00062ba0", 0x62ba0, 0x62cf0),
        ("FUN_00062cf0", 0x62cf0, 0x62e10),
        ("FUN_000639e0", 0x639e0, 0x63e30),
        ("FUN_00063e30", 0x63e30, 0x63e90),
        ("FUN_00063e90", 0x63e90, 0x640df),
        ("path_heap_bubble_up", 0x5e150, 0x5e330),
        ("path_heap_bubble_down", 0x5e330, 0x5e560),
        ("path_heap_pop_cheapest_node", 0x5e560, 0x5e680),
        ("path_heap_insert", 0x5e680, 0x5e700),
        ("path_state_approach_point", 0x5e9b0, 0x5eae0),
        ("ai_find_inactive_encounters", 0x3fb40, 0x3fc90),
        ("ai_release_inactive_encounters", 0x3fc90, 0x3fdbd),
        ("actor_berserk", 0x31440, 0x314f0),
        # path build + prop lifecycle (2026-07-26 wave)
        ("path_state_build_path", 0x5eae0, 0x5ef80),
        ("FUN_0005ef80", 0x5ef80, 0x5f1d0),
        ("prop_add", 0x64170, 0x643d0),
        ("FUN_00064b40", 0x64b40, 0x64cd0),
        ("FUN_00064cd0", 0x64cd0, 0x64f50),
        ("prop_new_unacknowledged", 0x645a0, 0x647c0),
        ("prop_position_refresh", 0x31df0, 0x32170),
        ("prop_status_refresh", 0x33440, 0x342a0),
        ("FUN_0005f740", 0x5f740, 0x5ff70),
        ("actor_perception_unit_from_swarm", 0x31c00, 0x31df0),
        # perception + path edge wave (2026-07-26)
        ("build_path_edges_for_surface", 0x5f240, 0x5f3c0),
        ("closest_point_to_attractor", 0x5f3c0, 0x5f490),
        ("path_attractor_weight", 0x5f490, 0x5f550),
        ("actor_perception_desire_prop", 0x2f6e0, 0x2f910),
        ("actor_perception_find_sense_position", 0x31a90, 0x31c00),
        ("FUN_00032170", 0x32170, 0x32380),
        ("actor_expected_acknowledgement", 0x32940, 0x32ac0),
        ("actor_perception_refresh_danger_zone", 0x32380, 0x32940),
        ("actor_visibility_at_point", 0x314f0, 0x31850),
        ("actor_perception_unreachable", 0x32ac0, 0x32b50),
        ("FUN_0002f5f0", 0x2f5f0, 0x2f6e0),
        # perception orphan + audibility wave (2026-07-26)
        ("actor_audibility_at_point", 0x31850, 0x31a90),
        ("actor_perception_refresh_test_object", 0x342a0, 0x34970),
        ("actor_perception_create_orphan_from_friend", 0x34970, 0x34c80),
        ("prop_orphan_from_friend", 0x64970, 0x64a60),
        ("prop_orphan_transition", 0x648a0, 0x64970),
        ("FUN_000647c0", 0x647c0, 0x648a0),
        ("prop_orphan_update_information", 0x64a60, 0x64a80),
        ("FUN_00064400", 0x64400, 0x645a0),
        # ai damage / allegiance / lifecycle wave (2026-07-26)
        ("ai_adjust_damage", 0x3f900, 0x3f970),
        ("ai_handle_allegiance_broken_notification", 0x40150, 0x40280),
        ("ai_handle_damage", 0x40460, 0x40570),
        ("ai_handle_deleted_object", 0x40700, 0x40860),
        ("ai_handle_unit_effect", 0x40860, 0x409a0),
        ("ai_consider_major_upgrade", 0x41250, 0x413c0),
        ("actor_combat_build_grenade_trajectory", 0x218d0, 0x219e0),
        # combat + objects wave (2026-07-26)
        ("actor_aim_projectile", 0x220c0, 0x22390),
        ("FUN_00022b40", 0x22b40, 0x22ba0),
        ("object_update", 0x1444f0, 0x1446a0),
        ("FUN_00085000", 0x85000, 0x850ce),
        # encounters.obj implemented-but-unported (2026-07-26)
        ("FUN_00053b80", 0x53b80, 0x53bf0),
        ("FUN_00053bf0", 0x53bf0, 0x53c50),
        ("FUN_00053c50", 0x53c50, 0x53da0),
        ("FUN_00053e80", 0x53e80, 0x53ee0),
        ("FUN_00053ee0", 0x53ee0, 0x53f40),
        ("FUN_00053f40", 0x53f40, 0x54020),
        ("FUN_000564b0", 0x564b0, 0x565c0),
        ("FUN_000565c0", 0x565c0, 0x566a0),
        ("encounters_initialize", 0x566a0, 0x56790),
        ("FUN_00057330", 0x57330, 0x57380),
        ("FUN_00057380", 0x57380, 0x575d0),
        ("FUN_00057b40", 0x57b40, 0x57bc0),
        ("FUN_00057d00", 0x57d00, 0x57ef0),
        ("FUN_00058700", 0x58700, 0x58710),
        ("FUN_00058710", 0x58710, 0x58720),
        ("FUN_00058ae0", 0x58ae0, 0x58af0),
        ("FUN_00058af0", 0x58af0, 0x58c40),
        ("FUN_00058c40", 0x58c40, 0x58fa0),
        ("FUN_00058fd0", 0x58fd0, 0x59480),
        ("FUN_00059c40", 0x59c40, 0x59d30),
        ("encounter_modify_pursuit_desires", 0x59d30, 0x59dd0),
        ("encounter_determine_pursuit_availability", 0x59dd0, 0x5a050),
        ("encounter_link_activation", 0x5a5a0, 0x5a640),
        ("FUN_0005ac60", 0x5ac60, 0x5acf0),
        ("encounter_verify_firing_position_owner_actor_indices", 0x5b370, 0x5b4b0),
        ("encounter_build_firing_position_owner_actor_indices", 0x5b4b0, 0x5b5e0),
        ("encounter_mark_examined_pursuit_position", 0x5b5e0, 0x5b6e0),
        ("encounter_pursuit_position_already_examined", 0x5b6e0, 0x5b790),
        ("FUN_0005B790", 0x5b790, 0x5ba70),
        ("encounter_force_activate", 0x5ba70, 0x5baa0),
        ("encounter_force_deactivate", 0x5baa0, 0x5bad0),
        ("encounter_post_combat_select_random_behavior", 0x5bad0, 0x5bbe0),
        ("FUN_0005bbe0", 0x5bbe0, 0x5c3a0),
        ("encounter_get_actor_starting_location", 0x5c3a0, 0x5c510),
        ("encounter_spawn_actor", 0x5c510, 0x5c630),
        ("encounter_set_respawn", 0x5c630, 0x5c680),
        ("FUN_0005c680", 0x5c680, 0x5c940),
        ("FUN_0005ca80", 0x5ca80, 0x5d200),
        # damage + objects + vehicles + weapons wave (2026-07-26)
        ("object_get_maximum_shield_vitality", 0x136700, 0x136741),
        ("FUN_00136b40", 0x136b40, 0x136bbe),
        ("FUN_00138f30", 0x138f30, 0x138f69),
        ("FUN_00138f70", 0x138f70, 0x138fc5),
        ("FUN_00085280", 0x85280, 0x85350),
        ("FUN_001342a0", 0x1342a0, 0x134350),
        ("vehicle_causes_collision_damage", 0x1b5580, 0x1b55c0),
        ("weapon_can_be_fired", 0xfaf50, 0xfafe0),
        ("weapon_useful", 0xfafe0, 0xfb00c),
        ("weapon_compute_movement_penalty", 0xfb010, 0xfb07c),
        ("FUN_00085350", 0x85350, 0x85380),
        ("FUN_00138fd0", 0x138fd0, 0x1390cf),
        ("vehicle_hover", 0x1b55c0, 0x1b55f0),
        ("vehicle_is_flipped", 0x1b5680, 0x1b56ac),
        ("FUN_001a0db0", 0x1a0db0, 0x1a0e00),
        ("FUN_001b5500", 0x1b5500, 0x1b5580),
        ("FUN_001b5610", 0x1b5610, 0x1b5657),
        ("FUN_000fb910", 0xfb910, 0xfb990),
        ("FUN_000fb990", 0xfb990, 0xfb9da),
        ("FUN_001a8770", 0x1a8770, 0x1a8782),
        # gameplay wave 7 (2026-07-26)
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        ("FUN_001b5400", 0x1b5400, 0x1b54fb),
        ("FUN_001b56b0", 0x1b56b0, 0x1b5747),
        ("FUN_000fb690", 0xfb690, 0xfb6d6),
        # gameplay wave 8 (2026-07-26)
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00133300", 0x133300, 0x133496),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c8a),
        # gameplay wave 9 (2026-07-26)
        ("FUN_001b4dc0", 0x1b4dc0, 0x1b53f3),
        ("vehicle_export_function_values", 0x1b79c0, 0x1b7e48),
        ("FUN_001b6560", 0x1b6560, 0x1b69a0),
        # gameplay wave 10 (2026-07-26)
        ("FUN_00134c40", 0x134c40, 0x134e50),
        ("FUN_00139480", 0x139480, 0x1396dc),
        ("FUN_001b72b0", 0x1b72b0, 0x1b74c6),
        ("FUN_001b74d0", 0x1b74d0, 0x1b77e1),
        ("FUN_000de3f0", 0xde3f0, 0xde560),
        # gameplay wave 11 (2026-07-26)
        ("FUN_001b7020", 0x1b7020, 0x1b72a5),
        ("FUN_001b77f0", 0x1b77f0, 0x1b79c0),
        ("FUN_001b6ca0", 0x1b6ca0, 0x1b6e11),
        # gameplay wave 12 (2026-07-26)
        ("FUN_000de560", 0xde560, 0xdeb4f),
        ("FUN_001b5f20", 0x1b5f20, 0x1b5fed),
        ("FUN_001b6560", 0x1b6560, 0x1b69a0),
        ("FUN_001b6e20", 0x1b6e20, 0x1b7016),
        # gameplay wave 13 (2026-07-26)
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c8a),
        ("vehicle_export_function_values", 0x1b79c0, 0x1b7e48),
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_001b5400", 0x1b5400, 0x1b54fb),
        ("FUN_000de3f0", 0xde3f0, 0xde560),
        # gameplay wave 14 (2026-07-26)
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00133300", 0x133300, 0x133496),
        ("actor_aim_projectile", 0x220c0, 0x22390),
        ("FUN_001b4dc0", 0x1b4dc0, 0x1b53f3),
        # gameplay wave 15 (2026-07-26)
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c8a),
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        ("FUN_00149680", 0x149680, 0x149d00),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        ("FUN_001491d0", 0x1491d0, 0x1493a0),
        # gameplay wave 16 (2026-07-26)
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        ("FUN_001b81d0", 0x1b81d0, 0x1b856c),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c8a),
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        # gameplay wave 17 (2026-07-26)
        ("FUN_001b8570", 0x1b8570, 0x1b8f08),
        ("item_update", 0xf7340, 0xf7ca1),
        ("FUN_000fd570", 0xfd570, 0xfdc87),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        # gameplay wave 18 (2026-07-26)
        ("FUN_001b8570", 0x1b8570, 0x1b8f08),
        ("item_update", 0xf7340, 0xf7ca1),
        ("FUN_000f5fb0", 0xf5fb0, 0xf63c4),
        ("FUN_000f4cf0", 0xf4cf0, 0xf4e92),
        # gameplay wave 19 (2026-07-26)
        ("FUN_000f7110", 0xf7110, 0xf7340),
        ("multiplayer_settings_select_list_update_item", 0xf4210, 0xf46e0),
        ("FUN_000f46e0", 0xf46e0, 0xf4b60),
        ("FUN_00135510", 0x135510, 0x135f1b),
        ("FUN_001b6e20", 0x1b6e20, 0x1b7016),
        # gameplay wave 20 (2026-07-26)
        ("first_person_weapon_update", 0xdd580, 0xddad8),
        ("FUN_0001b280", 0x1b280, 0x1b750),
        ("get_local_player_input_blob", 0xb70b0, 0xb7e30),
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        # gameplay wave 21 (2026-07-26)
        ("first_person_weapon_draw", 0xdce80, 0xdd110),
        ("FUN_0001aeb0", 0x1aeb0, 0x1b280),
        ("vehicle_stuck", 0x1b8060, 0x1b81c7),
        ("object_compute_function_values", 0x13e7b0, 0x13eb30),
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        # gameplay wave 22 (2026-07-26)
        ("FUN_000f4b60", 0xf4b60, 0xf4cec),
        ("FUN_000f5800", 0xf5800, 0xf58c6),
        ("FUN_000f3690", 0xf3690, 0xf3740),
        ("FUN_0019cff0", 0x19cff0, 0x19d070),
        ("first_person_weapon_get_marker_by_name", 0xdd190, 0xdd260),
        # gameplay wave 23 (2026-07-26)
        ("vehicle_accelerate", 0x1b5c90, 0x1b5d8c),
        ("FUN_001a4440", 0x1a4440, 0x1a4990),
        ("FUN_001a4990", 0x1a4990, 0x1a4a50),
        ("player_aim_projectile", 0xa6130, 0xa6470),
        ("get_particle_world_position", 0x1339a0, 0x134061),
        ("FUN_001336a0", 0x1336a0, 0x133750),
        ("FUN_001335e0", 0x1335e0, 0x1336a0),
        # gameplay wave 24 (2026-07-26)
        ("FUN_001a4a70", 0x1a4a70, 0x1a4c50),
        ("physics_compute_biped_collision", 0x151a50, 0x151ec0),
        ("biped_limp_noodle_valid_joint_rotation", 0x19f540, 0x19fa1c),
        ("FUN_0019fa20", 0x19fa20, 0x1a01c3),
        ("FUN_001a4c50", 0x1a4c50, 0x1a5300),
        # gameplay wave 25 (2026-07-26)
        ("FUN_00154a50", 0x154a50, 0x154fc0),
        ("weather_particle_system_render", 0xa4e20, 0xa54b0),
        ("FUN_000a0800", 0xa0800, 0xa0d50),
        ("actor_action_handle_vehicle_entry", 0x1dfa0, 0x1e360),
        ("point_physics_definition_interpolate", 0x1548c0, 0x154a20),
        # gameplay wave 26 (2026-07-26)
        ("collision_sphere_test_vector", 0x14bdb0, 0x14bf30),
        ("collision_cylinder_test_vector", 0x14bf30, 0x14c220),
        ("collision_prism_test_vector", 0x14c220, 0x14c4b0),
        ("FUN_0014c4b0", 0x14c4b0, 0x14c6d0),
        ("FUN_00154270", 0x154270, 0x1544d0),
        # gameplay wave 27 (2026-07-26)
        ("lightning_offset_marker_position", 0x135420, 0x135510),
        ("object_get_self_illumination", 0x1393b0, 0x139480),
        ("FUN_00154540", 0x154540, 0x154630),
        ("FUN_00135510", 0x135510, 0x135f1b),
        ("first_person_weapon_adjust_light", 0xdd340, 0xdd410),
        # gameplay wave 28 (2026-07-26)
        ("item_get_position_even_if_in_inventory", 0xf6a60, 0xf6ae3),
        ("FUN_00154630", 0x154630, 0x1546b0),
        ("FUN_001546b0", 0x1546b0, 0x1546f0),
        ("FUN_001546f0", 0x1546f0, 0x154750),
        ("FUN_00154750", 0x154750, 0x1547d0),
        ("FUN_001547d0", 0x1547d0, 0x15485e),
        # gameplay wave 29 (2026-07-26)
        ("vehicle_reset", 0x1b5770, 0x1b5820),
        ("vehicle_new", 0x1b5820, 0x1b5890),
        ("FUN_000dcdc0", 0xdcdc0, 0xdce00),
        ("first_person_weapon_center_flashlight", 0xdd260, 0xdd340),
        ("FUN_00145660", 0x145660, 0x14573b),
        ("FUN_00146be0", 0x146be0, 0x146d40),
        # gameplay wave 30 (2026-07-26)
        ("first_person_weapon_render_update", 0xddae0, 0xddb90),
        ("lights_initialize", 0x1391e0, 0x139290),
        ("FUN_00145580", 0x145580, 0x145610),
        ("weapon_owner_update", 0xfc4b0, 0xfc549),
        ("FUN_00085280", 0x85280, 0x85350),
        ("FUN_00145610", 0x145610, 0x145660),
        ("lights_initialize_for_new_map", 0x1392b0, 0x1392e0),
        ("lights_dispose_from_old_map", 0x1392e0, 0x139300),
        ("first_person_weapon_get_marker_by_name_render", 0xddb90, 0xddbd0),
        # gameplay wave 31 (2026-07-26)
        ("FUN_00145740", 0x145740, 0x1457b0),
        ("FUN_000de0e0", 0xde0e0, 0xde140),
        ("FUN_00139350", 0x139350, 0x1393b0),
        ("vehicle_render_debug", 0x1b5d90, 0x1b5df0),
        ("FUN_000fb990", 0xfb990, 0xfb9da),
        ("FUN_000fce60", 0xfce60, 0xfceb4),
        ("FUN_000fcdd0", 0xfcdd0, 0xfce59),
        # gameplay wave 32 (2026-07-26)
        ("FUN_000f5660", 0xf5660, 0xf56a8),
        ("FUN_000f56b0", 0xf56b0, 0xf56fb),
        ("object_postprocess_node_matrices", 0x13df70, 0x13dfc0),
        ("weapon_reloading", 0xfc690, 0xfc70a),
        ("FUN_000fb510", 0xfb510, 0xfb594),
        ("weapon_trigger_release_charge", 0xfb880, 0xfb904),
        ("FUN_000fcd10", 0xfcd10, 0xfcdcd),
        ("weapon_new", 0xfbd10, 0xfbe94),
        # gameplay wave 33 (2026-07-26)
        ("lights_enable", 0x139300, 0x139310),
        ("light_delete", 0x139310, 0x139350),
        ("first_person_weapon_message_from_unit", 0xde360, 0xde3f0),
        ("FUN_000fcec0", 0xfcec0, 0xfcf13),
        ("FUN_000fcc90", 0xfcc90, 0xfcd0a),
        ("FUN_000f5640", 0xf5640, 0xf5650),
        ("FUN_000f5650", 0xf5650, 0xf5660),
        ("items_initialize", 0xf5f90, 0xf5fa0),
        ("items_initialize_for_new_map", 0xf5fa0, 0xf5fb0),
        ("breakable_surfaces_reset", 0x1459d0, 0x1459e0),
        ("weapon_delete", 0xfbea0, 0xfbf00),
        # gameplay wave 34 (2026-07-26)
        ("FUN_00145560", 0x145560, 0x145580),
        ("object_get_type", 0xf5f10, 0xf5f30),
        ("FUN_00154a20", 0x154a20, 0x154a50),
        ("render_debug_collision_sphere", 0x14ad60, 0x14ad80),
        ("render_debug_collision_cylinder", 0x14ad80, 0x14adb0),
        ("object_propagate_flag_to_children", 0x13ee60, 0x13eef6),
        ("weapon_build_weapon_interface_state", 0xfc550, 0xfc690),
        ("FUN_000fb5a0", 0xfb5a0, 0xfb68a),
        # gameplay wave 35 (2026-07-26)
        ("FUN_001b5500", 0x1b5500, 0x1b5540),
        ("vehicle_causes_collision_damage", 0x1b5580, 0x1b55b0),
        ("vehicle_hover", 0x1b55c0, 0x1b55f0),
        ("biped_approximate_surface_index", 0x1a1b90, 0x1a1bb2),
        ("first_person_weapon_get_marker_by_name_render", 0xddb90, 0xddbd0),
        ("weapon_get_zoom_magnification", 0xfc780, 0xfc8e0),
        ("FUN_000fd0b0", 0xfd0b0, 0xfd145),
        ("FUN_001a8910", 0x1a8910, 0x1a892e),
        # gameplay wave 36 (2026-07-26)
        ("FUN_000f5800", 0xf5800, 0xf58c6),
        ("FUN_000fb990", 0xfb990, 0xfb9da),
        ("FUN_000fcdd0", 0xfcdd0, 0xfce59),
        ("FUN_000fce60", 0xfce60, 0xfceb4),
        ("FUN_00135f20", 0x135f20, 0x135f4c),
        ("object_update_children_recursive", 0x1446a0, 0x144730),
        ("FUN_001a8950", 0x1a8950, 0x1a898e),
        ("FUN_001b5610", 0x1b5610, 0x1b5657),
        ("vehicle_is_flipped", 0x1b5680, 0x1b56ac),
        ("weapon_useful", 0xfafe0, 0xfb00c),
        # gameplay wave 37 (2026-07-26)
        ("FUN_001a8770", 0x1a8770, 0x1a8782),
        ("FUN_001a8890", 0x1a8890, 0x1a88ad),
        ("FUN_001a8910", 0x1a8910, 0x1a892e),
        ("weapon_reloading", 0xfc690, 0xfc70a),
        ("FUN_000fb510", 0xfb510, 0xfb594),
        ("FUN_000fb690", 0xfb690, 0xfb6d6),
        ("weapon_trigger_release_charge", 0xfb880, 0xfb904),
        ("FUN_001b56b0", 0x1b56b0, 0x1b5747),
        ("FUN_001b5ff0", 0x1b5ff0, 0x1b613b),
        # gameplay wave 38 (2026-07-26)
        ("FUN_001b6140", 0x1b6140, 0x1b624a),
        ("FUN_000fb5a0", 0xfb5a0, 0xfb68a),
        ("FUN_000fcc90", 0xfcc90, 0xfcd0a),
        ("FUN_000fcd10", 0xfcd10, 0xfcdcd),
        ("FUN_000fcec0", 0xfcec0, 0xfcf13),
        ("FUN_000fd0b0", 0xfd0b0, 0xfd145),
        ("object_propagate_flag_to_children", 0x13ee60, 0x13eef6),
        ("FUN_00138f30", 0x138f30, 0x138f69),
        ("FUN_00138f70", 0x138f70, 0x138fc5),
        # gameplay wave 39 (2026-07-26)
        ("biped_approximate_surface_index", 0x1a1b90, 0x1a1bb2),
        ("object_get_maximum_shield_vitality", 0x136700, 0x136741),
        ("FUN_000f5660", 0xf5660, 0xf56a8),
        ("FUN_000f56b0", 0xf56b0, 0xf56fb),
        ("weapon_owner_update", 0xfc4b0, 0xfc549),
        ("FUN_001b5f20", 0x1b5f20, 0x1b5fed),
        ("FUN_00145660", 0x145660, 0x14573b),
        ("weapon_compute_movement_penalty", 0xfb010, 0xfb07c),
        ("FUN_00138fd0", 0x138fd0, 0x1390cf),
        # gameplay wave 40 (2026-07-26)
        ("vehicle_accelerate", 0x1b5c90, 0x1b5d8c),
        ("FUN_001a1e70", 0x1a1e70, 0x1a1fa6),
        ("FUN_001b5400", 0x1b5400, 0x1b54fb),
        ("FUN_001b6ca0", 0x1b6ca0, 0x1b6e11),
        ("vehicle_stuck", 0x1b8060, 0x1b81c7),
        # gameplay wave 41 (2026-07-26)
        ("FUN_001a1fb0", 0x1a1fb0, 0x1a215b),
        ("FUN_000f4b60", 0xf4b60, 0xf4cec),
        ("FUN_00134070", 0x134070, 0x134292),
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        ("FUN_001b6e20", 0x1b6e20, 0x1b7016),
        # gameplay wave 42 (2026-07-26)
        ("weapon_new", 0xfbd10, 0xfbe94),
        ("FUN_001b7020", 0x1b7020, 0x1b72a5),
        ("FUN_000f4cf0", 0xf4cf0, 0xf4e92),
        ("FUN_001b72b0", 0x1b72b0, 0x1b74c6),
        ("FUN_00136b40", 0x136b40, 0x136bbe),
        # gameplay wave 43 (2026-07-26)
        ("FUN_001b6560", 0x1b6560, 0x1b69a0),
        ("vehicle_export_function_values", 0x1b79c0, 0x1b7e48),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c8a),
        ("FUN_001b81d0", 0x1b81d0, 0x1b856c),
        ("FUN_001b74d0", 0x1b74d0, 0x1b77e1),
        # gameplay wave 44 (2026-07-26)
        ("FUN_001a4c50", 0x1a4c50, 0x1a5300),
        ("FUN_001b4dc0", 0x1b4dc0, 0x1b53f3),
        ("FUN_001a4440", 0x1a4440, 0x1a4990),
        ("biped_limp_noodle_valid_joint_rotation", 0x19f540, 0x19fa1c),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        # gameplay wave 45 (2026-07-26)
        ("FUN_001b8570", 0x1b8570, 0x1b8f08),
        ("FUN_00135510", 0x135510, 0x135f1b),
        ("item_update", 0xf7340, 0xf7ca1),
        ("FUN_0019fa20", 0x19fa20, 0x1a01c3),
        ("FUN_000fd570", 0xfd570, 0xfdc87),
        # gameplay wave 46 (2026-07-26)
        ("get_particle_world_position", 0x1339a0, 0x134061),
        ("FUN_000de560", 0xde560, 0xdeb4f),
        ("first_person_weapon_update", 0xdd580, 0xddad8),
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00136bc0", 0x136bc0, 0x136f3e),
        # gameplay wave 47 (2026-07-26)
        ("FUN_000f1710", 0xf1710, 0xf1ecc),
        ("FUN_000f5900", 0xf5900, 0xf5ee5),
        ("FUN_00138900", 0x138900, 0x138e11),
        ("FUN_001b6250", 0x1b6250, 0x1b6555),
        ("FUN_001b69a0", 0x1b69a0, 0x1b6c9a),
        ("weapon_export_function_values", 0xfbf00, 0xfc243),
        # gameplay wave 48 (2026-07-26)
        ("FUN_0013b380", 0x13b380, 0x13bcd4),
        ("FUN_001b0630", 0x1b0630, 0x1b0cf7),
        ("FUN_00122e50", 0x122e50, 0x123463),
        ("FUN_001afd30", 0x1afd30, 0x1b04af),
        ("FUN_00143550", 0x143550, 0x1439fb),
        ("FUN_001b1400", 0x1b1400, 0x1b1a10),
        # gameplay wave 49 (2026-07-26)
        ("FUN_000853c0", 0x853c0, 0x85a24),
        ("objects_garbage_collect_tick", 0x144b50, 0x14516d),
        ("FUN_00084ae0", 0x84ae0, 0x84fde),
        ("item_set_position", 0xf6d60, 0xf7103),
        ("FUN_00139e50", 0x139e50, 0x13a242),
        ("unit_aiming_vector", 0x1ab410, 0x1ab76b),
        # gameplay wave 50 (2026-07-26)
        ("FUN_001a2f40", 0x1a2f40, 0x1a440a),
        ("FUN_001b3690", 0x1b3690, 0x1b4da9),
        ("FUN_000f9c40", 0xf9c40, 0xfac17),
        ("FUN_000f90d0", 0xf90d0, 0xf9c28),
        ("object_cause_damage", 0x137d20, 0x1384d3),
        ("FUN_001ac680", 0x1ac680, 0x1acd66),
        # gameplay wave 51 (2026-07-26)
        ("object_compute_node_matrices", 0x141b70, 0x14350a),
        ("FUN_001a03c0", 0x1a03c0, 0x1a0859),
        ("unit_cause_player_melee_damage", 0x1aea90, 0x1af0ca),
        ("FUN_001234b0", 0x1234b0, 0x12398d),
        ("unit_throw_grenade_begin", 0x1b2090, 0x1b2239),
        ("FUN_00136f40", 0x136f40, 0x137158),
        ("weapon_overcharged", 0xfb2f0, 0xfb508),
        ("object_damage_update", 0x1384e0, 0x1388f3),
        # gameplay wave 52 (2026-07-26)
        ("objects_dump_memory", 0x13f4b0, 0x13f9e8),
        ("unit_clip_to_aiming_bounds", 0x1ada90, 0x1adea5),
        ("FUN_001a68d0", 0x1a68d0, 0x1a6c9e),
        ("unit_set_control", 0x1af990, 0x1afd2a),
        ("unit_update_running_blind", 0x1af340, 0x1af6a7),
        ("FUN_001a71c0", 0x1a71c0, 0x1a74c9),
        ("unit_find_best_enter_seat", 0x1ad800, 0x1ada86),
        ("unit_exit_seat_end", 0x1b2dd0, 0x1b3055),
        # gameplay wave 53 (2026-07-26)
        ("FUN_001a6350", 0x1a6350, 0x1a6796),
        ("FUN_00121d60", 0x121d60, 0x122059),
        ("animation_get_node_orientations", 0x121640, 0x121938),
        ("FUN_001ab110", 0x1ab110, 0x1ab40a),
        ("FUN_001a7790", 0x1a7790, 0x1a7a88),
        ("unit_board_vehicle", 0x1b2b80, 0x1b2dcf),
        ("unit_control_trace", 0x1af6b0, 0x1af98f),
        ("unit_impact_melee_damage", 0x1b2290, 0x1b24ca),
        # gameplay wave 54 (2026-07-26)
        ("FUN_00137690", 0x137690, 0x1377c3),
        ("FUN_00137170", 0x137170, 0x13736e),
        ("FUN_00141970", 0x141970, 0x141b38),
        ("unit_record_damage", 0x1a8ee0, 0x1a912a),
        ("unit_cause_melee_damage", 0x1ae840, 0x1aea8a),
        ("FUN_001abd90", 0x1abd90, 0x1ac028),
        ("FUN_001a25e0", 0x1a25e0, 0x1a27fe),
        ("FUN_000f5750", 0xf5750, 0xf58f3),
        # gameplay wave 55 (2026-07-26)
        ("biped_fix_position", 0x1a1430, 0x1a18f9),
        ("overlay_animation_apply_continuous_scaled", 0x121940, 0x121c27),
        ("FUN_001acd70", 0x1acd70, 0x1acf90),
        ("FUN_001a01d0", 0x1a01d0, 0x1a03bd),
        ("unit_render_debug", 0x1ad060, 0x1ad260),
        ("unit_adjust_plan_overlap", 0x1acb70, 0x1acd67),
        ("unit_died", 0x1b3060, 0x1b32ce),
        ("FUN_001a2b90", 0x1a2b90, 0x1a2d8e),
        # gameplay wave 56 (2026-07-26)
        # Ends stop at final RET (before align nop / JT); multi-JT uses skips.
        ("FUN_001ad260", 0x1ad260, 0x1ad713),
        ("FUN_001b0d90", 0x1b0d90, 0x1b1229),
        (
            "unit_impulse_to_animation_kind",
            0x1a9560,
            0x1a979d,
            [(0x1a969c, 0x1a96d4), (0x1a96d4, 0x1a96dc)],
        ),
        ("unit_animation_start_action", 0x1a8990, 0x1a8af8),
        ("FUN_001a2440", 0x1a2440, 0x1a25c0),
        ("FUN_001a0be0", 0x1a0be0, 0x1a0da9),
        ("structure_test_vector", 0x198cb0, 0x198f0a),
        ("game_engine_get_score_hud_text", 0xac4e0, 0xac9d8),
        # gameplay wave 57 (2026-07-26)
        ("FUN_001a6e20", 0x1a6e20, 0x1a6ee1),
        ("unit_adjust_projectile_ray", 0x1acf90, 0x1ad051),
        ("FUN_0013ab20", 0x13ab20, 0x13aec9),
        ("FUN_0013cf50", 0x13cf50, 0x13d567),
        ("FUN_00134e80", 0x134e80, 0x135209),
        ("FUN_001a6ef0", 0x1a6ef0, 0x1a70c1),
        ("FUN_000f8920", 0xf8920, 0xf8d27),
        ("FUN_001b2780", 0x1b2780, 0x1b2b7d),
        # gameplay wave 58 (2026-07-26)
        ("FUN_000f4ea0", 0xf4ea0, 0xf528c),
        ("FUN_0013bce0", 0x13bce0, 0x13c02c),
        ("FUN_0013a740", 0x13a740, 0x13aa0d),
        ("FUN_0013cb80", 0x13cb80, 0x13cdc4),
        ("FUN_000f8720", 0xf8720, 0xf8912),
        ("unit_drop_weapons_on_death", 0x1abbd0, 0x1abcca),
        ("vehicle_scripting_load_magic", 0x1b3400, 0x1b357a),
        ("FUN_000fc990", 0xfc990, 0xfcaef),
        ("FUN_001a2900", 0x1a2900, 0x1a2a59),
        ("vehicle_scripting_find_available_seats", 0x1adfc0, 0x1ae14c),
        # gameplay wave 59 (2026-07-26)
        ("FUN_00139c20", 0x139c20, 0x139e47),
        ("FUN_0013a420", 0x13a420, 0x13a5e8),
        ("FUN_0009ec30", 0x9ec30, 0x9ee33),
        ("FUN_001aaf40", 0x1aaf40, 0x1ab108),
        ("unit_set_seat_state", 0x1a9240, 0x1a93de),
        ("FUN_001ae490", 0x1ae490, 0x1ae5f8),
        ("FUN_001a74d0", 0x1a74d0, 0x1a7638),
        ("unit_scripting_enter_vehicle", 0x1b32d0, 0x1b33f8),
        ("FUN_001a2160", 0x1a2160, 0x1a228a),
        ("objects_reconnect_to_structure_bsp", 0x1417c0, 0x1418fa),
        # gameplay wave 60 (2026-07-26)
        ("find_objects_from_point_vector", 0x13f120, 0x13f378),
        ("FUN_00135210", 0x135210, 0x1353a1),
        ("FUN_001a0680", 0x1a0680, 0x1a07b1),
        ("FUN_001a2290", 0x1a2290, 0x1a243d),
        ("FUN_001b04b0", 0x1b04b0, 0x1b0629),
        ("FUN_000ae110", 0xae110, 0xae247),
        ("FUN_001a8b20", 0x1a8b20, 0x1a8ca0),
        ("FUN_001a9f20", 0x1a9f20, 0x1aa071),
        ("FUN_00136150", 0x136150, 0x1362c4),
        ("FUN_001a1a10", 0x1a1a10, 0x1a1b8b),
        # gameplay wave 61 (2026-07-26)
        (
            "virtual_keyboard_process_input",
            0xf63f0,
            0xf66ea,
            [(0xf66ec, 0xf673c)],
        ),
        ("FUN_00145490", 0x145490, 0x145551),
        ("FUN_00134ae0", 0x134ae0, 0x134bd1),
        ("FUN_001a8550", 0x1a8550, 0x1a868f),
        ("FUN_001a7ea0", 0x1a7ea0, 0x1a7f71),
        ("FUN_001a6d10", 0x1a6d10, 0x1a6e19),
        ("FUN_000adf70", 0xadf70, 0xae0a0),
        ("FUN_001a9c90", 0x1a9c90, 0x1a9d99),
        ("FUN_0013a5f0", 0x13a5f0, 0x13a738),
        ("unit_try_and_exit_seat", 0x1b3580, 0x1b3690),
        ("FUN_001390d0", 0x1390d0, 0x1391d9),
        ("unit_place", 0x1b24d0, 0x1b2610),
        ("FUN_0013aa10", 0x13aa10, 0x13ab20),
        # gameplay wave 62 (2026-07-26)
        ("FUN_00139a30", 0x139a30, 0x139b3f),
        ("FUN_001414e0", 0x1414e0, 0x1415e6),
        ("FUN_0013a250", 0x13a250, 0x13a333),
        ("FUN_0013a340", 0x13a340, 0x13a420),
        ("FUN_001a2800", 0x1a2800, 0x1a2900),
        ("unit_melee_attack_begin", 0x1b1b60, 0x1b1c49),
        ("FUN_001a7b50", 0x1a7b50, 0x1a7c6f),
        ("FUN_001a0f10", 0x1a0f10, 0x1a101a),
        ("FUN_0013ce90", 0x13ce90, 0x13cf4e),
        ("unit_create_initial_weapons", 0x1b2660, 0x1b273b),
        ("FUN_0013b290", 0x13b290, 0x13b377),
        ("FUN_001a7650", 0x1a7650, 0x1a7723),
        # gameplay wave 63 (2026-07-26)
        ("FUN_000ae250", 0xae250, 0xae30d),
        ("FUN_001a0a40", 0x1a0a40, 0x1a0b29),
        ("FUN_001362d0", 0x1362d0, 0x1363c6),
        ("FUN_001a0e00", 0x1a0e00, 0x1a0f01),
        ("FUN_0009eb40", 0x9eb40, 0x9ec29),
        ("FUN_001a70d0", 0x1a70d0, 0x1a71b6),
        ("FUN_0013cdd0", 0x13cdd0, 0x13ce8d),
        ("FUN_0013f080", 0x13f080, 0x13f11a),
        ("FUN_000fcaf0", 0xfcaf0, 0xfcbc1),
        ("FUN_0013dcc0", 0x13dcc0, 0x13dda0),
        ("FUN_0013b1b0", 0x13b1b0, 0x13b286),
        ("FUN_000fad00", 0xfad00, 0xfad51),
        # gameplay wave 64 (2026-07-26)
        ("FUN_001365d0", 0x1365d0, 0x1366a6),
        ("FUN_001a6bf0", 0x1a6bf0, 0x1a6c9e),
        ("FUN_00139b40", 0x139b40, 0x139c1d),
        ("FUN_0013c2e0", 0x13c2e0, 0x13c39a),
        ("FUN_000f68b0", 0xf68b0, 0xf6901),
        ("FUN_001a6280", 0x1a6280, 0x1a634b),
        ("FUN_00085180", 0x85180, 0x85252),
        ("FUN_000fac20", 0xfac20, 0xfacdf),
        ("FUN_001aa430", 0x1aa430, 0x1aa4c5),
        ("FUN_00139810", 0x139810, 0x1398a1),
        ("FUN_000f8640", 0xf8640, 0xf8718),
        ("FUN_001a2a60", 0x1a2a60, 0x1a2b09),
        # gameplay wave 65 (2026-07-26)
        ("FUN_001a7df0", 0x1a7df0, 0x1a7e62),
        ("FUN_00135f90", 0x135f90, 0x136034),
        ("FUN_0013c490", 0x13c490, 0x13c4f5),
        ("FUN_000f6b80", 0xf6b80, 0xf6c31),
        ("FUN_00139990", 0x139990, 0x139a21),
        ("FUN_001a0b30", 0x1a0b30, 0x1a0bd5),
        ("FUN_0013ddd0", 0x13ddd0, 0x13de73),
        ("FUN_00136a00", 0x136a00, 0x136a7e),
        ("FUN_0013c100", 0x13c100, 0x13c1ad),
        ("FUN_000f8590", 0xf8590, 0xf8634),
        ("FUN_00138e30", 0x138e30, 0x138ea4),
        ("object_new_by_name", 0x144940, 0x1449a5),
        # gameplay wave 66 (2026-07-26)
        ("FUN_0013c080", 0x13c080, 0x13c0fc),
        ("FUN_00140750", 0x140750, 0x1407d6),
        ("FUN_001a7ad0", 0x1a7ad0, 0x1a7b42),
        ("FUN_001a2b10", 0x1a2b10, 0x1a2b8e),
        ("FUN_001363d0", 0x1363d0, 0x136447),
        ("FUN_0013dc10", 0x13dc10, 0x13dca7),
        ("FUN_0008dc30", 0x8dc30, 0x8dca3),
        ("FUN_000f7e60", 0xf7e60, 0xf7ebc),
        ("FUN_0013c250", 0x13c250, 0x13c2dd),
        ("FUN_0013c1b0", 0x13c1b0, 0x13c241),
        ("FUN_0013c5c0", 0x13c5c0, 0x13c61f),
        ("FUN_0013c740", 0x13c740, 0x13c79f),
        # gameplay wave 67 (2026-07-26)
        ("FUN_0013c980", 0x13c980, 0x13c9dc),
        ("FUN_0013c6e0", 0x13c6e0, 0x13c73c),
        ("FUN_001ab8c0", 0x1ab8c0, 0x1ab937),
        ("FUN_000ae0a0", 0xae0a0, 0xae101),
        ("unit_leap_begin", 0x1b1c70, 0x1b1cdf),
        ("FUN_0013ca30", 0x13ca30, 0x13caaf),
        ("FUN_001a7d80", 0x1a7d80, 0x1a7de5),
        ("FUN_0013db60", 0x13db60, 0x13dbd1),
        ("FUN_0013c800", 0x13c800, 0x13c858),
        ("FUN_0013c7a0", 0x13c7a0, 0x13c7f8),
        ("FUN_0013c680", 0x13c680, 0x13c6d8),
        ("FUN_0013c500", 0x13c500, 0x13c558),
        # gameplay wave 68 (2026-07-26)
        ("FUN_0013c430", 0x13c430, 0x13c488),
        ("FUN_0013d8b0", 0x13d8b0, 0x13d91e),
        ("FUN_0013c860", 0x13c860, 0x13c8b1),
        ("FUN_0013c920", 0x13c920, 0x13c971),
        ("FUN_0013c8c0", 0x13c8c0, 0x13c911),
        ("FUN_0013c620", 0x13c620, 0x13c671),
        ("FUN_0013c560", 0x13c560, 0x13c5b1),
        ("FUN_001a7730", 0x1a7730, 0x1a778e),
        ("FUN_001abd10", 0x1abd10, 0x1abd81),
        ("FUN_00141900", 0x141900, 0x14196b),
        ("FUN_001a6870", 0x1a6870, 0x1a68cc),
        ("FUN_0013cab0", 0x13cab0, 0x13cb22),
        # gameplay wave 69 (2026-07-26)
        ("unit_has_night_vision_weapon", 0x1b13a0, 0x1b1400),
        ("FUN_0013c9e0", 0x13c9e0, 0x13ca27),
        ("FUN_001a7c70", 0x1a7c70, 0x1a7cb3),
        ("FUN_0013b150", 0x13b150, 0x13b1af),
        ("FUN_000f52f0", 0xf52f0, 0xf5384),
        ("FUN_001398d0", 0x1398d0, 0x139927),
        ("FUN_001a67e0", 0x1a67e0, 0x1a6820),
        ("FUN_000f6750", 0xf6750, 0xf67b0),
        ("FUN_00136840", 0x136840, 0x13688f),
        ("FUN_001360a0", 0x1360a0, 0x1360fe),
        ("FUN_001a6cd0", 0x1a6cd0, 0x1a6d0f),
        ("FUN_000f7fa0", 0xf7fa0, 0xf7ff8),
        # gameplay wave 70 (2026-07-26)
        ("valid_real_matrix4x3", 0xf6d00, 0xf6d51),
        ("FUN_001ab870", 0x1ab870, 0x1ab8b9),
        ("FUN_0013c030", 0x13c030, 0x13c077),
        ("FUN_001aa360", 0x1aa360, 0x1aa3bf),
        ("FUN_00136040", 0x136040, 0x136097),
        ("FUN_00136890", 0x136890, 0x1368d6),
        ("objects_scripting_attach", 0x144ae0, 0x144b21),
        ("FUN_0013cb30", 0x13cb30, 0x13cb7d),
        ("FUN_001a6820", 0x1a6820, 0x1a6867),
        ("FUN_00136100", 0x136100, 0x136150),
        # gameplay wave 71 (2026-07-26) — AI/HS next-domain large weaks
        ("FUN_00038e60", 0x38e60, 0x39c2f, [(0x39c30, 0x39c74)]),
        ("FUN_0003dc20", 0x3dc20, 0x3e56c),
        ("FUN_00022390", 0x22390, 0x22b3b),
        ("FUN_00017120", 0x17120, 0x17838, [(0x17838, 0x178a8)]),
        ("FUN_000cb230", 0xcb230, 0xcb70d, [(0xcb710, 0xcb7ac)]),
        ("FUN_00024cf0", 0x24cf0, 0x25333),
        ("FUN_00018b90", 0x18b90, 0x190bf, [(0x190c0, 0x190f0)]),
        ("FUN_00055dd0", 0x55dd0, 0x56318),
        ("FUN_00038370", 0x38370, 0x3887f),
        ("FUN_000559a0", 0x559a0, 0x55dcb),
        ("FUN_000c6d90", 0xc6d90, 0xc71bd),
        ("FUN_00027410", 0x27410, 0x27869),
        # gameplay wave 72 (2026-07-26)
        ("FUN_0005a6e0", 0x5a6e0, 0x5aaa3),
        ("FUN_000425c0", 0x425c0, 0x42a2a),
        ("FUN_000c74c0", 0xc74c0, 0xc783b),
        ("FUN_00021ae0", 0x21ae0, 0x21e48),
        ("FUN_00014770", 0x14770, 0x14b38),
        ("FUN_00013ef0", 0x13ef0, 0x14292),
        ("FUN_00015520", 0x15520, 0x15863),
        ("FUN_0003f030", 0x3f030, 0x3f34d),
        ("FUN_00019370", 0x19370, 0x19748),
        ("FUN_00016590", 0x16590, 0x1694e),
        ("FUN_00036f20", 0x36f20, 0x37240),
        ("FUN_000cd840", 0xcd840, 0xcdb2a),
        # gameplay wave 73 (2026-07-26)
        ("FUN_0003e7a0", 0x3e7a0, 0x3eaa3),
        ("FUN_00037d50", 0x37d50, 0x37fcb),
        ("FUN_0003c410", 0x3c410, 0x3c7b5),
        ("FUN_00038880", 0x38880, 0x38adf),
        ("FUN_00039c80", 0x39c80, 0x39f2e),
        ("FUN_0005af70", 0x5af70, 0x5b1b3),
        ("FUN_00055350", 0x55350, 0x5561a),
        ("FUN_0001a7e0", 0x1a7e0, 0x1aadc),
        ("FUN_000c6b00", 0xc6b00, 0xc6d81),
        ("FUN_00039f30", 0x39f30, 0x3a159),
        ("FUN_00027090", 0x27090, 0x272c9),
        ("FUN_0005a120", 0x5a120, 0x5a3ac),
        # gameplay wave 74 (2026-07-26)
        ("FUN_00027ff0", 0x27ff0, 0x2824a),
        ("FUN_000169a0", 0x169a0, 0x16b89),
        ("FUN_0001ac00", 0x1ac00, 0x1acaf),
        ("FUN_0002a2b0", 0x2a2b0, 0x2a32a),
        ("FUN_000272d0", 0x272d0, 0x27404),
        ("FUN_000192b0", 0x192b0, 0x1936d),
        ("FUN_00019c70", 0x19c70, 0x19d00),
        ("FUN_0001a080", 0x1a080, 0x1a0f9),
        ("FUN_00015040", 0x15040, 0x15149),
        ("FUN_00016210", 0x16210, 0x163c6),
        ("FUN_00014e90", 0x14e90, 0x14feb),
        ("FUN_00019940", 0x19940, 0x19ac0),
        # gameplay wave 75 (2026-07-26)
        ("FUN_00025c10", 0x25c10, 0x27079),
        ("FUN_00027a60", 0x27a60, 0x27dc5),
        ("FUN_00046f10", 0x46f10, 0x4907e, [(298604, 298640), (298624, 298640)]),
        ("FUN_00016050", 0x16050, 0x16209),
        ("FUN_000278e0", 0x278e0, 0x27a57),
        ("FUN_000153e0", 0x153e0, 0x1551e),
        ("FUN_000159d0", 0x159d0, 0x15b12),
        ("FUN_0001a420", 0x1a420, 0x1a58d),
        ("FUN_00013dd0", 0x13dd0, 0x13eee),
        ("FUN_00019b20", 0x19b20, 0x19c61),
        ("actor_look_secondary_stop", 0x16bd0, 0x16c3e),
        ("FUN_00016ff0", 0x16ff0, 0x1705a),
        # gameplay wave 76 (2026-07-26)
        ("FUN_00015f60", 0x15f60, 0x15ffd),
        ("FUN_00014480", 0x14480, 0x1450d),
        ("FUN_00014540", 0x14540, 0x145bc),
        ("FUN_00015880", 0x15880, 0x158fb),
        ("FUN_0001a600", 0x1a600, 0x1a666),
        ("FUN_00014ba0", 0x14ba0, 0x14c03),
        ("FUN_00024ca0", 0x24ca0, 0x24cee),
        ("FUN_00016cf0", 0x16cf0, 0x16d38),
        # gameplay wave 77 (2026-07-26) — math/networking + leftover looking
        ("sieve_of_eratosthenes", 0x80d50, 0x80ea4),
        ("message_encrypt", 0x80940, 0x80a32),
        ("message_decrypt", 0x80a40, 0x80b38),
        ("FUN_00012ad0", 0x12ad0, 0x12bd9),
        ("FUN_001139d0", 0x1139d0, 0x113a89),
        ("tea_decrypt", 0x808b0, 0x8093f),
        ("key_agreement_build_message", 0x803d0, 0x80463),
        ("FUN_00113930", 0x113930, 0x1139c7),
        ("tea_encrypt", 0x80820, 0x808a8),
        ("create_message", 0x80ca0, 0x80d27),
        ("key_agreement_peek_packet_type", 0x80530, 0x8059d),
        ("key_message_xor_keystream", 0x807d0, 0x80817),
        ("FUN_00027a10", 0x27a10, 0x27a57),
        # gameplay wave 78 (2026-07-26) — full-extent AI/networking leftovers
        ("actor_look_update", 0x29040, 0x2a288),
        ("FUN_00015cf0", 0x15cf0, 0x15ea9),
        ("FUN_0001a670", 0x1a670, 0x1a7df),
        ("actor_look_compute_prop_interest", 0x16d40, 0x16e62),
        ("FUN_000197d0", 0x197d0, 0x198c6),
        ("build_message_header", 0x80b40, 0x80c20),
        ("FUN_00015900", 0x15900, 0x159c4),
        ("byte_swap_message_header", 0x80c20, 0x80c92),
        ("FUN_00014620", 0x14620, 0x1465a),
        ("actor_clear_aim_target", 0x17060, 0x1708e),
        ("prime_compare", 0x80d30, 0x80d4c),
        # gameplay wave 79 (2026-07-26) — rasterizer/path/props Capstone weaks
        ("rasterizer_transparent_geometry_group_draw", 0x174d10, 0x17878f, [(0x178790, 0x1787b8), (0x1787b8, 0x1787d8), (0x1787d8, 0x1787f8), (0x1787f8, 0x178818)]),
        ("FUN_0002bd80", 0x2bd80, 0x2cda2),
        ("prop_status_refresh", 0x33440, 0x3429a),
        ("actor_move_update", 0x2e560, 0x2f198),
        ("actor_move_compute_facing", 0x2daa0, 0x2e521, [(0x2e524, 0x2e534), (0x2e534, 0x2e544), (0x2e544, 0x2e558)]),
        ("FUN_00181c20", 0x181c20, 0x1824d2),
        ("FUN_0005f740", 0x5f740, 0x5ff6d),
        ("actor_perception_refresh_danger_zone", 0x32380, 0x32940),
        ("FUN_0011de10", 0x11de10, 0x11e326),
        ("actor_path_refresh", 0x2cdb0, 0x2d333, [(0x2d334, 0x2d344)]),
        ("path_state_build_path", 0x5eae0, 0x5ef80),
        ("FUN_001800b0", 0x1800b0, 0x1804e9),
        # gameplay wave 80 (2026-07-26) — game/AI/render/structures Capstone weaks
        ("game_engine_player_killed", 0xaf660, 0xaf997),
        ("actor_destination_update", 0x2d350, 0x2d718),
        ("actor_visibility_at_point", 0x314f0, 0x3183d, [(0x31840, 0x31850)]),
        ("prop_position_refresh", 0x31df0, 0x3216b),
        ("render_scene", 0x184ea0, 0x185281),
        ("FUN_0002b020", 0x2b020, 0x2b307),
        ("convex_hull2d_reduce", 0x105d20, 0x106022),
        ("actor_action_handle_evasion", 0x20670, 0x20985),
        ("bsp3d_clip_line_to_leaves", 0x146e30, 0x1470aa),
        ("rasterizer_text_cache_character", 0x183880, 0x183bfc),
        ("actor_action_try_to_dive", 0x1fe70, 0x20120, [(0x20120, 0x20130), (0x20130, 0x20140)]),
        ("FUN_0002bab0", 0x2bab0, 0x2bd7d),
        # gameplay wave 81 (2026-07-26) — rasterizer/AI/net Capstone weaks
        ("rasterizer_draw_dynamic_vertices", 0x15d5b0, 0x15d8a1),
        ("FUN_00195790", 0x195790, 0x1959ec),
        ("FUN_0002b830", 0x2b830, 0x2baa2),
        ("FUN_0002ade0", 0x2ade0, 0x2b01b),
        ("FUN_0011beb0", 0x11beb0, 0x11c0f0),
        ("actor_perception_desire_prop", 0x2f6e0, 0x2f905),
        ("rasterizer_present", 0x157e40, 0x1580ab),
        ("actor_move_try_evasion_vector", 0x2a8f0, 0x2ab3d),
        ("FUN_00064cd0", 0x64cd0, 0x64e7e, [(0x64e80, 0x64ea4)]),
        ("prop_add", 0x64170, 0x643c2),
        ("FUN_0005ef80", 0x5ef80, 0x5f1cc),
        ("prop_new_unacknowledged", 0x645a0, 0x647c0),
        # gameplay wave 82 (2026-07-26) — net/structures/physics Capstone weaks
        ("FUN_0011bc20", 0x11bc20, 0x11be0b),
        ("FUN_00062680", 0x62680, 0x628a7),
        ("cluster_partition_add_object", 0x1917a0, 0x19199f),
        ("actor_pursuit_find_nearby_actors", 0x20280, 0x20468),
        ("FUN_00032170", 0x32170, 0x32377),
        ("collision_surface_test_line2d", 0x147d10, 0x147ecc),
        ("actor_perception_unit_from_swarm", 0x31c00, 0x31de4),
        ("collision_surface_area", 0x1477f0, 0x14798c),
        ("structure_render_surface_from_point_and_leaf", 0x198580, 0x198726),
        ("FUN_00197310", 0x197310, 0x1974e4),
        ("FUN_0011b2a0", 0x11b2a0, 0x11b520, [(0x11b520, 0x11b540)]),
        ("FUN_00197130", 0x197130, 0x19730b),
        # gameplay wave 83 (2026-07-26) — memory/AI/math/objects Capstone weaks
        ("FUN_0011c5f0", 0x11c5f0, 0x11c774),
        ("structure_clusters_in_cone", 0x198ad0, 0x198cac),
        ("actor_action_try_to_evade", 0x1fca0, 0x1fe6b),
        ("lrar_cache_new", 0x11c870, 0x11ca20),
        ("convex_polygon3d_verify", 0x106dc0, 0x106f43),
        ("actor_get_stopping_distances", 0x2a610, 0x2a7d1),
        ("FUN_001108b0", 0x1108b0, 0x110a0c),
        ("network_game_server_stalled_on_client", 0x12e1d0, 0x12e395),
        ("actor_move_try_evasion_direction", 0x2ab40, 0x2acc1, [(0x2acc4, 0x2acd8)]),
        ("FUN_00064b40", 0x64b40, 0x64ccb),
        ("object_update", 0x1444f0, 0x144694),
        ("build_path_edges_for_surface", 0x5f240, 0x5f3b4),
        # gameplay wave 84 (2026-07-26) — cache/net/AI/memory Capstone weaks
        ("cache_file_read_header_into_slot", 0x1bd020, 0x1bd1a4),
        ("array_resize", 0x117b90, 0x117cee),
        ("actor_perception_find_sense_position", 0x31a90, 0x31bfb),
        ("FUN_0011aa40", 0x11aa40, 0x11abac),
        ("FUN_0011ba50", 0x11ba50, 0x11bb70),
        ("actor_expected_acknowledgement", 0x32940, 0x32aba),
        ("rasterizer_text_draw_cached_chars", 0x183cf0, 0x183e52),
        ("FUN_0011a770", 0x11a770, 0x11a8b9, [(0x11a8bc, 0x11a8d0)]),
        ("actor_move_get_avoidance_direction", 0x2b5d0, 0x2b71b),
        ("convex_hull2d_test_vector", 0x1063f0, 0x106503),
        ("memory_pool_block_resize", 0x11e8a0, 0x11e9b6),
        ("actor_move_to_point", 0x2d720, 0x2d84d),
        # gameplay wave 85 (2026-07-26) — memory/AI/net/rasterizer Capstone weaks
        ("lrar_cache_dispose", 0x11cab0, 0x11cbed),
        ("ai_communication_initialize", 0x42a30, 0x42b7f),
        ("calculate_vertex", 0x105830, 0x105971),
        ("rasterizer_swizzle_compute_masks", 0x182690, 0x1827b1),
        ("actor_move_get_avoidance_vector", 0x2b490, 0x2b5c1),
        ("FUN_0011c310", 0x11c310, 0x11c423),
        ("FUN_00106030", 0x106030, 0x106128),
        ("FUN_00119df0", 0x119df0, 0x119eea),
        ("FUN_0002b310", 0x2b310, 0x2b3f6),
        ("FUN_0011b750", 0x11b750, 0x11b84d),
        ("FUN_0011b650", 0x11b650, 0x11b745),
        ("actor_action_try_to_throw_grenade", 0x1fa60, 0x1fb79),
        # gameplay wave 86 (2026-07-26) — priority Capstone weaks
        ("FUN_0011a430", 0x11a430, 0x11a532, [(0x11a534, 0x11a548)]),
        ("ai_debug_get_path_storage", 0x49120, 0x4921b),
        ("actor_aim_jump", 0x2ace0, 0x2add4),
        ("actor_action_consider_grenade", 0x1fb80, 0x1fc91),
        ("actor_get_best_damaging_prop", 0x2fa70, 0x2fb5b),
        ("FUN_00077040", 0x77040, 0x7711c),
        ("FUN_0011a340", 0x11a340, 0x11a422),
        ("FUN_00195550", 0x195550, 0x195644),
        ("FUN_0011d320", 0x11d320, 0x11d3e5),
        ("FUN_0002f380", 0x2f380, 0x2f46b),
        ("collision_surface_perimeter", 0x147710, 0x1477e1),
        ("rasterizer_text_draw_cached_char", 0x183c00, 0x183ce4),
        # gameplay wave 87 (2026-07-26) — AI/structures/input Capstone weaks
        ("input_get_raw_data_string", 0xd0030, 0xd011d),
        ("actor_move_to_prop", 0x2d9b0, 0x2da99),
        ("actor_update_prop_desire", 0x14360, 0x14458),
        ("hashtable_new", 0x11b850, 0x11b949),
        ("FUN_000624b0", 0x624b0, 0x62595),
        ("actor_path_3d_available", 0x2b720, 0x2b823),
        ("csstricmp", 0x8e190, 0x8e24b),
        ("leaf_map_mark_portal_designators", 0x191cb0, 0x191d78),
        ("ai_communication_initialize_for_new_map", 0x42b90, 0x42c92),
        ("closest_point_to_attractor", 0x5f3c0, 0x5f483),
        ("FUN_000625a0", 0x625a0, 0x62673),
        ("actor_action_allow_cover_seeking", 0x1ccc0, 0x1cd96),
        # gameplay wave 88 (2026-07-26) — AI/structures/net/HUD Capstone weaks
        ("actor_action_handle_grenade_throwing", 0x205a0, 0x2066f),
        ("path_attractor_weight", 0x5f490, 0x5f549),
        ("lruv_cache_get_page_usage", 0x11da60, 0x11db00),
        ("FUN_001956d0", 0x1956d0, 0x19578c),
        ("FUN_0011c0f0", 0x11c0f0, 0x11c1ac),
        ("FUN_0010c440", 0x10c440, 0x10c502),
        ("FUN_000628b0", 0x628b0, 0x62960),
        ("FUN_0011bb70", 0x11bb70, 0x11bc1c),
        ("FUN_00062410", 0x62410, 0x624b0),
        ("actor_action_handle_combat_transition", 0x204f0, 0x20598),
        ("cluster_partition_globals_new", 0x191500, 0x1915d0),
        ("hud_set_element_digital", 0xd0c80, 0xd0d44),
        # gameplay wave 89 (2026-07-26) — AI/net/units/rasterizer Capstone weaks
        ("actor_perception_acknowledge", 0x2f2b0, 0x2f379),
        ("FUN_0011be10", 0x11be10, 0x11beaa),
        ("FUN_0011a230", 0x11a230, 0x11a2cf),
        ("periodic_functions_initialize", 0x10ad10, 0x10add0),
        ("unit_drop_grenades_on_death", 0x1abb20, 0x1abbca),
        ("reference_list_copy", 0x191440, 0x1914f6),
        ("actor_move_to_firing_position", 0x2d900, 0x2d9ae),
        ("actor_move_to_move_position", 0x2d850, 0x2d8fb),
        ("actor_path_input_new", 0x2a470, 0x2a52c),
        ("rasterizer_transparent_geometry_group_to_presorted_index", 0x1844b0, 0x184567),
        ("FUN_00191bd0", 0x191bd0, 0x191c6f),
        ("shell_update", 0x105c80, 0x105d18),
        # gameplay wave 90 (2026-07-26) — interface/AI/net/scenario Capstone weaks
        ("interface_draw_splitscreen_dividers", 0xdfdc0, 0xdfe97),
        ("set_file_location_volume_name", 0x199360, 0x199413),
        ("cluster_partition_remove_object", 0x1919a0, 0x191a41),
        ("system_exception_name", 0x8e500, 0x8e5ca, [(0x8e5cc, 0x8e5e8)]),
        ("hud_messaging_get_objective", 0xd4fb0, 0xd5068),
        ("FUN_0018e500", 0x18e500, 0x18e5b7),
        ("encounter_link_activation", 0x5a5a0, 0x5a634),
        ("actor_move_force_stop", 0x2a860, 0x2a8ee),
        ("rasterizer_swizzle_interleave_bits", 0x1827c0, 0x182840),
        ("reference_list_remove", 0x1913c0, 0x19143e),
        ("FUN_0011a5d0", 0x11a5d0, 0x11a650),
        ("FUN_0011a650", 0x11a650, 0x11a6cf),
        # gameplay wave 91 (2026-07-26) — priority AI/rasterizer/HUD Capstone weaks
        ("actor_move_transform_avoidance_vector", 0x2b400, 0x2b487),
        ("bsp3d_find_leaf", 0x146db0, 0x146e25),
        ("hashtable_dispose", 0x11b960, 0x11b9f1),
        ("rasterizer_text_get_character_position", 0x183770, 0x183814),
        ("rasterizer_transparent_geometry_next_group", 0x1843b0, 0x18444d),
        ("system_stristr", 0x8e250, 0x8e2a6),
        ("hud_set_state_message", 0xd4d90, 0xd4e2a),
        ("actor_test_destination", 0x2a580, 0x2a60e),
        ("ai_conversation_advance", 0x43520, 0x435a1),
        ("actor_move_animation_impulse", 0x2a7e0, 0x2a85d),
        ("actor_action_handle_berserk_transition", 0x20470, 0x204e6),
        ("game_engine_player_event", 0xad0c0, 0xad135),
    ]

    xbe = Xbe.from_file(args.xbe)
    pe = pefile.PE(args.pe)
    rows = []

    print("=== Structural mnemonic match (XBE orig vs clang lift) ===")
    print("(Interim — VC71 needs RXDK CL.Exe; equivalence needs delinked .obj)\n")

    for target in targets:
        if len(target) == 4:
            name, va, end, skip = target
        else:
            name, va, end = target
            skip = None
        orig = xbe_bytes(xbe, va, end)
        cand, cand_va = pe_fn_bytes(pe, name)
        # Unexported neighbors can sit between this export and the next
        # (batch 56 FUN_001a0be0). Only trim when PE is longer than the XBE
        # window and a RET (+ nops + push ebp) lands near that window size.
        if len(cand) > len(orig) + 16:
            md = Cs(CS_ARCH_X86, CS_MODE_32)
            insns = list(md.disasm(cand, cand_va))
            best_off = None
            for i, insn in enumerate(insns):
                if insn.mnemonic != "ret":
                    continue
                off = insn.address + insn.size - cand_va
                if abs(off - len(orig)) > 32:
                    continue
                j = i + 1
                while j < len(insns) and insns[j].mnemonic == "nop":
                    j += 1
                if (
                    j < len(insns)
                    and insns[j].mnemonic == "push"
                    and insns[j].op_str == "ebp"
                ):
                    best_off = off
                    break
            if best_off is not None:
                cand = cand[:best_off]
        o_m = xbe_mnemonics(orig, va, skip)
        c_m = mnemonics(cand, cand_va)
        # Normalize trailing align nops so RET-vs-RET+nop ends still match.
        while o_m and o_m[-1] == "nop":
            o_m.pop()
        while c_m and c_m[-1] == "nop":
            c_m.pop()
        ratio = SequenceMatcher(None, o_m, c_m, autojunk=False).ratio() * 100.0
        o_calls = sum(1 for m in o_m if m == "call")
        c_calls = sum(1 for m in c_m if m == "call")
        print(
            f"{name}: {ratio:5.1f}%  "
            f"orig_insns={len(o_m)} cand_insns={len(c_m)} "
            f"calls {o_calls}->{c_calls}  "
            f"orig_bytes={len(orig)} cand_bytes={len(cand)}"
        )
        rows.append(
            {
                "name": name,
                "addr": hex(va),
                "match_pct": round(ratio, 2),
                "orig_insns": len(o_m),
                "cand_insns": len(c_m),
                "orig_calls": o_calls,
                "cand_calls": c_calls,
                "note": "clang-vs-xbe interim; not VC71",
            }
        )

    out = Path(args.json_out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(rows, indent=2) + "\n")
    print(f"\nwrote {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
