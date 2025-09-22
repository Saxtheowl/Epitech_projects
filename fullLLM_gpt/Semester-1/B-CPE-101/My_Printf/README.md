# My_Printf (B-CPE-101)

Implementation of both training steps defined in the subject PDFs:

- **mini_printf** – bootstrap exercise supporting `%s`, `%c`, `%d`, `%i`, `%%` to practise
  variadic arguments (`mini_printf.pdf`).
- **my_printf** – extended `printf` reimplementation with flags, width/precision and a
  broad conversion set (`my_printf.pdf`).

## Layout

```
mini_printf/  # minimal version, builds libmini_printf.a
my_printf/    # full implementation, builds libmy_printf.a
scripts/      # project-level test runner
```

## Build

```sh
make          # builds libmini_printf.a and libmy_printf.a
make clean    # removes objects/test binaries for both subprojects
make fclean   # clean + remove libraries
make re       # full rebuild
```

Each subdirectory exposes the same targets (`all`, `clean`, `fclean`, `re`, `test`).

## Tests

```sh
./scripts/test.sh  # rebuilds + runs the mini_printf and my_printf suites
```

- `mini_printf` regression: compares stdout against the expected transcript (strings,
  chars, signed ints, literal `%%`, NULL string).
- `my_printf` regression: builds a reference binary using system `printf`, executes the
  same scenarios (flags, width, precision, dynamic `*`, integer bases, `%p`, floating
  formats, `%n`) and diffs the outputs.

The my_printf tests also ensure compatible behaviour for special cases such as
NULL strings (`(null)`) and `%p` on `NULL` (`(nil)`).

## Notes

- Only the permitted C/POSIX calls are used across both projects: `write`, `malloc`,
  `free`, `exit`, and the variadic macros (`va_*`).
- `my_printf` supports flags (`- + 0 # space`), width (fixed & dynamic), precision
  (fixed & dynamic), length modifiers (`hh`, `h`, `l`, `ll`, `L`) and conversions
  `%c`, `%s`, `%d`, `%i`, `%u`, `%o`, `%x`, `%X`, `%p`, `%f`, `%F`, `%e`, `%E`, `%g`, `%G`,
  `%%`, `%n`. Unsupported specifiers are printed verbatim (subject behaviour when
  outside scope).
