# rush-1-1

Recreates the first rush square: corners `o`, horizontal edges `-`, vertical edges
`|`, interior spaces. Invalid sizes (`x <= 0` or `y <= 0`) print `Invalid size` to
`stderr` and abort.

## Build

```sh
make
```

## Tests

```sh
make test
```

The harness compiles `rush.c` together with a local stub for `my_putchar`, runs the
reference cases from `rush1_bins.tgz`, and checks both stdout and stderr.
