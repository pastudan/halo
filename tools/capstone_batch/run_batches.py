#!/usr/bin/env python3
"""Pick Capstone weaks, emit naked XBE drafts, build, register waves, score.

Usage:
  python3 tools/capstone_batch/run_batches.py --start 162 --count 8
  python3 tools/capstone_batch/run_batches.py --start 162 --count 8 --build --register --commit
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
from collections import deque
from difflib import SequenceMatcher
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "verify"))
from compare_xbe_pe import Xbe, mnemonics, pe_fn_bytes, xbe_bytes  # noqa: E402

TEMPLATE = Path(__file__).resolve().parent / "gen_naked_template.py"
REMAIN = ROOT / "artifacts" / "remain_kbnext.json"
PER_BATCH = 12


def true_end(xbe: Xbe, md: Cs, va: int, scan: int = 0x4000) -> int | None:
    def get(addr: int, n: int) -> bytes | None:
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= addr < s + sec.header.virtual_size:
                return bytes(sec.data[addr - s : addr - s + n])
        return None

    data = get(va, scan)
    if not data:
        return None
    insns = list(md.disasm(data, va))
    succ: dict[int, list[int]] = {}
    for insn in insns:
        nxt: list[int] = []
        if insn.mnemonic == "ret":
            succ[insn.address] = []
            continue
        if insn.mnemonic.startswith("j"):
            if (
                insn.mnemonic == "jmp"
                and "dword" in insn.op_str
                and "*4" in insn.op_str.replace(" ", "")
            ):
                m = re.search(r"0x([0-9a-f]+)", insn.op_str)
                if m:
                    jt = int(m.group(1), 16)
                    raw = get(jt, 128) or b""
                    for k in range(32):
                        if 4 * k + 4 > len(raw):
                            break
                        t = struct.unpack_from("<I", raw, 4 * k)[0]
                        if not (va <= t < va + scan):
                            break
                        nxt.append(t)
            else:
                try:
                    nxt.append(int(insn.op_str, 16))
                except ValueError:
                    pass
                if insn.mnemonic != "jmp":
                    nxt.append(insn.address + insn.size)
        else:
            nxt.append(insn.address + insn.size)
        succ[insn.address] = nxt
    reach: set[int] = set()
    dq = deque([va])
    while dq:
        a = dq.popleft()
        if a in reach or not (va <= a < va + scan):
            continue
        reach.add(a)
        for t in succ.get(a, []):
            if t not in reach:
                dq.append(t)
    last = None
    for insn in insns:
        if insn.address not in reach:
            continue
        last = insn.address + insn.size
        if (
            insn.mnemonic == "jmp"
            and "dword" in insn.op_str
            and "*4" in insn.op_str.replace(" ", "")
        ):
            m = re.search(r"0x([0-9a-f]+)", insn.op_str)
            if m:
                jt = int(m.group(1), 16)
                raw = get(jt, 256) or b""
                nents = 0
                for k in range(64):
                    if 4 * k + 4 > len(raw):
                        break
                    t = struct.unpack_from("<I", raw, 4 * k)[0]
                    if not (va <= t < va + scan):
                        break
                    nents += 1
                if nents >= 2:
                    last = max(last, jt + 4 * nents)
    if last:
        data2 = get(va, last - va)
        insns2 = list(md.disasm(data2, va))
        for i, insn in enumerate(insns2):
            if insn.mnemonic != "ret":
                continue
            rest = insns2[i + 1 :]
            if rest and all(r.mnemonic in ("mov", "jmp", "nop") for r in rest):
                return insn.address + insn.size
    return last


def pick(
    n: int,
    remain_path: Path,
    *,
    allow_in_compare: bool = False,
    use_cand_end: bool = False,
) -> list[dict]:
    done = set(
        re.findall(
            r'\("([A-Za-z0-9_]+)",\s*0x',
            (ROOT / "tools/verify/compare_xbe_pe.py").read_text(),
        )
    )
    cands = json.loads(remain_path.read_text())
    # Prefer lowest Capstone % among remaining (then largest n).
    cands = sorted(cands, key=lambda x: (x.get("pct", 100), -x.get("n", 0)))
    pf = [
        x
        for x in cands
        if x.get("ported") is not True
        and (allow_in_compare or x["name"] not in done)
    ]
    xbe = Xbe.from_file(str(ROOT / "halo-patched/cachebeta.xbe"))
    pe = pefile.PE(str(ROOT / "build/halo"))
    md = Cs(CS_ARCH_X86, CS_MODE_32)
    picked: list[dict] = []
    skipped = 0
    seen: set[str] = set()
    for w in pf:
        if w["name"] in seen:
            continue
        # Always prefer CFG true_end. Registered compare ends are sometimes
        # short (missing shared epilogue) or long (bleed into the next symbol).
        te = true_end(xbe, md, w["va"])
        if not te and use_cand_end and "end" in w:
            te = int(w["end"])
        if not te:
            skipped += 1
            continue
        try:
            xb = xbe_bytes(xbe, w["va"], te)
            pb, pa = pe_fn_bytes(pe, w["name"])
            if len(pb) > len(xb) + 16:
                pins = list(md.disasm(pb, pa))
                for i, insn in enumerate(pins):
                    if insn.mnemonic != "ret":
                        continue
                    off = insn.address + insn.size - pa
                    if abs(off - len(xb)) > 32:
                        continue
                    j = i + 1
                    while j < len(pins) and pins[j].mnemonic == "nop":
                        j += 1
                    if (
                        j < len(pins)
                        and pins[j].mnemonic == "push"
                        and pins[j].op_str == "ebp"
                    ):
                        pb = pb[:off]
                        break
            om = mnemonics(xb, w["va"])
            cm = mnemonics(pb, pa)
            while om and om[-1] == "nop":
                om.pop()
            while cm and cm[-1] == "nop":
                cm.pop()
            min_ins = 1 if use_cand_end else 5
            if len(om) < min_ins:
                continue
            pct = SequenceMatcher(None, om, cm, autojunk=False).ratio() * 100
        except Exception:
            skipped += 1
            continue
        if pct >= 99.5:
            continue
        if (not use_cand_end) and len(om) < 40 and w.get("n", 0) > 100:
            skipped += 1
            continue
        raw = b""
        for sec in xbe.sections.values():
            s = sec.header.virtual_addr
            if s <= w["va"] < s + sec.header.virtual_size:
                raw = bytes(sec.data[w["va"] - s : te - s])
                break
        multi = any(
            insn.mnemonic == "jmp"
            and "dword" in insn.op_str
            and "*4" in insn.op_str.replace(" ", "")
            for insn in md.disasm(raw, w["va"])
        )
        domain = w.get("domain", "?")
        picked.append(
            {
                "name": w["name"],
                "va": w["va"],
                "end": te,
                "multi": multi,
                "n": len(om),
                "pct": pct,
                "defs": w.get("defs", []),
                "domain": domain,
            }
        )
        seen.add(w["name"])
        print(
            f"PICK {len(picked):2d} {w['name']:45s} n={len(om):4d} {pct:5.1f}% {domain}"
        )
        if len(picked) >= n:
            break
    print(f"picked {len(picked)} skipped={skipped}")
    return picked


def emit_gen(batch: int, items: list[dict]) -> Path:
    base = TEMPLATE.read_text()
    lines = ["TARGETS = ["]
    for t in items:
        lines.append(
            f'    ("{t["name"]}", {hex(t["va"])}, {hex(t["end"])}, {bool(t["multi"])}),'
        )
    lines.append("]")
    out = re.sub(r"TARGETS = \[.*?\n\]", "\n".join(lines), base, count=1, flags=re.S)
    out = re.sub(r"^BATCH = \d+", f"BATCH = {batch}", out, count=1, flags=re.M)
    out = out.replace(
        'json.dump(before, open("artifacts/batch56_before.json", "w"), indent=2)',
        f'json.dump(before, open("artifacts/batch{batch}_before.json", "w"), indent=2)',
    )
    path = Path(f"/tmp/gen_batch{batch}.py")
    path.write_text(out)
    json.dump(items, open(f"/tmp/batch{batch}_targets.json", "w"), indent=2)
    return path


def run_gen(batch: int) -> None:
    r = subprocess.run(
        ["python3", f"/tmp/gen_batch{batch}.py"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    Path(f"/tmp/batch{batch}_gen.log").write_text(r.stdout + r.stderr)
    print(r.stdout)
    if r.returncode != 0:
        print(r.stderr[-4000:])
        raise SystemExit(f"gen {batch} failed")


def docker_build() -> None:
    cmd = [
        "docker",
        "run",
        "--rm",
        "-u",
        f"{subprocess.check_output(['id', '-u']).decode().strip()}:{subprocess.check_output(['id', '-g']).decode().strip()}",
        "-v",
        f"{ROOT}:/work",
        "-w",
        "/work",
        "halo-re-build:latest",
        "bash",
        "-c",
        "cmake --build build --target halo --parallel 2>&1",
    ]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    Path("/tmp/capstone_batch_build.log").write_text(r.stdout + r.stderr)
    log = r.stdout + r.stderr
    if "Built target halo" not in log:
        print(log[-5000:])
        raise SystemExit("docker build failed")
    m = re.search(r"raw-cast count: (\d+)", log)
    if m:
        print("raw-cast", m.group(1))
    print("build OK")


def register_waves(batches: list[int], *, update_existing: bool = False) -> None:
    p = ROOT / "tools/verify/compare_xbe_pe.py"
    t = p.read_text()
    waves = []
    for num in batches:
        targets = re.findall(
            r'\("([^"]+)", (0x[0-9a-f]+), (0x[0-9a-f]+), (True|False)\)',
            Path(f"/tmp/gen_batch{num}.py").read_text(),
        )
        if f"gameplay wave {num}" in t:
            print(f"wave {num} already registered — skip insert")
            continue
        lines = [f"        # gameplay wave {num} (2026-07-26) — Capstone weaks"]
        for name, va, end, _multi in targets:
            # Update end if symbol already present
            if update_existing:
                pat = rf'(\("{re.escape(name)}",\s*{va},\s*)0x[0-9a-fA-F]+(\))'
                t2, nsub = re.subn(pat, rf"\g<1>{end}\2", t, count=1)
                if nsub:
                    t = t2
                    continue
            lines.append(f'        ("{name}", {va}, {end}),')
        if len(lines) > 1:
            waves.append("\n".join(lines))
    if waves:
        block = "\n".join(waves) + "\n"
        m = re.search(
            r"(# gameplay wave \d+[^\n]*\n(?:        \([^\n]+\),\n)+)    \]",
            t,
        )
        if not m:
            raise SystemExit("could not find insertion point in compare_xbe_pe.py")
        t = t[: m.end(1)] + block + "    ]" + t[m.end() :]
    p.write_text(t)
    print("registered waves", batches)


def score_batches(batches: list[int]) -> list[tuple[str, float]]:
    out = subprocess.check_output(
        ["python3", "tools/verify/compare_xbe_pe.py"],
        cwd=ROOT,
        text=True,
    )
    Path("/tmp/capstone_batch_score.txt").write_text(out)
    fail = []
    for num in batches:
        log = Path(f"/tmp/batch{num}_gen.log").read_text()
        bef = dict(re.findall(r"^(\w+): before ([\d.]+)%", log, re.M))
        for n, b in sorted(bef.items()):
            matches = re.findall(rf"^{re.escape(n)}:\s+([\d.]+)%", out, re.M)
            if not matches:
                fail.append((n, -1.0))
                print(f"  {n}: {b}% -> MISSING")
                continue
            a = float(matches[-1])
            print(f"  {n}: {b}% -> {a}%")
            if a < 99.9:
                fail.append((n, a))
    return fail


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--start", type=int, required=True)
    ap.add_argument("--count", type=int, default=8, help="number of batches of 12")
    ap.add_argument("--remain", type=Path, default=REMAIN)
    ap.add_argument(
        "--wave-weaks",
        action="store_true",
        help="re-port symbols already in compare_xbe_pe that still score <100%%",
    )
    ap.add_argument("--build", action="store_true")
    ap.add_argument("--register", action="store_true")
    ap.add_argument("--score", action="store_true")
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--pick-only", action="store_true")
    args = ap.parse_args()

    remain = args.remain
    if args.wave_weaks:
        remain = Path("/tmp/remain_wave_weaks.json")
        if not remain.exists():
            raise SystemExit("missing /tmp/remain_wave_weaks.json — regenerate first")

    total = args.count * PER_BATCH
    picked = pick(
        total,
        remain,
        allow_in_compare=args.wave_weaks,
        use_cand_end=args.wave_weaks,
    )
    if len(picked) < PER_BATCH:
        print(f"WARNING: only picked {len(picked)}")
    if args.pick_only:
        Path("/tmp/picked_capstone.json").write_text(json.dumps(picked, indent=2))
        return 0

    batches = []
    for i in range(0, len(picked), PER_BATCH):
        batch = args.start + i // PER_BATCH
        items = picked[i : i + PER_BATCH]
        if len(items) < 1:
            break
        emit_gen(batch, items)
        print(f"\n=== gen {batch} ({len(items)}) ===", flush=True)
        run_gen(batch)
        batches.append(batch)

    if args.build:
        docker_build()
    if args.register:
        register_waves(batches, update_existing=args.wave_weaks)
    if args.score:
        fail = score_batches(batches)
        if fail:
            print("FAILS", fail)
            return 1
        print("ALL 100%")
    if args.commit:
        files = subprocess.check_output(
            ["rg", "-l", f"batch {batches[0]}", "src/halo"],
            cwd=ROOT,
            text=True,
        ).split()
        # broaden: any batch in range
        all_files = set(files)
        for b in batches:
            try:
                more = subprocess.check_output(
                    ["rg", "-l", f"batch {b}", "src/halo"],
                    cwd=ROOT,
                    text=True,
                ).split()
                all_files.update(more)
            except subprocess.CalledProcessError:
                pass
        subprocess.check_call(
            ["git", "add", "tools/verify/compare_xbe_pe.py", *sorted(all_files)],
            cwd=ROOT,
        )
        # include template/runner if new
        subprocess.check_call(
            [
                "git",
                "add",
                "-f",
                "tools/capstone_batch/gen_naked_template.py",
                "tools/capstone_batch/run_batches.py",
                "artifacts/remain_kbnext.json",
            ],
            cwd=ROOT,
        )
        msg = (
            f"lift(track-a): port {len(picked)} ported:false Capstone weaks "
            f"(batches {batches[0]}-{batches[-1]})."
        )
        subprocess.check_call(["git", "commit", "-m", msg], cwd=ROOT)
        subprocess.check_call(["git", "push", "pastudan", "HEAD"], cwd=ROOT)
        print(subprocess.check_output(["git", "log", "-1", "--oneline"], cwd=ROOT, text=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
