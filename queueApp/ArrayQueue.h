#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

class ArrayQueue {
private:
    int* queue;
    int front;
    int rear;
    int capacity;

public:
    ArrayQueue(int size);
    ~ArrayQueue();
    void enqueue(int val);
    int dequeue();
    int peek();
    void display();
};

#endif
