/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 4 test
** File description:
** Test for Paladin class
*/

#include "Paladin.hpp"

int main()
{
    Paladin paladin("Uther", 99);
    paladin.attack();
    paladin.special();
    paladin.rest();
    paladin.damage(50);
    return 0;
}