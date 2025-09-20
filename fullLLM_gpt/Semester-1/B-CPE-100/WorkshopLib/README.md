# WorkshopLib (B-CPE-100)

Static implementation of the Epitech `libmy` workshop: the `lib/libmy.a` archive exposes
all 30 mandatory helper routines (printing, string utilities, math helpers, and memory
inspectors).

## Layout

- `include/my.h`: public header with the full API.
- `lib/my/*.c`: one source file per required function.
- `tests/test.c`: regression suite validating representative behaviours across the API.

## Build

```sh
make
```

This produces `lib/libmy.a`. All objects live alongside their source files under
`lib/my/` for easy delivery.

## Tests

```sh
make test         # build + run the regression harness
./scripts/test.sh # convenience wrapper
```

The harness links against the freshly built library, exercises arithmetic/string helpers,
and asserts the expected results. A concise `[OK] libmy unit tests` summary is printed on
success.

## Cleaning

```sh
make clean   # drop objects and transient test binary
make fclean  # clean + remove the static library
make re      # rebuild from scratch
```

## Notes

- Only the `write(2)` system call is used inside the output helpers, matching Pool
  constraints.
- Remove generated artefacts (`lib/libmy.a`, `tests/unit`) before submitting to the
  grader.
