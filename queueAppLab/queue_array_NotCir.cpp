#include <iostream>
using namespace std;

#define SIZE 5
string jobs[SIZE];
int front = -1, rear = -1;

bool isEmpty() {
    return front == -1 || front > rear;
}

bool isFull() {
    return rear == SIZE - 1;
}

void addJob(string job) {
    if (isFull()) {
        cout << "Queue Full\n";
        return;
    }

    if (isEmpty())
        front = 0;

    rear++;
    jobs[rear] = job;
}

void printJob() {
    if (isEmpty()) {
        cout << "No jobs\n";
        return;
    }

    cout << "Printing: " << jobs[front] << endl;
    front++;
}

int main() {
    addJob("Doc1");
    addJob("Doc2");
    addJob("Doc3");

    printJob();
    printJob();
}
