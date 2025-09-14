#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/my_sudo"
TMP="$DIR/tests/tmp"; mkdir -p "$TMP"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; printf "%s\n" "$2" | sed 's/^/      /'; }

make -C "$DIR" >/dev/null

# A known solvable Sudoku
cat > "$TMP/in.txt" << 'EOF'
53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79
EOF

exp="$TMP/exp.txt"; cat > "$exp" << 'EOF'
534678912
672195348
198342567
859761423
426853791
713924856
961537284
287419635
345286179
EOF

out="$TMP/out.txt"
"$BIN" "$TMP/in.txt" > "$out"
diff -q "$exp" "$out" >/dev/null && ok "solve known grid" || ko "solve known grid" "$(diff -u "$exp" "$out" || true)"

# Invalid size
printf "1\n" > "$TMP/bad.txt"
if "$BIN" "$TMP/bad.txt" 2>/dev/null; then ko "invalid input" "expected error"; else ok "invalid input"; fi

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

