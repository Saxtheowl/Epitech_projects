# Firtree

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `Tree.pdf`

## Subject Summary
- Page 2: Project in C compiled with `cc our_main.c our_my_putchar.c tree.c`; graders
  provide `main`/`my_putchar`, and only `write(2)` is authorised. Delivery must only
  contain the necessary sources (no binaries or helper mains).
- Page 2: Implement `void tree(int size);` that draws an ASCII fir tree; `size = 0`
  must simply print nothing. Required delivery file: `tree.c`.
- Page 2: Encourage small, single-responsibility functions and automated tests.
- Page 3: Official renderings are provided for sizes `1` and `5` (also available via the
  `firtree` oracle shipped alongside the subject).

## Requirements
- [MUST] Expose `void tree(int size);` producing the exact ASCII layout defined in the
  subject/oracle.
- [MUST] Use only the subject-provided output primitive (`my_putchar` → `write(2)`).
- [MUST] Treat `size = 0` as a valid no-op (no characters printed, exit success).
- [SHOULD] Keep delivery clean of binaries/objects, splitting the logic into focused
  helpers that respect the coding style.
- [OPTIONAL] Automate verification against the provided oracle to ensure regression-free
  output.

## Implementation Notes
- `src/tree.c` now forwards every character emission to `my_putchar`, keeping the
  implementation compliant with the "only write" requirement.
- `src/my_putchar.c` provides a local fallback (simple `write`) so the binary remains
  runnable outside the grading environment; remove if the delivery must only contain
  `tree.c`.
- `src/main.c` offers a lightweight argument parser (digits only, no `ctype.h`) for
  manual testing; graders will link their own main.
- Makefile compiles `src/main.c`, `src/tree.c`, and `src/my_putchar.c`; `make test`
  exercises the functional suite.

## Test Strategy
- `make test` extrait l’oracle officiel, compare les sorties pour les tailles `0` à `5`,
  et vérifie les erreurs (argument manquant, chaîne non numérique, entier négatif).

## Evaluation Checklist
- [x] Builds with `make` and strict warning flags.
- [x] Output of `tree(size)` matches the oracle for tested sizes.
- [x] `size = 0` produces no output and succeeds.
- [x] Automated tests documented and passing.

## Risks / Follow-up
- Remove helper binaries/mains and the extracted oracle directory before official
  submission, keeping only `tree.c` and required sources.
- Additional large-size visual checks can complement automated coverage.
