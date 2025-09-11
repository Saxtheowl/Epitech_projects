/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_sort_params.c - TASK 06
*/

void my_putchar(char c);
int my_putstr(char const *str);
int my_strcmp(char const *s1, char const *s2);

static void my_swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char **argv)
{
    int i, j;
    
    for (i = 1; i < argc - 1; i++) {
        for (j = i + 1; j < argc; j++) {
            if (my_strcmp(argv[i], argv[j]) > 0) {
                my_swap(&argv[i], &argv[j]);
            }
        }
    }
    
    for (i = 0; i < argc; i++) {
        my_putstr(argv[i]);
        my_putchar('\n');
    }
    
    return 0;
}