# BSQ - Biggest Square Finder

## Description
BSQ finds the largest possible square in a 2D grid while avoiding obstacles. The program uses dynamic programming to efficiently solve this classic algorithmic problem.

## Algorithm
The implementation uses a dynamic programming approach with a memoization matrix:
1. **DP Matrix**: `dp[i][j]` represents the side length of the largest square ending at position (i,j)
2. **Recurrence**: `dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1` if cell is empty
3. **Base Case**: `dp[i][j] = 0` if cell contains obstacle, `1` for border cells
4. **Solution**: Track maximum value and its position during matrix filling

## Input Format
```
<number_of_lines>
<line1_with_dots_and_obstacles>
<line2_with_dots_and_obstacles>
...
```
- `.` represents empty space
- `o` represents obstacle
- All lines must have same length
- Each line ends with `\\n`

## Output
The program prints the input grid with the largest square filled with `x` characters.
Priority: highest square first, then leftmost if tied.

## Usage
```bash
make
./bsq map_file
```

## Testing
```bash
make tests_run
```

## Implementation Strategy
- **Memory Management**: Proper allocation/deallocation of 2D arrays
- **File Parsing**: Robust parsing with validation
- **Error Handling**: Returns 84 on any error as per Epitech standards
- **Algorithm Complexity**: O(n*m) time, O(n*m) space

## Constraints
- Uses only allowed system calls: open, read, write, close, malloc, free, stat
- Follows Epitech C coding style
- No external libraries beyond standard system calls