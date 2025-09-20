# Bootcamp Phoenix

Bootcamp Phoenix regroups the five practice days from the B-BOO-101 module. Each day focuses on a specific set of C fundamentals, progressively combining them into larger deliverables.

## Organisation

```
Day01/  # Elementary printing and parsing helpers
Day02/  # Recursion, arithmetic and string algorithms (+ Criterion-like unit tests)
Day03/  # Phoenix static library and argument helpers
Day04/  # Memory management, string splitting, parameter structures
Day05/  # `star` program (ASCII art generator)
lib/phoenix/  # Static library exposing common helpers
includes/     # Public header (phoenix.h)
tests/        # Automated unit-test harness + scenarios
scripts/test.sh  # Convenience entry point for the full test suite
```

## Build

All components (library + binaries) can be built from the project root:

```bash
make           # build the phoenix library and every required executable
make clean     # remove intermediary objects
make fclean    # clean + remove binaries and the library
make re        # full rebuild
```

Individual deliverables keep their own Makefile (for example `Day03/task04`, `Day04/task02`, `Day05`). The phoenix library is rebuilt automatically when needed.

## Tests

Automated tests (unit coverage + behavioural checks) are bundled in `tests/` and executed through `make test`:

```bash
make test      # builds, runs unit tests, and validates the star outputs
```

The custom testing harness produces gcov coverage artefacts. Example coverage after a full run:

- `my_strcpy.c` – 100% line coverage / 100% branch coverage
- `my_strncmp.c` – 93.33% line coverage / 83.33% branch coverage

A convenience wrapper is also available:

```bash
./scripts/test.sh
```

## Notable implementation details

- `includes/phoenix.h` centralises every public prototype and the `info_param` structure shared across the days.
- `lib/phoenix/Makefile` builds `libphoenix.a` from Day01/Day02 sources and exposes it to the later tasks (`task04`, `task05`, `star`, etc.).
- Day04’s `task02/` ships with a minimal `main.c` mirroring the subject’s example so the project remains buildable and testable locally. The file can safely be replaced by the official harness if needed.
- A lightweight Criterion-compatible harness (`tests/framework.[ch]`) is used instead of the original library to stay self-contained on the target environment while keeping the same assertion API.
