#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/eval_expr"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1 -> got '$2'"; }

run(){ out=$($BIN "$1"); if [ "$out" = "$2" ]; then ok "$1"; else ko "$1" "$out"; fi }

make -C "$DIR" >/dev/null

run "(3+2)*5" 25
run "2+2" 4
run "10-3-2" 5
run "18/3/3" 2
run "5*3%4" 3
run "40 + (2*5) - 7" 43
run "-3+10" 7
run "-(2-5)" 3

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)
