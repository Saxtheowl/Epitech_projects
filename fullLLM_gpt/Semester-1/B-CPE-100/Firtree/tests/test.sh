#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/firtree"
ORACLE_DIR="$DIR/.firtree_tmp"
ORACLE_BIN="$ORACLE_DIR/firtree"

if [ ! -x "$ORACLE_BIN" ]; then
  if [ -f "$DIR/firtree.tgz" ]; then
    mkdir -p "$ORACLE_DIR"
    tar -xzf "$DIR/firtree.tgz" -C "$ORACLE_DIR"
    chmod +x "$ORACLE_BIN" || true
  fi
fi

if [ ! -x "$ORACLE_BIN" ]; then
  echo "[WARN] Oracle binary not available; running smoke tests only." >&2
fi

ok=0; ko=0
run_case() {
  local n="$1"
  if [ -x "$ORACLE_BIN" ]; then
    if diff -u <("$ORACLE_BIN" "$n") <("$BIN" "$n"); then
      echo "[OK] n=$n"
      ok=$((ok+1))
    else
      echo "[KO] n=$n"
      ko=$((ko+1))
    fi
  else
    "$BIN" "$n" >/dev/null && { echo "[OK] smoke n=$n"; ok=$((ok+1)); } || { echo "[KO] smoke n=$n"; ko=$((ko+1)); }
  fi
}

run_case 1
run_case 2
run_case 3
run_case 4
run_case 5

# Error handling: invalid
if "$BIN" 0 >/tmp/ft_out_$$ 2>/dev/null; then echo "[KO] n=0 should fail"; ko=$((ko+1)); else echo "[OK] n=0 error"; ok=$((ok+1)); fi
rm -f /tmp/ft_out_$$

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
