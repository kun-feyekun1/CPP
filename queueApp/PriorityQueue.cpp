#include <iostream>
#include "PriorityQueue.h"
using namespace std;

Person::Person(string n, int a, string g) : name(n), age(a), gender(g) {}

void PriorityQueue::enqueue(Person p) {
    queue.push_back(p);
}

Person PriorityQueue::dequeueByGender(const string& gender) {
    for (size_t i = 0; i < queue.size(); i++) {
        if (queue[i].gender == gender) {
            Person p = queue[i];
            queue.erase(queue.begin() + i);
            return p;
        }
    }
    cout << "No person of gender " << gender << " found.\n";
    return Person("", -1, "");
}

Person PriorityQueue::dequeueByAge() {
    if (queue.empty()) {
        cout << "Queue empty.\n";
        return Person("", -1, "");
    }
    size_t idx = 0;
    for (size_t i = 1; i < queue.size(); i++) {
        if (queue[i].age > queue[idx].age) idx = i;
    }
    Person p = queue[idx];
    queue.erase(queue.begin() + idx);
    return p;
}

void PriorityQueue::display() {
    if (queue.empty()) {
        cout << "Priority queue empty.\n";
        return;
    }
    cout << "Priority Queue:\n";
    for (auto p : queue) {
        cout << p.name << " | Age: " << p.age << " | Gender: " << p.gender << endl;
    }
}
