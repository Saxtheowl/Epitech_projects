#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/count_island"
MAP="$DIR/map.txt"

ok=0; ko=0

if [ ! -x "$BIN" ]; then echo "[KO] binary missing"; exit 1; fi

out="$($BIN "$MAP")"
st=$?
if [ $st -ne 0 ]; then echo "[KO] program exit $st"; ko=$((ko+1)); else echo "[OK] program exit 0"; ok=$((ok+1)); fi

if printf "%s" "$out" | rg -q "X"; then echo "[KO] still contains X"; ko=$((ko+1)); else echo "[OK] no X"; ok=$((ok+1)); fi
if printf "%s" "$out" | rg -q "[0-9]"; then echo "[OK] has digits"; ok=$((ok+1)); else echo "[KO] no digits"; ko=$((ko+1)); fi

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
