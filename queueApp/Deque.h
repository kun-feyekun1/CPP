#ifndef DEQUE_H
#define DEQUE_H

class Deque {
private:
    int* arr;
    int front;
    int rear;
    int capacity;

public:
    Deque(int size);
    ~Deque();
    void insertFront(int val);
    void insertRear(int val);
    int deleteFront();
    int deleteRear();
    int peekFront();
    int peekRear();
    void display();
};

#endif
