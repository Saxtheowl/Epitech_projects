# my_ls

Re-implementation of a subset of `ls` supporting the exact mandatory options from the subject: `-a -l -R -d -r -t`.

## Build

```bash
make
```

This produces the `my_ls` binary.

## Usage

```bash
./my_ls [-alRdrt] [FILE...]
```

- `-a` : include hidden files (those whose names start with `.`)
- `-l` : long format (mode, links, owner, group, size, mtime, name)
- `-R` : recurse into subdirectories
- `-d` : list directories themselves, not their contents
- `-r` : reverse order of sort
- `-t` : sort by modification time (newest first). Without `-t`, entries are sorted by name.

Multiple files and directories are supported. When multiple paths are provided, files are listed first, then directories. Section headers (`path:`) are printed like GNU `ls`.

## Errors & Exit Codes

- All error messages are printed to **stderr**.
- If any error occurs (invalid option, missing path, permission denied, etc.), the program exits with **84**. Otherwise it exits with **0**.

## Tests

A Python stdlib-only test runner is provided:

```bash
make tests_run
```

It runs functional and error-path tests and prints a small report to stdout.

## Notes / Limits

- No color or column layout without `-l` (these are **bonus** in the subject and intentionally not implemented).
- Time formatting uses `ctime()`-style `"Mmm dd HH:MM"` snippet for simplicity.
