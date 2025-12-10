#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Front and Rear pointers
Node* front = nullptr;
Node* rear = nullptr;

// -------------------------------------
// ENQUEUE (Insert at Rear)
// -------------------------------------
void enqueue(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
}

// -------------------------------------
// DEQUEUE (Delete from Front)
// -------------------------------------
void dequeue() {
    if (front == nullptr) {
        cout << "Queue Underflow\n";
        return;
    }

    cout << "Dequeued: " << front->data << endl;
    Node* temp = front;
    front = front->next;

    if (front == nullptr)
        rear = nullptr;

    delete temp;
}

// -------------------------------------
// PEEK front element
// -------------------------------------
int peekFront() {
    if (front == nullptr) {
        cout << "Queue is empty\n";
        return -1;
    }
    return front->data;
}

// PEEK rear element
int peekRear() {
    if (rear == nullptr) {
        cout << "Queue is empty\n";
        return -1;
    }
    return rear->data;
}

// -------------------------------------
// Check if Queue is Empty
// -------------------------------------
bool isEmpty() {
    return front == nullptr;
}

// -------------------------------------
// Count number of elements
// -------------------------------------
int size() {
    int count = 0;
    Node* temp = front;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// -------------------------------------
// Search a value in queue
// -------------------------------------
bool search(int value) {
    Node* temp = front;
    while (temp != nullptr) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// -------------------------------------
// Update first occurrence of a value
// -------------------------------------
void updateValue(int oldVal, int newVal) {
    Node* temp = front;
    while (temp != nullptr) {
        if (temp->data == oldVal) {
            temp->data = newVal;
            return;
        }
        temp = temp->next;
    }
    cout << "Value not found!\n";
}

// -------------------------------------
// Insert at Position (1-based)
// -------------------------------------
void insertAtPosition(int pos, int value) {
    if (pos < 1) {
        cout << "Invalid position!\n";
        return;
    }

    if (pos == 1) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = front;
        front = newNode;

        if (rear == nullptr)
            rear = newNode;

        return;
    }

    Node* temp = front;
    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = temp->next;
    temp->next = newNode;

    if (newNode->next == nullptr)
        rear = newNode;
}

// -------------------------------------
// Delete at Position (1-based)
// -------------------------------------
void deleteAtPosition(int pos) {
    if (front == nullptr) {
        cout << "Queue is empty!\n";
        return;
    }

    if (pos == 1) {
        dequeue();
        return;
    }

    Node* temp = front;
    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;

    if (del == rear)
        rear = temp;

    delete del;
}

// -------------------------------------
// Replace value at position
// -------------------------------------
void replaceValueAtPosition(int pos, int newValue) {
    Node* temp = front;
    for (int i = 1; temp != nullptr && i < pos; i++)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    temp->data = newValue;
}

// -------------------------------------
// Reverse Queue
// -------------------------------------
void reverseQueue() {
    Node* prev = nullptr;
    Node* curr = front;
    Node* next = nullptr;

    rear = front;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    front = prev;
}

// -------------------------------------
// Delete entire queue
// -------------------------------------
void deleteEntireQueue() {
    while (front != nullptr)
        dequeue();
}

// -------------------------------------
// Display Queue
// -------------------------------------
void display() {
    Node* temp = front;
    cout << "Queue (front → rear): ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// -------------------------------------
// Display queue in reverse (without reversing it)
// -------------------------------------
void displayReverseHelper(Node* node) {
    if (node == nullptr) return;
    displayReverseHelper(node->next);
    cout << node->data << " ";
}

void displayReverse() {
    cout << "Queue (rear → front): ";
    displayReverseHelper(front);
    cout << endl;
}

// -------------------------------------
// MAIN FUNCTION
// -------------------------------------
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    cout << "Front: " << peekFront() << endl;
    cout << "Rear: " << peekRear() << endl;

    insertAtPosition(2, 15);
    display();

    deleteAtPosition(3);
    display();

    updateValue(20, 200);
    display();

    reverseQueue();
    display();

    cout << "Reverse display (without modifying queue): ";
    displayReverse();

    cout << "Size: " << size() << endl;

    deleteEntireQueue();
    display();

    return 0;
}
