#include <iostream>
#include "StackApplications.h"

// Reverse a string using linked list stack
void reverseString(const string &str) {
    LinkedListStack stack;
    for (char ch : str) stack.push(ch);

    cout << "Reversed: ";
    while (stack.peek() != -1) {
        cout << (char)stack.pop();
    }
    cout << endl;
}

// Check if a string is palindrome
bool isPalindrome(const string &str) {
    LinkedListStack stack;
    for (char ch : str) stack.push(ch);

    for (char ch : str) {
        if (stack.pop() != ch) return false;
    }
    return true;
}

// Convert decimal to binary using array stack
void decimalToBinary(int n) {
    ArrayStack stack(32); // Max 32 bits
    while (n > 0) {
        stack.push(n % 2);
        n /= 2;
    }

    cout << "Binary: ";
    while (stack.peek() != -1) {
        cout << stack.pop();
    }
    cout << endl;
}
