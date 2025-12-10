
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* prev;
    Node* next;
};

Node* firstPtr = nullptr;

bool isEmpty() {
    return firstPtr == nullptr;
}

void push(char value) {
    Node* newNode = new Node;
    newNode->data = value;

    if (firstPtr == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        firstPtr = newNode;
    } 
    else {
        Node* lastPtr = firstPtr->prev;
        newNode->next = firstPtr;
        newNode->prev = lastPtr;
        lastPtr->next = newNode; 
        firstPtr->prev = newNode;
    }
}

char pop() {
    if (isEmpty())
        return '\0';

    Node* lastPtr = firstPtr->prev;
    char value = lastPtr->data;

    if (lastPtr == firstPtr) {
        delete lastPtr;
        firstPtr = nullptr;
    }
    else {
        Node* secondLast = lastPtr->prev;
        secondLast->next = firstPtr;
        firstPtr->prev = secondLast;

        delete lastPtr;
    }
    return value;
}


char peek() {
    if (isEmpty())
        return '\0';
    return firstPtr->prev->data;
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

string reverseString(const string& s) {
    firstPtr = nullptr;

    for (char c : s)
        push(c);

    string out = "";
    while (!isEmpty())
        out += pop();

    return out;
}

bool isPalindrome(const string& s) {
    return s == reverseString(s);
}

string decimalToBinary(int num) {
    firstPtr = nullptr;

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

string infixToPostfix(const string& infix) {
    firstPtr = nullptr;
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
