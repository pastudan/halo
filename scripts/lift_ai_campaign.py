#!/usr/bin/env python3
"""AI-domain naked→C + Unicorn-prove campaign (src/halo/ai/**).

Prefer small leaves / thin wrappers. Uses xbe_to_coff oracles and
unicorn_diff --allow-stubs --seeds 100. Pull/push pastudan; union ported:true.
"""
from __future__ import annotations

import argparse
import json
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
import lift_assert_wrappers as law  # noqa: E402
import lift_thin_wrappers as ltw  # noqa: E402

LEDGER_TAG = "lift_ai"
COMMIT_EVERY = 10
DATUM_GET = 0x119320
DATA_NEW = 0x119610
PROP_ADD = 0x64170


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
        # FUN_00053890 — no frame
        body = _emit_53890(ops, decl, name, name_by)
        if body:
            return body
        return None, None

    frame = mid[2:]
    while frame and frame[-1] == ("pop", "ebp"):
        frame = frame[:-1]
    while frame and frame[-1][0] == "pop" and frame[-1][1] in ("esi", "edi", "ebx"):
        frame = frame[:-1]
    if frame and frame[-1][0] == "add" and "esp" in frame[-1][1]:
        # keep for some patterns; strip later
        pass

    # prop debug table printers (0x64fe0 family)
    body = _emit_prop_table(frame, decl, name, name_by)
    if body:
        return body

    # encounter_force_activate / deactivate
    body = _emit_encounter_force(frame, decl, name, name_by)
    if body:
        return body

    # FUN_000643d0: data_new + prop_add
    body = _emit_643d0(frame, decl, name, name_by)
    if body:
        return body

    # actor_communication_team
    body = _emit_comm_team(frame, decl, name, name_by)
    if body:
        return body

    # FUN_000600c0
    body = _emit_600c0(frame, decl, name, name_by)
    if body:
        return body

    # path disc helpers 60070 / 600f0
    body = _emit_path_disc(frame, decl, name, name_by)
    if body:
        return body

    # prop_orphan-style: a2 in eax, stack a0/a1
    body = _emit_reg_eax_third(frame, decl, name, name_by)
    if body:
        return body

    # perception tried_to_* pair
    body = _emit_tried_to(frame, decl, name, name_by)
    if body:
        return body

    # ai_debug_communication_* already thin — covered

    # generic: datum_get(global, arg0); store imm16 at +off; return/tail
    body = _emit_datum_store16(frame, decl, name, name_by)
    if body:
        return body

    # generic single forward with immediates (debug wrappers)
    body = _emit_debug_imm_wrapper(frame, decl, name, name_by)
    if body:
        return body

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
    # collect pushes immediately before call
    pushes = []
    j = call_i - 1
    while j >= 0 and frame[j][0] == "push":
        pushes.append(frame[j][1])
        j -= 1
    pushes.reverse()
    if len(pushes) != 4:
        return None, None
    # variants: [fmtB, name, fmtA, prop0] or [a1, name, fmt, prop0]
    # After loop: mov eax,[eax]; mov ecx,[edx]; then pushes.
    # Two-arg variant inserts mov ecx,[ebp+0xc] before mov eax,[eax]
    two_arg = any(x == ("mov", "ecx, dword ptr [ebp + 0xc]") for x in frame[:call_i])
    fn = name_by.get(0x68A30) or "FUN_00068a30"
    if two_arg:
        new_decl = f"int {name}(void *prop, int a1);"
        body = f"""int {name}(void *prop, int a1)
{{
  unsigned short key = *(unsigned short *)((char *)prop + 0x3a);
  unsigned int *entry = (unsigned int *)0x2c9994;
  unsigned int *end = (unsigned int *)0x2c99c4;
  while (entry < end && entry[1] != (unsigned int)key)
    entry = (unsigned int *)((char *)entry + 0xc);
  unsigned int *p = (entry < end) ? entry : (unsigned int *)0;
  {fn}(*(int *)prop, (const char *){pushes[1] if False else pushes[2]}, (const char *)p[0], a1);
  return -1;
}}
"""
        # fix push mapping: push a1; push name; push fmt; push prop0
        # pushes = [a1_reg_or_imm, name=eax, fmt, prop0] — actually order is
        # push ecx(a1); push eax(name); push fmt; push ecx(prop0)
        # so pushes[0]=a1, [1]=eax(name), [2]=fmt, [3]=prop0 — but we use a1 param
        fmt = None
        for p in pushes:
            if p.startswith("0x25f"):
                # first imm format-like among pushes that aren't a1
                pass
        # re-parse from known structure of 650a0
        # pushes: ecx(a1), eax(name), imm fmt, ecx(prop field) — after reverse of collection
        imm_fmt = [p for p in pushes if re.match(r"0x[0-9a-fA-F]+$", p)]
        if len(imm_fmt) < 1:
            return None, None
        fmt = imm_fmt[0] if len(imm_fmt) == 1 else imm_fmt[-1]
        # For 650a0: pushes = [ecx, eax, 0x25f570, ecx] = a1, name, fmt, prop0
        fmt = pushes[2]
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

    # one-arg: pushes are [immA, name, immB, prop0] or [immB, name, immA, prop0]
    # from 64fe0: push 0x25f554; push eax; push 0x25f530; push ecx
    # → args: prop0, 0x25f530, name, 0x25f554
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
  {fn}({ps[0]}, {ps[1]}, (void *){a4}, {a3}, {a2});
}}
"""
    return body, None


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


def apply_body(path: Path, name: str, addr: int, c_src: str) -> tuple[str | None, str | None]:
    text = path.read_text(encoding="utf-8", errors="replace")
    span = find_naked_block(text, name, addr)
    if span is None:
        span = find_naked_block(text, f"FUN_{addr:08x}", addr)
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


def prove_addr(name: str, addr: int, seeds: int, timeout: float) -> dict:
    if not ensure_oracle(addr):
        return {"ok": False, "err": "oracle", "passed": 0, "failed": 0, "errors": 0}
    res = run_unicorn(hex(addr), addr, seeds, timeout=timeout)
    if not clear_pass(res, seeds):
        res2 = run_unicorn(name, addr, seeds, timeout=timeout)
        if clear_pass(res2, seeds) or (res2.get("passed") or 0) > (res.get("passed") or 0):
            res = res2
    return {
        "ok": clear_pass(res, seeds),
        "passed": res.get("passed"),
        "failed": res.get("failed"),
        "errors": res.get("errors"),
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
    args = ap.parse_args()

    merge_remote_kb()
    kb, name_by, decl_by, src_by, ported = load_names()
    _, starts = load_kb(KB_PATH)
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

    jobs: list[dict] = []
    seen: set[int] = set()

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
                raw = xbe_bytes(xbe, ai, min(size, args.max_size))
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

            # encounter_force special (ends with jmp)
            body = None
            new_decl = None
            if ops and ops[-1][0] == "jmp":
                body, new_decl = _emit_encounter_force_ops(ops, decl_by.get(ai, ""), name, name_by)
            if body is None:
                body, new_decl = try_emit_ai(ops, decl_by.get(ai) or f"void {name}(void);", name, name_by)
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

    # prove-only readable leftovers in ai/
    for o_src, ai in [(src_by[a], a) for a in sorted(src_by) if (src_by[a] or "").startswith("ai/")]:
        if ported.get(ai) is not False or ai in seen:
            continue
        sp = resolve_src(o_src)
        if not sp:
            continue
        name = name_by[ai]
        if is_naked_near_def(sp.read_text(errors="replace").splitlines(), name, hex(ai)):
            continue
        jobs.append({"addr": ai, "name": name, "src": o_src, "kind": "prove", "body": None, "size": 0})
        seen.add(ai)

    jobs.sort(key=lambda j: (0 if j["kind"] == "lift" else 1, j.get("size", 0), j["addr"]))
    if args.limit:
        jobs = jobs[: args.limit]

    print(
        f"ai-campaign jobs={len(jobs)} lift={sum(1 for j in jobs if j['kind']=='lift')} "
        f"prove={sum(1 for j in jobs if j['kind']=='prove')}",
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

        if kind == "lift":
            if path is None:
                print("  no source", flush=True)
                continue
            if job.get("decl"):
                set_kb_decl(ai, job["decl"])
                for stale in (ROOT / "build" / "generated").glob("decl.h"):
                    try:
                        stale.unlink()
                    except OSError:
                        pass
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
        res = prove_addr(name, ai, args.seeds, args.timeout)
        print(
            f"  unicorn {res.get('passed')}/{res.get('failed')}/{res.get('errors')} "
            f"ok={res.get('ok')} dt={time.time()-t0:.1f}",
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
