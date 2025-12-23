#include <iostream>
using namespace std;

struct Task {
    string name;
    Task* next;
    Task* prev;
};

Task* front = nullptr;

bool isEmpty() { return front == nullptr; }

void addTask(string name) {
    Task* t = new Task{name, nullptr, nullptr};
    if (isEmpty()) {
        t->next = t->prev = t;
        front = t;
        return;
    }
    Task* rear = front->prev;
    t->next = front;
    t->prev = rear;
    rear->next = t;
    front->prev = t;
}

void executeTask() {
    if (isEmpty()) { cout << "No tasks\n"; return; }
    cout << "Executing: " << front->name << endl;

    if (front->next == front) { delete front; front = nullptr; return; }

    Task* rear = front->prev;
    Task* temp = front;
    front = front->next;
    rear->next = front;
    front->prev = rear;
    delete temp;
}

void display() {
    if (isEmpty()) { cout << "No tasks\n"; return; }
    Task* temp = front;
    cout << "Tasks: ";
    do {
        cout << temp->name << " ";
        temp = temp->next;
    } while (temp != front);
    cout << endl;
}

int main() {
    addTask("Task1");
    addTask("Task2");
    addTask("Task3");
    display();

    executeTask();
    display();
}
