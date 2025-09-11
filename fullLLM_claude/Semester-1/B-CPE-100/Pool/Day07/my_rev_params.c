/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_rev_params.c - TASK 05
*/

void my_putchar(char c);
int my_putstr(char const *str);

int main(int argc, char **argv)
{
    int i = argc - 1;
    
    while (i >= 0) {
        my_putstr(argv[i]);
        my_putchar('\n');
        i--;
    }
    
    return 0;
}