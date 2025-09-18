/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 2 test
** File description:
** Test for Enchanter class
*/

#include "Enchanter.hpp"

int main()
{
    Enchanter enchanter("Merlin", 40);
    enchanter.attack();
    enchanter.special();
    enchanter.rest();
    enchanter.special();
    enchanter.damage(50);
    return 0;
}