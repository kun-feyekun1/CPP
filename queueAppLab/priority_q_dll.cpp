#include <iostream>
using namespace std;

struct Patient {
    string name;
    int severity;  // Lower number = higher priority
    Patient* next;
    Patient* prev;
};

Patient* front = nullptr;

bool isEmpty() { return front == nullptr; }

void enqueue(string name, int severity) {
    Patient* newNode = new Patient{name, severity, nullptr, nullptr};

    if (isEmpty() || severity < front->severity) {
        newNode->next = front;
        if (front) front->prev = newNode;
        front = newNode;
        cout << "Patient added: " << name << " (Severity " << severity << ")" << endl;
        return;
    }

    Patient* temp = front;
    while (temp->next && temp->next->severity <= severity)
        temp = temp->next;

    newNode->next = temp->next;
    if (temp->next) temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;

    cout << "Patient added: " << name << " (Severity " << severity << ")" << endl;
}

void dequeue() {
    if (isEmpty()) { cout << "No patients\n"; return; }
    cout << "Treating: " << front->name << " (Severity " << front->severity << ")" << endl;
    Patient* temp = front;
    front = front->next;
    if (front) front->prev = nullptr;
    delete temp;
}

void display() {
    if (isEmpty()) { cout << "No patients\n"; return; }
    Patient* temp = front;
    cout << "Waiting List: ";
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
