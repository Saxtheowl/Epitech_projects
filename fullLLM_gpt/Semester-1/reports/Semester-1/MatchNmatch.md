# Match & Nmatch (B-CPE-100)

## Subject recap
- **Goal**: reimplement the Pool wildcard matching functions (`MatchNmatch.pdf`, pp.2-3).
  - `match(s1, s2)` returns `1` when `s2` matches `s1` with `*` acting as “any substring”, `0` otherwise.
  - `nmatch(s1, s2)` counts **all** distinct match combinations when `*` introduces multiple possibilities.
- **Constraints**: C only, linked with `lib/my`, no delivered `main`, only `write` allowed system call. Both functions compiled independently with the grader’s `main.c` (`MatchNmatch.pdf`, p.2).

## Requirements
- **MUST** deliver `match.c` and `nmatch.c` under `src/`, prototypes in `include/matchnmatch.h`.
- **MUST** handle patterns containing any number of `*`, including edge cases (empty strings, trailing stars, consecutive stars).
- **MUST** return `0` on mismatch and `1` (for `match`) or combination count (for `nmatch`) on match.
- **SHOULD** operate recursively without allocating extra buffers.
- **SHOULD** keep `NULL` inputs safe (return `0`).
- **SHOULD** provide automated tests validating behaviour vs the subject oracles.

## Implementation details
- Both functions share recursive helpers (`match_rec`, `nmatch_rec`) exploring two branches when a `*` is encountered: either the star consumes zero characters or consumes one (recurse on `s1 + 1`).
- Base case: reaching the end of `s2` yields success only if `s1` also ended.
- `nmatch` accumulates every successful branch instead of returning a boolean.
- Defensive `NULL` checks at the public entry points comply with undefined-input safety.

## Build & Layout
- `Makefile` compiles the two sources into objects (no binaries) and exposes standard targets (`clean`, `fclean`, `re`, `test`).
- Sources: `src/match.c`, `src/nmatch.c`; header `include/matchnmatch.h`.
- No `main.c` is shipped to respect the grading pipeline; local harness is generated on the fly.

## Tests
- `make test` (or `scripts/test.sh`) builds a temporary harness that calls `match`/`nmatch`, compares the results against the official oracle binaries contained in `match.tgz` and `nmatch.tgz`, and exercises canonical cases including subject examples:
  - `abcbd` vs `*b*` → `match=1`, `nmatch=2`.
  - `abc` vs `a**` → `match=1`, `nmatch=3`.
  - Negative scenarios (e.g., `abc` vs `ab*d`).
- Sample run: 11 patterns × 2 verdicts → `OK=22 KO=0`.

## Checklist
- [x] `match` implemented with wildcard support.
- [x] `nmatch` counts all combinations.
- [x] Header exposes prototypes; no forbidden system calls.
- [x] Automated suite aligned with subject binaries.
- [x] README summarises build/test instructions.

## Risks / follow-up
- Test harness depends on `match.tgz` / `nmatch.tgz`; if missing, comparisons downgrade to self-output. Ensure archives match the subject version.
- Recursion depth grows with input length; acceptable for Pool constraints but could stack overflow on extremely long strings (not expected in grading).
