#include <iostream>
#include "Deque.h"
using namespace std;

Deque::Deque(int size) {
    capacity = size;
    arr = new int[capacity];
    front = -1;
    rear = -1;
}

Deque::~Deque() {
    delete[] arr;
}

void Deque::insertFront(int val) {
    if ((front == 0 && rear == capacity - 1) || (front == rear + 1)) {
        cout << "Deque Overflow!\n";
        return;
    }
    if (front == -1) front = rear = 0;
    else if (front == 0) front = capacity - 1;
    else front--;
    arr[front] = val;
}

void Deque::insertRear(int val) {
    if ((front == 0 && rear == capacity - 1) || (front == rear + 1)) {
        cout << "Deque Overflow!\n";
        return;
    }
    if (rear == -1) front = rear = 0;
    else rear = (rear + 1) % capacity;
    arr[rear] = val;
}

int Deque::deleteFront() {
    if (front == -1) {
        cout << "Deque Underflow!\n";
        return -1;
    }
    int val = arr[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % capacity;
    return val;
}

int Deque::deleteRear() {
    if (rear == -1) {
        cout << "Deque Underflow!\n";
        return -1;
    }
    int val = arr[rear];
    if (front == rear) front = rear = -1;
    else if (rear == 0) rear = capacity - 1;
    else rear--;
    return val;
}

int Deque::peekFront() {
    if (front == -1) {
        cout << "Deque is empty!\n";
        return -1;
    }
    return arr[front];
}

int Deque::peekRear() {
    if (rear == -1) {
        cout << "Deque is empty!\n";
        return -1;
    }
    return arr[rear];
}

void Deque::display() {
    if (front == -1) {
        cout << "Deque is empty!\n";
        return;
    }
    cout << "Deque: ";
    int i = front;
    while (true) {
        cout << arr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % capacity;
    }
    cout << endl;
}
