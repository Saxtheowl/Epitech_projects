#include <stdlib.h>
#include <unistd.h>
#include "phoenix.h"

static void write_usage(void)
{
    static const char message[] = "Usage: ./star <number>\n";

    write(2, message, sizeof(message) - 1);
}

static int parse_size(char const *str, int *size)
{
    long value = 0;

    if (!str || !*str) {
        return -1;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
        value = value * 10 + (str[i] - '0');
        if (value > 10000) {
            return -1;
        }
    }
    *size = (int)value;
    return 0;
}

static void print_chars(char c, int count)
{
    for (int i = 0; i < count; ++i) {
        my_putchar(c);
    }
}

static void print_single_line(int leading)
{
    print_chars(' ', leading);
    my_putchar('*');
    my_putchar('\n');
}

static void print_double_line(int left, int right)
{
    print_chars(' ', left);
    my_putchar('*');
    print_chars(' ', right - left - 1);
    my_putchar('*');
    my_putchar('\n');
}

static void print_horizontal_bar(int size, int gap)
{
    int segment = 2 * size + 1;

    print_chars('*', segment);
    print_chars(' ', gap);
    print_chars('*', segment);
    my_putchar('\n');
}

static void draw_star(int size)
{
    int gap = (size >= 2) ? (2 * size - 3) : 1;
    int width = 4 * size + 2 + gap;
    int center = width / 2;
    int diamond_lines = 2 * size - 1;

    for (int i = 0; i < size; ++i) {
        int left = center - i;
        int right = center + i;

        if (left == right) {
            print_single_line(left);
        } else {
            print_double_line(left, right);
        }
    }
    print_horizontal_bar(size, gap);
    for (int i = 0; i < diamond_lines; ++i) {
        int offset = (i < size) ? i : (diamond_lines - 1 - i);
        int left = offset + 1;
        int right = width - 2 - offset;

        print_double_line(left, right);
    }
    print_horizontal_bar(size, gap);
    for (int i = size - 1; i >= 0; --i) {
        int left = center - i;
        int right = center + i;

        if (left == right) {
            print_single_line(left);
        } else {
            print_double_line(left, right);
        }
    }
}

int main(int argc, char **argv)
{
    int size = 0;

    if (argc != 2 || parse_size(argv[1], &size) != 0) {
        write_usage();
        return 84;
    }
    if (size == 0) {
        return EXIT_SUCCESS;
    }
    draw_star(size);
    return EXIT_SUCCESS;
}
