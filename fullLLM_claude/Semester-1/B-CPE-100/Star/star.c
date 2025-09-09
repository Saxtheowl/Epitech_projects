int my_putchar(char c);

static void print_spaces(int count)
{
    int i = 0;
    while (i < count) {
        my_putchar(' ');
        i++;
    }
}

static void print_stars(int count)
{
    int i = 0;
    while (i < count) {
        my_putchar('*');
        i++;
    }
}

static void print_line_with_pattern(int total_width, int left_stars, int middle_spaces, int right_stars)
{
    int left_spaces = (total_width - left_stars - middle_spaces - right_stars) / 2;
    
    print_spaces(left_spaces);
    if (left_stars > 0)
        print_stars(left_stars);
    if (middle_spaces > 0)
        print_spaces(middle_spaces);
    if (right_stars > 0)
        print_stars(right_stars);
    my_putchar('\n');
}

static void print_top_spike(unsigned int size)
{
    int total_width = 4 * size + 1;
    unsigned int i;
    
    for (i = 0; i < size; i++) {
        if (i == 0) {
            print_line_with_pattern(total_width, 1, 0, 0);
        } else {
            int spacing = 2 * i - 1;
            print_line_with_pattern(total_width, 1, spacing, 1);
        }
    }
}

static void print_horizontal_bars(unsigned int size)
{
    int total_width = 4 * size + 1;
    int bar_width = 2 * size + 1;
    int middle_gap = 2 * size - 1;
    
    print_line_with_pattern(total_width, bar_width, middle_gap, bar_width);
}

static void print_middle_section(unsigned int size)
{
    int total_width = 4 * size + 1;
    unsigned int i;
    
    for (i = 0; i < 2 * size - 1; i++) {
        int inner_spacing = 4 * size - 1;
        print_line_with_pattern(total_width, 1, inner_spacing, 1);
    }
}

static void print_bottom_spike(unsigned int size)
{
    int total_width = 4 * size + 1;
    int i;
    
    for (i = size - 1; i >= 0; i--) {
        if (i == 0) {
            print_line_with_pattern(total_width, 1, 0, 0);
        } else {
            int spacing = 2 * i - 1;
            print_line_with_pattern(total_width, 1, spacing, 1);
        }
    }
}

void star(unsigned int size)
{
    if (size == 0)
        return;
    
    if (size == 1) {
        print_spaces(3); my_putchar('*'); my_putchar('\n');
        print_stars(3); my_putchar(' '); print_stars(3); my_putchar('\n');
        print_spaces(1); my_putchar('*'); print_spaces(3); my_putchar('*'); my_putchar('\n');
        print_stars(3); my_putchar(' '); print_stars(3); my_putchar('\n');
        print_spaces(3); my_putchar('*'); my_putchar('\n');
        return;
    }
    
    print_top_spike(size);
    print_horizontal_bars(size);
    print_middle_section(size);
    print_horizontal_bars(size);
    print_bottom_spike(size);
}