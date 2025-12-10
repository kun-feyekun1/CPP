
#include <iostream>
using namespace std;

const int MAX = 10;
int arr[MAX];
int front = -1;
int rear = -1;

// -------------------------------------
// Check if Queue is Full
// -------------------------------------
bool isFull() {
    return (front == 0 && rear == MAX - 1) || (rear + 1 == front);
}

// -------------------------------------
// Check if Queue is Empty
// -------------------------------------
bool isEmpty() {
    return front == -1;
}

// -------------------------------------
// ENQUEUE
// -------------------------------------
void enqueue(int value) {
    if (isFull()) {
        cout << "Queue Overflow\n";
        return;
    }

    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    arr[rear] = value;
}

// -------------------------------------
// DEQUEUE
// -------------------------------------
void dequeue() {
    if (isEmpty()) {
        cout << "Queue Underflow\n";
        return;
    }

    cout << "Dequeued: " << arr[front] << endl;

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

// -------------------------------------
// PEEK Front
// -------------------------------------
int peekFront() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return -1;
    }
    return arr[front];
}

// PEEK Rear
int peekRear() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return -1;
    }
    return arr[rear];
}

// -------------------------------------
// SIZE
// -------------------------------------
int size() {
    if (isEmpty()) return 0;
    if (rear >= front) return rear - front + 1;
    return MAX - (front - rear - 1);
}

// -------------------------------------
// SEARCH
// -------------------------------------
bool search(int value) {
    if (isEmpty()) return false;

    int i = front;
    do {
        if (arr[i] == value)
            return true;
        i = (i + 1) % MAX;
    } while (i != (rear + 1) % MAX);

    return false;
}

// -------------------------------------
// UPDATE VALUE
// -------------------------------------
void updateValue(int oldVal, int newVal) {
    if (isEmpty()) return;

    int i = front;
    do {
        if (arr[i] == oldVal) {
            arr[i] = newVal;
            return;
        }
        i = (i + 1) % MAX;
    } while (i != (rear + 1) % MAX);

    cout << "Value not found!\n";
}

// -------------------------------------
// INSERT AT POSITION (1-based)
// -------------------------------------
void insertAtPosition(int pos, int value) {
    if (pos < 1 || pos > size() + 1) {
        cout << "Invalid position!\n";
        return;
    }

    if (isFull()) {
        cout << "Queue Overflow\n";
        return;
    }

    // Special case: insert at end
    if (pos == size() + 1) {
        enqueue(value);
        return;
    }

    int n = size();
    int idx = (front + pos - 1) % MAX;

    // Shift elements to make room
    int curr = rear;
    while (curr != idx - 1) {
        int prev = (curr - 1 + MAX) % MAX;
        arr[(curr + 1) % MAX] = arr[curr];
        curr = prev;
    }

    arr[idx] = value;
    rear = (rear + 1) % MAX;
}

// -------------------------------------
// DELETE AT POSITION (1-based)
// -------------------------------------
void deleteAtPosition(int pos) {
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return;
    }

    if (pos < 1 || pos > size()) {
        cout << "Invalid position!\n";
        return;
    }

    // Delete from front
    if (pos == 1) {
        dequeue();
        return;
    }

    int idx = (front + pos - 1) % MAX;
    int curr = idx;

    while (curr != rear) {
        int next = (curr + 1) % MAX;
        arr[curr] = arr[next];
        curr = next;
    }

    // Move rear backward
    if (rear == front) {
        front = rear = -1;
    } else {
        rear = (rear - 1 + MAX) % MAX;
    }
}

// -------------------------------------
// REPLACE VALUE AT POSITION
// -------------------------------------
void replaceValueAtPosition(int pos, int newValue) {
    if (pos < 1 || pos > size()) {
        cout << "Invalid position!\n";
        return;
    }

    int idx = (front + pos - 1) % MAX;
    arr[idx] = newValue;
}

// -------------------------------------
// REVERSE QUEUE
// -------------------------------------
void reverseQueue() {
    if (isEmpty()) return;

    int i = front;
    int j = rear;

    while (true) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        if (i == j || (i + MAX - 1) % MAX == j) break;

        i = (i + 1) % MAX;
        j = (j - 1 + MAX) % MAX;
    }
}

// -------------------------------------
// DELETE ENTIRE QUEUE
// -------------------------------------
void deleteEntireQueue() {
    front = rear = -1;
}

// -------------------------------------
// DISPLAY (front → rear)
// -------------------------------------
void display() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }

    cout << "Circular Queue: ";
    int i = front;
    do {
        cout << arr[i] << " ";
        i = (i + 1) % MAX;
    } while (i != (rear + 1) % MAX);

    cout << endl;
}

// -------------------------------------
// DISPLAY REVERSE (rear → front)
// -------------------------------------
void displayReverse() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }

    cout << "Reverse Queue: ";
    int i = rear;
    while (true) {
        cout << arr[i] << " ";
        if (i == front) break;
        i = (i - 1 + MAX) % MAX;
    }
    cout << endl;
}

// -------------------------------------
// MAIN
// -------------------------------------
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    cout << "Front: " << peekFront() << endl;
    cout << "Rear: " << peekRear() << endl;

    insertAtPosition(2, 15);
    display();

    deleteAtPosition(3);
    display();

    updateValue(20, 200);
    display();

    replaceValueAtPosition(2, 999);
    display();

    reverseQueue();
    display();

    displayReverse();

    cout << "Size: " << size() << endl;

    deleteEntireQueue();
    display();

    return 0;
}






// #include <iostream>
// using namespace std;

// class CircularQueue {
// private:
//     int *arr;
//     int size;
//     int front;
//     int rear;

// public:
//     // Constructor
//     CircularQueue(int s) {
//         size = s;
//         arr = new int[size];
//         front = -1;
//         rear = -1;
//     }

//     // Check if queue is empty
//     bool isEmpty() {
//         return (front == -1);
//     }

//     // Check if queue is full
//     bool isFull() {
//         return ((rear + 1) % size == front);
//     }

//     // Enqueue operation
//     void enqueue(int value) {
//         if (isFull()) {
//             cout << "Queue Overflow! Cannot insert " << value << endl;
//             return;
//         }

//         if (isEmpty()) {
//             front = rear = 0; // First element
//         } else {
//             rear = (rear + 1) % size;
//         }

//         arr[rear] = value;
//         cout << value << " enqueued.\n";
//     }

//     // Dequeue operation
//     int dequeue() {
//         if (isEmpty()) {
//             cout << "Queue Underflow! Cannot dequeue.\n";
//             return -1;
//         }

//         int removed = arr[front];

//         if (front == rear) {
//             // Queue becomes empty
//             front = rear = -1;
//         } else {
//             front = (front + 1) % size;
//         }

//         cout << removed << " dequeued.\n";
//         return removed;
//     }

//     // Peek (front element)
//     int peek() {
//         if (isEmpty()) {
//             cout << "Queue is empty.\n";
//             return -1;
//         }
//         return arr[front];
//     }

//     // Display queue elements
//     void display() {
//         if (isEmpty()) {
//             cout << "Queue is empty.\n";
//             return;
//         }

//         cout << "Queue elements: ";
//         int i = front;
//         while (true) {
//             cout << arr[i] << " ";
//             if (i == rear)
//                 break;
//             i = (i + 1) % size;
//         }
//         cout << endl;
//     }
// };

// int main() {
//     CircularQueue q(5);

//     q.enqueue(10);
//     q.enqueue(20);
//     q.enqueue(30);
//     q.enqueue(40);
//     q.enqueue(50);

//     q.display();

//     q.dequeue();
//     q.dequeue();

//     q.display();

//     q.enqueue(60);
//     q.enqueue(70);

//     q.display();

//     cout << "Front element: " << q.peek() << endl;

//     return 0;
// }
