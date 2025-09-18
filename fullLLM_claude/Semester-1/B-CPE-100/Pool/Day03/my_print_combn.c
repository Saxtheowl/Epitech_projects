void print_combination(int *digits, int n, int *first)
{
    int i = 0;
    
    if (!(*first)) {
        my_putchar(',');
        my_putchar(' ');
    }
    *first = 0;
    
    while (i < n) {
        my_putchar('0' + digits[i]);
        i++;
    }
}

void generate_combinations(int *digits, int pos, int start, int n, int *first)
{
    if (pos == n) {
        print_combination(digits, n, first);
        return;
    }
    
    while (start <= 9 - (n - pos - 1)) {
        digits[pos] = start;
        generate_combinations(digits, pos + 1, start + 1, n, first);
        start++;
    }
}

int my_print_combn(int n)
{
    int digits[10];
    int first = 1;
    
    if (n <= 0 || n >= 10)
        return (0);
    
    generate_combinations(digits, 0, 0, n, &first);
    return (0);
}