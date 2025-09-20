#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
PARENT="$(cd "$DIR/.." && pwd)"
ARCHIVE="$PARENT/rush1_bins.tgz"
ORACLE_BIN_NAME="rush1-5"
HARNESS_C="$DIR/tests/harness.c"
HARNESS_BIN="$DIR/tests/harness"
TMP_DIR="$(mktemp -d)"
CASES_FILE="$(mktemp)"

cleanup() {
  rm -f "$HARNESS_C" "$HARNESS_BIN" "$CASES_FILE"
  rm -rf "$TMP_DIR"
}
trap cleanup EXIT

cat >"$HARNESS_C" <<'CEOF'
#include <stdlib.h>
#include <unistd.h>

void rush(int x, int y);
void my_putchar(char c);

void my_putchar(char c)
{
    (void)!write(1, &c, 1);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return 84;
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    rush(x, y);
    return 0;
}
CEOF

cat >"$CASES_FILE" <<'EOFCASES'
5 3
5 1
1 1
1 5
4 4
0 3
EOFCASES

gcc -Wall -Wextra -Werror -I"$DIR/include" "$HARNESS_C" "$DIR/src/rush.c" -o "$HARNESS_BIN"

tar -xzf "$ARCHIVE" -C "$TMP_DIR"
ORACLE="$TMP_DIR/bin/$ORACLE_BIN_NAME"
if [ ! -x "$ORACLE" ]; then
  echo "[KO] missing oracle $ORACLE_BIN_NAME" >&2
  exit 1
fi

ok=0
ko=0

while read -r x y; do
  if [ -z "$x" ]; then
    continue
  fi
  ours_stdout="$(mktemp)"
  ours_stderr="$(mktemp)"
  oracle_stdout="$(mktemp)"
  oracle_stderr="$(mktemp)"

  "$HARNESS_BIN" "$x" "$y" >"$ours_stdout" 2>"$ours_stderr" || true
  "$ORACLE" "$x" "$y" >"$oracle_stdout" 2>"$oracle_stderr" || true

  if diff -u "$oracle_stdout" "$ours_stdout" >/dev/null && diff -u "$oracle_stderr" "$ours_stderr" >/dev/null; then
    echo "[OK] $ORACLE_BIN_NAME $x $y"
    ok=$((ok+1))
  else
    echo "[KO] $ORACLE_BIN_NAME $x $y" >&2
    diff -u "$oracle_stdout" "$ours_stdout" >&2 || true
    diff -u "$oracle_stderr" "$ours_stderr" >&2 || true
    ko=$((ko+1))
  fi

  rm -f "$ours_stdout" "$ours_stderr" "$oracle_stdout" "$oracle_stderr"
done <"$CASES_FILE"

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
