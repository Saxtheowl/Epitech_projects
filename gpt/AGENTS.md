# Repository Guidelines

## Project Structure & Module Organization
- Top-level directories: `Semester-0` … `Semester-5`.
- Each project lives in its own folder and commonly uses:
  - `src/` (implementation), `include/` (headers), `tests/` (unit tests), `assets/` (optional), and a `Makefile`.
- Example path: `Semester-2/B-CPE-210/Duo_Stumpers/TextCount/TextCount_roro/`.

## Build, Test, and Development Commands
- `cd <project>`: work inside the specific project directory.
- `make`: build the project (outputs binary in project root when applicable).
- `make clean | fclean | re`: remove objects, full clean, or rebuild from scratch.
- `make tests_run`: run unit tests (Criterion where provided) and usually enable coverage flags.
- Example: `cd Semester-2/B-CPE-210/Duo_Stumpers/TextCount/TextCount_roro && make tests_run`.

## Coding Style & Naming Conventions
- Indentation: 4 spaces, no tabs. Keep lines concise (≤100 chars preferred).
- C identifiers: `snake_case` for functions/variables, `UPPER_SNAKE_CASE` for macros/consts, `PascalCase` for types/structs.
- Headers: include guards like `PROJECT_NAME_H` and place public interfaces in `include/`.
- One responsibility per file; avoid global state; validate inputs.
- Format and lint: follow Epitech-style guidelines where applicable; keep `Makefile` targets standard.

## Testing Guidelines
- Framework: Criterion (for C projects) with tests in `tests/`.
- Naming: test files like `test_<unit>.c` or `<unit>_test.c`; small, isolated cases.
- Run: `make tests_run` in the project directory.
- Coverage: if configured, use `gcovr -r . --exclude tests` after tests to check coverage; aim for meaningful coverage on core logic.

## Commit & Pull Request Guidelines
- Commit style observed: short, descriptive messages (imperative tone); no strict Conventional Commits required.
- Message format: summary in first line; add brief context if needed.
- Scope clearly: mention project path when helpful (e.g., “TextCount: add tokenizer tests”).
- PRs should include: purpose, affected paths, build/test steps, and screenshots/logs when relevant.
- Hygiene: run `make fclean` before committing; do not commit binaries, `.o`, or generated coverage/artifacts.

## Security & Configuration Tips
- Never commit secrets or credentials. Use local env files that are git-ignored.
- Large assets and PDFs belong only if essential; prefer links when possible.
