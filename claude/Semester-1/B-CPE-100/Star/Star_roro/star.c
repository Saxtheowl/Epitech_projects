/*
** EPITECH PROJECT, 2024
** star.c
** File description:
** star function implementation
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

static void star_size_1(void)
{
    print_spaces(3);
    my_putchar('*');
    my_putchar('\n');
    
    print_stars(3);
    my_putchar(' ');
    print_stars(3);
    my_putchar('\n');
    
    print_spaces(1);
    my_putchar('*');
    print_spaces(3);
    my_putchar('*');
    my_putchar('\n');
    
    print_stars(3);
    my_putchar(' ');
    print_stars(3);
    my_putchar('\n');
    
    print_spaces(3);
    my_putchar('*');
    my_putchar('\n');
}

static void print_star_top(unsigned int size)
{
    unsigned int i = 0;
    unsigned int spaces = 0;
    unsigned int total_width = size * 4 + 7;

    for (i = 0; i <= size; i++) {
        spaces = total_width / 2 - i;
        print_spaces(spaces);
        my_putchar('*');
        if (i > 0) {
            print_spaces(2 * i - 1);
            my_putchar('*');
        }
        my_putchar('\n');
    }
}

static void print_horizontal_bar(unsigned int size)
{
    print_stars(size * 2 + 1);
    print_spaces(size * 2 + 5);
    print_stars(size * 2 + 1);
    my_putchar('\n');
}

static void print_middle_section(unsigned int size)
{
    unsigned int i = 0;
    unsigned int spaces_left = 1;
    unsigned int spaces_middle = size * 4 + 3;

    for (i = 0; i < size * 2; i++) {
        print_spaces(spaces_left);
        my_putchar('*');
        print_spaces(spaces_middle);
        my_putchar('*');
        my_putchar('\n');
        
        if (i < size - 1) {
            spaces_left++;
            spaces_middle -= 2;
        } else {
            spaces_left--;
            spaces_middle += 2;
        }
    }
}

void star(unsigned int size)
{
    if (size == 0)
        return;
    
    if (size == 1) {
        star_size_1();
        return;
    }
    
    print_star_top(size);
    print_horizontal_bar(size);
    print_middle_section(size);
    print_horizontal_bar(size);
    print_star_top(size);
}