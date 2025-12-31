#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (!root) return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

Node* findMaxPred(Node* root) {
    while (root->right!=nullptr)
        root = root->right;
    return root;
}

Node* findMinSucc(Node* root) {
    while (root->left!=nullptr) 
      root = root->left;
    return root;
}

Node* deleteByCopyingPred(Node* root, int value) {
    if (root == nullptr)
        return nullptr;

    if (value < root->data) {
        root->left = deleteByCopyingPred(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteByCopyingPred(root->right, value);
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* pred = findMaxPred(root->left);
            root->data = pred->data;
            root->left = deleteByCopyingPred(root->left, pred->data);
        }
    }
    return root;
}

Node* deleteByCopyingSucc(Node* root, int value) {
    if (root == nullptr)
        return nullptr;

    if (value < root->data) {
        root->left = deleteByCopyingSucc(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteByCopyingSucc(root->right, value);
    }
    else { 
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* succ = findMinSucc(root->right);
            root->data = succ->data;
            root->right = deleteByCopyingSucc(root->right, succ->data);
        }
    }
    return root;
}

Node* deleteByMergingLeft(Node* root, int value) {
    if (!root) return nullptr;

    if (value < root->data)
        root->left = deleteByMergingLeft(root->left, value);
    else if (value > root->data)
        root->right = deleteByMergingLeft(root->right, value);
    else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* tmp = root->left;
            while (tmp->right) 
              tmp = tmp->right;
            tmp->right = root->right;
            Node* del = root;
            root = root->left;
            delete del;
        }
    }
    return root;
}

Node* deleteByMergingRight(Node* root, int value) {
    if (!root) return nullptr;

    if (value < root->data)
        root->left = deleteByMergingRight(root->left, value);
    else if (value > root->data)
        root->right = deleteByMergingRight(root->right, value);
    else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        else if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) { 
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* tmp = root->right;
            while (tmp->left) tmp = tmp->left;
            tmp->left = root->left;
            Node* del = root;
            root = root->right;
            delete del;
        }
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    int values[] = {29,18,12,24,35,32,30,33,38,36,41,45};
    for (int k : values)
        root = insert(root, k);

    cout << "Original BST (Inorder): ";
    inorder(root); cout << endl;

    cout << "\nDeleting leaf Node: 12\n";
    root = deleteByCopyingPred(root, 12);
    inorder(root); cout << endl;

    cout << "\n Deleting single left child:  24 \n";
    root = deleteByCopyingSucc(root, 24);
    inorder(root); cout << endl;

    cout << "\n Deleting Node with right child: 41\n";
    root = deleteByMergingLeft(root, 41);
    inorder(root); cout << endl;

    cout << "\nDeletion by Copying: 35, Predecessor\n";
    root = deleteByCopyingPred(root, 35);
    inorder(root); cout << endl;

    cout << "\n Deletion by Merging: 35, Right \n";
    root = deleteByMergingRight(root, 35);
    inorder(root); cout << endl;

    return 0;
}
