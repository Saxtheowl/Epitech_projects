#!/bin/sh
set -eu
DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
BIN="$DIR/my_ls"
TMP="$DIR/tests/tmp"
mkdir -p "$TMP"

pass=0; fail=0
ok(){ pass=$((pass+1)); echo "[OK ] $1"; }
ko(){ fail=$((fail+1)); echo "[KO ] $1"; printf "%s\n" "$2" | sed 's/^/      /'; }

setup_tree(){
  rm -rf "$TMP/tree"; mkdir -p "$TMP/tree/a/b" "$TMP/tree/x"
  echo foo > "$TMP/tree/file1"
  echo bar > "$TMP/tree/.hidden"
  sleep 1
  echo baz > "$TMP/tree/file2"
}

make -C "$DIR" >/dev/null
setup_tree

# 1) basic listing
out=$("$BIN" "$TMP/tree")
echo "$out" | grep -q "file1" && echo "$out" | grep -q "file2" && ok "basic" || ko "basic" "$out"

# 2) -a includes hidden
out=$("$BIN" -a "$TMP/tree")
echo "$out" | grep -q ".hidden" && ok "-a shows hidden" || ko "-a shows hidden" "$out"

# 3) -t orders by mtime desc (file2 newer than file1)
first=$(echo "$out" | head -n1)
out_t=$("$BIN" -t "$TMP/tree")
test "$first" != "$out_t" && echo "$out_t" | head -n1 | grep -q "file2" && ok "-t sort" || ko "-t sort" "$out_t"

# 4) -R recursive prints subdir header
out=$("$BIN" -R "$TMP/tree")
echo "$out" | grep -q "$TMP/tree/a:" && ok "-R header" || ko "-R header" "$out"

# 5) -l long format starts with perms
out=$("$BIN" -l "$TMP/tree")
echo "$out" | sed '1d' | head -n1 | grep -Eq '^[dl-]r' && ok "-l format" || ko "-l format" "$out"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)
