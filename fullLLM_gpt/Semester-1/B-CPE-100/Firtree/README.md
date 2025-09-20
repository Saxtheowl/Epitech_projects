# Firtree (B-CPE-100)

Implementation of the Epitech "Fir Tree" exercise: render a scalable ASCII fir tree of the
requested size using only the `write(2)` system call (via the grader-provided `my_putchar`).

## Build

```sh
make
```

## Usage

```sh
./firtree <size>
```

- `<size>` is a non-negative integer. `0` is valid and produces no output, as required by
  the subject.
- Invalid inputs return exit code `84` without printing anything.

## Tests

```sh
make test
```

The test suite expands the official oracle shipped in `firtree.tgz`, compares the rendered
output for sizes 0 to 5, and checks representative error cases (missing argument,
non-numeric, negative input).
