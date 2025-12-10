#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;

    // Constructor
    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly linked list class
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Insert at the beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {  // Empty list
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {  // Empty list
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Insert at a specific position (1-based index)
    void insertAtPosition(int val, int pos) {
        if (pos <= 1) {
            insertAtBeginning(val);
            return;
        }

        Node* temp = head;
        int count = 1;
        while (temp != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == nullptr || temp->next == nullptr) {
            insertAtEnd(val);
        } else {
            Node* newNode = new Node(val);
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
        }
    }

    // Delete a node by value
    void deleteNode(int val) {
        Node* temp = head;
        while (temp != nullptr && temp->data != val) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value " << val << " not found.\n";
            return;
        }

        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;  // List becomes empty
        } else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Deleted value " << val << " from the list.\n";
    }

    // Search for a value
    bool search(int val) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }

    // Display the list forward
    void displayForward() {
        Node* temp = head;
        cout << "List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display the list backward
    void displayBackward() {
        Node* temp = tail;
        cout << "List (Backward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

// Demo usage
int main() {
    DoublyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtBeginning(5);
    list.insertAtEnd(20);
    list.insertAtPosition(15, 3);  // Insert 15 at position 3

    list.displayForward();   // Output: 5 10 15 20
    list.displayBackward();  // Output: 20 15 10 5

    list.deleteNode(10);
    list.displayForward();   // Output: 5 15 20

    if (list.search(15))
        cout << "15 is found in the list.\n";
    else
        cout << "15 is not found in the list.\n";

    return 0;
}
