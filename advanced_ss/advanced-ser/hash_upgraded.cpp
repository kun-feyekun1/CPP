#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

struct Entry {
    int key;
    string value;
    bool occupied;
};

Entry hashTable[SIZE];

void initTable() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i].occupied = false;
}

int hashFunction(int key) {
    return key % SIZE;
}

void insert(int key, string value) {
    int index = hashFunction(key);

    while (hashTable[index].occupied) {
        index = (index + 1) % SIZE;
    }

    hashTable[index].key = key;
    hashTable[index].value = value;
    hashTable[index].occupied = true;
}

string search(int key) {
    int index = hashFunction(key);
    int start = index;

    while (hashTable[index].occupied) {
        if (hashTable[index].key == key)
            return hashTable[index].value;

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    return "Not Found";
}

void printTable() {
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i].occupied)
            cout << i << " -> (" << hashTable[i].key
                 << ", " << hashTable[i].value << ")\n";
        else
            cout << i << " -> EMPTY\n";
    }
}

int main() {
    initTable();

    insert(101, "Mohammed");
    insert(205, "Hassen");
    insert(330, "Addis");

    printTable();

    cout << "\nSearch 205: " << search(205) << endl;

    return 0;
}