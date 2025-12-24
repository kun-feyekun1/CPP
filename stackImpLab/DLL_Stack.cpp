
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* topPtr = nullptr;

void push(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = topPtr;

    if (topPtr != nullptr) {
        topPtr->next = newNode;
    }

    topPtr = newNode;
}

int pop() {
    if (topPtr == nullptr) {
        cout << "Stack Underflow!" << endl;
        return -1;
    }

    int value = topPtr->data;
    Node* temp = topPtr;

    topPtr = topPtr->prev;

    if (topPtr != nullptr) {
        topPtr->next = nullptr;
    }

    delete temp;
    return value;
}

int peek() {
    if (topPtr == nullptr) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return topPtr->data;
}

bool isEmpty() {
    return (topPtr == nullptr);
}

void display() {
    Node* curr = topPtr;
    cout << "Stack (top -> bottom): ";
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << endl;
}

int main() {
    push(10);
    push(20);
    push(30);

    display();

    cout << "Top = " << peek() << endl;

    cout << "Popped = " << pop() << endl;
    display();

    return 0;
}
