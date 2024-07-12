#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <iostream>

class CircularQueue {
private:
    int size;
    int* Q;
    int front;
    int rear;

public:
    CircularQueue(int size =100) : size{ size }, front{ 0 }, rear{ 0 } {
        Q = new int[size]{};
    }

    ~CircularQueue() {
        delete[] Q;
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return (rear + 1) % size == front;
    }

    void enqueue(int x) {
        if (isFull()) {
            std::cout << "Queue is full" << std::endl;
            return;
        }
        rear = (rear + 1) % size;
        Q[rear] = x;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        front = (front + 1) % size;
    }

    int frontQueue() {
        if (isEmpty())
            return -1;
        int frontIdx = (front + 1) % size;
        return Q[frontIdx];
    }

    void display() {
        int i = (front + 1) % size;
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        std::cout << "Queue elements are: ";
        do {
            std::cout << Q[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % size;
        } while (i != (rear + 1) % size);
        std::cout << std::endl;
    }
};

#endif // CIRCULAR_QUEUE_H
