# rush-1-5

Mirrored corners: top row uses `A...C`, bottom row `C...A`, with `B` edges and a
space-filled interior. Invalid sizes print `Invalid size` on `stderr` and exit early.

## Build
```sh
make
```

## Tests
```sh
make test
```

`make test` runs the shared harness and asserts parity with the `rush1-5` oracle for
standard grids plus the invalid-parameter case.
