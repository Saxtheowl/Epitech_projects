#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;

    return s1[i] - s2[i];
}

void sort_args(char **argv, int argc)
{
    int i = 0;
    int j = 0;
    char *temp;

    while (i < argc - 1) {
        j = i + 1;
        while (j < argc) {
            if (my_strcmp(argv[i], argv[j]) > 0) {
                temp = argv[i];
                argv[i] = argv[j];
                argv[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    int i = 0;

    sort_args(argv, argc);

    while (i < argc) {
        my_putstr(argv[i]);
        my_putchar('\n');
        i++;
    }
    return 0;
}