#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/firtree"
TMP_DIR="$DIR/.firtree_tmp"
ARCHIVE="$DIR/firtree.tgz"
ORACLE_BIN="$TMP_DIR/firtree"

setup_oracle() {
  if [ -x "$ORACLE_BIN" ]; then
    return 0
  fi
  if [ ! -f "$ARCHIVE" ]; then
    echo "[WARN] Missing oracle archive; running smoke tests only." >&2
    return 1
  fi
  mkdir -p "$TMP_DIR"
  tar -xzf "$ARCHIVE" -C "$TMP_DIR"
  chmod +x "$ORACLE_BIN" || true
  return 0
}

ok=0
ko=0

compare_case() {
  local n="$1"
  local out my_out status oracle_status
  local my_tmp oracle_tmp
  my_tmp="$(mktemp)"
  oracle_tmp="$(mktemp)"

  set +e
  "$BIN" "$n" >"$my_tmp"
  status=$?
  if [ -x "$ORACLE_BIN" ]; then
    "$ORACLE_BIN" "$n" >"$oracle_tmp"
    oracle_status=$?
  else
    oracle_status=0
    : >"$oracle_tmp"
  fi
  set -e

  if [ "$status" -ne 0 ]; then
    echo "[KO] n=$n exit $status" >&2
    ko=$((ko+1))
  elif [ -x "$ORACLE_BIN" ] && [ "$status" -ne "$oracle_status" ]; then
    echo "[KO] n=$n exit mismatch (expected $oracle_status)" >&2
    ko=$((ko+1))
  elif [ -x "$ORACLE_BIN" ] && ! diff -u "$oracle_tmp" "$my_tmp" >/dev/null; then
    echo "[KO] n=$n diff" >&2
    diff -u "$oracle_tmp" "$my_tmp" >&2 || true
    ko=$((ko+1))
  else
    echo "[OK] n=$n"
    ok=$((ok+1))
  fi

  rm -f "$my_tmp" "$oracle_tmp"
}

error_case() {
  local label="$1"
  shift || true
  local tmp
  tmp="$(mktemp)"
  set +e
  "$BIN" "$@" >"$tmp" 2>&1
  local status=$?
  set -e
  if [ "$status" -eq 84 ] && [ ! -s "$tmp" ]; then
    echo "[OK] error $label"
    ok=$((ok+1))
  else
    echo "[KO] error $label (exit=$status, output=$(cat "$tmp"))" >&2
    ko=$((ko+1))
  fi
  rm -f "$tmp"
}

if [ ! -x "$BIN" ]; then
  echo "[KO] missing binary $BIN" >&2
  exit 1
fi

setup_oracle || true

for n in 0 1 2 3 4 5; do
  compare_case "$n"
done

error_case "missing arg"
error_case "non digit" foo
error_case "negative" -2

printf 'OK=%d KO=%d\n' "$ok" "$ko"
[ "$ko" -eq 0 ]
