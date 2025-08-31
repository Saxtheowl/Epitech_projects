/*
** EPITECH PROJECT, 2025
** FrenchNameFormatter
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "fr_name.h"

Test(fr_name, simple)
{
    char out[256];

    format_name_fr("jean-claude   van  damme", out, 256);
    cr_assert_str_eq(out, "Jean-Claude Van Damme");
}

Test(fr_name, accents_and_hyphens)
{
    char out[256];
    format_name_fr("marie-joSEphe dupont", out, 256);
    cr_assert_str_eq(out, "Marie-Josephe Dupont");
}
