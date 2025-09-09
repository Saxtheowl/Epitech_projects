int my_putchar(char c);




static void print_tree_part(int size, int max_width)
{
    int section;
    int i, j;
    
    for (section = 0; section < size; section++) {
        int section_height = 4 + section;
        int section_base_stars = 1 + 2 * section;
        
        int skip_lines = (section > 0) ? 2 : 0;
        
        for (i = skip_lines; i < section_height; i++) {
            int stars = section_base_stars + 2 * i;
            int spaces = (max_width - stars) / 2;
            
            for (j = 0; j < spaces; j++) {
                my_putchar(' ');
            }
            for (j = 0; j < stars; j++) {
                my_putchar('*');
            }
            my_putchar('\n');
        }
    }
}

static void print_trunk(int size, int max_width)
{
    int trunk_width = size;
    int trunk_height = size;
    int spaces = (max_width - trunk_width) / 2;
    int i, j;
    
    for (i = 0; i < trunk_height; i++) {
        for (j = 0; j < spaces; j++) {
            my_putchar(' ');
        }
        for (j = 0; j < trunk_width; j++) {
            my_putchar('|');
        }
        my_putchar('\n');
    }
}

void tree(int size)
{
    int max_width;
    int last_section_base;
    int last_section_height;
    int last_section_max_stars;
    
    if (size <= 0)
        return;
    
    last_section_base = 1 + 2 * (size - 1);
    last_section_height = 4 + (size - 1);
    last_section_max_stars = last_section_base + 2 * (last_section_height - 1);
    max_width = last_section_max_stars;
    
    print_tree_part(size, max_width);
    print_trunk(size, max_width);
}