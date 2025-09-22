# Bistro-matic (B-CPE-101)

## Subject recap
- **Goal**: implement an arbitrary-base arbitrary-precision calculator handling the five
  integer operators (`+`, `-`, `*`, `/`, `%`) plus parentheses and unary signs
  (`Bistro-matic.pdf`, pp.2-3).
- **Interface**: `./calc base operators size_read` then read `size_read` chars from
  `stdin`, evaluate, and print the result (`-h` usage example on p.2).
- **Constraints**:
  - Only `read`, `write`, `malloc`, `free`, `exit` allowed (p.3).
  - Errors must print `syntax error` or `error` on stderr and exit with code 84.
  - Support custom bases/operators (7-symbol operator string ordered `() +-*/%`).
  - Refuse invalid base/operator definitions (duplicate symbols) and zero/negative
    `size_read`.

## Implementation overview
- Recursive-descent parser with precedence levels (expr → term → factor) manages unary
  operators and parentheses. Any unexpected token triggers `syntax error`.
- Numbers are parsed using the provided base; digits are converted to an internal
  big-integer representation (base 10, little endian).
- Big integers support addition, subtraction, multiplication, long division, and modulo.
  Division/modulo detect zero divisors and emit `error` as required.
- Final results are converted back to the provided base; negative values are prefixed
  with the operator string’s subtraction symbol.
- Memory utilities (`my_malloc`, `my_strndup`, etc.) wrap forbidden libC helpers and
  call `fatal_error(ERROR_MSG)` on allocation failure.

## Tests
- `make test` (or `./scripts/test.sh`) runs `tests/test.sh`, covering:
  - Subject sample cases (default base, custom operators/base, nested parentheses).
  - Unary operator chains, large expressions, invalid `size_read` (0) rejection.
  - Syntax error scenario (`----++-6(12)`).
  - Division-by-zero pathway (ensuring `error` on stderr).
- All cases currently report `OK`.

## Checklist
- [x] Build system (`Makefile`) with `all`, `clean`, `fclean`, `re`, `test`.
- [x] Parser enforces syntax and operator precedence.
- [x] Arbitrary-precision engine handles big integers and base conversion.
- [x] Error handling per specification (stderr + exit 84) including invalid
      `size_read`.
- [x] Automated regression suite documented and reproducible.

## Risks & follow-up
- Division/modulo implement classic long division; performance is acceptable for Pool
  workloads but not optimized for extremely large inputs.
- Error reporting stops at the first encountered issue; further diagnostics (position of
  syntax errors) could aid debugging but are out of scope for the subject.
- Additional tests (especially edge cases from the moulinette test list) can be added to
  `tests/test.sh` if required.
