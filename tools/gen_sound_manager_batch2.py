#!/usr/bin/env python3
"""Generate sound_manager.obj batch2 draft implementations."""
from __future__ import annotations

from pathlib import Path

from sound_manager_batch2_impl import IMPL

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "tools" / "sound_manager_batch2_fragment.c"

DECLS = {
    "0x1be1b0": "void FUN_001be1b0(int cache_handle);",
    "0x1be270": "void *FUN_001be270(int cache_handle);",
    "0x1be2b0": "void FUN_001be2b0(void *perm_entry@<esi>);",
    "0x1c7b40": "void FUN_001c7b40(void);",
    "0x1c8700": "int FUN_001c8700(void *state, int sample_count, int16_t *out, void *track, void *bitstream);",
    "0x1c88a0": "void sound_is_active(int sound_index);",
    "0x1c8ee0": "void FUN_001c8ee0(void *pitch_range);",
    "0x1cb1a0": "void FUN_001cb1a0(int channel_index, int param);",
    "0x1cb1d0": "void FUN_001cb1d0(int channel_index, int a, int b, int c, int d, int e);",
    "0x1cb210": "char FUN_001cb210(short channel_index@<ax>, unsigned char flags@<bl>);",
    "0x1cb4c0": "char FUN_001cb4c0(void *driver_caps);",
    "0x1cb820": "void FUN_001cb820(void);",
    "0x1cb8f0": "void sound_reconnect_to_structure_bsp(void);",
    "0x1cbc20": "float FUN_001cbc20(float t);",
    "0x1cbc40": "char FUN_001cbc40(int sound_handle@<ebx>);",
    "0x1cc1c0": "char FUN_001cc1c0(int looping_handle, void *out);",
    "0x1cc200": "char FUN_001cc200(int looping_handle, void *source, void *position);",
    "0x1cc2f0": "void FUN_001cc2f0(int sound_handle@<eax>, int tag_index@<esi>);",
    "0x1cc440": "int FUN_001cc440(int source@<edi>);",
    "0x1cc4f0": "void FUN_001cc4f0(int sound_handle);",
    "0x1cc5b0": "void FUN_001cc5b0(int sound_tag_index, void *source);",
    "0x1cc710": "void sound_initialize(void **driver_out);",
    "0x1ccbe0": "float FUN_001ccbe0(int channel_index@<eax>, void *source@<edi>);",
    "0x1ccca0": "float FUN_001ccca0(int channel_index@<eax>, void *source@<edi>);",
    "0x1cce80": "char sound_update_time(int sound_a@<eax>, int sound_b@<edi>, float threshold);",
    "0x1cd190": "int FUN_001cd190(int sound_tag_index@<eax>, void *track, void *source);",
    "0x1cd390": "void FUN_001cd390(void *track_entry@<edi>, float *out@<esi>);",
    "0x1cd4d0": "void sound_stop_impulse_by_source_and_definition(int source, int definition);",
    "0x1cd540": "void sound_stop_all(void);",
    "0x1cd690": "void FUN_001cd690(void);",
    "0x1cd8b0": "short FUN_001cd8b0(int sound_handle);",
    "0x1ce550": "char sound_refresh_looping(int sound_tag_index, void *source, void *track, short track_type);",
    "0x1ce9c0": "void FUN_001ce9c0(void);",
    "0x1cebb0": "short FUN_001cebb0(int sound_handle);",
    "0x1cf100": "void FUN_001cf100(void);",
    "0x1cf360": "void FUN_001cf360(void);",
    "0x1cf820": "void FUN_001cf820(void **out);",
}


def main() -> None:
    OUT.write_text(IMPL.lstrip() + "\n")
    print("wrote", OUT, len(DECLS), "functions")


if __name__ == "__main__":
    main()
