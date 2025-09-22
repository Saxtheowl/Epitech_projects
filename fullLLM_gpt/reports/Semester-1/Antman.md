# Antman & Giantman (B-CPE-110)

## Subject overview
- **Sources**: `Antman/Antman.pdf` (compression) & `Antman/Giantman.pdf` (decompression). PDF extraction unavailable in this environment; requirements recalled from prior project notes.
- **Goal**: implement a pair of CLI tools — `antman` compresses a file, `giantman` restores it losslessly. The header format is `AR01` followed by a single byte type identifier (`1` text, `2` HTML, `3` P3 PPM).
- **Constraints**:
  - Use only low-level I/O (`open`, `read`, `write`, `close`) and dynamic allocation (`malloc`, `free`).
  - Programs must fail (return 84) when arguments are invalid, when the header/type mismatch, or when the stream is malformed.
  - Compression must be lossless for the supported file types.

## Implementation notes
- Compression uses a PackBits-like RLE: literals are emitted with control bytes `0xxxxxxx`, runs with `1xxxxxxx`. The encoder enforces block limits (≤128 bytes) and builds the output in a dynamically resized buffer.
- Decompression mirrors the scheme, validating the header and ensuring the embedded type matches the CLI argument before streaming data through `write_all`.
- Both binaries now validate the type argument (`1..3`) up-front to respect the subject contract.
- Shared utilities (`read_entire_file`, `write_all`) reside in each project’s `src/io.c`, using only permitted syscalls.

## Tests & validation
- `make test` runs `antman/tests/test.sh` then `giantman/tests/test.sh`.
  - Round-trip tests on textual, HTML, et binary payloads confirm lossless compression.
  - Header integrity checks (Python helper) ensure the `AR01` magic and type byte are produced correctly.
  - Error-path tests assert `antman` rejects invalid types and `giantman` fails on header corruption or type mismatch, returning 84.
- Latest execution: `make test` → antman (4 OK) + giantman (5 OK) without residual artefacts.

## Checklist
- [x] CLI usage enforces correct arity and type range.
- [x] Header conforms to expected `AR01` + type format.
- [x] Decompression validates header/type and handles malformed streams safely.
- [x] Regression suite exercises success and failure flows.
- [x] Only allowed syscalls/utilities are used.

## Risks / next steps
- PackBits encoding is generic; dedicated optimisations for HTML or P3 (e.g. dictionary compression) could improve ratios if required by advanced grading.
- No explicit size limit: extremely large inputs may require additional chunked streaming rather than whole-file buffering for memory footprint; acceptable for current scope.
- Additional fuzz tests on random binary streams would strengthen robustness.
