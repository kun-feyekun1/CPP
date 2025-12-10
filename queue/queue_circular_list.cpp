#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* front = nullptr;
Node* rear = nullptr;

// -------------------------------------
// ENQUEUE (Insert at Rear)
// -------------------------------------
void enqueue(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (front == nullptr) {  
        front = rear = newNode;
        newNode->next = front;   // Circular link
        return;
    }

    rear->next = newNode;
    rear = newNode;
    rear->next = front;          // Maintain circularity
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

    if (front == rear) {   // Only one node
        delete front;
        front = rear = nullptr;
        return;
    }

    Node* temp = front;
    front = front->next;
    rear->next = front; // Maintain circular link
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
    if (front == nullptr) return 0;

    int count = 0;
    Node* temp = front;
    do {
        count++;
        temp = temp->next;
    } while (temp != front);

    return count;
}

// -------------------------------------
// Search a value in queue
// -------------------------------------
bool search(int value) {
    if (front == nullptr) return false;

    Node* temp = front;
    do {
        if (temp->data == value)
            return true;
        temp = temp->next;
    } while (temp != front);

    return false;
}

// -------------------------------------
// Update first occurrence of a value
// -------------------------------------
void updateValue(int oldVal, int newVal) {
    if (front == nullptr) return;

    Node* temp = front;
    do {
        if (temp->data == oldVal) {
            temp->data = newVal;
            return;
        }
        temp = temp->next;
    } while (temp != front);

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

    Node* newNode = new Node();
    newNode->data = value;

    if (pos == 1) {
        if (front == nullptr) {
            front = rear = newNode;
            newNode->next = front;
            return;
        }

        newNode->next = front;
        front = newNode;
        rear->next = front;
        return;
    }

    Node* temp = front;
    for (int i = 1; i < pos - 1 && temp->next != front; i++)
        temp = temp->next;

    if (temp->next == front && pos > size() + 1) {
        cout << "Position out of range!\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    if (temp == rear) rear = newNode;
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
    for (int i = 1; i < pos - 1 && temp->next != front; i++)
        temp = temp->next;

    if (temp->next == front) {
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
    if (front == nullptr) return;

    Node* temp = front;
    for (int i = 1; i < pos && temp->next != front; i++)
        temp = temp->next;

    if (temp == front && pos != 1) {
        cout << "Position out of range!\n";
        return;
    }

    temp->data = newValue;
}

// -------------------------------------
// Reverse Queue
// -------------------------------------
void reverseQueue() {
    if (front == nullptr || front == rear) return;

    Node* prev = rear;
    Node* curr = front;
    Node* next = nullptr;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != front);

    rear = front;
    front = prev;
}

// -------------------------------------
// Delete entire queue
// -------------------------------------
void deleteEntireQueue() {
    while (!isEmpty())
        dequeue();
}

// -------------------------------------
// Display Queue (front → rear)
// -------------------------------------
void display() {
    if (front == nullptr) {
        cout << "Queue is empty\n";
        return;
    }

    Node* temp = front;
    cout << "Circular Queue: ";
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != front);

    cout << endl;
}

// -------------------------------------
// Display reverse (rear → front)
// -------------------------------------
void displayReverseHelper(Node* node, Node* start) {
    if (node->next != start)
        displayReverseHelper(node->next, start);
    cout << node->data << " ";
}

void displayReverse() {
    if (front == nullptr) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "Reverse Queue: ";
    displayReverseHelper(front, front);
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

    displayReverse();

    cout << "Size: " << size() << endl;

    deleteEntireQueue();
    display();

    return 0;
}
