#include <stdlib.h>
#include "bistromatic.h"

typedef struct {
    char *digits;
    int size;
    int sign;
} big_int_t;

static int get_digit_value(char digit, char const *base)
{
    int i = 0;
    
    while (base[i]) {
        if (base[i] == digit)
            return i;
        i++;
    }
    return -1;
}

static char get_digit_char(int value, char const *base)
{
    return base[value];
}

static big_int_t *create_big_int(int size)
{
    big_int_t *num = malloc(sizeof(big_int_t));
    
    if (!num)
        return NULL;
    
    num->digits = malloc(size + 1);
    if (!num->digits) {
        free(num);
        return NULL;
    }
    
    num->size = size;
    num->sign = 1;
    
    for (int i = 0; i < size; i++)
        num->digits[i] = 0;
    num->digits[size] = '\0';
    
    return num;
}

static void free_big_int(big_int_t *num)
{
    if (num) {
        if (num->digits)
            free(num->digits);
        free(num);
    }
}

static big_int_t *parse_number(char const *str, int start, int end, char const *base)
{
    int len = end - start;
    int base_len = 0;
    big_int_t *num;
    int i, j;
    
    while (base[base_len])
        base_len++;
    
    if (len <= 0)
        return NULL;
        
    num = create_big_int(len);
    if (!num)
        return NULL;
    
    for (i = start, j = 0; i < end; i++, j++) {
        int digit_val = get_digit_value(str[i], base);
        if (digit_val == -1) {
            free_big_int(num);
            return NULL;
        }
        num->digits[j] = digit_val;
    }
    
    return num;
}

static char *big_int_to_string(big_int_t *num, char const *base)
{
    char *result;
    int i;
    int start = 0;
    
    if (!num || !num->digits)
        return NULL;
    
    while (start < num->size - 1 && num->digits[start] == 0)
        start++;
    
    result = malloc(num->size - start + 2);
    if (!result)
        return NULL;
    
    i = 0;
    if (num->sign == -1)
        result[i++] = base[1];
    
    for (int j = start; j < num->size; j++) {
        result[i++] = get_digit_char(num->digits[j], base);
    }
    result[i] = '\0';
    
    return result;
}