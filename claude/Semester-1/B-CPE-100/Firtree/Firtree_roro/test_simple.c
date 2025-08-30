/*
** EPITECH PROJECT, 2024
** test_simple.c
** File description:
** simple test to compare outputs
*/

void tree(int size);
int my_putchar(char c);

int main(int argc, char **argv)
{
    if (argc == 2) {
        tree(argv[1][0] - '0');
    }
    return 0;
}