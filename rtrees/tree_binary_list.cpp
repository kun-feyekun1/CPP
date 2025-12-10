
#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Search in Binary Tree
bool search(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;

    if (value < root->data) 
      return search(root->left, value);
    else 
      return search(root->right, value);
}

// Count nodes
int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Find height of tree
int height(Node* root) {
    if (root == nullptr) return 0;
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    return max(lHeight, rHeight) + 1;
}

// Find minimum value node (used in deletion)
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Delete a node
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        // Node found
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Display tree (in-order)
void display(Node* root) {
    inorder(root);
    cout << endl;
}

// MAIN
int main() {
    Node* root = nullptr;

    // Insert nodes
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order traversal: ";
    inorder(root);
    cout << endl;

    cout << "Pre-order traversal: ";
    preorder(root);
    cout << endl;

    cout << "Post-order traversal: ";
    postorder(root);
    cout << endl;

    cout << "Search 40: " << (search(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (search(root, 90) ? "Found" : "Not Found") << endl;

    cout << "Number of nodes: " << countNodes(root) << endl;
    cout << "Height of tree: " << height(root) << endl;

    // Delete a node
    root = deleteNode(root, 20); // Leaf
    root = deleteNode(root, 30); // Node with one child
    root = deleteNode(root, 50); // Node with two children

    cout << "In-order traversal after deletions: ";
    inorder(root);
    cout << endl;

    return 0;
}
