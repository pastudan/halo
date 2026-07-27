#!/usr/bin/env python3
"""Track A networking/hs/interface/game — naked→C + Unicorn ≥100/0/0; never naked-true."""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
sys.path.insert(0, str(ROOT / "tools" / "equivalence"))

from lift_inventory_batch4 import find_naked_block  # noqa: E402
from prove_inventory_batch4 import ensure_oracle, flip_kb  # noqa: E402
from tu_compile import docker_compile  # noqa: E402
from unicorn_c_campaign import KB_PATH, append_ledger, clear_pass, count_ported  # noqa: E402

# (addr, source, name, body|None if already C, decl|None, float_tol|None)
ITEMS: list[tuple] = []


def L(addr, src, name, body, decl=None, ft=None):
    if body is not None:
        body = body.strip() + "\n"
    ITEMS.append((addr, src, name, body, decl, ft))


# --- already-readable C: prove-only ---
L(0xB42D0, "game/game.c", "FUN_000b42d0", None, "wchar_t *FUN_000b42d0(int param_1, wchar_t *dst);")

# --- hand lifts ---
L(
    0xE4500,
    "interface/ui_widget.c",
    "display_error_deferred",
    """
/* display_error_deferred (0xe4500) — readable C lift. */
void display_error_deferred(int16_t error_handle, int16_t local_player_index, char a3, char a4)
{
  int slot;
  int idx;

  if (local_player_index == (int16_t)-1)
    slot = 0;
  else {
    slot = (int)local_player_index;
    if (slot < 0 || slot >= 4) {
      display_assert((const char *)0x283424, (const char *)0x283280, 0x8f0, 1);
      system_exit(-1);
    }
  }
  idx = slot * 6;
  if (*(int16_t *)(0x46cc50 + idx) != (int16_t)-1) {
    error(2, (const char *)0x2833d0, slot);
    return;
  }
  *(int16_t *)(0x46cc50 + idx) = error_handle;
  *(int16_t *)(0x46cc52 + idx) = local_player_index;
  *(char *)(0x46cc54 + idx) = a3;
  *(char *)(0x46cc55 + idx) = a4;
}
""",
    "void display_error_deferred(int16_t error_handle, int16_t local_player_index, char a3, char a4);",
)

L(
    0xDD110,
    "interface/first_person_weapons.c",
    "first_person_weapon_get_local_index",
    """
/* first_person_weapon_get_local_index (0xdd110) — readable C lift. */
int first_person_weapon_get_local_index(int object_handle)
{
  int i;
  char *base;
  char *fp;
  int *slot;

  for (i = 0; i < 4; i++) {
    if ((int16_t)i < 0 || (int16_t)i >= 4) {
      display_assert((const char *)0x266fc0, (const char *)0x282294, 0x599, 1);
      system_exit(-1);
    }
    base = *(char **)0x46bea8;
    fp = base + i * 0x1ea0;
    slot = (int *)(fp + 8);
    if (*slot == object_handle && *fp != 0)
      return i;
  }
  return -1;
}
""",
    "int first_person_weapon_get_local_index(int object_handle);",
)

L(
    0xBB220,
    "game/players.c",
    "players_handle_deleted_object",
    """
/* players_handle_deleted_object (0xbb220) — readable C lift. */
void players_handle_deleted_object(int object_handle)
{
  void *obj;
  unsigned char type_bits;
  unsigned int mask;
  data_iter_t iter;
  void *player;

  obj = object_get_and_verify_type(object_handle, -1);
  type_bits = *(unsigned char *)((char *)obj + 0x64);
  mask = 1u << type_bits;
  if ((mask & 3) == 0)
    return;
  data_iterator_new(&iter, *(data_t **)0x5aa6d4);
  for (player = data_iterator_next(&iter); player != 0; player = data_iterator_next(&iter)) {
    if (*(int *)((char *)player + 0x34) == object_handle)
      player_died(*(int *)((char *)&iter + 8));
  }
}
""",
    "void players_handle_deleted_object(int object_handle);",
)

L(
    0x80B40,
    "networking/message_header.c",
    "build_message_header",
    """
/* build_message_header (0x80b40) — readable C lift. */
void build_message_header(unsigned short *header, unsigned short length, unsigned char type, unsigned char flags)
{
  unsigned short v;
  unsigned short t;
  unsigned short f;

  if (header == 0) {
    display_assert((const char *)0x265cc8, (const char *)0x265ccc, 0x43, 1);
    system_exit(-1);
  }
  if (length > 0xfff) {
    display_assert((const char *)0x265c94, (const char *)0x265ccc, 0x45, 1);
    system_exit(-1);
  }
  v = (unsigned short)((*header & 0xf) | ((unsigned short)length << 4));
  *header = v;
  if (type == 0 || type >= 4) {
    display_assert((const char *)0x265c64, (const char *)0x265ccc, 0x46, 1);
    system_exit(-1);
  }
  t = (unsigned short)((type & 3) << 2);
  v = (unsigned short)((*header & 0xfff3) | t);
  *header = v;
  if (flags > 3) {
    display_assert((const char *)0x265bec, (const char *)0x265ccc, 0x47, 1);
    system_exit(-1);
  }
  f = (unsigned short)(flags & 0xffff);
  v = (unsigned short)((*header & 0xfffc) | (f & 3));
  *header = v;
}
""",
    "void build_message_header(unsigned short *header, unsigned short length, unsigned char type, unsigned char flags);",
)

L(
    0x80CA0,
    "networking/message_header.c",
    "create_message",
    """
/* create_message (0x80ca0) — readable C lift. */
int create_message(int type, int payload, unsigned int payload_len, int buffer, unsigned short buffer_size)
{
  unsigned short total;
  int buf;
  int need;

  total = (unsigned short)(payload_len + 2);
  buf = buffer;
  if (buf != 0) {
    need = (int)(short)total;
    if ((int)buffer_size < need) {
      display_assert((const char *)0x265d24, (const char *)0x265ccc, 0x29, 1);
      system_exit(-1);
    }
  } else {
    buf = (int)debug_malloc((uint32_t)(int)(short)total, 0, (const char *)0x265ccc, 0x2e);
  }
  if (buf != 0) {
    build_message_header((unsigned short *)buf, total, (unsigned char)type, 0);
    if (payload != 0)
      csmemcpy((void *)(buf + 2), (void *)payload, (size_t)(payload_len & 0xffff));
  }
  return buf;
}
""",
    "int create_message(int type, int payload, unsigned int payload_len, int buffer, unsigned short buffer_size);",
)

def audit_naked_true() -> list[tuple[str, str, str]]:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    bad = []
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        if not src:
            continue
        sp = ROOT / "src" / "halo" / src
        if not sp.exists():
            continue
        text = sp.read_text(encoding="utf-8", errors="ignore")
        for f in o.get("functions") or []:
            if f.get("ported") is not True:
                continue
            name = f.get("name") or ""
            addr = (f.get("addr") or "").lower()
            if not addr:
                continue
            pat = re.compile(
                rf"/\*[^*]*\b{re.escape(addr)}\b[^*]*\*/\s*#if defined\(__clang__\)\s*"
                rf"(?:static[\s\S]*?)?__attribute__\(\(naked[\s\S]*?#endif",
                re.I,
            )
            if pat.search(text):
                bad.append((name or "?", addr, src))
    return bad


def apply_one(addr, source, name, body, decl) -> tuple[bool, str, str]:
    sp = ROOT / "src" / "halo" / source
    text = sp.read_text(encoding="utf-8", errors="replace")
    if body is None:
        if re.search(rf"0x{addr:x}", text, re.I) and "naked" not in (
            re.search(rf"/\*[^*]*0x{addr:x}[^*]*\*/([\s\S]{{0,120}})", text, re.I).group(1)
            if re.search(rf"/\*[^*]*0x{addr:x}[^*]*\*/([\s\S]{{0,120}})", text, re.I)
            else "naked"
        ):
            return True, "already_c", text
        # already C without "readable C" marker
        if not re.search(
            rf"0x{addr:x}[^\n]*\*/\s*#if defined\(__clang__\)\s*(?:static[\s\S]*?)?__attribute__\(\(naked",
            text,
            re.I,
        ):
            return True, "already_c", text
        return False, "still_naked", text
    if re.search(rf"0x{addr:x}[^\n]*readable C lift", text, re.I):
        return True, "already", text
    span = find_naked_block(text, name, addr)
    if not span:
        return False, "locate", text
    chunk = text[span[0] : span[1]]
    if len(chunk.encode()) > 2500:
        return False, "too_big", text
    new_text = text[: span[0]] + body + "\n" + text[span[1] :]
    if "int16_t" in body and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    sp.write_text(new_text, encoding="utf-8")
    if decl:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                    fn["decl"] = decl if decl.endswith(";") else decl + ";"
                    if not fn.get("name"):
                        fn["name"] = name
        KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
    if not docker_compile(source):
        sp.write_text(text, encoding="utf-8")
        return False, "compile", text
    return True, "ok", text


def run_uni(name: str, addr: int, seeds: int = 100, timeout: float = 120.0, ft=None) -> dict:
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s{seeds}.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        str(seeds),
        "-q",
        "--output-json",
        str(outj),
    ]
    if ft is not None:
        cmd += ["--float-tolerance", str(ft)]
    env = os.environ.copy()
    env["BIPED_SIBLING_RESOLVE"] = "1"
    try:
        proc = subprocess.run(
            cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env
        )
    except subprocess.TimeoutExpired:
        return {"passed": 0, "failed": 0, "errors": 1, "tail": "TIMEOUT"}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    elif outj.exists():
        try:
            payload = json.loads(outj.read_text())
            passed = payload.get("passed", payload.get("seeds_passed"))
            failed = payload.get("failed", payload.get("seeds_failed"))
            errors = payload.get("errors", payload.get("seeds_errors"))
        except Exception:
            pass
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "tail": text[-500:],
        "missing_candidate": "missing_build_object" in text or "cannot find" in text,
    }


def commit_push(flips: list[str], touched: set[Path]) -> None:
    files = ["kb.json", "scripts/lift_grok_w5.py"]
    files += [str(p.relative_to(ROOT)) for p in sorted(touched)]
    files = list(dict.fromkeys(files))
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): {len(flips)} Unicorn-prove leaves ({' '.join(flips[:8])}) (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
    for _ in range(5):
        subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        rb = subprocess.run(
            ["git", "rebase", "pastudan/track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rb.returncode == 0:
            break
        print("rebase fail", (rb.stdout or "")[-200:], (rb.stderr or "")[-200:], flush=True)
        subprocess.run(["git", "rebase", "--abort"], cwd=ROOT, capture_output=True)
        return
    bad = audit_naked_true()
    # filter false positives for necessity-naked that aren't ported - audit only ported
    bad = [b for b in bad if b[1]]
    if bad:
        print("ABORT push naked-true", bad[:10], flush=True)
        return
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    print("PUSH", r.returncode, (r.stderr or r.stdout)[-400:], flush=True)


def main() -> int:
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    total0 = true0 + false0
    print(f"start true={true0}/{total0} ({100*true0/total0:.2f}%) naked_true={len(audit_naked_true())}", flush=True)
    flips: list[str] = []
    touched: set[Path] = set()

    for addr, source, name, body, decl, ft in ITEMS:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        already = False
        for o in kb.get("objects", []):
            for fn in o.get("functions") or []:
                if fn.get("addr") and int(fn["addr"], 16) == addr and fn.get("ported") is True:
                    already = True
        if already:
            print(f"\n== 0x{addr:x} {name} already true ==", flush=True)
            continue
        print(f"\n== 0x{addr:x} {name} ==", flush=True)
        ok, err, orig = apply_one(addr, source, name, body, decl)
        if not ok:
            print(f"  apply FAIL {err}", flush=True)
            continue
        if err == "compile":
            continue
        if not ensure_oracle(addr):
            print("  oracle FAIL", flush=True)
            if body is not None:
                (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        res = run_uni(name, addr, ft=ft)
        if not clear_pass(res, 100):
            res2 = run_uni(hex(addr), addr, ft=ft)
            if clear_pass(res2, 100) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
        okp = clear_pass(res, 100)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={okp}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(addr),
                "name": name,
                "ok": okp,
                "phase": "lift_grok_w5",
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )
        if not okp:
            if body is not None and err != "already_c":
                (ROOT / "src" / "halo" / source).write_text(orig)
            print(f"  REVERT {(res.get('tail') or '')[-180:]}", flush=True)
            continue
        cur = (ROOT / "src" / "halo" / source).read_text(encoding="utf-8", errors="ignore")
        if re.search(
            rf"0x{addr:x}[^\n]*\*/\s*#if defined\(__clang__\)\s*(?:static[\s\S]*?)?__attribute__\(\(naked",
            cur,
            re.I,
        ):
            print("  REVERT still naked", flush=True)
            if body is not None:
                (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(name)
            touched.add(ROOT / "src" / "halo" / source)
            print(f"  FLIP {len(flips)}", flush=True)

    print("FLIPS", flips, flush=True)
    if flips:
        bad = audit_naked_true()
        print("pre-push naked_true", len(bad), bad[:5], flush=True)
        if bad:
            print("REFUSING commit: naked-true != 0", flush=True)
            return 2
        commit_push(flips, touched)
    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    total1 = true1 + false1
    print(
        f"DONE proven={len(flips)} tip={true1}/{total1} ({100*true1/total1:.2f}%) naked_true={len(audit_naked_true())}",
        flush=True,
    )
    print("SYMBOLS", " ".join(flips), flush=True)
    return 0 if len(flips) >= 1 else 1


if __name__ == "__main__":
    raise SystemExit(main())
