#!/usr/bin/env bash
set -euo pipefail

DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$DIR/count_island"
MAP_FILE="$DIR/map.txt"
EXPECTED_OUT="$(mktemp)"
EXPECTED_COUNT_FILE="$(mktemp)"
UNIT_BIN="$DIR/tests/unit_cases"

cleanup() {
  rm -f "$EXPECTED_OUT" "$EXPECTED_COUNT_FILE" "$UNIT_BIN"
}
trap cleanup EXIT

if [ ! -x "$BIN" ]; then
  echo "[KO] missing binary $BIN" >&2
  exit 1
fi

python3 - <<'PY' "$MAP_FILE" "$EXPECTED_OUT" "$EXPECTED_COUNT_FILE"
import sys
from pathlib import Path

map_path = Path(sys.argv[1])
out_path = Path(sys.argv[2])
count_path = Path(sys.argv[3])
lines = map_path.read_text().splitlines()
if not lines:
    out_path.write_text("")
    count_path.write_text("0")
    raise SystemExit
height = int(lines[0]) if lines[0].strip() else 0
grid_lines = lines[1:height + 1]
grid = [list(line) for line in grid_lines]
rows = len(grid)

sys.setrecursionlimit(10000)

def flood(r, c, mark):
    if r < 0 or r >= rows:
        return
    row = grid[r]
    if c < 0 or c >= len(row):
        return
    if row[c] != 'X':
        return
    row[c] = mark
    flood(r - 1, c, mark)
    flood(r + 1, c, mark)
    flood(r, c - 1, mark)
    flood(r, c + 1, mark)

islands = 0
for r in range(rows):
    for c in range(len(grid[r])):
        if grid[r][c] == 'X':
            if islands >= 10:
                raise SystemExit('Map contains more than 10 islands')
            flood(r, c, chr(ord('0') + islands))
            islands += 1

out_path.write_text("\n".join("".join(row) for row in grid) + "\n")
count_path.write_text(str(islands))
PY

ok=0
ko=0

compare_output() {
  local result
  result="$(mktemp)"
  "$BIN" "$MAP_FILE" >"$result"
  if diff -u "$EXPECTED_OUT" "$result" >/dev/null; then
    echo "[OK] map transformation"
    ok=$((ok+1))
  else
    echo "[KO] map transformation" >&2
    diff -u "$EXPECTED_OUT" "$result" >&2 || true
    ko=$((ko+1))
  fi
  rm -f "$result"
}

compile_unit_tests() {
  cat >"$DIR/tests/unit_cases.c" <<'CEOF'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "count_island.h"

static int test_single_island(void)
{
    char row0[] = "XX";
    char row1[] = "XX";
    char *world[] = {row0, row1, NULL};
    int count = count_island(world);
    if (count != 1) {
        fprintf(stderr, "Expected 1 island, got %d\n", count);
        return 1;
    }
    if (row0[0] != '0' || row0[1] != '0' || row1[0] != '0' || row1[1] != '0') {
        fprintf(stderr, "Island not filled with 0s\n");
        return 1;
    }
    return 0;
}

static int test_diagonal_islands(void)
{
    char row0[] = "X..";
    char row1[] = ".X.";
    char row2[] = "..X";
    char *world[] = {row0, row1, row2, NULL};
    int count = count_island(world);
    if (count != 3) {
        fprintf(stderr, "Expected 3 islands, got %d\n", count);
        return 1;
    }
    if (row0[0] != '0' || row1[1] != '1' || row2[2] != '2') {
        fprintf(stderr, "Diagonal islands not numbered correctly\n");
        return 1;
    }
    return 0;
}

static int test_no_island(void)
{
    char row0[] = "....";
    char row1[] = "....";
    char *world[] = {row0, row1, NULL};
    int count = count_island(world);
    if (count != 0) {
        fprintf(stderr, "Expected 0 island, got %d\n", count);
        return 1;
    }
    if (row0[0] != '.' || row1[3] != '.') {
        fprintf(stderr, "Dots should remain untouched\n");
        return 1;
    }
    return 0;
}

static char **load_map(const char *path, int *height)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
        return NULL;

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        return NULL;
    }

    int rows = atoi(buffer);
    if (rows <= 0) {
        fclose(fp);
        return NULL;
    }

    char **grid = malloc(sizeof(char *) * (rows + 1));
    if (grid == NULL) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < rows; ++i) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL) {
            rows = i;
            break;
        }
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';
        grid[i] = malloc(len + 1);
        if (grid[i] == NULL) {
            rows = i;
            break;
        }
        memcpy(grid[i], buffer, len + 1);
    }
    grid[rows] = NULL;
    fclose(fp);
    if (height != NULL)
        *height = rows;
    return grid;
}

static void free_map(char **grid)
{
    if (grid == NULL)
        return;
    for (int i = 0; grid[i] != NULL; ++i)
        free(grid[i]);
    free(grid);
}

static int test_large_map(void)
{
    int rows = 0;
    char **grid = load_map("MAP_PLACEHOLDER", &rows);
    if (grid == NULL) {
        fprintf(stderr, "Failed to load map file\n");
        return 1;
    }
    int count = count_island(grid);
    if (count != EXPECTED_COUNT) {
        fprintf(stderr, "Expected %d islands, got %d\n", EXPECTED_COUNT, count);
        free_map(grid);
        return 1;
    }
    int seen[10] = {0};
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; grid[r][c] != '\0'; ++c) {
            char ch = grid[r][c];
            if (ch == 'X') {
                fprintf(stderr, "Unconverted X at (%d,%d)\n", r, c);
                free_map(grid);
                return 1;
            }
            if (ch >= '0' && ch <= '9')
                seen[ch - '0'] = 1;
        }
    }
    for (int i = 0; i < EXPECTED_COUNT && i < 10; ++i) {
        if (!seen[i]) {
            fprintf(stderr, "Island %d not present in output\n", i);
            free_map(grid);
            return 1;
        }
    }
    free_map(grid);
    return 0;
}

int main(void)
{
    int failures = 0;

    failures += test_single_island();
    failures += test_diagonal_islands();
    failures += test_no_island();
    failures += test_large_map();

    if (failures != 0)
        return 84;
    return 0;
}
CEOF

  sed -i "s|MAP_PLACEHOLDER|$MAP_FILE|" "$DIR/tests/unit_cases.c"
  expected_count="$(cat "$EXPECTED_COUNT_FILE")"
  sed -i "s/EXPECTED_COUNT/$expected_count/" "$DIR/tests/unit_cases.c"

  gcc -Wall -Wextra -Werror -I"$DIR/include" "$DIR/src/count_island.c" "$DIR/tests/unit_cases.c" -o "$UNIT_BIN"
}

run_unit_tests() {
  if "$UNIT_BIN"; then
    echo "[OK] unit cases"
    ok=$((ok+1))
  else
    echo "[KO] unit cases" >&2
    ko=$((ko+1))
  fi
  rm -f "$DIR/tests/unit_cases.c"
}

compare_output
compile_unit_tests
run_unit_tests

echo "OK=$ok KO=$ko"
[ "$ko" -eq 0 ]
