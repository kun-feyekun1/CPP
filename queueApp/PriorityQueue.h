#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <string>
#include <vector>
using namespace std;

struct Person {
    string name;
    int age;
    string gender;
    Person(string n, int a, string g);
};

class PriorityQueue {
private:
    vector<Person> queue;

public:
    void enqueue(Person p);
    Person dequeueByGender(const string& gender);
    Person dequeueByAge();
    void display();
};

#endif
