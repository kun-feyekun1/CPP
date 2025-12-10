#include <iostream>
#include "CircularQueue.h"
using namespace std;

CircularQueue::CircularQueue(int size) {
    capacity = size;
    queue = new int[capacity];
    front = -1;
    rear = -1;
}

CircularQueue::~CircularQueue() {
    delete[] queue;
}

void CircularQueue::enqueue(int val) {
    if ((front == 0 && rear == capacity - 1) || (rear + 1) % capacity == front) {
        cout << "Queue Overflow!\n";
        return;
    }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % capacity;
    queue[rear] = val;
}

int CircularQueue::dequeue() {
    if (front == -1) {
        cout << "Queue Underflow!\n";
        return -1;
    }
    int val = queue[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % capacity;
    return val;
}

int CircularQueue::peek() {
    if (front == -1) {
        cout << "Queue is empty!\n";
        return -1;
    }
    return queue[front];
}

void CircularQueue::display() {
    if (front == -1) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue: ";
    int i = front;
    while (true) {
        cout << queue[i] << " ";
        if (i == rear) break;
        i = (i + 1) % capacity;
    }
    cout << endl;
}
