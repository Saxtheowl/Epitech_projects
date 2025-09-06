/*
** EPITECH PROJECT, 2025
** Day08 - Tests
** File description:
** Unit tests for Droid class
*/

#include <criterion/criterion.h>
#include "../ex00/Droid.hpp"

Test(Droid, default_constructor)
{
    Droid droid;
    
    cr_assert_str_eq(droid.getId().c_str(), "");
    cr_assert_eq(droid.getEnergy(), 50);
    cr_assert_eq(droid.getAttack(), 25);
    cr_assert_eq(droid.getToughness(), 15);
    cr_assert_str_eq(droid.getStatus().c_str(), "Standing by");
}

Test(Droid, parametric_constructor)
{
    Droid droid("R2D2");
    
    cr_assert_str_eq(droid.getId().c_str(), "R2D2");
    cr_assert_eq(droid.getEnergy(), 50);
    cr_assert_eq(droid.getAttack(), 25);
    cr_assert_eq(droid.getToughness(), 15);
    cr_assert_str_eq(droid.getStatus().c_str(), "Standing by");
}

Test(Droid, copy_constructor)
{
    Droid droid1("C3PO");
    droid1.setEnergy(75);
    droid1.setStatus("Active");
    
    Droid droid2(droid1);
    
    cr_assert_str_eq(droid2.getId().c_str(), "C3PO");
    cr_assert_eq(droid2.getEnergy(), 75);
    cr_assert_str_eq(droid2.getStatus().c_str(), "Active");
}

Test(Droid, assignment_operator)
{
    Droid droid1("BB8");
    droid1.setEnergy(80);
    
    Droid droid2;
    droid2 = droid1;
    
    cr_assert_str_eq(droid2.getId().c_str(), "BB8");
    cr_assert_eq(droid2.getEnergy(), 80);
}

Test(Droid, equality_operators)
{
    Droid droid1("Test1");
    Droid droid2("Test2");
    Droid droid3("Test3");
    
    droid3.setEnergy(droid1.getEnergy());
    droid3.setAttack(droid1.getAttack());
    droid3.setToughness(droid1.getToughness());
    droid3.setStatus(droid1.getStatus());
    
    cr_assert(droid1 == droid3);
    cr_assert(droid1 != droid2);
}

Test(Droid, energy_transfer)
{
    Droid droid("Test");
    droid.setEnergy(30);
    
    std::size_t energySource = 100;
    droid << energySource;
    
    cr_assert_eq(droid.getEnergy(), 100);
    cr_assert_eq(energySource, 30);
}