#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/infin_add"

pass=0
fail=0

run() {
  out=$($BIN "$1" "$2")
  if [ "$out" = "$3" ]; then
    pass=$((pass + 1))
    printf '[OK ] %s + %s = %s\n' "$1" "$2" "$3"
  else
    fail=$((fail + 1))
    printf '[KO ] %s + %s -> got %s (expected %s)\n' "$1" "$2" "$out" "$3"
  fi
}

make -C "$DIR" >/dev/null

run "-876435" "987143265" "986266830"
run "-807965" "-34532" "-842497"
run "435439435845843984358439" "45359766785665822182412343254343435433339459569" "45359766785665822182412778693779281277323818008"
run "000123" "000001" "124"
run "999" "1" "1000"
run "-1000" "1" "-999"
run "500" "-500" "0"
run "123456789123456789" "-987654321987654321" "-864197532864197532"

printf '%s\n' '-----'
printf 'Passed: %d  Failed: %d\n' "$pass" "$fail"
[ "$fail" -eq 0 ]
