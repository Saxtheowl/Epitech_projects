#!/usr/bin/env bash
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Smoke tests for detection on example apps (no docker required)
#

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
ZIP="${ROOT_DIR%/*}/Whanos/whanos_example_apps.zip"
OUT_DIR="$(dirname "$0")/examples"

if [ ! -f "$ZIP" ]; then
    echo "Examples zip not found: $ZIP" >&2
    exit 0
fi

rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

python3 - <<PY
import sys, zipfile, os
zip_path = os.path.abspath("$ZIP")
out_dir = os.path.abspath("$OUT_DIR")
with zipfile.ZipFile(zip_path) as z:
    z.extractall(out_dir)
print("Extracted to:", out_dir)
PY

BASE_DIR="$OUT_DIR"
SUBS=("$OUT_DIR"/*)
if [ "${#SUBS[@]}" -eq 1 ] && [ -d "${SUBS[0]}" ]; then
    BASE_DIR="${SUBS[0]}"
fi

echo "=== Detection results (in $BASE_DIR) ==="
for d in "$BASE_DIR"/*; do
    [ -d "$d" ] || continue
    printf "%-40s -> " "$(basename "$d")"
    python3 "$ROOT_DIR/src/whanos_detect.py" "$d" || true
done

echo "OK"
