#!/bin/sh
# Legacy entry point — physics now lives in engine/ (Track B).
exec "$(dirname "$0")/../engine/build.sh"
