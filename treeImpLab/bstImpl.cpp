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
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

bool search(Node* root, int key) {
    if (root == NULL)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

Node* findMax(Node* root) {
    while (root && root->right != NULL)
        root = root->right;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(Node* root) {
    if (root == NULL)
        return -1;
    int leftH = height(root->left);
    int rightH = height(root->right);
    return max(leftH, rightH) + 1;
}

int countNodes(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node* root = NULL;
    int choice, value;

    while (true) {
        cout << "\n--- BST MENU ---\n";
        cout << "1. Insert\n2. Search\n3. Inorder\n4. Preorder\n5. Postorder\n";
        cout << "6. Delete\n7. Min\n8. Max\n9. Height\n10. Count Nodes\n11. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                root = insert(root, value);
                break;

            case 2:
                cout << "Enter key to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Found\n";
                else
                    cout << "Not Found\n";
                break;

            case 3:
                inorder(root);
                cout << endl;
                break;

            case 4:
                preorder(root);
                cout << endl;
                break;

            case 5:
                postorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;

            case 7:
                if (findMin(root))
                    cout << "Min: " << findMin(root)->data << endl;
                else
                    cout << "Tree empty\n";
                break;

            case 8:
                if (findMax(root))
                    cout << "Max: " << findMax(root)->data << endl;
                else
                    cout << "Tree empty\n";
                break;

            case 9:
                cout << "Height: " << height(root) << endl;
                break;

            case 10:
                cout << "Total Nodes: " << countNodes(root) << endl;
                break;

            case 11:
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}
