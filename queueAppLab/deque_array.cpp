#include <iostream>
using namespace std;

#define SIZE 5
string actions[SIZE];
int front = -1, rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return (rear + 1) % SIZE == front;
}

void addAction(string action) {
    if (isFull()) {
        front = (front + 1) % SIZE;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % SIZE;

    actions[rear] = action;
}

void undo() {
    if (isEmpty()) {
        cout << "Nothing to undo\n";
        return;
    }

    cout << "Undo: " << actions[rear] << endl;

    if (front == rear)
        front = rear = -1;
    else
        rear = (rear - 1 + SIZE) % SIZE;
}

void display() {
    if (isEmpty()) return;

    int i = front;
    cout << "History: ";
    while (true) {
        cout << actions[i] << " ";
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    cout << endl;
}

int main() {
    addAction("Type A");
    addAction("Type B");
    addAction("Delete");
    display();

    undo();
    display();
}
