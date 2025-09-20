# rush-1-3

Corner set `{A, C}` with `B` edges (classic rush #3). Single-row/column cases return
only `B` characters; invalid parameters trigger `Invalid size` on `stderr`.

## Build
```sh
make
```

## Tests
```sh
make test
```

The harness validates the canonical grids and the error case against the bundled
`rush1-3` oracle.
