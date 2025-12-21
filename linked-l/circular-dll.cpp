#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Head pointer
Node* head = NULL;

// 1. Insert at beginning
void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;

    if (head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }

    Node* last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
    head = newNode;
}

// 2. Insert at end
void insertAtEnd(int value) {
    if (head == NULL) {
        insertAtBeginning(value);
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;

    Node* last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;
}

// 3. Insert at specific position (1-based)
void insertAtPosition(int value, int position) {
    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
        if (temp == head) {
            cout << "Position out of range\n";
            return;
        }
    }

    Node* newNode = new Node();
    newNode->data = value;

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

// 4. Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    if (head->next == head) {
        delete head;
        head = NULL;
        return;
    }

    Node* last = head->prev;
    Node* temp = head;

    head = head->next;
    last->next = head;
    head->prev = last;

    delete temp;
}

// 5. Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    if (head->next == head) {
        delete head;
        head = NULL;
        return;
    }

    Node* last = head->prev;
    Node* secondLast = last->prev;

    secondLast->next = head;
    head->prev = secondLast;

    delete last;
}

// 6. Delete by value
void deleteByValue(int value) {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;

    do {
        if (temp->data == value) {
            if (temp->next == temp) {
                delete temp;
                head = NULL;
                return;
            }

            if (temp == head)
                head = head->next;

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            return;
        }
        temp = temp->next;
    } while (temp != head);

    cout << "Value not found\n";
}

// 7. Search an element
bool search(int value) {
    if (head == NULL)
        return false;

    Node* temp = head;
    do {
        if (temp->data == value)
            return true;
        temp = temp->next;
    } while (temp != head);

    return false;
}

// 8. Count number of nodes
int countNodes() {
    if (head == NULL)
        return 0;

    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

// 9. Reverse the circular doubly linked list
void reverseList() {
    if (head == NULL || head->next == head)
        return;

    Node* current = head;
    Node* temp = NULL;

    do {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    } while (current != head);

    head = head->next;
}

// 10. Display the list
void display() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " <-> ";
        temp = temp->next;
    } while (temp != head);

    cout << "(back to head)\n";
}

// Main function
int main() {
    insertAtBeginning(10);
    insertAtEnd(20);
    insertAtEnd(30);
    insertAtPosition(15, 2);

    cout << "Circular Doubly Linked List:\n";
    display();

    deleteFromBeginning();
    cout << "After deleting from beginning:\n";
    display();

    deleteFromEnd();
    cout << "After deleting from end:\n";
    display();

    deleteByValue(20);
    cout << "After deleting value 20:\n";
    display();

    cout << "Search 15: ";
    cout << (search(15) ? "Found\n" : "Not Found\n");

    cout << "Total nodes: " << countNodes() << endl;

    reverseList();
    cout << "After reversing:\n";
    display();

    return 0;
}
