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
        int idx = word[i] - 'a';
        if (!curr->children[idx])
            curr->children[idx] = createNode();
        curr = curr->children[idx];
    }
    curr->isEnd = true;
}

void printWords(TrieNode* root, char buffer[], int depth) {
    if (root->isEnd) {
        buffer[depth] = '\0';
        cout << buffer << endl;
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (root->children[i]) {
            buffer[depth] = i + 'a';
            printWords(root->children[i], buffer, depth + 1);
        }
    }
}

bool autocomplete(TrieNode* root, char prefix[]) {
    TrieNode* curr = root;

    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a';
        if (!curr->children[idx])
            return false;
        curr = curr->children[idx];
    }

    char buffer[50];
    int depth = 0;
    while (prefix[depth]) {
        buffer[depth] = prefix[depth];
        depth++;
    }

    printWords(curr, buffer, depth);
    return true;
}

int main() {
    TrieNode* root = createNode();

    insert(root, (char*)"apple");
    insert(root, (char*)"app");
    insert(root, (char*)"application");
    insert(root, (char*)"bat");
    insert(root, (char*)"ball");

    cout << "Autocomplete for 'app':" << endl;
    autocomplete(root, (char*)"app");

    return 0;
}
