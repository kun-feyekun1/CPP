
// Priority Queue using Singly Linked List – Hospital Emergency Room
#include <iostream>
using namespace std;

struct Patient {
    string name;
    int severity; // lower = higher severity
    Patient* next;
};

Patient* front = nullptr;

bool isEmpty() { return front == nullptr; }

void enqueue(string name, int severity) {
    Patient* newNode = new Patient{name, severity, nullptr};

    if (front == nullptr || severity < front->severity) {
        newNode->next = front;
        front = newNode;
        cout << "Patient added: " << name << " severity " << severity << endl;
        return;
    }

    Patient* temp = front;
    while (temp->next != nullptr && temp->next->severity <= severity)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Patient added: " << name << " severity " << severity << endl;
}

void dequeue() {
    if (isEmpty()) { cout << "No patients\n"; return; }
    Patient* temp = front;
    cout << "Treating patient: " << front->name << " severity " << front->severity << endl;
    front = front->next;
    delete temp;
}

void display() {
    if (isEmpty()) { cout << "No patients\n"; return; }
    Patient* temp = front;
    cout << "Waiting list: ";
    while (temp) {
        cout << temp->name << "(" << temp->severity << ") ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    enqueue("Ali", 2);
    enqueue("Sara", 1);
    enqueue("John", 3);
    display();

    dequeue();
    display();
}
