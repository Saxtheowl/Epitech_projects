#include "UniquePointer.hpp"
#include "SharedPointer.hpp"
#include "List.hpp"
#include <iostream>
#include <cassert>

void testUniquePointer() {
    std::cout << "Testing UniquePointer..." << std::endl;

    {
        UniquePointer ptr1;
        UniquePointer ptr2(new TestObject("Test1"));
    }

    {
        UniquePointer ptr1(new TestObject("Move1"));
        UniquePointer ptr2 = std::move(ptr1);
        ptr2->touch();
    }

    std::cout << "UniquePointer tests passed!" << std::endl;
}

void testSharedPointer() {
    std::cout << "Testing SharedPointer..." << std::endl;

    {
        SharedPointer ptr1;
        SharedPointer ptr2(new TestObject("Shared1"));
        SharedPointer ptr3(ptr2);

        assert(ptr2.use_count() == 2);
        assert(ptr3.use_count() == 2);

        ptr2->touch();
        (*ptr3).touch();
    }

    std::cout << "SharedPointer tests passed!" << std::endl;
}

void testList() {
    std::cout << "Testing List..." << std::endl;

    List list;
    assert(list.empty());
    assert(list.size() == 0);

    list.pushBack(new TestObject("Item1"));
    list.pushBack(new TestObject("Item2"));
    list.pushFront(new TestObject("Item0"));

    assert(!list.empty());
    assert(list.size() == 3);

    // Test iterator
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it) {
            (*it)->touch();
        }
    }

    list.clear();
    assert(list.empty());

    std::cout << "List tests passed!" << std::endl;
}

int main() {
    std::cout << "Running unit tests for Day11 project..." << std::endl;

    try {
        testUniquePointer();
        testSharedPointer();
        testList();

        std::cout << "\nAll tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}