#include <iostream>
#include "ArrayStack.h"
using namespace std;

ArrayStack::ArrayStack(int size) {
    capacity = size;
    stack = new int[capacity];
    top = -1;
}

ArrayStack::~ArrayStack() {
    delete[] stack;
}

void ArrayStack::push(int val) {
    if (top == capacity - 1) {
        cout << "Stack Overflow!\n";
        return;
    }
    stack[++top] = val;
}

int ArrayStack::pop() {
    if (top == -1) {
        cout << "Stack Underflow!\n";
        return -1;
    }
    return stack[top--];
}

int ArrayStack::peek() {
    if (top == -1) {
        cout << "Stack is empty!\n";
        return -1;
    }
    return stack[top];
}

bool ArrayStack::search(int val) {
    for (int i = 0; i <= top; i++) {
        if (stack[i] == val) return true;
    }
    return false;
}

void ArrayStack::display() {
    cout << "Stack: ";
    for (int i = top; i >= 0; i--) {
        cout << stack[i] << " ";
    }
    cout << endl;
}
