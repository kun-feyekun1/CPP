#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* front = NULL;

bool isEmpty() {
    return front == NULL;
}

void enqueue(int x) {
    Node* newNode = new Node;
    newNode->data = x;

    if (isEmpty()) {
        newNode->next = newNode;
        newNode->prev = newNode;
        front = newNode;
    } else {
        Node* rear = front->prev;
        newNode->next = front;
        newNode->prev = rear;
        rear->next = newNode;
        front->prev = newNode;
    }

    cout << x << " enqueued.\n";
}

int dequeue() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }

    int x = front->data;

    if (front->next == front) {
        delete front;
        front = NULL;
    } else {
        Node* rear = front->prev;
        Node* temp = front;
        front = front->next;
        rear->next = front;
        front->prev = rear;
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
