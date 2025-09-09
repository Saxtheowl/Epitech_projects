#include "infin_add.h"

static char *get_absolute_value(char const *num)
{
    if (num[0] == '-')
        return my_strdup(num + 1);
    return my_strdup(num);
}

static int is_negative(char const *num)
{
    return (num[0] == '-');
}

char *infin_add(char const *num1, char const *num2)
{
    char *abs1 = get_absolute_value(num1);
    char *abs2 = get_absolute_value(num2);
    char *result;
    int neg1 = is_negative(num1);
    int neg2 = is_negative(num2);
    
    if (neg1 == neg2) {
        result = add_positive_numbers(abs1, abs2);
        if (neg1) {
            char *temp = malloc(my_strlen(result) + 2);
            temp[0] = '-';
            int i;
            for (i = 0; result[i]; i++)
                temp[i + 1] = result[i];
            temp[i + 1] = '\0';
            free(result);
            result = temp;
        }
    } else {
        int cmp = compare_absolute_values(abs1, abs2);
        if (cmp == 0) {
            result = my_strdup("0");
        } else if (cmp > 0) {
            result = subtract_positive_numbers(abs1, abs2);
            if (neg1) {
                char *temp = malloc(my_strlen(result) + 2);
                temp[0] = '-';
                int i;
                for (i = 0; result[i]; i++)
                    temp[i + 1] = result[i];
                temp[i + 1] = '\0';
                free(result);
                result = temp;
            }
        } else {
            result = subtract_positive_numbers(abs2, abs1);
            if (neg2) {
                char *temp = malloc(my_strlen(result) + 2);
                temp[0] = '-';
                int i;
                for (i = 0; result[i]; i++)
                    temp[i + 1] = result[i];
                temp[i + 1] = '\0';
                free(result);
                result = temp;
            }
        }
    }
    
    free(abs1);
    free(abs2);
    return result;
}