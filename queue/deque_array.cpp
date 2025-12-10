#include <iostream>
using namespace std;

const int SIZE = 5;   // change as you want
int arr[SIZE];
int front = -1;
int rear  = -1;

// ----------------------------
// Check if empty
bool isEmpty() {
    return (front == -1);
}

// Check if full
bool isFull() {
    return ((front == 0 && rear == SIZE - 1) || (front == rear + 1));
}

// ----------------------------
// Insert at FRONT
void insertFront(int x) {
    if (isFull()) {
        cout << "Deque is FULL\n";
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    }
    else if (front == 0) {
        front = SIZE - 1;
    }
    else {
        front--;
    }

    arr[front] = x;
    cout << x << " inserted at FRONT\n";
}

// Insert at REAR
void insertRear(int x) {
    if (isFull()) {
        cout << "Deque is FULL\n";
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    }
    else if (rear == SIZE - 1) {
        rear = 0;
    }
    else {
        rear++;
    }

    arr[rear] = x;
    cout << x << " inserted at REAR\n";
}

// ----------------------------
// Delete from FRONT
void deleteFront() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }

    cout << arr[front] << " removed from FRONT\n";

    if (front == rear) {
        front = rear = -1;   // deque is now empty
    }
    else if (front == SIZE - 1) {
        front = 0;
    }
    else {
        front++;
    }
}

// Delete from REAR
void deleteRear() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }

    cout << arr[rear] << " removed from REAR\n";

    if (front == rear) {
        front = rear = -1;
    }
    else if (rear == 0) {
        rear = SIZE - 1;
    }
    else {
        rear--;
    }
}

// ----------------------------
// Get FRONT element
void getFront() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }
    cout << "Front element = " << arr[front] << endl;
}

// Get REAR element
void getRear() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }
    cout << "Rear element = " << arr[rear] << endl;
}

// ----------------------------
// Display elements
void display() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
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

// ----------------------------
int main() {
    insertRear(10);
    insertRear(20);
    insertFront(5);
    insertFront(2);
    insertRear(30);

    display();

    deleteFront();
    deleteRear();

    display();

    getFront();
    getRear();

    return 0;
}
