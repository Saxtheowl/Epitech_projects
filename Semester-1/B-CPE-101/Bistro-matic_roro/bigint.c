#include <stdlib.h>
#include "bistromatic.h"

static char *add_positive(char const *nb1, char const *nb2, char const *base)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int max_len = (len1 > len2) ? len1 : len2;
    int base_len = my_strlen(base);
    char *result = malloc(max_len + 2);
    int carry = 0;
    int i, j, k = max_len;
    
    if (!result)
        return NULL;
    
    result[max_len + 1] = '\0';
    
    for (i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; i--, j--, k--) {
        int val1 = (i >= 0) ? char_to_int(nb1[i], base) : 0;
        int val2 = (j >= 0) ? char_to_int(nb2[j], base) : 0;
        int sum = val1 + val2 + carry;
        
        carry = sum / base_len;
        result[k] = int_to_char(sum % base_len, base);
    }
    
    return remove_leading_zeros(result, base);
}

static char *sub_positive(char const *nb1, char const *nb2, char const *base)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int base_len = my_strlen(base);
    char *result = malloc(len1 + 1);
    int borrow = 0;
    int i, j, k = len1 - 1;
    
    if (!result)
        return NULL;
    
    result[len1] = '\0';
    
    for (i = len1 - 1, j = len2 - 1; i >= 0; i--, j--, k--) {
        int val1 = char_to_int(nb1[i], base);
        int val2 = (j >= 0) ? char_to_int(nb2[j], base) : 0;
        
        val1 -= borrow;
        if (val1 < val2) {
            val1 += base_len;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result[k] = int_to_char(val1 - val2, base);
    }
    
    return remove_leading_zeros(result, base);
}

char *bigint_add(char const *nb1, char const *nb2, char const *base)
{
    int neg1 = is_negative(nb1, base);
    int neg2 = is_negative(nb2, base);
    
    if (neg1 && neg2) {
        return add_positive(nb1 + 1, nb2 + 1, base);
    } else if (neg1) {
        return bigint_sub(nb2, nb1 + 1, base);
    } else if (neg2) {
        return bigint_sub(nb1, nb2 + 1, base);
    } else {
        return add_positive(nb1, nb2, base);
    }
}

char *bigint_sub(char const *nb1, char const *nb2, char const *base)
{
    int neg1 = is_negative(nb1, base);
    int neg2 = is_negative(nb2, base);
    int cmp;
    
    if (neg1 && neg2) {
        return bigint_sub(nb2 + 1, nb1 + 1, base);
    } else if (neg1) {
        return add_positive(nb1 + 1, nb2, base);
    } else if (neg2) {
        return add_positive(nb1, nb2 + 1, base);
    } else {
        cmp = compare_abs(nb1, nb2, base);
        if (cmp >= 0) {
            return sub_positive(nb1, nb2, base);
        } else {
            char *result = sub_positive(nb2, nb1, base);
            char *neg_result = malloc(my_strlen(result) + 2);
            if (!neg_result)
                return NULL;
            neg_result[0] = base[my_strlen(base) - 1];
            int i = 0;
            while (result[i]) {
                neg_result[i + 1] = result[i];
                i++;
            }
            neg_result[i + 1] = '\0';
            free(result);
            return neg_result;
        }
    }
}

char *bigint_mul(char const *nb1, char const *nb2, char const *base)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int base_len = my_strlen(base);
    char *result = malloc(len1 + len2 + 1);
    int i, j;
    
    if (!result)
        return NULL;
    
    for (i = 0; i < len1 + len2; i++)
        result[i] = base[0];
    result[len1 + len2] = '\0';
    
    for (i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        for (j = len2 - 1; j >= 0; j--) {
            int val1 = char_to_int(nb1[i], base);
            int val2 = char_to_int(nb2[j], base);
            int curr = char_to_int(result[i + j + 1], base);
            int prod = val1 * val2 + curr + carry;
            
            carry = prod / base_len;
            result[i + j + 1] = int_to_char(prod % base_len, base);
        }
        result[i] = int_to_char(carry, base);
    }
    
    return remove_leading_zeros(result, base);
}

char *bigint_div(char const *nb1, char const *nb2, char const *base)
{
    char *result = malloc(2);
    (void)nb1;
    (void)nb2;
    if (!result)
        return NULL;
    result[0] = base[0];
    result[1] = '\0';
    return result;
}

char *bigint_mod(char const *nb1, char const *nb2, char const *base)
{
    char *result = malloc(2);
    (void)nb1;
    (void)nb2;
    if (!result)
        return NULL;
    result[0] = base[0];
    result[1] = '\0';
    return result;
}