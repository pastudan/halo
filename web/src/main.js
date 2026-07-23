import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import {
  computeBoundsTree, disposeBoundsTree, acceleratedRaycast,
} from 'three-mesh-bvh';

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

const sun = new THREE.DirectionalLight(0xfff2dd, 2.4);
sun.position.set(0.4, 1, 0.35).multiplyScalar(100);
scene.add(sun);
scene.add(new THREE.HemisphereLight(0xbfd8ff, 0x5a4a33, 1.1));

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

// Halo BSP lighting is fully baked: diffuse map x lightmap, no dynamic lights.
function upgradeMaterial(mesh) {
  const src = mesh.material;
  const extras = src.userData || {};
  const cls = extras.shader_class || '';

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
    mat = new THREE.MeshBasicMaterial({
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
loadBsp('/b30a.glb');
loadBsp('/b30b.glb');

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

window.__player = player; // debug / scripted navigation
window.__scene = scene;
window.__colliders = colliders;
window.__THREE = THREE;

fetch('/spawn.json').then((r) => r.json()).then((spawns) => {
  if (spawns.length) {
    const s = spawns[0];
    player.pos.set(s.position[0], s.position[1] + EYE + 0.5, s.position[2]);
    player.yaw = s.facing_rad - Math.PI / 2; // halo yaw (rad, 0=+X, z-up) -> three yaw about Y
  }
});

// teleport spots: 1 = beach spawn, 2 = map room interior (b30b)
const TELEPORTS = {
  Digit1: () => fetch('/spawn.json').then((r) => r.json()).then((s) => {
    player.pos.set(s[0].position[0], s[0].position[1] + EYE + 0.5, s[0].position[2]);
    player.vel.set(0, 0, 0);
  }),
  Digit2: () => {
    // drop into the b30b interior from its bounding box center
    const b30b = colliders.filter((c) => c.parent?.name === 'b30b' || c.name === 'b30b');
    const box = new THREE.Box3();
    (b30b.length ? b30b : colliders).forEach((c) => box.expandByObject(c));
    const ctr = box.getCenter(new THREE.Vector3());
    player.pos.set(ctr.x, box.max.y - 2, ctr.z);
    player.vel.set(0, 0, 0);
    player.fly = true;
  },
};

// ---------------------------------------------------------------- input
const keys = new Set();
addEventListener('keydown', (e) => {
  keys.add(e.code);
  if (e.code === 'KeyF') player.fly = !player.fly;
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
    `${player.fly ? 'FLY' : player.grounded ? 'WALK' : 'AIR '}  ` +
    `x ${player.pos.x.toFixed(1)}  y ${player.pos.y.toFixed(1)}  z ${player.pos.z.toFixed(1)}`;

  renderer.render(scene, camera);
}
tick();

addEventListener('resize', () => {
  camera.aspect = innerWidth / innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(innerWidth, innerHeight);
});
