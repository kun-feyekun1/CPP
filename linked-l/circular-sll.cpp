#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
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
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != head)
        temp = temp->next;

    newNode->next = head;
    temp->next = newNode;
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

    Node* temp = head;
    while (temp->next != head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = head;
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

    Node* temp = head;
    Node* last = head;

    while (last->next != head)
        last = last->next;

    head = head->next;
    last->next = head;
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

    Node* temp = head;
    Node* prev = NULL;

    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = head;
    delete temp;
}

// 6. Delete by value
void deleteByValue(int value) {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* curr = head;
    Node* prev = NULL;

    do {
        if (curr->data == value) {
            if (curr == head && curr->next == head) {
                delete curr;
                head = NULL;
                return;
            }

            if (curr == head) {
                Node* last = head;
                while (last->next != head)
                    last = last->next;

                head = head->next;
                last->next = head;
                delete curr;
                return;
            }

            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != head);

    cout << "Value not found\n";
}

void deleteByValue(int value) {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* curr = head;
    Node* prev = NULL;

    // Special handling if head itself holds the value
    if (head->data == value) {

        // Case 1: only one node
        if (head->next == head) {
            delete head;
            head = NULL;
            return;
        }

        // Case 2: multiple nodes
        Node* last = head;
        while (last->next != head)
            last = last->next;

        last->next = head->next;
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // General case: value is NOT in head
    prev = head;
    curr = head->next;

    while (curr != head) {
        if (curr->data == value) {
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

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

// 9. Reverse the circular singly linked list
void reverseList() {
    if (head == NULL || head->next == head)
        return;

    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;
    Node* last = head;

    while (last->next != head)
        last = last->next;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != head);

    head->next = prev;
    head = prev;
    last->next = head;
}

// 10. Display the list
void display() {
    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " -> ";
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

    cout << "Circular Singly Linked List:\n";
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
