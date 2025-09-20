# rush-1-4

Corners alternate between `A` (left) and `C` (right) on both top and bottom rows;
all borders use `B`. Degenerate dimensions reduce to `B` only, and invalid sizes
emit `Invalid size`.

## Build
```sh
make
```

## Tests
```sh
make test
```

The automated suite compares stdout/stderr with the official `rush1-4` reference for
common dimensions and the error scenario.
