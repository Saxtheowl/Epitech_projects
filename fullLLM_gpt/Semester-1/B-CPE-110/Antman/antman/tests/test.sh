#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$ROOT_DIR/antman"
GIANT_DIR="$ROOT_DIR/../giantman"
GIANT="$GIANT_DIR/giantman"

TMP_DIR="$(mktemp -d)"
cleanup(){ rm -rf "$TMP_DIR"; }
trap cleanup EXIT

make -C "$ROOT_DIR" >/dev/null
make -C "$GIANT_DIR" >/dev/null

pass=0
fail=0

ok(){ pass=$((pass + 1)); printf '[OK ] %s\n' "$1"; }
ko(){ fail=$((fail + 1)); printf '[KO ] %s\n' "$1" >&2; }

roundtrip(){
  name=$1; content=$2; type=$3
  src="$TMP_DIR/${name}.src"
  comp="$TMP_DIR/${name}.ant"
  out="$TMP_DIR/${name}.out"
  printf '%b' "$content" >"$src"
  if ! "$BIN" "$src" "$type" >"$comp"; then
    ko "$name (compression failed)"
    return
  fi
  # header validation
  if ! python3 - "$comp" "$type" <<'PY'
import sys, pathlib
path = pathlib.Path(sys.argv[1])
data = path.read_bytes()
expected = int(sys.argv[2]) & 0xFF
if len(data) < 5 or data[:4] != b'AR01' or data[4] != expected:
    sys.exit(1)
PY
  then
    ko "$name (invalid header)"
    return
  fi
  if ! "$GIANT" "$comp" "$type" >"$out"; then
    ko "$name (decompression failed)"
    return
  fi
  if diff -q "$src" "$out" >/dev/null; then
    ok "$name"
  else
    ko "$name (mismatch)"
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

roundtrip "lyrics" "Maiha hi Maiha hou Maiha ha Maiha ha ha" 1
roundtrip "html" "<html><body><p>Hello</p></body></html>" 2
roundtrip "binary" "\x00\x00\x00\x01\x02\x02\x02\x02\xff\xff" 3

expect_fail "invalid type" "$BIN" "$TMP_DIR/lyrics.src" 4

printf -- '-----\nPassed: %d  Failed: %d\n' "$pass" "$fail"
[ "$fail" -eq 0 ]
