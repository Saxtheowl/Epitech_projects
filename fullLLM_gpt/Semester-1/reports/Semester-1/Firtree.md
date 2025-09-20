# Firtree (B-CPE-100)

## Subject recap
- **Goal**: render a scalable ASCII fir tree according to `Tree.pdf` (pp.2-3) using only the grader-provided `my_putchar`/`write`.
- **Prototype**: `void tree(int size);` (Tree.pdf, p.2).
- **Constraints**: no delivered `main`, only `write`, single `tree.c` source checked out by the grader, compiled together with their `main.c` and `my_putchar.c` (Tree.pdf, p.2). Nothing must be printed for size `0`.

## Requirements
- **MUST** draw the foliage block-by-block, widening each line by two stars and applying the official shrink rule between blocks.
- **MUST** keep the tree horizontally centred using leading spaces.
- **MUST** build a trunk of width `size` (odd) or `size + 1` (even), height `size`, centred under the foliage (from the public subject binary examples, p.3).
- **MUST** rely exclusively on `write` (via `put_char` helper) and avoid global state.
- **SHOULD** provide automation to compare outputs with the subject oracle and validate error cases.

## Implementation
- `src/tree.c` implements a helper `compute_base_width` to know the total base width, then iterates block-by-block while applying the shrink deltas described in the Pool guidelines. Recursive `flood` is not required; everything is iterative.
- The trunk width adapts to even/odd sizes and is centred with the same spacing logic as the foliage.
- An auxiliary `src/main.c` (not delivered) parses CLI arguments, rejects invalid input (missing arg, non-number, negative) by returning `84`, and calls `tree`.

## Build & layout
- `Makefile` builds `firtree` from `src/main.c` + `src/tree.c`; standard targets (`all`, `clean`, `fclean`, `re`, `test`).
- Public header `include/tree.h` exposes the prototype expected by the grader.

## Tests
- `make test` (or `scripts/test.sh`) runs `tests/test.sh`, which:
  1. Extracts the official oracle binary from `firtree.tgz` and compares outputs for sizes 0 through 5.
  2. Checks error handling (missing argument, non-digit, negative input) expects exit code 84 and no output.
- Sample run: nine checks, all `[OK]`, summary `OK=9 KO=0`.

## Checklist
- [x] `tree(int size)` implemented and confined to `src/tree.c`.
- [x] No delivered `main`, only helper for local validation.
- [x] Uses only `write` via `put_char`.
- [x] Automated regression suite aligned with subject oracle.
- [x] README documents build/run/test steps.

## Risks / follow-up
- Oracle archive `firtree.tgz` is required for golden-output comparisons; if unavailable, the script falls back to smoke tests. Ensure the archive remains version-aligned with the subject.
- The shrink rule relies on fixed constants from the Pool guidelines; any future subject change would require re-synchronising `compute_base_width`.
