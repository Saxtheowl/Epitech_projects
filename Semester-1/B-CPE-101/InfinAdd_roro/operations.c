#include <stdlib.h>
#include "infin_add.h"

char *add_positive(char const *nb1, char const *nb2)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int max_len = (len1 > len2) ? len1 : len2;
    char *result = malloc(max_len + 3);
    int carry = 0;
    int i = 0;
    
    if (!result)
        return NULL;
    
    for (i = 0; i < max_len + 2; i++)
        result[i] = '0';
    result[max_len + 2] = '\0';
    
    for (i = 0; i < max_len || carry; i++) {
        int digit1 = (i < len1) ? nb1[len1 - 1 - i] - '0' : 0;
        int digit2 = (i < len2) ? nb2[len2 - 1 - i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        
        carry = sum / 10;
        result[max_len + 1 - i] = (sum % 10) + '0';
    }
    
    return remove_leading_zeros(result);
}

char *sub_positive(char const *nb1, char const *nb2)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    char *result = malloc(len1 + 1);
    int borrow = 0;
    int i, j, k;
    
    if (!result)
        return NULL;
    
    k = len1 - 1;
    result[len1] = '\0';
    
    for (i = len1 - 1, j = len2 - 1; i >= 0; i--, j--, k--) {
        int digit1 = nb1[i] - '0';
        int digit2 = (j >= 0) ? nb2[j] - '0' : 0;
        
        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result[k] = (digit1 - digit2) + '0';
    }
    
    return remove_leading_zeros(result);
}

char *infin_add(char const *nb1, char const *nb2)
{
    int neg1, neg2;
    char *result;
    char *temp_result;
    int cmp;
    
    if (!nb1 || !nb2)
        return NULL;
    
    neg1 = is_negative(nb1);
    neg2 = is_negative(nb2);
    
    if (neg1 && neg2) {
        result = add_positive(nb1 + 1, nb2 + 1);
        if (!result)
            return NULL;
        if (my_strlen(result) == 1 && result[0] == '0') {
            return result;
        }
        temp_result = malloc(my_strlen(result) + 2);
        if (!temp_result) {
            free(result);
            return NULL;
        }
        temp_result[0] = '-';
        my_strcpy(temp_result + 1, result);
        free(result);
        return temp_result;
    } else if (neg1) {
        cmp = compare_abs(nb1, nb2);
        if (cmp > 0) {
            result = sub_positive(nb1 + 1, nb2);
            if (!result)
                return NULL;
            temp_result = malloc(my_strlen(result) + 2);
            if (!temp_result) {
                free(result);
                return NULL;
            }
            temp_result[0] = '-';
            my_strcpy(temp_result + 1, result);
            free(result);
            return remove_leading_zeros(temp_result);
        } else {
            return sub_positive(nb2, nb1 + 1);
        }
    } else if (neg2) {
        cmp = compare_abs(nb1, nb2);
        if (cmp >= 0) {
            return sub_positive(nb1, nb2 + 1);
        } else {
            result = sub_positive(nb2 + 1, nb1);
            if (!result)
                return NULL;
            temp_result = malloc(my_strlen(result) + 2);
            if (!temp_result) {
                free(result);
                return NULL;
            }
            temp_result[0] = '-';
            my_strcpy(temp_result + 1, result);
            free(result);
            return remove_leading_zeros(temp_result);
        }
    } else {
        return add_positive(nb1, nb2);
    }
}