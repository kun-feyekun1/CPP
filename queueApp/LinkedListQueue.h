#ifndef LINKEDLISTQUEUE_H
#define LINKEDLISTQUEUE_H

struct Node {
    int data;
    Node* next;
    Node(int val);
};

class LinkedListQueue {
private:
    Node* front;
    Node* rear;

public:
    LinkedListQueue();
    ~LinkedListQueue();
    void enqueue(int val);
    int dequeue();
    int peek();
    void display();
};

#endif
