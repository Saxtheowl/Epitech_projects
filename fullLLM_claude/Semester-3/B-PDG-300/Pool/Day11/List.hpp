#pragma once

#include "IObject.hpp"
#include <exception>
#include <cstddef>

class List {
private:
    struct Node {
        IObject* data;
        Node* next;
        Node* prev;

        Node(IObject* obj) : data(obj), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t listSize;

public:
    class InvalidOperationException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Invalid operation on list";
        }
    };

    class InvalidIteratorException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Invalid iterator";
        }
    };

    class Iterator {
    private:
        Node* current;
        const List* owner;

    public:
        class OutOfRangeException : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Iterator out of range";
            }
        };

        Iterator(Node* node, const List* list) : current(node), owner(list) {}

        IObject* operator*() const {
            if (!current) {
                throw OutOfRangeException();
            }
            return current->data;
        }

        Iterator& operator++() {
            if (!current) {
                throw OutOfRangeException();
            }
            current = current->next;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current && owner == other.owner;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        friend class List;
    };

    List();
    ~List();

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    bool empty() const;
    std::size_t size() const;
    IObject*& front();
    IObject* front() const;
    IObject*& back();
    IObject* back() const;
    void pushBack(IObject* obj);
    void pushFront(IObject* obj);
    void popFront();
    void popBack();
    void clear();
    void forEach(void(*function)(IObject*));

    Iterator begin() const;
    Iterator end() const;
    Iterator erase(Iterator it);
    Iterator insert(Iterator it, IObject* obj);
};