# Firtree (B-CPE-100)

ASCII fir tree renderer printing a tree of given size to stdout.

## Build
- `make` builds the `firtree` binary.

## Run
- `./firtree <size>` where `<size>` is a positive integer.
- On invalid args or size <= 0, exits with code 84 and no output.

## Test
- `make test` compares output against the official oracle in `firtree.tgz` (if present) for sizes 1..5, and checks error case for 0.
