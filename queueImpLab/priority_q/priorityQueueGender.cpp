#include <iostream>
using namespace std;

struct GNode {
    char gender; // 'M' or 'F'
    GNode* next;
};

// Global front pointer
GNode* front = NULL;

// Enqueue: Females have higher priority
void enqueue(char g) {
    GNode* n = new GNode();
    n->gender = g;
    n->next = NULL;

    if (front == NULL || g == 'F' || g == 'f') {
        n->next = front;
        front = n;
    } else {
        GNode* temp = front;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }

    cout << g << " enqueued.\n";
}

// Dequeue
char dequeue() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return '?';
    }

    char g = front->gender;
    GNode* temp = front;
    front = front->next;
    delete temp;

    cout << g << " dequeued.\n";
    return g;
}

// Peek
char peek() {
    if (front == NULL) return '?';
    return front->gender;
}

// Display
void display() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue: ";
    GNode* temp = front;
    while (temp) {
        cout << temp->gender << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    enqueue('M');
    enqueue('F');
    enqueue('M');
    enqueue('F');

    display();

    dequeue();
    display();

    cout << "Front element: " << peek() << endl;
}
