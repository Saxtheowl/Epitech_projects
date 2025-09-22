#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT_DIR/calc"

if [ ! -x "$BIN" ]; then
  echo "[KO] missing binary $BIN" >&2
  exit 1
fi

SYNTAX_MSG="syntax error"
ERROR_MSG="error"

run_case() {
  local base="$1"
  local ops="$2"
  local size="$3"
  local expr="$4"
  local expected="$5"
  local label="$6"
  local out_file err_file

  out_file="$(mktemp)"
  err_file="$(mktemp)"
  printf '%s' "$expr" | "$BIN" "$base" "$ops" "$size" >"$out_file" 2>"$err_file" || true
  if [ "$(cat "$out_file")" = "$expected" ] && [ ! -s "$err_file" ]; then
    echo "[OK] $label"
  else
    echo "[KO] $label" >&2
    echo "stdout: $(cat "$out_file")" >&2
    echo "stderr: $(cat "$err_file")" >&2
    rm -f "$out_file" "$err_file"
    exit 1
  fi
  rm -f "$out_file" "$err_file"
}

run_case "0123456789" "()+-*/%" 3 "3+6" "9" "3+6"
run_case "0123456789" "{}vwxyz" 3 "3v6" "9" "custom plus"
run_case "0123456789" "()+-*/%" 11 "----++-6*12" "-72" "multiple unary"
run_case "0123456789" "()+-*/%" 12 "-(12-(4*32))" "116" "nested"
run_case "0A@!;ie& ]" "()+-*/%" 12 "-(e@-(;*!@))" "ee" "custom base"
run_case "0123456789" "()+-*/%" 84 "-(12*(13+15/5*(6/(12+14%(30%5+(10*25)-46)+16)-20)/43)*20)*(-(12-98*42)*(16+63-50/3))" "-744629760" "big expression"

# Syntax error case
out_file="$(mktemp)"
err_file="$(mktemp)"
printf '%s' "----++-6(12)" | "$BIN" "0123456789" "()+-*/%" 10 >"$out_file" 2>"$err_file" || true
if [ ! -s "$out_file" ] && [ "$(cat "$err_file")" = "$SYNTAX_MSG" ]; then
  echo "[OK] syntax error"
else
  echo "[KO] syntax error" >&2
  echo "stdout: $(cat "$out_file")" >&2
  echo "stderr: $(cat "$err_file")" >&2
  rm -f "$out_file" "$err_file"
  exit 1
fi
rm -f "$out_file" "$err_file"

# Division by zero
out_file="$(mktemp)"
err_file="$(mktemp)"
printf '%s' "10/0" | "$BIN" "0123456789" "()+-*/%" 4 >"$out_file" 2>"$err_file" || true
if [ ! -s "$out_file" ] && [ "$(cat "$err_file")" = "$ERROR_MSG" ]; then
  echo "[OK] division by zero"
else
  echo "[KO] division by zero" >&2
  echo "stdout: $(cat "$out_file")" >&2
  echo "stderr: $(cat "$err_file")" >&2
  rm -f "$out_file" "$err_file"
  exit 1
fi
rm -f "$out_file" "$err_file"

# Zero/negative size argument
out_file="$(mktemp)"
err_file="$(mktemp)"
printf '%s' "3+6" | "$BIN" "0123456789" "()+-*/%" 0 >"$out_file" 2>"$err_file" || true
if [ ! -s "$out_file" ] && [ "$(cat "$err_file")" = "$SYNTAX_MSG" ]; then
  echo "[OK] invalid size"
else
  echo "[KO] invalid size" >&2
  echo "stdout: $(cat "$out_file")" >&2
  echo "stderr: $(cat "$err_file")" >&2
  rm -f "$out_file" "$err_file"
  exit 1
fi
rm -f "$out_file" "$err_file"
