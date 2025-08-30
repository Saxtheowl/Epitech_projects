/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Big integer operations in arbitrary base
*/

#include <stdlib.h>
#include <string.h>
#include "bistro.h"

static int ensure(bigint_t *x, int need)
{
    int nc;
    int *nd;

    if (x->n + need <= x->cap)
        return 0;
    nc = x->cap ? x->cap * 2 : 8;
    while (nc < x->n + need)
        nc *= 2;
    nd = realloc(x->d, (size_t)nc * sizeof(int));
    if (!nd)
        return -1;
    x->d = nd;
    x->cap = nc;
    return 0;
}

void bi_init(bigint_t *x)
{
    x->d = NULL;
    x->n = 0;
    x->cap = 0;
    x->sign = 1;
}

void bi_free(bigint_t *x)
{
    free(x->d);
    x->d = NULL;
    x->n = 0;
    x->cap = 0;
}

void bi_trim(bigint_t *x)
{
    while (x->n > 0 && x->d[x->n - 1] == 0)
        x->n -= 1;
    if (x->n == 0)
        x->sign = 1;
}

static int bi_push_digit(bigint_t *x, int dig)
{
    if (ensure(x, 1) != 0)
        return -1;
    x->d[x->n++] = dig;
    return 0;
}

int bi_from_str(bigint_t *x, const char *s, const base_t *bs)
{
    const char *p;
    bigint_t acc;
    bigint_t tmp;
    int v;
    int i;

    bi_init(&acc);
    bi_init(&tmp);
    bi_init(x);
    bi_push_digit(&acc, 0);
    p = s;
    if (*p == '-') {
        x->sign = -1;
        p += 1;
    } else {
        x->sign = 1;
    }
    for (; *p; ++p) {
        v = bs->map[(unsigned char)*p];
        if (v < 0)
            break;
        /* acc = acc * b + v */
        tmp.n = 0;
        for (i = 0; i < acc.n; ++i)
            bi_push_digit(&tmp, acc.d[i]);
        /* multiply by base */
        {
            int carry = 0;
            for (i = 0; i < tmp.n; ++i) {
                int t = tmp.d[i] * bs->b + carry;
                tmp.d[i] = t % bs->b;
                carry = t / bs->b;
            }
            if (carry)
                bi_push_digit(&tmp, carry);
        }
        /* add v */
        {
            int carry = v;
            for (i = 0; i < tmp.n; ++i) {
                int t = tmp.d[i] + carry;
                tmp.d[i] = t % bs->b;
                carry = t / bs->b;
                if (carry == 0)
                    break;
            }
            if (carry)
                bi_push_digit(&tmp, carry);
        }
        bi_free(&acc);
        acc.d = NULL; acc.n = 0; acc.cap = 0; acc.sign = 1;
        /* move tmp to acc */
        acc.d = tmp.d; acc.n = tmp.n; acc.cap = tmp.cap; acc.sign = 1;
        tmp.d = NULL; tmp.n = 0; tmp.cap = 0;
    }
    /* x = acc */
    x->d = acc.d; x->n = acc.n; x->cap = acc.cap;
    bi_trim(x);
    return 0;
}

char *bi_to_str(const bigint_t *x, const base_t *bs)
{
    int i;
    int j;
    int z;
    char *buf;
    int len;

    if (x->n == 0) {
        buf = malloc(2);
        if (!buf)
            return NULL;
        buf[0] = bs->digits[0];
        buf[1] = '\0';
        return buf;
    }
    len = x->n + (x->sign < 0 ? 1 : 0) + 1;
    buf = malloc((size_t)len);
    if (!buf)
        return NULL;
    z = 0;
    if (x->sign < 0)
        buf[z++] = '-';
    j = x->n - 1;
    for (i = j; i >= 0; --i)
        buf[z++] = bs->digits[x->d[i]];
    buf[z] = '\0';
    return buf;
}

int bi_cmp_abs(const bigint_t *a, const bigint_t *b)
{
    int i;

    if (a->n != b->n)
        return (a->n > b->n) ? 1 : -1;
    for (i = a->n - 1; i >= 0; --i) {
        if (a->d[i] != b->d[i])
            return (a->d[i] > b->d[i]) ? 1 : -1;
    }
    return 0;
}

int bi_add(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs)
{
    int i;
    int carry;
    int na;
    int nb;

    r->n = 0;
    r->sign = 1;
    if (a->sign == b->sign) {
        r->sign = a->sign;
        carry = 0;
        na = a->n;
        nb = b->n;
        for (i = 0; i < na || i < nb || carry; ++i) {
            int da = (i < na) ? a->d[i] : 0;
            int db = (i < nb) ? b->d[i] : 0;
            int t = da + db + carry;
            bi_push_digit(r, t % bs->b);
            carry = t / bs->b;
        }
    } else {
        const bigint_t *p;
        const bigint_t *q;
        int cmp;

        p = a; q = b;
        cmp = bi_cmp_abs(p, q);
        if (cmp == 0) {
            r->n = 0; r->sign = 1; return 0;
        }
        if (cmp < 0) { p = b; q = a; }
        r->sign = p->sign;
        carry = 0;
        for (i = 0; i < p->n; ++i) {
            int dp = p->d[i];
            int dq = (i < q->n) ? q->d[i] : 0;
            int t = dp - dq - carry;
            if (t < 0) { t += bs->b; carry = 1; } else carry = 0;
            bi_push_digit(r, t);
        }
        bi_trim(r);
    }
    return 0;
}

int bi_sub(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs)
{
    bigint_t nb;
    int res;

    nb = *b;
    nb.sign = -b->sign;
    res = bi_add(r, a, &nb, bs);
    return res;
}

int bi_mul(bigint_t *r, const bigint_t *a, const bigint_t *b, const base_t *bs)
{
    int i;
    int j;
    int *tmp;

    free(r->d);
    r->cap = a->n + b->n + 2;
    r->d = calloc((size_t)r->cap, sizeof(int));
    if (!r->d) { r->n = 0; return -1; }
    r->n = a->n + b->n + 1;
    for (i = 0; i < a->n; ++i) {
        int carry = 0;
        for (j = 0; j < b->n || carry; ++j) {
            long cur = r->d[i + j] + (long)a->d[i] * (j < b->n ? b->d[j] : 0) + carry;
            r->d[i + j] = (int)(cur % bs->b);
            carry = (int)(cur / bs->b);
        }
    }
    bi_trim(r);
    r->sign = a->sign * b->sign;
    (void)tmp;
    return 0;
}

int bi_divmod(bigint_t *q, bigint_t *m, const bigint_t *a, const bigint_t *b, const base_t *bs)
{
    /* helpers */
    auto int mul_small(bigint_t *r, const bigint_t *x, int k, const base_t *bs) {
        int i, carry = 0;
        r->n = 0;
        if (k == 0 || x->n == 0) { r->n = 0; return 0; }
        if (ensure(r, x->n + 2) != 0) return -1;
        for (i = 0; i < x->n; ++i) {
            int t = x->d[i] * k + carry;
            r->d[i] = t % bs->b;
            carry = t / bs->b;
        }
        r->n = x->n;
        if (carry) r->d[r->n++] = carry;
        return 0;
    };
    auto int add_small(bigint_t *x, int k, const base_t *bs) {
        int i = 0, carry = k;
        if (ensure(x, 1) != 0) return -1;
        if (x->n == 0) { x->d[0] = 0; x->n = 1; }
        while (carry) {
            if (i >= x->n) { if (ensure(x, 1) != 0) return -1; x->d[x->n++] = 0; }
            int t = x->d[i] + carry;
            x->d[i] = t % bs->b;
            carry = t / bs->b;
            i += 1;
        }
        return 0;
    };
    auto int sub_inplace(bigint_t *x, const bigint_t *y, const base_t *bs) {
        int i, borrow = 0;
        for (i = 0; i < x->n; ++i) {
            int dy = (i < y->n) ? y->d[i] : 0;
            int t = x->d[i] - dy - borrow;
            if (t < 0) { t += bs->b; borrow = 1; } else borrow = 0;
            x->d[i] = t;
        }
        bi_trim(x);
        return 0;
    };

    bigint_t rem;
    int i;

    if (b->n == 0)
        return -1;
    bi_init(q);
    bi_init(&rem);
    bi_init(m);
    q->cap = a->n + 1;
    q->d = calloc((size_t)q->cap, sizeof(int));
    if (!q->d) return -1;
    q->n = a->n;
    /* long division */
    for (i = a->n - 1; i >= 0; --i) {
        int j;
        if (ensure(&rem, 1) != 0) return -1;
        /* rem = rem * base */
        if (rem.n == 0) { rem.n = 1; rem.d[0] = 0; }
        else {
            if (ensure(&rem, 1) != 0) return -1;
            for (j = rem.n; j > 0; --j)
                rem.d[j] = rem.d[j - 1];
            rem.n += 1;
            rem.d[0] = 0;
        }
        /* rem += a->d[i] */
        if (add_small(&rem, a->d[i], bs) != 0) return -1;
        /* find digit qd such that b*qd <= rem < b*(qd+1) */
        {
            int qd;
            bigint_t prod;
            bi_init(&prod);
            qd = bs->b - 1;
            for (; qd > 0; --qd) {
                mul_small(&prod, b, qd, bs);
                if (bi_cmp_abs(&prod, &rem) <= 0)
                    break;
            }
            q->d[i] = qd;
            if (qd > 0) {
                sub_inplace(&rem, &prod, bs);
            }
            bi_free(&prod);
        }
    }
    bi_trim(q);
    q->sign = a->sign * b->sign;
    rem.sign = a->sign;
    *m = rem;
    return 0;
}
