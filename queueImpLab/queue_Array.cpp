
#include <iostream>
using namespace std;

#define SIZE 100

int queueArray[SIZE];
int front = -1;
int rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return rear == SIZE - 1;
}

void enqueue(int x) {
    if (isFull()) {
        cout << "Queue Overflow!\n";
        return;
    }
    if (isEmpty())
        front = 0;

    queueArray[++rear] = x;
    cout << x << " enqueued.\n";
}

int dequeue() {
    if (isEmpty()) {
        cout << "Queue Underflow!\n";
        return -1;
    }

    int x = queueArray[front];

    if (front == rear) {

        front = rear = -1;
    } else {
        front++;
    }

    cout << x << " dequeued.\n";
    return x;
}

int peek() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }
    return queueArray[front];
}

void display() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue: ";
    for (int i = front; i <= rear; i++)
        cout << queueArray[i] << " ";
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
