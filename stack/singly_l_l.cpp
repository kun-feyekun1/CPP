#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;
    
void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    // If list is empty
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    temp->next = newNode;
}

void insertAtPosition(int pos, int value) {
    if (pos < 1) {
        cout << "Invalid position!\n";
        return;
    }

    if (pos == 1) {
        insertAtBeginning(value);
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;

    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtBeginning() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
}

// --------------------------
// Delete from End
// --------------------------
void deleteAtEnd() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* temp = head;
    while (temp->next->next != nullptr)
        temp = temp->next;

    delete temp->next;
    temp->next = nullptr;
}

// --------------------------
// Delete at Position
// --------------------------
void deleteAtPosition(int pos) {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    if (pos == 1) {
        deleteAtBeginning();
        return;
    }

    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    delete del;
}

// --------------------------
// Search for a value
// --------------------------
bool searchNode(int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// --------------------------
// Update a node's value
// --------------------------
void updateValue(int oldValue, int newValue) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == oldValue) {
            temp->data = newValue;
            return;
        }
        temp = temp->next;
    }
    cout << "Value not found!\n";
}

// --------------------------
// Count Nodes
// --------------------------
int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// --------------------------
// Reverse the List
// --------------------------
void reverseList() {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;   // store next
        curr->next = prev;   // reverse link
        prev = curr;         // move prev
        curr = next;         // move curr
    }

    head = prev;
}

// --------------------------
// Delete Entire List
// --------------------------
void deleteEntireList() {
    while (head != nullptr)
        deleteAtBeginning();
}

// --------------------------
// Display List
// --------------------------
void display() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// --------------------------
// MAIN PROGRAM
// --------------------------
int main() {
    Node* head = nullptr;

    insertAtBeginning(30);
    insertAtBeginning(20);
    insertAtBeginning(10);

    insertAtEnd(40);
    insertAtEnd(50);

    insertAtPosition(3, 25);

    cout << "List after insertions: ";
    display();

    deleteAtBeginning();
    deleteAtEnd();
    deleteAtPosition(3);

    cout << "List after deletions: ";
    display();

    cout << "Total nodes: " << countNodes() << "\n";

    if (searchNode(25))
        cout << "25 found\n";
    else
        cout << "25 not found\n";

    updateValue(20, 200);
    cout << "List after update: ";
    display();

    reverseList();
    cout << "Reversed list: ";
    display();

    deleteEntireList();
    cout << "List after deleting all nodes: ";
    display();

    return 0;
}
