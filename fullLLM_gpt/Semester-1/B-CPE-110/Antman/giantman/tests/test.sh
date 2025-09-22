#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
ANT_DIR="$ROOT_DIR/../antman"
ANT_BIN="$ANT_DIR/antman"
BIN="$ROOT_DIR/giantman"

TMP_DIR="$(mktemp -d)"
cleanup(){ rm -rf "$TMP_DIR"; }
trap cleanup EXIT

make -C "$ANT_DIR" >/dev/null
make -C "$ROOT_DIR" >/dev/null

pass=0
fail=0

ok(){ pass=$((pass + 1)); printf '[OK ] %s\n' "$1"; }
ko(){ fail=$((fail + 1)); printf '[KO ] %s\n' "$1" >&2; }

roundtrip(){
  label=$1; data=$2; type=$3
  prefix="$TMP_DIR/${label}"
  printf '%b' "$data" >"$prefix.orig"
  "$ANT_BIN" "$prefix.orig" "$type" >"$prefix.ant"
  if "$BIN" "$prefix.ant" "$type" >"$prefix.out" && diff -q "$prefix.orig" "$prefix.out" >/dev/null; then
    ok "$label"
  else
    ko "$label"
  fi
}

expect_fail(){
  label=$1; shift
  if "$@" >/dev/null 2>&1; then
    ko "$label"
  else
    ok "$label"
  fi
}

roundtrip "text" "Hello Hello Hello!!!" 1
roundtrip "html" "<div><span>Test</span></div>" 2
roundtrip "binary" "\x00\x00\x01AAAA\xff\xff\xff" 3

prefix="$TMP_DIR/mismatch"
printf '%s' "ABCDEF" >"$prefix.orig"
"$ANT_BIN" "$prefix.orig" 1 >"$prefix.ant"
expect_fail "mismatched type" "$BIN" "$prefix.ant" 2

invalid="$TMP_DIR/invalid.ant"
python3 - "$invalid" <<'PY'
import pathlib, sys
path = pathlib.Path(sys.argv[1])
path.write_bytes(b'WRNG' + bytes([1, 0, 0, 0]))
PY
expect_fail "invalid header" "$BIN" "$invalid" 1

printf -- '-----\nPassed: %d  Failed: %d\n' "$pass" "$fail"
[ "$fail" -eq 0 ] && echo "giantman: tests OK"
