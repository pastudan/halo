// Loader/bridge for the portable engine WASM (engine/) — Track B.
// Falls back to legacy /halo_phys.wasm if engine.wasm is missing.
// The core runs in native Halo space (z-up, world units, 30Hz ticks);
// this module converts to/from three.js space (y-up, meters).

const W = 3.048; // meters per world unit

export const TICK = 1 / 30;

const toHalo = (v) => [v.x / W, -v.z / W, v.y / W];
const toThree = (h) => ({ x: h[0] * W, y: h[2] * W, z: -h[1] * W });

async function fetchWasm() {
  for (const url of ['/engine.wasm', '/halo_phys.wasm']) {
    const r = await fetch(url);
    if (r.ok) return { buf: await r.arrayBuffer(), url };
  }
  throw new Error('no engine.wasm or halo_phys.wasm');
}

export async function loadPhysics() {
  const [{ buf, url }, cbspA, cbspB, constants] = await Promise.all([
    fetchWasm(),
    fetch('/b30a.cbsp').then((r) => r.arrayBuffer()),
    fetch('/b30b.cbsp').then((r) => r.arrayBuffer()),
    fetch('/constants.json').then((r) => r.json()),
  ]);
  const { instance } = await WebAssembly.instantiate(buf, {});
  const ex = instance.exports;

  const arenaFn = ex.engine_arena || ex.phys_arena;
  const loadBsp = ex.engine_load_bsp || ex.phys_load_bsp;
  const setConst = ex.engine_set_constants || ex.phys_set_constants;
  const fnSpawn = ex.engine_spawn || ex.phys_spawn;
  const fnInput = ex.engine_input || ex.phys_input;
  const fnTick = ex.engine_tick || ex.phys_tick;
  const fnState = ex.engine_state || ex.phys_state;
  const fnRay = ex.engine_ray || ex.phys_ray;
  const coreId = ex.engine_core_id ? ex.engine_core_id() : 1.0;

  const arena = arenaFn();
  let off = 0;
  for (const [slot, bufBsp] of [[0, cbspA], [1, cbspB]]) {
    new Uint8Array(ex.memory.buffer).set(new Uint8Array(bufBsp), arena + off);
    if (!loadBsp(slot, off, bufBsp.byteLength)) {
      throw new Error(`cbsp load failed for slot ${slot}`);
    }
    off += bufBsp.byteLength + 64;
  }

  setConst(
    constants.run_forward, constants.run_backward, constants.run_sideways,
    constants.run_acceleration, constants.airborne_acceleration,
    constants.jump_velocity, constants.gravity,
    constants.standing_camera_height, constants.standing_collision_height,
    constants.collision_radius,
  );

  const label = coreId >= 2 ? 'wasm-engine' : 'wasm';

  return {
    constants,
    url,
    label,
    coreId,
    spawn(pos) {
      const eyeUp = constants.standing_camera_height;
      const h = toHalo(pos);
      fnSpawn(h[0], h[1], h[2] - eyeUp);
    },
    input(fwd, side, yaw, jump) {
      const fx = -Math.sin(yaw);
      const fy = Math.cos(yaw);
      fnInput(fwd, side, fx, fy, jump ? 1 : 0);
    },
    tick() { fnTick(); },
    state() {
      const p = fnState();
      const f = new Float32Array(ex.memory.buffer, p, 10);
      const feet = toThree([f[0], f[1], f[2]]);
      const eyeH = f[7] * W;
      return {
        eye: { x: feet.x, y: feet.y + eyeH, z: feet.z },
        grounded: f[6] > 0.5,
        velZ: f[5],
      };
    },
    raycast(origin, dir) {
      const o = toHalo(origin);
      const d = [dir.x / W, -dir.z / W, dir.y / W];
      return fnRay(o[0], o[1], o[2], d[0], d[1], d[2]);
    },
  };
}
