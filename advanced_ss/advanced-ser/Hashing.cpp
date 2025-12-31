#include <iostream>
using namespace std;

#define SIZE 10

int hashTable[SIZE];

void initTable() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

int hashFunction(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hashFunction(key);

    while (hashTable[index] != -1)
        index = (index + 1) % SIZE;

    hashTable[index] = key;
}

int search(int key) {
    int index = hashFunction(key);
    int start = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key)
            return index;
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }
    return -1;
}

int main() {
    initTable();
    insert(23);
    insert(43);
    insert(13);

    cout << search(43);
    return 0;
}
