#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* prev;
    Node* next;
};

Node* topPtr = nullptr;

// Stack empty?
bool isEmpty() {
    return topPtr == nullptr;
}

// Push using doubly linked list
void push(char value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;        // stack grows to the right
    newNode->prev = topPtr;

    if (topPtr != nullptr)
        topPtr->next = newNode;

    topPtr = newNode;
}

// Pop from stack
char pop() {
    if (isEmpty())
        return '\0';

    Node* temp = topPtr;
    char value = temp->data;

    topPtr = topPtr->prev;

    if (topPtr != nullptr)
        topPtr->next = nullptr;

    delete temp;
    return value;
}

// Peek
char peek() {
    if (isEmpty())
        return '\0';
    return topPtr->data;
}

// Character checks
bool isAlphaNum(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

// Precedence for infix -> postfix
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Reverse string using stack
string reverseString(const string& s) {
    topPtr = nullptr;

    for (char c : s)
        push(c);

    string rev = "";
    while (!isEmpty())
        rev += pop();

    return rev;
}

// Palindrome check
bool isPalindrome(const string& s) {
    return s == reverseString(s);
}

// Decimal to binary
string decimalToBinary(int num) {
    topPtr = nullptr;

    if (num == 0)
        return "0";

    while (num > 0) {
        push((num % 2) + '0');
        num /= 2;
    }

    string bin = "";
    while (!isEmpty())
        bin += pop();

    return bin;
}

// Infix to postfix
string infixToPostfix(const string& infix) {
    topPtr = nullptr;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (ch == ' ') continue;

        if (isAlphaNum(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (!isEmpty() && peek() != '(')
                postfix += pop();
            pop(); // remove '('
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

// Main program
int main() {
    int choice;

    while (true) {
        cout << "\n===== DOUBLY LINKED LIST STACK APPLICATIONS =====\n";
        cout << "1. Reverse String\n";
        cout << "2. Palindrome Check\n";
        cout << "3. Decimal to Binary\n";
        cout << "4. Infix to Postfix\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string s;
            cout << "Enter string: ";
            getline(cin, s);
            cout << "Reversed: " << reverseString(s) << endl;
        }
        else if (choice == 2) {
            string s;
            cout << "Enter string: ";
            getline(cin, s);
            cout << (isPalindrome(s) ? "Palindrome" : "Not Palindrome") << endl;
        }
        else if (choice == 3) {
            int num;
            cout << "Enter decimal number: ";
            cin >> num;
            cout << "Binary: " << decimalToBinary(num) << endl;
        }
        else if (choice == 4) {
            string infix;
            cout << "Enter infix expression: ";
            getline(cin, infix);
            cout << "Postfix: " << infixToPostfix(infix) << endl;
        }
        else if (choice == 5) {
            return 0;
        }
    }
}
