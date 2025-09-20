#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
HARNESS_C="$DIR/tests/harness.c"
HARNESS_BIN="$DIR/tests/harness"
SRC_MATCH="$DIR/src/match.c"
SRC_NMATCH="$DIR/src/nmatch.c"
INCLUDE="$DIR/include"
CASES_FILE="$(mktemp)"
ORACLE_DIR="$(mktemp -d)"

cleanup() {
  rm -f "$HARNESS_BIN" "$HARNESS_C" "$CASES_FILE"
  rm -rf "$ORACLE_DIR"
}
trap cleanup EXIT

cat >"$HARNESS_C" <<'CEOF'
#include <stdio.h>
#include <stdlib.h>

#include "matchnmatch.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        return 84;
    }
    const char *s = argv[1];
    const char *p = argv[2];
    int m = match(s, p);
    int n = nmatch(s, p);
    printf("match(\"%s\", \"%s\") returned %d\n", s, p, m);
    printf("nmatch(\"%s\", \"%s\") returned %d\n", s, p, n);
    return 0;
}
CEOF

gcc -Wall -Wextra -Werror -I"$INCLUDE" "$HARNESS_C" "$SRC_MATCH" "$SRC_NMATCH" -o "$HARNESS_BIN"

# Prepare reference executables from subject archives
if [ -f "$DIR/match.tgz" ]; then
  tar -xzf "$DIR/match.tgz" -C "$ORACLE_DIR"
fi
if [ -f "$DIR/nmatch.tgz" ]; then
  tar -xzf "$DIR/nmatch.tgz" -C "$ORACLE_DIR"
fi
ORACLE_MATCH="$ORACLE_DIR/match"
ORACLE_NMATCH="$ORACLE_DIR/nmatch"
if [ ! -x "$ORACLE_MATCH" ] || [ ! -x "$ORACLE_NMATCH" ]; then
  echo "[WARN] Oracle binaries missing; skipping comparison." >&2
fi

cat >"$CASES_FILE" <<'EOFCASES'
"" "" # match empty strings
"" "*" # star matches empty
"abc" "abc" # identical strings
"abc" "a*c" # simple star
"abc" "*" # single star all
"abcbd" "*b*" # subject example (2 combos)
"abc" "a**" # subject example (3 combos)
"abcd" "a*d" # star middle
"aaaa" "a*" # repeated characters
"abacabaaa" "a*a*a" # multiple stars
"abc" "ab*d" # negative match
EOFCASES

ok=0
ko=0

while read -r raw_s raw_p _; do
  [ -z "$raw_s" ] && continue
  s="${raw_s#\"}"
  s="${s%\"}"
  p="${raw_p#\"}"
  p="${p%\"}"

  harness_out="$($HARNESS_BIN "$s" "$p")"
  match_line="$(printf '%s\n' "$harness_out" | sed -n '1p')"
  nmatch_line="$(printf '%s\n' "$harness_out" | sed -n '2p')"

  if [ -x "$ORACLE_MATCH" ]; then
    expect_match="$($ORACLE_MATCH "$s" "$p")"
  else
    expect_match="$match_line"
  fi
  if [ -x "$ORACLE_NMATCH" ]; then
    expect_nmatch="$($ORACLE_NMATCH "$s" "$p")"
  else
    expect_nmatch="$nmatch_line"
  fi

  if [ "$match_line" = "$expect_match" ]; then
    echo "[OK] match '$s' '$p'"
    ok=$((ok+1))
  else
    echo "[KO] match '$s' '$p'" >&2
    echo "expected: $expect_match" >&2
    echo "got:      $match_line" >&2
    ko=$((ko+1))
  fi

  if [ "$nmatch_line" = "$expect_nmatch" ]; then
    echo "[OK] nmatch '$s' '$p'"
    ok=$((ok+1))
  else
    echo "[KO] nmatch '$s' '$p'" >&2
    echo "expected: $expect_nmatch" >&2
    echo "got:      $nmatch_line" >&2
    ko=$((ko+1))
  fi

done <"$CASES_FILE"

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
