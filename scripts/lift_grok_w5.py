#!/usr/bin/env python3
"""Track A networking/hs/interface/game — naked→C + Unicorn ≥100/0/0."""
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

ITEMS: list[tuple] = []


def L(addr, src, name, body, decl=None):
    ITEMS.append((addr, src, name, body.strip() + "\n", decl))


L(
    0xE2470,
    "interface/progress_bar.c",
    "SetTextureStageStateSmart",
    """
/* SetTextureStageStateSmart (0xe2470) — readable C lift. */
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
""",
    "void SetTextureStageStateSmart(int stage, int state, int value);",
)

L(
    0xBC6C0,
    "game/players.c",
    "debug_player_teleport",
    """
/* debug_player_teleport (0xbc6c0) — readable C lift. */
void debug_player_teleport(int16_t local_a, int16_t local_b)
{
  int unit_a;
  int unit_b;
  int player_a;
  void *obj;
  void *pos;

  player_a = local_player_get_player_index(local_a);
  if (player_a == -1)
    unit_a = -1;
  else
    unit_a = *(int *)((char *)datum_get(*(data_t **)0x5aa6d4, player_a) + 0x34);

  player_a = local_player_get_player_index(local_b);
  if (player_a == -1)
    unit_b = -1;
  else
    unit_b = *(int *)((char *)datum_get(*(data_t **)0x5aa6d4, player_a) + 0x34);

  if (unit_a == -1 || unit_b == -1)
    return;
  obj = object_get_and_verify_type(unit_b, 3);
  pos = (char *)obj + 0x50;
  FUN_000bb670(player_index_from_unit_index(unit_a), (void *)unit_b, pos);
}
""",
    "void debug_player_teleport(int16_t local_a, int16_t local_b);",
)

L(
    0x11A230,
    "networking/network_messages.c",
    "FUN_0011a230",
    """
/* FUN_0011a230 (0x11a230) — readable C lift. */
bool FUN_0011a230(int *state, const char *source, short max_length)
{
  int n;
  int used;
  int cap;
  char *dst;
  int need;

  n = (int)(short)strnlen(source, (int)max_length);
  used = state[1];
  dst = (char *)state[0] + used;
  cap = state[2];
  need = used + n + 1;
  if (need > cap) {
    display_assert((const char *)0x28f010, (const char *)0x28eef8, 0xb6, 1);
    system_exit(-1);
  }
  if (used + n + 1 <= cap && *((char *)state + 0xc) == 0) {
    csstrncpy(dst, source, (size_t)n);
    dst[n] = 0;
    state[1] = used + n + 1;
    return *((char *)state + 0xc) == 0;
  }
  *((char *)state + 0xc) = 1;
  return *((char *)state + 0xc) == 0;
}
""",
    "bool FUN_0011a230(int *state, const char *source, short max_length);",
)

L(
    0xF0100,
    "interface/ui_widget_game_data_input_functions.c",
    "FUN_000f0100",
    """
/* FUN_000f0100 (0xf0100) — readable C lift. */
char FUN_000f0100(void *unused_widget, void *player_ui, char *out_flag)
{
  int16_t ctrl;
  int16_t cur;

  (void)unused_widget;
  if (player_ui == 0) {
    display_assert((const char *)0x288670, (const char *)0x2859a4, 0x11c7, 1);
    system_exit(-1);
  }
  ctrl = *(int16_t *)((char *)player_ui + 2);
  cur = player_ui_get_single_player_local_player_controller(0);
  if (ctrl == cur) {
    ui_widget_display_error(0x12, -1, 1, 0);
    *out_flag = 1;
    return 0;
  }
  player_ui_set_single_player_local_player_controller(1, ctrl);
  return 1;
}
""",
    "char FUN_000f0100(void *unused_widget, void *player_ui, char *out_flag);",
)

L(
    0xE1F20,
    "interface/progress_bar.c",
    "FUN_000e1f20",
    """
/* FUN_000e1f20 (0xe1f20) — readable C lift. */
int __stdcall FUN_000e1f20(int unused, unsigned int reg, float a, float b, float c, float d)
{
  (void)unused;
  D3DDevice_SetVertexData4f(reg, a, b, c, d);
  return 0;
}
""",
    "int __stdcall FUN_000e1f20(int unused, unsigned int reg, float a, float b, float c, float d);",
)

L(
    0x803D0,
    "networking/message_header.c",
    "key_agreement_build_message",
    """
/* key_agreement_build_message (0x803d0) — readable C lift. */
unsigned short *key_agreement_build_message(short type, void *data, int buffer, unsigned short buffer_size)
{
  char encoded[0x84];
  int encoded_size;
  unsigned short *msg;
  unsigned short hdr;

  csmemset(encoded, 0, sizeof(encoded));
  encoded_size = 0x80;
  if (!encode_packet_group((group_definition *)0x2ee588, data, encoded, &encoded_size, type, 1))
    return 0;
  msg = (unsigned short *)create_message(3, (int)encoded, (unsigned int)encoded_size, buffer, buffer_size);
  if (msg == 0)
    return 0;
  hdr = *msg;
  hdr = (unsigned short)((hdr & 0xfffe) | 2);
  *msg = hdr;
  return msg;
}
""",
    "unsigned short *key_agreement_build_message(short type, void *data, int buffer, unsigned short buffer_size);",
)

L(
    0xD98C0,
    "interface/event_manager.c",
    "FUN_000d98c0",
    """
/* FUN_000d98c0 (0xd98c0) — readable C lift. */
void FUN_000d98c0(int16_t local_a, int16_t local_b)
{
  void *src;
  void *dst;
  int i;

  if (local_a == (int16_t)-1) {
    display_assert((const char *)0x281eb8, (const char *)0x281eec, 0x89, 1);
    system_exit(-1);
  }
  if (local_b == (int16_t)-1) {
    display_assert((const char *)0x281e98, (const char *)0x281eec, 0x8a, 1);
    system_exit(-1);
  }
  src = FUN_000d8bc0(local_b);
  dst = FUN_000d8bc0(local_a);
  for (i = 0; i < 0xa; i++)
    ((int *)dst)[i] = ((int *)src)[i];
  src = FUN_000d8c30(local_b);
  dst = FUN_000d8c30(local_a);
  for (i = 0; i < 0x14; i++)
    ((int *)dst)[i] = ((int *)src)[i];
}
""",
    "void FUN_000d98c0(int16_t local_a, int16_t local_b);",
)


def audit_naked_true():
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    bad = []
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        sp = ROOT / "src" / "halo" / src
        if not sp.is_file():
            continue
        text = sp.read_text(encoding="utf-8", errors="ignore")
        for f in o.get("functions") or []:
            if f.get("ported") is not True:
                continue
            addr = (f.get("addr") or "").lower()
            if not addr:
                continue
            if re.search(
                rf"/\*[^*]*\b{re.escape(addr)}\b[^*]*\*/\s*#if defined\(__clang__\)\s*"
                rf"(?:static[\s\S]*?)?__attribute__\(\(naked[\s\S]*?#endif",
                text,
                re.I,
            ):
                bad.append((f.get("name") or "?", addr, src))
    return bad


def apply_one(addr, source, name, body, decl):
    sp = ROOT / "src" / "halo" / source
    text = sp.read_text(encoding="utf-8", errors="replace")
    if re.search(rf"0x{addr:x}[^\n]*readable C lift", text, re.I):
        return True, "already", text
    span = find_naked_block(text, name, addr)
    if not span:
        return False, "locate", text
    if len(text[span[0] : span[1]].encode()) > 3500:
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


def run_uni(name, addr, timeout=120.0):
    outj = ROOT / "artifacts" / "equivalence" / f"uni_{addr:08x}_s100.json"
    outj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        sys.executable,
        str(ROOT / "tools" / "equivalence" / "unicorn_diff.py"),
        name,
        "--allow-stubs",
        "--no-stub-arg-trace",
        "--seeds",
        "100",
        "-q",
        "--output-json",
        str(outj),
    ]
    env = os.environ.copy()
    env["BIPED_SIBLING_RESOLVE"] = "1"
    try:
        proc = subprocess.run(cmd, cwd=str(ROOT), capture_output=True, text=True, timeout=timeout, env=env)
    except subprocess.TimeoutExpired:
        return {"passed": 0, "failed": 0, "errors": 1, "tail": "TIMEOUT"}
    text = (proc.stdout or "") + (proc.stderr or "")
    m = re.search(r"(\d+) passed, (\d+) failed, (\d+) errors", text)
    passed = failed = errors = None
    if m:
        passed, failed, errors = map(int, m.groups())
    return {
        "passed": passed,
        "failed": failed,
        "errors": errors,
        "tail": text[-500:],
        "missing_candidate": "cannot find" in text or "missing_build" in text,
    }


def commit_push(flips, touched):
    files = ["kb.json", "scripts/lift_grok_w5.py"] + [str(p.relative_to(ROOT)) for p in sorted(touched)]
    subprocess.run(["git", "add"] + files, cwd=ROOT, check=False)
    msg = f"lift(track-a): {len(flips)} Unicorn-prove leaves ({' '.join(flips[:8])}) (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed", r.stdout, r.stderr, flush=True)
        return
    for _ in range(3):
        subprocess.run(["git", "fetch", "pastudan", "track-a-collision-bsp"], cwd=ROOT, capture_output=True)
        # stash dirt
        subprocess.run(["git", "stash", "push", "-u", "-m", "tmp"], cwd=ROOT, capture_output=True)
        rb = subprocess.run(
            ["git", "rebase", "pastudan/track-a-collision-bsp"], cwd=ROOT, capture_output=True, text=True
        )
        subprocess.run(["git", "stash", "pop"], cwd=ROOT, capture_output=True)
        if rb.returncode == 0:
            break
        print("rebase fail", (rb.stderr or rb.stdout)[-300:], flush=True)
        subprocess.run(["git", "rebase", "--abort"], cwd=ROOT, capture_output=True)
        return
    if audit_naked_true():
        print("ABORT naked-true", audit_naked_true()[:5], flush=True)
        return
    r = subprocess.run(
        ["git", "push", "pastudan", "HEAD:track-a-collision-bsp"], cwd=ROOT, capture_output=True, text=True
    )
    print("PUSH", r.returncode, (r.stderr or r.stdout)[-400:], flush=True)


def main():
    true0, false0 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    total0 = true0 + false0
    print(f"start true={true0}/{total0} ({100*true0/total0:.2f}%) naked_true={len(audit_naked_true())}", flush=True)
    flips = []
    touched = set()
    for addr, source, name, body, decl in ITEMS:
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if any(
            fn.get("addr") and int(fn["addr"], 16) == addr and fn.get("ported") is True
            for o in kb["objects"]
            for fn in o.get("functions") or []
        ):
            print(f"\n== 0x{addr:x} {name} already ==", flush=True)
            continue
        print(f"\n== 0x{addr:x} {name} ==", flush=True)
        ok, err, orig = apply_one(addr, source, name, body, decl)
        if not ok:
            print(f"  apply FAIL {err}", flush=True)
            continue
        if not ensure_oracle(addr):
            print("  oracle FAIL", flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        res = run_uni(name, addr)
        if not clear_pass(res, 100):
            res2 = run_uni(hex(addr), addr)
            if clear_pass(res2, 100) or (res2.get("passed") or 0) > (res.get("passed") or 0):
                res = res2
        okp = clear_pass(res, 100)
        print(f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} ok={okp}", flush=True)
        append_ledger({"addr": hex(addr), "name": name, "ok": okp, "phase": "lift_grok_w5",
                       "passed": res.get("passed"), "failed": res.get("failed"), "errors": res.get("errors")})
        if not okp:
            (ROOT / "src" / "halo" / source).write_text(orig)
            print(f"  REVERT {(res.get('tail') or '')[-160:]}", flush=True)
            continue
        cur = (ROOT / "src" / "halo" / source).read_text(encoding="utf-8", errors="ignore")
        if re.search(
            rf"0x{addr:x}[^\n]*\*/\s*#if defined\(__clang__\)\s*(?:static[\s\S]*?)?__attribute__\(\(naked",
            cur,
            re.I,
        ):
            print("  REVERT still naked", flush=True)
            (ROOT / "src" / "halo" / source).write_text(orig)
            continue
        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, addr):
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            flips.append(name)
            touched.add(ROOT / "src" / "halo" / source)
            print(f"  FLIP {len(flips)}", flush=True)
    print("FLIPS", flips, flush=True)
    if flips and not audit_naked_true():
        commit_push(flips, touched)
    true1, false1 = count_ported(json.loads(KB_PATH.read_text(encoding="utf-8")))
    total1 = true1 + false1
    print(f"DONE proven={len(flips)} tip={true1}/{total1} ({100*true1/total1:.2f}%) naked_true={len(audit_naked_true())}", flush=True)
    print("SYMBOLS", " ".join(flips), flush=True)
    return 0 if flips else 1


if __name__ == "__main__":
    raise SystemExit(main())
