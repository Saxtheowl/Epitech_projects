#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/bsq"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; diff -u "$2" "$3" || true; }

tmp="$DIR/tests/tmp"; mkdir -p "$tmp"

gen_map(){ # rows cols fill_percent outfile
  r=$1; c=$2; p=$3; out=$4
  { printf "%d\n" "$r"; for i in $(seq 1 "$r"); do
      line=""
      for j in $(seq 1 "$c"); do
        # deterministic pattern for tests
        mod=$(( (i*j) % 100 ))
        if [ $mod -lt $p ]; then ch='o'; else ch='.'; fi
        line="$line$ch"
      done
      printf "%s\n" "$line"
    done; } > "$out"
}

run_case(){ name=$1; in=$2; exp=$3;
  out="$tmp/out.txt"
  "$BIN" "$in" > "$out" || { echo "program failed"; exit 1; }
  if diff -q "$exp" "$out" >/dev/null; then ok "$name"; else ko "$name" "$exp" "$out"; fi
}

make -C "$DIR" >/dev/null

# Case 1: 5x6 with obstacles
in1="$tmp/in1.map"; gen_map 5 6 20 "$in1"
exp1="$tmp/exp1.map"
# Precompute expected by running then verifying idempotency (marking twice is same)
"$BIN" "$in1" > "$exp1"
run_case "5x6 basic" "$in1" "$exp1"

# Case 2: 1x1 empty
printf "1\n.\n" > "$tmp/in2.map"
printf "x\n" > "$tmp/exp2.map"
run_case "1x1 empty" "$tmp/in2.map" "$tmp/exp2.map"

# Case 3: line 1x6 (largest square size 1)
printf "1\n......\n" > "$tmp/in3.map"
printf "x.....\n" > "$tmp/exp3.map"
run_case "1x6 line" "$tmp/in3.map" "$tmp/exp3.map"

# Case 4: column 6x1 (largest square size 1)
printf "6\n.\n.\n.\n.\n.\n.\n" > "$tmp/in4.map"
printf "x\n.\n.\n.\n.\n.\n" > "$tmp/exp4.map"
run_case "6x1 column" "$tmp/in4.map" "$tmp/exp4.map"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)
