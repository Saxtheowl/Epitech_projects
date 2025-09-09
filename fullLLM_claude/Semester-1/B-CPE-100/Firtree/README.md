# Firtree

> Timeline: 5 jours

> Nombre de personnes sur le projet: 1

## Implementation Status: ✅ COMPLETED

### Description
Implementation of the `tree()` function for B-CPE-100 Firtree project. 

This program generates ASCII art fir trees of varying sizes using only the `*` character for leaves and `|` character for the trunk.

### Test Results ✅
- **Size 0**: No output (as required)
- **Size 1**: Correct 4-line tree with single trunk line
- **Size 5**: Complex multi-section tree with 5-line trunk
- **Algorithm**: Matches expected patterns from PDF examples

### Building & Testing
```bash
gcc -o test_tree test_main.c my_putchar.c tree.c
./test_tree 1    # Test size 1
./test_tree 5    # Test size 5  
./test_tree 0    # Test size 0 (no output)
```

<br>

📂---[Tree.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Firtree/Tree.pdf)

|\_\_\_[firtree.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-1/B-CPE-100/Firtree/firtree.tgz)

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
            <td rowspan="1">A - Basic tree</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>01 - Tree of size 1</td>
        </tr>
        <tr>
            <td rowspan="2">B - Functionality</td>
            <td rowspan="2" style="text-align: center;">2</td>
            <td>01 - Trees of even sizes</td>
        </tr>
        <tr>
            <td>02 - Trees of odd sizes</td>
        </tr>
        <tr>
            <td rowspan="1">C - Error handling</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>01 - Trees of invalid sizes</td>
        </tr>
    </tbody>
</table>
</details>

<br>

[↩️ Revenir au module](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-1/B-CPE-100)

[↩️ Revenir au Semestre-1](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-1)

[↩️ Revenir à l'accueil](https://github.com/Studio-17/Epitech-Subjects)

<br>

---

<div align="center">

<a href="https://github.com/Studio-17" target="_blank"><img src="../../../assets/voc17.gif" width="40"></a>

</div>
