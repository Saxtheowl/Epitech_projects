# InfinAdd (B-CPE-101)

## Subject recap
- **Binary**: `infin_add` (`InfinAdd.pdf`, p.2).
- **Requirements**:
  - Implement infinite addition for two string operands (signed), printing the result
    without leading zeros and a single `-` when negative.
  - No libC allowed apart from `write`, `malloc`, `free`.
  - Provide a Makefile with `all`, `clean`, `fclean`, `re`.
- **Examples** (p.3):
  - `./infin_add “-876435” “987143265”` → `986266830`
  - `./infin_add “-807965” “-34532”` → `-842497`
  - Big integer cases span dozens of digits.

## Implementation
- Parse each operand: skip spaces, collapse successive `+/-`, record sign, strip
  leading zeros (default to `0`).
- Store digits in dynamically allocated strings, use absolute addition/subtraction:
  - `add_abs` performs grade-school addition from least significant digit.
  - `sub_abs` subtracts assuming `|a| ≥ |b|` and trims leading zeros.
  - `compare_abs` determines subtraction direction when signs differ.
- Compose the final string with sign prefix when necessary; zero is normalised to `0`.
- All helpers rely solely on internal utilities (`my_strlen`, `my_strdup_range`, etc.)
  backed by `write`/`malloc`/`free`.

## Validation
- `make test` (or `./scripts/test.sh`) runs `tests/test.sh` which rebuilds the project
  then executes representative cases:
  - Subject samples (`-876435 + 987143265`, `-807965 + -34532`, large 40+ digit inputs).
  - Handling of leading zeros, carries, negative combinations and zero results.
- Sample output:
  ```
  [OK ] -876435 + 987143265 = 986266830
  ...
  Passed: 8  Failed: 0
  ```

## Checklist
- [x] Makefile with expected targets, no forbidden dependencies.
- [x] Sign handling (`+/-`) and leading zero stripping.
- [x] Arbitrary precision addition/subtraction.
- [x] Result formatting without superfluous zeros/signs.
- [x] Automated regression suite.

## Risks / follow-up
- Internally uses base-10 character arithmetic; complexity is O(n) for addition and
  subtraction, sufficient for subject scope.
- No input validation for non-digit characters beyond the initial parse (per subject
  assumption of valid numbers). Tightening checks is optional if future requirements
  change.
