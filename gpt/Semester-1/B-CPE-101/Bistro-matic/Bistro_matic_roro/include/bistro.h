/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Prototypes for bistro-matic
*/

#ifndef BISTRO_H
    #define BISTRO_H

    #include <stddef.h>

    #define ERR_CODE 84

    typedef struct base_s {
        const char *digits;
        int b;
        int map[256];
        char ops[8];
        char op_add;
        char op_sub;
        char op_mul;
        char op_div;
        char op_mod;
        char op_lpar;
        char op_rpar;
        char op_neg;
    } base_t;

    typedef struct bigint_s {
        int *d;
        int n;
        int cap;
        int sign;
    } bigint_t;

    char *eval_expr(const char *base, const char *ops,
        const char *expr, unsigned int size);

    int base_init(base_t *bs, const char *digits, const char *ops);

    void bi_init(bigint_t *x);
    void bi_free(bigint_t *x);
    int bi_from_str(bigint_t *x, const char *s, const base_t *bs);
    char *bi_to_str(const bigint_t *x, const base_t *bs);

    void bi_trim(bigint_t *x);
    int bi_cmp_abs(const bigint_t *a, const bigint_t *b);
    int bi_add(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs);
    int bi_sub(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs);
    int bi_mul(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs);
    int bi_divmod(bigint_t *q, bigint_t *m, const bigint_t *a, const bigint_t *b, const base_t *bs);

    typedef struct ctx_s {
        const char *p;
        const char *end;
        base_t bs;
    } ctx_t;

    long skip_ws(ctx_t *c);
    int is_op(ctx_t *c, char ch, char *which);

    int parse_number(ctx_t *c, bigint_t *out);
    int parse_factor(ctx_t *c, bigint_t *out);
    int parse_term(ctx_t *c, bigint_t *out);
    int parse_expr(ctx_t *c, bigint_t *out);

#endif /* BISTRO_H */
