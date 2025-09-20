# B-BOO-101 — Bootcamp Phoenix

## Subject recap

- **Day01** — basic display helpers and parsing (`Bootcamp_Phoenix/Day01/day01.pdf`, pp.2-6)
- **Day02** — recursion and strings + Criterion unit tests (`Day02/day02.pdf`, pp.2-7)
- **Day03** — static library `libphoenix`, concat helpers, argument printers (`Day03/day03.pdf`, pp.2-5)
- **Day04** — dynamic allocation, string splitting, parameter structures (`Day04/day04.pdf`, pp.2-6)
- **Day05** — `star` program driven by a size argument, error handling on stdout/stderr (`Day05/day05.pdf`, pp.2-3 + `star_examples.txt`)

## Requirements snapshot

- **MUST** implement every function listed in the five PDFs with the specified prototypes and constraints (only `my_putchar` / `write` / `malloc` / `free` where stated).
- **MUST** build a static library `libphoenix.a` exposing the required helpers and ship the public header `includes/phoenix.h` (Day03).
- **MUST** provide individual Makefiles for `task04`, `task05`, `Day04/task02`, `Day05`, each rebuilding the phoenix library before linking.
- **MUST** produce automated tests for `my_strcpy` and `my_strncmp` with ≥60% line coverage & ≥40% branch coverage (Day02 p.7).
- **MUST** ensure `star` validates arguments, prints usage on stderr for invalid inputs, and reproduces the reference ASCII art (Day05).
- **SHOULD** keep deliverables free of useless files (`.o`, binaries) and follow the prohibition about shipping `my_putchar` except inside the library.
- **OPTIONAL** bonuses and additional helpers may live under a `bonus/` directory (not needed here).

## Architecture & implementation

- Central header `includes/phoenix.h` aggregates every prototype plus the shared `info_param` struct. All source files across the five days include it to stay consistent.
- `lib/phoenix/Makefile` builds `libphoenix.a` from Day01/Day02 sources + `my_putchar`. Build artefacts are isolated under `lib/phoenix/build/` to keep day folders clean.
- Day03 programs (`task04`, `task05`) and later deliverables link against the library and reuse the same helpers (e.g. `show_string`, `my_strncmp`).
- Day04 implements memory-oriented helpers (`duplicate_string`, `split_string`, `parameters_to_array`, `show_parameters_array`). A local `main.c` is provided in `task02/` so the Makefile remains buildable without the grader harness.
- Day05’s `star` adopts a function-per-phase layout (top cone, horizontal bars, diamond core, bottom cone) and prints usage to stderr (`write(2, ...)`) with exit code 84 on invalid parameters.
- Automated tests live under `tests/`. Because Criterion is unavailable on the target machine, a lightweight compatibility harness (`tests/framework.[ch]`) reproduces the essential API (`Test`, `cr_assert_*`, `cr_redirect_stdout`) and still drives `gcov` instrumentation. Behaviour matches the original intent while keeping the workflow self-contained.

## Verification

Commands:

```bash
make            # builds library + executables
make test       # runs unit tests + star scenario checks
./scripts/test.sh  # convenience wrapper
```

Key results:

- 33 automated unit scenarios covering Day01–Day04 helpers (stdout expectations + edge cases).
- `my_strcpy.c` — 100% line coverage, 100% branch coverage (gcov).
- `my_strncmp.c` — 93.33% line coverage, 83.33% branch coverage (gcov).
- `tests/test_star.py` validates the `star` output for sizes 0,1,2,4,5 (matching `star_examples.txt`) and argument error handling.

## Risks & follow-up

- Criterion is emulated via the custom harness; the interface matches the subject, but if a real Criterion environment is available the harness can be swapped transparently.
- Day04’s `task02/main.c` mirrors the example from the subject. The grading pipeline may inject its own file—removing ours before handing in is safe, as the Makefile expects it.
- No additional bonus tasks were required; all mandatory scope is implemented and exercised by automated tests.
