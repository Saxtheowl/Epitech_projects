/*
** EPITECH PROJECT, 2025
** Pokemon
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "pokemon.h"

Test(pokemon, effectiveness_basic)
{
    cr_assert_eq(effectiveness("fire", "grass"), EFF_SUPER);
    cr_assert_eq(effectiveness("water", "fire"), EFF_SUPER);
    cr_assert_eq(effectiveness("grass", "fire"), EFF_NOT);
    cr_assert_eq(effectiveness("electric", "ground"), EFF_NOT);
}

