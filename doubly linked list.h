#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<class T> class DoubleLinkedList;
template<class T>
class DoubleNode
{
    friend class DoubleLinkedList<T>;

public:
    DoubleNode(const T& val, DoubleNode* f = nullptr, DoubleNode* l = nullptr)
        : next{ f }, prev{ l }, value{ val }
    {}
    T getValue() const { return value; }
    DoubleNode<T>* getNext() const { return next; }
private:
    T value;
    DoubleNode* next;
    DoubleNode* prev;
};

template <class T>
class DoubleLinkedList
{
    template<class U>
    friend std::ostream& operator<<(std::ostream& output, const DoubleLinkedList<U>& list);

public:
    size_t length = 0;

    DoubleLinkedList()
        : first{ nullptr }, last{ nullptr }
    {}

    DoubleLinkedList(size_t l)
        : first{ nullptr }, last{ nullptr }
    {
        if (l == 0) {
            throw std::length_error("length cannot be zero");
        }
        for (size_t i = 0; i < l; i++) {
            push_back(T());
        }
    }

    DoubleLinkedList(const std::initializer_list<T>& values)
        : first{ nullptr }, last{ nullptr }
    {
        for (const T& i : values) {
            push_back(i);
        }
    }

    bool empty() const {
        return first == nullptr;
    }

    void push_back(const T& newValue) {
        if (empty()) {
            DoubleNode<T>* newNode = new DoubleNode<T>(newValue);
            first = last = newNode;
        }
        else {
            DoubleNode<T>* newNode = new DoubleNode<T>(newValue);
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        length++;
    }

    T& pop_back() {
        if (empty()) {
            throw std::logic_error("the list is empty");
        }
        else {
            DoubleNode<T>* temp = last;
            last = last->prev;
            if (last != nullptr) {
                last->next = nullptr;
            }
            else {
                first = nullptr;
            }
            T& val = temp->value;
            delete temp;
            length--;
            if (length == 0) {
                first = nullptr;
            }
            return val;
        }
    }

    T back() const {
        if (empty()) {
            throw std::length_error("it's empty");
        }
        return last->value;
    }

    void push_front(const T& newValue) {
        if (empty()) {
            DoubleNode<T>* newNode = new DoubleNode<T>(newValue);
            first = last = newNode;
        }
        else {
            DoubleNode<T>* newNode = new DoubleNode<T>(newValue);
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        }
        length++;
    }

    T& pop_front() {
        if (empty()) {
            throw std::logic_error("the list is empty");
        }
        else {
            DoubleNode<T>* temp = first;
            T& val = temp->value;
            first = first->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            delete temp;
            length--;
            if (length == 0) {
                last = nullptr;
            }
            return val;
        }
    }

    T front() const {
        if (empty()) {
            throw std::length_error("it's empty");
        }
        return first->value;
    }

    void printRevers() const {
        DoubleNode<T>* cur = last;
        for (size_t i = 0; i < length; i++) {
            std::cout << cur->getValue() << " ";
            cur = cur->prev;
        }
    }

    DoubleLinkedList<T> reverse() const {
        DoubleLinkedList<T> newLinkedList;
        DoubleNode<T>* cur = last;
        for (size_t i = 0; i < length; i++) {
            newLinkedList.push_back(cur->getValue());
            cur = cur->prev;
        }
        return newLinkedList;
    }

    void operator=(const DoubleLinkedList<T>& newLinked) {
        while (!empty()) {
            pop_back();
        }
        DoubleNode<T>* curOne = nullptr;
        DoubleNode<T>* curTwo = newLinked.first;
        for (size_t i = 0; i < newLinked.length; i++) {
            if (i == 0) {
                push_back(curTwo->getValue());
                curOne = first;
            }
            else {
                curOne->next = new DoubleNode<T>(curTwo->getValue(), nullptr, curOne);
                curOne = curOne->next;
                if (i == newLinked.length - 1) {
                    last = curOne;
                }
            }
            curTwo = curTwo->next;
        }
        length = newLinked.length;
    }

    void insert(int index, const T& v) {
        if (index > length) {
            throw std::out_of_range("out of range");
        }
        if (index == 0) {
            push_front(v);
        }
        else if (index == length) {
            push_back(v);
        }
        else {
            DoubleNode<T>* cur = first;
            for (int i = 0; i < index - 1; i++) {
                cur = cur->next;
            }
            DoubleNode<T>* nextCur = cur->next;
            DoubleNode<T>* newNode = new DoubleNode<T>(v);
            newNode->prev = cur;
            newNode->next = nextCur;
            cur->next = newNode;
            nextCur->prev = newNode;
            length++;
        }
    }

    void remove(int index) {
        if (index >= length) {
            throw std::out_of_range("out of range");
        }
        if (index == 0) {
            pop_front();
        }
        else if (index == length - 1) {
            pop_back();
        }
        else {
            DoubleNode<T>* cur = first;
            for (int i = 0; i < index; i++) {
                cur = cur->next;
            }
            DoubleNode<T>* prevCur = cur->prev;
            DoubleNode<T>* nextCur = cur->next;
            prevCur->next = nextCur;
            nextCur->prev = prevCur;
            delete cur;
            length--;
        }
    }

    T operator[](int index) const {
        if (index >= length) {
            throw std::out_of_range("out of range");
        }
        if (index == 0) {
            return front();
        }
        else if (index == length - 1) {
            return back();
        }
        else {
            DoubleNode<T>* cur = first;
            for (int i = 0; i < index; i++) {
                cur = cur->next;
            }
            return cur->getValue();
        }
    }

    ~DoubleLinkedList() {
        while (!empty()) {
            pop_back();
        }
    }

private:
    DoubleNode<T>* first;
    DoubleNode<T>* last;
};

template<class T>
std::ostream& operator<<(std::ostream& output, const DoubleLinkedList<T>& list) {
    DoubleNode<T>* cur = list.first;
    for (size_t i = 0; i < list.length; i++) {
        output << cur->getValue() << " ";
        cur = cur->getNext();
    }
    return output;
}

#endif // DOUBLELINKEDLIST_H
