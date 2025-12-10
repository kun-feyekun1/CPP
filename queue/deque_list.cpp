#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* frontPtr = NULL;
Node* rearPtr  = NULL;

// ----------------------------
// Check if empty
bool isEmpty() {
    return (frontPtr == NULL);
}

// ----------------------------
// Insert at FRONT
void insertFront(int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = frontPtr;

    if (isEmpty()) {
        frontPtr = rearPtr = newNode;
    } else {
        frontPtr->prev = newNode;
        frontPtr = newNode;
    }
    cout << x << " inserted at FRONT\n";
}

// ----------------------------
// Insert at REAR
void insertRear(int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = rearPtr;

    if (isEmpty()) {
        frontPtr = rearPtr = newNode;
    } else {
        rearPtr->next = newNode;
        rearPtr = newNode;
    }
    cout << x << " inserted at REAR\n";
}

// ----------------------------
// Delete from FRONT
void deleteFront() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }

    Node* temp = frontPtr;
    cout << temp->data << " removed from FRONT\n";

    frontPtr = frontPtr->next;

    if (frontPtr == NULL) { 
        rearPtr = NULL; 
    } else {
        frontPtr->prev = NULL;
    }

    delete temp;
}

// ----------------------------
// Delete from REAR
void deleteRear() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }

    Node* temp = rearPtr;
    cout << temp->data << " removed from REAR\n";

    rearPtr = rearPtr->prev;

    if (rearPtr == NULL) {
        frontPtr = NULL;
    } else {
        rearPtr->next = NULL;
    }

    delete temp;
}

// ----------------------------
// Get FRONT element
void getFront() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }
    cout << "Front element = " << frontPtr->data << endl;
}

// Get REAR element
void getRear() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }
    cout << "Rear element = " << rearPtr->data << endl;
}

// ----------------------------
// Display elements
void display() {
    if (isEmpty()) {
        cout << "Deque is EMPTY\n";
        return;
    }

    cout << "Deque: ";
    Node* temp = frontPtr;

    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// ----------------------------
int main() {
    insertRear(10);
    insertRear(20);
    insertFront(5);
    insertFront(2);

    display();

    deleteFront();
    deleteRear();

    display();

    getFront();
    getRear();

    return 0;
}
