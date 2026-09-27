# Track A status

Local tree: `halo-re/` → fork [pastudan/halo](https://github.com/pastudan/halo) (from [stianeklund/halo](https://github.com/stianeklund/halo)).

Active branch: [`track-a-collision-bsp`](https://github.com/pastudan/halo/tree/track-a-collision-bsp) · PR: https://github.com/pastudan/halo/pull/1

**Handoff:** [TRACK_A_HANDOFF.md](./TRACK_A_HANDOFF.md) — Unicorn proof grind; Capstone drained.

## Honest completion

| Scope | Status | Notes |
|-------|--------|-------|
| KB coverage (unset) | **~0** | Nearly every symbol is `ported:true` or `ported:false` |
| `ported:true` (proof) | **~5111 / ~8026 (~63.7%)** | Unicorn hard-leaf + sibling-resolve; emit-prove drained |
| `ported:false` drafts | **~2915** | Hand-lift + Unicorn; knowledge.py rejects prose/`static` decls |
| Capstone queues | **drained** | batches 162–402 |
| Local Unicorn verify | **primary proof path** | `xbe_to_coff` + `unicorn_diff` + `BIPED_SIBLING_RESOLVE` |
| Official VC71 / xemu | **blocked** | no local `CL.Exe` / BIOS |

**Not 100% yet.** Keep naked→C + Unicorn until false≈0.

### Proof tools

`tools/equivalence/xbe_to_coff.py`, `unicorn_diff.py`, `scripts/unicorn_c_campaign.py` (defaults `BIPED_SIBLING_RESOLVE=1`), `scripts/lift_emit_prove.py`, domain lifters under `scripts/`

## Hard rules

- Unicorn / VC71 / runtime (or prior stian true) before `ported:true`
- Never commit XBE/maps/ISOs
- Raw-cast ≤ **359**
