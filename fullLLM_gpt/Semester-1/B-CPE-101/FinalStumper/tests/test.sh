#!/bin/sh
set -eu
ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$ROOT_DIR/rush3"
ARCHIVE="$ROOT_DIR/rush1_bins.tgz"
TMP_DIR="$(mktemp -d)"

cleanup() {
  rm -rf "$TMP_DIR"
}
trap cleanup EXIT

if [ ! -x "$BIN" ]; then
  make -C "$ROOT_DIR" >/dev/null
fi

tar -xzf "$ARCHIVE" -C "$TMP_DIR"
ORACLE_DIR="$TMP_DIR/bin"

pass=0
fail=0

run() {
  input="$1"
  expected="$2"
  out="$(printf '%s' "$input" | "$BIN")"
  if [ "$out" = "$expected" ]; then
    pass=$((pass + 1))
    printf '[OK ] %s\n' "$expected"
  else
    fail=$((fail + 1))
    printf '[KO ] expected %s got %s\n' "$expected" "$out"
  fi
}

pipe_run() {
  generator="$1"
  args="$2"
  expected="$3"
  out="$("$generator" $args | "$BIN")"
  if [ "$out" = "$expected" ]; then
    pass=$((pass + 1))
    printf '[OK ] %s %s\n' "$(basename "$generator")" "$args"
  else
    fail=$((fail + 1))
    printf '[KO ] %s %s -> %s (expected %s)\n' "$(basename "$generator")" "$args" "$out" "$expected"
  fi
}

pipe_run "$ORACLE_DIR/rush1-1" "4 4" "[rush1-1] 4 4"
pipe_run "$ORACLE_DIR/rush1-2" "3 4" "[rush1-2] 3 4"
pipe_run "$ORACLE_DIR/rush1-3" "5 1" "[rush1-3] 5 1 || [rush1-4] 5 1 || [rush1-5] 5 1"
pipe_run "$ORACLE_DIR/rush1-4" "1 1" "[rush1-3] 1 1 || [rush1-4] 1 1 || [rush1-5] 1 1"
pipe_run "$ORACLE_DIR/rush1-5" "2 2" "[rush1-5] 2 2"
run "random\npattern" "none"

printf '%s\n' '-----'
printf 'Passed: %d  Failed: %d\n' "$pass" "$fail"
[ "$fail" -eq 0 ]
