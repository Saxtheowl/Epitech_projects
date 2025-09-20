# Final Stumper (B-CPE-101)

## Subject recap
- **Binary**: `rush3` (see `Final_Stumper` brief).
- **Goal**: read the output of any `rush1-x` generator and print which rush pattern(s)
  match, along with detected width and height.
- **Output**: `[rush1-n] w h` for each match, ordered by pattern, separated by ` || `.
  Print `none` if no variant matches. Always end with `\n`.
- **Constraints**: only `read`, `write`, `malloc`, `free`; handle invalid inputs by
  returning `none`. Recommended to reuse existing `rush1` logic.

## Implementation
- `main` reads up to BUFF_SIZE (4096) bytes from stdin, null-terminates and delegates
  to `rush3`.
- `rush3` computes width/height, ensuring uniform line lengths and rejecting empty or
  malformed input.
- Pattern comparison uses generator functions mirroring the official rush outputs.
  Special cases (`width == 1` or `height == 1`) produce ambiguous results (patterns
  3/4/5) per reference behaviour.
- Matching is done character-by-character; each row may end with an optional trailing
  newline.
- Output is streamed using small helper functions (`my_putchar`, `my_putstr`,
  `my_putnbr_unsigned`).

## Tests
- `make test` / `./scripts/test.sh`:
  - Extracts subject-provided binaries (`rush1_bins.tgz`).
  - Pipes several dimension sets through our `rush3` implementation.
  - Checks ambiguous cases (e.g. `rush1-4 1 1`, `rush1-3 5 1`).
  - Verifies the fallback `none` on arbitrary input.
- Sample run: `Passed: 6  Failed: 0`.

## Checklist
- [x] Detects all five rush patterns with correct formatting.
- [x] Handles ambiguous outputs by listing all matching variants.
- [x] Validates and normalises input dimensions.
- [x] Respects syscall constraints (`read`, `write`, `malloc`, `free`).
- [x] Automated regression suite documented.

## Risks / follow-up
- Current buffer size (4096) matches subject hint but could be extended to handle
  bigger inputs if needed (basic loop already stops when the buffer fills).
- Input validation assumes printable ASCII; further checks could enforce this if
  desired.
