
#include <iostream>
#include <cstring>     // only for strlen() and strcmp()
                       // you can remove strcmp too if you want fully raw

// Simple node for the linked list (chaining)
struct Node {
    char* key;         // student ID (dynamically allocated string)
    char* name;
    int age;
    float gpa;
    Node* next;

    Node(const char* k, const char* n, int a, float g) : next(nullptr) {
        // allocate and copy key
        key = new char[strlen(k) + 1];
        strcpy(key, k);

        // allocate and copy name
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        age = a;
        gpa = g;
    }

    ~Node() {
        delete[] key;
        delete[] name;
    }
};

// -----------------------------------------------------------------
// Hash Table class with chaining
// -----------------------------------------------------------------
class HashTable {
private:
    static const int TABLE_SIZE = 13;   // small prime number
    Node* table[TABLE_SIZE];            // array of pointers to chains

    // Very simple hash function for strings
    unsigned int hash(const char* key) const {
        unsigned int h = 0;
        while (*key) {
            h = h * 31 + (*key);
            key++;
        }
        return h % TABLE_SIZE;
    }

    // Helper: compare two C-strings
    bool equal(const char* a, const char* b) const {
        return strcmp(a, b) == 0;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // Insert or update
    void insert(const char* id, const char* name, int age, float gpa) {
        unsigned int index = hash(id);
        Node* current = table[index];

        // Look for existing key
        while (current) {
            if (equal(current->key, id)) {
                // Update existing
                delete[] current->name;
                current->name = new char[strlen(name) + 1];
                strcpy(current->name, name);
                current->age = age;
                current->gpa = gpa;
                std::cout << "Updated: " << id << "\n";
                return;
            }
            current = current->next;
        }

        // New entry
        Node* newNode = new Node(id, name, age, gpa);
        newNode->next = table[index];
        table[index] = newNode;
        std::cout << "Inserted: " << id << "\n";
    }

    // Find student by ID
    void find(const char* id) const {
        unsigned int index = hash(id);
        Node* current = table[index];

        while (current) {
            if (equal(current->key, id)) {
                std::cout << "Found -> ID: " << current->key
                          << "  Name: " << current->name
                          << "  Age: " << current->age
                          << "  GPA: " << current->gpa << "\n";
                return;
            }
            current = current->next;
        }
        std::cout << "Not found: " << id << "\n";
    }

    // Remove by ID
    void remove(const char* id) {
        unsigned int index = hash(id);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (equal(current->key, id)) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                std::cout << "Removed: " << id << "\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Not found to remove: " << id << "\n";
    }

    // Print whole table
    void print() const {
        std::cout << "\n=== Hash Table Content ===\n";
        std::cout << "Bucket   Content\n";
        std::cout << "------------------------\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            std::cout << "[" << i << "]    ";
            Node* current = table[i];
            if (!current) {
                std::cout << "(empty)\n";
                continue;
            }
            while (current) {
                std::cout << current->key << " (" << current->name << ")  →  ";
                current = current->next;
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};

// -----------------------------------------------------------------
// Demo
// -----------------------------------------------------------------
int main() {
    HashTable ht;

    ht.insert("ST001", "Abebe Kebede",     20, 3.85f);
    ht.insert("ST015", "Sara Mohammed",    19, 3.92f);
    ht.insert("ST028", "Dawit Tesfaye",    21, 3.45f);
    ht.insert("ST042", "Fatima Ali",       18, 3.67f);
    ht.insert("ST001", "Abebe Kebede",     20, 3.88f);  // update

    ht.print();

    std::cout << "\nLookup tests:\n";
    ht.find("ST015");
    ht.find("ST999");           // not exists

    std::cout << "\nRemove tests:\n";
    ht.remove("ST028");
    ht.remove("ST777");         // not exists

    ht.print();

    return 0;
}