#include <iostream>
#include "ArrayQueue.h"
using namespace std;

ArrayQueue::ArrayQueue(int size) {
    capacity = size;
    queue = new int[capacity];
    front = -1;
    rear = -1;
}

ArrayQueue::~ArrayQueue() {
    delete[] queue;
}

void ArrayQueue::enqueue(int val) {
    if (rear == capacity - 1) {
        cout << "Queue Overflow!\n";
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = val;
}

int ArrayQueue::dequeue() {
    if (front == -1 || front > rear) {
        cout << "Queue Underflow!\n";
        return -1;
    }
    return queue[front++];
}

int ArrayQueue::peek() {
    if (front == -1 || front > rear) {
        cout << "Queue is empty!\n";
        return -1;
    }
    return queue[front];
}

void ArrayQueue::display() {
    if (front == -1 || front > rear) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue: ";
    for (int i = front; i <= rear; i++) {
        cout << queue[i] << " ";
    }
    cout << endl;
}
