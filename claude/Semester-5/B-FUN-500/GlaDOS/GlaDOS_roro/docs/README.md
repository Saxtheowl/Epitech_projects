# GLaDOS - Generic Language and Data Operand Syntax

GLaDOS is a functional programming language interpreter and compiler implemented in Haskell, following LISP semantics.

## Features

### Part 1: LISP Interpreter
- **S-Expression Syntax**: Full support for symbolic expressions
- **Data Types**: 64-bit integers, booleans (#t/#f), procedures
- **Variable Bindings**: `define` special form for variable and function definitions
- **Lambda Expressions**: Anonymous functions with closure support
- **Conditionals**: `if` expressions for control flow
- **Built-in Functions**: Arithmetic (+, -, *, div, mod) and comparison (<, eq?)
- **Recursion**: Support for recursive function definitions
- **Error Handling**: Comprehensive error messages with exit code 84

### Part 2: Advanced Features
- **Formal Grammar**: Complete BNF grammar specification
- **Advanced Evaluation**: Optimized evaluation engine
- **Comprehensive Testing**: Unit, integration, and property-based tests
- **CI/CD Pipeline**: Automated testing and release builds

## Building

### Prerequisites
- GHC 8.10.7 or later
- Stack (recommended) or Cabal

### Build Commands
```bash
# Build the project
make all

# Run tests
make test

# Run with coverage
make coverage

# Clean build artifacts
make clean
```

## Usage

GLaDOS reads from standard input and evaluates LISP expressions:

```bash
# Simple arithmetic
echo "(+ 1 2)" | ./glados
# Output: 3

# Function definition and call
cat > factorial.lisp << EOF
(define (fact n)
  (if (eq? n 1)
      1
      (* n (fact (- n 1)))))
(fact 5)
EOF
./glados < factorial.lisp
# Output: 120

# Lambda expressions
echo "((lambda (x y) (+ x y)) 3 4)" | ./glados
# Output: 7
```

## Language Syntax

### Basic Data Types
- **Integers**: `42`, `-15`
- **Booleans**: `#t` (true), `#f` (false)
- **Symbols**: `foo`, `+`, `my-var`

### Lists and Function Calls
```lisp
()                    ; Empty list
(1 2 3)              ; List of integers  
(+ 1 2)              ; Function call
(foo bar baz)        ; Function call with multiple arguments
```

### Variable Definition
```lisp
(define x 42)         ; Define variable
(define pi 3.14159)   ; Define constant
```

### Function Definition
```lisp
; Named function
(define (square x)
  (* x x))

; Anonymous function (lambda)
(lambda (x y) (+ x y))

; Function with lambda
(define add
  (lambda (x y) (+ x y)))
```

### Conditionals
```lisp
(if (< x 0)
    (- x)           ; then branch
    x)              ; else branch
```

### Built-in Functions

#### Arithmetic
- `(+ a b)` - Addition
- `(- a b)` - Subtraction  
- `(* a b)` - Multiplication
- `(div a b)` - Integer division
- `(mod a b)` - Modulo operation

#### Comparison
- `(< a b)` - Less than
- `(eq? a b)` - Equality test

## Examples

### Recursive Factorial
```lisp
(define (fact n)
  (if (eq? n 1)
      1
      (* n (fact (- n 1)))))
(fact 10)
```

### Higher-Order Functions
```lisp
(define (apply-twice f x)
  (f (f x)))

(define (square x)
  (* x x))

(apply-twice square 2)  ; Result: 16
```

### Nested Functions
```lisp
(define (make-adder n)
  (lambda (x) (+ x n)))

(define add5 (make-adder 5))
(add5 10)  ; Result: 15
```

## Architecture

### Parser
Hand-written recursive descent parser (no external parsing libraries):
- Tokenizes input into S-expressions
- Handles nested structures and whitespace
- Comprehensive error reporting

### Evaluator  
Environment-passing interpreter:
- Recursive evaluation of expressions
- Lexical scoping with closures
- Tail call optimization (planned)

### Type System
- Dynamic typing with runtime type checking
- Value types: integers, booleans, procedures
- Comprehensive error handling

## Testing

The project includes extensive test coverage:

- **Unit Tests**: Individual component testing
- **Integration Tests**: End-to-end functionality
- **Property Tests**: QuickCheck property-based testing
- **Coverage Reports**: Detailed code coverage analysis

```bash
# Run all tests
make test

# Run with coverage
make coverage

# Run specific test suite
stack test --test-arguments="--match Parser"
```

## CI/CD

Automated continuous integration with GitHub Actions:
- **Build Validation**: Automatic builds on push/PR
- **Test Execution**: Full test suite on multiple environments
- **Coverage Reporting**: Code coverage analysis
- **Release Builds**: Automated binary releases

## Error Handling

GLaDOS provides descriptive error messages and exits with code 84 on errors:

```bash
$ echo "(+ foo 2)" | ./glados
*** ERROR : variable foo is not bound.
$ echo $?
84
```

## Grammar Specification

See `docs/grammar.bnf` for the complete formal grammar specification in Extended BNF notation.

## Development

### Project Structure
```
glados/
├── src/
│   └── GLaDOS/
│       ├── Core.hs          # Main interpreter
│       ├── Parser.hs        # S-expression parser
│       ├── Evaluator.hs     # Expression evaluator
│       └── Types.hs         # Data types and ADTs
├── app/
│   └── Main.hs              # CLI entry point
├── tests/
│   └── GLaDOS/
│       ├── ParserSpec.hs    # Parser tests
│       ├── EvaluatorSpec.hs # Evaluator tests
│       └── IntegrationSpec.hs # Integration tests
├── docs/
│   ├── grammar.bnf          # BNF grammar
│   └── README.md            # This file
└── Makefile                 # Build configuration
```

### Contributing
1. Follow Haskell style conventions
2. Add tests for new features
3. Update documentation
4. Ensure all tests pass before submitting

## License

This project is part of the Epitech curriculum (B5 - Advanced Functional Programming).

---

*"The cake is a lie, but the code is real."* - GLaDOS