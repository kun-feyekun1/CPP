#include <iostream>
using namespace std;

struct Student {
    int id;
    string name;
    Student* left;
    Student* right;
};

Student* createStudent(int id, string name) {
    Student* s = new Student;
    s->id = id;
    s->name = name;
    s->left = NULL;
    s->right = NULL;
    return s;
}

Student* insert(Student* root, int id, string name) {
    if (root == NULL)
        return createStudent(id, name);

    if (id < root->id)
        root->left = insert(root->left, id, name);
    else if (id > root->id)
        root->right = insert(root->right, id, name);

    return root;
}

Student* search(Student* root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);
    return search(root->right, id);
}

void inorder(Student* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "ID: " << root->id << " | Name: " << root->name << endl;
        inorder(root->right);
    }
}

Student* findMin(Student* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

Student* deleteStudent(Student* root, int id) {
    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = deleteStudent(root->left, id);
    else if (id > root->id)
        root->right = deleteStudent(root->right, id);
    else {
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }

        Student* temp = findMin(root->right);
        root->id = temp->id;
        root->name = temp->name;
        root->right = deleteStudent(root->right, temp->id);
    }
    return root;
}

int countStudents(Student* root) {
    if (root == NULL)
        return 0;
    return 1 + countStudents(root->left) + countStudents(root->right);
}

int height(Student* root) {
    if (root == NULL)
        return -1;
    return max(height(root->left), height(root->right)) + 1;
}

Student* findMax(Student* root) {
    while (root && root->right != NULL)
        root = root->right;
    return root;
}

int main() {
    Student* root = NULL;
    int choice, id;
    string name;

    while (true) {
        cout << "\n--- STUDENT RECORD SYSTEM (BST) ---\n";
        cout << "1. Add Student\n2. Search Student\n3. Update Student\n";
        cout << "4. Delete Student\n5. Display All\n6. Count Students\n";
        cout << "7. Tree Height\n8. Min ID\n9. Max ID\n10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                root = insert(root, id, name);
                break;

            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                if (search(root, id))
                    cout << "Student found\n";
                else
                    cout << "Student not found\n";
                break;

            case 3:
                cout << "Enter ID to update: ";
                cin >> id;
                if (search(root, id)) {
                    cout << "Enter new name: ";
                    cin >> name;
                    search(root, id)->name = name;
                    cout << "Updated successfully\n";
                } else {
                    cout << "Student not found\n";
                }
                break;

            case 4:
                cout << "Enter ID to delete: ";
                cin >> id;
                root = deleteStudent(root, id);
                break;

            case 5:
                inorder(root);
                break;

            case 6:
                cout << "Total Students: " << countStudents(root) << endl;
                break;

            case 7:
                cout << "Height: " << height(root) << endl;
                break;

            case 8:
                if (findMin(root))
                    cout << "Min ID: " << findMin(root)->id << endl;
                else
                    cout << "Tree empty\n";
                break;

            case 9:
                if (findMax(root))
                    cout << "Max ID: " << findMax(root)->id << endl;
                else
                    cout << "Tree empty\n";
                break;

            case 10:
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}
