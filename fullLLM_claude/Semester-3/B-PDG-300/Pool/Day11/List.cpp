#include "List.hpp"

List::List() : head(nullptr), tail(nullptr), listSize(0) {}

List::~List() {
    clear();
}

bool List::empty() const {
    return listSize == 0;
}

std::size_t List::size() const {
    return listSize;
}

IObject*& List::front() {
    if (empty()) {
        throw InvalidOperationException();
    }
    return head->data;
}

IObject* List::front() const {
    if (empty()) {
        throw InvalidOperationException();
    }
    return head->data;
}

IObject*& List::back() {
    if (empty()) {
        throw InvalidOperationException();
    }
    return tail->data;
}

IObject* List::back() const {
    if (empty()) {
        throw InvalidOperationException();
    }
    return tail->data;
}

void List::pushBack(IObject* obj) {
    Node* newNode = new Node(obj);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

void List::pushFront(IObject* obj) {
    Node* newNode = new Node(obj);
    if (empty()) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    listSize++;
}

void List::popFront() {
    if (empty()) {
        throw InvalidOperationException();
    }
    Node* toDelete = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete toDelete;
    listSize--;
}

void List::popBack() {
    if (empty()) {
        throw InvalidOperationException();
    }
    Node* toDelete = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete toDelete;
    listSize--;
}

void List::clear() {
    while (!empty()) {
        popFront();
    }
}

void List::forEach(void(*function)(IObject*)) {
    for (Node* current = head; current; current = current->next) {
        function(current->data);
    }
}

List::Iterator List::begin() const {
    return Iterator(head, this);
}

List::Iterator List::end() const {
    return Iterator(nullptr, this);
}

List::Iterator List::erase(Iterator it) {
    if (it.owner != this || !it.current) {
        throw InvalidIteratorException();
    }

    Node* toDelete = it.current;
    Node* nextNode = toDelete->next;

    if (toDelete == head && toDelete == tail) {
        head = tail = nullptr;
    } else if (toDelete == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (toDelete == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
    }

    delete toDelete;
    listSize--;
    return Iterator(nextNode, this);
}

List::Iterator List::insert(Iterator it, IObject* obj) {
    if (it.owner != this) {
        throw InvalidIteratorException();
    }

    if (!it.current) {
        pushBack(obj);
        return Iterator(tail, this);
    }

    Node* newNode = new Node(obj);
    Node* nextNode = it.current;

    if (nextNode == head) {
        pushFront(obj);
        return Iterator(head, this);
    }

    newNode->next = nextNode;
    newNode->prev = nextNode->prev;
    nextNode->prev->next = newNode;
    nextNode->prev = newNode;
    listSize++;

    return Iterator(newNode, this);
}