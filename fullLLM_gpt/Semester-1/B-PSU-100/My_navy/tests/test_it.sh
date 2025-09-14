#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/my_navy"
TMP="$DIR/tests/tmp"
mkdir -p "$TMP"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; printf "%s\n" "$2" | sed 's/^/      /'; }

make -C "$DIR" >/dev/null

cat > "$TMP/map" << 'EOF'
2:C1:C2
3:D4:F4
4:A10:D10
5:J1:J5
EOF

P1_MOVES="C1 C2 D4 E4 F4 A10 B10 C10 D10 J1 J2 J3 J4 J5"
P2_MOVES="A1 A2 A3 A4 A5 A6 A7 A8 A9 A1 A2 A3 A4 A5"

( MOVES="$P1_MOVES" "$BIN" "$TMP/map" > "$TMP/p1.out" 2>&1 & echo $! > "$TMP/p1.pid" )
sleep 0.3
P1PID=$(cat "$TMP/p1.pid")
( MOVES="$P2_MOVES" "$BIN" "$P1PID" "$TMP/map" > "$TMP/p2.out" 2>&1 & echo $! > "$TMP/p2.pid" )

sleep 6 || true

out1=$(cat "$TMP/p1.out" || true)
out2=$(cat "$TMP/p2.out" || true)

echo "$out1" | grep -q "I win" && ok "P1 wins" || ko "P1 wins" "$out1"
echo "$out2" | grep -q "I lose" && ok "P2 loses" || ko "P2 loses" "$out2"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

