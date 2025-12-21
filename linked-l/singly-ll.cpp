
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtPosition(int value, int position) {
    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;

    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Position out of range\n";
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// 4. Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
}

// 5. Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    if (head->next == NULL) {
        delete head;
        head = NULL;
        return;
    }

    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = NULL;
}

// 6. Delete by value
void deleteByValue(int value) {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        cout << "Value not found\n";
        return;
    }

    Node* delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;
}

// 7. Search an element
bool search(int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// 8. Count number of nodes
int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 9. Reverse the linked list
void reverseList() {
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head = prev;
}

// 10. Display the list
void display() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// Main function
int main() {
    insertAtBeginning(10);
    insertAtEnd(20);
    insertAtEnd(30);
    insertAtPosition(15, 2);

    cout << "Linked List: ";
    display();

    deleteFromBeginning();
    cout << "After deleting from beginning: ";
    display();

    deleteFromEnd();
    cout << "After deleting from end: ";
    display();

    deleteByValue(20);
    cout << "After deleting value 20: ";
    display();

    cout << "Search 15: ";
    cout << (search(15) ? "Found\n" : "Not Found\n");

    cout << "Total nodes: " << countNodes() << endl;

    reverseList();
    cout << "After reversing: ";
    display();

    return 0;
}
