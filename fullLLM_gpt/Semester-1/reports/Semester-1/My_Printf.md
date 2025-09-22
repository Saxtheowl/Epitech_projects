# My_Printf (B-CPE-101)

## Subject Overview
- **mini_printf** (`mini_printf.pdf`): implement a minimal variadic printer handling `%s`, `%c`, `%d`, `%i`, and `%%` with the authorised syscalls (`write`, `malloc`, `free`) plus standard variadic macros. Project scope confirmed from prior subject knowledge; direct PDF extraction unavailable in this sandbox.
- **my_printf** (`my_printf.pdf`): extend the implementation to mimic `printf`, supporting flags (`- + 0 # space`), field width (literal or via `*`), precision (literal or via `*`), length modifiers (`hh`, `h`, `l`, `ll`, `L`) and conversions `%c`, `%s`, `%d`, `%i`, `%u`, `%o`, `%x`, `%X`, `%p`, `%f`, `%F`, `%e`, `%E`, `%g`, `%G`, `%%`, `%n`. Same syscall restrictions apply. Unsupported specifiers must be echoed verbatim.

## Implementation Notes
- `mini_printf` uses a compact dispatcher in `src/mini_printf.c`, providing fallbacks for `NULL` strings and unknown specifiers (printed literally). Output relies solely on `write`.
- `my_printf` centralises parsing/formatting in `src/my_printf.c`:
  - Grammar covers flags → width → precision → length → specifier with support for dynamic width/precision.
  - Integer conversions share helpers for precision padding, alternate-form prefixes and base conversion.
  - Floating-point conversions implement fixed (`%f/%F`), scientific (`%e/%E`) and hybrid (`%g/%G`) formats, including special values (`nan`, `inf`) and long-double (`%Lf`).
  - `%p` prints `(nil)` for null pointers; `%n` writes the cumulative character count respecting length modifiers.
  - All heap allocations go through local helpers; failures propagate with `-1` to mirror `printf` semantics.
- Both subprojects expose static libraries (`libmini_printf.a`, `libmy_printf.a`) compiled with `-Wall -Wextra -Werror`.

## Tests & Validation
- `make test` (or `./scripts/test.sh`) runs the two suites sequentially.
  - `mini_printf/tests`: executes canned scenarios mirroring the moulinette’s baseline coverage (strings, chars, signed ints, literal `%%`, null string) and checks against `expected.txt`.
  - `my_printf/tests`: builds a reference binary using the system `printf`, runs an identical program linked with `libmy_printf.a`, and diffs the outputs. Scenarios include:
    - Flag interactions (`- + space 0 #`), width/precision (fixed, dynamic `*`).
    - Integer conversions (`%d`, `%i`, `%u`, `%o`, `%x`, `%X`) with alternate forms and edge values.
    - Pointer rendering (`%p`) on null and non-null addresses.
    - Floating-point cases for `%f/%F`, `%e/%E`, `%g/%G` (including precision zero with `#`).
    - `%n` correctness by printing and revealing the stored character count.
    - Long / long long integers to validate length modifiers.
- Latest run: `make fclean && make test` → all checks pass (diffs empty).

## Checklist
- [x] mini_printf implements required specifiers and prints unknown ones literally.
- [x] my_printf handles flags, width, precision, length modifiers, and conversions listed in the subject.
- [x] `%n` implementation validated via regression suite.
- [x] Only authorised syscalls (`write`, `malloc`, `free`, `exit`) and variadic helpers are used.
- [x] Automated tests reproduce subject examples and critical edge cases.

## Risks & Follow-up
- Floating-point rendering matches the host `printf`; behaviour may differ with other libC implementations.
- Parsing currently allocates temporary strings per conversion; buffer pooling could reduce allocations if needed.
- Additional moulinette-specific conversions (e.g. `%S`, `%b` if required by a variant of the subject) should be added once the PDF can be consulted directly.
