#!/usr/bin/env python3
"""Draft all unset symbols for one kb object (handles missing sources + duplicate names)."""
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


def tool_slug(object_name: str, source_rel: str) -> str:
    if source_rel:
        return re.sub(r"[^a-z0-9]+", "_", Path(source_rel).stem.lower()).strip("_")
    return slug(object_name)


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


def load_decls_for_obj(obj: dict, *, skip_existing: bool = False) -> dict[str, str]:
    gen = load_gen_mod()
    kb = json.loads((ROOT / "kb.json").read_text())
    existing: set[str] = set()
    if skip_existing:
        src_rel = obj.get("source")
        if src_rel:
            src_path = HALO_SRC / src_rel
            if src_path.is_file():
                existing = gen.existing_fn_names(src_path.read_text())
    decls: dict[str, str] = {}
    for f in obj["functions"]:
        if f.get("ported") is not None:
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


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--object", required=True)
    ap.add_argument("--occurrence", type=int, default=0)
    args = ap.parse_args()

    kb_path = ROOT / "kb.json"
    kb = json.loads(kb_path.read_text())
    matches = find_objects(kb, args.object)
    if not matches:
        raise SystemExit(f"unknown object {args.object!r}")
    if args.occurrence >= len(matches):
        raise SystemExit(
            f"occurrence {args.occurrence} out of range for {args.object!r} "
            f"({len(matches)} entries)"
        )
    obj = matches[args.occurrence]
    unset = sum(1 for f in obj["functions"] if f.get("ported") is None)
    if unset == 0:
        print(f"{args.object}[{args.occurrence}]: already 0 unset")
        return

    source_rel = obj.get("source") or default_source(args.object, args.occurrence)
    if not obj.get("source"):
        obj["source"] = source_rel
        kb_path.write_text(json.dumps(kb, indent=2) + "\n")

    src_path = HALO_SRC / source_rel
    src_path.parent.mkdir(parents=True, exist_ok=True)
    if not src_path.is_file():
        src_path.write_text(
            f"/* kb object: {args.object} -> {source_rel} */\n\n"
        )

    ensure_cmake(source_rel)

    gen = load_gen_mod()
    decls = load_decls_for_obj(obj, skip_existing=True)
    if not decls:
        raise SystemExit(f"no draftable unset symbols in {args.object}")

    s = tool_slug(args.object, source_rel)
    marker = f"/* --- {args.object} batch drafts"
    impl_parts = [f"/* --- {args.object} batch drafts (2026-07-26) --- */\n"]
    for addr in sorted(decls.keys(), key=lambda x: int(x, 16)):
        impl_parts.append(f"/* {addr} */\n{gen.gen_stub_body(decls[addr])}")
    impl_text = "\n".join(impl_parts)
    impl_out = ROOT / "tools" / f"{s}_batch_impl.c"
    frag_out = ROOT / "tools" / f"{s}_batch_fragment.c"
    impl_out.write_text(impl_text)
    frag_out.write_text(impl_text)

    src_text = src_path.read_text()
    if marker not in src_text:
        if src_text and not src_text.endswith("\n"):
            src_text += "\n"
        src_path.write_text(src_text + impl_text)

    al_path = ROOT / "tools/audit/deactivation_allowlist.json"
    al = json.loads(al_path.read_text())
    have_al = {e["addr"].lower() for e in al if isinstance(e, dict)}
    for addr, decl in decls.items():
        for f in obj["functions"]:
            if f["addr"].lower() == addr:
                f["decl"] = decl
                f["ported"] = False
                break
        if addr.lower() in have_al:
            continue
        fn = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", decl)
        al.append(
            {
                "addr": addr,
                "name": fn.group(1) if fn else f"FUN_{int(addr, 16):08x}",
                "object": args.object,
                "reason": "draft lift pending VC71/equivalence — keep inactive until scored",
                "since": "2026-07-26",
            }
        )
        have_al.add(addr.lower())

    al_path.write_text(json.dumps(al, indent=2) + "\n")
    kb_path.write_text(json.dumps(kb, indent=2) + "\n")

    subprocess.run(
        [
            sys.executable,
            "tools/audit/extract_reg_args.py",
            "--apply",
            "--batch",
            args.object,
        ],
        cwd=ROOT,
        check=False,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )

    print(f"{args.object}[{args.occurrence}]: drafted {len(decls)} -> {source_rel}")


if __name__ == "__main__":
    main()
