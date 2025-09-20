# Star (B-CPE-100)

Implementation of the Epitech "Star" exercise: render a symmetrical ASCII star of the
requested size to stdout using only the `write(2)` system call.

## Build

```sh
make
```

## Usage

```sh
./star <size>
```

- `<size>` is a non-negative integer. `0` produces no output, as required by the
  subject.
- On invalid input the program returns `84` without printing anything.

## Tests

```sh
make test
```

The test suite regenerates the official examples from `star_example.txt`, checks the
rendered star for sizes 1, 2, 4 and 5, validates the `size = 0` edge case and the
expected failures (missing argument, non numeric input, negative value).
