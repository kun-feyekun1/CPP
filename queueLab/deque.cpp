#include <iostream>
using namespace std;

#define SIZE 100

int arr[SIZE];
int front = -1;
int rear = -1;

bool isFull() {
    return (rear + 1) % SIZE == front;
}

bool isEmpty() {
    return front == -1;
}

// Enqueue at front
void enqueueFront(int x) {
    if (isFull()) {
        cout << "Deque Full!\n";
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else {
        front = (front - 1 + SIZE) % SIZE;
    }

    arr[front] = x;
    cout << x << " enqueued at front.\n";
}

// Enqueue at rear
void enqueueRear(int x) {
    if (isFull()) {
        cout << "Deque Full!\n";
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % SIZE;

    arr[rear] = x;
    cout << x << " enqueued at rear.\n";
}

// Dequeue from front
int dequeueFront() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x = arr[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;

    cout << x << " dequeued from front.\n";
    return x;
}

// Dequeue from rear
int dequeueRear() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return -1;
    }

    int x = arr[rear];
    if (front == rear)
        front = rear = -1;
    else
        rear = (rear - 1 + SIZE) % SIZE;

    cout << x << " dequeued from rear.\n";
    return x;
}

// Peek front
int peekFront() {
    if (isEmpty()) return -1;
    return arr[front];
}

// Peek rear
int peekRear() {
    if (isEmpty()) return -1;
    return arr[rear];
}

// Display
void display() {
    if (isEmpty()) {
        cout << "Deque Empty!\n";
        return;
    }

    cout << "Deque: ";
    int i = front;
    while (true) {
        cout << arr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % SIZE;
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
