#include <iostream>
using namespace std;

struct Node {
    char gender;   // 'M' or 'F'
    int age;
    Node* next;
};

Node* front = NULL;

/* Enqueue with priority:
   1. Female before Male
   2. Older age first within same gender
*/
void enqueue(char gender, int age) {
    Node* n = new Node();
    n->gender = gender;
    n->age = age;
    n->next = NULL;

    // Case 1: Empty queue
    if (front == NULL) {
        front = n;
    }
    // Case 2: Higher priority than front
    else if (
        (gender == 'F' && front->gender == 'M') ||
        (gender == front->gender && age > front->age)
    ) {
        n->next = front;
        front = n;
    }
    // Case 3: Find correct position
    else {
        Node* temp = front;

        while (
            temp->next != NULL &&
            (
                // Same gender → age priority
                (temp->next->gender == gender && temp->next->age >= age) ||
                // Female already ahead of male
                (temp->next->gender == 'F' && gender == 'M')
            )
        ) {
            temp = temp->next;
        }

        n->next = temp->next;
        temp->next = n;
    }

    cout << gender << " (" << age << ") enqueued.\n";
}

void dequeue() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return;
    }

    Node* temp = front;
    cout << temp->gender << " (" << temp->age << ") dequeued.\n";
    front = front->next;
    delete temp;
}

void peek() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return;
    }
    cout << "Front: " << front->gender << " (" << front->age << ")\n";
}

void display() {
    if (front == NULL) {
        cout << "Queue Empty!\n";
        return;
    }

    cout << "Queue: ";
    Node* temp = front;
    while (temp) {
        cout << temp->gender << "(" << temp->age << ") -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    enqueue('M', 30);
    enqueue('F', 25);
    enqueue('M', 50);
    enqueue('F', 40);
    enqueue('F', 20);

    display();

    dequeue();
    display();

    peek();

    return 0;
}
