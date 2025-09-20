# Rush1 – Squares Renderer

Five variants of the classical pool "rush" exercise are implemented under `rush-1-1/`
… `rush-1-5/`. Each variant exposes a single `rush(int x, int y);` function composed
exclusively with the grader-provided `my_putchar`, and reproduces the exact ASCII
patterns detailed in `Rush1.pdf`.

## Layout

- `rush-1-*/include/rush.h` – shared prototype delivered with each assignment.
- `rush-1-*/src/rush.c` – dedicated implementation (delegates to a tiny helper to pick
  the correct character for a given tile).
- `rush-1-*/tests/test.sh` – regression suite comparing the output against the official
  binaries shipped in `rush1_bins.tgz`.
- `rush1_bins.tgz` – subject-provided oracle executables (`rush1-1` … `rush1-5`).

## Build & Test

Each sub-assignment ships an independent Makefile:

```sh
cd rush-1-1   # or rush-1-2, …
make          # compiles src/rush.c → src/rush.o
make test     # builds a temporary harness and diff the output vs oracle
make fclean   # cleanup objects and transient harness
```

The tests cover:
- canonical examples from the subject (`5x3`, `5x1`, `1x1`, `1x5`, `4x4`),
- error handling (`rush(0, y)` → `Invalid size\n` on stderr),
- edge cases where width or height collapses to 1 (expected pure border symbols).

## Implementation Notes

- Error handling follows the specification: `rush` returns early and writes
  `Invalid size\n` to `stderr` when `x <= 0` or `y <= 0`.
- Interior logic favours readability: a helper function decides which character to
  emit per coordinate; special cases ensure degenerate rectangles (width/height 1)
  match the oracle outputs exactly.
- No `main` nor `my_putchar` is delivered—only the grader interfaces are referenced.
