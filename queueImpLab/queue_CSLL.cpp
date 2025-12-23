#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* front = NULL;
Node* rear = NULL;

bool isEmpty() {
    return front == NULL;
}

void enqueue(int x) {
    Node* newNode = new Node;
    newNode->data = x;

    if (isEmpty()) {
        front = rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = front;
        rear->next = newNode;
        rear = newNode;
    }

    cout << x << " enqueued.\n";
}

int dequeue() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }

    int x = front->data;

    if (front == rear) {
        delete front;
        front = rear = NULL;
    } else {
        Node* temp = front;
        front = front->next;
        rear->next = front;
        delete temp;
    }

    cout << x << " dequeued.\n";
    return x;
}

int peek() {
    if (isEmpty()) return -1;
    return front->data;
}

void display() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return;
    }

    Node* temp = front;
    cout << "Queue: ";
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != front);
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
