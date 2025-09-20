# Count_island

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `CountIsland.pdf`

## Subject Summary
- Page 2: Project in C compiled with `cc -o count_island *.c test_files/our_main.c -I include
  -L lib/my -lmy`; only `write(2)` is authorised. Delivery must contain clean sources,
  with headers under `include/` and no custom `main`.
- Page 3: Autograder builds the personal `libmy` via `lib/my/build.sh`; emphasises modular
  functions and automated tests.
- Page 4: Implement `int count_island(char **world);` that scans the map line by line,
  replaces each island of `X` characters with its discovery index starting at `0`, and
  returns the total number of islands (maximum of 10). The grid terminates with a
  `NULL` pointer.

## Requirements
- [MUST] Provide `int count_island(char **world);` that mutates the grid in place,
  numbering islands sequentially from `0` in scanning order and returning the total.
- [MUST] Preserve dots and avoid introducing extra characters; only neighbouring cells
  (up, down, left, right) belong to an island.
- [MUST] Leave the array untouched when empty/null and support up to 10 islands.
- [SHOULD] Split logic into focused helpers and rely exclusively on the allowed output
  primitives if printing is required (not needed for the core function).
- [OPTIONAL] Provide automated regression tests to validate labelling and counting.

## Implementation Notes
- `src/count_island.c` implements a recursive flood-fill (`flood_fill`) to replace each
  `X` island with the appropriate digit while tracking the overall count.
- Header now exposes the required prototype; all auxiliary helpers stay `static` to keep
  the public API minimal.
- Makefile links against the subject-supplied `main.o` purely for local execution; cards
  should remove it before hand-in.

## Test Strategy
- `make test` rebuilds the `count_island` binary, recreates the expected transformation
  for `map.txt` (independent Python implementation), and compiles a dedicated unit test
  harness that checks small crafted cases plus ensures the large map yields nine islands
  with no residual `X` characters.

## Evaluation Checklist
- [x] Builds with `make` and strict warning flags.
- [x] `count_island` returns the island count and mutates the map as specified.
- [x] Automated tests cover canonical examples and edge cases via `make test`.

## Risks / Follow-up
- Remove `main.o`, generated binaries, and temporary test artefacts before submission.
- Recursion depth is bounded by map size; for significantly larger maps an iterative
  flood-fill could prevent stack pressure if needed.
