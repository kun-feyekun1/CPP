#include <iostream>
using namespace std;

struct GNode {
    char gender; // 'M' or 'F'
    GNode* next;
};

GNode* front = NULL;
GNode* fend = NULL;

void enqueue(char g) {
    GNode* n = new GNode();
    n->gender = g;
    n->next = NULL;

    if (front == NULL ) {
        n->next = front;
        front = n;
   
    } else {
        GNode* fend = NULL;
        while ( fend -> next -> gender != ('f' || 'F') && fend->next != NULL )
            fend = fend->next;
            
            n->next=fend->next;
            fend->next = n;

    }

    cout << g << " enqueued.\n";
}

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

char peek() {
    if (front == NULL) return '?';
    return front->gender;
}

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
