/*
** EPITECH PROJECT, 2024
** show_combinations
** File description:
** Display all combinations of three different digits in ascending order
*/

int my_putchar(char c);

int show_combinations(void)
{
    int a, b, c;
    int first = 1;

    for (a = 0; a <= 7; a++) {
        for (b = a + 1; b <= 8; b++) {
            for (c = b + 1; c <= 9; c++) {
                if (!first) {
                    my_putchar(',');
                    my_putchar(' ');
                }
                my_putchar(a + '0');
                my_putchar(b + '0');
                my_putchar(c + '0');
                first = 0;
            }
        }
    }
    return 0;
}