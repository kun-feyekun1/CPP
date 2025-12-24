#include <iostream>
#include <string>
using namespace std;

/* ================= STACK USING CSLL ================= */

struct Node {
    char data;
    Node* next;
};

Node* topPtr = nullptr;

/* ---------- BASIC STACK OPERATIONS ---------- */

bool isEmpty() {
    return topPtr == nullptr;
}

void push(char value) {
    Node* newNode = new Node;
    newNode->data = value;

    if (topPtr == nullptr) {
        newNode->next = newNode;   // circular self link
        topPtr = newNode;
    } else {
        Node* last = topPtr;
        while (last->next != topPtr)
            last = last->next;

        last->next = newNode;
        newNode->next = topPtr;
        topPtr = newNode;
    }
}

char pop() {
    if (isEmpty())
        return '\0';

    char value = topPtr->data;

    // only one node
    if (topPtr->next == topPtr) {
        delete topPtr;
        topPtr = nullptr;
        return value;
    }

    Node* temp = topPtr;
    Node* last = topPtr;

    while (last->next != topPtr)
        last = last->next;

    topPtr = topPtr->next;
    last->next = topPtr;

    delete temp;
    return value;
}

char peek() {
    if (isEmpty())
        return '\0';
    return topPtr->data;
}

/* ---------- HELPER FUNCTIONS ---------- */

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

/* ---------- APPLICATIONS ---------- */

string reverseString(const string& s) {
    topPtr = nullptr;

    for (char c : s)
        push(c);

    string rev = "";
    while (!isEmpty())
        rev += pop();

    return rev;
}

bool isPalindrome(const string& s) {
    return s == reverseString(s);
}

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

/* ================= MAIN ================= */

int main() {
    int choice;

    while (true) {
        cout << "\n===== CSLL STACK APPLICATIONS =====\n";
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
        else {
            cout << "Invalid choice!\n";
        }
    }
}
