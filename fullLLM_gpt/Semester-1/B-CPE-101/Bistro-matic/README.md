# Bistro-matic (B-CPE-101)

Arbitrary-precision calculator handling custom bases and operator symbols. Supports
`+`, `-`, unary `+/-`, `*`, `/`, `%`, and parentheses, all evaluated with the Pool
rules (no libC besides `read`, `write`, `malloc`, `free`, `exit`).

## Contraintes du sujet
- `MUST` n’utiliser que `read`, `write`, `malloc`, `free`, `exit` (Bistro-matic.pdf p.3).
- `MUST` accepter une base personnalisée (≥ 2 symboles, tous distincts) et une table
  d’opérateurs de 7 caractères ordonnés `() +-*/%`.
- `MUST` lire exactement `size_read` caractères sur stdin et retourner `syntax error`
  ou `error` sur stderr (code 84) selon la nature de l’échec.
- `SHOULD` refuser toute duplication de symbole base/opérateur et trim les espaces
  selon les règles du sujet.
- `KNOWN LIMIT` calculs sur entiers uniquement (pas de décimales) mais précision
  arbitraire via big integers.

## Build

```sh
make
```

Produces the `calc` binary.

## Usage

```sh
echo "3+6" | ./calc 0123456789 '()+-*/%' 3
```

Parameters:
- `base`: characters representing digits of the numeral system (≥ 2 symbols, unique).
- `operators`: seven characters defining `(`, `)`, `+`, `-`, `*`, `/`, `%` in that order.
- `size_read`: number of characters to read from stdin.

On syntax errors the program prints `syntax error` to `stderr` and exits with 84; on
other runtime errors (e.g., division by zero) it prints `error` to `stderr` and exits 84.

## Tests

```sh
make test         # run non-regression suite
./scripts/test.sh # convenience wrapper
```

The test suite exercises:
- Reference examples from the subject (default and custom bases/operators).
- Nested parentheses and multiple unary operators.
- Syntax error propagation.
- Division by zero handling.

## Code layout

- `main.c`: argument parsing and I/O plumbing provided by the subject (rewired to use
  the local helpers).
- `include/`: headers for the big integer engine, parser, and utilities.
- `src/utils.c`: minimal replacements for forbidden libC helpers (`my_strlen`,
  `my_putstr`, `my_atoi`, etc.).
- `src/bigint.c`: big integer implementation working in base 10 internally with
  conversion to arbitrary bases.
- `src/parser.c`: recursive-descent parser with operator precedence and unary support.
- `src/eval_expr.c`: glue between parser and evaluator, formatting the final result.

## Notes

- The evaluator uses a shunting-like recursive grammar, applying operations as soon as
  precedence allows, which keeps memory usage bounded.
- Big integer division/modulo implement long division; intermediate buffers dynamically
  resize via custom helpers (no `realloc`).
- Error helpers ensure every fatal condition prints the correct message to `stderr`
  before exiting with code 84.
