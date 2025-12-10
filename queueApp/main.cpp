#include <iostream>
#include "ArrayQueue.h"
#include "CircularQueue.h"
#include "LinkedListQueue.h"
#include "Deque.h"
#include "PriorityQueue.h"
using namespace std;

int main() {
    cout << "--- Array Queue ---\n";
    ArrayQueue aQ(5);
    aQ.enqueue(10); aQ.enqueue(20); aQ.enqueue(30);
    aQ.display();
    cout << "Dequeue: " << aQ.dequeue() << endl;
    aQ.display();

    cout << "\n--- Circular Queue ---\n";
    CircularQueue cQ(5);
    cQ.enqueue(1); cQ.enqueue(2); cQ.enqueue(3);
    cQ.display();
    cout << "Dequeue: " << cQ.dequeue() << endl;
    cQ.display();

    cout << "\n--- Linked List Queue ---\n";
    LinkedListQueue lQ;
    lQ.enqueue(100); lQ.enqueue(200); lQ.enqueue(300);
    lQ.display();
    cout << "Dequeue: " << lQ.dequeue() << endl;
    lQ.display();

    cout << "\n--- Deque ---\n";
    Deque dq(5);
    dq.insertRear(5); dq.insertRear(10); dq.insertFront(1);
    dq.display();
    cout << "Delete Front: " << dq.deleteFront() << endl;
    dq.display();
    cout << "Delete Rear: " << dq.deleteRear() << endl;
    dq.display();

    cout << "\n--- Priority Queue ---\n";
    PriorityQueue pq;
    pq.enqueue(Person("Alice", 25, "Female"));
    pq.enqueue(Person("Bob", 30, "Male"));
    pq.enqueue(Person("Carol", 28, "Female"));
    pq.display();

    cout << "\nDequeue by Gender (Female):\n";
    Person p = pq.dequeueByGender("Female");
    cout << p.name << endl;
    pq.display();

    cout << "\nDequeue by Age (oldest):\n";
    p = pq.dequeueByAge();
    cout << p.name << endl;
    pq.display();

    return 0;
}
