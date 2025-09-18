#pragma once

#include "IObject.hpp"
#include <utility>

class SharedPointer {
private:
    IObject* ptr;
    size_t* refCount;

    void release() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
        }
    }

public:
    SharedPointer() : ptr(nullptr), refCount(nullptr) {}

    SharedPointer(IObject* obj) : ptr(obj), refCount(obj ? new size_t(1) : nullptr) {}

    SharedPointer(const SharedPointer& other) : ptr(other.ptr), refCount(other.refCount) {
        if (refCount) {
            (*refCount)++;
        }
    }

    SharedPointer& operator=(const SharedPointer& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) {
                (*refCount)++;
            }
        }
        return *this;
    }

    SharedPointer& operator=(IObject* obj) {
        release();
        ptr = obj;
        refCount = obj ? new size_t(1) : nullptr;
        return *this;
    }

    ~SharedPointer() {
        release();
    }

    IObject* operator->() const {
        return ptr;
    }

    IObject& operator*() const {
        return *ptr;
    }

    void reset(IObject* obj = nullptr) {
        release();
        ptr = obj;
        refCount = obj ? new size_t(1) : nullptr;
    }

    void swap(SharedPointer& other) {
        std::swap(ptr, other.ptr);
        std::swap(refCount, other.refCount);
    }

    size_t use_count() const {
        return refCount ? *refCount : 0;
    }
};