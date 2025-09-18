/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 0 test
** File description:
** Test for Peasant class
*/

#include "Peasant.hpp"

int main()
{
    Peasant peasant("Gildas", 42);
    peasant.damage(50);
    peasant.damage(100);
    peasant.damage(200);
    peasant.rest();
    return 0;
}