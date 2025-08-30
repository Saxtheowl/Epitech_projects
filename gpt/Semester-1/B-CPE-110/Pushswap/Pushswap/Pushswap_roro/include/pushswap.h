/*
** EPITECH PROJECT, 2025
** Pushswap_roro
** File description:
** Prototypes for pushswap
*/

#ifndef PUSHSWAP_H
    #define PUSHSWAP_H

    #include <stddef.h>

    #define ERR_CODE 84

    typedef struct vec_s {
        int *data;
        int size;
        int cap;
    } vec_t;

    typedef struct ops_s {
        char *buf;
        int len;
        int cap;
    } ops_t;

    int run_pushswap(int ac, char **av);

    int vec_init(vec_t *v);
    void vec_free(vec_t *v);
    int vec_push(vec_t *v, int x);
    int vec_pop_front(vec_t *v, int *out);
    int vec_push_front(vec_t *v, int x);
    int vec_rotate(vec_t *v);
    int vec_rrotate(vec_t *v);

    int ops_init(ops_t *o);
    void ops_free(ops_t *o);
    int ops_add(ops_t *o, const char *op);

    int parse_args(int ac, char **av, vec_t *out);
    int compress_values(vec_t *v);
    int is_sorted(const vec_t *v);

#endif /* PUSHSWAP_H */
