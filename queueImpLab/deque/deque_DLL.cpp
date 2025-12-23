#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* front = NULL;
Node* rear = NULL;

bool isEmpty() {
    return front == NULL;
}

void enqueueFront(int x) {
    Node* newNode = new Node;
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = front;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        front->prev = newNode;
        front = newNode;
    }

    cout << x << " enqueued at front.\n";
}

void enqueueRear(int x) {
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = rear;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << x << " enqueued at rear.\n";
}

int dequeueFront() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x = front->data;
    Node* temp = front;

    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
        front->prev = NULL;
    }

    delete temp;
    cout << x << " dequeued from front.\n";
    return x;
}

int dequeueRear() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x = rear->data;
    Node* temp = rear;

    if (front == rear) {
        front = rear = NULL;
    } else {
        rear = rear->prev;
        rear->next = NULL;
    }

    delete temp;
    cout << x << " dequeued from rear.\n";
    return x;
}

int peekFront() {
    if (isEmpty()) return -1;
    return front->data;
}

int peekRear() {
    if (isEmpty()) return -1;
    return rear->data;
}

void display() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return;
    }

    Node* temp = front;
    cout << "Deque: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    enqueueRear(10);
    enqueueRear(20);
    enqueueFront(5);
    display();

    dequeueFront();
    display();

    dequeueRear();
    display();

    cout << "Front element: " << peekFront() << endl;
    cout << "Rear element: " << peekRear() << endl;
}
