# Minishell2

> Timeline: 3 semaines

> Nombre de personnes sur le projet: 1

<br>

📂---[Bootstrap_minishell2](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-2/B-PSU-200/Minishell2/Bootstrap_minishell2)

ㅤㅤ|\_\_\_[Minishell2_bootstrap.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-2/B-PSU-200/Minishell2/Bootstrap_minishell2/Minishell2_bootstrap.pdf)

|\_\_\_[Minishell2](https://github.com/Studio-17/Epitech-Subjects/tree/main/Semester-2/B-PSU-200/Minishell2/Minishell2)

ㅤㅤ|\_\_\_[Minishell2.pdf](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-2/B-PSU-200/Minishell2/Minishell2/Minishell2.pdf)

ㅤㅤ|\_\_\_[tester.tgz](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-2/B-PSU-200/Minishell2/Minishell2/tester.tgz)


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
            <td rowspan="5">01 - basic tests</td>
            <td rowspan="5" style="text-align: center;">5</td>
            <td>Empty</td>
        </tr>
    		<tr>
			<td>SegFault without core dump</td>
		</tr>
		<tr>
			<td>Simple exec</td>
		</tr>
		<tr>
			<td>run simple commands</td>
		</tr>
		<tr>
			<td>wrong simple command</td>
		</tr>
        <tr>
            <td rowspan="5">02 - path handling</td>
            <td rowspan="5" style="text-align: center;">5</td>
            <td>PATH 1</td>
        </tr>
    		<tr>
			<td>PATH 2</td>
		</tr>
		<tr>
			<td>PATH 3</td>
		</tr>
		<tr>
			<td>PATH 4</td>
		</tr>
		<tr>
			<td>PATH 5</td>
		</tr>
        <tr>
            <td rowspan="5">02 - path handling - eval</td>
            <td rowspan="5" style="text-align: center;">5</td>
            <td>PATH 1</td>
        </tr>
    		<tr>
			<td>PATH 2</td>
		</tr>
		<tr>
			<td>PATH 3</td>
		</tr>
		<tr>
			<td>PATH 4</td>
		</tr>
		<tr>
			<td>PATH 5</td>
		</tr>
        <tr>
            <td rowspan="2">03 - setenv and unsetenv</td>
            <td rowspan="2" style="text-align: center;">2</td>
            <td>setenv and unsetenv</td>
        </tr>
    		<tr>
			<td>setenv and unsetenv with special values</td>
		</tr>
        <tr>
            <td rowspan="2">03 - setenv and unsetenv - eval</td>
            <td rowspan="2" style="text-align: center;">2</td>
            <td>setenv and unsetenv</td>
        </tr>
    		<tr>
			<td>setenv and unsetenv with special values</td>
		</tr>
        <tr>
            <td rowspan="3">04 - builtin cd</td>
            <td rowspan="3" style="text-align: center;">3</td>
            <td>cd</td>
        </tr>
    		<tr>
			<td>cd and error messages</td>
		</tr>
		<tr>
			<td>cd-</td>
		</tr>
        <tr>
            <td rowspan="3">04 - builtin cd - eval</td>
            <td rowspan="3" style="text-align: center;">3</td>
            <td>cd</td>
        </tr>
    		<tr>
			<td>cd and error messages</td>
		</tr>
		<tr>
			<td>cd-</td>
		</tr>
        <tr>
            <td rowspan="8">05 - line formatting (space and tabs)</td>
            <td rowspan="8" style="text-align: center;">8</td>
            <td>space 1</td>
        </tr>
    		<tr>
			<td>space 2</td>
		</tr>
		<tr>
			<td>space 3</td>
		</tr>
		<tr>
			<td>space 4</td>
		</tr>
		<tr>
			<td>space and tab</td>
		</tr>
		<tr>
			<td>tab 1</td>
		</tr>
		<tr>
			<td>tab 2</td>
		</tr>
		<tr>
			<td>tab 3</td>
		</tr>
        <tr>
            <td rowspan="8">05 - line formatting (space and tabs) - eval</td>
            <td rowspan="8" style="text-align: center;">8</td>
            <td>space 1</td>
        </tr>
    		<tr>
			<td>space 2</td>
		</tr>
		<tr>
			<td>space 3</td>
		</tr>
		<tr>
			<td>space 4</td>
		</tr>
		<tr>
			<td>space and tab</td>
		</tr>
		<tr>
			<td>tab 1</td>
		</tr>
		<tr>
			<td>tab 2</td>
		</tr>
		<tr>
			<td>tab 3</td>
		</tr>
        <tr>
            <td rowspan="3">06 - error handling</td>
            <td rowspan="3" style="text-align: center;">3</td>
            <td>Bin not compatible</td>
        </tr>
    		<tr>
			<td>SegFault with core dump</td>
		</tr>
		<tr>
			<td>exec a directory</td>
		</tr>
        <tr>
            <td rowspan="3">06 - error handling - eval</td>
            <td rowspan="3" style="text-align: center;">3</td>
            <td>Bin not compatible</td>
        </tr>
    		<tr>
			<td>SegFault without core dump</td>
		</tr>
		<tr>
			<td>exec a directory</td>
		</tr>
        <tr>
            <td rowspan="5">07 - separator</td>
            <td rowspan="5" style="text-align: center;">5</td>
            <td>advanced separator 1</td>
        </tr>
    		<tr>
			<td>advanced separator 2</td>
		</tr>
		<tr>
			<td>complex separator</td>
		</tr>
		<tr>
			<td>multiple separator</td>
		</tr>
		<tr>
			<td>separator basic</td>
		</tr>
        <tr>
            <td rowspan="4">08 - simple pipe</td>
            <td rowspan="4" style="text-align: center;">4</td>
            <td>pipe with big input</td>
        </tr>
    		<tr>
			<td>simple pipe 1</td>
		</tr>
		<tr>
			<td>simple pipe 2</td>
		</tr>
		<tr>
			<td>simple pipe 3</td>
		</tr>
        <tr>
            <td rowspan="2">09 - simple redirections</td>
            <td rowspan="2" style="text-align: center;">2</td>
            <td>output double-redirect</td>
        </tr>
    		<tr>
			<td>output redirect</td>
		</tr>
        <tr>
            <td rowspan="7">10 - advanced pipe</td>
            <td rowspan="7" style="text-align: center;">7</td>
            <td>Multipipe and Error</td>
        </tr>
    		<tr>
			<td>Pipe with builtin</td>
		</tr>
		<tr>
			<td>error and pipe</td>
		</tr>
		<tr>
			<td>multipipe</td>
		</tr>
		<tr>
			<td>multipipe and FDMAX</td>
		</tr>
		<tr>
			<td>only a pipe</td>
		</tr>
		<tr>
			<td>pipe and error</td>
		</tr>
        <tr>
            <td rowspan="1">11 - advanced redirections</td>
            <td rowspan="1" style="text-align: center;">1</td>
            <td>redirect on bin and big files</td>
        </tr>
        <tr>
            <td rowspan="4">12 - advanced manipulations</td>
            <td rowspan="4" style="text-align: center;">4</td>
            <td>Long command line with multiple redirect and pipe</td>
        </tr>
    		<tr>
			<td>empty seperator</td>
		</tr>
		<tr>
			<td>redirect output on input</td>
		</tr>
		<tr>
			<td>running mysh inside mysh</td>
		</tr>
	</tbody>
</table>
</details>

<br>

[↩️ Revenir au module](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-2/B-PSU-200)

[↩️ Revenir au Semester-2](https://github.com/Studio-17/Epitech-Subjects/blob/main/Semester-2)

[↩️ Revenir à l'accueil](https://github.com/Studio-17/Epitech-Subjects)

<br>

---

<div align="center">

<a href="https://github.com/Studio-17" target="_blank"><img src="../../../assets/voc17.gif" width="40"></a>

</div>