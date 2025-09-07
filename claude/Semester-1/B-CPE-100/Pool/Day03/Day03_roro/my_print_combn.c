void my_putchar(char c);

static void print_combination(int *combination, int n, int *first)
{
    int i = 0;

    if (!(*first)) {
        my_putchar(',');
        my_putchar(' ');
    }
    while (i < n) {
        my_putchar('0' + combination[i]);
        i++;
    }
    *first = 0;
}

static void generate_combinations(int *combination, int n, int start, int pos, int *first)
{
    int i;

    if (pos == n) {
        print_combination(combination, n, first);
        return;
    }
    
    i = start;
    while (i <= 9 - (n - pos - 1)) {
        combination[pos] = i;
        generate_combinations(combination, n, i + 1, pos + 1, first);
        i++;
    }
}

int my_print_combn(int n)
{
    int combination[10];
    int first = 1;

    if (n <= 0 || n >= 10) {
        return 0;
    }
    
    generate_combinations(combination, n, 0, 0, &first);
    return 0;
}