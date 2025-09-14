# Wolfram Elementary Cellular Automaton

A Haskell implementation of elementary cellular automata following Wolfram's rules.

## Features

- Implements Rules 30, 90, and 110
- Infinite space simulation (conceptually infinite grid)
- Windowed display with configurable size and movement
- Command-line argument parsing without external dependencies
- Pure functional implementation using higher-order functions and pattern matching

## Requirements

- Haskell Stack (LTS 18.10) or GHC 8.10+
- Only `base` library dependency

## Building

### With Stack (Recommended)
```bash
make
```

### With GHC directly
```bash
ghc -O2 -isrc -o wolfram app/Main.hs
```

### Manual Stack build
```bash
stack build
stack install --local-bin-path .
```

## Usage

```
./wolfram --rule R [--start S] [--lines L] [--window W] [--move M]

Options:
  --rule R       Ruleset to use (30, 90, 110) [MANDATORY]
  --start S      Generation number to start display (default: 0)
  --lines L      Number of lines to display (default: infinite)
  --window W     Number of cells per line (default: 80)  
  --move M       Window translation (default: 0)
```

## Examples

```bash
# Basic rule 30 with 20 lines
./wolfram --rule 30 --lines 20

# Rule 90 starting from generation 100
./wolfram --rule 90 --lines 20 --start 100

# Rule 30 with window movement
./wolfram --rule 30 --lines 10 --move 20

# Infinite simulation (Ctrl+C to stop)
./wolfram --rule 110
```

## Implementation Details

### Architecture
- `src/Wolfram.hs`: Core library with cellular automaton logic
- `app/Main.hs`: Executable entry point and I/O handling
- Uses pure functional programming principles
- Pattern matching for rule implementation
- Higher-order functions for generation sequences

### Rules Implementation
Each rule is implemented as a pattern match on three-cell neighborhoods:
- Rule 30: Chaotic behavior
- Rule 90: Simple symmetric patterns  
- Rule 110: Turing-complete behavior

### Infinite Space Handling
The implementation uses a finite list representation with implicit dead cells
at boundaries, expanding dynamically as needed while trimming unnecessary
dead cells for efficiency.

## Error Handling

The program returns exit code 84 on errors and displays usage information.
All command-line arguments are validated with appropriate error messages.

## Project Structure

```
.
├── Makefile                 # Build system wrapper
├── README.md               # This file
├── app/
│   └── Main.hs            # Executable entry point
├── package.yaml           # Stack/hpack configuration
├── src/
│   └── Wolfram.hs         # Core library implementation  
└── stack.yaml             # Stack resolver configuration
```