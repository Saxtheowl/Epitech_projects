/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include "spongebob.h"

static int check_with_start(const char *s, int start_upper)
{
    int i;
    int expect_upper;

    expect_upper = start_upper;
    i = 0;
    while (s[i] != '\0') {
        if (isalpha((unsigned char)s[i])) {
            if (expect_upper && !isupper((unsigned char)s[i]))
                return 0;
            if (!expect_upper && !islower((unsigned char)s[i]))
                return 0;
            expect_upper = !expect_upper;
        }
        i = i + 1;
    }
    return 1;
}

int is_spongebob_case(const char *s)
{
    if (s == NULL || *s == '\0')
        return 0;
    if (check_with_start(s, 0))
        return 1;
    if (check_with_start(s, 1))
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    if (is_spongebob_case(argv[1]))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

