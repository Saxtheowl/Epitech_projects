#!/usr/bin/env sh
#
# EPITECH PROJECT, 2025
# NOOB tests

set -eu

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT INT TERM

touch "$tmpdir/a.txt"
chmod 666 "$tmpdir/a.txt"

out=$(bash src/noob.sh "$tmpdir")
echo "$out" | grep -q "a.txt"
echo "NOOB tests OK"

