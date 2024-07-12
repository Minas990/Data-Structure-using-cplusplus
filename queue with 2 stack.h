#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include <iostream>

using namespace std;

class STACK
{
private:
    struct Node
    {
        int data;
        Node* next;
    };

    Node* top;
    int size;

public:
    STACK() : size(0), top(nullptr) {}
    ~STACK()
    {
        while (top)
        {
            Node* p = top->next;
            delete top;
            top = p;
        }
    }

    void push(int x)
    {
        Node* t = new Node();
        t->data = x;
        t->next = top;
        top = t;
        size++;
    }

    bool isEmpty() const { return size == 0; }

    void pop()
    {
        if (isEmpty())
            cout << "STACK IS EMPTY!" << endl;
        else
        {
            Node* p = top;
            top = top->next;
            delete p;
            --size;
        }
    }

    void display() const
    {
        Node* p = top;
        while (p)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    int peek(int pos) const
    {
        Node* p = top;
        for (int i = 0; p && i < pos - 1; i++)
            p = p->next;
        return p ? p->data : -1;
    }

    int stackTop() const
    {
        if (top)
            return top->data;
        return -1;
    }
};

class QueueWithTwoStacks
{
private:
    STACK first;
    STACK two;

public:
    void push(int x)
    {
        first.push(x);
    }

    void pop()
    {
        if (two.isEmpty() && first.isEmpty())
            return;

        if (!two.isEmpty())
            two.pop();
        else
        {
            while (!first.isEmpty())
            {
                two.push(first.stackTop());
                first.pop();
            }
            two.pop();
        }
    }
};

#endif // STACK_QUEUE_H
