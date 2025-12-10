#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

class ArrayStack {
private:
    int* stack;
    int top;
    int capacity;

public:
    ArrayStack(int size);
    ~ArrayStack();
    void push(int val);
    int pop();
    int peek();
    bool search(int val);
    void display();
};

#endif
