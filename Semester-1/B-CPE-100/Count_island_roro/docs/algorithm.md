# Count Island Algorithm Documentation

## Overview
The Count Island project implements a flood fill algorithm to count and number connected islands of 'X' characters in a 2D matrix.

## Algorithm Description

### Core Function: `count_island(char **world)`
- **Input**: A 2D array of characters where 'X' represents island cells
- **Output**: Integer representing the total number of islands found
- **Side Effect**: Replaces 'X' characters with their island number (0, 1, 2, ...)

### Flood Fill Implementation
The algorithm uses recursive flood fill to identify connected components:

1. **Main Loop**: Iterate through every cell in the 2D matrix
2. **Island Detection**: When an 'X' is found, start a flood fill
3. **Flood Fill Process**:
   - Mark current cell with island ID (converted to character)
   - Recursively visit all 4 adjacent cells (up, down, left, right)
   - Continue until no more connected 'X' cells are found
4. **Island Counting**: Increment counter after each complete flood fill

### Key Functions

#### `flood_fill(char **world, int x, int y, int rows, int cols, int island_id)`
- Recursively marks all connected 'X' cells with the island ID
- Uses bounds checking to prevent array access errors
- Modifies the original matrix in-place

#### `is_valid_position(char **world, int x, int y, int rows, int cols)`
- Validates coordinates are within matrix bounds
- Checks if the cell contains an 'X' character
- Returns 1 if valid position with 'X', 0 otherwise

## Complexity Analysis
- **Time Complexity**: O(n × m) where n and m are matrix dimensions
- **Space Complexity**: O(n × m) in worst case due to recursion depth
- Each cell is visited exactly once during the flood fill process

## Example
Input matrix:
```
X.X
.X.
X.X
```

After processing:
```
0.1
.2.
3.4
```

Return value: 5 (five separate islands found)

## Edge Cases Handled
- Empty matrix (no 'X' characters): returns 0
- NULL pointer input: returns 0
- Single cell islands: properly counted
- Large connected islands: correctly identified as single island
- Matrix with no islands: returns 0