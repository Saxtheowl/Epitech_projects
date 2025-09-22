#!/usr/bin/env python3
"""Reference BSQ solver used by tests to compute expected output from a map file."""
from __future__ import annotations
import sys
from pathlib import Path


def parse_map(path: Path):
    data = path.read_text()
    if not data:
        raise ValueError("empty file")
    lines = data.splitlines()
    if not lines:
        raise ValueError("missing header")
    try:
        rows = int(lines[0])
    except ValueError as exc:
        raise ValueError("invalid row count") from exc
    if rows <= 0:
        raise ValueError("row count must be positive")
    body = lines[1:]
    if len(body) != rows:
        raise ValueError("row count mismatch")
    cols = None
    grid = []
    for line in body:
        if cols is None:
            cols = len(line)
            if cols <= 0:
                raise ValueError("empty row")
        if len(line) != cols:
            raise ValueError("non uniform row length")
        for ch in line:
            if ch not in {'.', 'o'}:
                raise ValueError("invalid character")
        grid.append(list(line))
    return rows, cols, grid


def solve(rows: int, cols: int, grid):
    dp = [[0] * cols for _ in range(rows)]
    best_size = 0
    best_x = best_y = 0
    for y in range(rows):
        for x in range(cols):
            if grid[y][x] == 'o':
                dp[y][x] = 0
                continue
            if y == 0 or x == 0:
                dp[y][x] = 1
            else:
                dp[y][x] = 1 + min(dp[y - 1][x], dp[y][x - 1], dp[y - 1][x - 1])
            if dp[y][x] > best_size:
                best_size = dp[y][x]
                best_x = x - best_size + 1
                best_y = y - best_size + 1
    for dy in range(best_size):
        for dx in range(best_size):
            grid[best_y + dy][best_x + dx] = 'x'
    return grid


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("Usage: solve_ref.py <map>", file=sys.stderr)
        return 84
    path = Path(argv[1])
    rows, cols, grid = parse_map(path)
    solve(rows, cols, grid)
    for row in grid:
        print(''.join(row))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
