#include <iostream>
#include "LinkedListQueue.h"
using namespace std;

Node::Node(int val) : data(val), next(nullptr) {}

LinkedListQueue::LinkedListQueue() : front(nullptr), rear(nullptr) {}

LinkedListQueue::~LinkedListQueue() {
    while (front) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

void LinkedListQueue::enqueue(int val) {
    Node* newNode = new Node(val);
    if (!rear) front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

int LinkedListQueue::dequeue() {
    if (!front) {
        cout << "Queue Underflow!\n";
        return -1;
    }
    Node* temp = front;
    int val = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return val;
}

int LinkedListQueue::peek() {
    if (!front) {
        cout << "Queue is empty!\n";
        return -1;
    }
    return front->data;
}

void LinkedListQueue::display() {
    if (!front) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue: ";
    Node* temp = front;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
