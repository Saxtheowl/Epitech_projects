# MatchNmatch Project Report

## Project Information
- **Subject**: B-CPE-100 - MatchNmatch
- **Timeline**: 6 jours
- **PDF Reference**: MatchNmatch.pdf (pages 1-3)
- **Status**: ✅ COMPLETED

## Objective Summary (from PDF pages 2-3)

### MATCH Function:
- **Purpose**: Find if two strings match with wildcard support
- **Prototype**: `int match(char const *s1, char const *s2);`
- **Wildcard**: '*' can replace any character string (even empty)
- **Returns**: 1 if match, 0 otherwise
- **Example**: "main.c" and "*.c" match (replace * with "main")

### NMATCH Function:
- **Purpose**: Count number of ways two strings can match
- **Prototype**: `int nmatch(char const *s1, char const *s2);`
- **Multiple wildcards**: Several combinations possible
- **Returns**: Number of matching combinations
- **Examples**: 
  - "abcbd" and "*b*" → 2 matches: (a, cbd) and (abc, d)
  - "abc" and "a**" → 3 matches: (nothing, bc), (b, c), (bc, nothing)

## Requirements Analysis (from PDF page 2)
### MUST Requirements:
- ✅ Language: C
- ✅ Delivery: match.c and nmatch.c only
- ✅ Library in lib/my/ with build.sh script
- ✅ Headers in include/
- ✅ Only write() system call allowed
- ✅ Built separately with individual mains
- ✅ No main function in delivery

### SHOULD Requirements:
- ✅ Split into small functions (Coding Style)
- ✅ Comprehensive unit tests
- ✅ Test individual functions

## Algorithm Design & Implementation

### Match Algorithm:
1. **Base cases**: Handle NULL pointers, empty strings
2. **Pattern end**: If pattern ends, string must also end
3. **Wildcard handling**: When '*' found:
   - Try matching without consuming characters (empty match)
   - Try consuming one character and continue with same pattern
4. **Character matching**: Direct character comparison
5. **Recursive approach**: Natural for pattern matching

### NMatch Algorithm:
1. **Base cases**: Same as match
2. **Wildcard expansion**: When '*' found:
   - Try all possible substring consumptions (0 to remaining length)
   - Sum all possible matches for each consumption
3. **Combinatorial counting**: Accumulate all valid combinations
4. **Recursive enumeration**: Explore all possible paths

### File Structure:
```
MatchNmatch/
├── match.c                # Match function implementation
├── nmatch.c               # NMatch function implementation  
├── include/my.h           # Function prototypes
├── lib/my/               # Standard library
│   ├── build.sh          # Library build script
│   ├── my_putchar.c      # Character output
│   ├── my_putstr.c       # String output
│   ├── my_put_nbr.c      # Number output
│   └── my_strlen.c       # String utilities
├── tests/                # Test framework
│   ├── match_main.c      # Match test harness
│   ├── nmatch_main.c     # NMatch test harness
│   └── test.sh           # Comprehensive test runner
└── Makefile              # Build system
```

## Implementation Details

### Match Function:
```c
int match(char const *s1, char const *s2)
```
- **Null safety**: Handles NULL input pointers
- **Recursive design**: Natural pattern matching logic
- **Wildcard logic**: '*' can match empty string or consume characters
- **Character comparison**: Direct equality check for non-wildcards

### NMatch Function:
```c
int nmatch(char const *s1, char const *s2)  
```
- **Combinatorial exploration**: Counts all valid matching combinations
- **Wildcard expansion**: Tries all possible substring consumptions
- **Accumulative counting**: Sums results from recursive calls
- **Efficient enumeration**: Avoids duplicate counting

### Key Features:
- **Recursive algorithms**: Clean, mathematical approach
- **Wildcard support**: Unlimited '*' characters in patterns
- **Edge case handling**: Empty strings, NULL pointers, no wildcards
- **Memory efficient**: No dynamic allocation, pure computational

## Testing Strategy & Results

### Test Cases Design:
**Match Function:**
- Basic matching: "main.c" vs "*.c" → 1
- Multiple wildcards: "abc" vs "a*b*c" → 1  
- Edge cases: empty strings, no match scenarios

**NMatch Function:**
- PDF examples: "abcbd" vs "*b*" → 2, "abc" vs "a**" → 3
- Complex patterns: Multiple consecutive wildcards
- Boundary cases: Single character, empty patterns

### Test Results: ✅ ALL PASSED
```bash
=== MATCH TESTS ===
match("main.c", "*.c") = 1 ✓
match("main.c", "*.*") = 1 ✓
match("abc", "a*b*c") = 1 ✓
match("", "*") = 1 ✓
[... 11 tests total, all passing]

=== NMATCH TESTS ===  
nmatch("abcbd", "*b*") = 2 ✓
nmatch("abc", "a**") = 3 ✓
nmatch("aba", "*a*") = 2 ✓
[... 9 tests total, all passing]
```

## Build & Compilation

### Library Build:
```bash
cd lib/my && ./build.sh
```

### Individual Function Build (per PDF):
```bash
gcc -o match *.c test_files/match_main.c -I./include -L./lib/my -lmy
gcc -o nmatch *.c test_files/nmatch_main.c -I./include -L./lib/my -lmy
```

### Comprehensive Testing:
```bash
./tests/test.sh  # Builds and runs all tests
```

## Evaluation Checklist

### Functionality:
- ✅ Match function correctly identifies string matches with wildcards
- ✅ NMatch function accurately counts all matching combinations
- ✅ Handles all PDF examples correctly
- ✅ Proper wildcard behavior (can match empty strings)
- ✅ Edge case handling (empty strings, no wildcards, NULL pointers)

### Technical Requirements:
- ✅ Uses only write() system call (through my_putchar)
- ✅ Delivers only match.c and nmatch.c
- ✅ Library structure in lib/my/ with build.sh
- ✅ Headers properly organized in include/
- ✅ Compiles without warnings
- ✅ Functions can be built separately

### Code Quality:
- ✅ Recursive algorithms are clean and maintainable
- ✅ Follows Epitech coding style
- ✅ Comprehensive test coverage
- ✅ Proper error handling for edge cases

## Algorithm Complexity

### Match Function:
- **Time**: O(2^n) worst case (exponential backtracking)
- **Space**: O(n) recursion depth
- **Optimizable**: Could use dynamic programming for overlapping subproblems

### NMatch Function:
- **Time**: O(2^n) worst case (explores all combinations)
- **Space**: O(n) recursion depth  
- **Behavior**: Counts all valid paths through pattern matching tree

## Risk Assessment

### Covered:
- ✅ Input validation (NULL pointers)
- ✅ Pattern edge cases (consecutive wildcards, empty patterns)
- ✅ String boundary conditions
- ✅ Memory safety (no dynamic allocation)

### Assumptions:
- Input strings are well-formed (null-terminated)
- Pattern complexity remains reasonable (no stack overflow)
- Only '*' character is used as wildcard

### Performance Considerations:
- Exponential complexity acceptable for typical use cases
- Real-world patterns usually don't trigger worst-case scenarios
- Could be optimized with memoization if needed

## Conclusion

The MatchNmatch project has been **successfully implemented** with:
- ✅ Complete functionality for both match() and nmatch() functions
- ✅ Correct handling of all PDF examples and edge cases
- ✅ Robust recursive algorithms with proper wildcard support
- ✅ Comprehensive testing demonstrating correctness
- ✅ Full compliance with build and delivery requirements
- ✅ Clean, maintainable code following Epitech standards

Both functions correctly implement string pattern matching with wildcard support, ready for evaluation and integration with the Epitech testing framework.