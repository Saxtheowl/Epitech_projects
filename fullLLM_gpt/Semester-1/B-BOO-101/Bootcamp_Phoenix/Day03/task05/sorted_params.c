#include <stdlib.h>
#include "phoenix.h"

static int string_length(char const *str)
{
    int len = 0;

    while (str && str[len] != '\0') {
        ++len;
    }
    return len;
}

static int compare_strings(char const *a, char const *b)
{
    int index = 0;

    while (a && b) {
        char ca = a[index];
        char cb = b[index];

        if (ca != cb || ca == '\0' || cb == '\0') {
            return (unsigned char)ca - (unsigned char)cb;
        }
        ++index;
    }
    return string_length(a) - string_length(b);
}

static void sort_arguments(int argc, char **argv)
{
    for (int i = 0; i < argc - 1; ++i) {
        for (int j = i + 1; j < argc; ++j) {
            if (compare_strings(argv[i], argv[j]) > 0) {
                char *tmp = argv[i];
                argv[i] = argv[j];
                argv[j] = tmp;
            }
        }
    }
}

int main(int argc, char **argv)
{
    sort_arguments(argc, argv);
    for (int i = 0; i < argc; ++i) {
        show_string(argv[i]);
        my_putchar('\n');
    }
    return EXIT_SUCCESS;
}
