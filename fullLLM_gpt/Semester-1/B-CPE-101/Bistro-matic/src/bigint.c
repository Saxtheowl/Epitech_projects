#include <stdlib.h>
#include "bistromatic.h"
#include "utils.h"
#include "bigint.h"

#define BIG_BASE 10

static big_t *big_create(size_t capacity)
{
    size_t cap = capacity < 1 ? 1 : capacity;
    big_t *value = my_malloc(sizeof(big_t));

    value->digits = my_malloc(cap);
    for (size_t i = 0; i < cap; ++i)
        value->digits[i] = 0;
    value->len = 1;
    value->cap = cap;
    value->sign = 0;
    return value;
}

static void big_ensure_capacity(big_t *value, size_t capacity)
{
    if (value->cap >= capacity)
        return;
    unsigned char *new_digits = my_malloc(capacity);
    for (size_t i = 0; i < capacity; ++i)
        new_digits[i] = 0;
    for (size_t i = 0; i < value->len; ++i)
        new_digits[i] = value->digits[i];
    free(value->digits);
    value->digits = new_digits;
    value->cap = capacity;
}

static void big_normalize(big_t *value)
{
    while (value->len > 1 && value->digits[value->len - 1] == 0)
        --value->len;
    if (value->len == 1 && value->digits[0] == 0)
        value->sign = 0;
}

big_t *big_from_int(int number)
{
    big_t *result = big_create(2);
    unsigned int n;

    if (number == 0) {
        result->digits[0] = 0;
        result->len = 1;
        result->sign = 0;
        return result;
    }
    result->sign = number < 0 ? -1 : 1;
    n = (number < 0) ? (unsigned int)(-number) : (unsigned int)number;
    result->len = 0;
    while (n > 0) {
        big_ensure_capacity(result, result->len + 1);
        result->digits[result->len++] = (unsigned char)(n % BIG_BASE);
        n /= BIG_BASE;
    }
    big_normalize(result);
    return result;
}

big_t *big_clone(const big_t *src)
{
    big_t *copy = big_create(src->len);

    copy->len = src->len;
    copy->sign = src->sign;
    for (size_t i = 0; i < src->len; ++i)
        copy->digits[i] = src->digits[i];
    return copy;
}

big_t *big_abs_clone(const big_t *src)
{
    big_t *copy = big_clone(src);

    if (!big_is_zero(copy))
        copy->sign = 1;
    return copy;
}

void big_free(big_t *value)
{
    if (!value)
        return;
    free(value->digits);
    free(value);
}

int big_is_zero(const big_t *value)
{
    return value->len == 1 && value->digits[0] == 0;
}

int big_compare_abs(const big_t *a, const big_t *b)
{
    if (a->len > b->len)
        return 1;
    if (a->len < b->len)
        return -1;
    for (size_t idx = a->len; idx-- > 0;) {
        if (a->digits[idx] > b->digits[idx])
            return 1;
        if (a->digits[idx] < b->digits[idx])
            return -1;
    }
    return 0;
}

static void big_add_small_inplace(big_t *value, unsigned int add)
{
    unsigned int carry = add;
    size_t i = 0;

    while (carry > 0 || i < value->len) {
        if (i == value->len) {
            big_ensure_capacity(value, value->len + 1);
            value->digits[value->len++] = 0;
        }
        unsigned int sum = (unsigned int)value->digits[i] + carry;
        value->digits[i] = (unsigned char)(sum % BIG_BASE);
        carry = sum / BIG_BASE;
        ++i;
    }
    if (!big_is_zero(value))
        value->sign = 1;
    big_normalize(value);
}

static void big_mul_small_inplace(big_t *value, unsigned int factor)
{
    if (big_is_zero(value) || factor == 1)
        return;
    if (factor == 0) {
        value->len = 1;
        value->digits[0] = 0;
        value->sign = 0;
        return;
    }
    unsigned int carry = 0;
    for (size_t i = 0; i < value->len; ++i) {
        unsigned int prod = (unsigned int)value->digits[i] * factor + carry;
        value->digits[i] = (unsigned char)(prod % BIG_BASE);
        carry = prod / BIG_BASE;
    }
    while (carry > 0) {
        big_ensure_capacity(value, value->len + 1);
        value->digits[value->len++] = (unsigned char)(carry % BIG_BASE);
        carry /= BIG_BASE;
    }
    if (!big_is_zero(value))
        value->sign = 1;
    big_normalize(value);
}

static void big_sub_abs_inplace(big_t *a, const big_t *b)
{
    unsigned int borrow = 0;

    for (size_t i = 0; i < a->len; ++i) {
        int diff = (int)a->digits[i] - (int)(i < b->len ? b->digits[i] : 0) - (int)borrow;
        if (diff < 0) {
            diff += BIG_BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        a->digits[i] = (unsigned char)diff;
    }
    big_normalize(a);
    if (big_is_zero(a))
        a->sign = 0;
}

static big_t *big_add_abs(const big_t *a, const big_t *b)
{
    size_t max_len = (a->len > b->len) ? a->len : b->len;
    big_t *res = big_create(max_len + 1);
    unsigned int carry = 0;

    res->len = 0;
    for (size_t i = 0; i < max_len; ++i) {
        unsigned int sum = carry;
        if (i < a->len)
            sum += a->digits[i];
        if (i < b->len)
            sum += b->digits[i];
        res->digits[res->len++] = (unsigned char)(sum % BIG_BASE);
        carry = sum / BIG_BASE;
    }
    if (carry) {
        res->digits[res->len++] = (unsigned char)carry;
    }
    res->sign = 1;
    big_normalize(res);
    return res;
}

static big_t *big_sub_abs(const big_t *a, const big_t *b)
{
    big_t *res = big_clone(a);

    big_sub_abs_inplace(res, b);
    return res;
}

big_t *big_add(const big_t *a, const big_t *b)
{
    if (a->sign == 0)
        return big_clone(b);
    if (b->sign == 0)
        return big_clone(a);
    if (a->sign == b->sign) {
        big_t *res = big_add_abs(a, b);
        res->sign = a->sign;
        if (big_is_zero(res))
            res->sign = 0;
        return res;
    }
    int cmp = big_compare_abs(a, b);
    if (cmp == 0)
        return big_from_int(0);
    if (cmp > 0) {
        big_t *res = big_sub_abs(a, b);
        res->sign = a->sign;
        if (big_is_zero(res))
            res->sign = 0;
        return res;
    }
    big_t *res = big_sub_abs(b, a);
    res->sign = b->sign;
    if (big_is_zero(res))
        res->sign = 0;
    return res;
}

big_t *big_sub(const big_t *a, const big_t *b)
{
    big_t tmp = *b;
    big_t *res;

    tmp.sign = -tmp.sign;
    res = big_add(a, &tmp);
    return res;
}

big_t *big_mul(const big_t *a, const big_t *b)
{
    if (big_is_zero(a) || big_is_zero(b))
        return big_from_int(0);
    big_t *res = big_create(a->len + b->len);

    res->len = a->len + b->len;
    for (size_t i = 0; i < a->len; ++i) {
        unsigned int carry = 0;
        for (size_t j = 0; j < b->len; ++j) {
            size_t idx = i + j;
            unsigned int prod = (unsigned int)a->digits[i] * b->digits[j]
                               + res->digits[idx] + carry;
            res->digits[idx] = (unsigned char)(prod % BIG_BASE);
            carry = prod / BIG_BASE;
        }
        size_t idx = i + b->len;
        while (carry > 0) {
            unsigned int sum = res->digits[idx] + carry;
            res->digits[idx] = (unsigned char)(sum % BIG_BASE);
            carry = sum / BIG_BASE;
            ++idx;
        }
    }
    res->sign = (a->sign == b->sign) ? 1 : -1;
    big_normalize(res);
    if (big_is_zero(res))
        res->sign = 0;
    return res;
}

static big_t *big_divmod_positive(const big_t *a, const big_t *b, big_t **rem_out)
{
    big_t *dividend = big_abs_clone(a);
    big_t *divisor = big_abs_clone(b);

    if (big_is_zero(divisor)) {
        big_free(dividend);
        big_free(divisor);
        fatal_error(ERROR_MSG);
    }
    if (big_compare_abs(dividend, divisor) < 0) {
        big_t *quot = big_from_int(0);
        if (rem_out)
            *rem_out = dividend;
        else
            big_free(dividend);
        big_free(divisor);
        return quot;
    }
    big_t *quot = big_create(dividend->len);
    big_t *current = big_from_int(0);

    quot->len = dividend->len;
    for (size_t i = quot->len; i-- > 0;)
        quot->digits[i] = 0;

    for (size_t i = dividend->len; i-- > 0;) {
        big_mul_small_inplace(current, BIG_BASE);
        big_add_small_inplace(current, dividend->digits[i]);
        unsigned int q = 0;
        while (big_compare_abs(current, divisor) >= 0) {
            big_sub_abs_inplace(current, divisor);
            ++q;
        }
        quot->digits[i] = (unsigned char)q;
        if (!big_is_zero(current))
            current->sign = 1;
    }
    big_normalize(quot);
    big_free(divisor);
    if (rem_out)
        *rem_out = current;
    else
        big_free(current);
    big_free(dividend);
    return quot;
}

big_t *big_div(const big_t *a, const big_t *b)
{
    big_t *rem = NULL;
    big_t *quot = big_divmod_positive(a, b, &rem);

    if (!big_is_zero(quot))
        quot->sign = (a->sign == b->sign) ? 1 : -1;
    else
        quot->sign = 0;
    big_free(rem);
    return quot;
}

big_t *big_mod(const big_t *a, const big_t *b)
{
    big_t *rem = NULL;
    big_t *quot = big_divmod_positive(a, b, &rem);

    (void)quot;
    if (!big_is_zero(rem) && a->sign < 0)
        rem->sign = -1;
    big_free(quot);
    return rem;
}

static big_t *big_divmod_small(const big_t *a, unsigned int base, unsigned int *remainder)
{
    big_t *quot = big_create(a->len);
    unsigned int rem = 0;

    quot->len = a->len;
    for (size_t i = quot->len; i-- > 0;) {
        unsigned int value = rem * BIG_BASE + a->digits[i];
        quot->digits[i] = (unsigned char)(value / base);
        rem = value % base;
    }
    big_normalize(quot);
    if (remainder)
        *remainder = rem;
    return quot;
}

char *big_to_base_string(const big_t *value, const char *base,
                         unsigned int base_len, char minus_char)
{
    if (big_is_zero(value)) {
        char *zero = my_malloc(2);
        zero[0] = base[0];
        zero[1] = '\0';
        return zero;
    }
    big_t *tmp = big_abs_clone(value);
    size_t capacity = tmp->len * 4 + 2;
    char *buffer = my_malloc(capacity);
    size_t index = 0;

    while (!big_is_zero(tmp)) {
        unsigned int rem = 0;
        big_t *next = big_divmod_small(tmp, base_len, &rem);
        buffer[index++] = base[rem];
        big_free(tmp);
        tmp = next;
    }
    big_free(tmp);
    size_t extra = (value->sign < 0) ? 1 : 0;
    char *out = my_malloc(index + extra + 1);
    size_t pos = 0;

    if (value->sign < 0)
        out[pos++] = minus_char;
    while (index-- > 0)
        out[pos++] = buffer[index];
    out[pos] = '\0';
    free(buffer);
    return out;
}

static int char_to_value(const int *map, char c)
{
    int v = map[(unsigned char)c];

    if (v < 0)
        fatal_error(SYNTAX_ERROR_MSG);
    return v;
}

big_t *big_from_base_digits(const char *base, const int *map,
                            const char *digits, size_t len)
{
    big_t *value = big_from_int(0);
    unsigned int base_len = (unsigned int)my_strlen(base);

    for (size_t i = 0; i < len; ++i) {
        int digit = char_to_value(map, digits[i]);
        big_mul_small_inplace(value, base_len);
        big_add_small_inplace(value, (unsigned int)digit);
    }
    return value;
}

big_t *big_negate_clone(const big_t *value)
{
    big_t *copy = big_clone(value);

    if (!big_is_zero(copy))
        copy->sign = -copy->sign;
    return copy;
}
