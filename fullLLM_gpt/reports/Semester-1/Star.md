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
- `src/star.c` route désormais chaque caractère vers `my_putchar` (aucun `write`
  direct), tout en conservant la géométrie de l'étoile.
- `src/my_putchar.c` fournit une implémentation locale minimaliste (simple `write`) pour
  pouvoir lancer le binaire sans les fichiers du correcteur.
- `src/main.c` reste un exécutable de confort, avec un parseur maison (digits uniquement).
- Makefile compile `main.c`, `star.c`, `my_putchar.c` et expose les cibles habituelles.

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
