#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/my_top"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; printf "%s\n" "$2" | sed 's/^/      /'; }

make -C "$DIR" >/dev/null

out=$($BIN -b -n 5)
echo "$out" | head -n1 | grep -q "PID" && ok "header" || ko "header" "$out"
lines=$(echo "$out" | wc -l)
[ "$lines" -ge 2 ] && ok "has rows" || ko "has rows" "$out"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

