#include <stdlib.h>
#include "../include/infin_add.h"

size_t my_strlen(char const *str);
int my_is_space(char c);
char *my_strdup_range(char const *start, char const *end);

typedef struct {
    int sign;
    char *digits;
} number_t;

static void free_number(number_t *num)
{
    if (num && num->digits) {
        free(num->digits);
        num->digits = NULL;
    }
}

static char *strip_leading_zeros(char *digits)
{
    size_t i = 0;

    while (digits[i] == '0' && digits[i + 1] != '\0')
        ++i;
    if (i == 0)
        return digits;
    char *trimmed = my_strdup_range(digits + i, digits + my_strlen(digits));
    free(digits);
    return trimmed;
}

static number_t parse_number(char const *str)
{
    number_t number = {1, NULL};
    char const *ptr = str;

    while (my_is_space(*ptr))
        ++ptr;
    while (*ptr == '+' || *ptr == '-') {
        if (*ptr == '-')
            number.sign = -number.sign;
        ++ptr;
    }
    char const *start = ptr;
    while (*ptr >= '0' && *ptr <= '9')
        ++ptr;
    if (start == ptr) {
        number.sign = 0;
        number.digits = my_strdup_range("0", "0" + 1);
        return number;
    }
    number.digits = my_strdup_range(start, ptr);
    if (!number.digits)
        return number;
    number.digits = strip_leading_zeros(number.digits);
    if (number.digits[0] == '0' && number.digits[1] == '\0')
        number.sign = 0;
    return number;
}

static int compare_abs(char const *a, char const *b)
{
    size_t len_a = my_strlen(a);
    size_t len_b = my_strlen(b);

    if (len_a > len_b)
        return 1;
    if (len_a < len_b)
        return -1;
    for (size_t i = 0; i < len_a; ++i) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}

static char *add_abs(char const *a, char const *b)
{
    size_t len_a = my_strlen(a);
    size_t len_b = my_strlen(b);
    size_t max_len = (len_a > len_b) ? len_a : len_b;
    char *res = malloc(max_len + 2);
    size_t idx_a = len_a;
    size_t idx_b = len_b;
    size_t idx_r = max_len + 1;
    int carry = 0;

    if (!res)
        return NULL;
    res[idx_r] = '\0';
    while (idx_r-- > 0) {
        int sum = carry;
        if (idx_a > 0)
            sum += a[--idx_a] - '0';
        if (idx_b > 0)
            sum += b[--idx_b] - '0';
        res[idx_r] = (char)('0' + (sum % 10));
        carry = sum / 10;
    }
    if (res[0] == '0') {
        char *trim = my_strdup_range(res + 1, res + my_strlen(res));
        free(res);
        return trim;
    }
    return res;
}

static char *sub_abs(char const *a, char const *b)
{
    size_t len_a = my_strlen(a);
    size_t len_b = my_strlen(b);
    char *res = malloc(len_a + 1);
    size_t idx_a = len_a;
    size_t idx_b = len_b;
    size_t idx_r = len_a;
    int borrow = 0;

    if (!res)
        return NULL;
    res[idx_r] = '\0';
    while (idx_r-- > 0) {
        int diff = (a[--idx_a] - '0') - borrow;
        if (idx_b > 0)
            diff -= (b[--idx_b] - '0');
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res[idx_r] = (char)('0' + diff);
    }
    return strip_leading_zeros(res);
}

static char *build_result(char const *digits, int sign)
{
    size_t len = my_strlen(digits);
    if (sign < 0 && !(len == 1 && digits[0] == '0')) {
        char *res = malloc(len + 2);
        if (!res)
            return NULL;
        res[0] = '-';
        for (size_t i = 0; i < len; ++i)
            res[i + 1] = digits[i];
        res[len + 1] = '\0';
        return res;
    }
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; ++i)
        copy[i] = digits[i];
    copy[len] = '\0';
    return copy;
}

char *infin_add(const char *lhs, const char *rhs)
{
    number_t a = parse_number(lhs);
    number_t b = parse_number(rhs);
    char *digits = NULL;
    int sign = 0;

    if (!a.digits || !b.digits) {
        free_number(&a);
        free_number(&b);
        return NULL;
    }
    if (a.sign == 0 && b.sign == 0) {
        digits = my_strdup_range("0", "0" + 1);
        sign = 0;
    } else if (a.sign == 0) {
        digits = my_strdup_range(b.digits, b.digits + my_strlen(b.digits));
        sign = b.sign;
    } else if (b.sign == 0) {
        digits = my_strdup_range(a.digits, a.digits + my_strlen(a.digits));
        sign = a.sign;
    } else if (a.sign == b.sign) {
        digits = add_abs(a.digits, b.digits);
        sign = a.sign;
    } else {
        int cmp = compare_abs(a.digits, b.digits);
        if (cmp == 0) {
            digits = my_strdup_range("0", "0" + 1);
            sign = 0;
        } else if (cmp > 0) {
            digits = sub_abs(a.digits, b.digits);
            sign = a.sign;
        } else {
            digits = sub_abs(b.digits, a.digits);
            sign = b.sign;
        }
    }
    free_number(&a);
    free_number(&b);
    if (!digits)
        return NULL;
    if (digits[0] == '0' && digits[1] == '\0')
        sign = 0;
    char *result = build_result(digits, sign);
    free(digits);
    return result;
}
