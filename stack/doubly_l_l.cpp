
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;

void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;

    if (head != nullptr)
        head->prev = newNode;

    head = newNode;
}

void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
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

    Node* temp = head;
    for (int i = 1; temp != nullptr && i < pos - 1; i++)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != nullptr)
        temp->next->prev = newNode;

    temp->next = newNode;
}

void deleteAtBeginning() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    Node* temp = head;
    head = head->next;

    if (head != nullptr)
        head->prev = nullptr;

    delete temp;
}

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
    while (temp->next != nullptr)
        temp = temp->next;

    temp->prev->next = nullptr;
    delete temp;
}

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
    for (int i = 1; temp != nullptr && i < pos; i++)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Position out of range!\n";
        return;
    }

    if (temp->next != nullptr)
        temp->next->prev = temp->prev;

    if (temp->prev != nullptr)
        temp->prev->next = temp->next;

    delete temp;
}

Node* searchNode(int value) {    
    Node* temp = head;    
    while (temp != nullptr) {
        if (temp->data == value)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void updateValue(int oldValue, int newValue) {
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->data == oldValue) {
            temp->data = newValue;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "Value not found!\n";
    else
        cout << "All matching values updated.\n";
}

int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void reverseList() {
    Node* temp = nullptr;
    Node* curr = head;

    while (curr != nullptr) {
        temp = curr->prev;       // swap prev and next
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;       // move to next node (previous before swap)
    }

    if (temp != nullptr)
        head = temp->prev;  // update head to last node
}

void deleteEntireList() {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void displayForward() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

void displayBackward() {
    if (head == nullptr) {
        cout << "NULL\n";
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    }
    cout << "NULL\n";
}

int main() {

    insertAtBeginning(30);
    insertAtBeginning(20);
    insertAtBeginning(10);

    insertAtEnd(40);
    insertAtEnd(50);

    insertAtPosition(3, 25);

    cout << "List after insertions (forward): ";
    displayForward();

    deleteAtBeginning();
    deleteAtEnd();
    deleteAtPosition(3);

    cout << "List after deletions (forward): ";
    displayForward();

    cout << "List backward: ";
    displayBackward();

    cout << "Total nodes: " << countNodes() << endl;

    if (searchNode(25))
        cout << "25 found\n";
    else
        cout << "25 not found\n";

    updateValue(20, 200);
    cout << "List after update: ";
    displayForward();

    reverseList();
    cout << "Reversed list: ";
    displayForward();

    deleteEntireList();
    cout << "List after deleting all nodes: ";
    displayForward();

    return 0;
}
