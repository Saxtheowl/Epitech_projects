void my_putchar(char c);

static int get_base_len(char const *base)
{
    int len = 0;
    int i = 0;
    int j;

    while (base[len] != '\0')
        len++;

    if (len <= 1)
        return -1;

    while (i < len) {
        if (base[i] == '+' || base[i] == '-')
            return -1;
        j = i + 1;
        while (j < len) {
            if (base[i] == base[j])
                return -1;
            j++;
        }
        i++;
    }
    return len;
}

static void putnbr_rec(int nbr, char const *base, int base_len)
{
    if (nbr >= base_len)
        putnbr_rec(nbr / base_len, base, base_len);
    my_putchar(base[nbr % base_len]);
}

int my_putnbr_base(int nbr, char const *base)
{
    int base_len = get_base_len(base);

    if (base_len == -1)
        return 0;

    if (nbr < 0) {
        my_putchar('-');
        if (nbr == -2147483648) {
            putnbr_rec(2147483648 / base_len, base, base_len);
            my_putchar(base[2147483648 % base_len]);
            return 0;
        }
        nbr = -nbr;
    }

    putnbr_rec(nbr, base, base_len);
    return 0;
}