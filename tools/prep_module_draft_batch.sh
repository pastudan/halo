#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OBJECT="$1"
cd "$ROOT"
SLUG="$(python3 -c "import re,sys; print(re.sub(r'[^a-z0-9]+','_',sys.argv[1].replace('.obj','').lower()).strip('_'))" "$OBJECT")"
SRC="$(python3 -c "
import json,sys
kb=json.load(open('kb.json'))
o=next(x for x in kb['objects'] if x['name']==sys.argv[1])
print('src/halo/'+o.get('source',''))
" "$OBJECT")"
MARKER="/* --- ${OBJECT} batch drafts"
python3 tools/gen_module_draft_batch.py --object "$OBJECT"
if ! grep -qF "$MARKER" "$SRC" 2>/dev/null; then
  cat "tools/${SLUG}_batch_impl.c" >> "$SRC"
fi
python3 tools/apply_module_draft_batch.py --object "$OBJECT"
python3 tools/audit/extract_reg_args.py --apply --batch "$OBJECT" 2>/dev/null || true
