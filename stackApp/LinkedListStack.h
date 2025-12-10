#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

struct Node {
    int data;
    Node* next;
    Node(int val);
};

class LinkedListStack {
private:
    Node* top;

public:
    LinkedListStack();
    ~LinkedListStack();
    void push(int val);
    int pop();
    int peek();
    bool search(int val);
    void display();
};

#endif
