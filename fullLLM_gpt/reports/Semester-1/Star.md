# Star

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `B-CPE-100_Star.pdf`

## Subject Summary
- Page 2: Project must be written in C, compiled with `cc -o star *.c`; graders add their
  own `main.c` and `my_putchar.c`. Only `write(2)` is authorised and neither helper file
  should be delivered.
- Page 2: Implement `void star(unsigned int size);` that prints an ASCII star; size `0`
  is valid and must produce no output.
- Page 3: Example renderings are provided for sizes `1`, `2`, `4`, and `5` (also in
  `star_example.txt`).

## Requirements
- [MUST] Expose `void star(unsigned int size);` matching the provided ASCII layout.
- [MUST] Use only the allowed output primitive (`write(2)` / subject `my_putchar`).
- [MUST] Treat `size = 0` as a no-op instead of an error.
- [SHOULD] Ship clean sources without binaries, objects, or helper mains in delivery.
- [OPTIONAL] Offer local tooling (Makefile/tests) for validation.

## Implementation Notes
- `src/star.c` reconstructs the geometric sections (top cone, horizontal bars, arms)
  using simple loops and the `write(2)` helper; no other libc calls are required.
- `src/main.c` is kept only as a local runner to exercise the function.
- Makefile now follows the usual `make`, `clean`, `fclean`, `re`, `test` contract and
  compiles with `-Wall -Wextra -Werror`.

## Test Strategy
- `make test` (wrapper in `tests/test.sh`) regenerates expectations from the official
  examples, validates rendering for sizes `0`, `1`, `2`, `4`, `5`, and checks three error
  scenarios (missing argument, non-digit, negative input).

## Evaluation Checklist
- [x] Builds successfully via `make`.
- [x] Output relies solely on `write(2)` and matches the subject examples.
- [x] Edge case `size = 0` prints nothing.
- [x] Automated tests pass with `make test`.

## Risks / Follow-up
- Remove the helper `main` (and any generated artifacts) before official hand-in, per
  subject rules.
- Only a subset of sizes is covered automatically; manual inspection for additional
  values is still advised.
