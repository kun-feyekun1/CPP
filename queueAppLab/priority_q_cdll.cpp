#include <iostream>
using namespace std;

struct Task {
    string name;
    int priority;  // Lower number = higher priority
    Task* next;
    Task* prev;
};

Task* front = nullptr;

bool isEmpty() { return front == nullptr; }

void enqueue(string name, int priority) {
    Task* newNode = new Task{name, priority, nullptr, nullptr};

    if (isEmpty()) {
        newNode->next = newNode->prev = newNode;
        front = newNode;
        cout << "Task added: " << name << " (Priority " << priority << ")" << endl;
        return;
    }

    Task* temp = front;
    do {
        if (priority < temp->priority) break;
        temp = temp->next;
    } while (temp != front);

    Task* prevNode = temp->prev;

    newNode->next = temp;
    newNode->prev = prevNode;
    prevNode->next = newNode;
    temp->prev = newNode;

    if (temp == front && priority < front->priority) front = newNode;

    cout << "Task added: " << name << " (Priority " << priority << ")" << endl;
}

void executeTask() {
    if (isEmpty()) { cout << "No tasks\n"; return; }

    cout << "Executing: " << front->name << " (Priority " << front->priority << ")" << endl;

    if (front->next == front) { delete front; front = nullptr; return; }

    Task* temp = front;
    Task* prev = front->prev;
    Task* next = front->next;

    prev->next = next;
    next->prev = prev;
    front = next;
    delete temp;
}

void display() {
    if (isEmpty()) { cout << "No tasks\n"; return; }
    Task* temp = front;
    cout << "Tasks: ";
    do {
        cout << temp->name << "(" << temp->priority << ") ";
        temp = temp->next;
    } while (temp != front);
    cout << endl;
}

int main() {
    enqueue("Task1", 3);
    enqueue("Task2", 1);
    enqueue("Task3", 2);
    display();

    executeTask();
    display();
}
