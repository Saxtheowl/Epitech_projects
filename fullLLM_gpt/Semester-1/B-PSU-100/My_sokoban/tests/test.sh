#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/my_sokoban"
TMP="$DIR/tests/tmp"
mkdir -p "$TMP"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; diff -u "$2" "$3" || true; }

make -C "$DIR" >/dev/null

# Invalid usage
if "$BIN" >/dev/null 2>&1; then ko "usage no arg" /dev/null /dev/null; else ok "usage no arg"; fi

# Build a tiny valid map
cat > "$TMP/map1" << 'EOF'
#####
#PXO#
#####
EOF

# No moves: just render initial
exp="$TMP/exp1"; cat > "$exp" << 'EOF'
#####
#PXO#
#####
EOF
out="$TMP/out1"; MOVES="" "$BIN" "$TMP/map1" > "$out"
diff -q "$exp" "$out" >/dev/null && ok "render initial" || ko "render initial" "$exp" "$out"

# Push X right onto O: moves = R
cat > "$TMP/map2" << 'EOF'
#####
#PXO#
#####
EOF
exp2="$TMP/exp2"; cat > "$exp2" << 'EOF'
#####
# PX#
#####
EOF
out2="$TMP/out2"; MOVES="R" "$BIN" "$TMP/map2" > "$out2"
diff -q "$exp2" "$out2" >/dev/null && ok "push onto target" || ko "push onto target" "$exp2" "$out2"

# Collision with wall: move up should no-op
cat > "$TMP/map3" << 'EOF'
#####
#P XO
#####
EOF
exp3="$TMP/exp3"; cat > "$exp3" << 'EOF'
#####
#P XO
#####
EOF
out3="$TMP/out3"; MOVES="U" "$BIN" "$TMP/map3" > "$out3" || true
diff -q "$exp3" "$out3" >/dev/null && ok "collision wall" || ko "collision wall" "$exp3" "$out3"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

