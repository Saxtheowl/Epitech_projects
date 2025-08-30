/*
** EPITECH PROJECT, 2024
** test_main.c
** File description:
** simple test for star function
*/

void star(unsigned int size);

int main(int argc, char **argv)
{
    if (argc == 2) {
        star(argv[1][0] - '0');
    } else {
        star(0);
        star(1);
        star(2);
    }
    return 0;
}