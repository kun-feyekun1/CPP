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

void enqueueFront(int x) {
    Node* newNode = new Node;
    newNode->data = x;

    if (isEmpty()) {
        front = rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = front;
        rear->next = newNode;
        front = newNode;
    }

    cout << x << " enqueued at front.\n";
}

void enqueueRear(int x) {
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

    cout << x << " enqueued at rear.\n";
}

int dequeueFront() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
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

    cout << x << " dequeued from front.\n";
    return x;
}

int dequeueRear() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x = rear->data;

    if (front == rear) {
        delete rear;
        front = rear = NULL;
    } else {
        Node* temp = front;
        while (temp->next != rear)
            temp = temp->next;

        temp->next = front;
        delete rear;
        rear = temp;
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
    return rear->data;
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
