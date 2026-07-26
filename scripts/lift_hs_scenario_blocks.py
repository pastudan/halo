#!/usr/bin/env python3
"""Lift HS scenario tag-block wrappers:

  if (*(int *)0x326a08 != -1)
    FUN_000c40f0(name_off, elem_size, (char *)global_scenario_get() + block_off);
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from capstone import CS_ARCH_X86, CS_MODE_32, Cs  # noqa: E402
from xbe import Xbe  # noqa: E402
from xbe_to_coff import load_kb, xbe_bytes  # noqa: E402
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    git_push,
    is_naked_near_def,
    resolve_src,
    run_unicorn,
)

GLOBAL_SCENARIO = 0x326A08
GLOBAL_SCENARIO_GET = 0x18E380
FUN_C40F0 = 0xC40F0


def try_emit(insns: list[str], name: str) -> str | None:
    ops = []
    for line in insns:
        parts = line.strip().split(None, 1)
        ops.append((parts[0], parts[1] if len(parts) > 1 else ""))
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None
    body = ops[:-1]
    # cmp dword ptr [0x326a08], -1 ; je X ; push ebx ; call get ; add eax, OFF ;
    # push SIZE ; push NAMEOFF ; mov ebx, eax ; call c40f0 ; add esp, 8 ; pop ebx
    if len(body) != 11:
        return None
    if body[0] != ("cmp", f"dword ptr [0x{GLOBAL_SCENARIO:x}], -1") and not (
        body[0][0] == "cmp" and "0x326a08" in body[0][1] and "-1" in body[0][1]
    ):
        return None
    if body[1][0] != "je":
        return None
    if body[2] != ("push", "ebx"):
        return None
    if body[3][0] != "call":
        return None
    m = re.search(r"0x([0-9a-fA-F]+)", body[3][1])
    if not m or int(m.group(1), 16) != GLOBAL_SCENARIO_GET:
        return None
    if body[4][0] != "add" or not body[4][1].startswith("eax,"):
        return None
    off_s = body[4][1].split(",", 1)[1].strip()
    if body[5][0] != "push" or body[6][0] != "push":
        return None
    size_s, name_s = body[5][1], body[6][1]
    if body[7] != ("mov", "ebx, eax"):
        return None
    if body[8][0] != "call":
        return None
    m = re.search(r"0x([0-9a-fA-F]+)", body[8][1])
    if not m or int(m.group(1), 16) != FUN_C40F0:
        return None
    if body[9][0] != "add" or body[10] != ("pop", "ebx"):
        return None
    return (
        f"void {name}(void)\n"
        f"{{\n"
        f"  if (*(int *)0x{GLOBAL_SCENARIO:x} != -1) {{\n"
        f"    FUN_000c40f0((int16_t){name_s}, {size_s}, "
        f"(char *)global_scenario_get() + {off_s});\n"
        f"  }}\n"
        f"}}\n"
    )


def commit_chunk(n: int) -> str | None:
    subprocess.run(["git", "add", "-u", "src/halo/hs", "kb.json"], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_hs_scenario_blocks.py",
            "scripts/lift_hs_macro_wrappers.py",
            "scripts/lift_thin_wrappers.py",
        ],
        cwd=ROOT,
        check=False,
    )
    msg = f"lift(track-a): HS scenario-block wrappers + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    git_push()
    print(f"COMMIT+PUSH {sha}", flush=True)
    return sha


def main() -> int:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, src_by, ported = {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            name_by[ai] = func_name(fn) or f"FUN_{ai:08x}"
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    by_addr, starts = load_kb(KB_PATH)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, _ = count_ported(kb)
    flips, shas, since = [], [], 0

    for i, ai in enumerate(starts):
        if ported.get(ai) is not False:
            continue
        src = src_by.get(ai) or ""
        if "hs/" not in src:
            continue
        end = starts[i + 1] if i + 1 < len(starts) else ai + 64
        if end - ai > 64:
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        name = name_by[ai]
        lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        if not is_naked_near_def(lines, name, hex(ai)):
            continue
        try:
            raw = xbe_bytes(xbe, ai, min(end, ai + 64))
        except Exception:
            continue
        insns = []
        for insn in md.disasm(raw, ai):
            insns.append(f"{insn.mnemonic} {insn.op_str}".strip())
            if insn.mnemonic in ("ret", "retn"):
                break
        else:
            continue
        body = try_emit(insns, name)
        if not body:
            continue
        c_src = f"/* {name} (0x{ai:x}) — readable C lift (HS scenario-block wrapper). */\n{body}"
        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            # try FUN_ form
            span = find_naked_block(text, f"FUN_{ai:08x}", ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}", flush=True)
            continue
        sp.write_text(text[: span[0]] + c_src + "\n" + text[span[1] :], encoding="utf-8")
        print(f"LIFTED {hex(ai)} {name}", flush=True)
        for stale in (ROOT / "build").rglob(sp.name + ".obj"):
            try:
                stale.unlink()
            except OSError:
                pass
        if not ensure_oracle(ai):
            sp.write_text(text, encoding="utf-8")
            print("  oracle FAIL", flush=True)
            continue
        res = run_unicorn(hex(ai), ai, 100, timeout=45.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(name, ai, 100, timeout=45.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "hs_scenario_block",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT", flush=True)
            continue
        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            sp.write_text(text, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            ported[ai] = True
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        if since >= 11:
            sha = commit_chunk(since)
            if sha:
                shas.append(sha)
            since = 0

    if since:
        sha = commit_chunk(since)
        if sha:
            shas.append(sha)

    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {"proven": len(flips), "flips": flips, "shas": shas, "true0": true0, "true1": true1}
    Path("/tmp/hs_scenario_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
