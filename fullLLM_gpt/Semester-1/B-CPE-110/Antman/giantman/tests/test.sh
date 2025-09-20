#!/bin/sh
set -eu
ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
ANT_DIR="$ROOT_DIR/../antman"
ANT_BIN="$ANT_DIR/antman"
BIN="$ROOT_DIR/giantman"
TMP_DIR="$ROOT_DIR/tests/tmp"

mkdir -p "$TMP_DIR"

make -C "$ANT_DIR" >/dev/null
make -C "$ROOT_DIR" >/dev/null

compress() {
  local content="$1"
  local type="$2"
  local prefix="$TMP_DIR/case"
  printf '%b' "$content" > "${prefix}.orig"
  "$ANT_BIN" "${prefix}.orig" "$type" > "${prefix}.ant"
  "$BIN" "${prefix}.ant" "$type" > "${prefix}.out"
  diff -q "${prefix}.orig" "${prefix}.out"
}

compress "Hello Hello Hello!!!" 1
compress "<div><span>Test</span></div>" 2
compress "\x00\x00\x01AAAA\xff\xff\xff" 3

rm -rf "$TMP_DIR"

echo "giantman: tests OK"
