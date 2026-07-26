"""Docker TU compile + decl.h regen helpers for Track A Unicorn lifters."""
from __future__ import annotations

import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
UID, GID = os.getuid(), os.getgid()
IMAGE = "halo-re-build:latest"


def regen_decl_h() -> bool:
    r = subprocess.run(
        [
            "docker",
            "run",
            "--rm",
            "-u",
            f"{UID}:{GID}",
            "-v",
            f"{ROOT}:/work",
            "-w",
            "/work",
            IMAGE,
            "bash",
            "-c",
            "cmake --build build --target import_libs_target --parallel 1 >/tmp/imp.log 2>&1; tail -5 /tmp/imp.log",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    ok = (ROOT / "build" / "generated" / "decl.h").exists() and r.returncode == 0
    if not ok:
        print("regen_decl_h FAIL", (r.stderr or r.stdout)[-400:], flush=True)
    return ok


def docker_compile(src: str) -> bool:
    src = src.replace("\\", "/")
    if src.startswith("src/halo/"):
        src = src[len("src/halo/") :]
    cmake_obj = ROOT / "build" / "CMakeFiles" / "halo.dir" / "src" / "halo" / f"{src}.obj"
    cmake_obj.parent.mkdir(parents=True, exist_ok=True)
    (ROOT / "build" / "equivalence").mkdir(parents=True, exist_ok=True)
    base = Path(src).name
    cmd = f"""
set -e
clang -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-parameter \
  -Wno-error -target i386-pc-win32 -march=pentium3 -mno-sse -nostdlib -ffreestanding \
  -fno-builtin -fno-exceptions -mstack-probe-size=65536 \
  -I/work/src -I/work/third_party/xbox -I/work/build/generated \
  -include /work/src/common.h \
  -c /work/src/halo/{src} -o /work/build/equivalence/{base}.obj
mkdir -p $(dirname /work/build/CMakeFiles/halo.dir/src/halo/{src}.obj)
cp /work/build/equivalence/{base}.obj /work/build/CMakeFiles/halo.dir/src/halo/{src}.obj
"""
    r = subprocess.run(
        [
            "docker",
            "run",
            "--rm",
            "-u",
            f"{UID}:{GID}",
            "-v",
            f"{ROOT}:/work",
            "-w",
            "/work",
            IMAGE,
            "bash",
            "-c",
            cmd,
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        print("compile FAIL", src, (r.stderr or r.stdout)[-600:], flush=True)
        return False
    return True
