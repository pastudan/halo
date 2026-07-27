#!/usr/bin/env python3
"""Track A grokO batch V: lift/prove easy leaves, push each Unicorn 100/0/0 win."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import (  # noqa: E402
    KB_PATH,
    append_ledger,
    clear_pass,
    count_ported,
    func_name,
    is_naked_near_def,
    resolve_src,
)

SEEDS = 100
TIMEOUT = 55.0
TARGET = 15

# Hand lifts: (addr, src, name, body, decl)
LIFTS: list[tuple[int, str, str, str, str]] = []


def L(addr: int, src: str, name: str, body: str, decl: str) -> None:
    LIFTS.append((addr, src, name, body.strip() + "\n", decl))


# Empty ret stubs in sprites (still naked / false)
L(
    0x17D980,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017d980",
    """
/* FUN_0017d980 (0x17d980) — readable C lift. */
void FUN_0017d980(void)
{
}
""",
    "void FUN_0017d980(void);",
)
L(
    0x17D990,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017d990",
    """
/* FUN_0017d990 (0x17d990) — readable C lift. */
void FUN_0017d990(void)
{
}
""",
    "void FUN_0017d990(void);",
)
L(
    0x17E030,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017e030",
    """
/* FUN_0017e030 (0x17e030) — readable C lift. */
void FUN_0017e030(void)
{
}
""",
    "void FUN_0017e030(void);",
)

# Frame-tail jmp thunks already partially lifted but ensure body
L(
    0x17CF70,
    "rasterizer/rasterizer_sprites.c",
    "FUN_0017cf70",
    """
/* FUN_0017cf70 (0x17cf70) — readable C lift (frame-tail jmp to 0x15f210). */
void FUN_0017cf70(void)
{
  ((void (*)(void))0x15f210)();
}
""",
    "void FUN_0017cf70(void);",
)

# Preferred-domain: SetTextureStageStateSmart via hybrid ABI helpers
L(
    0xE2470,
    "interface/progress_bar.c",
    "SetTextureStageStateSmart",
    """
/* SetTextureStageStateSmart (0xe2470) — readable C lift. */
void SetTextureStageStateSmart(int stage, int state, int value)
{
  if (state < 0x16) {
    ((void (__stdcall *)(uint32_t))((uintptr_t)D3DDevice_SetTextureStageState))(
        (uint32_t)value);
    /* stage@ecx state@edx value@stack — match XBE hybrid ABI via asm-free
       register-arg call through declared HFUNC. */
    D3DDevice_SetTextureStageState((uint32_t)stage, (uint32_t)state, (uint32_t)value);
    return;
  }
  if (state == 0x1c) {
    D3DDevice_SetTextureState_TexCoordIndex((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state == 0x1d) {
    D3DDevice_SetTextureState_BorderColor((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state == 0x1e) {
    D3DDevice_SetTextureState_ColorKeyColor((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state <= 0x1b) {
    D3DDevice_SetTextureState_BumpEnv((uint32_t)stage, (uint32_t)state, (uint32_t)value);
  }
}
""",
    "void SetTextureStageStateSmart(int stage, int state, int value);",
)

# structures / networking / cache ready lifts from grokN
L(
    0x1913C0,
    "structures/structures.c",
    "reference_list_remove",
    """
/* reference_list_remove (0x1913c0) — readable C lift. */
void reference_list_remove(void *data, int *head, int value)
{
  void *node;
  int *link;

  link = head;
  if (*link == -1) {
    display_assert(
        csprintf((char *)0x5ab100, (const char *)0x2b2564, value),
        (const char *)0x2b25a0,
        0x6d,
        1);
    system_exit(-1);
    return;
  }
  for (;;) {
    node = datum_get(data, *link);
    if (*(int *)((char *)node + 4) == value) {
      datum_delete(data, *link);
      *link = *(int *)((char *)node + 8);
      return;
    }
    link = (int *)((char *)node + 8);
    if (*link == -1) {
      display_assert(
          csprintf((char *)0x5ab100, (const char *)0x2b2564, value),
          (const char *)0x2b25a0,
          0x6d,
          1);
      system_exit(-1);
      return;
    }
  }
}
""",
    "void reference_list_remove(void *data, int *head, int value);",
)

L(
    0x81110,
    "networking/message_header.c",
    "FUN_00081110",
    """
/* FUN_00081110 (0x81110) — readable C lift. */
unsigned int FUN_00081110(unsigned int bit_count /* @<esi> */, unsigned int bit_offset /* @<edi> */, int unused)
{
  if (bit_count <= 2) {
    display_assert((const char *)0x265de0, (const char *)0x265da0, 0x85, 1);
    system_exit(-1);
  }
  if (bit_offset >= (bit_count - 1)) {
    display_assert((const char *)0x265dd8, (const char *)0x265da0, 0x86, 1);
    system_exit(-1);
  }
  return FUN_00080fc0(bit_offset, unused, bit_count);
}
""",
    "unsigned int FUN_00081110(unsigned int bit_count /* @<esi> */, unsigned int bit_offset /* @<edi> */, int unused);",
)


def body_is_readable(lines: list[str], name: str, addr: str) -> bool:
    if is_naked_near_def(lines, name, addr):
        return False
    names = [n for n in (name, f"FUN_{int(addr, 16):08x}") if n]
    for nm in names:
        pat = re.compile(rf"\b{re.escape(nm)}\s*\(")
        for i, line in enumerate(lines):
            if not pat.search(line):
                continue
            chunk = "\n".join(lines[max(0, i - 2) : min(len(lines), i + 60)])
            if "__declspec(naked)" in chunk or "__attribute__((naked" in chunk:
                return False
            if "__asm" in chunk:
                return False
            if "{" in chunk:
                return True
    return False


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        sys.executable,
        str(ROOT / "tools/equivalence/unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(SEEDS),
        "-q",
        "--output-json",
        str(outj),
    ]
    env = os.environ.copy()
    env.setdefault("BIPED_SIBLING_RESOLVE", "1")
    t0 = time.time()
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=TIMEOUT, env=env
        )
    except subprocess.TimeoutExpired as exc:
        text = (exc.stdout or "") + (exc.stderr or "")
        return {
            "passed": None,
            "failed": None,
            "errors": None,
            "dt": round(time.time() - t0, 2),
            "timeout": True,
            "tail": text[-400:],
            "missing_candidate": False,
        }
    text = (proc.stdout or "") + (proc.stderr or "")
    (ROOT / "artifacts" / "equivalence" / f"{name}_smoke.log").write_text(
        text, encoding="utf-8", errors="replace"
    )
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    p = f = e = None
    if m:
        p, f, e = map(int, m.groups())
    return {
        "passed": p,
        "failed": f,
        "errors": e,
        "dt": round(time.time() - t0, 2),
        "timeout": False,
        "tail": text[-400:],
        "missing_candidate": "missing_build_object" in text
        or "cannot find build .obj" in text,
    }


def set_decl(addr: int, decl: str, name: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not decl.endswith(";"):
        decl += ";"
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                fn["name"] = name
    KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")


def apply_lift(addr: int, source: str, name: str, body: str, decl: str) -> str | None:
    sp = resolve_src(source)
    if sp is None:
        return "missing_src"
    text = sp.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines()
    if body_is_readable(lines, name, hex(addr)):
        set_decl(addr, decl, name)
        return None  # already readable
    span = find_naked_block(text, name, addr) or find_naked_block(
        text, f"FUN_{addr:08x}", addr
    )
    if not span:
        return "locate"
    new_text = text[: span[0]] + body + "\n" + text[span[1] :]
    if "stdint.h" not in new_text and ("uint32_t" in body or "int16_t" in body):
        new_text = "#include <stdint.h>\n" + new_text
    if "uintptr_t" in body and "stdint.h" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    sp.write_text(new_text, encoding="utf-8")
    set_decl(addr, decl, name)
    if not docker_compile(source):
        sp.write_text(text, encoding="utf-8")
        return "compile"
    return None


def merge_remote() -> None:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    r = subprocess.run(
        ["git", "show", "pastudan/track-a-collision-bsp:kb.json"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0 or not r.stdout:
        return
    try:
        theirs = json.loads(r.stdout)
    except json.JSONDecodeError:
        return
    ours = json.loads(KB_PATH.read_text(encoding="utf-8"))
    tmap = {
        int(fn["addr"], 16)
        for o in theirs.get("objects", [])
        for fn in o.get("functions") or []
        if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True
    }
    n = 0
    for o in ours.get("objects", []):
        for fn in o.get("functions") or []:
            if (
                isinstance(fn, dict)
                and fn.get("addr")
                and int(fn["addr"], 16) in tmap
                and fn.get("ported") is not True
            ):
                fn["ported"] = True
                n += 1
    if n:
        KB_PATH.write_text(json.dumps(ours, indent=2) + "\n", encoding="utf-8")
        print(f"merged {n} remote ported:true", flush=True)


def commit_push(name: str, addr: int, touched: list[Path]) -> bool:
    merge_remote()
    files = ["kb.json", "tools/equivalence/leaf_cache.json", "scripts/lift_grokO_batchV.py"]
    for p in touched:
        files.append(str(p.relative_to(ROOT)))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): {name} Unicorn-prove (ported:true)."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return False
    subprocess.run(
        ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
    )
    # if rebase conflict on kb, merge ported and continue
    if (ROOT / ".git" / "rebase-merge").exists() or (
        ROOT / ".git" / "rebase-apply"
    ).exists():
        merge_remote()
        subprocess.run(["git", "add", "kb.json"], cwd=ROOT, capture_output=True)
        subprocess.run(
            ["git", "rebase", "--continue"],
            cwd=ROOT,
            capture_output=True,
            env={**os.environ, "GIT_EDITOR": "true"},
        )
    pr = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print("PUSH", pr.returncode, (pr.stderr or pr.stdout)[-300:], flush=True)
    if pr.returncode != 0:
        # retry once
        subprocess.run(
            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
        )
        pr = subprocess.run(
            ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        print("PUSH2", pr.returncode, (pr.stderr or pr.stdout)[-300:], flush=True)
    return pr.returncode == 0


def inventory_prove_only() -> list[dict]:
    """Already-readable falses: prefer domains + sprite thunks."""
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    prefer = (
        "devices/",
        "effects/",
        "game/",
        "items/",
        "units/",
        "ai/",
        "interface/",
        "rasterizer/rasterizer_sprites",
        "cseries/",
        "structures/",
        "networking/",
        "math/",
        "cache/",
        "sound/",
        "text/",
    )
    skip = ("xdk/", "libcmt", "bink", "d3d", "kb_common", "tiff")
    out = []
    cache: dict[Path, list[str]] = {}
    for obj in kb.get("objects", []):
        src = (obj.get("source") or "").replace("\\", "/")
        if any(s in src.lower() for s in skip):
            continue
        if not any(p in src for p in prefer):
            continue
        sp = resolve_src(src)
        if not sp:
            continue
        if sp not in cache:
            cache[sp] = sp.read_text(encoding="utf-8", errors="replace").splitlines()
        lines = cache[sp]
        for fn in obj.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            if fn.get("ported") is not False:
                continue
            name = func_name(fn)
            addr = fn["addr"]
            if not body_is_readable(lines, name, addr):
                continue
            out.append(
                {
                    "addr": addr,
                    "addr_int": int(addr, 16),
                    "name": name,
                    "src": src,
                    "sp": sp,
                }
            )
    # prefer sprites / tiny addrs first
    def key(r):
        src = r["src"]
        pri = 0 if "rasterizer_sprites" in src else 1 if any(
            p in src for p in ("devices/", "effects/", "game/", "items/", "units/", "ai/", "interface/")
        ) else 2
        return (pri, r["addr_int"])

    out.sort(key=key)
    return out


def prove_one(name: str, ai: int, src: str, sp: Path) -> bool:
    lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
    if not body_is_readable(lines, name, hex(ai)):
        print("  DEMOTE not readable", flush=True)
        return False
    src_rel = src.replace("\\", "/")
    if src_rel.startswith("src/halo/"):
        src_rel = src_rel[len("src/halo/") :]
    if not docker_compile(src_rel):
        print("  compile FAIL", flush=True)
        return False
    if not ensure_oracle(ai):
        print("  oracle FAIL", flush=True)
        return False
    res = run_uni(name, ai)
    if not clear_pass(res, SEEDS):
        res2 = run_uni(hex(ai), ai)
        if clear_pass(res2, SEEDS) or (res2.get("passed") or 0) > (res.get("passed") or 0):
            res = res2
            name = hex(ai)
    ok = clear_pass(res, SEEDS)
    print(
        f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
        f"{res.get('dt')}s ok={ok}",
        flush=True,
    )
    append_ledger(
        {
            "addr": hex(ai),
            "name": name,
            "ok": ok,
            "phase": "grokO_batchV",
            "passed": res.get("passed"),
            "failed": res.get("failed"),
            "errors": res.get("errors"),
        }
    )
    if not ok:
        return False
    # final readable check
    lines = sp.read_text(encoding="utf-8", errors="replace").splitlines()
    # resolve original name from kb
    return True


def main() -> int:
    target = int(sys.argv[1]) if len(sys.argv) > 1 else TARGET
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} false={false0} target={target}", flush=True)

    flips: list[str] = []
    flip_names: list[str] = []

    # Phase 1: apply hand lifts then prove
    for addr, source, name, body, decl in LIFTS:
        if len(flips) >= target:
            break
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = any(
            isinstance(fn, dict)
            and fn.get("addr")
            and int(fn["addr"], 16) == addr
            and fn.get("ported") is True
            for o in kb["objects"]
            for fn in o.get("functions") or []
        )
        if already:
            print(f"\n== 0x{addr:x} {name} already true ==", flush=True)
            continue
        print(f"\n== 0x{addr:x} {name} [lift] ==", flush=True)
        # skip broken SetTextureStageStateSmart double-call version — fix below
        if addr == 0xE2470:
            # correct body without bogus stdcall cast
            body = """/* SetTextureStageStateSmart (0xe2470) — readable C lift. */
void SetTextureStageStateSmart(int stage, int state, int value)
{
  if (state < 0x16) {
    D3DDevice_SetTextureStageState((uint32_t)stage, (uint32_t)state, (uint32_t)value);
    return;
  }
  if (state == 0x1c) {
    D3DDevice_SetTextureState_TexCoordIndex((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state == 0x1d) {
    D3DDevice_SetTextureState_BorderColor((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state == 0x1e) {
    D3DDevice_SetTextureState_ColorKeyColor((uint32_t)stage, (uint32_t)value);
    return;
  }
  if (state <= 0x1b) {
    D3DDevice_SetTextureState_BumpEnv((uint32_t)stage, (uint32_t)state, (uint32_t)value);
  }
}
"""
        err = apply_lift(addr, source, name, body, decl)
        if err:
            print(f"  apply FAIL {err}", flush=True)
            continue
        sp = resolve_src(source)
        assert sp
        if not prove_one(name, addr, source, sp):
            # revert lift if we introduced it and prove failed? keep readable false
            print("  prove FAIL (kept readable C)", flush=True)
            continue
        if not body_is_readable(
            sp.read_text(encoding="utf-8", errors="replace").splitlines(),
            name,
            hex(addr),
        ):
            print("  DEMOTE naked", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(hex(addr))
            flip_names.append(name)
            print(f"  FLIP total={len(flips)}", flush=True)
            commit_push(name, addr, [sp])

    # Phase 2: prove already-readable queue
    rows = inventory_prove_only()
    print(f"\nprove-only queue={len(rows)}", flush=True)
    compiled: set[str] = set()
    for r in rows:
        if len(flips) >= target:
            break
        name, ai, src, sp = r["name"], r["addr_int"], r["src"], r["sp"]
        if any(hex(ai) == f for f in flips):
            continue
        print(f"\n== {hex(ai)} {name} [prove] ({src}) ==", flush=True)
        src_rel = src.replace("\\", "/")
        if src_rel.startswith("src/halo/"):
            src_rel = src_rel[len("src/halo/") :]
        if src_rel not in compiled:
            if not docker_compile(src_rel):
                print("  compile FAIL", flush=True)
                continue
            compiled.add(src_rel)
        if not ensure_oracle(ai):
            print("  oracle FAIL", flush=True)
            continue
        res = run_uni(name, ai)
        if not clear_pass(res, SEEDS):
            res2 = run_uni(hex(ai), ai)
            if clear_pass(res2, SEEDS) or (res2.get("passed") or 0) > (
                res.get("passed") or 0
            ):
                res = res2
        ok = clear_pass(res, SEEDS)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"{res.get('dt')}s ok={ok}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": ok,
                "phase": "grokO_batchV_prove",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not ok:
            continue
        if not body_is_readable(
            sp.read_text(encoding="utf-8", errors="replace").splitlines(),
            name,
            hex(ai),
        ):
            print("  DEMOTE naked", flush=True)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(hex(ai))
            flip_names.append(name)
            print(f"  FLIP total={len(flips)}", flush=True)
            commit_push(name, ai, [sp])

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "proven": len(flips),
        "names": flip_names,
        "flips": flips,
        "true0": true0,
        "true1": true1,
        "delta": true1 - true0,
    }
    outp = ROOT / "artifacts" / "equivalence" / "grokO_batchV_summary.json"
    outp.parent.mkdir(parents=True, exist_ok=True)
    outp.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print("DONE", summary, flush=True)
    return 0 if len(flips) >= target else 1


if __name__ == "__main__":
    raise SystemExit(main())
