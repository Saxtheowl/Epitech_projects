/*
** EPITECH PROJECT, 2024
** to_number
** File description:
** Convert a string to an integer with overflow handling
*/

static int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static int handle_overflow(long long result, int sign)
{
    if (sign == 1 && result > 2147483647)
        return 0;
    if (sign == -1 && result > 2147483648)
        return 0;
    return 1;
}

int to_number(char const *str)
{
    int i = 0;
    int sign = 1;
    long long result = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (is_digit(str[i])) {
        result = result * 10 + (str[i] - '0');
        if (!handle_overflow(result, sign))
            return 0;
        i++;
    }
    return (int)(result * sign);
}