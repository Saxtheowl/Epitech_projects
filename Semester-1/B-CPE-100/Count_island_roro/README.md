# Count Island

## Description

This project implements the `count_island` function that identifies and counts islands in a 2D world represented as a character array. Islands are formed by connected 'X' characters, where connection is defined as horizontal or vertical adjacency (not diagonal).

## Compilation

```bash
make all
```

## Usage

The program expects a 2D array of strings where:
- '.' represents water
- 'X' represents land
- The last element must be NULL

```c
char *world[] = {
    "X..X",
    "....",
    "X..X",
    NULL
};
int result = count_island(world);
```

## Function Prototype

```c
int count_island(char **world);
```

## Algorithm

1. Scans the world line by line from top to bottom, left to right
2. When an 'X' is found, uses flood fill to mark all connected 'X' characters
3. Replaces 'X' characters with their island number (starting from 0)
4. Returns the total number of islands found

## Options

This is a library function with no command-line options.

## Error Handling

- Returns 0 if the world is NULL or empty
- Maximum 10 islands supported
- Uses only the `write` system call

## Tests

Run the comprehensive test suite:

```bash
make tests_run
```

The test suite includes:
- Single island detection
- Multiple separate islands
- Connected island patterns
- Empty world handling
- NULL input handling
- Complex patterns
- Large connected islands

## Project Structure

```
Count_island_roro/
├── include/
│   └── my.h
├── lib/
│   └── my/
│       ├── build.sh
│       ├── libmy.a
│       └── *.c
├── src/
│   └── count_island.c
├── tests_py/
│   └── run_tests.py
├── docs/
│   ├── subject.pdf
│   └── epitech_c_coding_style.pdf
├── Makefile
└── README.md
```

## Requirements

- Language: C
- Coding Style: Epitech
- Compilation: gcc with -Wall -Wextra -std=c99
- Allowed system call: write only
- Library: Must use custom libmy

## Exit Codes

- 0: Success
- 84: Error (following Epitech standards)