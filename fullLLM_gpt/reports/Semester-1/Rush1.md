# Rush1

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `Rush1.pdf`

## Subject Summary
- Page 2–3: Implement `void rush(int x, int y);` using only `my_putchar` (linked from
  the grader). Invalid input must print `Invalid size\n` to `stderr` and return.
- Page 4–13: Five square variants (`rush-1-1` … `rush-1-5`) specifying distinct corner
  and edge characters; behaviour is detailed through sample outputs (`5x3`, `5x1`,
  `1x1`, `1x5`, `4x4`).
- Oracle binaries (`rush1-1` … `rush1-5`) are provided for self-validation.

## Requirements
- [MUST] Provide `rush(int x, int y);` for each variant with exact character layouts
  and newline handling.
- [MUST] Reject non-positive dimensions by writing `Invalid size\n` to `stderr` and
  producing no further output.
- [SHOULD] Factor the implementation to avoid copy/paste bugs while preserving the
  allowed API (no custom `main`, only `write(2)` via `my_putchar`).
- [OPTIONAL] Supply automated tests comparing outputs with the reference binaries.

## Implementation Notes
- Each subdirectory `rush-1-n/` exposes a standalone `rush.c` with a small helper that
  picks the correct tile per coordinate, including special handling for single-row or
  single-column grids so outputs match the official reference.
- Makefiles build the object file only (expecting the grader’s `main`) and wire
  `make test` to the local regression script.
- Error messaging is consistent across variants and uses `write(2, ...)` directly.

## Test Strategy
- For each variant, `tests/test.sh` compiles a temporary harness (`rush.c` + stub
  `my_putchar`), executes the same scenarios as in the PDF, and diffs stdout/stderr
  against the oracle binary extracted from `rush1_bins.tgz`.

## Evaluation Checklist
- [x] `rush` implemented for variants 1–5.
- [x] Invalid dimensions produce the mandated error message on `stderr`.
- [x] Automated comparison with official binaries available via `make test`.

## Risks / Follow-up
- Recursion not involved; stack usage is minimal. For very large grids, execution time
  scales linearly with area (expected). No further risks identified.
