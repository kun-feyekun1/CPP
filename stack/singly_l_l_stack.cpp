#include <iostream>
using namespace std;

#define SIZE 5

int arr[SIZE];
int top = -1;

void push(int val) {
    if(top == SIZE - 1) {
        cout << "Stack Overflow\n";
        return;
    }
    top++;
    arr[top] = val;
}

void pop() {
    if(top == -1) {
        cout << "Stack Underflow\n";
        return;
    }
    cout << "Popped: " << arr[top] << endl;
    top--;
}

int peek() {
    if(top == -1) {
        cout << "Stack is empty\n";
        return -1;
    }
    return arr[top];
}

void display() {
    if(top == -1) {
        cout << "Stack is empty\n";
        return;
    }
    for(int i = top; i >=0; i--)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {

    push(10);
    push(20);
    push(30);

    display();

    pop();
    cout << "Top: " << peek() << endl;

    display();

    return 0;
}
