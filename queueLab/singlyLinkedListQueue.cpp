#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Global front and rear pointers
Node* front = NULL;
Node* rear = NULL;

bool isEmpty() {
    return front == NULL;
}

void enqueue(int x) {
    Node* n = new Node();
    n->data = x;
    n->next = NULL;

    if (isEmpty()) {
        front = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    cout << x << " enqueued.\n";
}

int dequeue() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }
    Node* temp = front;
    int x = temp->data;

    front = front->next;
    if (front == NULL) rear = NULL;

    delete temp;
    cout << x << " dequeued.\n";
    return x;
}

int peek() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }
    return front->data;
}

void display() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue: ";
    Node* curr = front;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();
    display();

    cout << "Front element: " << peek() << endl;
}
