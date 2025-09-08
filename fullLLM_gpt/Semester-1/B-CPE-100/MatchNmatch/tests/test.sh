#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")/.." && pwd)"
ORACLE_DIR="$DIR/._tmp"
ORACLE_MATCH="$ORACLE_DIR/match"
ORACLE_NMATCH="$ORACLE_DIR/nmatch"
MATCH_BIN="$DIR/match"
NMATCH_BIN="$DIR/nmatch"

mkdir -p "$ORACLE_DIR"
if [ -f "$DIR/match.tgz" ] && [ ! -x "$ORACLE_MATCH" ]; then
  tar -xzf "$DIR/match.tgz" -C "$ORACLE_DIR"
  chmod +x "$ORACLE_MATCH" || true
fi
if [ -f "$DIR/nmatch.tgz" ] && [ ! -x "$ORACLE_NMATCH" ]; then
  tar -xzf "$DIR/nmatch.tgz" -C "$ORACLE_DIR"
  chmod +x "$ORACLE_NMATCH" || true
fi

ok=0; ko=0
run_pair() {
  local s="$1" p="$2"
  if ! diff -u <("$ORACLE_MATCH" "$s" "$p") <("$MATCH_BIN" "$s" "$p"); then
    echo "[KO] match '$s' '$p'"; ko=$((ko+1)); else echo "[OK] match '$s' '$p'"; ok=$((ok+1)); fi
  if ! diff -u <("$ORACLE_NMATCH" "$s" "$p") <("$NMATCH_BIN" "$s" "$p"); then
    echo "[KO] nmatch '$s' '$p'"; ko=$((ko+1)); else echo "[OK] nmatch '$s' '$p'"; ok=$((ok+1)); fi
}

cases=(
  "abc abc"
  "abc a*c"
  "abc *"
  "abcdef a*f"
  "abcdef a*d*f"
  "aaaa a*"
  "aaaa *a"
  "abacabaaa a*a*a"
  "abc ab*d"
)

for pair in "${cases[@]}"; do
  s="${pair%% *}"; p="${pair#* }"
  run_pair "$s" "$p"
done

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
