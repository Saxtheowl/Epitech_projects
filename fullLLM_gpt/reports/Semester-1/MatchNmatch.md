# MatchNmatch

- Semester: Semester-1
- UE: B-CPE-100
- Subject source: `MatchNmatch.pdf`

## Subject Summary
- Page 2: Project in C compiled alongside the student `libmy`; graders provide their
  own `main.c` and only the `write(2)` system call is authorised. Both exercises are
  graded independently (`match` and `nmatch`).
- Page 3: `int match(char const *s1, char const *s2);` returns 1 when the pattern `s2`
  (with `*` wildcards) can be substituted to match `s1`, otherwise 0. `*` stands for any
  sequence (possibly empty) and may appear multiple times.
- Page 3: `int nmatch(char const *s1, char const *s2);` counts the number of distinct
  substitutions that make the strings match (examples: `abcbd` vs `*b*` → 2,
  `abc` vs `a**` → 3).

## Requirements
- [MUST] Provide `match` and `nmatch` conforming to the subject prototypes without
  embedding a `main`.
- [MUST] Support multiple `*` wildcards, including leading/trailing ones, and return 0
  for non-matching cases.
- [MUST] Default to 0 when the inputs are `NULL` and avoid forbidden system calls.
- [SHOULD] Keep recursion concise to limit stack growth and avoid additional
  allocations.
- [OPTIONAL] Supply automated regression tests against the provided oracles.

## Implementation Notes
- `src/match.c` runs a recursive DFS that either consumes a literal character or, for
  `*`, tries the empty substitution first (pruning early matches) then consumes one
  character at a time.
- `src/nmatch.c` uses similar recursion but accumulates every valid substitution count
  when exploring `*` branches.
- The Makefile now compiles only the objects, ready for the graders’ mains; the test
  harness is generated on the fly and cleaned afterwards.

## Test Strategy
- `make test` builds a temporary harness that prints the results of both functions,
  runs it on curated cases, and compares each output line to the official reference
  binaries extracted from `match.tgz` and `nmatch.tgz`.

## Evaluation Checklist
- [x] `match` and `nmatch` compiled without auxiliary mains.
- [x] Outputs align with the official oracles on representative cases.
- [x] Makefile provides `all`, `clean`, `fclean`, `re`, `test` targets.

## Risks / Follow-up
- Recursion depth still depends on input length; convert to iterative DP if the tester
  stresses very long strings.
- The oracle comparison covers common cases; extend the suite if additional corner
  cases arise.
