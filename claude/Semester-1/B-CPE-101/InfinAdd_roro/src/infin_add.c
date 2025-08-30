/*
** EPITECH PROJECT, 2024
** infin_add.c
** File description:
** infinite addition main function
*/

#include <stdlib.h>
#include "../include/infin_add.h"

static int is_negative(char const *nb)
{
    return (nb != NULL && nb[0] == '-');
}

static char const *get_absolute(char const *nb)
{
    if (nb == NULL)
        return NULL;
    return is_negative(nb) ? nb + 1 : nb;
}

char *infin_add(char const *nb1, char const *nb2)
{
    int neg1 = is_negative(nb1);
    int neg2 = is_negative(nb2);
    char const *abs1 = get_absolute(nb1);
    char const *abs2 = get_absolute(nb2);
    char *result;

    if (nb1 == NULL || nb2 == NULL)
        return NULL;
    if (!neg1 && !neg2) {
        result = add_positive(abs1, abs2);
    } else if (neg1 && neg2) {
        result = add_positive(abs1, abs2);
        if (result != NULL && result[0] != '0') {
            char *neg_result = malloc(my_strlen(result) + 2);
            if (neg_result == NULL) {
                free(result);
                return NULL;
            }
            neg_result[0] = '-';
            my_strcpy(neg_result + 1, result);
            free(result);
            result = neg_result;
        }
    } else if (neg1 && !neg2) {
        result = subtract_positive(abs2, abs1);
    } else {
        result = subtract_positive(abs1, abs2);
    }
    if (result != NULL)
        result = remove_leading_zeros(result);
    return result;
}