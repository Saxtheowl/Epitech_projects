/*
** EPITECH PROJECT, 2025
** InfinAdd_roro
** File description:
** Infinite precision addition of two integers as strings
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "infin_add.h"

static char *prepend_minus(char *s)
{
    size_t n;
    char *p;

    if (s == NULL)
        return NULL;
    n = strlen(s);
    p = malloc(n + 2);
    if (p == NULL) {
        free(s);
        return NULL;
    }
    p[0] = '-';
    memcpy(p + 1, s, n + 1);
    free(s);
    return p;
}

static int cmp_abs(const char *a, const char *b)
{
    size_t na;
    size_t nb;

    while (*a == '0' && a[1] != '\0')
        a++;
    while (*b == '0' && b[1] != '\0')
        b++;
    na = strlen(a);
    nb = strlen(b);
    if (na != nb)
        return (na > nb) ? 1 : -1;
    return strcmp(a, b);
}

static char *rev(char *s)
{
    size_t i;
    size_t j;
    char t;

    i = 0;
    j = strlen(s);
    if (j == 0)
        return s;
    j -= 1;
    while (i < j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i += 1;
        j -= 1;
    }
    return s;
}

static char *add_abs(const char *a, const char *b)
{
    int ia;
    int ib;
    int carry;
    int da;
    int db;
    int s;
    int k;
    int na;
    int nb;
    char *out;

    na = (int)strlen(a);
    nb = (int)strlen(b);
    out = malloc((size_t)(na + nb + 3));
    if (out == NULL)
        return NULL;
    k = 0;
    carry = 0;
    ia = na - 1;
    ib = nb - 1;
    while (ia >= 0 || ib >= 0 || carry) {
        da = (ia >= 0) ? (a[ia] - '0') : 0;
        db = (ib >= 0) ? (b[ib] - '0') : 0;
        s = da + db + carry;
        out[k++] = (char)('0' + (s % 10));
        carry = s / 10;
        ia -= 1;
        ib -= 1;
    }
    out[k] = '\0';
    rev(out);
    return out;
}

static char *sub_abs(const char *a, const char *b)
{
    int ia;
    int ib;
    int da;
    int db;
    int k;
    int na;
    int nb;
    int borrow;
    char *out;

    na = (int)strlen(a);
    nb = (int)strlen(b);
    out = malloc((size_t)(na + 1));
    if (out == NULL)
        return NULL;
    k = 0;
    borrow = 0;
    ia = na - 1;
    ib = nb - 1;
    while (ia >= 0) {
        da = a[ia] - '0' - borrow;
        db = (ib >= 0) ? (b[ib] - '0') : 0;
        if (da < db) {
            da += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        out[k++] = (char)('0' + (da - db));
        ia -= 1;
        ib -= 1;
    }
    while (k > 1 && out[k - 1] == '0')
        k -= 1;
    out[k] = '\0';
    rev(out);
    return out;
}

int is_number(const char *s)
{
    const char *p;

    if (s == NULL || *s == '\0')
        return 0;
    p = s;
    if (*p == '+' || *p == '-')
        p += 1;
    if (*p == '\0')
        return 0;
    for (; *p; ++p) {
        if (!isdigit((unsigned char)*p))
            return 0;
    }
    return 1;
}

void trim_sign(const char *s, const char **digits, int *neg)
{
    const char *p;

    p = s;
    *neg = 0;
    if (*p == '+' || *p == '-') {
        *neg = (*p == '-') ? 1 : 0;
        p += 1;
    }
    while (*p == '0' && p[1] != '\0')
        p += 1;
    *digits = p;
}

char *infin_add(const char *a, const char *b)
{
    const char *da;
    const char *db;
    int na;
    int nb;
    int c;
    char *res;

    if (!is_number(a) || !is_number(b))
        return NULL;
    trim_sign(a, &da, &na);
    trim_sign(b, &db, &nb);
    if (na == nb) {
        res = add_abs(da, db);
    } else {
        c = cmp_abs(da, db);
        if (na && !nb) {
            res = (c >= 0) ? sub_abs(da, db) : sub_abs(db, da);
            if (c >= 0 && res && strcmp(res, "0") != 0)
                res = prepend_minus(res);
        } else if (!na && nb) {
            res = (c >= 0) ? sub_abs(da, db) : sub_abs(db, da);
            if (c < 0 && res && strcmp(res, "0") != 0)
                res = prepend_minus(res);
        } else {
            res = add_abs(da, db);
        }
    }
    if (res == NULL)
        return NULL;
    if (na && nb && strcmp(res, "0") != 0)
        return prepend_minus(res);
    return res;
}
