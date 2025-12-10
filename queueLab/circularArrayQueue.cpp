#include <iostream>
using namespace std;

#define SIZE 100

int arr[SIZE];
int front = -1;
int rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return (rear + 1) % SIZE == front;
}

void enqueue(int x) {
    if (isFull()) {
        cout << "Queue Full!\n";
        return;
    }
    if (isEmpty())
        front = 0;
    rear = (rear + 1) % SIZE;
    arr[rear] = x;
    cout << x << " enqueued.\n";
}

int dequeue() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }
    int x = arr[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;

    cout << x << " dequeued.\n";
    return x;
}

int peek() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return -1;
    }
    return arr[front];
}

void display() {
    if (isEmpty()) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue: ";
    int i = front;
    while (true) {
        cout << arr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
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
