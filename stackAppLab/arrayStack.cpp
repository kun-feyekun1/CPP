
#include <iostream>
#include <string>
using namespace std;


#define MAX_SIZE 100

char stackArr[MAX_SIZE];
int topIndex = -1;

void initStack() {
    topIndex = -1;
}

bool isEmpty() {
    return topIndex == -1;
}

bool isFull() {
    return topIndex == MAX_SIZE - 1;
}

void push(char value) {
    if (!isFull())
        stackArr[++topIndex] = value;
}

char pop() {
    if (isEmpty())
        return '\0';
    return stackArr[topIndex--];
}

char peek() {
    if (isEmpty())
        return '\0';
    return stackArr[topIndex];
}

bool isChar(char c) {
    return (c >= '0' && c <= '9') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z');
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string infixToPostfix(const string& infix) {
    initStack();
    string postfix = "";

    for (char ch : infix) {
        if (ch == ' ') continue;

        if (isChar(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (!isEmpty() && peek() != '(')
                postfix += pop();
            pop();
        }
        else {
            while (!isEmpty() && precedence(ch) <= precedence(peek()))
                postfix += pop();
            push(ch);
        }
    }

    while (!isEmpty())
        postfix += pop();

    return postfix;
}

int main() {
    int choice;

    while (true) {
        cout << "1. Infix to Postfix\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

         if (choice == 1) {
            string infix;
            cout << "Enter infix expression: ";
            getline(cin, infix);
            cout << "Postfix: " << infixToPostfix(infix) << endl;
        }
        else if(choice == 2) {
            return 0;
        }
    }
}
