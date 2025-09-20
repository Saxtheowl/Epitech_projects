# WorkshopLib

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `WorkshopLib.pdf`

## Subject Summary
- Page 2: Optional workshop to stabilise the personal `libmy`; deliver `lib/libmy.a`
  compiled via a Makefile (with `re`, `clean`, `fclean` targets). Sources must sit inside
  `lib/my/`, header(s) under `include/`, and only `write(2)` may be used for output.
- Page 2: Library must expose the 30 canonical pool functions (`my_putchar`,
  `my_isneg`, …, `my_strncat`). The workshop expects iterative improvements through
  regular reviews.

## Requirements
- [MUST] Provide implementations for all 30 listed functions with the expected
  behaviour from the C pool exercises.
- [MUST] Build a static library named `lib/libmy.a` with the standard Makefile rules and
  no extraneous binaries/objects in delivery.
- [SHOULD] Keep the API in `include/my.h` and structure sources under `lib/my/`.
- [OPTIONAL] Supply automated tests exercising the most error-prone routines.

## Implementation Notes
- Each function lives in its own translation unit in `lib/my/`. Printing helpers rely
  exclusively on `write(2)` (`my_putchar`) and are reused by `my_put_nbr`, `my_putstr`,
  `my_showstr`, and `my_showmem`.
- Algorithmic helpers (`my_getnbr`, `my_sort_int_array`, `my_find_prime_sup`, etc.) follow
  the reference pool specifications, including overflow handling for `my_getnbr` and the
  hexdump formatting for `my_showmem`.
- The top-level Makefile archives the objects into `lib/libmy.a` and wires `make test`
  to the local regression script.

## Test Strategy
- `make test` builds `lib/libmy.a`, compiles a lightweight C harness (`tests/test.c`),
  links it against the library, and executes targeted assertions over string
  manipulation, classification predicates, numeric routines, and the printable helpers.

## Evaluation Checklist
- [x] Static library produced (`lib/libmy.a`).
- [x] All 30 required symbols implemented and prototyped in `include/my.h`.
- [x] Makefile exposes `all`, `clean`, `fclean`, `re`, `test`.
- [x] Automated regression comes with `make test`.

## Risks / Follow-up
- Printing tests rely on visual inspection of stdout; expand the harness if stricter
  validation is needed.
- The recursive flood-fill and recursion-based functions assume moderate input sizes;
  refactor to iterative versions if stack limits become a concern.
