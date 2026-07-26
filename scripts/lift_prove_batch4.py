#!/usr/bin/env python3
"""Atomic naked→C lifts + Unicorn prove for batch4 leaves."""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KB_PATH = ROOT / "kb.json"


def replace_once(path: Path, pattern: str, replacement: str, flags=0) -> None:
    text = path.read_text(encoding="utf-8", errors="replace")
    new, n = re.subn(pattern, replacement, text, count=1, flags=flags)
    if n != 1:
        raise SystemExit(f"replace failed in {path}: {pattern[:60]!r} n={n}")
    path.write_text(new, encoding="utf-8")


def replace_naked_block(path: Path, name: str, addr: int, body: str) -> None:
    text = path.read_text(encoding="utf-8", errors="replace")
    pats = [
        re.compile(
            rf"/\*[^*]*\b{re.escape(name)}\b[^*]*\*/\s*"
            rf"#if\s+defined\s*\(\s*__clang__\s*\)[\s\S]*?#endif\s*\n",
            re.M,
        ),
        re.compile(
            rf"/\*[^*]*0x{addr:x}[^*]*\*/\s*"
            rf"#if\s+defined\s*\(\s*__clang__\s*\)[\s\S]*?#endif\s*\n",
            re.M,
        ),
    ]
    for pat in pats:
        m = pat.search(text)
        if m:
            path.write_text(text[: m.start()] + body.strip() + "\n\n" + text[m.end() :], encoding="utf-8")
            return
    if re.search(rf"\b{re.escape(name)}\s*\([^;]*\)\s*\{{", text) and "naked" not in text[
        text.find(name) : text.find(name) + 200
    ]:
        print(f"already C: {name}")
        return
    path.write_text(text.rstrip() + "\n\n" + body.strip() + "\n", encoding="utf-8")
    print(f"appended: {name}")


def prove(name: str, addr: int) -> bool:
    oracle = ROOT / "delinked" / "functions" / f"{addr:08x}.obj"
    subprocess.run(
        [sys.executable, str(ROOT / "tools/equivalence/xbe_to_coff.py"), "--addr", hex(addr), "--out", str(oracle)],
        cwd=ROOT,
        capture_output=True,
    )
    # drop stale TU obj if present
    for p in (ROOT / "build").rglob(f"*{Path(name).name}*"):
        pass
    try:
        proc = subprocess.run(
            [
                sys.executable,
                str(ROOT / "tools/equivalence/unicorn_diff.py"),
                name,
                "--allow-stubs",
                "--seeds",
                "100",
                "-q",
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
            timeout=60,
        )
    except subprocess.TimeoutExpired:
        print(f"  TIMEOUT {name}")
        return False
    out = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", out)
    if not m:
        print(f"  NO-PARSE {name}: {out[-180:].replace(chr(10), ' ')}")
        return False
    p, f, e = map(int, m.groups())
    ok = proc.returncode == 0 and f == 0 and e == 0 and p >= 90
    print(f"  {name}: {p}/{f}/{e} ok={ok}")
    return ok


def main() -> int:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))

    # --- cache_files FUN_001b9920 ---
    replace_once(
        ROOT / "src/halo/cache/cache_files.c",
        r"/\*\s*0x1b9920\s*\*/\s*int FUN_001b9920\(void\)\s*\{[\s\S]*?\n\}\n",
        """/* FUN_001b9920 (0x1b9920) — readable C lift from XBE leaf. */
int FUN_001b9920(void)
{
  return *(int *)0x4e4d68;
}
""",
    )
    print("fixed FUN_001b9920")

    # --- player_control action tests ---
    pc = ROOT / "src/halo/game/player_control.c"
    text = pc.read_text(encoding="utf-8", errors="replace")
    marker = (
        "void player_control_action_test_reset(void) {\n"
        "  uint32_t *base = *(uint32_t **)0x457090;\n"
        "  base[0] = 0;\n"
        "  base[1] = 0;\n"
        "}\n"
    )
    if "player_control_action_test_accept" not in text:
        block = """
/* player_control_action_test_accept (0xb6ab0) — readable C lift from XBE leaf. */
char player_control_action_test_accept(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x4;
  base[2] |= 0x4;
  return (char)((base[0] >> 2) & 1);
}

/* player_control_action_test_back (0xb6ad0) — readable C lift from XBE leaf. */
char player_control_action_test_back(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x8;
  base[2] |= 0x8;
  return (char)((base[0] >> 3) & 1);
}

/* player_control_action_test_action (0xb6af0) — readable C lift from XBE leaf. */
char player_control_action_test_action(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  base[1] |= 0x1;
  base[2] |= 0x1;
  return (char)(base[0] & 1);
}

/* player_control_action_test_look_relative_up (0xb6bb0) — readable C lift from XBE leaf. */
char player_control_action_test_look_relative_up(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  return (char)((base[0] >> 7) & 1);
}

/* player_control_action_test_look_relative_down (0xb6bc0) — readable C lift from XBE leaf. */
char player_control_action_test_look_relative_down(void)
{
  unsigned int *base = *(unsigned int **)0x457090;
  return (char)((base[0] >> 8) & 1);
}

"""
        if marker not in text:
            raise SystemExit("player_control marker missing")
        pc.write_text(text.replace(marker, marker + "\n" + block, 1), encoding="utf-8")
        print("inserted action tests")
    else:
        print("action tests already present")

    # --- shader predicates ---
    shaders = ROOT / "src/halo/shaders/shaders.c"
    shader_lifts = [
        (
            0x1909D0,
            "shader_type_is_transparent",
            """
/* shader_type_is_transparent (0x1909d0) — readable C lift from XBE leaf. */
char shader_type_is_transparent(int16_t type)
{
  if (type == 1) {
    return 1;
  }
  if (type <= 4) {
    return 0;
  }
  if (type > 10) {
    return 0;
  }
  return 1;
}
""",
            "char shader_type_is_transparent(int16_t type);",
        ),
        (
            0x1909F0,
            "shader_type_is_lightmapped",
            """
/* shader_type_is_lightmapped (0x1909f0) — readable C lift from XBE leaf. */
char shader_type_is_lightmapped(int16_t type)
{
  if (type < 3) {
    return 0;
  }
  if (type <= 4) {
    return 1;
  }
  if (type == 8) {
    return 1;
  }
  return 0;
}
""",
            "char shader_type_is_lightmapped(int16_t type);",
        ),
        (
            0x190A30,
            "shader_type_is_valid_for_environment",
            """
/* shader_type_is_valid_for_environment (0x190a30) — readable C lift from XBE leaf. */
char shader_type_is_valid_for_environment(int16_t type)
{
  if (type == 3) {
    return 1;
  }
  if (type <= 4) {
    return 0;
  }
  if (type > 9) {
    return 0;
  }
  return 1;
}
""",
            "char shader_type_is_valid_for_environment(int16_t type);",
        ),
        (
            0x190A70,
            "shader_type_is_valid_for_modifier",
            """
/* shader_type_is_valid_for_modifier (0x190a70) — readable C lift from XBE leaf. */
char shader_type_is_valid_for_modifier(int16_t type)
{
  if (type == 1) {
    return 1;
  }
  if (type <= 4) {
    return 0;
  }
  if (type > 10) {
    return 0;
  }
  return 1;
}
""",
            "char shader_type_is_valid_for_modifier(int16_t type);",
        ),
    ]
    for addr, name, body, _decl in shader_lifts:
        replace_naked_block(shaders, name, addr, body)
        print(f"shader lift {name}")

    # kb renames / decls
    targets = {
        0x100330: ("FUN_00100330", "char FUN_00100330(void);", None),
        0x100370: ("main_won_map", "void main_won_map(void);", None),
        0x1B9920: ("FUN_001b9920", "int FUN_001b9920(void);", None),
        0xB6AB0: ("player_control_action_test_accept", "char player_control_action_test_accept(void);", None),
        0xB6AD0: ("player_control_action_test_back", "char player_control_action_test_back(void);", None),
        0xB6AF0: ("player_control_action_test_action", "char player_control_action_test_action(void);", None),
        0xB6BB0: (
            "player_control_action_test_look_relative_up",
            "char player_control_action_test_look_relative_up(void);",
            None,
        ),
        0xB6BC0: (
            "player_control_action_test_look_relative_down",
            "char player_control_action_test_look_relative_down(void);",
            None,
        ),
    }
    for addr, name, body, decl in shader_lifts:
        targets[addr] = (name, decl, None)

    for obj in kb.get("objects", []):
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            if ai in targets:
                name, decl, _ = targets[ai]
                fn["name"] = name
                fn["decl"] = decl

    # prove set
    prove_list = [
        (0x100370, "main_won_map"),
        (0x1B9920, "FUN_001b9920"),
        (0xB6AB0, "player_control_action_test_accept"),
        (0xB6AD0, "player_control_action_test_back"),
        (0xB6AF0, "player_control_action_test_action"),
        (0xB6BB0, "player_control_action_test_look_relative_up"),
        (0xB6BC0, "player_control_action_test_look_relative_down"),
    ] + [(a, n) for a, n, _b, _d in shader_lifts]

    # stale objs
    for rel in (
        "build/CMakeFiles/halo.dir/src/halo/cache/cache_files.c.obj",
        "build/CMakeFiles/halo.dir/src/halo/game/player_control.c.obj",
        "build/CMakeFiles/halo.dir/src/halo/shaders/shaders.c.obj",
    ):
        p = ROOT / rel
        if p.exists():
            p.unlink()

    flips = []
    for ai, name in prove_list:
        print(f"prove {hex(ai)} {name}")
        if prove(name, ai):
            flips.append(ai)
            for obj in kb.get("objects", []):
                for fn in obj.get("functions") or []:
                    if fn.get("addr") and int(fn["addr"], 16) == ai:
                        fn["ported"] = True

    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    true = sum(
        1
        for o in kb["objects"]
        for f in (o.get("functions") or [])
        if isinstance(f, dict) and f.get("ported") is True
    )
    false = sum(
        1
        for o in kb["objects"]
        for f in (o.get("functions") or [])
        if isinstance(f, dict) and f.get("ported") is False
    )
    print(f"flips={len(flips)} {[hex(a) for a in flips]}")
    print(f"kb true={true} false={false}")
    return 0 if flips else 1


if __name__ == "__main__":
    raise SystemExit(main())
