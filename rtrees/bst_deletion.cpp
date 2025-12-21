#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int key) {
    Node* n = new Node;
    n->key = key;
    n->left = n->right = nullptr;
    return n;
}

Node* insert(Node* root, int key) {
    if (!root) return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Find max (predecessor)
Node* findMax(Node* root) {
    while (root->right) root = root->right;
    return root;
}

// Find min (successor)
Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

/* ================== DELETION BY COPYING ================== */
// Case 1: replace with predecessor
Node* deleteByCopyingPred(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteByCopyingPred(root->left, key);
    else if (key > root->key)
        root->right = deleteByCopyingPred(root->right, key);
    else if (root->left && root->right) { // Node with 2 children
        Node* pred = findMax(root->left);
        root->key = pred->key;
        root->left = deleteByCopyingPred(root->left, pred->key);
    }
    return root;
}

// Case 2: replace with successor
Node* deleteByCopyingSucc(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteByCopyingSucc(root->left, key);
    else if (key > root->key)
        root->right = deleteByCopyingSucc(root->right, key);
    else if (root->left && root->right) { // Node with 2 children
        Node* succ = findMin(root->right);
        root->key = succ->key;
        root->right = deleteByCopyingSucc(root->right, succ->key);
    }
    return root;
}

/* ================== DELETION BY MERGING ================== */
// Case 1: merge left into right
Node* deleteByMergingLeft(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteByMergingLeft(root->left, key);
    else if (key > root->key)
        root->right = deleteByMergingLeft(root->right, key);
    else if (root->left && root->right) {
        Node* tmp = root->left;
        while (tmp->right) tmp = tmp->right;
        tmp->right = root->right;
        Node* del = root;
        root = root->left;
        delete del;
    }
    return root;
}

// Case 2: merge right into left
Node* deleteByMergingRight(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteByMergingRight(root->left, key);
    else if (key > root->key)
        root->right = deleteByMergingRight(root->right, key);
    else if (root->left && root->right) {
        Node* tmp = root->right;
        while (tmp->left) tmp = tmp->left;
        tmp->left = root->left;
        Node* del = root;
        root = root->right;
        delete del;
    }
    return root;
}

/* ================== INORDER TRAVERSAL ================== */
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

/* ================== MAIN ================== */
int main() {
    Node* root = nullptr;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int k : keys)
        root = insert(root, k);

    cout << "Original BST (Inorder): ";
    inorder(root); cout << endl;

    cout << "\n--- Deletion by Copying: Predecessor ---\n";
    root = deleteByCopyingPred(root, 50);
    inorder(root); cout << endl;

    // Rebuild
    root = nullptr;
    for (int k : keys)
        root = insert(root, k);

    cout << "\n--- Deletion by Copying: Successor ---\n";
    root = deleteByCopyingSucc(root, 50);
    inorder(root); cout << endl;

    // Rebuild
    root = nullptr;
    for (int k : keys)
        root = insert(root, k);

    cout << "\n--- Deletion by Merging: Left ---\n";
    root = deleteByMergingLeft(root, 50);
    inorder(root); cout << endl;

    // Rebuild
    root = nullptr;
    for (int k : keys)
        root = insert(root, k);

    cout << "\n--- Deletion by Merging: Right ---\n";
    root = deleteByMergingRight(root, 50);
    inorder(root); cout << endl;

    return 0;
}
