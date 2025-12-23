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

void enqueueFront(int x) {
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
        front = newNode;
    }

    cout << x << " enqueued at front.\n";
}

void enqueueRear(int x) {
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

    cout << x << " enqueued at rear.\n";
}

int dequeueFront() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
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

    cout << x << " dequeued from front.\n";
    return x;
}

int dequeueRear() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    Node* rear = front->prev;
    int x = rear->data;

    if (rear->next == rear) {
        delete rear;
        front = NULL;
    } else {
        Node* newRear = rear->prev;
        newRear->next = front;
        front->prev = newRear;
        delete rear;
    }

    cout << x << " dequeued from rear.\n";
    return x;
}

int peekFront() {
    if (isEmpty()) return -1;
    return front->data;
}

int peekRear() {
    if (isEmpty()) return -1;
    return front->prev->data;
}

void display() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return;
    }

    Node* temp = front;
    cout << "Deque: ";
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != front);
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

    cout << "Front: " << peekFront() << endl;
    cout << "Rear: " << peekRear() << endl;
}
