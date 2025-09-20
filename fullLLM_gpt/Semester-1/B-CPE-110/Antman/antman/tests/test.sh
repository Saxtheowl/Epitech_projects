#!/bin/sh
set -eu
ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$ROOT_DIR/antman"
GIANT_DIR="$ROOT_DIR/../giantman"
GIANT="$GIANT_DIR/giantman"
TMP_DIR="$ROOT_DIR/tests/tmp"

mkdir -p "$TMP_DIR"

make -C "$ROOT_DIR" >/dev/null
make -C "$GIANT_DIR" >/dev/null

pass=0
fail=0

compress_and_check() {
  local name="$1"
  local input="$2"
  local type="$3"
  local comp="$TMP_DIR/${name}.ant"
  local out="$TMP_DIR/${name}.out"

  printf '%b' "$input" > "$TMP_DIR/${name}.txt"
  if ! "$BIN" "$TMP_DIR/${name}.txt" "$type" > "$comp"; then
    echo "[KO] $name (compression failed)"
    fail=$((fail + 1))
    return
  fi
  if ! "$GIANT" "$comp" "$type" > "$out"; then
    echo "[KO] $name (decompression failed)"
    fail=$((fail + 1))
    return
  fi
  if diff -q "$TMP_DIR/${name}.txt" "$out" >/dev/null; then
    echo "[OK] $name"
    pass=$((pass + 1))
  else
    echo "[KO] $name (mismatch)"
    fail=$((fail + 1))
  fi
}

compress_and_check "lyrics" "Maiha hi Maiha hou Maiha ha Maiha ha ha" 1
compress_and_check "html" "<html><body><p>Hello</p></body></html>" 2
compress_and_check "binary" "\x00\x00\x00\x01\x02\x02\x02\x02\xff\xff" 3

rm -rf "$TMP_DIR"

if [ "$fail" -eq 0 ]; then
  echo "Passed: $pass Failed: $fail"
else
  echo "Passed: $pass Failed: $fail"
  exit 1
fi
