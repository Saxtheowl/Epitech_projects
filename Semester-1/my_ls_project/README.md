# my_ls — Epitech-style `ls` reimplementation

Reimplementation of `ls` supporting **mandatory** options: `-a`, `-l`, `-R`, `-d`, `-r`, `-t` and a list of files/dirs.
Errors go to **stderr** and the program exits with **84** on error, **0** otherwise.

## Build (Ubuntu 24.04)

```bash
make
```

Produces the binary: `./my_ls`.

## Usage

```bash
./my_ls [-alRdrt] [FILE...]
```

Examples:
```bash
./my_ls
./my_ls -l
./my_ls -a -l /dev /usr/sbin
./my_ls -lRt
./my_ls -d .
```

## Tests

Tests are implemented in **Python (stdlib only)** and run via:
```bash
make tests_run
```

The test runner compiles the project, builds temporary fixtures (no network, no external deps), then prints a clear OK/KO report to stdout.

## Notes & Constraints

- Only the mandatory features are implemented (no bonus: no colors, no multi-column layout without `-l`, etc.).
- On any error (unknown option, missing file, permission denied, …), an error message is printed to stderr and the program exits with **84**.
- The code follows Epitech C Coding Style as closely as possible (headers, spacing, <80 cols, ≤20 lines per function as feasible).
