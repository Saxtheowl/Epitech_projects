#include <unistd.h>
#include "../include/my.h"

int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: division by zero\n");
        return 84;
    }
    return a / b;
}

int mod(int a, int b)
{
    if (b == 0) {
        my_putstr("Stop: modulo by zero\n");
        return 84;
    }
    return a % b;
}

int do_operation(int a, char op, int b)
{
    int result;

    if (op == '+')
        result = add(a, b);
    else if (op == '-')
        result = sub(a, b);
    else if (op == '*')
        result = mul(a, b);
    else if (op == '/') {
        if (b == 0) {
            write(2, "Stop: division by zero\n", 23);
            return 84;
        }
        result = divide(a, b);
    } else if (op == '%') {
        if (b == 0) {
            write(2, "Stop: modulo by zero\n", 21);
            return 84;
        }
        result = mod(a, b);
    } else {
        my_put_nbr(0);
        my_putchar('\n');
        return 84;
    }
    my_put_nbr(result);
    my_putchar('\n');
    return 0;
}

int main(int ac, char **av)
{
    int a, b;
    char op;

    if (ac != 4)
        return 84;

    a = my_getnbr(av[1]);
    op = av[2][0];
    b = my_getnbr(av[3]);

    return do_operation(a, op, b);
}