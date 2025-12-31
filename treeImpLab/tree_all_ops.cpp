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
    if (root == nullptr) return createNode(value);
    if (value < root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return root;
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

bool search(Node* root, int value) {
    if (!root) return false;
    if (root->data == value) return true;
    return (value < root->data) ? search(root->left, value) : search(root->right, value);
}

// Count total nodes
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Count internal nodes
int countInternalNodes(Node* root) {
    if (!root || (!root->left && !root->right)) return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

// Height of tree
int height(Node* root) {
    if (!root) return 0;
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    return max(lHeight, rHeight) + 1;
}

// Find minimum value node
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left) 
       current = current->left;
    return current;
}

// Find maximum value node
Node* maxValueNode(Node* root) {
    Node* current = root;
    while (current && current->right) current = current->right;
    return current;
}

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* inorderSuccessor(Node* root, Node* target) {
    if (target->right != nullptr)
        return findMin(target->right);

    Node* successor = nullptr;
    Node* curr = root;
    while (curr != nullptr) {
        if (target->data < curr->data) {
            successor = curr;
            curr = curr->left;
        } else if (target->data > curr->data) {
            curr = curr->right;
        } else
            break;
    }
    return successor;
}

Node* findMax(Node* root) {
    while (root->right != nullptr)
        root = root->right;
    return root;
}

Node* inorderPredecessor(Node* root, Node* target) {
    if (target->left != nullptr)
        return findMax(target->left);

    Node* predecessor = nullptr;
    Node* curr = root;
    while (curr != nullptr) {
        if (target->data > curr->data) {
            predecessor = curr;
            curr = curr->right;
        } else if (target->data < curr->data) {
            curr = curr->left;
        } else
            break;
    }
    return predecessor;
}


Node* inorderPredecessor(Node* root, Node* target) {
    if (!root || !target) return nullptr;

    if (target->left != nullptr) {
        Node* temp = target->left;
        while (temp->right != nullptr)
        temp = temp->right;
        return temp;
    }
    
    Node* curr = root;
    Node* predecessor = nullptr;

    while (curr != nullptr) {
        if (target->data > curr->data) {
            predecessor = curr;
            curr = curr->right;
        } else if (target->data < curr->data) {
            curr = curr->left;
        } else {
            break;
        }
    }
  return predecessor;
}

Node* inorderSuccessor(Node* root, Node* target) {
    if (!root || !target) return nullptr;

    Node* successor = nullptr;
    if (target->right != nullptr) {
        Node* temp = target->right;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    Node* curr = root;
    while (curr != nullptr) {
        if (target->data < curr->data) {
            successor = curr;
            curr = curr->left;
        } else if (target->data > curr->data) {
            curr = curr->right;
        } else {
            break;
        }
    }

    return successor;
}

// Sum of all nodes
int sumNodes(Node* root) {
    if (!root) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

// Delete a node
Node* deleteNode(Node* root, int value) {
    if (!root) return root;

    if (value < root->data) root->left = deleteNode(root->left, value);
    else if (value > root->data) root->right = deleteNode(root->right, value);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
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

int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order: "; inorder(root); cout << endl;
    cout << "Pre-order: "; preorder(root); cout << endl;
    cout << "Post-order: "; postorder(root); cout << endl;

    cout << "Search 40: " << (search(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (search(root, 90) ? "Found" : "Not Found") << endl;

    cout << "Total nodes: " << countNodes(root) << endl;
    cout << "Leaf nodes: " << countLeafNodes(root) << endl;
    cout << "Internal nodes: " << countInternalNodes(root) << endl;
    cout << "Height of tree: " << height(root) << endl;
    cout << "Minimum value: " << minValueNode(root)->data << endl;
    cout << "Maximum value: " << maxValueNode(root)->data << endl;
    cout << "Sum of all nodes: " << sumNodes(root) << endl;

    // Delete some nodes
    root = deleteNode(root, 20);
    root = deleteNode(root, 30);
    root = deleteNode(root, 50);

    cout << "In-order after deletions: "; inorder(root); cout << endl;

    return 0;
}
