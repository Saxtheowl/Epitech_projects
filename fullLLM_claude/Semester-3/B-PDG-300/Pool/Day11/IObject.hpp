#pragma once

#include <string>
#include <iostream>

class IObject {
public:
    virtual ~IObject() = default;
    virtual void touch() = 0;
};

class TestObject : public IObject {
private:
    std::string name;

public:
    TestObject(const std::string& name) : name(name) {
        std::cout << name << " is alive" << std::endl;
    }

    ~TestObject() {
        std::cout << name << " is dead" << std::endl;
    }

    void touch() override {
        std::cout << name << " is touched" << std::endl;
    }
};