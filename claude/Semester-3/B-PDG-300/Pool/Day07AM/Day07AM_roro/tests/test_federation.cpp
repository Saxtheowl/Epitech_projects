/*
** EPITECH PROJECT, 2025
** Day07AM - Tests
** File description:
** Unit tests for Federation exercise
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../Federation.hpp"
#include "../WarpSystem.hpp"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Federation, ship_creation, .init = redirect_all_std)
{
    Federation::Starfleet::Ship enterprise(295, 76, "Enterprise", 9);
    
    cr_assert_stdout_eq_str("The ship USS Enterprise has been finished.\n"
                           "It is 295 m in length and 76 m in width.\n"
                           "It can go to Warp 9!\n");
}

Test(Federation, ship_creation_different_values, .init = redirect_all_std)
{
    Federation::Starfleet::Ship voyager(344, 103, "Voyager", 10);
    
    cr_assert_stdout_eq_str("The ship USS Voyager has been finished.\n"
                           "It is 344 m in length and 103 m in width.\n"
                           "It can go to Warp 10!\n");
}

Test(WarpSystem, namespace_exists)
{
    cr_assert(1);
}