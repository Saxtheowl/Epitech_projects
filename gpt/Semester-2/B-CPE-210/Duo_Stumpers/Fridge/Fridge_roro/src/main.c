/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fridge.h"

static void trim(char *s)
{
    int i;
    int j;

    i = 0;
    while (isspace((unsigned char)s[i]))
        i = i + 1;
    j = 0;
    while (s[i] != '\0') {
        s[j] = s[i];
        i = i + 1;
        j = j + 1;
    }
    s[j] = '\0';
    while (j > 0 && isspace((unsigned char)s[j - 1])) {
        s[j - 1] = '\0';
        j = j - 1;
    }
}

int parse_list(const char *s, item_t *items, int max)
{
    int count;
    const char *p;

    count = 0;
    p = s;
    while (*p != '\0' && count < max) {
        char name[64];
        char qbuf[16];
        int ni = 0;
        int qi = 0;

        while (*p != '\0' && *p != ':' && ni < 63)
            name[ni++] = *p++;
        if (*p != ':')
            break;
        name[ni] = '\0';
        p++;
        while (*p != '\0' && *p != ',' && qi < 15)
            qbuf[qi++] = *p++;
        qbuf[qi] = '\0';
        if (*p == ',')
            p++;
        trim(name);
        items[count].qty = atoi(qbuf);
        strncpy(items[count].name, name, 63);
        items[count].name[63] = '\0';
        count = count + 1;
        while (*p == ' ')
            p++;
    }
    return count;
}

int can_prepare(const item_t *inv, int n_inv, const item_t *rec, int n_rec)
{
    int i;
    int j;
    int ok;

    i = 0;
    while (i < n_rec) {
        ok = 0;
        j = 0;
        while (j < n_inv) {
            if (strcmp(rec[i].name, inv[j].name) == 0) {
                if (inv[j].qty >= rec[i].qty)
                    ok = 1;
                break;
            }
            j = j + 1;
        }
        if (!ok)
            return 0;
        i = i + 1;
    }
    return 1;
}

int main(int argc, char **argv)
{
    item_t inv[64];
    item_t rec[64];
    int n_inv;
    int n_rec;

    if (argc != 3)
        return 84;
    n_inv = parse_list(argv[1], inv, 64);
    n_rec = parse_list(argv[2], rec, 64);
    if (n_inv <= 0 || n_rec <= 0)
        return 84;
    if (can_prepare(inv, n_inv, rec, n_rec))
        printf("OK\n");
    else
        printf("KO\n");
    return 0;
}

