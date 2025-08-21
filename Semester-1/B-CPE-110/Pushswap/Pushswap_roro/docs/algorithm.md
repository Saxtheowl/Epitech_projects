# Pushswap Algorithm Documentation

## Overview
The Pushswap project implements a sorting algorithm using two stacks (lists) with a limited set of operations. The goal is to sort the first stack using the minimum number of operations.

## Available Operations

### Swap Operations
- **sa**: Swap the first two elements of list A
- **sb**: Swap the first two elements of list B  
- **sc**: Execute sa and sb simultaneously

### Push Operations
- **pa**: Push first element from B to top of A
- **pb**: Push first element from A to top of B

### Rotate Operations
- **ra**: Rotate A upward (first becomes last)
- **rb**: Rotate B upward (first becomes last)
- **rr**: Execute ra and rb simultaneously

### Reverse Rotate Operations
- **rra**: Rotate A downward (last becomes first)
- **rrb**: Rotate B downward (last becomes first)
- **rrr**: Execute rra and rrb simultaneously

## Algorithm Strategy

### Small Lists (≤ 5 elements)
For small lists, we use a simple strategy:
1. Find the minimum element
2. Rotate it to the top using the shortest path (ra or rra)
3. Push to B if not sorted
4. Push back from B when needed

### Large Lists (> 5 elements)
For larger lists, we use a divide-and-conquer approach:
1. Calculate a rough median value
2. Push elements smaller than median to B
3. Rotate larger elements in A
4. Recursively sort remaining elements in A (≤ 3)
5. Push all elements back from B to A

## Implementation Details

### Data Structures
- **node_t**: Linked list node with integer value and next pointer
- **list_t**: List structure with head pointer and size counter
- **game_t**: Game state with both lists and operations tracking

### Operation Tracking
- Operations are stored in a dynamically allocated string
- Each operation is separated by spaces
- Final output excludes leading/trailing spaces

### Error Handling
- Invalid numbers return error code 84
- Duplicate numbers return error code 84
- Already sorted lists output nothing (empty line)
- Single element or empty input outputs nothing

## Complexity Analysis
- **Time Complexity**: O(n²) for worst case, O(n log n) average
- **Space Complexity**: O(n) for the second list and operation storage
- **Operation Count**: Optimized to minimize the number of operations

## Edge Cases
1. **Empty input**: No output, exit code 0
2. **Single element**: No output, exit code 0
3. **Already sorted**: No output, exit code 0
4. **Reverse sorted**: Maximum operations needed
5. **Duplicates**: Error output, exit code 84
6. **Invalid input**: Error output, exit code 84