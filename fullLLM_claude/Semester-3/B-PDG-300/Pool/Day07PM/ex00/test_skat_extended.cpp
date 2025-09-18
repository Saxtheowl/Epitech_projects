/*
** EPITECH PROJECT, 2024
** Day07 PDG - Extended Test Exercise 0
** File description:
** Extended test for Skat class
*/

#include "Skat.hpp"
#include <iostream>

int main()
{
    // Test default constructor
    Skat defaultSkat;
    std::cout << "Default Skat name: " << defaultSkat.name() << std::endl;
    defaultSkat.status();
    
    // Test constructor with parameters
    Skat s("Junior", 5);
    std::cout << "Soldier " << s.name() << std::endl;
    s.status();
    s.useStimPaks();
    
    // Test sharing stimpaks
    int stock = 0;
    std::cout << "Stock before sharing: " << stock << std::endl;
    s.shareStimPaks(2, stock);
    std::cout << "Stock after sharing: " << stock << std::endl;
    s.status();
    
    // Test sharing too many stimpaks
    s.shareStimPaks(10, stock);
    
    // Test adding stimpaks
    s.addStimPaks(3);
    s.status();
    
    // Test adding 0 stimpaks
    s.addStimPaks(0);
    
    // Test using all stimpaks
    while (s.stimPaks() > 0) {
        s.useStimPaks();
    }
    s.status();
    
    // Test using stimpaks when empty
    s.useStimPaks();
    
    return 0;
}