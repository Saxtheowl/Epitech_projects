/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 5 test
** File description:
** Test for Character Interface
*/

#include "ICharacter.hpp"
#include "Peasant.hpp"
#include "Knight.hpp"
#include "Enchanter.hpp"
#include "Priest.hpp"
#include "Paladin.hpp"

int main()
{
    ICharacter* peasant = new Peasant("Gildas", 42);
    ICharacter* knight = new Knight("Arthur", 20);
    ICharacter* enchanter = new Enchanter("Merlin", 20);
    ICharacter* priest = new Priest("Trichelieu", 20);
    ICharacter* paladin = new Paladin("Uther", 99);

    peasant->attack();
    knight->special();
    enchanter->rest();
    priest->damage(21);
    paladin->attack();

    delete peasant;
    delete knight;
    delete enchanter;
    delete priest;
    delete paladin;

    return 0;
}