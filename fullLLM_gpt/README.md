# EvalExpr (B-CPE-101)

Evaluates a single arithmetic expression passed as CLI argument and prints the result
followed by a newline.

## Build

```sh
make
```

Targets: `clean`, `fclean`, `re`, `test`.

## Usage

```sh
./eval_expr "(3+2)*5"   # → 25
```

- Only one argument is expected. Any other arity returns 84 without output.
- Expressions may contain spaces, parentheses, unary `+`/`-`, and the operators
  `+`, `-`, `*`, `/`, `%`. Inputs are guaranteed valid (per subject).

## Implementation

- Recursive-descent parser with three precedence levels (expression → term →
  factor).
- Factors handle nested parentheses and unlimited unary signs.
- Numbers are parsed as long longs, the final result is cast to `int`.
- No libC helpers are used; only `write`, `malloc`, `free` (plus project-local
  helpers).

## Tests

```sh
make test          # compile + run regression suite
./scripts/test.sh  # convenience wrapper
```

The suite covers operator precedence, unary chains, nested parentheses, spacing,
modulo, and division.
