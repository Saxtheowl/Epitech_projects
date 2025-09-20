# Count_island (B-CPE-100)

## Subject recap
- **Goal**: flood-fill each island of contiguous `X` cells in a rectangular grid, replacing them with their discovery index (starting at `0`) and return the number of islands (`CountIsland.pdf`, pp.2-4).
- **Inputs**: a `char **world` where each row is a NUL-terminated string of `.` or `X`, and the last pointer is `NULL` (`CountIsland.pdf`, p.4).
- **Constraints**: delivery in pure C, only `write` as system call, build with `lib/my`, no delivered `main`, all sources compile with `*.c`, max 10 islands (`CountIsland.pdf`, pp.2-4).

## Requirements
- **MUST** expose `int count_island(char **world);` performing in-place labelling and returning the island count.
- **MUST** scan linearly (top-to-bottom, left-to-right) and assign incremental digits starting at `0`.
- **MUST** treat horizontal/vertical adjacency as connectivity; diagonals are separate islands.
- **MUST** keep `.` untouched and ensure no `X` remains after processing.
- **MUST** respect grading build pipeline (sources under `src/`, headers under `include/`, no `main`).
- **SHOULD** provide reusable helpers (string length, flood-fill) with minimal responsibilities.
- **SHOULD** ship automated tests covering edge cases and the provided reference map.
- **OPTIONAL** extend beyond 10 islands (not required by the subject).

## Implementation notes
- Core algorithm: DFS flood-fill (`flood_fill`) marking each discovered `X` with the current digit, relying on a local `my_strlen` helper for row bounds.
- Two-pass structure: iterate rows/columns, trigger flood-fill when an `X` is found, increment island counter afterwards. Digits are generated as `'0' + islands` (valid for subject’s ≤10 islands guarantee).
- Defensive checks guard against `NULL` inputs and empty grids, returning `0` without modification.

## Build & layout
- `Makefile` builds `count_island` by linking `src/count_island.c` with the supplied `main.o` (excluded from delivery). Targets: `make`, `make clean`, `make fclean`, `make re`, `make test`.
- Public headers in `include/`, sources in `src/`, auxiliary assets in `map.txt`, `tests/`, `scripts/`.

## Tests
- `make test` (or `scripts/test.sh`) executes:
  1. A Python harness that replicates the expected transformation for `map.txt` and diffs the program output.
  2. A generated C unit binary covering single island, diagonal separation, all-`.` grids, and a large-map regression (validating numbering and absence of raw `X`).
- Sample run: `[OK] map transformation`, `[OK] unit cases`, summary `OK=2 KO=0`.

## Checklist for grading
- [x] `count_island` implemented per specification.
- [x] No delivered `main`; only `write` used from the standard library.
- [x] Sources compile with `gcc *.c` alongside `libmy`.
- [x] Automated tests reproducible via `make test`.
- [x] README summarises build/run/test instructions.

## Risks / follow-up
- Subject expects integration with `lib/my` (from Pool Day07); local Makefile links directly for convenience. Ensure `lib/my` is present when packaging for grading.
- Current numbering uses ASCII digits; if >10 islands ever required, implementation would need multi-character labels (out of scope here).
