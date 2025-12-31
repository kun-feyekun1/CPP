#include <iostream>
using namespace std;

#define ALPHABET 26

struct TrieNode {
    TrieNode* children[ALPHABET];
    bool isEnd;
};

TrieNode* createNode() {
    TrieNode* node = new TrieNode;
    node->isEnd = false;

    for (int i = 0; i < ALPHABET; i++)
        node->children[i] = nullptr;

    return node;
}

void insert(TrieNode* root, char word[]) {
    TrieNode* curr = root;

    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';

        if (!curr->children[index])
            curr->children[index] = createNode();

        curr = curr->children[index];
    }
    curr->isEnd = true;
}

bool search(TrieNode* root, char word[]) {
    TrieNode* curr = root;

    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';

        if (!curr->children[index])
            return false;

        curr = curr->children[index];
    }
    return curr->isEnd;
}

int main() {
    TrieNode* root = createNode();

    insert(root, (char*)"apple");
    insert(root, (char*)"app");
    insert(root, (char*)"bat");

    cout << search(root, (char*)"app") << endl;    // 1 (true)
    cout << search(root, (char*)"bat") << endl;    // 1
    cout << search(root, (char*)"bad") << endl;    // 0

    return 0;
}
