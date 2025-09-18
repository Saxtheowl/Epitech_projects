int my_getnbr(char const *str)
{
    int i = 0;
    int sign = 1;
    long result = 0;
    
    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }
    
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            sign = -sign;
        }
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        if (result > 2147483647) {
            return (0);
        }
        i++;
    }
    
    result = result * sign;
    
    if (result < -2147483648 || result > 2147483647) {
        return (0);
    }
    
    return ((int)result);
}