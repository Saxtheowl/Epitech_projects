/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0 test
** File description:
** Test for fruit hierarchy
*/

#include "Lemon.hpp"
#include "Orange.hpp"
#include "Strawberry.hpp"
#include "Almond.hpp"
#include <iostream>

int main()
{
    Lemon lemon;
    Orange orange;
    Strawberry strawberry;
    Almond almond;

    std::cout << "=== Before peeling ===" << std::endl;
    std::cout << lemon << " peeled: " << lemon.isPeeled() << " vitamins: " << lemon.getVitamins() << std::endl;
    std::cout << orange << " peeled: " << orange.isPeeled() << " vitamins: " << orange.getVitamins() << std::endl;
    std::cout << strawberry << " peeled: " << strawberry.isPeeled() << " vitamins: " << strawberry.getVitamins() << std::endl;
    std::cout << almond << " peeled: " << almond.isPeeled() << " vitamins: " << almond.getVitamins() << std::endl;

    std::cout << "\n=== After peeling ===" << std::endl;
    lemon.peel();
    orange.peel();
    strawberry.peel();
    almond.peel();

    std::cout << lemon << " peeled: " << lemon.isPeeled() << " vitamins: " << lemon.getVitamins() << std::endl;
    std::cout << orange << " peeled: " << orange.isPeeled() << " vitamins: " << orange.getVitamins() << std::endl;
    std::cout << strawberry << " peeled: " << strawberry.isPeeled() << " vitamins: " << strawberry.getVitamins() << std::endl;
    std::cout << almond << " peeled: " << almond.isPeeled() << " vitamins: " << almond.getVitamins() << std::endl;

    return 0;
}