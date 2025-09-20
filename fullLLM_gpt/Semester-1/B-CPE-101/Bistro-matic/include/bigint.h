#ifndef BIGINT_H
#define BIGINT_H

#include <stddef.h>

typedef struct {
    int sign;
    size_t len;
    size_t cap;
    unsigned char *digits;
} big_t;

big_t *big_from_int(int value);
big_t *big_clone(const big_t *src);
big_t *big_abs_clone(const big_t *src);
void big_free(big_t *value);
int big_is_zero(const big_t *value);
int big_compare_abs(const big_t *a, const big_t *b);
big_t *big_from_base_digits(const char *base, const int *map,
                            const char *digits, size_t len);
big_t *big_add(const big_t *a, const big_t *b);
big_t *big_sub(const big_t *a, const big_t *b);
big_t *big_mul(const big_t *a, const big_t *b);
big_t *big_div(const big_t *a, const big_t *b);
big_t *big_mod(const big_t *a, const big_t *b);
char *big_to_base_string(const big_t *value, const char *base,
                         unsigned int base_len, char minus_char);
big_t *big_negate_clone(const big_t *value);

#endif
