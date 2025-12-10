#include <iostream>
using namespace std;

class ArrayStack {
private:
    int top;
    int capacity;
    int* arr;

public:
    ArrayStack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << value << endl;
            return;
        }
        arr[++top] = value;
        cout << value << " pushed to stack.\n";
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        cout << arr[top] << " popped from stack.\n";
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is Empty!\n";
            return -1;
        }
        return arr[top];
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }

        cout << "Stack elements: ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    int size;
    cout << "Enter stack size: ";
    cin >> size;

    ArrayStack st(size);

    int choice, value;

    while (true) {
        cout << "\n--- ARRAY STACK MENU ---\n";
        cout << "1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                st.push(value);
                break;

            case 2:
                st.pop();
                break;

            case 3:
                cout << "Top element: " << st.peek() << endl;
                break;

            case 4:
                st.display();
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
