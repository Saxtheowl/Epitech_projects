#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/star"

ok=0; ko=0
run_case() {
  local n="$1"; shift
  local expect_file="$DIR/tests/expected_$n.txt"
  if [ ! -f "$expect_file" ]; then
    echo "[WARN] Missing expected file for n=$n" >&2
    return 0
  fi
  local out
  if ! out="$($BIN "$n")"; then
    echo "[KO] star $n returned non-zero" >&2
    ko=$((ko+1))
    return 0
  fi
  if diff -u "$expect_file" <(printf "%s\n" "$out"); then
    echo "[OK] n=$n"
    ok=$((ok+1))
  else
    echo "[KO] n=$n"
    ko=$((ko+1))
  fi
}

# Build expected outputs from provided example file, normalizing cat -e lines
gen_expected() {
  local example="$DIR/star_example.txt"
  for n in 1 2 4 5; do
    awk -v n="$n" '
      $0 ~ ("^\\$> \\./star " n "(\\s*\\|.*)?$") {inblk=1; next}
      $0 ~ "^\\$> " { if (inblk) exit; else next }
      inblk { print }
    ' "$example" \
    | sed 's/\$$//g' \
    > "$DIR/tests/expected_${n}.txt"
  done
}

chmod +x "$DIR/star" 2>/dev/null || true
mkdir -p "$DIR/tests"
if [ -f "$DIR/star_example.txt" ]; then
  gen_expected
fi

run_case 1 || true
run_case 2 || true
run_case 4 || true
run_case 5 || true

# Error handling: size 0 should fail and produce no stdout
if "$BIN" 0 >/tmp/star_out_$$ 2>/dev/null; then
  echo "[KO] n=0 should fail"; ko=$((ko+1))
else
  if [ -s /tmp/star_out_$$ ]; then echo "[KO] n=0 printed output"; ko=$((ko+1)); else echo "[OK] n=0 error"; ok=$((ok+1)); fi
fi
rm -f /tmp/star_out_$$

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
