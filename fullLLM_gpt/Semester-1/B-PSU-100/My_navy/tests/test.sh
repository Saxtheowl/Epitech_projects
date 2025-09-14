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

# Usage
out=$($BIN -h)
echo "$out" | grep -q "USAGE" && ok "usage" || ko "usage" "$out"

# Invalid args
if $BIN 2>/dev/null; then ko "invalid args" "expected error"; else ok "invalid args"; fi

# Valid map
cat > "$TMP/map.txt" << 'EOF'
2:C1:C2
3:D4:F4
4:A10:D10
5:J1:J5
EOF
out=$($BIN "$TMP/map.txt")
echo "$out" | grep -q "2" && echo "$out" | grep -q "5" && ok "load map" || ko "load map" "$out"

# Invalid map (overlap)
cat > "$TMP/bad.txt" << 'EOF'
2:C1:C2
3:C1:E1
4:A10:D10
5:J1:J5
EOF
if $BIN "$TMP/bad.txt" 2>/dev/null; then ko "invalid overlap" "expected failure"; else ok "invalid overlap"; fi

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

