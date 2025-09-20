# Match & Nmatch (B-CPE-100)

Re-implementation of the pool pattern-matching exercises:

- `match` tells whether two strings can match when the pattern may contain `*`
  wildcards.
- `nmatch` counts all distinct matches produced by the same `*` semantics.

Both functions follow the official prototypes:

```c
int match(char const *s1, char const *s2);
int nmatch(char const *s1, char const *s2);
```

The wildcard `*` substitutes any string (including the empty string). Other
characters compare literally.

## Build

```sh
make
```

`make` only compiles the object files (`src/match.c`, `src/nmatch.c`). They are
ready to be linked with the subject’s graders.

## Tests

```sh
make test
```

`make test` compiles a lightweight harness that exercises both functions against
canonical cases and compares the answers to the official subject oracles
(`match.tgz`, `nmatch.tgz`). The harness is transient and removed automatically.

## Cleaning

```sh
make clean   # object files + test harness
make fclean  # clean + remove stray binaries (if any)
make re      # rebuild from scratch
```

## Notes

- The sources don’t embed a `main`; the graders will supply theirs.
- `match`/`nmatch` accept `NULL` inputs defensively by returning 0.
- Only recursion is used (no additional allocations or forbidden system calls).
