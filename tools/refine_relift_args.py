#!/usr/bin/env python3
"""Refine relifted draft bodies: recover stack/register call arguments from XBE.

Re-disassembles ported:false functions whose bodies are relift drafts and
replaces them with improved argument recovery (fewer 0 placeholders). Does not
touch kb.json ported flags or decls.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

PRIORITY = [
    "collision_bsp.obj",
    "players.obj",
    "player_control.obj",
    "hs.obj",
    "hs_runtime.obj",
    "objects.obj",
    "units.obj",
    "weapons.obj",
    "encounters.obj",
    "vehicles.obj",
    "ai.obj",
    "main.obj",
]

# CRT amalgams — never --force whole module
SKIP_FORCE = {
    "crt_amalgam.obj",
    "crt_amalgam2.obj",
    "crt_amalgam3.obj",
}


def load_relift():
    spec = importlib.util.spec_from_file_location(
        "relift_stubs_from_xbe", ROOT / "tools" / "relift_stubs_from_xbe.py"
    )
    mod = importlib.util.module_from_spec(spec)
    sys.modules["relift_stubs_from_xbe"] = mod
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


def count_zero_calls(text: str) -> dict[str, int]:
    """Heuristic counts of placeholder call sites."""
    # foo(0, 0) or foo(0,0) — two or more bare zero args
    z2 = len(re.findall(r"\w+\([^)]*\b0\b[^)]*,\s*[^)]*\b0\b", text))
    # trailing , 0) — last arg is literal zero (excludes 0x)
    ztail = len(re.findall(r",\s*0\s*\)", text))
    # (void *...)0 in calls — register placeholders
    regcast = len(
        re.findall(
            r"\((?:char|void|unsigned char|wchar_t|float|int|data_t)[^)]*\)"
            r"\(uintptr_t\)(?:eax|ebx|ecx|edx|esi|edi)",
            text,
        )
    )
    relift = text.count("relift:")
    return {"z2": z2, "ztail": ztail, "regcast": regcast, "relift": relift}


def module_stats(kb: dict, relift, object_name: str) -> dict | None:
    matches = [o for o in kb["objects"] if o.get("name") == object_name]
    if not matches:
        return None
    obj = matches[0]
    src_rel = obj.get("source")
    if not src_rel:
        return None
    path = ROOT / "src" / "halo" / src_rel
    if not path.is_file():
        return None
    text = path.read_text()
    drafts = 0
    for f in obj.get("functions", []):
        if f.get("ported") is not False:
            continue
        addr = f["addr"].lower()
        name = relift.fn_name_from_decl(f.get("decl") or "", addr)
        span = relift.find_function_def_for_addr(text, name, addr)
        if span and relift.is_relift_draft(text[span[1] : span[2]]):
            drafts += 1
    stats = count_zero_calls(text)
    stats["drafts"] = drafts
    stats["source"] = src_rel
    return stats


def docker_build() -> tuple[bool, str]:
    cmd = [
        "docker",
        "run",
        "--rm",
        "-u",
        f"{__import__('os').getuid()}:{__import__('os').getgid()}",
        "-v",
        f"{ROOT}:/work",
        "-w",
        "/work",
        "halo-re-build:latest",
        "bash",
        "-c",
        "cmake --build build --target halo --parallel 2>&1",
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    out = proc.stdout + proc.stderr
    m = re.search(r"raw-cast count: (\d+)", out)
    raw = int(m.group(1)) if m else None
    ok = proc.returncode == 0 and raw == 403
    return ok, out


def main() -> None:
    ap = argparse.ArgumentParser(description="Refine relift draft call arguments")
    ap.add_argument(
        "--object",
        action="append",
        help="kb object name (default: priority gameplay modules)",
    )
    ap.add_argument("--occurrence", type=int, default=0)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--no-build", action="store_true")
    ap.add_argument("--stats-only", action="store_true")
    args = ap.parse_args()

    relift = load_relift()
    kb = json.loads((ROOT / "kb.json").read_text())
    objects = args.object or PRIORITY

    print("module                         drafts  z2  ztail regcast  relift")
    before_all: dict[str, dict] = {}
    for on in objects:
        st = module_stats(kb, relift, on)
        if not st:
            continue
        before_all[on] = st
        print(
            f"{on:30} {st['drafts']:6} {st['z2']:4} {st['ztail']:5} "
            f"{st['regcast']:7} {st['relift']:6}"
        )

    if args.stats_only:
        return

    total = 0
    for on in objects:
        if on in SKIP_FORCE:
            print(f"skip {on} (CRT amalgam)")
            continue
        r = relift.relift_object(
            on,
            occurrence=args.occurrence,
            dry_run=args.dry_run,
            force=True,
        )
        total += r["relifted"]
        label = on if not r.get("occurrence") else f"{on}[{r['occurrence']}]"
        print(
            f"refined {label}: relifted {r['relifted']} "
            f"(skipped {r['skipped']}, candidates {r['stub_before']})"
        )

    print(f"\nTOTAL refined: {total}")

    if args.dry_run:
        return

    # reload kb for post stats
    kb = json.loads((ROOT / "kb.json").read_text())
    print("\nAfter refine:")
    print("module                         drafts  z2  ztail regcast  relift  delta_z2")
    for on in objects:
        st = module_stats(kb, relift, on)
        if not st:
            continue
        b = before_all.get(on, {})
        dz2 = st["z2"] - b.get("z2", 0)
        print(
            f"{on:30} {st['drafts']:6} {st['z2']:4} {st['ztail']:5} "
            f"{st['regcast']:7} {st['relift']:6} {dz2:+4}"
        )

    if not args.no_build and total:
        ok, out = docker_build()
        if not ok:
            print(out[-8000:], file=sys.stderr)
            raise SystemExit("docker build failed or raw-cast != 403")
        print("\n".join(out.strip().splitlines()[-3:]))


if __name__ == "__main__":
    main()
