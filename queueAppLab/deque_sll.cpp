#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;

void insertRear(int x) {
    Node* n = new Node{x, nullptr};
    if (!rear) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}

void removeFront() {
    if (!front) return;
    Node* t = front;
    front = front->next;
    if (!front) rear = nullptr;
    delete t;
}

void display() {
    Node* t = front;
    cout << "Window: ";
    while (t) {
        cout << t->data << " ";
        t = t->next;
    }
    cout << endl;
}

int main() {
    insertRear(10);
    insertRear(20);
    insertRear(15);
    display();

    removeFront();
    display();
}
