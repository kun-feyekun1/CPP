#include <iostream>
#include "ArrayStack.h"
#include "LinkedListStack.h"
#include "StackApplications.h"
using namespace std;

int main() {
    cout << "--- Array-based Stack ---\n";
    ArrayStack aStack(5);
    aStack.push(10); aStack.push(20); aStack.push(30);
    aStack.display();
    cout << "Pop: " << aStack.pop() << endl;

    cout << "\n--- Linked List Stack ---\n";
    LinkedListStack lStack;
    lStack.push(1); lStack.push(2); lStack.push(3);
    lStack.display();
    cout << "Peek: " << lStack.peek() << endl;

    cout << "\n--- Stack Applications ---\n";
    string str = "madam";
    reverseString(str);
    cout << str << " is " << (isPalindrome(str) ? "" : "not ") << "a palindrome.\n";

    int num = 25;
    decimalToBinary(num);

    return 0;
}
