#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/star"

ok=0
ko=0

gen_expected() {
  local example="$DIR/star_example.txt"
  : >"$DIR/tests/expected_0.txt"
  if [ ! -f "$example" ]; then
    return
  fi
  for n in 1 2 4 5; do
    awk -v n="$n" '
      $0 ~ ("^\\$> \\./star " n "(\\s*\\|.*)?$") {inblk=1; next}
      $0 ~ "^\\$> " { if (inblk) exit; else next }
      inblk { sub(/\s*\$$/, ""); print }
    ' "$example" >"$DIR/tests/expected_${n}.txt"
  done
}

run_valid_case() {
  local n="$1"
  local expect_file="$DIR/tests/expected_${n}.txt"
  local tmp
  tmp="$(mktemp)"
  set +e
  "$BIN" "$n" >"$tmp"
  local status=$?
  set -e
  if [ "$status" -ne 0 ]; then
    echo "[KO] n=$n exit $status" >&2
    ko=$((ko+1))
    rm -f "$tmp"
    return
  fi
  if [ -f "$expect_file" ]; then
    if diff -u "$expect_file" "$tmp" >/dev/null; then
      echo "[OK] n=$n"
      ok=$((ok+1))
    else
      echo "[KO] n=$n diff" >&2
      ko=$((ko+1))
      diff -u "$expect_file" "$tmp" >&2 || true
    fi
  else
    if [ -s "$tmp" ]; then
      echo "[KO] n=$n unexpected output" >&2
      ko=$((ko+1))
    else
      echo "[OK] n=$n"
      ok=$((ok+1))
    fi
  fi
  rm -f "$tmp"
}

run_error_case() {
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

mkdir -p "$DIR/tests"
gen_expected

run_valid_case 0
run_valid_case 1
run_valid_case 2
run_valid_case 4
run_valid_case 5

run_error_case "missing arg"
run_error_case "non digit" foo
run_error_case "negative" -2

printf 'OK=%d KO=%d\n' "$ok" "$ko"
[ "$ko" -eq 0 ]
