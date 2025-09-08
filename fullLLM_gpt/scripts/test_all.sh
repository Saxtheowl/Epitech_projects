#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
color() { printf "\033[%sm%s\033[0m" "$1" "$2"; }
info() { echo "["$(color 34 INFO)"] $*"; }
ok() { echo "["$(color 32 OK)"] $*"; }
ko() { echo "["$(color 31 KO)"] $*"; }

run_make_test() {
  local dir="$1"
  if [ -f "$dir/Makefile" ] || [ -f "$dir/makefile" ]; then
    if make -C "$dir" -n test >/dev/null 2>&1; then
      info "make -C $dir test"
      if make -C "$dir" test; then ok "test passed in $dir"; else ko "test failed in $dir"; fi
      return
    fi
    if make -C "$dir" -n >/dev/null 2>&1; then
      info "make -C $dir"
      if make -C "$dir"; then ok "build ok in $dir"; else ko "build failed in $dir"; fi
      return
    fi
  fi
  info "No Makefile in $dir"
}

# Iterate projects
shopt -s nullglob
for sem in "$ROOT"/Semester-*; do
  [ -d "$sem" ] || continue
  info "Semester: $(basename "$sem")"
  for proj in "$sem"/*; do
    [ -d "$proj" ] || continue
    info " Project: $(basename "$proj")"
    # Try each immediate subdir as a subproject
    found=0
    for sub in "$proj"/*; do
      [ -d "$sub" ] || continue
      found=1
      info "  Subproject: $(basename "$sub")"
      run_make_test "$sub" || true
    done
    if [ "$found" = 0 ]; then
      info "  (no subprojects)"
      run_make_test "$proj" || true
    fi
  done
  echo
done
