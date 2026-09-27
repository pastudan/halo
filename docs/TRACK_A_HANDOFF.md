# Track A handoff — Unicorn proof grind (~62.3%)

**Updated:** 2026-07-26  
Prefer **Grok 4.5** (`cursor-grok-4.5-high-fast`) for subagents.

Parent: [TRACK_A.md](./TRACK_A.md) · [DECOMP_PROGRESS.md](./DECOMP_PROGRESS.md) · PR: https://github.com/pastudan/halo/pull/1

## Honest status

| Queue | State |
|-------|--------|
| Capstone PE-export weaks | **0** |
| `ported:true` | **~5000 / ~8026 (~62.3%)** |
| `ported:false` | **~3026** |
| Raw-cast | **359** |
| **100% proven** | **Not done** |

### Remaining false (approx)

| Domain | ~Count | Notes |
|--------|------:|-------|
| xdk | 698 | Unicorn synthetic oracles weak; needs VC71/Ghidra |
| rasterizer | ~315 | Hard / GPU |
| ai | ~240 | Active; sibling-resolve + AI emitters |
| bitmaps | 231 | |
| interface | ~200 | Prefer non-crashing TUs; watch decl drift |
| libcmt | 203 | Skip / VC71 |
| other gameplay | ~rest | Wrapper + leaf grind |

### Critical: `qsort` in `src/common.h`

Keep `void __cdecl qsort(void *, unsigned, unsigned, int (__cdecl *)(const void *, const void *));` in `src/common.h`. Without it, freestanding Docker TU compiles mis-type naked CRT bindings as `double(double)` and break `ai/encounters.c` and friends. Do not drop it in drive-by commits.

## Proof path (macOS, no RXDK)

```bash
python3 tools/analysis/knowledge.py --gen-header build/generated/decl.h
python3 tools/equivalence/xbe_to_coff.py --addr 0x...
# Prefer --no-stub-arg-trace for assert wrappers (string immediates):
BIPED_SIBLING_RESOLVE=1 python3 tools/equivalence/unicorn_diff.py NAME \
  --allow-stubs --no-stub-arg-trace --seeds 100 -q
# campaigns:
python3 scripts/unicorn_c_campaign.py --gameplay-only --timeout 20
python3 scripts/lift_unicode_strings.py
python3 scripts/lift_emit_prove.py --prefer text/unicode --max-size 200
python3 scripts/lift_ai_campaign.py --allow-wrappers
```

Deps: `pip install unicorn z3-solver`. Docker image `halo-re-build:latest` for TU compile before Unicorn.

## Hard rules

- Unicorn/VC71/runtime (or prior stian true) before `ported:true`
- Never flip naked asm as true
- Never commit XBE; raw-cast ≤359
- Push: `git push pastudan HEAD:track-a-collision-bsp`
- kb `decl` must be a real prototype (knowledge.py rejects prose/`static`)

## Next

1. Hand-lift remaining 80–400B naked gameplay leaves (weapons/sound/network/ai/ui)
2. Expand assert emitters for unicode/assert+`_wcslen` clusters still naked
3. XDK/libcmt when VC71/RXDK available
4. Fix readable-C Unicorn fails (float-tol / real-callees / body bugs)
