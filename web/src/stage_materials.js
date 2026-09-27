// Strict interpreter for Halo texture-stage programs (stages.json).
// Phase 2: materials are driven only by machine-readable stage ops produced by
// tools/extract_stage_programs.py. When Track A recovers the real rasterizer
// bind functions, regenerate stages.json from that C — this file should not
// grow new per-class special cases.
import * as THREE from 'three';
import { haloTime } from './halo_materials.js';

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
    const u = (f) => `/${entry.cube}_f${f}.png`;
    const t = cubeLoader.load([u(0), u(1), u(4), u(5), u(3), u(2)]);
    t.colorSpace = THREE.SRGBColorSpace;
    texCache.set(entry.cube, t);
  }
  return texCache.get(entry.cube);
}

function v3(rgb, scale = 1) {
  return new THREE.Vector3(rgb[0] * scale, rgb[1] * scale, rgb[2] * scale);
}

const GAMMA = /* glsl */`
vec3 h2g(vec3 c) { return pow(max(c, 0.0), vec3(1.0 / 2.2)); }
vec3 g2l(vec3 c) { return pow(max(c, 0.0), vec3(2.2)); }
vec3 op_modulate(vec3 a, vec3 b) { return a * b; }
vec3 op_modulate2x(vec3 a, vec3 b) { return clamp(a * b * 2.0, 0.0, 1.0); }
vec3 op_add_signed2x(vec3 a, vec3 b) { return clamp(a + 2.0 * b - 1.0, 0.0, 1.0); }
`;

function combineFn(op) {
  if (op === 'modulate') return 'op_modulate';
  if (op === 'add_signed2x') return 'op_add_signed2x';
  return 'op_modulate2x';
}

function findStages(program, op) {
  return (program.stages || []).filter((s) => s.op === op);
}

function detailExprFromOp(op) {
  if (op === 'modulate') return 'b * d';
  if (op === 'add_signed2x') return 'clamp(b + 2.0 * d - 1.0, 0.0, 1.0)';
  return 'clamp(b * d * 2.0, 0.0, 1.0)';
}

/** Lower stage program → same GLSL path as halo_materials senv (proven). */
function interpretSenv(program, opts) {
  const samples = findStages(program, 'sample');
  const base = samples.find((s) => s.map === 'base');
  const detailP = samples.find((s) => s.map === 'detail_p' || s.map === 'detail');
  const detailS = samples.find((s) => s.map === 'detail_s');
  const micro = samples.find((s) => s.map === 'micro');
  const lerp = (program.stages || []).find((s) => s.op === 'lerp');
  const combines = (program.stages || []).filter((s) =>
    s.op === 'modulate' || s.op === 'modulate2x' || s.op === 'add_signed2x');
  const detailOp = combines[0]?.op || 'modulate2x';
  const microOp = combines[1]?.op || detailOp;
  const cube = findStages(program, 'cube_fresnel')[0];

  const mat = new THREE.MeshLambertMaterial({
    map: tex2d(base?.tex),
    lightMap: program.lightmap ? (opts.lightmap || null) : null,
    lightMapIntensity: 2.0,
  });
  if (program.alpha_tested && base?.tex?.alpha) {
    mat.alphaTest = 0.5;
    mat.side = THREE.DoubleSide;
  }

  const uniforms = {};
  const hasP = !!(detailP && tex2d(detailP.tex));
  const hasS = !!(detailS && tex2d(detailS.tex));
  const hasM = !!(micro && tex2d(micro.tex));
  const blended = !!lerp;

  if (hasP) {
    uniforms.tDetailP = { value: tex2d(detailP.tex) };
    uniforms.uDetailPScale = { value: detailP.scale || 1 };
  }
  if (hasS) {
    uniforms.tDetailS = { value: tex2d(detailS.tex) };
    uniforms.uDetailSScale = { value: detailS.scale || 1 };
  }
  if (hasM) {
    uniforms.tMicro = { value: tex2d(micro.tex) };
    uniforms.uMicroScale = { value: micro.scale || 1 };
  }
  if (cube?.cube && cubeTex(cube.cube)) {
    uniforms.tHaloCube = { value: cubeTex(cube.cube) };
    uniforms.uReflPerp = { value: v3(cube.perp_rgb || [1, 1, 1], cube.perp_b || 0) };
    uniforms.uReflPar = { value: v3(cube.par_rgb || [1, 1, 1], cube.par_b || 0) };
  }

  let detailCode = '';
  if (hasP && hasS) {
    detailCode = /* glsl */`
      vec3 hDp = texture2D( tDetailP, vMapUv * uDetailPScale ).rgb;
      vec3 hDs = texture2D( tDetailS, vMapUv * uDetailSScale ).rgb;
      vec3 d = h2g( ${blended ? 'mix( hDs, hDp, hBase.a )' : 'hDp * hDs'} );
      { vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExprFromOp(detailOp)} ); }`;
  } else if (hasP || hasS) {
    const t = hasP ? 'tDetailP, vMapUv * uDetailPScale' : 'tDetailS, vMapUv * uDetailSScale';
    detailCode = /* glsl */`
      vec3 d = h2g( texture2D( ${t} ).rgb );
      { vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExprFromOp(detailOp)} ); }`;
  }
  let microCode = '';
  if (hasM) {
    microCode = /* glsl */`
      { vec3 d = h2g( texture2D( tMicro, vMapUv * uMicroScale ).rgb );
        vec3 b = h2g( hBase.rgb ); hBase.rgb = g2l( ${detailExprFromOp(microOp)} ); }`;
  }

  const decls = [
    hasP ? 'uniform sampler2D tDetailP; uniform float uDetailPScale;' : '',
    hasS ? 'uniform sampler2D tDetailS; uniform float uDetailSScale;' : '',
    hasM ? 'uniform sampler2D tMicro; uniform float uMicroScale;' : '',
    uniforms.tHaloCube ? 'uniform samplerCube tHaloCube; uniform vec3 uReflPerp; uniform vec3 uReflPar;' : '',
  ].join('\n');

  mat.onBeforeCompile = (shader) => {
    Object.assign(shader.uniforms, uniforms);
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', `#include <common>\n${GAMMA}\n${decls}\nfloat hSpecMask = 1.0;`)
      .replace('#include <map_fragment>', /* glsl */`
        #ifdef USE_MAP
          vec4 hBase = texture2D( map, vMapUv );
          hSpecMask = hBase.a;
          ${detailCode}
          ${microCode}
          ${program.alpha_tested ? '' : 'hBase.a = 1.0;'}
          diffuseColor *= hBase;
        #endif`)
      .replace('#include <opaque_fragment>', uniforms.tHaloCube ? /* glsl */`
        {
          vec3 hV = normalize( vViewPosition );
          vec3 hR = inverseTransformDirection( reflect( -hV, normal ), viewMatrix );
          float hNdV = clamp( dot( normal, hV ), 0.0, 1.0 );
          outgoingLight += textureCube( tHaloCube, hR ).rgb
            * mix( uReflPar, uReflPerp, hNdV ) * hSpecMask;
        }
        #include <opaque_fragment>` : '#include <opaque_fragment>');
  };
  mat.customProgramCacheKey = () => `stage:senv:${opts.key}`;
  return mat;
}

function interpretSoso(program, opts) {
  const samples = findStages(program, 'sample');
  const base = samples.find((s) => s.map === 'base');
  const det = samples.find((s) => s.map === 'detail');
  const mat = new THREE.MeshLambertMaterial({ map: tex2d(base?.tex) });
  if (program.alpha_tested) mat.alphaTest = 0.5;
  if (program.two_sided || mat.alphaTest) mat.side = THREE.DoubleSide;

  const us = base?.u_scale || 1;
  const vs = base?.v_scale || 1;
  const uniforms = {};
  if (det) {
    uniforms.tDetail = { value: tex2d(det.tex) };
    uniforms.uDetailScale = {
      value: new THREE.Vector2(det.u_scale || 1, det.v_scale || 1),
    };
  }
  const combine = (program.stages || []).find((s) =>
    s.op === 'modulate' || s.op === 'modulate2x' || s.op === 'add_signed2x');
  const fn = combineFn(combine?.op || 'modulate2x');

  mat.onBeforeCompile = (shader) => {
    Object.assign(shader.uniforms, uniforms);
    shader.fragmentShader = shader.fragmentShader
      .replace('#include <common>', `#include <common>\n${GAMMA}\n`
        + (det ? 'uniform sampler2D tDetail; uniform vec2 uDetailScale;' : ''))
      .replace('#include <map_fragment>', /* glsl */`
        #ifdef USE_MAP
          vec2 hUv = vMapUv * vec2(${us.toFixed(4)}, ${vs.toFixed(4)});
          vec4 hBase = texture2D( map, hUv );
          ${det ? `{ vec3 a = h2g( hBase.rgb ); vec3 b = h2g( texture2D( tDetail, hUv * uDetailScale ).rgb );
            hBase.rgb = g2l( ${fn}( a, b ) ); }` : ''}
          diffuseColor *= hBase;
        #endif`);
  };
  mat.customProgramCacheKey = () => `stage:soso:${opts.key}`;
  return mat;
}

function slideVel(a) {
  if (!a || a.function === 'one' || a.function === 'zero' || !a.period) return 0;
  return (a.scale || 1) / a.period;
}

function interpretWater(program) {
  const samples = findStages(program, 'sample');
  const mask = samples.find((s) => s.map === 'mask');
  const rip = findStages(program, 'water_ripples')[0];
  const cube = findStages(program, 'cube_fresnel')[0];
  const ripples = [];
  for (let i = 0; i < 4; i++) {
    const r = (rip?.ripples || [])[i] || { angle: 0, velocity: 0, repeats: 1, contribution: 0 };
    ripples.push(new THREE.Vector4(
      Math.cos(r.angle) * r.velocity, Math.sin(r.angle) * r.velocity,
      r.repeats || 1, r.contribution));
  }
  const mat = new THREE.ShaderMaterial({
    uniforms: THREE.UniformsUtils.merge([THREE.UniformsLib.fog, {
      tMask: { value: tex2d(mask?.tex) },
      tRipple: { value: tex2d(rip?.ripple_tex, { srgb: false }) },
      tCube: { value: cubeTex(cube?.cube) },
      uPerp: { value: v3(cube?.perp_rgb || [1, 1, 1], cube?.perp_b || 0) },
      uPar: { value: v3(cube?.par_rgb || [1, 1, 1], cube?.par_b || 0) },
      uTime: haloTime,
      uRippleScale: { value: rip?.ripple_scale || 1 },
      uRipples: { value: ripples },
    }]),
    transparent: true,
    depthWrite: false,
    side: THREE.DoubleSide,
    fog: true,
    vertexShader: /* glsl */`
      varying vec2 vUv; varying vec3 vWorldPos; varying vec3 vWorldNormal;
      #include <common>
      #include <fog_pars_vertex>
      void main() {
        vUv = uv;
        vec4 wp = modelMatrix * vec4( position, 1.0 );
        vWorldPos = wp.xyz;
        vWorldNormal = normalize( mat3( modelMatrix ) * normal );
        gl_Position = projectionMatrix * viewMatrix * wp;
        #include <fog_vertex>
      }`,
    fragmentShader: /* glsl */`
      uniform sampler2D tMask; uniform sampler2D tRipple; uniform samplerCube tCube;
      uniform vec3 uPerp; uniform vec3 uPar; uniform float uTime; uniform float uRippleScale;
      uniform vec4 uRipples[4];
      varying vec2 vUv; varying vec3 vWorldPos; varying vec3 vWorldNormal;
      #include <common>
      #include <fog_pars_fragment>
      void main() {
        vec2 ruv = vUv * uRippleScale;
        vec2 acc = vec2( 0.0 );
        for ( int i = 0; i < 4; i++ ) {
          vec4 r = uRipples[ i ];
          acc += ( texture2D( tRipple, ruv * r.z + r.xy * uTime ).rg - 0.5 ) * r.w;
        }
        float hDist = length( cameraPosition - vWorldPos );
        vec3 N = normalize( vWorldNormal + vec3( acc.x, 0.0, acc.y )
          * 1.4 / ( 1.0 + hDist * 0.004 ) );
        vec3 V = normalize( cameraPosition - vWorldPos );
        vec3 R = reflect( -V, N );
        float ndv = clamp( dot( N, V ), 0.0, 1.0 );
        vec3 refl = textureCube( tCube, R ).rgb;
        vec4 mask = texture2D( tMask, vUv );
        ${cube?.mask ? 'refl *= mask.a;' : ''}
        vec3 col = refl * mix( uPar, uPerp, ndv ) + vec3( 0.01, 0.045, 0.05 );
        gl_FragColor = vec4( col, mix( 0.97, 0.55, ndv ) );
        #include <fog_fragment>
        #include <colorspace_fragment>
      }`,
  });
  return mat;
}

const CHICAGO_BLEND = {
  add: THREE.AdditiveBlending,
  multiply: THREE.MultiplyBlending,
  double_multiply: THREE.MultiplyBlending,
  subtract: THREE.SubtractiveBlending,
};

function interpretChicago(program) {
  const samples = findStages(program, 'sample');
  if (!samples.length) return null;
  const uniforms = { uTime: haloTime };
  let decls = 'uniform float uTime;';
  let uvCode = '';
  let stageCode = '';
  samples.forEach((m, i) => {
    uniforms[`tMap${i}`] = { value: tex2d(m.tex) };
    decls += `\nuniform sampler2D tMap${i};`;
    const vu = slideVel(m.u_anim);
    const vv = slideVel(m.v_anim);
    uvCode += `vec2 uv${i} = vUv * vec2(${(m.u_scale || 1).toFixed(4)}, ${(m.v_scale || 1).toFixed(4)})`
      + ` + vec2(${(m.u_offset || 0).toFixed(4)}, ${(m.v_offset || 0).toFixed(4)})`
      + ((vu || vv) ? ` + uTime * vec2(${vu.toFixed(6)}, ${vv.toFixed(6)})` : '')
      + ';\n';
  });
  const combines = (program.stages || []).filter((s) => s.op === 'chicago_combine' || s.op === 'mov');
  stageCode += 'vec4 cur = texture2D( tMap0, uv0 );\n';
  combines.forEach((c) => {
    if (c.op === 'mov') return;
    const idx = parseInt(String(c.b).replace('r', ''), 10);
    if (c.fn === 'multiply') stageCode += `cur *= texture2D( tMap${idx}, uv${idx} );\n`;
    else if (c.fn === 'blend_current_alpha') {
      stageCode += `{ vec4 m = texture2D( tMap${idx}, uv${idx} ); cur = mix( cur, m, cur.a ); }\n`;
    } else if (c.fn === 'current') { /* noop */ }
    else stageCode += `{ vec4 m = texture2D( tMap${idx}, uv${idx} ); cur.rgb = mix( cur.rgb, m.rgb, m.a ); cur.a *= m.a; }\n`;
  });

  const mat = new THREE.ShaderMaterial({
    uniforms: THREE.UniformsUtils.merge([THREE.UniformsLib.fog, uniforms]),
    transparent: true,
    depthWrite: false,
    side: program.two_sided ? THREE.DoubleSide : THREE.FrontSide,
    fog: true,
    vertexShader: /* glsl */`
      varying vec2 vUv;
      #include <common>
      #include <fog_pars_vertex>
      void main() {
        vUv = uv;
        gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
        #include <fog_vertex>
      }`,
    fragmentShader: /* glsl */`
      ${decls}
      varying vec2 vUv;
      #include <common>
      #include <fog_pars_fragment>
      void main() {
        ${uvCode}
        ${stageCode}
        gl_FragColor = cur;
        #include <fog_fragment>
        #include <colorspace_fragment>
      }`,
  });
  mat.blending = CHICAGO_BLEND[program.blend] || THREE.NormalBlending;
  if (program.alpha_tested) {
    mat.transparent = false;
    mat.depthWrite = true;
    mat.alphaTest = 0.5;
  }
  return mat;
}

export async function loadStagePrograms(url) {
  const res = await fetch(url);
  if (!res.ok) throw new Error(`stages.json ${res.status}`);
  const data = await res.json();
  return { programs: data.programs || data, cache: new Map() };
}

export function createStageMaterial(reg, shaderPath, opts = {}) {
  if (!reg || !shaderPath) return null;
  const program = reg.programs[shaderPath];
  if (!program) return null;
  const key = shaderPath + (opts.lightmap ? `|${opts.lightmap.uuid}` : '');
  if (reg.cache.has(key)) return reg.cache.get(key);

  let mat = null;
  const o = { key, lightmap: opts.lightmap };
  if (program.class === 'shader_environment') mat = interpretSenv(program, o);
  else if (program.class === 'shader_model') mat = interpretSoso(program, o);
  else if (program.class === 'shader_transparent_water') mat = interpretWater(program);
  else if (program.class?.startsWith('shader_transparent_chicago')) mat = interpretChicago(program);
  else if (program.class?.startsWith('shader_transparent_')) {
    // Phase 4 stubs: glass/plasma/meter/generic — base sample only
    const base = findStages(program, 'sample')[0];
    mat = new THREE.MeshLambertMaterial({
      map: tex2d(base?.tex),
      transparent: true,
      depthWrite: false,
      opacity: 0.85,
    });
  }

  if (mat) mat.userData = { shader: shaderPath, shader_class: program.class, stage: true };
  reg.cache.set(key, mat);
  return mat;
}
