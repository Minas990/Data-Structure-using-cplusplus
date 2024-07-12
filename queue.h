#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

struct Node
{
    int data;
    Node* next;
};

class QUEUE
{
private:
    Node* first;
    Node* rear;

public:
    QUEUE() : first(nullptr), rear(nullptr) {}

    ~QUEUE()
    {
        while (first)
        {
            Node* p = first->next;
            delete first;
            first = p;
        }
        rear = nullptr; // Ensure rear is null after deletion
    }

    bool isEmpty() const
    {
        return !first;
    }

    void enqueue(int x)
    {
        Node* t = new Node();
        t->data = x;
        t->next = nullptr;
        if (isEmpty())
            first = rear = t;
        else
        {
            rear->next = t;
            rear = t;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty. Cannot dequeue." << std::endl;
            return;
        }
        if (first == rear)
        {
            delete first;
            first = rear = nullptr;
        }
        else
        {
            Node* p = first->next;
            delete first;
            first = p;
        }
    }

    int get_front() const
    {
        if (isEmpty())
            return -1;
        else
            return first->data;
    }

    void display() const
    {
        Node* p = first;
        while (p)
        {
            std::cout << p->data << ' ';
            p = p->next;
        }
        std::cout << std::endl;
    }
};

#endif // QUEUE_H
