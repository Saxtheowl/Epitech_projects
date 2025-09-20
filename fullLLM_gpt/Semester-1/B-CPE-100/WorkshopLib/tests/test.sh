#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
LIB="$DIR/lib/libmy.a"
TEST_BIN="$DIR/tests/unit"
CASES_SRC="$DIR/tests/test.c"
LOG_FILE="$DIR/tests/.unit.log"

if [ ! -f "$LIB" ]; then
  echo "[KO] missing library $LIB" >&2
  exit 1
fi

gcc -Wall -Wextra -Werror -I"$DIR/include" "$CASES_SRC" "$LIB" -o "$TEST_BIN"
if "$TEST_BIN" >"$LOG_FILE" 2>&1; then
  echo "[OK] libmy unit tests"
else
  status=$?
  echo "[KO] libmy unit tests (exit=$status)" >&2
  cat "$LOG_FILE" >&2
  rm -f "$LOG_FILE" "$TEST_BIN"
  exit $status
fi
rm -f "$LOG_FILE" "$TEST_BIN"
