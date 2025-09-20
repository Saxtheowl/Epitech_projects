# Count_island (B-CPE-100)

Implementation of the Epitech "Count Island" exercise: walk a rectangular map of `.` and
`X`, label each contiguous block of `X` with its discovery index (starting at `0`) and
return the number of islands found.

## Build

```sh
make
```

The provided `Makefile` links the delivered `count_island.c` with the subject `main.o`
for convenient local runs. Drop `main.o` before submitting, as the graders will supply
their own entry point.

## Usage

```sh
./count_island <map_file>
```

The example `map.txt` follows the subject convention: the first line gives the map
height, followed by that many rows composed of `.` and `X`.

## Tests

```sh
make test
```

The test suite:
- rebuilds the reference transformation for `map.txt` and diffs it against the program
  output;
- compiles a dedicated unit binary that exercises small edge cases and asserts the
  return value / labelling contract of `count_island`.
