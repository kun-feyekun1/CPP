
#include <iostream>
using namespace std;

// Doubly Linked List Node
struct Node
{
    int data;
    Node *next;
    Node *prev; // NEW: Pointer to previous node
};

Node *top = NULL;

// PUSH operation
void push(int val)
{
    Node *newNode = new Node();
    newNode->data = val;
    newNode->next = top;  // new node points to old top
    newNode->prev = NULL; // previous is NULL since it's the new top

    if (top != NULL)
        top->prev = newNode; // old top points back to new node

    top = newNode; // update top
}

// POP operation
void pop()
{
    if (top == NULL)
    {
        cout << "Stack Underflow\n";
        return;
    }

    cout << "Popped: " << top->data << endl;

    Node *temp = top;
    top = top->next; // move top down

    if (top != NULL)
        top->prev = NULL; // remove backward link

    delete temp;
}

// PEEK operation
int peek()
{
    if (top == NULL)
    {
        cout << "Stack is empty\n";
        return -1;
    }
    return top->data;
}

// DISPLAY stack top → bottom
void display()
{
    if (top == NULL)
    {
        cout << "Stack is empty\n";
        return;
    }

    Node *temp = top;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    // Push values 1 to 5
    for (int i = 1; i <= 5; i++)
        push(i);

    display();

    pop();
    cout << "Top: " << peek() << endl;

    display();

    return 0;
}
