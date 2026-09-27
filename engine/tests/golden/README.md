# Golden fixtures (Track A → Track B)

Capture from xemu (patched XBE) or from the browser debug hooks, then compare
against `engine.wasm` outputs.

## Layout

```
fixtures/
  rays.jsonl     # {o:[x,y,z], d:[dx,dy,dz], t: expected}  Halo wu, z-up
  steps.jsonl    # {spawn, inputs[], eye_end} biped walk sequences
```

## Capture (browser)

With the viewer running and `window.__phys` loaded:

```js
// ray: origin + dir in three.js meters → convert via physics.js conventions
const t = window.__phys.raycast(origin, dir);
```

## Run

```bash
.venv/bin/python engine/tests/run_golden.py
```

Empty fixtures directory = skip (exit 0). Populate after Track A is available.
