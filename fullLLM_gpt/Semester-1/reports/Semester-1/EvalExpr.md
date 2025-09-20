# EvalExpr (B-CPE-101)

## Subject recap
- **Prototype**: `int eval_expr(char const *str);` (EvalExpr.pdf, p.2).
- **Goal**: evaluate an arithmetic expression comprised of integers, parentheses,
  and operators `+ - * / %` with correct precedence and unary handling.
- **Constraints**: use only `write`, `malloc`, `free` (EvalExpr.pdf, p.2). The provided
  `main.c` prints the result and returns 84 when argument count ≠ 2. Inputs are
  guaranteed valid (no syntax errors or division by zero).

## Implementation
- Recursive-descent parser splitting grammar into `factor` (numbers, parenthesis,
  unary signs), `term` (`*`, `/`, `%`), and `expression` (`+`, `-`).
- Whitespace skipped manually (no `ctype.h`).
- Numbers parsed into signed 64-bit accumulator; final result cast back to `int`.
- Output helpers (`my_putchar`, `my_put_nbr`) rely solely on `write`.

## Verification
- `make test` / `./scripts/test.sh` compile the project and run regression cases
  covering precedence, nested parentheses, unary adoption, modulo, and spacing.
- Example output:
  - `(3+2)*5` → `25`
  - `--++10` → `10`
  - `  12 * ( -3 + 5 )` → `24`
- Summary: `Passed: 11  Failed: 0`.

## Checklist
- [x] Parser handles unary signs and parentheses.
- [x] Operator precedence `/` `%` `*` before `+` `-`.
- [x] Respects syscall constraints (no libC helpers).
- [x] Tests automated via Makefile target + wrapper.

## Risks / follow-up
- Intermediate arithmetic uses `long long`; extremely large values beyond signed
  64-bit range would overflow (acceptable given subject expectations).
- Additional corner cases (e.g., deeply nested expressions) can be added to the
  test suite as needed.
