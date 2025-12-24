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

    if (topPtr == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        topPtr = newNode;
    } else {
        Node* bottom = topPtr->next;

        newNode->next = bottom;
        newNode->prev = topPtr;

        topPtr->next = newNode;
        bottom->prev = newNode;

        topPtr = newNode;
    }
}

int pop() {
    if (topPtr == nullptr) {
        cout << "Stack Underflow!" << endl;
        return -1;
    }

    int value = topPtr->data;

    if (topPtr->next == topPtr) {
        delete topPtr;
        topPtr = nullptr;
    } else {
        Node* bottom = topPtr->next;
        Node* temp = topPtr;

        topPtr = topPtr->prev;
        topPtr->next = bottom;
        bottom->prev = topPtr;

        delete temp;
    }

    return value;
}

int peek() {
    if (topPtr == nullptr) {
        cout << "Stack Empty!" << endl;
        return -1;
    }
    return topPtr->data;
}

void display() {
    if (topPtr == nullptr) {
        cout << "Stack empty\n";
        return;
    }

    Node* temp = topPtr;
    cout << "Stack (top -> bottom): ";

    do {
        cout << temp->data << " ";
        temp = temp->prev;
    } while (temp != topPtr);

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
