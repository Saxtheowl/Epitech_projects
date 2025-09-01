# 42sh - Advanced Unix Shell

A comprehensive Unix shell implementation based on TCSH, featuring advanced command line processing and job control.

## Overview

42sh is an advanced shell that extends basic shell functionality with sophisticated features including variable expansion, globbing, job control, aliases, and command history. This implementation follows TCSH compatibility guidelines.

## Features Implemented

### ✅ **Core Shell Functionality**
- **Command Execution**: Execute external programs with PATH resolution
- **Built-in Commands**: cd, echo, env, setenv, unsetenv, exit, help
- **Pipes**: Full pipeline support with multiple commands
- **Redirections**: Input (<), output (>), append (>>), error (2>)
- **Command Line Parsing**: Robust lexical analysis and parsing

### ✅ **Advanced Features per PDF Specification**

#### **Inhibitors** (' ')
- **Single Quotes**: Prevent variable expansion and special character interpretation
- **Double Quotes**: Allow variable expansion while preserving spaces
- Example: `echo 'Hello $USER'` vs `echo "Hello $USER"`

#### **Globbing** (*, ?, [, ])
- **Wildcard Expansion**: `*.c`, `src/*.h`, `[a-z]*`
- **Pattern Matching**: Automatic expansion of glob patterns
- **Path Resolution**: Works with relative and absolute paths
- Example: `ls src/*.c` expands to list all C files in src/

#### **Variables**
- **Local Variables**: `set VAR=value`, `echo $VAR`
- **Environment Variables**: `setenv VAR value`, `unsetenv VAR`
- **Special Variables**:
  - `$cwd` - Current working directory
  - `$term` - Terminal type (42sh)
  - `$$` - Process ID
  - `$?` - Exit status of last command

#### **Job Control** (&, fg, bg)
- **Background Jobs**: `command &`
- **Job Management**: `jobs`, `fg [job]`, `bg [job]`
- **Process Tracking**: Automatic job status updates
- Example: `sleep 10 & ; jobs ; fg 1`

#### **History** (!)
- **Command History**: `history` displays previous commands
- **Persistent Storage**: History saved between sessions
- **History Management**: Duplicate prevention and size limits

#### **Aliases**
- **Alias Creation**: `alias name=value`
- **Alias Management**: `alias` (list all), `unalias name`
- **Command Expansion**: Automatic alias substitution
- Example: `alias ll='ls -l'`

#### **Built-in Commands**
- `cd [directory]` - Change directory with ~ and - support
- `echo [-n] [args]` - Display text with optional newline suppression  
- `env` - Display environment variables
- `setenv var value` - Set environment variable
- `unsetenv var` - Remove environment variable
- `exit [code]` - Exit shell with optional exit code
- `help` - Display available commands
- `jobs` - List active background jobs
- `fg [job]` - Bring job to foreground
- `bg [job]` - Continue job in background
- `set var=value` - Set shell variable
- `unset var` - Remove shell variable
- `alias [name[=value]]` - Manage command aliases
- `history` - Display command history

## Usage

### Basic Usage
```bash
# Compile
make

# Run interactive shell
./42sh

# Display help
./42sh -h
```

### Examples

#### Variable Usage
```bash
42sh$ set NAME=World
42sh$ echo Hello $NAME
Hello World
42sh$ echo Current directory: $cwd
Current directory: /home/user/project
```

#### Globbing
```bash
42sh$ ls src/*.c
src/main.c src/parser.c src/lexer.c
42sh$ echo *.h
shell.h config.h
```

#### Job Control
```bash
42sh$ sleep 30 &
[1] 12345
42sh$ jobs
[1]  Running                    sleep
42sh$ fg 1
# Brings sleep to foreground
```

#### Pipes and Redirections
```bash
42sh$ ls | wc -l
5
42sh$ echo "Hello World" > output.txt
42sh$ cat < input.txt | grep pattern
```

#### Aliases
```bash
42sh$ alias ll='ls -l'
42sh$ alias grep='grep --color'
42sh$ ll
# Executes 'ls -l'
```

## Technical Implementation

### Architecture
- **Lexer**: Tokenizes input with support for quotes and special characters
- **Parser**: Builds command pipelines and handles redirections
- **Executor**: Manages process creation, pipes, and job control
- **Variable System**: Handles local and environment variable expansion
- **Job Control**: Tracks background processes and provides fg/bg functionality

### Memory Management
- Proper cleanup of all allocated structures
- No memory leaks in normal operation
- Safe handling of dynamic arrays and strings

### Signal Handling
- SIGCHLD for job control updates
- SIGINT for interactive interruption
- Proper signal management for job control

## Compatibility

- **Reference Shell**: TCSH
- **Error Handling**: Exit codes match TCSH behavior
- **Syntax**: Compatible with TCSH command syntax
- **Features**: Implements core TCSH functionality subset

## File Structure

```
src/
├── main.c              # Entry point and initialization
├── shell.c             # Core shell loop and management
├── lexer.c             # Lexical analysis and tokenization
├── parser.c            # Command parsing and AST building
├── executor.c          # Command execution and process management
├── builtins.c          # Built-in command implementations
├── env.c               # Environment variable management
├── variables.c         # Shell variable management
├── aliases.c           # Alias management
├── history.c           # Command history functionality
├── jobs.c              # Job control implementation
├── globbing.c          # Wildcard expansion
├── signals.c           # Signal handling
├── utils.c             # Utility functions
└── line_editing.c      # Command line input handling

include/
└── shell.h             # Main header with all declarations
```

## Requirements Met

- ✅ **Binary name**: 42sh
- ✅ **Language**: C with Epitech coding standards
- ✅ **Compilation**: Makefile with re, clean, fclean rules
- ✅ **Functions**: Standard libC functions only
- ✅ **Error handling**: Proper error messages and exit codes
- ✅ **TCSH compatibility**: Core features and syntax support

## Testing

The shell has been tested with:
- Basic command execution
- Complex pipeline operations
- Variable expansion scenarios
- Globbing pattern matching
- Job control operations
- Built-in command functionality
- Error handling and edge cases

## Notes

This implementation focuses on stability and core functionality over advanced features. All mandatory features from the project specification are implemented and tested. The shell provides a solid foundation for Unix command line operations with modern shell conveniences.