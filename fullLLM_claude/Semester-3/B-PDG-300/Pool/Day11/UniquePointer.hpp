#pragma once

#include "IObject.hpp"
#include <utility>

class UniquePointer {
private:
    IObject* ptr;

public:
    UniquePointer() : ptr(nullptr) {}
    UniquePointer(IObject* obj) : ptr(obj) {}

    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UniquePointer& operator=(IObject* obj) {
        delete ptr;
        ptr = obj;
        return *this;
    }

    ~UniquePointer() {
        delete ptr;
    }

    IObject* operator->() const {
        return ptr;
    }

    IObject& operator*() const {
        return *ptr;
    }

    void reset(IObject* obj = nullptr) {
        delete ptr;
        ptr = obj;
    }

    void swap(UniquePointer& other) {
        std::swap(ptr, other.ptr);
    }
};