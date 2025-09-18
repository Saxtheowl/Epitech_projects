/*
** EPITECH PROJECT, 2024
** Day13 PDG - Exercise 3
** File description:
** UniquePointer template class
*/

#ifndef UNIQUEPOINTER_HPP_
#define UNIQUEPOINTER_HPP_

template<typename Type>
class UniquePointer
{
private:
    Type* ptr;

public:
    UniquePointer() : ptr(nullptr) {}
    
    UniquePointer(Type* p) : ptr(p) {}
    
    // Non-copyable
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;
    
    ~UniquePointer()
    {
        delete ptr;
    }
    
    UniquePointer& operator=(Type* p)
    {
        if (ptr != p) {
            delete ptr;
            ptr = p;
        }
        return *this;
    }
    
    void reset()
    {
        delete ptr;
        ptr = nullptr;
    }
    
    Type* get()
    {
        return ptr;
    }
    
    Type* operator->()
    {
        return ptr;
    }
};

#endif /* !UNIQUEPOINTER_HPP_ */