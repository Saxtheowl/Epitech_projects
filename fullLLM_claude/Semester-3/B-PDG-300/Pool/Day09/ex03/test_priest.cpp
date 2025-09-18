/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 3 test
** File description:
** Test for Priest class
*/

#include "Priest.hpp"

int main()
{
    Priest priest("Trichelieu", 20);
    priest.attack();
    priest.special();
    priest.rest();
    priest.special();
    priest.damage(50);
    return 0;
}