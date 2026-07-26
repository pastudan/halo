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
    size = min((nxt - addr) if nxt else 0x800, 0x1000)
    off = pe.get_offset_from_rva(addr - base)
    data = pe.__data__[off : off + size]
    # Strip trailing padding bytes, then drop trailing NOP instructions
    # (clang often emits multi-byte NOPs that may be truncated at the next export).
    while len(data) > 16 and data[-1] in (0x90, 0xCC, 0x00):
        data = data[:-1]
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    while True:
        insns = list(md.disasm(data, addr))
        if len(insns) < 2 or insns[-1].mnemonic != "nop":
            break
        data = data[: insns[-1].address - addr]
    return data, addr


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
        ("FUN_00136bc0", 0x136bc0, 0x136f40),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00133300", 0x133300, 0x133496),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c90),
        # gameplay wave 9 (2026-07-26)
        ("FUN_001b4dc0", 0x1b4dc0, 0x1b5400),
        ("FUN_00138900", 0x138900, 0x138e15),
        ("vehicle_export_function_values", 0x1b79c0, 0x1b7ee0),
        ("FUN_001b6560", 0x1b6560, 0x1b69a0),
        ("FUN_001b6250", 0x1b6250, 0x1b6560),
        # gameplay wave 10 (2026-07-26)
        ("FUN_00134c40", 0x134c40, 0x134e50),
        ("FUN_00139480", 0x139480, 0x1396dc),
        ("FUN_001b72b0", 0x1b72b0, 0x1b74c6),
        ("FUN_001b74d0", 0x1b74d0, 0x1b77f0),
        ("FUN_000de3f0", 0xde3f0, 0xde560),
        # gameplay wave 11 (2026-07-26)
        ("FUN_001b7020", 0x1b7020, 0x1b72a5),
        ("FUN_001b77f0", 0x1b77f0, 0x1b79c0),
        ("FUN_001b6ca0", 0x1b6ca0, 0x1b6e11),
        # gameplay wave 12 (2026-07-26)
        ("FUN_000de560", 0xde560, 0xdeb50),
        ("FUN_001b5f20", 0x1b5f20, 0x1b5fed),
        ("FUN_001b6560", 0x1b6560, 0x1b69a0),
        ("FUN_001b69a0", 0x1b69a0, 0x1b6ca0),
        ("FUN_001b6e20", 0x1b6e20, 0x1b7016),
        # gameplay wave 13 (2026-07-26)
        ("FUN_00136bc0", 0x136bc0, 0x136f40),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c90),
        ("vehicle_export_function_values", 0x1b79c0, 0x1b7ee0),
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00138900", 0x138900, 0x138e15),
        ("FUN_001b5400", 0x1b5400, 0x1b54fb),
        ("FUN_000de3f0", 0xde3f0, 0xde560),
        # gameplay wave 14 (2026-07-26)
        ("FUN_001345b0", 0x1345b0, 0x134adb),
        ("FUN_00133300", 0x133300, 0x133496),
        ("actor_aim_projectile", 0x220c0, 0x22390),
        ("FUN_001b4dc0", 0x1b4dc0, 0x1b5400),
        # gameplay wave 15 (2026-07-26)
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c90),
        ("FUN_00136bc0", 0x136bc0, 0x136f40),
        ("FUN_00149680", 0x149680, 0x149d00),
        ("FUN_001377d0", 0x1377d0, 0x137d00),
        ("FUN_001491d0", 0x1491d0, 0x1493a0),
        # gameplay wave 16 (2026-07-26)
        ("FUN_001b6250", 0x1b6250, 0x1b6560),
        ("weapon_export_function_values", 0xfbf00, 0xfc290),
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        ("FUN_001b81d0", 0x1b81d0, 0x1b8570),
        ("vehicle_preprocess_node_orientations", 0x1b5890, 0x1b5c90),
        ("FUN_00136bc0", 0x136bc0, 0x136f40),
        # gameplay wave 17 (2026-07-26)
        ("FUN_001b8570", 0x1b8570, 0x1b8f10),
        ("item_update", 0xf7340, 0xf7cb0),
        ("FUN_000fd570", 0xfd570, 0xfdc90),
        ("FUN_00138900", 0x138900, 0x138e15),
        ("FUN_001377d0", 0x1377d0, 0x137d12),
        # gameplay wave 18 (2026-07-26)
        ("FUN_001b8570", 0x1b8570, 0x1b8f10),
        ("item_update", 0xf7340, 0xf7cb0),
        ("FUN_000f5900", 0xf5900, 0xf5f10),
        ("FUN_000f5fb0", 0xf5fb0, 0xf63c4),
        ("FUN_000f4cf0", 0xf4cf0, 0xf4ea0),
        # gameplay wave 19 (2026-07-26)
        ("FUN_000f7110", 0xf7110, 0xf7340),
        ("multiplayer_settings_select_list_update_item", 0xf4210, 0xf46e0),
        ("FUN_000f46e0", 0xf46e0, 0xf4b60),
        ("FUN_00135510", 0x135510, 0x135f20),
        ("FUN_001b6e20", 0x1b6e20, 0x1b7016),
        # gameplay wave 20 (2026-07-26)
        ("first_person_weapon_update", 0xdd580, 0xddae0),
        ("FUN_000f1710", 0xf1710, 0xf1ed0),
        ("FUN_0001b280", 0x1b280, 0x1b750),
        ("get_local_player_input_blob", 0xb70b0, 0xb7e30),
        ("FUN_00136bc0", 0x136bc0, 0x136f40),
        # gameplay wave 21 (2026-07-26)
        ("first_person_weapon_draw", 0xdce80, 0xdd110),
        ("FUN_0001aeb0", 0x1aeb0, 0x1b280),
        ("vehicle_stuck", 0x1b8060, 0x1b81c7),
        ("object_compute_function_values", 0x13e7b0, 0x13eb30),
        ("weapon_export_function_values", 0xfbf00, 0xfc290),
        ("glow_trailing_particle_new", 0x134350, 0x1345b0),
        # gameplay wave 22 (2026-07-26)
        ("FUN_000f4b60", 0xf4b60, 0xf4cec),
        ("FUN_000f5900", 0xf5900, 0xf5f10),
        ("FUN_000f5800", 0xf5800, 0xf58c6),
        ("FUN_000f3690", 0xf3690, 0xf3740),
        ("FUN_0019cff0", 0x19cff0, 0x19d070),
        ("first_person_weapon_get_marker_by_name", 0xdd190, 0xdd260),
        # gameplay wave 23 (2026-07-26)
        ("vehicle_accelerate", 0x1b5c90, 0x1b5d8c),
        ("FUN_001a4440", 0x1a4440, 0x1a4990),
        ("FUN_001a4990", 0x1a4990, 0x1a4a50),
        ("player_aim_projectile", 0xa6130, 0xa6470),
        ("get_particle_world_position", 0x1339a0, 0x134070),
        ("FUN_001336a0", 0x1336a0, 0x133750),
        ("FUN_001335e0", 0x1335e0, 0x1336a0),
        # gameplay wave 24 (2026-07-26)
        ("FUN_001a4a70", 0x1a4a70, 0x1a4c50),
        ("physics_compute_biped_collision", 0x151a50, 0x151ec0),
        ("biped_limp_noodle_valid_joint_rotation", 0x19f540, 0x19fa20),
        ("FUN_0019fa20", 0x19fa20, 0x1a01d0),
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
        ("FUN_00135510", 0x135510, 0x135f20),
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
        ("weapon_new", 0xfbd10, 0xfbea0),
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
    ]

    xbe = Xbe.from_file(args.xbe)
    pe = pefile.PE(args.pe)
    rows = []

    print("=== Structural mnemonic match (XBE orig vs clang lift) ===")
    print("(Interim — VC71 needs RXDK CL.Exe; equivalence needs delinked .obj)\n")

    for name, va, end in targets:
        orig = xbe_bytes(xbe, va, end)
        cand, cand_va = pe_fn_bytes(pe, name)
        o_m = mnemonics(orig, va)
        c_m = mnemonics(cand, cand_va)
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
