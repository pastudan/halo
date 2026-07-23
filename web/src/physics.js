// Loader/bridge for the WASM Halo physics core (physics/halo_phys.c).
// The core runs in native Halo space (z-up, world units, 30Hz ticks);
// this module converts to/from three.js space (y-up, meters).

const W = 3.048; // meters per world unit

export const TICK = 1 / 30;

// three.js (x,y,z) -> halo (x, -z, y) / W
const toHalo = (v) => [v.x / W, -v.z / W, v.y / W];
// halo (hx,hy,hz) -> three (hx, hz, -hy) * W
const toThree = (h) => ({ x: h[0] * W, y: h[2] * W, z: -h[1] * W });

export async function loadPhysics() {
  const [wasmBuf, cbspA, cbspB, constants] = await Promise.all([
    fetch('/halo_phys.wasm').then((r) => r.arrayBuffer()),
    fetch('/b30a.cbsp').then((r) => r.arrayBuffer()),
    fetch('/b30b.cbsp').then((r) => r.arrayBuffer()),
    fetch('/constants.json').then((r) => r.json()),
  ]);
  const { instance } = await WebAssembly.instantiate(wasmBuf, {});
  const ex = instance.exports;

  const arena = ex.phys_arena();
  let off = 0;
  for (const [slot, buf] of [[0, cbspA], [1, cbspB]]) {
    new Uint8Array(ex.memory.buffer).set(new Uint8Array(buf), arena + off);
    if (!ex.phys_load_bsp(slot, off, buf.byteLength)) {
      throw new Error(`cbsp load failed for slot ${slot}`);
    }
    off += buf.byteLength + 64;
  }

  ex.phys_set_constants(
    constants.run_forward, constants.run_backward, constants.run_sideways,
    constants.run_acceleration, constants.airborne_acceleration,
    constants.jump_velocity, constants.gravity,
    constants.standing_camera_height, constants.standing_collision_height,
    constants.collision_radius,
  );

  return {
    constants,
    // pos: three.js Vector3 of the EYE point (matches viewer camera)
    spawn(pos) {
      const eyeUp = constants.standing_camera_height; // wu
      const h = toHalo(pos);
      ex.phys_spawn(h[0], h[1], h[2] - eyeUp);
    },
    // fwd/side in -1..1, yaw = three.js camera yaw, jump bool
    input(fwd, side, yaw, jump) {
      const fx = -Math.sin(yaw);
      const fy = Math.cos(yaw);
      ex.phys_input(fwd, side, fx, fy, jump ? 1 : 0);
    },
    tick() { ex.phys_tick(); },
    // returns { eye: {x,y,z} in three.js meters, grounded }
    state() {
      const p = ex.phys_state();
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
      return ex.phys_ray(o[0], o[1], o[2], d[0], d[1], d[2]);
    },
  };
}
