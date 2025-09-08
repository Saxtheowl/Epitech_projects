# B-BOO-101 / Bootcamp Phoenix / Day01 - Project Report

## Project Summary
**Objective**: Implement 6 fundamental C programming tasks focusing on basic string and number operations
**Source**: `day01.pdf` (6 pages)
**Module**: B-BOO-101 Phoenix Bootcamp (0 credits)
**Timeline**: 48h
**Status**: ✅ COMPLETED

## Requirements Analysis

### Discovery (PDF pages 2-6)
The PDF specifies:
- **Repository**: BOO_phoenix_d01_$ACADEMICYEAR  
- **Language**: C
- **Compilation**: gcc *.c (+ Epitech's main and my_putchar)
- **Constraints**: 
  - Only `my_putchar()` allowed for output
  - Error code 84 for errors, 0 for success
  - No main or my_putchar in delivery
  - All bonus files in `bonus/` directory

### Required Tasks (MUST)
1. **Task 01 - show_alphabet**: Display lowercase alphabet a-z
2. **Task 02 - show_combinations**: Display three-digit combinations with different digits (012, 013, ..., 789)  
3. **Task 03 - show_number**: Display any integer including INT_MIN
4. **Task 04 - show_string**: Display string characters one-by-one
5. **Task 05 - reverse_string**: Reverse string by swapping chars two-by-two
6. **Task 06 - to_number**: Parse string to integer with overflow handling

## Architecture & Implementation

### Language & Build System
- **Language**: C
- **Compiler**: GCC with -Wall -Wextra -Werror
- **Build**: Makefile with clean, fclean, test targets
- **Testing**: Comprehensive test suite in `tests/` directory

### Algorithm Approach
- **show_alphabet**: Simple loop from 'a' to 'z'
- **show_combinations**: Triple nested loops ensuring a < b < c
- **show_number**: Recursive approach handling INT_MIN edge case
- **show_string**: Iterate through string until null terminator
- **reverse_string**: Two-pointer approach swapping from ends
- **to_number**: Parse with sign handling and overflow detection

### Error Handling
- Overflow protection in `to_number` using long long
- INT_MIN special handling in `show_number`
- Proper null-termination checks
- Memory safety in string operations

## Implementation Steps

### Step 1: Core Functions ✅
- Implemented all 6 required functions
- Each function follows exact prototype specification
- Used only `my_putchar` for output as constrained

### Step 2: Build System ✅
- Created Makefile with proper CFLAGS
- Added compilation targets for all source files
- Integrated test build and execution

### Step 3: Testing ✅
- Created comprehensive test suite covering all functions
- Implemented `my_putchar` for testing environment
- Added edge case tests (INT_MIN, overflow, empty strings)

### Step 4: Documentation ✅
- Updated project README with implementation details
- Added build instructions and usage examples
- Documented constraints and requirements

## Testing Results

### Test Coverage
- **show_alphabet**: Alphabet output verified ✅
- **show_combinations**: All 120 combinations (012-789) ✅  
- **show_number**: Regular numbers, 0, negatives, INT_MIN ✅
- **show_string**: Normal strings and empty string ✅
- **reverse_string**: Strings of various lengths (1-6 chars) ✅
- **to_number**: Complex parsing, signs, overflow cases ✅

### Test Execution
```bash
make test
```
All functions compile without warnings and execute correctly.

## Evaluation Checklist

### Technical Requirements ✅
- [x] All 6 tasks implemented
- [x] Correct function prototypes
- [x] Only my_putchar used for output
- [x] No compilation warnings/errors
- [x] Proper error handling
- [x] Overflow protection in to_number

### Code Quality ✅
- [x] Epitech C coding style (inferred from documentation)
- [x] Proper file headers
- [x] Clean function implementations
- [x] No memory leaks or segfaults

### Testing ✅
- [x] Comprehensive test coverage
- [x] Edge cases handled
- [x] Automated test execution via Makefile
- [x] All tests pass successfully

## Risk Assessment & Completeness

### Covered Areas ✅
- All functional requirements implemented
- Proper build system with testing
- Documentation and usage instructions
- Error handling and edge cases
- Epitech-specific constraints respected

### Potential Issues
- No known issues - all tests pass
- Implementation handles all specified edge cases
- Proper memory management without leaks

## Files Delivered
```
Day01/
├── show_alphabet.c      # Task 01 implementation
├── show_combinations.c  # Task 02 implementation  
├── show_number.c       # Task 03 implementation
├── show_string.c       # Task 04 implementation
├── reverse_string.c    # Task 05 implementation
├── to_number.c         # Task 06 implementation
├── Makefile            # Build system
├── README.md           # Project documentation
└── tests/
    ├── test_main.c     # Comprehensive test suite
    └── my_putchar.c    # Testing helper function
```

## Conclusion
Day01 of Phoenix Bootcamp successfully completed with all 6 tasks implemented, tested, and documented. The implementation respects all Epitech constraints and provides a solid foundation for the bootcamp series.