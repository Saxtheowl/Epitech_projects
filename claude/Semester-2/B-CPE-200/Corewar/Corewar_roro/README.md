# Corewar - Virtual Machine

A complete implementation of the Corewar virtual machine - a programming tournament game where champions fight for memory supremacy.

## Overview

Corewar is a virtual machine that executes programs called "champions" in a shared memory arena. Champions fight by attempting to survive the longest while executing instructions. The last champion to execute the `live` instruction wins.

## Architecture

The virtual machine implements:
- **16 instructions** as specified in the Epitech Corewar subject
- **Memory management** with 6KB (6144 bytes) of shared memory
- **Process scheduling** with cycle-based execution
- **Champion loading** from `.cor` bytecode files
- **Live checking** mechanism for survival detection

## Features

- ✅ **All 16 Instructions**: live, ld, st, add, sub, and, or, xor, zjmp, ldi, sti, fork, lld, lldi, lfork, aff
- ✅ **Virtual Machine**: Complete VM with process management and memory handling
- ✅ **Champion Loading**: Reads `.cor` files with proper header validation
- ✅ **Command Line Interface**: Full argument parsing with -dump, -n, -a options
- ✅ **Memory Dump**: Hexadecimal memory visualization
- ✅ **Cycle Management**: Proper cycle counting and process scheduling

## Instructions Implemented

| Opcode | Mnemonic | Description |
|--------|----------|-------------|
| 0x01 | live | Indicates that the player is alive |
| 0x02 | ld | Load value into register |
| 0x03 | st | Store register value to memory/register |
| 0x04 | add | Add two registers, store in third |
| 0x05 | sub | Subtract two registers, store in third |
| 0x06 | and | Binary AND operation |
| 0x07 | or | Binary OR operation |
| 0x08 | xor | Binary XOR operation |
| 0x09 | zjmp | Jump if carry is set |
| 0x0a | ldi | Load indirect with index |
| 0x0b | sti | Store indirect with index |
| 0x0c | fork | Create new process |
| 0x0d | lld | Long load (no modulo) |
| 0x0e | lldi | Long load indirect (no modulo) |
| 0x0f | lfork | Long fork (no modulo) |
| 0x10 | aff | Display character |

## Usage

```bash
# Compile
make

# Run with champions
./corewar champion1.cor champion2.cor

# Run with memory dump after 100 cycles
./corewar -dump 100 champion1.cor champion2.cor

# Specify champion number and load address
./corewar -n 1 -a 0 champion1.cor -n 2 -a 1000 champion2.cor

# Display help
./corewar
```

## Command Line Options

- `-dump nbr_cycle`: Dumps memory after specified cycles in hexadecimal format
- `-n prog_number`: Sets the champion's player number (1-4)
- `-a load_address`: Sets the champion's loading address in memory

## Memory Layout

- **Total Memory**: 6144 bytes (MEM_SIZE)
- **Index Modulo**: 512 (IDX_MOD) for relative addressing
- **Register Size**: 4 bytes per register
- **16 Registers**: r1 to r16 per process

## Process Management

Each champion starts with:
- **PC (Program Counter)**: Points to current instruction
- **16 Registers**: r1 contains champion ID, others initialized to 0
- **Carry Flag**: Set by arithmetic and logical operations
- **Cycle Counter**: Tracks execution timing

## Game Rules

- Champions execute instructions in round-robin fashion
- Each instruction has a specific execution time in cycles
- Champions must execute `live` instruction every CYCLE_TO_DIE cycles
- Last champion to execute `live` wins the game
- Memory is shared - champions can modify each other's code

## File Structure

```
src/
├── main.c              # Entry point
├── parser.c            # Command line parsing
├── champion.c          # Champion loading and management
├── vm.c               # Virtual machine core
├── process.c          # Process management
├── instructions.c     # Instruction execution framework
├── operations.c       # Instructions 1-8 implementation
├── operations2.c      # Instructions 9-16 implementation
└── op.c              # Instruction definitions

include/
├── corewar.h         # Main header file
└── op.h             # Instruction constants and structures
```

## Technical Details

- **Instruction Format**: Opcode + Coding Byte + Parameters
- **Parameter Types**: Register (T_REG), Direct (T_DIR), Indirect (T_IND)
- **Endianness**: Big-endian format for multi-byte values
- **Memory Protection**: Proper bounds checking and modulo operations
- **Error Handling**: Robust error checking with exit code 84

## Testing

The project includes champion files for testing:
- `abel.cor` - "Abel" - L'amer noir
- `bill.cor` - "Bill" - Equilibre
- `pdd.cor` - Test champion
- `tyron.cor` - Test champion

```bash
# Run tests
make test
```

## Compilation

```bash
make          # Build corewar
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild from scratch
```

## Requirements Met

- ✅ Binary name: `corewar`
- ✅ Language: C with proper Epitech coding style
- ✅ Compilation: Makefile with re, clean, fclean rules
- ✅ Authorized functions: Only allowed system calls used
- ✅ Error handling: Exit code 84 for errors, 0 for success
- ✅ Virtual Machine: Complete implementation with all features
- ✅ Memory dump: Required -dump flag functionality
- ✅ Champion support: Loads and executes .cor files correctly

## Notes

This is a educational implementation of the Corewar virtual machine, designed to understand:
- Virtual machine architecture
- Process scheduling and management
- Assembly language interpretation
- Memory management and protection
- Game theory and competitive programming