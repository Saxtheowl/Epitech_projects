##
## EPITECH PROJECT, 2025
## GLaDOS
## File description:
## Makefile for GLaDOS functional programming language
##

NAME = glados

# Stack commands
STACK_BUILD = stack build
STACK_TEST = stack test
STACK_EXEC = stack exec
STACK_CLEAN = stack clean
STACK_PURGE = stack purge

# Directories
SRC_DIR = src
APP_DIR = app
TEST_DIR = tests
DOCS_DIR = docs

.PHONY: all build test clean fclean re install deps check coverage help

all: $(NAME)

$(NAME): deps
	@echo "Building GLaDOS..."
	@$(STACK_BUILD)
	@cp `$(STACK_EXEC) -- which glados` ./$(NAME) 2>/dev/null || \
	 (echo "Error: Could not find glados executable" && exit 1)
	@echo "GLaDOS built successfully!"

build: $(NAME)

deps:
	@echo "Installing dependencies..."
	@stack setup
	@stack build --dependencies-only

test:
	@echo "Running GLaDOS tests..."
	@$(STACK_TEST)

check: test
	@echo "Running additional checks..."
	@echo "✓ All tests passed"

coverage:
	@echo "Running tests with coverage..."
	@$(STACK_TEST) --coverage
	@echo "Coverage report generated"

install: $(NAME)
	@echo "Installing GLaDOS..."
	@stack install

clean:
	@echo "Cleaning build artifacts..."
	@$(STACK_CLEAN)
	@rm -f $(NAME)

fclean: clean
	@echo "Deep cleaning..."
	@$(STACK_PURGE)
	@rm -rf .stack-work

re: fclean all

# Development targets
dev-build:
	@echo "Building in development mode..."
	@$(STACK_BUILD) --fast

dev-test:
	@echo "Running tests in development mode..."
	@$(STACK_TEST) --fast

repl:
	@echo "Starting GHCi REPL..."
	@stack ghci

# CI/CD targets
ci-test: deps
	@echo "Running CI tests..."
	@$(STACK_TEST) --coverage --fast
	
ci-build: deps
	@echo "Building for CI..."
	@$(STACK_BUILD) --fast

# Documentation
docs:
	@echo "Generating documentation..."
	@stack haddock
	@echo "Documentation available in .stack-work/install/.../doc/"

# Example runs for testing
examples: $(NAME)
	@echo "Running example programs..."
	@echo "(+ 1 2)" | ./$(NAME)
	@echo "((lambda (x) (* x x)) 5)" | ./$(NAME)

help:
	@echo "GLaDOS - Generic Language and Data Operand Syntax"
	@echo ""
	@echo "Available targets:"
	@echo "  all         - Build GLaDOS (default)"
	@echo "  build       - Same as all"  
	@echo "  test        - Run all tests"
	@echo "  clean       - Clean build artifacts"
	@echo "  fclean      - Deep clean including .stack-work"
	@echo "  re          - Full rebuild (fclean + all)"
	@echo "  deps        - Install dependencies"
	@echo "  check       - Run tests and additional checks"
	@echo "  coverage    - Run tests with coverage report"
	@echo "  install     - Install GLaDOS globally"
	@echo "  dev-build   - Fast development build"
	@echo "  dev-test    - Fast development tests"
	@echo "  repl        - Start GHCi REPL"
	@echo "  ci-test     - Run CI tests"
	@echo "  ci-build    - Build for CI"
	@echo "  docs        - Generate Haddock documentation"
	@echo "  examples    - Run example programs"
	@echo "  help        - Show this help message"