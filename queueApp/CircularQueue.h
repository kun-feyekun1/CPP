#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

class CircularQueue {
private:
    int* queue;
    int front;
    int rear;
    int capacity;

public:
    CircularQueue(int size);
    ~CircularQueue();
    void enqueue(int val);
    int dequeue();
    int peek();
    void display();
};

#endif
