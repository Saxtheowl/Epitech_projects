#include <stddef.h>
#include <stdlib.h>
#include "../include/rush3.h"

size_t my_strlen(const char *str);
int my_is_printable(char c);

typedef char (*pattern_func)(size_t, size_t, size_t, size_t);

typedef struct {
    const char *name;
    pattern_func func;
} pattern_entry_t;

const pattern_entry_t *get_pattern_table(size_t *count);

static int compute_dimensions(const char *input, size_t *width, size_t *height)
{
    size_t w = 0;
    size_t h = 0;
    const char *ptr = input;

    if (!input || *input == '\0')
        return 0;
    while (ptr[w] && ptr[w] != '\n')
        ++w;
    if (w == 0)
        return 0;
    while (*ptr) {
        size_t line_len = 0;
        while (ptr[line_len] && ptr[line_len] != '\n')
            ++line_len;
        if (line_len != w)
            return 0;
        ++h;
        ptr += line_len;
        if (*ptr == '\n')
            ++ptr;
        else
            break;
    }
    if (*ptr != '\0')
        return 0;
    *width = w;
    *height = h;
    return (w > 0 && h > 0);
}

static int matches_pattern(const pattern_entry_t *pattern, const char *input,
                           size_t width, size_t height)
{
    const char *ptr = input;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            char expected = pattern->func(x, y, width, height);
            if (*ptr != expected)
                return 0;
            ++ptr;
        }
        if (y + 1 < height) {
            if (*ptr != '\n')
                return 0;
            ++ptr;
        } else if (*ptr == '\n') {
            ++ptr;
        }
    }
    return *ptr == '\0';
}

void rush3(const char *input)
{
    size_t width = 0;
    size_t height = 0;
    size_t pattern_count = 0;
    const pattern_entry_t *patterns = get_pattern_table(&pattern_count);
    int first = 1;
    int found = 0;

    if (!compute_dimensions(input, &width, &height)) {
        my_putstr("none\n");
        return;
    }
    for (size_t i = 0; i < pattern_count; ++i) {
        if (matches_pattern(&patterns[i], input, width, height)) {
            if (!first)
                my_putstr(" || ");
            my_putstr("[");
            my_putstr(patterns[i].name);
            my_putstr("] ");
            my_putnbr_unsigned(width);
            my_putstr(" ");
            my_putnbr_unsigned(height);
            first = 0;
            found = 1;
        }
    }
    if (!found)
        my_putstr("none");
    my_putchar('\n');
}
