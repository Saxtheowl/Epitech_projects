/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 1 test
** File description:
** Test for Knight class
*/

#include "Knight.hpp"

int main()
{
    Knight knight("Arthur", 20);
    knight.attack();
    knight.special();
    knight.rest();
    knight.special();
    knight.damage(50);
    return 0;
}