
#include <iostream>
using namespace std;

struct AgeNode {
    int age;
    AgeNode* next;
};

// Global front pointer
AgeNode* front = NULL;

// Enqueue: Higher age has higher priority
void enqueue(int age) {
    AgeNode* n = new AgeNode();
    n->age = age;
    n->next = NULL;

    if (front == NULL || age > front->age) {
        n->next = front;
        front = n;
    } else {
        AgeNode* temp = front;
        while (temp->next != NULL && temp->next->age >= age)
            temp = temp->next;

        n->next = temp->next;
        temp->next = n;
    }

    cout << age << " enqueued.\n";
}

// Dequeue
int dequeue() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return -1;
    }

    int age = front->age;
    AgeNode* temp = front;
    front = front->next;
    delete temp;

    cout << age << " dequeued.\n";
    return age;
}

// Peek
int peek() {
    if (front == NULL) return -1;
    return front->age;
}

// Display
void display() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue (Older first): ";
    AgeNode* temp = front;
    while (temp) {
        cout << temp->age << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    enqueue(25);
    enqueue(40);
    enqueue(30);
    enqueue(50);

    display();

    dequeue();
    display();

    cout << "Front element: " << peek() << endl;
}
