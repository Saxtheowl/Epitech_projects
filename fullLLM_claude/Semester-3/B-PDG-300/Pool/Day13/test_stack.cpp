/*
** EPITECH PROJECT, 2024
** Day13 PDG - Test Exercise 2
** File description:
** Test for Stack class
*/

#include "Stack.hpp"
#include <iostream>

int main(void)
{
    Stack stack;
    
    stack.push(42.21);
    stack.push(84.42);
    stack.push(21.12);
    stack.add();
    stack.div();
    
    try {
        stack.mul();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    std::cout << stack.top() << std::endl;
    
    return 0;
}