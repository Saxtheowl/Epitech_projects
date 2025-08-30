/*
** EPITECH PROJECT, 2024
** tree.c
** File description:
** fir tree implementation - main deliverable
*/

void my_putchar(char c);

static void print_spaces(int count)
{
    int i = 0;

    for (i = 0; i < count; i++)
        my_putchar(' ');
}

static void print_stars(int count)
{
    int i = 0;

    for (i = 0; i < count; i++)
        my_putchar('*');
}

static void print_line(int stars, int max_width)
{
    int spaces = (max_width - stars) / 2;

    print_spaces(spaces);
    print_stars(stars);
    my_putchar('\n');
}

static void print_trunk(int size, int max_width)
{
    int i = 0;
    int j = 0;
    int trunk_width = size;
    int spaces = (max_width - trunk_width) / 2;

    for (i = 0; i < size; i++) {
        print_spaces(spaces);
        for (j = 0; j < trunk_width; j++)
            my_putchar('|');
        my_putchar('\n');
    }
}

static int get_max_width(int size)
{
    int i = 0;
    int max_stars = 0;

    if (size <= 0)
        return 0;
    if (size == 1)
        return 7;
    
    for (i = 0; i < size; i++)
        max_stars += (3 + i) * 2 + 1;
    return max_stars;
}

void tree(int size)
{
    int max_width = 0;
    int section = 0;
    int line = 0;
    int stars = 0;
    int lines_per_section = 0;
    int section_start_width = 0;

    if (size <= 0)
        return;
    
    max_width = (size == 1) ? 7 : 2 * (size * 2 + size + 5) + 1;
    
    if (size == 1) {
        print_line(1, 7);
        print_line(3, 7);
        print_line(5, 7);
        print_line(7, 7);
        print_trunk(1, 7);
        return;
    }

    section_start_width = 1;
    for (section = 0; section < size; section++) {
        lines_per_section = 3 + section;
        
        for (line = 0; line < lines_per_section; line++) {
            stars = section_start_width + line * 2;
            print_line(stars, max_width);
        }
        
        if (section < size - 1)
            section_start_width = section_start_width + 2 * (lines_per_section - 1) - 2;
    }
    
    print_trunk(size, max_width);
}