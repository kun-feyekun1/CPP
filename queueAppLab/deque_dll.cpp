#include <iostream>
using namespace std;

struct Node {
    string action;
    Node* prev;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;

bool isEmpty() { return front == nullptr; }

void addAction(string act) { // insert at rear
    Node* n = new Node{act, rear, nullptr};
    if (isEmpty()) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
    cout << "Action added: " << act << endl;
}

void undo() { // remove from rear
    if (isEmpty()) { cout << "Nothing to undo\n"; return; }
    cout << "Undo: " << rear->action << endl;
    Node* temp = rear;
    rear = rear->prev;
    if (rear) rear->next = nullptr;
    else front = nullptr;
    delete temp;
}

void redo() { // remove from front
    if (isEmpty()) { cout << "Nothing to redo\n"; return; }
    cout << "Redo: " << front->action << endl;
    Node* temp = front;
    front = front->next;
    if (front) front->prev = nullptr;
    else rear = nullptr;
    delete temp;
}

void display() {
    Node* temp = front;
    cout << "History: ";
    while (temp) {
        cout << temp->action << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    addAction("Type A");
    addAction("Type B");
    addAction("Delete");
    display();

    undo();
    display();

    redo();
    display();
}
