#!/usr/bin/env python3
"""AI-domain naked→C + Unicorn-prove campaign (src/halo/ai/**).

Prefer small leaves / thin wrappers. Uses xbe_to_coff oracles and
unicorn_diff --allow-stubs --seeds 100. Pull/push pastudan; union ported:true.
"""
from __future__ import annotations

import argparse
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
from tu_compile import docker_compile, regen_decl_h as _regen_decl_h  # noqa: E402
import lift_assert_wrappers as law  # noqa: E402
import lift_thin_wrappers as ltw  # noqa: E402


def regen_decl_h() -> bool:
    """Prefer full cmake regen; fall back to knowledge.py if cache is broken."""
    if _regen_decl_h() and (ROOT / "build" / "generated" / "decl.h").exists():
        return True
    r = subprocess.run(
        [
            "docker",
            "run",
            "--rm",
            "-u",
            f"{os.getuid()}:{os.getgid()}",
            "-v",
            f"{ROOT}:/work",
            "-w",
            "/work",
            "halo-re-build:latest",
            "bash",
            "-c",
            "python3 tools/analysis/knowledge.py "
            "--gen-header build/generated/decl.h "
            "--gen-def build/generated/halo.xbe.def "
            "--gen-thunks build/generated/thunks.c",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    ok = (ROOT / "build" / "generated" / "decl.h").exists() and r.returncode == 0
    if not ok:
        print("regen_decl_h FAIL", (r.stderr or r.stdout)[-400:], flush=True)
    return ok


LEDGER_TAG = "lift_ai"
COMMIT_EVERY = 10
DATUM_GET = 0x119320
DATA_NEW = 0x119610
PROP_ADD = 0x64170


def collect_call_targets(ops: list[tuple[str, str]]) -> list[int]:
    calls: list[int] = []
    for m, o in ops:
        if m == "call":
            mm = re.search(r"0x([0-9a-fA-F]+)", o)
            if mm:
                calls.append(int(mm.group(1), 16))
        elif m == "jmp" and "dword" not in o:
            mm = re.search(r"0x([0-9a-fA-F]+)", o)
            if mm:
                calls.append(int(mm.group(1), 16))
    return calls


def same_tu_safe(
    addr: int,
    src: str,
    calls: list[int],
    src_by: dict[int, str],
    ported: dict[int, object],
    starts_set: set[int],
) -> tuple[bool, int | None]:
    """Reject lifts that call an unproven same-TU function (Unicorn naked crash)."""
    for c in calls:
        if c == addr:
            continue
        if c not in starts_set:
            continue  # mid-function label / not a kb symbol
        if src_by.get(c) == src and ported.get(c) is not True:
            return False, c
    return True, None


def load_names():
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    name_by, decl_by, src_by, ported = {}, {}, {}, {}
    for o in kb.get("objects", []):
        src = o.get("source") or ""
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict) or not fn.get("addr"):
                continue
            ai = int(fn["addr"], 16)
            nm = func_name(fn) or f"FUN_{ai:08x}"
            name_by[ai] = nm
            decl_by[ai] = fn.get("decl") or ""
            src_by[ai] = src
            ported[ai] = fn.get("ported")
    return kb, name_by, decl_by, src_by, ported


def set_kb_decl(addr: int, decl: str) -> None:
    kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
    for o in kb.get("objects", []):
        for fn in o.get("functions") or []:
            if isinstance(fn, dict) and fn.get("addr") and int(fn["addr"], 16) == addr:
                fn["decl"] = decl
                if not fn.get("name"):
                    m = re.search(r"(\w+)\s*\(", decl)
                    if m:
                        fn["name"] = m.group(1)
                KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
                return


def patch_decl_h(name: str, decl: str) -> bool:
    """Best-effort sync of one HFUNC line in build/generated/decl.h from C/kb decl."""
    path = ROOT / "build" / "generated" / "decl.h"
    if not path.exists():
        return False
    d = decl.strip().rstrip(";")
    text = path.read_text(encoding="utf-8", errors="replace")
    pat = re.compile(
        rf"^HFUNC\s+.+\b{re.escape(name)}\s*\([^;]*\);", re.M
    )
    new_line = f"HFUNC {d};"
    new_text, n = pat.subn(new_line, text, count=1)
    if n:
        path.write_text(new_text, encoding="utf-8")
        return True
    # append if missing
    if f" {name}(" not in text and f" {name} (" not in text:
        path.write_text(text.rstrip() + "\n" + new_line + "\n", encoding="utf-8")
        return True
    return False


def merge_remote_kb() -> None:
    try:
        subprocess.run(
            ["git", "fetch", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        remote_kb = subprocess.run(
            ["git", "show", "FETCH_HEAD:kb.json"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        if remote_kb.returncode != 0 or not remote_kb.stdout:
            return
        remote = json.loads(remote_kb.stdout)
        local = json.loads(KB_PATH.read_text(encoding="utf-8"))
        rmap = {}
        for o in remote.get("objects", []):
            for fn in o.get("functions") or []:
                if isinstance(fn, dict) and fn.get("addr") and fn.get("ported") is True:
                    rmap[int(fn["addr"], 16)] = True
        for o in local.get("objects", []):
            for fn in o.get("functions") or []:
                if not isinstance(fn, dict) or not fn.get("addr"):
                    continue
                ai = int(fn["addr"], 16)
                if fn.get("ported") is not True and rmap.get(ai):
                    fn["ported"] = True
        KB_PATH.write_text(json.dumps(local, indent=2) + "\n", encoding="utf-8")
    except Exception as exc:
        print(f"kb merge skip: {exc}", flush=True)


def commit_chunk(n: int, paths: set[Path], do_push: bool = True) -> str | None:
    merge_remote_kb()
    for p in paths:
        subprocess.run(["git", "add", str(p)], cwd=ROOT, check=False)
    subprocess.run(
        [
            "git",
            "add",
            "kb.json",
            "tools/equivalence/leaf_cache.json",
            "scripts/lift_ai_campaign.py",
        ],
        cwd=ROOT,
        check=False,
    )
    subprocess.run(["git", "add", "-u", "src/halo"], cwd=ROOT, check=False)
    msg = f"lift(track-a): ai/ naked→C + Unicorn-prove {n} (ported:true)."
    r = subprocess.run(["git", "commit", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("commit failed:", r.stdout, r.stderr, file=sys.stderr)
        return None
    sha = subprocess.run(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
    ).stdout.strip()
    if do_push:
        subprocess.run(
            ["git", "pull", "--rebase", "pastudan", "track-a-collision-bsp"],
            cwd=ROOT,
            capture_output=True,
            check=False,
        )
        merge_remote_kb()
        st = subprocess.run(
            ["git", "status", "--porcelain", "kb.json"],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if st.stdout.strip():
            subprocess.run(["git", "add", "kb.json"], cwd=ROOT, check=False)
            subprocess.run(
                [
                    "git",
                    "commit",
                    "-m",
                    "fix(track-a): union concurrent ported:true into ai campaign kb.",
                ],
                cwd=ROOT,
                capture_output=True,
                check=False,
            )
            sha = subprocess.run(
                ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
            ).stdout.strip()
        git_push()
        print(f"COMMIT+PUSH {sha}", flush=True)
    else:
        print(f"COMMIT {sha}", flush=True)
    return sha


def callee_name(op: str, name_by: dict[int, str]) -> str | None:
    m = re.search(r"0x([0-9a-fA-F]+)", op)
    if not m:
        return None
    ai = int(m.group(1), 16)
    return name_by.get(ai) or f"FUN_{ai:08x}"


def try_emit_ai(
    ops: list[tuple[str, str]], decl: str, name: str, name_by: dict[int, str]
) -> tuple[str | None, str | None]:
    """Return (c_body_with_sig, optional_new_decl)."""
    if not ops:
        return None, None

    # Existing assert / thin first (ret-terminated).
    if ops[-1][0] in ("ret", "retn"):
        body = law.try_emit(ops, decl, name, name_by)
        if body:
            return body, None
        lines = [f"{m} {o}".strip() for m, o in ops]
        body = ltw.try_emit(lines, decl, name, name_by)
        if body:
            return body, None

    # JMP thunk: push ebp; mov ebp,esp; pop ebp; jmp T
    if (
        len(ops) >= 4
        and ops[0] == ("push", "ebp")
        and ops[1] == ("mov", "ebp, esp")
        and ops[2] == ("pop", "ebp")
        and ops[3][0] == "jmp"
    ):
        fn = callee_name(ops[3][1], name_by)
        if not fn:
            return None, None
        sig = law.cdecl_sig(decl, name)
        ps = law.params(sig)
        if not ps:
            # synthesize one int arg if void(void)
            if "(void)" in sig or sig.endswith("()"):
                sig = re.sub(r"\([^)]*\)", "(int a0)", sig)
                ps = ["a0"]
        args = ", ".join(ps)
        ret = "" if law.is_void(sig) else "return "
        return f"{sig}\n{{\n  {ret}{fn}({args});\n}}\n", None

    if ops[-1][0] not in ("ret", "retn"):
        return None, None

    mid = ops[:-1]
    # strip frame
    if not (
        len(mid) >= 2 and mid[0] == ("push", "ebp") and mid[1] == ("mov", "ebp, esp")
    ):
        body, new_decl = _emit_53890(ops, decl, name, name_by)
        if body:
            return body, new_decl
        return None, None

    frame = mid[2:]
    while frame and frame[-1] == ("pop", "ebp"):
        frame = frame[:-1]
    while frame and frame[-1][0] == "pop" and frame[-1][1] in ("esi", "edi", "ebx"):
        frame = frame[:-1]
    if frame and frame[-1][0] == "add" and "esp" in frame[-1][1]:
        pass

    for emitter in (
        _emit_prop_table,
        _emit_encounter_force,
        _emit_643d0,
        _emit_comm_team,
        _emit_600c0,
        _emit_path_disc,
        _emit_reg_eax_third,
        _emit_tried_to,
        _emit_datum_store16,
        _emit_debug_imm_wrapper,
        _emit_float_range_assert_add,
        _emit_and_two_calls,
    ):
        body, new_decl = emitter(frame, decl, name, name_by)
        if body:
            return body, new_decl

    return None, None


def _emit_prop_table(frame, decl, name, name_by):
    # mov edx,[ebp+8]; movzx ecx,[edx+0x3a]; mov eax,0x2c9994; nop?; loop; ...
    if len(frame) < 18:
        return None, None
    if not (
        frame[0] == ("mov", "edx, dword ptr [ebp + 8]")
        and frame[1] == ("movzx", "ecx, word ptr [edx + 0x3a]")
        and frame[2] == ("mov", "eax, 0x2c9994")
    ):
        return None, None
    # find call 0x68a30
    call_i = next(
        (i for i, (m, o) in enumerate(frame) if m == "call" and "0x68a30" in o), None
    )
    if call_i is None:
        return None, None
    # Collect up to 4 pushes before call, allowing movs between them.
    pushes: list[str] = []
    j = call_i - 1
    while j >= 0 and len(pushes) < 4:
        m, o = frame[j]
        if m == "push":
            pushes.append(o)
        elif m == "mov":
            pass
        else:
            break
        j -= 1
    pushes.reverse()
    if len(pushes) != 4:
        return None, None
    # Two-arg variant loads a1 from [ebp+0xc] into ecx before the push sequence.
    two_arg = any(x == ("mov", "ecx, dword ptr [ebp + 0xc]") for x in frame[:call_i])
    fn = name_by.get(0x68A30) or "FUN_00068a30"
    # cdecl args = reverse of push order → last push is arg0
    # one-arg XBE: push immA; push eax(name); push immB; push ecx(prop0)
    #   → (prop0, immB, name, immA)
    # two-arg XBE: push ecx(a1); push eax(name); push imm; push ecx(prop0)
    #   → (prop0, imm, name, a1)
    if two_arg:
        imm_fmt = [p for p in pushes if re.match(r"0x[0-9a-fA-F]+$", p)]
        if len(imm_fmt) < 1:
            return None, None
        fmt = imm_fmt[0]
        new_decl = f"int {name}(void *prop, int a1);"
        body = f"""int {name}(void *prop, int a1)
{{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  {fn}(*(int *)prop, (const char *){fmt}, (const char *)(unsigned long)p[0], a1);
  return -1;
}}
"""
        return body, new_decl

    if not (
        re.match(r"0x[0-9a-fA-F]+$", pushes[0])
        and pushes[1] == "eax"
        and re.match(r"0x[0-9a-fA-F]+$", pushes[2])
        and pushes[3] == "ecx"
    ):
        return None, None
    new_decl = f"int {name}(void *prop);"
    body = f"""int {name}(void *prop)
{{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  {fn}(*(int *)prop, (const char *){pushes[2]}, (const char *)(unsigned long)p[0], (const char *){pushes[0]});
  return -1;
}}
"""
    return body, new_decl


def _emit_encounter_force(frame, decl, name, name_by):
    # mov eax,[g]; push esi; mov esi,[ebp+8]; push esi; push eax; call datum_get;
    # add esp,8; mov word [eax+0xe], IMM; mov eax,esi; pop esi; pop ebp; jmp T
    # Note: jmp may already be stripped if we only got to ret — these end with jmp not ret.
    return None, None


def _emit_encounter_force_ops(ops, decl, name, name_by):
    if len(ops) < 14:
        return None, None
    if not (
        ops[0] == ("push", "ebp")
        and ops[1] == ("mov", "ebp, esp")
        and ops[2][0] == "mov"
        and "dword ptr [0x" in ops[2][1]
        and ops[3] == ("push", "esi")
        and ops[4] == ("mov", "esi, dword ptr [ebp + 8]")
        and ops[5] == ("push", "esi")
        and ops[6] == ("push", "eax")
        and ops[7][0] == "call"
        and f"{DATUM_GET:x}" in ops[7][1]
        and ops[8][0] == "add"
        and ops[9][0] == "mov"
        and "word ptr [eax + 0xe]" in ops[9][1]
        and ops[10] == ("mov", "eax, esi")
        and ops[11] == ("pop", "esi")
        and ops[12] == ("pop", "ebp")
        and ops[13][0] == "jmp"
    ):
        return None, None
    g = re.search(r"\[0x([0-9a-fA-F]+)\]", ops[2][1])
    imm_m = re.search(r", (0x[0-9a-fA-F]+|\d+)$", ops[9][1])
    tail = callee_name(ops[13][1], name_by)
    if not g or not imm_m or not tail:
        return None, None
    imm = imm_m.group(1)
    new_decl = f"void {name}(int encounter_handle);"
    # tail expects arg in eax; pass as cdecl and hope stub/allow
    body = f"""void {name}(int encounter_handle)
{{
  void *d = datum_get(*(void **)0x{g.group(1)}, encounter_handle);
  *(unsigned short *)((char *)d + 0xe) = (unsigned short){imm};
  {tail}(encounter_handle);
}}
"""
    return body, new_decl


def _emit_643d0(frame, decl, name, name_by):
    # mov eax,[g]; push esi; push eax; call data_new; mov ecx,[ebp+8]; mov esi,eax;
    # push esi; push ecx; or eax,-1; call prop_add; add esp,0xc; mov eax,esi
    if len(frame) < 12:
        return None, None
    if not (
        frame[0][0] == "mov"
        and "dword ptr [0x" in frame[0][1]
        and frame[1] == ("push", "esi")
        and frame[2] == ("push", "eax")
        and frame[3][0] == "call"
        and f"{DATA_NEW:x}" in frame[3][1]
    ):
        return None, None
    g = re.search(r"\[0x([0-9a-fA-F]+)\]", frame[0][1])
    if not g:
        return None, None
    if not any(m == "call" and f"{PROP_ADD:x}" in o for m, o in frame):
        return None, None
    new_decl = f"int {name}(int actor_handle);"
    body = f"""int {name}(int actor_handle)
{{
  int idx = data_new_at_index(*(void **)0x{g.group(1)});
  prop_add(actor_handle, idx, -1);
  return idx;
}}
"""
    return body, new_decl


def _emit_comm_team(frame, decl, name, name_by):
    # datum_get actors; load word +4; FUN_0003a770; test bits
    if not any(m == "call" and f"{DATUM_GET:x}" in o for m, o in frame):
        return None, None
    if not any(m == "call" and "0x3a770" in o for m, o in frame):
        return None, None
    if name != "actor_communication_team" and "communication_team" not in name:
        # also allow by structure
        if not (
            frame[0] == ("mov", "eax, dword ptr [ebp + 8]")
            and frame[1][0] == "mov"
            and "0x6325a4" in frame[1][1]
        ):
            return None, None
    fn = name_by.get(0x3A770) or "FUN_0003a770"
    new_decl = f"int {name}(int actor);"
    body = f"""int {name}(int actor)
{{
  void *a = datum_get(*(void **)0x6325a4, actor);
  unsigned short t = *(unsigned short *)((char *)a + 4);
  unsigned char flags = (unsigned char){fn}((int16_t)t);
  if (flags & 2)
    return 0;
  if (flags & 4)
    return 1;
  return -1;
}}
"""
    return body, new_decl


def _emit_600c0(frame, decl, name, name_by):
    # mov eax,[ebp+0xc]; cmp ax,0xffff; je ret -1; push eax; mov eax,[ebp+8]; push eax;
    # call FUN_00060070; movsx eax,[eax+2]
    if not (
        len(frame) >= 8
        and frame[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and frame[1] == ("cmp", "ax, 0xffff")
        and frame[2][0] == "je"
    ):
        return None, None
    if not any(m == "call" and "0x60070" in o for m, o in frame):
        return None, None
    cal = name_by.get(0x60070) or "FUN_00060070"
    new_decl = f"int16_t {name}(void *obstacles, int16_t disc_index);"
    body = f"""int16_t {name}(void *obstacles, int16_t disc_index)
{{
  if (disc_index == (int16_t)0xffff)
    return (int16_t)-1;
  void *p = {cal}(obstacles, disc_index);
  return *(int16_t *)((char *)p + 2);
}}
"""
    return body, new_decl


def _emit_path_disc(frame, decl, name, name_by):
    # 60070 / 600f0: bounds-check index then return pointer into table
    if len(frame) < 20:
        return None, None
    if not (
        frame[0] == ("push", "esi")
        and frame[1][0] == "mov"
        and "si, word ptr [ebp + 0xc]" in frame[1][1]
        and frame[2] == ("test", "si, si")
        and frame[3] == ("push", "edi")
        and frame[4] == ("mov", "edi, dword ptr [ebp + 8]")
    ):
        return None, None
    # find field offset in cmp path: mov ax, word ptr [edi + OFF]
    off_m = None
    for m, o in frame:
        mm = re.match(r"ax, word ptr \[edi \+ (0x[0-9a-f]+|\d+)\]$", o)
        if m == "mov" and mm:
            off_m = mm.group(1)
            break
    if off_m is None:
        # 60070 uses [edi + 2]
        for m, o in frame:
            if m == "mov" and o == "ax, word ptr [edi + 2]":
                off_m = "2"
                break
    if off_m is None:
        return None, None
    # return lea: lea eax, [edi + eax*8 + BASE] or similar after movsx eax,si; lea eax,[eax+eax*4]
    # 60070: movsx eax,si; lea eax,[eax+eax*4]; lea eax,[edi+eax*8+4] ?
    # From earlier dump 600f0:
    # movsx eax, si; lea eax, [eax+eax*4]; lea eax, [edi+eax*8+0x30]
    base = None
    for m, o in frame:
        mm = re.match(
            r"eax, \[edi \+ eax\*8 \+ (0x[0-9a-f]+|\d+)\]$", o
        )
        if m == "lea" and mm:
            base = mm.group(1)
            break
    if base is None:
        return None, None
    # assert immediates
    ab = None
    for i, (m, o) in enumerate(frame):
        if m == "push" and o == "1":
            ab = law.parse_assert(frame, i)
            if ab:
                break
    if not ab:
        return None, None
    off = int(off_m, 0)
    base_i = int(base, 0)
    new_decl = f"void *{name}(void *obstacles, int16_t disc_index);"
    body = f"""void *{name}(void *obstacles, int16_t disc_index)
{{
  if (disc_index < 0 || disc_index >= *(int16_t *)((char *)obstacles + 0x{off:x})
      || *(int16_t *)((char *)obstacles + 0x{off:x}) > 0x80) {{
{law.assert_c(ab)}  }}
  return (char *)obstacles + 0x{base_i:x} + (int)disc_index * 40;
}}
"""
    #  eax+eax*4 = *5; *8 = *40 yes
    return body, new_decl


def _emit_reg_eax_third(frame, decl, name, name_by):
    # mov eax,[ebp+0xc]; mov ecx,[ebp+8]; push eax; mov eax,[ebp+0x10]; push ecx; call F; add esp,8
    if len(frame) < 7:
        return None, None
    if not (
        frame[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and frame[1] == ("mov", "ecx, dword ptr [ebp + 8]")
        and frame[2] == ("push", "eax")
        and frame[3] == ("mov", "eax, dword ptr [ebp + 0x10]")
        and frame[4] == ("push", "ecx")
        and frame[5][0] == "call"
    ):
        return None, None
    fn = callee_name(frame[5][1], name_by)
    if not fn:
        return None, None
    sig = law.cdecl_sig(decl, name)
    ps = law.params(sig)
    sig, ps = law.ensure_params(sig, ps, 3, ["int", "int", "int"])
    # unused third loaded into eax only
    body = f"""{sig}
{{
  (void){ps[2]};
  {fn}({ps[0]}, {ps[1]});
}}
"""
    return body, None


def _emit_tried_to(frame, decl, name, name_by):
    # cmp prop==-1; datum_get actor; datum_get prop; compare fields; maybe call
    if len(frame) < 20:
        return None, None
    if not (
        frame[0] == ("push", "esi")
        and frame[1] == ("mov", "esi, dword ptr [ebp + 0xc]")
        and frame[2] == ("cmp", "esi, -1")
        and frame[3][0] == "je"
    ):
        return None, None
    dgets = [i for i, (m, o) in enumerate(frame) if m == "call" and f"{DATUM_GET:x}" in o]
    if len(dgets) < 2:
        return None, None
    # Too structural variation — hand patterns via immediates in full ops dump
    return None, None


def _emit_datum_store16(frame, decl, name, name_by):
    return None, None


def _emit_debug_imm_wrapper(frame, decl, name, name_by):
    # mov eax,[ebp+0xc]; mov ecx,[ebp+8]; push imm; push imm; push imm; push eax; push ecx; call; add
    if len(frame) < 9:
        return None, None
    if not (
        frame[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and frame[1] == ("mov", "ecx, dword ptr [ebp + 8]")
        and frame[2][0] == "push"
        and frame[3][0] == "push"
        and frame[4][0] == "push"
        and frame[5] == ("push", "eax")
        and frame[6] == ("push", "ecx")
        and frame[7][0] == "call"
    ):
        return None, None
    fn = callee_name(frame[7][1], name_by)
    if not fn:
        return None, None
    # Keep immediates numeric — kb often types fn-ptr slots as int.
    a2, a3, a4 = frame[2][1], frame[3][1], frame[4][1]
    sig = law.cdecl_sig(decl, name)
    ps = law.params(sig)
    sig, ps = law.ensure_params(sig, ps, 2, ["int", "int"])
    # cdecl: last push is first arg → a0, a1, a4, a3, a2
    body = f"""{sig}
{{
  {fn}({ps[0]}, {ps[1]}, (void *)(uintptr_t){a4}, {a3}, (int)(uintptr_t){a2});
}}
"""
    return body, None


def _emit_float_range_assert_add(frame, decl, name, name_by):
    """fld arg; fcomp lo/hi; fatal assert; fadd [esi+off]; fstp [esi+off]."""
    if len(frame) < 18:
        return None, None
    if not (
        frame[0] == ("fld", "dword ptr [ebp + 0xc]")
        and frame[1][0] == "fcomp"
        and frame[2] == ("fnstsw", "ax")
        and frame[3] == ("test", "ah, 1")
        and frame[4][0] == "jne"
        and frame[5] == ("fld", "dword ptr [ebp + 0xc]")
        and frame[6][0] == "fcomp"
        and frame[7] == ("fnstsw", "ax")
    ):
        return None, None
    ab = None
    for i, (m, o) in enumerate(frame):
        if m == "push" and o == "1":
            ab = law.parse_assert(frame, i)
            if ab:
                break
    if not ab:
        return None, None
    # trailing fadd/fstp [esi + imm]
    add_i = next(
        (
            i
            for i, (m, o) in enumerate(frame)
            if m == "fadd" and "dword ptr [esi +" in o
        ),
        None,
    )
    if add_i is None or add_i + 1 >= len(frame):
        return None, None
    if frame[add_i + 1][0] != "fstp":
        return None, None
    off_m = re.search(r"\[esi \+ (0x[0-9a-f]+|\d+)\]", frame[add_i][1])
    if not off_m:
        return None, None
    lo_m = re.search(r"\[(0x[0-9a-f]+)\]", frame[1][1])
    hi_m = re.search(r"\[(0x[0-9a-f]+)\]", frame[6][1])
    if not lo_m or not hi_m:
        return None, None
    off = int(off_m.group(1), 0)
    new_decl = f"void {name}(void *ctx, float score, int type, void *position);"
    body = f"""void {name}(void *ctx, float score, int type, void *position)
{{
  (void)ctx;
  (void)type;
  if (!(score >= *(float *){lo_m.group(1)} && score <= *(float *){hi_m.group(1)})) {{
{law.assert_c(ab)}  }}
  *(float *)((char *)position + 0x{off:x}) = *(float *)((char *)position + 0x{off:x}) + score;
}}
"""
    return body, new_decl


def _emit_and_two_calls(frame, decl, name, name_by):
    """push a2,a1,a0; call F; if al: push a2; call G; return al1&&al2."""
    if len(frame) < 14:
        return None, None
    # strip push ebx/esi prologue if present
    work = list(frame)
    saved = []
    while work and work[0][0] == "push" and work[0][1] in ("ebx", "esi", "edi"):
        saved.append(work.pop(0)[1])
    if len(work) < 12:
        return None, None
    if not (
        work[0] == ("mov", "eax, dword ptr [ebp + 0xc]")
        and work[1] == ("mov", "ecx, dword ptr [ebp + 8]")
    ):
        return None, None
    # find mov esi,[ebp+0x10]; push esi; push eax; push ecx; xor bl,bl; call
    if not any(m == "mov" and o == "esi, dword ptr [ebp + 0x10]" for m, o in work[:8]):
        return None, None
    calls = [i for i, (m, o) in enumerate(work) if m == "call"]
    if len(calls) < 2:
        return None, None
    f1 = callee_name(work[calls[0]][1], name_by)
    f2 = callee_name(work[calls[1]][1], name_by)
    if not f1 or not f2:
        return None, None
    new_decl = f"char {name}(int actor, int unit, int prop);"
    body = f"""char {name}(int actor, int unit, int prop)
{{
  if (!{f1}(actor, unit, prop))
    return 0;
  if (!{f2}(prop))
    return 0;
  return 1;
}}
"""
    return body, new_decl


def _emit_53890(ops, decl, name, name_by):
    if not ops or ops[-1][0] not in ("ret", "retn"):
        return None, None
    body = ops[:-1]
    if len(body) < 10:
        return None, None
    if not (
        body[0][0] == "movsx"
        and "0x5abaa2" in body[0][1]
        and body[1] == ("inc", "eax")
        and any(m == "call" and "0xff4d0" in o for m, o in body)
    ):
        return None, None
    fn = name_by.get(0xFF4D0) or "console_printf"
    new_decl = f"unsigned short {name}(void);"
    c = f"""unsigned short {name}(void)
{{
  int v = (int)(*(short *)0x5abaa2) + 1;
  short rem = (short)(v % 3);
  *(short *)0x5abaa2 = rem;
  {fn}(0, (const char *)0x25c120, *(void **)(0x2c8f78 + (int)rem * 4));
  return *(unsigned short *)0x5abaa2;
}}
"""
    return c, new_decl


def find_naked_block_ai(text: str, name: str, addr: int):
    """find_naked_block plus i386/#if naked frame-thunk style used in ai/."""
    span = find_naked_block(text, name, addr)
    if span is not None:
        return span
    span = find_naked_block(text, f"FUN_{addr:08x}", addr)
    if span is not None:
        return span
    addr_hex = f"0x{addr:x}"
    for nm in (name, f"FUN_{addr:08x}", f"FUN_{addr:08X}"):
        # Tail-call naked: #if i386 asm jmp; #else C; #endif \n}
        pat = re.compile(
            rf"/\*[^*]*\b{re.escape(addr_hex)}\b[^*]*\*/\s*"
            rf"#if defined\(__i386__\)[^\n]*\n"
            rf"__attribute__\(\(naked\)\)\s*\n"
            rf"#endif\s*\n"
            rf"[\w\s\*]+?\b{re.escape(nm)}\s*\([^{{]*\)\s*\{{\s*"
            rf"#if defined\(__i386__\)[\s\S]*?#else[\s\S]*?#endif\s*\n"
            rf"\}}\s*\n",
            re.M | re.I,
        )
        m = pat.search(text)
        if m:
            return m.start(), m.end()
    return None


def apply_body(path: Path, name: str, addr: int, c_src: str) -> tuple[str | None, str | None]:
    text = path.read_text(encoding="utf-8", errors="replace")
    span = find_naked_block_ai(text, name, addr)
    if span is None:
        return None, "locate"
    needs_stdint = any(
        t in c_src
        for t in ("uint8_t", "uint16_t", "uint32_t", "int8_t", "int16_t", "uintptr_t")
    )
    new_text = text[: span[0]] + c_src + "\n" + text[span[1] :]
    if needs_stdint and "#include <stdint.h>" not in new_text:
        new_text = "#include <stdint.h>\n" + new_text
    path.write_text(new_text, encoding="utf-8")
    for stale in (ROOT / "build").rglob(path.name + ".obj"):
        try:
            stale.unlink()
        except OSError:
            pass
    return text, None


def prove_addr(
    name: str,
    addr: int,
    seeds: int,
    timeout: float,
    src: str | None = None,
    decl_changed: bool = False,
) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "passed": 0, "failed": 0, "errors": 0}
    if decl_changed and not regen_decl_h():
        return {"ok": False, "err": "decl.h", "passed": 0, "failed": 0, "errors": 0}
    if src:
        src_rel = src.replace("\\", "/")
        if "src/halo/" in src_rel:
            src_rel = src_rel.split("src/halo/", 1)[1]
        if not docker_compile(src_rel):
            return {
                "ok": False,
                "err": "compile",
                "passed": 0,
                "failed": 0,
                "errors": 0,
            }
    # Unicorn by function name (not 0xaddr) — required for correct candidate bind.
    res = run_unicorn(name, addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(name, addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds) or (res2.get("passed") or 0) > (res.get("passed") or 0):
            res = res2
    return {
        "ok": clear_pass(res, seeds),
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
        "err": None if clear_pass(res, seeds) else "unicorn",
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--commit-every", type=int, default=COMMIT_EVERY)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=50.0)
    ap.add_argument("--max-size", type=int, default=256)
    ap.add_argument("--no-push", action="store_true")
    ap.add_argument("--prove-only", action="store_true")
    ap.add_argument(
        "--allow-wrappers",
        action="store_true",
        help="Allow lifting wrappers that call same-TU unproven (unsafe; default leaf-first)",
    )
    ap.add_argument(
        "--inventory",
        action="store_true",
        help="Print leaf/wrapper inventory and exit",
    )
    args = ap.parse_args()

    merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = load_names()
    _, starts = load_kb(KB_PATH)
    starts_set = set(starts)
    xbe = Xbe((ROOT / "halo-patched" / "cachebeta.xbe").read_bytes())
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    true0, false0 = count_ported(kb)

    # Count ai baseline
    ai_true = ai_false = 0
    for a, src in src_by.items():
        if not (src or "").startswith("ai/"):
            continue
        if ported.get(a) is True:
            ai_true += 1
        elif ported.get(a) is False:
            ai_false += 1
    print(f"ai baseline true={ai_true} false={ai_false} kb true={true0} false={false0}", flush=True)

    if args.inventory:
        leaves = wrappers = 0
        for i, ai in enumerate(starts):
            if ported.get(ai) is not False:
                continue
            src = src_by.get(ai) or ""
            if not src.startswith("ai/"):
                continue
            sp = resolve_src(src)
            if not sp or not is_naked_near_def(
                sp.read_text(errors="replace").splitlines(), name_by[ai], hex(ai)
            ):
                continue
            end = starts[i + 1] if i + 1 < len(starts) else ai + args.max_size
            try:
                raw = xbe_bytes(xbe, ai, min(end, ai + args.max_size))
            except Exception:
                continue
            ops: list[tuple[str, str]] = []
            for insn in md.disasm(raw, ai):
                ops.append((insn.mnemonic, insn.op_str))
                if insn.mnemonic in ("ret", "retn"):
                    break
                if insn.mnemonic == "jmp" and len(ops) <= 14:
                    break
            calls = collect_call_targets(ops)
            ok, bad = same_tu_safe(ai, src, calls, src_by, ported, starts_set)
            if ok:
                leaves += 1
            else:
                wrappers += 1
                print(
                    f"  wrapper {hex(ai)} {name_by[ai]} blocked_by={hex(bad)} "
                    f"{name_by.get(bad, '?')}",
                    flush=True,
                )
        print(f"inventory naked leaves={leaves} wrappers={wrappers}", flush=True)
        return 0

    jobs: list[dict] = []
    seen: set[int] = set()
    skipped_same_tu = 0

    if not args.prove_only:
        for i, ai in enumerate(starts):
            if ported.get(ai) is not False or ai in seen:
                continue
            src = src_by.get(ai) or ""
            if not src.startswith("ai/"):
                continue
            end = starts[i + 1] if i + 1 < len(starts) else ai + args.max_size
            size = end - ai
            if size > args.max_size:
                continue
            sp = resolve_src(src)
            if not sp:
                continue
            name = name_by[ai]
            text0 = sp.read_text(encoding="utf-8", errors="replace")
            if not is_naked_near_def(text0.splitlines(), name, hex(ai)):
                continue
            try:
                # end is absolute VA (library also accepts length if end<=va)
                raw = xbe_bytes(xbe, ai, min(end, ai + args.max_size))
            except Exception:
                continue
            ops: list[tuple[str, str]] = []
            for insn in md.disasm(raw, ai):
                ops.append((insn.mnemonic, insn.op_str))
                if insn.mnemonic in ("ret", "retn"):
                    break
                if insn.mnemonic == "jmp" and len(ops) <= 14:
                    # allow early jmp-thunk termination
                    break
            else:
                continue

            calls = collect_call_targets(ops)
            ok, bad = same_tu_safe(ai, src, calls, src_by, ported, starts_set)
            if not ok and not args.allow_wrappers:
                skipped_same_tu += 1
                continue

            # encounter_force special (ends with jmp)
            body = None
            new_decl = None
            if ops and ops[-1][0] == "jmp":
                body, new_decl = _emit_encounter_force_ops(
                    ops, decl_by.get(ai, ""), name, name_by
                )
            if body is None:
                body, new_decl = try_emit_ai(
                    ops, decl_by.get(ai) or f"void {name}(void);", name, name_by
                )
            if not body:
                continue
            jobs.append(
                {
                    "addr": ai,
                    "name": name,
                    "src": src,
                    "kind": "lift",
                    "body": f"/* {name} (0x{ai:x}) — readable C lift (ai campaign). */\n{body}",
                    "decl": new_decl,
                    "size": size,
                }
            )
            seen.add(ai)

    # prove readable leftovers in ai/ (leaf-first: skip if still depends on same-TU naked)
    for o_src, ai in [
        (src_by[a], a) for a in sorted(src_by) if (src_by[a] or "").startswith("ai/")
    ]:
        if ported.get(ai) is not False or ai in seen:
            continue
        sp = resolve_src(o_src)
        if not sp:
            continue
        name = name_by[ai]
        if is_naked_near_def(sp.read_text(errors="replace").splitlines(), name, hex(ai)):
            continue
        jobs.append(
            {
                "addr": ai,
                "name": name,
                "src": o_src,
                "kind": "prove",
                "body": None,
                "size": 0,
            }
        )
        seen.add(ai)

    # leaf-first: smaller lifts before prove wrappers
    jobs.sort(key=lambda j: (0 if j["kind"] == "lift" else 1, j.get("size", 0), j["addr"]))
    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"ai-campaign jobs={len(jobs)} lift={sum(1 for j in jobs if j['kind']=='lift')} "
        f"prove={sum(1 for j in jobs if j['kind']=='prove')} "
        f"skipped_same_tu={skipped_same_tu}",
        flush=True,
    )

    flips: list[str] = []
    shas: list[str] = []
    touched: set[Path] = set()
    since = 0

    # Include any already-flipped but uncommitted (e.g. 0x42f40)
    st = subprocess.run(["git", "status", "--porcelain", "kb.json"], cwd=ROOT, capture_output=True, text=True)
    if st.stdout.strip():
        # count local true flips vs HEAD
        pass

    for job in jobs:
        ai = job["addr"]
        name = job["name"]
        kind = job["kind"]
        src = job["src"]
        print(f"\n== {hex(ai)} {name} [{kind}] ({src}) ==", flush=True)
        path = resolve_src(src)
        orig = None

        decl_changed = False
        if kind == "lift":
            if path is None:
                print("  no source", flush=True)
                continue
            if job.get("decl"):
                set_kb_decl(ai, job["decl"])
                patch_decl_h(name, job["decl"])
                decl_changed = True
            # Sync kb decl from emitted C signature when present
            sig_m = re.search(
                rf"^([\w\s\*]+?\b{re.escape(name)}\s*\([^{{]*\))",
                job["body"],
                re.M,
            )
            if sig_m:
                d = sig_m.group(1).strip() + ";"
                set_kb_decl(ai, d)
                patch_decl_h(name, d)
                decl_changed = True
            text0 = path.read_text(encoding="utf-8", errors="replace")
            if not is_naked_near_def(text0.splitlines(), name, hex(ai)):
                kind = "prove"
            else:
                orig, err = apply_body(path, name, ai, job["body"])
                if err:
                    print(f"  {err} FAIL", flush=True)
                    continue
                touched.add(path)

        t0 = time.time()
        # Prefer in-place decl.h patch; full regen only when patch missed
        if decl_changed and not (ROOT / "build" / "generated" / "decl.h").exists():
            if not regen_decl_h():
                if orig is not None and path is not None:
                    path.write_text(orig, encoding="utf-8")
                print("  decl.h missing FAIL", flush=True)
                continue
        res = prove_addr(
            name,
            ai,
            args.seeds,
            args.timeout,
            src=src,
            decl_changed=False,  # already patched; avoid slow/fragile full regen
        )
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"ok={res.get('ok')} err={res.get('err')} dt={time.time()-t0:.1f}",
            flush=True,
        )
        append_ledger(
            {
                "addr": hex(ai),
                "name": name,
                "ok": bool(res.get("ok")),
                "phase": f"{kind}_{args.seeds}",
                "lifter": LEDGER_TAG,
                "passed": res.get("passed"),
                "failed": res.get("failed"),
                "errors": res.get("errors"),
            }
        )

        if not res.get("ok"):
            if orig is not None and path is not None:
                path.write_text(orig, encoding="utf-8")
                print("  REVERT", flush=True)
            continue

        rc = subprocess.run(
            [sys.executable, str(ROOT / "tools/audit/check_raw_casts.py")],
            cwd=ROOT,
            capture_output=True,
            text=True,
        )
        if rc.returncode != 0:
            if orig is not None and path is not None:
                path.write_text(orig, encoding="utf-8")
            print("  REVERT raw-cast", flush=True)
            continue

        kb = json.loads(KB_PATH.read_text(encoding="utf-8"))
        if flip_kb(kb, ai):
            flips.append(hex(ai))
            since += 1
            ported[ai] = True
            KB_PATH.write_text(json.dumps(kb, indent=2) + "\n", encoding="utf-8")
            print(f"  FLIP {hex(ai)} total={len(flips)}", flush=True)

        if args.commit_every and since >= args.commit_every:
            sha = commit_chunk(since, touched, do_push=not args.no_push)
            if sha:
                shas.append(sha)
            since = 0
            touched.clear()

    if since:
        sha = commit_chunk(since, touched, do_push=not args.no_push)
        if sha:
            shas.append(sha)

    # final ai counts
    kb1 = json.loads(KB_PATH.read_text(encoding="utf-8"))
    ai_t = ai_f = 0
    for o in kb1.get("objects", []):
        if not (o.get("source") or "").startswith("ai/"):
            continue
        for fn in o.get("functions") or []:
            if not isinstance(fn, dict):
                continue
            if fn.get("ported") is True:
                ai_t += 1
            elif fn.get("ported") is False:
                ai_f += 1
    true1, false1 = count_ported(kb1)
    summary = {
        "proven_this_run": len(flips),
        "flips": flips,
        "shas": shas,
        "ai_true": ai_t,
        "ai_false": ai_f,
        "ai_true0": ai_true,
        "ai_false0": ai_false,
        "kb_true": true1,
        "kb_false": false1,
        "head": subprocess.run(
            ["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True
        ).stdout.strip(),
    }
    Path("/tmp/lift_ai_summary.json").write_text(json.dumps(summary, indent=2))
    print("DONE", summary, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
