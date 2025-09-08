# Day01 - Welcome Back (IMPLEMENTED)

> Timeline: 48h

> Nombre de personnes sur le projet: 1

## Overview
Phoenix Bootcamp Day01 - Implementation of 6 basic C programming tasks focusing on fundamental string and number operations.

## Tasks Implemented

### Task 01 - show_alphabet ✅
- **File**: `show_alphabet.c`
- **Function**: `int show_alphabet(void)`
- **Description**: Displays the lowercase alphabet in ascending order on a single line

### Task 02 - show_combinations ✅
- **File**: `show_combinations.c`
- **Function**: `int show_combinations(void)`
- **Description**: Displays all combinations of three different digits in ascending order (012, 013, ..., 789)

### Task 03 - show_number ✅
- **File**: `show_number.c`
- **Function**: `int show_number(int nb)`
- **Description**: Displays any integer including handling INT_MIN (-2147483648)

### Task 04 - show_string ✅
- **File**: `show_string.c`
- **Function**: `int show_string(char const *str)`
- **Description**: Displays characters of a string one-by-one

### Task 05 - reverse_string ✅
- **File**: `reverse_string.c`
- **Function**: `char *reverse_string(char *str)`
- **Description**: Reverses a string by swapping characters two by two

### Task 06 - to_number ✅
- **File**: `to_number.c`
- **Function**: `int to_number(char const *str)`
- **Description**: Converts a string to integer with complex parsing and overflow handling

## Build Instructions

```bash
make        # Compile all object files
make test   # Build and run comprehensive tests
make clean  # Remove object files
make fclean # Remove all generated files
```

## Testing
The project includes comprehensive tests in the `tests/` directory:
- `test_main.c`: Main test program covering all functions
- `my_putchar.c`: Helper function for character output

Run tests with: `make test`

## Constraints
- Only `my_putchar` function allowed for output
- Error handling with exit code 84 for errors
- Must handle integer overflow in `to_number`
- Proper string manipulation without segmentation faults

<br>

📂---[day01.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-BOO-101/Bootcamp_Phoenix/Day01/day01.pdf)

<br>

<details>
<summary> Tests de la moulinette </summary>
<table align="center">
    <thead>
    <tr>
            <td colspan="3" align="center"><strong>MOULINETTE</strong></td>
    </tr>
        <tr>
            <th>SOMMAIRE</th>
            <th>NB DE TESTS</th>
            <th>DETAILS</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="1">01 - task01</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task01</td>
        </tr>
        <tr>
            <td rowspan="1">02 - task02</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task02</td>
        </tr>
        <tr>
            <td rowspan="1">03 - task03</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task03</td>
        </tr>
        <tr>
            <td rowspan="1">04 - task04</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task04</td>
        </tr>
        <tr>
            <td rowspan="1">05 - task05</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task05</td>
        </tr>
        <tr>
            <td rowspan="1">06 - task06</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>task06</td>
        </tr>
    </tbody>
</table>
</details>

<br>

[↩️ Revenir au projet](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-1/B-BOO-101/Bootcamp_Phoenix)

[↩️ Revenir au module](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-1/B-BOO-101)

[↩️ Revenir au Semestre-1](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-1)

[↩️ Revenir à l'accueil](https://github.com/Studio-17/Epitech-Subjects)

<br>

---

<div align="center">

<a href="https://github.com/Studio-17" target="_blank"><img src="../../../../assets/voc17.gif" width="40"></a>

</div>
