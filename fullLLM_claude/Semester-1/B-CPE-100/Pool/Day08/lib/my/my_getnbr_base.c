/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_getnbr_base.c
*/

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

static int char_in_base(char c, char const *base)
{
    int i = 0;
    
    while (base[i] != '\0') {
        if (base[i] == c)
            return i;
        i++;
    }
    return -1;
}

int my_getnbr_base(char const *str, char const *base)
{
    int base_len = get_base_len(base);
    int sign = 1;
    int result = 0;
    int i = 0;
    int char_val;
    
    if (!is_valid_base(base))
        return 0;
    
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    
    while (str[i] != '\0') {
        char_val = char_in_base(str[i], base);
        if (char_val == -1)
            break;
        result = result * base_len + char_val;
        i++;
    }
    
    return result * sign;
}