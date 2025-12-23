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
    newNode->next = front;
    front = newNode;

    if (rear == NULL)
        rear = newNode;

    cout << x << " enqueued at front.\n";
}

void enqueueRear(int x) {
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;

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

    Node* temp = front;
    int x = temp->data;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;
    cout << x << " dequeued from front.\n";
    return x;
}

int dequeueRear() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x;

    if (front == rear) {
        x = front->data;
        delete front;
        front = rear = NULL;
    } else {
        Node* temp = front;
        while (temp->next != rear)
            temp = temp->next;

        x = rear->data;
        delete rear;
        rear = temp;
        rear->next = NULL;
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
