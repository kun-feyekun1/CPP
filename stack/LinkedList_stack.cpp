#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *top = NULL;

void push(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = top;
    top = newNode;
}

void pop()
{
    if (top == NULL)
    {
        cout << "Stack Underflow\n";
        return;
    }
    cout << "Popped: " << top->data << endl;
    Node *temp = top;
    top = top->next;
    delete temp;
}

int peek()
{
    if (top == NULL)
    {
        cout << "Stack is empty\n";
        return -1;
    }
    return top->data;
}

void display()
{
    if (top == NULL)
    {
        cout << "Stack is empty\n";
        return;
    }
    Node *moh = top;
    while (moh != NULL)
    {
        cout << moh->data << " ";
        moh = moh->next;
    }
    cout << endl;
}

int main()
{
    int i = 1;
    while (i <= 5)
    {
        push(i);
        i++;
    }

    display();

    pop();
    cout << "Top: " << peek() << endl;

    display();

    return 0;
}
