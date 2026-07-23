// Faithful-ish reimplementation of Halo 1's fixed-function shader classes as
// three.js materials, driven directly by tag parameters (shaders.json from
// tools/extract_shaders.py).
//
// - shader_environment: base map + primary/secondary detail (blended by base
//   alpha for "blended" types) + micro detail, combined in gamma space like
//   D3D texture stages (MODULATE2X et al); cube-map reflection with
//   parallel/perpendicular fresnel tints masked by base alpha. Built on
//   MeshLambertMaterial so lightmaps, ambient and the flashlight still apply.
// - shader_model: base * detail (function/scales from tag), alpha test,
//   instancing-compatible (standard chunks preserved).
// - shader_transparent_water: 4 scrolling ripple layers perturbing a cube-map
//   reflection, parallel/perpendicular tints, base-mask modulation.
// - shader_transparent_chicago(_extended): up to 4 animated texture stages
//   with D3D combine functions and framebuffer blend.
import * as THREE from 'three';

export const haloTime = { value: 0 };  // shared uniform, advanced by the app

const texLoader = new THREE.TextureLoader();
const cubeLoader = new THREE.CubeTextureLoader();
const texCache = new Map();

function tex2d(entry, { srgb = true } = {}) {
  if (!entry || !entry.tex) return null;
  const key = entry.tex + (srgb ? ':s' : ':l');
  if (!texCache.has(key)) {
    const t = texLoader.load(`/${entry.tex}`);
    t.wrapS = t.wrapT = THREE.RepeatWrapping;
    t.colorSpace = srgb ? THREE.SRGBColorSpace : THREE.NoColorSpace;
    t.anisotropy = 8;
    texCache.set(key, t);
  }
  return texCache.get(key);
}

function cubeTex(entry) {
  if (!entry || !entry.cube) return null;
  if (!texCache.has(entry.cube)) {
    // halo/D3D faces are +x -x +y -y +z -z in halo's z-up world;
    // three.js wants [px nx py ny pz nz] y-up: halo +z -> +y, halo +y -> -z
    const u = (f) => `/${entry.cube}_f${f}.png`;
    const t = cubeLoader.load([u(0), u(1), u(4), u(5), u(3), u(2)]);
    t.colorSpace = THREE.SRGBColorSpace;
    texCache.set(entry.cube, t);
  }
  return texCache.get(entry.cube);
}

function v3(rgbArr, scale = 1) {
  return new THREE.Vector3(rgbArr[0] * scale, rgbArr[1] * scale, rgbArr[2] * scale);
}

// D3D texture stages combined in gamma space; three samples are linear.
const GAMMA_HELPERS = /* glsl */`
vec3 h2g(vec3 c) { return pow(max(c, 0.0), vec3(1.0 / 2.2)); }
vec3 g2l(vec3 c) { return pow(max(c, 0.0), vec3(2.2)); }
`;

// detail combine expression in gamma space (b = base gamma, d = detail gamma)
function detailExpr(fn) {
  if (fn === 'multiply') return 'b * d';
  if (fn === 'double_biased_add') return 'clamp(b + 2.0 * d - 1.0, 0.0, 1.0)';
  return 'clamp(b * d * 2.0, 0.0, 1.0)';  // double_biased_multiply (default)
}

// ---------------------------------------------------------------------------
// shader_environment
// ---------------------------------------------------------------------------
function senvMaterial(def, opts) {
  const mat = new THREE.MeshLambertMaterial({
    map: tex2d(def.base),
    lightMap: opts.lightmap || null,
    lightMapIntensity: 2.0,
  });
  if (def.alpha_tested && def.base && def.base.alpha) {
    mat.alphaTest = 0.5;
    mat.side = THREE.DoubleSide;
  }

  const uniforms = {};
  const blended = def.type !== 'normal';
  const hasP = !!tex2d(def.primary_detail);
  const hasS = !!tex2d(def.secondary_detail);
  const hasM = !!tex2d(def.micro_detail);
  if (hasP) {
    uniforms.tDetailP = { value: tex2d(def.primary_detail) };
    uniforms.uDetailPScale = { value: def.primary_detail_scale || 1 };
  }
  if (hasS) {
    uniforms.tDetailS = { value: tex2d(def.secondary_detail) };
    uniforms.uDetailSScale = { value: def.secondary_detail_scale || 1 };
  }
  if (hasM) {
    uniforms.tMicro = { value: tex2d(def.micro_detail) };
    uniforms.uMicroScale = { value: def.micro_detail_scale || 1 };
  }
  const refl = def.reflection && cubeTex(def.reflection.cube) ? def.reflection : null;
  if (refl) {
    uniforms.tHaloCube = { value: cubeTex(refl.cube) };
    uniforms.uReflPerp = { value: v3(refl.perpendicular_tint, refl.perpendicular_brightness) };
    uniforms.uReflPar = { value: v3(refl.parallel_tint, refl.parallel_brightness) };
  }

  // detail sample expression (with primary/secondary blending by base alpha)
  let detailCode = '';
  if (hasP && hasS) {
    detailCode = /* glsl */`
      vec3 hDp = texture2D( tDetailP, vMapUv * uDetailPScale ).rgb;
      vec3 hDs = texture2D( tDetailS, vMapUv * uDetailSScale ).rgb;
      vec3 d = h2g( ${blended ? 'mix( hDs, hDp, hBase.a )' : 'hDp * hDs'} );
      { vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExpr(def.detail_function)} ); }`;
  } else if (hasP || hasS) {
    const t = hasP ? 'tDetailP, vMapUv * uDetailPScale' : 'tDetailS, vMapUv * uDetailSScale';
    detailCode = /* glsl */`
      vec3 d = h2g( texture2D( ${t} ).rgb );
      { vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExpr(def.detail_function)} ); }`;
  }
  let microCode = '';
  if (hasM) {
    microCode = /* glsl */`
      { vec3 d = h2g( texture2D( tMicro, vMapUv * uMicroScale ).rgb );
        vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExpr(def.micro_detail_function)} ); }`;
  }

  const decls = [
    hasP ? 'uniform sampler2D tDetailP; uniform float uDetailPScale;' : '',
    hasS ? 'uniform sampler2D tDetailS; uniform float uDetailSScale;' : '',
    hasM ? 'uniform sampler2D tMicro; uniform float uMicroScale;' : '',
    refl ? 'uniform samplerCube tHaloCube; uniform vec3 uReflPerp; uniform vec3 uReflPar;' : '',
  ].join('\n');

  mat.onBeforeCompile = (shader) => {
    Object.assign(shader.uniforms, uniforms);
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', `#include <common>\n${GAMMA_HELPERS}\n${decls}\nfloat hSpecMask = 1.0;`)
      .replace('#include <map_fragment>', /* glsl */`
        #ifdef USE_MAP
          vec4 hBase = texture2D( map, vMapUv );
          hSpecMask = hBase.a;
          ${detailCode}
          ${microCode}
          ${def.alpha_tested ? '' : 'hBase.a = 1.0;'}
          diffuseColor *= hBase;
        #endif`)
      .replace('#include <opaque_fragment>', /* glsl */`
        ${refl ? `
        {
          vec3 hV = normalize( vViewPosition );
          vec3 hR = inverseTransformDirection( reflect( -hV, normal ), viewMatrix );
          float hNdV = clamp( dot( normal, hV ), 0.0, 1.0 );
          outgoingLight += textureCube( tHaloCube, hR ).rgb
            * mix( uReflPar, uReflPerp, hNdV ) * hSpecMask;
        }` : ''}
        #include <opaque_fragment>`);
  };
  mat.customProgramCacheKey = () => `senv:${opts.key}`;
  return mat;
}

// ---------------------------------------------------------------------------
// shader_model (scenery; must keep standard chunks for InstancedMesh)
// ---------------------------------------------------------------------------
function sosoMaterial(def, opts) {
  const mat = new THREE.MeshLambertMaterial({ map: tex2d(def.base) });
  if (def.alpha_tested && def.base && def.base.alpha) mat.alphaTest = 0.5;
  if (def.two_sided || mat.alphaTest) mat.side = THREE.DoubleSide;

  const det = tex2d(def.detail);
  const uniforms = {};
  const baseScale = new THREE.Vector2(def.u_scale || 1, def.v_scale || 1);
  if (det) {
    uniforms.tDetail = { value: det };
    uniforms.uDetailScale = {
      value: new THREE.Vector2(def.detail_scale || 1,
        def.detail_v_scale || def.detail_scale || 1),
    };
  }
  mat.onBeforeCompile = (shader) => {
    Object.assign(shader.uniforms, uniforms);
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', `#include <common>\n${GAMMA_HELPERS}\n`
        + (det ? 'uniform sampler2D tDetail; uniform vec2 uDetailScale;' : ''))
      .replace('#include <map_fragment>', /* glsl */`
        #ifdef USE_MAP
          vec2 hUv = vMapUv * vec2(${baseScale.x.toFixed(4)}, ${baseScale.y.toFixed(4)});
          vec4 hBase = texture2D( map, hUv );
          ${det ? `
          { vec3 d = h2g( texture2D( tDetail, hUv * uDetailScale ).rgb );
            vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExpr(def.detail_function)} ); }` : ''}
          diffuseColor *= hBase;
        #endif`);
  };
  mat.customProgramCacheKey = () => `soso:${opts.key}`;
  return mat;
}

// ---------------------------------------------------------------------------
// shader_transparent_water
// ---------------------------------------------------------------------------
const WATER_VERT = /* glsl */`
varying vec2 vUv;
varying vec3 vWorldPos;
varying vec3 vWorldNormal;
#include <common>
#include <fog_pars_vertex>
void main() {
  vUv = uv;
  vec4 wp = modelMatrix * vec4( position, 1.0 );
  vWorldPos = wp.xyz;
  vWorldNormal = normalize( mat3( modelMatrix ) * normal );
  vec4 mvPosition = viewMatrix * wp;
  gl_Position = projectionMatrix * mvPosition;
  #include <fog_vertex>
}`;

const WATER_FRAG = /* glsl */`
uniform sampler2D tMask;
uniform sampler2D tRipple;
uniform samplerCube tCube;
uniform vec3 uPerp;
uniform vec3 uPar;
uniform float uTime;
uniform float uRippleScale;
uniform vec4 uRipples[4];   // (dir.x * vel, dir.y * vel, repeats, contribution)
varying vec2 vUv;
varying vec3 vWorldPos;
varying vec3 vWorldNormal;
#include <common>
#include <fog_pars_fragment>
void main() {
  vec2 ruv = vUv * uRippleScale;
  vec2 acc = vec2( 0.0 );
  for ( int i = 0; i < 4; i++ ) {
    vec4 r = uRipples[ i ];
    vec2 p = texture2D( tRipple, ruv * r.z + r.xy * uTime ).rg - 0.5;
    acc += p * r.w;
  }
  // emulate the tag's ripple mipmap fade: distant water gets calmer normals
  float hDist = length( cameraPosition - vWorldPos );
  vec3 N = normalize( vWorldNormal + vec3( acc.x, 0.0, acc.y )
    * 1.4 / ( 1.0 + hDist * 0.004 ) );
  vec3 V = normalize( cameraPosition - vWorldPos );
  vec3 R = reflect( -V, N );
  float ndv = clamp( dot( N, V ), 0.0, 1.0 );
  vec3 refl = textureCube( tCube, R ).rgb;
  vec4 mask = texture2D( tMask, vUv );
  vec3 tint = mix( uPar, uPerp, ndv );
  #ifdef MASK_MODULATES
    refl *= mask.a;
  #endif
  vec3 col = refl * tint + vec3( 0.01, 0.045, 0.05 );
  float alpha = mix( 0.97, 0.55, ndv );
  gl_FragColor = vec4( col, alpha );
  #include <fog_fragment>
  #include <colorspace_fragment>
}`;

function waterMaterial(def, opts) {
  const rip = [];
  for (let i = 0; i < 4; i++) {
    const r = (def.ripples || [])[i] || { angle: 0, velocity: 0, repeats: 1, contribution: 0 };
    rip.push(new THREE.Vector4(
      Math.cos(r.angle) * r.velocity, Math.sin(r.angle) * r.velocity,
      r.repeats || 1, r.contribution));
  }
  const mat = new THREE.ShaderMaterial({
    uniforms: THREE.UniformsUtils.merge([THREE.UniformsLib.fog, {}]),
    vertexShader: WATER_VERT,
    fragmentShader: WATER_FRAG,
    transparent: true,
    depthWrite: false,
    side: THREE.DoubleSide,
    fog: true,
  });
  Object.assign(mat.uniforms, {
    tMask: { value: tex2d(def.base) },
    tRipple: { value: tex2d(def.ripple_maps, { srgb: false }) },
    tCube: { value: cubeTex(def.reflection_cube) },
    uPerp: { value: v3(def.perpendicular_tint, def.perpendicular_brightness) },
    uPar: { value: v3(def.parallel_tint, def.parallel_brightness) },
    uTime: haloTime,
    uRippleScale: { value: def.ripple_scale || 1 },
    uRipples: { value: rip },
  });
  if (def.alpha_modulates_reflection) mat.defines.MASK_MODULATES = '';
  mat.customProgramCacheKey = () => `swat:${opts.key}`;
  return mat;
}

// ---------------------------------------------------------------------------
// shader_transparent_chicago / _extended
// ---------------------------------------------------------------------------
const CHICAGO_BLEND = {
  add: THREE.AdditiveBlending,
  component_max: THREE.AdditiveBlending,
  alpha_multiply_add: THREE.AdditiveBlending,
  multiply: THREE.MultiplyBlending,
  double_multiply: THREE.MultiplyBlending,
  component_min: THREE.MultiplyBlending,
  subtract: THREE.SubtractiveBlending,
};

function slideVel(a) {
  // "slide" animation: one full uv cycle every `period` seconds
  if (!a || a.function === 'one' || a.function === 'zero' || !a.period) return 0;
  return (a.scale || 1) / a.period;
}

function chicagoStage(i, fn, alphaFn) {
  const s = `texture2D( tMap${i}, uv${i} )`;
  if (i === 0) return `vec4 cur = ${s};`;
  if (fn === 'current') return '';  // passthrough
  if (fn === 'multiply') return `cur *= ${s};`;
  if (fn === 'double_multiply') return `{ vec4 m = ${s}; cur.rgb = g2l( clamp( h2g( cur.rgb ) * h2g( m.rgb ) * 2.0, 0.0, 1.0 ) ); cur.a *= m.a; }`;
  if (fn === 'add') return `cur += ${s};`;
  if (fn === 'blend_current_alpha') return `{ vec4 m = ${s}; cur = mix( cur, m, cur.a ); }`;
  if (fn === 'blend_next_map_alpha') return `{ vec4 m = ${s}; cur = mix( cur, m, m.a ); }`;
  return `{ vec4 m = ${s}; cur.rgb = mix( cur.rgb, m.rgb, m.a ); cur.a *= m.a; }`;
}

function chicagoMaterial(def, opts) {
  const maps = (def.maps || []).filter((m) => m.map && m.map.tex).slice(0, 4);
  if (!maps.length) return null;

  const uniforms = { uTime: haloTime };
  let decls = 'uniform float uTime;';
  let uvCode = '';
  let stageCode = '';
  maps.forEach((m, i) => {
    uniforms[`tMap${i}`] = { value: tex2d(m.map) };
    decls += `\nuniform sampler2D tMap${i};`;
    const su = m.u_scale || 1;
    const sv = m.v_scale || 1;
    const vu = slideVel(m.u_anim);
    const vv = slideVel(m.v_anim);
    uvCode += `vec2 uv${i} = vUv * vec2(${su.toFixed(4)}, ${sv.toFixed(4)})`
      + ` + vec2(${(m.u_offset || 0).toFixed(4)}, ${(m.v_offset || 0).toFixed(4)})`
      + ((vu || vv) ? ` + uTime * vec2(${vu.toFixed(6)}, ${vv.toFixed(6)})` : '')
      + ';\n';
    stageCode += chicagoStage(i, m.color_function, m.alpha_function) + '\n';
  });

  const mat = new THREE.ShaderMaterial({
    uniforms: THREE.UniformsUtils.merge([THREE.UniformsLib.fog, {}]),
    vertexShader: /* glsl */`
      varying vec2 vUv;
      #include <common>
      #include <fog_pars_vertex>
      void main() {
        vUv = uv;
        vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );
        gl_Position = projectionMatrix * mvPosition;
        #include <fog_vertex>
      }`,
    fragmentShader: /* glsl */`
      ${decls}
      varying vec2 vUv;
      #include <common>
      #include <fog_pars_fragment>
      ${GAMMA_HELPERS}
      void main() {
        ${uvCode}
        ${stageCode}
        gl_FragColor = cur;
        #include <fog_fragment>
        #include <colorspace_fragment>
      }`,
    transparent: true,
    depthWrite: false,
    side: def.two_sided ? THREE.DoubleSide : THREE.FrontSide,
    fog: true,
  });
  Object.assign(mat.uniforms, uniforms);
  mat.blending = CHICAGO_BLEND[def.blend] || THREE.NormalBlending;
  if (def.alpha_tested) {
    mat.transparent = false;
    mat.depthWrite = true;
    mat.alphaTest = 0.5;
  }
  mat.customProgramCacheKey = () => `schi:${opts.key}`;
  return mat;
}

// ---------------------------------------------------------------------------
// registry
// ---------------------------------------------------------------------------
export async function loadHaloShaders(url) {
  const res = await fetch(url);
  if (!res.ok) throw new Error(`shaders.json ${res.status}`);
  return { defs: await res.json(), cache: new Map() };
}

/** Build (and cache) a material for `shaderPath`; null if not supported. */
export function createHaloMaterial(reg, shaderPath, opts = {}) {
  if (!reg || !shaderPath) return null;
  const def = reg.defs[shaderPath];
  if (!def) return null;
  const key = shaderPath + (opts.lightmap ? `|${opts.lightmap.uuid}` : '');
  if (reg.cache.has(key)) return reg.cache.get(key);

  let mat = null;
  const o = { key, lightmap: opts.lightmap };
  if (def.class === 'shader_environment') mat = senvMaterial(def, o);
  else if (def.class === 'shader_model') mat = sosoMaterial(def, o);
  else if (def.class === 'shader_transparent_water') mat = waterMaterial(def, o);
  else if (def.class.startsWith('shader_transparent_chicago')) mat = chicagoMaterial(def, o);
  // glass/meter/plasma/generic: fall through to the caller's default handling

  if (mat) mat.userData = { shader: shaderPath, shader_class: def.class };
  reg.cache.set(key, mat);
  return mat;
}
