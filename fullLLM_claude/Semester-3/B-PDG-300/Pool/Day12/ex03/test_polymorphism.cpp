/*
** EPITECH PROJECT, 2024
** Day12 PDG - Test Exercise 3
** File description:
** Test for polymorphism
*/

#include "Buzz.hpp"
#include "Woody.hpp"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "=== Testing polymorphism ===\n";
    
    std::unique_ptr<Toy> b(new Buzz("buzziiiii"));
    std::unique_ptr<Toy> w(new Woody("wood"));
    std::unique_ptr<Toy> t(new Toy(Toy::ALIEN, "ET", "alien.txt"));
    
    b->speak("To the code, and beyond !!!!!!!!");
    w->speak("There's a snake in my boot.");
    t->speak("the claaaaaaw");
    
    std::cout << "\nPolymorphism test completed!" << std::endl;
    return 0;
}