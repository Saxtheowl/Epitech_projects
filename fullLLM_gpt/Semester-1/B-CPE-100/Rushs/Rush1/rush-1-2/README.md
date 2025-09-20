# rush-1-2

Variant with `/` `\` corners and `*` borders. Degenerate rows/columns collapse to
pure `*` as per the official oracle. Invalid sizes emit `Invalid size` on `stderr`.

## Build
```sh
make
```

## Tests
```sh
make test
```

The test script replays the subject binaries (`rush1-2`) for widths/heights 0..5 and
compares stdout/stderr with the local implementation.
