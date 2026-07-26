#!/usr/bin/env python3
"""Lift unicode ctype/case thin wrappers; Unicorn-prove; commit+push."""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    git_push,
    run_unicorn,
)

# (addr, name, body, decl)
LIFTS = [
    (
        0x19E460,
        "uisalpha",
        """
/* uisalpha (0x19e460) — readable C lift. */
int uisalpha(int c)
{
  return FUN_001dc3e9(c, 0x103);
}
""",
        "int uisalpha(int c);",
    ),
    (
        0x19E480,
        "uisupper",
        """
/* uisupper (0x19e480) — readable C lift. */
int uisupper(int c)
{
  return FUN_001dc3e9(c, 1);
}
""",
        "int uisupper(int c);",
    ),
    (
        0x19E4A0,
        "uislower",
        """
/* uislower (0x19e4a0) — readable C lift. */
int uislower(int c)
{
  return FUN_001dc3e9(c, 2);
}
""",
        "int uislower(int c);",
    ),
    (
        0x19E4C0,
        "uisdigit",
        """
/* uisdigit (0x19e4c0) — readable C lift. */
int uisdigit(int c)
{
  return FUN_001dc3e9(c, 4);
}
""",
        "int uisdigit(int c);",
    ),
    (
        0x19E4E0,
        "uisxdigit",
        """
/* uisxdigit (0x19e4e0) — readable C lift. */
int uisxdigit(int c)
{
  return FUN_001dc3e9(c, 0x80);
}
""",
        "int uisxdigit(int c);",
    ),
    (
        0x19E500,
        "uisspace",
        """
/* uisspace (0x19e500) — readable C lift. */
int uisspace(int c)
{
  return FUN_001dc3e9(c, 8);
}
""",
        "int uisspace(int c);",
    ),
    (
        0x19E520,
        "uispunct",
        """
/* uispunct (0x19e520) — readable C lift. */
int uispunct(int c)
{
  return FUN_001dc3e9(c, 0x10);
}
""",
        "int uispunct(int c);",
    ),
    (
        0x19E540,
        "uisalnum",
        """
/* uisalnum (0x19e540) — readable C lift. */
int uisalnum(int c)
{
  return FUN_001dc3e9(c, 0x107);
}
""",
        "int uisalnum(int c);",
    ),
    (
        0x19E560,
        "uisprint",
        """
/* uisprint (0x19e560) — readable C lift. */
int uisprint(int c)
{
  return FUN_001dc3e9(c, 0x157);
}
""",
        "int uisprint(int c);",
    ),
    (
        0x19E580,
        "uisgraph",
        """
/* uisgraph (0x19e580) — readable C lift. */
int uisgraph(int c)
{
  return FUN_001dc3e9(c, 0x117);
}
""",
        "int uisgraph(int c);",
    ),
    (
        0x19E5A0,
        "uiscntrl",
        """
/* uiscntrl (0x19e5a0) — readable C lift. */
int uiscntrl(int c)
{
  return FUN_001dc3e9(c, 0x20);
}
""",
        "int uiscntrl(int c);",
    ),
    (
        0x19E5C0,
        "utoupper",
        """
/* utoupper (0x19e5c0) — readable C lift. */
int utoupper(int c)
{
  return (int)(unsigned short)FUN_001dc27c(c);
}
""",
        "int utoupper(int c);",
    ),
    (
        0x19E5E0,
        "utolower",
        """
/* utolower (0x19e5e0) — readable C lift. */
int utolower(int c)
{
  return (int)(unsigned short)FUN_001da8e3(c);
}
""",
        "int utolower(int c);",
    ),
    (
        0x100860,
        "main_get_current_solo_level",
        """
/* main_get_current_solo_level (0x100860) — readable C lift. */
int main_get_current_solo_level(void)
{
  return main_get_solo_level_from_name((char *)0x46da55);
}
""",
        "int main_get_current_solo_level(void);",
    ),
    (
        0x188880,
        "FUN_00188880",
        """
/* FUN_00188880 (0x188880) — readable C lift. */
void FUN_00188880(void)
{
  FUN_001887b0(-0xd);
}
""",
        "void FUN_00188880(void);",
    ),
    (
        0x93640,
        "FUN_00093640",
        """
/* FUN_00093640 (0x93640) — readable C lift. */
void FUN_00093640(int title)
{
  cinematic_set_title_delayed(title, 0);
}
""",
        "void FUN_00093640(int title);",
    ),
    (
        0x1457B0,
        "FUN_001457b0",
        """
/* FUN_001457b0 (0x1457b0) — readable C lift. */
void FUN_001457b0(int a0, int a1, int a2)
{
  FUN_00145660(a0, a1, a2, 0);
}
""",
        "void FUN_001457b0(int a0, int a1, int a2);",
    ),
    (
        0x1457D0,
        "FUN_001457d0",
        """
/* FUN_001457d0 (0x1457d0) — readable C lift. */
void FUN_001457d0(int a0, int a1, int a2, int a3)
{
  FUN_00145660(a0, a1, a2, a3);
}
""",
        "void FUN_001457d0(int a0, int a1, int a2, int a3);",
    ),
]


def resolve_src_for_addr(ai: int) -> tuple[Path, str] | None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                src = o.get("source") or ""
                for base in (ROOT / "src" / "halo", ROOT / "src"):
                    p = base / src
                    if p.exists():
                        return p, src
    return None


def main() -> int:
    true0, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    flips = []
    # First try one unicode to validate callee names exist
    for ai, name, body, decl in LIFTS:
        loc = resolve_src_for_addr(ai)
        if not loc:
            print(f"skip no src {hex(ai)}")
            continue
        sp, _src = loc
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        ported = None
        for o in kb["objects"]:
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == ai:
                    ported = fn.get("ported")
                    if decl:
                        fn["decl"] = decl
        if ported is not False:
            print(f"skip already {hex(ai)} ported={ported}")
            continue
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")

        text = sp.read_text(encoding="utf-8", errors="replace")
        span = find_naked_block(text, name, ai)
        if span is None:
            print(f"skip locate {hex(ai)} {name}")
            continue
        sp.write_text(text[: span[0]] + body.strip() + "\n\n" + text[span[1] :], encoding="utf-8")
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
        res = run_unicorn(name, ai, 100, timeout=40.0)
        ok = clear_pass(res, 100)
        if not ok:
            res2 = run_unicorn(hex(ai), ai, 100, timeout=40.0)
            if clear_pass(res2, 100):
                res, ok = res2, True
        print(f"  ok={ok} {res.get('passed')}/{res.get('failed')}/{res.get('errors')}", flush=True)
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "unicode_ctype",
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
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")

    if flips:
        subprocess.run(["git", "add", "-u", "src/halo", "kb.json"], cwd=ROOT, check=False)
        subprocess.run(
            ["git", "add", "kb.json", "tools/equivalence/leaf_cache.json", "scripts/lift_unicode_ctype.py"],
            cwd=ROOT,
            check=False,
        )
        msg = f"lift(track-a): unicode/main thin wrappers + Unicorn-prove {len(flips)} (ported:true)."
        subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, check=False)
        git_push()

    # also push any ahead commits
    subprocess.run(["git", "push", "pastudan", "HEAD"], cwd=ROOT, check=False)

    true1, _ = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    summary = {"proven": len(flips), "flips": flips, "sha": sha, "true0": true0, "true1": true1}
    Path("/tmp/unicode_lift_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
