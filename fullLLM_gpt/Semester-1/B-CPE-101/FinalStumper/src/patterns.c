#include <stddef.h>

static char rush_1_1_char(size_t x, size_t y, size_t width, size_t height)
{
    size_t last_col = width - 1;
    size_t last_row = height - 1;

    if ((x == 0 || x == last_col) && (y == 0 || y == last_row))
        return 'o';
    if (y == 0 || y == last_row)
        return '-';
    if (x == 0 || x == last_col)
        return '|';
    return ' ';
}

static char rush_1_2_char(size_t x, size_t y, size_t width, size_t height)
{
    size_t last_col = width - 1;
    size_t last_row = height - 1;

    if (width == 1 || height == 1)
        return '*';
    if (y == 0 && x == 0)
        return '/';
    if (y == 0 && x == last_col)
        return '\\';
    if (y == last_row && x == 0)
        return '\\';
    if (y == last_row && x == last_col)
        return '/';
    if (y == 0 || y == last_row || x == 0 || x == last_col)
        return '*';
    return ' ';
}

static char rush_1_3_char(size_t x, size_t y, size_t width, size_t height)
{
    if (width == 1 || height == 1)
        return 'B';
    size_t last_col = width - 1;
    size_t last_row = height - 1;

    if (y == 0 && (x == 0 || x == last_col))
        return 'A';
    if (y == last_row && (x == 0 || x == last_col))
        return 'C';
    if (y == 0 || y == last_row || x == 0 || x == last_col)
        return 'B';
    return ' ';
}

static char rush_1_4_char(size_t x, size_t y, size_t width, size_t height)
{
    if (width == 1 || height == 1)
        return 'B';
    size_t last_col = width - 1;
    size_t last_row = height - 1;

    if (y == 0 && x == 0)
        return 'A';
    if (y == 0 && x == last_col)
        return 'C';
    if (y == last_row && x == 0)
        return 'A';
    if (y == last_row && x == last_col)
        return 'C';
    if (y == 0 || y == last_row || x == 0 || x == last_col)
        return 'B';
    return ' ';
}

static char rush_1_5_char(size_t x, size_t y, size_t width, size_t height)
{
    if (width == 1 || height == 1)
        return 'B';
    size_t last_col = width - 1;
    size_t last_row = height - 1;

    if (y == 0 && x == 0)
        return 'A';
    if (y == 0 && x == last_col)
        return 'C';
    if (y == last_row && x == 0)
        return 'C';
    if (y == last_row && x == last_col)
        return 'A';
    if (y == 0 || y == last_row || x == 0 || x == last_col)
        return 'B';
    return ' ';
}

typedef char (*pattern_func)(size_t, size_t, size_t, size_t);

typedef struct {
    const char *name;
    pattern_func func;
} pattern_entry_t;

const pattern_entry_t *get_pattern_table(size_t *count)
{
    static const pattern_entry_t patterns[] = {
        {"rush1-1", rush_1_1_char},
        {"rush1-2", rush_1_2_char},
        {"rush1-3", rush_1_3_char},
        {"rush1-4", rush_1_4_char},
        {"rush1-5", rush_1_5_char},
    };
    if (count)
        *count = sizeof(patterns) / sizeof(patterns[0]);
    return patterns;
}
