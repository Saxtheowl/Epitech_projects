#include "infin_add.h"

int compare_absolute_values(char const *num1, char const *num2)
{
    int len1 = my_strlen(num1);
    int len2 = my_strlen(num2);
    int i;
    
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;
    
    for (i = 0; i < len1; i++) {
        if (num1[i] > num2[i])
            return 1;
        if (num1[i] < num2[i])
            return -1;
    }
    
    return 0;
}

char *add_positive_numbers(char const *num1, char const *num2)
{
    int len1 = my_strlen(num1);
    int len2 = my_strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;
    char *temp = malloc(max_len + 2);
    char *result;
    int carry = 0;
    int i;
    
    if (!temp)
        return 0;
    
    temp[max_len + 1] = '\0';
    
    for (i = 0; i < max_len; i++) {
        int digit1 = (i < len1) ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        
        temp[max_len - i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    
    if (carry) {
        temp[0] = carry + '0';
        result = my_strdup(temp);
    } else {
        result = my_strdup(temp + 1);
    }
    
    free(temp);
    return result;
}

char *subtract_positive_numbers(char const *num1, char const *num2)
{
    int len1 = my_strlen(num1);
    int len2 = my_strlen(num2);
    char *result = malloc(len1 + 1);
    int borrow = 0;
    int i;
    
    if (!result)
        return 0;
    
    result[len1] = '\0';
    
    for (i = 0; i < len1; i++) {
        int digit1 = num1[len1 - 1 - i] - '0' - borrow;
        int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;
        
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result[len1 - 1 - i] = (digit1 - digit2) + '0';
    }
    
    return remove_leading_zeros(result);
}