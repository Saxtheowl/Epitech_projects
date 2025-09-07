#!/usr/bin/env bash
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Build examples with whanos_build (no push)
#

set -euo pipefail
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
EX="${ROOT_DIR}/examples"

echo "== Detect and build examples =="
for ex in c javascript python befunge; do
  d="$EX/$ex"
  [ -d "$d" ] || continue
  echo "-- $ex --"
  python3 "$ROOT_DIR/src/whanos_detect.py" "$d"
  python3 "$ROOT_DIR/src/whanos_build.py" "$d" "example-$ex:latest" || true
  printf 'deployment:\n  replicas: 1\n  ports: [80]\n' > "$d/whanos.yml"
  python3 "$ROOT_DIR/src/whanos_k8s_gen.py" "$d/whanos.yml" "example-$ex:latest" --name "${ex}-app" | sed -n '1,30p'
done
echo OK

