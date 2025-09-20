# BSQ (B-CPE-110)

## Subject recap
- **Binary**: `bsq` (`BSQ.pdf`).
- Read a map file: first line contains the number of rows; subsequent lines use `.`
  for empty cells and `o` for obstacles.
- Find the largest square of `.` and replace it with `x`. If multiple solutions
  exist, choose the highest; if still tied, choose the leftmost.
- Allowed syscalls: `open`, `read`, `close`, `write`, `malloc`, `free`, `stat`.
- On error, write an error message to stderr and exit 84 (this implementation
  returns 84 without additional output for invalid input).

## Implementation summary
- `read_entire_file` allocates a buffer dynamically (doubling strategy) using only
  permitted syscalls; contents are null-terminated for easier processing.
- `parse_map` validates the header, character set, row lengths, and total number of
  lines, then fills a contiguous grid buffer.
- `solve_bsq` employs dynamic programming to compute the maximal square ending at
  each cell; ties naturally preserve the first (top-left) occurrence.
- `mark_square` overwrites the winning square with `x` prior to printing.
- `write_all` prints each row atomically, preserving the original structure.

## Testing
- `make test` (or `./scripts/test.sh`) generates several deterministic maps and
  compares the program output to the expected annotated maps:
  - 5×6 mixed map with obstacles.
  - 1×1, 1×N, and N×1 edge cases.
- All scenarios currently report `Passed: 4  Failed: 0`.

## Risks / follow-up
- Current tests cover representative scenarios; adding more heterogeneous grids
  would increase confidence.
- Input larger than 4kB is supported thanks to the doubling buffer, but extremely
  large maps may still stress available memory; this is acceptable for project
  constraints.
