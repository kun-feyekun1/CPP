#include <iostream>
#include "LinkedListStack.h"
using namespace std;

Node::Node(int val) : data(val), next(nullptr) {}

LinkedListStack::LinkedListStack() {
    top = nullptr;
}

LinkedListStack::~LinkedListStack() {
    while (top) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void LinkedListStack::push(int val) {
    Node* newNode = new Node(val);
    newNode->next = top;
    top = newNode;
}

int LinkedListStack::pop() {
    if (!top) {
        cout << "Stack Underflow!\n";
        return -1;
    }
    Node* temp = top;
    int val = temp->data;
    top = top->next;
    delete temp;
    return val;
}

int LinkedListStack::peek() {
    if (!top) {
        cout << "Stack is empty!\n";
        return -1;
    }
    return top->data;
}

bool LinkedListStack::search(int val) {
    Node* temp = top;
    while (temp) {
        if (temp->data == val) return true;
        temp = temp->next;
    }
    return false;
}

void LinkedListStack::display() {
    Node* temp = top;
    cout << "Stack: ";
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
