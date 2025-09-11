/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_params.c - TASK 04
*/

void my_putchar(char c);
int my_putstr(char const *str);

int main(int argc, char **argv)
{
    int i = 0;
    
    while (i < argc) {
        my_putstr(argv[i]);
        my_putchar('\n');
        i++;
    }
    
    return 0;
}