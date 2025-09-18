/*
** EPITECH PROJECT, 2024
** Day13 PDG - Test Exercise 3
** File description:
** Test for UniquePointer
*/

#include "UniquePointer.hpp"
#include <iostream>

class Example
{
private:
    int _id;
    
public:
    Example(int id) : _id(id) { std::cout << "#" << _id << " construction" << std::endl; }
    ~Example() { std::cout << "#" << _id << " destruction" << std::endl; }
    void method() const { std::cout << "#" << _id << " method" << std::endl; }
};

int main(void)
{
    UniquePointer<Example> ptr1(new Example(1));
    UniquePointer<Example> ptr2(new Example(2));
    
    ptr1.reset();
    ptr2 = new Example(3);
    ptr2.get()->method();
    ptr2->method();
    
    return 0;
}