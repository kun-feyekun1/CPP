
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

bool search(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;

    if (value < root->data) 
      return search(root->left, value);
    else 
      return search(root->right, value);
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countEdges(Node* root) {
    int nodes = countNodes(root);
    if (nodes == 0) return 0;
    return nodes - 1;
}

//another form for edge count
int countEdges(Node* root) {
    if (root == nullptr) return 0;

    int edges = 0;
    if (root->left) edges++;
    if (root->right) edges++;

    return edges + countEdges(root->left) + countEdges(root->right);
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    return max(lHeight, rHeight) + 1;
}

Node* minValueNode(Node* root) {
    Node* curr = root;
    while (curr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

Node* maxValueNode(Node* root) {
    Node* curr = root;
    while (curr && curr->right != nullptr)
        curr = curr->right;
    return curr;
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

    cout << "In order traversal: ";
    inorder(root);
    cout << endl;

    cout << "Pre order traversal: ";
    preorder(root);
    cout << endl;

    cout << "Post order traversal: ";
    postorder(root);
    cout << endl;

    cout << "max val: "<< maxValueNode(root)->data; 
    cout << endl;

    cout << "min val: "<< minValueNode(root)->data;
    cout << endl;
    
    cout << "Search 40: " << (search(root, 40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (search(root, 90) ? "Found" : "Not Found") << endl;
    
    cout << "Number of nodes: " << countNodes(root) << endl;
    cout << "number of edges: "<<countEdges(root)<<endl;
    cout << "Height of tree: " << height(root) << endl;

    cout << endl;

    return 0;
}


// docker run -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=Strong!Pass123" -p 1433:1433 --name sqlserver2022 -d mcr.microsoft.com/mssql/server:2022-latest
// docker pull mcr.microsoft.com/mssql/server:2022-latest

// docker run -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=Strong!Pass123" -p 1433:1433 --name sqlserver2022 -v D:\SQLData:/var/opt/mssql -d mcr.microsoft.com/mssql/server:2022-latest


// docker run -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=Strong!Pass123" -p 1433:1433 --name sqlserver2022 -v D:/SQLData:/var/opt/mssql -d mcr.microsoft.com/mssql/server:2022-latest
// docker run -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=Strong!Pass123" -p 1433:1433 --name sqlserver2022 -d mcr.microsoft.com/mssql/server:2022-latest
