# Star (B-CPE-100)

ASCII star renderer that prints a star of given size to stdout.

## Build

- `make` builds the `star` binary.
- `make clean | fclean | re` for cleanup.

## Run

- `./star <size>` where `<size>` is a positive integer.
- Error cases (invalid args or size <= 0) return exit code 84 and no output.

## Test

- `make test` runs functional tests against the examples from `star_example.txt` (sizes 1, 2, 4, 5) and checks error handling for 0.

