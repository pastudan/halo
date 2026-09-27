import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import {
  computeBoundsTree, disposeBoundsTree, acceleratedRaycast,
} from 'three-mesh-bvh';
import { loadPhysics, TICK } from './physics.js';
import { loadHaloShaders, createHaloMaterial, haloTime } from './halo_materials.js';
import { loadStagePrograms, createStageMaterial } from './stage_materials.js';

THREE.BufferGeometry.prototype.computeBoundsTree = computeBoundsTree;
THREE.BufferGeometry.prototype.disposeBoundsTree = disposeBoundsTree;
THREE.Mesh.prototype.raycast = acceleratedRaycast;

// ---------------------------------------------------------------- scene
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setPixelRatio(Math.min(devicePixelRatio, 2));
renderer.setSize(innerWidth, innerHeight);
document.getElementById('app').appendChild(renderer.domElement);

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x87b5d8);
scene.fog = new THREE.Fog(0x87b5d8, 400, 2200);

const camera = new THREE.PerspectiveCamera(75, innerWidth / innerHeight, 0.1, 4000);
scene.add(camera);

// Lighting layers: BSP lightmapped surfaces have the sun baked into their
// lightmaps, so the dynamic sun/sky lights live on layer 1 and only affect
// scenery and other non-lightmapped materials. A dim ambient (layer 0,
// everything) keeps unlit interiors readable.
const sun = new THREE.DirectionalLight(0xfff2dd, 2.4);
sun.position.set(0.4, 1, 0.35).multiplyScalar(100);
sun.layers.set(1);
scene.add(sun);
const sky = new THREE.HemisphereLight(0xbfd8ff, 0x5a4a33, 1.1);
sky.layers.set(1);
scene.add(sky);
scene.add(new THREE.AmbientLight(0xdfe8ff, 0.35));

// flashlight: spotlight riding the camera, toggled with Q. Wide-ish cone with
// a soft penumbra approximates Halo's flashlight gel falloff.
const flashlight = new THREE.SpotLight(0xfff3d8, 60, 40, Math.PI / 5.5, 0.85, 1.15);
flashlight.position.set(0.2, -0.25, 0);
flashlight.visible = false;
camera.add(flashlight);
camera.add(flashlight.target);
flashlight.target.position.set(0, 0, -10);

// (the BSP itself contains the sea surface — shader_transparent_water)

// ---------------------------------------------------------------- level loading
const loader = new GLTFLoader();
const colliders = [];
const loadingEl = document.getElementById('loading');
let pending = 2;

const texLoader = new THREE.TextureLoader();
const lmCache = new Map();
function lightmapTex(url) {
  if (!lmCache.has(url)) {
    const t = texLoader.load(url);
    t.flipY = false; // match glTF UV convention (UV2 comes from the GLB)
    t.channel = 1;
    t.colorSpace = THREE.SRGBColorSpace;
    lmCache.set(url, t);
  }
  return lmCache.get(url);
}

// Halo framebuffer blend function -> three.js blending
function applyBlend(mat, blend) {
  if (blend === 'add' || blend === 'alpha_multiply_add' || blend === 'component_max') {
    mat.blending = THREE.AdditiveBlending;
  } else if (blend === 'multiply' || blend === 'double_multiply' || blend === 'component_min') {
    mat.blending = THREE.MultiplyBlending;
  } else if (blend === 'subtract') {
    mat.blending = THREE.SubtractiveBlending;
  }
  if (mat.blending !== THREE.NormalBlending) {
    mat.transparent = true;
    mat.depthWrite = false;
  }
}

// Halo BSP lighting is fully baked: diffuse map x lightmap. Lambert (rather
// than unlit Basic) so the ambient fill and flashlight can also contribute.
// When the shader registry is available, the tag-faithful GLSL materials
// (detail maps, cube reflections, ripple water, animated chicago stages)
// take priority; the code below is the fallback.
function upgradeMaterial(mesh) {
  const src = mesh.material;
  const extras = src.userData || {};
  const cls = extras.shader_class || '';

  if (extras.shader) {
    const lm = extras.lightmap && mesh.geometry.attributes.uv1
      ? lightmapTex(`/${extras.lightmap}`) : null;
    // Prefer strict stage-program interpreter (Phase 2); fall back to tag GLSL.
    if (stageReg) {
      const sm = createStageMaterial(stageReg, extras.shader, { lightmap: lm });
      if (sm) {
        sm.userData = { ...extras, ...sm.userData };
        return sm;
      }
    }
    if (haloReg) {
      const hm = createHaloMaterial(haloReg, extras.shader, { lightmap: lm });
      if (hm) {
        hm.userData = { ...extras, ...hm.userData };
        return hm;
      }
    }
  }

  if (cls === 'shader_transparent_water') {
    const water = new THREE.MeshStandardMaterial({
      color: 0x2a6a88, transparent: true, opacity: 0.7,
      roughness: 0.12, metalness: 0.1, depthWrite: false,
    });
    water.userData = extras;
    return water;
  }
  // shoreline foam: animated in the real game; render as a faint additive overlay
  if ((extras.shader || '').endsWith('\\waves')) {
    const foam = new THREE.MeshBasicMaterial({
      map: src.map || null, transparent: true, opacity: 0.25,
      blending: THREE.AdditiveBlending, depthWrite: false,
    });
    foam.userData = extras;
    return foam;
  }
  if (src.map) src.map.anisotropy = 8;

  let mat = src;
  if (extras.lightmap && mesh.geometry.attributes.uv1) {
    mat = new THREE.MeshLambertMaterial({
      map: src.map || null,
      color: src.map ? 0xffffff : 0x888888,
      lightMap: lightmapTex(`/${extras.lightmap}`),
      lightMapIntensity: 2.0, // Halo applies lightmaps with D3D MODULATE2X
      transparent: src.transparent,
      side: src.side,
    });
    mat.userData = extras;
  }
  if (extras.blend) applyBlend(mat, extras.blend);
  return mat;
}

function loadBsp(url) {
  loader.load(url, (gltf) => {
    gltf.scene.traverse((obj) => {
      if (obj.isMesh) {
        obj.material = upgradeMaterial(obj);
        // materials without a baked lightmap keep getting the dynamic sun/sky
        if (!obj.material.lightMap) obj.layers.enable(1);
        obj.geometry.computeBoundsTree();
        colliders.push(obj);
      }
    });
    scene.add(gltf.scene);
    if (--pending === 0) loadingEl.textContent = '';
  }, (ev) => {
    if (ev.total) loadingEl.textContent = `loading… ${Math.round((ev.loaded / ev.total) * 100)}%`;
  });
}
// shader registries first, so materials can be built tag-faithfully
let haloReg = null;
let stageReg = null;
Promise.all([
  loadHaloShaders('/shaders.json').catch((e) => {
    console.warn('halo shaders unavailable:', e); return null;
  }),
  loadStagePrograms('/stages.json').catch((e) => {
    console.warn('stage programs unavailable:', e); return null;
  }),
]).then(([hReg, sReg]) => {
  haloReg = hReg;
  stageReg = sReg;
  loadBsp('/b30a.glb');
  loadBsp('/b30b.glb');
  loadScenery();
});

// ---------------------------------------------------------------- scenery
// trees/rocks/props from the scenario tag, instanced per model part
function sceneryMaterial(src) {
  const extras = src.userData || {};
  if (extras.shader) {
    if (stageReg) {
      const sm = createStageMaterial(stageReg, extras.shader);
      if (sm) return sm;
    }
    if (haloReg) {
      const hm = createHaloMaterial(haloReg, extras.shader);
      if (hm) return hm;
    }
  }
  const mat = new THREE.MeshLambertMaterial({
    map: src.map || null,
    color: src.map ? 0xffffff : 0x999999,
    alphaTest: src.alphaTest || 0,
    side: src.alphaTest ? THREE.DoubleSide : src.side,
    transparent: src.transparent,
  });
  mat.userData = extras;
  if (extras.blend) applyBlend(mat, extras.blend);
  return mat;
}

function loadScenery() {
  Promise.all([
    loader.loadAsync('/scenery.glb'),
    fetch('/scenery.json').then((r) => r.json()),
  ]).then(([gltf, info]) => {
  const byModel = new Map();
  for (const inst of info.instances) {
    if (!byModel.has(inst.m)) byModel.set(inst.m, []);
    byModel.get(inst.m).push(inst);
  }
  const mtx = new THREE.Matrix4();
  const pos = new THREE.Vector3();
  const quat = new THREE.Quaternion();
  const eul = new THREE.Euler();
  const one = new THREE.Vector3(1, 1, 1);
  let count = 0;
  for (const [mi, list] of byModel) {
    const tpl = gltf.scene.getObjectByName(`pal_${mi}`);
    if (!tpl) continue;
    tpl.traverse((obj) => {
      if (!obj.isMesh) return;
      const imesh = new THREE.InstancedMesh(
        obj.geometry, sceneryMaterial(obj.material), list.length);
      list.forEach((inst, i) => {
        pos.set(inst.p[0], inst.p[1], inst.p[2]);
        // halo yaw/pitch/roll (z-up) -> three: yaw about Y, pitch about -Z, roll about X
        eul.set(inst.r[2], inst.r[0], -inst.r[1], 'YZX');
        quat.setFromEuler(eul);
        mtx.compose(pos, quat, one);
        imesh.setMatrixAt(i, mtx);
      });
      imesh.layers.enable(1); // receive the dynamic sun/sky
      scene.add(imesh);
    });
    count += list.length;
  }
  console.log(`scenery: ${count} instances of ${byModel.size} models`);
  }).catch((e) => console.warn('scenery not loaded:', e));
}

// ---------------------------------------------------------------- player
const EYE = 1.7;           // meters
const WALK = 7, SPRINT = 14, FLY = 30;
const GRAV = 22, JUMP = 8;

const player = {
  pos: new THREE.Vector3(-203, 10, -55),
  vel: new THREE.Vector3(),
  yaw: 0, pitch: 0,
  fly: false, grounded: false,
};

// ---- WASM engine (Track B); ?jsphys falls back to the JS stub
// Fly mode is debug-only (?fly or ?debug); Phase 3 removes it as escape hatch.
const qs = new URLSearchParams(location.search);
const useJsPhys = qs.has('jsphys');
const flyAllowed = qs.has('fly') || qs.has('debug');
let phys = null;
let physNeedsSpawn = true;
let physAccum = 0;
const physPrev = { eye: new THREE.Vector3(), grounded: false };
const physCur = { eye: new THREE.Vector3(), grounded: false };
if (!useJsPhys) {
  loadPhysics().then((p) => { phys = p; window.__phys = p; console.log('physics core:', p.label, p.url); })
    .catch((e) => console.error('WASM engine failed, using JS fallback:', e));
}

window.__player = player; // debug / scripted navigation
window.__scene = scene;
window.__colliders = colliders;
window.__THREE = THREE;

function movePlayerTo(pos) {
  player.pos.copy(pos);
  player.vel.set(0, 0, 0);
  physNeedsSpawn = true;
}

fetch('/spawn.json').then((r) => r.json()).then((spawns) => {
  if (spawns.length) {
    const s = spawns[0];
    movePlayerTo(new THREE.Vector3(s.position[0], s.position[1] + EYE + 0.5, s.position[2]));
    player.yaw = s.facing_rad - Math.PI / 2; // halo yaw (rad, 0=+X, z-up) -> three yaw about Y
  }
});

// teleport spots: 1 = beach spawn, 2 = map room interior (b30b)
const TELEPORTS = {
  Digit1: () => fetch('/spawn.json').then((r) => r.json()).then((s) => {
    player.fly = false;
    movePlayerTo(new THREE.Vector3(s[0].position[0], s[0].position[1] + EYE + 0.5, s[0].position[2]));
  }),
  Digit2: () => {
    // map room interior (b30b): a spot on the walkable floor
    player.fly = false;
    movePlayerTo(new THREE.Vector3(17, 6.5 + EYE + 0.5, 62));
  },
};

// ---------------------------------------------------------------- input
const keys = new Set();
addEventListener('keydown', (e) => {
  keys.add(e.code);
  if (e.code === 'KeyF' && flyAllowed) player.fly = !player.fly;
  else if (e.code === 'KeyF' && !flyAllowed) {
    console.info('Fly mode disabled (add ?fly to URL for debug noclip)');
  }
  if (e.code === 'KeyQ') flashlight.visible = !flashlight.visible;
  if (TELEPORTS[e.code]) TELEPORTS[e.code]();
});
addEventListener('keyup', (e) => keys.delete(e.code));

const overlay = document.getElementById('overlay');
overlay.addEventListener('click', () => renderer.domElement.requestPointerLock());
document.addEventListener('pointerlockchange', () => {
  overlay.style.display = document.pointerLockElement ? 'none' : 'flex';
});
addEventListener('mousemove', (e) => {
  if (!document.pointerLockElement) return;
  player.yaw -= e.movementX * 0.0022;
  player.pitch = THREE.MathUtils.clamp(player.pitch - e.movementY * 0.0022, -1.55, 1.55);
});

function gamepad() {
  const gp = navigator.getGamepads?.()[0];
  if (!gp) return { mx: 0, mz: 0, lx: 0, ly: 0, jump: false, sprint: false };
  const dz = (v) => (Math.abs(v) > 0.15 ? v : 0);
  return {
    mx: dz(gp.axes[0]), mz: dz(gp.axes[1]),
    lx: dz(gp.axes[2]), ly: dz(gp.axes[3]),
    jump: gp.buttons[0]?.pressed, sprint: gp.buttons[10]?.pressed,
  };
}

// ---------------------------------------------------------------- movement
const ray = new THREE.Raycaster();
ray.far = 300;
const DOWN = new THREE.Vector3(0, -1, 0);

function groundHeight(pos) {
  ray.set(new THREE.Vector3(pos.x, pos.y + 1, pos.z), DOWN);
  const hits = ray.intersectObjects(colliders, false);
  return hits.length ? hits[0].point.y : -Infinity;
}

const hud = document.getElementById('hud');
const clock = new THREE.Clock();

function tick() {
  requestAnimationFrame(tick);
  const dt = Math.min(clock.getDelta(), 0.05);
  haloTime.value = clock.elapsedTime; // drives water ripples / chicago stages
  const gp = gamepad();

  player.yaw -= gp.lx * 2.4 * dt;
  player.pitch = THREE.MathUtils.clamp(player.pitch - gp.ly * 1.8 * dt, -1.55, 1.55);

  const fwd = new THREE.Vector3(-Math.sin(player.yaw), 0, -Math.cos(player.yaw));
  const right = new THREE.Vector3(-fwd.z, 0, fwd.x);
  const move = new THREE.Vector3();
  if (keys.has('KeyW')) move.add(fwd);
  if (keys.has('KeyS')) move.sub(fwd);
  if (keys.has('KeyD')) move.add(right);
  if (keys.has('KeyA')) move.sub(right);
  move.addScaledVector(fwd, -gp.mz).addScaledVector(right, gp.mx);
  if (move.lengthSq() > 1) move.normalize();

  const sprint = keys.has('ShiftLeft') || keys.has('ShiftRight') || gp.sprint;

  if (player.fly) {
    const spd = FLY * (sprint ? 3 : 1);
    player.pos.addScaledVector(move, spd * dt);
    if (keys.has('Space') || gp.jump) player.pos.y += spd * dt;
    if (keys.has('KeyC')) player.pos.y -= spd * dt;
    player.vel.set(0, 0, 0);
    physNeedsSpawn = true; // re-sync wasm when we land back into walk mode
  } else if (phys) {
    // ---- faithful Halo movement: fixed 30Hz WASM ticks, interpolated render
    if (physNeedsSpawn) {
      phys.spawn(player.pos);
      const st = phys.state();
      physPrev.eye.set(st.eye.x, st.eye.y, st.eye.z);
      physCur.eye.copy(physPrev.eye);
      physAccum = 0;
      physNeedsSpawn = false;
    }
    const fwdIn = (keys.has('KeyW') ? 1 : 0) - (keys.has('KeyS') ? 1 : 0) - gp.mz;
    const sideIn = (keys.has('KeyD') ? 1 : 0) - (keys.has('KeyA') ? 1 : 0) + gp.mx;
    const jump = keys.has('Space') || gp.jump;
    phys.input(fwdIn, sideIn, player.yaw, jump);

    physAccum += dt;
    while (physAccum >= TICK) {
      phys.tick();
      physAccum -= TICK;
      physPrev.eye.copy(physCur.eye);
      physPrev.grounded = physCur.grounded;
      const st = phys.state();
      physCur.eye.set(st.eye.x, st.eye.y, st.eye.z);
      physCur.grounded = st.grounded;
    }
    player.pos.lerpVectors(physPrev.eye, physCur.eye, physAccum / TICK);
    player.grounded = physCur.grounded;
  } else {
    const spd = sprint ? SPRINT : WALK;
    player.pos.x += move.x * spd * dt;
    player.pos.z += move.z * spd * dt;

    player.vel.y -= GRAV * dt;
    player.pos.y += player.vel.y * dt;

    const feet = player.pos.y - EYE;
    let gh = groundHeight(new THREE.Vector3(player.pos.x, feet + 0.5, player.pos.z));
    gh = Math.max(gh, -1.2); // sea floor: wade waist-deep instead of sinking
    if (feet <= gh + 0.02) {
      player.pos.y = gh + EYE;
      player.vel.y = 0;
      player.grounded = true;
      if (keys.has('Space') || gp.jump) player.vel.y = JUMP;
    } else {
      player.grounded = false;
    }
    // fell into the ocean / void -> respawn-ish clamp
    if (player.pos.y < -60) { player.pos.y = 60; player.vel.set(0, 0, 0); }
  }

  camera.position.copy(player.pos);
  camera.rotation.set(0, 0, 0);
  camera.rotateY(player.yaw);
  camera.rotateX(player.pitch);

  hud.textContent =
    `${player.fly ? 'FLY' : player.grounded ? 'WALK' : 'AIR '} ` +
    `[${player.fly ? 'js' : phys ? phys.label : 'js'}]  ` +
    `x ${player.pos.x.toFixed(1)}  y ${player.pos.y.toFixed(1)}  z ${player.pos.z.toFixed(1)}`;

  renderer.render(scene, camera);
}
tick();

addEventListener('resize', () => {
  camera.aspect = innerWidth / innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(innerWidth, innerHeight);
});
