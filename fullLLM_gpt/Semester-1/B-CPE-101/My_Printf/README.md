# My_Printf (B-CPE-101)

Implementation of both training steps:

- **mini_printf** – limited `%s`, `%c`, `%d`, `%i`, `%%` handling, focused on `va_list` usage.
- **my_printf** – full-featured replacement for `printf` (C99): flags (`- + 0 # space`),
  field width, precision (including `*`), length modifiers (`hh`, `h`, `l`, `ll`, `L`),
  and conversions `%c`, `%s`, `%d`, `%i`, `%u`, `%o`, `%x`, `%X`, `%p`, `%f`, `%F`, `%e`, `%E`,
  `%g`, `%G`, `%%`, `%n`.

## Layout

```
mini_printf/  # minimal version, builds libmini_printf.a
my_printf/    # full implementation, builds libmy_printf.a
scripts/      # project-level test runner
```

## Build

```sh
make          # builds both libraries via sub-Makefiles
make clean    # removes objects/binaries
make fclean   # clean + removes libraries/binaries
make re       # full rebuild
```

Each subdirectory exposes the same targets.

## Tests

```sh
./scripts/test.sh  # runs mini_printf + my_printf test suites
```

- `mini_printf/tests/test.sh` compares the output against an expected file covering
  `%s`, `%c`, `%d`, `%%`.
- `my_printf/tests/test.sh` builds a reference program using the system `printf`,
  runs both implementations on a broad sample (flags, width/precision, dynamic
  `*`, integer bases, pointers, floating-point formats), and diffs the outputs.

The my_printf tests also ensure compatible behaviour for special cases such as
NULL strings (`(null)`) and `%p` on `NULL` (`(nil)`).

## Notes

- No buffer handling is implemented (as allowed by the subject). All writes use
  `write(2)` directly.
- Only the permitted libC functions are used: `write`, `malloc`, `free`,
  `va_start`, `va_arg`, `va_end`, `va_copy`.
