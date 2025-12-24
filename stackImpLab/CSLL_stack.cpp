#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* topPtr = nullptr;

void push(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (topPtr == nullptr) {
        newNode->next = newNode;   // circular self link
        topPtr = newNode;
    } else {
        Node* temp = topPtr;
        while (temp->next != topPtr)
            temp = temp->next;

        temp->next = newNode;
        newNode->next = topPtr;
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
        Node* temp = topPtr;
        Node* last = topPtr;

        while (last->next != topPtr)
            last = last->next;

        topPtr = topPtr->next;
        last->next = topPtr;
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
        temp = temp->next;
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
