int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\f' || str[i] == '\v') {
        i++;
    }

    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            sign = -sign;
        }
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        if (result > (2147483647 - (str[i] - '0')) / 10) {
            return 0;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }

    result = result * sign;

    if (result < -2147483648 || result > 2147483647) {
        return 0;
    }

    return result;
}