#include <iostream>
using namespace std;

struct Node {
    string name;
    Node* next;
    Node* prev;
};

Node* front = nullptr;
Node* rear = nullptr;

bool isEmpty() { return front == nullptr; }

void enqueue(string name) {
    Node* n = new Node{name, nullptr, rear};
    if (isEmpty()) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
    cout << "Customer added: " << name << endl;
}

void dequeue() {
    if (isEmpty()) { cout << "No customers\n"; return; }
    cout << "Serving: " << front->name << endl;
    Node* temp = front;
    front = front->next;
    if (front) front->prev = nullptr;
    else rear = nullptr;
    delete temp;
}

void display() {
    Node* temp = front;
    cout << "Queue: ";
    while (temp) {
        cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    enqueue("Ali");
    enqueue("Sara");
    enqueue("John");
    display();

    dequeue();
    display();
}
