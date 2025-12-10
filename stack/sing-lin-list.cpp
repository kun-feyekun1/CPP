
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;

void insertAtBeginning( int value ) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Insert at end
void insertAtEnd( int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Insert at a given position (0-based)
void insertAtPosition( int value, int position) {
    if (position < 0) {
        cout << "Invalid position!\n";
        return;
    }

    if (position == 0) {
        insertAtBeginning( value);
        return;
    }

    Node* newNode = new Node();
    newNode->data = value;

    Node* temp = head;
    int index = 0;

    while (temp != nullptr && index < position - 1) {
        temp = temp->next;
        index++;
    }

    if (temp == nullptr) {
        cout << "Position out of bounds!\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete from beginning
void deleteFromBeginning() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
}

// Delete from end
void deleteFromEnd() {
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
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
}

// Delete at specific position
void deleteAtPosition(int position) {
    if (position < 0 || head == nullptr) {
        cout << "Invalid position or empty list!\n";
        return;
    }

    if (position == 0) {
        deleteFromBeginning();
        return;
    }

    Node* temp = head;
    int index = 0;

    while (temp != nullptr && index < position - 1) {
        temp = temp->next;
        index++;
    }

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of bounds!\n";
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
}

// Search for a value
bool search(int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// Get length of linked list
int length() {
    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Display linked list
void display() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    Node* temp = head;
    cout << "Linked List: ";
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// Clear the entire list
void clear() {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Main function (demo)
int main() {

    // Insert operations
    insertAtBeginning(10);
    insertAtBeginning(5);
    insertAtEnd(20);
    insertAtPosition(15, 2);

    display();
    cout << "Length: " << length() << endl;

    // Delete operations
    deleteFromBeginning();
    deleteFromEnd();
    deleteAtPosition(1);

    display();

    cout << "Searching 15: " 
         << (search(15) ? "Found" : "Not Found") 
         << endl;

    // Free all memory
    clear();

    return 0;
}



// #include <iostream>
// using namespace std;

// class Node {
// public:
//     int data;
//     Node* next;

//     Node(int value) {
//         data = value;
//         next = nullptr;
//     }
// };

// // ---------------------------
// // Singly Linked List Class
// // ---------------------------
// class LinkedList {
// private:
//     Node* head;

// public:
//     LinkedList() {
//         head = nullptr;
//     }

//     // Insert at the beginning
//     void insertAtBeginning(int value) {
//         Node* newNode = new Node(value);
//         newNode->next = head;
//         head = newNode;
//     }

//     // Insert at the end
//     void insertAtEnd(int value) {
//         Node* newNode = new Node(value);

//         if (head == nullptr) {
//             head = newNode;
//             return;
//         }

//         Node* temp = head;
//         while (temp->next != nullptr) {
//             temp = temp->next;
//         }

//         temp->next = newNode;
//     }

//     // Insert at a given position (0-based index)
//     void insertAtPosition(int value, int position) {
//         if (position < 0) {
//             cout << "Invalid position!\n";
//             return;
//         }

//         if (position == 0) {
//             insertAtBeginning(value);
//             return;
//         }

//         Node* newNode = new Node(value);
//         Node* temp = head;
//         int index = 0;

//         while (temp != nullptr && index < position - 1) {
//             temp = temp->next;
//             index++;
//         }

//         if (temp == nullptr) {
//             cout << "Position out of bounds!\n";
//             delete newNode;
//             return;
//         }

//         newNode->next = temp->next;
//         temp->next = newNode;
//     }

//     // Delete from beginning
//     void deleteFromBeginning() {
//         if (head == nullptr) {
//             cout << "List is empty!\n";
//             return;
//         }

//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }

//     // Delete from end
//     void deleteFromEnd() {
//         if (head == nullptr) {
//             cout << "List is empty!\n";
//             return;
//         }

//         if (head->next == nullptr) {
//             delete head;
//             head = nullptr;
//             return;
//         }

//         Node* temp = head;
//         while (temp->next->next != nullptr) {
//             temp = temp->next;
//         }

//         delete temp->next;
//         temp->next = nullptr;
//     }

//     // Delete from a specific position
//     void deleteAtPosition(int position) {
//         if (position < 0 || head == nullptr) {
//             cout << "Invalid position or empty list!\n";
//             return;
//         }

//         if (position == 0) {
//             deleteFromBeginning();
//             return;
//         }

//         Node* temp = head;
//         int index = 0;

//         while (temp != nullptr && index < position - 1) {
//             temp = temp->next;
//             index++;
//         }

//         if (temp == nullptr || temp->next == nullptr) {
//             cout << "Position out of bounds!\n";
//             return;
//         }

//         Node* toDelete = temp->next;
//         temp->next = toDelete->next;
//         delete toDelete;
//     }

//     // Search for a value
//     bool search(int value) {
//         Node* temp = head;
//         while (temp != nullptr) {
//             if (temp->data == value) {
//                 return true;
//             }
//             temp = temp->next;
//         }
//         return false;
//     }

//     // Get the length of the list
//     int length() {
//         int count = 0;
//         Node* temp = head;

//         while (temp != nullptr) {
//             count++;
//             temp = temp->next;
//         }
//         return count;
//     }

//     // Display the linked list
//     void display() {
//         Node* temp = head;
//         if (temp == nullptr) {
//             cout << "List is empty!\n";
//             return;
//         }

//         cout << "Linked List: ";
//         while (temp != nullptr) {
//             cout << temp->data << " -> ";
//             temp = temp->next;
//         }
//         cout << "NULL\n";
//     }

//     // Clear the entire list
//     void clear() {
//         Node* temp;

//         while (head != nullptr) {
//             temp = head;
//             head = head->next;
//             delete temp;
//         }
//     }

//     // Destructor to free memory
//     ~LinkedList() {
//         clear();
//     }
// };

// // ---------------------------
// // Main Function (Demo)
// // ---------------------------
// int main() {
//     LinkedList list;

//     list.insertAtBeginning(10);
//     list.insertAtBeginning(5);
//     list.insertAtEnd(20);
//     list.insertAtPosition(15, 2);

//     list.display();
//     cout << "Length: " << list.length() << endl;

//     list.deleteFromBeginning();
//     list.deleteFromEnd();
//     list.deleteAtPosition(1);

//     list.display();

//     cout << "Searching 15: " << (list.search(15) ? "Found" : "Not Found") << endl;

//     return 0;
// }
