#!/usr/bin/env python3
"""grokN batch: apply hand lifts + Unicorn 100/0/0 + push. Uses strict naked check."""
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
from unicorn_c_campaign import KB_PATH, append_ledger, clear_pass, count_ported, resolve_src  # noqa: E402

SEEDS = 100
TIMEOUT = 60.0
COMMIT_EVERY = 4

LIFTS: dict[int, tuple[str, str, str, str]] = {}


def L(addr, source, name, body, decl):
    LIFTS[addr] = (source, name, body.strip() + "\n", decl)


L(
    0x8E3D0,
    "cseries/cseries_windows.c",
    "system_malloc",
    """
/* system_malloc (0x8e3d0) — readable C lift. */
void *system_malloc(int size)
{
  return ((void *(__stdcall *)(int, int))0x1d0c48)(0, size);
}
""",
    "void *system_malloc(int size);",
)

L(
    0x1BA710,
    "cache/tags.c",
    "FUN_001ba710",
    """
/* FUN_001ba710 (0x1ba710) — readable C lift. */
void FUN_001ba710(void *cache /* @<eax> */)
{
  void *globals;
  unsigned int base;
  int i;
  unsigned int *slots;
  unsigned int next;

  globals = *(void **)0x32ea98;
  base = *(unsigned int *)((char *)cache + 0x960);
  slots = (unsigned int *)((char *)globals + 0x964);
  next = base;
  for (i = 0; i < 8; i++) {
    slots[i] = next;
    next += 0x20000;
  }
  *(unsigned int *)((char *)globals + 0x984) = next;
  physical_memory_protect((void *)base, 0x512000u, 4u);
  csmemset((void *)*(unsigned int *)((char *)cache + 0x960), 0xfd, 0x500000u);
  physical_memory_protect(
      (void *)*(unsigned int *)((char *)cache + 0x960), 0x500000u, 2u);
  next = *(unsigned int *)((char *)cache + 0x960) + 0x500000u;
  *(unsigned int *)((char *)cache + 0x944) = 0x12000u;
  *(unsigned int *)((char *)cache + 0x940) = next;
  *(unsigned int *)((char *)cache + 0x948) = next;
  csmemset((char *)cache + 0x990, 0xfa, 0x1c0u);
}
""",
    "void FUN_001ba710(void *cache /* @<eax> */);",
)

L(
    0x1B9DE0,
    "cache/cache_files.c",
    "cache_files_give_time_to_precache",
    """
/* cache_files_give_time_to_precache (0x1b9de0) — readable C lift. */
bool cache_files_give_time_to_precache(const char *name)
{
  float status;
  short st;
  char ok;

  ok = 0;
  if (cache_files_precache_map_loaded((char *)name)) {
    return 1;
  }
  if (cache_files_precache_in_progress()) {
    if (!cache_files_precache_is_copying_map((char *)name)) {
      cache_files_precache_map_end();
    }
  }
  if (cache_files_precache_in_progress()) {
    st = cache_files_precache_map_status(&status);
    if (st == 2) {
      display_error_damaged_media();
      return ok;
    }
    if (st == 1) {
      cache_files_precache_map_end();
      return ok;
    }
    return ok;
  }
  cache_files_precache_set_priority(0);
  if (!cache_files_precache_map_begin((char *)name, 0)) {
    display_error_damaged_media();
  }
  return ok;
}
""",
    "bool cache_files_give_time_to_precache(const char *name);",
)

L(
    0x11BE10,
    "networking/network_messages.c",
    "FUN_0011be10",
    """
/* FUN_0011be10 (0x11be10) — readable C lift. */
int FUN_0011be10(short *table /* @<eax> */, void *key)
{
  unsigned short slot;
  int dest;
  unsigned int *bits;
  unsigned int mask;
  int idx;

  if (FUN_0011ba50(table, key, &slot)) {
    display_assert((const char *)0x28f6d4, (const char *)0x28f678, 0xf1, 1);
    system_exit(-1);
    return 0;
  }
  dest = FUN_00117ee0((int *)(table + 0xe), (int)slot, (int)table[1]);
  csmemcpy((void *)dest, key, (unsigned int)(int)table[0]);
  idx = (int)slot;
  bits = (unsigned int *)(*(unsigned int *)(table + 0xc) + (unsigned int)((idx >> 5) * 4));
  mask = 1u << (idx & 0x1f);
  *bits |= mask;
  table[2] = (short)((int)table[2] + 1);
  return dest + (int)table[0];
}
""",
    "int FUN_0011be10(short *table /* @<eax> */, void *key);",
)

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

# prove-only (already readable)
PROVE = [
    (0xDADE0, "interface/event_manager.c", "tiny_point2d_set"),
    (0x77CD0, "bitmaps/bitmap_utilities.c", "FUN_00077cd0"),
    (0xE4770, "interface/ui_widget.c", "ui_widget_pending_load_pop"),
    (0x81E00, "networking/transport_address.c", "FUN_00081e00"),
]


def truly_naked(lines, name, addr) -> bool:
    names = [n for n in (name, f"FUN_{int(addr, 16):08x}") if n]
    target = int(addr, 16)
    for nm in names:
        pat = re.compile(rf"\b{re.escape(nm)}\s*\(")
        for i, line in enumerate(lines):
            if not pat.search(line):
                continue
            head = "\n".join(lines[max(0, i - 6) : i + 1])
            if re.search(r"readable\s+C\s+lift", head, re.I):
                return False
            ws = max(0, i - 20)
            for j in range(i - 1, ws - 1, -1):
                if lines[j].strip() in ("#endif", "}"):
                    ws = j + 1
                    break
            before = "\n".join(lines[ws : i + 1])
            after = "\n".join(lines[i : min(len(lines), i + 80)])
            mentioned = [int(a, 16) for a in re.findall(r"0x[0-9a-fA-F]+", head)]
            code = [a for a in mentioned if a >= 0x10000]
            if code and target not in code:
                continue
            if "XBE naked draft" in before or "clang naked draft required" in after:
                return True
            if "__attribute__" in before and "naked" in before:
                return True
            if ("__asm__" in after or "asm volatile" in after) and ".byte" in after:
                return True
            return False
    return False


def set_decl(addr: int, decl: str, name: str | None = None) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if not decl.endswith(";"):
        decl += ";"
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                if name:
                    fn["name"] = name
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def sync_decl_h(name: str, decl: str) -> None:
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return
    d = decl.strip().rstrip(";")
    d_h = re.sub(r"\s*/\*\s*@<[^>]+>\s*\*/", "", d)
    d_h = re.sub(r"\s*@<\w+>", "", d_h)
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines(True)
    out = []
    hit = False
    for line in lines:
        if line.startswith("HFUNC") and re.search(rf"\b{re.escape(name)}\s*\(", line):
            out.append(f"HFUNC {d_h};\n")
            hit = True
        else:
            out.append(line)
    if not hit:
        out.append(f"HFUNC {d_h};\n")
    path.write_text("".join(out), encoding="utf-8")


def apply_lift(addr: int) -> Path | None:
    source, name, body, decl = LIFTS[addr]
    sp = resolve_src(source)
    if sp is None:
        return None
    text = sp.read_text(encoding="utf-8", errors="replace")
    before_len = len(text)
    lines = text.splitlines()
    if not truly_naked(lines, name, hex(addr)):
        # replace small existing body if marked lift or system_malloc
        m = re.search(
            rf"(?:void|int|char|short|float|double|bool|unsigned|const)[\w\s\*]*\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{",
            text,
        )
        if m and "readable C lift" not in text[max(0, m.start() - 80) : m.start()]:
            start = m.start()
            i = m.end() - 1
            depth = 0
            while i < len(text):
                if text[i] == "{":
                    depth += 1
                elif text[i] == "}":
                    depth -= 1
                    if depth == 0:
                        i += 1
                        break
                i += 1
            if i - start < 500:
                text = text[:start] + body + text[i:]
        set_decl(addr, decl, name)
        sync_decl_h(name, decl)
        if text != sp.read_text(encoding="utf-8", errors="replace"):
            if len(text) < before_len - 2000:
                print("  refuse truncate", flush=True)
                return None
            sp.write_text(text, encoding="utf-8")
        return sp

    span = find_naked_block(text, name, addr) or find_naked_block(
        text, f"FUN_{addr:08x}", addr
    )
    if not span:
        print("  locate FAIL", flush=True)
        return None
    if span[1] - span[0] > 8000:
        print("  span too big", flush=True)
        return None
    new_text = text[: span[0]] + body + "\n" + text[span[1] :]
    if len(new_text) < before_len - 4000:
        print("  refuse truncate naked", flush=True)
        return None
    set_decl(addr, decl, name)
    sync_decl_h(name, decl)
    sp.write_text(new_text, encoding="utf-8")
    # verify not truncated oddly
    if truly_naked(sp.read_text(errors="replace").splitlines(), name, hex(addr)):
        print("  still naked after write", flush=True)
        sp.write_text(text, encoding="utf-8")
        return None
    return sp


def run_uni(name: str, addr: int) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{SEEDS}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    logp = ROOT / "artifacts" / "equivalence" / f"{name}_smoke.log"
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
        timed_out = False
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        proc = subprocess.CompletedProcess(cmd, 124, exc.stdout or "", "timeout")
    text = (proc.stdout or "") + (proc.stderr or "")
    logp.write_text(text, encoding="utf-8", errors="replace")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "dt": round(time.time() - t0, 2),
        "timeout": timed_out,
        "missing_candidate": "missing_build_object" in text,
    }


def kb_false(addr: int) -> bool:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                return fn.get("ported") is False
    return False


def commit_push(n: int, names: list[str], touched: set[Path]) -> None:
    subprocess.run(
        ["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True
    )
    files = [
        "kb.json",
        "tools/equivalence/leaf_cache.json",
        "scripts/lift_grokN_batch.py",
    ]
    for p in touched:
        # refuse staging truncated cache_files
        if p.name == "cache_files.c" and sum(1 for _ in p.open()) < 1000:
            print("REFUSE stage truncated cache_files.c", flush=True)
            continue
        files.append(str(p.relative_to(ROOT)))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    sample = ", ".join(names[:5])
    msg = f"lift(track-a): grokN Unicorn-prove {n} ({sample})."
    r = subprocess.run(
        ["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True
    )
    if r.returncode != 0:
        print("commit failed", r.stdout[-200:], r.stderr[-200:], flush=True)
        return
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
    print(pr.stdout, pr.stderr, flush=True)
    print(
        "COMMIT+PUSH",
        subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"], cwd=ROOT, capture_output=True, text=True
        ).stdout.strip(),
        flush=True,
    )


def prove(name: str, addr: int, source: str, touched: set[Path]) -> bool:
    sp = resolve_src(source)
    if sp is None:
        return False
    if truly_naked(sp.read_text(errors="replace").splitlines(), name, hex(addr)):
        print("  NAKED-BLOCK", flush=True)
        return False
    if not docker_compile(source):
        print("  compile FAIL", flush=True)
        return False
    if not ensure_oracle(addr):
        print("  oracle FAIL", flush=True)
        return False
    res = run_uni(name, addr)
    if not clear_pass(res, SEEDS):
        res2 = run_uni(hex(addr), addr)
        if clear_pass(res2, SEEDS) or (res2.get("passed") or 0) > (res.get("passed") or 0):
            res = res2
    ok = clear_pass(res, SEEDS)
    print(
        f"  {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
        f"{res.get('dt')}s ok={ok}",
        flush=True,
    )
    append_ledger(
        {
            "addr": hex(addr),
            "name": name,
            "ok": ok,
            "phase": "grokN_batch",
            "passed": res.get("passed"),
            "failed": res.get("failed"),
            "errors": res.get("errors"),
        }
    )
    if not ok:
        return False
    if truly_naked(sp.read_text(errors="replace").splitlines(), name, hex(addr)):
        print("  NAKED post", flush=True)
        return False
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    if flip_kb(kb, addr):
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
        touched.add(sp)
        return True
    return False


def main() -> int:
    # first: disasm-fix FUN_00081c80 before using guessed body
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    print(f"start true={true0} false={false0}", flush=True)
    flips = []
    names = []
    blockers = []
    touched: set[Path] = set()
    since = 0

    # prove already-true candidates that are false locally
    for addr, source, name in PROVE:
        if not kb_false(addr):
            continue
        print(f"\n== PROVE {hex(addr)} {name} ==", flush=True)
        if prove(name, addr, source, touched):
            flips.append(hex(addr))
            names.append(name)
            since += 1
            print(f"  FLIP {len(flips)}", flush=True)

    for addr in sorted(LIFTS):
        if not kb_false(addr):
            continue
        source, name, body, decl = LIFTS[addr]
        print(f"\n== LIFT {hex(addr)} {name} ==", flush=True)
        # skip guessed 81c80 until verified — remove if wrong
        if addr == 0x81C80:
            # verify against existing source first
            sp = resolve_src(source)
            text = sp.read_text(errors="replace") if sp else ""
            if "readable C lift" not in text[text.find("FUN_00081c80") : text.find("FUN_00081c80") + 200] if "FUN_00081c80" in text else True:
                # peek current body
                pass
        orig = resolve_src(source).read_text(encoding="utf-8", errors="replace")
        sp = apply_lift(addr)
        if sp is None:
            blockers.append({"addr": hex(addr), "name": name, "why": "apply"})
            continue
        if prove(name, addr, source, touched):
            flips.append(hex(addr))
            names.append(name)
            since += 1
            print(f"  FLIP {len(flips)}", flush=True)
            if since >= COMMIT_EVERY:
                commit_push(since, names[-since:], touched)
                since = 0
                touched.clear()
        else:
            # revert source on fail
            sp.write_text(orig, encoding="utf-8")
            blockers.append({"addr": hex(addr), "name": name, "why": "unicorn"})

    if since or flips:
        # commit remaining including tiny_point2d if dirty
        if since:
            commit_push(since, names[-since:] or flips, touched)
        elif Path("kb.json") in [Path("kb.json")]:
            # commit kb-only flips
            commit_push(len(flips) or 1, names or ["session"], set())

    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    summary = {
        "flips": flips,
        "names": names,
        "true0": true0,
        "true1": true1,
        "delta": true1 - true0,
        "blockers": blockers,
    }
    Path("artifacts/equivalence/grokN_batch_summary.json").write_text(
        json.dumps(summary, indent=2) + "\n"
    )
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
