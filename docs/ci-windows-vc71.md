# Windows CI + VC71 (Track A)

## GitHub-hosted (`windows-latest`)

Workflow: `.github/workflows/windows-build.yml`

- Installs LLVM + Ninja via Chocolatey
- Builds `halo` with `toolchains/llvm.cmake` (same as Ubuntu/macOS)
- Does **not** patch an XBE (no game binary in CI)
- Does **not** run VC71 scoring (RXDK is not redistributable)

## Official VC71 scores (self-hosted)

VC71 needs Microsoft Xbox Development Kit `CL.Exe` (MSVC 7.1), typically at:

`C:\Program Files (x86)\RXDK\xbox\bin\vc71\CL.Exe`

1. On a Windows machine with RXDK installed, [add a self-hosted runner](https://docs.github.com/en/actions/hosting-your-own-runners) to this repo.
2. Label it: `self-hosted`, `Windows`, `rxdk`.
3. Place delinked reference objects under `delinked/` (Ghidra export).
4. Actions → **Windows Build** → Run workflow → enable **run_vc71**.

Or locally:

```bash
python tools/verify/vc71_verify.py --function FUN_00148eb0
python tools/lift_pipeline.py --target 0x148eb0 --no-metadata-update --verify-policy auto
```

## XBE / assets

Never commit `cachebeta.xbe` or `halo-patched/maps`. Supply them locally for `patched_xbe` / xemu.
