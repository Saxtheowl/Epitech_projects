/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_putnbr_base.c
*/

void my_putchar(char c);

static int get_base_len(char const *base)
{
    int len = 0;
    
    while (base[len] != '\0')
        len++;
    return len;
}

static int is_valid_base(char const *base)
{
    int len = get_base_len(base);
    int i, j;
    
    if (len < 2)
        return 0;
        
    for (i = 0; i < len; i++) {
        if (base[i] == '+' || base[i] == '-')
            return 0;
        for (j = i + 1; j < len; j++) {
            if (base[i] == base[j])
                return 0;
        }
    }
    return 1;
}

static void putnbr_base_positive(int nbr, char const *base, int base_len)
{
    if (nbr >= base_len)
        putnbr_base_positive(nbr / base_len, base, base_len);
    my_putchar(base[nbr % base_len]);
}

int my_putnbr_base(int nbr, char const *base)
{
    int base_len = get_base_len(base);
    
    if (!is_valid_base(base))
        return 0;
    
    if (nbr < 0) {
        my_putchar('-');
        if (nbr == -2147483648) {
            putnbr_base_positive(2147483648 / base_len, base, base_len);
            my_putchar(base[2147483648 % base_len]);
        } else {
            putnbr_base_positive(-nbr, base, base_len);
        }
    } else {
        putnbr_base_positive(nbr, base, base_len);
    }
    
    return 0;
}