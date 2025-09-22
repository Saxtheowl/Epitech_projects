#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
PROJECTS=(
  "Rush1/rush-1-1"
  "Rush1/rush-1-2"
  "Rush1/rush-1-3"
  "Rush1/rush-1-4"
  "Rush1/rush-1-5"
)

ok=0
fail=0

for rel in "${PROJECTS[@]}"; do
  dir="$ROOT_DIR/$rel"
  if [ ! -d "$dir" ]; then
    printf '[WARN] missing directory %s (skipped)\n' "$rel" >&2
    continue
  fi
  printf '[INFO] Running tests in %s...\n' "$rel"
  if make -C "$dir" test; then
    ok=$((ok + 1))
  else
    fail=$((fail + 1))
  fi
  printf '\n'

done

printf 'Summary: %d OK / %d failed\n' "$ok" "$fail"
[ "$fail" -eq 0 ]
