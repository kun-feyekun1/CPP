#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* prev;
    Node* next;
};

Node* topPtr = nullptr;

bool isEmpty() {
    return topPtr == nullptr;
}

// Push using circular doubly linked list
void push(char value) {
    Node* newNode = new Node;
    newNode->data = value;

    if (topPtr == nullptr) {
        // First node → points to itself
        newNode->next = newNode;
        newNode->prev = newNode;
        topPtr = newNode;
    } 
    else {
        Node* last = topPtr->prev;

        newNode->next = topPtr;
        newNode->prev = last;

        last->next = newNode;
        topPtr->prev = newNode;

        topPtr = newNode;   // new node becomes top
    }
}

// Pop from circular doubly linked list
char pop() {
    if (isEmpty())
        return '\0';

    char value = topPtr->data;

    if (topPtr->next == topPtr) {
        // only 1 node
        delete topPtr;
        topPtr = nullptr;
    }
    else {
        Node* last = topPtr->prev;
        Node* second = topPtr->next;

        last->next = second;
        second->prev = last;

        delete topPtr;
        topPtr = second;   // move top to next element
    }

    return value;
}

char peek() {
    if (isEmpty())
        return '\0';
    return topPtr->data;
}

bool isAlphaNum(char c) {
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

// Reverse string
string reverseString(const string& s) {
    topPtr = nullptr;

    for (char c : s)
        push(c);

    string out = "";
    while (!isEmpty())
        out += pop();

    return out;
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

// Infix to Postfix
string infixToPostfix(const string& infix) {
    topPtr = nullptr;
    string postfix = "";

    for (char ch : infix) {
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

// MAIN PROGRAM
int main() {
    int choice;

    while (true) {
        cout << "\n===== CIRCULAR DOUBLY LINKED LIST STACK =====\n";
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
