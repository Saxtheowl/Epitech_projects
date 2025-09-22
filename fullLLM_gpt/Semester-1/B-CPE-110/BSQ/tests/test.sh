#!/bin/sh
set -eu

DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/bsq"
REF="$DIR/tests/solve_ref.py"
DATA_DIR="$DIR/tests/data"

TMP_DIR="$(mktemp -d)"
cleanup(){ rm -rf "$TMP_DIR"; }
trap cleanup EXIT

pass=0
fail=0

ok(){ pass=$((pass + 1)); printf '[OK ] %s\n' "$1"; }
ko(){ fail=$((fail + 1)); printf '[KO ] %s\n' "$1" >&2; shift; "$@"; }

build(){ make -C "$DIR" >/dev/null; }

run_valid(){
  name=$1
  map_file=$2
  exp="$TMP_DIR/${name}.expected"
  out="$TMP_DIR/${name}.out"
  python3 "$REF" "$map_file" >"$exp"
  if "$BIN" "$map_file" >"$out"; then
    if diff -u "$exp" "$out" >/dev/null; then
      ok "$name"
    else
      ko "$name" diff -u "$exp" "$out"
    fi
  else
    ko "$name" printf '%s\n' "program exited with failure"
  fi
}

run_invalid(){
  name=$1
  map_file=$2
  out="$TMP_DIR/${name}.out"
  err="$TMP_DIR/${name}.err"
  if "$BIN" "$map_file" >"$out" 2>"$err"; then
    ko "$name" printf '%s\n' "expected non-zero exit"
  else
    status=$?
    if [ -s "$out" ]; then
      ko "$name" printf '%s\n' "expected no stdout"
    else
      err_content="$(tr -d '\n' < "$err")"
      if [ "$err_content" = "map error" ] && [ "$status" -eq 84 ]; then
        ok "$name"
      else
        ko "$name" printf '%s\n' "expected rc=84 and stderr 'map error'"
      fi
    fi
  fi
}

build

run_valid "basic" "$DATA_DIR/valid_basic.map"
run_valid "single_row" "$DATA_DIR/valid_single_row.map"
run_valid "single_col" "$DATA_DIR/valid_single_col.map"
run_valid "all_obstacles" "$DATA_DIR/valid_all_obstacles.map"

run_invalid "invalid_char" "$DATA_DIR/invalid_char.map"
run_invalid "invalid_rowlen" "$DATA_DIR/invalid_rowlen.map"
run_invalid "invalid_count" "$DATA_DIR/invalid_count.map"

printf -- '-----\nPassed: %d  Failed: %d\n' "$pass" "$fail"
[ "$fail" -eq 0 ]
