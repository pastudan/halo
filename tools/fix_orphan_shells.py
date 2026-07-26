#!/usr/bin/env python3
"""Add C function shells for ported:false kb symbols missing from source."""
from __future__ import annotations

import argparse
import importlib.util
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CMAKE = ROOT / "src" / "CMakeLists.txt"
HALO_SRC = ROOT / "src" / "halo"


def slug(name: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", name.replace(".obj", "").lower()).strip("_")


def find_objects(kb: dict, name: str) -> list[dict]:
    return [o for o in kb["objects"] if o.get("name") == name]


def default_source(object_name: str, occurrence: int) -> str:
    if object_name == "<common>":
        return "kb_common_stubs.c"
    if object_name == "<xdk_stubs>":
        return "xdk/xdk_stubs_rt.c" if occurrence == 0 else "xdk/xdk_stubs_xapi.c"
    if object_name.startswith("LIBCMT:"):
        base = object_name.split(":", 1)[1].replace(".obj", "")
        return f"libcmt/{base}.c"
    if object_name.startswith("XAPILIB:"):
        base = object_name.split(":", 1)[1].replace(".obj", "")
        return f"xdk/xapilib/{base}.c"
    if object_name.startswith("XNET:"):
        base = object_name.split(":", 1)[1].replace(".obj", "")
        return f"xdk/xnet/{base}.c"
    raise ValueError(f"no default source for {object_name!r}")


def ensure_cmake(source_rel: str) -> bool:
    entry = f"\thalo/{source_rel.replace(chr(92), '/')}"
    text = CMAKE.read_text()
    if entry.strip() in text.replace("\r", ""):
        return False
    marker = "\thalo/shell.c"
    if marker not in text:
        raise RuntimeError("CMakeLists.txt layout changed — cannot insert source")
    text = text.replace(marker, f"{entry}\n{marker}", 1)
    CMAKE.write_text(text)
    return True


def load_gen_mod():
    spec_path = ROOT / "tools" / "gen_module_draft_batch.py"
    spec = importlib.util.spec_from_file_location("gen_module_draft_batch", spec_path)
    mod = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


def orphan_decls(obj: dict) -> dict[str, str]:
    gen = load_gen_mod()
    src_rel = obj.get("source")
    existing: set[str] = set()
    if src_rel:
        src_path = HALO_SRC / src_rel
        if src_path.is_file():
            existing = gen.existing_fn_names(src_path.read_text())
    decls: dict[str, str] = {}
    for f in obj["functions"]:
        if f.get("ported") is not False:
            continue
        addr = f["addr"].lower()
        decl = (f.get("decl") or f"void {gen.fn_name('', addr)}(void);").strip()
        if not decl.endswith(";"):
            decl += ";"
        name = gen.fn_name(decl, addr)
        if name in existing:
            continue
        decls[addr] = decl
    return decls


def fix_object(object_name: str, *, occurrence: int = 0, relift: bool = False) -> dict:
    kb_path = ROOT / "kb.json"
    kb = json.loads(kb_path.read_text())
    matches = find_objects(kb, object_name)
    if not matches:
        raise SystemExit(f"unknown object {object_name!r}")
    if occurrence >= len(matches):
        raise SystemExit(f"occurrence {occurrence} out of range for {object_name!r}")
    obj = matches[occurrence]

    source_rel = obj.get("source") or default_source(object_name, occurrence)
    if not obj.get("source"):
        obj["source"] = source_rel
        kb_path.write_text(json.dumps(kb, indent=2) + "\n")

    src_path = HALO_SRC / source_rel
    src_path.parent.mkdir(parents=True, exist_ok=True)
    if not src_path.is_file():
        src_path.write_text(f"/* kb object: {object_name} -> {source_rel} */\n\n")

    ensure_cmake(source_rel)

    gen = load_gen_mod()
    decls = orphan_decls(obj)
    if not decls:
        return {"object": object_name, "added": 0, "source": str(src_path)}

    marker = f"/* --- {object_name} orphan shells"
    impl_parts = [f"/* --- {object_name} orphan shells (2026-07-26) --- */\n"]
    for addr in sorted(decls.keys(), key=lambda x: int(x, 16)):
        impl_parts.append(f"/* orphan {addr} */\n{gen.gen_stub_body(decls[addr], addr)}")
    impl_text = "\n".join(impl_parts)

    src_text = src_path.read_text()
    if marker not in src_text:
        if src_text and not src_text.endswith("\n"):
            src_text += "\n"
        src_path.write_text(src_text + impl_text)

    relifted = 0
    if relift:
        proc = subprocess.run(
            [
                sys.executable,
                "tools/relift_stubs_from_xbe.py",
                "--object",
                object_name,
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            print(proc.stdout, proc.stderr, file=sys.stderr)
            raise SystemExit(proc.returncode)
        m = re.search(r"relifted (\d+)", proc.stdout)
        if m:
            relifted = int(m.group(1))
        print(proc.stdout.strip())

    return {
        "object": object_name,
        "added": len(decls),
        "relifted": relifted,
        "source": str(src_path),
    }


def list_orphans() -> list[tuple[str, str, str]]:
    gen = load_gen_mod()
    kb = json.loads((ROOT / "kb.json").read_text())
    out: list[tuple[str, str, str]] = []
    for obj in kb["objects"]:
        on = obj.get("name") or ""
        src_rel = obj.get("source")
        if not src_rel:
            continue
        src_path = HALO_SRC / src_rel
        existing = (
            gen.existing_fn_names(src_path.read_text())
            if src_path.is_file()
            else set()
        )
        for f in obj.get("functions", []):
            if f.get("ported") is not False:
                continue
            addr = f["addr"].lower()
            decl = f.get("decl") or ""
            name = gen.fn_name(decl, addr)
            if name not in existing:
                out.append((on, name, addr))
    return out


def main() -> None:
    ap = argparse.ArgumentParser(description="Add C shells for ported:false orphans")
    ap.add_argument("--object", action="append", help="kb object name (repeatable)")
    ap.add_argument("--all", action="store_true", help="Fix every orphan")
    ap.add_argument("--list", action="store_true", help="Print orphan counts and exit")
    ap.add_argument("--occurrence", type=int, default=0)
    ap.add_argument("--relift", action="store_true", help="Run relift_stubs_from_xbe after adding")
    args = ap.parse_args()

    if args.list:
        orphans = list_orphans()
        from collections import Counter

        print(f"orphans: {len(orphans)}")
        for obj, cnt in Counter(o for o, _, _ in orphans).most_common(30):
            print(f"  {obj}: {cnt}")
        return

    if args.all:
        objects = sorted({o for o, _, _ in list_orphans()})
        total_added = 0
        for obj in objects:
            r = fix_object(obj, occurrence=0, relift=args.relift)
            if r["added"]:
                print(f"{obj}: added {r['added']} shells")
                total_added += r["added"]
        print(f"TOTAL added: {total_added}")
        return

    if not args.object:
        ap.error("pass --object, --all, or --list")

    total = 0
    for obj in args.object:
        r = fix_object(obj, occurrence=args.occurrence, relift=args.relift)
        print(f"{r['object']}: added {r['added']} shells")
        total += r["added"]
    print(f"TOTAL added: {total}")


if __name__ == "__main__":
    main()
