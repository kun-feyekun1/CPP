#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* topPtr = nullptr;

bool isEmpty() {
    return topPtr == nullptr;
}

void push(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = topPtr;
    topPtr = newNode;

    cout << value << " pushed to stack.\n";
}

int pop() {
    if (isEmpty()) {
        cout << "Stack Underflow!\n";
        return -1;
    }

    Node* temp = topPtr;
    int value = temp->data;
    topPtr = topPtr->next;
    delete temp;

    cout << value << " popped from stack.\n";
    return value;
}

int peek() {
    if (isEmpty()) {
        cout << "Stack is empty!\n";
        return -1;
    }
    return topPtr->data;
}

void display() {
    if (isEmpty()) {
        cout << "Stack is empty!\n";
        return;
    }

    cout << "Stack elements: ";
    Node* temp = topPtr;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    int choice, value;

    while (true) {
        cout << "\n--- STACK MENU ---\n";
        cout << "1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            push(value);
            break;

        case 2:
            pop();
            break;

        case 3:
            cout << "Top element: " << peek() << endl;
            break;

        case 4:
            display();
            break;

        case 5:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}
