#!/bin/sh
set -eu
ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
TMP_DIR="$ROOT_DIR/tests/tmp"
mkdir -p "$TMP_DIR"
DB="$TMP_DIR/file.json"
BDSH="$ROOT_DIR/bdsh"

pass=0; fail=0
ok() { pass=$((pass+1)); echo "[OK ] $1"; }
ko() { fail=$((fail+1)); echo "[KO ] $1"; printf "%s\n" "$2" | sed 's/^/      /'; }

run() { echo "+ $*"; "$@"; }

rm -f "$DB" 2>/dev/null || true

# Create database
if run "$BDSH" -f "$DB" create database; then ok "create database"; else ko "create database" "failed"; fi

# Create tables
run "$BDSH" -f "$DB" create table user id,firstname,lastname || ko "create table user" "failed"
run "$BDSH" -f "$DB" create table age id,age || ko "create table age" "failed"

# Inserts
run "$BDSH" -f "$DB" insert user id=1,firstname=John,lastname=SMITH || ko "insert 1" "failed"
run "$BDSH" -f "$DB" insert user id=4,firstname=\"Robert John\",lastname=WILLIAMS || ko "insert 2" "failed"
run "$BDSH" -f "$DB" insert user id=2,firstname=Lisa,lastname=SIMPSON || ko "insert 3" "failed"
run "$BDSH" -f "$DB" insert user id=10,lastname=SMITH || ko "insert 4" "failed"
run "$BDSH" -f "$DB" insert user firstname=Laura,lastname=SMITH || ko "insert 5" "failed"
run "$BDSH" -f "$DB" insert user id=9 || ko "insert 6" "failed"
run "$BDSH" -f "$DB" insert age id=1,age=42 || ko "insert age" "failed"

# Select simple
out=$("$BDSH" -f "$DB" select user firstname,lastname)
echo "$out" | grep -q "firstname" && echo "$out" | grep -q "lastname" && ok "select projection" || ko "select projection" "$out"

# Select with where
out=$("$BDSH" -f "$DB" select user firstname,id where lastname=SMITH)
echo "$out" | grep -q "SMITH" && ok "select where" || ko "select where" "$out"

# Order by
out=$("$BDSH" -f "$DB" select user firstname where lastname=SMITH orderby firstname)
echo "$out" | grep -q "firstname" && ok "select orderby" || ko "select orderby" "$out"

# Join
out=$("$BDSH" -f "$DB" select user,age age,firstname,lastname join id where age=42)
echo "$out" | grep -q "42" && echo "$out" | grep -q "John" && ok "select join" || ko "select join" "$out"

# JSON output
out=$("$BDSH" -j -f "$DB" select user firstname,lastname)
echo "$out" | grep -q "\[" && echo "$out" | grep -q "lastname" && ok "select -j" || ko "select -j" "$out"

echo "-----"
echo "Passed: $pass  Failed: $fail"
exit $([ "$fail" -eq 0 ] && echo 0 || echo 1)

