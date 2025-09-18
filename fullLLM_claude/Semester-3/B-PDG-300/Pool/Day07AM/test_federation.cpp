/*
** EPITECH PROJECT, 2024
** Day07AM PDG - Test
** File description:
** Test for Federation::Starfleet::Ship
*/

#include "Federation.hpp"
#include "WarpSystem.hpp"

int main()
{
    Federation::Starfleet::Ship enterprise(289, 132, "Enterprise", 9);
    Federation::Starfleet::Ship voyager(344, 138, "Voyager", 9);
    
    return 0;
}