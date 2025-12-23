
// Priority Queue using Array – Task Scheduling Simulation
#include <iostream>
using namespace std;

#define SIZE 10
struct Task {
    string name;
    int priority; // lower number = higher priority
};

Task queue[SIZE];
int front = -1, rear = -1;

bool isEmpty() { return front == -1; }
bool isFull() { return (rear + 1) % SIZE == front; }

void enqueue(string name, int prio) {
    if (isFull()) { cout << "Queue full!\n"; return; }

    Task t{name, prio};
    if (isEmpty()) front = rear = 0;
    else rear = (rear + 1) % SIZE;
    queue[rear] = t;
    cout << "Task added: " << name << " with priority " << prio << endl;
}

void dequeue() {
    if (isEmpty()) { cout << "Queue empty!\n"; return; }

    int idx = front;
    for (int i = front; i != (rear + 1) % SIZE; i = (i + 1) % SIZE)
        if (queue[i].priority < queue[idx].priority) idx = i;

    cout << "Executing task: " << queue[idx].name << " with priority " << queue[idx].priority << endl;

    // Shift elements
    int i = idx;
    while (i != rear) {
        int next = (i + 1) % SIZE;
        queue[i] = queue[next];
        i = next;
    }
    if (front == rear) front = rear = -1;
    else rear = (rear - 1 + SIZE) % SIZE;
}

void display() {
    if (isEmpty()) { cout << "Queue empty\n"; return; }
    int i = front;
    cout << "Tasks in queue: ";
    while (true) {
        cout << queue[i].name << "(" << queue[i].priority << ") ";
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    cout << endl;
}

int main() {
    enqueue("Task1", 3);
    enqueue("Task2", 1);
    enqueue("Task3", 2);
    display();

    dequeue();
    display();
}
