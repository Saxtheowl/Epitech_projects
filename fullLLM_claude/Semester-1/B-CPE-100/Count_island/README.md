# Count_island

> Timeline: 1 semaines

> Nombre de personnes sur le projet: 1

## Implementation Status: ✅ COMPLETED

### Description
Implementation of the count_island function for Epitech B-CPE-100 project. 

This program counts islands in a 2D grid where:
- '.' represents water
- 'X' represents land
- Connected 'X' characters form an island (4-directional connectivity)

The function replaces each 'X' with the island number (starting from 0) and returns the total number of islands found.

### Project Structure
```
Count_island/
├── include/my.h         # Header file
├── lib/my/             # Library directory
│   ├── build.sh        # Library build script
│   ├── my_putchar.c    # Character output
│   ├── my_putstr.c     # String output
│   ├── my_put_nbr.c    # Number output
│   └── my_strlen.c     # String length
├── tests/              # Test directory
│   ├── test_main.c     # Unit tests
│   └── test.sh         # Test runner
├── count_island.c      # Main implementation
├── test_map.c          # Map file tester
├── map.txt             # Test map
└── Makefile           # Build system
```

### Building & Testing

**Build library:**
```bash
cd lib/my && ./build.sh
```

**Build project:**
```bash
make
```

**Run tests:**
```bash
make test
```

### Test Results
- All unit tests pass ✅
- Correctly identifies 9 islands in provided map.txt ✅
- Islands are numbered 0-8 as required ✅

📂---[CountIsland.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Count_island/CountIsland.pdf)

|\_\_\_[Epitech_README.txt](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Count_island/Epitech_README.txt)

|\_\_\_[map.txt](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Count_island/map.txt)

|\_\_\_[main.o](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Count_island/main.o)


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
            <td rowspan="1">01 - Count Island</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>01 - Count island</td>
        </tr>
        <tr>
            <td rowspan="1">02 - Return Value</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>01 - Return value</td>
        </tr>
        <tr>
            <td rowspan="1">03 - Error handling</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>01 - Error handling</td>
        </tr>
	</tbody>
</table>
</details>


<br>

[↩️ Revenir au module](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100)

[↩️ Revenir au Semester-1](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1)

[↩️ Revenir à l'accueil](https://github.com/Studio-17/Epitech-Subjects)

<br>

---

<div align="center">

<a href="https://github.com/Studio-17" target="_blank"><img src="../../../assets/voc17.gif" width="40"></a>

</div>