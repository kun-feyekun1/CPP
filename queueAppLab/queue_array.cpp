#include <iostream>
using namespace std;

#define SIZE 5
string jobs[SIZE];
int front = -1, rear = -1;

bool isEmpty() { return front == -1; }
bool isFull() { return (rear + 1) % SIZE == front; }

void addJob(string job) {
    if (isFull()) {
        cout << "Printer Busy\n";
        return;
    }

    if (isEmpty()) front = rear = 0;
    else rear = (rear + 1) % SIZE;

    jobs[rear] = job;
}

void printJob() {
    if (isEmpty()) {
        cout << "No jobs\n";
        return;
    }

    cout << "Printing: " << jobs[front] << endl;

    if (front == rear) front = rear = -1;
    else front = (front + 1) % SIZE;
}

int main() {
    addJob("Doc1");
    addJob("Doc2");
    addJob("Doc3");

    printJob();
    printJob();
}
