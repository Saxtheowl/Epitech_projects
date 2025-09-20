# BSQ (B-CPE-110)

Finds the largest possible square in a grid while avoiding obstacles. The map is
read from a file where the first line gives the number of rows, followed by rows of
`.` (empty) and `o` (obstacles).

## Build

```sh
make
```

Produces the `bsq` binary. Additional targets: `clean`, `fclean`, `re`, `test`.

## Usage

```sh
./bsq maps/example_map
```

On success, the program prints the map with the largest square filled using `x`.
If the map is invalid the program prints nothing and exits with status 84.

## Implementation notes

- `read_entire_file` loads the file using only the allowed system calls
  (`open`, `read`, `close`, `malloc`, `free`).
- `parse_map` validates dimensions, character set and uniform line length.
- Dynamic programming (`solve_bsq`) computes square sizes in O(rows × cols).
- `mark_square` replaces the winning square with `x` before the map is printed.

## Tests

```sh
make test          # builds and runs regression scenarios
./scripts/test.sh  # convenience wrapper
```

`tests/test.sh` generates sample maps and compares program output to checkpoints,
covering rectangular cases, 1×N/ N×1 edge cases, and obstacle configurations.
