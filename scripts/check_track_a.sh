#!/bin/sh
# Report Track A (stianeklund/halo clone in halo-re/ + XBE) readiness.
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
HR="$ROOT/halo-re"
XBE="$HR/halo-patched/cachebeta.xbe"
PIN_MD5="c7869590a1c64ad034e49a5ee0c02465"
EXPECT_REMOTE="stianeklund/halo"

echo "== Track A readiness =="
if [ ! -d "$HR" ]; then
  echo "FAIL: halo-re/ missing (clone https://github.com/stianeklund/halo → halo-re/)"
  exit 1
fi
echo "ok: halo-re present"

if [ -d "$HR/.git" ]; then
  remote=$(git -C "$HR" remote get-url origin 2>/dev/null || true)
  case "$remote" in
    *"$EXPECT_REMOTE"*) echo "ok: origin is $EXPECT_REMOTE" ;;
    "") echo "note: no git remote (ok if vendored tree)" ;;
    *) echo "WARN: origin is $remote (expected $EXPECT_REMOTE)" ;;
  esac
  rev=$(git -C "$HR" rev-parse --short HEAD 2>/dev/null || true)
  [ -n "$rev" ] && echo "ok: HEAD $rev"
fi

if [ ! -f "$XBE" ]; then
  echo "BLOCKED: $XBE not found"
  echo "  Supply Xbox Halo CE 01.10.12.2276 as cachebeta.xbe (MD5 $PIN_MD5)"
  echo "  See docs/UPSTREAM.md and docs/ENGINE.md"
else
  if command -v md5 >/dev/null 2>&1; then
    got=$(md5 -q "$XBE")
  else
    got=$(md5sum "$XBE" | awk '{print $1}')
  fi
  if [ "$got" = "$PIN_MD5" ]; then
    echo "ok: cachebeta.xbe MD5 matches pin"
  else
    echo "FAIL: cachebeta.xbe MD5 $got (expected $PIN_MD5)"
    exit 1
  fi
fi

if [ -f "$HR/halo-patched/default.xbe" ]; then
  echo "ok: patched default.xbe present"
else
  echo "note: no patched default.xbe yet (Docker build in halo-re/)"
fi

if [ -x /opt/homebrew/opt/llvm/bin/clang ] || [ -x /usr/local/opt/llvm/bin/clang ]; then
  echo "ok: Homebrew LLVM clang found"
elif command -v docker >/dev/null 2>&1; then
  echo "note: use Docker for Track A build (see docs/UPSTREAM.md)"
else
  echo "note: install LLVM clang or Docker to build Track A"
fi

echo "Track B WASM: $([ -f "$ROOT/web/public/engine.wasm" ] && echo ok || echo MISSING — run engine/build.sh)"
exit 0
