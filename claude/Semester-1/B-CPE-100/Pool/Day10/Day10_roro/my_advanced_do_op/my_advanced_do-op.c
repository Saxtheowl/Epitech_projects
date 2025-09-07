#include <unistd.h>
#include "../include/my.h"
#include "../include/my_operator.h"
#include "../include/my_opp.h"

int my_add(int a, int b)
{
    return a + b;
}

int my_sub(int a, int b)
{
    return a - b;
}

int my_mul(int a, int b)
{
    return a * b;
}

int my_div(int a, int b)
{
    if (b == 0) {
        write(2, "Stop: division by zero\n", 23);
        return 84;
    }
    return a / b;
}

int my_mod(int a, int b)
{
    if (b == 0) {
        write(2, "Stop: modulo by zero\n", 21);
        return 84;
    }
    return a % b;
}

int my_usage(int a, int b)
{
    (void)a;
    (void)b;
    write(2, "error: only [ + - / * % ] are supported\n", 40);
    return 84;
}

int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str == NULL)
        return 0;

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

int my_strcmp_op(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return -1;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;

    return s1[i] - s2[i];
}

int find_operator(char *op)
{
    int i = 0;

    while (OPERATORS_FUNCS[i].op[0] != '\0') {
        if (my_strcmp_op(OPERATORS_FUNCS[i].op, op) == 0)
            return i;
        i++;
    }
    return -1;
}

int main(int ac, char **av)
{
    int a, b, result;
    int op_index;

    if (ac != 4)
        return 84;

    a = my_getnbr(av[1]);
    b = my_getnbr(av[3]);

    op_index = find_operator(av[2]);
    
    if (op_index == -1) {
        my_usage(0, 0);
        return 84;
    }

    if ((my_strcmp_op(av[2], "/") == 0 && b == 0) ||
        (my_strcmp_op(av[2], "%") == 0 && b == 0)) {
        result = OPERATORS_FUNCS[op_index].func(a, b);
        return 84;
    }

    result = OPERATORS_FUNCS[op_index].func(a, b);
    my_put_nbr(result);
    my_putchar('\n');
    return 0;
}